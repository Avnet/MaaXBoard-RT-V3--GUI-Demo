/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016, 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_host_config.h"
#include "usb_host.h"
#include "usb_host_hid.h"
#include "host_keyboard_mouse.h"
#include "host_mouse.h"
#include "usb_peripherals.h"
#include "globals.h"
#include "lvgl_demo.h"
#include "HIDParser.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

static QueueHandle_t *hid_devices_queue;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief process hid data and print mouse action.
 *
 * @param buffer   hid data buffer.
 */
static void USB_HostMouseProcessBuffer(HID_ReportInfo_t *hid_report ,uint8_t *buffer);

/*!
 * @brief host mouse control transfer callback.
 *
 * This function is used as callback function for control transfer .
 *
 * @param param      the host mouse instance pointer.
 * @param data       data buffer pointer.
 * @param dataLength data length.
 * @status         transfer result status.
 */
static void USB_HostHidControlCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status);

/*!
 * @brief host mouse interrupt in transfer callback.
 *
 * This function is used as callback function when call USB_HostHidRecv .
 *
 * @param param      the host mouse instance pointer.
 * @param data       data buffer pointer.
 * @param dataLength data length.
 * @status           transfer result status.
 */
static void USB_HostHidInCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status);

/*******************************************************************************
 * Variables
 ******************************************************************************/

USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
static uint8_t s_MouseBuffer[HID_BUFFER_SIZE]; /*!< use to receive report descriptor and data */
static usb_host_mouse_instance_t *head_mouse_inst, *curr_mouse_inst;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*Host hid example doesn't support HID report descriptor analysis, this example assume that the received data are sent
 * by specific order. */
static void USB_HostMouseProcessBuffer(HID_ReportInfo_t *hid_report ,uint8_t *buffer)
{
	struct hid_device mouse_dev;
	int16_t temp = 0;
	mouse_dev.dev_type = MOUSE_DEVICE;
	int index = 0;
	int items = 0;
	if (hid_report->UsingReportIDs == true)
	{
		index++;
	}

	/* find buttons and reserved bits */
	while(hid_report->ReportItems[items].Attributes.BitSize == 1)
	{
		items++;
	}

	mouse_dev.dev_btn = buffer[index];
	index = index + (items/8);

	/* next item must be X and Y */
	if (hid_report->ReportItems[items].Attributes.BitSize == 8)
	{
		temp = 0;
		temp |= buffer[index++];
		temp = temp & 0x80 ? temp | 0xFF00 : temp;
		mouse_dev.x_motion = temp;

		temp = 0;
		temp = buffer[index++];
		temp = temp & 0x80 ? temp | 0xFF00 : temp;
		mouse_dev.y_motion = temp;
	}
	else if (hid_report->ReportItems[items].Attributes.BitSize == 12)
	{
		temp = 0;
		temp |= buffer[index++];
		temp |= (buffer[index] & 0x0F) << 8;
		temp = ( temp & 0x800 ? temp | 0xf000 : temp );
		mouse_dev.x_motion = temp;

		temp = 0;
		temp |= (buffer[index++] & 0xF0) >> 4;
		temp |= (buffer[index++]) << 4;
		temp = ( temp & 0x800 ? temp | 0xf000 : temp );
		mouse_dev.y_motion = temp;
	}
	else
	{
		mouse_dev.x_motion = (buffer[index]>>8) | ((buffer[index+1]<<8));
		mouse_dev.y_motion = (buffer[index+2]>>8) | ((buffer[index+3]<<8));
	}

	/* send the mouse state value to hid_devices_queue */
	xQueueSend(*hid_devices_queue, (void *) &mouse_dev, 10);
}

static void USB_HostHidControlCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status)
{
    usb_host_mouse_instance_t *mouseInstance = (usb_host_mouse_instance_t *)param;

    if (mouseInstance->runWaitState == kUSB_HostHidRunWaitSetInterface) /* set interface finish */
    {
        mouseInstance->runState = kUSB_HostHidRunSetInterfaceDone;
    }
    else if (mouseInstance->runWaitState == kUSB_HostHidRunWaitSetIdle) /* hid set idle finish */
    {
        mouseInstance->runState = kUSB_HostHidRunSetIdleDone;
    }
    else if (mouseInstance->runWaitState ==
             kUSB_HostHidRunWaitGetReportDescriptor) /* hid get report descriptor finish */
    {
        mouseInstance->runState = kUSB_HostHidRunGetReportDescriptorDone;
        USB_ProcessHIDReport(data, dataLength, &(mouseInstance->hid_report)); /* parse the hid report descriptor */
    }
    else if (mouseInstance->runWaitState == kUSB_HostHidRunWaitSetProtocol) /* hid set protocol finish */
    {
        mouseInstance->runState = kUSB_HostHidRunSetProtocolDone;
    }
    else
    {
    }
}

static void USB_HostHidInCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status)
{
    usb_host_mouse_instance_t *mouseInstance = (usb_host_mouse_instance_t *)param;

    if (mouseInstance->runWaitState == kUSB_HostHidRunWaitDataReceived)
    {
        if (mouseInstance->deviceState == kStatus_DEV_Attached)
        {
            if (status == kStatus_USB_Success)
            {
                mouseInstance->runState = kUSB_HostHidRunDataReceived; /* go to process data */
            }
            else
            {
                mouseInstance->runState = kUSB_HostHidRunPrimeDataReceive; /* go to prime next receiving */
            }
        }
    }
}

void* USB_getMouseInstanceHead()
{
	return head_mouse_inst;
}


void USB_HostHidMouseTask(void *param)
{
    usb_host_hid_descriptor_t *hidDescriptor;
    uint32_t mouseReportLength = 0;
    uint8_t *descriptor;
    uint32_t endPosition;

    custom_usb_host_mouse_instance_t *mouse_struct = (custom_usb_host_mouse_instance_t *)param;
    hid_devices_queue = mouse_struct->hid_queue;

    curr_mouse_inst = head_mouse_inst;
    usb_host_mouse_instance_t *mouseInstance;

    while(curr_mouse_inst != NULL)
    {
    	mouseInstance = curr_mouse_inst;
		/* device state changes, process once for each state */
		if (mouseInstance->deviceState != mouseInstance->prevState)
		{
			mouseInstance->prevState = mouseInstance->deviceState;
			switch (mouseInstance->deviceState)
			{
				case kStatus_DEV_Idle:
					break;

				case kStatus_DEV_Attached: /* deivce is attached and numeration is done */
					mouseInstance->runState = kUSB_HostHidRunSetInterface;
					/* hid class initialization */
					if (USB_HostHidInit(mouseInstance->deviceHandle, &mouseInstance->classHandle) != kStatus_USB_Success)
					{
						usb_echo("host hid class initialize fail\r\n");
					}
					else
					{
						usb_echo("mouse attached\r\n");
					}
					break;

				case kStatus_DEV_Detached: /* device is detached */
					mouseInstance->deviceState = kStatus_DEV_Idle;
					mouseInstance->runState    = kUSB_HostHidRunIdle;
					USB_HostHidDeinit(mouseInstance->deviceHandle,
									  mouseInstance->classHandle); /* hid class de-initialization */
					mouseInstance->classHandle = NULL;

					// remove the node from the list
					curr_mouse_inst = head_mouse_inst;
					usb_host_mouse_instance_t *prev_mouse_inst = NULL;
					while(curr_mouse_inst != NULL)
					{
						if (curr_mouse_inst == mouseInstance)
						{
							if (prev_mouse_inst == NULL)
							{
								head_mouse_inst = curr_mouse_inst->next; /* update the list HEAD */
								vPortFree(curr_mouse_inst);
								curr_mouse_inst = head_mouse_inst;
							}
							else
							{
								prev_mouse_inst->next = curr_mouse_inst->next;
								vPortFree(curr_mouse_inst);
								curr_mouse_inst = prev_mouse_inst->next;
							}
							break;
						}
						else
						{
							prev_mouse_inst = curr_mouse_inst;
							curr_mouse_inst = curr_mouse_inst->next;
						}
					}

					usb_echo("mouse detached\r\n");
					usb_devices[0].deviceExist = 0;

					setHIDsRefreshed();
					continue;
					//break;

				default:
					break;
			}
		}

		/* run state */
		switch (mouseInstance->runState)
		{
			case kUSB_HostHidRunIdle:
				break;

			case kUSB_HostHidRunSetInterface: /* 1. set hid interface */
				mouseInstance->runWaitState = kUSB_HostHidRunWaitSetInterface;
				mouseInstance->runState     = kUSB_HostHidRunIdle;
				if (USB_HostHidSetInterface(mouseInstance->classHandle, mouseInstance->interfaceHandle, 0,
											USB_HostHidControlCallback, mouseInstance) != kStatus_USB_Success)
				{
					usb_echo("set interface error\r\n");
				}
				break;

			case kUSB_HostHidRunSetInterfaceDone: /* 2. hid set idle */
				mouseInstance->maxPacketSize =
					USB_HostHidGetPacketsize(mouseInstance->classHandle, USB_ENDPOINT_INTERRUPT, USB_IN);

				/* first: set idle */
				mouseInstance->runWaitState = kUSB_HostHidRunWaitSetIdle;
				mouseInstance->runState     = kUSB_HostHidRunIdle;
				if (USB_HostHidSetIdle(mouseInstance->classHandle, 0, 0, USB_HostHidControlCallback, mouseInstance) !=
					kStatus_USB_Success)
				{
					usb_echo("Error in USB_HostHidSetIdle\r\n");
				}
				break;

			case kUSB_HostHidRunSetIdleDone: /* 3. hid get report descriptor */
				/* get report descriptor's length */
				hidDescriptor = NULL;
				descriptor    = (uint8_t *)((usb_host_interface_t *)mouseInstance->interfaceHandle)->interfaceExtension;
				endPosition   = (uint32_t)descriptor +
							  ((usb_host_interface_t *)mouseInstance->interfaceHandle)->interfaceExtensionLength;

				while ((uint32_t)descriptor < endPosition)
				{
					if (*(descriptor + 1) == USB_DESCRIPTOR_TYPE_HID) /* descriptor type */
					{
						hidDescriptor = (usb_host_hid_descriptor_t *)descriptor;
						break;
					}
					else
					{
						descriptor = (uint8_t *)((uint32_t)descriptor + (*descriptor)); /* next descriptor */
					}
				}

				if (hidDescriptor != NULL)
				{
					usb_host_hid_class_descriptor_t *hidClassDescriptor;
					hidClassDescriptor = (usb_host_hid_class_descriptor_t *)&(hidDescriptor->bHidDescriptorType);
					for (uint8_t index = 0; index < hidDescriptor->bNumDescriptors; ++index)
					{
						hidClassDescriptor += index;
						if (hidClassDescriptor->bHidDescriptorType == USB_DESCRIPTOR_TYPE_HID_REPORT)
						{
							mouseReportLength =
								(uint16_t)USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(hidClassDescriptor->wDescriptorLength);
							break;
						}
					}
				}
				if (mouseReportLength > HID_BUFFER_SIZE)
				{
					usb_echo("hid buffer is too small\r\n");
					mouseInstance->runState = kUSB_HostHidRunIdle;
					return;
				}

				if (mouseReportLength > 0) /* when report descriptor length is zero, go to next step */
				{
					mouseInstance->runWaitState = kUSB_HostHidRunWaitGetReportDescriptor;
					mouseInstance->runState     = kUSB_HostHidRunIdle;
					/* second: get report descriptor */
					USB_HostHidGetReportDescriptor(mouseInstance->classHandle, mouseInstance->mouseBuffer,
												   mouseReportLength, USB_HostHidControlCallback, mouseInstance);
					break;
				}

			case kUSB_HostHidRunGetReportDescriptorDone: /* 4. hid set protocol */
				mouseInstance->runWaitState = kUSB_HostHidRunWaitSetProtocol;
				mouseInstance->runState     = kUSB_HostHidRunIdle;
				/* third: set protocol */
				if (USB_HostHidSetProtocol(mouseInstance->classHandle, USB_HOST_HID_REQUEST_PROTOCOL_REPORT,
										   USB_HostHidControlCallback, mouseInstance) != kStatus_USB_Success)
				{
					usb_echo("Error in USB_HostHidSetProtocol\r\n");
				}
				break;

			case kUSB_HostHidRunSetProtocolDone: /* 5. start to receive data */
				mouseInstance->runWaitState = kUSB_HostHidRunWaitDataReceived;
				mouseInstance->runState     = kUSB_HostHidRunIdle;
				if (USB_HostHidRecv(mouseInstance->classHandle, mouseInstance->mouseBuffer, mouseInstance->maxPacketSize,
									USB_HostHidInCallback, mouseInstance) != kStatus_USB_Success)
				{
					usb_echo("Error in USB_HostHidRecv\r\n");
				}
				break;

			case kUSB_HostHidRunDataReceived: /* process received data and receive next data */
				USB_HostMouseProcessBuffer(&(mouseInstance->hid_report), mouseInstance->mouseBuffer);

				mouseInstance->runWaitState = kUSB_HostHidRunWaitDataReceived;
				mouseInstance->runState     = kUSB_HostHidRunIdle;
				if (USB_HostHidRecv(mouseInstance->classHandle, mouseInstance->mouseBuffer, mouseInstance->maxPacketSize,
									USB_HostHidInCallback, mouseInstance) != kStatus_USB_Success)
				{
					usb_echo("Error in USB_HostHidRecv\r\n");
				}
				break;

			case kUSB_HostHidRunPrimeDataReceive: /* receive data */
				mouseInstance->runWaitState = kUSB_HostHidRunWaitDataReceived;
				mouseInstance->runState     = kUSB_HostHidRunIdle;
				if (USB_HostHidRecv(mouseInstance->classHandle, mouseInstance->mouseBuffer, mouseInstance->maxPacketSize,
									USB_HostHidInCallback, mouseInstance) != kStatus_USB_Success)
				{
					usb_echo("Error in USB_HostHidRecv\r\n");
				}
				break;

			default:
				break;
		}
		curr_mouse_inst = curr_mouse_inst->next;
    }
}

usb_status_t USB_HostHidMouseEvent(usb_device_handle deviceHandle,
                                   usb_host_configuration_handle configurationHandle,
                                   uint32_t eventCode)
{
    usb_status_t status = kStatus_USB_Success;
    uint8_t id;
    usb_host_configuration_t *configuration;
    uint8_t interfaceIndex;
    usb_host_interface_t *interface;
    uint32_t infoValue;

    switch (eventCode)
    {
        case kUSB_HostEventAttach:
            /* judge whether is configurationHandle supported */
            configuration = (usb_host_configuration_t *)configurationHandle;
            for (interfaceIndex = 0; interfaceIndex < configuration->interfaceCount; ++interfaceIndex)
            {
                interface = &configuration->interfaceList[interfaceIndex];
                id        = interface->interfaceDesc->bInterfaceClass;
                if (id != USB_HOST_HID_CLASS_CODE)
                {
                    continue;
                }
                id = interface->interfaceDesc->bInterfaceSubClass;
                if ((id != USB_HOST_HID_SUBCLASS_CODE_NONE) && (id != USB_HOST_HID_SUBCLASS_CODE_BOOT))
                {
                    continue;
                }
                id = interface->interfaceDesc->bInterfaceProtocol;
                if (id != USB_HOST_HID_PROTOCOL_MOUSE)
                {
                    continue;
                }
                else
                {
                	if (head_mouse_inst == NULL) /* empty list */
                	{
                		curr_mouse_inst = pvPortMalloc(sizeof(usb_host_mouse_instance_t));
						curr_mouse_inst->mouseBuffer     = s_MouseBuffer;
						curr_mouse_inst->deviceHandle    = deviceHandle;
						curr_mouse_inst->interfaceHandle = interface;
						curr_mouse_inst->configHandle    = configurationHandle;
						curr_mouse_inst->next = NULL;
						head_mouse_inst = curr_mouse_inst;
                	}
                	else
                	{
                		curr_mouse_inst = head_mouse_inst;
                		while (curr_mouse_inst->next!=NULL)
						{
							curr_mouse_inst = curr_mouse_inst->next;
						}
						curr_mouse_inst->next = pvPortMalloc(sizeof(usb_host_mouse_instance_t));
						curr_mouse_inst->next->mouseBuffer     = s_MouseBuffer;
						curr_mouse_inst->next->deviceHandle    = deviceHandle;
						curr_mouse_inst->next->interfaceHandle = interface;
						curr_mouse_inst->next->configHandle    = configurationHandle;
						curr_mouse_inst->next->next = NULL;
                	}
                	return kStatus_USB_Success;
                }
            }
            status = kStatus_USB_NotSupported;
            break;

        case kUSB_HostEventNotSupported:
            break;

        case kUSB_HostEventEnumerationDone:

        	curr_mouse_inst = head_mouse_inst;
        	while(curr_mouse_inst != NULL)
        	{
        		if (curr_mouse_inst->configHandle == configurationHandle)
        		{
        			if ((curr_mouse_inst->deviceHandle != NULL) && (curr_mouse_inst->interfaceHandle != NULL))
					{
						/* the device enumeration is done */
						if (curr_mouse_inst->deviceState == kStatus_DEV_Idle)
						{
							curr_mouse_inst->deviceState = kStatus_DEV_Attached;
							usb_devices[0].deviceExist = 1;
							USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDevicePID, &infoValue);
							usb_devices[0].devicePid = infoValue;
							usb_echo("hid mouse attached:pid=0x%x", infoValue);
							USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceVID, &infoValue);
							usb_devices[0].deviceVid = infoValue;
							usb_echo("vid=0x%x ", infoValue);
							USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceAddress, &infoValue);
							usb_devices[0].address = infoValue;
							usb_echo("address=%d\r\n", infoValue);

							setHIDsRefreshed();
						}
						else
						{
							usb_echo("not idle mouse instance\r\n");
							status = kStatus_USB_Error;
						}
					}
        			break;
        		}
        		curr_mouse_inst = curr_mouse_inst->next;
        	}
            break;

        case kUSB_HostEventDetach:
        	curr_mouse_inst = head_mouse_inst;
        	while(curr_mouse_inst != NULL)
        	{
        		if (curr_mouse_inst->configHandle == configurationHandle)
				{
					/* the device is detached */
        			curr_mouse_inst->configHandle = NULL;
					if (curr_mouse_inst->deviceState != kStatus_DEV_Idle)
					{
						curr_mouse_inst->deviceState = kStatus_DEV_Detached;
					}
					break;
				}
        		curr_mouse_inst = curr_mouse_inst->next;
        	}
            break;

        default:
            break;
    }
    return status;
}
