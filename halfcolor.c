#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main(void) {
    int w, h, ch;
    unsigned char *img = stbi_load("fireguy.jpg", &w, &h, &ch, 0);

    if(img==NULL) {
        printf("error");
        exit(1);
    }
 int m,n;
    size_t imgsz=w*h*ch;
    unsigned char *nimg=malloc(imgsz);
    int d=0;
    unsigned char *a=img,*b=nimg;


    int c=w-m;

    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {


        *b=(*(a+1)+*(a))/2;
        *(b+1)=*(a);
        *(b+2)=*(a+2);


        if(ch==4)
            {
                *(b+3)=*(a+3);
            }

                a+=ch;

            b+=ch;
        }
    }








    stbi_write_png("fireguyfl.png",w,h,ch,nimg,w*ch);
    free(nimg);
    stbi_image_free(img);

}
