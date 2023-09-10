#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Wire.h>


/*Change to your screen resolution*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

float nextPrice = 9;
float currentPrice = 9;

LV_IMG_DECLARE(qr01600);
LV_IMG_DECLARE(qr00900);

static lv_style_t style_price;
static lv_style_t style_store;


/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void init_styles()
{
    lv_style_init(&style_price);
    lv_style_set_text_font(&style_price, &lv_font_montserrat_32);
    lv_style_set_text_color(&style_price, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_color(&style_price, lv_color_hex(0x1156a5));
    lv_style_set_pad_all(&style_price, 10);
    lv_style_set_bg_opa(&style_price, LV_OPA_100);

    lv_style_init(&style_store);
    lv_style_set_text_font(&style_store, &lv_font_montserrat_20);
    lv_style_set_text_color(&style_store, lv_color_hex(0x000000));
}

void load_qr_code(float price)
{
    /* Create a static image object */
    static lv_obj_t* img1 = NULL;

    /* Clean up the memory from the previous image */
    if (img1 != NULL)
    {
        lv_obj_del(img1);
        img1 = NULL; // Reset the pointer to NULL
    }

    /* Create a new image object */
    img1 = lv_img_create(lv_scr_act());
    int price_switch = (int)(price * 100);
    switch (price_switch)
    {
    case 1600:
        lv_img_set_src(img1, &qr01600);
        break;
    case 900:
        lv_img_set_src(img1, &qr00900);
        break;
    }
}

void draw()
{
    // Create Price Label
    String price_label = String(currentPrice) + " CHF";

    static lv_obj_t *label = NULL;

    // Clean up the memory from the previous label
    if (label != NULL)
    {
        lv_obj_del(label);
        label = NULL; // Reset the pointer to NULL
    }
    label = lv_label_create(lv_scr_act());

    lv_label_set_text(label, price_label.c_str());
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 130);
    lv_obj_add_style(label, &style_price, 0);

    // Create Store Name Label
    String store_name = "Pumpkings";
    static lv_obj_t *label_store = NULL;

    // Clean up the memory from the previous label
    if (label_store != NULL)
    {
        lv_obj_del(label_store);
        label_store = NULL; // Reset the pointer to NULL
    }
    label_store = lv_label_create(lv_scr_act());

    lv_label_set_text(label_store, store_name.c_str());
    lv_obj_align(label_store, LV_ALIGN_CENTER, 0, 200);
    lv_obj_add_style(label_store, &style_store, 0);

    // Create QR Code
    load_qr_code(currentPrice);
}

void clean_all_objects()
{
    
    // Delete all objects
    lv_obj_clean(lv_scr_act());

}

void receiveEvent(int bytesReceived) {
  float value;
  if (bytesReceived == sizeof(value)) {
    Wire.readBytes((uint8_t*)&value, bytesReceived);
    Serial.print("Received value: ");
    Serial.println(value);
    nextPrice = value;
  }
}

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */
    Serial.println("Starting...");

    lv_init();

    tft.begin();        /* TFT init */
    tft.setRotation(0); /* Landscape orientation, flipped */

    /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
    //uint16_t calData[5] = {275, 3620, 264, 3532, 1};
    // tft.setTouch( calData );

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Initialize Serial Communication
    uint8_t address = 0x08;
    Wire.begin(address); // address of this ESP32
    Wire.onReceive(receiveEvent);

    init_styles();

    draw();

    // Check initial free_size:

}
void print_free_size(){

    lv_mem_monitor_t mem_mon;
    lv_mem_monitor(&mem_mon);
    Serial.print("free_size = ");
    Serial.println(mem_mon.free_size);
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
    // Redraw if price has changed
    if (nextPrice != currentPrice)
    {

        print_free_size();

        currentPrice = nextPrice;
        //clean_all_objects();
        draw();
    }
}