// crack.c
// z5125769 ZHENYU YAO
// 2017-04-25
// COMP1511 ASGNMNT01

#include <stdio.h>
#include "captcha.h"

int crack(int height, int width, int pixels[height][width]) {
    
    HOLE_PROP hole_prop = get_hole_properties(height, width, pixels);
    MOUTH_DIR mouth_dir = get_mouth_direction(height, width, pixels);

    double density = get_density(height, width, pixels);
    double aspect_r = get_aspect_ratio(height, width);
    double hr_balance = get_horizontal_balance(height, width, pixels);
    double vt_balance = get_vertical_balance(height, width, pixels);

    // based on several experiments
    if (hole_prop.n == 2)
        return 8;
    else if (hole_prop.n == 1) {
        if (hole_prop.l < 0.55 && hole_prop.l > 0.45 && hole_prop.f > 0.115)
            return 0;
        else if (hole_prop.l > 0.4 && hole_prop.l < 0.61)
            return 4;
        else if (hole_prop.l < 0.4)
            return 6;
        else
            return 9;
    } else {
        if ((mouth_dir.u == 1 && mouth_dir.l == 0 && vt_balance > 0.54) || (mouth_dir.u == 0 && mouth_dir.l == 0 && vt_balance >= 0.56))
            return 7;
        else if ((mouth_dir.u == 1 && mouth_dir.l == 1) || (mouth_dir.u == 0 && mouth_dir.l == 1 && hr_balance <= 0.54))
            return 3;
        else if ((mouth_dir.u == 2 && mouth_dir.l == 1) || (mouth_dir.u == 2 && mouth_dir.l == 0) || (mouth_dir.u == 0 && mouth_dir.l == 1)) 
            return 5;
        else if ((mouth_dir.u == 1 && mouth_dir.l == 2) || (mouth_dir.u == 0 && mouth_dir.l == 2) || (mouth_dir.u == 1 && mouth_dir.l == 0 && aspect_r / density <= 3.5))
            return 2;
        else 
            return 1;
    }
}
