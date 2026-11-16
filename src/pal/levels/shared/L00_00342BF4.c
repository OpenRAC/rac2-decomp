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

/* Updates a flying particle (PAL): moves it along its velocity, fades it and ends it (hand-adapted from func_002C8880). */
void part_update_flying_pal(char *self) {
    float a[4];
    float b[4];
    char *p = self + 0x20;
    float remaining, faded_alpha, alpha, progress;
    int color;

    b[0] = *(float *)(self + 0x20);
    b[1] = *(float *)(p + 4);
    b[2] = *(float *)(p + 8);
    b[3] = 0;
    vec_transform_or_copy(self + 0x10, self + 0x10);
    remaining = IntToFloat(*(short *)(self + 0xA)) / IntToFloat(*(unsigned char *)(p + 0x11));
    progress = 1.0f - remaining;
    if (*(unsigned char *)(p + 0x13) == 0) {
        color = FastTweenColor(progress, 0x103080, *(int *)(p + 0xC));
        *(int *)(self + 4) = color | (*(unsigned char *)(p + 0x12) << 24);
        *(float *)(self + 0xC) = *(float *)(p + 0x14) + (*(float *)(p + 0x18) - *(float *)(p + 0x14)) * progress;
        FastVecScale(a, b, *(float *)(p + 0x1C) * math_ease_out_quad(progress));
    } else {
        alpha = IntToFloat(*(unsigned char *)(p + 0x12));
        faded_alpha = IntToFloat(*(unsigned char *)(p + 0x12));
        faded_alpha = faded_alpha * math_square(progress);
        *(int *)(self + 4) = *(int *)(p + 0xC) | (FloatToInt(alpha - faded_alpha) << 24);
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





