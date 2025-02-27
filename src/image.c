#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_threshold(float *img, int w, int h, int T) {
    
    //Loop over the gray-scale values 
    for (int i = 0; i < h * w; i++) {
         if (img[i] <= T) {
            img[i] = 0;
         } else {
            img[i] = 255;
         }
    }
    
}

void scale_image(float *result, const float *img, int w, int h) {
    float max = img[0];
    float min = img[0];

    for (int i = 0; i < w*h; i++) {
       //compute max value 
       if (img[i] >= max) {
        max = img[i];
       }
       //compute min value
       if (img[i] <= min) {
        min = img[i];
       }

       //edge case where max = min 
       if (max == min) {
        for (int k = 0; k < w*h; k++) { 
            result[k] = 0;
        }
       } 

      //Scale these values back
       for (int j = 0; j < w*h; j++) { 
          result[j] = ((img[j]-min) / (max - min))*255;
       }


    }
    

}

float get_pixel_value(const float *img, int w, int h, int x, int y) {
    (void)img;
    (void)w;
    (void)h;
    (void)x;
    (void)y;

    // TODO: Implement me!

    return 0;
}

float *array_init(int size) {
    (void)size;

    // TODO: Implement me!

    return NULL;
}

void array_destroy(float *m) {
    (void)m;

    // TODO: Implement me!
}

float *read_image_from_file(const char *filename, int *w, int *h) {
    (void)filename;
    (void)w;
    (void)h;

    // TODO: Implement me!

    return NULL;
}

void write_image_to_file(const float *img, int w, int h, const char *filename) {
    (void)img;
    (void)w;
    (void)h;
    (void)filename;

    // TODO: Implement me!
}
