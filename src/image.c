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
    if ( x < 0 ){
        x = -x - 1 ;
     } else if ( x >= w){
        x = 2 * (w - 1) - x ; 
    }
        if ( y < 0 ){
        y = -y - 1 ;
     } else if ( y >= h){
        y = 2 * (h - 1) - y ; 
    }
     int index = y * w + x;
     return img[index];
    
    
}

float *array_init(int size) {
   
    float *arr = (float *)malloc(size * sizeof(float));
    if (arr == NULL) {
        return NULL;
    }
    return arr;
}

void array_destroy(float *m) {
    if (m != NULL) {
        free(m);
    }
}

float *read_image_from_file(const char *filename, int *w, int *h) {
    FILE *fileptr = fopen(filename, "r");
    if (fileptr == NULL) {
        fprintf(stderr,"Error: File %s not found\n", filename);
        return NULL;
    }

    char file_type[3];
    int max_gray_value;

    //file type check(read the header )
    if( fscanf(fileptr, "%2s", file_type) != 1 || strcmp(file_type, "P2") != 0) {
        fprintf(stderr, "Error: Invalid file type\n");
        fclose(fileptr);
        return NULL;
    }
    
    // Dimension check 
    
    if (fscanf(fileptr, "%d %d", w, h) != 2 || *w <= 0 || *h <= 0) {
        fprintf(stderr, "Error: Invalid dimensions\n");
        fclose(fileptr);
        return NULL;
    }

    //Read the maximum gray value
    if (fscanf(fileptr, "%d", &max_gray_value) != 1 || max_gray_value < 0 || max_gray_value > 255 ) {
        fprintf(stderr, "Error: Invalid max gray value\n");
        fclose(fileptr);
        return NULL;
    }
    
    //Allocate memory for the image 
    float *img = array_init((*w) * (*h)); 
    if (img == NULL) {
        fclose(fileptr);
        return NULL;
    }
    
    //Read the pixel values 
    for (int i = 0; i < (*w)*(*h); i++) {
    int pixel_value;
    if (fscanf(fileptr, "%d", &pixel_value) != 1) {
        fprintf(stderr, "Error: Invalid pixel value\n");
        array_destroy(img);
        fclose(fileptr);
        return NULL;
    }
    
    if (pixel_value <0 || pixel_value > 255) {
        fprintf(stderr, "Error: Invalid pixel value\n");
        array_destroy(img);
        fclose(fileptr);
        return NULL;
    }
    img[i] = (float)pixel_value;
 }
    fclose(fileptr);
    return img;
}

void write_image_to_file(const float *img, int w, int h, const char *filename  ) {
     FILE *fileptr = fopen(filename, "w");
      if (fileptr == NULL) {  //check if the file is found
        fprintf(stderr, "Error: File not %s found\n", filename);
        return;  
      }
    
      fprintf(fileptr, "P2\n");
      fprintf(fileptr, "%d %d\n", w, h);
      fprintf(fileptr, "255\n");   
    
    //Write the pixel values
    
    for (int i = 0; i < w*h; i++) {
        int pixel_value = (int)img[i];
        if (pixel_value < 0) pixel_value = 0;
        if (pixel_value > 255) pixel_value = 255;
        fprintf(fileptr, "%d\n", pixel_value);
    }
    fclose(fileptr);
}





