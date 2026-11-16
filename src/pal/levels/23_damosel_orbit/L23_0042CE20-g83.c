#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_flying_shot_child_scale __attribute__((sda));
extern s32 g_flying_shot_spark_effect_a __attribute__((sda));
extern s32 g_flying_shot_spark_effect_b __attribute__((sda));
extern float g_flying_shot_vel_init_a __attribute__((sda));
extern float g_flying_shot_vel_init_b __attribute__((sda));
extern float g_flying_shot_vel_init_c __attribute__((sda));
extern float g_flying_shot_vel_init_d __attribute__((sda));
extern u8 g_zero_l23_vec[] MACRO_ADDR;
extern void *CreateMoby(s32);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float vec_length_xy(void *);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void *part_spawn_ground_effect(void *, s32, s32, s32, s32, void *, float, float, float, s32);

/* Creates a child shot of the parent moving along its direction, with a ground effect trail. (PAL) */
u8 *flying_shot_create_child_pal(u8 *parent, TI128 *dir_vec, TI128 *start_pos, s32 hit_state, float shot_damage) {
    u8 *child = CreateMoby(0x1230);
    u8 *payload;
    float rotation_random;
    float particle_random;
    float init_vel_0, init_vel_1, init_vel_2, init_vel_3;

    if (child != 0) {
        child[0x30] = 0xFF;
        *(s16 *)(child + 0x32) = 0xFF;
        child[0x31] = 1;
        child[0xBC] = hit_state;
        child[0x20] = 0;
        *(s64 *)(child + 0x38) = *(s64 *)(parent + 0x38);
        qcopy(child + 0x10, start_pos);
        payload = *(u8 **)(child + 0x68);
        qcopy(payload, dir_vec);
        *(u8 **)(payload + 0x10) = parent;
        *(float *)(payload + 0x14) = shot_damage;
        *(float *)(payload + 0x20) = 0.15f;
        *(u16 *)(child + 0x34) |= 0x208;
        *(float *)(child + 0xF8) = FastAddRotations(mat_fast_helper_a(((float *)dir_vec)[0], ((float *)dir_vec)[1]), 1.5707965f);
        *(float *)(child + 0xF0) = -mat_fast_helper_a(vec_length_xy(dir_vec), ((float *)dir_vec)[2]);
        rotation_random = math_random_angle();
        math_apply_axis_rotation_to_quat(child + 0xE0, child + 0xE0, child + 0xD0, rotation_random);
        math_apply_axis_rotation_to_quat(child + 0xC0, child + 0xC0, child + 0xD0, rotation_random);
        euler_rotation_basis(child + 0xC0, child + 0xF0);
        child[0x23] = 0x80;
        *(float *)(child + 0x2C) = g_flying_shot_child_scale;
        *(u16 *)(child + 0x34) |= 0x100;
        *(s32 *)(payload + 0x24) = 0;
        particle_random = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(child + 0x10, 0xC, g_flying_shot_spark_effect_a, 0, 10, g_zero_l23_vec, particle_random * 0.3f, particle_random, 0.0f, 0);
        part_spawn_ground_effect(child + 0x10, 0xC, g_flying_shot_spark_effect_b, 1, -10, g_zero_l23_vec, particle_random * 0.04f, particle_random * 0.4f, 0.0f, 0);
        init_vel_0 = g_flying_shot_vel_init_a;
        init_vel_1 = g_flying_shot_vel_init_b;
        init_vel_2 = g_flying_shot_vel_init_c;
        init_vel_3 = g_flying_shot_vel_init_d;
        *(float *)(payload + 0x30) = init_vel_0;
        *(float *)(payload + 0x34) = init_vel_1;
        *(float *)(payload + 0x38) = init_vel_2;
        *(float *)(payload + 0x3C) = init_vel_3;
    }
    return child;
}
