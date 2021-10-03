/*
 * board_i2c.c
 *
 *  Created on: May 14, 2021
 *      Author: gulziibayar
 */

/* @Brief
 * There are total 4 lpi2c peripherals available on the Maaxboard RT.
 * lpi2c#2 - touchscreen chip(0x38), TO136<Rev.2> Security chip (0x50), Camera OV5640 (0x3C)
 * lpi2c#3 - available on 40 pin connector, no device is connected by default
 * lpi2c#5 - audio codec (0x0A), available on 18 pin connector
 * lpi2c#6 - available on 40 pin conenctor, no device is connected by default
 *
 * Freertos handle of lpi2c#2, lpi2c#5 are initialized by lvgl, audio tasks respectively.
 * lpi2c3, lpi2c6 are initialized by console task.
 *
 * Freertos i2c library is used for scanning the bus.
 * Bus is scanned with following way.
 * 		if address exists following transaction will take place. START+(ADDRESS)(R) + DATA + STOP
 * 		Otherwise START+(ADDRESS)(R) + STOP
 */

#include "fsl_lpi2c.h"
#include "board.h"
#include "expansion_i2c.h"
#include "fsl_debug_console.h"
#include "audio_demo.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define I2C_BUS_SIZE  4

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern lpi2c_rtos_handle_t master_rtos_handle2;
extern lpi2c_rtos_handle_t master_rtos_handle3;
extern lpi2c_rtos_handle_t master_rtos_handle6;

/*****************************************************************************\
 * Function:    scan_i2c_bus
 * Inputs:      lpi2c_rtos_handle_t *rtos_i2c_handle - rtos i2c handle
 * 				uint8_t *buff - expecting 16 byte buffer
 * Returns:     void
 * Description:
 *     This function checks all nodes 0 - 0x80 addresses. Store the address
 *     information inside input buffer. There can be total of 128 nodes.
 *     16 = 128/8. Each bit represents the node.
\*****************************************************************************/
void scan_i2c_bus(lpi2c_rtos_handle_t *rtos_i2c_handle, uint8_t *buff)
{
	uint8_t rxBuff;	// dummy byte
	uint8_t index = 0;
	uint8_t bit_pos = 0;
	status_t ret;
	uint32_t status;
	status_t reVal        = kStatus_Fail;
	size_t txCount        = 0xFFU;


    /* Lock resource mutex */
    if (xSemaphoreTake(rtos_i2c_handle->mutex, portMAX_DELAY) != pdTRUE)
    {
        return;
    }
	// Iterate through the address starting at 0x00
	for(uint8_t i2caddress=0;i2caddress<0x80;i2caddress++)
	{
		index = i2caddress/8;
		bit_pos = 7-(i2caddress%8);
		if (BOARD_LPI2C_Receive(rtos_i2c_handle->base, i2caddress, 0, 0, &rxBuff, 1) == kStatus_LPI2C_Nak)
		{
			buff[index] &= ~(1<<bit_pos);
			LPI2C_MasterStop(rtos_i2c_handle->base);
		}
		else
		{
			buff[index] |= (1<<bit_pos);
		}

		SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
	}

	LPI2C_MasterStop(rtos_i2c_handle->base);
	/* Unlock resource mutex */
	(void)xSemaphoreGive(rtos_i2c_handle->mutex);
}


/*****************************************************************************\
 * Function:    validate_i2c_index
 * Input:       index for i2c bus
 * Returns:     uint8_t
 * Description:
 *     returns the 1 - valid, 0 - not valid
\*****************************************************************************/
uint8_t valid_i2c_index(int index)
{
	int validIndexes[I2C_BUS_SIZE] = {2, 3, 5, 6};

	for (int i=0; i < I2C_BUS_SIZE; i++)
	{
		if (index == validIndexes[i])
		{
			return 1;
		}
	}
	return 0;
}

/*****************************************************************************\
 * Function:    select_i2c_bus
 * Input:       uint8_t index - index for i2c peripherals (1-4)
 * Returns:     void
 * Description:
 *     returns the LPI2C handle address based on the 1-4 indexing.
\*****************************************************************************/
lpi2c_rtos_handle_t *select_i2c_bus(uint8_t index)
{
	lpi2c_rtos_handle_t *rtos_i2c_handle;

	switch(index)
	{
	case 2:
		rtos_i2c_handle = &master_rtos_handle2;
		break;
	case 3:
		rtos_i2c_handle = &master_rtos_handle3;
		break;
	case 5:
		rtos_i2c_handle = (lpi2c_rtos_handle_t *)getRtosI2cHandle();
		break;
	case 6:
		rtos_i2c_handle = &master_rtos_handle6;
		break;
	default:
		rtos_i2c_handle = &master_rtos_handle3;
		break;
	}
	return rtos_i2c_handle;
}


