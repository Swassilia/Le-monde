#include "Image.h"
#include <vector>



int main (int argc, char** argv) { 
    srand(time(NULL));

    Pixel noir (0, 0, 0); 
    for(int h=0;h<10;h++){
    Image r0_0(4,4);
    r0_0.bruit();
    r0_0.sauver("../../data/terrain/image_source.png");
    Image r_0(256,256);
    r_0.aggrandissement( r0_0 );
    r_0.sauver("../../data/terrain/image_source_aggrandit.png");

    Image r0_01(8,8);
    r0_01.bruit();
    //r0_01.sauver("./data/R0001.ppm");
    Image r_01(256,256);
    r_01.aggrandissement(r0_01);
    //r_01.sauver("./data/R0001.ppm");

    Image r0_1(16,16);
    r0_1.bruit();
    //r0_1.sauver("./data/R01.ppm");
    Image r_1(256,256);
    r_1.aggrandissement( r0_1 );
    //r_1.sauver("./data/R1.ppm");
    Image r0_2(256,256);
    r0_2.bruit();
    //r0_2.sauver("./data/R02.ppm");
    Image r_2(256,256);
    r_2.aggrandissement( r0_2 );
    //r_2.sauver("./data/R2.ppm");

    Image final(256,256);
    
    final.concat(r_0,r_01,r_1,r_2);
    final.sauver("../../data/terrain/final"+std::to_string(h)+".png"); 
    }

    final.ovale();
    final.sauver("../../data/terrain/final_oval.png");



    
    /*int const taille_base = 4;
    int i = 1;
    std::vector<Image> images;
    std::vector<Image> images_aggrandit;
    for (int j = 0; j < 4; ++j) {
        images.push_back(j == 0 ? Image(taille_base, taille_base) : Image(taille_base * i, taille_base * i));
        i *= 2;
    }
    for (int j = 0; j < 4; ++j) {
        images_aggrandit.push_back(Image(taille_base * i, taille_base * i));      
    }
    Image final(taille_base*i,taille_base*i);
    for (int h=0;h<10;h++){
        for(int l=0; l<4 ; l++){
            images[l].bruit();
            images_aggrandit[l].aggrandissement(images[l]);
        }
        final.concat(images_aggrandit[0],images_aggrandit[1],images_aggrandit[2],images_aggrandit[3]);
        final.sauver("./data/final"+std::to_string(h)+".ppm");
    }*/

    /*
    Image image_origine(2,2);
    image_origine.bruit();
    image_aggrandi_deux.aggrandissement(image_origine);
    image_origine.sauver("./data/image_origine.ppm");

    Image image_aggrandi_deux(256,256);
    image_aggrandi_deux.aggrandissement(image_origine);
    image_aggrandi_deux.sauver("./data/imagetest1.ppm");

    Image image_aggrandi_trois(8,8);
    image_aggrandi_trois.aggrandissement(image_aggrandi_deux);
    image_aggrandi_trois.sauver("./data/imagetest2.ppm");

    /*Image image_aggrandit(256,256);
    image_aggrandit.effacer(noir);
    image_aggrandit.aggrandissement(image_origine);
    image_aggrandit.sauver("./data/image_aggrandit.ppm");
    Image image_2(64,64);
    image_2.bruit();
    image_2.sauver("./data/image2.ppm");
    Image image_2_grand(256,256);
    image_2_grand.aggrandissement(image_2);
    image_2_grand.sauver("./data/image2grand.ppm");
    Image image_3(128,128);
    image_3.bruit();
    image_3.sauver("./data/image3.ppm");
    Image image_3_grand(256,256);
    image_3_grand.aggrandissement(image_3);
    image_3_grand.sauver("./data/image3grand.ppm");
    Image image_4(256,256);
    image_4.bruit();
    image_4.sauver("./data/image4.ppm");
    Image image_4_grand(256,256);
    image_4_grand.aggrandissement(image_4);
    image_4_grand.sauver("./data/image4grand.ppm");
    Image final(256,256);
    final.concat(image_4_grand,image_3_grand,image_2_grand,image_aggrandit);
    final.sauver("./data/image_final.ppm");
    */
   return 0;
}