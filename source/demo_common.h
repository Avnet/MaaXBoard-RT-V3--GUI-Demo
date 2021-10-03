
#ifndef _DEMO_COMMON_H_
#define _DEMO_COMMON_H_

#include "FreeRTOS.h"
#include "task.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_soc_src.h"

/*******************************************************************************
 * Functions
 ******************************************************************************/
void setInputSignal(bool state);
bool getInputSignal();

void set_red_led(bool state);
void set_green_led(bool state);
void set_blue_led(bool state);

bool get_red_led();
bool get_green_led();
bool get_blue_led();

void initLEDs();

#endif //_DEMO_COMMON_H_
