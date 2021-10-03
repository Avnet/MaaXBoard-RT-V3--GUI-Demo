/**
 * @brief - Maaxboard RT Demo
 * @Description - Demo program can be interacted with both GUI and Console.
 * LPUART1 is used at baudrate 115200 for console application. It is physically available on debug UART 3-pin header.
 * LPUART6 is used for printing debug message. It is available on 40 pin header.
 *
 * Following commands are available on console
 *--------- PERIPHERALS ----------------
 * led ***    : RGB LEDs on/off
 * i2c #      : I2C Scan (bus# 2/3/5/6)
 *--------- WIFI & LAN -----------------
 * ws         : Wifi Scan
 * wc         : Wifi Connect
 * wi         : Wifi Info
 * es         : Ethernet Scan
 * -------- USB HOST & DEV -------------
 * ul         : USB List (attached devices)
 * uk         : Keyboard Test
 * um         : Mouse Test
 *--------- AUDIO & VIDEO --------------
 * am ##      : Audio L/R output (mic# 1-4)
 *--------- UTILITY --------------------
 * stats      : RTOS Statistics
 * clr        : Clear the terminal
 * q/ctrl+c   : Abort the command
 * ? / h      : Menu Help
 */

/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "FreeRTOS.h"
#include "queue.h"
#include "event_groups.h"
#include "fsl_lpuart_freertos.h"

#include "fsl_debug_console.h"
#include "littlevgl_support.h"
#include "pin_mux.h"
#include "board.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"

#include "fsl_soc_src.h"

#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include "globals.h"
#include "demo_common.h"
#include "audio_demo.h"
#include "lvgl_demo.h"
#include "network_demo.h"
#include "usb_peripherals.h"
#include "UART_CLI.h"
#include "ether_if.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
portSTACK_TYPE *lvgl_task_stack = NULL;
TaskHandle_t lvgl_task_task_handler;

portSTACK_TYPE *wifi_task_stack = NULL;
TaskHandle_t wifi_task_task_handler;

portSTACK_TYPE *console_task_stack = NULL;
TaskHandle_t console_task_task_handler;

volatile uint32_t cmdEnable = 0;

/* Freertos queue */
static QueueHandle_t hid_devices_queue = NULL;
static QueueHandle_t wifi_commands_queue = NULL;
static QueueHandle_t wifi_response_queue = NULL;

/* This buffer is used for storing wifi SSIDs, wifi network information */
uint8_t shared_buff[2048];

/******* UART handle definition ***************/
static lpuart_rtos_handle_t uart_rtos_handle;
static struct _lpuart_handle tuart_handle;
static uint8_t background_buffer[32];

lpuart_rtos_config_t lpuart_config = {
	.base		 = DEMO_LPUART,
    .baudrate    = 115200,
    .parity      = kLPUART_ParityDisabled,
    .stopbits    = kLPUART_OneStopBit,
    .buffer      = background_buffer,
    .buffer_size = sizeof(background_buffer),
};

/******* USB HID device definition ***************/
static usb_host_handle g_HostHandle;
/*! @brief USB host mouse instance global variable */
/*! @brief USB host keyboard instance global variable */
static usb_host_keyboard_instance_t g_HostHidKeyboard;
static custom_usb_host_mouse_instance_t t_usb_host_mouse;
static custom_usb_host_keyboard_instance_t t_usb_host_keyboard;
static custom_usb_log_instance_t t_usb_log;
static custom_wifi_instance_t t_wifi_cmd;
static custom_console_instance_t t_console;

static EventGroupHandle_t event_group_demo; /*!< Freertos eventgroup for wifi, ethernet connectivity tasks */
static uint32_t perfCounter = 0; 			/*!< counter used for freeRTOS tasks runtime analysis */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
static void uart_init();

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief S1 button switch interrupt service ISR
 */
void BOARD_USER_BUTTON_IRQ_HANDLER(void)
{
    /* clear the interrupt status */
    GPIO_PortClearInterruptFlags(BOARD_USER_BUTTON_GPIO, 1U << BOARD_USER_BUTTON_GPIO_PIN);

    setInputSignal(true);

    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief PIT1 Timer interrupt service ISR
 */
void PIT1_IRQHANDLER(void)
{
	PIT_ClearStatusFlags(PIT1_PERIPHERAL, PIT1_CHANNEL_0, kPIT_TimerFlag);
	perfCounter++;
	//__DSB();
}

/*!
 * @brief Configures the PIT timer, it will be called by Freertos
 */
void AppConfigureTimerForRuntimeStats(void) {
	pit_config_t config;

	PIT_GetDefaultConfig(&config);
	config.enableRunInDebug = false;
	PIT_Init(PIT1_PERIPHERAL, &config);
	PIT_SetTimerPeriod(PIT1_PERIPHERAL, PIT1_CHANNEL_0, PIT1_CHANNEL_0_TICKS);
	PIT_EnableInterrupts(PIT1_PERIPHERAL, PIT1_CHANNEL_0, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT1_IRQN);
	PIT_StartTimer(PIT1_PERIPHERAL, PIT1_CHANNEL_0);
}

/*!
 * @brief Returns 32bit counter value. Used for freertos runtime analysis
 */
uint32_t AppGetRuntimeCounterValueFromISR(void) {
	return perfCounter;
}

/*!
 * @brief Main function
 */
int main(void)
{
    BaseType_t stat;

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_BootClockRUN();

    /*
     * Reset the displaymix, otherwise during debugging, the
     * debugger may not reset the display, then the behavior
     * is not right.
     */
    SRC_AssertSliceSoftwareReset(SRC, kSRC_DisplaySlice);

    BOARD_InitPins();
    BOARD_InitMipiPanelPins();
    BOARD_InitDebugConsole();

    if (detect_display())
    {
    	PRINTF("Display detected. Starting lvgl task\r\n");
    	BOARD_MIPIPanelTouch_I2C_Init();
    	#if defined(GUI_EN) && (GUI_EN==1)
    		/* 1. Freertos task: lvgl "Gui Guider"
    		 * displays GUI pages on 7 inch touch display. It uses lvgl library version 7.11.0  */
    	   stat = xTaskCreate(lvgl_task, "lvgl", configMINIMAL_STACK_SIZE + 800, lvgl_task_stack, tskIDLE_PRIORITY + 3, &lvgl_task_task_handler);
    	   assert(pdPASS == stat);
    	#endif
    }
    else
    {
    	PRINTF("Display not detected.\r\n");
    	BOARD_MIPIPanelTouch_I2C_Init();
    }

    /* initialize lpi2c2, lpi2c3 */
    BOARD_RTOS_I2C_Init(2);
    BOARD_RTOS_I2C_Init(3);
    /* configure uart for Maaxboard RT for console task*/
    uart_init();
	/* Init input switch GPIO. */
    EnableIRQ(BOARD_USER_BUTTON_IRQ);

    /* Freertos Queue for usb mouse and keyboards */
	hid_devices_queue = xQueueCreate(10, sizeof(struct hid_device));
	/* Enable queue view in MCUX IDE FreeRTOS TAD plugin. */
	if (hid_devices_queue != NULL)
	{
		vQueueAddToRegistry(hid_devices_queue, "usbQ");
	}

	wifi_commands_queue = xQueueCreate(10, sizeof(struct t_user_wifi_command));
	if (wifi_commands_queue != NULL)
	{
		vQueueAddToRegistry(wifi_commands_queue, "wifiQ");
	}

	wifi_response_queue = xQueueCreate(1, sizeof(uint8_t));
	/* Enable queue view in MCUX IDE FreeRTOS TAD plugin. */
	if (wifi_response_queue != NULL)
	{
		vQueueAddToRegistry(wifi_response_queue, "wResQ");
	}
	event_group_demo = xEventGroupCreate();

	PRINTF("Debug Session");
	SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

	/******** Freertos task declarations ********/
    os_setup_tick_function(vApplicationTickHook_lvgl);

#if defined(WIFI_EN) && (WIFI_EN==1)
    /* 2. Freertos task: wifi
     * @brief ssid scan, wifi connect to ssid (hardcoded), get wifi network info*/
	t_wifi_cmd.cmd_queue = &wifi_commands_queue;
	t_wifi_cmd.event_group_wifi = &event_group_demo;
	t_wifi_cmd.wifi_resQ = &wifi_response_queue;
    stat = xTaskCreate(wifi_task, "wifi", configMINIMAL_STACK_SIZE + 800, &t_wifi_cmd, tskIDLE_PRIORITY + 4, &wifi_task_task_handler);
    assert(pdPASS == stat);
#endif

	/* must be called before starting ethernet tasks. */
	dual_eth_configuration();

#if defined(ETH100MB_EN) && (ETH100MB_EN==1)
	/* 3. Freertos task: eth_100Mb
	 * @brief dhcp client running to get ip address */
	stat = xTaskCreate(eth_100m_task, "eth_100Mb", configMINIMAL_STACK_SIZE + 200, &event_group_demo, 3, NULL);
	assert(pdPASS == stat);
#endif

#if defined(ETH1GB_EN) && (ETH1GB_EN==1)
	/* 4. Freertos task: eth_1Gb
	 * @brief dhcp client running to get ip address */
	stat = xTaskCreate(eth_1g_task, "eth_1Gb", configMINIMAL_STACK_SIZE + 200, &event_group_demo, 3, NULL);
	assert(pdPASS == stat);
#endif

#if defined(USB_PERIPH_EN) && (USB_PERIPH_EN==1)
	/* 5. Freertos task: usb host task
	 * @brief: USB host task for enumerating hid devices */
	USB_HostApplicationInit(&g_HostHandle);
	stat = xTaskCreate(USB_HostTask, "usb host task", 2000L / sizeof(portSTACK_TYPE), g_HostHandle, 4, NULL);
	assert(pdPASS == stat);

	/* 6. Freertos task: mouse task
	 * @brief: reading mouse value from hid device */
	t_usb_host_mouse.hid_queue = &hid_devices_queue;
	stat = xTaskCreate(USB_HostApplicationMouseTask, "mouse task", 2000L / sizeof(portSTACK_TYPE), &t_usb_host_mouse, 3,
					NULL);
	assert(pdPASS == stat);

	/* 7. Freertos task: keyboard task
	 * @brief: reading keyboard value from hid device */
	t_usb_host_keyboard.hid_queue = &hid_devices_queue;
	t_usb_host_keyboard.host_hid_keyboard = &g_HostHidKeyboard;
	stat = xTaskCreate(USB_HostApplicationKeyboardTask, "keyboard task", 2000L / sizeof(portSTACK_TYPE),
					&t_usb_host_keyboard, 3, NULL);
	assert(pdPASS == stat);

	/* 8. Freertos task: USB_log
	 * @brief: logs mouse, keyboard values on the console screen */
	t_usb_log.hid_queue = &hid_devices_queue;
	t_usb_log.uart_handle = &uart_rtos_handle;
	stat = xTaskCreate(USB_logTask, "USB_log", configMINIMAL_STACK_SIZE + 166, &t_usb_log, 2, NULL);
	assert(pdPASS == stat);

#endif

#if defined(CONSOLE_EN) && (CONSOLE_EN==1)
	/* 9. Freertos task: Console_task
	 * @brief: console application using lpuart1 peripheral */
    t_console.cmd_queue = &wifi_commands_queue;
    t_console.wifi_resQ = &wifi_response_queue;
    t_console.uart_handle = &uart_rtos_handle;
    t_console.event_group_wifi = &event_group_demo;
    stat = xTaskCreate(console_task, "Console_task", configMINIMAL_STACK_SIZE + 200, &t_console, 3, NULL);
    assert(pdPASS == stat);
#endif

#if defined(AUDIO_EN) && (AUDIO_EN==1)
	/* Audio task */
	/* 10. Freertos task: av_task
	 * @brief: read 4 microphones, output selected mic to audio codec */
    stat = xTaskCreate(audio_task_init, "av_task", configMINIMAL_STACK_SIZE + 200, NULL, 3, NULL);
    assert(pdPASS == stat);
#endif
    /* Init scheduler */
    vTaskStartScheduler();

    for (;;)
    {
    } /* should never get here */
}

static void uart_init()
{
	NVIC_SetPriority(DEMO_LPUART_IRQn, 5);
	lpuart_config.srcclk = DEMO_LPUART_CLK_FREQ;
	LPUART_RTOS_Init(&uart_rtos_handle, &tuart_handle, &lpuart_config);
}

/*!
 * @brief Malloc failed hook.
 */
void vApplicationMallocFailedHook(void)
{
    for (;;)
        ;
}

/*!
 * @brief Stack overflow hook.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)pcTaskName;
    (void)xTask;

    for (;;)
        ;
}
