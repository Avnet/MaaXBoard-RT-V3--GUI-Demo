/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts/guider_fonts.h"

typedef struct
{
	lv_obj_t *screen0_MENU;
	lv_obj_t *screen0_MENU_cursor_img;
	lv_obj_t *screen0_MENU_canvas_white;
	lv_obj_t *screen0_MENU_avlogoimg0;
	lv_obj_t *screen0_MENU_board_img;
	lv_obj_t *screen0_MENU_page_label;
	lv_obj_t *screen0_MENU_label_1;
	lv_obj_t *screen0_MENU_imgbtn_1;
	lv_obj_t *screen0_MENU_imgbtn_1_label;
	lv_obj_t *screen0_MENU_imgbtn_2;
	lv_obj_t *screen0_MENU_imgbtn_2_label;
	lv_obj_t *screen0_MENU_imgbtn_3;
	lv_obj_t *screen0_MENU_imgbtn_3_label;
	lv_obj_t *screen0_MENU_imgbtn_4;
	lv_obj_t *screen0_MENU_imgbtn_4_label;
	lv_obj_t *screen0_MENU_imgbtn_5;
	lv_obj_t *screen0_MENU_imgbtn_5_label;
	lv_obj_t *screen0_MENU_imgbtn_6;
	lv_obj_t *screen0_MENU_imgbtn_6_label;
	lv_obj_t *screen1_LEDs;
	lv_obj_t *screen1_LEDs_canvas_white;
	lv_obj_t *screen1_LEDs_left_btn;
	lv_obj_t *screen1_LEDs_left_btn_label;
	lv_obj_t *screen1_LEDs_left_label;
	lv_obj_t *screen1_LEDs_avlogoimg0;
	lv_obj_t *screen1_LEDs_right_btn;
	lv_obj_t *screen1_LEDs_right_btn_label;
	lv_obj_t *screen1_LEDs_right_label;
	lv_obj_t *screen1_LEDs_img_5oodt29s;
	lv_obj_t *screen1_LEDs_redbtn0;
	lv_obj_t *screen1_LEDs_redbtn0_label;
	lv_obj_t *screen1_LEDs_greenbtn0;
	lv_obj_t *screen1_LEDs_greenbtn0_label;
	lv_obj_t *screen1_LEDs_bluebtn0;
	lv_obj_t *screen1_LEDs_bluebtn0_label;
	lv_obj_t *screen1_LEDs_led_red_on;
	lv_obj_t *screen1_LEDs_led_red_off;
	lv_obj_t *screen1_LEDs_home_btn;
	lv_obj_t *screen1_LEDs_home_btn_label;
	lv_obj_t *screen1_LEDs_page_label;
	lv_obj_t *screen1_LEDs_led_green_on;
	lv_obj_t *screen1_LEDs_led_green_off;
	lv_obj_t *screen1_LEDs_led_blue_on;
	lv_obj_t *screen1_LEDs_led_blue_off;
	lv_obj_t *screen2_WIFI;
	lv_obj_t *screen2_WIFI_canvas_white;
	lv_obj_t *screen2_WIFI_left_btn;
	lv_obj_t *screen2_WIFI_left_btn_label;
	lv_obj_t *screen2_WIFI_left_label;
	lv_obj_t *screen2_WIFI_avlogoimg0;
	lv_obj_t *screen2_WIFI_right_btn;
	lv_obj_t *screen2_WIFI_right_btn_label;
	lv_obj_t *screen2_WIFI_right_label;
	lv_obj_t *screen2_WIFI_home_btn;
	lv_obj_t *screen2_WIFI_home_btn_label;
	lv_obj_t *screen2_WIFI_page_label;
	lv_obj_t *screen2_WIFI_ssid_list;
	lv_obj_t *screen2_WIFI_ssid_label;
	lv_obj_t *screen2_WIFI_ip_addr_label;
	lv_obj_t *screen2_WIFI_font_label;
	lv_obj_t *screen2_WIFI_ssid_refresh_imgbtn;
	lv_obj_t *screen2_WIFI_ssid_refresh_imgbtn_label;
	lv_obj_t *screen2_WIFI_ssid_scan_label;
	lv_obj_t *screen2_WIFI_eth_list;
	lv_obj_t *screen3_USB;
	lv_obj_t *screen3_USB_canvas_white;
	lv_obj_t *screen3_USB_left_btn;
	lv_obj_t *screen3_USB_left_btn_label;
	lv_obj_t *screen3_USB_left_label;
	lv_obj_t *screen3_USB_avlogoimg0;
	lv_obj_t *screen3_USB_right_btn;
	lv_obj_t *screen3_USB_right_btn_label;
	lv_obj_t *screen3_USB_right_label;
	lv_obj_t *screen3_USB_home_btn;
	lv_obj_t *screen3_USB_home_btn_label;
	lv_obj_t *screen3_USB_page_label;
	lv_obj_t *screen3_USB_usb_list;
	lv_obj_t *screen3_USB_usb_devices_label;
	lv_obj_t *screen3_USB_input_label;
	lv_obj_t *screen3_USB_i2c_nodes_label;
	lv_obj_t *screen3_USB_i2c_table;
	lv_obj_t *screen3_USB_input_area;
	lv_obj_t *screen3_USB_kbd_imgbtn;
	lv_obj_t *screen3_USB_kbd_imgbtn_label;
	lv_obj_t *screen3_USB_mouse_imgbtn;
	lv_obj_t *screen3_USB_mouse_imgbtn_label;
	lv_obj_t *screen3_USB_i2c_scan_imgbtn;
	lv_obj_t *screen3_USB_i2c_scan_imgbtn_label;
	lv_obj_t *screen3_USB_font_label;
	lv_obj_t *screen3_USB_i2c_ddlist;
	lv_obj_t *screen4_AV;
	lv_obj_t *screen4_AV_canvas_white;
	lv_obj_t *screen4_AV_left_btn;
	lv_obj_t *screen4_AV_left_btn_label;
	lv_obj_t *screen4_AV_left_label;
	lv_obj_t *screen4_AV_avlogoimg0;
	lv_obj_t *screen4_AV_right_btn;
	lv_obj_t *screen4_AV_right_btn_label;
	lv_obj_t *screen4_AV_right_label;
	lv_obj_t *screen4_AV_home_btn;
	lv_obj_t *screen4_AV_home_btn_label;
	lv_obj_t *screen4_AV_page_label;
	lv_obj_t *screen4_AV_camera_label;
	lv_obj_t *screen4_AV_camera_state_label;
	lv_obj_t *screen4_AV_playback_label;
	lv_obj_t *screen4_AV_mic_label;
	lv_obj_t *screen4_AV_mic1_cb;
	lv_obj_t *screen4_AV_mic2_cb;
	lv_obj_t *screen4_AV_mic3_cb;
	lv_obj_t *screen4_AV_mic4_cb;
	lv_obj_t *screen4_AV_mic_chart;
	lv_obj_t *screen5_SYSTEM;
	lv_obj_t *screen5_SYSTEM_canvas_white;
	lv_obj_t *screen5_SYSTEM_left_btn;
	lv_obj_t *screen5_SYSTEM_left_btn_label;
	lv_obj_t *screen5_SYSTEM_left_label;
	lv_obj_t *screen5_SYSTEM_avlogoimg0;
	lv_obj_t *screen5_SYSTEM_right_btn;
	lv_obj_t *screen5_SYSTEM_right_btn_label;
	lv_obj_t *screen5_SYSTEM_right_label;
	lv_obj_t *screen5_SYSTEM_home_btn;
	lv_obj_t *screen5_SYSTEM_home_btn_label;
	lv_obj_t *screen5_SYSTEM_page_label;
	lv_obj_t *screen5_SYSTEM_custom_chart;
	lv_obj_t *screen5_SYSTEM_custom_label;
	lv_obj_t *screen5_SYSTEM_custom_imgbtn;
	lv_obj_t *screen5_SYSTEM_custom_imgbtn_label;
	lv_obj_t *screen5_SYSTEM_instructions_label;
	lv_obj_t *screen5_SYSTEM_custom_value_label;
	lv_obj_t *screen6_HELP;
	lv_obj_t *screen6_HELP_canvas_white;
	lv_obj_t *screen6_HELP_left_btn;
	lv_obj_t *screen6_HELP_left_btn_label;
	lv_obj_t *screen6_HELP_left_label;
	lv_obj_t *screen6_HELP_avlogoimg0;
	lv_obj_t *screen6_HELP_right_btn;
	lv_obj_t *screen6_HELP_right_btn_label;
	lv_obj_t *screen6_HELP_right_label;
	lv_obj_t *screen6_HELP_home_btn;
	lv_obj_t *screen6_HELP_home_btn_label;
	lv_obj_t *screen6_HELP_page_label;
	lv_obj_t *screen6_HELP_demo_label;
	lv_obj_t *screen6_HELP_label_1;
	lv_obj_t *screen6_HELP_label_2;
	lv_obj_t *screen6_HELP_label_3;
	lv_obj_t *screen6_HELP_label_4;
	lv_obj_t *screen6_HELP_label_5;
	lv_obj_t *screen6_HELP_label_6;
	lv_obj_t *screen6_HELP_label_7;
	lv_obj_t *screen6_HELP_label_8;
	lv_obj_t *screen6_HELP_label_9;
	lv_obj_t *screen6_HELP_label_10;
	lv_obj_t *screen6_HELP_label_11;
	lv_obj_t *screen6_HELP_label_12;
	lv_obj_t *screen6_HELP_maaxboard_version_label;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen0_MENU(lv_ui *ui);
void setup_scr_screen1_LEDs(lv_ui *ui);
void setup_scr_screen2_WIFI(lv_ui *ui);
void setup_scr_screen3_USB(lv_ui *ui);
void setup_scr_screen4_AV(lv_ui *ui);
void setup_scr_screen5_SYSTEM(lv_ui *ui);
void setup_scr_screen6_HELP(lv_ui *ui);
LV_IMG_DECLARE(_led_blue_off_alpha_110x110);
LV_IMG_DECLARE(_button_alpha_320x106);
LV_IMG_DECLARE(_mouse_alpha_45x45);
LV_IMG_DECLARE(_led_red_on_alpha_110x110);
LV_IMG_DECLARE(_button_alpha_160x50);
LV_IMG_DECLARE(_eth_disconnect_40x40);
LV_IMG_DECLARE(_button_on_alpha_220x80);
LV_IMG_DECLARE(_home_icon_alpha_132x132);
LV_IMG_DECLARE(_led_green_off_alpha_110x110);
LV_IMG_DECLARE(_eth_connect_40x40);
LV_IMG_DECLARE(_led_green_on_alpha_110x110);
LV_IMG_DECLARE(_left_icon_alpha_132x132);
LV_IMG_DECLARE(_SBC_Help_Image_alpha_424x645);
LV_IMG_DECLARE(_button_alpha_220x80);
LV_IMG_DECLARE(_IoT_Smart_Asset_Monitoring_G_600ppi_alpha_500x500);
LV_IMG_DECLARE(_button_on_alpha_320x106);
LV_IMG_DECLARE(_button_on_alpha_160x50);
LV_IMG_DECLARE(_led_red_off_alpha_110x110);
LV_IMG_DECLARE(_avnet_logo2_alpha_130x130);
LV_IMG_DECLARE(_right_icon_alpha_132x132);
LV_IMG_DECLARE(_button_alpha_190x106);
LV_IMG_DECLARE(_button_on_alpha_190x106);
LV_IMG_DECLARE(_led_blue_on_alpha_110x110);

#ifdef __cplusplus
}
#endif
#endif
