/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen2_WIFI(lv_ui *ui){

	//Write codes screen2_WIFI
	ui->screen2_WIFI = lv_obj_create(NULL, NULL);

	//Write codes screen2_WIFI_canvas_white
	ui->screen2_WIFI_canvas_white = lv_canvas_create(ui->screen2_WIFI, NULL);

	//Write style LV_CANVAS_PART_MAIN for screen2_WIFI_canvas_white
	static lv_style_t style_screen2_WIFI_canvas_white_main;
	lv_style_init(&style_screen2_WIFI_canvas_white_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_canvas_white_main
	lv_style_set_image_recolor(&style_screen2_WIFI_canvas_white_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen2_WIFI_canvas_white_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_canvas_white, LV_CANVAS_PART_MAIN, &style_screen2_WIFI_canvas_white_main);
	lv_obj_set_pos(ui->screen2_WIFI_canvas_white, 0, 0);
	lv_obj_set_size(ui->screen2_WIFI_canvas_white, 720, 1280);
	lv_color_t *buf_screen2_WIFI_canvas_white = (lv_color_t*)lv_mem_alloc(720*1280*4);
	lv_canvas_set_buffer(ui->screen2_WIFI_canvas_white, buf_screen2_WIFI_canvas_white, 720, 1280, LV_IMG_CF_TRUE_COLOR);

	//Write codes screen2_WIFI_left_btn
	ui->screen2_WIFI_left_btn = lv_imgbtn_create(ui->screen2_WIFI, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen2_WIFI_left_btn
	static lv_style_t style_screen2_WIFI_left_btn_main;
	lv_style_init(&style_screen2_WIFI_left_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_left_btn_main
	lv_style_set_text_color(&style_screen2_WIFI_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen2_WIFI_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen2_WIFI_left_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen2_WIFI_left_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_left_btn, LV_IMGBTN_PART_MAIN, &style_screen2_WIFI_left_btn_main);
	lv_obj_set_pos(ui->screen2_WIFI_left_btn, 44, 1100);
	lv_obj_set_size(ui->screen2_WIFI_left_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen2_WIFI_left_btn,LV_BTN_STATE_RELEASED,&_left_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen2_WIFI_left_btn,LV_BTN_STATE_PRESSED,&_left_icon_alpha_132x132);

	//Write codes screen2_WIFI_left_label
	ui->screen2_WIFI_left_label = lv_label_create(ui->screen2_WIFI, NULL);
	lv_label_set_text(ui->screen2_WIFI_left_label, "LEDs");
	lv_label_set_long_mode(ui->screen2_WIFI_left_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen2_WIFI_left_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen2_WIFI_left_label
	static lv_style_t style_screen2_WIFI_left_label_main;
	lv_style_init(&style_screen2_WIFI_left_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_left_label_main
	lv_style_set_radius(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen2_WIFI_left_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen2_WIFI_left_label, LV_LABEL_PART_MAIN, &style_screen2_WIFI_left_label_main);
	lv_obj_set_pos(ui->screen2_WIFI_left_label, 20, 1200);
	lv_obj_set_size(ui->screen2_WIFI_left_label, 180, 0);

	//Write codes screen2_WIFI_avlogoimg0
	ui->screen2_WIFI_avlogoimg0 = lv_img_create(ui->screen2_WIFI, NULL);

	//Write style LV_IMG_PART_MAIN for screen2_WIFI_avlogoimg0
	static lv_style_t style_screen2_WIFI_avlogoimg0_main;
	lv_style_init(&style_screen2_WIFI_avlogoimg0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_avlogoimg0_main
	lv_style_set_image_recolor(&style_screen2_WIFI_avlogoimg0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen2_WIFI_avlogoimg0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen2_WIFI_avlogoimg0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_avlogoimg0, LV_IMG_PART_MAIN, &style_screen2_WIFI_avlogoimg0_main);
	lv_obj_set_pos(ui->screen2_WIFI_avlogoimg0, 0, 0);
	lv_obj_set_size(ui->screen2_WIFI_avlogoimg0, 130, 130);
	lv_obj_set_click(ui->screen2_WIFI_avlogoimg0, true);
	lv_img_set_src(ui->screen2_WIFI_avlogoimg0,&_avnet_logo2_alpha_130x130);
	lv_img_set_pivot(ui->screen2_WIFI_avlogoimg0, 0,0);
	lv_img_set_angle(ui->screen2_WIFI_avlogoimg0, 0);

	//Write codes screen2_WIFI_right_btn
	ui->screen2_WIFI_right_btn = lv_imgbtn_create(ui->screen2_WIFI, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen2_WIFI_right_btn
	static lv_style_t style_screen2_WIFI_right_btn_main;
	lv_style_init(&style_screen2_WIFI_right_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_right_btn_main
	lv_style_set_text_color(&style_screen2_WIFI_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen2_WIFI_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen2_WIFI_right_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen2_WIFI_right_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_right_btn, LV_IMGBTN_PART_MAIN, &style_screen2_WIFI_right_btn_main);
	lv_obj_set_pos(ui->screen2_WIFI_right_btn, 544, 1100);
	lv_obj_set_size(ui->screen2_WIFI_right_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen2_WIFI_right_btn,LV_BTN_STATE_RELEASED,&_right_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen2_WIFI_right_btn,LV_BTN_STATE_PRESSED,&_right_icon_alpha_132x132);

	//Write codes screen2_WIFI_right_label
	ui->screen2_WIFI_right_label = lv_label_create(ui->screen2_WIFI, NULL);
	lv_label_set_text(ui->screen2_WIFI_right_label, "USB");
	lv_label_set_long_mode(ui->screen2_WIFI_right_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen2_WIFI_right_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen2_WIFI_right_label
	static lv_style_t style_screen2_WIFI_right_label_main;
	lv_style_init(&style_screen2_WIFI_right_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_right_label_main
	lv_style_set_radius(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen2_WIFI_right_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen2_WIFI_right_label, LV_LABEL_PART_MAIN, &style_screen2_WIFI_right_label_main);
	lv_obj_set_pos(ui->screen2_WIFI_right_label, 520, 1200);
	lv_obj_set_size(ui->screen2_WIFI_right_label, 180, 0);

	//Write codes screen2_WIFI_home_btn
	ui->screen2_WIFI_home_btn = lv_imgbtn_create(ui->screen2_WIFI, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen2_WIFI_home_btn
	static lv_style_t style_screen2_WIFI_home_btn_main;
	lv_style_init(&style_screen2_WIFI_home_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_home_btn_main
	lv_style_set_text_color(&style_screen2_WIFI_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen2_WIFI_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen2_WIFI_home_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen2_WIFI_home_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_home_btn, LV_IMGBTN_PART_MAIN, &style_screen2_WIFI_home_btn_main);
	lv_obj_set_pos(ui->screen2_WIFI_home_btn, 294, 1100);
	lv_obj_set_size(ui->screen2_WIFI_home_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen2_WIFI_home_btn,LV_BTN_STATE_RELEASED,&_home_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen2_WIFI_home_btn,LV_BTN_STATE_PRESSED,&_home_icon_alpha_132x132);

	//Write codes screen2_WIFI_page_label
	ui->screen2_WIFI_page_label = lv_label_create(ui->screen2_WIFI, NULL);
	lv_label_set_text(ui->screen2_WIFI_page_label, "Wi-Fi & Ethernet");
	lv_label_set_long_mode(ui->screen2_WIFI_page_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen2_WIFI_page_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen2_WIFI_page_label
	static lv_style_t style_screen2_WIFI_page_label_main;
	lv_style_init(&style_screen2_WIFI_page_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_page_label_main
	lv_style_set_radius(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_48);
	lv_style_set_text_letter_space(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen2_WIFI_page_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen2_WIFI_page_label, LV_LABEL_PART_MAIN, &style_screen2_WIFI_page_label_main);
	lv_obj_set_pos(ui->screen2_WIFI_page_label, 180, 45);
	lv_obj_set_size(ui->screen2_WIFI_page_label, 500, 0);

	//Write codes screen2_WIFI_ssid_list
	ui->screen2_WIFI_ssid_list = lv_list_create(ui->screen2_WIFI, NULL);
	lv_list_set_edge_flash(ui->screen2_WIFI_ssid_list, true);

	//Write style LV_LIST_PART_BG for screen2_WIFI_ssid_list
	static lv_style_t style_screen2_WIFI_ssid_list_bg;
	lv_style_init(&style_screen2_WIFI_ssid_list_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_ssid_list_bg
	lv_style_set_radius(&style_screen2_WIFI_ssid_list_bg, LV_STATE_DEFAULT, 3);
	lv_style_set_border_color(&style_screen2_WIFI_ssid_list_bg, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen2_WIFI_ssid_list_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_screen2_WIFI_ssid_list_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen2_WIFI_ssid_list_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen2_WIFI_ssid_list_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen2_WIFI_ssid_list, LV_LIST_PART_BG, &style_screen2_WIFI_ssid_list_bg);

	//Write style LV_LIST_PART_SCROLLABLE for screen2_WIFI_ssid_list
	static lv_style_t style_screen2_WIFI_ssid_list_scrollable;
	lv_style_init(&style_screen2_WIFI_ssid_list_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_ssid_list_scrollable
	lv_style_set_radius(&style_screen2_WIFI_ssid_list_scrollable, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen2_WIFI_ssid_list_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_ssid_list_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_ssid_list_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_ssid_list_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_ssid_list, LV_LIST_PART_SCROLLABLE, &style_screen2_WIFI_ssid_list_scrollable);

	//Write style LV_BTN_PART_MAIN for screen2_WIFI_ssid_list
	static lv_style_t style_screen2_WIFI_ssid_list_main_child;
	lv_style_init(&style_screen2_WIFI_ssid_list_main_child);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_ssid_list_main_child
	lv_style_set_radius(&style_screen2_WIFI_ssid_list_main_child, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen2_WIFI_ssid_list_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_ssid_list_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_ssid_list_main_child, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_ssid_list_main_child, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_ssid_list_main_child, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_obj_set_pos(ui->screen2_WIFI_ssid_list, 0, 240);
	lv_obj_set_size(ui->screen2_WIFI_ssid_list, 720, 550);
	lv_obj_t *screen2_WIFI_ssid_list_btn;
	screen2_WIFI_ssid_list_btn = lv_list_add_btn(ui->screen2_WIFI_ssid_list, LV_SYMBOL_WIFI, "entry");
	lv_obj_add_style(screen2_WIFI_ssid_list_btn, LV_BTN_PART_MAIN, &style_screen2_WIFI_ssid_list_main_child);

	//Write codes screen2_WIFI_ssid_label
	ui->screen2_WIFI_ssid_label = lv_label_create(ui->screen2_WIFI, NULL);
	lv_label_set_text(ui->screen2_WIFI_ssid_label, "Wi-Fi SSIDs:");
	lv_label_set_long_mode(ui->screen2_WIFI_ssid_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen2_WIFI_ssid_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen2_WIFI_ssid_label
	static lv_style_t style_screen2_WIFI_ssid_label_main;
	lv_style_init(&style_screen2_WIFI_ssid_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_ssid_label_main
	lv_style_set_radius(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen2_WIFI_ssid_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen2_WIFI_ssid_label, LV_LABEL_PART_MAIN, &style_screen2_WIFI_ssid_label_main);
	lv_obj_set_pos(ui->screen2_WIFI_ssid_label, 30, 180);
	lv_obj_set_size(ui->screen2_WIFI_ssid_label, 400, 0);

	//Write codes screen2_WIFI_ip_addr_label
	ui->screen2_WIFI_ip_addr_label = lv_label_create(ui->screen2_WIFI, NULL);
	lv_label_set_text(ui->screen2_WIFI_ip_addr_label, "Ethernet Interfaces:");
	lv_label_set_long_mode(ui->screen2_WIFI_ip_addr_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen2_WIFI_ip_addr_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen2_WIFI_ip_addr_label
	static lv_style_t style_screen2_WIFI_ip_addr_label_main;
	lv_style_init(&style_screen2_WIFI_ip_addr_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_ip_addr_label_main
	lv_style_set_radius(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen2_WIFI_ip_addr_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen2_WIFI_ip_addr_label, LV_LABEL_PART_MAIN, &style_screen2_WIFI_ip_addr_label_main);
	lv_obj_set_pos(ui->screen2_WIFI_ip_addr_label, 30, 840);
	lv_obj_set_size(ui->screen2_WIFI_ip_addr_label, 500, 0);

	//Write codes screen2_WIFI_font_label
	ui->screen2_WIFI_font_label = lv_label_create(ui->screen2_WIFI, NULL);
	lv_label_set_text(ui->screen2_WIFI_font_label, "");
	lv_label_set_long_mode(ui->screen2_WIFI_font_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen2_WIFI_font_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen2_WIFI_font_label
	static lv_style_t style_screen2_WIFI_font_label_main;
	lv_style_init(&style_screen2_WIFI_font_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_font_label_main
	lv_style_set_radius(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_letter_space(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen2_WIFI_font_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen2_WIFI_font_label, LV_LABEL_PART_MAIN, &style_screen2_WIFI_font_label_main);
	lv_obj_set_pos(ui->screen2_WIFI_font_label, 20, 140);
	lv_obj_set_size(ui->screen2_WIFI_font_label, 200, 0);

	//Write codes screen2_WIFI_ssid_refresh_imgbtn
	ui->screen2_WIFI_ssid_refresh_imgbtn = lv_imgbtn_create(ui->screen2_WIFI, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen2_WIFI_ssid_refresh_imgbtn
	static lv_style_t style_screen2_WIFI_ssid_refresh_imgbtn_main;
	lv_style_init(&style_screen2_WIFI_ssid_refresh_imgbtn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_ssid_refresh_imgbtn_main
	lv_style_set_text_color(&style_screen2_WIFI_ssid_refresh_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen2_WIFI_ssid_refresh_imgbtn_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_24);
	lv_style_set_image_recolor(&style_screen2_WIFI_ssid_refresh_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen2_WIFI_ssid_refresh_imgbtn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen2_WIFI_ssid_refresh_imgbtn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_ssid_refresh_imgbtn, LV_IMGBTN_PART_MAIN, &style_screen2_WIFI_ssid_refresh_imgbtn_main);
	lv_obj_set_pos(ui->screen2_WIFI_ssid_refresh_imgbtn, 530, 176);
	lv_obj_set_size(ui->screen2_WIFI_ssid_refresh_imgbtn, 160, 50);
	lv_imgbtn_set_src(ui->screen2_WIFI_ssid_refresh_imgbtn,LV_BTN_STATE_RELEASED,&_button_alpha_160x50);
	lv_imgbtn_set_src(ui->screen2_WIFI_ssid_refresh_imgbtn,LV_BTN_STATE_PRESSED,&_button_on_alpha_160x50);
	ui->screen2_WIFI_ssid_refresh_imgbtn_label = lv_label_create(ui->screen2_WIFI_ssid_refresh_imgbtn, NULL);
	lv_label_set_text(ui->screen2_WIFI_ssid_refresh_imgbtn_label, "Wi-Fi Scan");

	//Write codes screen2_WIFI_ssid_scan_label
	ui->screen2_WIFI_ssid_scan_label = lv_label_create(ui->screen2_WIFI, NULL);
	lv_label_set_text(ui->screen2_WIFI_ssid_scan_label, "Scanning...");
	lv_label_set_long_mode(ui->screen2_WIFI_ssid_scan_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen2_WIFI_ssid_scan_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen2_WIFI_ssid_scan_label
	static lv_style_t style_screen2_WIFI_ssid_scan_label_main;
	lv_style_init(&style_screen2_WIFI_ssid_scan_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_ssid_scan_label_main
	lv_style_set_radius(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen2_WIFI_ssid_scan_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen2_WIFI_ssid_scan_label, LV_LABEL_PART_MAIN, &style_screen2_WIFI_ssid_scan_label_main);
	lv_obj_set_pos(ui->screen2_WIFI_ssid_scan_label, 210, 490);
	lv_obj_set_size(ui->screen2_WIFI_ssid_scan_label, 300, 0);

	//Write codes screen2_WIFI_eth_list
	ui->screen2_WIFI_eth_list = lv_list_create(ui->screen2_WIFI, NULL);
	lv_list_set_edge_flash(ui->screen2_WIFI_eth_list, true);

	//Write style LV_LIST_PART_BG for screen2_WIFI_eth_list
	static lv_style_t style_screen2_WIFI_eth_list_bg;
	lv_style_init(&style_screen2_WIFI_eth_list_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_eth_list_bg
	lv_style_set_radius(&style_screen2_WIFI_eth_list_bg, LV_STATE_DEFAULT, 3);
	lv_style_set_border_color(&style_screen2_WIFI_eth_list_bg, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen2_WIFI_eth_list_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_screen2_WIFI_eth_list_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen2_WIFI_eth_list_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen2_WIFI_eth_list_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen2_WIFI_eth_list, LV_LIST_PART_BG, &style_screen2_WIFI_eth_list_bg);

	//Write style LV_LIST_PART_SCROLLABLE for screen2_WIFI_eth_list
	static lv_style_t style_screen2_WIFI_eth_list_scrollable;
	lv_style_init(&style_screen2_WIFI_eth_list_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_eth_list_scrollable
	lv_style_set_radius(&style_screen2_WIFI_eth_list_scrollable, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen2_WIFI_eth_list_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_eth_list_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_eth_list_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_eth_list_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen2_WIFI_eth_list, LV_LIST_PART_SCROLLABLE, &style_screen2_WIFI_eth_list_scrollable);

	//Write style LV_BTN_PART_MAIN for screen2_WIFI_eth_list
	static lv_style_t style_screen2_WIFI_eth_list_main_child;
	lv_style_init(&style_screen2_WIFI_eth_list_main_child);

	//Write style state: LV_STATE_DEFAULT for style_screen2_WIFI_eth_list_main_child
	lv_style_set_radius(&style_screen2_WIFI_eth_list_main_child, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen2_WIFI_eth_list_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen2_WIFI_eth_list_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen2_WIFI_eth_list_main_child, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen2_WIFI_eth_list_main_child, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen2_WIFI_eth_list_main_child, LV_STATE_DEFAULT, lv_color_make(0x0d, 0x30, 0x55));
	lv_obj_set_pos(ui->screen2_WIFI_eth_list, 0, 903);
	lv_obj_set_size(ui->screen2_WIFI_eth_list, 720, 180);
	lv_obj_t *screen2_WIFI_eth_list_btn;
	screen2_WIFI_eth_list_btn = lv_list_add_btn(ui->screen2_WIFI_eth_list, &_eth_connect_40x40, "Eth 100Mb : Connected, ip:192.168.5.100 sub:255.255.255.0 gw:192.168.5.1");
	lv_obj_add_style(screen2_WIFI_eth_list_btn, LV_BTN_PART_MAIN, &style_screen2_WIFI_eth_list_main_child);
	screen2_WIFI_eth_list_btn = lv_list_add_btn(ui->screen2_WIFI_eth_list, &_eth_disconnect_40x40, "Eth 1Gb : Disconnected");
	lv_obj_add_style(screen2_WIFI_eth_list_btn, LV_BTN_PART_MAIN, &style_screen2_WIFI_eth_list_main_child);

	//Init events for screen
	events_init_screen2_WIFI(ui);
}
