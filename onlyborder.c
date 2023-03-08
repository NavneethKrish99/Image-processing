
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main(void) {
    int w, h, ch,w1, h1, ch1;
    unsigned char *img = stbi_load("sizever1.jpg", &w, &h, &ch, 0);

    if(img==NULL) {
        printf("error");
        exit(1);
    }
    printf("width - %d  ||| height - %d  |||  channels - %d \n",w,h,ch);
    size_t imgsz=w*h*ch;
    unsigned char *nimg = malloc(imgsz);
    unsigned char *a=img,*b=nimg;
    for(int height=1;height<=h;height++)
    {
        for(int width=1;width<=w;width++)
        {
             if(height==1||height==h||width==1||width==w)
             {
                *b=(uint8_t)0;
                *(b+1)=(uint8_t)0;
                *(b+2)=(uint8_t)0;
             }
             else
             {
                *b=*a;
                *(b+1)=*(a+1);
                *(b+2)=*(a+2);
                if(ch==4)
                {
                    *(b+3)=*(a+3);
                }


             }
             a+=ch;
             b+=ch;

        }

    }


    stbi_write_jpg("try2.jpg",w,h,ch,nimg,100);
    stbi_image_free(img);
    free(nimg);



}
