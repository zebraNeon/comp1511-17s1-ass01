// bounding_box.c
// z5125769 ZHENYU YAO
// 2017-04-24
// COMP1511 ASGMNT01

#include <stdio.h>
#include "captcha.h"

void get_bounding_boxs(int height, int width, int pixels[height][width], 
    int start_rows[CAPTCHA_N], int start_columns[CAPTCHA_N], 
    int boxs_height[CAPTCHA_N], int boxs_width[CAPTCHA_N]) {

    for (int k = 0; k < CAPTCHA_N; k++) {
        
        int start_tmp = (k == 0)? 0 : start_columns[k - 1] + boxs_width[k - 1];
        start_columns[k] += start_tmp;

        for (int i = start_tmp; i < width; i++) {
            int boo = 0;
            for (int j = 0; j < height; j++)
                boo |= pixels[j][i];
            if (!boo) (start_columns[k])++;
            else break;
        }

        for (int i = start_columns[k]; i < width; i++) {
            int boo = 0;
            for (int j = 0; j < height; j++)
                boo |= pixels[j][i];
            if (boo) boxs_width[k]++;
            else break;
        }
    }

    for (int k = 0; k < CAPTCHA_N; k++) {

        int tmp[height][boxs_width[k]];
        for (int j = 0; j < height; j++)
            for (int i = 0; i < boxs_width[k]; i++)
                tmp[j][i] = pixels[j][start_columns[k] + i];

        for (int i = 0; i < height; i++) {
            int boo = 0;
            for (int j = 0; j < boxs_width[k]; j++)
                boo |= tmp[i][j];
            if (!boo) start_rows[k]++;
            else break;
        }

        for (int i = start_rows[k]; i < height; i++) {
            int boo = 0;
            for (int j = 0; j < boxs_width[k]; j++)
                boo |= tmp[i][j];
            if (boo) boxs_height[k]++;
            else break;
        }
    }
}
