#include "include_asm.h"

#include "common.h"
extern f32 FastAddRotations(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 g_unused_float_param __attribute__((sda));
extern u8 *g_moby_l07_array __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 g_boss_cam_distance __attribute__((sda));
extern f32 g_boss_cam_height __attribute__((sda));
extern u32 g_boss_screen_color __attribute__((sda));
extern f32 g_bomb_scale __attribute__((sda));
extern f32 g_beam_fade_in_rate __attribute__((sda));
extern f32 g_beam_fade_out_rate __attribute__((sda));
extern f32 g_beam_spin_rate __attribute__((sda));
extern f32 ApproachValue(f32 *value, f32 target, f32 step);
extern f32 FastAddRotations(f32 a, f32 b);
extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern f32 g_hero_reset_offset_z;
extern u8 g_hero_l07_reset_position __attribute__((sda));
extern u8 *g_joint_record_table;
extern u8 *g_matrix_l07_record_table;
extern s32 g_ship_phase_state;
extern u8 *cam_alloc_override_slot(s32);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern f32 fast_subtract_rotations(f32 a, f32 b);
extern f32 math_approach_target_with_direction_mode(void *a0, void *a1, f32 a2, f32 a3, f32 a4, f32 a5, s32 a6);
extern f32 g_aim_yaw_turn_accel __attribute__((sda));
extern f32 g_aim_yaw_max_turn_speed __attribute__((sda));
extern u8 *g_world_info __attribute__((nosda));
extern u8 *g_snowfall_target_moby MACRO_ADDR;
extern u8 g_aim_yaw_init_flag;
extern u8 g_hero_state[];
extern u32 g_frame_l07_counter MACRO_ADDR;
extern f32 fast_vec_dist(u8 *a, u8 *b);
extern f32 g_bomb_scale __attribute__((sda));
extern u8 *g_hit_object_list[];

/* Steers the object's two angles: the yaw toward the argument, the pitch from the shared
   record, and the two scaled fields of the state record. */
void moby_steer_aim_yaw_pal(u8 *moby)
{
    u8 *world_state;
    u8 *vars;
    u8 *cam_state;
    u8 *world;
    u8 *target_moby;
    f32 *cam_pos;
    f32 yaw_error;
    f32 target_yaw;
    f32 current_yaw;
    f32 max_turn_speed;
    f32 turn_accel;
    f32 pi;

    world = g_world_info;
    if (*(s16 *)(world + 0x86) != 0) {
        return;
    }
    target_moby = g_snowfall_target_moby;
    if (target_moby == 0) {
        return;
    }
    pi = 3.14159274f;
    world_state = *(u8 **)(world + 0x70);
    vars = *(u8 **)(moby + 0x68);
    cam_pos = (f32 *)(world_state + 0x160);
    target_yaw = FastAddRotations(*(f32 *)(target_moby + 0xF8), pi);
    cam_state = world_state + 0x1C0;
    current_yaw = mat_fast_helper_a(cam_pos[0], cam_pos[1]);
    yaw_error = fast_subtract_rotations(target_yaw, current_yaw);
    turn_accel = g_aim_yaw_turn_accel * 6.981318e-06f;
    max_turn_speed = g_aim_yaw_max_turn_speed * 0.0003490659f;
    if (g_aim_yaw_init_flag == 0) {
        yaw_error = FastAddRotations(yaw_error, pi);
    }
    math_approach_target_with_direction_mode(&yaw_error, vars + 0x1A8, 0.0f, turn_accel, turn_accel, max_turn_speed, 0);
    *(f32 *)(cam_state + 0x1C) = 1.0f;
    *(f32 *)(cam_state + 0x14) = -*(f32 *)(vars + 0x1A8);
}
