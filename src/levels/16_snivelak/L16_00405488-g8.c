#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *CreateMoby(s32);
extern void euler_rotation_basis(void *, void *);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float vec_length_xy(void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern u8 *part_spawn_ground_effect(void *, s32, s32, s32, s32, void *, float, float, float, s32);
extern float g_snivelak_shot_scale __attribute__((sda));
extern s32 g_snivelak_glow_texture_a __attribute__((sda));
extern s32 g_snivelak_glow_texture_b __attribute__((sda));
extern u8 g_particle_template[] __attribute__((sda));

/* Spawns the 0xEBD object at the position with the velocity, aims it along the velocity,
   hands it to its owner and starts two particle bursts on it. */
/* Spawns a flying shot at the position, aims it along its velocity and starts two particle bursts. */
u8 *snivelak_spawn_aimed_shot(float speed, u8 *owner, float *velocity, TI128 *position)
{
    u8 *obj;
    u8 *state;
    u8 *pos;
    u8 *rotation;
    u8 *axis;
    float scale;
    float angle;
    obj = CreateMoby(0xEBD);
    if (obj) {
        obj[0x30] = 255;
        *(u16 *)(obj + 0x32) = 255;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(s64 *)(obj + 0x38) = *(s64 *)(owner + 0x38);
        pos = obj + 0x10;
        qcopy(pos, position);
        state = *(u8 **)(obj + 0x68);
        qcopy(state, velocity);
        *(u8 **)(state + 0x10) = owner;
        *(float *)(state + 0x14) = speed;
        *(float *)(state + 0x20) = 0.15f;
        *(u16 *)(obj + 0x34) |= 0x208;
        rotation = obj + 0xC0;
        axis = obj + 0xD0;
        *(float *)(obj + 0xF8) = FastAddRotations(mat_fast_helper_a(velocity[0], velocity[1]), 1.5707965f);
        *(float *)(obj + 0xF0) = -mat_fast_helper_a(vec_length_xy(velocity), velocity[2]);
        angle = math_random_angle();
        math_apply_axis_rotation_to_quat(obj + 0xE0, obj + 0xE0, axis, angle);
        math_apply_axis_rotation_to_quat(rotation, rotation, axis, angle);
        euler_rotation_basis(rotation, obj + 0xF0);
        obj[0x23] = 128;
        *(float *)(obj + 0x2C) = g_snivelak_shot_scale;
        *(u16 *)(obj + 0x34) |= 0x100;
        *(s32 *)(state + 0x24) = 0;
        scale = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(pos, 15, g_snivelak_glow_texture_a, 0, 10, g_particle_template, scale * 0.3f, scale, 0.0f, 0);
        part_spawn_ground_effect(pos, 15, g_snivelak_glow_texture_b, 1, -10, g_particle_template, scale * 0.04f, scale * 0.4f, 0.0f, 0);
    }
    return obj;
}
