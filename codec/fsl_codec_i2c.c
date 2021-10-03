/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_codec_i2c.h"
#include "fsl_lpi2c.h"
#include "fsl_lpi2c_freertos.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to i2c bases for each instance. */
static LPI2C_Type *const s_i2cBases[] = LPI2C_BASE_PTRS;
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Codec i2c bus initilization.
 *
 * param handle i2c master handle.
 * param i2CInstance instance number of the i2c bus, such as 0 is corresponding to I2C0.
 * param i2cBaudrate i2c baudrate.
 * param i2cSourceClockHz i2c source clock frequency.
 * return kStatus_HAL_I2cSuccess is success, else initial failed.
 */
status_t CODEC_I2C_Init(void *handle, uint32_t i2cInstance, uint32_t i2cBaudrate, uint32_t i2cSourceClockHz)
{
	lpi2c_master_config_t masterConfig;
    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = i2cBaudrate;
    return LPI2C_RTOS_Init((lpi2c_rtos_handle_t *)handle, s_i2cBases[i2cInstance], &masterConfig, i2cSourceClockHz);
}

/*!
 * brief Codec i2c de-initilization.
 *
 * param handle i2c master handle.
 * return kStatus_HAL_I2cSuccess is success, else deinitial failed.
 */
status_t CODEC_I2C_Deinit(void *handle)
{
	LPI2C_RTOS_Deinit((lpi2c_rtos_handle_t *)handle);
}

/*!
 * brief codec i2c send function.
 *
 * param handle i2c master handle.
 * param deviceAddress codec device address.
 * param subAddress register address.
 * param subaddressSize register address width.
 * param txBuff tx buffer pointer.
 * param txBuffSize tx buffer size.
 * return kStatus_HAL_I2cSuccess is success, else send failed.
 */
status_t CODEC_I2C_Send(void *handle,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize)
{
    lpi2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = (uint32_t)subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = txBuff;
    masterXfer.dataSize       = txBuffSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    return LPI2C_RTOS_Transfer((lpi2c_rtos_handle_t *)handle, &masterXfer);
}

/*!
 * brief codec i2c receive function.
 *
 * param handle i2c master handle.
 * param deviceAddress codec device address.
 * param subAddress register address.
 * param subaddressSize register address width.
 * param rxBuff rx buffer pointer.
 * param rxBuffSize rx buffer size.
 * return kStatus_HAL_I2cSuccess is success, else receive failed.
 */
status_t CODEC_I2C_Receive(void *handle,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kHAL_I2cRead;
    masterXfer.subaddress     = (uint32_t)subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = rxBuffSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    return LPI2C_RTOS_Transfer((lpi2c_rtos_handle_t *)handle, &masterXfer);
}
