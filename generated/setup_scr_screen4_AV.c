/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen4_AV(lv_ui *ui){

	//Write codes screen4_AV
	ui->screen4_AV = lv_obj_create(NULL, NULL);

	//Write codes screen4_AV_canvas_white
	ui->screen4_AV_canvas_white = lv_canvas_create(ui->screen4_AV, NULL);

	//Write style LV_CANVAS_PART_MAIN for screen4_AV_canvas_white
	static lv_style_t style_screen4_AV_canvas_white_main;
	lv_style_init(&style_screen4_AV_canvas_white_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_canvas_white_main
	lv_style_set_image_recolor(&style_screen4_AV_canvas_white_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen4_AV_canvas_white_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen4_AV_canvas_white, LV_CANVAS_PART_MAIN, &style_screen4_AV_canvas_white_main);
	lv_obj_set_pos(ui->screen4_AV_canvas_white, 0, 0);
	lv_obj_set_size(ui->screen4_AV_canvas_white, 720, 1280);
	lv_color_t *buf_screen4_AV_canvas_white = (lv_color_t*)lv_mem_alloc(720*1280*4);
	lv_canvas_set_buffer(ui->screen4_AV_canvas_white, buf_screen4_AV_canvas_white, 720, 1280, LV_IMG_CF_TRUE_COLOR);

	//Write codes screen4_AV_left_btn
	ui->screen4_AV_left_btn = lv_imgbtn_create(ui->screen4_AV, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen4_AV_left_btn
	static lv_style_t style_screen4_AV_left_btn_main;
	lv_style_init(&style_screen4_AV_left_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_left_btn_main
	lv_style_set_text_color(&style_screen4_AV_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen4_AV_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen4_AV_left_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen4_AV_left_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen4_AV_left_btn, LV_IMGBTN_PART_MAIN, &style_screen4_AV_left_btn_main);
	lv_obj_set_pos(ui->screen4_AV_left_btn, 44, 1100);
	lv_obj_set_size(ui->screen4_AV_left_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen4_AV_left_btn,LV_BTN_STATE_RELEASED,&_left_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen4_AV_left_btn,LV_BTN_STATE_PRESSED,&_left_icon_alpha_132x132);

	//Write codes screen4_AV_left_label
	ui->screen4_AV_left_label = lv_label_create(ui->screen4_AV, NULL);
	lv_label_set_text(ui->screen4_AV_left_label, "USB");
	lv_label_set_long_mode(ui->screen4_AV_left_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen4_AV_left_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen4_AV_left_label
	static lv_style_t style_screen4_AV_left_label_main;
	lv_style_init(&style_screen4_AV_left_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_left_label_main
	lv_style_set_radius(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen4_AV_left_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_left_label, LV_LABEL_PART_MAIN, &style_screen4_AV_left_label_main);
	lv_obj_set_pos(ui->screen4_AV_left_label, 20, 1200);
	lv_obj_set_size(ui->screen4_AV_left_label, 180, 0);

	//Write codes screen4_AV_avlogoimg0
	ui->screen4_AV_avlogoimg0 = lv_img_create(ui->screen4_AV, NULL);

	//Write style LV_IMG_PART_MAIN for screen4_AV_avlogoimg0
	static lv_style_t style_screen4_AV_avlogoimg0_main;
	lv_style_init(&style_screen4_AV_avlogoimg0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_avlogoimg0_main
	lv_style_set_image_recolor(&style_screen4_AV_avlogoimg0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen4_AV_avlogoimg0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen4_AV_avlogoimg0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen4_AV_avlogoimg0, LV_IMG_PART_MAIN, &style_screen4_AV_avlogoimg0_main);
	lv_obj_set_pos(ui->screen4_AV_avlogoimg0, 0, 0);
	lv_obj_set_size(ui->screen4_AV_avlogoimg0, 130, 130);
	lv_obj_set_click(ui->screen4_AV_avlogoimg0, true);
	lv_img_set_src(ui->screen4_AV_avlogoimg0,&_avnet_logo2_alpha_130x130);
	lv_img_set_pivot(ui->screen4_AV_avlogoimg0, 0,0);
	lv_img_set_angle(ui->screen4_AV_avlogoimg0, 0);

	//Write codes screen4_AV_right_btn
	ui->screen4_AV_right_btn = lv_imgbtn_create(ui->screen4_AV, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen4_AV_right_btn
	static lv_style_t style_screen4_AV_right_btn_main;
	lv_style_init(&style_screen4_AV_right_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_right_btn_main
	lv_style_set_text_color(&style_screen4_AV_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen4_AV_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen4_AV_right_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen4_AV_right_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen4_AV_right_btn, LV_IMGBTN_PART_MAIN, &style_screen4_AV_right_btn_main);
	lv_obj_set_pos(ui->screen4_AV_right_btn, 544, 1100);
	lv_obj_set_size(ui->screen4_AV_right_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen4_AV_right_btn,LV_BTN_STATE_RELEASED,&_right_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen4_AV_right_btn,LV_BTN_STATE_PRESSED,&_right_icon_alpha_132x132);

	//Write codes screen4_AV_right_label
	ui->screen4_AV_right_label = lv_label_create(ui->screen4_AV, NULL);
	lv_label_set_text(ui->screen4_AV_right_label, "CUSTOM");
	lv_label_set_long_mode(ui->screen4_AV_right_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen4_AV_right_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen4_AV_right_label
	static lv_style_t style_screen4_AV_right_label_main;
	lv_style_init(&style_screen4_AV_right_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_right_label_main
	lv_style_set_radius(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen4_AV_right_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_right_label, LV_LABEL_PART_MAIN, &style_screen4_AV_right_label_main);
	lv_obj_set_pos(ui->screen4_AV_right_label, 520, 1200);
	lv_obj_set_size(ui->screen4_AV_right_label, 180, 0);

	//Write codes screen4_AV_home_btn
	ui->screen4_AV_home_btn = lv_imgbtn_create(ui->screen4_AV, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen4_AV_home_btn
	static lv_style_t style_screen4_AV_home_btn_main;
	lv_style_init(&style_screen4_AV_home_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_home_btn_main
	lv_style_set_text_color(&style_screen4_AV_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen4_AV_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen4_AV_home_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen4_AV_home_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen4_AV_home_btn, LV_IMGBTN_PART_MAIN, &style_screen4_AV_home_btn_main);
	lv_obj_set_pos(ui->screen4_AV_home_btn, 294, 1100);
	lv_obj_set_size(ui->screen4_AV_home_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen4_AV_home_btn,LV_BTN_STATE_RELEASED,&_home_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen4_AV_home_btn,LV_BTN_STATE_PRESSED,&_home_icon_alpha_132x132);

	//Write codes screen4_AV_page_label
	ui->screen4_AV_page_label = lv_label_create(ui->screen4_AV, NULL);
	lv_label_set_text(ui->screen4_AV_page_label, "Audio & Video");
	lv_label_set_long_mode(ui->screen4_AV_page_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen4_AV_page_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen4_AV_page_label
	static lv_style_t style_screen4_AV_page_label_main;
	lv_style_init(&style_screen4_AV_page_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_page_label_main
	lv_style_set_radius(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_48);
	lv_style_set_text_letter_space(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen4_AV_page_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_page_label, LV_LABEL_PART_MAIN, &style_screen4_AV_page_label_main);
	lv_obj_set_pos(ui->screen4_AV_page_label, 180, 45);
	lv_obj_set_size(ui->screen4_AV_page_label, 500, 0);

	//Write codes screen4_AV_camera_label
	ui->screen4_AV_camera_label = lv_label_create(ui->screen4_AV, NULL);
	lv_label_set_text(ui->screen4_AV_camera_label, "Camera State:");
	lv_label_set_long_mode(ui->screen4_AV_camera_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen4_AV_camera_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen4_AV_camera_label
	static lv_style_t style_screen4_AV_camera_label_main;
	lv_style_init(&style_screen4_AV_camera_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_camera_label_main
	lv_style_set_radius(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, lv_color_make(0xa8, 0xa8, 0xa8));
	lv_style_set_text_font(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen4_AV_camera_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_camera_label, LV_LABEL_PART_MAIN, &style_screen4_AV_camera_label_main);
	lv_obj_set_pos(ui->screen4_AV_camera_label, 30, 180);
	lv_obj_set_size(ui->screen4_AV_camera_label, 600, 0);

	//Write codes screen4_AV_camera_state_label
	ui->screen4_AV_camera_state_label = lv_label_create(ui->screen4_AV, NULL);
	lv_label_set_text(ui->screen4_AV_camera_state_label, "Not Connected");
	lv_label_set_long_mode(ui->screen4_AV_camera_state_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen4_AV_camera_state_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen4_AV_camera_state_label
	static lv_style_t style_screen4_AV_camera_state_label_main;
	lv_style_init(&style_screen4_AV_camera_state_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_camera_state_label_main
	lv_style_set_radius(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, lv_color_make(0xa8, 0xa8, 0xa8));
	lv_style_set_text_font(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_SemiBold_40);
	lv_style_set_text_letter_space(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen4_AV_camera_state_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_camera_state_label, LV_LABEL_PART_MAIN, &style_screen4_AV_camera_state_label_main);
	lv_obj_set_pos(ui->screen4_AV_camera_state_label, 30, 233);
	lv_obj_set_size(ui->screen4_AV_camera_state_label, 600, 0);

	//Write codes screen4_AV_playback_label
	ui->screen4_AV_playback_label = lv_label_create(ui->screen4_AV, NULL);
	lv_label_set_text(ui->screen4_AV_playback_label, "Note: Up to 2 selected mic will be sent to audio jack.");
	lv_label_set_long_mode(ui->screen4_AV_playback_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen4_AV_playback_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen4_AV_playback_label
	static lv_style_t style_screen4_AV_playback_label_main;
	lv_style_init(&style_screen4_AV_playback_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_playback_label_main
	lv_style_set_radius(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_16);
	lv_style_set_text_letter_space(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen4_AV_playback_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_playback_label, LV_LABEL_PART_MAIN, &style_screen4_AV_playback_label_main);
	lv_obj_set_pos(ui->screen4_AV_playback_label, 60, 950);
	lv_obj_set_size(ui->screen4_AV_playback_label, 600, 0);

	//Write codes screen4_AV_mic_label
	ui->screen4_AV_mic_label = lv_label_create(ui->screen4_AV, NULL);
	lv_label_set_text(ui->screen4_AV_mic_label, "Microphone Input:");
	lv_label_set_long_mode(ui->screen4_AV_mic_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen4_AV_mic_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen4_AV_mic_label
	static lv_style_t style_screen4_AV_mic_label_main;
	lv_style_init(&style_screen4_AV_mic_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic_label_main
	lv_style_set_radius(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen4_AV_mic_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_mic_label, LV_LABEL_PART_MAIN, &style_screen4_AV_mic_label_main);
	lv_obj_set_pos(ui->screen4_AV_mic_label, 32, 320);
	lv_obj_set_size(ui->screen4_AV_mic_label, 600, 0);

	//Write codes screen4_AV_mic1_cb
	ui->screen4_AV_mic1_cb = lv_checkbox_create(ui->screen4_AV, NULL);
	lv_checkbox_set_text(ui->screen4_AV_mic1_cb, "mic 1");

	//Write style LV_CHECKBOX_PART_BG for screen4_AV_mic1_cb
	static lv_style_t style_screen4_AV_mic1_cb_bg;
	lv_style_init(&style_screen4_AV_mic1_cb_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic1_cb_bg
	lv_style_set_radius(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_text_letter_space(&style_screen4_AV_mic1_cb_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_mic1_cb, LV_CHECKBOX_PART_BG, &style_screen4_AV_mic1_cb_bg);

	//Write style LV_CHECKBOX_PART_BULLET for screen4_AV_mic1_cb
	static lv_style_t style_screen4_AV_mic1_cb_bullet;
	lv_style_init(&style_screen4_AV_mic1_cb_bullet);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic1_cb_bullet
	lv_style_set_radius(&style_screen4_AV_mic1_cb_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic1_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic1_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic1_cb_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic1_cb_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen4_AV_mic1_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen4_AV_mic1_cb_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen4_AV_mic1_cb, LV_CHECKBOX_PART_BULLET, &style_screen4_AV_mic1_cb_bullet);
	lv_obj_set_pos(ui->screen4_AV_mic1_cb, 50, 830);

	//Write codes screen4_AV_mic2_cb
	ui->screen4_AV_mic2_cb = lv_checkbox_create(ui->screen4_AV, NULL);
	lv_checkbox_set_text(ui->screen4_AV_mic2_cb, "mic 2");

	//Write style LV_CHECKBOX_PART_BG for screen4_AV_mic2_cb
	static lv_style_t style_screen4_AV_mic2_cb_bg;
	lv_style_init(&style_screen4_AV_mic2_cb_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic2_cb_bg
	lv_style_set_radius(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_text_letter_space(&style_screen4_AV_mic2_cb_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_mic2_cb, LV_CHECKBOX_PART_BG, &style_screen4_AV_mic2_cb_bg);

	//Write style LV_CHECKBOX_PART_BULLET for screen4_AV_mic2_cb
	static lv_style_t style_screen4_AV_mic2_cb_bullet;
	lv_style_init(&style_screen4_AV_mic2_cb_bullet);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic2_cb_bullet
	lv_style_set_radius(&style_screen4_AV_mic2_cb_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic2_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic2_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic2_cb_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic2_cb_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen4_AV_mic2_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen4_AV_mic2_cb_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen4_AV_mic2_cb, LV_CHECKBOX_PART_BULLET, &style_screen4_AV_mic2_cb_bullet);
	lv_obj_set_pos(ui->screen4_AV_mic2_cb, 210, 830);

	//Write codes screen4_AV_mic3_cb
	ui->screen4_AV_mic3_cb = lv_checkbox_create(ui->screen4_AV, NULL);
	lv_checkbox_set_text(ui->screen4_AV_mic3_cb, "mic 3");

	//Write style LV_CHECKBOX_PART_BG for screen4_AV_mic3_cb
	static lv_style_t style_screen4_AV_mic3_cb_bg;
	lv_style_init(&style_screen4_AV_mic3_cb_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic3_cb_bg
	lv_style_set_radius(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_text_letter_space(&style_screen4_AV_mic3_cb_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_mic3_cb, LV_CHECKBOX_PART_BG, &style_screen4_AV_mic3_cb_bg);

	//Write style LV_CHECKBOX_PART_BULLET for screen4_AV_mic3_cb
	static lv_style_t style_screen4_AV_mic3_cb_bullet;
	lv_style_init(&style_screen4_AV_mic3_cb_bullet);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic3_cb_bullet
	lv_style_set_radius(&style_screen4_AV_mic3_cb_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic3_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic3_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic3_cb_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic3_cb_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen4_AV_mic3_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen4_AV_mic3_cb_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen4_AV_mic3_cb, LV_CHECKBOX_PART_BULLET, &style_screen4_AV_mic3_cb_bullet);
	lv_obj_set_pos(ui->screen4_AV_mic3_cb, 370, 830);

	//Write codes screen4_AV_mic4_cb
	ui->screen4_AV_mic4_cb = lv_checkbox_create(ui->screen4_AV, NULL);
	lv_checkbox_set_text(ui->screen4_AV_mic4_cb, "mic 4");

	//Write style LV_CHECKBOX_PART_BG for screen4_AV_mic4_cb
	static lv_style_t style_screen4_AV_mic4_cb_bg;
	lv_style_init(&style_screen4_AV_mic4_cb_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic4_cb_bg
	lv_style_set_radius(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_text_letter_space(&style_screen4_AV_mic4_cb_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen4_AV_mic4_cb, LV_CHECKBOX_PART_BG, &style_screen4_AV_mic4_cb_bg);

	//Write style LV_CHECKBOX_PART_BULLET for screen4_AV_mic4_cb
	static lv_style_t style_screen4_AV_mic4_cb_bullet;
	lv_style_init(&style_screen4_AV_mic4_cb_bullet);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic4_cb_bullet
	lv_style_set_radius(&style_screen4_AV_mic4_cb_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_screen4_AV_mic4_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic4_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic4_cb_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic4_cb_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen4_AV_mic4_cb_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen4_AV_mic4_cb_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen4_AV_mic4_cb, LV_CHECKBOX_PART_BULLET, &style_screen4_AV_mic4_cb_bullet);
	lv_obj_set_pos(ui->screen4_AV_mic4_cb, 530, 830);

	//Write codes screen4_AV_mic_chart
	ui->screen4_AV_mic_chart = lv_chart_create(ui->screen4_AV, NULL);

	//Write style LV_CHART_PART_BG for screen4_AV_mic_chart
	static lv_style_t style_screen4_AV_mic_chart_bg;
	lv_style_init(&style_screen4_AV_mic_chart_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic_chart_bg
	lv_style_set_bg_color(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_screen4_AV_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen4_AV_mic_chart, LV_CHART_PART_BG, &style_screen4_AV_mic_chart_bg);

	//Write style LV_CHART_PART_SERIES_BG for screen4_AV_mic_chart
	static lv_style_t style_screen4_AV_mic_chart_series_bg;
	lv_style_init(&style_screen4_AV_mic_chart_series_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen4_AV_mic_chart_series_bg
	lv_style_set_line_color(&style_screen4_AV_mic_chart_series_bg, LV_STATE_DEFAULT, lv_color_make(0xe8, 0xe8, 0xe8));
	lv_style_set_line_width(&style_screen4_AV_mic_chart_series_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_line_opa(&style_screen4_AV_mic_chart_series_bg, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen4_AV_mic_chart, LV_CHART_PART_SERIES_BG, &style_screen4_AV_mic_chart_series_bg);
	lv_obj_set_pos(ui->screen4_AV_mic_chart, 30, 390);
	lv_obj_set_size(ui->screen4_AV_mic_chart, 660, 420);
	lv_chart_set_type(ui->screen4_AV_mic_chart,LV_CHART_TYPE_LINE);
	lv_chart_set_range(ui->screen4_AV_mic_chart,0,100);
	lv_chart_set_div_line_count(ui->screen4_AV_mic_chart, 3, 5);

	//Init events for screen
	events_init_screen4_AV(ui);
}
