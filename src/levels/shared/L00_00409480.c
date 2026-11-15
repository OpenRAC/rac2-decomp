#include "common.h"
extern int FloatToInt(float);
extern void VU1_addGSregister(unsigned int reg, unsigned long value);
extern void gfx_draw_colored_rectangle(int a, int b, int c, int d, unsigned long e);
extern short g_screen_adjust_offsets[];

/* Draws a gray flash over the whole screen that fades out as time passes. */
void gfx_draw_screen_flash_fade(char *arg)
{
    int *vars = *(int **)(arg + 104);
    short *display;
    int gray;
    int rgba;

    gray = 128 - FloatToInt((float)(vars[2] * 2));
    rgba = gray << 24;
    rgba |= gray << 16;
    rgba |= gray << 8;
    rgba |= gray;
    VU1_addGSregister(66, 72);
    display = g_screen_adjust_offsets;
    gfx_draw_colored_rectangle(0, display[0xA9], 0, display[0xA8], rgba);
    gfx_draw_colored_rectangle(0, display[0xA9], 0, display[0xA8], rgba);
    gfx_draw_colored_rectangle(0, display[0xA9], 0, display[0xA8], rgba);
    gfx_draw_colored_rectangle(0, display[0xA9], 0, display[0xA8], rgba);
}
