#include "common.h"

/* func_00336548 is a unit of its own: -ffast-math turns its clamp into retail's min.s, and
   -G8 gives the $gp load of D_001AD9E8. The size pointer is read again for the clamp's
   right-hand side and both size components are read before the second limit conversion,
   which lets GCSE replace that reload with retail's register copy. */

typedef struct {
    float *position;
    float *size;
    char pad08[4];
    int *fill;
    float *scale;
    char pad14[0x28];
    unsigned int limit;
    char pad40[4];
    int back;
} Bar_336548;

extern int g_progress_bar_context;

extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);

/* Clamps the bar's width to its limit, then draws the full background and the clamped fill. */
void hud_draw_progress_bar(Bar_336548 *bar) {
    float x, y, width, height, right;
    int colors[2], bottom, context, x0, y0;

    if (*bar->scale == 0.0f) return;
    x = bar->position[0];
    y = bar->position[1];
    context = g_progress_bar_context;
    bar->size[0] = bar->size[0] > (float)bar->limit ? (float)bar->limit : bar->size[0];
    y0 = (int)y;
    x0 = (int)x;
    width = bar->size[0];
    height = bar->size[1];
    colors[1] = colors[0] = bar->back;
    right = x + (float)bar->limit;
    bottom = (int)(y + height);
    gfx_draw_screen_rectangle(x0, y0, (int)right, bottom, context, colors);
    colors[0] = bar->fill[0];
    colors[1] = bar->fill[1];
    gfx_draw_screen_rectangle((int)x, (int)y, (int)(x + width), bottom, context, colors);
}
