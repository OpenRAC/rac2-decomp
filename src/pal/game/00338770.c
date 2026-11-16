#include "include_asm.h"
#include "names.h"

extern int hud_draw_widget_text(void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern void FontPrintScaled_pal(float x, float y, unsigned long color, char *text, int characterLimit,
        float scale, unsigned long texture, char *metrics);
extern float text_calc_fit_scale(char *text, int length, int maxWidth, float minScale);

/* func_PAL_00338770, the PAL copy of func_00336A78: the same C, with the text first shrunk to
   fit its maximum width by func_PAL_00280358 and moved by what the scale gave up. */
/* Draws a text label left, centre or right aligned, shrinking the text to fit its maximum width
 * (PAL version). */
void text_label_draw_pal(char *widget)
{
    float y_offset = 0.0f;
    float x;
    float y;
    int width;
    unsigned long texture;
    int color;
    char *position;
    char *scale;

    if (*(int *)(widget + 0x48) != 0) {
        **(float **)(widget + 4) = text_calc_fit_scale(*(char **)(widget + 0x40), -1, *(int *)(widget + 0x4C), *(float *)(widget + 0x50));
        y_offset = 3.0f - (**(float **)(widget + 4) - *(float *)(widget + 0x50)) * 10.0f;
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
    position = *(char **)(widget);
    scale = *(char **)(widget + 4);
    color = *(int *)(*(char **)(widget + 12));
    y = *(float *)(position + 4) + y_offset;
    texture = GetEffectTextureDescriptor(*(int *)(widget + 56));
    FontPrintScaled_pal(x, y, color, *(char **)(widget + 64), width, *(float *)(scale), texture,
            *(char **)(widget + 52));
}
