#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
int main()
{
    int w,h,chn;
    unsigned char *img =stbi_load("random.jpeg",&w,&h,&chn,0);
    if(img==NULL)
    {
        printf("Error in loading the image.");
        exit(1);
    }
    printf("Image---- width = %dpx  ,  height = %dpx   and  channels = %d\n", w, h, chn);

    int imsz=w*h*chn;
    int gsc=chn==4?2:1;
    int nimgsz=w*h*gsc;

    unsigned char *nimg=malloc(nimgsz);

    for(unsigned char *a=img,*b=nimg;a!=img+imsz;a+=chn,b+=gsc)
    {
        *b=(uint8_t)(0.3*(*a)+*(a+1)*(0.59)+*(a+2)*(0.11));

        if(chn==4)
        {
            *(b+1)=*(a+3);
        }
    }
stbi_write_png("rand.png",w,h,gsc,nimg,w*gsc);

stbi_image_free(img);

free(nimg);


}
