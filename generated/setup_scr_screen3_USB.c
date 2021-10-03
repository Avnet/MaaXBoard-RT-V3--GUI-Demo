/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

static lv_obj_t * kb;
static void kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
{
	/* Just call the regular event handler */
	lv_keyboard_def_event_cb(event_kb, event);
	if(event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL){
		if(NULL != kb){
			lv_obj_del(kb);
		}
	}
}
static void text_area_event_cb(lv_obj_t* ta, lv_event_t event)
{

	if(event == LV_EVENT_CLICKED){
		 if( !lv_debug_check_obj_valid(kb) ){
			/* Create a keyboard and make it fill the width of the above text areas */
			kb = lv_keyboard_create(lv_scr_act(), NULL);
			lv_obj_set_event_cb(kb, kb_event_cb);
			lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
		}
		lv_keyboard_set_textarea(kb, ta);
		lv_keyboard_set_cursor_manage(kb, true); 
	}
}

void setup_scr_screen3_USB(lv_ui *ui){

	//Write codes screen3_USB
	ui->screen3_USB = lv_obj_create(NULL, NULL);

	//Write codes screen3_USB_canvas_white
	ui->screen3_USB_canvas_white = lv_canvas_create(ui->screen3_USB, NULL);

	//Write style LV_CANVAS_PART_MAIN for screen3_USB_canvas_white
	static lv_style_t style_screen3_USB_canvas_white_main;
	lv_style_init(&style_screen3_USB_canvas_white_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_canvas_white_main
	lv_style_set_image_recolor(&style_screen3_USB_canvas_white_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_canvas_white_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_canvas_white, LV_CANVAS_PART_MAIN, &style_screen3_USB_canvas_white_main);
	lv_obj_set_pos(ui->screen3_USB_canvas_white, 0, 0);
	lv_obj_set_size(ui->screen3_USB_canvas_white, 720, 1280);
	lv_color_t *buf_screen3_USB_canvas_white = (lv_color_t*)lv_mem_alloc(720*1280*4);
	lv_canvas_set_buffer(ui->screen3_USB_canvas_white, buf_screen3_USB_canvas_white, 720, 1280, LV_IMG_CF_TRUE_COLOR);

	//Write codes screen3_USB_left_btn
	ui->screen3_USB_left_btn = lv_imgbtn_create(ui->screen3_USB, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen3_USB_left_btn
	static lv_style_t style_screen3_USB_left_btn_main;
	lv_style_init(&style_screen3_USB_left_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_left_btn_main
	lv_style_set_text_color(&style_screen3_USB_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen3_USB_left_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_left_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen3_USB_left_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_left_btn, LV_IMGBTN_PART_MAIN, &style_screen3_USB_left_btn_main);
	lv_obj_set_pos(ui->screen3_USB_left_btn, 44, 1100);
	lv_obj_set_size(ui->screen3_USB_left_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen3_USB_left_btn,LV_BTN_STATE_RELEASED,&_left_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen3_USB_left_btn,LV_BTN_STATE_PRESSED,&_left_icon_alpha_132x132);

	//Write codes screen3_USB_left_label
	ui->screen3_USB_left_label = lv_label_create(ui->screen3_USB, NULL);
	lv_label_set_text(ui->screen3_USB_left_label, "Wi-Fi");
	lv_label_set_long_mode(ui->screen3_USB_left_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen3_USB_left_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen3_USB_left_label
	static lv_style_t style_screen3_USB_left_label_main;
	lv_style_init(&style_screen3_USB_left_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_left_label_main
	lv_style_set_radius(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen3_USB_left_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen3_USB_left_label, LV_LABEL_PART_MAIN, &style_screen3_USB_left_label_main);
	lv_obj_set_pos(ui->screen3_USB_left_label, 20, 1200);
	lv_obj_set_size(ui->screen3_USB_left_label, 180, 0);

	//Write codes screen3_USB_avlogoimg0
	ui->screen3_USB_avlogoimg0 = lv_img_create(ui->screen3_USB, NULL);

	//Write style LV_IMG_PART_MAIN for screen3_USB_avlogoimg0
	static lv_style_t style_screen3_USB_avlogoimg0_main;
	lv_style_init(&style_screen3_USB_avlogoimg0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_avlogoimg0_main
	lv_style_set_image_recolor(&style_screen3_USB_avlogoimg0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_avlogoimg0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen3_USB_avlogoimg0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_avlogoimg0, LV_IMG_PART_MAIN, &style_screen3_USB_avlogoimg0_main);
	lv_obj_set_pos(ui->screen3_USB_avlogoimg0, 0, 0);
	lv_obj_set_size(ui->screen3_USB_avlogoimg0, 130, 130);
	lv_obj_set_click(ui->screen3_USB_avlogoimg0, true);
	lv_img_set_src(ui->screen3_USB_avlogoimg0,&_avnet_logo2_alpha_130x130);
	lv_img_set_pivot(ui->screen3_USB_avlogoimg0, 0,0);
	lv_img_set_angle(ui->screen3_USB_avlogoimg0, 0);

	//Write codes screen3_USB_right_btn
	ui->screen3_USB_right_btn = lv_imgbtn_create(ui->screen3_USB, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen3_USB_right_btn
	static lv_style_t style_screen3_USB_right_btn_main;
	lv_style_init(&style_screen3_USB_right_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_right_btn_main
	lv_style_set_text_color(&style_screen3_USB_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen3_USB_right_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_right_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen3_USB_right_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_right_btn, LV_IMGBTN_PART_MAIN, &style_screen3_USB_right_btn_main);
	lv_obj_set_pos(ui->screen3_USB_right_btn, 544, 1100);
	lv_obj_set_size(ui->screen3_USB_right_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen3_USB_right_btn,LV_BTN_STATE_RELEASED,&_right_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen3_USB_right_btn,LV_BTN_STATE_PRESSED,&_right_icon_alpha_132x132);

	//Write codes screen3_USB_right_label
	ui->screen3_USB_right_label = lv_label_create(ui->screen3_USB, NULL);
	lv_label_set_text(ui->screen3_USB_right_label, "A & V");
	lv_label_set_long_mode(ui->screen3_USB_right_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen3_USB_right_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen3_USB_right_label
	static lv_style_t style_screen3_USB_right_label_main;
	lv_style_init(&style_screen3_USB_right_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_right_label_main
	lv_style_set_radius(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen3_USB_right_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen3_USB_right_label, LV_LABEL_PART_MAIN, &style_screen3_USB_right_label_main);
	lv_obj_set_pos(ui->screen3_USB_right_label, 520, 1200);
	lv_obj_set_size(ui->screen3_USB_right_label, 180, 0);

	//Write codes screen3_USB_home_btn
	ui->screen3_USB_home_btn = lv_imgbtn_create(ui->screen3_USB, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen3_USB_home_btn
	static lv_style_t style_screen3_USB_home_btn_main;
	lv_style_init(&style_screen3_USB_home_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_home_btn_main
	lv_style_set_text_color(&style_screen3_USB_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_screen3_USB_home_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_home_btn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen3_USB_home_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_home_btn, LV_IMGBTN_PART_MAIN, &style_screen3_USB_home_btn_main);
	lv_obj_set_pos(ui->screen3_USB_home_btn, 294, 1100);
	lv_obj_set_size(ui->screen3_USB_home_btn, 132, 132);
	lv_imgbtn_set_src(ui->screen3_USB_home_btn,LV_BTN_STATE_RELEASED,&_home_icon_alpha_132x132);
	lv_imgbtn_set_src(ui->screen3_USB_home_btn,LV_BTN_STATE_PRESSED,&_home_icon_alpha_132x132);

	//Write codes screen3_USB_page_label
	ui->screen3_USB_page_label = lv_label_create(ui->screen3_USB, NULL);
	lv_label_set_text(ui->screen3_USB_page_label, "USB & Expansion");
	lv_label_set_long_mode(ui->screen3_USB_page_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen3_USB_page_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen3_USB_page_label
	static lv_style_t style_screen3_USB_page_label_main;
	lv_style_init(&style_screen3_USB_page_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_page_label_main
	lv_style_set_radius(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, lv_color_make(0x13, 0x80, 0x36));
	lv_style_set_text_font(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_48);
	lv_style_set_text_letter_space(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen3_USB_page_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen3_USB_page_label, LV_LABEL_PART_MAIN, &style_screen3_USB_page_label_main);
	lv_obj_set_pos(ui->screen3_USB_page_label, 180, 45);
	lv_obj_set_size(ui->screen3_USB_page_label, 500, 0);

	//Write codes screen3_USB_usb_list
	ui->screen3_USB_usb_list = lv_list_create(ui->screen3_USB, NULL);
	lv_list_set_edge_flash(ui->screen3_USB_usb_list, true);

	//Write style LV_LIST_PART_BG for screen3_USB_usb_list
	static lv_style_t style_screen3_USB_usb_list_bg;
	lv_style_init(&style_screen3_USB_usb_list_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_usb_list_bg
	lv_style_set_radius(&style_screen3_USB_usb_list_bg, LV_STATE_DEFAULT, 3);
	lv_style_set_border_color(&style_screen3_USB_usb_list_bg, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen3_USB_usb_list_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_screen3_USB_usb_list_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen3_USB_usb_list_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen3_USB_usb_list_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen3_USB_usb_list, LV_LIST_PART_BG, &style_screen3_USB_usb_list_bg);

	//Write style LV_LIST_PART_SCROLLABLE for screen3_USB_usb_list
	static lv_style_t style_screen3_USB_usb_list_scrollable;
	lv_style_init(&style_screen3_USB_usb_list_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_usb_list_scrollable
	lv_style_set_radius(&style_screen3_USB_usb_list_scrollable, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen3_USB_usb_list_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_usb_list_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_usb_list_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_usb_list_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_usb_list, LV_LIST_PART_SCROLLABLE, &style_screen3_USB_usb_list_scrollable);

	//Write style LV_BTN_PART_MAIN for screen3_USB_usb_list
	static lv_style_t style_screen3_USB_usb_list_main_child;
	lv_style_init(&style_screen3_USB_usb_list_main_child);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_usb_list_main_child
	lv_style_set_radius(&style_screen3_USB_usb_list_main_child, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen3_USB_usb_list_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_usb_list_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_usb_list_main_child, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_usb_list_main_child, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_usb_list_main_child, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_obj_set_pos(ui->screen3_USB_usb_list, 0, 235);
	lv_obj_set_size(ui->screen3_USB_usb_list, 720, 190);
	lv_obj_t *screen3_USB_usb_list_btn;

	//Write codes screen3_USB_usb_devices_label
	ui->screen3_USB_usb_devices_label = lv_label_create(ui->screen3_USB, NULL);
	lv_label_set_text(ui->screen3_USB_usb_devices_label, "Connected HID Devices");
	lv_label_set_long_mode(ui->screen3_USB_usb_devices_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen3_USB_usb_devices_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen3_USB_usb_devices_label
	static lv_style_t style_screen3_USB_usb_devices_label_main;
	lv_style_init(&style_screen3_USB_usb_devices_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_usb_devices_label_main
	lv_style_set_radius(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen3_USB_usb_devices_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen3_USB_usb_devices_label, LV_LABEL_PART_MAIN, &style_screen3_USB_usb_devices_label_main);
	lv_obj_set_pos(ui->screen3_USB_usb_devices_label, 30, 180);
	lv_obj_set_size(ui->screen3_USB_usb_devices_label, 600, 0);

	//Write codes screen3_USB_input_label
	ui->screen3_USB_input_label = lv_label_create(ui->screen3_USB, NULL);
	lv_label_set_text(ui->screen3_USB_input_label, "Input Test");
	lv_label_set_long_mode(ui->screen3_USB_input_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen3_USB_input_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen3_USB_input_label
	static lv_style_t style_screen3_USB_input_label_main;
	lv_style_init(&style_screen3_USB_input_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_input_label_main
	lv_style_set_radius(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen3_USB_input_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen3_USB_input_label, LV_LABEL_PART_MAIN, &style_screen3_USB_input_label_main);
	lv_obj_set_pos(ui->screen3_USB_input_label, 30, 455);
	lv_obj_set_size(ui->screen3_USB_input_label, 300, 0);

	//Write codes screen3_USB_i2c_nodes_label
	ui->screen3_USB_i2c_nodes_label = lv_label_create(ui->screen3_USB, NULL);
	lv_label_set_text(ui->screen3_USB_i2c_nodes_label, "I2C Nodes");
	lv_label_set_long_mode(ui->screen3_USB_i2c_nodes_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen3_USB_i2c_nodes_label, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for screen3_USB_i2c_nodes_label
	static lv_style_t style_screen3_USB_i2c_nodes_label_main;
	lv_style_init(&style_screen3_USB_i2c_nodes_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_i2c_nodes_label_main
	lv_style_set_radius(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_40);
	lv_style_set_text_letter_space(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen3_USB_i2c_nodes_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen3_USB_i2c_nodes_label, LV_LABEL_PART_MAIN, &style_screen3_USB_i2c_nodes_label_main);
	lv_obj_set_pos(ui->screen3_USB_i2c_nodes_label, 30, 755);
	lv_obj_set_size(ui->screen3_USB_i2c_nodes_label, 250, 0);

	//Write codes screen3_USB_i2c_table
	ui->screen3_USB_i2c_table = lv_table_create(ui->screen3_USB, NULL);

	//Write style LV_TABLE_PART_BG for screen3_USB_i2c_table
	static lv_style_t style_screen3_USB_i2c_table_bg;
	lv_style_init(&style_screen3_USB_i2c_table_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_i2c_table_bg
	lv_style_set_bg_color(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, lv_color_make(0xd5, 0xde, 0xe6));
	lv_style_set_border_width(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, lv_color_make(0x39, 0x3c, 0x41));
	lv_style_set_text_decor(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, &lv_font_inconsolata_light_18);
	lv_style_set_pad_left(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_screen3_USB_i2c_table_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen3_USB_i2c_table, LV_TABLE_PART_BG, &style_screen3_USB_i2c_table_bg);

	//Write style LV_TABLE_PART_CELL1 for screen3_USB_i2c_table
	static lv_style_t style_screen3_USB_i2c_table_cell1;
	lv_style_init(&style_screen3_USB_i2c_table_cell1);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_i2c_table_cell1
	lv_style_set_border_color(&style_screen3_USB_i2c_table_cell1, LV_STATE_DEFAULT, lv_color_make(0xd5, 0xde, 0xe6));
	lv_style_set_border_width(&style_screen3_USB_i2c_table_cell1, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen3_USB_i2c_table, LV_TABLE_PART_CELL1, &style_screen3_USB_i2c_table_cell1);
	lv_obj_set_pos(ui->screen3_USB_i2c_table, 24, 810);
	lv_table_set_col_cnt(ui->screen3_USB_i2c_table,5);
	lv_table_set_row_cnt(ui->screen3_USB_i2c_table,9);
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,0,0," ");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,1,0,"00");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,2,0,"10");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,3,0,"20");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,4,0,"30");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,5,0,"40");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,6,0,"50");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,7,0,"60");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,8,0,"70");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,0,1,"00:01:02:03");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,1,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,2,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,3,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,4,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,5,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,6,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,7,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,8,1,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,0,2,"04:05:06:07");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,1,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,2,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,3,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,4,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,5,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,6,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,7,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,8,2,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,0,3,"08:09:0A:0B");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,1,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,2,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,3,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,4,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,5,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,6,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,7,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,8,3,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,0,4,"0C:0D:0E:0F");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,1,4,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,2,4,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,3,4,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,4,4,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,5,4,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,6,4,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,7,4,"--:--:--:--");
	lv_table_set_cell_value(ui->screen3_USB_i2c_table,8,4,"--:--:--:--");
	lv_obj_set_style_local_pad_left(ui->screen3_USB_i2c_table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_right(ui->screen3_USB_i2c_table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_top(ui->screen3_USB_i2c_table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_pad_bottom(ui->screen3_USB_i2c_table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 0);

	//Write codes screen3_USB_input_area
	ui->screen3_USB_input_area = lv_textarea_create(ui->screen3_USB, NULL);

	//Write style LV_PAGE_PART_BG for screen3_USB_input_area
	static lv_style_t style_screen3_USB_input_area_bg;
	lv_style_init(&style_screen3_USB_input_area_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_input_area_bg
	lv_style_set_radius(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, lv_color_make(0x41, 0xc3, 0x63));
	lv_style_set_border_width(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_text_color(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, &lv_font_inconsolata_light_28);
	lv_style_set_text_letter_space(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_right(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_top(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_bottom(&style_screen3_USB_input_area_bg, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->screen3_USB_input_area, LV_PAGE_PART_BG, &style_screen3_USB_input_area_bg);

	//Write style LV_PAGE_PART_SCROLLABLE for screen3_USB_input_area
	static lv_style_t style_screen3_USB_input_area_scrollable;
	lv_style_init(&style_screen3_USB_input_area_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_input_area_scrollable
	lv_style_set_radius(&style_screen3_USB_input_area_scrollable, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_input_area_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_input_area_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_input_area_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_input_area_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_input_area, LV_PAGE_PART_SCROLLABLE, &style_screen3_USB_input_area_scrollable);

	//Write style LV_PAGE_PART_EDGE_FLASH for screen3_USB_input_area
	static lv_style_t style_screen3_USB_input_area_edge_flash;
	lv_style_init(&style_screen3_USB_input_area_edge_flash);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_input_area_edge_flash
	lv_style_set_radius(&style_screen3_USB_input_area_edge_flash, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_input_area_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_input_area_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_input_area_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_input_area_edge_flash, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_input_area, LV_PAGE_PART_EDGE_FLASH, &style_screen3_USB_input_area_edge_flash);
	lv_obj_set_pos(ui->screen3_USB_input_area, 20, 510);
	lv_obj_set_size(ui->screen3_USB_input_area, 680, 200);
	lv_textarea_set_text(ui->screen3_USB_input_area,"Press 'keyboard' or 'mouse' to capture HID input...");
	lv_obj_set_event_cb(ui->screen3_USB_input_area, text_area_event_cb);
	lv_textarea_set_text_align(ui->screen3_USB_input_area, LV_LABEL_ALIGN_LEFT);

	//Write codes screen3_USB_kbd_imgbtn
	ui->screen3_USB_kbd_imgbtn = lv_imgbtn_create(ui->screen3_USB, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen3_USB_kbd_imgbtn
	static lv_style_t style_screen3_USB_kbd_imgbtn_main;
	lv_style_init(&style_screen3_USB_kbd_imgbtn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_kbd_imgbtn_main
	lv_style_set_text_color(&style_screen3_USB_kbd_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_kbd_imgbtn_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_24);
	lv_style_set_image_recolor(&style_screen3_USB_kbd_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_kbd_imgbtn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen3_USB_kbd_imgbtn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_kbd_imgbtn, LV_IMGBTN_PART_MAIN, &style_screen3_USB_kbd_imgbtn_main);
	lv_obj_set_pos(ui->screen3_USB_kbd_imgbtn, 360, 451);
	lv_obj_set_size(ui->screen3_USB_kbd_imgbtn, 160, 50);
	lv_imgbtn_set_src(ui->screen3_USB_kbd_imgbtn,LV_BTN_STATE_RELEASED,&_button_alpha_160x50);
	lv_imgbtn_set_src(ui->screen3_USB_kbd_imgbtn,LV_BTN_STATE_PRESSED,&_button_on_alpha_160x50);
	lv_imgbtn_set_src(ui->screen3_USB_kbd_imgbtn,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_160x50);
	lv_imgbtn_set_src(ui->screen3_USB_kbd_imgbtn,LV_BTN_STATE_CHECKED_PRESSED,&_button_alpha_160x50);
	lv_imgbtn_set_checkable(ui->screen3_USB_kbd_imgbtn, true);
	ui->screen3_USB_kbd_imgbtn_label = lv_label_create(ui->screen3_USB_kbd_imgbtn, NULL);
	lv_label_set_text(ui->screen3_USB_kbd_imgbtn_label, "keyboard");

	//Write codes screen3_USB_mouse_imgbtn
	ui->screen3_USB_mouse_imgbtn = lv_imgbtn_create(ui->screen3_USB, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen3_USB_mouse_imgbtn
	static lv_style_t style_screen3_USB_mouse_imgbtn_main;
	lv_style_init(&style_screen3_USB_mouse_imgbtn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_mouse_imgbtn_main
	lv_style_set_text_color(&style_screen3_USB_mouse_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_mouse_imgbtn_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_24);
	lv_style_set_image_recolor(&style_screen3_USB_mouse_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_mouse_imgbtn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen3_USB_mouse_imgbtn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_mouse_imgbtn, LV_IMGBTN_PART_MAIN, &style_screen3_USB_mouse_imgbtn_main);
	lv_obj_set_pos(ui->screen3_USB_mouse_imgbtn, 530, 451);
	lv_obj_set_size(ui->screen3_USB_mouse_imgbtn, 160, 50);
	lv_imgbtn_set_src(ui->screen3_USB_mouse_imgbtn,LV_BTN_STATE_RELEASED,&_button_alpha_160x50);
	lv_imgbtn_set_src(ui->screen3_USB_mouse_imgbtn,LV_BTN_STATE_PRESSED,&_button_on_alpha_160x50);
	lv_imgbtn_set_src(ui->screen3_USB_mouse_imgbtn,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_160x50);
	lv_imgbtn_set_src(ui->screen3_USB_mouse_imgbtn,LV_BTN_STATE_CHECKED_PRESSED,&_button_alpha_160x50);
	lv_imgbtn_set_checkable(ui->screen3_USB_mouse_imgbtn, true);
	ui->screen3_USB_mouse_imgbtn_label = lv_label_create(ui->screen3_USB_mouse_imgbtn, NULL);
	lv_label_set_text(ui->screen3_USB_mouse_imgbtn_label, "mouse");

	//Write codes screen3_USB_i2c_scan_imgbtn
	ui->screen3_USB_i2c_scan_imgbtn = lv_imgbtn_create(ui->screen3_USB, NULL);

	//Write style LV_IMGBTN_PART_MAIN for screen3_USB_i2c_scan_imgbtn
	static lv_style_t style_screen3_USB_i2c_scan_imgbtn_main;
	lv_style_init(&style_screen3_USB_i2c_scan_imgbtn_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_i2c_scan_imgbtn_main
	lv_style_set_text_color(&style_screen3_USB_i2c_scan_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_i2c_scan_imgbtn_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_24);
	lv_style_set_image_recolor(&style_screen3_USB_i2c_scan_imgbtn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen3_USB_i2c_scan_imgbtn_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen3_USB_i2c_scan_imgbtn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen3_USB_i2c_scan_imgbtn, LV_IMGBTN_PART_MAIN, &style_screen3_USB_i2c_scan_imgbtn_main);
	lv_obj_set_pos(ui->screen3_USB_i2c_scan_imgbtn, 530, 751);
	lv_obj_set_size(ui->screen3_USB_i2c_scan_imgbtn, 160, 50);
	lv_imgbtn_set_src(ui->screen3_USB_i2c_scan_imgbtn,LV_BTN_STATE_RELEASED,&_button_alpha_160x50);
	lv_imgbtn_set_src(ui->screen3_USB_i2c_scan_imgbtn,LV_BTN_STATE_PRESSED,&_button_on_alpha_160x50);
	ui->screen3_USB_i2c_scan_imgbtn_label = lv_label_create(ui->screen3_USB_i2c_scan_imgbtn, NULL);
	lv_label_set_text(ui->screen3_USB_i2c_scan_imgbtn_label, "scan");

	//Write codes screen3_USB_font_label
	ui->screen3_USB_font_label = lv_label_create(ui->screen3_USB, NULL);
	lv_label_set_text(ui->screen3_USB_font_label, "");
	lv_label_set_long_mode(ui->screen3_USB_font_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen3_USB_font_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen3_USB_font_label
	static lv_style_t style_screen3_USB_font_label_main;
	lv_style_init(&style_screen3_USB_font_label_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_font_label_main
	lv_style_set_radius(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_letter_space(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen3_USB_font_label_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen3_USB_font_label, LV_LABEL_PART_MAIN, &style_screen3_USB_font_label_main);
	lv_obj_set_pos(ui->screen3_USB_font_label, 570, 131);
	lv_obj_set_size(ui->screen3_USB_font_label, 100, 0);

	//Write codes screen3_USB_i2c_ddlist
	ui->screen3_USB_i2c_ddlist = lv_dropdown_create(ui->screen3_USB, NULL);
	lv_dropdown_set_options(ui->screen3_USB_i2c_ddlist, "I2C2\nI2C3\nI2C5\nI2C6");
	lv_dropdown_set_max_height(ui->screen3_USB_i2c_ddlist, 270);

	//Write style LV_DROPDOWN_PART_MAIN for screen3_USB_i2c_ddlist
	static lv_style_t style_screen3_USB_i2c_ddlist_main;
	lv_style_init(&style_screen3_USB_i2c_ddlist_main);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_i2c_ddlist_main
	lv_style_set_radius(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0x41, 0xc3, 0x63));
	lv_style_set_border_width(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_24);
	lv_style_set_text_line_space(&style_screen3_USB_i2c_ddlist_main, LV_STATE_DEFAULT, 20);
	lv_obj_add_style(ui->screen3_USB_i2c_ddlist, LV_DROPDOWN_PART_MAIN, &style_screen3_USB_i2c_ddlist_main);

	//Write style LV_DROPDOWN_PART_SELECTED for screen3_USB_i2c_ddlist
	static lv_style_t style_screen3_USB_i2c_ddlist_selected;
	lv_style_init(&style_screen3_USB_i2c_ddlist_selected);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_i2c_ddlist_selected
	lv_style_set_radius(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen3_USB_i2c_ddlist_selected, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_24);
	lv_obj_add_style(ui->screen3_USB_i2c_ddlist, LV_DROPDOWN_PART_SELECTED, &style_screen3_USB_i2c_ddlist_selected);

	//Write style LV_DROPDOWN_PART_LIST for screen3_USB_i2c_ddlist
	static lv_style_t style_screen3_USB_i2c_ddlist_list;
	lv_style_init(&style_screen3_USB_i2c_ddlist_list);

	//Write style state: LV_STATE_DEFAULT for style_screen3_USB_i2c_ddlist_list
	lv_style_set_radius(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen3_USB_i2c_ddlist_list, LV_STATE_DEFAULT, &lv_font_OpenSans_Regular_24);
	lv_obj_add_style(ui->screen3_USB_i2c_ddlist, LV_DROPDOWN_PART_LIST, &style_screen3_USB_i2c_ddlist_list);
	lv_obj_set_pos(ui->screen3_USB_i2c_ddlist, 380, 755);
	lv_obj_set_width(ui->screen3_USB_i2c_ddlist, 120);

	//Init events for screen
	events_init_screen3_USB(ui);
}
