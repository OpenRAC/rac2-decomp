#include "common.h"

/* func_US2_00339740, the USA v2.00 copy of func_00338810: the same fade, with a
   new step before the layout: while the widest row is 470 or more, take the
   next smaller scale from func_US2_003396E8 and measure the rows again. */
extern int *object_get_fourth_field(void *);

extern void object_set_value_float(void *, float);

extern int text_measure_width_small_scaled(u8 *, int, float);

extern float text_panel_get_scale_us2(void *, int);

extern float ref_L00_00338810_02 __attribute__((sda));

extern float ref_L00_00338810_03 __attribute__((sda));

void text_panel_update_fade_us2(void *object)
{
    char *panel = (char *)object;
    u32 *fill_color;
    u32 *text_color;
    u32 *bracket_color;
    u32 *top_color;
    u32 fade;
    int fade_frames = *(int *)(panel + 0x1B8);
    int alpha = *(u8 *)((u8 *)*(u32 **)(panel + 8) + 3);
    int half_height;
    int half_width;
    int i;
    float height_f;
    float height_scale;
    float zero;

    if (fade_frames > 0) {
        alpha += 8;
        fade_frames--;
        alpha = (alpha < 0x61) ? alpha : 0x60;
        *(int *)(panel + 0x1B8) = fade_frames;
    } else {
        alpha = (alpha - 8 >= 0) ? alpha - 8 : 0;
    }

    if (alpha == 0) {
        *(int *)*(int *)(panel + 4) = 0;
        return;
    }

    fade = alpha << 24;

    fill_color = *(u32 **)(panel + 8);
    *fill_color = (*fill_color & 0x00FFFFFF) | fade;
    text_color = *(u32 **)(panel + 0xC);
    *text_color = (*text_color & 0x00FFFFFF) | fade;
    bracket_color = (u32 *)object_get_fourth_field(panel + 0x10);
    *bracket_color = (*bracket_color & 0x00FFFFFF) | fade;
    top_color = (u32 *)object_get_fourth_field(panel + 0x5C);
    *top_color = (*top_color & 0x00FFFFFF) | fade;

    while (*(int *)(panel + 0x1D4) >= 0x1D6 && *(int *)(panel + 0x1C4) != 0) {
        *(int *)(panel + 0x1C4) = *(int *)(panel + 0x1C4) - 1;
        if (*(u8 **)(panel + 0x1D8) != 0) {
            *(int *)(panel + 0x1D4) = 0;
            for (i = 0; i < *(int *)(panel + 0x1B0); i++) {
                int width = text_measure_width_small_scaled(((u8 **)(panel + 0x1D8))[i], -1,
                        text_panel_get_scale_us2(panel, *(int *)(panel + 0x1C4)));
                int widest = *(int *)(panel + 0x1D4);

                if (widest < width)
                    widest = width;
                *(int *)(panel + 0x1D4) = widest;
            }
        }
    }

    switch (*(int *)(panel + 0x1C4)) {
    case 0:
        *(int *)(panel + 0x1BC) = 5;
        *(int *)(panel + 0x1C0) = 5;
        break;
    case 1:
        *(int *)(panel + 0x1BC) = 6;
        *(int *)(panel + 0x1C0) = 5;
        break;
    case 2:
        *(int *)(panel + 0x1BC) = 8;
        *(int *)(panel + 0x1C0) = 6;
        break;
    }

    if (*(int *)(panel + 0x1C4) == 3)
        return;

    zero = 0.0f;
    half_width = (*(int *)(panel + 0x1D4) >> 1) + *(int *)(panel + 0x1BC);
    half_height = ((*(int *)(panel + 0x1B0) << 4) >> 1) + *(int *)(panel + 0x1C0);
    *(int *)(panel + 0x1A8) = half_width;
    *(int *)(panel + 0x1AC) = half_height;
    object_set_value_float(panel + 0x5C, ((float)half_width - 40.0f) * 0.004950495f * 0.5675f + 0.005f);
    if (zero < ref_L00_00338810_02)
        object_set_value_float(panel + 0x5C, ref_L00_00338810_02);
    height_f = (float)*(int *)(panel + 0x1AC);
    height_scale = (height_f - 14.0f) * 0.0065789474f;
    object_set_value_float(panel + 0x10, height_scale * 0.85f + 0.03f);
    if (zero <= ref_L00_00338810_03)
        object_set_value_float(panel + 0x10, ref_L00_00338810_03);
    *(float *)(panel + 0x1D0) = height_scale * 306.0f + 23.5f;
}
