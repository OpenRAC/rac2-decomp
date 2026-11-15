#include "include_asm.h"

#include "common.h"
typedef int BossQuadword __attribute__((mode(TI)));
extern u8 *D_L16_001B2C0C;
extern float D_L16_001B9B00[4];
extern float D_L16_001B18CC __attribute__((sda));
extern float D_L16_001B18D0 __attribute__((sda));
extern float D_L16_001B18D4 __attribute__((sda));
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern u8 *CreateMoby(int);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern void moby_set_state(u8 *, int, int);
extern void vec_store_helper(void *);
extern int math_fast_helper_a(void *, float);
extern void transform_vector(void *, void *, void *);
extern float FastAddRotations(float, float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void moby_mark_spawned(void *), func_002A0F48(void *);
extern void func_PAL_L16_00418580(u8 *);

/* Creates an aimed projectile or a random trajectory across the arena. */
u8 *func_PAL_L16_00418260(u8 *moby, int aimed)
{
    float position[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *object = CreateMoby(0x9b0);
    u8 *motion;
    float angle;
    if (object) {
        moby_init_child_from_parent(object, moby);
        moby_set_state(object, 0, -1);
        motion = *(u8 **)(object + 0x68);
        if (aimed) {
            *(BossQuadword *)(object + 0x10) = *(BossQuadword *)D_L16_001B9B00;
            *(float *)(object + 0x18) += 20.0f;
            angle = FastAddRotations(mat_fast_helper_a(*(float *)(*(u8 **)(state + 0x24c) + 0x10) - *(float *)(object + 0x10), *(float *)(*(u8 **)(state + 0x24c) + 0x14) - *(float *)(object + 0x14)), 1.5707964f);
            position[0] = math_fast_sin_or_cos_a(angle) * D_L16_001B18CC;
            position[1] = math_fast_sin_or_cos_b(angle) * D_L16_001B18CC;
            position[2] = 0.0f;
            FastVecAdd(position, position, moby + 0x10);
            position[2] = *(float *)(state + 0x264) + D_L16_001B18D0;
            *(BossQuadword *)(motion + 0x10) = *(BossQuadword *)position;
            FastVecSub(target, position, object + 0x10);
            FastVecScale(motion, target, 1.0f / D_L16_001B18D4);
            *(int *)(motion + 0x30) = ((s32)(FloatToInt(D_L16_001B18D4 * 1.2f)) * 5 + 2) / 6;
        } else {
            u8 *scatterState = *(u8 **)(moby + 0x68);
            vec_store_helper(position);
            position[0] = math_random_float_range(-1.0f, 1.0f);
            position[2] = math_random_float_range(-1.0f, 1.0f);
            vec_store_helper(target);
            target[0] = math_random_float_range(-1.0f, 1.0f);
            target[2] = math_random_float_range(-1.0f, 1.0f);
            position[1] = math_random_int_below(2) ? 1.0f : -1.0f;
            target[1] = -position[1];
            transform_vector(position, position, D_L16_001B2C0C + *(int *)(scatterState + 0x19c) * 128);
            position[3] = 3.0f;
            if (math_fast_helper_a(position, 255.0f) != -1) { moby_mark_spawned(object); return 0; }
            transform_vector(target, target, D_L16_001B2C0C + *(int *)(scatterState + 0x19c) * 128);
            *(BossQuadword *)(object + 0x10) = *(BossQuadword *)position;
            *(BossQuadword *)(motion + 0x10) = *(BossQuadword *)target;
            FastVecSub(motion, target, position);
            FastVecScale(motion, motion, 0.002f);
            *(int *)(motion + 0x30) = 500;
        }
        *(float *)(object + 0xf8) = mat_fast_helper_a(*(float *)motion, *(float *)(motion + 4));
        *(void (**)(u8 *))(object + 0x64) = func_PAL_L16_00418580;
        func_002A0F48(object);
    }
    return object;
}
