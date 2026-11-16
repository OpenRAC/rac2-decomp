#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define U8(p, o) (*(unsigned char *)((p) + (o)))
#define U16(p, o) (*(unsigned short *)((p) + (o)))
#define S(p, o) (*(short *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
extern char g_hero_state_block[], g_hero_position[];
extern int g_hero_moby __attribute__((nosda));
extern int g_frame_l02_counter;
extern float g_chickenbot_wait_min __attribute__((sda));
extern float D_L02_001B00F8_abs MACRO_ADDR;
extern volatile float g_chickenbot_wait_max MACRO_ADDR;
extern void enemy_init(void *);
extern void moby_l02_explode_and_remove(void *);
extern void moby_reset_turn_place(void *);
extern void chickenbot_update_group_pulse_color(void *);
extern void turret_clamp_aim_yaw_pitch(void *);
extern void part_spawn_two_puffs(void *);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int FastDecTimer(void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int moby_run_entry_hook_by_mode(void *, void *, int);
extern int moby_count_group_side_from_object(void *, int, int);
extern int math_is_value_within_step_us2(void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void path_clamp_move_to_area(void *, void *, void *, int, float);
extern int moby_start_effect_from_entry(void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int coll_test_hit_at_bone(void *, int, int, int, int, int, float, float, float);
extern int moby_check_target_point_from_offset(char *, void *);
extern int coll_sweep_from_object(void *, float, float *, int, float, float, int, int, int);

/* Per-frame update of a creature with a state machine. It picks animations, wanders, turns toward the hero and runs, then checks its own state to move or attack (USA v2.00). */
void chickenbot_state_machine_update_us2(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float angle, speed;
    int anim_index;
    Quad path_pos;

    enemy_init(moby);
    switch (U8(moby, 0x95)) {
    case 0:
        if (flag_set_second_pending(moby)) {
            moby_set_controller_speed_limits(moby, 0.005f, 0.06666667f, 0.006981317885220051f,
                         0.41887909173965454f);
            F(vars, 0x1D0) = 0.06666667f;
            F(vars, 0x124) = 0.006666666828095913f;
            F(vars, 0x134) = 0.5f;
            S(vars, 0x33A) = math_random_int_range(0, 30);
        }
        if (S(vars, 0x314) == 1) {
            if (FastDecTimer(vars + 0x33A)) {
                if (math_random_int_below(3))
                    moby_set_state(moby, 9, 2);
                else
                    moby_set_state(moby, 8, 2);
                break;
            }
        }
        if (S(vars, 0x316)) {
            if (math_random_int_below(2))
                moby_set_state(moby, 7, 1);
            else
                moby_set_state(moby, 6, 1);
            S(vars, 0x316) = 0;
            if (S(vars, 0x310) < 300)
                S(vars, 0x310) = math_random_int_range(480, 600);
        }
        break;
    case 1:
        if (flag_set_second_pending(moby)) {
            moby_set_controller_speed_limits(moby, 0.005f, 0.06666667f, 0.01745329424738884f,
                         1.047197699546814f);
            F(vars, 0x1D0) = 0.06666667f;
            F(vars, 0x134) = 0.05f;
        }
        if (S(vars, 0x314) == 1) {
            moby_set_state(moby, 9, 2);
        } else if (S(vars, 0x310) == 0)
            moby_set_state(moby, 1, 0);
        break;
    case 2:
        if (flag_set_second_pending(moby)) {
            moby_set_controller_speed_limits(moby, 0.005f, 0.06666667f, 0.01745329424738884f,
                         1.047197699546814f);
            F(vars, 0x1D0) = 0.06666667f;
            F(vars, 0x124) = 0.006666666828095913f;
            F(vars, 0x134) = 0.05f;
            S(vars, 0x33A) = math_random_int_range(0, 30);
        }
        if (S(vars, 0x314) != 1 && FastDecTimer(vars + 0x33A)) {
            moby_set_state(moby, 3, 1);
            S(vars, 0x310) = math_random_int_range(580, 600);
        }
        break;
    case 3: {
        unsigned int flags;
        flags = moby_dispatch_action_by_kind(moby, vars + 0x50);
        if (flags & 1)
            moby_l02_explode_and_remove(moby);
        else if (flags & 2) {
            if (S(vars, 0x314) == 1)
                moby_set_state(moby, 9, 2);
            else {
                moby_set_state(moby, 3, 1);
                S(vars, 0x310) = math_random_int_range(580, 600);
            }
        }
        break;
    }
    }
    switch (U8(moby, 0x20)) {
    case 1:
        if (U8(moby, 0x31)) {
            if (flag_set_first_pending(moby)) {
                anim_index = !math_random_int_below(4);
                if (U8(moby, 0x43) != anim_index)
                    anim_start_blended(moby, anim_index, 0, 10);
                S(vars, 0x312) = math_random_int_range(60, 120);
            }
            if (U8(moby, 0x43) == 1) {
                if (U8(moby, 0x60) & 2)
                    anim_start_blended(moby, 0, 0, 20);
            } else if (!S(vars, 0x312) &&
                       (!S(vars, 0x338) || FastVecDot(vars + 0x300, g_hero_state_block) > 0.8f))
                moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            if (U8(moby, 0x43) != 6)
                anim_start_blended(moby, 6, 0, 20);
            angle = math_random_angle();
            speed = math_random_float_range(2, 5);
            F(vars, 0x2F0) = math_fast_sin_or_cos_a(angle) * speed;
            F(vars, 0x2F4) = math_fast_sin_or_cos_b(angle) * speed;
            F(vars, 0x2F8) = 0;
            FastVecAdd(vars + 0x2F0, vars + 0x2F0, vars + 0x2E0);
            if (I(vars, 0x218) != -1) {
                path_pos = *(Quad *)(vars + 0x2E0);
                path_clamp_move_to_area(&path_pos, vars + 0x2F0, vars + 0x2F0, I(vars, 0x218), 1.5f);
            }
        }
        moby_run_entry_hook_by_mode(moby, vars + 0x2F0, 0);
        if (U16(moby, 0x96) > 30 && (F(vars, 0x1CC) <= 0.5f || U16(moby, 0x96) > 180))
            moby_set_state(moby, 1, -1);
        break;
    case 3:
        if (flag_set_first_pending(moby) && U8(moby, 0x43) != math_random_int_below(2) + 4)
            anim_start_blended(moby, math_random_int_below(2) + 4, 0, 10);
        if (fast_vec_dist(moby + 0x10, g_hero_position) < D_L02_001B00F8_abs)
            moby_set_state(moby, 4, -1);
        else if (U8(moby, 0x60) & 2) {
            switch (math_random_int_below(3)) {
            case 0:
                moby_set_state(moby, 6, -1);
                break;
            case 1:
                moby_set_state(moby, 7, -1);
                break;
            case 2:
                moby_set_state(moby, 5, -1);
                break;
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(moby) && U8(moby, 0x43) != math_random_int_below(2) + 2)
            anim_start_blended(moby, math_random_int_below(2) + 2, 0, 10);
        moby_check_target_point_from_offset(moby, vars + 0x1F0);
        if (U8(moby, 0x60) & 2)
            moby_set_state(moby, 3, -1);
        break;
    case 7:
        if (flag_set_first_pending(moby) && U8(moby, 0x43) != 12)
            anim_start_blended(moby, 12, 0, 10);
        moby_check_target_point_from_offset(moby, vars + 0x1F0);
        if (U8(moby, 0x60) & 2)
            moby_set_state(moby, 3, -1);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            if (U8(moby, 0x43) != 6)
                anim_start_blended(moby, 6, 0, 10);
            {
                float upper = g_chickenbot_wait_max;
                F(vars, 0x334) = math_random_float_range(g_chickenbot_wait_min, upper) + 0.5f;
            }
        }
        if ((moby_run_entry_hook_by_mode(moby, vars + 0x2E0, 0) & 0x80) ||
            vec_distance_xy(moby + 0x10, g_hero_position) > F(vars, 0x334)) {
            if (math_random_int_below(2))
                moby_set_state(moby, 6, -1);
            else
                moby_set_state(moby, 7, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            if (U8(moby, 0x43) != 6)
                anim_start_blended(moby, 6, 0, 20);
            angle = math_random_angle();
            speed = math_random_float_range(2, 5);
            F(vars, 0x2F0) = math_fast_sin_or_cos_a(angle) * speed;
            F(vars, 0x2F4) = math_fast_sin_or_cos_b(angle) * speed;
            F(vars, 0x2F8) = 0;
            FastVecAdd(vars + 0x2F0, vars + 0x2F0, vars + 0x2E0);
            if (I(vars, 0x218) != -1) {
                path_pos = *(Quad *)(vars + 0x2E0);
                path_clamp_move_to_area(&path_pos, vars + 0x2F0, vars + 0x2F0, I(vars, 0x218), 1.5f);
            }
        }
        moby_run_entry_hook_by_mode(moby, vars + 0x2F0, 0);
        if (U16(moby, 0x96) > 30 && (F(vars, 0x1CC) <= 0.5f || U16(moby, 0x96) > 180))
            moby_set_state(moby, 3, -1);
        break;
    case 8:
        if (flag_set_first_pending(moby) && U8(moby, 0x43) != math_random_int_below(2) + 2)
            anim_start_blended(moby, math_random_int_below(2) + 2, 0, 10);
        if (U8(moby, 0x60) & 2)
            moby_set_state(moby, 9, -1);
        break;
    case 9:
        if (flag_set_first_pending(moby) && U8(moby, 0x43) != 6)
            anim_start_blended(moby, 6, 0, 5);
        if (!(U16(moby, 0x96) & 3))
            F(vars, 0x31C) = moby_count_group_side_from_object(moby, g_hero_moby, -1) * 0.087266475f;
        moby_run_entry_hook_by_mode(moby, vars + 0x1F0, 1);
        turret_clamp_aim_yaw_pitch(moby);
        if (F(vars, 0x1CC) <= 1.25f)
            moby_set_state(moby, 10, -1);
        break;
    case 10:
        if (flag_set_first_pending(moby)) {
            F(vars, 0x320) = mat_fast_helper_a(F(vars, 0x1F0) - F(moby, 0x10),
                                       F(vars, 0x1F4) - F(moby, 0x14));
            if (U8(moby, 0x43) != 8)
                anim_start_blended(moby, 8, 2, 10);
        }
        moby_start_effect_from_entry(moby, F(vars, 0x320));
        if (math_is_value_within_step_us2(moby, 13))
            coll_test_hit_at_bone(moby, 1, 0x4000001, 0, 1, 0, 0.75f, U8(vars, 0x34), 1);
        if (U8(moby, 0x60) & 2)
            moby_set_state(moby, 9, -1);
        break;
    case 14:
        if (flag_set_first_pending(moby)) {
            if (U8(moby, 0x43) != 10)
                anim_start_blended(moby, 10, 0, 5);
            I(vars, 0x1BC) = g_frame_l02_counter;
        }
        vec_scale_to_length(&path_pos, vars + 0x1A0, 1);
        moby_run_entry_hook_by_mode(moby, &path_pos, 0);
        part_spawn_two_puffs(moby);
        coll_sweep_from_object(moby, 0.6f, (float *)(moby + 0x10), 0x4000000, 1, 1, 0, 1, 0);
        if (F(vars, 0x190) >= F(moby, 0x18)) {
            if (S(vars, 0x314) == 1)
                moby_set_state(moby, 8, 2);
            else
                moby_set_state(moby, 2, 0);
            I(vars, 0x138) &= -18;
        }
        break;
    case 12:
        moby_l02_explode_and_remove(moby);
        break;
    }
    moby_reset_turn_place(moby);
    if (U8(moby, 0x31))
        chickenbot_update_group_pulse_color(moby);
}
