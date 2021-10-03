/*
 * ether_if.h
 *
 *  Created on: Jun 2, 2021
 *      Author: gulziibayar
 */

#ifndef ETHER_IF_H_
#define ETHER_IF_H_

/*****************************************************************************\
 * Function:    eth_100m_task
 * Input:       parameter (eventgroup)
 * Returns:     void
 * Description:
 *     Main body of ethernet 100Mb task
\*****************************************************************************/
void eth_100m_task(void *pvParameters);

/*****************************************************************************\
 * Function:    eth_1g_task
 * Input:       parameter (eventgroup)
 * Returns:     void
 * Description:
 *     Main body of ethernet 1Gb task
\*****************************************************************************/
void eth_1g_task(void *pvParameters);

/*****************************************************************************\
 * Function:    dual_eth_configuration
 * Input:       void
 * Returns:     void
 * Description:
 *     Pin, clock, speed configuration for both ethernet interfaces
\*****************************************************************************/
void dual_eth_configuration();
#endif /* ETHER_IF_H_ */
