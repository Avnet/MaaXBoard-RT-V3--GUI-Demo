/*
 * audio_test.h
 *
 *  Created on: Jun 7, 2021
 *      Author: gulziibayar
 */

#ifndef AUDIO_DEMO_H_
#define AUDIO_TEST_H_

/*****************************************************************************\
 * Function:    disableAllMicChannels
 * Inputs:      void
 * Returns:     void
 * Description:
 *     This functions disables all the mic channels
\*****************************************************************************/
void disableAllMicChannels();

/*****************************************************************************\
 * Function:    getEnabledChannels
 * Inputs:      void
 * Returns:     uint8_t[2] pointer
 * Description:
 *     This functions returns the pointer to enabled mic channels uint8_t[0] - left, uint8_t[1] - right
\*****************************************************************************/
uint8_t * getEnabledChannels();

/*****************************************************************************\
 * Function:    enableMicChannel
 * Inputs:      uint8_t ch - channel number 0 - 3
 * 				bool state - true or false
 * Returns:     void
 * Description:
 *     This functions enables the selected channel from the GUI.
 *     Up to 4 channels are can be enabled
\*****************************************************************************/
void enableMicChannel(int id, bool state);

/*****************************************************************************\
 * Function:    audio_task_init
 * Inputs:      void
 * Returns:     void
 * Description:
 *     Main body of the audio_demo task
\*****************************************************************************/
void audio_task_init();

/*****************************************************************************\
 * Function:    enableAudioMicChannels
 * Inputs:      uint8_t ch - channel number 0 - 3
 * 				bool state - true or false
 * Returns:     void
 * Description:
 *     This functions enables the selected channel from the console.
 *     Only 2 channels can be enabled. Audio L/R
\*****************************************************************************/
void enableAudioMicChannels(uint8_t ch, uint8_t val);

/*****************************************************************************\
 * Function:    getRtosI2cHandle
 * Inputs:      void
 * Returns:     void * - RTOS I2C handle of lpi2c5 peripheral
 * Description:
 *	Audio codec driver initializes lpi2c5 peripheral, need this handle for scanning from gui or console.
\*****************************************************************************/
void * getRtosI2cHandle();
#endif /* AUDIO_DEMO_H_ */
