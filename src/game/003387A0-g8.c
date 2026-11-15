#include "common.h"

/* The fade alpha of a mesh: the alpha byte of its colours, and the two
   sub-objects' fade values.  Both callees and both fade limits sit at a
   different address in every program that holds this function, so they are
   named after the function that uses them. */
extern int *ref_L00_00338810_00(void *);

extern void ref_L00_00338810_01(void *, float);

extern float ref_L00_00338810_02 __attribute__((sda));

extern float ref_L00_00338810_03 __attribute__((sda));

/* Fades a text panel in while it should show and out when it should not, and sizes its border pieces to fit the text. */
void text_panel_update_fade(void *object)
{
    char *panel = (char *)object;
    u32 *fillColor;
    u32 *textColor;
    u32 *bracketColor;
    u32 *topColor;
    int showTimer = *(int *)(panel + 0x1B8);
    int alpha = *(u8 *)((u8 *)*(u32 **)(panel + 8) + 3);
    int lineCount;
    int baseSize;
    float heightFloat;
    float tween;
    float zero;

    if (showTimer > 0) {
        alpha += 8;
        showTimer--;
        alpha = (alpha < 0x61) ? alpha : 0x60;
        *(int *)(panel + 0x1B8) = showTimer;
    } else {
        alpha = (alpha - 8 >= 0) ? alpha - 8 : 0;
    }

    if (alpha == 0) {
        *(int *)*(int *)(panel + 4) = 0;
        return;
    }

    tween = 0.0f;
    alpha <<= 24;

    fillColor = *(u32 **)(panel + 8);
    *fillColor = (*fillColor & 0x00FFFFFF) | (u32)alpha;
    textColor = *(u32 **)(panel + 0xC);
    *textColor = (*textColor & 0x00FFFFFF) | (u32)alpha;
    bracketColor = (u32 *)ref_L00_00338810_00(panel + 0x10);
    *bracketColor = (*bracketColor & 0x00FFFFFF) | (u32)alpha;
    topColor = (u32 *)ref_L00_00338810_00(panel + 0x5C);
    *topColor = (*topColor & 0x00FFFFFF) | (u32)alpha;

    if (*(int *)(panel + 0x1C4) != 1)
        return;

    baseSize = *(int *)(panel + 0x1D4);
    lineCount = *(int *)(panel + 0x1B0);
    *(int *)(panel + 0x1BC) = 8;
    *(int *)(panel + 0x1C0) = 6;
    *(int *)(panel + 0x1AC) = ((lineCount << 4) >> 1) + 6;
    *(int *)(panel + 0x1A8) = (baseSize >> 1) + 8;
    zero = tween;
    ref_L00_00338810_01(panel + 0x5C, ((float)((baseSize >> 1) + 8) - 4.0000000000000000000000e+01f)
            * 4.9504949711263179779053e-03f * 5.6749999523162841796875e-01f
            + 4.9999998882412910461426e-03f);
    if (zero < ref_L00_00338810_02)
        ref_L00_00338810_01(panel + 0x5C, ref_L00_00338810_02);
    lineCount = *(int *)(panel + 0x1AC);
    heightFloat = (float)lineCount;
    tween = (heightFloat - 1.4000000000000000000000e+01f) * 6.5789474174380302429199e-03f;
    ref_L00_00338810_01(panel + 0x10, tween * 8.5000002384185791015625e-01f
            + 2.9999999329447746276855e-02f);
    if (zero <= ref_L00_00338810_03)
        ref_L00_00338810_01(panel + 0x10, ref_L00_00338810_03);
    *(float *)(panel + 0x1D0) = tween * 3.0600000000000000000000e+02f
            + 2.3500000000000000000000e+01f;
}
