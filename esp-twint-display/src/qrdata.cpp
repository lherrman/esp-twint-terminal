const char * get_qr_data(float price)
{
    int price_switch = (int)(price * 100);
    switch (price_switch)
    {
        case 100:
            return "02:f024cf34e6324bd3a2621c56aab7ca25#7fc1cd86da487abf7855e7887ca464fca5fa0690#";
             break;
        case 1000:
            return "02:7363bb62006e4691ba9a67c80a3410ed#29a457e84debfd716594ddc95ac4255148ad3104#";
             break;
        case 10000:
            return "02:d994e5d0a1a84296a935955d55053631#c4a94fc80f09ed5aa53ffab8068da50355271e8e#";
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
        case 2200:
            return "02:6f66e514df54482ea1e2061f5562db1c#567d600eff86425cf77c4f4528de8bcc854f2022#";
             break;
        case 2300:
            return "02:5e16a020fbec41df8e7f463ba6cc584d#7f944903a96b234618ab8b78dc56835ccd6a2cc7#";
             break;
        case 2400:
            return "02:d25bcde315f24878b3ddb7d4acf2f53b#772fffe60687e0bc151e8ce405247609e656d019#";
             break;
        case 2500:
            return "02:ef664828386649ea95f8c43a238511b1#23edc70f39b400ea14928b534f2c9b74c3c50daf#";
             break;
        case 2600:
            return "02:fedd12f1a519435ea455e777c1c84446#cd24702870a9326b249982f7a58f79fe45cef069#";
             break;
        case 2700:
            return "02:ab4efc5774194633acbeadde09478c75#3dc261cd3f230d0c7d78d32eb0c3e3c8b4e042dc#";
             break;
        case 2800:
            return "02:5664fbc6f28843d59898e47effd52fe7#b5f009488de61233a4fd5364e3e71587d2d83d05#";
             break;
        case 2900:
            return "02:d0a24683191e45beaf72ba735a5729cf#2d2e60b0451174b8c1a0a231daa8a7af90f98968#";
             break;
        case 300:
            return "02:b6cd2f9389f8471095774608cb260edb#b88ad9e3000ea65675bd1660c68e84bd78a6e733#";
             break;
        case 3000:
            return "02:a6186eca96014c548e2e63f471c9099f#2b7f75409400b82909b976948a70592718e6080b#";
             break;
        case 3100:
            return "02:5b8c01f4d6734cf096256439a5e25296#6cdcc82ac3fe4eb0962ba7e9c70d6a6c69f9da6b#";
             break;
        case 3200:
            return "02:0332faa668ae4d03a3052d9cff418043#7dcb59d7e42cfb46d6910d01cb85a884579f1ff3#";
             break;
        case 3300:
            return "02:67eb61b989894b69b68072d546cfb9b6#72a8af109c1cdfb4d8f16ee12226cd94fa014894#";
             break;
        case 3400:
            return "02:a0b4b158ea684c04b82a561be426df6f#0d87275ecedaf206751e48e63e8a39c3b90a63c3#";
             break;
        case 3500:
            return "02:03d972ab182b42a4ba57d9972adec78e#b8208a69aa36a2cfb849a507ca4d627e38a6818f#";
             break;
        case 3600:
            return "02:e166c8ba6b924ff8a51d2e354e617ae7#ab698383336957bc152fd53e2fd541827ce91073#";
             break;
        case 3700:
            return "02:61a266358d4a4e7488ddd270efb1cf45#5cbf2ab2a7474dd5bfb658713830021f7d141d40#";
             break;
        case 3800:
            return "02:ad3c8512a709413981388d8d5ac4fda4#df36861bb6f664f85885f755c7213cc91a3a304c#";
             break;
        case 3900:
            return "02:e09feea546ca49dda760322784fbc408#c8367b776115d604b7e9d9c88ceb96d154c09674#";
             break;
        case 400:
            return "02:86c3643d28754b47ba1d9535c698410a#373f7a0d4a66762eac6d36c1069fdb6473a36a42#";
             break;
        case 4000:
            return "02:22928b15c9804948b19da4fd647ae945#d505d828eaf9d554805b0f9feea8647c1f340625#";
             break;
        case 4100:
            return "02:57f7b76939374ff0ae847fc0c247297f#bd7edf9d266961c5bcb3a29a72f93740d37f3011#";
             break;
        case 4200:
            return "02:b746cfa6ad7a4b8ab5e05c6e2624c670#a720ffa9bb3c151786bb4a6b08ee87d172d2ac86#";
             break;
        case 4300:
            return "02:4fe51df4280b469587c964a02b2e6520#fa75dc30d7b41f4e4e19d601957c5a4a355f47d3#";
             break;
        case 4400:
            return "02:09d16fc98ab8497c8103251a73b0cc29#8d11d722139a1cea5dcfdbebe11de04ba8629ee2#";
             break;
        case 4500:
            return "02:edef666570e543d9ae89e1e5b5f87962#8d14c5722ad5d7e663c5913f976c5b4b6f893227#";
             break;
        case 4600:
            return "02:c74a5ad379b94b4aa2dec5b49c48b884#6fdf4575a9fbfd1626d3088652ecc8c7f1198163#";
             break;
        case 4700:
            return "02:06ed99f1476b4ddea5c065adc0d84ba0#a396ca9426ca23cc830cc8c677bcbc17e19afc8d#";
             break;
        case 4800:
            return "02:352c2f4df54c4b61ad99cc3017dcf02a#7255d22b0ad9aa53352e3ef9f71a6f898b7200f2#";
             break;
        case 4900:
            return "02:2ef205ae9c81412a91de0861c443cc0f#123194834c7d143e69fd97f6ec0e4a4af6b1dc02#";
             break;
        case 500:
            return "02:ab7b0eb906684424ba8ac797227dfcbd#a2ae38573cb9a8a30717a58628059da607fa6bb6#";
             break;
        case 5000:
            return "02:3bacc5cb409e4705a477f5f4b064651f#0c3ab6b6afb2ca93d7163cab8f2f69ee1c9f6e89#";
             break;
        case 5100:
            return "02:18aef4c1618d4a75906daa0d8592e493#0d24f1881f01ec6400d369f1db0279f3686b0fca#";
             break;
        case 5200:
            return "02:f1816d7fb32f450c962ca11bbaa888dd#8fe6cd07e937ab824cae7babd74d20578e12b1e3#";
             break;
        case 5300:
            return "02:34846f26673e4d7c847cbd0346385e47#598c4e70cc046fbe868578d601d2fec30911d0e7#";
             break;
        case 5400:
            return "02:0481efc7d2414f46a80648bb89a885a3#146fe5e10f3c7e53d7d73f10178072bf9ac4f7e6#";
             break;
        case 5500:
            return "02:9038fdb48210481ab7cf07eeeede3ea6#9e12affba5c7df75abd0b577910b6d9192e514c7#";
             break;
        case 5600:
            return "02:3134f9101be64613833709767e15b952#fd79263b77330f0e51b9d6bba23c12bfccbd4e79#";
             break;
        case 5700:
            return "02:0dcaab77709a46e4a561d293c680ce3e#8cc2c2ec91ed22fb6bd32b8f1a8b29f12502031c#";
             break;
        case 5800:
            return "02:0eab1fd39e264c159f6597cb9561adc5#10d5a21c4058eb9d5f7d4beaa2644e8096ef0ac9#";
             break;
        case 5900:
            return "02:52d5412b54fe4630ba842805f664f7a3#d44358cefdd0a4d0e9bedbc97dbb06a9e70f6b88#";
             break;
        case 600:
            return "02:e20c7a0c75064acb8e89d7a8fc42cd01#5c022041922f9cac10c5a146a89020adda856e4c#";
             break;
        case 6000:
            return "02:bdd2dae4e2494522869312375a7520e9#531e9fb154913dff891acf922514e9ce050ca5d0#";
             break;
        case 6100:
            return "02:69cd8182ce6a41da84674e3b60b3a956#7f0ddc7a34a5372a06ba451f21d96b80135a54c2#";
             break;
        case 6200:
            return "02:3dd150ef69d64b7a96a165ba0ed914de#a6d38fc223b6026dc0529c0202bc51bf6bd1b376#";
             break;
        case 6300:
            return "02:3223c252784b4f2a92493feabb08fa75#39392a69624f8bbb186983ed4c45c38486ecdbd2#";
             break;
        case 6400:
            return "02:cd62adf6999c46b1bad31c1cd4f6f2a1#7db243f4c30fddf01a0c0356a77747e4686afe7d#";
             break;
        case 6500:
            return "02:8b49c4d41cad4ff1a726d6b3cdc7c54e#e857779f4892e6cd3f26d2be7028bef9fe8c7c02#";
             break;
        case 6600:
            return "02:d64d0adaa6d14b8581dd4ebc932dd9bc#3f9e67e7871172e5130c9d458cf99113fd94ae4f#";
             break;
        case 6700:
            return "02:b0ef16ab21c84baf8d129407fb9b32c9#d2d98ae9a28bd811814ee4fdf21390107a6ccac7#";
             break;
        case 6800:
            return "02:421cd6292fe242b18f1bf8124d3c5ce2#0c0f792d8bcf63c63e0ecfa7e1c99c955c832de5#";
             break;
        case 6900:
            return "02:7bafe2e4e2b54cddba2889ffe2981d3d#a37d5fc4cbc8c482f81ce706506cf72197eb9e8e#";
             break;
        case 700:
            return "02:962aaad14bdc449cafb92dc65a79333e#94d5b035faef9e4e6de8be87ce526124c6683e9a#";
             break;
        case 7000:
            return "02:25e1365793914c0ebe5ad26071be6db6#664467e43f6df7dd4640c1971d65d58d089751f4#";
             break;
        case 7100:
            return "02:f6fe06a5f99144d1a17d1f096920e225#6a5b43d6cd5f5b62a41bec28d518296182945a00#";
             break;
        case 7200:
            return "02:efee2c121b3f4fc6b2baf4f07bd0c829#2e10fcc8e8b0a5a2a063be825532c56c63b707b2#";
             break;
        case 7300:
            return "02:2dad1456f3794bd7af757987316ef473#1cb661e6db4cc4c3ece1c16518619c32ffb67cc7#";
             break;
        case 7400:
            return "02:cffd9cb1c26549d496c35efc6400f235#ba5088c4d801041161d2bab9ae70c2147217e702#";
             break;
        case 7500:
            return "02:82dd4cecd2bd4cac8b95ab63c030e9f2#d5f329839832e8dddde4f701b10c8a2ffe8132ac#";
             break;
        case 7600:
            return "02:f7d1cae0725f464ba717835580b0d493#b811efe5cb420882f6b6bb8a1bd5f0d888f0e612#";
             break;
        case 7700:
            return "02:e117c326522b46d69b14c5197aea0e87#65959d4445930e276132e33e02d00d80a171a870#";
             break;
        case 7800:
            return "02:99d2cebeb752479aafdbb74591dbb698#bd7b27257d42194b34e33f6c597378384d93c9d5#";
             break;
        case 7900:
            return "02:ce5137d3dd9f41c1b21e79dd558e4834#9b97673d8d2c6e3bf4021570802bbacfad772677#";
             break;
        case 800:
            return "02:d5d2e79cdd544c498317f651f648ce14#886ca9a64eb479efa694d0fd0e3a0b232016a7dd#";
             break;
        case 8000:
            return "02:268af014f53c4d0e9c10083a413863fd#341516728f9f4f300b2da6e9b6763464893ffa83#";
             break;
        case 8100:
            return "02:e3839cdaaa7844cf98df90810257ae0f#164550b32f9c83ea6a48ce0a2b88ef84f9401aab#";
             break;
        case 8200:
            return "02:daf3cfda36d64844acd4f92fbb101562#ac0944f2a2f47fd2753294c53c21959ee915265f#";
             break;
        case 8300:
            return "02:13fd88b9e0af44a1ad2c2c22b6dc9955#aa781a76f2337f6e1fa01fdb7c9af25aedf7deca#";
             break;
        case 8400:
            return "02:1f47457108404bcea2fae5ac426fe5d7#13c530fccf5826dddc1b991cd9ef416fbd7fb441#";
             break;
        case 8500:
            return "02:5d691009679c494fa6a1a5cd26b0ee77#29905e6e08bb9f0071a73140aed924f4fd5973fb#";
             break;
        case 8600:
            return "02:7834c1fa963b43bfa77481ebb515b12c#be223d693f2882475ef562dee0ced37bc05701b8#";
             break;
        case 8700:
            return "02:2f5cdc332d91415eb2478d8771d5ea6d#c44b94d7e6754acd1aa20e0885b4c9832134af3a#";
             break;
        case 8800:
            return "02:e52a111d9d524da592d7f953d8b41ef7#2af9cc3525eb638f71113a1c1411fc5984fe2cc6#";
             break;
        case 8900:
            return "02:b58a9c98c1144c05b9649ec35eda2b92#953b5e940b98d24e74cdf9778417221c5959e7bd#";
             break;
        case 900:
            return "02:68fc89929d6348d9aa6d270a1425a965#928942409ead76410e713bcb7cf3f5bd66edefad#";
             break;
        case 9000:
            return "02:ac757162cc144984ab2d0ac2721d548c#0eebff8dc262bb5d92c8bfa1eb110b6cd5fa37e9#";
             break;
        case 9100:
            return "02:5fa7879db30648a38481aa7570aa1979#b79ad78040bd50916d95351ce1efafe68eea4d9b#";
             break;
        case 9200:
            return "02:012bcab8dd7b420b9324747af0f83d4f#f102e5047b9675c3cfd26f01b2b0ae96735bd0e5#";
             break;
        case 9300:
            return "02:0c1198f02bf14e969a71b6c4443820f3#12026a3c3280ee84fd6c854b0c893154778b1b5c#";
             break;
        case 9400:
            return "02:1962956a7de04d22950f47b860577337#7559fa3bb2f7cbee5488be1e30425f51adffb65c#";
             break;
        case 9500:
            return "02:8cedc6cc996349b1837a2518f39376ef#ba169220747ceb81102e16a193ebfb459b0f7906#";
             break;
        case 9600:
            return "02:2fb97ecbb8774ae7906cfe6a6ae8b078#45573c74186e518dc73e33127787b3b518f4ca92#";
             break;
        case 9700:
            return "02:afca37caf91c414d9f89b1bea757b847#db09ebe70746b54f6b3baacfbb51bb2feef204c8#";
             break;
        case 9800:
            return "02:d14b8eb2be464c43bcde23ad36b88c79#f85049ffd21b0919413af630e13e4938132628bf#";
             break;
        case 9900:
            return "02:9254e40dca404969bf5e48440ebeac4e#5ac1febd28452ae9bf6215213b6122a15a5c08d1#";
             break;
        default:
            return "02:5dff699a101a41af9593179033a016dc#ebd8abedc0d3a2839848874766a7022744f4c982#";
            break;
    }
}
