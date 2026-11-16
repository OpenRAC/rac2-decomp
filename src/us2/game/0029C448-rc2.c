#include "include_asm.h"
#include "common.h"
extern void text_box_draw_frame(char *, unsigned int, unsigned int, float, float, float, float);
extern s32 g_resident_data_base;

/* The renderer consumes all four FP bounds, unchanged by this setup. */
/* Passes a screen rectangle (top, bottom, left, right) to the level object, if one is loaded. */
void level_set_rect_us2(s32 alpha, s32 color, float top, float bottom, float left, float right) {
    s32 alpha_copy;
    s32 color_copy;

    alpha_copy = alpha;
    color_copy = color;
    if (g_resident_data_base != 0) {
        text_box_draw_frame((char *)(g_resident_data_base + 0x36F28), alpha_copy, color_copy, top, bottom, left, right);
    }
}
