#include "common.h"

/* func_PAL_0033A5F0, the PAL copy of func_00338810: the same C, where the fade steps by 9, a loop
   drops to a smaller text mode until the widest line fits, and the margins follow the mode. */
extern int *ref_L00_00338810_00(void *);

extern void ref_L00_00338810_01(void *, float);

extern float ref_L00_00338810_02 __attribute__((sda));

extern float ref_L00_00338810_03 __attribute__((sda));

extern int text_measure_width_small_scaled(char *, int, float);

extern float text_panel_mode_scale_pal(void *, int);

/* Fades the text panel in or out and fits its text: steps the alpha by 9, drops to a smaller text
 * mode until the widest line fits, and sets the panel size and border scales (PAL version). */
void text_panel_update_fade_pal(void *object)
{
    char *panel = (char *)object;
    u32 *color_box;
    u32 *color_text;
    u32 *color_top;
    u32 *color_side;
    int counter = *(int *)(panel + 0x1B8);
    int alpha = *(u8 *)((u8 *)*(u32 **)(panel + 8) + 3);
    int alpha_shifted;
    int half_height;
    int half_width;
    int i;
    float height_float;
    float height_scale;
    float zero;

    if (counter > 0) {
        alpha += 9;
        counter--;
        alpha = (alpha < 0x61) ? alpha : 0x60;
        *(int *)(panel + 0x1B8) = counter;
    } else {
        alpha = (alpha - 9 >= 0) ? alpha - 9 : 0;
    }

    if (alpha == 0) {
        *(int *)*(int *)(panel + 4) = 0;
        return;
    }

    alpha_shifted = alpha << 24;

    color_box = *(u32 **)(panel + 8);
    *color_box = (*color_box & 0x00FFFFFF) | (u32)alpha_shifted;
    color_text = *(u32 **)(panel + 0xC);
    *color_text = (*color_text & 0x00FFFFFF) | (u32)alpha_shifted;
    color_top = (u32 *)ref_L00_00338810_00(panel + 0x10);
    *color_top = (*color_top & 0x00FFFFFF) | (u32)alpha_shifted;
    color_side = (u32 *)ref_L00_00338810_00(panel + 0x5C);
    *color_side = (*color_side & 0x00FFFFFF) | (u32)alpha_shifted;

    while (*(int *)(panel + 0x1D4) > 0x1D5 && *(int *)(panel + 0x1C4) != 0) {
        *(int *)(panel + 0x1C4) -= 1;
        if (*(int *)(panel + 0x1D8) != 0) {
            *(int *)(panel + 0x1D4) = 0;
            for (i = 0; i < *(int *)(panel + 0x1B0); i++) {
                float scale = text_panel_mode_scale_pal(panel, *(int *)(panel + 0x1C4));
                int line_width = text_measure_width_small_scaled(((char **)(panel + 0x1D8))[i], -1, scale);
                *(int *)(panel + 0x1D4) = (*(int *)(panel + 0x1D4) < line_width) ? line_width : *(int *)(panel + 0x1D4);
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

    half_width = (*(int *)(panel + 0x1D4) >> 1) + *(int *)(panel + 0x1BC);
    half_height = ((*(int *)(panel + 0x1B0) << 4) >> 1) + *(int *)(panel + 0x1C0);
    *(int *)(panel + 0x1A8) = half_width;
    *(int *)(panel + 0x1AC) = half_height;
    zero = 0.0f;
    ref_L00_00338810_01(panel + 0x5C, ((float)half_width - 4.0000000000000000000000e+01f)
            * 0.004950495f * 5.6749999523162841796875e-01f
            + 4.9999998882412910461426e-03f);
    if (zero < ref_L00_00338810_02)
        ref_L00_00338810_01(panel + 0x5C, ref_L00_00338810_02);
    half_height = *(int *)(panel + 0x1AC);
    height_float = (float)half_height;
    height_scale = (height_float - 1.4000000000000000000000e+01f) * 6.5789474174380302429199e-03f;
    ref_L00_00338810_01(panel + 0x10, height_scale * 8.5000002384185791015625e-01f
            + 2.9999999329447746276855e-02f);
    if (zero <= ref_L00_00338810_03)
        ref_L00_00338810_01(panel + 0x10, ref_L00_00338810_03);
    *(float *)(panel + 0x1D0) = height_scale * 3.0600000000000000000000e+02f
            + 2.3500000000000000000000e+01f;
}
