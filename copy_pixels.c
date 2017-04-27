// copy_pixels.c
// z5125769 ZHENYU YAO
// 2017-04-10
// COMP1511 Lab07 Ex3

#include <stdio.h>
#include "captcha.h"

void copy_pixels(int height, int width, int pixels[height][width],
    int start_row, int start_column, int copy_height, int copy_width,
    int copy[copy_height][copy_width]) {
    
    for (int i = start_row; i < start_row + copy_height; i++)
        for (int j = start_column; j < start_column + copy_width; j++)
            copy[i - start_row][j - start_column] = pixels[i][j];
}
