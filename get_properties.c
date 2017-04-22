// get_properties.c
// z5125769 ZHENYU YAO
// ~ 2017-04-22
// COMP1511 ASGMNT01

#include <stdio.h>
#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width]) { // algorithm listed on UNSW CSE website
    int clm_s = 0, n_bk = 0;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (pixels[i][j]) clm_s += j, n_bk++;
    return ((double)clm_s / (double)n_bk + 0.5) / width;
}

double get_vertical_balance(int height, int width, int pixels[height][width]) {
    int rw_s = 0, n_bk = 0;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (pixels[j][i]) rw_s += j, n_bk++;
    return ((double)rw_s / (double)n_bk + 0.5) / height;
}

double get_density(int height, int width, int pixels[height][width]) {
    int n_bk = 0;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (pixels[i][j]) n_bk++;
    return (double)n_bk / ((double)height * (double)width);
}

HOLE_PROP get_hole_properties(int height,int width, int pixels[height][width]) { // may be splited into several functions, but anyway

    HOLE_PROP hole_prop = {.n = 0, .l = 0, .f = 0}; // in captcha.h

    int tmp[height][width]; // not to change the value of pixels, anyway
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++) 
            tmp[j][i] = pixels[j][i];

    for (int j = 0; j < height; j++) { // get rid of space outside the graph of number
        for (int i = 0; tmp[j][i] != 1; i++) 
            tmp[j][i] = 2;
        for (int i = width - 1; tmp[j][i] != 1; i--) 
            tmp[j][i] = 2;
    }

    for (int i = 0; i < width; i++) { // there won't be a hole at the first or last row
        if (tmp[0][i] == 0) tmp[0][i] = 2;
        else if (tmp[height - 1][i] == 0) tmp[height - 1][i] = 2;
    }

    int boo = 1;
    while (boo) { // fill 0 that is adjacent to 2 with 2
        boo = 0;
        for (int j = 1; j < height - 1; j++) { // avoid out of bound error here
            for (int i = 1; i < width - 1; i++) { // and here
                if (tmp[j][i] == 0 && (tmp[j - 1][i] == 2 || tmp[j + 1][i] == 2 || tmp[j][i - 1] == 2 || tmp[j][i + 1] == 2 || 
                        tmp[j - 1][i - 1] == 2 || tmp[j - 1][i + 1] == 2 || tmp[j + 1][i - 1] == 2 || tmp[j + 1][i + 1] == 2)) {
                    tmp[j][i] = 2;
                    boo = 1;
                }
            }
        }
    }

    int g_r[height]; // row with white gap (i.e. 22111000011122)
    for (int j = 0; j < height; j++) g_r[j] = 0;
	for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            if (tmp[j][i] == 0) {g_r[j] = 1; break;}
    int s = 0; // count changes
    for (int j = 0; j < height - 1; j++)
        if (g_r[j] ^ g_r[j + 1]) s++;
    hole_prop.n = s / 2;
     
    int rw_s = 0, n_wt = 0; // modified on get_vertical_balance
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (!tmp[j][i]) rw_s += j, n_wt++;
    hole_prop.l = ((double)rw_s / (double)n_wt + 0.5) / height;

    hole_prop.f = (double)n_wt / (double)(height * width);

/*
    // DEBUG // print the image
    for (int j = 0; j < height; j++) {
       for (int i = 0; i < width; i++) {
            if (tmp[j][i] == 1)
                putchar('*');
            else if (tmp[j][i] == 0)
                putchar('.');
            else putchar('-');
       }
       puts("");
    }
*/

    return hole_prop;
}
