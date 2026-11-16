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
extern int shooter_entity_base_update(void *);
extern void entity_spawn_death_effects(void *);
extern void entity_finish_update(void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern void follow_camera_set_distance(int, float, float);
extern void follow_camera_set_height(float, float);
extern int flag_set_second_pending(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern void anim_start_blended(void *, int, int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int moby_l01_turn_toward_target(void *, void *);
extern int math_random_int_below(int);
extern int moby_check_target_point_from_offset(void *, void *);
extern float mat_fast_helper_a(float, float);
extern int moby_move_to_target_temp_limits(void *, void *, int, float, float, float);
extern int moby_turn_toward_target_and_step(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float moby_get_anim_value(void *);
extern int moby_start_effect_from_entry(void *, float);
extern int coll_sweep_from_object(void *, void *, int, float, float, int, float, int, int);
extern float FastDiffRots(float, float);
extern int moby_count_group_not_in_state(int, int);

/* Update the entity's submode, movement target and timed attack actions. */
void UpdateSiberiusEntityActions(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    float time;
    int result;
    int choices[4];
    if (g_frame_l07_counter >= 2 && g_cutscene_l07_active_flag != I(state, 0x350)) return;
    if (shooter_entity_base_update(actor)) goto cleanup;
    {
        switch (B(actor, 0x95)) {
        case 0:
            if (I(state, 0x2D4) == 1) {moby_set_state(actor, 6, 2); break;}
            if (I(state, 0x2D0)) {
                moby_set_state(actor, 3, 1);
                I(state, 0x2D0) = 0;
                if (I(state, 0x344) < 300) I(state, 0x344) = math_random_int_range(480, 600);
            }
            break;
        case 1:
            if (I(state, 0x2D4) == 1) moby_set_state(actor, 6, 2);
            break;
        case 2:
            follow_camera_set_distance(0, g_follow_cam_distance, 0.003f);
            follow_camera_set_height(g_follow_cam_height, 0.003f);
            if (flag_set_second_pending(actor))
                moby_set_controller_speed_limits(actor, g_entity_accel_limit*0.00027777778f, g_entity_speed_limit*0.016666668f, g_entity_turn_accel_limit*4.848137450608192e-06f, g_entity_turn_speed_limit*0.0002908882452175021f);
            if (I(state, 0x2D4) != 1 && B(actor, 0x20) != 7) {
                if (I(state, 0x338)) moby_set_state(actor, 3, 1);
                else moby_set_state(actor, 4, 1);
                I(state, 0x344) = math_random_int_range(580, 600);
            }
            break;
        case 3:
            result = moby_dispatch_action_by_kind(actor, state + 0x140);
            if (result & 1) {
                entity_spawn_death_effects(actor);
cleanup:
                /* The initialization helper also reaches this shared cleanup. */
                moby_mark_spawned(actor);
                return;
            }
            if (result & 2) {moby_set_state(actor, 7, 2);I(state, 0x344) = math_random_int_range(580, 600);}
            break;
        }
    }
    switch (B(actor, 0x20)) {
    case 1:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 2) anim_start_blended(actor, 2, 0, 20);
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) moby_set_state(actor, 2, -1);
        break;
    case 2: {
        float radius, angle;
        if (flag_set_first_pending(actor)) {
            if (B(actor, 0x43) != 8) anim_start_blended(actor, 8, 0, 20);
            radius = math_random_float_range(0, 5);
            angle = math_random_angle();
            F(state, 0x300) = math_fast_sin_or_cos_a(angle)*radius;
            F(state, 0x304) = math_fast_sin_or_cos_b(angle)*radius;
            F(state, 0x308) = 0;
            FastVecAdd(state + 0x300, state + 0x300, state + 0x2F0);
        }
        result = moby_l01_turn_toward_target(actor, state + 0x300);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 40) || H(actor, 0x96) > 180) moby_set_state(actor, 1, -1);
        break;
    }
    case 3:
        if (flag_set_first_pending(actor)) {
            *(struct Choice61 *)choices = g_entity_choice_set;
            if (B(actor, 0x43) != choices[math_random_int_below(4)]) anim_start_blended(actor, choices[math_random_int_below(4)], 0, 20);
        }
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) moby_set_state(actor, 4, -1);
        break;
    case 4: {
        float radius, angle;
        if (flag_set_first_pending(actor)) {
            if (B(actor, 0x43) != 8) anim_start_blended(actor, 8, 0, 20);
            radius = math_random_float_range(0, 3);
            angle = math_random_angle();
            F(state, 0x300) = math_fast_sin_or_cos_a(angle)*radius;
            F(state, 0x304) = math_fast_sin_or_cos_b(angle)*radius;
            F(state, 0x308) = 0;
            FastVecAdd(state + 0x300, state + 0x300, state + 0x2F0);
        }
        moby_check_target_point_from_offset(actor, state + 0x210);
        angle = mat_fast_helper_a(F(state, 0x300)-F(actor, 0x10), F(state, 0x304)-F(actor, 0x14));
        result = moby_move_to_target_temp_limits(actor, state + 0x300, 16, angle, -1, -1);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 40) || H(actor, 0x96) > 180) moby_set_state(actor, 3, -1);
        break;
    }
    case 6:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 11) anim_start_blended(actor, 11, 0, 20);
        moby_turn_toward_target_and_step(actor, state + 0x210, 0);
        if (vec_distance_xy(actor + 0x10, state + 0x210) < g_entity_arrive_distance) moby_set_state(actor, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 12) anim_start_blended(actor, 12, 5, 10);
        time = moby_get_anim_value(actor);
        if (time < 19) moby_start_effect_from_entry(actor, mat_fast_helper_a(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14)));
        else if (time<=22) {
            coll_sweep_from_object(actor, *(char **)(state + 0x330)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
            coll_sweep_from_object(actor, *(char **)(state + 0x334)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
        }
        if (B(actor, 0x60) & 2) {
            time = vec_distance_xy(actor + 0x10, state + 0x210);
            if (g_entity_arrive_distance+0.5f < time ||
                FastDiffRots(F(actor, 0xF8), mat_fast_helper_a(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14))) > 0.349065899848938f)
                moby_set_state(actor, 6, -1);
        }
        break;
    case 9:
        if (!moby_count_group_not_in_state(I(state, 0x2B8), -1) || F(state, 0x20) < *(short *)(state + 0x24)) moby_set_state(actor, 10, -1);
        break;
    case 10:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 1) anim_start_blended(actor, 1, 0, 2);
        if (B(actor, 0x60) & 2) moby_set_state(actor, 6, -1);
        break;
    }
    entity_finish_update(actor);
}
