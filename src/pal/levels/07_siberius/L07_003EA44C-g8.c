/* func_PAL_L07_003EA44C, the PAL copy of func_L07_003E61E0: the same C, where the three
 * retimed 0x344 stores (480..600 and 580..600, twice) take PAL's 50 Hz scale. */
#include "common.h"
#define I(p, o) (*(int *)((p)+(o)))
#define H(p, o) (*(unsigned short *)((p)+(o)))
#define B(p, o) (*(unsigned char *)((p)+(o)))
#define F(p, o) (*(float *)((p)+(o)))
extern int g_frame_l07_counter MACRO_ADDR;
extern int g_cutscene_l07_active_flag NOT_SDA;
extern float g_entity_arrive_distance __attribute__((sda));
extern float g_entity_accel_limit __attribute__((sda));
extern float g_entity_speed_limit __attribute__((sda));
extern float g_entity_turn_accel_limit __attribute__((sda));
extern float g_entity_turn_speed_limit __attribute__((sda));
extern float g_follow_cam_distance __attribute__((sda));
extern float g_follow_cam_height __attribute__((sda));
extern struct Choice61 {int a, b, c, d;} g_entity_choice_set;
extern int shooter_entity_base_update_pal(void *);
extern void entity_spawn_death_effects_pal(void *);
extern void entity_finish_update_pal(void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern void follow_camera_set_distance(int, float, float);
extern void follow_camera_set_height(float, float);
extern int flag_set_second_pending(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int math_random_int_below(int);
extern int moby_check_target_point_from_offset(void *, void *);
extern float mat_fast_helper_a(float, float);
extern int moby_move_to_target_temp_limits_pal(void *, void *, int, float, float, float);
extern int moby_turn_toward_target_and_step_pal(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float moby_get_anim_value(void *);
extern int moby_start_effect_from_entry(void *, float);
extern int coll_sweep_from_object(void *, void *, int, float, float, int, float, int, int);
extern float FastDiffRots(float, float);
extern int moby_count_group_not_in_state(int, int);

/* Update the entity's submode, movement target and timed attack actions. */
void siberius_entity_actions_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float anim_time;
    int result;
    int choices[4];
    if (g_frame_l07_counter >= 2 && g_cutscene_l07_active_flag != I(vars, 0x350)) return;
    if (shooter_entity_base_update_pal(moby)) goto cleanup;
    {
        switch (B(moby, 0x95)) {
        case 0:
            if (I(vars, 0x2D4) == 1) {moby_set_state(moby, 6, 2); break;}
            if (I(vars, 0x2D0)) {
                moby_set_state(moby, 3, 1);
                I(vars, 0x2D0) = 0;
                if (I(vars, 0x344) < 250) I(vars, 0x344) = ((s32)(math_random_int_range(480, 600)) * 5 + 2) / 6;
            }
            break;
        case 1:
            if (I(vars, 0x2D4) == 1) moby_set_state(moby, 6, 2);
            break;
        case 2:
            follow_camera_set_distance(0, g_follow_cam_distance, 0.003f);
            follow_camera_set_height(g_follow_cam_height, 0.003f);
            if (flag_set_second_pending(moby))
                moby_set_controller_speed_limits(moby, g_entity_accel_limit*0.00040000002f, g_entity_speed_limit*0.020000001f, g_entity_turn_accel_limit*6.981318e-06f, g_entity_turn_speed_limit*0.0003490659f);
            if (I(vars, 0x2D4) != 1 && B(moby, 0x20) != 7) {
                if (I(vars, 0x338)) moby_set_state(moby, 3, 1);
                else moby_set_state(moby, 4, 1);
                I(vars, 0x344) = ((s32)(math_random_int_range(580, 600)) * 5 + 2) / 6;
            }
            break;
        case 3:
            result = moby_dispatch_action_by_kind(moby, vars + 0x140);
            if (result & 1) {
                entity_spawn_death_effects_pal(moby);
cleanup:
                /* The initialization helper also reaches this shared cleanup. */
                moby_mark_spawned(moby);
                return;
            }
            if (result & 2) {moby_set_state(moby, 7, 2);I(vars, 0x344) = ((s32)(math_random_int_range(580, 600)) * 5 + 2) / 6;}
            break;
        }
    }
    switch (B(moby, 0x20)) {
    case 1:
        if (flag_set_first_pending(moby) && B(moby, 0x43) != 2) anim_start_blended_pal(moby, 2, 0, 17);
        if ((B(moby, 0x60) & 2) && !I(vars, 0x338)) moby_set_state(moby, 2, -1);
        break;
    case 2: {
        float radius, angle;
        if (flag_set_first_pending(moby)) {
            if (B(moby, 0x43) != 8) anim_start_blended_pal(moby, 8, 0, 17);
            radius = math_random_float_range(0, 5);
            angle = math_random_angle();
            F(vars, 0x300) = math_fast_sin_or_cos_a(angle)*radius;
            F(vars, 0x304) = math_fast_sin_or_cos_b(angle)*radius;
            F(vars, 0x308) = 0;
            FastVecAdd(vars + 0x300, vars + 0x300, vars + 0x2F0);
        }
        result = moby_l01_turn_toward_target_pal(moby, vars + 0x300);
        if (result == 128 || (I(vars, 0xD0) && H(moby, 0x96) > 33) || H(moby, 0x96) > 150) moby_set_state(moby, 1, -1);
        break;
    }
    case 3:
        if (flag_set_first_pending(moby)) {
            *(struct Choice61 *)choices = g_entity_choice_set;
            if (B(moby, 0x43) != choices[math_random_int_below(4)]) anim_start_blended_pal(moby, choices[math_random_int_below(4)], 0, 17);
        }
        if ((B(moby, 0x60) & 2) && !I(vars, 0x338)) moby_set_state(moby, 4, -1);
        break;
    case 4: {
        float radius, angle;
        if (flag_set_first_pending(moby)) {
            if (B(moby, 0x43) != 8) anim_start_blended_pal(moby, 8, 0, 17);
            radius = math_random_float_range(0, 3);
            angle = math_random_angle();
            F(vars, 0x300) = math_fast_sin_or_cos_a(angle)*radius;
            F(vars, 0x304) = math_fast_sin_or_cos_b(angle)*radius;
            F(vars, 0x308) = 0;
            FastVecAdd(vars + 0x300, vars + 0x300, vars + 0x2F0);
        }
        moby_check_target_point_from_offset(moby, vars + 0x210);
        angle = mat_fast_helper_a(F(vars, 0x300)-F(moby, 0x10), F(vars, 0x304)-F(moby, 0x14));
        result = moby_move_to_target_temp_limits_pal(moby, vars + 0x300, 16, angle, -1, -1);
        if (result == 128 || (I(vars, 0xD0) && H(moby, 0x96) > 33) || H(moby, 0x96) > 150) moby_set_state(moby, 3, -1);
        break;
    }
    case 6:
        if (flag_set_first_pending(moby) && B(moby, 0x43) != 11) anim_start_blended_pal(moby, 11, 0, 17);
        moby_turn_toward_target_and_step_pal(moby, vars + 0x210, 0);
        if (vec_distance_xy(moby + 0x10, vars + 0x210) < g_entity_arrive_distance) moby_set_state(moby, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(moby) && B(moby, 0x43) != 12) anim_start_blended_pal(moby, 12, 5, 8);
        anim_time = moby_get_anim_value(moby);
        if (anim_time < 19) moby_start_effect_from_entry(moby, mat_fast_helper_a(F(vars, 0x210)-F(moby, 0x10), F(vars, 0x214)-F(moby, 0x14)));
        else if (anim_time<=22) {
            coll_sweep_from_object(moby, *(char **)(vars + 0x330)+0x10, 1, 0.333f, (float)B(vars, 0x34), 0, 1.0f, 1, 0);
            coll_sweep_from_object(moby, *(char **)(vars + 0x334)+0x10, 1, 0.333f, (float)B(vars, 0x34), 0, 1.0f, 1, 0);
        }
        if (B(moby, 0x60) & 2) {
            anim_time = vec_distance_xy(moby + 0x10, vars + 0x210);
            if (g_entity_arrive_distance+0.5f < anim_time ||
                FastDiffRots(F(moby, 0xF8), mat_fast_helper_a(F(vars, 0x210)-F(moby, 0x10), F(vars, 0x214)-F(moby, 0x14))) > 0.349065899848938f)
                moby_set_state(moby, 6, -1);
        }
        break;
    case 9:
        if (!moby_count_group_not_in_state(I(vars, 0x2B8), -1) || F(vars, 0x20) < *(short *)(vars + 0x24)) moby_set_state(moby, 10, -1);
        break;
    case 10:
        if (flag_set_first_pending(moby) && B(moby, 0x43) != 1) anim_start_blended_pal(moby, 1, 0, 2);
        if (B(moby, 0x60) & 2) moby_set_state(moby, 6, -1);
        break;
    }
    entity_finish_update_pal(moby);
}
