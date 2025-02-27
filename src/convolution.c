#include "convolution.h"

#include <stdlib.h>

#include "image.h"

void convolve(float *result, const float *img, int w, int h,
              const float *matrix, int w_m, int h_m) {
 // center of the kernel
 int center_x = w_m / 2;
 int center_y = h_m / 2;

 // Iterate over each pixel of input
 for (int y = 0; y < h; y++) {
     for (int x = 0; x < w; x++) {
         float sum = 0.0; 

         // Apply the kernel to the bounds of (x,y)
         for (int ky = 0; ky < h_m; ky++) {
             for (int kx = 0; kx < w_m; kx++) {
                 // corresponding pixel of input
                 int img_x = x + kx - center_x;
                 int img_y = y + ky - center_y;

                
                 float pixel_value = get_pixel_value(img, w, h, img_x, img_y);

         
                 int kernel_index = ky * w_m + kx;

                 // Multiply and accumulate
                 sum += pixel_value * matrix[kernel_index];
             }
         }

         // Store 
         result[y * w + x] = sum;
     }
 }


}

// float get_pixel_value(const float *img, int w, int h, int x, int y)