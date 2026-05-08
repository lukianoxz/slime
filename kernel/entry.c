#include "slmsys.h"

static uint8_t slime_logo[8 * 8] = {
     0,  0, 10, 10,  0,  0,  0,  0,
     0, 10,  0, 10, 10,  0,  0,  0,
     0,  0,  0, 10, 10,  2,  0,  0,
     0,  0, 10, 10, 10,  2,  2,  0,
     0, 10, 10,  2,  2,  2,  2,  0,
    10, 10,  2,  2,  2,  2,  2,  2,
    10, 10,  2,  2,  2,  2,  2,  2,
     0, 10, 10,  2,  2,  2,  0,  0
};

void slm_kernel_entry() {
    slmsys_init_video();
    slmsys_draw_image(6, 6, 8, 8, slime_logo, 0, true);
}