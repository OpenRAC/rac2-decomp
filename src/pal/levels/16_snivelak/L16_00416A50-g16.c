#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *g_snivelak_target __attribute__((sda));
extern float g_snivelak_arm_spread_a __attribute__((sda));
extern float g_snivelak_arm_spread_b __attribute__((sda));
extern float g_snivelak_arm_shot_radius __attribute__((sda));
extern float g_snivelak_child_template[4] __attribute__((sda));
extern void moby_transform_joint_point(void *, s32, void *);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern u8 *func_PAL_L16_00412A98(void *, void *, s32);
extern s32 CollLine(void *, void *, s32, void *, s32);

void snivelak_fire_arm_shot_pal(u8 *arg)
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
    if (g_snivelak_target) {
        state = *(u8 **)(arg + 0x68);
        children = (u8 **)(state + 0x238);
        moby_transform_joint_point(*(u8 **)((u32)children + (*(s32 *)(state + 0x240) << 2)), 0, matrix);
        children = (u8 **)((u32)children + (*(s32 *)(state + 0x240) << 2));
        func_PAL_002A7E68(*children, 1, 0, 3);
        *(TI128 *)origin = *(TI128 *)(matrix + 12);
        vec_scale_to_length(forward, matrix, 20.0f);
        FastVecAdd(forward, forward, origin);
        *(TI128 *)hero = *(TI128 *)(g_snivelak_target + 0x10);
        hero[2] += 2.0f;
        zero = 0.0f;
        degree = 0.017453294f;
        angle = mat_fast_helper_a(*(float *)(arg + 0x10) - *(float *)(g_snivelak_target + 0x10), *(float *)(arg + 0x14) - *(float *)(g_snivelak_target + 0x14));
        spread = math_random_signed_float_range(zero, g_snivelak_arm_spread_a);
        angle = FastAddRotations(angle, spread * degree);
        spread = math_random_float_range(zero, g_snivelak_arm_spread_b);
        vec_build_spherical_offset(random, g_snivelak_arm_shot_radius, angle, spread * degree);
        FastVecAdd(random, random, hero);
        func_PAL_L16_00412A98(arg, origin, 150);
        index = (*(s32 *)(state + 0x240) + 1) & 1;
        *(s32 *)(state + 0x240) = index;
        *(TI128 *)child = *(TI128 *)g_snivelak_child_template;
        if (index) child[1] = -child[1];
        matrix_mul_vec3(child, child, *(u8 **)(state + 0x1F0) + 0xC0);
        FastVecAdd(child, child, *(u8 **)(state + 0x1F0) + 0x10);
        *(TI128 *)target = *(TI128 *)(g_snivelak_target + 0x10);
        target[2] += 4.0f;
        if (CollLine(child, target, 2, *(u8 **)(state + 0x1F0), 0))
            *(s32 *)(state + 0x240) = (*(s32 *)(state + 0x240) + 1) & 1;
    }
}
