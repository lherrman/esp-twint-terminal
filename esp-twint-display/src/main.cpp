#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Wire.h>

#include "qrdata.h"

// TFT Display
static const uint16_t screen_width = 320;
static const uint16_t screen_height = 480;
TFT_eSPI tft = TFT_eSPI(screen_width, screen_height); /* TFT instance */

// LVGL Objects
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screen_width * 10];

static lv_style_t style_price;
static lv_style_t style_store;
static lv_style_t style_screen;
static lv_style_t style_logo;
static lv_style_t style_qr;

static lv_obj_t *qr;
static lv_obj_t *price_label;
static lv_obj_t *store_label;
static lv_obj_t *img_logo;

LV_IMG_DECLARE(logo_small);
LV_IMG_DECLARE(logo_large);

// Colors
static lv_color_t color_bg_light = lv_color_hex(0xFFFFFF);
static lv_color_t color_fg_light = lv_color_hex(0x000000);
static lv_color_t color_bg_dark = lv_color_hex(0x000000);
static lv_color_t color_fg_dark = lv_color_hex(0xFFFFFF);

// Variables
float next_price = -1;
float current_price = -1;
int setting_show_default_qr_code = 0;
int setting_show_default_qr_code_old = 0;
int setting_dark_mode = 1;
int setting_dark_mode_old = 1;

// Parameters
int qr_code_size = 250;
int qr_code_offset_top = 85;


void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void init_lv_objects()
{
    // Styles
    lv_style_init(&style_price);
    lv_style_set_text_font(&style_price, &lv_font_montserrat_32);
    lv_style_set_text_color(&style_price, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_color(&style_price, lv_color_hex(0x1156a5));
    lv_style_set_pad_all(&style_price, 10);
    lv_style_set_bg_opa(&style_price, LV_OPA_100);

    lv_style_init(&style_store);
    lv_style_set_text_font(&style_store, &lv_font_montserrat_20);
    lv_style_set_text_color(&style_store, color_fg_light);

    lv_style_init(&style_logo);
    lv_style_set_clip_corner(&style_logo, true);
    lv_style_set_radius(&style_logo, 5);

    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, color_bg_light);

    lv_style_init(&style_qr);
    lv_style_set_border_opa(&style_qr, LV_OPA_0);

    // Screen
    lv_obj_add_style(lv_scr_act(), &style_screen, 0);

    // QR Code
    qr = lv_qrcode_create(lv_scr_act(), qr_code_size, color_fg_light, color_bg_light);
    lv_obj_align(qr, LV_ALIGN_TOP_MID, 0, qr_code_offset_top);

    // Twint Logo (small and large)
    img_logo = lv_img_create(lv_scr_act());
    lv_img_set_src(img_logo, &logo_small);
    lv_obj_add_style(img_logo, &style_logo, 0);

    // Price Label
    price_label = lv_label_create(lv_scr_act());
    lv_obj_align(price_label, LV_ALIGN_CENTER, 0, 140);
    lv_obj_add_style(price_label, &style_price, 0);

    // Store Label
    String store_name = "Pumpkings";
    store_label = lv_label_create(lv_scr_act());
    lv_obj_align(store_label, LV_ALIGN_CENTER, 0, 200);
    lv_obj_add_style(store_label, &style_store, 0);
    lv_label_set_text(store_label, store_name.c_str());

}

void set_dark_mode(bool enable)
{
    if (enable)
    {
        lv_style_set_bg_color(&style_screen, color_bg_dark);
        lv_style_set_text_color(&style_store, color_fg_dark);

        lv_obj_del(qr);
        qr = lv_qrcode_create(lv_scr_act(), qr_code_size, color_fg_dark, color_bg_dark);
        lv_obj_align(qr, LV_ALIGN_TOP_MID, 0, qr_code_offset_top);

        lv_obj_invalidate(lv_scr_act());
    }
    else
    {
        lv_style_set_bg_color(&style_screen, color_bg_light);
        lv_style_set_text_color(&style_store, color_fg_light);

        lv_obj_del(qr);
        qr = lv_qrcode_create(lv_scr_act(), qr_code_size, color_fg_light, color_bg_light);
        lv_obj_align(qr, LV_ALIGN_TOP_MID, 0, qr_code_offset_top);

        lv_obj_invalidate(lv_scr_act());
    }
}

void update_qr_code()
{
    // Hide QR code if price is 0 and setting is set to hide default QR code
    if ((setting_show_default_qr_code == 0) && (current_price == -1))
    {
        lv_obj_add_flag(qr, LV_OBJ_FLAG_HIDDEN);}
    else{
        lv_obj_clear_flag(qr, LV_OBJ_FLAG_HIDDEN);
    }

    // Load data and update QR code
    const char *data = get_qr_data(current_price);
    lv_qrcode_update(qr, data, strlen(data));
}

void update_twint_logo()
{
    // Move and resize logo if price is 0 and setting is set to hide default QR code
    if ((setting_show_default_qr_code == 0) && ((current_price == -1)))
    {
        lv_img_set_src(img_logo, &logo_large);
        lv_obj_align(img_logo, LV_ALIGN_TOP_MID, 0, 200);
        lv_obj_set_style_radius(img_logo, LV_RADIUS_CIRCLE, 0);
    }
    else{
        lv_img_set_src(img_logo, &logo_small);
        lv_obj_align(img_logo, LV_ALIGN_TOP_MID, 0, 10);
        lv_obj_set_style_radius(img_logo, LV_RADIUS_CIRCLE, 0);
    }
}

void update_price_label()
{
    // Update Price Label
    String price_label_text = String(current_price) + " CHF";
    lv_label_set_text(price_label, price_label_text.c_str());

    // Hide Price Label if price is -1
    if ((current_price == -1) || (current_price == 0)){
        lv_obj_add_flag(price_label, LV_OBJ_FLAG_HIDDEN);
    }else{
        lv_obj_clear_flag(price_label, LV_OBJ_FLAG_HIDDEN);
    }
}


void update_store_label()
{
    // Update Price Label
    // Set visibility
    if (false){
        lv_obj_add_flag(store_label, LV_OBJ_FLAG_HIDDEN);
    }else{
        lv_obj_clear_flag(store_label, LV_OBJ_FLAG_HIDDEN);
    }

    // Hide QR code if price is -1 and setting is set to hide
    if ((setting_show_default_qr_code == 0) && (current_price == -1))
    {
        lv_obj_add_flag(qr, LV_OBJ_FLAG_HIDDEN);}
    else{
        lv_obj_clear_flag(qr, LV_OBJ_FLAG_HIDDEN);
    }
}

void draw()
{
    update_price_label();
    update_twint_logo();
    update_store_label();
    update_qr_code();
}


void receive_event(int bytes_received)
{
    // Data format: 4 bytes float + 1 byte setting_show_default_qr_code + 1 byte setting_dark_mode
    uint8_t package[6];
    float value;
    if (bytes_received == sizeof(package))
    {
        Wire.readBytes((uint8_t *)&package, bytes_received);

        setting_show_default_qr_code = package[4];
        setting_dark_mode = package[5];
        memcpy(&value, &package[0], sizeof(value));

        next_price = value;
    }
}

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */
    Serial.println("Starting...");

    // Initialize LVGL
    lv_init();

    // Initialize TFT
    tft.begin();        
    tft.setRotation(0); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screen_width * 10);

    //Initialize the display
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screen_width;
    disp_drv.ver_res = screen_height;
    disp_drv.flush_cb = display_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Initialize Serial Communication
    uint8_t address = 0x08;
    Wire.begin(address); // address of this ESP32
    Wire.onReceive(receive_event);

    // Initialize LVGL Objects
    init_lv_objects();

    set_dark_mode(true);

    draw();
}
void print_free_memory()
{
    lv_mem_monitor_t mem_mon;
    lv_mem_monitor(&mem_mon);
    Serial.print("free_size = ");
    Serial.println(mem_mon.free_size);
}

bool price_changed()
{
    // Monitor if value has changed to trigger redraw
    if (next_price != current_price) 
    {
        current_price = next_price;
        return true; }
    else{
        return false;
    }
}

bool setting_changed()
{
    // Monitor if value has changed to trigger redraw
    if ((setting_show_default_qr_code != setting_show_default_qr_code_old) ||
        (setting_dark_mode != setting_dark_mode_old))
    {
        setting_show_default_qr_code_old = setting_show_default_qr_code;
        setting_dark_mode_old = setting_dark_mode;
        return true; }
    else{
        return false;
    }
}

void loop()
{
    lv_timer_handler();

    if (price_changed())
    {
        draw();
    }
    if (setting_changed())
    {
        set_dark_mode(setting_dark_mode);
        draw();
    }
}
