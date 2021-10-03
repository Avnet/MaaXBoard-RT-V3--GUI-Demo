/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen0_MENU(lv_ui *ui){

	//Write codes screen0_MENU
	ui->screen0_MENU = lv_obj_create(NULL, NULL);

	//Write codes screen0_MENU_cursor_img
	ui->screen0_MENU_cursor_img = lv_img_create(ui->screen0_MENU, NULL);

	//Write style LV_IMG_PART_MAIN for screen0_MENU_cursor_img
	static lv_style_t style_screen0_MENU_cursor_img_main;
	lv_style_init(&style_screen0_MENU_cursor_img_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_cursor_img_main
	lv_style_set_image_recolor(&style_screen0_MENU_cursor_img_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_cursor_img_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_cursor_img_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_cursor_img, LV_IMG_PART_MAIN, &style_screen0_MENU_cursor_img_main);
	lv_obj_set_pos(ui->screen0_MENU_cursor_img, 177, 205);
	lv_obj_set_size(ui->screen0_MENU_cursor_img, 45, 45);
	lv_obj_set_click(ui->screen0_MENU_cursor_img, true);
	lv_img_set_src(ui->screen0_MENU_cursor_img,&_mouse_alpha_45x45);
	lv_img_set_pivot(ui->screen0_MENU_cursor_img, 0,0);
	lv_img_set_angle(ui->screen0_MENU_cursor_img, 0);

	//Write codes screen0_MENU_canvas_white
	ui->screen0_MENU_canvas_white = lv_canvas_create(ui->screen0_MENU, NULL);

	//Write style LV_CANVAS_PART_MAIN for screen0_MENU_canvas_white
	static lv_style_t style_screen0_MENU_canvas_white_main;
	lv_style_init(&style_screen0_MENU_canvas_white_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_canvas_white_main
	lv_style_set_image_recolor(&style_screen0_MENU_canvas_white_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_canvas_white_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_canvas_white, LV_CANVAS_PART_MAIN, &style_screen0_MENU_canvas_white_main);
	lv_obj_set_pos(ui->screen0_MENU_canvas_white, 0, 0);
	lv_obj_set_size(ui->screen0_MENU_canvas_white, 720, 1280);
	lv_color_t *buf_screen0_MENU_canvas_white = (lv_color_t*)lv_mem_alloc(720*1280*4);
	lv_canvas_set_buffer(ui->screen0_MENU_canvas_white, buf_screen0_MENU_canvas_white, 720, 1280, LV_IMG_CF_TRUE_COLOR);

	//Write codes screen0_MENU_avlogoimg0
	ui->screen0_MENU_avlogoimg0 = lv_img_create(ui->screen0_MENU, NULL);

	//Write style LV_IMG_PART_MAIN for screen0_MENU_avlogoimg0
	static lv_style_t style_screen0_MENU_avlogoimg0_main;
	lv_style_init(&style_screen0_MENU_avlogoimg0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_avlogoimg0_main
	lv_style_set_image_recolor(&style_screen0_MENU_avlogoimg0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_avlogoimg0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_avlogoimg0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_avlogoimg0, LV_IMG_PART_MAIN, &style_screen0_MENU_avlogoimg0_main);
	lv_obj_set_pos(ui->screen0_MENU_avlogoimg0, 0, 0);
	lv_obj_set_size(ui->screen0_MENU_avlogoimg0, 130, 130);
	lv_obj_set_click(ui->screen0_MENU_avlogoimg0, true);
	lv_img_set_src(ui->screen0_MENU_avlogoimg0,&_avnet_logo2_alpha_130x130);
	lv_img_set_pivot(ui->screen0_MENU_avlogoimg0, 0,0);
	lv_img_set_angle(ui->screen0_MENU_avlogoimg0, 0);

	//Write codes screen0_MENU_board_img
	ui->screen0_MENU_board_img = lv_img_create(ui->screen0_MENU, NULL);

	//Write style LV_IMG_PART_MAIN for screen0_MENU_board_img
	static lv_style_t style_screen0_MENU_board_img_main;
	lv_style_init(&style_screen0_MENU_board_img_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_board_img_main
	lv_style_set_image_recolor(&style_screen0_MENU_board_img_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_board_img_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_board_img_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_board_img, LV_IMG_PART_MAIN, &style_screen0_MENU_board_img_main);
	lv_obj_set_pos(ui->screen0_MENU_board_img, 148, 185);
	lv_obj_set_size(ui->screen0_MENU_board_img, 424, 645);
	lv_obj_set_click(ui->screen0_MENU_board_img, true);
	lv_img_set_src(ui->screen0_MENU_board_img,&_SBC_Help_Image_alpha_424x645);
	lv_img_set_pivot(ui->screen0_MENU_board_img, 0,0);
	lv_img_set_angle(ui->screen0_MENU_board_img, 0);

	//Write codes screen0_MENU_page_label
	ui->screen0_MENU_page_label = lv_label_create(ui->screen0_MENU, NULL);
	lv_label_set_text(ui->screen0_MENU_page_label, "MaaxBoard RT");
	lv_label_set_long_mode(ui->screen0_MENU_page_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen0_MENU_page_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen0_MENU_page_label
	static lv_style_t style_screen0_MENU_page_label_main;
	lv_style_init(&style_screen0_MENU_page_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_page_label_main
	lv_style_set_radius(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_48);
	lv_style_set_text_letter_space(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen0_MENU_page_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen0_MENU_page_label, LV_LABEL_PART_MAIN, &style_screen0_MENU_page_label_main);
	lv_obj_set_pos(ui->screen0_MENU_page_label, 180, 45);
	lv_obj_set_size(ui->screen0_MENU_page_label, 500, 0);

	//Write codes screen0_MENU_label_1
	ui->screen0_MENU_label_1 = lv_label_create(ui->screen0_MENU, NULL);
	lv_label_set_text(ui->screen0_MENU_label_1, "GUI demo application");
	lv_label_set_long_mode(ui->screen0_MENU_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen0_MENU_label_1, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen0_MENU_label_1
	static lv_style_t style_screen0_MENU_label_1_main;
	lv_style_init(&style_screen0_MENU_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_label_1_main
	lv_style_set_radius(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_30);
	lv_style_set_text_letter_space(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen0_MENU_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen0_MENU_label_1, LV_LABEL_PART_MAIN, &style_screen0_MENU_label_1_main);
	lv_obj_set_pos(ui->screen0_MENU_label_1, 180, 100);
	lv_obj_set_size(ui->screen0_MENU_label_1, 500, 0);

	//Write codes screen0_MENU_imgbtn_1
	ui->screen0_MENU_imgbtn_1 = lv_imgbtn_create(ui->screen0_MENU, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen0_MENU_imgbtn_1
	static lv_style_t style_screen0_MENU_imgbtn_1_main;
	lv_style_init(&style_screen0_MENU_imgbtn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_imgbtn_1_main
	lv_style_set_text_color(&style_screen0_MENU_imgbtn_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen0_MENU_imgbtn_1_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen0_MENU_imgbtn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_imgbtn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_imgbtn_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_imgbtn_1, LV_IMGBTN_PART_MAIN, &style_screen0_MENU_imgbtn_1_main);
	lv_obj_set_pos(ui->screen0_MENU_imgbtn_1, 30, 890);
	lv_obj_set_size(ui->screen0_MENU_imgbtn_1, 320, 106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_1,LV_BTN_STATE_RELEASED,&_button_alpha_320x106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_1,LV_BTN_STATE_PRESSED,&_button_on_alpha_320x106);
	lv_imgbtn_set_checkable(ui->screen0_MENU_imgbtn_1, true);
	ui->screen0_MENU_imgbtn_1_label = lv_label_create(ui->screen0_MENU_imgbtn_1, NULL);
	lv_label_set_text(ui->screen0_MENU_imgbtn_1_label, "LED Control");

	//Write codes screen0_MENU_imgbtn_2
	ui->screen0_MENU_imgbtn_2 = lv_imgbtn_create(ui->screen0_MENU, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen0_MENU_imgbtn_2
	static lv_style_t style_screen0_MENU_imgbtn_2_main;
	lv_style_init(&style_screen0_MENU_imgbtn_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_imgbtn_2_main
	lv_style_set_text_color(&style_screen0_MENU_imgbtn_2_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen0_MENU_imgbtn_2_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen0_MENU_imgbtn_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_imgbtn_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_imgbtn_2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_imgbtn_2, LV_IMGBTN_PART_MAIN, &style_screen0_MENU_imgbtn_2_main);
	lv_obj_set_pos(ui->screen0_MENU_imgbtn_2, 370, 890);
	lv_obj_set_size(ui->screen0_MENU_imgbtn_2, 320, 106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_2,LV_BTN_STATE_RELEASED,&_button_alpha_320x106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_2,LV_BTN_STATE_PRESSED,&_button_on_alpha_320x106);
	lv_imgbtn_set_checkable(ui->screen0_MENU_imgbtn_2, true);
	ui->screen0_MENU_imgbtn_2_label = lv_label_create(ui->screen0_MENU_imgbtn_2, NULL);
	lv_label_set_text(ui->screen0_MENU_imgbtn_2_label, "Audio & Video");

	//Write codes screen0_MENU_imgbtn_3
	ui->screen0_MENU_imgbtn_3 = lv_imgbtn_create(ui->screen0_MENU, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen0_MENU_imgbtn_3
	static lv_style_t style_screen0_MENU_imgbtn_3_main;
	lv_style_init(&style_screen0_MENU_imgbtn_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_imgbtn_3_main
	lv_style_set_text_color(&style_screen0_MENU_imgbtn_3_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen0_MENU_imgbtn_3_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen0_MENU_imgbtn_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_imgbtn_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_imgbtn_3_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_imgbtn_3, LV_IMGBTN_PART_MAIN, &style_screen0_MENU_imgbtn_3_main);
	lv_obj_set_pos(ui->screen0_MENU_imgbtn_3, 30, 1015);
	lv_obj_set_size(ui->screen0_MENU_imgbtn_3, 320, 106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_3,LV_BTN_STATE_RELEASED,&_button_alpha_320x106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_3,LV_BTN_STATE_PRESSED,&_button_on_alpha_320x106);
	lv_imgbtn_set_checkable(ui->screen0_MENU_imgbtn_3, true);
	ui->screen0_MENU_imgbtn_3_label = lv_label_create(ui->screen0_MENU_imgbtn_3, NULL);
	lv_label_set_text(ui->screen0_MENU_imgbtn_3_label, "Wi-Fi & Network");

	//Write codes screen0_MENU_imgbtn_4
	ui->screen0_MENU_imgbtn_4 = lv_imgbtn_create(ui->screen0_MENU, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen0_MENU_imgbtn_4
	static lv_style_t style_screen0_MENU_imgbtn_4_main;
	lv_style_init(&style_screen0_MENU_imgbtn_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_imgbtn_4_main
	lv_style_set_text_color(&style_screen0_MENU_imgbtn_4_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen0_MENU_imgbtn_4_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen0_MENU_imgbtn_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_imgbtn_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_imgbtn_4_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_imgbtn_4, LV_IMGBTN_PART_MAIN, &style_screen0_MENU_imgbtn_4_main);
	lv_obj_set_pos(ui->screen0_MENU_imgbtn_4, 370, 1015);
	lv_obj_set_size(ui->screen0_MENU_imgbtn_4, 320, 106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_4,LV_BTN_STATE_RELEASED,&_button_alpha_320x106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_4,LV_BTN_STATE_PRESSED,&_button_on_alpha_320x106);
	lv_imgbtn_set_checkable(ui->screen0_MENU_imgbtn_4, true);
	ui->screen0_MENU_imgbtn_4_label = lv_label_create(ui->screen0_MENU_imgbtn_4, NULL);
	lv_label_set_text(ui->screen0_MENU_imgbtn_4_label, "Custom");

	//Write codes screen0_MENU_imgbtn_5
	ui->screen0_MENU_imgbtn_5 = lv_imgbtn_create(ui->screen0_MENU, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen0_MENU_imgbtn_5
	static lv_style_t style_screen0_MENU_imgbtn_5_main;
	lv_style_init(&style_screen0_MENU_imgbtn_5_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_imgbtn_5_main
	lv_style_set_text_color(&style_screen0_MENU_imgbtn_5_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen0_MENU_imgbtn_5_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen0_MENU_imgbtn_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_imgbtn_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_imgbtn_5_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_imgbtn_5, LV_IMGBTN_PART_MAIN, &style_screen0_MENU_imgbtn_5_main);
	lv_obj_set_pos(ui->screen0_MENU_imgbtn_5, 30, 1140);
	lv_obj_set_size(ui->screen0_MENU_imgbtn_5, 320, 106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_5,LV_BTN_STATE_RELEASED,&_button_alpha_320x106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_5,LV_BTN_STATE_PRESSED,&_button_on_alpha_320x106);
	lv_imgbtn_set_checkable(ui->screen0_MENU_imgbtn_5, true);
	ui->screen0_MENU_imgbtn_5_label = lv_label_create(ui->screen0_MENU_imgbtn_5, NULL);
	lv_label_set_text(ui->screen0_MENU_imgbtn_5_label, "USB & Expansion");

	//Write codes screen0_MENU_imgbtn_6
	ui->screen0_MENU_imgbtn_6 = lv_imgbtn_create(ui->screen0_MENU, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen0_MENU_imgbtn_6
	static lv_style_t style_screen0_MENU_imgbtn_6_main;
	lv_style_init(&style_screen0_MENU_imgbtn_6_main);

	//Write style state: LV_STATE_DEFAULT for style_screen0_MENU_imgbtn_6_main
	lv_style_set_text_color(&style_screen0_MENU_imgbtn_6_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen0_MENU_imgbtn_6_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_36);
	lv_style_set_image_recolor(&style_screen0_MENU_imgbtn_6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen0_MENU_imgbtn_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen0_MENU_imgbtn_6_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen0_MENU_imgbtn_6, LV_IMGBTN_PART_MAIN, &style_screen0_MENU_imgbtn_6_main);
	lv_obj_set_pos(ui->screen0_MENU_imgbtn_6, 370, 1140);
	lv_obj_set_size(ui->screen0_MENU_imgbtn_6, 320, 106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_6,LV_BTN_STATE_RELEASED,&_button_alpha_320x106);
	lv_imgbtn_set_src(ui->screen0_MENU_imgbtn_6,LV_BTN_STATE_PRESSED,&_button_on_alpha_320x106);
	lv_imgbtn_set_checkable(ui->screen0_MENU_imgbtn_6, true);
	ui->screen0_MENU_imgbtn_6_label = lv_label_create(ui->screen0_MENU_imgbtn_6, NULL);
	lv_label_set_text(ui->screen0_MENU_imgbtn_6_label, "Help & Info");

	//Init events for screen
	events_init_screen0_MENU(ui);
}
