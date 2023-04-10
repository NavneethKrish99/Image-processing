#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
int main()
{
    int w,h,ch;
    unsigned char *img = stbi_load("abhiram.jpeg",&w,&h,&ch,0);
    if(img==NULL)
    {
        printf("the image isnt there in the working folder");
        exit(1);
    }
    printf("Image----  |  width = %dpx  |  , |  height = %dpx  |  |  channels = %d  |\n", w, h, ch);
    int imgsize = w*h*ch;
    unsigned char *a=img;
    uint8_t threshold_matrix[4][4] = {{10, 120, 30, 140},
                                  {150, 60, 170, 80},
                                  {20, 130, 40, 150},
                                  {160, 70, 180, 90}};
int row = 0,col=0;

    if(ch==3||ch==4){



    int gsch = ch==4?2:1;
    int gssz=w*h*gsch;
    unsigned char *gsimg = malloc(gssz);
    unsigned char *b=gsimg;
    for(*a,*b;a!=img+imgsize;a+=ch,b+=gsch)
    {
        *b=(uint8_t)(0.3*(*a)+*(a+1)*(0.59)+*(a+2)*(0.11));
        *b=*b>threshold_matrix[row][col]?255:0;
        col=(col+1)%4;
        if(col==0)
        {
            row=(row+1)%4;
        }
        if(ch==4){
            *(b+1)=*(a+1);
        }}
        stbi_write_png("abhiram1.png",w,h,gsch,gsimg,w*gsch);
        free(img);
        stbi_image_free(gsimg);

        return 0;
    }
    else{


        unsigned char *nimg=malloc(imgsize);
        //unsigned char *b=nimg;

        for(unsigned char *a=img,*b=nimg;a!=img+imgsize;a+=ch,b+=ch)
    {
        *b=(*a>threshold_matrix[row][col]) ? 255:0;
        col=(col+1)%4;
        if(col==0)
        {
            row=(row+1)%4;
        }
        if(ch==2)
        {
            *(b+1)=*(a+1);
        }
    }
        stbi_write_png("123.png",w,h,ch,nimg,w*ch);
        free(img);
        stbi_image_free(nimg);

    }

}
