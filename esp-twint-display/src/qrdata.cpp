const char * get_qr_data(float price)
{
    int price_switch = (int)(price * 100);
    switch (price_switch)
    {
        case 1000:
            return "02:7363bb62006e4691ba9a67c80a3410ed#29a457e84debfd716594ddc95ac4255148ad3104#";
             break;
        case 1100:
            return "02:e2e9df1ae9a045b897fe65040e3067f4#d478e63b890f814694e28ab7bdd0e4ecfff978bd#";
             break;
        case 1200:
            return "02:9416bf7a7f9d43e996ef06f6a326f719#9df9f54eb972c5838588943813d053f6c94a9bd0#";
             break;
        case 1300:
            return "02:a27c164b775944598d781d4cffee8c8b#6869a2a06ec0725e82d31a58e2b616a1399cc8f7#";
             break;
        case 1400:
            return "02:bb6bba106f404e55b1f57ea0152d9ce4#1aa4891c87ef86fb6d480910f29b2c341ef9f289#";
             break;
        case 1500:
            return "02:25ec2044933a4d7f9fca79ecee415641#0269e2a49c6564d8e6f708b05c42b74acf285f9f#";
             break;
        case 1600:
            return "02:426c97e86bd548b6897b19c54967d64a#86fe642b9ba54b73694f491d308b19025c2ca3db#";
             break;
        case 1700:
            return "02:e62478b65f8b455cae99796fa668b1fb#e432cb331c91ea26067fceea04e6125df24b12c9#";
             break;
        case 1800:
            return "02:59d4654336b54a9aa6fa6f1a7c6bfac2#ee89093eba51f3aad093c7828bdb2eaa067cd7af#";
             break;
        case 1900:
            return "02:13f3f35364b5417aa9cb3d1070feadb0#dc615c5e51727b1ac45c51b91939d8dad483a826#";
             break;
        case 200:
            return "02:2dfd22166a484177b29a0a64a55a38f0#409aeb3cf39327c3e391343580199950f78517a0#";
             break;
        case 2000:
            return "02:53a08878dd0a443f964534d85c91e77b#be196acd209ab6c239689ea005f4c724644873df#";
             break;
        case 2100:
            return "02:3938f92da41c4c2d87a8e81330bd1227#ced1100cb38d6288136de1eb722f9b18b6b9f2b1#";
             break;
        case 300:
            return "02:b6cd2f9389f8471095774608cb260edb#b88ad9e3000ea65675bd1660c68e84bd78a6e733#";
             break;
        case 400:
            return "02:86c3643d28754b47ba1d9535c698410a#373f7a0d4a66762eac6d36c1069fdb6473a36a42#";
             break;
        case 500:
            return "02:ab7b0eb906684424ba8ac797227dfcbd#a2ae38573cb9a8a30717a58628059da607fa6bb6#";
             break;
        case 600:
            return "02:e20c7a0c75064acb8e89d7a8fc42cd01#5c022041922f9cac10c5a146a89020adda856e4c#";
             break;
        case 700:
            return "02:962aaad14bdc449cafb92dc65a79333e#94d5b035faef9e4e6de8be87ce526124c6683e9a#";
             break;
        case 800:
            return "02:d5d2e79cdd544c498317f651f648ce14#886ca9a64eb479efa694d0fd0e3a0b232016a7dd#";
             break;
        case 900:
            return "02:68fc89929d6348d9aa6d270a1425a965#928942409ead76410e713bcb7cf3f5bd66edefad#";
             break;
        default:
            return "02:68fc89929d6348d9aa6d270a1425aa65#928942409ead76410e713bcb7cf3f5bd66edefad#";
            break;
    }
}
