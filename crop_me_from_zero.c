#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main(void) {
    int w, h, ch;
    unsigned char *img = stbi_load("dishonoured.png", &w, &h, &ch, 0);

    if(img==NULL) {
        printf("error");
        exit(1);
    }
 int m,n;
    size_t imgsz=w*h*ch;
    printf("enter w and h: ");
    scanf("%d %d",&m,&n);
    size_t ex=m*n*ch;
    unsigned char *nimg=malloc(ex);
    int d=0;
    unsigned char *a=img,*b=nimg;
    int c=w-m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {

        d=d+1;
        *b=*a;
        *(b+1)=*(a+1);
        *(b+2)=*(a+2);


        if(ch==4)
            {
                *(b+3)=*(a+3);
            }


            if( d % (m)==0)
            {
                a=a+ch+c*ch;
                d=0;
            }
            else
            {
                a+=ch;
            }

            b+=ch;
        }
    }
    stbi_write_jpg("sizever1.jpg",m,n,ch,nimg,100);
    free(nimg);
    stbi_image_free(img);

}
