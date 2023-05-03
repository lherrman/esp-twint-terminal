#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>


/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

int currentPrice = 9;

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch( &touchX, &touchY, 600 );

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
    }
 
}

void load_qr_code(float price) 
{
/* Create an image object */
lv_obj_t *img1 = lv_img_create( lv_scr_act() );

int price_switch = (int)(price*100);
switch (price_switch)
{
  case 1600:
    LV_IMG_DECLARE(qr01600)
    lv_img_set_src(img1, &qr01600);
    break;
  case 900:
    LV_IMG_DECLARE(qr00900)
    lv_img_set_src(img1, &qr00900);
    break;
  }
}

void draw()
{

    // Create Price Label
    String price_label = String(currentPrice) + ".00 CHF";
    
    static lv_style_t style_price;
    lv_style_init(&style_price);
    lv_style_set_text_font(&style_price, &lv_font_montserrat_32);
    lv_style_set_text_color(&style_price, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_color(&style_price, lv_color_hex(0x1156a5));
    lv_style_set_pad_all(&style_price, 10);
    lv_style_set_bg_opa(&style_price, LV_OPA_100);

    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, price_label.c_str() );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 130 );
    lv_obj_add_style(label, &style_price, 0);

    // Create Store Name Label
    String store_name = "Pumpkings";
    static lv_style_t style_store;
    lv_style_init(&style_store);
    lv_style_set_text_font(&style_store, &lv_font_montserrat_20);
    lv_style_set_text_color(&style_store, lv_color_hex(0x000000));

    lv_obj_t *label_store = lv_label_create( lv_scr_act() );
    lv_label_set_text( label_store, store_name.c_str() );
    lv_obj_align( label_store, LV_ALIGN_CENTER, 0, 200 );
    lv_obj_add_style(label_store, &style_store, 0);


    // switch case loading image
    switch (currentPrice)
    {
    case 9:
        LV_IMG_DECLARE(qr09);
        lv_img_set_src(img1, &qr09);
        break;
    case 16:
        LV_IMG_DECLARE(qr16);
        lv_img_set_src(img1, &qr16);
        break;
    default:
        LV_IMG_DECLARE(qrcode);
        lv_img_set_src(img1, &qrcode);
        break;
    }

}


void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    lv_init();


    tft.begin();          /* TFT init */
    tft.setRotation(0); /* Landscape orientation, flipped */

    /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
    uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
    //tft.setTouch( calData );

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

    draw();

    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay( 5 );

}
