#ifndef SLMSYS_VIDEO_H
#define SLMSYS_VIDEO_H

extern void slmsys_init_video();
extern void slmsys_quit_video();

extern void slmsys_draw_pixel(uint16_t x, uint16_t y, uint8_t color);

void slmsys_draw_image(uint16_t x, uint16_t y, uint16_t size_x, uint16_t size_y ,uint8_t *image, uint8_t ignore, bool ignore_enable);

#define C_BLACK 0x00
#define C_BLUE 0x01
#define C_GREEN 0x02
#define C_CIAN 0x03
#define C_RED 0x04
#define C_MAGENTA 0x05
#define C_BROWN 0x06
#define C_LGRAY 0x07
#define C_DGRAY 0x08
#define C_LBLUE 0x09
#define C_LGREEN 0x0A
#define C_LCIAN 0x0B
#define C_LRED 0x0C
#define C_LMAGENTA 0x0D
#define C_YELLOW 0x0E
#define C_WHITE 0x0F 

#endif