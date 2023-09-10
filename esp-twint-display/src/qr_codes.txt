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
