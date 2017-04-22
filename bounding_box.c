// bounding_box.c
// z5125769 ZHENYU YAO
// 2017-04-10
// COMP1511 Lab07 Ex2

#include <stdio.h>
#include "captcha.h"

void get_bounding_box(int height, int width, int pixels[height][width], 
    int *start_row, int *start_column, int *box_height, int *box_width) {
    
    *start_row = 0, *start_column = 0, *box_height = 0, *box_width = 0;
    
    for (int i = 0; i < height; i++) {
        int boo = 0;
        for (int j = 0; j < width; j++)
            boo |= pixels[i][j];
        if (!boo) (*start_row)++;
        else break;
    }

    for (int i = *start_row; i < height; i++) {
        int boo = 0;
        for (int j = 0; j < width; j++)
            boo |= pixels[i][j];
        if (boo) (*box_height)++;
        else break;
    }

    for (int i = 0; i < width; i++) {
        int boo = 0;
        for (int j = 0; j < height; j++)
            boo |= pixels[j][i];
        if (!boo) (*start_column)++;
        else break;
    }

    for (int i = *start_column; i < width; i++) {
        int boo = 0;
        for (int j = 0; j < height; j++)
            boo |= pixels[j][i];
        if (boo) (*box_width)++;
        else break;
    }
}

