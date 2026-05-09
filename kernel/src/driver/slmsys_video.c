#include "../../slmsys.h"

void slmsys_draw_image(uint16_t x, uint16_t y, uint16_t size_x, uint16_t size_y ,uint8_t *image, uint8_t ignore, bool ignore_enable) {
    for (uint16_t i = 0; i < size_y; i++) {
        for (uint16_t j = 0; j < size_x; j++) {
            uint8_t image_color = image[j + (size_x * i)];
            if (ignore_enable) {
                if (image_color != ignore) {
                    uint16_t x_offset = x + j;
                    uint16_t y_offset = y + i;
                    slmsys_draw_pixel(x_offset, y_offset, image_color);
                }
            } else {
                uint16_t x_offset = x + j;
                uint16_t y_offset = y + i;
                slmsys_draw_pixel(x_offset, y_offset, image_color);
            }
        }
    }
}