/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LITTLEVGL_SUPPORT_H
#define LITTLEVGL_SUPPORT_H

#include <stdint.h>
#include "display_support.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*
 * The littlevgl demos are for landscape panel. So for portrait panels, only
 * part of the screen is used.
 */
#define LCD_WIDTH DEMO_BUFFER_WIDTH
#if (DEMO_BUFFER_HEIGHT > DEMO_BUFFER_WIDTH)
//pf #define LCD_HEIGHT (LCD_WIDTH * 9 / 16)
#define LCD_HEIGHT DEMO_BUFFER_HEIGHT     //pf SDK examples limit the screen height to 405 pixels! Restriction removed here for height of 1280 pixels
#else
#define LCD_HEIGHT DEMO_BUFFER_HEIGHT
#endif
#define LCD_FB_BYTE_PER_PIXEL DEMO_BUFFER_BYTE_PER_PIXEL

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void lv_port_pre_init(void);
void lv_port_disp_init(void);
void lv_port_indev_init(void);

#if defined(__cplusplus)
}
#endif

uint8_t detect_display();

#endif /*LITTLEVGL_SUPPORT_H */
