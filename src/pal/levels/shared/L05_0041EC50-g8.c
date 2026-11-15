/* func_PAL_L05_0041EC50, the PAL copy of func_L05_00419F10: the same C, where the speed scale becomes 0.02, the sprite lifetime 50 and the sprite gravity is scaled by 1.44. */
#include "common.h"

typedef int BurstVector __attribute__((mode(TI)));
extern float D_L05_001B105C __attribute__((sda));
extern float D_L05_001B1060 __attribute__((sda));
extern float D_L05_001B1064 __attribute__((sda));
extern float D_L05_001B1068 __attribute__((sda));
extern float D_L05_001B106C __attribute__((sda));
extern float D_L05_001B1070 __attribute__((sda));
extern float D_L05_001B1074 __attribute__((sda));
extern char D_L05_001B96C0[];
extern u8 *D_L05_001FF240[] NOT_SDA;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_ground_effect(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern int FloatToInt(float);

/* Emits count pairs of sprites (func_002C2210) at a jittered pos, each heading along
   the direction to D_L05_001B96C0 turned by a random angle about the up axis. */
void func_PAL_L05_0041EC50(float *pos, int count, int color, char *owner)
{
    float dir[4], tmp[4], toward[4], up[4], half[4];
    int i, sign;
    float size, angle;
    char *sprite;

    *(BurstVector *)up = 0;
    up[2] = 1.0f;
    up[3] = 1.0f;
    if (*(int *)(*(char **)(owner + 0x68) + 0x30)) {
        D_L05_001B105C = 0.1f;
        D_L05_001B1060 = 6.0f;
        D_L05_001B1064 = 2.0f;
        D_L05_001B1068 = 10.0f;
    }
    FastVecSub(toward, D_L05_001B96C0, pos);
    vec_scale_to_length(half, toward, 0.5f);
    toward[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(D_L05_001B1070, D_L05_001B1074);
        sign = math_random_int_below(2);
        if (!sign)
            sign = sign - 1;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(dir, toward, up, angle);
        vec_scale_to_length(dir, dir, math_random_float_range(D_L05_001B105C, D_L05_001B1060) * 0.020000001f);
        dir[2] = math_random_float_range(D_L05_001B1064, D_L05_001B1068) * 0.020000001f;
        FastVecAdd(tmp, pos, half);
        pos[0] += math_random_signed_float_range(0.0f, 0.15f);
        pos[1] += math_random_signed_float_range(0.0f, 0.15f);
        pos[2] += math_random_signed_float_range(0.0f, 0.15f);
        sprite = part_spawn_ground_effect(pos, 50, size * 0.1f, size, color, 0, sign, dir, D_L05_001B106C * 1.44f, 0);
        if (sprite) {
            sprite[2] = D_L05_001FF240[97][6];
            sprite[9] = FloatToInt(4.0f) + 0x70;
        }
        sprite = part_spawn_ground_effect(pos, 50, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, dir,
                               D_L05_001B106C * 1.44f, 0);
        if (sprite) {
            sprite[2] = D_L05_001FF240[97][6];
            sprite[9] = FloatToInt(4.0f) + 0x70;
        }
    }
}
