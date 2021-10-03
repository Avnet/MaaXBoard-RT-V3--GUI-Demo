/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "littlevgl_support.h"
#include "lvgl.h"
#if defined(FSL_RTOS_FREE_RTOS)
#include "FreeRTOS.h"
#include "semphr.h"
#endif
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_cache.h"
#include "fsl_debug_console.h"

//pf #include "fsl_gt911.h"
#include "fsl_ft5406_rt.h"
#include "avt-ili9881c.h"

#if LV_USE_GPU && LV_USE_GPU_NXP_PXP
#include "src/lv_gpu/lv_gpu_nxp_pxp.h"
#include "src/lv_gpu/lv_gpu_nxp_pxp_osa.h"
#endif

//user added
#include "globals.h"
#include "usb_peripherals.h"
#include "fsl_lpi2c.h"
#include "fsl_lpi2c_freertos.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern lpi2c_rtos_handle_t master_rtos_handle6;

/* Cache line size. */
#ifndef FSL_FEATURE_L2CACHE_LINESIZE_BYTE
#define FSL_FEATURE_L2CACHE_LINESIZE_BYTE 0
#endif
#ifndef FSL_FEATURE_L1DCACHE_LINESIZE_BYTE
#define FSL_FEATURE_L1DCACHE_LINESIZE_BYTE 0
#endif

#if (FSL_FEATURE_L2CACHE_LINESIZE_BYTE > FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#define DEMO_CACHE_LINE_SIZE FSL_FEATURE_L2CACHE_LINESIZE_BYTE
#else
#define DEMO_CACHE_LINE_SIZE FSL_FEATURE_L1DCACHE_LINESIZE_BYTE
#endif

#if (DEMO_CACHE_LINE_SIZE > 0)
#define DEMO_FB_ALIGN DEMO_CACHE_LINE_SIZE
#else
#define DEMO_FB_ALIGN 4U
#endif

#define DEMO_FB_SIZE                                                                                      \
    (((DEMO_BUFFER_WIDTH * DEMO_BUFFER_HEIGHT * DEMO_BUFFER_BYTE_PER_PIXEL) + DEMO_CACHE_LINE_SIZE - 1) & \
     ~(DEMO_CACHE_LINE_SIZE - 1))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

static void DEMO_InitTouch(void);

static bool DEMO_ReadMouse(lv_indev_drv_t *drv, lv_indev_data_t *data);
static bool DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data);

static void DEMO_BufferSwitchOffCallback(void *param, void *switchOffBuffer);

static void BOARD_PullMIPIPanelTouchResetPin(bool pullUp);

//pf static void BOARD_ConfigMIPIPanelTouchIntPin(gt911_int_pin_mode_t mode);

/*******************************************************************************
 * Variables
 ******************************************************************************/
SDK_ALIGN(static uint8_t s_frameBuffer[2][DEMO_FB_SIZE], DEMO_FB_ALIGN);

#if defined(FSL_RTOS_FREE_RTOS)
static SemaphoreHandle_t s_transferDone;
#else
static volatile bool s_transferDone;
#endif

/* static gt911_handle_t s_touchHandle;

static const gt911_config_t s_touchConfig = {
    .I2C_SendFunc     = BOARD_MIPIPanelTouch_I2C_Send,
    .I2C_ReceiveFunc  = BOARD_MIPIPanelTouch_I2C_Receive,
    .pullResetPinFunc = BOARD_PullMIPIPanelTouchResetPin,
    .intPinFunc       = BOARD_ConfigMIPIPanelTouchIntPin,
    .timeDelayMsFunc  = VIDEO_DelayMs,
    .touchPointNum    = 1,
    .i2cAddrMode      = kGT911_I2cAddrMode0,
    .intTrigMode      = kGT911_IntRisingEdge,
};
*/

/* Touch driver handle */   //pf
static ft5406_rt_handle_t touchHandle;

static int s_touchResolutionX = 720;  //pf
static int s_touchResolutionY = 1280;

/*******************************************************************************
 * Code
 ******************************************************************************/

void lv_port_pre_init(void)
{
}

void lv_port_disp_init(void)
{
    static lv_disp_buf_t disp_buf;

    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));
    lv_disp_buf_init(&disp_buf, s_frameBuffer[0], s_frameBuffer[1], LCD_WIDTH * LCD_HEIGHT);

    status_t status;
    dc_fb_info_t fbInfo;

    /*-------------------------
     * Initialize your display
     * -----------------------*/
    taskENTER_CRITICAL();
    BOARD_PrepareDisplayController();
    taskEXIT_CRITICAL();
    status = g_dc.ops->init(&g_dc);
    if (kStatus_Success != status)
    {
        assert(0);
    }

    g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &fbInfo);
    fbInfo.pixelFormat = DEMO_BUFFER_PIXEL_FORMAT;
    fbInfo.width       = DEMO_BUFFER_WIDTH;
    fbInfo.height      = DEMO_BUFFER_HEIGHT;
    fbInfo.startX      = DEMO_BUFFER_START_X;
    fbInfo.startY      = DEMO_BUFFER_START_Y;
    fbInfo.strideBytes = DEMO_BUFFER_STRIDE_BYTE;
    g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

    g_dc.ops->setCallback(&g_dc, 0, DEMO_BufferSwitchOffCallback, NULL);

#if defined(FSL_RTOS_FREE_RTOS)
    s_transferDone = xSemaphoreCreateBinary();
    if (NULL == s_transferDone)
    {
        PRINTF("Frame semaphore create failed\r\n");
        assert(0);
    }
#else
    s_transferDone = false;
#endif

    /* littlevgl starts render in frame buffer 0, so show frame buffer 1 first. */
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_frameBuffer[1]);

    /* Wait for frame buffer sent to display controller video memory. */
    if ((g_dc.ops->getProperty(&g_dc) & kDC_FB_ReserveFrameBuffer) == 0)
    {
#if defined(FSL_RTOS_FREE_RTOS)
        if (xSemaphoreTake(s_transferDone, portMAX_DELAY) != pdTRUE)
        {
            PRINTF("Wait semaphore error: s_transferDone\r\n");
            assert(0);
        }
#else
        while (false == s_transferDone)
        {
        }
#endif
    }

    g_dc.ops->enableLayer(&g_dc, 0);

    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    lv_disp_drv_t disp_drv;      /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = DEMO_FlushDisplay;

    /*Set a display buffer*/
    disp_drv.buffer = &disp_buf;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);

#if LV_USE_GPU && LV_USE_GPU_NXP_PXP
    lv_gpu_nxp_pxp_init(&pxp_default_cfg);
#endif
}

static void DEMO_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
#if defined(FSL_RTOS_FREE_RTOS)
    BaseType_t taskAwake = pdFALSE;

    xSemaphoreGiveFromISR(s_transferDone, &taskAwake);
    portYIELD_FROM_ISR(taskAwake);
#else
    s_transferDone = true;
#endif
}

static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
#if !defined(FSL_RTOS_FREE_RTOS)
    s_transferDone = false;
#endif

    DCACHE_CleanInvalidateByRange((uint32_t)color_p, DEMO_FB_SIZE);
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)color_p);

#if defined(FSL_RTOS_FREE_RTOS)
    if (xSemaphoreTake(s_transferDone, portMAX_DELAY) == pdTRUE)
    {
        /* IMPORTANT!!!
         * Inform the graphics library that you are ready with the flushing*/
        lv_disp_flush_ready(disp_drv);
    }
    else
    {
        PRINTF("Display flush failed\r\n");
        assert(0);
    }
#else
    while (false == s_transferDone)
    {
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
#endif
}

void lv_port_indev_init(void)
{
    lv_indev_drv_t indev_drv;

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad */
    DEMO_InitTouch();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = DEMO_ReadTouch;
    lv_indev_drv_register(&indev_drv);

    //testing mouse
    lv_indev_drv_t indev_drv_test;
    lv_indev_drv_init(&indev_drv_test);
    indev_drv_test.type    = LV_INDEV_TYPE_POINTER;
    indev_drv_test.read_cb = DEMO_ReadMouse;
    lv_indev_t * mouse_indev = lv_indev_drv_register(&indev_drv_test);

    LV_IMG_DECLARE(_mouse_alpha_45x45);                          /*Declare the image file.*/
    lv_obj_t * cursor_obj =  lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &_mouse_alpha_45x45);             /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);

}

static void BOARD_PullMIPIPanelTouchResetPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(BOARD_MIPI_PANEL_TOUCH_RST_GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(BOARD_MIPI_PANEL_TOUCH_RST_GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PIN, 0);
    }
}

/*
static void BOARD_ConfigMIPIPanelTouchIntPin(gt911_int_pin_mode_t mode)
{
    if (mode == kGT911_IntPinInput)
    {
        BOARD_MIPI_PANEL_TOUCH_INT_GPIO->GDIR &= ~(1UL << BOARD_MIPI_PANEL_TOUCH_INT_PIN);
    }
    else
    {
        if (mode == kGT911_IntPinPullDown)
        {
            GPIO_PinWrite(BOARD_MIPI_PANEL_TOUCH_INT_GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PIN, 0);
        }
        else
        {
            GPIO_PinWrite(BOARD_MIPI_PANEL_TOUCH_INT_GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PIN, 1);
        }

        BOARD_MIPI_PANEL_TOUCH_INT_GPIO->GDIR |= (1UL << BOARD_MIPI_PANEL_TOUCH_INT_PIN);
    }
}
*/

/*Initialize your touchpad*/
static void DEMO_InitTouch(void)
{
    status_t status;

    const gpio_pin_config_t resetPinConfig = {
        .direction = kGPIO_DigitalOutput, .outputLogic = 0, .interruptMode = kGPIO_NoIntmode};
    GPIO_PinInit(BOARD_MIPI_PANEL_TOUCH_RST_GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PIN, &resetPinConfig);

    const gpio_pin_config_t intPinConfig = {
        .direction = kGPIO_DigitalInput, .outputLogic = 0, .interruptMode = kGPIO_NoIntmode};
    GPIO_PinInit(BOARD_MIPI_PANEL_TOUCH_INT_GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PIN, &intPinConfig);

    //pf status = GT911_Init(&s_touchHandle, &s_touchConfig);


    status = FT5406_RT_Init(&touchHandle, &master_rtos_handle6);  //pf OK!

    if (kStatus_Success != status)
    {
        PRINTF("Touch IC initialization failed\r\n");
        assert(false);
    }

    //pf  GT911_GetResolution(&s_touchHandle, &s_touchResolutionX, &s_touchResolutionY);
}

/* Will be called by the library to read the touchpad */
static bool DEMO_ReadMouse(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
	int x, y;
	mouse_t mouse_instance;

	read_mouseState(&mouse_instance);
    /*Set the last pressed coordinates*/
    data->point.x = mouse_instance.x;
    data->point.y = mouse_instance.y;
    if (mouse_instance.btn&(1<<0)) // left btn clicked
    {
    	data->state = LV_INDEV_STATE_PR;
    }
    else
    {
    	data->state = LV_INDEV_STATE_REL;
    }
    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}


/* Will be called by the library to read the touchpad */
static bool DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
	static touch_event_t touch_event;
    static int touch_x = 0;
    static int touch_y = 0;

 //pf   if (kStatus_Success == GT911_GetSingleTouch(&s_touchHandle, &touch_x, &touch_y))
    if (kStatus_Success == FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y))  //pf OK!
    {
        if ((touch_event == kTouch_Down) || (touch_event == kTouch_Contact))
        {
            data->state = LV_INDEV_STATE_PR;

            //PRINTF("DEBUG DEMO_ReadTouch: LV_INDEV_STATE_PR x:%d y:%d\r\n", touch_x, touch_y);
        }
        else
        {
            data->state = LV_INDEV_STATE_REL;
            
            //PRINTF("DEBUG DEMO_ReadTouch: LV_INDEV_STATE_REL x:%d y:%d\r\n", touch_x, touch_y);
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
        
        //PRINTF("DEBUG DEMO_ReadTouch: LV_INDEV_STATE_REL x:%d y:%d\r\n", touch_x, touch_y);
    }

    /*Set the last pressed coordinates*/
    data->point.x = touch_x * DEMO_PANEL_WIDTH / s_touchResolutionX;
    data->point.y = touch_y * DEMO_PANEL_HEIGHT / s_touchResolutionY;

    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}


/*
int BOARD_Touch_Poll(void)
{
    touch_event_t touch_event;
    int touch_x;
    int touch_y;
    GUI_PID_STATE pid_state;

    if (kStatus_Success != FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y))
    {
        return 0;
    }
    else if (touch_event != kTouch_Reserved)
    {
        pid_state.x = touch_y;
        pid_state.y = touch_x;
        pid_state.Pressed = ((touch_event == kTouch_Down) || (touch_event == kTouch_Contact));
        pid_state.Layer = 0;
        GUI_TOUCH_StoreStateEx(&pid_state);
        return 1;
    }
    return 0;
}
*/

static bool touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    touch_event_t touch_event;
    static int touch_x = 0;
    static int touch_y = 0;

    if (kStatus_Success == FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y))
    {
        if ((touch_event == kTouch_Down) || (touch_event == kTouch_Contact))
        {
            data->state = LV_INDEV_STATE_PR;
            // PRINTF("DEBUG touchpad_read: LV_INDEV_STATE_PR\r\n");
        }
        else
        {
            data->state = LV_INDEV_STATE_REL;
            // PRINTF("DEBUG touchpad_read: LV_INDEV_STATE_REL\r\n");
        }
    } else {
        data->state = LV_INDEV_STATE_REL;
        // PRINTF("DEBUG touchpad_read: LV_INDEV_STATE_REL\r\n");
    }

    /*Set the last pressed coordinates*/
    data->point.x = touch_y;
    data->point.y = touch_x;

    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}

/*!
 * @brief detect display if display is connected. 1 - true, 0 - false
 */
uint8_t detect_display()
{
	uint8_t rxBuff;	/* dummy byte to read */
	BOARD_LPI2C_Init(BOARD_MIPI_PANEL_TOUCH_I2C_BASEADDR, (CLOCK_GetFreq(kCLOCK_OscRc48MDiv2)));
	if (BOARD_LPI2C_Receive(BOARD_MIPI_PANEL_TOUCH_I2C_BASEADDR, FT5406_RT_I2C_ADDRESS, 0, 0, &rxBuff, 1) != kStatus_LPI2C_Nak)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

