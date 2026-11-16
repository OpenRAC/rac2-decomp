#include "include_asm.h"
#include "common.h"

/* func_PAL_L01_003E0710, the PAL copy of func_L01_003DC078: the same C, where speeds and
   accelerations grow by 6/5, and particle lifetimes take (x * 5 + 2) / 6 for 50 Hz. */
extern f32 vec_distance_xy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 coll_sweep_from_object(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 coll_cast_object_line(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern f32 math_random_float_range(f32, f32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void vec_build_spherical_offset(void *, f32, f32, f32);
extern s32 func_001163B0(void);
extern s32 FloatToInt(f32);
extern u8 *part_spawn_trail(void *, void *, void *, u32, u32, s32, s32, s32, s32);

void muckdweller_fire_spit_shot_pal(u8 *moby, s32 skip) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 end[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));
    f32 velocity[4] __attribute__((aligned(16)));
    f32 acceleration[4] __attribute__((aligned(16)));
    f32 particle_pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    f32 angle, yaw, distance, height;
    u8 *particle;

    distance = vec_distance_xy(moby + 0x10, *(u8 **)(state + 0x2F0) + 0x10);
    height = *(f32 *)(*(u8 **)(state + 0x2F0) + 0x18) - *(f32 *)(moby + 0x18);
    angle = fast_subtract_rotations(mat_fast_helper_a(distance, height), *(f32 *)(moby + 0xF4));
    if (angle > 0.3490659f) angle = 0.3490659f;
    else if (angle < -0.3490659f) angle = -0.3490659f;
    angle = FastAddRotations(angle, *(f32 *)(moby + 0xF4));
    yaw = *(f32 *)(moby + 0xF8);

    moby_transform_joint_to_world(moby, 0, pos);
    vec_scale_to_length(offset, moby + 0xC0, -0.4f);
    FastVecAdd(pos, pos, offset);
    vec_scale_to_length(offset, moby + 0xE0, 0.3f);
    FastVecAdd(pos, pos, offset);

    if (*(s16 *)(*(u8 **)(state + 0x2F0) + 0xAA) == 0xB1A) {
        coll_sweep_from_object(moby, pos, 1.0f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
        return;
    }

    particle = *(u8 **)(state + 0x3F0);
    if (particle) {
        if (particle[0] == 2 && particle[1] != 0x80) {
            distance = vec_distance_xy(pos, particle + 0x10);
            if (*(f32 *)(state + 0x3F4) < distance) *(f32 *)(state + 0x3F4) = distance;
        } else {
            *(u8 **)(state + 0x3F0) = 0;
            *(f32 *)(state + 0x3F4) = 3.0f;
        }
        vec_build_spherical_offset(end, *(f32 *)(state + 0x3F4), yaw, angle);
        FastVecAdd(end, end, pos);
        coll_cast_object_line(moby, pos, end, (f32)state[0x34], 0x4000001, 1.0f, 0, 1, 0);
        coll_sweep_from_object(moby, end, 0.3f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
    }
    if (skip) return;

    {
        s32 i, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned;

        velocity[3] = 0.2f;
        acceleration[3] = 1.0f;
        for (i = 0; i < 2; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x50608040;
            color2 = 0x10608040;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x30304020;
                color2 = 0x30304020;
            }
            qcopy(particle_pos, pos);
            particle_pos[0] += math_random_float_range(-0.18f, 0.18f);
            particle_pos[1] += math_random_float_range(-0.18f, 0.18f);
            particle_pos[2] += math_random_float_range(-0.18f, 0.18f);
            vec_build_spherical_offset(velocity, 0.18f, yaw, angle);
            velocity[2] += math_random_float_range(0.009000001f, 0.011000001f);
            vec_build_spherical_offset(acceleration, 0.010000001f,
                          FastAddRotations(yaw, math_random_float_range(-9.0f, 9.0f) * 0.017453294f), angle);
            acceleration[2] += math_random_float_range(-0.036000002f, -0.044000003f);
            life = FloatToInt((math_random_float_range(2.0f, 4.0f) * 5.0f + 2.0f) * 0.16666667f);
            size = FloatToInt((math_random_float_range(20.0f, 24.0f) * 5.0f + 2.0f) * 0.16666667f);
            duration = FloatToInt((math_random_float_range(30.0f, 36.0f) * 5.0f + 2.0f) * 0.16666667f);
            spawned = part_spawn_trail(particle_pos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned) {
                if (!*(u8 **)(state + 0x3F0)) *(u8 **)(state + 0x3F0) = spawned;
                if (variant) spawned[3] = 0x48;
            }
        }
    }
    {
        s32 i, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned = 0;

        velocity[3] = 0.05f;
        acceleration[3] = 0.09f;
        for (i = 0; i < 3; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x8050FF30;
            color2 = 0x3050FF30;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x80306000;
                color2 = 0x30304000;
            }
            qcopy(particle_pos, pos);
            particle_pos[0] += math_random_float_range(-0.24f, 0.24f);
            particle_pos[1] += math_random_float_range(-0.24f, 0.24f);
            particle_pos[2] += math_random_float_range(-0.24f, 0.24f);
            vec_build_spherical_offset(velocity, 0.20000002f,
                          FastAddRotations(yaw, math_random_float_range(-18.0f, 18.0f) * 0.017453294f), angle);
            velocity[2] += math_random_float_range(0.007f, 0.015000001f);
            vec_build_spherical_offset(acceleration, 0.010000001f,
                          FastAddRotations(yaw, math_random_float_range(-4.0f, 4.0f) * 0.017453294f), angle);
            acceleration[2] += math_random_float_range(-0.016800001f, -0.036000002f);
            life = FloatToInt((math_random_float_range(2.0f, 4.0f) * 5.0f + 2.0f) * 0.16666667f);
            size = FloatToInt((math_random_float_range(20.0f, 24.0f) * 5.0f + 2.0f) * 0.16666667f);
            duration = FloatToInt((math_random_float_range(100.0f, 120.00001f) * 5.0f + 2.0f) * 0.16666667f);
            spawned = part_spawn_trail(particle_pos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned && variant) spawned[3] = 0x48;
        }
    }
}
