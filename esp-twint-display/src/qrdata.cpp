const char * get_qr_data(float price)
{
    int price_switch = (int)(price * 100);
    switch (price_switch)
    {
        case 1600:
            return "02:426c97e86bd548b6897b19c54967d64a#86fe642b9ba54b73694f491d308b19025c2ca3db#";
             break;
        case 900:
            return "02:68fc89929d6348d9aa6d270a1425a965#928942409ead76410e713bcb7cf3f5bd66edefad#";
             break;
        default:
            return "02:68fc89929d6348d9aa6d270a1425aa65#928942409ead76410e713bcb7cf3f5bd66edefad#";
            break;
    }
}
