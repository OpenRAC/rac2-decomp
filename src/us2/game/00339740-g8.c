#include "common.h"

/* func_US2_00339740, the USA v2.00 copy of func_00338810: the same fade, with a
   new step before the layout: while the widest row is 470 or more, take the
   next smaller scale from func_US2_003396E8 and measure the rows again. */
extern int *func_00335E20(void *);

extern void func_003363C0(void *, float);

extern int func_0027F288(u8 *, int, float);

extern float func_US2_003396E8(void *, int);

extern float ref_L00_00338810_02 __attribute__((sda));

extern float ref_L00_00338810_03 __attribute__((sda));

void func_US2_00339740(void *object)
{
    char *obj = (char *)object;
    u32 *c1;
    u32 *c2;
    u32 *c3;
    u32 *c4;
    u32 fade;
    int counter = *(int *)(obj + 0x1B8);
    int alpha = *(u8 *)((u8 *)*(u32 **)(obj + 8) + 3);
    int v0;
    int v1;
    int i;
    float f0;
    float f20;
    float f21;

    if (counter > 0) {
        alpha += 8;
        counter--;
        alpha = (alpha < 0x61) ? alpha : 0x60;
        *(int *)(obj + 0x1B8) = counter;
    } else {
        alpha = (alpha - 8 >= 0) ? alpha - 8 : 0;
    }

    if (alpha == 0) {
        *(int *)*(int *)(obj + 4) = 0;
        return;
    }

    fade = alpha << 24;

    c1 = *(u32 **)(obj + 8);
    *c1 = (*c1 & 0x00FFFFFF) | fade;
    c2 = *(u32 **)(obj + 0xC);
    *c2 = (*c2 & 0x00FFFFFF) | fade;
    c3 = (u32 *)func_00335E20(obj + 0x10);
    *c3 = (*c3 & 0x00FFFFFF) | fade;
    c4 = (u32 *)func_00335E20(obj + 0x5C);
    *c4 = (*c4 & 0x00FFFFFF) | fade;

    while (*(int *)(obj + 0x1D4) >= 0x1D6 && *(int *)(obj + 0x1C4) != 0) {
        *(int *)(obj + 0x1C4) = *(int *)(obj + 0x1C4) - 1;
        if (*(u8 **)(obj + 0x1D8) != 0) {
            *(int *)(obj + 0x1D4) = 0;
            for (i = 0; i < *(int *)(obj + 0x1B0); i++) {
                int width = func_0027F288(((u8 **)(obj + 0x1D8))[i], -1,
                        func_US2_003396E8(obj, *(int *)(obj + 0x1C4)));
                int widest = *(int *)(obj + 0x1D4);

                if (widest < width)
                    widest = width;
                *(int *)(obj + 0x1D4) = widest;
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

    f21 = 0.0f;
    v1 = (*(int *)(obj + 0x1D4) >> 1) + *(int *)(obj + 0x1BC);
    v0 = ((*(int *)(obj + 0x1B0) << 4) >> 1) + *(int *)(obj + 0x1C0);
    *(int *)(obj + 0x1A8) = v1;
    *(int *)(obj + 0x1AC) = v0;
    func_003363C0(obj + 0x5C, ((float)v1 - 40.0f) * 0.004950495f * 0.5675f + 0.005f);
    if (f21 < ref_L00_00338810_02)
        func_003363C0(obj + 0x5C, ref_L00_00338810_02);
    f0 = (float)*(int *)(obj + 0x1AC);
    f20 = (f0 - 14.0f) * 0.0065789474f;
    func_003363C0(obj + 0x10, f20 * 0.85f + 0.03f);
    if (f21 <= ref_L00_00338810_03)
        func_003363C0(obj + 0x10, ref_L00_00338810_03);
    *(float *)(obj + 0x1D0) = f20 * 306.0f + 23.5f;
}
