#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long u64;

extern int hud_draw_widget_text(void *);
extern u64 tex_get_effect_descriptor_us2(int);
extern void text_draw_scaled_us2(float, float, u64, u8 *, int, float, u64, u8 *);
extern float text_fit_scale_to_width_us2(u8 *, int, int, float);
extern void gfx_enable_screen_flag(void);
extern void gfx_disable_screen_flag(void);

/* func_US2_003378A0, the USA v2.00 copy of func_00336A78: the same C with a new start, which sets
   the mode word func_0027F110/func_0027F120 write from +0x54, and with +0x48 set stores the
   fitted scale of func_US2_002804C0 and turns it into a vertical offset for the text. */
/* Draws a text label widget, aligned left, centered or right, with the optional fitted-scale offset (v2.00 copy). */
void text_label_draw_us2(char *widget)
{
    float x;
    float y;
    float offset;
    int width;
    u64 texture;
    int color;
    float *scale;

    if (*(int *)(widget + 0x54) != 0) {
        gfx_enable_screen_flag();
    } else {
        gfx_disable_screen_flag();
    }
    offset = 0.0f;
    if (*(int *)(widget + 0x48) != 0) {
        **(float **)(widget + 4) = text_fit_scale_to_width_us2(*(u8 **)(widget + 0x40), -1, *(int *)(widget + 0x4C), *(float *)(widget + 0x50));
        offset = 3.0f - (**(float **)(widget + 4) - *(float *)(widget + 0x50)) * 10.0f;
    }
    if (*(float *)(*(char **)(widget + 16)) == 0.0f) {
        return;
    }
    if (*(int *)(widget + 64) == 0) {
        return;
    }
    width = hud_draw_widget_text(widget);
    x = *(float *)(*(char **)(widget));
    switch (*(int *)(widget + 68)) {
    case 0:
        break;
    case 1:
        x = x - (float)(width >> 1);
        break;
    case 2:
        x = x - (float)width;
        break;
    }
    y = *(float *)(*(char **)(widget) + 4) + offset;
    color = *(int *)(*(char **)(widget + 12));
    scale = *(float **)(widget + 4);
    texture = tex_get_effect_descriptor_us2(*(int *)(widget + 56));
    text_draw_scaled_us2(x, y, color, *(u8 **)(widget + 64), width, *scale, texture, *(u8 **)(widget + 52));
}
