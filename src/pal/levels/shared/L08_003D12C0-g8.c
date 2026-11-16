#include "include_asm.h"
#include "common.h"
extern s32 g_saved_float_hold_active __attribute__((sda));
extern f32 g_saved_float_hold_value __attribute__((sda));
extern f32 g_saved_hold_float __attribute__((nosda));
extern f32 g_aim_camera_distance_far __attribute__((sda));
extern f32 g_aim_camera_distance_near __attribute__((sda));
extern f32 g_aim_camera_height __attribute__((sda));
extern f32 g_aim_camera_offset_x __attribute__((sda));
extern s32 g_aim_camera_offset_y __attribute__((sda));
extern f32 g_aim_camera_offset_z __attribute__((sda));
extern u8 *g_camera_l08_state_ptr __attribute__((nosda));
extern char g_hero_position[] __attribute__((nosda));
extern void follow_camera_set_distance(s32, f32, f32);
extern void follow_camera_set_height(f32, f32);
extern void cam_set_aim_offset_target(f32, s32, f32);
extern void cam_set_tuning_value(f32);
extern void cam_set_speeds_if_nonzero(f32, f32);
extern void cam_set_turn_speeds_if_nonzero(f32, f32);
extern void cam_set_snap_flag(void);
extern void cam_set_lock_flag(void);
extern s32 IsPointInCuboid(void *, s32);
extern f32 IntToFloat(s32);
extern f32 math_ease_out_quad(f32);
extern s32 g_current_map_index;

/* Flags the level's object, feeds the camera its aim values and advances the
   counter the aim is scaled by. */
void cam_update_aim_values_pal(s32 *counter, u8 *moby) {
    u8 *owner;
    f32 blend, speed_a, speed_b, turn_speed;

    owner = *(u8 **)((u8 *)moby + 0x68);
    if (*(s16 *)((u8 *)g_camera_l08_state_ptr + 0x86) == 0) {
        *(s32 *)((u8 *)*(u8 **)((u8 *)g_camera_l08_state_ptr + 0x70) + 0x250) = 2;
    }

    cam_set_aim_offset_target(g_aim_camera_offset_x, g_aim_camera_offset_y, g_aim_camera_offset_z);
    follow_camera_set_distance(0, g_aim_camera_distance_near, g_aim_camera_distance_far);

    if (*(s32 *)((u8 *)owner + 0xC8) >= 0 &&
        IsPointInCuboid(g_hero_position, *(s32 *)((u8 *)owner + 0xC8)) != 0) {
        cam_set_tuning_value(0.52359885f);
    }

    follow_camera_set_height(g_aim_camera_height, 0.003f);
    cam_set_lock_flag();

    blend = IntToFloat(*counter) / IntToFloat(0x4B);
    if (blend > 1.0f)
        blend = 1.0f;

    speed_a = blend * 0.985f + 0.015f;
    speed_b = blend * 0.8f + 0.2f;
    turn_speed = blend * 0.044999998062849045f + 0.015f;

    cam_set_speeds_if_nonzero(speed_a, speed_b);
    cam_set_turn_speeds_if_nonzero(turn_speed, 0.2f);
    cam_set_snap_flag();

    if (*counter < 0x4B)
        *counter = *counter + 1;
}
