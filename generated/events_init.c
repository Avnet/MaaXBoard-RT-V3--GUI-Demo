/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "demo_common.h"
#include "lvgl_demo.h"

void events_init(lv_ui *ui)
{
}

static void screen0_MENU_imgbtn_1event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openLEDScreen();
	}
		break;
	default:
		break;
	}
}

static void screen0_MENU_imgbtn_2event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openAVScreen();
	}
		break;
	default:
		break;
	}
}

static void screen0_MENU_imgbtn_3event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openNetworkScreen();
	}
		break;
	default:
		break;
	}
}

static void screen0_MENU_imgbtn_4event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openCustomScreen();
	}
		break;
	default:
		break;
	}
}

static void screen0_MENU_imgbtn_5event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openUSBScreen();
	}
		break;
	default:
		break;
	}
}

static void screen0_MENU_imgbtn_6event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openHelpScreen();
	}
		break;
	default:
		break;
	}
}

void events_init_screen0_MENU(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen0_MENU_imgbtn_1, screen0_MENU_imgbtn_1event_handler);
	lv_obj_set_event_cb(ui->screen0_MENU_imgbtn_2, screen0_MENU_imgbtn_2event_handler);
	lv_obj_set_event_cb(ui->screen0_MENU_imgbtn_3, screen0_MENU_imgbtn_3event_handler);
	lv_obj_set_event_cb(ui->screen0_MENU_imgbtn_4, screen0_MENU_imgbtn_4event_handler);
	lv_obj_set_event_cb(ui->screen0_MENU_imgbtn_5, screen0_MENU_imgbtn_5event_handler);
	lv_obj_set_event_cb(ui->screen0_MENU_imgbtn_6, screen0_MENU_imgbtn_6event_handler);
}

static void screen1_LEDs_left_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

static void screen1_LEDs_right_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openNetworkScreen();
	}
		break;
	default:
		break;
	}
}

static void screen1_LEDs_redbtn0event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			set_red_led(true);
		}
	}
		break;
	case LV_EVENT_RELEASED:
	{
		if (!(lv_btn_get_state(obj) & LV_STATE_CHECKED))
		{
			set_red_led(false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen1_LEDs_greenbtn0event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			set_green_led(true);
		}
	}
		break;
	case LV_EVENT_RELEASED:
	{
		if (!(lv_btn_get_state(obj) & LV_STATE_CHECKED))
		{
			set_green_led(false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen1_LEDs_bluebtn0event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			set_blue_led(true);
		}
	}
		break;
	case LV_EVENT_RELEASED:
	{
		if (!(lv_btn_get_state(obj) & LV_STATE_CHECKED))
		{
			set_blue_led(false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen1_LEDs_home_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

void events_init_screen1_LEDs(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen1_LEDs_left_btn, screen1_LEDs_left_btnevent_handler);
	lv_obj_set_event_cb(ui->screen1_LEDs_right_btn, screen1_LEDs_right_btnevent_handler);
	lv_obj_set_event_cb(ui->screen1_LEDs_redbtn0, screen1_LEDs_redbtn0event_handler);
	lv_obj_set_event_cb(ui->screen1_LEDs_greenbtn0, screen1_LEDs_greenbtn0event_handler);
	lv_obj_set_event_cb(ui->screen1_LEDs_bluebtn0, screen1_LEDs_bluebtn0event_handler);
	lv_obj_set_event_cb(ui->screen1_LEDs_home_btn, screen1_LEDs_home_btnevent_handler);
}

static void screen2_WIFI_left_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openLEDScreen();
	}
		break;
	default:
		break;
	}
}

static void screen2_WIFI_right_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openUSBScreen();
	}
		break;
	default:
		break;
	}
}

static void screen2_WIFI_home_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

static void screen2_WIFI_ssid_refresh_imgbtnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		startSSIDScan();
	}
		break;
	default:
		break;
	}
}

void events_init_screen2_WIFI(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen2_WIFI_left_btn, screen2_WIFI_left_btnevent_handler);
	lv_obj_set_event_cb(ui->screen2_WIFI_right_btn, screen2_WIFI_right_btnevent_handler);
	lv_obj_set_event_cb(ui->screen2_WIFI_home_btn, screen2_WIFI_home_btnevent_handler);
	lv_obj_set_event_cb(ui->screen2_WIFI_ssid_refresh_imgbtn, screen2_WIFI_ssid_refresh_imgbtnevent_handler);
}

static void screen3_USB_left_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openNetworkScreen();
	}
		break;
	default:
		break;
	}
}

static void screen3_USB_right_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openAVScreen();
	}
		break;
	default:
		break;
	}
}

static void screen3_USB_home_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

static void screen3_USB_kbd_imgbtnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			setCaptureKeyboardInputOnTA(true);
		}
		else
		{
			setCaptureKeyboardInputOnTA(false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen3_USB_mouse_imgbtnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			setCaptureMouseInputOnTA(true);
		}
		else
		{
			setCaptureMouseInputOnTA(false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen3_USB_i2c_scan_imgbtnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		scani2cBusAndDisplay();
	}
		break;
	default:
		break;
	}
}

static void screen3_USB_i2c_ddlistevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		int ddIndex = lv_dropdown_get_selected(obj);

		switch (ddIndex)
		{
		case 0:
			setI2cBus(I2C2);
			break;
		case 1:
			setI2cBus(I2C3);
			break;
		case 2:
			setI2cBus(I2C5);
			break;
		case 3:
			setI2cBus(I2C6);
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
}

void events_init_screen3_USB(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen3_USB_left_btn, screen3_USB_left_btnevent_handler);
	lv_obj_set_event_cb(ui->screen3_USB_right_btn, screen3_USB_right_btnevent_handler);
	lv_obj_set_event_cb(ui->screen3_USB_home_btn, screen3_USB_home_btnevent_handler);
	lv_obj_set_event_cb(ui->screen3_USB_kbd_imgbtn, screen3_USB_kbd_imgbtnevent_handler);
	lv_obj_set_event_cb(ui->screen3_USB_mouse_imgbtn, screen3_USB_mouse_imgbtnevent_handler);
	lv_obj_set_event_cb(ui->screen3_USB_i2c_scan_imgbtn, screen3_USB_i2c_scan_imgbtnevent_handler);
	lv_obj_set_event_cb(ui->screen3_USB_i2c_ddlist, screen3_USB_i2c_ddlistevent_handler);
}

static void screen4_AV_left_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openUSBScreen();
	}
		break;
	default:
		break;
	}
}

static void screen4_AV_right_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openCustomScreen();
	}
		break;
	default:
		break;
	}
}

static void screen4_AV_home_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

static void screen4_AV_mic1_cbevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			enableMic(1, true);
		}
		else
		{
			enableMic(1, false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen4_AV_mic2_cbevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			enableMic(2, true);
		}
		else
		{
			enableMic(2, false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen4_AV_mic3_cbevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			enableMic(3, true);
		}
		else
		{
			enableMic(3, false);
		}
	}
		break;
	default:
		break;
	}
}

static void screen4_AV_mic4_cbevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			enableMic(4, true);
		}
		else
		{
			enableMic(4, false);
		}
	}
		break;
	default:
		break;
	}
}

void events_init_screen4_AV(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen4_AV_left_btn, screen4_AV_left_btnevent_handler);
	lv_obj_set_event_cb(ui->screen4_AV_right_btn, screen4_AV_right_btnevent_handler);
	lv_obj_set_event_cb(ui->screen4_AV_home_btn, screen4_AV_home_btnevent_handler);
	lv_obj_set_event_cb(ui->screen4_AV_mic1_cb, screen4_AV_mic1_cbevent_handler);
	lv_obj_set_event_cb(ui->screen4_AV_mic2_cb, screen4_AV_mic2_cbevent_handler);
	lv_obj_set_event_cb(ui->screen4_AV_mic3_cb, screen4_AV_mic3_cbevent_handler);
	lv_obj_set_event_cb(ui->screen4_AV_mic4_cb, screen4_AV_mic4_cbevent_handler);
}

static void screen5_SYSTEM_left_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openAVScreen();
	}
		break;
	default:
		break;
	}
}

static void screen5_SYSTEM_right_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openHelpScreen();
	}
		break;
	default:
		break;
	}
}

static void screen5_SYSTEM_home_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

static void screen5_SYSTEM_custom_imgbtnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		if (lv_btn_get_state(obj) & LV_STATE_CHECKED)
		{
			connectToSelectedAP();
		}
	}
		break;
	default:
		break;
	}
}

void events_init_screen5_SYSTEM(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen5_SYSTEM_left_btn, screen5_SYSTEM_left_btnevent_handler);
	lv_obj_set_event_cb(ui->screen5_SYSTEM_right_btn, screen5_SYSTEM_right_btnevent_handler);
	lv_obj_set_event_cb(ui->screen5_SYSTEM_home_btn, screen5_SYSTEM_home_btnevent_handler);
	lv_obj_set_event_cb(ui->screen5_SYSTEM_custom_imgbtn, screen5_SYSTEM_custom_imgbtnevent_handler);
}

static void screen6_HELP_left_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openCustomScreen();
	}
		break;
	default:
		break;
	}
}

static void screen6_HELP_right_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

static void screen6_HELP_home_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		openMenuScreen();
	}
		break;
	default:
		break;
	}
}

void events_init_screen6_HELP(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen6_HELP_left_btn, screen6_HELP_left_btnevent_handler);
	lv_obj_set_event_cb(ui->screen6_HELP_right_btn, screen6_HELP_right_btnevent_handler);
	lv_obj_set_event_cb(ui->screen6_HELP_home_btn, screen6_HELP_home_btnevent_handler);
}
