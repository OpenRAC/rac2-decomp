#include "names.h"
/* func_PAL_L02_003F639C, the PAL copy of func_00322CC0: the same C at 50 Hz, where frame counts become
 * (x * 5 + 2) / 6 (func_002A7820 results at run time, literals such as animation blends in place), per-frame
 * rates become x * 6 / 5 (and x * 36 / 25 for accelerations), and PAL's own callees take their names.
 */
#include "common.h"

typedef int QuadPAL003F639C __attribute__((mode(TI)));

extern int g_current_game_mode MACRO_ADDR;
extern char g_hero_position[];
extern char *g_active_attacker_robot;
extern u8 g_sound_state[];
extern u32 g_path_table[];
extern char g_str_robot_debug[];

extern int group_enemy_init_update_pal(char *);
extern void moby_mark_spawned(void *);
extern int moby_step_at_own_position_factor_pal(char *object, float factor);
extern int flag_set_second_pending(char *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int math_fast_float_d(void *);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float vec_distance_xy(void *, void *);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern int moby_dispatch_action_by_kind(char *, char *);
extern int PlayMobySound(int, int, char *);
extern void group_destroy_attached_parts(char *, char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void part_spawn_masked_debris_pal(char *, int, float *, float, float, float, float, unsigned char);
extern void SetDeathBits_pal(char *, int, int);
extern int coll_sweep_from_object(char *, char *, int, int, int, int, float, float, float);
extern void part_spawn_explosion_with_sparks_pal(char *, char *, float, float, int);
extern int moby_step_at_own_position_pal(char *);
extern float ApproachValue(void *, float, float);
extern void moby_wander_around_home_point_pal(char *, char *, float, float);
extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);
extern float moby_turn_toward_position(char *, char *, char *, float, float, float);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void snd_stop_voice(s32);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void STUB_printf(const char *, ...);
extern void euler_rotation_basis(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float vec_length_xy(void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float fast_vec_dist(void *, void *);
extern int path_follow_nodes_pal(char *, u32);
extern float FastDiffRots(float, float);
extern int moby_turn_toward_target_and_step_pal(char *, void *, float);
extern int moby_step_controller_pal(char *, void *, float);
extern float moby_get_anim_value(char *);
extern int coll_test_hit_at_bone(void *, int, float, float, int, float, int, int, int);
extern void gfx_add_draw_callback_first(void (*)(char *), char *);
extern void enemy_record_position_trail(char *);
extern void robot_draw_trails(char *);
extern void group_enemy_update_turn_joints_pal(char *);

/* Updates a robot enemy: picks its behaviour state, walks and attacks, and explodes when destroyed
   (PAL: 50 Hz timings). */
void robot_l02_update_pal(char *self)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);

    if (group_enemy_init_update_pal(self) != 0) {
        moby_mark_spawned(self);
        return;
    }

    if (*(u8 *)(self + 0x20) != 0xC && *(u8 *)(self + 0x95) != 2)
        moby_step_at_own_position_factor_pal(self, *(float *)(self + 0xF8));

    if (g_current_game_mode == 2) {
        *(u16 *)(self + 0x34) |= 0x41;
        *(u16 *)(self + 0x34) &= ~0x1000;
        *(int *)(self + 0x98) = 0;
        if (*(char **)(vars + 0x2A0) != 0 && *(char **)(vars + 0x2A4) != 0) {
            *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) |= 0x41;
            *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) &= ~0x1000;
            *(int *)(*(char **)(vars + 0x2A4) + 0x98) = 0;
            *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x41;
            *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) &= ~0x1000;
            *(int *)(*(char **)(vars + 0x2A0) + 0x98) = 0;
        }
        return;
    }

    *(u16 *)(self + 0x34) &= ~0x41;
    *(u16 *)(self + 0x34) |= 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    if (*(char **)(vars + 0x2A0) != 0 && *(char **)(vars + 0x2A4) != 0) {
        *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) &= ~0x41;
        *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) |= 0x1000;
        *(int *)(*(char **)(vars + 0x2A4) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A4) + 0x24) + 0x10);
        *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) &= ~0x41;
        *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x1000;
        *(int *)(*(char **)(vars + 0x2A0) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A0) + 0x24) + 0x10);
    }

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && g_current_game_mode != 2) {
            if (math_fast_float_d(vars + 0x2D0) != 0) {
                moby_set_state(self, 0xB, 4);
                if (*(u8 *)(self + 0x42) == 0) {
                    if (*(u8 *)(self + 0x43) != 1)
                        anim_start_blended_pal(self, 1, 0, 3);
                } else if (*(u8 *)(self + 0x43) != 5) {
                    int variant = math_random_int_below(2);
                    anim_start_blended_pal(self, 5, variant, (math_random_int_range(10, 20) * 5 + 2) / 6);
                }
                if (*(int *)(vars + 0x288) != -1) {
                    moby_set_state(self, 0xA, 1);
                    if (*(u8 *)(self + 0x43) != 0x1A)
                        anim_start_blended_pal(self, 0x1A, 0, 3);
                }
            }
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f) {
            moby_set_state(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    anim_start_blended_pal(self, 1, 0, 3);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int variant = math_random_int_below(2);
                anim_start_blended_pal(self, 5, variant, (math_random_int_range(10, 20) * 5 + 2) / 6);
            }
            *(int *)(vars + 0x294) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0) {
            moby_set_state(self, 9, 3);
            *(s16 *)(vars + 0x276) = 0;
            if (*(s16 *)(vars + 0x270) < 250)
                *(s16 *)(vars + 0x270) = (math_random_int_range(480, 600) * 5 + 2) / 6;
        }
        break;
    case 2: {
        char *hit;
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        *(int *)(self + 0x98) = 0;
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            if (math_fast_float_d(vars + 0x2D0) != 0) {
                moby_set_state(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    anim_start_blended_pal(self, 0x19, 0, 3);
                *(int *)(vars + 0x2E4) = 1;
            }
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            moby_set_state(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                anim_start_blended_pal(self, 0x19, 0, 3);
            *(int *)(vars + 0x2E4) = 1;
        }
        hit = part_find_owned_effect_slot(*(char **)(vars + 0x2E0), 0x10000, 0);
        if (hit != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(hit + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2E0) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xC;
            if (*(int *)(vars + 0x2E4) == 0) {
                moby_set_state(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    anim_start_blended_pal(self, 0x19, 0, 3);
                *(int *)(vars + 0x2E4) = 1;
            }
            if (*(float *)(vars + 0x20) <= 0.0f)
                moby_set_state(self, 0xF, 5);
        }
        qcopy(*(char **)(vars + 0x2E0) + 0x10, self + 0x10);
        break;
    }
    case 3:
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0
            && ((float *)g_hero_position)[2] - *(float *)(self + 0x18) < 3.25f) {
            moby_set_state(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    anim_start_blended_pal(self, 1, 0, 3);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int variant = math_random_int_below(2);
                anim_start_blended_pal(self, 5, variant, (math_random_int_range(10, 20) * 5 + 2) / 6);
            }
        } else if (*(s16 *)(vars + 0x270) == 0) {
            moby_set_state(self, 2, 0);
            if (*(u8 *)(self + 0x43) != 4)
                anim_start_blended_pal(self, 4, 0, 0x8);
        }
        break;
    case 4:
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if ((*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1)
            || *(float *)(vars + 0x238) - *(float *)(self + 0x18) >= 3.25f) {
            if (*(u8 *)(self + 0x20) != 5) if (*(u8 *)(self + 0x20) != 4) {
                moby_set_state(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7) {
                    int variant = math_random_int_below(2);
                    anim_start_blended_pal(self, 7, variant, (math_random_int_range(10, 20) * 5 + 2) / 6);
                }
                *(s16 *)(vars + 0x270) = (math_random_int_range(580, 600) * 5 + 2) / 6;
            }
        }
        break;
    case 5: {
        int flags = moby_dispatch_action_by_kind(self, vars + 0x60);
        if ((flags & 1) || (*(float *)(vars + 0x20) <= 0.0f && *(int *)(vars + 0x2EC) == 0)) {
            char *child;
            PlayMobySound(0xD, 0, self);
            group_destroy_attached_parts(self, vars + 0x2A0);
            child = *(char **)(vars + 0x2E0);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7)
                moby_mark_spawned(child);
            *(QuadPAL003F639C *)v = 0;
            v[2] = 0.75f;
            matrix_mul_vec3(v, v, self + 0xC0);
            FastVecAdd(v, v, self + 0x10);
            SpawnExplosion_pal(v, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);




            vec_scale_to_length(w, vars + 0xE0, 0.060000002f);
            part_spawn_masked_debris_pal(self, 0x3F8, w, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);

            SetDeathBits_pal(self, 0, 3);
            moby_mark_spawned(self);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                moby_set_state(self, 0xC, 4);
                if (*(u8 *)(self + 0x43) != 0xB)
                    anim_start_blended_pal(self, 0xB, 0, 0x8);
            } else {
                moby_set_state(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7)
                    anim_start_blended_pal(self, 7, 0, 0x8);
                *(s16 *)(vars + 0x270) = (math_random_int_range(580, 600) * 5 + 2) / 6;
            }
            if (*(int *)(vars + 0x294) != 1)
                *(int *)(vars + 0x294) = 1;
        }
        if (*(int *)(vars + 0x2EC) != 0)
            coll_sweep_from_object(self, self + 0x10, 0x10000, 0, 1, 0, 0.9f, 0.1f, 1.0f);
        break;
    }
    case 6:
        moby_dispatch_action_by_kind(self, vars + 0x60);
        if ((*(u8 *)(self + 0x60) & 2) || *(float *)(self + 0x18) < 100.0f) {
            group_destroy_attached_parts(self, vars + 0x2A0);
            part_spawn_explosion_with_sparks_pal(self, self + 0x10, 0.5f, 13.0f, -1);
            SetDeathBits_pal(self, 0, 3);
            moby_mark_spawned(self);
            return;
        }
        v[0] = 0.0f;
        v[1] = -0.4f;
        v[2] = 0.0f;
        FastVecAdd(self + 0x10, self + 0x10, v);
        break;
    }

    switch (*(u8 *)(self + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2F0) != 0)
            moby_step_at_own_position_pal(self);
        break;
    case 2: {
        int anim;
        math_fast_float_d(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 8 && anim != 2 && anim != 4 && anim != 8)
            anim_start_blended_pal(self, 8, 0, 0xC);
        if (*(int *)(vars + 0x2D8) > 17)
            ApproachValue(vars + 0x214, 0.060000002f, 0.0012f);
        else
            ApproachValue(vars + 0x214, 0.0f, 0.0012f);
        anim = *(u8 *)(self + 0x43);
        if (anim == 8) {
            if (*(int *)(vars + 0x2D8) == 0) {
                anim_start_blended_pal(self, 4, 0, 0xA);
                if (math_random_int_below(3) == 1 && *(u8 *)(self + 0x43) != 2)
                    anim_start_blended_pal(self, 2, 0, 0xA);
            }
            moby_wander_around_home_point_pal(self, vars + 0x200, 0.35f, 0.25f);
        } else if (anim == 2 || anim == 4) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = math_random_int_range(100, 583);
                if (*(u8 *)(self + 0x43) != 8)
                    anim_start_blended_pal(self, 8, 0, 0xA);
            }
        }
        break;
    }
    case 3:
        moby_scale_owner_words_by_angles(self, vars + 0x298, vars + 0x29C, 0.06981318f, 0.062831864f, 0.015707966f);
        break;
    case 5: {
        u8 *slot = g_sound_state + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float y;
        if (*(char **)(slot + 0x88) != self || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = PlayMobySound(0xB, 4, self);
        *(int *)(vars + 0x2BC) += 1;
        moby_turn_toward_position(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        math_spring_float_to_goal(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        math_spring_float_to_goal(self + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
        y = *(float *)(self + 0x18);
        if (y - height > 0.05f) {
            *(float *)(self + 0x18) = y - height * 0.00025f;
        } else {
            int index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *other = g_sound_state + index * 0x70;
                if (*(char **)(other + 0x88) == self && other[0x74] != 0)
                    snd_stop_voice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            moby_set_state(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xF)
                anim_start_blended_pal(self, 0xF, 0, 2);
        }
        if (*(u8 *)(self + 0x60) & 2) {
            moby_set_state(self, 4, -1);
            if (*(u8 *)(self + 0x43) != 0x1A)
                anim_start_blended_pal(self, 0x1A, 0, 0xC);
        }
        break;
    }
    case 4: {
        float height;
        float above;
        *(int *)(vars + 0x2BC) += 1;
        moby_turn_toward_position(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        math_spring_float_to_goal(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        math_spring_float_to_goal(self + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            math_step_value_toward_target(self + 0x18, vars + 0x280, height, 0.020000001f, 0.19600002f, 0.20000002f);
        } else {
            int index = *(int *)(vars + 0x2C0);
            char *child;
            if (index != -1) {
                u8 *slot = g_sound_state + index * 0x70;
                if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                    snd_stop_voice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            STUB_printf(g_str_robot_debug, *(int *)(vars + 0x2BC));
            moby_set_state(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xF)
                anim_start_blended_pal(self, 0xF, 0, 2);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            child = *(char **)(vars + 0x2E0);
            if (*(s16 *)(child + 0xAA) == 0xAB7)
                moby_mark_spawned(child);
            *(float *)(vars + 0x30) = 0.5f;
            *(u16 *)(self + 0x34) |= 0x1000;
        }
        break;
    }
    case 6:
        if (*(u8 *)(self + 0x60) & 2) {
            moby_set_state(self, 7, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                anim_start_blended_pal(self, 0xE, 0, 0xC);
        }
        break;
    case 7: {
        float height;
        float above;
        math_spring_float_to_goal(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        moby_turn_toward_position(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        height = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            math_step_value_toward_target(self + 0x18, vars + 0x280, height, 0.030000001f, 0.19600002f, 0.3f);
        } else {
            moby_set_state(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xF)
                anim_start_blended_pal(self, 0xF, 0, 2);
        }
        break;
    }
    case 8:
        if (*(u8 *)(self + 0x60) & 2) {
            moby_set_state(self, 0xC, 4);
            if (*(u8 *)(self + 0x43) != 8)
                anim_start_blended_pal(self, 8, 0, 0xC);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            *(float *)(self + 0x18) = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
        }
        break;
    case 9: {
        u8 anim;
        math_fast_float_d(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 0xB && anim != 6 && anim != 7 && anim != 0xB)
            anim_start_blended_pal(self, 0xB, 0, 0xC);
        if (*(int *)(vars + 0x2D8) > 17)
            ApproachValue(vars + 0x214, 0.120000005f, 0.0024f);
        else
            ApproachValue(vars + 0x214, 0.0f, 0.0024f);
        if (*(u8 *)(self + 0x43) == 0xB) {
            if (*(int *)(vars + 0x2D8) == 0) {
                anim_start_blended_pal(self, 6, 0, 0xA);
                if (math_random_int_below(3) == 1 && *(u8 *)(self + 0x43) != 7)
                    anim_start_blended_pal(self, 7, 0, 0xA);
            }
            moby_wander_around_home_point_pal(self, vars + 0x200, 0.35f, 0.25f);
        } else if (*(u8 *)(self + 0x43) == 6 || *(u8 *)(self + 0x43) == 7) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = math_random_int_range(100, 167);
                if (*(u8 *)(self + 0x43) != 0xB)
                    anim_start_blended_pal(self, 0xB, 0, 0xA);
            }
        }
        break;
    }
    case 10:
        qcopy(v, vars + 0x300);
        v[2] -= 3.0f;
        FastVecSub(w, v, self + 0x10);
        *(float *)(self + 0xF8) = mat_fast_helper_a(w[0], w[1]);
        *(float *)(self + 0xF4) = mat_fast_helper_a(vec_length_xy(w), w[2]);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        vec_spring_to_target(self + 0x10, v, vars + 0x280, 0.020000001f, 0.0f, 0.40000004f);
        if (fast_vec_dist(self + 0x10, v) < 0.4f) {
            if (*(u8 *)(self + 0x43) != 0xE)
                anim_start_blended_pal(self, 0xE, 0, 0x8);
            moby_set_state(self, 7, -1);
        }
        break;
    case 11:
        moby_step_at_own_position_pal(self);
        if (*(u8 *)(self + 0x60) & 2) {
            moby_set_controller_speed_limits(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            moby_set_state(self, 0xC, -1);
            if (*(u8 *)(self + 0x43) != 0xB)
                anim_start_blended_pal(self, 0xB, 0, 0xC);
        }
        break;
    case 12:
        if (*(int *)(vars + 0x2F8) != -1) {
            if (path_follow_nodes_pal(self, g_path_table[*(int *)(vars + 0x2F8)]) != 0
                || vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f)
                *(int *)(vars + 0x2F8) = -1;
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
                   && FastDiffRots(*(float *)(self + 0xF8),
                                    mat_fast_helper_a(*(float *)(vars + 0x230) - *(float *)(self + 0x10),
                                                  *(float *)(vars + 0x234) - *(float *)(self + 0x14))) < 0.20943953f) {
            moby_set_state(self, 0xD, -1);
            if (*(u8 *)(self + 0x43) != 0x1B)
                anim_start_blended_pal(self, 0x1B, 0, 5);
            if (math_random_int_below(2) == 1) {
                if (*(u8 *)(self + 0x43) != 0x10)
                    anim_start_blended_pal(self, 0x10, 0, 5);
            }
            *(int *)(vars + 0x2B0) = 0;
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            moby_turn_toward_target_and_step_pal(self, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            moby_step_controller_pal(self, self + 0x10,
                          mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        }
        if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 5.0f && *(u8 *)(self + 0x42) == 8) {
            if (*(u8 *)(self + 0x43) != 0xB)
                anim_start_blended_pal(self, 0xB, 0, 3);
            moby_set_controller_speed_limits(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        }
        break;
    case 13: {
        float frame;
        if (*(u8 *)(self + 0x60) & 2) {
            *(float *)(vars + 0x2E8) = 8.0f;
            if (g_active_attacker_robot == self) {
                moby_set_state(self, 0xE, -1);
                if (*(u8 *)(self + 0x43) != 0x11)
                    anim_start_blended_pal(self, 0x11, 0, 6);
            } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                moby_set_controller_speed_limits(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                moby_set_state(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    anim_start_blended_pal(self, 0xB, 0, 0x8);
            } else {
                moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                moby_set_state(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    anim_start_blended_pal(self, 8, 0, 0x8);
            }
        }
        moby_step_at_own_position_pal(self);
        frame = moby_get_anim_value(self);
        if (*(u8 *)(self + 0x42) == 0x1B || *(u8 *)(self + 0x42) == 0x10) {
            if (frame >= 19.0f && frame <= 25.0f) {
                coll_test_hit_at_bone(self, 0, 0.35f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                coll_test_hit_at_bone(self, 1, 0.15f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                coll_test_hit_at_bone(self, 2, 0.15f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                coll_test_hit_at_bone(self, 9, 0.35f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
            }
        }
        if ((*(u8 *)(self + 0x42) == 0x1B || *(u8 *)(self + 0x42) == 0x10) && frame >= 17.0f && frame <= 25.0f) {
            gfx_add_draw_callback_first(robot_draw_trails, self);
            enemy_record_position_trail(self);
            *(float *)(vars + 0x2E8) = 25.0f;
        }
        break;
    }
    case 14: {
        float frame;
        if (*(u8 *)(self + 0x60) & 2) {
            if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                moby_set_controller_speed_limits(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                moby_set_state(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    anim_start_blended_pal(self, 0xB, 0, 0x8);
            } else {
                moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                moby_set_state(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    anim_start_blended_pal(self, 8, 0, 0x8);
            }
        }
        moby_step_at_own_position_pal(self);
        frame = moby_get_anim_value(self);
        if (*(u8 *)(self + 0x42) == 0x11 && (frame <= 5.0f || (frame >= 12.0f && frame <= 15.0f)))
            *(int *)(vars + 0x2C4) = 1;
        else
            *(int *)(vars + 0x2C4) = 0;
        break;
    }
    }
    group_enemy_update_turn_joints_pal(self);
}
