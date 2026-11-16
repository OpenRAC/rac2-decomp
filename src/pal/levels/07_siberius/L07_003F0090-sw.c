#include "names.h"
/* func_PAL_L07_003F0090, the PAL copy of func_L00_003D54B0: the same C, with rates per frame scaled by 6/5 (per frame
 * squared by 36/25), tick counts rescaled, and func_002A7820's timers through the 50 Hz scale.
 */
#include "common.h"

typedef int Quad003F0090 __attribute__((mode(TI)));

extern int g_game_l00_mode MACRO_ADDR;
extern u8 g_sound_state[];
extern char g_default_vector[] __attribute__((sda));
extern char g_str_flying_enemy_debug[];

extern int robot_init_check_health_pal(char *);
extern void moby_mark_spawned(void *);
extern int flag_set_second_pending(char *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern float math_fabs(float);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern int math_random_int_range(int, int);
extern float vec_distance_xy(void *, void *);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern int moby_dispatch_action_by_kind(char *, char *);
extern int PlayMobySound(int, int, char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void robot_spawn_death_debris_pal(void *);
extern void SetDeathBits_pal(char *, int, int);
extern int moby_step_at_own_position_pal(char *);
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
extern float FastDiffRots(float, float);
extern int moby_turn_toward_target_and_step_pal(char *, void *, float);
extern int moby_step_controller_pal(char *, void *, float);
extern void part_spawn_joint_hit_effects_pal(float, char *, void *, int);
extern void gfx_add_draw_callback_third(void (*)(char *), char *);
extern void robot_draw_joint_flash(char *);
extern void robot_update_timers_limbs_pal(char *);
extern void robot_draw_glow_effects(char *);

/* Per-frame update of a flying enemy (PAL: 50 Hz timings). It idles, hovers and chases the player, takes hits, and crashes and explodes when its health runs out. */
void flying_l07_l00_enemy_update_pal(char *moby)
{
    float point[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);

    if (robot_init_check_health_pal(moby) != 0) {
        moby_mark_spawned(moby);
        return;
    }

    if (g_game_l00_mode == 2) {
        *(u16 *)(moby + 0x34) |= 0x41;
        *(u16 *)(moby + 0x34) &= ~0x1000;
        *(int *)(moby + 0x98) = 0;
        return;
    }

    *(u16 *)(moby + 0x34) &= ~0x41;
    *(u16 *)(moby + 0x34) |= 0x1000;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);

    switch (*(u8 *)(moby + 0x95)) {
    case 0:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0
            && math_fabs(*(float *)(moby + 0x18) - *(float *)(vars + 0x238)) < 2.0f && g_game_l00_mode != 2) {
            moby_set_state(moby, 0xB, 4);
            if (*(u8 *)(moby + 0x43) != 1)
                anim_start_blended_pal(moby, 1, 0, 3);
            if (*(int *)(vars + 0x288) != -1) {
                moby_set_state(moby, 0xA, 1);
                if (*(u8 *)(moby + 0x43) != 0x1A)
                    anim_start_blended_pal(moby, 0x1A, 0, 3);
            }
        } else if (*(s16 *)(vars + 0x276) != 0) {
            moby_set_state(moby, 9, 3);
            *(s16 *)(vars + 0x276) = 0;
            if (*(s16 *)(vars + 0x270) < 250)
                *(s16 *)(vars + 0x270) = ((s32)(math_random_int_range(480, 600)) * 5 + 2) / 6;
        }
        break;
    case 2: {
        char *effect_slot;
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            moby_set_state(moby, 5, -1);
            if (*(u8 *)(moby + 0x43) != 0x19)
                anim_start_blended_pal(moby, 0x19, 0, 3);
            *(int *)(vars + 0x2B0) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            moby_set_state(moby, 5, -1);
            if (*(u8 *)(moby + 0x43) != 0x19)
                anim_start_blended_pal(moby, 0x19, 0, 3);
            *(int *)(vars + 0x2B0) = 1;
        }
        effect_slot = part_find_owned_effect_slot(*(char **)(vars + 0x2AC), 0x10000, 0);
        if (effect_slot != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(effect_slot + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2AC) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xC;
            if (*(int *)(vars + 0x2B0) == 0) {
                moby_set_state(moby, 5, -1);
                if (*(u8 *)(moby + 0x43) != 0x19)
                    anim_start_blended_pal(moby, 0x19, 0, 3);
                *(int *)(vars + 0x2B0) = 1;
            }
            if (*(float *)(vars + 0x20) <= 0.0f)
                moby_set_state(moby, 0xF, 5);
        }
        qcopy(*(char **)(vars + 0x2AC) + 0x10, moby + 0x10);
        break;
    }
    case 3:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0) {
            moby_set_state(moby, 0xB, 4);
            if (*(u8 *)(moby + 0x43) != 1)
                anim_start_blended_pal(moby, 1, 0, 3);
        } else if (*(s16 *)(vars + 0x270) == 0) {
            moby_set_state(moby, 2, 0);
            if (*(u8 *)(moby + 0x43) != 3)
                anim_start_blended_pal(moby, 3, 0, 8);
        }
        break;
    case 4:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1) {
            if (*(u8 *)(moby + 0x20) != 5) if (*(u8 *)(moby + 0x20) != 4) {
                moby_set_state(moby, 9, 3);
                if (*(u8 *)(moby + 0x43) != 6)
                    anim_start_blended_pal(moby, 6, 0, 8);
                *(s16 *)(vars + 0x270) = ((s32)(math_random_int_range(580, 600)) * 5 + 2) / 6;
            }
        }
        break;
    case 5: {
        int flags = moby_dispatch_action_by_kind(moby, vars + 0x60);
        int index = *(int *)(vars + 0x2C0);
        if (index != -1) {
            u8 *slot = g_sound_state + index * 0x70;
            if (*(char **)(slot + 0x88) == moby && slot[0x74] != 0)
                snd_stop_voice(index);
        }
        *(int *)(vars + 0x2C0) = -1;
        if ((flags & 1) || *(float *)(vars + 0x20) <= 0.0f) {
            char *child;
            PlayMobySound(0xC, 0, moby);
            child = *(char **)(vars + 0x2AC);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7)
                moby_mark_spawned(child);
            *(Quad003F0090 *)point = 0;
            point[2] = 0.75f;
            *(u16 *)(moby + 0x34) |= 0x41;
            *(u16 *)(moby + 0x34) &= ~0x1000;
            *(int *)(moby + 0x98) = 0;
            matrix_mul_vec3(point, point, moby + 0xC0);
            FastVecAdd(point, point, moby + 0x10);
            SpawnExplosion_pal(point, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);
            robot_spawn_death_debris_pal(moby);
            SetDeathBits_pal(moby, 0, 3);
            moby_mark_spawned(moby);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                moby_set_state(moby, 0xC, 4);
                if (*(u8 *)(moby + 0x43) != 0x1C)
                    anim_start_blended_pal(moby, 0x1C, 0, 8);
            } else {
                moby_set_state(moby, 9, 3);
                if (*(u8 *)(moby + 0x43) != 6)
                    anim_start_blended_pal(moby, 6, 0, 8);
                *(s16 *)(vars + 0x270) = ((s32)(math_random_int_range(580, 600)) * 5 + 2) / 6;
            }
        }
        break;
    }
    }

    switch (*(u8 *)(moby + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2BC) == 0)
            moby_step_at_own_position_pal(moby);
        break;
    case 3:
        moby_scale_owner_words_by_angles(moby, vars + 0x2A4, vars + 0x2A8, 0.06981318f, 0.062831864f, 0.015707966f);
        break;
    case 5: {
        u8 *slot = g_sound_state + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float moby_y;
        *(int *)(vars + 0x2A0) += 1;
        if (*(char **)(slot + 0x88) != moby || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = PlayMobySound(0xD, 4, moby);
        moby_turn_toward_position(moby, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        math_spring_float_to_goal(moby + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        math_spring_float_to_goal(moby + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        moby_y = *(float *)(moby + 0x18);
        if (moby_y - height > 0.05f) {
            *(float *)(moby + 0x18) = moby_y - height * 0.00025f;
        } else {
            int index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *other = g_sound_state + index * 0x70;
                if (*(char **)(other + 0x88) == moby && other[0x74] != 0)
                    snd_stop_voice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            moby_set_state(moby, 8, -1);
            if (*(u8 *)(moby + 0x43) != 0xE)
                anim_start_blended_pal(moby, 0xE, 0, 2);
        }
        if (*(u8 *)(moby + 0x60) & 2) {
            moby_set_state(moby, 4, -1);
            if (*(u8 *)(moby + 0x43) != 0x1A)
                anim_start_blended_pal(moby, 0x1A, 0, 0xC);
        }
        break;
    }
    case 4: {
        float height;
        float above;
        *(int *)(vars + 0x2A0) += 1;
        moby_turn_toward_position(moby, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        math_spring_float_to_goal(moby + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        math_spring_float_to_goal(moby + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        above = *(float *)(moby + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            math_step_value_toward_target(moby + 0x18, vars + 0x280, height, 0.020000001f, 0.19600002f, 0.20000002f);
        } else {
            int index;
            char *child;
            STUB_printf(g_str_flying_enemy_debug, *(int *)(vars + 0x2A0));
            index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *slot = g_sound_state + index * 0x70;
                if (*(char **)(slot + 0x88) == moby && slot[0x74] != 0)
                    snd_stop_voice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            moby_set_state(moby, 8, -1);
            if (*(u8 *)(moby + 0x43) != 0xE)
                anim_start_blended_pal(moby, 0xE, 0, 2);
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            child = *(char **)(vars + 0x2AC);
            if (*(s16 *)(child + 0xAA) == 0xAB7)
                moby_mark_spawned(child);
            *(float *)(vars + 0x30) = 0.5f;
            *(u16 *)(moby + 0x34) |= 0x1000;
        }
        break;
    }
    case 6:
        if (*(u8 *)(moby + 0x60) & 2) {
            moby_set_state(moby, 7, -1);
            if (*(u8 *)(moby + 0x43) != 0xD)
                anim_start_blended_pal(moby, 0xD, 0, 0xC);
        }
        break;
    case 7: {
        float height;
        float above;
        math_spring_float_to_goal(moby + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        moby_turn_toward_position(moby, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        height = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        above = *(float *)(moby + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            math_step_value_toward_target(moby + 0x18, vars + 0x280, height, 0.030000001f, 0.19600002f, 0.3f);
        } else {
            moby_set_state(moby, 8, -1);
            if (*(u8 *)(moby + 0x43) != 0xE)
                anim_start_blended_pal(moby, 0xE, 0, 2);
        }
        break;
    }
    case 8:
        if (*(u8 *)(moby + 0x60) & 2) {
            moby_set_state(moby, 0xC, 4);
            if (*(u8 *)(moby + 0x43) != 0x1C)
                anim_start_blended_pal(moby, 0x1C, 0, 0xC);
            *(float *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        }
        break;
    case 10:
        qcopy(point, vars + 0x380);
        point[2] -= 3.0f;
        FastVecSub(delta, point, moby + 0x10);
        *(float *)(moby + 0xF8) = mat_fast_helper_a(delta[0], delta[1]);
        *(float *)(moby + 0xF4) = mat_fast_helper_a(vec_length_xy(delta), delta[2]);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        vec_spring_to_target(moby + 0x10, point, vars + 0x280, 0.020000001f, 0.0f, 0.40000004f);
        if (fast_vec_dist(moby + 0x10, point) < 0.4f) {
            if (*(u8 *)(moby + 0x43) != 0xD)
                anim_start_blended_pal(moby, 0xD, 0, 8);
            moby_set_state(moby, 7, -1);
        }
        break;
    case 11:
        moby_step_at_own_position_pal(moby);
        if (*(u8 *)(moby + 0x60) & 2) {
            moby_set_controller_speed_limits(moby, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
            moby_set_state(moby, 0xC, -1);
            if (*(u8 *)(moby + 0x43) != 0x1C)
                anim_start_blended_pal(moby, 0x1C, 0, 0xC);
        }
        break;
    case 12:
        moby_set_controller_speed_limits(moby, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
        if (vec_distance_xy(moby + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
            && FastDiffRots(*(float *)(moby + 0xF8),
                             mat_fast_helper_a(*(float *)(vars + 0x230) - *(float *)(moby + 0x10),
                                           *(float *)(vars + 0x234) - *(float *)(moby + 0x14))) < 0.38397247f) {
        } else if (vec_distance_xy(moby + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            moby_turn_toward_target_and_step_pal(moby, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            moby_step_controller_pal(moby, moby + 0x10,
                          mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(moby + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(moby + 0x14)));
        }
        if (*(u8 *)(moby + 0x42) == 0x1C)
            part_spawn_joint_hit_effects_pal(*(float *)(vars + 0x298), moby, g_default_vector, 4);
        break;
    case 13: {
        char *target;
        if (*(u8 *)(moby + 0x42) == 0xF)
            gfx_add_draw_callback_third(robot_draw_joint_flash, moby);
        target = *(char **)(vars + 0x240);
        moby_step_controller_pal(moby, moby + 0x10,
                      mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(moby + 0x10),
                                    *(float *)(target + 0x14) - *(float *)(moby + 0x14)));
        break;
    }
    case 14:
        if (*(u8 *)(moby + 0x60) & 2) {
            if (vec_distance_xy(moby + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                moby_set_controller_speed_limits(moby, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
                moby_set_state(moby, 0xC, -1);
                if (*(u8 *)(moby + 0x43) != 0x1C)
                    anim_start_blended_pal(moby, 0x1C, 0, 8);
            } else {
                moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                moby_set_state(moby, 0xC, -1);
                if (*(u8 *)(moby + 0x43) != 7)
                    anim_start_blended_pal(moby, 7, 0, 8);
            }
        }
        break;
    }
    robot_update_timers_limbs_pal(moby);
    gfx_add_draw_callback_third(robot_draw_glow_effects, moby);
}
