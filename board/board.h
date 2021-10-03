/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "fsl_lpi2c.h"
#include "fsl_lpi2c_freertos.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "MIMXRT1170-EVK"
#ifndef DEBUG_CONSOLE_UART_INDEX
#define DEBUG_CONSOLE_UART_INDEX 6
#endif

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_CLK_FREQ 24000000

#if DEBUG_CONSOLE_UART_INDEX == 1
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART1
#define BOARD_DEBUG_UART_INSTANCE 1U
#define BOARD_UART_IRQ            LPUART1_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART1_IRQHandler
#elif DEBUG_CONSOLE_UART_INDEX == 2
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART2
#define BOARD_DEBUG_UART_INSTANCE 2U
#define BOARD_UART_IRQ            LPUART2_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART2_IRQHandler
#elif DEBUG_CONSOLE_UART_INDEX == 6
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART6
#define BOARD_DEBUG_UART_INSTANCE 6U
#define BOARD_UART_IRQ            LPUART6_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART6_IRQHandler
#elif DEBUG_CONSOLE_UART_INDEX == 12
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART12
#define BOARD_DEBUG_UART_INSTANCE 12U
#define BOARD_UART_IRQ            LPUART12_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART12_IRQHandler
#else
#error "Unsupported UART"
#endif

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE (115200U)
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/* Definitions for eRPC MU transport layer */
#if defined(FSL_FEATURE_MU_SIDE_A)
#define MU_BASE        MUA
#define MU_IRQ         MUA_IRQn
#define MU_IRQ_HANDLER MUA_IRQHandler
#endif
#if defined(FSL_FEATURE_MU_SIDE_B)
#define MU_BASE        MUB
#define MU_IRQ         MUB_IRQn
#define MU_IRQ_HANDLER MUB_IRQHandler
#endif
#define MU_IRQ_PRIORITY (2)

/*! @brief USER (GREEN) RGB LED on MaaXBoard RT Rev.1 and Rev.2 is on GPIO8_IO28 */
#define LOGIC_LED_ON  (0U)
#define LOGIC_LED_OFF (1U)
#ifndef BOARD_USER_LED_GPIO
#define BOARD_USER_LED_GPIO GPIO8        //MaaXBoard Rev.1 and Rev.2
#endif
#ifndef BOARD_USER_LED_GPIO_PIN
#define BOARD_USER_LED_GPIO_PIN (28U)    //MaaXBoard Rev.1 and Rev.2
#endif

#define USER_LED_INIT(output)                                            \
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, output); \
    BOARD_USER_LED_GPIO->GDIR |= (1U << BOARD_USER_LED_GPIO_PIN) /*!< Enable target USER_LED */
#define USER_LED_OFF() \
    GPIO_PortClear(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN)                 /*!< Turn off target USER_LED */
#define USER_LED_ON() GPIO_PortSet(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN) /*!<Turn on target USER_LED*/
#define USER_LED_TOGGLE()                                       \
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, \
                  0x1 ^ GPIO_PinRead(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN)) /*!< Toggle target USER_LED */

/*! @brief USER_RED RGB LED on MaaXBoard RT is on GPIO9_IO07 */
#ifndef BOARD_USER_LED_RED_GPIO
#define BOARD_USER_LED_RED_GPIO GPIO9        //MaaXBoard Rev.2
#endif
#ifndef BOARD_USER_LED_RED_GPIO_PIN
#define BOARD_USER_LED_RED_GPIO_PIN (7U)     //MaaXBoard Rev.2
#endif

#define USER_LED_RED_INIT(output)                                            \
    GPIO_PinWrite(BOARD_USER_LED_RED_GPIO, BOARD_USER_LED_RED_GPIO_PIN, output); \
    BOARD_USER_LED_RED_GPIO->GDIR |= (1U << BOARD_USER_LED_RED_GPIO_PIN) /*!< Enable target USER_LED */
#define USER_LED_RED_OFF() \
    GPIO_PortClear(BOARD_USER_LED_RED_GPIO, 1U << BOARD_USER_LED_RED_GPIO_PIN)                 /*!< Turn off target USER_LED */
#define USER_LED_RED_ON() GPIO_PortSet(BOARD_USER_LED_RED_GPIO, 1U << BOARD_USER_LED_RED_GPIO_PIN) /*!<Turn on target USER_LED*/
#define USER_LED_RED_TOGGLE()                                       \
    GPIO_PinWrite(BOARD_USER_LED_RED_GPIO, BOARD_USER_LED_RED_GPIO_PIN, \
                  0x1 ^ GPIO_PinRead(BOARD_USER_LED_RED_GPIO, BOARD_USER_LED_RED_GPIO_PIN))    /*!< Toggle target USER_LED */

/*! @brief USER_BLUE RGB LED on MaaXBoard RT is on GPIO9_IO09 */
#ifndef BOARD_USER_LED_BLUE_GPIO
#define BOARD_USER_LED_BLUE_GPIO GPIO9        //MaaXBoard Rev.2
#endif
#ifndef BOARD_USER_LED_BLUE_GPIO_PIN
#define BOARD_USER_LED_BLUE_GPIO_PIN (9U)     //MaaXBoard Rev.2
#endif

#define USER_LED_BLUE_INIT(output)                                            \
    GPIO_PinWrite(BOARD_USER_LED_BLUE_GPIO, BOARD_USER_LED_BLUE_GPIO_PIN, output); \
    BOARD_USER_LED_BLUE_GPIO->GDIR |= (1U << BOARD_USER_LED_BLUE_GPIO_PIN) /*!< Enable target USER_LED */
#define USER_LED_BLUE_OFF() \
    GPIO_PortClear(BOARD_USER_LED_BLUE_GPIO, 1U << BOARD_USER_LED_BLUE_GPIO_PIN)                 /*!< Turn off target USER_LED */
#define USER_LED_BLUE_ON() GPIO_PortSet(BOARD_USER_LED_BLUE_GPIO, 1U << BOARD_USER_LED_BLUE_GPIO_PIN) /*!<Turn on target USER_LED*/
#define USER_LED_BLUE_TOGGLE()                                       \
    GPIO_PinWrite(BOARD_USER_LED_BLUE_GPIO, BOARD_USER_LED_BLUE_GPIO_PIN, \
                  0x1 ^ GPIO_PinRead(BOARD_USER_LED_BLUE_GPIO, BOARD_USER_LED_BLUE_GPIO_PIN))    /*!< Toggle target USER_LED */


/*! @brief USER Button Switch on MaaXBoard RT Rev.1 is on GPIO8_IO22  */
/*! @brief USER Button Switch on MaaXBoard RT Rev.2 is on GPIO13_IO00  */
/*! @brief Define the port interrupt number for the board switch */
#ifndef BOARD_USER_BUTTON_GPIO
#define BOARD_USER_BUTTON_GPIO GPIO13     //MaaXBoard Rev.2 S1 button: GPIO = GPIO13
#endif
#ifndef BOARD_USER_BUTTON_GPIO_PIN
#define BOARD_USER_BUTTON_GPIO_PIN (0U)   //MaaXBoard Rev.2 S1 button: PIN  = IO00
#endif
#define BOARD_USER_BUTTON_IRQ         GPIO13_Combined_0_31_IRQn       // Combined IRQ flag for GPIO13 signal 0 - 31
#define BOARD_USER_BUTTON_IRQ_HANDLER GPIO13_Combined_0_31_IRQHandler
#define BOARD_USER_BUTTON_NAME        "S1" //MaaXBoard S1 pushbutton

/*! @brief The board flash size */
#define BOARD_FLASH_SIZE (0x1000000U)

/* SKIP_SEMC_INIT can also be defined independently */
#ifdef USE_SDRAM
#define SKIP_SEMC_INIT
#endif

/*! @brief The ENET0 PHY address. */
#define BOARD_ENET0_PHY_ADDRESS (0x02U) /* Phy address of enet port 0. */

/*! @brief The ENET1 PHY address. */
#define BOARD_ENET1_PHY_ADDRESS (0x07U) /* Phy address of enet port 1. */

/*! @brief The EMVSIM SMARTCARD PHY configuration. */
#define BOARD_SMARTCARD_MODULE                (EMVSIM1)      /*!< SMARTCARD communicational module instance */
#define BOARD_SMARTCARD_MODULE_IRQ            (EMVSIM1_IRQn) /*!< SMARTCARD communicational module IRQ handler */
#define BOARD_SMARTCARD_CLOCK_MODULE_CLK_FREQ (CLOCK_GetRootClockFreq(kCLOCK_Root_Emv1))
#define BOARD_SMARTCARD_CLOCK_VALUE           (4000000U) /*!< SMARTCARD clock frequency */

/* USB PHY condfiguration */
#define BOARD_USB_PHY_D_CAL     (0x07U)
#define BOARD_USB_PHY_TXCAL45DP (0x06U)
#define BOARD_USB_PHY_TXCAL45DM (0x06U)

#define BOARD_ARDUINO_INT_IRQ   (GPIO1_INT3_IRQn)
#define BOARD_ARDUINO_I2C_IRQ   (LPI2C1_IRQn)
#define BOARD_ARDUINO_I2C_INDEX (1)

#define BOARD_HAS_SDCARD (1U)

/*! @brief The WIFI-QCA shield pin. */
#define BOARD_INITGT202SHIELD_PWRON_GPIO      GPIO1               /*!< GPIO device name: GPIO */
#define BOARD_INITGT202SHIELD_PWRON_PORT      1U                  /*!< PORT device index: 1 */
#define BOARD_INITGT202SHIELD_PWRON_GPIO_PIN  3U                  /*!< PIO4 pin index: 3 */
#define BOARD_INITGT202SHIELD_PWRON_PIN_NAME  GPIO1_3             /*!< Pin name */
#define BOARD_INITGT202SHIELD_PWRON_LABEL     "PWRON"             /*!< Label */
#define BOARD_INITGT202SHIELD_PWRON_NAME      "PWRON"             /*!< Identifier name */
#define BOARD_INITGT202SHIELD_PWRON_DIRECTION kGPIO_DigitalOutput /*!< Direction */

#define BOARD_INITGT202SHIELD_IRQ_GPIO      GPIO1              /*!< GPIO device name: GPIO */
#define BOARD_INITGT202SHIELD_IRQ_PORT      1U                 /*!< PORT device index: 1 */
#define BOARD_INITGT202SHIELD_IRQ_GPIO_PIN  19U                /*!< PIO1 pin index: 19 */
#define BOARD_INITGT202SHIELD_IRQ_PIN_NAME  GPIO1_19           /*!< Pin name */
#define BOARD_INITGT202SHIELD_IRQ_LABEL     "IRQ"              /*!< Label */
#define BOARD_INITGT202SHIELD_IRQ_NAME      "IRQ"              /*!< Identifier name */
#define BOARD_INITGT202SHIELD_IRQ_DIRECTION kGPIO_DigitalInput /*!< Direction */

#define BOARD_INITSILEX2401SHIELD_PWRON_GPIO      GPIO1               /*!< GPIO device name: GPIO */
#define BOARD_INITSILEX2401SHIELD_PWRON_PORT      1U                  /*!< PORT device index: 1 */
#define BOARD_INITSILEX2401SHIELD_PWRON_GPIO_PIN  9U                  /*!< PIO4 pin index: 9 */
#define BOARD_INITSILEX2401SHIELD_PWRON_PIN_NAME  GPIO1_9             /*!< Pin name */
#define BOARD_INITSILEX2401SHIELD_PWRON_LABEL     "PWRON"             /*!< Label */
#define BOARD_INITSILEX2401SHIELD_PWRON_NAME      "PWRON"             /*!< Identifier name */
#define BOARD_INITSILEX2401SHIELD_PWRON_DIRECTION kGPIO_DigitalOutput /*!< Direction */

#define BOARD_INITSILEX2401SHIELD_IRQ_GPIO      GPIO1              /*!< GPIO device name: GPIO */
#define BOARD_INITSILEX2401SHIELD_IRQ_PORT      1U                 /*!< PORT device index: 1 */
#define BOARD_INITSILEX2401SHIELD_IRQ_GPIO_PIN  11U                /*!< PIO1 pin index: 11 */
#define BOARD_INITSILEX2401SHIELD_IRQ_PIN_NAME  GPIO1_11           /*!< Pin name */
#define BOARD_INITSILEX2401SHIELD_IRQ_LABEL     "IRQ"              /*!< Label */
#define BOARD_INITSILEX2401SHIELD_IRQ_NAME      "IRQ"              /*!< Identifier name */
#define BOARD_INITSILEX2401SHIELD_IRQ_DIRECTION kGPIO_DigitalInput /*!< Direction */

/* @Brief Board accelerator sensor configuration */
#define BOARD_ACCEL_I2C_BASEADDR LPI2C5
/* Clock divider for LPI2C clock source */
#define BOARD_ACCEL_I2C_CLOCK_FREQ (CLOCK_GetRootClockFreq(kCLOCK_Root_Lpi2c5))

#define BOARD_CODEC_I2C_BASEADDR             LPI2C5
#define BOARD_CODEC_I2C_INSTANCE             5U
#define BOARD_CODEC_I2C_CLOCK_SOURCE_SELECT  (0U)
#define BOARD_CODEC_I2C_CLOCK_SOURCE_DIVIDER (6U)
#define BOARD_CODEC_I2C_CLOCK_FREQ           (24000000U)

/* @Brief Board CAMERA configuration */
#define BOARD_CAMERA_I2C_BASEADDR      LPI2C2
#define BOARD_CAMERA_I2C_CLOCK_ROOT    kCLOCK_Root_Lpi2c2
#define BOARD_CAMERA_I2C_CLOCK_SOURCE  (1U)  /* OSC24M. */
#define BOARD_CAMERA_I2C_CLOCK_DIVIDER (12U) /* Divider = 12, LPI2C clock frequency 2M. */

/*! @brief The camera pins. */
#define BOARD_CAMERA_PWDN_GPIO GPIO2            //MaaXBoard v2 uses GPIO2.08
#define BOARD_CAMERA_PWDN_PIN  8U
#define BOARD_CAMERA_RST_GPIO  GPIO9            //MaaXBoard v2 uses GPIO9.08
#define BOARD_CAMERA_RST_PIN   8U

// ====================================================
// MaaXBoard RT MIPI-DSI Pinout
// ====================================================
//  pin B9  : MIPI_DSI : MIPI_DSI_CKP   : DSI_CKP     :
//  pin A9  : MIPI_DSI : MIPI_DSI_CKN   : DSI_CKN     :
//  pin B8  : MIPI_DSI : MIPI_DSI_DP0   : DSI_DP0     :
//  pin A8  : MIPI_DSI : MIPI_DSI_DN0   : DSI_DN0     :
//  pin B10 : MIPI_DSI : MIPI_DSI_DP1   : DSI_DP1     :
//  pin A10 : MIPI_DSI : MIPI_DSI_DN1   : DSI_DN1     :
//  pin K4  : I2C2_SDA : GPIO_EMC_B2_01 : I2C2_SDA    : (LPI2C2_SDA)
//  pin K2  : I2C2_SCL : GPIO_EMC_B2_00 : I2C2_SCL    : (LPI2C2_SCL)

//  pin M17 : GPIO9.28 : GPIO_AD_29     : DSI_EN      : (WDOG_B)     = active HIGH
//  pin K17 : GPIO9.29 : GPIO_AD_30     : DSI_TS_INT  : (SIM1_TRXD)  = active LOW
//  pin P13 : GPIO9.04 : GPIO_AD_05     : DSI_TS_RST  : (SIM1_CLK)   = active LOW
//  pin M2  : GPIO8.22 : GPIO_EMC_B2_12 : DSI_LCD_RST : (SIM1_RST)   = active LOW (unused, is on 20pin header)
//  pin R1  : GPIO8.13 : GPIO_EMC_B2_03 : DSI_BL_PWM  : (LPSPI1_SDO) = active HIGH
// ====================================================
// RT1176 Processor to MIPI-CSI Camera Interface
// ====================================================
//  pin B11 : MIPI_CSI  : MIPI_CSI_DP0   : CSI_DP0    :
//  pin A11 : MIPI_CSI  : MIPI_CSI_DN0   : CSI_DN0    :
//  pin B13 : MIPI_CSI  : MIPI_CSI_DP1   : CSI_DP1    :
//  pin A13 : MIPI_CSI  : MIPI_CSI_DN1   : CSI_DN1    :
//  pin B12 : MIPI_CSI  : MIPI_CSI_CKP   : CSI_CKP    :
//  pin A12 : MIPI_CSI  : MIPI_CSI_CKN   : CSI_CKN    :
//  pin K4  : I2C5_SDA  : GPIO_EMC_B2_01 : I2C2_SDA   : (CSI_I2C2_SDA)
//  pin K2  : I2C5_SCL  : GPIO_EMC_B2_00 : I2C2_SCL   : (CSI_I2C2_SCL)
//  pin K1  : GPIO2.08  : GPIO_EMC_B1_40 : CAM_PWDN   : (CSI_PWDN)
//  pin R16 : GPIO9.08  : GPIO_LPSR_15   : CAM_RST    : (CSI_RSTB) (Note! Unused, routed to pin? of 18 pin header. Do not connect to pin U7 !!!)
// ====================================================

/*! @brief MIPI panel pins (MaaXBoard-RT) */
#define BOARD_MIPI_PANEL_RST_GPIO   GPIO9      //MaaXBoard DSI_LCD_RST on GPIO8.22 - Changed to GPIO9.04
#define BOARD_MIPI_PANEL_RST_PIN    4
#define BOARD_MIPI_PANEL_POWER_GPIO GPIO9      //MaaXBoard DSI_EN on GPIO9.28
#define BOARD_MIPI_PANEL_POWER_PIN  28
/* Back light pin. */
#define BOARD_MIPI_PANEL_BL_GPIO GPIO8         //MaaXBoard DSI_BL_PWM on GPIO8.13
#define BOARD_MIPI_PANEL_BL_PIN  13
/* Touch Screen (MaaXBoard-RT) */
#define BOARD_MIPI_PANEL_TOUCH_I2C_BASEADDR      LPI2C6
#define BOARD_MIPI_PANEL_TOUCH_I2C_CLOCK_ROOT    kCLOCK_Root_Lpi2c6
#define BOARD_MIPI_PANEL_TOUCH_I2C_CLOCK_SOURCE  (1U)  /* OSC24M. */
#define BOARD_MIPI_PANEL_TOUCH_I2C_CLOCK_DIVIDER (12U) /* Divider = 12, LPI2C clock frequency 2M. */
#define BOARD_MIPI_PANEL_TOUCH_I2C_CLOCK_FREQ    CLOCK_GetRootClockFreq(BOARD_MIPI_PANEL_TOUCH_I2C_CLOCK_ROOT)
#define BOARD_MIPI_PANEL_TOUCH_RST_GPIO          GPIO8  //MaaXBoard DSI_TS_RST on GPIO9.04
#define BOARD_MIPI_PANEL_TOUCH_RST_PIN           22
#define BOARD_MIPI_PANEL_TOUCH_INT_GPIO          GPIO9  //MaaXBoard DSI_TS_INT on GPIO9.29
#define BOARD_MIPI_PANEL_TOUCH_INT_PIN           29


/* SD card detection method when using wifi module. */
#define BOARD_WIFI_SD_DETECT_TYPE kSDMMCHOST_DetectCardByHostDATA3

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
uint32_t BOARD_DebugConsoleSrcFreq(void);

void BOARD_InitDebugConsole(void);

void BOARD_ConfigMPU(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize);
status_t BOARD_RTOS_LPI2C_Receive(lpi2c_rtos_handle_t *handle,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subAddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
status_t BOARD_LPI2C_SendSCCB(LPI2C_Type *base,
                              uint8_t deviceAddress,
                              uint32_t subAddress,
                              uint8_t subaddressSize,
                              uint8_t *txBuff,
                              uint8_t txBuffSize);
status_t BOARD_LPI2C_ReceiveSCCB(LPI2C_Type *base,
                                 uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subaddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
void BOARD_Camera_I2C_Init(void);
status_t BOARD_Camera_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Camera_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

status_t BOARD_Camera_I2C_SendSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Camera_I2C_ReceiveSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

void BOARD_RTOS_I2C_Init(uint8_t i2c_periph);
void BOARD_MIPIPanelTouch_I2C_Init(void);
status_t BOARD_MIPIPanelTouch_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_MIPIPanelTouch_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */

void BOARD_SD_Pin_Config(uint32_t speed, uint32_t strength);
void BOARD_MMC_Pin_Config(uint32_t speed, uint32_t strength);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
