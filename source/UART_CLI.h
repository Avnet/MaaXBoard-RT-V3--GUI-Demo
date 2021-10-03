/*
 * UART_CLI.h
 *
 *  Created on: May 14, 2021
 *      Author: gulziibayar
 */

#ifndef UART_CLI_H_
#define UART_CLI_H_
#include "fsl_lpuart_freertos.h"

/*****************************************************************************\
 * Function:    console_task
 * Input:       custom_console_instance_t *, for passing parameters
 * Returns:     void
 * Description:
 *     Main body of console task
\*****************************************************************************/
void console_task(void *pvParameters);
#endif /* UART_CLI_H_ */
