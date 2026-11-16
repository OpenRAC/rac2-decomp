#include "include_asm.h"

#include "common.h"
extern f32  g_fan_rotation_rate __attribute__((sda));
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 g_fan_float_table[] SDATA(D_L03_001B0350);
extern f32 g_trail_projectile_scale __attribute__((sda));
extern u32 g_shared_record_pending;
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern u8  *g_moby_record_base;
extern u8   g_sound_state[];
extern s32  g_ant_bridge_divisor __attribute__((sda));
extern f32  g_ant_bridge_angle_limit __attribute__((sda));
extern s32  g_camera_trigger_active __attribute__((sda));
extern char g_hero_position[];
extern char g_camera_pose_buffer[];
typedef struct {
    s32 index;
    u8 pad04[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
} L03_22C8State;
typedef struct {
    u32 field00;
    u8 pad04[0xC];
} L03_22C8Entry;
extern L03_22C8Entry *g_path_l03_entry_table[];
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void moby_mark_spawned(char *a0);
extern s32  point_in_path_xy(char *a0, void *a1, u32 a2);
extern void SetCamera5Pose(char *a0, char *a1, s32 a2, s32 a3, s32 a4);
extern void cam_compute_aim_and_angles(char *a0, f32 *a1, f32 *a2);
extern void FastVecSub(void *, void *, void *);
extern f32  FastVecLength(f32 *a0);
extern void math_approach_target_with_braking(f32 *a0, f32 a1, f32 a2, f32 a3, f32 a4);
extern void vec_scale_to_length(f32 *a0, f32 *a1, f32 a2);
extern void FastVecAdd(void *, void *, void *);
extern void object_copy_vector_to_selected(char *a0);
extern f32 math_approach_target_with_direction_mode(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);
extern void cam_set_state_rotation(char *a0);
extern void cam_set_mode_state(s32 a0);

void camera_trigger_area_update_pal(char *moby)
{
    L03_22C8State *vars = *(L03_22C8State **)(moby + 0x68);
    f32 aim_pos[4] __attribute__((aligned(16)));
    f32 aim_angles[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 speed;
    f32 distance;
    f32 blend;
    f32 angle_speed;

    if (g_camera_trigger_active != 0) {
        return;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        if (vars->index == -1) {
            moby_mark_spawned(moby);
        }
        break;
    case 1:
        if (point_in_path_xy(g_hero_position, ((u8 *)g_path_l03_entry_table[vars->index] + 0x10), g_path_l03_entry_table[vars->index]->field00) != 0) {
            SetCamera5Pose(g_camera_pose_buffer, g_camera_pose_buffer + 0x10, 1, 0, 0);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        speed = 0.004f;
        cam_compute_aim_and_angles(moby, aim_pos, aim_angles);
        blend = 1.0f;
        FastVecSub(delta, aim_pos, g_camera_pose_buffer);
        angle_speed = 0.0012566373f;
        distance = FastVecLength(delta);
        math_approach_target_with_braking(&vars->f18, distance, speed, speed, blend);
        vec_scale_to_length(delta, delta, vars->f18);
        FastVecAdd(g_camera_pose_buffer, delta, g_camera_pose_buffer);
        object_copy_vector_to_selected(g_camera_pose_buffer);
        math_approach_target_with_direction_mode(g_camera_pose_buffer + 0x14, &vars->f1C, aim_angles[1], angle_speed, angle_speed, blend, 0);
        math_approach_target_with_direction_mode(g_camera_pose_buffer + 0x18, &vars->f20, aim_angles[2], angle_speed, angle_speed, blend, 0);
        cam_set_state_rotation(g_camera_pose_buffer + 0x10);
        if (point_in_path_xy(g_hero_position, ((u8 *)g_path_l03_entry_table[vars->index] + 0x10), g_path_l03_entry_table[vars->index]->field00) == 0) {
            cam_set_mode_state(1);
            moby_set_state(moby, 1, -1);
        }
        break;
    }
}
