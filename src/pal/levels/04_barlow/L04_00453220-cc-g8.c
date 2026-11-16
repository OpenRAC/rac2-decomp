#include "names.h"
/* func_PAL_L04_00453220, the PAL copy of func_L04_0044D860: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; scale D_L04_001B1898. */
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
extern void FastVecSub(char *, char *, char *);

extern u8 g_pull_anim_index;
extern u8 *g_hero_l04_moby;
extern f32 g_pull_step_speed __attribute__((sda));
extern f32 g_pull_side_speed __attribute__((sda));
extern f32 g_pull_base_scale __attribute__((sda));
extern int g_pull_decay_value __attribute__((sda));
extern f32 g_pull_min_value __attribute__((sda));
extern void func_PAL_002A7E68(void *, int, int, int);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float IntToFloat(int);

int func_PAL_L04_00453220(u8 *object) {
    float delta[4];
    u8 *data = *(u8 **)(object + 0x68);
    float heading, length, step, ratio, angle, minimum, scale, decay;
    u8 *target;
    int result;
    if (object[0x43] != g_pull_anim_index)
        func_PAL_002A7E68(object, g_pull_anim_index, 0, 8);
    if (g_hero_l04_moby) {
        heading = mat_fast_helper_a(*(float *)(object + 0x10) - *(float *)(g_hero_l04_moby + 0x10),
                               *(float *)(object + 0x14) - *(float *)(g_hero_l04_moby + 0x14));
        angle = FastAddRotations(*(float *)(object + 0xF8),
            fast_subtract_rotations(heading, *(float *)(object + 0xF8)) * 0.1f);
        target = g_hero_l04_moby + 0x10;
        *(float *)(object + 0xF8) = angle;
        FastVecSub((char *)delta, (char *)target, (char *)object + 0x10);
        delta[2] -= *(float *)(data + 0x220);
        length = FastVecLength(delta);
        if (length != 0.0f) {
            float fraction;
            step = g_pull_step_speed * 0.020000001f;
            if (length < step)
                step = length;
            fraction = step / length;
            FastVecScale(delta, delta, fraction);
            FastVecAdd(object + 0x10, object + 0x10, delta);
            delta[0] = math_fast_sin_or_cos_a(FastAddRotations(heading, 1.5707964897155762f)) * 0.020000001f * g_pull_side_speed;
            delta[1] = math_fast_sin_or_cos_b(FastAddRotations(heading, 1.5707964897155762f)) * 0.020000001f * g_pull_side_speed;
            delta[2] = 0.0f;
            FastVecAdd(object + 0x10, object + 0x10, delta);
        }
        decay = IntToFloat((((int)(g_pull_decay_value) * 5 + 2) / 6));
        minimum = g_pull_min_value;
        *(float *)(object + 0x2C) -= *(float *)(data + 0x230) / decay;
        if (*(float *)(object + 0x2C) < minimum)
            *(float *)(object + 0x2C) = minimum;
        ratio = *(float *)(object + 0x2C) / *(float *)(data + 0x230);
        if (ratio > 1.0f)
            ratio = 1.0f;
        scale = g_pull_base_scale + (*(float *)(data + 0x30) - g_pull_base_scale) * ratio;
        {
            u8 *hero = g_hero_l04_moby;
            *(float *)(data + 0x220) = scale;
            if (!hero || hero[0x20] == 0x5A || (s8)hero[0x20] < 0)
                result = 1;
            else
                result = 0;
            goto done;
        }
    }
    result = 1;
done:
    return result;
}
