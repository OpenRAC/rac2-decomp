#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern u8 *D_L16_001B16C0 __attribute__((sda));
extern float D_L16_001B1780 __attribute__((sda));
extern float D_L16_001B1784 __attribute__((sda));
extern float D_L16_001B1788 __attribute__((sda));
extern float D_L16_001B1790[4] __attribute__((sda));
extern void moby_transform_joint_point(void *, s32, void *);
extern void anim_start_blended(void *, s32, s32, s32);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void snivelak_spawn_shot_from_matrix(void *, void *, s32);
extern s32 CollLine(void *, void *, s32, void *, s32);

/* Fires a shot from the boss's current arm toward the player with a small random spread, then switches to the other arm. */
void snivelak_fire_arm_shot(u8 *moby)
{
    float matrix[16];
    float origin[4];
    float forward[4];
    float random[4];
    float hero[4];
    float child[4];
    float target[4];
    u8 *state;
    u8 **children;
    s32 index;
    float angle;
    float zero;
    float degree;
    float spread;
    if (D_L16_001B16C0) {
        state = *(u8 **)(moby + 0x68);
        children = (u8 **)(state + 0x238);
        moby_transform_joint_point(*(u8 **)((u32)children + (*(s32 *)(state + 0x240) << 2)), 0, matrix);
        children = (u8 **)((u32)children + (*(s32 *)(state + 0x240) << 2));
        anim_start_blended(*children, 1, 0, 3);
        *(TI128 *)origin = *(TI128 *)(matrix + 12);
        vec_scale_to_length(forward, matrix, 20.0f);
        FastVecAdd(forward, forward, origin);
        *(TI128 *)hero = *(TI128 *)(D_L16_001B16C0 + 0x10);
        hero[2] += 2.0f;
        zero = 0.0f;
        degree = 0.017453294f;
        angle = mat_fast_helper_a(*(float *)(moby + 0x10) - *(float *)(D_L16_001B16C0 + 0x10), *(float *)(moby + 0x14) - *(float *)(D_L16_001B16C0 + 0x14));
        spread = math_random_signed_float_range(zero, D_L16_001B1780);
        angle = FastAddRotations(angle, spread * degree);
        spread = math_random_float_range(zero, D_L16_001B1784);
        vec_build_spherical_offset(random, D_L16_001B1788, angle, spread * degree);
        FastVecAdd(random, random, hero);
        snivelak_spawn_shot_from_matrix(moby, origin, 180);
        index = (*(s32 *)(state + 0x240) + 1) & 1;
        *(s32 *)(state + 0x240) = index;
        *(TI128 *)child = *(TI128 *)D_L16_001B1790;
        if (index) child[1] = -child[1];
        matrix_mul_vec3(child, child, *(u8 **)(state + 0x1F0) + 0xC0);
        FastVecAdd(child, child, *(u8 **)(state + 0x1F0) + 0x10);
        *(TI128 *)target = *(TI128 *)(D_L16_001B16C0 + 0x10);
        target[2] += 4.0f;
        if (CollLine(child, target, 2, *(u8 **)(state + 0x1F0), 0))
            *(s32 *)(state + 0x240) = (*(s32 *)(state + 0x240) + 1) & 1;
    }
}
