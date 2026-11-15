#include "include_asm.h"
#include "names.h"

extern float IntToFloat(int a);
extern int FloatToInt(float f);
extern int FastTweenColor(float, int, int);
extern float math_ease_out_quad(float f);
extern float math_square(float f);
extern void FastVecScale(char *a, char *b, float f);
extern void FastVecAdd(char *a, char *b, char *c);
extern void vec_transform_or_copy(char *a, char *b);
extern int FastDecTimer(char *p);
extern void part_kill(char *p);

/* Hand-adapted from func_002C8880. */
void func_PAL_L00_00342BF4(char *self) {
    float a[4];
    float b[4];
    char *p = self + 0x20;
    float t, f20, f21, f22;
    int color;

    b[0] = *(float *)(self + 0x20);
    b[1] = *(float *)(p + 4);
    b[2] = *(float *)(p + 8);
    b[3] = 0;
    vec_transform_or_copy(self + 0x10, self + 0x10);
    t = IntToFloat(*(short *)(self + 0xA)) / IntToFloat(*(unsigned char *)(p + 0x11));
    f22 = 1.0f - t;
    if (*(unsigned char *)(p + 0x13) == 0) {
        color = FastTweenColor(f22, 0x103080, *(int *)(p + 0xC));
        *(int *)(self + 4) = color | (*(unsigned char *)(p + 0x12) << 24);
        *(float *)(self + 0xC) = *(float *)(p + 0x14) + (*(float *)(p + 0x18) - *(float *)(p + 0x14)) * f22;
        FastVecScale(a, b, *(float *)(p + 0x1C) * math_ease_out_quad(f22));
    } else {
        f21 = IntToFloat(*(unsigned char *)(p + 0x12));
        f20 = IntToFloat(*(unsigned char *)(p + 0x12));
        f20 = f20 * math_square(f22);
        *(int *)(self + 4) = *(int *)(p + 0xC) | (FloatToInt(f21 - f20) << 24);
        FastVecScale(a, b, *(float *)(p + 0x1C));
    }
    FastVecAdd(self + 0x10, a, self + 0x10);
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(p + 0x10);
    if (FastDecTimer(self + 0xA) != 0) {
        if (*(unsigned char *)(p + 0x13) == 0) {
            *(unsigned char *)(p + 0x13) = 1;
            *(unsigned char *)(p + 0x11) = 0x11;
            *(short *)(self + 0xA) = 0x11;
        } else {
            part_kill(self);
        }
    }
}





