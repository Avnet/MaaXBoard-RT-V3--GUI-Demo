/*
 * ether_if.c
 *
 *  Created on: Jun 2, 2021
 *      Author: gulziibayar
 */

/* @Brief
 * There are two ethernet interfaces. 100Mb, 1Gb
 * Each interface runs its own freertos task. Each task uses dhcp client from LWIP thread to connect the network.
 * Must use following driver for interacting phy.
 * ethernet 100Mb - fsl_phyksz8081.c
 * ethernet 1Gb - fsl_phyksz9131rnx.c
 *
 * Following two ethernet tasks assume LWIP thread is running which is started by wifi task.
 *
 * There are two global struct defined here. They are updated accordingly when connected or disconnected to network.
 * 		1. eth_100mb_addr
 * 		2. eth_1g_addr
 */

#include "lwip/opt.h"
#if LWIP_IPV4 && LWIP_DHCP && LWIP_NETCONN

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "globals.h"

#include "lwip/dhcp.h"
#include "lwip/ip_addr.h"
#include "lwip/netifapi.h"
#include "lwip/prot/dhcp.h"
#include "lwip/tcpip.h"
#include "lwip/sys.h"
#include "enet_ethernetif.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_phy.h"

#include "fsl_phyksz8081.h"
#include "fsl_phyksz9131rnx.h"
#include "fsl_enet_mdio.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_enet.h"

/* MAC address configuration. */
#define configMAC_ADDR_100M                \
    {                                      \
        0x02, 0x12, 0x13, 0x10, 0x15, 0x11 \
    }

#define configMAC_ADDR_1G                  \
    {                                      \
        0x02, 0x12, 0x13, 0x10, 0x15, 0x12 \
    }

/* phy address in MDIO bus */
#define PHY_ADDRESS_100M    BOARD_ENET0_PHY_ADDRESS
#define PHY_ADDRESS_1G      BOARD_ENET1_PHY_ADDRESS

/* Phy operations functions for each phy */
#define PHY_OPS_100M        phyksz8081_ops
#define PHY_OPS_1G          phyksz9131rnx_ops

/* Function pointer for each interface initialization function */
#define NETIF_INIT_FN_100M 	ethernetif0_init
#define NETIF_INIT_FN_1G 	ethernetif1_init

/* MDIO operations. */
#define EXAMPLE_MDIO_OPS enet_ops

/* ENET clock frequency. */
#define EXAMPLE_CLOCK_FREQ CLOCK_GetRootClockFreq(kCLOCK_Root_Bus)

#ifndef EXAMPLE_NETIF_INIT_FN
/*! @brief Network interface initialization function. */
#define EXAMPLE_NETIF_INIT_FN ethernetif0_init
#endif /* EXAMPLE_NETIF_INIT_FN */

/*! @brief Stack size of the thread which prints DHCP info. */
#define PRINT_THREAD_STACKSIZE 512

/*! @brief Priority of the thread which prints DHCP info. */
#define PRINT_THREAD_PRIO DEFAULT_THREAD_PRIO

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t enet_mode_cnt = 0;

static mdio_handle_t mdioHandle100Mb = {.ops = &EXAMPLE_MDIO_OPS};
static mdio_handle_t mdioHandle1Gb = {.ops = &EXAMPLE_MDIO_OPS};
static phy_handle_t phyHandle_100m   = {.phyAddr = PHY_ADDRESS_100M, .mdioHandle = &mdioHandle100Mb, .ops = &PHY_OPS_100M};
static phy_handle_t phyHandle_1g   = {.phyAddr = PHY_ADDRESS_1G, .mdioHandle = &mdioHandle1Gb, .ops = &PHY_OPS_1G};

static struct netif netif_100m;
static struct netif netif_1g;
// global variables for storing ethernet interfaces state
static bool gConnected;

ip_ro_t eth_100mb_addr = {.eth = 0};
ip_ro_t eth_1g_addr = {.eth = 1};

static EventGroupHandle_t *temp_event_group;
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Enet1, Enet2 clock configuration
 */
static void BOARD_InitModuleClock(void)
{
    const clock_sys_pll1_config_t sysPll1Config = {
        .pllDiv2En = true,
    };
    CLOCK_InitSysPll1(&sysPll1Config);

    // set clock for 100M
    clock_root_config_t rootCfg = {.mux = 4, .div = 10}; /* Generate 50M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet1, &rootCfg);

    // set clock for 1G
    rootCfg.mux = 4;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Enet2, &rootCfg);

    /* Select syspll2pfd3, 528*18/24 = 396M */
    CLOCK_InitPfd(kCLOCK_PllSys2, kCLOCK_Pfd3, 24);
    rootCfg.mux = 7;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Bus, &rootCfg); /* Generate 198M bus clock. */
}

/*!
 * @brief Enet1, Enet2 clock mux
 */
static void IOMUXC_SelectENETClock(void)
{
	IOMUXC_GPR->GPR4 |= 0x3; /* 50M ENET_REF_CLOCK output to PHY and ENET module. */
	IOMUXC_GPR->GPR5 |= IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_MASK; /* bit1:iomuxc_gpr_enet_clk_dir
	                                                                 bit0:GPR_ENET_TX_CLK_SEL(internal or OSC) */
}

/*!
 * @brief Utility function for comparing arrays
 */
static uint8_t compareArrays(uint8_t a[], uint8_t b[], int len)
{
	for (int i=0; i<len; i++)
	{
		if (a[i] != b[i])
		{
			return 0;
		}
	}
	return 1;
}

/*!
 * @brief configure miiMode, miiSpeed based on the MAC address
 */
void BOARD_ENETFlexibleConfigure(enet_config_t *config, uint8_t *hwAddr)
{
	uint8_t temp_arr[6] = configMAC_ADDR_100M;

	if (compareArrays(hwAddr, temp_arr, 6))
	{
		config->miiMode = kENET_RmiiMode;
		config->miiSpeed = kENET_MiiSpeed100M;
	}
	else
	{
		config->miiMode = kENET_RgmiiMode;
		config->miiSpeed = kENET_MiiSpeed1000M;
	}
}

/*!
 * @brief Link status call back
 *
 * @param netif pointer
 */
static void cbETHLinkStatus(struct netif *state_netif)
{
	if (netif_is_link_up(state_netif))
	{
		PRINTF("LINK IS UP\r\n");
	}
	else
	{
		PRINTF("LINK IS UP\r\n");
	}
}

/*!
 * @brief Link status call back
 *
 * @param netif pointer
 */
static void cbETHNetIFStatus(struct netif *state_netif)
{
	char ip[16];
	char ipgw[16];
	uint8_t tempArr[6] = configMAC_ADDR_100M;
	uint8_t eth0_eth1 = 0;

	// check which ethernet interface received event
	if (compareArrays(state_netif->hwaddr, tempArr, 6))
	{
		eth0_eth1 = 0;
	}
	else
	{
		eth0_eth1 = 1;
	}

	if (netif_is_up(state_netif))
	{
		strcpy(ip, ip4addr_ntoa(netif_ip4_addr(state_netif)));
		strcpy(ipgw, ip4addr_ntoa(netif_ip4_gw(state_netif)));
		//messageDebug(DBG_INFO, __MODULE__, __LINE__,"cbETHNetIFStatus==UP, local interface IP is %s, GW IP is %s", ip, ipgw);
		PRINTF("%s==UP, local interface IP is %s, GW IP is %s\r\n", eth0_eth1==0?"eth_100Mb":"eth_1Gb", ip, ipgw);
		//PRINTF("cbETHNetIFStatus==UP\r\n");
		if (state_netif->ip_addr.addr)
		{
			gConnected=true;
			if (eth0_eth1==0)
			{
				eth_100mb_addr.connected = true;
				eth_100mb_addr.ip = (state_netif->ip_addr).addr;
				eth_100mb_addr.sub = (state_netif->netmask).addr;
				eth_100mb_addr.gw = (state_netif->gw).addr;
			}
			else
			{
				eth_1g_addr.connected = true;
				eth_1g_addr.ip = (state_netif->ip_addr).addr;
				eth_1g_addr.sub = (state_netif->netmask).addr;
				eth_1g_addr.gw = (state_netif->gw).addr;
			}
		}
	}
	else
	{
		if (eth0_eth1==0)
		{
			eth_100mb_addr.connected = false;
		}
		else
		{
			eth_1g_addr.connected = false;
		}

		PRINTF("%s==DOWN\r\n", eth0_eth1==0?"eth_100Mb":"eth_1Gb");
		gConnected=false;
	}
}

/*!
 * @brief Main body for Ethetnet 100Mb task
 */
static void init_ENET_100mb()
{
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
	static mem_range_t non_dma_memory[] = NON_DMA_MEMORY_ARRAY;
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
	ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;
	ethernetif_config_t enet_config = {
		.phyHandle  = &phyHandle_100m,
		.macAddress = configMAC_ADDR_100M,
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
		.non_dma_memory = non_dma_memory,
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
	};

	IP4_ADDR(&netif_ipaddr, 0U, 0U, 0U, 0U);
	IP4_ADDR(&netif_netmask, 0U, 0U, 0U, 0U);
	IP4_ADDR(&netif_gw, 0U, 0U, 0U, 0U);

	/* tcpip_init must be uncommented, if there is no wifi */
	//tcpip_init(NULL, NULL);
	netifapi_netif_add(&netif_100m, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, NETIF_INIT_FN_100M,
					   tcpip_input);

	netif_set_status_callback(&netif_100m, cbETHNetIFStatus);
	netif_set_link_callback(&netif_100m, cbETHLinkStatus);

	phy_config_t phyConfig;
	status_t status;

	phyConfig.phyAddr = enet_config.phyHandle->phyAddr;
	phyConfig.autoNeg = true;

	status = PHY_Init(enet_config.phyHandle, &phyConfig);

	if (kStatus_Success != status)
	{
		PRINTF("PHY 100Mb cannot be initialized\r\n");
		vTaskSuspend(NULL);
		//while(1);
	}

	/* set the event group ETH_100m_RDY bit*/
	xEventGroupSetBits(*temp_event_group, ETH_100m_RDY );
	bool link;
	static bool oldLink=false;
	while(1)
	{
		PHY_GetLinkStatus(enet_config.phyHandle, &link);

		if (link != oldLink)
		{
		   if (link)
		   {
			   sys_lock_tcpip_core();
			   netif_set_up(&netif_100m);
			   dhcp_start(&netif_100m);
			   sys_unlock_tcpip_core();
			   PRINTF("100Mb Link is coming up\r\n");
		   }
		   else
		   {
			   sys_lock_tcpip_core();
			   dhcp_release_and_stop(&netif_100m);
			   netif_set_down(&netif_100m);
			   sys_unlock_tcpip_core();
			   PRINTF("100Mb Link is going down..\r\n");
		   }
		   oldLink=link;
		}
		vTaskDelay(10);
	}
}

/*!
 * @brief Main body for Ethetnet 1Gb task
 */
static void init_ENET_1g() // must be called after 100m
{
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
	static mem_range_t non_dma_memory[] = NON_DMA_MEMORY_ARRAY;
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
	ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;
	ethernetif_config_t enet_config = {
		.phyHandle  = &phyHandle_1g,
		.macAddress = configMAC_ADDR_1G,
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
		.non_dma_memory = non_dma_memory,
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
	};

	gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
	/*
	 * Following 2 lines must be uncommented when running ethernet 1G alone without 100mb
	 */

	EnableIRQ(ENET_1G_MAC0_Tx_Rx_1_IRQn);
	EnableIRQ(ENET_1G_MAC0_Tx_Rx_2_IRQn);

	IP4_ADDR(&netif_ipaddr, 0U, 0U, 0U, 0U);
	IP4_ADDR(&netif_netmask, 0U, 0U, 0U, 0U);
	IP4_ADDR(&netif_gw, 0U, 0U, 0U, 0U);

	/* tcpip_init must be uncommented, if there is no wifi or ethernet100mb task*/
	//tcpip_init(NULL, NULL);

	netifapi_netif_add(&netif_1g, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, NETIF_INIT_FN_1G,
					   tcpip_input);

	netif_set_status_callback(&netif_1g, cbETHNetIFStatus);
	netif_set_link_callback(&netif_1g, cbETHLinkStatus);

	phy_config_t phyConfig;
	status_t status;

	phyConfig.phyAddr = enet_config.phyHandle->phyAddr;
	phyConfig.autoNeg = true;

	status = PHY_Init(enet_config.phyHandle, &phyConfig);

	if (kStatus_Success != status)
	{
		PRINTF("PHY 1G cannot be initialized\r\n");
		vTaskSuspend(NULL);
		//while(1);
	}

	bool link;
	static bool oldLink=false;
	while(1)
	{
		PHY_GetLinkStatus(enet_config.phyHandle, &link);

		if (link != oldLink)
		{
		   if (link)
		   {
			   sys_lock_tcpip_core();
			   netif_set_up(&netif_1g);
			   dhcp_start(&netif_1g);
			   sys_unlock_tcpip_core();
			   PRINTF("1Gb Link is coming up\r\n");
		   }
		   else
		   {
			   sys_lock_tcpip_core();
			   dhcp_release_and_stop(&netif_1g);
			   netif_set_down(&netif_1g);
			   sys_unlock_tcpip_core();
			   PRINTF("1Gb Link is going down..\r\n");
		   }
		   oldLink=link;
		}
		vTaskDelay(10);
	}
}

/*!
 * @brief Pin, clock, speed configuration for both ethernet interfaces
 */
void dual_eth_configuration()
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
    BOARD_InitModuleClock();
    IOMUXC_SelectENETClock();
    BOARD_InitEnetPins(); //100mb
    BOARD_InitEnet1GPins(); //1gb
    GPIO_PinInit(GPIO9, 11, &gpio_config);
    GPIO_PinInit(GPIO8, 21, &gpio_config);
    /* Pull up the ENET_INT before RESET. */
    GPIO_WritePinOutput(GPIO9, 11, 1);
    GPIO_WritePinOutput(GPIO8, 21, 0);
    SDK_DelayAtLeastUs(10000, CLOCK_GetFreq(kCLOCK_CpuClk));
    GPIO_WritePinOutput(GPIO8, 21, 1);
    SDK_DelayAtLeastUs(6, CLOCK_GetFreq(kCLOCK_CpuClk));

    mdioHandle100Mb.resource.csrClock_Hz = EXAMPLE_CLOCK_FREQ;
    mdioHandle1Gb.resource.csrClock_Hz = EXAMPLE_CLOCK_FREQ;
}

/*******************************************************************************
 * Freetos Task: eth_100m
 * @brief dhcp client running to get ip address
 ******************************************************************************/
void eth_100m_task(void *pvParameters)
{
	temp_event_group = (EventGroupHandle_t *)pvParameters;
	EventBits_t bits;
	/* used for waiting wifi, wifi should initialize lwip thread. */

#if (defined(WIFI_EN) && (WIFI_EN==1))
	bits = xEventGroupWaitBits(*temp_event_group, WIFI_RDY, pdFALSE, pdTRUE, portMAX_DELAY);
#else
	tcpip_init(NULL, NULL);
#endif
	init_ENET_100mb();
}

/*******************************************************************************
 * Freetos Task: eth_1G
 * @brief dhcp client running to get ip address
 ******************************************************************************/
void eth_1g_task(void *pvParameters)
{
	temp_event_group = (EventGroupHandle_t *)pvParameters;
	EventBits_t bits, compareBits = 0;

#if (defined(WIFI_EN) && (WIFI_EN==1))
	compareBits |= WIFI_RDY;
#endif

#if (defined(ETH100MB_EN) && (ETH100MB_EN==1))
	compareBits |= ETH_100m_RDY;
#endif

	/* used for waiting wifi, eth_100Mb task */
#if (defined(WIFI_EN) && (WIFI_EN==1)) || (defined(ETH100MB_EN) && (ETH100MB_EN==1))
	bits = xEventGroupWaitBits(*temp_event_group, compareBits, pdFALSE, pdTRUE, portMAX_DELAY);
#else
	tcpip_init(NULL, NULL);
#endif
	init_ENET_1g();
}

#endif
