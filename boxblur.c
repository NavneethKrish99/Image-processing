
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void pix(unsigned char *c,unsigned char *b,size_t sz,unsigned char *img,int width,int height,int ch,int w,int h)
{
    uint8_t sumR=0,sumG=0,sumB=0;
    for(int i=height-1;i<=height+1;i++)
    {
        for(int j=width-1;j<=width+1;j++)
        {
            size_t pixvalue=w*(i-1)*ch+j*ch-ch;
            c=img+pixvalue;
          /*  if(j==width||i==height)
            {
            sumR=sumR+(*c) * (0);
            sumG=sumG+(*(c+1)) * (0);
            sumB=sumB+(*(c+2)) * (0);
            }
            else
            {
            sumR=sumR+(*c) * (1);
            sumG=sumG+(*(c+1)) * (1);
            sumB=sumB+(*(c+2)) * (1);
            }*/

            sumR=sumR+(*c) * (1.0/9.0);
            sumG=sumG+(*(c+1)) * (1.0/9.0);
            sumB=sumB+(*(c+2)) * (1.0/9.0);


        }
    }
    *b=sumR;
    *(b+1)=sumG;
    *(b+2)=sumB;
}



int main(void) {
    int w, h, ch,w1, h1, ch1;
    unsigned char *img = stbi_load("me&namita.jpg", &w, &h, &ch, 0);

    if(img==NULL) {
        printf("error");
        exit(1);
    }
    printf("width - %d  ||| height - %d  |||  channels - %d \n",w,h,ch);
    size_t imgsz=w*h*ch,sz;
    unsigned char *nimg = malloc(imgsz);
    unsigned char *a=img,*b=nimg,*c=img;

    for(int height=1;height<=h;height++)
    {
        for(int width=1;width<=w;width++)
        {
            sz=w*(height-1)*ch+width*ch-ch;
             if(height==1||height==h||width==1||width==w)
             {
                *b=*a;
                *(b+1)=*(a+1);
                *(b+2)=*(a+2);
                if(ch==4)
                {
                    *(b+3)=*(a+3);
                }
             }

             else
             {

                 pix(c,b,sz,img,width,height,ch,w,h);

             }
             a+=ch;
             b+=ch;

        }

    }


    stbi_write_jpg("comp1_me&namita.jpg",w,h,ch,nimg,100);
    stbi_image_free(img);
    free(nimg);



}
