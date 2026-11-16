#include "common.h"

extern float g_anchor_move_seconds __attribute__((sda));

extern void FastVecSub(float *, float *, float *);

extern void FastVecAdd(float *, float *, float *);

extern void FastVecScale(float *, float *, float);

extern float math_fast_sin_or_cos_a(float);

extern float IntToFloat(s32);

extern s32 FloatToInt(float);

/* Scales the sub-object's angle by pi, takes the frame it names and measures the object's
   own height against the frame's, writing the difference into the sub-object. */
void platform_place_on_path_by_timer(char *object_in, char *path_in, char *old_position_in)
{
    f32 delta[4];
    f32 wave;
    f32 value;
    f32 ease;
    f32 fraction;
    s32 index;
    s32 truncated;
    char *path = path_in;
    char *moby = object_in;
    char *vars;
    char *old_position = old_position_in;

    vars = *(char **)(moby + 0x68);
    value = *(f32 *)(vars + 0xA8);
    value = value * 3.1415929f;
    value = value / (g_anchor_move_seconds * 60.0f);
    wave = math_fast_sin_or_cos_a(value);
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
    *(f32 *)(vars + 0xC0) = *(f32 *)(moby + 0x18) - *(f32 *)(old_position + 8);
}
