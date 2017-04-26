int read_pbm(char filename[], int height, int width, int pixels[height][width]);
int get_pbm_dimensions(char filename[], int *height, int *width);
void print_image(int height, int width, int pixels[height][width]);
void get_bounding_box(int height, int width, int pixels[height][width],
    int *start_row, int *start_column, int *box_height, int *box_width);
void copy_pixels(int height, int width, int pixels[height][width],
    int start_row, int start_column, int copy_height, int copy_width,
    int copy[copy_height][copy_width]);
double get_horizontal_balance(int height, int width, int pixels[height][width]);

// added for ASGMNT01
#define CAPTCHA_N 4 // use const anyway

typedef struct {
    int n; // number
    double l; // location
    double f; // fraction
} HOLE_PROP;
typedef struct {
    int u; // for upper part // 1 for left, 2 for right, 0 for none
    int l; // for lower part // 1 for left, 2 for right, 0 for none
} MOUTH_DIR;

double get_vertical_balance(int height, int width, int pixels[height][width]);
double get_density(int height, int width, int pixels[height][width]);
HOLE_PROP get_hole_properties(int height, int width, int pixels[height][width]);
double get_aspect_ratio(int height, int width);
void get_bounding_boxs(int height, int width, int pixels[height][width],
    int start_rows[CAPTCHA_N], int start_columns[CAPTCHA_N], 
    int boxs_height[CAPTCHA_N], int boxs_width[CAPTCHA_N]);
int crack(int height, int width, int pixels[height][width]);
MOUTH_DIR get_mouth_direction(int height, int width, int pixels[height][width]);
