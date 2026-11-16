#include "common.h"

/* func_PAL_L17_003C7908, the PAL copy of func_L17_003C3AF0: the same C, where the period
   D * 60 becomes the 50 Hz (D * 300 + 2) / 6. */

extern float g_anchor_move_seconds __attribute__((sda));

extern void FastVecSub(float *, float *, float *);

extern void FastVecAdd(float *, float *, float *);

extern void FastVecScale(float *, float *, float);

extern float math_fast_sin_or_cos_a(float);

extern float IntToFloat(s32);

extern s32 FloatToInt(float);

/* Scales the sub-object's angle by pi, takes the frame it names and measures the object's
   own height against the frame's, writing the difference into the sub-object. */
void platform_place_on_path_by_timer_pal(char *moby, char *path, char *old_pos)
{
    f32 step[4];
    f32 value;
    f32 angle;
    f32 progress;
    f32 fraction;
    s32 index;
    s32 whole;
    char *path_ref = path;
    char *moby_ref = moby;
    char *vars;
    char *old_ref = old_pos;

    vars = *(char **)(moby_ref + 0x68);
    angle = *(f32 *)(vars + 0xA8);
    angle = angle * 3.1415929f;
    angle = angle / ((g_anchor_move_seconds * 300.0f + 2.0f) * 0.16666667f);
    value = math_fast_sin_or_cos_a(angle);
    progress = 1.0f - value;
    progress = progress * 0.5f;
    value = IntToFloat(*(s32 *)path_ref - 1);
    angle = value * progress;
    whole = FloatToInt(angle);
    index = whole;
    fraction = IntToFloat(*(s32 *)path_ref - 1) * progress - IntToFloat(index);
    if (index == *(s32 *)path_ref - 1) {
        qcopy(moby_ref + 0x10, path_ref + (index * 16 + 0x10));
    } else {
        FastVecSub(step, (f32 *)(path_ref + (index * 16 + 0x20)), (f32 *)(path_ref + (index * 16 + 0x10)));
        FastVecScale(step, step, fraction);
        FastVecAdd((f32 *)(moby_ref + 0x10), step, (f32 *)(path_ref + (index * 16 + 0x10)));
    }
    *(f32 *)(vars + 0xC0) = *(f32 *)(moby_ref + 0x18) - *(f32 *)(old_ref + 8);
}
