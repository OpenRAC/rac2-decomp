#include "common.h"

extern int g_enemy_freeze_flag[];
extern unsigned int g_pad_held_flags __attribute__((nosda));
extern u8 g_hero_position[];
extern int *g_path_l11_table[];
extern float g_wander_angle_param __attribute__((sda));
extern float g_wander_angle_speed __attribute__((sda));
extern int g_creature_burst_count;
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void math_random_planar_offset(float *, float);
extern void FastVecAdd(float *, float *, float *);
extern void moby_set_state(u8 *, int, int);
extern int math_random_int_below(int);
extern void anim_start_blended_pal(u8 *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int math_random_int_range(int, int);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern int hero_set_control_motion_and_step(char *, void *);
extern float MobySpringTurn(void *, float *, float, float, float, float);
extern void moby_mark_spawned(void *);
extern float mat_fast_helper_a(float, float);
extern void math_update_wrapped_angle_offset(float *, float *, float *, float, float, float);
extern int moby_l01_turn_toward_target_pal(char *, char *);
extern void vec_random_direction(float *, float, float);
extern u8 *debris_l11_spawn_piece_pal(u8 *, float *, float *);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern void value_set_and_smooth_pal(void *, float *, float, int, int);
#define VF(offset) (*(float *)(vars + (offset)))
#define VI(offset) (*(int *)(vars + (offset)))

/* func_PAL_L11_00476610, the PAL copy of func_L11_004702F0: the same C, with speeds and rates
 * rescaled for 50 Hz and frame counts written ((s32)(x) * 5 + 2) / 6.
 * Level-11 creature update, a state machine on object[0x20]: wanders between random points
 * near its spawn, follows a path from D_L11_001FF580, or turns away from the hero; when hit it
 * bursts into 14 pieces (func_PAL_L11_00399B70), counts towards D_L11_001AED08 and deletes itself. */
void wandering_l11_creature_update_pal(u8 *moby) {
    float motion[4], previous[4];
    u8 *vars;
    int *path;
    float *point;
    float angle, distance;
    int start_frame, blend_time;
    u16 timer;
    if (g_enemy_freeze_flag[0]) return;
    vars = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        *(u8 **)(vars + 0x18) = vars + 0x20;
        *(float *)(moby + 0x2C) *= 1.5f;
        qcopy(vars + 0x110, moby + 0x10);
        VF(0x24) = VF(0x20) = 0.4f;
        VF(0x54) = 0.25f;
        VF(0x2C) = VF(0x28) = 0.6f;
        VF(0x50) = VF(0x30) = 1.48353004f;
        VF(0x4C) = 0.002f;
        moby_set_controller_speed_limits(moby, 0.00080000004f, 0.020000001f, 0.0016755164f, 0.12566373f);
        math_random_planar_offset((float *)(vars + 0x120), 4.0f);
        FastVecAdd((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
        moby_set_state(moby, VI(0x130), -1);
        moby[0x30] = 255;
        start_frame = math_random_int_below(8);
        blend_time = math_random_int_below(18);
        anim_start_blended_pal(moby, 0, start_frame, ((s32)blend_time * 5 + 2) / 6);
        VI(0x144) = 0;
        if (VI(0x140) != -1 && VI(0x130) != 8) {
            *(float *)(moby + 0x2C) *= 1.5f;
            if (moby[0x43] != 4) {
                start_frame = math_random_int_below(3);
                blend_time = math_random_int_below(8);
                anim_start_blended_pal(moby, 4, start_frame, ((s32)(blend_time + 10) * 5 + 2) / 6);
            }
            moby_set_state(moby, 7, -1);
        }
        break;
    case 2:
        if (fast_vec_dist(moby + 0x10, g_hero_position) < 9.0f) {
            if (moby[0x43] != 3) anim_start_blended_pal(moby, 3, 0, 8);
            moby_set_state(moby, 4, -1);
            break;
        }
        if (*(int *)(g_hero_position + 0x11C8) != 10 && *(int *)(g_hero_position + 0x11C8) != 13 && (g_pad_held_flags & 0x20)) {
            if (!(vec_distance_xy(moby + 0x10, g_hero_position) < 64.0f) || VI(0x150)) break;
            VF(0x134) = (float)math_random_int_range(170, 190);
            if (moby[0x43] != 4) anim_start_blended_pal(moby, 4, 0, 8);
            VF(0x138) = 0.10000001f;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 4:
        if (moby[0x60] & 2) {
            VF(0x134) = (float)math_random_int_range(170, 190);
            if (moby[0x43] != 4) anim_start_blended_pal(moby, 4, 0, 8);
            VF(0x138) = 0.040000003f;
            moby_set_state(moby, 5, -1);
        }
        break;
    case 5:
        VF(0x138) += 0.012f;
        if (VF(0x138) > 0.14000001f) VF(0x138) = 0.14000001f;
        qcopy(previous, moby + 0x10);
        angle = FastAddRotations(*(float *)(moby + 0xF8), VF(0x134) * 0.017453294f);
        vec_build_spherical_offset(motion, VF(0x138), angle, 2.96706009f);
        hero_set_control_motion_and_step((char *)moby, motion);
        if (vec_distance_xy(moby + 0x10, previous) < VF(0x138)) {
            angle = FastAddRotations(*(float *)(moby + 0xF8), 3.141593f);
            MobySpringTurn(moby, (float *)(vars + 0x13C), angle, 0.000199999995f, 0.00200000009f, 0.04f);
        }
        if (vec_distance_xy(moby + 0x10, g_hero_position) > 64.0f) {
            moby_mark_spawned(moby);
            return;
        }
        math_update_wrapped_angle_offset((float *)moby, (float *)(vars + 0x148), (float *)(vars + 0x14C), g_wander_angle_param, g_wander_angle_speed * 0.0003490659f, -1.0f);
        break;
    case 6:
        VF(0x138) += 0.012f;
        if (VF(0x138) > 0.50000006f) VF(0x138) = 0.50000006f;
        angle = FastAddRotations(*(float *)(moby + 0xF8), VF(0x134) * 0.017453294f);
        vec_build_spherical_offset(motion, VF(0x138), angle, 2.96706009f);
        FastVecAdd((float *)(moby + 0x10), (float *)(moby + 0x10), motion);
        if (vec_distance_xy(moby + 0x10, g_hero_position) > 64.0f) {
            moby_mark_spawned(moby);
            return;
        }
        break;
    case 7:
        path = g_path_l11_table[VI(0x140)];
        distance = vec_distance_xy(moby + 0x10, path + 4 + VI(0x144) * 4);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = mat_fast_helper_a(distance, point[6] - *(float *)(moby + 0x18));
        vec_build_spherical_offset(motion, 0.14000001f, *(float *)(moby + 0xF8), angle);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = mat_fast_helper_a(point[4] - *(float *)(moby + 0x10), point[5] - *(float *)(moby + 0x14));
        MobySpringTurn(moby, (float *)(vars + 0x13C), angle, 9.99999975e-05f, 0.00100000005f, 0.02f);
        FastVecAdd((float *)(moby + 0x10), (float *)(moby + 0x10), motion);
        if (moby[0x43] != 4) anim_start_blended_pal(moby, 4, 0, 8);
        if (vec_distance_xy(moby + 0x10, path + 4 + VI(0x144) * 4) < 0.6f) {
            ++VI(0x144);
            if (VI(0x144) >= *path - 1) VI(0x144) = *path - 1;
        }
        math_update_wrapped_angle_offset((float *)moby, (float *)(vars + 0x148), (float *)(vars + 0x14C), g_wander_angle_param, g_wander_angle_speed * 0.0003490659f, -1.0f);
        break;
    case 8:
        if (moby[0x43] != 2) anim_start_blended_pal(moby, 2, 0, 8);
        if (vec_distance_xy(moby + 0x10, vars + 0x120) < 0.5f ||
            VI(0xA0) || *(u16 *)(moby + 0x96) >= 240) {
            *(u16 *)(moby + 0x96) = 0;
            VI(0xA0) = 0;
            math_random_planar_offset((float *)(vars + 0x120), 4.0f);
            FastVecAdd((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
            if (math_random_int_below(4) == 1) {
                if (moby[0x43] != 1) anim_start_blended_pal(moby, 1, 0, 8);
                moby_set_state(moby, 9, -1);
            }
        } else {
            moby_l01_turn_toward_target_pal((char *)moby, (char *)vars + 0x120);
        }
        if (fast_vec_dist(moby + 0x10, g_hero_position) < 10.0f) {
            if (moby[0x43] != 2) anim_start_blended_pal(moby, 2, 0, 8);
            moby_set_state(moby, 4, -1);
        }
        break;
    case 9:
        if (moby[0x60] & 2) {
            moby_set_state(moby, 8, -1);
            if (moby[0x43] != 2) anim_start_blended_pal(moby, 2, 0, 8);
        }
        if (fast_vec_dist(moby + 0x10, g_hero_position) < 10.0f) {
            if (moby[0x43] != 2) anim_start_blended_pal(moby, 2, 0, 8);
            moby_set_state(moby, 4, -1);
        }
        break;
    }
    timer = *(u16 *)(moby + 0x96);
    if (timer < 65535) *(short *)(moby + 0x96) = timer + 1;
    if (moby[0x42] == 4) *(float *)(moby + 0x48) = 2.5f;
    else if (moby[0x42]) *(float *)(moby + 0x48) = 1.0f;
    if (part_find_owned_effect_slot(moby, 0x10000, 0)) {
        int i;
        for (i = 0; i < 14; i++) {
            u8 *particle;
            vec_random_direction(motion, 0.080000006f, 0.120000005f);
            particle = debris_l11_spawn_piece_pal(moby, (float *)(moby + 0x10), motion);
            particle[0x30] = *(u16 *)(particle + 0x32) = 255;
        }
        ++g_creature_burst_count;
        moby_mark_spawned(moby);
    } else {
        value_set_and_smooth_pal(moby, (float *)(vars + 0x160), 2.5f, 0, 1);
    }
}
