#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void pix(unsigned char *img,unsigned char *a,unsigned char *b,int w,int h,int ch,int hi,int jw)
{
    size_t pixel;
    pixel = w*(hi-1)*ch + jw*ch - ch;
    a=pixel + img;
    *b = *a;
    *(b+1) = *(a+1);
    *(b+2) = *(a+2);
    if(ch==4)
    {
        *(b+3)=*(a+3);
    }
}

int main(void) {
    int w, h, ch,w1, h1, ch1;
    unsigned char *img = stbi_load("skull1.png", &w, &h, &ch, 0);

    if(img==NULL)
    {
        printf("error");
        exit(1);
    }
    printf("width - %d  ||| height - %d  |||  channels - %d \n",w,h,ch);
    size_t imgsize =w*h*ch ;
    unsigned char *nimg = malloc(imgsize);
    unsigned char *a=img,*b=nimg;

    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {

            pix(img,a,b,w,h,ch,i,j);

            a+=ch;
            b+=ch;
        }
    }
    stbi_write_png("skull_1_pix.png",w,h,ch,nimg,w*ch);
    free(nimg);
    stbi_image_free(img);
    }


