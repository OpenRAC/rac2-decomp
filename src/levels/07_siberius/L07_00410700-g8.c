#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(u8 *a, s32 b, s32 c);
extern f32 g_ship_second_phase_pos __attribute__((sda));
extern f32 g_ship_second_phase_hero_pos __attribute__((sda));
extern f32 g_ship_second_phase_hero_rot __attribute__((sda));
extern f32 g_ship_second_phase_camera_origin __attribute__((sda));
extern f32 g_ship_second_phase_camera_y;
extern f32 g_ship_second_phase_camera_z;
extern f32 g_ship_fade_seconds_param __attribute__((sda));
extern f32 g_ship_approach_minutes_param __attribute__((sda));
extern u16 **g_group_l07_id_lists;
extern u8 *g_joint_record_table;
extern s32 g_ship_phase_state;
extern s32 g_music_state[];
extern char g_hero_position[];
extern f32 g_hero_state[];
extern void func_002A0F48(u8 *a);
extern void math_approach_target_with_braking(void *a, f32 b, f32 c, f32 d, f32 e);
extern void hero_reset_position_and_direction(void *obj, void *pos, s32 a2, s32 a3);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern f32 vec_distance_xy(void *a, void *b);
extern void SetCamera5Pose(void *a, void *b, s32 c, s32 d, s32 e);
extern void moby_build_matrix(u8 *a);

/* Starts the second phase of the object: its two position vectors, the shared timer record, the
   effect call and the camera-facing vector, then raises bit 2 of every record of the group. */
void ship_start_second_phase(u8 *moby, s32 group)
{
    f32 look_angles[4];
    f32 eye_pos[4];
    u8 *vars;
    u16 *entry;
    u8 *record;
    f32 flat_dist;
    f32 *camera_origin;

    moby_set_state(moby, 5, -1);
    qcopy(moby + 0x10, &g_ship_second_phase_pos);
    qcopy(moby + 0xF0, &g_ship_second_phase_hero_pos);
    *(u16 *)(moby + 0x34) &= 0xFFFD;
    func_002A0F48(moby);
    vars = *(u8 **)(moby + 0x68);
    g_music_state[9] = (*(s32 *)(vars + 0xD4) & 0x3FFF) + 3000;
    g_music_state[10] = 0;
    math_approach_target_with_braking(vars + 0x11C, 400.0f - g_ship_second_phase_pos, 5.0f,
                  g_ship_approach_minutes_param * 0.00027777778f, g_ship_fade_seconds_param * 0.016666668f);
    *(s32 *)(vars + 0x16B0) = 0;
    *(s32 *)(vars + 0xD0) = group;
    *(f32 *)(vars + 0x16B8) = 1.0f;
    *(s32 *)(vars + 0x16BC) = 0;
    hero_reset_position_and_direction(&g_ship_second_phase_hero_rot, &g_ship_second_phase_hero_pos, 0x6F, 1);
    *(TI128 *)eye_pos = *(TI128 *)g_hero_position;
    eye_pos[2] = eye_pos[2] + 1.0f;
    qzero_nc(look_angles);
    camera_origin = &g_ship_second_phase_camera_origin;
    look_angles[2] = mat_fast_helper_a(g_hero_state[0x20] - g_ship_second_phase_camera_origin, g_hero_state[0x21] - g_ship_second_phase_camera_y);
    flat_dist = vec_distance_xy(eye_pos, camera_origin);
    look_angles[1] = mat_fast_helper_a(flat_dist, g_ship_second_phase_camera_z - eye_pos[2]);
    SetCamera5Pose(camera_origin, look_angles, 1, 0, 0);
    moby_build_matrix(moby);
    for (entry = g_group_l07_id_lists[group];
         entry != 0 && ((s16)entry[-1] >= 0 || entry == g_group_l07_id_lists[group]) &&
         (record = g_joint_record_table + ((*entry & 0x7FFF) << 5)) != 0;
         entry++) {
        record[0x1E] |= 4;
    }
    g_ship_phase_state = 0;
}
