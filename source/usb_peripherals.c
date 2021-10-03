/*
 * usb_peripherals.c
 *
 *  Created on: May 10, 2021
 *      Author: gulziibayar
 */
#include "usb_peripherals.h"
#include "usb_host_config.h"
#include "usb_host.h"
#include "fsl_device_registers.h"
#include "usb_host_hid.h"
#include "host_keyboard_mouse.h"
#include "host_keyboard.h"
#include "host_mouse.h"
#include "clock_config.h"
#include "usb_phy.h"
#include "board.h"
#include "globals.h"
#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include "lvgl_demo.h"

/*******************************************************************************
 * Globals
 ******************************************************************************/

static QueueHandle_t *hid_devices_queue;
/*! Global variables for storing x,y coordinates of display, can be removed*/
static uint8_t mouse_btn = 0;;
int x_coordinate = 0;
int y_coordinate = 0;
extern volatile uint32_t cmdEnable;
static usb_host_handle *g_HostHandle;
struct hid_peripheral usb_devices[2] = {
		{0,0,0,0},	// mouse
		{0,0,0,0}	// keyboard
};
static mouse_t mouse_instance_t;
/*!
 * @brief host callback function.
 *
 * device attach/detach callback function.
 *
 * @param deviceHandle          device handle.
 * @param configurationHandle   attached device's configuration descriptor information.
 * @param eventCode             callback event code, please reference to enumeration host_event_t.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_NotSupported         The application don't support the configuration.
 */
static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode);

extern void USB_HostClockInit(void);
extern void USB_HostIsrEnable(void);
extern void USB_HostTaskFn(void *param);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Allocate the memory for the heap. */
#if defined(configAPPLICATION_ALLOCATED_HEAP) && (configAPPLICATION_ALLOCATED_HEAP)
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) uint8_t ucHeap[configTOTAL_HEAP_SIZE];
#endif

static lpuart_rtos_handle_t *handle;
/*******************************************************************************
 * Code
 ******************************************************************************/

void USB_OTG1_IRQHandler(void)
{
    USB_HostEhciIsrFunction(*g_HostHandle);
}

void USB_OTG2_IRQHandler(void)
{
    USB_HostEhciIsrFunction(*g_HostHandle);
}

void USB_HostClockInit(void)
{
    uint32_t usbClockFreq;
    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL,
        BOARD_USB_PHY_TXCAL45DP,
        BOARD_USB_PHY_TXCAL45DM,
    };
    usbClockFreq = 24000000;
    if (CONTROLLER_ID == kUSB_ControllerEhci0)
    {
        CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, usbClockFreq);
        CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, usbClockFreq);
    }
    else
    {
        CLOCK_EnableUsbhs1PhyPllClock(kCLOCK_Usbphy480M, usbClockFreq);
        CLOCK_EnableUsbhs1Clock(kCLOCK_Usb480M, usbClockFreq);
    }
    USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL0_CLK_HZ, &phyConfig);
}

void USB_HostIsrEnable(void)
{
    uint8_t irqNumber;

    uint8_t usbHOSTEhciIrq[] = USBHS_IRQS;
    irqNumber                = usbHOSTEhciIrq[CONTROLLER_ID - kUSB_ControllerEhci0];
/* USB_HOST_CONFIG_EHCI */

/* Install isr, set priority, and enable IRQ. */
#if defined(__GIC_PRIO_BITS)
    GIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#else
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#endif
    EnableIRQ((IRQn_Type)irqNumber);
}

void USB_HostTaskFn(void *param)
{
    USB_HostEhciTaskFunction(param);
}

/*!
 * @brief USB isr function.
 */

static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode)
{
    usb_status_t status1;
    usb_status_t status2;
    usb_status_t status = kStatus_USB_Success;

    switch (eventCode & 0x0000FFFFU)
    {
        case kUSB_HostEventAttach:
            status1 = USB_HostHidKeyboardEvent(deviceHandle, configurationHandle, eventCode);
            status2 = USB_HostHidMouseEvent(deviceHandle, configurationHandle, eventCode);
            if ((status1 == kStatus_USB_NotSupported) && (status2 == kStatus_USB_NotSupported))
            {
                status = kStatus_USB_NotSupported;
            }
            break;

        case kUSB_HostEventNotSupported:
            usb_echo("device not supported.\r\n");
            break;

        case kUSB_HostEventEnumerationDone:
            status1 = USB_HostHidKeyboardEvent(deviceHandle, configurationHandle, eventCode);
            status2 = USB_HostHidMouseEvent(deviceHandle, configurationHandle, eventCode);
            if ((status1 != kStatus_USB_Success) && (status2 != kStatus_USB_Success))
            {
                status = kStatus_USB_Error;
            }
            break;

        case kUSB_HostEventDetach:
            status1 = USB_HostHidKeyboardEvent(deviceHandle, configurationHandle, eventCode);
            status2 = USB_HostHidMouseEvent(deviceHandle, configurationHandle, eventCode);
            if ((status1 != kStatus_USB_Success) && (status2 != kStatus_USB_Success))
            {
                status = kStatus_USB_Error;
            }
            break;

        case kUSB_HostEventEnumerationFail:
            usb_echo("enumeration failed\r\n");
            break;

        default:
            break;
    }
    return status;
}

void USB_HostApplicationInit(usb_host_handle *t_hostHandle)
{
	g_HostHandle = t_hostHandle;
    usb_status_t status = kStatus_USB_Success;

    USB_HostClockInit();

#if ((defined FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT))
    SYSMPU_Enable(SYSMPU, 0);
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

    status = USB_HostInit(CONTROLLER_ID, g_HostHandle, USB_HostEvent);
    if (status != kStatus_USB_Success)
    {
        usb_echo("host init error\r\n");
        return;
    }
    USB_HostIsrEnable();

    usb_echo("host init done\r\n");
}

/*******************************************************************************
 * Freetos Task: usb host task
 * @brief USB host task for enumerating hid devices
 ******************************************************************************/
void USB_HostTask(void *param)
{
    while (1)
    {
        USB_HostTaskFn(param);
        vTaskDelay(20/portTICK_PERIOD_MS);
    }
}

/*******************************************************************************
 * Freetos Task: mouse task
 * @brief: reading mouse value from hid device
 ******************************************************************************/
void USB_HostApplicationMouseTask(void *param)
{
    while (1)
    {
        USB_HostHidMouseTask(param);
        vTaskDelay(50/portTICK_PERIOD_MS);
    }
}

/*******************************************************************************
 * Freetos Task: keyboard task
 * @brief: reading keyboard value from hid device
 ******************************************************************************/
void USB_HostApplicationKeyboardTask(void *param)
{
    while (1)
    {
        USB_HostHidKeyboardTask(param);
        vTaskDelay(50/portTICK_PERIOD_MS);
    }
}

void read_mouseState(mouse_t *mouse_i)
{
	mouse_i->x = x_coordinate;
	mouse_i->y = y_coordinate;
	mouse_i->btn = mouse_btn;
	mouse_btn = 0;
}

/*******************************************************************************
 * Freetos Task: USB_log
 * @brief receive "hid_device" structure data from queue, prints the value on the serial port.
 ******************************************************************************/
void USB_logTask(void *param)
{
	custom_usb_log_instance_t *t_usb_log = (custom_usb_log_instance_t *)param;
	hid_devices_queue = t_usb_log->hid_queue;
	handle = t_usb_log->uart_handle;
	struct hid_device usb_hid_received;
	char usb_buff[10];
    while (1)
    {
        if (xQueueReceive(*hid_devices_queue, &(usb_hid_received), portMAX_DELAY) != pdTRUE)
        {
            //PRINTF("Failed to receive queue.\r\n");
        } else {
        	if (usb_hid_received.dev_type == MOUSE_DEVICE) {
        		mouse_btn = usb_hid_received.dev_btn;
        		int16_t x_val = (int16_t)usb_hid_received.x_motion;
				int16_t y_val = (int16_t)usb_hid_received.y_motion;

				x_coordinate = x_coordinate + (int)((float)x_val*x_sensitivity);
				y_coordinate = y_coordinate + (int)((float)y_val*y_sensitivity);

				if (x_coordinate < X_MIN) {
					x_coordinate = X_MIN;
				} else if (x_coordinate > X_MAX) {
					x_coordinate = X_MAX;
				}

				if (y_coordinate < Y_MIN) {
					y_coordinate = Y_MIN;
				} else if (y_coordinate > Y_MAX) {
					y_coordinate = Y_MAX;
				}
				if (cmdEnable & (1<<mouseLogEn)) {
					sprintf(usb_buff, "%d:%d\r\n", x_coordinate, y_coordinate);
					LPUART_RTOS_Send(handle,usb_buff,strlen(usb_buff));
				}
				//usb_echo("%d %d\r\n", x_coordinate, y_coordinate);

                if (capturingMouseInputOnTA())
                {
                    sprintf(usb_buff, "%d:%d\r\n", x_coordinate, y_coordinate);
                    writeToHIDInputTextArea(usb_buff);
                }

        	} else if (usb_hid_received.dev_type == KEYBOARD_DEVICE) {
        		//usb_echo("%c", usb_hid_received.dev_btn);
				if (cmdEnable & (1<<keyboardLogEn)) {
					sprintf(usb_buff, "%c", usb_hid_received.dev_btn);
					LPUART_RTOS_Send(handle,usb_buff,strlen(usb_buff));
				}

                if (capturingKeyboardInputOnTA())
                {
                	if (usb_hid_received.dev_btn == '\b')
                	{
                		deleteLeftCharTextArea();
                	}
                	else
                	{
                		sprintf(usb_buff, "%c", usb_hid_received.dev_btn);
                		writeToHIDInputTextArea(usb_buff);
                	}
                }
        	}
        }
    }
}
