// get_properties.c
// z5125769 ZHENYU YAO
// 2017-04-15 ~ 2017-04-29
// COMP1511 ASGMNT01

#include <stdio.h>
#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width]) { // algorithm listed on UNSW CSE website
    int clm_s = 0, n_bk = 0;
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            if (pixels[j][i]) clm_s += i, n_bk++;
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
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            if (pixels[j][i]) n_bk++;
    return (double)n_bk / ((double)height * (double)width);
}

HOLE_PROP get_hole_properties(int height,int width, int pixels[height][width]) {

    HOLE_PROP hole_prop = {.n = 0, .l = 0, .f = 0}; // -> captcha.h

    // not to change the value of pixels
    int tmp[height][width]; 
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++) 
            tmp[j][i] = pixels[j][i];

    // prepare for the 2 spreading
    for (int j = 0; j < height; j++) {
        if (tmp[j][0] == 0) tmp[j][0] = 2;
        if (tmp[j][width - 1] == 0) tmp[j][width - 1] = 2;
    }

    // there won't be a hole at the first or last row
    for (int i = 0; i < width; i++) {        
        if (tmp[0][i] == 0) tmp[0][i] = 2;
        if (tmp[height - 1][i] == 0) tmp[height - 1][i] = 2;
    }

    // spreading 2 around the graph, then 0 can indicate holes
    // fill 0 that is adjacent to 2 with 2
    int boo = 1;
    while (boo) {    
        boo = 0;
        // avoid out of bound error
        for (int j = 1; j < height - 1; j++) { 
            for (int i = 1; i < width - 1; i++) {
                if (tmp[j][i] == 0 && (tmp[j - 1][i] == 2 || tmp[j + 1][i] == 2 ||
                        tmp[j][i - 1] == 2 || tmp[j][i + 1] == 2 || tmp[j - 1][i - 1] == 2 ||
                        tmp[j - 1][i + 1] == 2 || tmp[j + 1][i - 1] == 2 || tmp[j + 1][i + 1] == 2)) {
                    tmp[j][i] = 2;
                    boo = 1;
                }
            }
        }
    }

    // mark the rows with 0 inside (i.e. 22111000011122)
    int arr[height]; 
    for (int j = 0; j < height; j++) arr[j] = 0;
	for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            if (tmp[j][i] == 0) {
                arr[j] = 1;
                // one zero is enough
                break; 
            }

    // count changes, which can be identified as blocks multiplied by 2
    int s = 0; 
    for (int j = 0; j < height - 1; j++)
        if (arr[j] ^ arr[j + 1]) s++;
    hole_prop.n = s / 2;

    // this part is modified on get_vertical_balance
    int rw_s = 0, n_wt = 0; 
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (!tmp[j][i]) rw_s += j, n_wt++;

    // avoid -nan
    if (n_wt) hole_prop.l = ((double)rw_s / (double)n_wt + 0.5) / height;
    else hole_prop.l = 0; 

    hole_prop.f = (double)n_wt / (double)(height * width);

    return hole_prop;
}

double get_aspect_ratio(int height, int width) {
    return (double)height / (double)width;
}

MOUTH_DIR get_mouth_direction(int height, int width, int pixels[height][width]) {

    MOUTH_DIR mouth_dir = {.u = 0, .l = 0}; // -> captcha.h

    // not to change the value of pixels
    int tmp[height][width]; 
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++) 
            tmp[j][i] = pixels[j][i];

    // assume the mouth is usually across both the left and the right part
    for (int j = 0; j < height; j++) {
        tmp[j][width / 2] = 3;
    }

    // prepare for the 2 spreading
    for (int j = 0; j < height; j++) { 
        if (tmp[j][0] == 0) tmp[j][0] = 2;
        if (tmp[j][width - 1] == 0) tmp[j][width - 1] = 2;
    }
    // there won't be a mouth at the first or last row
    for (int i = 0; i < width; i++) { 
        if (tmp[0][i] == 0) tmp[0][i] = 2;
        if (tmp[height - 1][i] == 0) tmp[height - 1][i] = 2;
    }

    // spreading 2 around the graph, then 0 can indicate holes
    // fill 0 that is adjacent to 2 with 2
    int boo = 1;
    while (boo) {
        boo = 0;
        // avoid out of bound error
        for (int j = 1; j < height - 1; j++) { 
            for (int i = 1; i < width - 1; i++) {
                if (tmp[j][i] == 0 && (tmp[j - 1][i] == 2 || tmp[j + 1][i] == 2 ||
                         tmp[j][i - 1] == 2 || tmp[j][i + 1] == 2 || tmp[j - 1][i - 1] == 2 || 
                         tmp[j - 1][i + 1] == 2 || tmp[j + 1][i - 1] == 2 || tmp[j + 1][i + 1] == 2)) {
                    tmp[j][i] = 2;
                    boo = 1;
                }
            }
        }
    }

    // mark the rows with 0 inside
    int arr[height]; 
    for (int j = 0; j < height; j++) arr[j] = 0;

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            if (tmp[j][i] == 0) {
                arr[j] = 1;
                // one zero is enough
                break;
            }

    // get the middle point (row) of '1' group
    int s = 0, s_ = 0, boo_ = 0; 
    for (int j = 0; j < height; j++) {
        if (arr[j] == 1) {
            boo_ = 1;
            s += j;
            s_++;
        }
        // only count and add in a continuous group of '1'
        else if (arr[j] == 0 && boo_ == 1) { 
            // here using mouth_dir as a tmp var, its value will be assigned later
            if (s / s_ > height / 2) mouth_dir.u = s / s_; 
            else mouth_dir.l = s / s_;
            s = 0, s_ = 0, boo_ = 0;
        }
    }
    
    // once certain 3 is hitted by water-like spreading 4, the mouth is identified
    // same method as above, now 4 is used 
    for (int j = 0; j < height; j++) { 
        if (tmp[j][0] == 2) tmp[j][0] = 4;
        if (tmp[j][width - 1] == 2)tmp[j][width - 1] = 4; 
    }

    boo = 1;
    while (boo) {
        boo = 0;
        for (int j = 1; j < height - 1; j++) {
            for (int i = 1; i < width - 1; i++) {
                if (tmp[j][i] == 2 && (tmp[j - 1][i] == 4 || tmp[j + 1][i] == 4 || 
                        tmp[j][i - 1] == 4 || tmp[j][i + 1] == 4 || tmp[j - 1][i - 1] == 4 || 
                        tmp[j - 1][i + 1] == 4 || tmp[j + 1][i - 1] == 4 || tmp[j + 1][i + 1] == 4)) {
                    tmp[j][i] = 4;
                    boo = 1;
                }
            }
        }
    }

    if (tmp[mouth_dir.u][width / 2 - 1] == 4) 
        mouth_dir.u = 1; // which means towards left 
    else if (tmp[mouth_dir.u][width / 2 + 1] == 4) 
        mouth_dir.u = 2; // or right
    else 
        mouth_dir.u = 0; // no mouth in the upper half

    if (tmp[mouth_dir.l][width / 2 - 1] == 4) 
        mouth_dir.l = 1; // same for the lower one
    else if (tmp[mouth_dir.l][width / 2 + 1] == 4) 
        mouth_dir.l = 2;
    else 
        mouth_dir.l = 0; 

    return mouth_dir;
}
