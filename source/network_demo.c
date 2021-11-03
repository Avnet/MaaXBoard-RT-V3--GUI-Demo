
#include "demo_common.h"
#include "lvgl_demo.h"
#include "network_demo.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"

#if defined(SD8801)
#include "sd8801_wlan.h"
#elif defined(SD8977)
#include "sduart8977_wlan_bt.h"
#elif defined(SD8978)
#include "sduart8978_wlan_bt.h"
#elif defined(SD8987)
#include "sduart8987_wlan_bt.h"
#elif defined(SD8997)
#include "sduart8997_wlan_bt.h"
#elif defined(SD9097)
#include "pvt_sd9097_wlan.h"
#elif defined(SD9098)
#include "pvt_sd9098_wlan.h"
#endif

#include "wlan.h"
#include "wifi.h"
#include "wm_net.h"
#include "dhcp-server.h"

#include "fsl_sdmmc_host.h"
#include "lwiperf.h"
#include "lwip/tcpip.h"

#include "fsl_common.h"
#include <stdio.h>
#include "globals.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

TimerHandle_t timer;

static void timer_poll_udp_client(TimerHandle_t timer);

// Hardwired SSID, passphrase of Soft AP to star
#define AP_SSID       "NXP_Soft_AP"
#define AP_PASSPHRASE "12345678"

// Hardwired SSID, passphrase of AP to connect to
// Change this to fit your AP

#if defined(__FAT_BUILD__)
#define EXT_AP_SSID       	"AVNET_5G"
#define EXT_AP_PASSPHRASE 	""
#else
#define EXT_AP_SSID       	"max123"
#define EXT_AP_PASSPHRASE 	"1qaz2wsx"
#endif

#ifndef IPERF_SERVER_ADDRESS
#define IPERF_SERVER_ADDRESS "10.0.0.1"
#endif

#ifndef IPERF_UDP_CLIENT_RATE
#define IPERF_UDP_CLIENT_RATE (100 * 1024 * 1024) /* 100 Mbit/s */
#endif

#ifndef IPERF_CLIENT_AMOUNT
#define IPERF_CLIENT_AMOUNT (-1000) /* 10 seconds */
#endif

#define MAX_RETRY_TICKS 50

struct iperf_test_context
{
    bool server_mode;
    bool tcp;
    enum lwiperf_client_type client_type;
    void *iperf_session;
};

static struct iperf_test_context ctx;

struct wlan_network sta_network;
struct wlan_network uap_network;

static void iperf_test_start(void *arg);
static void iperf_test_abort(void *arg);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static int network_added     = 0;
static int uap_network_added = 0;
static int network_initialized = 0;
static bool s_wifi_ready     = false;

static QueueHandle_t *wifi_cmd_queue;
static QueueHandle_t *wifi_response_queue;
static volatile EventGroupHandle_t *event_group_wifi;


static volatile uint32_t wifi_status = 0;
#define BIT_SCAN_RDY	0
#define BIT_CONN_RDY	1


#if defined(__FAT_BUILD__)
static tWifiSSID wifiList[100];
static uint8_t wifiListLen = 0;
#endif

/*******************************************************************************
 * Functions
 ******************************************************************************/
static void printSeparator(void)
{
    PRINTF("========================================\r\n");
}

/*!
 * @brief returns the wifi ssid string pointer, and its length
 */
void getTargetSSID(char* nameBuffer, int bufLen)
{
    strncpy(nameBuffer, EXT_AP_SSID, bufLen);
}

/*!
 * @brief callback for wifi scan
 */
int __scan_cb(unsigned int count)
{
    struct wlan_scan_result res;
    int i;
    int err;
	shared_buff[0] = 0xAA;
	shared_buff[1] = 0xBB;
	shared_buff[2] = (uint8_t)count;	// assuming ssid count is < 256

#if defined(__FAT_BUILD__)
	wifiListLen = 0;
#endif

    if (count == 0)
    {
        PRINTF("no networks found\r\n");
    }
    else
    {
		int offset = 3;
		PRINTF("%d network%s found:\r\n", count, count == 1 ? "" : "s");

		for (i = 0; i < count; i++)
		{
			//err = wlan_get_scan_result(i, shared_buff+offset+i*sizeof(struct wlan_scan_result));
			err = wlan_get_scan_result(i, &res);
			if (err)
			{
				PRINTF("Error: can't get scan res %d\r\n", i);
				continue;
			}
			memcpy((shared_buff+offset+i*sizeof(struct wlan_scan_result)), &res, sizeof(struct wlan_scan_result));
			print_mac(res.bssid);

#if defined(__FAT_BUILD__)
			if(wifiListLen<100)
			{
				strncpy(wifiList[wifiListLen].name, res.ssid, sizeof(wifiList[wifiListLen].name)-1);
				wifiList[wifiListLen].strength = res.rssi;
				wifiListLen++;
			}

#endif

			char strBuffer[40];
			if (res.ssid[0])
				sprintf(strBuffer, "\"%s\"", res.ssid);
			else
				sprintf(strBuffer, "(hidden)");

			PRINTF(" %s \r\n", strBuffer);

			PRINTF("\tchannel: %d\r\n", res.channel);

			char strBuffer2[40];
			sprintf(strBuffer2, "rssi: -%d dBm", res.rssi);

			PRINTF("\t%s\r\n", strBuffer2);

			char strBuffer3[100];
			sprintf(strBuffer3, "%s, %s", strBuffer, strBuffer2);

			addItemToSSIDList(strBuffer3);

			PRINTF("\tsecurity: ");
			if (res.wep)
				PRINTF("WEP ");
			if (res.wpa && res.wpa2)
				PRINTF("WPA/WPA2 Mixed ");
			else
			{
				if (res.wpa)
					PRINTF("WPA ");
				if (res.wpa2)
					PRINTF("WPA2 ");
				if (res.wpa3_sae)
					PRINTF("WPA3 SAE ");
				if (res.wpa2_entp)
					PRINTF("WPA2 Enterprise");
			}
			if (!(res.wep || res.wpa || res.wpa2 || res.wpa3_sae || res.wpa2_entp))
				PRINTF("OPEN ");
			PRINTF("\r\n");

			PRINTF("\tWMM: %s\r\n", res.wmm ? "YES" : "NO");
		}
    }
    wifi_status |= (1<<BIT_SCAN_RDY);
    return 0;
}

/*!
 * @brief initiate wifi scan
 */
void ssidScan(void)
{
    if (!isWifiReady())
    {
        PRINTF("Error: Wi-Fi module is still not ready. Wait a few seconds and retry\r\n");
        return;
    }

    if (wlan_scan(__scan_cb))
        PRINTF("Error: scan request failed\r\n");
    else
        PRINTF("Scan scheduled...\r\n");
}

/*!
 * @brief connects to hardcoded wifi network
 */
int connectToAP(void)
{
    int ret;

    PRINTF("Connecting to %s .....", sta_network.ssid);
    ret = wlan_connect(sta_network.name);

    if (ret != WM_SUCCESS)
    {
        PRINTF("Failed to connect %d\r\n", ret);
    }
    return ret;
}

int8_t getCurrentSignalStrength(short *rssi)
{
    int ret;

    // PRINTF("Getting RSSI for %s .....\r\n", sta_network.ssid);

    int snr = 0;

    if (network_initialized)
    {
        ret = wlan_get_current_signal_strength(rssi, &snr);

        if (ret != WM_SUCCESS)
        {
            PRINTF("Failed to get RSSI: %d\r\n", ret);
        }

        return 0;
    }
    else
    {
    	/* error wifi not initialized */
    	return 1;
    }


}

static const char *print_role(enum wlan_bss_role role)
{
    switch (role)
    {
        case WLAN_BSS_ROLE_STA:
            return "Infra";
        case WLAN_BSS_ROLE_UAP:
            return "uAP";
        case WLAN_BSS_ROLE_ANY:
            return "any";
    }

    return "unknown";
}

static void print_address(struct wlan_ip_config *addr, enum wlan_bss_role role)
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

    PRINTF("\r\n\tIPv4 Address\r\n");
    PRINTF("\taddress: %s", addr_type);
    PRINTF("\r\n\t\tIP:\t\t%s", inet_ntoa(ip));
    PRINTF("\r\n\t\tgateway:\t%s", inet_ntoa(gw));
    PRINTF("\r\n\t\tnetmask:\t%s", inet_ntoa(nm));
    PRINTF("\r\n\t\tdns1:\t\t%s", inet_ntoa(dns1));
    PRINTF("\r\n\t\tdns2:\t\t%s", inet_ntoa(dns2));
    PRINTF("\r\n");
}

static void print_network(struct wlan_network *network)
{
    PRINTF("\"%s\"\r\n\tSSID: %s\r\n\tBSSID: ", network->name, network->ssid[0] ? network->ssid : "(hidden)");

    print_mac(network->bssid);

    if (network->channel)
        PRINTF("\r\n\tchannel: %d", network->channel);
    else
        PRINTF("\r\n\tchannel: %s", "(Auto)");

    PRINTF("\r\n\trole: %s\r\n", print_role(network->role));

    char *sec_tag = "\tsecurity";
    if (!network->security_specific)
    {
        sec_tag = "\tsecurity [Wildcard]";
    }
    switch (network->security.type)
    {
        case WLAN_SECURITY_NONE:
            PRINTF("%s: none\r\n", sec_tag);
            break;
        case WLAN_SECURITY_WEP_OPEN:
            PRINTF("%s: WEP (open)\r\n", sec_tag);
            break;
        case WLAN_SECURITY_WEP_SHARED:
            PRINTF("%s: WEP (shared)\r\n", sec_tag);
            break;
        case WLAN_SECURITY_WPA:
            PRINTF("%s: WPA\r\n", sec_tag);
            break;
        case WLAN_SECURITY_WPA2:
            PRINTF("%s: WPA2\r\n", sec_tag);
            break;
        case WLAN_SECURITY_WPA_WPA2_MIXED:
            PRINTF("%s: WPA/WPA2 Mixed\r\n", sec_tag);
            break;
        case WLAN_SECURITY_WPA3_SAE:
            PRINTF("%s: WPA3 SAE\r\n", sec_tag);
            break;
        default:
            break;
    }

    print_address(&network->ip, network->role);
}

/*!
 * @brief gets wifi network information(ip, sub, gw) and store in buffer
 */
uint8_t printWlanInfo(void)
{
    enum wlan_connection_state state;
    struct wlan_network psta_network;
    struct wlan_network puap_network;
    int sta_found = 0;
    uint8_t ret = 0x01;
    if (wlan_get_connection_state(&state))
    {
    	ret = 0;
        PRINTF(
            "Error: unable to get STA connection"
            " state\r\n");
    }
    else
    {
        switch (state)
        {
            case WLAN_CONNECTED:
                if (!wlan_get_current_network(&psta_network))
                {
                    PRINTF("Station connected to:\r\n");
                    print_network(&psta_network);
                    sta_found = 1;
                	shared_buff[0] = 0xCC;
                	shared_buff[1] = 0xDD;
                	shared_buff[2] = 1;
                    memcpy(&shared_buff[3], &psta_network, sizeof(struct wlan_network));
                    ret = 0x01;
                }
                else
                {
                    PRINTF("Station not connected\r\n");
                	ret = 0x02;
                }
                break;
            default:
            	ret = 0x02;
                PRINTF("Station not connected\r\n");
                break;
        }
    }
    return ret;

    if (wlan_get_current_uap_network(&puap_network))
        PRINTF("uAP not started\r\n");
    else
    {
        /* Since uAP automatically changes the channel to the one that
         * STA is on */
        if (sta_found == 1)
            puap_network.channel = psta_network.channel;

        if (puap_network.role == WLAN_BSS_ROLE_UAP)
            PRINTF("uAP started as:\r\n");

        print_network(&puap_network);
    }
}

/* Callback Function passed to WLAN Connection Manager. The callback function
 * gets called when there are WLAN Events that need to be handled by the
 * application.
 */
int wlan_event_callback(enum wlan_event_reason reason, void *data)
{
    struct wlan_ip_config addr;
    char ip[16];
    static int auth_fail = 0;

    printSeparator();
    PRINTF("app_cb: WLAN: received event %d\r\n", reason);
    printSeparator();

    switch (reason)
    {
        case WLAN_REASON_INITIALIZED:
            PRINTF("app_cb: WLAN initialized\r\n");
            xEventGroupSetBits(*event_group_wifi, WIFI_RDY );
            int ret;
            network_initialized = 1;
            printSeparator();

            /* Print WLAN FW Version */
            wlan_version_extended();
            printSeparator();

            if (!network_added)
            {
                uint8_t network_name_len = 0;
                uint8_t ssid_len         = 0;
                uint8_t psk_len          = 0;
                memset(&sta_network, 0, sizeof(struct wlan_network));

                network_name_len = (strlen("sta_network") < WLAN_NETWORK_NAME_MAX_LENGTH) ?
                                       (strlen("sta_network") + 1) :
                                       WLAN_NETWORK_NAME_MAX_LENGTH;
                strncpy(sta_network.name, "sta_network", network_name_len);

                ssid_len = (strlen(EXT_AP_SSID) <= IEEEtypes_SSID_SIZE) ? strlen(EXT_AP_SSID) : IEEEtypes_SSID_SIZE;
                memcpy(sta_network.ssid, (const char *)EXT_AP_SSID, ssid_len);
                sta_network.ip.ipv4.addr_type = ADDR_TYPE_DHCP;
                sta_network.ssid_specific     = 1;

                if (strlen(EXT_AP_PASSPHRASE))
                {
                    sta_network.security.type = WLAN_SECURITY_WILDCARD;
                    psk_len = (strlen(EXT_AP_PASSPHRASE) <= (WLAN_PSK_MAX_LENGTH - 1)) ? strlen(EXT_AP_PASSPHRASE) :
                                                                                         (WLAN_PSK_MAX_LENGTH - 1);
                    strncpy(sta_network.security.psk, EXT_AP_PASSPHRASE, psk_len);
                    sta_network.security.psk_len = psk_len;
                }
                else
                {
                    sta_network.security.type = WLAN_SECURITY_NONE;
                }

                ret = wlan_add_network(&sta_network);

                if (ret != 0)
                {
                    PRINTF(" Failed to add network %d\r\n", ret);
                    return 0;
                }
                network_added = 1;
            }

            if (!uap_network_added)
            {
                uint8_t ssid_len = 0;
                uint8_t psk_len  = 0;

                wlan_initialize_uap_network(&uap_network);

                /* Set SSID as passed by the user */
                ssid_len = (strlen(AP_SSID) <= IEEEtypes_SSID_SIZE) ? strlen(AP_SSID) : IEEEtypes_SSID_SIZE;
                memcpy(uap_network.ssid, (const char *)AP_SSID, ssid_len);
                /* Channel 0 sets channel selection to auto */
                uap_network.channel       = 0;
                uap_network.security.type = WLAN_SECURITY_WPA2;
                /* Set the passphrase. Max WPA2 passphrase can be upto 64 ASCII chars */
                psk_len = (strlen(AP_PASSPHRASE) <= (WLAN_PSK_MAX_LENGTH - 1)) ? strlen(AP_PASSPHRASE) :
                                                                                 (WLAN_PSK_MAX_LENGTH - 1);
                strncpy(uap_network.security.psk, AP_PASSPHRASE, psk_len);
                uap_network.security.psk_len = psk_len;

                ret = wlan_add_network(&uap_network);
                if (ret != WM_SUCCESS)
                {
                    PRINTF(" Failed to add uAP network %d\r\n", ret);
                    return 0;
                }

                uap_network_added = 1;
            }

            timer = xTimerCreate("UDP Poll Timer", 1 / portTICK_PERIOD_MS, pdTRUE, (void *)0, timer_poll_udp_client);
            if (timer == NULL)
            {
                PRINTF("UDP Poll Timer creation failed!\r\n");
            }

            if (xTimerStart(timer, 0) != pdPASS)
            {
                PRINTF("UDP Poll Timer could not be started!\r\n");
            }

            if (network_added && uap_network_added)
            {
                s_wifi_ready = true;
            }

            break;
        case WLAN_REASON_INITIALIZATION_FAILED:
            PRINTF("app_cb: WLAN: initialization failed\r\n");
            break;
        case WLAN_REASON_SUCCESS:
            PRINTF("app_cb: WLAN: connected to network\r\n");

            ret = wlan_get_address(&addr);
            if (ret != WM_SUCCESS)
            {
                PRINTF("failed to get IP address\r\n");
                return 0;
            }

            net_inet_ntoa(addr.ipv4.address, ip);

            PRINTF("Connected to following BSS:\r\n");
            PRINTF("SSID = [%s], IP = [%s]\r\n", sta_network.ssid, ip);
            wifi_status |= (1<<BIT_CONN_RDY); //flag used for notifying other freertos tasks
            auth_fail = 0;

            notifyConnectedToAP();

            break;
        case WLAN_REASON_CONNECT_FAILED:
            PRINTF("app_cb: WLAN: connect failed\r\n");
            break;
        case WLAN_REASON_NETWORK_NOT_FOUND:
            PRINTF("app_cb: WLAN: network not found\r\n");
            break;
        case WLAN_REASON_NETWORK_AUTH_FAILED:
            PRINTF("app_cb: WLAN: network authentication failed\r\n");
            auth_fail++;
            if (auth_fail >= 3)
            {
                PRINTF("Authentication Failed. Disconnecting ... \r\n");
                wlan_disconnect();
                auth_fail = 0;
            }
            break;
        case WLAN_REASON_ADDRESS_SUCCESS:
            PRINTF("network mgr: DHCP new lease\r\n");
            break;
        case WLAN_REASON_ADDRESS_FAILED:
            PRINTF("app_cb: failed to obtain an IP address\r\n");
            break;
        case WLAN_REASON_USER_DISCONNECT:
            PRINTF("app_cb: disconnected\r\n");
            auth_fail = 0;
            break;
        case WLAN_REASON_LINK_LOST:
            PRINTF("app_cb: WLAN: link lost\r\n");
            break;
        case WLAN_REASON_CHAN_SWITCH:
            PRINTF("app_cb: WLAN: channel switch\r\n");
            break;
        case WLAN_REASON_UAP_SUCCESS:
            PRINTF("app_cb: WLAN: UAP Started\r\n");
            printSeparator();
            PRINTF("Soft AP \"%s\" Started successfully\r\n", AP_SSID);
            printSeparator();
            if (dhcp_server_start(net_get_uap_handle()))
                PRINTF("Error in starting dhcp server\r\n");

            PRINTF("DHCP Server started successfully\r\n");
            printSeparator();
            break;
        case WLAN_REASON_UAP_CLIENT_ASSOC:
            PRINTF("app_cb: WLAN: UAP a Client Associated\r\n");
            printSeparator();
            PRINTF("Client => ");
            print_mac((const char *)data);
            PRINTF("Associated with Soft AP\r\n");
            printSeparator();
            break;
        case WLAN_REASON_UAP_CLIENT_DISSOC:
            PRINTF("app_cb: WLAN: UAP a Client Dissociated\r\n");
            printSeparator();
            PRINTF("Client => ");
            print_mac((const char *)data);
            PRINTF("Dis-Associated from Soft AP\r\n");
            printSeparator();
            break;
        case WLAN_REASON_UAP_STOPPED:
            PRINTF("app_cb: WLAN: UAP Stopped\r\n");
            printSeparator();
            PRINTF("Soft AP \"%s\" Stoped successfully\r\n", AP_SSID);
            printSeparator();

            dhcp_server_stop();

            PRINTF("DHCP Server stopped successfully\r\n");
            printSeparator();
            break;
        case WLAN_REASON_PS_ENTER:
            PRINTF("app_cb: WLAN: PS_ENTER\r\n");
            break;
        case WLAN_REASON_PS_EXIT:
            PRINTF("app_cb: WLAN: PS EXIT\r\n");
            break;
        default:
            PRINTF("app_cb: WLAN: Unknown Event: %d\r\n", reason);
    }
    return 0;
}

/*!
 * @brief returns the state of wifi connectivity
 */
bool isWifiReady(void)
{
    return s_wifi_ready;
}

static int32_t waitWifiStatus(uint32_t ms, uint32_t statusMask)
{
	uint32_t curr_ms = 0;
	while((wifi_status&(1<<statusMask)) == 0 && curr_ms < ms)
	{
		vTaskDelay(100/portTICK_RATE_MS);// 100ms
		curr_ms = curr_ms + 100;
	}
	wifi_status&=~(1<<statusMask);
	if (curr_ms>=ms)
	{
		return 0; // timed out;
	}
	return 1;
}

/*******************************************************************************
 * Freetos Task: wifi
 * @brief ssid scan, wifi connect to ssid (hardcoded), get wifi network info
 ******************************************************************************/
void wifi_task(void *param)
{
	//  reset pulse to WL_REG_ON, but it seems to be unnecessary
	gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    GPIO_PinInit(GPIO9, 13, &gpio_config);
    GPIO_WritePinOutput(GPIO9, 13, 1);
    SDK_DelayAtLeastUs(30000, CLOCK_GetFreq(kCLOCK_CpuClk));
    GPIO_WritePinOutput(GPIO9, 13, 0);
    SDK_DelayAtLeastUs(30000, CLOCK_GetFreq(kCLOCK_CpuClk));
    GPIO_WritePinOutput(GPIO9, 13, 1);
    SDK_DelayAtLeastUs(30000, CLOCK_GetFreq(kCLOCK_CpuClk));

	custom_wifi_instance_t *t_wifi = (custom_wifi_instance_t *)param;
	wifi_cmd_queue = t_wifi->cmd_queue;
	wifi_response_queue = t_wifi->wifi_resQ;
	event_group_wifi = t_wifi->event_group_wifi;
	const EventBits_t xBitsToSet = WIFI_CONSOLE_NDATA;
	uint8_t dummy_byte = 0xAA;
    int32_t result = 0;
    (void)result;

    PRINTF("Initialize WLAN Driver\r\n");
    /* Initialize WIFI Driver */
	result = wlan_init(wlan_fw_bin, wlan_fw_bin_len);

    assert(WM_SUCCESS == result);

    result = wlan_start(wlan_event_callback);

    assert(WM_SUCCESS == result);
    struct t_user_wifi_command wifi_cmd_received;
    PRINTF("wifi task running\r\n");
    while (1)
    {
        /* wait for interface up */
        os_thread_sleep(os_msec_to_ticks(500));

        if (xQueueReceive(*wifi_cmd_queue, &(wifi_cmd_received), portMAX_DELAY) != pdTRUE)
        {
        	PRINTF("no received\r\n");
        }
        else
        {
        	PRINTF("command received\r\n");
        	switch (wifi_cmd_received.cmd_type)
        	{
				case WIFI_SCAN:
					PRINTF("cmd: wifi scan\r\n");
					ssidScan();
					if(waitWifiStatus(10000, BIT_SCAN_RDY))
					{
						PRINTF("wifi scan ready\r\n");
						//xQueueSend(*wifi_response_queue, &dummy_byte, 10);
						xEventGroupSetBits(*event_group_wifi, xBitsToSet );
					} else
					{
						PRINTF("Timeout: wifi scan\r\n");
					}
					break;
				case WIFI_CONN:
					if (connectToAP()==WM_SUCCESS)
					{

						if (waitWifiStatus(20000, BIT_CONN_RDY))
						{
							dummy_byte = 0x01;
						}
						else
						{
							dummy_byte = 0x02;
							PRINTF("Timeout: wifi conn\r\n");
						}
					}
					else
					{
						dummy_byte = 0x03;
					}
					xQueueSend(*wifi_response_queue, &dummy_byte, 10);
					break;
				case WIFI_IP:
					dummy_byte = printWlanInfo();
					xQueueSend(*wifi_response_queue, &dummy_byte, 10);
					break;
				default:
					break;
        	}
        }
    }
}

/* Report state => string */
const char *report_type_str[] = {
    "TCP_DONE_SERVER (RX)",        /* LWIPERF_TCP_DONE_SERVER,*/
    "TCP_DONE_CLIENT (TX)",        /* LWIPERF_TCP_DONE_CLIENT,*/
    "TCP_ABORTED_LOCAL",           /* LWIPERF_TCP_ABORTED_LOCAL, */
    "TCP_ABORTED_LOCAL_DATAERROR", /* LWIPERF_TCP_ABORTED_LOCAL_DATAERROR, */
    "TCP_ABORTED_LOCAL_TXERROR",   /* LWIPERF_TCP_ABORTED_LOCAL_TXERROR, */
    "TCP_ABORTED_REMOTE",          /* LWIPERF_TCP_ABORTED_REMOTE, */
    "UDP_DONE_SERVER (RX)",        /* LWIPERF_UDP_DONE_SERVER, */
    "UDP_DONE_CLIENT (TX)",        /* LWIPERF_UDP_DONE_CLIENT, */
    "UDP_ABORTED_LOCAL",           /* LWIPERF_UDP_ABORTED_LOCAL, */
    "UDP_ABORTED_LOCAL_DATAERROR", /* LWIPERF_UDP_ABORTED_LOCAL_DATAERROR, */
    "UDP_ABORTED_LOCAL_TXERROR",   /* LWIPERF_UDP_ABORTED_LOCAL_TXERROR, */
    "UDP_ABORTED_REMOTE",          /* LWIPERF_UDP_ABORTED_REMOTE, */
};

/** Prototype of a report function that is called when a session is finished.
    This report function shows the test results. */
static void lwiperf_report(void *arg,
                           enum lwiperf_report_type report_type,
                           const ip_addr_t *local_addr,
                           u16_t local_port,
                           const ip_addr_t *remote_addr,
                           u16_t remote_port,
                           u64_t bytes_transferred,
                           u32_t ms_duration,
                           u32_t bandwidth_kbitpsec)
{
    PRINTF("-------------------------------------------------\r\n");
    if (report_type < (sizeof(report_type_str) / sizeof(report_type_str[0])))
    {
        PRINTF(" %s \r\n", report_type_str[report_type]);
        if (local_addr && remote_addr)
        {
            PRINTF(" Local address : %u.%u.%u.%u ", ((u8_t *)local_addr)[0], ((u8_t *)local_addr)[1],
                   ((u8_t *)local_addr)[2], ((u8_t *)local_addr)[3]);
            PRINTF(" Port %d \r\n", local_port);
            PRINTF(" Remote address : %u.%u.%u.%u ", ((u8_t *)remote_addr)[0], ((u8_t *)remote_addr)[1],
                   ((u8_t *)remote_addr)[2], ((u8_t *)remote_addr)[3]);
            PRINTF(" Port %d \r\n", remote_port);
            PRINTF(" Bytes Transferred %llu \r\n", bytes_transferred);
            PRINTF(" Duration (ms) %d \r\n", ms_duration);
            PRINTF(" Bandwidth (Mbitpsec) %d \r\n", bandwidth_kbitpsec / 1000);
        }
    }
    else
    {
        PRINTF(" IPERF Report error\r\n");
    }
    PRINTF("\r\n");
}

/*!
 * @brief Function to start iperf test.
 */
static void iperf_test_start(void *arg)
{
    struct iperf_test_context *ctx = (struct iperf_test_context *)arg;
    ip4_addr_t server_address;

    ctx->iperf_session = NULL;

    if (!(ctx->tcp) && ctx->client_type == LWIPERF_DUAL)
    {
        /* Reducing timer interval of UDP Tx for Rx to run */
        xTimerChangePeriod(timer, os_msec_to_ticks(4), 100);
    }
    else
    {
        /* Setting timer to original value of 1 ms */
        xTimerChangePeriod(timer, 1 / portTICK_PERIOD_MS, 100);
    }

    if (ctx->server_mode)
    {
        if (ctx->tcp)
        {
            ctx->iperf_session = lwiperf_start_tcp_server(IP_ADDR_ANY, LWIPERF_TCP_PORT_DEFAULT, lwiperf_report, 0);
        }
        else
        {
            ctx->iperf_session =
                lwiperf_start_udp_server(netif_ip_addr4(netif_default), LWIPERF_TCP_PORT_DEFAULT, lwiperf_report, 0);
        }
    }
    else
    {
        if (ipaddr_aton(IPERF_SERVER_ADDRESS, &server_address) && IP_IS_V4(&server_address))
        {
            if (ctx->tcp)
            {
                ctx->iperf_session = lwiperf_start_tcp_client(&server_address, LWIPERF_TCP_PORT_DEFAULT,
                                                              ctx->client_type, IPERF_CLIENT_AMOUNT, lwiperf_report, 0);
            }
            else
            {
                ctx->iperf_session = lwiperf_start_udp_client(
                    netif_ip_addr4(netif_default), LWIPERF_TCP_PORT_DEFAULT, &server_address, LWIPERF_TCP_PORT_DEFAULT,
                    ctx->client_type, IPERF_CLIENT_AMOUNT, IPERF_UDP_CLIENT_RATE, 0, lwiperf_report, NULL);
            }
        }
        else
        {
            PRINTF("IPERF_SERVER_ADDRESS is not a valid IPv4 address!\r\n");
        }
    }

    if (ctx->iperf_session == NULL)
    {
        PRINTF("IPERF initialization failed!\r\n");
    }
}

/*!
 * @brief Function to abort iperf test.
 */
static void iperf_test_abort(void *arg)
{
    struct iperf_test_context *ctx = (struct iperf_test_context *)arg;

    if (ctx->iperf_session != NULL)
    {
        lwiperf_abort(ctx->iperf_session);
        ctx->iperf_session = NULL;
    }
}

/*!
 * @brief Invokes UDP polling, to be run on tcpip_thread.
 */
static void poll_udp_client(void *arg)
{
    LWIP_UNUSED_ARG(arg);

    lwiperf_poll_udp_client();
}

/*!
 * @brief Invokes UDP polling on tcpip_thread.
 */
static void timer_poll_udp_client(TimerHandle_t timer)
{
    LWIP_UNUSED_ARG(timer);

    tcpip_try_callback(poll_udp_client, NULL);
}


#if defined(__FAT_BUILD__)
/*!
 * @brief FAT wifi network found status.
 */
bool FATIsWifiNetworkFound(char* name)
{
	for(int i=0; i<wifiListLen; i++)
	{
		if(strcmp(name, wifiList[i].name) == 0) return true;
	}

	return false;
}

/*!
 * @brief FAT wifi network signal strength.
 */
int16_t FATGetWifiSignalStrength(char* name)
{
	for(int i=0; i<wifiListLen; i++)
	{
		if(strcmp(name, wifiList[i].name) == 0) return wifiList[i].strength;
	}

	return -1;
}
#endif
