#include "common.h"

extern float D_L17_001B0240 __attribute__((sda));

extern void func_00282CF0(float *, float *, float *);

extern void func_00282CC0(float *, float *, float *);

extern void func_00282D30(float *, float *, float);

extern float func_00283180(float);

extern float func_00283CE0(s32);

extern s32 func_00283CF0(float);

/* Scales the sub-object's angle by pi, takes the frame it names and measures the object's
   own height against the frame's, writing the difference into the sub-object. */
void func_L17_003C3AF0(char *objectIn, char *pathIn, char *oldPositionIn)
{
    f32 delta[4];
    f32 wave;
    f32 value;
    f32 ease;
    f32 fraction;
    s32 index;
    s32 truncated;
    char *path = pathIn;
    char *moby = objectIn;
    char *vars;
    char *oldPosition = oldPositionIn;

    vars = *(char **)(moby + 0x68);
    value = *(f32 *)(vars + 0xA8);
    value = value * 3.1415929f;
    value = value / (D_L17_001B0240 * 60.0f);
    wave = FastSinOrCosA(value);
    ease = 1.0f - wave;
    ease = ease * 0.5f;
    wave = IntToFloat(*(s32 *)path - 1);
    value = wave * ease;
    truncated = FloatToInt(value);
    index = truncated;
    fraction = IntToFloat(*(s32 *)path - 1) * ease - IntToFloat(index);
    if (index == *(s32 *)path - 1) {
        qcopy(moby + 0x10, path + (index * 16 + 0x10));
    } else {
        FastVecSub(delta, (f32 *)(path + (index * 16 + 0x20)), (f32 *)(path + (index * 16 + 0x10)));
        FastVecScale(delta, delta, fraction);
        FastVecAdd((f32 *)(moby + 0x10), delta, (f32 *)(path + (index * 16 + 0x10)));
    }
    *(f32 *)(vars + 0xC0) = *(f32 *)(moby + 0x18) - *(f32 *)(oldPosition + 8);
}
