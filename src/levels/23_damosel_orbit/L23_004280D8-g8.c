#include "names.h"
/* Spawns a projectile child: copies the launch direction and position, aims it, and
   queues its two particle trails (func_002C2210). The table address is an .sdata macro
   word, rebuilt for each call. */

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

/* Creates a child shot with a particle trail, launched from a parent object in a given
   direction. */
u8 *flying_shot_create_child(u8 *parent, TI128 *direction, TI128 *position, s32 hit_state, float radius) {
    u8 *obj = CreateMoby(0x1230 /* moby class 4656 */);
    u8 *payload;
    float rotationRandom;
    float particleRandom;
    float vel0, vel1, vel2, vel3;

    if (obj != 0) {
        obj[0x30] = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0xBC] = hit_state;
        obj[0x20] = 0;
        *(s64 *)(obj + 0x38) = *(s64 *)(parent + 0x38);
        qcopy(obj + 0x10, position);
        payload = *(u8 **)(obj + 0x68);
        qcopy(payload, direction);
        *(u8 **)(payload + 0x10) = parent;
        *(float *)(payload + 0x14) = radius;
        *(float *)(payload + 0x20) = 0.15f;
        *(u16 *)(obj + 0x34) |= 0x208;
        *(float *)(obj + 0xF8) = FastAddRotations(mat_fast_helper_a(((float *)direction)[0], ((float *)direction)[1]), 1.5707965f);
        *(float *)(obj + 0xF0) = -mat_fast_helper_a(vec_length_xy(direction), ((float *)direction)[2]);
        rotationRandom = math_random_angle();
        math_apply_axis_rotation_to_quat(obj + 0xE0, obj + 0xE0, obj + 0xD0, rotationRandom);
        math_apply_axis_rotation_to_quat(obj + 0xC0, obj + 0xC0, obj + 0xD0, rotationRandom);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        obj[0x23] = 0x80;
        *(float *)(obj + 0x2C) = g_flying_shot_child_scale;
        *(u16 *)(obj + 0x34) |= 0x100;
        *(s32 *)(payload + 0x24) = 0;
        particleRandom = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(obj + 0x10, 0xF, g_flying_shot_spark_effect_a, 0, 10, g_zero_l23_vec, particleRandom * 0.3f, particleRandom, 0.0f, 0);
        part_spawn_ground_effect(obj + 0x10, 0xF, g_flying_shot_spark_effect_b, 1, -10, g_zero_l23_vec, particleRandom * 0.04f, particleRandom * 0.4f, 0.0f, 0);
        vel0 = g_flying_shot_vel_init_a;
        vel1 = g_flying_shot_vel_init_b;
        vel2 = g_flying_shot_vel_init_c;
        vel3 = g_flying_shot_vel_init_d;
        *(float *)(payload + 0x30) = vel0;
        *(float *)(payload + 0x34) = vel1;
        *(float *)(payload + 0x38) = vel2;
        *(float *)(payload + 0x3C) = vel3;
    }
    return obj;
}
