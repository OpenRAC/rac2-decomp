#include "include_asm.h"



#include "common.h"
extern s32 math_random_int_below(s32 a0);
extern s32 snd_play_from_class_bank(s32 a0, s32 a1, char *a2, s32 a3);
extern s32 PlayMobySound(s32 a0, s32 a1, char *a2);
extern int math_random_int_below(int);
extern u8 *g_hero_moby;
extern s32 g_trigger_event_list_head __attribute__((sda));
extern u8 g_unused_level_byte __attribute__((sda));
extern s32 g_trigger_event_flag __attribute__((sda));
extern s32 g_unused_l22_level_word __attribute__((sda));
extern s32 math_fast_float_d(s32);
extern int FastDecTimer();
extern void build_axis_rotation_quaternion(s32, s32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern void AttachManipulator(s32, s32, s32);
extern u8 *g_space_ship_owner_moby[] __attribute__((sda));
extern f32 g_space_ship_param_y __attribute__((sda));
extern u8 *g_hero_moby;

/* func_L22_0040C888 is in L22_0040C888-g8.c. */

/* func_L22_0040D638 lives in L22_00358778-state-g8.c. */

/* Updates a ship enemy: ticks its timers, counts its age, attaches the manipulator and spins its rotation. */
void l22_manipulator_spin_update_pal(s32 moby_arg) {
    s32 moby = moby_arg;
    s32 vars = *(u32 *)(moby + 0x68);

    math_fast_float_d(vars + 0x258);
    FastDecTimer(vars + 0x25C);
    if (*(u16 *)(moby + 0x96) <= 0xFFFE)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
    if (*(u8 *)(vars + 0x211) == 0)
        AttachManipulator(moby, 7, vars + 0x210);
    build_axis_rotation_quaternion(vars + 0x220, 2, *(f32 *)(vars + 0x26C));
    *(f32 *)(vars + 0x26C) = fast_subtract_rotations(*(f32 *)(vars + 0x26C), 0.49916422f);
}


extern void vec_scale_to_length(void *, void *, float);
extern s32 func_2F36F0(s32);
extern f32 func_2F4AD0(f32, f32);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void vec_scale_to_length(void *, void *, f32);

/* Fires two trail effects from the ship's joints 2 and 3 toward a target point. */
void ship_fire_trail_effects_pal(u8 *ship, f32 *target_pos, f32 scale_arg) {
    f32 joint_pos[4] __attribute__((aligned(16)));
    f32 dir[4] __attribute__((aligned(16)));
    f32 scale = scale_arg;

    if (g_space_ship_owner_moby[0] != 0 && *(f32 *)(*(u8 **)(g_space_ship_owner_moby[0] + 0x68) + 0x20) <= 0.0f) {
        return;
    }
    moby_transform_joint_to_world(ship, 2, joint_pos);
    if (scale == 0.0f) {
        scale = g_space_ship_param_y;
    }
    FastVecSub(dir, target_pos, joint_pos);
    vec_scale_to_length(dir, dir, 0.8000001f);
    part_spawn_trail_effect_pal(joint_pos, dir, &scale);
    moby_transform_joint_to_world(ship, 3, joint_pos);
    FastVecSub(dir, target_pos, joint_pos);
    vec_scale_to_length(dir, dir, 0.8000001f);
    part_spawn_trail_effect_pal(joint_pos, dir, &scale);
}


extern int moby_copy_vector_to_child();
extern void FastVecAdd(void *, void *, void *);
extern int moby_check_target_point_from_offset(s32, s32);
extern void arena_push_point_out(void *, f32);

/* Steers a moby toward a target point, optionally keeping the step inside the arena. */
void moby_steer_toward_point_pal(s32 moby, s32 target, s32 push_out, f32 speed_arg) {
    u8 step[0x10];
    u8 next_pos[0x10];
    f32 speed = speed_arg;

    FastVecSub(step, (void *)target, (void *)(moby + 0x10));
    speed = speed * 0.020000001f;
    vec_scale_to_length(step, step, speed);
    if (push_out != 0) {
        FastVecAdd(next_pos, (void *)(moby + 0x10), step);
        arena_push_point_out(next_pos, 7.2f);
        FastVecSub(step, next_pos, (void *)(moby + 0x10));
        vec_scale_to_length(step, step, speed);
    }
    moby_check_target_point_from_offset(moby, target);
    moby_copy_vector_to_child(moby, step);
}

