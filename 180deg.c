#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
int main(void)
{
    int w,h,ch;
    unsigned char *img = stbi_load("lio_m.png",&w,&h,&ch,0);
    if(img==NULL)
    {
        printf("error");
        exit(1);
    }
    printf("%d width   %d height    %d channels",w,h,ch);
    size_t imgsize=w*h*ch;
    size_t nimgsize=(w*h*ch)-ch;
    unsigned char *nimg=malloc(imgsize);

    for(unsigned char *a=img+nimgsize,*b=nimg;a>=img;a-=ch,b+=ch)
    {
        *b=*a;
        *(b+1)=*(a+1);
        *(b+2)=*(a+2);
        if(ch==4)
        {
            *(b+3)=*(a+3);
        }
    }
    stbi_write_png("180deg3.png",w,h,ch,nimg,w*ch);
    stbi_image_free(img);
    free(nimg);
}
