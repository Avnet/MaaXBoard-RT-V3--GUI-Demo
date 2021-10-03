/*
 * board_i2c.h
 *
 *  Created on: May 14, 2021
 *      Author: gulziibayar
 */

#ifndef EXPANSION_I2C_H_
#define EXPANSION_I2C_H_

#include "fsl_lpi2c.h"
#include "fsl_lpi2c_freertos.h"

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
void scan_i2c_bus(lpi2c_rtos_handle_t *rtos_i2c_handle, uint8_t *buff);

/*****************************************************************************\
 * Function:    select_i2c_bus
 * Input:       uint8_t index - index for i2c peripherals (1-4)
 * Returns:     void
 * Description:
 *     returns the LPI2C rtos handle address based on the 1-4 indexing.
\*****************************************************************************/
lpi2c_rtos_handle_t *select_i2c_bus(uint8_t index);

/*****************************************************************************\
 * Function:    validate_i2c_index
 * Input:       index for i2c bus
 * Returns:     uint8_t
 * Description:
 *     returns the 1 - valid, 0 - not valid, used for console input param validation
\*****************************************************************************/
uint8_t valid_i2c_index(int index);
#endif /* EXPANSION_I2C_H_ */
