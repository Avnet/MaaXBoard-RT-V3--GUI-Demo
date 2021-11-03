/*
 * UART_CLI.c
 *
 *  Created on: May 14, 2021
 *      Author: gulziibayar
 */

/* @Brief
 * MaaxBoard RT CLI use LPUART1 on J17 Debug UART 3 pin header.
 * Adding new command:
 * 1. create the function with these 3 parameters. pcWriteBuffer is the output buffer sending string to console,
 * 	  after command execution. Look for other functions.
 * 		static BaseType_t newFunction( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
 * 		{}
 * 2. create the new struct like below
 * 		static const CLI_Command_Definition_t taskNewFuncCommandStruct =
 *		{
 *			"newfunc",
 *			"--------- UTILITY --------------------\r\n"
 *			" newfunc      : newfunc description \r\n",
 *			newFunction,
 *			0
 *		};
 * 3. FreeRTOS_CLIRegisterCommand( &taskNewFuncCommandStruct )
 *
 * For more: https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_CLI/FreeRTOS_Plus_Command_Line_Interface.html
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

#include "fsl_debug_console.h"
#include <expansion_i2c.h>
#include "UART_CLI.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h"
#include "board.h"
#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include "FreeRTOS_CLI.h"
#include <stdio.h>
#include "usb_peripherals.h"
#include "globals.h"
#include "fsl_lpuart.h"
#include "network_demo.h"
#include "wlan.h"
#include "demo_common.h"
#include "lwip/tcpip.h"
#include "lwip/inet.h"
#include "audio_demo.h"
#include "host_mouse.h"
/*******************************************************************************
 * Globals
 ******************************************************************************/

static uint8_t i2cScannedNodes[16];
static lpuart_rtos_handle_t *handle;
static QueueHandle_t *wifi_cmd_queue;
static QueueHandle_t *wifi_response_queue;
static EventGroupHandle_t *event_group_wifi;

/* ethernet */
extern ip_ro_t eth_100mb_addr;
extern ip_ro_t eth_1g_addr;
ip_ro_t *eth_instance;

static usb_host_mouse_instance_t *curr_mouse_inst;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Task priorities. */
#define uart_task_PRIORITY (configMAX_PRIORITIES - 1)

#define MAX_INPUT_LENGTH    50
//#define MAX_OUTPUT_LENGTH   configCOMMAND_INT_MAX_OUTPUT_SIZE
#define MAX_OUTPUT_LENGTH   128
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* Constant TEXT for cli */

#if defined(__FAT_BUILD__)
const char *TEXT_WELCOME            = "**** FACTORY TESTER ****\r\n>";
#else
const char *TEXT_WELCOME            = "**** MaaxBoard RT CLI ****\r\n>";
#endif

const char *TEXT_ABORT_CMD			= "\r\n***Command Aborted****\r\n>";
const char *TEXT_BUFFER_OVERRUN     = "\r\nRing buffer overrun!\r\n";
const char *TEXT_HW_OVERRUN 		= "\r\nHardware buffer overrun!\r\n";
const char *TEXT_VT100_CLEARSCREEN  = "\033[2J\033[H";
const char *TEXT_SCAN_I2C			= "\r\nList of i2c addresses:\r\n";
const char *TEXT_LIST_USB			= "\r\nList of USB devices:\r\n";
const char *TEXT_MOUSE_DEMO		    = "\r\nMove the mouse:\r\n";
const char *TEXT_KBOARD_DEMO		= "\r\nType Keyboard:\r\n";
const char *TEXT_LED_ERROR			= "\r\nParam error: eg: led 101\r\n";
const char *TEXT_AUDIO_ERROR		= "\r\nParam error: eg: am 01 (L->empty, R->mic1, Note: L!=R; 0-no sound)\r\n";
const char *TEXT_I2C_ERROR			= "\r\nParam error: eg: i2c 3 (allows scan of I2C buses 2,3,5,6)\r\n";
const char *TEXT_ETH_ERROR			= "\r\nParam error: eg: es 0,1 (to scan 100M or 1G Ethernet port)\r\n";
const char *TEXT_CMD_ERROR			= "\r\nCommand Error\r\n";
const char *TEXT_FREETOS_STATS		= "\r\nTask                    Abs Time        %Time\r\n"
										   "____________________________________________\r\n";

/*******************************************************************************
 * Code
 ******************************************************************************/

extern volatile uint32_t cmdEnable;
// pointer used points to allocated temporary memory on the heap.
static void *ptr_temp = NULL;
static char *ptr_aux = NULL;
static volatile EventBits_t bits;
static struct t_user_wifi_command wifi_cmd_toSend;
static struct wlan_network network;

/*!
 * @brief Application entry point.
 */

/* Utility function prototypes */
static uint16_t copyTillNewLine(char * dest, char *src);
static int print_address(struct wlan_ip_config *addr, enum wlan_bss_role role, uint8_t *printBuff, int length);

/* Console functions starts here */

/*****************************************************************************\
 * Function:    clearCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function clears the screen. It is run by the CLI interpreter
\*****************************************************************************/
static BaseType_t clearCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;

    const char *clearScreen = TEXT_VT100_CLEARSCREEN;
    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,&clearScreen[processed],xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    processed = processed + xWriteBufferLen-1;
    if(processed < (int)strlen(clearScreen))
        return pdTRUE;

    processed = 0;
    return pdFALSE;
}

/*****************************************************************************\
 * Function:    listUSBCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function prints lists all the USB hid devices on the console.
\*****************************************************************************/
static BaseType_t listUSBCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;
    int length = 0;
    BaseType_t xReturn;
    if (processed==0)
    {
    	length += sprintf(pcWriteBuffer+length, "\r\nList Of USB devices:\r\n");
    	curr_mouse_inst = (usb_host_mouse_instance_t *)USB_getMouseInstanceHead();
    	processed++;
    	xReturn = pdTRUE;
    }
    else if (processed == 1)
    {
    	if (curr_mouse_inst != NULL)
    	{
    		/* print all the mouse nodes in the list */
    		uint32_t pid_t, vid_t, address_t;
    		USB_HostHelperGetPeripheralInformation(curr_mouse_inst->deviceHandle, kUSB_HostGetDevicePID, &pid_t);
			USB_HostHelperGetPeripheralInformation(curr_mouse_inst->deviceHandle, kUSB_HostGetDeviceVID, &vid_t);
			USB_HostHelperGetPeripheralInformation(curr_mouse_inst->deviceHandle, kUSB_HostGetDeviceAddress, &address_t);

			length += sprintf(pcWriteBuffer+length, "hid mouse: pid=0x%x vid=0x%x addr=%d\r\n",
					pid_t, vid_t, address_t);
			curr_mouse_inst = curr_mouse_inst->next;
    	}
    	else
    	{
    		pcWriteBuffer[0] = 0;
    		processed++;
    	}
    	xReturn = pdTRUE;
    }
    else
    {
        if (usb_devices[1].deviceExist) {
        	sprintf(pcWriteBuffer+strlen(pcWriteBuffer), "hid keyboard attached:pid=0x%x vid=0x%x addr=%d\r\n",
            		usb_devices[1].devicePid, usb_devices[1].deviceVid, usb_devices[1].address);
        }
        processed = 0;
        xReturn = pdFALSE;
    }

    pcWriteBuffer[xWriteBufferLen-1]=0;
    return xReturn;
}

/*****************************************************************************\
 * Function:    scanCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function prints discovered i2c nodes on the console.
\*****************************************************************************/
static BaseType_t scanCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;
    BaseType_t xReturn;
    uint16_t offset;
    // first time calling this function
    if (processed==0)
    {
    	int8_t *pcParameter1;
    	BaseType_t xParameter1StringLength;

    	pcParameter1 = (int8_t *)FreeRTOS_CLIGetParameter
    					   (
    						 /* The command string itself. */
    						 pcCommandString,
    						 /* Return the first parameter. */
    						 1,
    						 /* Store the parameter string length. */
    						 &xParameter1StringLength
    					   );
    	/* Terminate parameter. */
    	pcParameter1[ xParameter1StringLength ] = 0x00;

    	uint8_t validInput = 1;
    	int x = atoi(pcParameter1);
    	/* input parameter validation */
    	if (!valid_i2c_index(x))
    	{
    		// Only allowed to write up top xWriteBufferLen bytes ...
    		strncpy(pcWriteBuffer,TEXT_I2C_ERROR,xWriteBufferLen-1);
    		pcWriteBuffer[xWriteBufferLen-1]=0;

    		return pdFALSE;
    	}

    	scan_i2c_bus(select_i2c_bus(x), i2cScannedNodes);
    	// i2cScannedNodes stores the all the discovered address info.
        const char *text = TEXT_SCAN_I2C;
        // Only allowed to write up top xWriteBufferLen bytes ...
        strncpy(pcWriteBuffer,&text[0],xWriteBufferLen-1);
    	strncpy(pcWriteBuffer+strlen(pcWriteBuffer), "   ", 4);
    	offset = strlen(pcWriteBuffer);
    	for(int i=0;i<0x10;i++)
    	{
    		sprintf(pcWriteBuffer+offset+i*3, "%02X ", i);
    	}
    	processed++;
    	xReturn = pdTRUE;
    } else if (processed < 9)
    {
    	uint8_t index = 0;
    	uint8_t bit_pos = 0;
    	sprintf(pcWriteBuffer, "\r\n%02X ", (processed-1)<<4);
    	offset = strlen(pcWriteBuffer);
    	for (int i2caddress=0; i2caddress<0x10; i2caddress++)
    	{
    		uint8_t curr_node = (processed-1)*16+i2caddress;
    		index = curr_node/8;
    		bit_pos = 7-(curr_node%8);
    		if (i2cScannedNodes[index] & (1<<bit_pos))
    		{
    			sprintf(pcWriteBuffer+offset+i2caddress*3, "%02X ", curr_node);
    		} else
    		{
    			strncpy(pcWriteBuffer+offset+i2caddress*3, "-- ", 4);
    		}
    	}
    	processed++;
    	xReturn = pdTRUE;
    } else
    {
    	processed = 0;
    	pcWriteBuffer[0]=0;
    	xReturn = pdFALSE;
    }

    return xReturn;
}

/*****************************************************************************\
 * Function:    mouseCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function enables printing mouse coordinates on the console.
\*****************************************************************************/
static BaseType_t mouseCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;

    const char *text = TEXT_MOUSE_DEMO;
    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,&text[processed],xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    cmdEnable |= (1<<mouseLogEn);
    return pdFALSE;
}

/*****************************************************************************\
 * Function:    keyboardCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function enables printing keyboard keys on the console.
\*****************************************************************************/
static BaseType_t keyboardCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;

    const char *text = TEXT_KBOARD_DEMO;
    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,&text[processed],xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    cmdEnable |= (1<<keyboardLogEn);
    return pdFALSE;
}

/*****************************************************************************\
 * Function:    audioCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function controls audio output. E.g. am 12 -> left -> mic1, right -> mic2 will be heard on the audio output.
 *     Note: Only up to mic can be chosen.	E.g. am 01 -> left -> nothing, right -> mic2
\*****************************************************************************/
static BaseType_t audioCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    /* Expecting one parameter */
    int8_t *pcParameter1;
    BaseType_t xParameter1StringLength;
    int length = 0;

    pcParameter1 = (int8_t *)FreeRTOS_CLIGetParameter
                        (
                          /* The command string itself. */
                          pcCommandString,
                          /* Return the first parameter. */
                          1,
                          /* Store the parameter string length. */
                          &xParameter1StringLength
                        );
    /* Terminate parameter. */
    pcParameter1[ xParameter1StringLength ] = 0x00;

    uint8_t validInput = 1;
    /* input parameter validation */
    if (xParameter1StringLength == 2)
    {
    	uint8_t count = 0;
    	uint8_t sum = 0;
    	for (uint8_t i=0; i<2; i++)
    	{
    		if(pcParameter1[i] >= 0x30 && pcParameter1[i] <= 0x34)
    		{
    			count++;
    		}
    	}
    	if (count==2)
    	{
    		if (pcParameter1[0] == pcParameter1[1] && pcParameter1[0] != 0x30)
    		{
    		    strncpy(pcWriteBuffer,TEXT_AUDIO_ERROR,xWriteBufferLen-1);
    		    pcWriteBuffer[xWriteBufferLen-1]=0;
    		    return pdFALSE;
    		}
    		disableAllMicChannels();
    		// enable mic here
    		for (uint8_t i=0; i<2; i++)
    		{
    			if (pcParameter1[i] != 0x30)
				{
    				enableAudioMicChannels(i, pcParameter1[i]-0x30);
				}
    		}

    		length += sprintf(pcWriteBuffer+length, "\r\nSuccess: Audio L->");
    		uint8_t temp[10];
    		if (pcParameter1[0]==0x30)
    		{
    			length += sprintf(pcWriteBuffer+length, "empty");
    		}
    		else
    		{
    			length += sprintf(pcWriteBuffer+length, "mic%c", pcParameter1[0]);
    		}

    		length += sprintf(pcWriteBuffer+length, ", R->");
    		if (pcParameter1[1]==0x30)
			{
				length += sprintf(pcWriteBuffer+length, "empty");
			}
			else
			{
				length += sprintf(pcWriteBuffer+length, "mic%c", pcParameter1[1]);
			}
    		length += sprintf(pcWriteBuffer+length, " are selected.");

    		//length += sprintf(pcWriteBuffer+length, "\r\n*** Audio L->mic#%c, R->mic#%c are selected\r\n", pcParameter1[0]==0x30?'_':pcParameter1[0], pcParameter1[1]==0x30?'_':pcParameter1[1]);
    		pcWriteBuffer[xWriteBufferLen-1]=0;
    		return pdFALSE;
    	}
    }

    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,TEXT_AUDIO_ERROR,xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    return pdFALSE;
}

/*****************************************************************************\
 * Function:    controlLedCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function controls individual leds. E.g. led 101 -> red on, green off, blue on
\*****************************************************************************/
static BaseType_t controlLedCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    /* Expecting one parameter */
    int8_t *pcParameter1;
    BaseType_t xParameter1StringLength;

    pcParameter1 = (int8_t *)FreeRTOS_CLIGetParameter
                        (
                          /* The command string itself. */
                          pcCommandString,
                          /* Return the first parameter. */
                          1,
                          /* Store the parameter string length. */
                          &xParameter1StringLength
                        );
    /* Terminate parameter. */
    pcParameter1[ xParameter1StringLength ] = 0x00;

    uint8_t validInput = 1;
    /* input parameter validation */
    if (xParameter1StringLength == 3) {
    	uint8_t count = 0;
    	for (uint8_t i=0; i<3; i++) {
    		if(pcParameter1[i] == 0x31 || pcParameter1[i] == 0x30) {
    			count++;
    		}
    	}
    	if (count==3) {
    		set_red_led(pcParameter1[0]==0x30?0:1);
    		set_green_led(pcParameter1[1]==0x30?0:1);
    		set_blue_led(pcParameter1[2]==0x30?0:1);
    		pcWriteBuffer[0] = 0; // to make sure
    		return pdFALSE;
    	}
    }

    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,TEXT_LED_ERROR,xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    return pdFALSE;
}

/*****************************************************************************\
 * Function:    exitCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function disables printing mouse, keyboard data on the console.
\*****************************************************************************/
static BaseType_t exitCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;

    char *text = "\r\nquit\r\n";
    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,&text[processed],xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    cmdEnable = 0;
    return pdFALSE;
}

#if configGENERATE_RUN_TIME_STATS
/*****************************************************************************\
 * Function:    taskStatsCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function returns list of tasks.
\*****************************************************************************/
static BaseType_t taskStatsCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;
    int char_cnt = 0;
    UBaseType_t cnt;
    BaseType_t xReturn;
    char *text;
    // initial call
    if (processed == 0)
    {
    	cnt = uxTaskGetNumberOfTasks();
    	if (cnt>0 && cnt<20)
    	{
    		ptr_temp = pvPortMalloc(40*cnt);
    		vTaskGetRunTimeStats((char *)ptr_temp);
    		ptr_aux = (char *)ptr_temp;
    		text = (char *)TEXT_FREETOS_STATS;
    		strncpy(pcWriteBuffer,&text[0],xWriteBufferLen-1);
    		processed++;
    		xReturn = pdTRUE;
    	}
    	else
    	{
    		// more than 20 or 0 tasks
    		text = "\r\ncan't list more than 20\r\n";
    	    // Only allowed to write up top xWriteBufferLen bytes ...
    	    strncpy(pcWriteBuffer,&text[0],xWriteBufferLen-1);
    		xReturn = pdFALSE;
    	}
    }
    else if (processed == 1)
    {
    	char_cnt = copyTillNewLine(pcWriteBuffer, ptr_aux);
		ptr_aux = ptr_aux + char_cnt;
		if (char_cnt)
		{
			xReturn = pdTRUE;
		}
		else
		{
			xReturn = pdFALSE;
	    	// free the memory
	    	vPortFree(ptr_temp);
	    	pcWriteBuffer[0] = 0;
	    	processed = 0;
		}
    }
    return xReturn;
}
#endif

/*****************************************************************************\
 * Function:    wifiScanCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function initiates wifi scan, prints discovered networks on the console.
\*****************************************************************************/
static BaseType_t wifiScanCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;
    static int ssid_cnt = 0;
    int length = 0;
    BaseType_t xReturn;
    uint8_t dummy_byte;
    const EventBits_t xBitsToWaitFor = WIFI_CONSOLE_NDATA;
    char *text;
    struct wlan_scan_result *ssid_entry;
    if (processed == 0)	// initial call
    {
    	wifi_cmd_toSend.cmd_type = WIFI_SCAN;
		wifi_cmd_toSend.task_name = CONSOLE_TASK;
		wifi_cmd_toSend.payload = NULL;
		xQueueSend(*wifi_cmd_queue, (void *) &wifi_cmd_toSend, 10);
		length += sprintf(pcWriteBuffer+length, "\r\nScanning wifi ...\r\n");
		// Only allowed to write up top xWriteBufferLen bytes ...
		processed++;
		xReturn = pdTRUE;
    }
    else if (processed==1)
    {
    	// wait 15seconds;
    	bits = xEventGroupWaitBits(*event_group_wifi, xBitsToWaitFor, pdTRUE, pdFALSE, 15000 / portTICK_RATE_MS);

    	if (!(bits&xBitsToWaitFor))
    	//if (xQueueReceive(*wifi_response_queue, &(dummy_byte), 15000 / portTICK_RATE_MS) != pdTRUE)
		{
    		//no event arrived
			length = sprintf(pcWriteBuffer+length, "\r\n Wifi not working\r\n");
			processed = 0;
			xReturn = pdFALSE;
		}
    	else
    	{
    		//event arrived
    		ssid_cnt = shared_buff[2];
			length += sprintf(pcWriteBuffer+length,"\r\n%d network%s found:\r\n\n", ssid_cnt, ssid_cnt == 1 ? "" : "s");

			//allocate memory for storage
			ptr_temp = pvPortMalloc(sizeof(struct wlan_scan_result)*ssid_cnt);
			ptr_aux = ptr_temp; //ptr_temp will be later used for freeing memory.
			memcpy(ptr_temp,&shared_buff[3],sizeof(struct wlan_scan_result)*shared_buff[2]);
			processed++;
			xReturn = pdTRUE;
    	}
    }
    else
    {
    	//print the ssid one by one
    	if (processed - 2 < ssid_cnt)
    	{
    		ssid_entry = (struct wlan_scan_result *)(ptr_aux + (processed-2)*sizeof(struct wlan_scan_result));
    		length += sprintf(pcWriteBuffer+length, "%02X:%02X:%02X:%02X:%02X:%02X ", ssid_entry->bssid[0],
    				ssid_entry->bssid[1], ssid_entry->bssid[2],
					ssid_entry->bssid[3], ssid_entry->bssid[4],
					ssid_entry->bssid[5]);
			if (ssid_entry->ssid[0])
			{
				length += sprintf(pcWriteBuffer+length, "\"%s\"\r\n", ssid_entry->ssid);
			}
			else
			{
				length += sprintf(pcWriteBuffer+length, "(hidden)\r\n");
			}
			length += sprintf(pcWriteBuffer+length, "\tchannel: %d", ssid_entry->channel);
			length += sprintf(pcWriteBuffer+length, "\trssi: -%d dBm", ssid_entry->rssi);
			length += sprintf(pcWriteBuffer+length, "\tsecurity: ");

			if (ssid_entry->wep)
			{
				length += sprintf(pcWriteBuffer+length, "WEP ");
			}

			if (ssid_entry->wpa && ssid_entry->wpa2)
			{
				length += sprintf(pcWriteBuffer+length, "WPA/WPA2 Mixed ");
			}
			else
			{
				if (ssid_entry->wpa)
					length += sprintf(pcWriteBuffer+length, "WPA ");
				if (ssid_entry->wpa2)
					length += sprintf(pcWriteBuffer+length, "WPA2 ");
				if (ssid_entry->wpa3_sae)
					length += sprintf(pcWriteBuffer+length, "WPA3 SAE ");
				if (ssid_entry->wpa2_entp)
					length += sprintf(pcWriteBuffer+length, "WPA2 Enterprise");
			}
			if (!(ssid_entry->wep || ssid_entry->wpa || ssid_entry->wpa2 || ssid_entry->wpa3_sae || ssid_entry->wpa2_entp))
				length += sprintf(pcWriteBuffer+length, "OPEN ");
			length += sprintf(pcWriteBuffer+length, "\tWMM: %s\r\n", ssid_entry->wmm ? "YES" : "NO");
			processed++;
			xReturn = pdTRUE;
    	}
    	else
    	{
    		processed = 0;
    		pcWriteBuffer[0];
    		vPortFree(ptr_temp);	// free memory
    		xReturn = pdFALSE;
    	}

    }
    // safe to put terminator at the end of buffer,
    pcWriteBuffer[xWriteBufferLen-1]=0;
    return xReturn;
}


/*****************************************************************************\
 * Function:    connectApCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function connects to the External AP defined in the network_demo.c .
\*****************************************************************************/
static BaseType_t connectApCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;
    BaseType_t xReturn;
    int length = 0;
    uint8_t response_byte;
    if (processed == 0)
    {
    	wifi_cmd_toSend.cmd_type = WIFI_CONN;
		wifi_cmd_toSend.task_name = CONSOLE_TASK;
		wifi_cmd_toSend.payload = NULL;
		xQueueSend(*wifi_cmd_queue, (void *) &wifi_cmd_toSend, 10);
    	length += sprintf(pcWriteBuffer+length,"\r\nConnecting to AP...\r\n");
    	processed++;
    	xReturn = pdTRUE;
    }
    else {
    	if (xQueueReceive(*wifi_response_queue, &(response_byte), 22000 / portTICK_RATE_MS) != pdTRUE)
		{
			//no event arrived
			length = sprintf(pcWriteBuffer+length, "\r\n No response\r\n");
			processed = 0;
			xReturn = pdFALSE;
		}
		else
		{
			// connected to network
			length += sprintf(pcWriteBuffer+length,"\r\n%s connected...\r\n\n", response_byte == 0x01 ? "" : "not");
			processed=0;
			xReturn = pdFALSE;
		}
    }
    pcWriteBuffer[xWriteBufferLen-1]=0;
    return xReturn;
}

/*****************************************************************************\
 * Function:    printIpCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function prints the IP address.
\*****************************************************************************/
static BaseType_t printIpCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;
    BaseType_t xReturn;
    int length = 0;
    uint8_t response_byte;

    if (processed == 0)
    {
    	wifi_cmd_toSend.cmd_type = WIFI_IP;
		wifi_cmd_toSend.task_name = CONSOLE_TASK;
		wifi_cmd_toSend.payload = NULL;
		xQueueSend(*wifi_cmd_queue, (void *) &wifi_cmd_toSend, 10);
    	length += sprintf(pcWriteBuffer+length,"\r\nWlan Info\r\n");
    	processed++;
    	xReturn = pdTRUE;
    }
    else if (processed == 1)
    {
    	if (xQueueReceive(*wifi_response_queue, &(response_byte), 17000 / portTICK_RATE_MS) != pdTRUE)
		{
			//no event arrived
			length = sprintf(pcWriteBuffer+length, "\r\n No response\r\n");
			processed = 0;
			xReturn = pdFALSE;
		}
    	else
		{
			if (response_byte == 0x01)
			{
				memcpy(&network, &shared_buff[3], sizeof(struct wlan_network));
				length += sprintf(pcWriteBuffer+length,"Connected to \"%s\"\r\n\tSSID: %s\r\n\tBSSID: ", network.name, network.ssid[0] ? network.ssid : "(hidden)");
				length += sprintf(pcWriteBuffer+length, "%02X:%02X:%02X:%02X:%02X:%02X ", network.bssid[0],
						network.bssid[1], network.bssid[2],
						network.bssid[3], network.bssid[4],
						network.bssid[5]);
				if (network.channel)
				{
					length += sprintf(pcWriteBuffer+length, "\r\n\tchannel: %d", network.channel);
				}
				else
				{
					length += sprintf(pcWriteBuffer+length, "\r\n\tchannel: %d", "(Auto)");
				}

				char *sec_tag = "\tsecurity";
				if (!network.security_specific)
				{
					sec_tag = "\tsecurity [Wildcard]";
				}
				switch (network.security.type)
				{
					case WLAN_SECURITY_NONE:
						length += sprintf(pcWriteBuffer+length, "%s: none\r\n", sec_tag);
						break;
					case WLAN_SECURITY_WEP_OPEN:
						length += sprintf(pcWriteBuffer+length, "%s: WEP (open)\r\n", sec_tag);
						break;
					case WLAN_SECURITY_WEP_SHARED:
						length += sprintf(pcWriteBuffer+length, "%s: WEP (shared)\r\n", sec_tag);
						break;
					case WLAN_SECURITY_WPA:
						length += sprintf(pcWriteBuffer+length, "%s: WPA\r\n", sec_tag);
						break;
					case WLAN_SECURITY_WPA2:
						length += sprintf(pcWriteBuffer+length, "%s: WPA2\r\n", sec_tag);
						break;
					case WLAN_SECURITY_WPA_WPA2_MIXED:
						length += sprintf(pcWriteBuffer+length, "%s: WPA/WPA2 Mixed\r\n", sec_tag);
						break;
					case WLAN_SECURITY_WPA3_SAE:
						length += sprintf(pcWriteBuffer+length, "%s: WPA3 SAE\r\n", sec_tag);
						break;
					default:
						break;
				}
				processed++;
				xReturn = pdTRUE;
			}
			else
			{
				// no ip info received.
				length = sprintf(pcWriteBuffer+length, "\r\n Not Connected\r\n");
				processed = 0;
				xReturn = pdFALSE;
			}
		}
    }
    else {
    	// print ip, this is last line.
    	length = print_address(&network.ip, network.role, pcWriteBuffer, length);
		processed = 0;
		xReturn = pdFALSE;
    }
    pcWriteBuffer[xWriteBufferLen-1]=0;
    return xReturn;
}

/*****************************************************************************\
 * Function:    ethernetScanCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function prints the status of both ethernet interfaces
\*****************************************************************************/
static BaseType_t ethernetScanCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
	(void)pcCommandString;
	int length = 0;
	BaseType_t xReturn;
	static int processed = 0;

	if (processed == 0)
	{
		eth_instance = &eth_100mb_addr;
	}
	else
	{
		eth_instance = &eth_1g_addr;
	}

	if (eth_instance->connected)
	{
		length += sprintf(pcWriteBuffer+length, "\r\nEth_%s: connected\r\n", processed==0?"100Mb":"1Gb  ");
		length += sprintf(pcWriteBuffer+length, "IPv4 Address   : %d.%d.%d.%d\r\n",
				(uint8_t)((eth_instance->ip)), (uint8_t)((eth_instance->ip)>>8),
				(uint8_t)((eth_instance->ip)>>16), (uint8_t)((eth_instance->ip)>>24));
		length += sprintf(pcWriteBuffer+length, "IPv4 Subnet    : %d.%d.%d.%d\r\n",
				(uint8_t)((eth_instance->sub)), (uint8_t)((eth_instance->sub)>>8),
				(uint8_t)((eth_instance->sub)>>16), (uint8_t)((eth_instance->sub)>>24));
		length += sprintf(pcWriteBuffer+length, "IPv4 Gateway   : %d.%d.%d.%d\r\n",
				(uint8_t)((eth_instance->gw)), (uint8_t)((eth_instance->gw)>>8),
				(uint8_t)((eth_instance->gw)>>16), (uint8_t)((eth_instance->gw)>>24));
	}else
	{
		length += sprintf(pcWriteBuffer+length, "\r\nEth_%s: not connected\r\n", processed==0?"100Mb":"1Gb  ");
	}
	processed++;
	pcWriteBuffer[xWriteBufferLen-1]=0;
	xReturn = pdTRUE;
	if (processed == 2)
	{
		processed = 0;
		xReturn = pdFALSE;

	}
	return xReturn;
}









/************************ FAT LOGIC ************************/
#if defined(__FAT_BUILD__)

/*****************************************************************************\
 * Function:    FAT_ethernetIPCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function sends the IP address of selected interface on UART
\*****************************************************************************/
static BaseType_t FAT_ethernetIPCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
	if ((eth_1g_addr.connected) && (eth_100mb_addr.connected))
	{
		sprintf(pcWriteBuffer, "100Mb=%d.%d.%d.%d, 1G=%d.%d.%d.%d\r\n",
				(uint8_t)((eth_100mb_addr.ip)), (uint8_t)((eth_100mb_addr.ip)>>8),
				(uint8_t)((eth_100mb_addr.ip)>>16), (uint8_t)((eth_100mb_addr.ip)>>24),
				(uint8_t)((eth_1g_addr.ip)), (uint8_t)((eth_1g_addr.ip)>>8),
				(uint8_t)((eth_1g_addr.ip)>>16), (uint8_t)((eth_1g_addr.ip)>>24));
	}
	else if ((eth_1g_addr.connected) && (!eth_100mb_addr.connected))
	{
		sprintf(pcWriteBuffer, "100Mb=Not Connected, 1G=%d.%d.%d.%d\r\n",
				(uint8_t)((eth_1g_addr.ip)), (uint8_t)((eth_1g_addr.ip)>>8),
				(uint8_t)((eth_1g_addr.ip)>>16), (uint8_t)((eth_1g_addr.ip)>>24));
	}
	else if ((!eth_1g_addr.connected) && (eth_100mb_addr.connected))
	{
		sprintf(pcWriteBuffer, "100Mb=%d.%d.%d.%d, 1G=Not Connected\r\n",
				(uint8_t)((eth_100mb_addr.ip)), (uint8_t)((eth_100mb_addr.ip)>>8),
				(uint8_t)((eth_100mb_addr.ip)>>16), (uint8_t)((eth_100mb_addr.ip)>>24));
	}
	else
	{
		sprintf(pcWriteBuffer, "100Mb=Not connected, 1G=Not connected\r\n");
	}

	pcWriteBuffer[xWriteBufferLen-1]=0;

	return pdFALSE;
}


/*****************************************************************************\
 * Function:    FAT_HIDReportCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function sends the type of the connected HID device on UART
\*****************************************************************************/
static BaseType_t FAT_HIDReportCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
	(void)pcCommandString;
	int length = 0;
	BaseType_t xReturn;

	if (usb_devices[0].deviceExist) {
		sprintf(pcWriteBuffer, "=mouse\r\n");
	}

	else if (usb_devices[1].deviceExist) {
		sprintf(pcWriteBuffer, "=keyboard\r\n");
	}
	else {
		sprintf(pcWriteBuffer, "=Not connected\r\n");
	}

	pcWriteBuffer[xWriteBufferLen-1]=0;

	return pdFALSE;
}

/*****************************************************************************\
 * Function:    FAT_WIFIReportCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function sends the status of the FAT wifi node and signal strength
\*****************************************************************************/
static BaseType_t FAT_WIFIReportCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
	(void)pcCommandString;
	int length = 0;
	BaseType_t xReturn = pdFALSE;
    int8_t *pcParameter1;
    BaseType_t xParameter1StringLength;

    pcParameter1 = (int8_t *)FreeRTOS_CLIGetParameter
                        (
                          /* The command string itself. */
                          pcCommandString,
                          /* Return the first parameter. */
                          1,
                          /* Store the parameter string length. */
                          &xParameter1StringLength
                        );
    /* Terminate parameter. */
    pcParameter1[ xParameter1StringLength ] = 0x00;

    if (xParameter1StringLength >= 1) {

		const char s[2] = "|";
		char *node1;
		char *node2;
		bool validParameters = false;

		/* get the first token */
		node1 = strtok(pcParameter1, s);

		if( node1 != NULL )
		{
			node2 = strtok(NULL, s);

			if( node2 != NULL )
			{
				validParameters = true;
			}
		}

        if(validParameters)
        {
        	if(FATIsWifiNetworkFound(node1) && FATIsWifiNetworkFound(node2))
			{
				sprintf(pcWriteBuffer, " =2.4G signal strength: -%d, 5G signal strength: -%d\r\n",
						FATGetWifiSignalStrength(node1),
						FATGetWifiSignalStrength(node2));
			}
        	else if(!FATIsWifiNetworkFound(node1) && FATIsWifiNetworkFound(node2))
			{
				sprintf(pcWriteBuffer, " =2.4G Not connected, 5G signal strength: -%d\r\n",
						FATGetWifiSignalStrength(node2));
			}
        	else if(FATIsWifiNetworkFound(node1) && !FATIsWifiNetworkFound(node2))
			{
				sprintf(pcWriteBuffer, " =2.4G signal strength: -%d, 5G Not connected\r\n",
						FATGetWifiSignalStrength(node1));
			}
			else
			{
				sprintf(pcWriteBuffer, " =2.4G Not connected, 5G Not connected\r\n");
			}
        }
        else
        {
        	sprintf(pcWriteBuffer+length, " =Invalid parameter\r\n");
        }
    }
    else
    {
    	sprintf(pcWriteBuffer+length, " =Invalid parameter\r\n");
    }

	pcWriteBuffer[xWriteBufferLen-1]=0;

	return pdFALSE;
}

/*****************************************************************************\
 * Function:    FAT_PlayAudioCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This will play audio on the selected channel
\*****************************************************************************/
static BaseType_t FAT_PlayAudioCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
	(void)pcCommandString;
	int length = 0;
	BaseType_t xReturn;

	int32_t minIdle,  maxIdle, minTest, maxTest = 0;
	int16_t mic[4][2];

	FATPlayAudioTest();

	/* wait till test completes */
	while(FATIsAudioTestRunning());

	for (int i=0; i<4; i++)
	{
		FATGetTestResults(i, &minIdle, &maxIdle, &minTest, &maxTest);
		mic[i][0] = maxIdle-minIdle;
		mic[i][1] = maxTest-minTest;
	}
	sprintf(pcWriteBuffer, "Amplitudes: %d ,%d ,%d ,%d, %d ,%d ,%d ,%d\r\n",
			mic[0][0], mic[0][1],
			mic[1][0], mic[1][1],
			mic[2][0], mic[2][1],
			mic[3][0], mic[3][1]);

	pcWriteBuffer[xWriteBufferLen-1]=0;
	return pdFALSE;
}


#endif

/* Utility functions */

/*****************************************************************************\
 * Function:    copyTillNewLine
 * Input:       char * dest, char *src
 * Returns:     number bytes copied
 * Description:
 *     This function copies the src data to destination until first \n or 0.
\*****************************************************************************/
static uint16_t copyTillNewLine(char * dest, char *src)
{
	uint16_t cnt = 0;
	while(*src!=0 && *src!='\n')
	{
		*(dest++) = *(src++);
		cnt++;
	}
    // terminate the string
    if (*src=='\n')
    {
        *(dest++) = *src;
        cnt++;
    }
    *dest = 0;
	return cnt;
}

static int print_address(struct wlan_ip_config *addr, enum wlan_bss_role role, uint8_t *printBuff, int length)
{
    struct in_addr ip, gw, nm, dns1, dns2;
    char addr_type[10];
    ip.s_addr   = addr->ipv4.address;
    gw.s_addr   = addr->ipv4.gw;
    nm.s_addr   = addr->ipv4.netmask;
    dns1.s_addr = addr->ipv4.dns1;
    dns2.s_addr = addr->ipv4.dns2;
    if (addr->ipv4.addr_type == ADDR_TYPE_STATIC)
        strncpy(addr_type, "STATIC", sizeof(addr_type));
    else if (addr->ipv4.addr_type == ADDR_TYPE_STATIC)
        strncpy(addr_type, "AUTO IP", sizeof(addr_type));
    else
        strncpy(addr_type, "DHCP", sizeof(addr_type));

    //PRINTF("\r\n\tIPv4 Address\r\n");
    length += sprintf(printBuff+length, "\r\n\tIPv4 Address\r\n");
    //PRINTF("\taddress: %s", addr_type);
    length += sprintf(printBuff+length, "\taddress: %s", addr_type);
    //PRINTF("\r\n\t\tIP:\t\t%s", inet_ntoa(ip));
    length += sprintf(printBuff+length, "\r\n\t\tIP:\t\t%s", inet_ntoa(ip));
    //PRINTF("\r\n\t\tgateway:\t%s", inet_ntoa(gw));
    length += sprintf(printBuff+length, "\r\n\t\tgateway:\t%s", inet_ntoa(gw));
    //PRINTF("\r\n\t\tnetmask:\t%s", inet_ntoa(nm));
    length += sprintf(printBuff+length, "\r\n\t\tnetmask:\t%s", inet_ntoa(nm));
    //PRINTF("\r\n\t\tdns1:\t\t%s", inet_ntoa(dns1));
    length += sprintf(printBuff+length, "\r\n\t\tdns1:\t\t%s", inet_ntoa(dns1));
    //PRINTF("\r\n\t\tdns2:\t\t%s", inet_ntoa(dns2));
    length += sprintf(printBuff+length, "\r\n\t\tdns1:\t\t%s", inet_ntoa(dns2));
    //PRINTF("\r\n");
    length += sprintf(printBuff+length, "\r\n");
    return length;
}

/* Console command structs */
/***************** PERIPHERALS COMMANDS ************************/
static const CLI_Command_Definition_t controlLedCommandStruct =
{
    "led",
    "--------- PERIPHERALS ----------------\r\n"
    " led ***    : RGB LEDs on/off \r\n",
	controlLedCommand,
    1
};

static const CLI_Command_Definition_t i2cScanCommandStruct =
{
    "i2c",
    " i2c #      : I2C Scan (bus# 2/3/5/6) \r\n",
	scanCommand,
    1
};

/***************** WIFI & LAN COMMANDS *************************/
static const CLI_Command_Definition_t scanWifiCommandStruct =
{
    "ws",
    "--------- WIFI & LAN -----------------\r\n"
    " ws         : Wifi Scan \r\n",
	wifiScanCommand,
    0
};

static const CLI_Command_Definition_t connectWifiCommandStruct =
{
    "wc",
    " wc         : Wifi Connect \r\n",
	connectApCommand,
    0
};

static const CLI_Command_Definition_t printIpCommandStruct =
{
    "wi",
    " wi         : Wifi Info \r\n",
	printIpCommand,
    0
};

static const CLI_Command_Definition_t ethernetScanCommandStruct =
{
    "es",
    " es         : Ethernet Scan \r\n",
	ethernetScanCommand,
    0
};




/************************ FAT LOGIC ************************/
#if defined(__FAT_BUILD__)
static const CLI_Command_Definition_t FAT_ethernetIPCommandStruct =
{
    "ip",
	"--------- FAT COMMANDS ---------------\r\n"
    " ip         : Ethernet IP request \r\n",
	FAT_ethernetIPCommand,
    0
};

static const CLI_Command_Definition_t FAT_HIDReportCommandStruct =
{
    "hid",
    " hid         : Connected HID device \r\n",
	FAT_HIDReportCommand,
    0
};

static const CLI_Command_Definition_t FAT_WIFIReportCommandStruct =
{
    "wifi",
    " wifi         : wifi status and signal strength \r\n",
	FAT_WIFIReportCommand,
    1
};

static const CLI_Command_Definition_t FAT_PlayAudioCommandStruct =
{
    "play",
    " play         : play audio test sample \r\n",
	FAT_PlayAudioCommand,
    0
};

#endif


/***************** USB HOST & DEV ******************************/
static const CLI_Command_Definition_t listUSBCommandStruct =
{
    "ul",
    " -------- USB HOST & DEV -------------\r\n"
    " ul         : USB List (attached devices) \r\n",
	listUSBCommand,
    0
};

static const CLI_Command_Definition_t enableKeyboardCommandStruct =
{
    "uk",
    " uk         : Keyboard Test \r\n",
	keyboardCommand,
    0
};

static const CLI_Command_Definition_t enableMouseCommandStruct =
{
    "um",
    " um         : Mouse Test \r\n",
	mouseCommand,
    0
};

/***************** A&V COMMANDS *******************************/
static const CLI_Command_Definition_t audioCommandStruct =
{
    "am",
    "--------- AUDIO & VIDEO --------------\r\n"
    " am ##      : Audio L/R output (mic# 1-4)\r\n",
	audioCommand,
    1
};

/***************** UTILITY COMMANDS ****************************/
#if configGENERATE_RUN_TIME_STATS
static const CLI_Command_Definition_t taskStatsCommandStruct =
{
    "stats",
    "--------- UTILITY --------------------\r\n"
    " stats      : RTOS Statistics \r\n",
	taskStatsCommand,
    0
};
#endif
static const CLI_Command_Definition_t clearCommandStruct =
{
    "clr",
    " clr        : Clear the terminal \r\n",
    clearCommand,
    0
};

static const CLI_Command_Definition_t exitCommandStruct =
{
    "q",
    " q/ctrl+c   : Abort the command \r\n",
	exitCommand,
    0
};

static const CLI_Command_Definition_t helpCommandStruct =
{
    "h",
    " ? / h      : Menu Help \r\n"
	"========= "
	MAAXBOARD_VERSION_STRING
	"\r\n",
	prvHelpCommand,
    0
};

/*******************************************************************************
 * Freetos Task: USB_log
 * @brief receive console application using lpuart1 peripheral.
 ******************************************************************************/
void console_task(void *pvParameters)
{
	custom_console_instance_t *t_console_instance = (custom_console_instance_t *)pvParameters;
	handle = t_console_instance->uart_handle;
	wifi_cmd_queue = t_console_instance->cmd_queue;
	event_group_wifi = t_console_instance->event_group_wifi;
	wifi_response_queue = t_console_instance->wifi_resQ;
	char pcOutputString[ MAX_OUTPUT_LENGTH ], pcInputString[ MAX_INPUT_LENGTH ];

	memset( pcInputString, 0x00, MAX_INPUT_LENGTH );
	uint8_t cRxedChar, cInputIndex = 0;
	BaseType_t xMoreDataToFollow;
    int error;
    size_t n = 0;

    /* Send introduction message. */
    if (kStatus_Success != LPUART_RTOS_Send(handle, (uint8_t *)TEXT_WELCOME, strlen(TEXT_WELCOME)))
    {
        vTaskSuspend(NULL);
    }

    /* Registering cli commands */
    /***************** PERIPHERALS COMMANDS ************************/
    FreeRTOS_CLIRegisterCommand( &controlLedCommandStruct );
    FreeRTOS_CLIRegisterCommand( &i2cScanCommandStruct );

    /***************** WIFI & LAN COMMANDS *************************/
    FreeRTOS_CLIRegisterCommand( &scanWifiCommandStruct );
    FreeRTOS_CLIRegisterCommand( &connectWifiCommandStruct );
    FreeRTOS_CLIRegisterCommand( &printIpCommandStruct );
    FreeRTOS_CLIRegisterCommand( &ethernetScanCommandStruct );

    /***************** USB HOST & DEV ******************************/
    FreeRTOS_CLIRegisterCommand( &listUSBCommandStruct );
    FreeRTOS_CLIRegisterCommand( &enableKeyboardCommandStruct );
    FreeRTOS_CLIRegisterCommand( &enableMouseCommandStruct );

    /***************** AUDIO & VIDEO *******************************/
    FreeRTOS_CLIRegisterCommand( &audioCommandStruct);

    /***************** UTILITY COMMANDS ****************************/
#if configGENERATE_RUN_TIME_STATS
    FreeRTOS_CLIRegisterCommand( &taskStatsCommandStruct );
#endif
    FreeRTOS_CLIRegisterCommand( &clearCommandStruct );
    FreeRTOS_CLIRegisterCommand( &exitCommandStruct );
    FreeRTOS_CLIRegisterCommand( &helpCommandStruct );


    /************************ FAT LOGIC ************************/
#if defined(__FAT_BUILD__)
    FreeRTOS_CLIRegisterCommand( &FAT_ethernetIPCommandStruct );
    FreeRTOS_CLIRegisterCommand( &FAT_HIDReportCommandStruct);
    FreeRTOS_CLIRegisterCommand( &FAT_WIFIReportCommandStruct);
    FreeRTOS_CLIRegisterCommand( &FAT_PlayAudioCommandStruct);
#endif

    /* Receive user input and send it back to terminal. */

    while(1)
    {
    	LPUART_RTOS_Receive(handle, &cRxedChar, sizeof( cRxedChar ), &n);
		if( cRxedChar == '\r' )
		{
			/* A newline character was received, so the input command string is
			complete and can be processed.  Transmit a line separator, just to
			make the output easier to read. */
			LPUART_RTOS_Send(handle,&cRxedChar,1);
			/* The command interpreter is called repeatedly until it returns
			pdFALSE.  See the "Implementing a command" documentation for an
			exaplanation of why this is. */
			do
			{
				/* Send the command string to the command interpreter.  Any
				output generated by the command interpreter will be placed in the
				pcOutputString buffer. */
				xMoreDataToFollow = FreeRTOS_CLIProcessCommand
				(
					pcInputString,   /* The command string.*/
					pcOutputString,  /* The output buffer. */
					MAX_OUTPUT_LENGTH/* The size of the output buffer. */
				);
				/* Write the output generated by the command interpreter to the
				console. */
				if (pcOutputString[0] !=0)
				{
					LPUART_RTOS_Send(handle, pcOutputString, strlen( pcOutputString ) );
				}
			} while( xMoreDataToFollow != pdFALSE );
			//print prompt after each command
			sprintf(pcOutputString, "\r\n> ", 4);
			LPUART_RTOS_Send(handle, pcOutputString, strlen( pcOutputString ) );
			/* All the strings generated by the input command have been sent.
			Processing of the command is complete.  Clear the input string ready
			to receive the next command. */
			cInputIndex = 0;
			memset( pcInputString, 0x00, MAX_INPUT_LENGTH );
		}
		else if (cRxedChar == 0x03)	// end of text, ctrl+c
		{
			cmdEnable = 0;
			LPUART_RTOS_Send(handle, (uint8_t *)TEXT_ABORT_CMD, strlen(TEXT_ABORT_CMD));
		}
		else
		{
		/* The if() clause performs the processing after a newline character
		is received.  This else clause performs the processing if any other
		character is received. */
			if( cRxedChar == 8 ) // backspace character
			{
				LPUART_RTOS_Send(handle,&cRxedChar,1);
				/* Backspace was pressed.  Erase the last character in the input
				buffer - if there are any. */
				if( cInputIndex > 0 )
				{
					cInputIndex--;
					pcInputString[ cInputIndex ] = '\0';
				}
			}
			else
			{
				/* A character was entered.  It was not a new line, backspace
				or carriage return, so it is accepted as part of the input and
				placed into the input buffer.  When a \n is entered the complete
				string will be passed to the command interpreter. */
				if( cInputIndex < MAX_INPUT_LENGTH )
				{
					LPUART_RTOS_Send(handle,&cRxedChar,1);
					pcInputString[ cInputIndex ] = cRxedChar;
					cInputIndex++;
				}
			}
		}
		vTaskDelay(100/portTICK_PERIOD_MS);
    }
    vTaskSuspend(NULL);
}
