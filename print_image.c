// print_image.c
// z5125769 ZHENYU YAO
// 2017-04-10
// COMP1511 Lab07 Ex1

#include <stdio.h>
#include "captcha.h"

void print_image(int height, int width, int pixels[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0 ; j < width; j++) {
            printf("%s", pixels[height - i - 1][j] ? "*" : ".");
        }
        putchar('\n');
    }
}
