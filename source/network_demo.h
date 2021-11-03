/** @file network_demo.h
 *  @brief Function prototypes for wifi commands.
 */
#ifndef _NETWORK_DEMO_H_
#define _NETWORK_DEMO_H_

#include <wm_os.h>

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*****************************************************************************\
 * Function:    getTargetSSID
 * Input:       nameBuffer - pointer to wifi ssid string, bufLen - length of string
 * Returns:     void
 * Description:
 *     Initiate wifi scan command
\*****************************************************************************/
void getTargetSSID(char* nameBuffer, int bufLen);

/*****************************************************************************\
 * Function:    ssidScan
 * Input:       void
 * Returns:     void
 * Description:
 *     Initiate wifi scan command
\*****************************************************************************/
void ssidScan(void);

/*****************************************************************************\
 * Function:    connectToAP
 * Input:       void
 * Returns:     int 0 - success, 1 - fail
 * Description:
 *     Connects to harcoded wifi network
\*****************************************************************************/
int connectToAP(void);

/*****************************************************************************\
 * Function:    getCurrentSignalStrength
 * Input:       short pointer
 * Returns:     int8_t
 * Description:
 *     This function return 0 - success, 1 - fail
\*****************************************************************************/
int8_t getCurrentSignalStrength(short *rssi);

/*****************************************************************************\
 * Function:    isWifiReady
 * Input:       void
 * Returns:     boolean
 * Description:
 *     This function will report whether board is connected to hardcoded wifi ssid.
\*****************************************************************************/
bool isWifiReady(void);

/*****************************************************************************\
 * Function:    wifi_task
 * Input:       void
 * Returns:     void
 * Description:
 *     Main Body of the Freertos wifi task
\*****************************************************************************/
void wifi_task(void *param);


#if defined(__FAT_BUILD__)
typedef struct
{
	char name[25];
	unsigned char strength;

}tWifiSSID;

bool FATIsWifiNetworkFound(char* name);
int16_t FATGetWifiSignalStrength(char* name);
#endif

#endif //_NETWORK_DEMO_H_
