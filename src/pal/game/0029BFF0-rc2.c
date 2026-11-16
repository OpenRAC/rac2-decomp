#include "include_asm.h"
#include "common.h"
extern void text_box_draw_frame(char *, unsigned int, unsigned int, float, float, float, float);
extern s32 g_resident_data_base;

/* The renderer consumes all four FP bounds, unchanged by this setup. */
void level_set_rect_pal(s32 first_arg, s32 second_arg, float top, float bottom, float left, float right) {
    s32 a;
    s32 b;

    a = first_arg;
    b = second_arg;
    if (g_resident_data_base != 0) {
        text_box_draw_frame((char *)(g_resident_data_base + 0x36F28), a, b, top, bottom, left, right);
    }
}
