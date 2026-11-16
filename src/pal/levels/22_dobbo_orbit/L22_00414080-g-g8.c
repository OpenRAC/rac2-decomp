#include "include_asm.h"

#include "common.h"
#include "common.h"
typedef struct Vars_004402D8 {
    u8 pad00[0x20];
    s32 f20;  
    f32 f24;  
    s32 f28[6];  
    f32 f40;  
    f32 f44;  
    f32 f48;  
    f32 f4C;  
    s32 f50;  
} Vars_004402D8;
typedef struct Entry_004402D8 {
    f32 x;  
    f32 y;  
    f32 z;  
    u8 pad0C[0x10];
    Vars_004402D8 *vars;  
} Entry_004402D8;
typedef struct Moby_004402D8 {
    u8 pad00[0x84];
    s16 f84;  
} Moby_004402D8;
typedef struct Player_004402D8 {
    u8 pad000[0x80];
    f32 f80[4];  
    u8 pad090[0x20];
    f32 fB0[4];  
    u8 pad0C0[0xB0];
    f32 f170;  
    u8 pad174[0x32A];
    u8 f49E;  
    u8 pad49F[0x81];
    f32 f520;  
    u8 pad524[0xF30];
    s16 f1454;  
    u8 pad1456[0xE3A];
    u8 *f2290;  
    s32 f2294;  
    u8 pad2298[0x4];
    s32 f229C;  
    u8 pad22A0[0x14];
    u8 f22B4;  
} Player_004402D8;
typedef struct Pad_004402D8 {
    u8 pad000[0x100];
    f32 f100;  
    f32 f104;  
} Pad_004402D8;
typedef struct CamSub_004402D8 {
    u8 pad000[0x250];
    s32 f250;  
} CamSub_004402D8;
typedef struct Cam_004402D8 {
    u8 pad00[0x70];
    CamSub_004402D8 *f70;  
    u8 pad74[0x12];
    s16 f86;  
} Cam_004402D8;
typedef struct CamMgr_004402D8 {
    u8 pad000[0x140];
    f32 f140[4];  
    u8 pad150[0x40];
    Cam_004402D8 *cam;  
} CamMgr_004402D8;
extern Entry_004402D8 *g_control_zone_table;
extern s32 g_hero_special_mode;
extern s32 g_current_map_index;
extern s32 g_game_mode __attribute__((nosda));
extern Player_004402D8 g_hero_state;
extern Pad_004402D8 g_pad_state;
extern CamMgr_004402D8 g_hero_l23_state_block;
extern s32 g_control_zone_mode;
extern f32 g_control_zone_angle_rad __attribute__((sda));
extern f32 g_control_zone_blend_dist __attribute__((sda));
extern f32 g_control_zone_cam_speed __attribute__((sda));
extern f32 g_control_zone_blend_a_start __attribute__((sda));
extern f32 g_control_zone_blend_b_start __attribute__((sda));
extern f32 g_control_zone_blend_a_end __attribute__((sda));
extern f32 g_control_zone_blend_b_end __attribute__((sda));
extern f32 g_control_zone_cam_distance __attribute__((sda));
extern f32 g_control_zone_cam_height __attribute__((sda));
extern f32 g_control_zone_aim_offset_a __attribute__((sda));
extern f32 g_control_zone_aim_offset_b __attribute__((sda));
extern f32 g_control_zone_tuning_deg __attribute__((sda));
extern f32 g_control_zone_angle_deg __attribute__((sda));
extern f32 g_control_zone_gravity_dist __attribute__((sda));
extern f32 fast_vec_dist(void *, void *);
extern f32 gravity_get_center_distance(void *);
extern s32 cam_release_request_slot(void *);
extern s32 cam_claim_request_slot(void *);
extern s32 IsPointInCuboid(void *, s32);
extern f32 math_fabs(f32);
extern void cam_set_snap_flag(void);
extern void set_follow_camera_orbit_clamp_mode(s32);
extern void cam_set_lock_flag(void);
extern void cam_set_speeds_if_nonzero(f32, f32);
extern s32 math_fast_float_d(void *);
extern void cam_set_strength_and_steer(void *, f32, f32);
extern f32 hero_find_collision_time(f32, f32, f32);
extern s32 FloatToInt(f32);
extern void cam_set_turn_speeds_if_nonzero(f32, f32);
extern void moby_push_axis_to_linked_node(f32, f32);
extern void cam_set_aim_offset_target(s32, f32, f32);
extern void follow_camera_set_distance(s32, f32, f32);
extern void follow_camera_set_height(f32, f32);
extern void cam_set_tuning_value(f32);

/* Same body as func_L23_004402D8, with this function's own callees. */
void ride_update_camera_control_pal(Moby_004402D8 *moby)
{
    Entry_004402D8 *entry = (Entry_004402D8 *)(moby->f84 * 32 + (s32)g_control_zone_table);
    Vars_004402D8 *vars = entry->vars;
    s32 i;

    if (vars->f20 == 0) {
        if (g_hero_special_mode != 0 || (g_current_map_index == 16 && g_game_mode == 0x81)) {
            f32 entry_pos[4];

            entry_pos[0] = entry->x;
            entry_pos[1] = entry->y;
            entry_pos[2] = entry->z;
            entry_pos[3] = 0.0f;
            vars->f24 = fast_vec_dist(entry_pos, g_hero_state.fB0);
            vars->f20 = 1;
        }
        return;
    }
    if (g_hero_l23_state_block.cam->f86 != 0
        || (g_hero_special_mode == 0 && (g_current_map_index != 16 || g_game_mode != 0x81))) {
        if (g_control_zone_gravity_dist < gravity_get_center_distance(g_hero_l23_state_block.f140)) {
            g_control_zone_mode = 3;
        } else {
            g_control_zone_mode = 0;
        }
        cam_release_request_slot(moby);
        return;
    }
    if (cam_claim_request_slot(moby) <= 0) {
        return;
    }
    i = 0;
    do {
        if (vars->f28[i] < 0) {
            break;
        }
        if (IsPointInCuboid(g_hero_state.f80, vars->f28[i]) != 0) {
            cam_set_turn_speeds_if_nonzero(0.04f, 0.2f);
            follow_camera_set_distance(0, vars->f40, 0.003f);
            follow_camera_set_height(vars->f44, 0.003f);
            return;
        }
        i++;
    } while (i < 6);
    if (g_hero_state.f22B4 == 2) {
        if (g_hero_state.f1454 != 0 || g_hero_state.f2294 == 0x5B
            || math_fabs(g_pad_state.f100) >= 0.3f || math_fabs(g_pad_state.f104) >= 0.3f) {
            cam_set_snap_flag();
            set_follow_camera_orbit_clamp_mode(0);
        }
    } else {
        cam_set_snap_flag();
        set_follow_camera_orbit_clamp_mode(0);
    }
    cam_set_lock_flag();
    cam_set_speeds_if_nonzero(g_control_zone_cam_speed, 0.2f);
    if (math_fast_float_d(&vars->f50) != 0 && !(g_hero_state.f170 > 0.005f)) {
        cam_set_strength_and_steer(g_hero_state.f2290 + 0xC0, 0.0052359886f, 0.0f);
    }
    if (math_fabs(g_pad_state.f100) >= 0.3f || math_fabs(g_pad_state.f104) >= 0.3f) {
        vars->f50 = 250;
    }
    if (g_hero_state.f22B4 == 2) {
        s32 hit_time;

        g_hero_l23_state_block.cam->f70->f250 = 2;
        hit_time = 0;
        if (g_hero_state.f49E != 0) {
            hit_time = FloatToInt(hero_find_collision_time(90.0f, g_hero_state.f520, -1.0f));
        }
        if (g_hero_state.f2294 == 0x5B && (g_hero_state.f49E == 0 || hit_time >= 17)) {
            cam_set_speeds_if_nonzero(0.5f, 1.0f);
            cam_set_turn_speeds_if_nonzero(0.05f, 0.2f);
            moby_push_axis_to_linked_node(0.04f, 0.0f);
            cam_set_aim_offset_target(0, g_control_zone_aim_offset_b, 0.005f);
            follow_camera_set_distance(1, g_control_zone_cam_distance, 0.01f);
            follow_camera_set_height(g_control_zone_cam_height, 0.01f);
            g_control_zone_angle_rad = g_control_zone_angle_deg * 0.017453294f;
            cam_set_tuning_value(g_control_zone_tuning_deg * 0.017453294f);
        } else {
            f32 dist;
            f32 blend;
            f32 cam_distance;
            f32 cam_height;

            cam_set_aim_offset_target(0, g_control_zone_aim_offset_a, 0.03f);
            if (g_hero_state.f229C == 2) {
                cam_set_turn_speeds_if_nonzero(0.04f, 0.2f);
            } else {
                cam_set_turn_speeds_if_nonzero(0.015f, 0.2f);
            }
            dist = fast_vec_dist(g_hero_state.f80, g_hero_state.fB0) - vars->f24;
            if (g_control_zone_blend_dist < dist) {
                dist = g_control_zone_blend_dist;
            } else if (dist < 0.0f) {
                dist = 0.0f;
            }
            blend = dist / g_control_zone_blend_dist;
            cam_distance = (g_control_zone_blend_a_end - g_control_zone_blend_a_start) * blend + g_control_zone_blend_a_start;
            cam_height = (g_control_zone_blend_b_end - g_control_zone_blend_b_start) * blend + g_control_zone_blend_b_start;
            follow_camera_set_distance(1, cam_distance, 0.005f);
            follow_camera_set_height(cam_height, 0.005f);
        }
        if (g_control_zone_gravity_dist < gravity_get_center_distance(g_hero_l23_state_block.f140)) {
            g_control_zone_mode = 3;
        } else {
            g_control_zone_mode = 0;
        }
    } else if (g_hero_state.f2294 == 0x81) {
        cam_set_turn_speeds_if_nonzero(0.05f, 0.2f);
        moby_push_axis_to_linked_node(0.04f, 0.0f);
        if (g_current_map_index == 16) {
            cam_set_aim_offset_target(0, 0.5f, 0.04f);
            follow_camera_set_distance(0, 4.0f, 0.002f);
            follow_camera_set_height(2.0f, 0.04f);
        } else {
            cam_set_aim_offset_target(0, 1.0f, 0.04f);
            follow_camera_set_distance(0, 2.0f, 0.002f);
            follow_camera_set_height(7.0f, 0.04f);
        }
    } else {
        if (g_hero_state.f229C == 2) {
            cam_set_turn_speeds_if_nonzero(0.04f, 0.2f);
        } else {
            cam_set_turn_speeds_if_nonzero(0.015f, 0.2f);
        }
        if (g_hero_state.f229C == 5) {
            follow_camera_set_distance(0, 4.0f, 0.003f);
            follow_camera_set_height(6.0f, 0.003f);
        } else {
            f32 dist;
            f32 blend;
            f32 cam_distance;
            f32 cam_height;

            dist = fast_vec_dist(g_hero_state.f80, g_hero_state.fB0) - vars->f24;
            if (g_control_zone_blend_dist < dist) {
                dist = g_control_zone_blend_dist;
            } else if (dist < 0.0f) {
                dist = 0.0f;
            }
            blend = dist / g_control_zone_blend_dist;
            cam_distance = (vars->f48 - vars->f40) * blend + vars->f40;
            cam_height = (vars->f4C - vars->f44) * blend + vars->f44;
            follow_camera_set_distance(0, cam_distance, 0.003f);
            follow_camera_set_height(cam_height, 0.003f);
        }
    }
}
