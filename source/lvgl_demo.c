
#include "gui_guider.h"
#include "littlevgl_support.h"
#include "lvgl.h"
#include "events_init.h"

#include "demo_common.h"
#include "audio_demo.h"
#include "lvgl_demo.h"
#include "network_demo.h"
#include "usb_peripherals.h"
#include "expansion_i2c.h"
#include "globals.h"
#include "host_mouse.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _activePage
{
    PAGE_NONE       = -1,
    PAGE_MENU       = 0,
    PAGE_LED        = 1,
    PAGE_NETWORK    = 2,
    PAGE_USB        = 3,
    PAGE_AV         = 4,
    PAGE_CUSTOM     = 5,
    PAGE_HELP       = 6,
} activePage;

#define MIC_GRAPH_POINTS 50
#define MIC_GRAPH_MIDDLE_POINT 50

#define CUSTOM_GRAPH_POINTS 50
#define CUSTOM_GRAPH_BASE_POINT 0
#define CUSTOM_GRAPH_REFRESH_INTERVAL 10

/*******************************************************************************
 * Variables
 ******************************************************************************/

static volatile bool s_lvgl_initialized = false;
static volatile activePage s_active_page = PAGE_NONE;

lv_ui guider_ui;

static bool s_lgvl_ready = false;

static void (*s_page_refresh)(void) = NULL;

static bool s_hid_list_refresh_required = true;

static i2cBus s_i2c_bus = I2C2;
//static LPI2C_Type *s_i2c_bus_type = NULL;
static lpi2c_rtos_handle_t *s_i2c_bus_handle = NULL;
static uint8_t s_i2c_scanned_nodes[16];

static char s_text_area_buffer[100];
static volatile char s_text_area_buffer_offset = 0;
static bool s_capture_mouse_input = false;
static bool s_capture_keyboard_input = false;

static bool s_ssid_scanning_label_visible = true;

static lv_chart_series_t *s_mic_1_series = NULL;
static lv_chart_series_t *s_mic_2_series = NULL;
static lv_chart_series_t *s_mic_3_series = NULL;
static lv_chart_series_t *s_mic_4_series = NULL;

static volatile lv_coord_t s_mic_1_buffer[MIC_GRAPH_POINTS];
static volatile lv_coord_t s_mic_2_buffer[MIC_GRAPH_POINTS];
static volatile lv_coord_t s_mic_3_buffer[MIC_GRAPH_POINTS];
static volatile lv_coord_t s_mic_4_buffer[MIC_GRAPH_POINTS];

static int s_mic_1_buffer_count = 0;
static int s_mic_2_buffer_count = 0;
static int s_mic_3_buffer_count = 0;
static int s_mic_4_buffer_count = 0;

static bool s_mic_1_series_visible = false;
static bool s_mic_2_series_visible = false;
static bool s_mic_3_series_visible = false;
static bool s_mic_4_series_visible = false;
static uint8_t audio_channels[2];
static bool *mic_states[4] = {&s_mic_1_series_visible, &s_mic_2_series_visible, &s_mic_3_series_visible, &s_mic_4_series_visible};

static int s_enabled_mic_count = 0;

static lv_chart_series_t *s_custom_series = NULL;
static int s_custom_graph_refresh_count = 0;

/************************ FAT LOGIC ************************/
#if defined(__FAT_BUILD__)
#define LED_DELAY_SLOW		0x20
#define LED_DELAY_FAST		0x8

static uint16_t delay = LED_DELAY_FAST;
#endif

//ethernet
extern ip_ro_t eth_100mb_addr;
extern ip_ro_t eth_1g_addr;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void ethernet_change_state_gui(ip_ro_t *eth_instance, lv_obj_t *screen2_WIFI_eth_item);

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*!
 * @brief adds item to lvgl list
 */
void addItemToList(lv_obj_t * obj, const char * text)
{
	static lv_style_t list_child_style;
	lv_style_init(&list_child_style);

	lv_style_set_radius(&list_child_style, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&list_child_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&list_child_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&list_child_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&list_child_style, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&list_child_style, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&list_child_style, LV_STATE_DEFAULT, &lv_font_OpenSans_Light_28);

	lv_obj_t *list_btn;
	list_btn = lv_list_add_btn(obj, NULL, text);
	lv_obj_add_style(list_btn, LV_BTN_PART_MAIN, &list_child_style);
}

/*!
 * @brief set i2c bus to scan
 */
void setI2cBus(i2cBus bus)
{
    s_i2c_bus = bus;

    switch (s_i2c_bus)
    {
    case I2C2:
    	s_i2c_bus_handle = select_i2c_bus(2);
        break;
    case I2C3:
    	s_i2c_bus_handle = select_i2c_bus(3);
        break;
    case I2C5:
    	s_i2c_bus_handle = select_i2c_bus(5);
        break;
    case I2C6:
    	s_i2c_bus_handle = select_i2c_bus(6);
        break;
    default:
        PRINTF("Unsupported bus selection: %d", s_i2c_bus);
        break;
    }

    scani2cBusAndDisplay();
}

/*!
 * @brief add scanned i2c nodes to table
 */
void scani2cBusAndDisplay(void)
{
    char buffer[12];

    if (s_active_page != PAGE_USB)
    {
        return;
    }

    scan_i2c_bus(s_i2c_bus_handle, s_i2c_scanned_nodes);

    for (uint16_t row = 1; row < 9; row++)
    {
        uint16_t col = 1;

        for (int i2caddress = 0; i2caddress < 0x10; i2caddress++)
        {
            uint8_t curr_node = ((row - 1) * 16) + i2caddress;
            uint8_t index = curr_node / 8;
            uint8_t bit_pos = 7 - (curr_node % 8);
            uint8_t offset = (i2caddress % 4);
            uint8_t bufferOffset = offset * 3;

            if (s_i2c_scanned_nodes[index] & (1 << bit_pos))
            {
                sprintf(buffer + bufferOffset, "%02X", curr_node);
            } 
            else
            {
                sprintf(buffer + bufferOffset, "--");
            }

            if (offset < 3)
            {
                sprintf(buffer + bufferOffset + 2, ":");
            }
            else
            {
	            lv_table_set_cell_value(guider_ui.screen3_USB_i2c_table, row, col, buffer);
                col++;
            }
        }
    }
}

/*!
 * @brief send text to the HID input test text area
 */
void writeToHIDInputTextArea(const char* text)
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }

    taskENTER_CRITICAL();

    s_text_area_buffer_offset += sprintf(s_text_area_buffer + s_text_area_buffer_offset, text);

    taskEXIT_CRITICAL();
}

/*!
 * @brief delete character from the left of the current cursor
 */
void deleteLeftCharTextArea()
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }

    taskENTER_CRITICAL();
	lv_textarea_del_char(guider_ui.screen3_USB_input_area);
    taskEXIT_CRITICAL();
}

/*!
 * @brief clear the HID input test text area buffer
 */
void clearTextAreaBuffer()
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }

    taskENTER_CRITICAL();

    s_text_area_buffer[0] = '\0';
    s_text_area_buffer_offset = 0;

    taskEXIT_CRITICAL();
}

/*!
 * @brief clear the HID input test text area
 */
void clearTextArea()
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }
    
    lv_textarea_set_text(guider_ui.screen3_USB_input_area, "");
}

/*!
 * @brief check if mouse input is being captured by HID input text area
 */
bool capturingMouseInputOnTA(void)
{
    if (s_active_page != PAGE_USB)
    {
        return false;
    }

    return s_capture_mouse_input;
}

/*!
 * @brief set text area to capture mouse input
 */
void setCaptureMouseInputOnTA(bool state)
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }

    s_capture_mouse_input = state;

    if (state)
    {
        s_capture_keyboard_input = false;

        lv_btn_set_state(guider_ui.screen3_USB_kbd_imgbtn, LV_BTN_STATE_RELEASED);

        clearTextAreaBuffer();
        clearTextArea();
    }
}

/*!
 * @brief check if keyboard input is being captured by HID input text area
 */
bool capturingKeyboardInputOnTA(void)
{
    if (s_active_page != PAGE_USB)
    {
        return false;
    }

    return s_capture_keyboard_input;
}

/*!
 * @brief set text area to capture keyboard input
 */
void setCaptureKeyboardInputOnTA(bool state)
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }

    s_capture_keyboard_input = state;

    if (state)
    {
        s_capture_mouse_input = false;

        lv_btn_set_state(guider_ui.screen3_USB_mouse_imgbtn, LV_BTN_STATE_RELEASED);

        clearTextAreaBuffer();
        clearTextArea();
    }
}

/*!
 * @brief refresh the HID input test text area
 */
void refreshTextArea()
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }

    taskENTER_CRITICAL();

    if (s_text_area_buffer[0] != '\0')
    {
        lv_textarea_add_text(guider_ui.screen3_USB_input_area, s_text_area_buffer);
        s_text_area_buffer[0] = '\0';
        s_text_area_buffer_offset = 0;
    }

    taskEXIT_CRITICAL();
}

/*!
 * @brief updates the list of HID devices in the USB page.
 */
void refreshHIDList(void)
{
    if (s_active_page != PAGE_USB)
    {
        return;
    }

    if (!s_hid_list_refresh_required)
        return;

    lv_list_clean(guider_ui.screen3_USB_usb_list);

    char buffer[100];

    /* get the head node of the mouse list */
    usb_host_mouse_instance_t *curr_mouse_inst;
    curr_mouse_inst = (usb_host_mouse_instance_t *)USB_getMouseInstanceHead();

    uint32_t pid_t, vid_t, address_t;

    while(curr_mouse_inst != NULL)
    {
    	USB_HostHelperGetPeripheralInformation(curr_mouse_inst->deviceHandle, kUSB_HostGetDevicePID, &pid_t);
    	USB_HostHelperGetPeripheralInformation(curr_mouse_inst->deviceHandle, kUSB_HostGetDeviceVID, &vid_t);
    	USB_HostHelperGetPeripheralInformation(curr_mouse_inst->deviceHandle, kUSB_HostGetDeviceAddress, &address_t);
    	sprintf(buffer, "hid mouse: pid=0x%x vid=0x%x addr=%d",
    			pid_t, vid_t, address_t);
    	addItemToList(guider_ui.screen3_USB_usb_list, buffer);
    	curr_mouse_inst = curr_mouse_inst->next;
    }

    /* currently one keyboard is supported at the moment. must introduce linked list in host_keyboard.c */
    if (usb_devices[1].deviceExist) {
    	sprintf(buffer, "hid keyboard: pid=0x%x vid=0x%x addr=%d",
        		usb_devices[1].devicePid, usb_devices[1].deviceVid, usb_devices[1].address);
        addItemToList(guider_ui.screen3_USB_usb_list, buffer); 
    }

    s_hid_list_refresh_required = false;
}

/*!
 * @brief refreshes the USB page.
 */
void refreshUSBPage(void)
{
    refreshHIDList();
    refreshTextArea();
}

/*!
 * @brief adds item to the list of SSIDs
 */
void addItemToSSIDList(const char * text)
{
    if (s_active_page != PAGE_NETWORK)
    {
        return;
    }

    if (s_ssid_scanning_label_visible)
    {
	    lv_obj_set_hidden(guider_ui.screen2_WIFI_ssid_scan_label, true);
        s_ssid_scanning_label_visible = false;
    }

	addItemToList(guider_ui.screen2_WIFI_ssid_list, text);
}

void setLedRedImgState(bool state)
{
    if (s_active_page != PAGE_LED)
    {
        return;
    }

    lv_obj_set_hidden(guider_ui.screen1_LEDs_led_red_off, state);
}

void setLedGreenImgState(bool state)
{
    if (s_active_page != PAGE_LED)
    {
        return;
    }

    lv_obj_set_hidden(guider_ui.screen1_LEDs_led_green_off, state);
}

void setLedBlueImgState(bool state)
{
    if (s_active_page != PAGE_LED)
    {
        return;
    }

    lv_obj_set_hidden(guider_ui.screen1_LEDs_led_blue_off, state);
}

/*!
* @brief Init color LEDs
*/
void initDefaultPageInteractions()
{
    initLEDs();

    s_page_refresh = NULL;
}

/*!
* @brief starts an ssid scan
*/
void startSSIDScan()
{
    lv_list_clean(guider_ui.screen2_WIFI_ssid_list);
    
    lv_obj_set_hidden(guider_ui.screen2_WIFI_ssid_scan_label, false);
    s_ssid_scanning_label_visible = true;

    ssidScan();
}

/*!
* @brief changes the network image and label
*/
static void ethernet_change_state_gui(ip_ro_t *eth_instance, lv_obj_t *screen2_WIFI_eth_item)
{
	uint8_t temp_buff[128];
	int length = 0;
	length = sprintf(temp_buff+length, "Eth %s : %s", eth_instance->eth==0?"100Mb":"1Gb", eth_instance->connected==true?"Connected, ":"Disconnected ");

	if (eth_instance->connected)
	{
		length += sprintf(temp_buff+length, "ip : %d.%d.%d.%d ",
					(uint8_t)((eth_instance->ip)), (uint8_t)((eth_instance->ip)>>8),
					(uint8_t)((eth_instance->ip)>>16), (uint8_t)((eth_instance->ip)>>24));
		length += sprintf(temp_buff+length, "sub : %d.%d.%d.%d ",
				(uint8_t)((eth_instance->sub)), (uint8_t)((eth_instance->sub)>>8),
				(uint8_t)((eth_instance->sub)>>16), (uint8_t)((eth_instance->sub)>>24));
		length += sprintf(temp_buff+length, "gw : %d.%d.%d.%d",
				(uint8_t)((eth_instance->gw)), (uint8_t)((eth_instance->gw)>>8),
				(uint8_t)((eth_instance->gw)>>16), (uint8_t)((eth_instance->gw)>>24));
	}

	if (screen2_WIFI_eth_item!=NULL)
	{
		if (eth_instance->connected)
		{
			lv_img_set_src(lv_list_get_btn_img(screen2_WIFI_eth_item), &_eth_connect_40x40);
		}
		else
		{
			lv_img_set_src(lv_list_get_btn_img(screen2_WIFI_eth_item), &_eth_disconnect_40x40);
		}
		lv_label_set_text(lv_list_get_btn_label(screen2_WIFI_eth_item), temp_buff);
	}
}

/*!
* @brief detects ethernet interface UP/DOWN event.
*/
static void refreshNetworkPage()
{
	static bool eth_100mb_last = false;
	static bool eth_1Gb_last = false;
	lv_obj_t *screen2_WIFI_list_1_btn;
    if (s_active_page != PAGE_NETWORK)
    {
        return;
    }

    if (eth_100mb_last != eth_100mb_addr.connected)
    {
    	screen2_WIFI_list_1_btn = lv_list_get_next_btn(guider_ui.screen2_WIFI_eth_list, NULL);
		ethernet_change_state_gui(&eth_100mb_addr, screen2_WIFI_list_1_btn);
		eth_100mb_last = eth_100mb_addr.connected;
    }

    if (eth_1Gb_last != eth_1g_addr.connected)
    {
    	screen2_WIFI_list_1_btn = lv_list_get_next_btn(guider_ui.screen2_WIFI_eth_list, NULL);
    	if (screen2_WIFI_list_1_btn)
    	{
    		screen2_WIFI_list_1_btn = lv_list_get_next_btn(guider_ui.screen2_WIFI_eth_list, screen2_WIFI_list_1_btn);
    		ethernet_change_state_gui(&eth_1g_addr, screen2_WIFI_list_1_btn);
    		eth_1Gb_last = eth_1g_addr.connected;
    	}
    }
}

/*!
* @brief Opens the network screen
*/
void openNetworkScreen()
{
    setup_scr_screen2_WIFI(&guider_ui);
    lv_scr_load_anim(guider_ui.screen2_WIFI, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    s_active_page = PAGE_NETWORK;
    initDefaultPageInteractions();

    // load the ethernet status information first time when page loaded
	lv_obj_t *screen2_WIFI_list_1_btn;
	screen2_WIFI_list_1_btn = lv_list_get_next_btn(guider_ui.screen2_WIFI_eth_list, NULL);
	ethernet_change_state_gui(&eth_100mb_addr, screen2_WIFI_list_1_btn);

	screen2_WIFI_list_1_btn = lv_list_get_next_btn(guider_ui.screen2_WIFI_eth_list, NULL);
	if (screen2_WIFI_list_1_btn)
	{
		screen2_WIFI_list_1_btn = lv_list_get_next_btn(guider_ui.screen2_WIFI_eth_list, screen2_WIFI_list_1_btn);
		ethernet_change_state_gui(&eth_1g_addr, screen2_WIFI_list_1_btn);
	}

    s_page_refresh = &refreshNetworkPage;
    startSSIDScan();
}

/*!
* @brief Opens the menu screen
*/
void openMenuScreen()
{
    setup_scr_screen0_MENU(&guider_ui);
    lv_scr_load_anim(guider_ui.screen0_MENU, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    s_active_page = PAGE_MENU;

    initDefaultPageInteractions();
}

/*!
* @brief Opens the LED screen
*/
void openLEDScreen()
{
    setup_scr_screen1_LEDs(&guider_ui);
    lv_scr_load_anim(guider_ui.screen1_LEDs, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    s_active_page = PAGE_LED;

    initDefaultPageInteractions();
}

/*!
* @brief Opens the USB screen
*/
void openUSBScreen()
{
    setup_scr_screen3_USB(&guider_ui);
    lv_scr_load_anim(guider_ui.screen3_USB, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    s_active_page = PAGE_USB;

    clearTextAreaBuffer();
    s_capture_mouse_input = false;
    s_capture_keyboard_input = false;

    initDefaultPageInteractions();

    s_page_refresh = &refreshUSBPage;

    s_hid_list_refresh_required = true;

    s_i2c_bus_handle = select_i2c_bus(2);
    scani2cBusAndDisplay();
}

/*!
* @brief Initializes microphone graph 
*/
void initMicGraph()
{
    lv_chart_set_point_count(guider_ui.screen4_AV_mic_chart, MIC_GRAPH_POINTS);

    s_mic_1_buffer_count = 0;
    s_mic_2_buffer_count = 0;
    s_mic_3_buffer_count = 0;
    s_mic_4_buffer_count = 0;

	s_mic_1_series = lv_chart_add_series(guider_ui.screen4_AV_mic_chart, LV_COLOR_RED);
	s_mic_2_series = lv_chart_add_series(guider_ui.screen4_AV_mic_chart, LV_COLOR_YELLOW);
	s_mic_3_series = lv_chart_add_series(guider_ui.screen4_AV_mic_chart, LV_COLOR_BLUE);
	s_mic_4_series = lv_chart_add_series(guider_ui.screen4_AV_mic_chart, LV_COLOR_CYAN);

	s_mic_1_series_visible = false;
	s_mic_2_series_visible = false;
	s_mic_3_series_visible = false;
	s_mic_4_series_visible = false;

	audio_channels[0] = 0;
	audio_channels[1] = 0;

    lv_chart_refresh(guider_ui.screen4_AV_mic_chart);
}

/*!
* @brief Initializes custom graph 
*/
void initCustomGraph()
{
    lv_chart_set_point_count(guider_ui.screen5_SYSTEM_custom_chart, CUSTOM_GRAPH_POINTS);

    s_custom_series = lv_chart_add_series(guider_ui.screen5_SYSTEM_custom_chart, LV_COLOR_RED);
    lv_chart_init_points(guider_ui.screen5_SYSTEM_custom_chart, s_custom_series, CUSTOM_GRAPH_BASE_POINT);

    lv_chart_refresh(guider_ui.screen5_SYSTEM_custom_chart);
}

/*!
 * @brief enable or disable inactive mic checkboxes.
 */
void enableInactiveMicCheckboxes(bool state)
{
    if (s_active_page != PAGE_AV)
    {
        return;
    }
    
    if (!s_mic_1_series_visible)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.screen4_AV_mic1_cb, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.screen4_AV_mic1_cb, LV_BTN_STATE_DISABLED);
        }
    }
    
    if (!s_mic_2_series_visible)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.screen4_AV_mic2_cb, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.screen4_AV_mic2_cb, LV_BTN_STATE_DISABLED);
        }
    }
    
    if (!s_mic_3_series_visible)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.screen4_AV_mic3_cb, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.screen4_AV_mic3_cb, LV_BTN_STATE_DISABLED);
        }
    }
    
    if (!s_mic_4_series_visible)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.screen4_AV_mic4_cb, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.screen4_AV_mic4_cb, LV_BTN_STATE_DISABLED);
        }
    }
}

/*!
 * @brief enable microphone.
 */
void enableMic(int mic, bool state)
{
    if (s_active_page != PAGE_AV)
    {
        return;
    }

    switch (mic)
    {
        case 1:
            s_mic_1_series_visible = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.screen4_AV_mic_chart, s_mic_1_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_1_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.screen4_AV_mic_chart, s_mic_1_series);
                s_mic_1_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(0, state);

            break;
        case 2:
            s_mic_2_series_visible = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.screen4_AV_mic_chart, s_mic_2_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_2_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.screen4_AV_mic_chart, s_mic_2_series);
                s_mic_2_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(1, state);

            break;
        case 3:
            s_mic_3_series_visible = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.screen4_AV_mic_chart, s_mic_3_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_3_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.screen4_AV_mic_chart, s_mic_3_series);
                s_mic_3_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(2, state);

            break;
        case 4:
            s_mic_4_series_visible = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.screen4_AV_mic_chart, s_mic_4_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_4_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.screen4_AV_mic_chart, s_mic_4_series);
                s_mic_4_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(3, state);

            break;
        default:
            PRINTF("Error: Invalid mic index: %d.\r\n", mic);
    }
	uint8_t *temp = getEnabledChannels();
	audio_channels[0] = *(temp++);
	audio_channels[1] = *(temp);
    enableInactiveMicCheckboxes(s_enabled_mic_count < 2);
}

/*!
 * @brief adds data to display on microphone graph.
 */
void addMicData(int mic, int16_t value)
{
    if (s_active_page != PAGE_AV)
    {
        return;
    }

    if (value > 100) 
        value = 100;
    else if (value < 0) 
        value = 0;

    taskENTER_CRITICAL();

    switch (mic)
    {
        case 1:
            if (s_mic_1_series_visible && (s_mic_1_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_1_buffer[s_mic_1_buffer_count] = value;
                s_mic_1_buffer_count++;
            }
            break;
        case 2:
            if (s_mic_2_series_visible && (s_mic_2_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_2_buffer[s_mic_2_buffer_count] = value;
                s_mic_2_buffer_count++;
            }
            break;
        case 3:
            if (s_mic_3_series_visible && (s_mic_3_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_3_buffer[s_mic_3_buffer_count] = value;
                s_mic_3_buffer_count++;
            }
            break;
        case 4:
            if (s_mic_4_series_visible && (s_mic_4_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_4_buffer[s_mic_4_buffer_count] = value;
                s_mic_4_buffer_count++;
            }
            break;
        default:
            PRINTF("Error: Invalid mic index: %d.\r\n", mic);
    }

    taskEXIT_CRITICAL();
}

/*!
 * @brief refreshes the microphone graph.
 */
void refreshMicGraph(void)
{
    int i;

    if (s_active_page != PAGE_AV)
    {
        return;
    }

    taskENTER_CRITICAL();

    // update mic 1 graph
    for (i = 0; i < s_mic_1_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.screen4_AV_mic_chart, s_mic_1_series, s_mic_1_buffer[i]);
    }
    s_mic_1_buffer_count = 0;

    // update mic 2 graph
    for (i = 0; i < s_mic_2_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.screen4_AV_mic_chart, s_mic_2_series, s_mic_2_buffer[i]);
    }
    s_mic_2_buffer_count = 0;

    // update mic 3 graph
    for (i = 0; i < s_mic_3_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.screen4_AV_mic_chart, s_mic_3_series, s_mic_3_buffer[i]);
    }
    s_mic_3_buffer_count = 0;

    // update mic 4 graph
    for (i = 0; i < s_mic_4_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.screen4_AV_mic_chart, s_mic_4_series, s_mic_4_buffer[i]);
    }
    s_mic_4_buffer_count = 0;

    taskEXIT_CRITICAL();
    
    lv_chart_refresh(guider_ui.screen4_AV_mic_chart);
}

/*!
 * @brief connect to selected AP.
 */
void connectToSelectedAP(void)
{
    connectToAP();
    
    taskENTER_CRITICAL();

    lv_label_set_text(guider_ui.screen5_SYSTEM_instructions_label, "Connecting...");

    taskEXIT_CRITICAL();
}

/*!
 * @brief handles a succesful connection to an AP.
 */
void notifyConnectedToAP(void)
{
    if (s_active_page != PAGE_CUSTOM)
    {
        return;
    }

    char ssid[80];
    getTargetSSID(ssid, 80);
    
    taskENTER_CRITICAL();

    char labelText[180];
    sprintf(labelText, "Connected to '%s'.", ssid);
    lv_label_set_text(guider_ui.screen5_SYSTEM_instructions_label, labelText);

    taskEXIT_CRITICAL();
}

/*!
 * @brief set the custom value background color.
 */
void setCustomValueBgColor(lv_color_t color)
{
	//Write style LV_LABEL_PART_MAIN for screen5_SYSTEM_custom_value_label
	static lv_style_t style_screen5_SYSTEM_custom_value_label_main;
	lv_style_init(&style_screen5_SYSTEM_custom_value_label_main);

	lv_style_set_bg_color(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, color);
	lv_style_set_bg_grad_color(&style_screen5_SYSTEM_custom_value_label_main, LV_STATE_DEFAULT, color);
	lv_obj_add_style(guider_ui.screen5_SYSTEM_custom_value_label, LV_LABEL_PART_MAIN, &style_screen5_SYSTEM_custom_value_label_main);
}

/*!
 * @brief set the custom value.
 */
void setCustomValue(short value)
{
    char valueText[180];
    sprintf(valueText, "%ddBm", value);
    lv_label_set_text(guider_ui.screen5_SYSTEM_custom_value_label, valueText);

    if (value < -100)
    {
        setCustomValueBgColor(lv_color_make(0xff, 0x00, 0x00));
    }
    else if (value < -85)
    {
        setCustomValueBgColor(lv_color_make(0xff, 0x88, 0x00));
    }
    else if (value < -70)
    {
        setCustomValueBgColor(lv_color_make(0xff, 0xff, 0x00));
    }
    else if (value >= -70)
    {
        setCustomValueBgColor(lv_color_make(0x00, 0xff, 0x00));
    }
}

/*!
 * @brief refreshes the custom graph.
 */
void refreshCustomGraph(void)
{
    if (s_active_page != PAGE_CUSTOM)
    {
        return;
    }

    if (s_custom_graph_refresh_count == 0)
    {
        short rssi;

        if (getCurrentSignalStrength(&rssi) == 0)
        {
            int value = 100 + rssi;

            if (value > 100) value = 100;
            else if (value < 0) value = 0;

            // PRINTF("RSSI: %d scaled: %d\r\n", rssi, value);

            lv_chart_set_next(guider_ui.screen5_SYSTEM_custom_chart, s_custom_series, value);

            setCustomValue(rssi);
        }
    }

    s_custom_graph_refresh_count = 
        (++s_custom_graph_refresh_count) % CUSTOM_GRAPH_REFRESH_INTERVAL;
    
    lv_chart_refresh(guider_ui.screen5_SYSTEM_custom_chart);
}


static void sync_enabled_mic()
{
	// check if different mics are enabled from console
	uint8_t *temp = getEnabledChannels();
	uint8_t left_channel = *(temp++);
	uint8_t right_channel = *(temp);

	if (audio_channels[0] != left_channel || audio_channels[1] != right_channel)
	{
		int temp;
		s_mic_1_series_visible = false;
		s_mic_2_series_visible = false;
		s_mic_3_series_visible = false;
		s_mic_4_series_visible = false;

		if (left_channel != 0)
		{
			*mic_states[left_channel-1] = true;
		}
		if (right_channel != 0)
		{
			*mic_states[right_channel-1] = true;
		}

		for (int i=0; i<4; i++)
		{
			if (*mic_states[i]==false)
			{
				enableMic(i+1, *mic_states[i]);
			}
		}
		for (int i=0; i<4; i++)
		{
			switch(i)
			{
				case 0:
					lv_checkbox_set_state(guider_ui.screen4_AV_mic1_cb, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				case 1:
					lv_checkbox_set_state(guider_ui.screen4_AV_mic2_cb, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				case 2:
					lv_checkbox_set_state(guider_ui.screen4_AV_mic3_cb, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				case 3:
					lv_checkbox_set_state(guider_ui.screen4_AV_mic4_cb, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				default:
					break;
			}
		}

		s_enabled_mic_count = 0;
		for (int i=0; i<4; i++)
		{
			if (*mic_states[i])
			{
				enableMic(i+1, *mic_states[i]);
			}
		}
		audio_channels[0] = left_channel;
		audio_channels[1] = right_channel;
	}
}
/*!
 * @brief refreshes the A/V page.
 */
void refreshAVPage(void)
{
	sync_enabled_mic();
	refreshMicGraph();
}

/*!
* @brief Opens the A/V screen
*/
void openAVScreen()
{
    setup_scr_screen4_AV(&guider_ui);
    lv_scr_load_anim(guider_ui.screen4_AV, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    s_active_page = PAGE_AV;

    initDefaultPageInteractions();

    initMicGraph();

    s_page_refresh = &refreshAVPage;
}

/*!
 * @brief refreshes the System page.
 */
void refreshCustomPage(void)
{
    refreshCustomGraph();
}

/*!
* @brief Opens the System screen
*/
void openCustomScreen()
{
    setup_scr_screen5_SYSTEM(&guider_ui);
    lv_scr_load_anim(guider_ui.screen5_SYSTEM, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    s_active_page = PAGE_CUSTOM;

    initDefaultPageInteractions();

    char ssid[80];
    getTargetSSID(ssid, 80);
    
    taskENTER_CRITICAL();

    char labelText[180];
    sprintf(labelText, "Click 'connect' to connect to '%s' and measure it's RSSI.", ssid);
    lv_label_set_text(guider_ui.screen5_SYSTEM_instructions_label, labelText);

    taskEXIT_CRITICAL();

    initCustomGraph();

#ifdef WIFI_EN
    s_page_refresh = &refreshCustomPage;
#endif
}

/*!
* @brief Opens the Help screen
*/
void openHelpScreen()
{
    setup_scr_screen6_HELP(&guider_ui);
    lv_scr_load_anim(guider_ui.screen6_HELP, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    s_active_page = PAGE_HELP;

    initDefaultPageInteractions();

    char labelText[80];
    sprintf(labelText, MAAXBOARD_VERSION_STRING);
    lv_label_set_text(guider_ui.screen6_HELP_maaxboard_version_label, labelText);
}

/*!
 * @brief FreeRTOS tick hook.
 */
void vApplicationTickHook_lvgl(void)
{
    if (s_lvgl_initialized)
    {
        lv_tick_inc(1);
    }
}

/*!
 * @brief returns 'true' if lvgl task has been properly initialized.
 */
bool isLvglReady(void)
{
    return s_lgvl_ready;
}

/*!
 * @brief indicate that array of connected HIDs has been refreshed.
 */
void setHIDsRefreshed(void)
{
    s_hid_list_refresh_required = true;
}

/*******************************************************************************
 * Freertos Task: lvgl
 * @brief - There are total 6 pages, task handles all gui object events, navigation
 ******************************************************************************/
void lvgl_task(void *param)
{
    lv_port_pre_init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    s_lvgl_initialized = true;

    setup_ui(&guider_ui);
    events_init(&guider_ui);

    s_lgvl_ready = true;

	set_red_led(false);
	set_green_led(false);
#if defined(__FAT_BUILD__)
    static uint16_t counter = 0;
    static uint8_t nextLED = 1;

	set_blue_led(true);
#else
	set_blue_led(false);
#endif
    s_page_refresh = NULL;

    openMenuScreen();

    for (;;)
    {
#if defined(__FAT_BUILD__)
		/************************ FAT LOGIC ************************/
		/* Constantly cycle through the RGB led colors */
		if (getInputSignal())
        {
        	/* Toggle RGB cycle speed every time the user button is pressed */
        	if(delay == LED_DELAY_SLOW)
        		delay = LED_DELAY_FAST;
        	else
        		delay = LED_DELAY_SLOW;

        	setInputSignal(false);
        }

		if(counter >= delay)
		{
			set_red_led(nextLED & 0x01?true:false);
			set_green_led(nextLED & 0x02?true:false);
			set_blue_led(nextLED & 0x04?true:false);
			counter = 0;
			nextLED <<= 1;
			if(nextLED > 4) nextLED = 1;
		}
		else counter++;

        if (s_page_refresh != NULL)
        {
            (*s_page_refresh)();
        }
#else
        if (getInputSignal())
        {
            switch (s_active_page)
            {
                case PAGE_LED:
                    openNetworkScreen();
                    break;
                
                case PAGE_NETWORK:
                    openUSBScreen();
                    break;
                
                case PAGE_USB:
                    openAVScreen();
                    break;
                
                case PAGE_AV:
                    openCustomScreen();
                    break;
                
                case PAGE_CUSTOM:
                    openHelpScreen();
                    break;

                case PAGE_NONE:
                case PAGE_HELP:
                    openMenuScreen();
                    break;

                case PAGE_MENU:
                    openLEDScreen();
                    break;
            }

            setInputSignal(false);
        }

        if (s_page_refresh != NULL)
        {
            (*s_page_refresh)();
        }
#endif
        lv_task_handler();
        vTaskDelay(5);
    }
}
