// crack_captcha.c
// z5125769 ZHENYU YAO
// 2017-04-24
// COMP1511 ASGNMNT01
// modified on the provided test_*.c in Lab07 written by Andrew Taylor

#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) { 
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
        int start_rows[CAPTCHA_N] = {0}, start_columns[CAPTCHA_N] = {0}, 
            boxs_width[CAPTCHA_N] = {0}, boxs_height[CAPTCHA_N] = {0};
        
        get_bounding_boxs(height, width, pixels, start_rows, start_columns, 
            boxs_height, boxs_width);

        for (int k = 0; k < CAPTCHA_N; k++) {
            int box_pixels[boxs_height[k]][boxs_width[k]];
            copy_pixels(height, width, pixels, start_rows[k], start_columns[k], 
                boxs_height[k], boxs_width[k], box_pixels);
            
            printf("%d",crack(boxs_height[k], boxs_width[k], box_pixels)); // 'main' -> 'crack' hand over
        } 
        printf("\n");
    }

    return 0;
}
