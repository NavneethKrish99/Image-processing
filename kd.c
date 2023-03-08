
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

// edge ig = { -1 , -1 , -1 , -1 , -1 } , { -1 , -1 , -1 , -1 , -1 } , { -1 , -1 , 24 , -1 , -1 } ,  { -1 , -1 , -1 , -1 , -1 } , { -1 , -1 , -1 , -1 , -1 }
// sobel ig = { -1 ,2 , -1 , 0 , 1 } , { -4 , -8 , 0 , 8 , 4 } , { -1 ,2 , -1 , 0 , 1 } , { 0 , 0 , 0 , 0 , 0 } , { 0 , 0 , 0 , 0 , 0 }
//{ 1.0/256.0 , 4.0/256.0 , 6.0/256.0 , 4.0/256.0 , 1.0/256.0 } , { 4.0/256.0 , 16.0/256.0 , 24.0/256.0 , 16.0/256.0 , 4.0/256.0 } , { 6.0/256.0 , 24.0/256.0 , 36.0/256.0 , 24.0/256.0 , 6.0/256.0 } ,  { 4.0/256.0 , 16.0/256.0 , 24.0/256.0 , 16.0/256.0 , 4.0/256.0 } , { 1.0/256.0 , 4.0/256.0 , 6.0/256.0 , 4.0/256.0 , 1.0/256.0 }
/*gauss blur 5x5 -        { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } */


                       /*   { 0 , 0 , 1 , 0 , 0 } ,
                          { 0 , 1 , 1 , 1 , 0 } ,
                          { 1 , 1 , 1 , 1 , 1 } ,
                          { 0 , 1 , 1 , 1 , 0 } ,
                          { 0 , 0 , 1 , 0 , 0 } */
void pix(unsigned char *c,unsigned char *b,size_t sz,unsigned char *img,int width,int height,int ch,int w,int h)
{
    uint8_t sumR=0,sumG=0,sumB=0;

    int r=0,col=0;

    float kernel[5][5]= { { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 } ,
                          { 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 , 1.0/25.0 }  };

    for(int i=height-2;i<=height+2;i++)
    {
        for(int j=width-2;j<=width+2;j++)
        {
            size_t pixvalue=w*(i-1)*ch+j*ch-ch;
            c=img+pixvalue;


            sumR=sumR+(*c) * kernel[r][col];
            sumG=sumG+(*(c+1)) * kernel[r][col];
            sumB=sumB+(*(c+2)) * kernel[r][col];




        col++;
        }
        col=0;
        r++;
    }
    *b=sumR;
    *(b+1)=sumG;
    *(b+2)=sumB;
}



int main(void) {
    int w, h, ch,w1, h1, ch1;
    unsigned char *img = stbi_load("pic.jpeg", &w, &h, &ch, 0);

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
             if(height==1||height==2||height==h||height==h-1||width==1||width==2||width==w-1||width==w)
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
                  if(ch==4) {*(b+3)=*(a+3);}
                 pix(c,b,sz,img,width,height,ch,w,h);

             }
             a+=ch;
             b+=ch;

        }

    }


    stbi_write_jpg("rand2.jpg",w,h,ch,nimg,100);
    stbi_image_free(img);
    free(nimg);



}

