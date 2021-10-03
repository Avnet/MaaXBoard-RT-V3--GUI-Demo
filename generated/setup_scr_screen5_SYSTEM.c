/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen5_SYSTEM(lv_ui *ui){

	//Write codes screen5_SYSTEM
	ui->screen5_SYSTEM = lv_obj_create(NULL, NULL);

	//Write codes screen5_SYSTEM_canvas_white
	ui->screen5_SYSTEM_canvas_white = lv_canvas_create(ui->screen5_SYSTEM, NULL);

	//Write style LV_CANVAS_PART_MAIN for screen5_SYSTEM_canvas_white
	static lv_style_t style_screen5_SYSTEM_canvas_white_main;
	lv_style_init(&style_screen5_SYSTEM_canvas_white_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_canvas_white_main
	lv_style_set_image_recolor(&style_screen5_SYSTEM_canvas_white_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen5_SYSTEM_canvas_white_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen5_SYSTEM_canvas_white, LV_CANVAS_PART_MAIN, &style_screen5_SYSTEM_canvas_white_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_canvas_white, 0, 0);
	lv_obj_set_size(ui->screen5_SYSTEM_canvas_white, 720, 1280);
	lv_color_t *buf_screen5_SYSTEM_canvas_white = (lv_color_t*)lv_mem_alloc(720*1280*4);
	lv_canvas_set_buffer(ui->screen5_SYSTEM_canvas_white, buf_screen5_SYSTEM_canvas_white, 720, 1280, LV_IMG_CF_TRUE_COLOR);

	//Write codes screen5_SYSTEM_left_btn
	ui->screen5_SYSTEM_left_btn = lv_imgbtn_create(ui->screen5_SYSTEM, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen5_SYSTEM_left_btn
	static lv_style_t style_screen5_SYSTEM_left_btn_main;
	lv_style_init(&style_screen5_SYSTEM_left_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_left_btn_main
	lv_style_set_text_color(&style_screen5_SYSTEM_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen5_SYSTEM_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen5_SYSTEM_left_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen5_SYSTEM_left_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen5_SYSTEM_left_btn, LV_IMGBTN_PART_MAIN, &style_screen5_SYSTEM_left_btn_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_left_btn, 44, 1100);
	lv_obj_set_size(ui->screen5_SYSTEM_left_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_left_btn,LV_BTN_STATE_RELEASED,&_left_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_left_btn,LV_BTN_STATE_PRESSED,&_left_icon_alpha_132x132);

	//Write codes screen5_SYSTEM_left_label
	ui->screen5_SYSTEM_left_label = lv_label_create(ui->screen5_SYSTEM, NULL);
	lv_label_set_text(ui->screen5_SYSTEM_left_label, "A & V");
	lv_label_set_long_mode(ui->screen5_SYSTEM_left_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen5_SYSTEM_left_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen5_SYSTEM_left_label
	static lv_style_t style_screen5_SYSTEM_left_label_main;
	lv_style_init(&style_screen5_SYSTEM_left_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_left_label_main
	lv_style_set_radius(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen5_SYSTEM_left_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen5_SYSTEM_left_label, LV_LABEL_PART_MAIN, &style_screen5_SYSTEM_left_label_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_left_label, 20, 1200);
	lv_obj_set_size(ui->screen5_SYSTEM_left_label, 180, 0);

	//Write codes screen5_SYSTEM_avlogoimg0
	ui->screen5_SYSTEM_avlogoimg0 = lv_img_create(ui->screen5_SYSTEM, NULL);

	//Write style LV_IMG_PART_MAIN for screen5_SYSTEM_avlogoimg0
	static lv_style_t style_screen5_SYSTEM_avlogoimg0_main;
	lv_style_init(&style_screen5_SYSTEM_avlogoimg0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_avlogoimg0_main
	lv_style_set_image_recolor(&style_screen5_SYSTEM_avlogoimg0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen5_SYSTEM_avlogoimg0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen5_SYSTEM_avlogoimg0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen5_SYSTEM_avlogoimg0, LV_IMG_PART_MAIN, &style_screen5_SYSTEM_avlogoimg0_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_avlogoimg0, 0, 0);
	lv_obj_set_size(ui->screen5_SYSTEM_avlogoimg0, 130, 130);
	lv_obj_set_click(ui->screen5_SYSTEM_avlogoimg0, true);
	lv_img_set_src(ui->screen5_SYSTEM_avlogoimg0,&_avnet_logo2_alpha_130x130);
	lv_img_set_pivot(ui->screen5_SYSTEM_avlogoimg0, 0,0);
	lv_img_set_angle(ui->screen5_SYSTEM_avlogoimg0, 0);

	//Write codes screen5_SYSTEM_right_btn
	ui->screen5_SYSTEM_right_btn = lv_imgbtn_create(ui->screen5_SYSTEM, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen5_SYSTEM_right_btn
	static lv_style_t style_screen5_SYSTEM_right_btn_main;
	lv_style_init(&style_screen5_SYSTEM_right_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_right_btn_main
	lv_style_set_text_color(&style_screen5_SYSTEM_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen5_SYSTEM_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen5_SYSTEM_right_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen5_SYSTEM_right_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen5_SYSTEM_right_btn, LV_IMGBTN_PART_MAIN, &style_screen5_SYSTEM_right_btn_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_right_btn, 544, 1100);
	lv_obj_set_size(ui->screen5_SYSTEM_right_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_right_btn,LV_BTN_STATE_RELEASED,&_right_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_right_btn,LV_BTN_STATE_PRESSED,&_right_icon_alpha_132x132);

	//Write codes screen5_SYSTEM_right_label
	ui->screen5_SYSTEM_right_label = lv_label_create(ui->screen5_SYSTEM, NULL);
	lv_label_set_text(ui->screen5_SYSTEM_right_label, "HELP");
	lv_label_set_long_mode(ui->screen5_SYSTEM_right_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen5_SYSTEM_right_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen5_SYSTEM_right_label
	static lv_style_t style_screen5_SYSTEM_right_label_main;
	lv_style_init(&style_screen5_SYSTEM_right_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_right_label_main
	lv_style_set_radius(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen5_SYSTEM_right_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen5_SYSTEM_right_label, LV_LABEL_PART_MAIN, &style_screen5_SYSTEM_right_label_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_right_label, 520, 1200);
	lv_obj_set_size(ui->screen5_SYSTEM_right_label, 180, 0);

	//Write codes screen5_SYSTEM_home_btn
	ui->screen5_SYSTEM_home_btn = lv_imgbtn_create(ui->screen5_SYSTEM, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen5_SYSTEM_home_btn
	static lv_style_t style_screen5_SYSTEM_home_btn_main;
	lv_style_init(&style_screen5_SYSTEM_home_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_home_btn_main
	lv_style_set_text_color(&style_screen5_SYSTEM_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen5_SYSTEM_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen5_SYSTEM_home_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen5_SYSTEM_home_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen5_SYSTEM_home_btn, LV_IMGBTN_PART_MAIN, &style_screen5_SYSTEM_home_btn_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_home_btn, 294, 1100);
	lv_obj_set_size(ui->screen5_SYSTEM_home_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_home_btn,LV_BTN_STATE_RELEASED,&_home_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_home_btn,LV_BTN_STATE_PRESSED,&_home_icon_alpha_132x132);

	//Write codes screen5_SYSTEM_page_label
	ui->screen5_SYSTEM_page_label = lv_label_create(ui->screen5_SYSTEM, NULL);
	lv_label_set_text(ui->screen5_SYSTEM_page_label, "Custom Functions");
	lv_label_set_long_mode(ui->screen5_SYSTEM_page_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen5_SYSTEM_page_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen5_SYSTEM_page_label
	static lv_style_t style_screen5_SYSTEM_page_label_main;
	lv_style_init(&style_screen5_SYSTEM_page_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_page_label_main
	lv_style_set_radius(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_48);
	lv_style_set_text_letter_space(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen5_SYSTEM_page_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen5_SYSTEM_page_label, LV_LABEL_PART_MAIN, &style_screen5_SYSTEM_page_label_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_page_label, 180, 45);
	lv_obj_set_size(ui->screen5_SYSTEM_page_label, 500, 0);

	//Write codes screen5_SYSTEM_custom_chart
	ui->screen5_SYSTEM_custom_chart = lv_chart_create(ui->screen5_SYSTEM, NULL);

	//Write style LV_CHART_PART_BG for screen5_SYSTEM_custom_chart
	static lv_style_t style_screen5_SYSTEM_custom_chart_bg;
	lv_style_init(&style_screen5_SYSTEM_custom_chart_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_custom_chart_bg
	lv_style_set_bg_color(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_screen5_SYSTEM_custom_chart_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen5_SYSTEM_custom_chart, LV_CHART_PART_BG, &style_screen5_SYSTEM_custom_chart_bg);

	//Write style LV_CHART_PART_SERIES_BG for screen5_SYSTEM_custom_chart
	static lv_style_t style_screen5_SYSTEM_custom_chart_series_bg;
	lv_style_init(&style_screen5_SYSTEM_custom_chart_series_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_custom_chart_series_bg
	lv_style_set_line_color(&style_screen5_SYSTEM_custom_chart_series_bg, LV_STATE_DEFAULT, lv_color_make(0xe8, 0xe8, 0xe8));
	lv_style_set_line_width(&style_screen5_SYSTEM_custom_chart_series_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_line_opa(&style_screen5_SYSTEM_custom_chart_series_bg, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen5_SYSTEM_custom_chart, LV_CHART_PART_SERIES_BG, &style_screen5_SYSTEM_custom_chart_series_bg);
	lv_obj_set_pos(ui->screen5_SYSTEM_custom_chart, 30, 244);
	lv_obj_set_size(ui->screen5_SYSTEM_custom_chart, 660, 350);
	lv_chart_set_type(ui->screen5_SYSTEM_custom_chart,LV_CHART_TYPE_LINE);
	lv_chart_set_range(ui->screen5_SYSTEM_custom_chart,0,100);
	lv_chart_set_div_line_count(ui->screen5_SYSTEM_custom_chart, 3, 5);

	//Write codes screen5_SYSTEM_custom_label
	ui->screen5_SYSTEM_custom_label = lv_label_create(ui->screen5_SYSTEM, NULL);
	lv_label_set_text(ui->screen5_SYSTEM_custom_label, "Wi-Fi Signal Strength:");
	lv_label_set_long_mode(ui->screen5_SYSTEM_custom_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen5_SYSTEM_custom_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen5_SYSTEM_custom_label
	static lv_style_t style_screen5_SYSTEM_custom_label_main;
	lv_style_init(&style_screen5_SYSTEM_custom_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_custom_label_main
	lv_style_set_radius(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen5_SYSTEM_custom_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen5_SYSTEM_custom_label, LV_LABEL_PART_MAIN, &style_screen5_SYSTEM_custom_label_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_custom_label, 32, 180);
	lv_obj_set_size(ui->screen5_SYSTEM_custom_label, 450, 0);

	//Write codes screen5_SYSTEM_custom_imgbtn
	ui->screen5_SYSTEM_custom_imgbtn = lv_imgbtn_create(ui->screen5_SYSTEM, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen5_SYSTEM_custom_imgbtn
	static lv_style_t style_screen5_SYSTEM_custom_imgbtn_main;
	lv_style_init(&style_screen5_SYSTEM_custom_imgbtn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_custom_imgbtn_main
	lv_style_set_text_color(&style_screen5_SYSTEM_custom_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen5_SYSTEM_custom_imgbtn_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen5_SYSTEM_custom_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen5_SYSTEM_custom_imgbtn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen5_SYSTEM_custom_imgbtn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen5_SYSTEM_custom_imgbtn, LV_IMGBTN_PART_MAIN, &style_screen5_SYSTEM_custom_imgbtn_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_custom_imgbtn, 29, 610);
	lv_obj_set_size(ui->screen5_SYSTEM_custom_imgbtn, 220, 80);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_custom_imgbtn,LV_BTN_STATE_RELEASED,&_button_alpha_220x80);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_custom_imgbtn,LV_BTN_STATE_PRESSED,&_button_on_alpha_220x80);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_custom_imgbtn,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_220x80);
	lv_imgbtn_set_src(ui->screen5_SYSTEM_custom_imgbtn,LV_BTN_STATE_CHECKED_PRESSED,&_button_alpha_220x80);
	lv_imgbtn_set_checkable(ui->screen5_SYSTEM_custom_imgbtn, true);
	ui->screen5_SYSTEM_custom_imgbtn_label = lv_label_create(ui->screen5_SYSTEM_custom_imgbtn, NULL);
	lv_label_set_text(ui->screen5_SYSTEM_custom_imgbtn_label, "connect");

	//Write codes screen5_SYSTEM_instructions_label
	ui->screen5_SYSTEM_instructions_label = lv_label_create(ui->screen5_SYSTEM, NULL);
	lv_label_set_text(ui->screen5_SYSTEM_instructions_label, "Click 'connect' to connect to '*' and measure it's RSSI");
	lv_label_set_long_mode(ui->screen5_SYSTEM_instructions_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen5_SYSTEM_instructions_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen5_SYSTEM_instructions_label
	static lv_style_t style_screen5_SYSTEM_instructions_label_main;
	lv_style_init(&style_screen5_SYSTEM_instructions_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_instructions_label_main
	lv_style_set_radius(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_28);
	lv_style_set_text_letter_space(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen5_SYSTEM_instructions_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen5_SYSTEM_instructions_label, LV_LABEL_PART_MAIN, &style_screen5_SYSTEM_instructions_label_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_instructions_label, 267, 622);
	lv_obj_set_size(ui->screen5_SYSTEM_instructions_label, 416, 0);

	//Write codes screen5_SYSTEM_custom_value_label
	ui->screen5_SYSTEM_custom_value_label = lv_label_create(ui->screen5_SYSTEM, NULL);
	lv_label_set_text(ui->screen5_SYSTEM_custom_value_label, "-100dBm");
	lv_label_set_long_mode(ui->screen5_SYSTEM_custom_value_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen5_SYSTEM_custom_value_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen5_SYSTEM_custom_value_label
	static lv_style_t style_screen5_SYSTEM_custom_value_label_main;
	lv_style_init(&style_screen5_SYSTEM_custom_value_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen5_SYSTEM_custom_value_label_main
	lv_style_set_radius(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen5_SYSTEM_custom_value_label, LV_LABEL_PART_MAIN, &style_screen5_SYSTEM_custom_value_label_main);
	lv_obj_set_pos(ui->screen5_SYSTEM_custom_value_label, 486, 175);
	lv_obj_set_size(ui->screen5_SYSTEM_custom_value_label, 200, 0);

	//Init events for screen
	events_init_screen5_SYSTEM(ui);
}
