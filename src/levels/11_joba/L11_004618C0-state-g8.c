#include "common.h"

extern int D_L11_001CAE40[];
extern unsigned int D_00138324 __attribute__((nosda));
extern u8 g_hero_position[];
extern int *D_L11_001FF580[];
extern float D_L11_001B2978 __attribute__((sda));
extern float D_L11_001B297C __attribute__((sda));
extern int D_L11_001AED08;
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void math_random_planar_offset(float *, float);
extern void FastVecAdd(float *, float *, float *);
extern void moby_set_state(u8 *, int, int);
extern int math_random_int_below(int);
extern void anim_start_blended(u8 *, int, int, int);
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
extern int moby_l01_turn_toward_target(char *, char *);
extern void vec_random_direction(float *, float, float);
extern u8 *debris_l11_spawn_piece(u8 *, float *, float *);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern void value_set_and_smooth(void *, float *, float, int, int);
#define VF(offset) (*(float *)(vars + (offset)))
#define VI(offset) (*(int *)(vars + (offset)))

/* Level-11 creature update, a state machine on object[0x20]: wanders between random points
 * near its spawn, follows a path from D_L11_001FF580, or turns away from the hero; when hit it
 * bursts into 14 pieces (func_L11_00396DC8), counts towards D_L11_001AED08 and deletes itself. */
void wandering_l11_creature_update(u8 *object) {
    float motion[4], previous[4];
    u8 *vars;
    int *path;
    float *point;
    float angle, distance;
    int first, second;
    u16 timer;
    if (D_L11_001CAE40[0]) return;
    vars = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        *(u8 **)(vars + 0x18) = vars + 0x20;
        *(float *)(object + 0x2C) *= 1.5f;
        qcopy(vars + 0x110, object + 0x10);
        VF(0x24) = VF(0x20) = 0.4f;
        VF(0x54) = 0.25f;
        VF(0x2C) = VF(0x28) = 0.6f;
        VF(0x50) = VF(0x30) = 1.48353004f;
        VF(0x4C) = 0.00138888892f;
        moby_set_controller_speed_limits(object, 0.000555555569f, 0.0166666675f, 0.00116355298f, 0.104719773f);
        math_random_planar_offset((float *)(vars + 0x120), 4.0f);
        FastVecAdd((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
        moby_set_state(object, VI(0x130), -1);
        object[0x30] = 255;
        first = math_random_int_below(8);
        second = math_random_int_below(18);
        anim_start_blended(object, 0, first, second);
        VI(0x144) = 0;
        if (VI(0x140) != -1 && VI(0x130) != 8) {
            *(float *)(object + 0x2C) *= 1.5f;
            if (object[0x43] != 4) {
                first = math_random_int_below(3);
                second = math_random_int_below(8);
                anim_start_blended(object, 4, first, second + 10);
            }
            moby_set_state(object, 7, -1);
        }
        break;
    case 2:
        if (fast_vec_dist(object + 0x10, g_hero_position) < 9.0f) {
            if (object[0x43] != 3) anim_start_blended(object, 3, 0, 10);
            moby_set_state(object, 4, -1);
            break;
        }
        if (*(int *)(g_hero_position + 0x11C8) != 10 && *(int *)(g_hero_position + 0x11C8) != 13 && (D_00138324 & 0x20)) {
            if (!(vec_distance_xy(object + 0x10, g_hero_position) < 64.0f) || VI(0x150)) break;
            VF(0x134) = (float)math_random_int_range(170, 190);
            if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
            VF(0x138) = 0.083333336f;
            moby_set_state(object, 6, -1);
        }
        break;
    case 4:
        if (object[0x60] & 2) {
            VF(0x134) = (float)math_random_int_range(170, 190);
            if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
            VF(0x138) = 0.033333335f;
            moby_set_state(object, 5, -1);
        }
        break;
    case 5:
        VF(0x138) += 0.008333334f;
        if (VF(0x138) > 0.116666675f) VF(0x138) = 0.116666675f;
        qcopy(previous, object + 0x10);
        angle = FastAddRotations(*(float *)(object + 0xF8), VF(0x134) * 0.017453294f);
        vec_build_spherical_offset(motion, VF(0x138), angle, 2.96706009f);
        hero_set_control_motion_and_step((char *)object, motion);
        if (vec_distance_xy(object + 0x10, previous) < VF(0x138)) {
            angle = FastAddRotations(*(float *)(object + 0xF8), 3.141593f);
            MobySpringTurn(object, (float *)(vars + 0x13C), angle, 0.000199999995f, 0.00200000009f, 0.04f);
        }
        if (vec_distance_xy(object + 0x10, g_hero_position) > 64.0f) {
            moby_mark_spawned(object);
            return;
        }
        math_update_wrapped_angle_offset((float *)object, (float *)(vars + 0x148), (float *)(vars + 0x14C), D_L11_001B2978, D_L11_001B297C * 0.00029088825f, -1.0f);
        break;
    case 6:
        VF(0x138) += 0.008333334f;
        if (VF(0x138) > 0.416666687f) VF(0x138) = 0.416666687f;
        angle = FastAddRotations(*(float *)(object + 0xF8), VF(0x134) * 0.017453294f);
        vec_build_spherical_offset(motion, VF(0x138), angle, 2.96706009f);
        FastVecAdd((float *)(object + 0x10), (float *)(object + 0x10), motion);
        if (vec_distance_xy(object + 0x10, g_hero_position) > 64.0f) {
            moby_mark_spawned(object);
            return;
        }
        break;
    case 7:
        path = D_L11_001FF580[VI(0x140)];
        distance = vec_distance_xy(object + 0x10, path + 4 + VI(0x144) * 4);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = mat_fast_helper_a(distance, point[6] - *(float *)(object + 0x18));
        vec_build_spherical_offset(motion, 0.116666675f, *(float *)(object + 0xF8), angle);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = mat_fast_helper_a(point[4] - *(float *)(object + 0x10), point[5] - *(float *)(object + 0x14));
        MobySpringTurn(object, (float *)(vars + 0x13C), angle, 9.99999975e-05f, 0.00100000005f, 0.02f);
        FastVecAdd((float *)(object + 0x10), (float *)(object + 0x10), motion);
        if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
        if (vec_distance_xy(object + 0x10, path + 4 + VI(0x144) * 4) < 0.5f) {
            ++VI(0x144);
            if (VI(0x144) >= *path - 1) VI(0x144) = *path - 1;
        }
        math_update_wrapped_angle_offset((float *)object, (float *)(vars + 0x148), (float *)(vars + 0x14C), D_L11_001B2978, D_L11_001B297C * 0.00029088825f, -1.0f);
        break;
    case 8:
        if (object[0x43] != 2) anim_start_blended(object, 2, 0, 10);
        if (vec_distance_xy(object + 0x10, vars + 0x120) < 0.5f ||
            VI(0xA0) || *(u16 *)(object + 0x96) >= 240) {
            *(u16 *)(object + 0x96) = 0;
            VI(0xA0) = 0;
            math_random_planar_offset((float *)(vars + 0x120), 4.0f);
            FastVecAdd((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
            if (math_random_int_below(4) == 1) {
                if (object[0x43] != 1) anim_start_blended(object, 1, 0, 10);
                moby_set_state(object, 9, -1);
            }
        } else {
            moby_l01_turn_toward_target((char *)object, (char *)vars + 0x120);
        }
        if (fast_vec_dist(object + 0x10, g_hero_position) < 10.0f) {
            if (object[0x43] != 2) anim_start_blended(object, 2, 0, 10);
            moby_set_state(object, 4, -1);
        }
        break;
    case 9:
        if (object[0x60] & 2) {
            moby_set_state(object, 8, -1);
            if (object[0x43] != 2) anim_start_blended(object, 2, 0, 10);
        }
        if (fast_vec_dist(object + 0x10, g_hero_position) < 10.0f) {
            if (object[0x43] != 2) anim_start_blended(object, 2, 0, 10);
            moby_set_state(object, 4, -1);
        }
        break;
    }
    timer = *(u16 *)(object + 0x96);
    if (timer < 65535) *(short *)(object + 0x96) = timer + 1;
    if (object[0x42] == 4) *(float *)(object + 0x48) = 2.5f;
    else if (object[0x42]) *(float *)(object + 0x48) = 1.0f;
    if (part_find_owned_effect_slot(object, 0x10000, 0)) {
        int i;
        for (i = 0; i < 14; i++) {
            u8 *particle;
            vec_random_direction(motion, 0.06666667f, 0.100000009f);
            particle = debris_l11_spawn_piece(object, (float *)(object + 0x10), motion);
            particle[0x30] = *(u16 *)(particle + 0x32) = 255;
        }
        ++D_L11_001AED08;
        moby_mark_spawned(object);
    } else {
        value_set_and_smooth(object, (float *)(vars + 0x160), 2.5f, 0, 1);
    }
}
