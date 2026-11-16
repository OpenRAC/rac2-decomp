#include "common.h"

/* func_PAL_L04_0041B5C0 (PAL, levels 4 and 11): the PAL copy of v2.00's func_US2_L04_00418348
   (src/us2/levels/shared/L04_00418348-box.c), with PAL's text id for the label. It draws a framed
   menu box titled 0xA41, a highlight bar sized to the width of label 0xE51 (at least the box
   width), and that label centred below it. The coordinates go through the menu_coord and label_y
   helpers, whose display-mode tests have no effect on the result. The bar's scale is read twice,
   once into s2 before the edges are computed, as retail loads it there. */

extern float g_race_hud_layout_scale MACRO_ADDR;
extern int g_screen_width MACRO_ADDR;
extern int g_box_margin SDATA(D_001B0ACC);
extern void gfx_draw_rounded_box(int top, int bottom, int left, int right, int alpha, int color);
extern void level_set_rect_pal(int alpha, int color, float top, float bottom, float left, float right);
extern void FontSetWindow(void *, int, int, int, int, int, int, int, int);
extern char *GetLocalizedString(int);
extern void text_draw_window_medium(void *, unsigned long long, char *, int);
extern int text_draw_centered_medium(int, int, unsigned long long, char *, int);
extern int text_measure_width_second_set(char *, int);

typedef struct {
    u8 pad[0xC];
    s16 width;
    u8 pad2[4];
    u16 flags;
    u8 rest[0xC];
} MenuBox;

extern int g_race_hud_mode __attribute__((sda));
static __inline__ int menu_coord(float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_PAL_L04_0041B5C0(void) {
    MenuBox box;
    float s, s2, half, bx, kx, ky;
    int w, left, right, center, on, x1, y1, x4, y4;

    half = 0.5f;
    bx = 222.0f;
    on = 1;
    s = g_race_hud_layout_scale;
    FontSetWindow(&box, menu_coord(bx, s, half, on), menu_coord(479.0f, s, half, on), 44, 468, 256, menu_coord(299.0f, s, half, on), 16, 3);
    kx = 263.0f;
    box.flags |= 4;
    text_draw_window_medium(&box, (int)0x80F0F0F0, GetLocalizedString(0xA41), -1);
    w = text_measure_width_second_set(GetLocalizedString(0xE51), -1);
    if (w < box.width)
        w = box.width;
    center = g_screen_width >> 1;
    s2 = g_race_hud_layout_scale;
    left = center - (w >> 1) - g_box_margin;
    right = center + (w >> 1) + g_box_margin;
    x1 = menu_coord(kx, s2, half, on);
    ky = 371.0f;
    y1 = menu_coord(ky, s2, half, on);
    gfx_draw_rounded_box(x1, y1, left, right, 96, 0x60442D00);
    s = g_race_hud_layout_scale;
    level_set_rect_pal(96, 0x55F0C070, (float)menu_coord(kx, s, half, on), (float)menu_coord(ky, s, half, on), (float)left, (float)right);
    box.flags &= ~4;
    text_draw_window_medium(&box, (int)0x80F0F0F0, GetLocalizedString(0xA41), -1);
    x4 = g_screen_width / 2;
    y4 = label_y((void *)x4, 349.0f, g_race_hud_layout_scale, half, on);
    text_draw_centered_medium(x4, y4, (int)0x80F0F0F0, GetLocalizedString(0xE51), -1);
}
