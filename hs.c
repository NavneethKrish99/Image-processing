
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main(void)
{
    int w,h,chn;
    unsigned char *img =stbi_load("gsc1.png",&w,&h,&chn,0);
    if(img==NULL)
    {
        printf("error");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", w, h, chn);

    // Error diffusion matrix
    int errorDiffusionMatrix[3][3] = {{0,0,0}, {0,0,7}, {3,5,1}};

    size_t imsz=w*h*chn;
    unsigned char *nimg=malloc(imsz);

    // Loop through the image
    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            int pixelIndex = i * w * chn + j * chn;
            unsigned char gray = img[pixelIndex];

            // Quantize the gray value
            unsigned char newValue = gray >= 128 ? 255 : 0;

            // Calculate the quantization error
            int error = gray - newValue;

            // Spread the error to the surrounding pixels
            for(int k=-1; k<=1; k++) {
                for(int l=-1; l<=1; l++) {
                    int row = i + k;
                    int col = j + l;
                    if(row >= 0 && row < h && col >= 0 && col < w) {
                        int neighborIndex = row * w * chn + col * chn;
                        img[neighborIndex] = (unsigned char)(img[neighborIndex] + error * errorDiffusionMatrix[k+1][l+1] / 16);
                    }
                }
            }

            nimg[pixelIndex] = newValue;
        }
    }

    stbi_write_png("error_diffusion.png", w, h, chn, nimg, w*chn);

    stbi_image_free(img);
    free(nimg);

    return 0;
}
