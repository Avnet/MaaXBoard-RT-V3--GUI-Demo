/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen1_LEDs(lv_ui *ui){

	//Write codes screen1_LEDs
	ui->screen1_LEDs = lv_obj_create(NULL, NULL);

	//Write codes screen1_LEDs_canvas_white
	ui->screen1_LEDs_canvas_white = lv_canvas_create(ui->screen1_LEDs, NULL);

	//Write style LV_CANVAS_PART_MAIN for screen1_LEDs_canvas_white
	static lv_style_t style_screen1_LEDs_canvas_white_main;
	lv_style_init(&style_screen1_LEDs_canvas_white_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_canvas_white_main
	lv_style_set_image_recolor(&style_screen1_LEDs_canvas_white_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_canvas_white_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_canvas_white, LV_CANVAS_PART_MAIN, &style_screen1_LEDs_canvas_white_main);
	lv_obj_set_pos(ui->screen1_LEDs_canvas_white, 0, 0);
	lv_obj_set_size(ui->screen1_LEDs_canvas_white, 720, 1280);
	lv_color_t *buf_screen1_LEDs_canvas_white = (lv_color_t*)lv_mem_alloc(720*1280*4);
	lv_canvas_set_buffer(ui->screen1_LEDs_canvas_white, buf_screen1_LEDs_canvas_white, 720, 1280, LV_IMG_CF_TRUE_COLOR);

	//Write codes screen1_LEDs_left_btn
	ui->screen1_LEDs_left_btn = lv_imgbtn_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen1_LEDs_left_btn
	static lv_style_t style_screen1_LEDs_left_btn_main;
	lv_style_init(&style_screen1_LEDs_left_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_left_btn_main
	lv_style_set_text_color(&style_screen1_LEDs_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen1_LEDs_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_left_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_left_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_left_btn, LV_IMGBTN_PART_MAIN, &style_screen1_LEDs_left_btn_main);
	lv_obj_set_pos(ui->screen1_LEDs_left_btn, 44, 1100);
	lv_obj_set_size(ui->screen1_LEDs_left_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen1_LEDs_left_btn,LV_BTN_STATE_RELEASED,&_left_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen1_LEDs_left_btn,LV_BTN_STATE_PRESSED,&_left_icon_alpha_132x132);

	//Write codes screen1_LEDs_left_label
	ui->screen1_LEDs_left_label = lv_label_create(ui->screen1_LEDs, NULL);
	lv_label_set_text(ui->screen1_LEDs_left_label, "MENU");
	lv_label_set_long_mode(ui->screen1_LEDs_left_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen1_LEDs_left_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen1_LEDs_left_label
	static lv_style_t style_screen1_LEDs_left_label_main;
	lv_style_init(&style_screen1_LEDs_left_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_left_label_main
	lv_style_set_radius(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen1_LEDs_left_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen1_LEDs_left_label, LV_LABEL_PART_MAIN, &style_screen1_LEDs_left_label_main);
	lv_obj_set_pos(ui->screen1_LEDs_left_label, 20, 1200);
	lv_obj_set_size(ui->screen1_LEDs_left_label, 180, 0);

	//Write codes screen1_LEDs_avlogoimg0
	ui->screen1_LEDs_avlogoimg0 = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_avlogoimg0
	static lv_style_t style_screen1_LEDs_avlogoimg0_main;
	lv_style_init(&style_screen1_LEDs_avlogoimg0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_avlogoimg0_main
	lv_style_set_image_recolor(&style_screen1_LEDs_avlogoimg0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_avlogoimg0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_avlogoimg0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_avlogoimg0, LV_IMG_PART_MAIN, &style_screen1_LEDs_avlogoimg0_main);
	lv_obj_set_pos(ui->screen1_LEDs_avlogoimg0, 0, 0);
	lv_obj_set_size(ui->screen1_LEDs_avlogoimg0, 130, 130);
	lv_obj_set_click(ui->screen1_LEDs_avlogoimg0, true);
	lv_img_set_src(ui->screen1_LEDs_avlogoimg0,&_avnet_logo2_alpha_130x130);
	lv_img_set_pivot(ui->screen1_LEDs_avlogoimg0, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_avlogoimg0, 0);

	//Write codes screen1_LEDs_right_btn
	ui->screen1_LEDs_right_btn = lv_imgbtn_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen1_LEDs_right_btn
	static lv_style_t style_screen1_LEDs_right_btn_main;
	lv_style_init(&style_screen1_LEDs_right_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_right_btn_main
	lv_style_set_text_color(&style_screen1_LEDs_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen1_LEDs_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_right_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_right_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_right_btn, LV_IMGBTN_PART_MAIN, &style_screen1_LEDs_right_btn_main);
	lv_obj_set_pos(ui->screen1_LEDs_right_btn, 544, 1100);
	lv_obj_set_size(ui->screen1_LEDs_right_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen1_LEDs_right_btn,LV_BTN_STATE_RELEASED,&_right_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen1_LEDs_right_btn,LV_BTN_STATE_PRESSED,&_right_icon_alpha_132x132);

	//Write codes screen1_LEDs_right_label
	ui->screen1_LEDs_right_label = lv_label_create(ui->screen1_LEDs, NULL);
	lv_label_set_text(ui->screen1_LEDs_right_label, "Wi-Fi");
	lv_label_set_long_mode(ui->screen1_LEDs_right_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen1_LEDs_right_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen1_LEDs_right_label
	static lv_style_t style_screen1_LEDs_right_label_main;
	lv_style_init(&style_screen1_LEDs_right_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_right_label_main
	lv_style_set_radius(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen1_LEDs_right_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen1_LEDs_right_label, LV_LABEL_PART_MAIN, &style_screen1_LEDs_right_label_main);
	lv_obj_set_pos(ui->screen1_LEDs_right_label, 520, 1200);
	lv_obj_set_size(ui->screen1_LEDs_right_label, 180, 0);

	//Write codes screen1_LEDs_img_5oodt29s
	ui->screen1_LEDs_img_5oodt29s = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_img_5oodt29s
	static lv_style_t style_screen1_LEDs_img_5oodt29s_main;
	lv_style_init(&style_screen1_LEDs_img_5oodt29s_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_img_5oodt29s_main
	lv_style_set_image_recolor(&style_screen1_LEDs_img_5oodt29s_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_img_5oodt29s_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_img_5oodt29s_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_img_5oodt29s, LV_IMG_PART_MAIN, &style_screen1_LEDs_img_5oodt29s_main);
	lv_obj_set_pos(ui->screen1_LEDs_img_5oodt29s, 110, 200);
	lv_obj_set_size(ui->screen1_LEDs_img_5oodt29s, 500, 500);
	lv_obj_set_click(ui->screen1_LEDs_img_5oodt29s, true);
	lv_img_set_src(ui->screen1_LEDs_img_5oodt29s,&_IoT_Smart_Asset_Monitoring_G_600ppi_alpha_500x500);
	lv_img_set_pivot(ui->screen1_LEDs_img_5oodt29s, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_img_5oodt29s, 0);

	//Write codes screen1_LEDs_redbtn0
	ui->screen1_LEDs_redbtn0 = lv_imgbtn_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen1_LEDs_redbtn0
	static lv_style_t style_screen1_LEDs_redbtn0_main;
	lv_style_init(&style_screen1_LEDs_redbtn0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_redbtn0_main
	lv_style_set_text_color(&style_screen1_LEDs_redbtn0_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen1_LEDs_redbtn0_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen1_LEDs_redbtn0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_redbtn0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_redbtn0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_redbtn0, LV_IMGBTN_PART_MAIN, &style_screen1_LEDs_redbtn0_main);
	lv_obj_set_pos(ui->screen1_LEDs_redbtn0, 20, 900);
	lv_obj_set_size(ui->screen1_LEDs_redbtn0, 190, 106);
	lv_imgbtn_set_src(ui->screen1_LEDs_redbtn0,LV_BTN_STATE_RELEASED,&_button_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_redbtn0,LV_BTN_STATE_PRESSED,&_button_on_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_redbtn0,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_redbtn0,LV_BTN_STATE_CHECKED_PRESSED,&_button_alpha_190x106);
	lv_imgbtn_set_checkable(ui->screen1_LEDs_redbtn0, true);
	ui->screen1_LEDs_redbtn0_label = lv_label_create(ui->screen1_LEDs_redbtn0, NULL);
	lv_label_set_text(ui->screen1_LEDs_redbtn0_label, "LED 1");

	//Write codes screen1_LEDs_greenbtn0
	ui->screen1_LEDs_greenbtn0 = lv_imgbtn_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen1_LEDs_greenbtn0
	static lv_style_t style_screen1_LEDs_greenbtn0_main;
	lv_style_init(&style_screen1_LEDs_greenbtn0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_greenbtn0_main
	lv_style_set_text_color(&style_screen1_LEDs_greenbtn0_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen1_LEDs_greenbtn0_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen1_LEDs_greenbtn0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_greenbtn0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_greenbtn0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_greenbtn0, LV_IMGBTN_PART_MAIN, &style_screen1_LEDs_greenbtn0_main);
	lv_obj_set_pos(ui->screen1_LEDs_greenbtn0, 265, 900);
	lv_obj_set_size(ui->screen1_LEDs_greenbtn0, 190, 106);
	lv_imgbtn_set_src(ui->screen1_LEDs_greenbtn0,LV_BTN_STATE_RELEASED,&_button_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_greenbtn0,LV_BTN_STATE_PRESSED,&_button_on_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_greenbtn0,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_greenbtn0,LV_BTN_STATE_CHECKED_PRESSED,&_button_alpha_190x106);
	lv_imgbtn_set_checkable(ui->screen1_LEDs_greenbtn0, true);
	ui->screen1_LEDs_greenbtn0_label = lv_label_create(ui->screen1_LEDs_greenbtn0, NULL);
	lv_label_set_text(ui->screen1_LEDs_greenbtn0_label, "LED 2");

	//Write codes screen1_LEDs_bluebtn0
	ui->screen1_LEDs_bluebtn0 = lv_imgbtn_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen1_LEDs_bluebtn0
	static lv_style_t style_screen1_LEDs_bluebtn0_main;
	lv_style_init(&style_screen1_LEDs_bluebtn0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_bluebtn0_main
	lv_style_set_text_color(&style_screen1_LEDs_bluebtn0_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen1_LEDs_bluebtn0_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen1_LEDs_bluebtn0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_bluebtn0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_bluebtn0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_bluebtn0, LV_IMGBTN_PART_MAIN, &style_screen1_LEDs_bluebtn0_main);
	lv_obj_set_pos(ui->screen1_LEDs_bluebtn0, 510, 900);
	lv_obj_set_size(ui->screen1_LEDs_bluebtn0, 190, 106);
	lv_imgbtn_set_src(ui->screen1_LEDs_bluebtn0,LV_BTN_STATE_RELEASED,&_button_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_bluebtn0,LV_BTN_STATE_PRESSED,&_button_on_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_bluebtn0,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_190x106);
	lv_imgbtn_set_src(ui->screen1_LEDs_bluebtn0,LV_BTN_STATE_CHECKED_PRESSED,&_button_alpha_190x106);
	lv_imgbtn_set_checkable(ui->screen1_LEDs_bluebtn0, true);
	ui->screen1_LEDs_bluebtn0_label = lv_label_create(ui->screen1_LEDs_bluebtn0, NULL);
	lv_label_set_text(ui->screen1_LEDs_bluebtn0_label, "LED 3");

	//Write codes screen1_LEDs_led_red_on
	ui->screen1_LEDs_led_red_on = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_led_red_on
	static lv_style_t style_screen1_LEDs_led_red_on_main;
	lv_style_init(&style_screen1_LEDs_led_red_on_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_led_red_on_main
	lv_style_set_image_recolor(&style_screen1_LEDs_led_red_on_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_led_red_on_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_led_red_on_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_led_red_on, LV_IMG_PART_MAIN, &style_screen1_LEDs_led_red_on_main);
	lv_obj_set_pos(ui->screen1_LEDs_led_red_on, 60, 760);
	lv_obj_set_size(ui->screen1_LEDs_led_red_on, 110, 110);
	lv_obj_set_click(ui->screen1_LEDs_led_red_on, true);
	lv_img_set_src(ui->screen1_LEDs_led_red_on,&_led_red_on_alpha_110x110);
	lv_img_set_pivot(ui->screen1_LEDs_led_red_on, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_led_red_on, 0);

	//Write codes screen1_LEDs_led_red_off
	ui->screen1_LEDs_led_red_off = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_led_red_off
	static lv_style_t style_screen1_LEDs_led_red_off_main;
	lv_style_init(&style_screen1_LEDs_led_red_off_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_led_red_off_main
	lv_style_set_image_recolor(&style_screen1_LEDs_led_red_off_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_led_red_off_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_led_red_off_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_led_red_off, LV_IMG_PART_MAIN, &style_screen1_LEDs_led_red_off_main);
	lv_obj_set_pos(ui->screen1_LEDs_led_red_off, 60, 760);
	lv_obj_set_size(ui->screen1_LEDs_led_red_off, 110, 110);
	lv_obj_set_click(ui->screen1_LEDs_led_red_off, true);
	lv_img_set_src(ui->screen1_LEDs_led_red_off,&_led_red_off_alpha_110x110);
	lv_img_set_pivot(ui->screen1_LEDs_led_red_off, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_led_red_off, 0);

	//Write codes screen1_LEDs_home_btn
	ui->screen1_LEDs_home_btn = lv_imgbtn_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen1_LEDs_home_btn
	static lv_style_t style_screen1_LEDs_home_btn_main;
	lv_style_init(&style_screen1_LEDs_home_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_home_btn_main
	lv_style_set_text_color(&style_screen1_LEDs_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen1_LEDs_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_home_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_home_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_home_btn, LV_IMGBTN_PART_MAIN, &style_screen1_LEDs_home_btn_main);
	lv_obj_set_pos(ui->screen1_LEDs_home_btn, 294, 1100);
	lv_obj_set_size(ui->screen1_LEDs_home_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen1_LEDs_home_btn,LV_BTN_STATE_RELEASED,&_home_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen1_LEDs_home_btn,LV_BTN_STATE_PRESSED,&_home_icon_alpha_132x132);

	//Write codes screen1_LEDs_page_label
	ui->screen1_LEDs_page_label = lv_label_create(ui->screen1_LEDs, NULL);
	lv_label_set_text(ui->screen1_LEDs_page_label, "LED Control");
	lv_label_set_long_mode(ui->screen1_LEDs_page_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen1_LEDs_page_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen1_LEDs_page_label
	static lv_style_t style_screen1_LEDs_page_label_main;
	lv_style_init(&style_screen1_LEDs_page_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_page_label_main
	lv_style_set_radius(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_48);
	lv_style_set_text_letter_space(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen1_LEDs_page_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen1_LEDs_page_label, LV_LABEL_PART_MAIN, &style_screen1_LEDs_page_label_main);
	lv_obj_set_pos(ui->screen1_LEDs_page_label, 180, 45);
	lv_obj_set_size(ui->screen1_LEDs_page_label, 500, 0);

	//Write codes screen1_LEDs_led_green_on
	ui->screen1_LEDs_led_green_on = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_led_green_on
	static lv_style_t style_screen1_LEDs_led_green_on_main;
	lv_style_init(&style_screen1_LEDs_led_green_on_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_led_green_on_main
	lv_style_set_image_recolor(&style_screen1_LEDs_led_green_on_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_led_green_on_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_led_green_on_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_led_green_on, LV_IMG_PART_MAIN, &style_screen1_LEDs_led_green_on_main);
	lv_obj_set_pos(ui->screen1_LEDs_led_green_on, 305, 760);
	lv_obj_set_size(ui->screen1_LEDs_led_green_on, 110, 110);
	lv_obj_set_click(ui->screen1_LEDs_led_green_on, true);
	lv_img_set_src(ui->screen1_LEDs_led_green_on,&_led_green_on_alpha_110x110);
	lv_img_set_pivot(ui->screen1_LEDs_led_green_on, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_led_green_on, 0);

	//Write codes screen1_LEDs_led_green_off
	ui->screen1_LEDs_led_green_off = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_led_green_off
	static lv_style_t style_screen1_LEDs_led_green_off_main;
	lv_style_init(&style_screen1_LEDs_led_green_off_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_led_green_off_main
	lv_style_set_image_recolor(&style_screen1_LEDs_led_green_off_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_led_green_off_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_led_green_off_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_led_green_off, LV_IMG_PART_MAIN, &style_screen1_LEDs_led_green_off_main);
	lv_obj_set_pos(ui->screen1_LEDs_led_green_off, 305, 760);
	lv_obj_set_size(ui->screen1_LEDs_led_green_off, 110, 110);
	lv_obj_set_click(ui->screen1_LEDs_led_green_off, true);
	lv_img_set_src(ui->screen1_LEDs_led_green_off,&_led_green_off_alpha_110x110);
	lv_img_set_pivot(ui->screen1_LEDs_led_green_off, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_led_green_off, 0);

	//Write codes screen1_LEDs_led_blue_on
	ui->screen1_LEDs_led_blue_on = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_led_blue_on
	static lv_style_t style_screen1_LEDs_led_blue_on_main;
	lv_style_init(&style_screen1_LEDs_led_blue_on_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_led_blue_on_main
	lv_style_set_image_recolor(&style_screen1_LEDs_led_blue_on_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_led_blue_on_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_led_blue_on_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_led_blue_on, LV_IMG_PART_MAIN, &style_screen1_LEDs_led_blue_on_main);
	lv_obj_set_pos(ui->screen1_LEDs_led_blue_on, 550, 760);
	lv_obj_set_size(ui->screen1_LEDs_led_blue_on, 110, 110);
	lv_obj_set_click(ui->screen1_LEDs_led_blue_on, true);
	lv_img_set_src(ui->screen1_LEDs_led_blue_on,&_led_blue_on_alpha_110x110);
	lv_img_set_pivot(ui->screen1_LEDs_led_blue_on, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_led_blue_on, 0);

	//Write codes screen1_LEDs_led_blue_off
	ui->screen1_LEDs_led_blue_off = lv_img_create(ui->screen1_LEDs, NULL);

	//Write style LV_IMG_PART_MAIN for screen1_LEDs_led_blue_off
	static lv_style_t style_screen1_LEDs_led_blue_off_main;
	lv_style_init(&style_screen1_LEDs_led_blue_off_main);

	//Write style state: LV_STATE_DEFAULT for style_screen1_LEDs_led_blue_off_main
	lv_style_set_image_recolor(&style_screen1_LEDs_led_blue_off_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen1_LEDs_led_blue_off_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen1_LEDs_led_blue_off_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen1_LEDs_led_blue_off, LV_IMG_PART_MAIN, &style_screen1_LEDs_led_blue_off_main);
	lv_obj_set_pos(ui->screen1_LEDs_led_blue_off, 550, 760);
	lv_obj_set_size(ui->screen1_LEDs_led_blue_off, 110, 110);
	lv_obj_set_click(ui->screen1_LEDs_led_blue_off, true);
	lv_img_set_src(ui->screen1_LEDs_led_blue_off,&_led_blue_off_alpha_110x110);
	lv_img_set_pivot(ui->screen1_LEDs_led_blue_off, 0,0);
	lv_img_set_angle(ui->screen1_LEDs_led_blue_off, 0);

	//Init events for screen
	events_init_screen1_LEDs(ui);
}
