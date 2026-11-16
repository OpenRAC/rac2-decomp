#include "names.h"
/* func_PAL_L09_003FEAF0 (levels 09 and 20), the PAL copy of func_L09_003FA080: the same C, with
 * the frame timers scaled 5/6 for 50 Hz and the turn rate scaled 6/5.  D_L09_001B0F40 is read as
 * a word here, and the timer tests of case 11 are written with the frame count first. */
#include "common.h"

extern int g_trooper_debug_flag __attribute__((sda));
extern int g_trooper_spawn_delay_min __attribute__((sda));
extern int g_trooper_spawn_delay_max __attribute__((sda));
extern float g_trooper_move_speed __attribute__((sda));
extern int g_frame_l09_counter __attribute__((sda));
extern float g_trooper_attack_range __attribute__((sda));
extern int g_trooper_fire_chance __attribute__((sda));
extern int g_trooper_frame_min __attribute__((sda));
extern int g_trooper_frame_max __attribute__((sda));
extern int g_trooper_anim_period __attribute__((sda));
extern int g_trooper_timer_min __attribute__((sda));
extern int g_trooper_timer_max __attribute__((sda));
extern s32 g_moby_record_table MACRO_ADDR;
extern char *g_path_l09_table[];
extern char g_str_trooper_debug_anim[];
extern char g_str_trooper_debug_msg[];

extern void STUB_printf(const char *, ...);
extern int FastDecTimer(void *);
extern float vec_distance_xy(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern float IntToFloat(int);
extern void moby_mark_spawned(void *);
extern void SetDeathBits(void *, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_wrap_angle_to_pi(float);
extern int moby_is_in_selected_zone(void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int part_spawn_damage_debris(void *, void *, void *);
extern int flag_set_first_pending(void *);
extern int moby_step_at_own_position_factor(void *, float);
extern int PlayMobySound(int, int, void *);
extern int func_001163B0(void);
extern void part_spawn_small_burst_pal(void *, float);
extern void shared_counter_release(void *);
extern void shared_counter_acquire(void *);
extern void trooper_clear_value_self_torso(void *);
extern void trooper_copy_owner_value_self_torso(void *);
extern void enemy_set_animation_state_pal(void *, int, int, int);
extern void moby_destroy_linked(void *);
extern int enemy_walk_to_next_path_point(void *, int);
extern s32 enemy_select_path(void *, int, int);
extern void transfer_state_to_nearest_eligible_object_pal(void *);
extern void trooper_rearm_spawn_timers_pal(void *);
extern void trooper_legs_update_frame_pal(void *);
extern void trooper_torso_update_attachment_pal(void *);
extern void trooper_attach_arm_parts(void *);
extern int enemy_check_line_of_sight(void *, int, int, int);
extern void trooper_fire_arm_shot_pal(void *);
extern void enemy_move_along_path(void *);
extern void enemy_choose_next_action_pal(void *);
extern int enemy_process_activation(void *);

/* Update for the Megacorp Trooper Legs (moby class 3343). It picks what the trooper does next: walk, aim, shoot or die (PAL: 50 Hz timings). */
void trooper_legs_update_pal(char *self)
{
    char *vars;
    int state;

    if (g_trooper_debug_flag != 0)
        return;
    if (moby_is_in_selected_zone(self + 0x10) == 0)
        return;
    vars = *(char **)(self + 0x68);
    if (enemy_process_activation(self) != 0)
        return;
    trooper_clear_value_self_torso(self);
    state = *(u8 *)(self + 0x95);
    trooper_legs_update_frame_pal(self);
    if (self == 0 || *(u8 *)(self + 0x20) == 0xFE || *(u8 *)(self + 0x20) == 0xFD || state == 0)
        return;

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        STUB_printf(g_str_trooper_debug_anim, *(s16 *)(self + 0xB2), *(s16 *)(self + 0xAA));
        break;
    case 1: {
        int k;
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        k = *(int *)(vars + 0x4B0);
        if (k == -1 || ((u8 *)((k << 8) + g_moby_record_table))[0x20] == 0xFE
            || ((u8 *)((k << 8) + g_moby_record_table))[0x20] == 0xFD) {
            if (*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x2E0) != 0) {
                *(int *)(vars + 0x2D8) = *(int *)(vars + 0x2D4);
                if ((*(u8 *)(vars + 0x302) ^ 1) & 1) {
                    *(s16 *)(vars + 0x2E0) = ((s32)(math_random_int_range(g_trooper_spawn_delay_min, g_trooper_spawn_delay_max)) * 5 + 2) / 6;
                    moby_set_state(self, *(u8 *)(self + 0x20), 2);
                } else {
                    enemy_set_animation_state_pal(self, 0xC, 0, math_random_int_range(7, 0xC));
                    moby_set_state(self, 8, 5);
                }
            }
        }
        break;
    }
    case 2:
        if (FastDecTimer(vars + 0x300) != 0) {
            *(int *)(vars + 0x2D8) = *(int *)(vars + 0x2D4);
            if (*(int *)(vars + 0x2B0) != -1) {
                enemy_select_path(self, *(int *)(vars + 0x2B0), -1);
                if (*(u8 *)(self + 0x42) != 2)
                    enemy_set_animation_state_pal(self, 2, 0, 0);
                moby_set_state(self, 2, 3);
            } else {
                enemy_select_path(self, *(int *)(vars + 0x2B8), -1);
                enemy_set_animation_state_pal(self, 2, 0, 0xA);
                *(float *)(self + 0x48) = g_trooper_move_speed;
                moby_set_state(self, 4, 3);
            }
            if (*(u8 *)(vars + 0x302) & 2) {
                enemy_select_path(self, *(int *)(vars + 0x2C0), -1);
                *(u8 *)(vars + 0x302) = 0;
            }
        }
    case 3:
        *(float *)(vars + 0x2EC) = mat_fast_helper_a(*(float *)(*(char **)(vars + 0x200) + 0x10) - *(float *)(self + 0x10),
                                                 *(float *)(*(char **)(vars + 0x200) + 0x14) - *(float *)(self + 0x14));
        if (*(int *)(vars + 0x204) == 1)
            *(s16 *)(vars + 0x2E0) = ((s32)(math_random_int_range(g_trooper_spawn_delay_min, g_trooper_spawn_delay_max)) * 5 + 2) / 6;
        break;
    case 4:
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        if (*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x2E0) != 0) {
            enemy_select_path(self, *(int *)(vars + 0x2B8), -1);
            *(s16 *)(vars + 0x2E0) = ((s32)(math_random_int_range(g_trooper_spawn_delay_min, g_trooper_spawn_delay_max)) * 5 + 2) / 6;
            enemy_set_animation_state_pal(self, 2, 0, 0xA);
            *(float *)(self + 0x48) = g_trooper_move_speed;
            moby_set_state(self, 4, 3);
        }
        break;
    case 5:
        *(float *)(vars + 0x2EC) = mat_fast_helper_a(*(float *)(*(char **)(vars + 0x200) + 0x10) - *(float *)(self + 0x10),
                                                 *(float *)(*(char **)(vars + 0x200) + 0x14) - *(float *)(self + 0x14));
        if (*(u8 *)(vars + 0x302) & 2) {
            enemy_set_animation_state_pal(self, func_001163B0() & 1, 0, math_random_int_range(10, 20));
            shared_counter_release(self);
            *(s16 *)(vars + 0x2E0) = ((s32)(math_random_int_range(g_trooper_spawn_delay_min, g_trooper_spawn_delay_max)) * 5 + 2) / 6;
            *(s16 *)(vars + 0x300) = 1;
            moby_set_state(self, *(u8 *)(self + 0x20), 2);
        }
        if (*(int *)(vars + 0x204) != 1 && *(s16 *)(vars + 0x2E0) == 0) {
            shared_counter_release(self);
            enemy_set_animation_state_pal(self, func_001163B0() & 1, 0, math_random_int_range(10, 20));
            moby_set_state(self, 5, 6);
        }
        break;
    case 6:
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        if (*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x2E0) != 0) {
            shared_counter_release(self);
            *(s16 *)(vars + 0x2E0) = ((s32)(math_random_int_range(g_trooper_spawn_delay_min, g_trooper_spawn_delay_max)) * 5 + 2) / 6;
            enemy_set_animation_state_pal(self, 3, 0, math_random_int_range(7, 0xC));
            moby_set_state(self, 5, 5);
        } else if (*(s16 *)(vars + 0x2E8) == 0) {
            shared_counter_release(self);
            enemy_select_path(self, *(int *)(vars + 0x2B8), 0);
            enemy_set_animation_state_pal(self, func_001163B0() & 1, 0, math_random_int_range(10, 20));
            moby_set_state(self, 4, 4);
        }
        break;
    case 7:
        *(float *)(vars + 0x2EC) = mat_fast_helper_a(*(float *)(*(char **)(vars + 0x200) + 0x10) - *(float *)(self + 0x10),
                                                 *(float *)(*(char **)(vars + 0x200) + 0x14) - *(float *)(self + 0x14));
        break;
    case 8:
        *(float *)(vars + 0x2EC) = FastAddRotations(*(float *)(vars + 0x2EC),
            (math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(g_frame_l09_counter) * 0.02f)) + 2.0f) * 0.027925273f);
        break;
    case 9: {
        int flags;
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        flags = moby_dispatch_action_by_kind(self, vars + 0x50);
        if (*(float *)(vars + 0x20) <= 0.0f
            && (*(u8 *)(self + 0x42) == 0xF || *(u8 *)(self + 0x43) == 0xF
                || (*(int *)(vars + 0x2DC) != -1 && *(int *)(vars + 0x2DC) == *(int *)(vars + 0x2B0))))
            moby_set_state(self, 0xF, -1);
        if (flags & 1) {
            if (*(float *)(vars + 0x20) > 0.0f)
                transfer_state_to_nearest_eligible_object_pal(self);
            shared_counter_release(self);
            moby_set_state(self, 0xF, -1);
        } else if (flags & 2) {
            shared_counter_release(self);
            *(s16 *)(vars + 0x2E0) = ((s32)(math_random_int_range(g_trooper_spawn_delay_min, g_trooper_spawn_delay_max)) * 5 + 2) / 6;
            if (*(u8 *)(self + 0x42) == 0xF || *(u8 *)(self + 0x43) == 0xF
                || (*(int *)(vars + 0x2DC) != -1 && *(int *)(vars + 0x2DC) == *(int *)(vars + 0x2B0))
                || *(int *)(vars + 0x428) != 0) {
                if (*(int *)(vars + 0x428) != 2) {
                    enemy_select_path(self, *(int *)(vars + 0x2B0), -1);
                    moby_set_state(self, 3, 3);
                } else {
                    moby_set_state(self, 0x10, 3);
                }
                enemy_set_animation_state_pal(self, 0xE, 0, math_random_int_range(7, 0xC));
            } else {
                if (*(int *)(vars + 0x2DC) != -1)
                    enemy_set_animation_state_pal(self, 0xB, 0, math_random_int_range(7, 0xC));
                else
                    enemy_set_animation_state_pal(self, 0, 0, math_random_int_range(7, 0xC));
                if (*(u8 *)(vars + 0x30F) != 0)
                    moby_set_state(self, 0xD, 8);
                else
                    moby_set_state(self, 6, 5);
            }
        }
        break;
    }
    }

    switch (*(u8 *)(self + 0x20)) {
    case 0:
        break;
    case 1:
        if (*(u8 *)(self + 0x60) & 2)
            enemy_set_animation_state_pal(self, 0xE, 0, math_random_int_range(7, 0xC));
        break;
    case 2:
        if ((*(char **)(vars + 0x2F8) != 0 && (*(u8 *)(*(char **)(vars + 0x2F8) + 0x60) & 2))
            || (*(u8 *)(self + 0x60) & 2)) {
            enemy_set_animation_state_pal(self, 0xE, 0, math_random_int_range(7, 0xC));
            moby_set_state(self, 3, -1);
        }
        break;
    case 4:
        if (*(int *)(vars + 0x2DC) != -1) {
            char *p = g_path_l09_table[*(int *)(vars + 0x2DC)] + *(s16 *)(vars + 0x1C8) * 0x10;
            moby_step_at_own_position_factor(self, mat_fast_helper_a(*(float *)(p + 0x10) - *(float *)(self + 0x10),
                                              *(float *)(p + 0x14) - *(float *)(self + 0x14)));
        }
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(int *)(vars + 0x2DC) != -1)
                enemy_set_animation_state_pal(self, 0xB, 0, math_random_int_range(7, 0xC));
            else
                enemy_set_animation_state_pal(self, 0, 0, math_random_int_range(7, 0xC));
            moby_set_state(self, 6, -1);
        }
        break;
    case 5:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(u8 *)(self + 0x95) == 5) {
                if (*(int *)(vars + 0x2DC) != -1)
                    enemy_set_animation_state_pal(self, 0xB, 0, math_random_int_range(7, 0xC));
                else
                    enemy_set_animation_state_pal(self, 0, 0, math_random_int_range(7, 0xC));
                moby_set_state(self, 6, -1);
            } else if (*(int *)(vars + 0x2DC) != -1) {
                enemy_set_animation_state_pal(self, 0xC, 0, math_random_int_range(7, 0xC));
                moby_set_state(self, 6, -1);
            }
        }
        break;
    case 3:
        if (*(u8 *)(self + 0x60) & 2)
            enemy_set_animation_state_pal(self, 0xE, 0, math_random_int_range(7, 0xC));
        if (enemy_walk_to_next_path_point(self, *(int *)(vars + 0x2DC)) != 0) {
            if (*(int *)(vars + 0x428) == 0) {
                *(int *)(vars + 0x138) &= ~4;
                enemy_select_path(self, *(int *)(vars + 0x2BC), -1);
                enemy_set_animation_state_pal(self, 0x10, 0, math_random_int_range(7, 0xC));
                moby_set_state(self, 7, 5);
            } else {
                moby_set_state(self, 0x10, 5);
            }
        }
        break;
    case 6:
        enemy_choose_next_action_pal(self);
        break;
    case 16: {
        int near;
        int close;
        int lt;
        int got;
        int tried;
        float d;
        near = 1;
        d = vec_distance_xy(self + 0x10, *(char **)(vars + 0x200) + 0x10);
        if (!(d <= *(float *)(vars + 0x4BC)))
            near = 0;
        close = 1;
        lt = **(int **)(vars + 0x304) < *(int *)(vars + 0x2CC);
        if (!(d < g_trooper_attack_range))
            close = 0;
        got = 0;
        tried = 0;
        if (flag_set_first_pending(self) != 0) {
            *(int *)(vars + 0x428) = 2;
            *(int *)(vars + 0x4B4) = 0;
            *(int *)(vars + 0x138) |= 0x10;
        }
        if (!close && near && lt && math_random_int_below(g_trooper_fire_chance - 1) == 0 && *(s16 *)(vars + 0x2E6) == 0) {
            tried = 1;
            got = enemy_check_line_of_sight(self, 0, *(u8 *)(vars + 0x30C) != 0, 0);
        }
        if ((close || got) && lt) {
            if (enemy_check_line_of_sight(self, 0, *(u8 *)(vars + 0x30C) != 0, 1) != 0)
                *(u8 *)(vars + 0x30D) = 1;
            *(int *)(vars + 0x138) &= ~0x10;
            shared_counter_acquire(self);
            enemy_set_animation_state_pal(self, 8, 0, 7);
            STUB_printf(g_str_trooper_debug_msg);
            moby_set_state(self, 0xA, -1);
        }
        if (tried && !got)
            *(u8 *)(vars + 0x30C) = ~*(u8 *)(vars + 0x30C);
        enemy_move_along_path(self);
        break;
    }
    case 7:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(u8 *)(vars + 0x30E) != 0) {
                enemy_set_animation_state_pal(self, 4, 0, math_random_int_range(7, 0xC));
                moby_set_state(self, 4, 5);
            } else {
                enemy_set_animation_state_pal(self, 0xC, 0, math_random_int_range(7, 0xC));
                moby_set_state(self, 8, 5);
            }
        }
        break;
    case 8: {
        float a = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(self + 0x10),
                                *(float *)(vars + 0x1F4) - *(float *)(self + 0x14));
        moby_step_at_own_position_factor(self, a);
        if (FastDiffRots(a, *(float *)(self + 0xF8)) < 0.17453295f) {
            enemy_set_animation_state_pal(self, 5, 0, math_random_int_range(7, 0xC));
            *(u8 *)(vars + 0x30C) = 0;
            *(u8 *)(vars + 0x30D) = 0;
            moby_set_state(self, 9, -1);
        }
        break;
    }
    case 9: {
        int near;
        int close;
        int lt;
        float d;
        near = 1;
        d = vec_distance_xy(self + 0x10, *(char **)(vars + 0x200) + 0x10);
        if (!(d <= *(float *)(vars + 0x4BC)))
            near = 0;
        close = 1;
        lt = **(int **)(vars + 0x304) < *(int *)(vars + 0x2CC);
        if (!(d < g_trooper_attack_range))
            close = 0;
        if (*(u8 *)(vars + 0x303) == 0) {
            int got = 0;
            int tried = 0;
            if (!close && near && lt && math_random_int_below(g_trooper_fire_chance - 1) == 0 && *(s16 *)(vars + 0x2E6) == 0) {
                tried = 1;
                got = enemy_check_line_of_sight(self, 0, *(u8 *)(vars + 0x30C) != 0, 0);
            }
            if (*(u8 *)(vars + 0x30C) != 0 && got && !close) {
                enemy_set_animation_state_pal(self, 0xB, 0, math_random_int_range(7, 0xC));
                moby_set_state(self, 6, -1);
            } else if (close || got) {
                if (enemy_check_line_of_sight(self, 0, *(u8 *)(vars + 0x30C) != 0, 1) != 0)
                    *(u8 *)(vars + 0x30D) = 1;
                shared_counter_acquire(self);
                enemy_set_animation_state_pal(self, 8, 0, 7);
                moby_set_state(self, 0xA, -1);
            } else if (*(u8 *)(self + 0x60) & 2) {
                enemy_set_animation_state_pal(self, 6, 0, math_random_int_range(7, 0xC));
            }
            if (tried && !got)
                *(u8 *)(vars + 0x30C) = ~*(u8 *)(vars + 0x30C);
        } else {
            if (*(u8 *)(self + 0x60) & 2)
                enemy_set_animation_state_pal(self, 6, 0, math_random_int_range(7, 0xC));
            if (close || (*(s16 *)(vars + 0x2E6) == 0 && near && lt)) {
                enemy_set_animation_state_pal(self, 0xB, 0, math_random_int_range(7, 0xC));
                moby_set_state(self, 6, -1);
            }
        }
        break;
    }
    case 10:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(u8 *)(vars + 0x30D) != 0)
                enemy_set_animation_state_pal(self, 0xA, 0, 0xA);
            else
                enemy_set_animation_state_pal(self, 0x13, 0, 0xC);
            *(u16 *)(vars + 0x2E4) = ((s32)(g_trooper_anim_period) * 5 + 2) / 6;
            moby_set_state(self, 0xB, -1);
        }
        break;
    case 11:
        if (*(u16 *)(self + 0x96) > ((s32)(g_trooper_frame_max) * 5 + 2) / 6)
            trooper_fire_arm_shot_pal(self);
        if ((*(u16 *)(self + 0x96) > ((s32)(g_trooper_frame_min) * 5 + 2) / 6
             && g_trooper_attack_range < vec_distance_xy(self + 0x10, *(char **)(vars + 0x200) + 0x10))
            || *(char **)(vars + 0x2F8) == 0) {
            *(s16 *)(vars + 0x2E6) = ((s32)(math_random_int_range(g_trooper_timer_min, g_trooper_timer_max)) * 5 + 2) / 6;
            shared_counter_release(self);
            enemy_set_animation_state_pal(self, 0xC, 0, math_random_int_range(7, 0xC));
            if (*(int *)(vars + 0x428) != 0)
                moby_set_state(self, 0x10, 5);
            else if (*(int *)(vars + 0x2DC) != -1 && *(int *)(vars + 0x2DC) == *(int *)(vars + 0x2B0))
                moby_set_state(self, 3, 5);
            else
                moby_set_state(self, 8, 5);
        }
        break;
    case 12:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(int *)(vars + 0x2DC) != -1)
                enemy_set_animation_state_pal(self, 0xB, 0, math_random_int_range(7, 0xC));
            else
                enemy_set_animation_state_pal(self, 0, 0, math_random_int_range(7, 0xC));
            moby_set_state(self, 6, 5);
        }
        break;
    case 13:
        if (*(u8 *)(self + 0x60) & 2)
            enemy_set_animation_state_pal(self, (func_001163B0() & 1) ? 0xA : 0x13, 0, math_random_int_range(0x19, 0x2D));
        if (*(u8 *)(self + 0x42) == 0xA || *(u8 *)(self + 0x42) == 0x13)
            trooper_fire_arm_shot_pal(self);
        break;
    case 14:
        shared_counter_release(self);
        break;
    case 15:
        *(float *)(vars + 0x20) = 0.0f;
        part_spawn_damage_debris(self, vars + 0x290, vars + 0x20);
        shared_counter_release(self);
        moby_destroy_linked(self);
        SetDeathBits(self, 0, 3);
        part_spawn_small_burst_pal(self, 0.4f);
        PlayMobySound(3, 0, self);
        moby_mark_spawned(self);
        return;
    }
    trooper_torso_update_attachment_pal(self);
    trooper_attach_arm_parts(self);
    trooper_rearm_spawn_timers_pal(self);
    trooper_copy_owner_value_self_torso(self);
    if (*(int *)(vars + 0x1D8) != -1 && *(u8 *)(self + 0x20) != 0 && *(u8 *)(self + 0x20) < 0xE) {
        transfer_state_to_nearest_eligible_object_pal(self);
        shared_counter_release(self);
        moby_set_state(self, 0xF, 0xA);
    }
}
