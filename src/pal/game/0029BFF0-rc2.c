#include "include_asm.h"
#include "common.h"
extern void text_box_draw_frame(char *, unsigned int, unsigned int, float, float, float, float);
extern s32 g_resident_data_base;

/* The renderer consumes all four FP bounds, unchanged by this setup. */
void level_set_rect_pal(s32 arg0, s32 arg1, float top, float bottom, float left, float right) {
    s32 a;
    s32 b;

    a = arg0;
    b = arg1;
    if (g_resident_data_base != 0) {
        text_box_draw_frame((char *)(g_resident_data_base + 0x36F28), a, b, top, bottom, left, right);
    }
}
