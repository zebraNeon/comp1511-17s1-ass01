// crack_digit.c
// z5125769 ZHENYU YAO
// 2017-04-22
// COMP1511 ASGNMNT01

#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) { // modified on the provided test_*.c in Lab07 written by Andrew Taylor
    int height, width; 

    int result; // 

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    // first get image dimensions
    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }

    // now declare appropriate array
    int pixels[height][width];
    if (read_pbm(argv[1], height, width, pixels)) {
        int start_row, start_column, box_width, box_height;
        get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);
        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);
    
        printf("%d\n",crack(box_height, box_width, box_pixels)); // 'main' -> 'crack' hand over 
    }

    return 0;
}
