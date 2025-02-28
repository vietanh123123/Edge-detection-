#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "convolution.h"
#include "derivation.h"
#include "gaussian_kernel.h"
#include "image.h"

int main(int const argc, char **const argv) {
    /**
     * Parse arguments. The parsed image file name and threshold are available
     * in the image_file_name and threshold global variables (see argparser.h).
     */
    parse_arguments(argc, argv);
    printf("Computing edges for image file %s with threshold %i\n",
           image_file_name, threshold);

    /**
     * Read Image from given file.
     *
     * If the input file is broken terminate with return value 1.
     *
     * Hint: The width and height of the image have to be accessible in the
     * scope of this function.
     */
       int w, h; 

       float *input_img = read_image_from_file(image_file_name, &w, &h);
       if (input_img == NULL) {
              return 1; 
       }

    /**
     * Blur the image by using convolve with the given Gaussian kernel matrix
     * gaussian_k (defined in gaussian_kernel.h). The width of the matrix is
     * gaussian_w, the height is gaussian_h.
     *
     * Afterwards, write the resulting blurred image to the file out_blur.pgm.
     */
    float *blurr_img = array_init(w * h);
     convolve(blurr_img, input_img, w, h, gaussian_k, gaussian_w, gaussian_h);
     write_image_to_file(blurr_img, w, h, "out_blur.pgm");

    /**
     * Compute the derivation of the blurred image computed above in both x and
     * y direction.
     *
     * Afterwards, rescale both results and write them to the files out_d_x.pgm
     * and out_d_y.pgm respectively.
     */
     float *d_x = array_init(w * h);
     float *d_y = array_init(w * h); 
     derivation_x_direction(d_x, blurr_img, w, h);
     derivation_y_direction(d_y, blurr_img, w, h);
     float *d_x_rescaled = array_init(w * h);
     float *d_y_rescaled = array_init(w * h);
     scale_image(d_x_rescaled, d_x, w, h);
     scale_image(d_y_rescaled, d_y, w, h);
     write_image_to_file(d_x_rescaled, w, h, "out_d_x.pgm");
     write_image_to_file(d_y_rescaled, w, h, "out_d_y.pgm");
    

/**
 * Compute the gradient magnitude of the blurred image by using the
 * (unscaled!) derivations in x- and y-direction computed earlier.
 *
 * Afterwards, rescale the result and write it to out_gm.pgm.
 */
float *gradient_matrix = array_init(w * h);
gradient_magnitude(gradient_matrix, d_x, d_y, w, h);
float *scale_gradient = array_init(w * h);
scale_image(scale_gradient, gradient_matrix, w, h);
write_image_to_file(scale_gradient, w, h, "out_gm.pgm");

/**
 * Apply the threshold to the gradient magnitude.
 * Then write the result to the file out_edges.pgm.
 */
apply_threshold(gradient_matrix, w, h, threshold);
write_image_to_file(gradient_matrix, w, h, "out_edges.pgm");

/**
 * Remember to free dynamically allocated memory when it is no longer used!
 */
array_destroy(input_img);
array_destroy(blurr_img);
array_destroy(d_x);
array_destroy(d_y);
array_destroy(d_x_rescaled);
array_destroy(d_y_rescaled);
array_destroy(gradient_matrix);
array_destroy(scale_gradient);

}
