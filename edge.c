
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"


void pix(unsigned char *c,unsigned char *b,size_t sz,unsigned char *img,int width,int height,int ch,int w,int h)
{
    uint8_t horizontalsum=0,verticalsum=0,gradient_magn;

    int r=0,col=0;

    float vertkernel[3][3]= { { 1 , 2 , 1 } , { 0 , 0 , 0 } , { -1 , -2 , -1 } };
    float horzkernel[3][3]= { { -1 , 0 , 1 } , { -2 , 0 , 2 } , { -1 , 0 , 1 } };

    for(int i=height-1;i<=height+1;i++)
    {
        for(int j=width-1;j<=width+1;j++)
        {
            size_t pixvalue=w*(i-1)*ch+j*ch-ch;
            c=img+pixvalue;

            horizontalsum=horizontalsum + (*c) * horzkernel[r][col];
            verticalsum=verticalsum + (*c) * vertkernel[r][col];

        col++;
        }
        col=0;
        r++;
    }
    gradient_magn=sqrt(horizontalsum*horizontalsum + verticalsum*verticalsum);
    *b= gradient_magn>60?(uint8_t)255:0;

}



int main(void) {
    int w, h, ch,w1, h1, ch1;
    unsigned char *img = stbi_load("gsc2.png", &w, &h, &ch, 0);

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

                if(ch==4)
                {
                    *(b+1)=*(a+1);
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


    stbi_write_jpg("edge3.jpg",w,h,ch,nimg,100);
    stbi_image_free(img);
    free(nimg);
}

/*Kernels
1) gaussian blur =  { 1.0/16.0 , 2.0/16.0 , 1.0/16.0 } , { 2.0/16.0 , 4.0/16.0 , 2.0/16.0 } , { 1.0/16.0 , 2.0/16.0 , 1.0/16.0 }
2) box blur =  { 1.0/9.0 , 1.0/9.0 , 1.0/9.0 } , { 1.0/9.0 , 1.0/9.0 , 1.0/9.0 } , { 1.0/9.0 , 1.0/9.0 , 1.0/9.0 }
3) ridge or edge = { -1 , -1 , -1 } , { -1 , 8 , -1 } , { -1 , -1 , -1 }
4) identity = { 0 , 0 , 0 } , { 0 , 1 , 0 } , { 0 , 0 , 0 }
5) sharpen = {0 , -1 , 0} , { -1 , 5 , -1} , { 0 , -1 , 0 }
6) sharpen =  {0 , 1 , 0} , { 1 , -4 , 1} , { 0 , 1 , 0 }
{ -1 , 0 , 1 } , { -2 , 0 , 2 } , { -1 , 0 , 1 }
 { -1 , -2 , -1 } , { 0 , 0 , 0 } , { 1 , 2 , 1 }

*/



