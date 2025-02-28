#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_threshold(float *img, int w, int h, int T) {
    // Loop over each row and each column in the image
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            // index
            int index = y * w + x;
            
    // Check if the pixel value is greater than the threshold
            if (img[index] > T) {
                img[index] = 255;
            } else {
                img[index] = 0;
            }
        }
    }

}

void scale_image(float *result, const float *img, int w, int h) {
  float min = img[0];
  float max = img[0];
  //find max min 
  for (int i = 1; i < w*h; i++){
    if (img[i] < min ){
        min = img[i];
    }
    if (img[i] > max){
        max = img[i];
    }
  }
  //check max min equal

  if (max== min){
    for (int i = 0; i < w*h; i++){
        result[i] = 0;
    } return;
  }
 //scale values 

 for (int i = 0; i < w * h; i++){
    result[i] = ((img[i]-min) / (max - min)) * 255 ;
  }


}

float get_pixel_value(const float *img, int w, int h, int x, int y) {
    if ( x < 0 ){
        x = -x - 1 ;
     } else if ( x >= w){
        x = 2 * w - x - 1 ; 
    }
        if ( y < 0 ){
        y = -y - 1 ;
     } else if ( y >= h){
        y = 2 * h - y - 1 ; 
    }
     int index = y * w + x;
     return img[index];
    }
    


float *array_init(int size) {
   
    // Allocate memory for the array of floats
    float *arr = (float *)malloc(size * sizeof(float));

    // Check if the allocation was successful
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
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
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }

    char file_type[3];
    int max_gray_value;

    //file type check
    if (fscanf(fileptr, "%2s", file_type) != 1 || strcmp(file_type, "P2") != 0) {
        fprintf(stderr, "Error: Invalid PGM file\n");
        fclose(fileptr);
        return NULL;
    }

    // Dimension check
    if (fscanf(fileptr, "%d %d", w, h) != 2 || *w <= 0 || *h <= 0) {
        fprintf(stderr, "Error: Invalid dimensions\n");
        fclose(fileptr);
        return NULL;
    }

    // Read the maximum gray value
    if (fscanf(fileptr, "%d", &max_gray_value) != 1 || max_gray_value < 0 || max_gray_value > 255) {
        fprintf(stderr, "Error: Invalid max gray value\n");
        fclose(fileptr);
        return NULL;
    }

    // Allocate memory for the image
    float *img = array_init((*w) * (*h));
    if (img == NULL) {
        fclose(fileptr);
        return NULL;
    }

    // Read pixel values
    for (int i = 0; i < (*w) * (*h); i++) {
        int pixel_value;
        if (fscanf(fileptr, "%d", &pixel_value) != 1) {
            fprintf(stderr, "Error: Invalid pixel input\n");
            array_destroy(img);
            fclose(fileptr);
            return NULL;
        }
        if (pixel_value < 0 || pixel_value > 255) {
            fprintf(stderr, "Error: Invalid pixel range\n");
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
 if (fileptr == NULL) {   // Check if file is oppened successfull
  fprintf(stderr, "Error: Can not open file %s \n", filename);
   return; 
   }

 fprintf(fileptr, "P2\n");
 fprintf(fileptr, "%d %d\n", w, h);
 fprintf(fileptr, "255\n");
 
 //Write the pixel value 

 for (int i = 0; i < w * h; i++){
   int pixel_value = (int) (img[i]);
   if (pixel_value < 0) pixel_value = 0;
   if (pixel_value > 255) pixel_value = 255;

   fprintf(fileptr, "%d\n", pixel_value);  
 }
 fclose(fileptr);

}





