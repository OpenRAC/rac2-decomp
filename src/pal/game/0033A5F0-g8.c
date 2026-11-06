#include "common.h"

/* func_PAL_0033A5F0, the PAL copy of func_00338810: the same C, where the fade steps by 9, a loop
   drops to a smaller text mode until the widest line fits, and the margins follow the mode. */
extern int *ref_L00_00338810_00(void *);

extern void ref_L00_00338810_01(void *, float);

extern float ref_L00_00338810_02 __attribute__((sda));

extern float ref_L00_00338810_03 __attribute__((sda));

extern int func_0027F288(char *, int, float);

extern float func_PAL_0033A598(void *, int);

void func_PAL_0033A5F0(void *object)
{
    char *obj = (char *)object;
    u32 *c1;
    u32 *c2;
    u32 *c3;
    u32 *c4;
    int counter = *(int *)(obj + 0x1B8);
    int alpha = *(u8 *)((u8 *)*(u32 **)(obj + 8) + 3);
    int top;
    int v0;
    int v1;
    int i;
    float f0;
    float f20;
    float f21;

    if (counter > 0) {
        alpha += 9;
        counter--;
        alpha = (alpha < 0x61) ? alpha : 0x60;
        *(int *)(obj + 0x1B8) = counter;
    } else {
        alpha = (alpha - 9 >= 0) ? alpha - 9 : 0;
    }

    if (alpha == 0) {
        *(int *)*(int *)(obj + 4) = 0;
        return;
    }

    top = alpha << 24;

    c1 = *(u32 **)(obj + 8);
    *c1 = (*c1 & 0x00FFFFFF) | (u32)top;
    c2 = *(u32 **)(obj + 0xC);
    *c2 = (*c2 & 0x00FFFFFF) | (u32)top;
    c3 = (u32 *)ref_L00_00338810_00(obj + 0x10);
    *c3 = (*c3 & 0x00FFFFFF) | (u32)top;
    c4 = (u32 *)ref_L00_00338810_00(obj + 0x5C);
    *c4 = (*c4 & 0x00FFFFFF) | (u32)top;

    while (*(int *)(obj + 0x1D4) > 0x1D5 && *(int *)(obj + 0x1C4) != 0) {
        *(int *)(obj + 0x1C4) -= 1;
        if (*(int *)(obj + 0x1D8) != 0) {
            *(int *)(obj + 0x1D4) = 0;
            for (i = 0; i < *(int *)(obj + 0x1B0); i++) {
                float scale = func_PAL_0033A598(obj, *(int *)(obj + 0x1C4));
                int w = func_0027F288(((char **)(obj + 0x1D8))[i], -1, scale);
                *(int *)(obj + 0x1D4) = (*(int *)(obj + 0x1D4) < w) ? w : *(int *)(obj + 0x1D4);
            }
        }
    }

    switch (*(int *)(obj + 0x1C4)) {
    case 0:
        *(int *)(obj + 0x1BC) = 5;
        *(int *)(obj + 0x1C0) = 5;
        break;
    case 1:
        *(int *)(obj + 0x1BC) = 6;
        *(int *)(obj + 0x1C0) = 5;
        break;
    case 2:
        *(int *)(obj + 0x1BC) = 8;
        *(int *)(obj + 0x1C0) = 6;
        break;
    }

    if (*(int *)(obj + 0x1C4) == 3)
        return;

    v1 = (*(int *)(obj + 0x1D4) >> 1) + *(int *)(obj + 0x1BC);
    v0 = ((*(int *)(obj + 0x1B0) << 4) >> 1) + *(int *)(obj + 0x1C0);
    *(int *)(obj + 0x1A8) = v1;
    *(int *)(obj + 0x1AC) = v0;
    f21 = 0.0f;
    ref_L00_00338810_01(obj + 0x5C, ((float)v1 - 4.0000000000000000000000e+01f)
            * 0.004950495f * 5.6749999523162841796875e-01f
            + 4.9999998882412910461426e-03f);
    if (f21 < ref_L00_00338810_02)
        ref_L00_00338810_01(obj + 0x5C, ref_L00_00338810_02);
    v0 = *(int *)(obj + 0x1AC);
    f0 = (float)v0;
    f20 = (f0 - 1.4000000000000000000000e+01f) * 6.5789474174380302429199e-03f;
    ref_L00_00338810_01(obj + 0x10, f20 * 8.5000002384185791015625e-01f
            + 2.9999999329447746276855e-02f);
    if (f21 <= ref_L00_00338810_03)
        ref_L00_00338810_01(obj + 0x10, ref_L00_00338810_03);
    *(float *)(obj + 0x1D0) = f20 * 3.0600000000000000000000e+02f
            + 2.3500000000000000000000e+01f;
}
