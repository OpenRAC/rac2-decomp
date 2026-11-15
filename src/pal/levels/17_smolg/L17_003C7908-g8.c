#include "common.h"

/* func_PAL_L17_003C7908, the PAL copy of func_L17_003C3AF0: the same C, where the period
   D * 60 becomes the 50 Hz (D * 300 + 2) / 6. */

extern float D_L17_001B0240 __attribute__((sda));

extern void FastVecSub(float *, float *, float *);

extern void FastVecAdd(float *, float *, float *);

extern void FastVecScale(float *, float *, float);

extern float math_fast_sin_or_cos_a(float);

extern float IntToFloat(s32);

extern s32 FloatToInt(float);

/* Scales the sub-object's angle by pi, takes the frame it names and measures the object's
   own height against the frame's, writing the difference into the sub-object. */
void func_PAL_L17_003C7908(char *a0, char *a1, char *a2)
{
    f32 v[4];
    f32 f0;
    f32 f12;
    f32 f21;
    f32 f20;
    s32 s0;
    s32 v0;
    char *s1 = a1;
    char *s2 = a0;
    char *s3;
    char *s4 = a2;

    s3 = *(char **)(s2 + 0x68);
    f12 = *(f32 *)(s3 + 0xA8);
    f12 = f12 * 3.1415929f;
    f12 = f12 / ((D_L17_001B0240 * 300.0f + 2.0f) * 0.16666667f);
    f0 = math_fast_sin_or_cos_a(f12);
    f21 = 1.0f - f0;
    f21 = f21 * 0.5f;
    f0 = IntToFloat(*(s32 *)s1 - 1);
    f12 = f0 * f21;
    v0 = FloatToInt(f12);
    s0 = v0;
    f20 = IntToFloat(*(s32 *)s1 - 1) * f21 - IntToFloat(s0);
    if (s0 == *(s32 *)s1 - 1) {
        qcopy(s2 + 0x10, s1 + (s0 * 16 + 0x10));
    } else {
        FastVecSub(v, (f32 *)(s1 + (s0 * 16 + 0x20)), (f32 *)(s1 + (s0 * 16 + 0x10)));
        FastVecScale(v, v, f20);
        FastVecAdd((f32 *)(s2 + 0x10), v, (f32 *)(s1 + (s0 * 16 + 0x10)));
    }
    *(f32 *)(s3 + 0xC0) = *(f32 *)(s2 + 0x18) - *(f32 *)(s4 + 8);
}
