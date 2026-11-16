#include "names.h"
/* func_PAL_L00_003D9580, the PAL copy of func_L00_003D54B0 (4,496 bytes): the same C, with the 50 Hz values.
 * Timers and blend counts scale by 5/6 (4 to 3, 10 to 8, 15 to 12, and func_002A7820's result written out),
 * and speeds by 6/5. The equal blend counts are why more arm tails cross-jump here than in the USA body.
 */
#include "common.h"

typedef int Quad003D54B0 __attribute__((mode(TI)));

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
extern void gfx_register_overlay_draw_callback(void (*)(char *), char *);
extern void robot_draw_joint_flash(char *);
extern void robot_update_timers_limbs_pal(char *);
extern void robot_draw_glow_effects(char *);

/* Per-frame update of a flying enemy. It idles, hovers and chases the player, takes hits, and crashes and explodes when its health runs out (PAL: 50 Hz timings). */
void flying_l00_l00_enemy_update_pal(char *self)
{
    float point[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);

    if (robot_init_check_health_pal(self) != 0) {
        moby_mark_spawned(self);
        return;
    }

    if (g_game_l00_mode == 2) {
        *(u16 *)(self + 0x34) |= 0x41;
        *(u16 *)(self + 0x34) &= ~0x1000;
        *(int *)(self + 0x98) = 0;
        return;
    }

    *(u16 *)(self + 0x34) &= ~0x41;
    *(u16 *)(self + 0x34) |= 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0
            && math_fabs(*(float *)(self + 0x18) - *(float *)(vars + 0x238)) < 2.0f && g_game_l00_mode != 2) {
            moby_set_state(self, 0xB, 4);
            if (*(u8 *)(self + 0x43) != 1)
                anim_start_blended_pal(self, 1, 0, 3);
            if (*(int *)(vars + 0x288) != -1) {
                moby_set_state(self, 0xA, 1);
                if (*(u8 *)(self + 0x43) != 0x1A)
                    anim_start_blended_pal(self, 0x1A, 0, 3);
            }
        } else if (*(s16 *)(vars + 0x276) != 0) {
            moby_set_state(self, 9, 3);
            *(s16 *)(vars + 0x276) = 0;
            if (*(s16 *)(vars + 0x270) < 250)
                *(s16 *)(vars + 0x270) = (((int)(math_random_int_range(480, 600)) * 5 + 2) / 6);
        }
        break;
    case 2: {
        char *hit;
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            moby_set_state(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                anim_start_blended_pal(self, 0x19, 0, 3);
            *(int *)(vars + 0x2B0) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            moby_set_state(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                anim_start_blended_pal(self, 0x19, 0, 3);
            *(int *)(vars + 0x2B0) = 1;
        }
        hit = part_find_owned_effect_slot(*(char **)(vars + 0x2AC), 0x10000, 0);
        if (hit != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(hit + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2AC) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xc;
            if (*(int *)(vars + 0x2B0) == 0) {
                moby_set_state(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    anim_start_blended_pal(self, 0x19, 0, 3);
                *(int *)(vars + 0x2B0) = 1;
            }
            if (*(float *)(vars + 0x20) <= 0.0f)
                moby_set_state(self, 0xF, 5);
        }
        qcopy(*(char **)(vars + 0x2AC) + 0x10, self + 0x10);
        break;
    }
    case 3:
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0) {
            moby_set_state(self, 0xB, 4);
            if (*(u8 *)(self + 0x43) != 1)
                anim_start_blended_pal(self, 1, 0, 3);
        } else if (*(s16 *)(vars + 0x270) == 0) {
            moby_set_state(self, 2, 0);
            if (*(u8 *)(self + 0x43) != 3)
                anim_start_blended_pal(self, 3, 0, 0x8);
        }
        break;
    case 4:
        if (flag_set_second_pending(self) != 0)
            moby_set_controller_speed_limits(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1) {
            if (*(u8 *)(self + 0x20) != 5) if (*(u8 *)(self + 0x20) != 4) {
                moby_set_state(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 6)
                    anim_start_blended_pal(self, 6, 0, 0x8);
                *(s16 *)(vars + 0x270) = (((int)(math_random_int_range(580, 600)) * 5 + 2) / 6);
            }
        }
        break;
    case 5: {
        int flags = moby_dispatch_action_by_kind(self, vars + 0x60);
        int index = *(int *)(vars + 0x2C0);
        if (index != -1) {
            u8 *slot = g_sound_state + index * 0x70;
            if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                snd_stop_voice(index);
        }
        *(int *)(vars + 0x2C0) = -1;
        if ((flags & 1) || *(float *)(vars + 0x20) <= 0.0f) {
            char *child;
            PlayMobySound(0xC, 0, self);
            child = *(char **)(vars + 0x2AC);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7)
                moby_mark_spawned(child);
            *(Quad003D54B0 *)point = 0;
            point[2] = 0.75f;
            *(u16 *)(self + 0x34) |= 0x41;
            *(u16 *)(self + 0x34) &= ~0x1000;
            *(int *)(self + 0x98) = 0;
            matrix_mul_vec3(point, point, self + 0xC0);
            FastVecAdd(point, point, self + 0x10);
            SpawnExplosion_pal(point, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);
            robot_spawn_death_debris_pal(self);
            SetDeathBits_pal(self, 0, 3);
            moby_mark_spawned(self);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                moby_set_state(self, 0xC, 4);
                if (*(u8 *)(self + 0x43) != 0x1C)
                    anim_start_blended_pal(self, 0x1C, 0, 0x8);
            } else {
                moby_set_state(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 6)
                    anim_start_blended_pal(self, 6, 0, 0x8);
                *(s16 *)(vars + 0x270) = (((int)(math_random_int_range(580, 600)) * 5 + 2) / 6);
            }
        }
        break;
    }
    }

    switch (*(u8 *)(self + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2BC) == 0)
            moby_step_at_own_position_pal(self);
        break;
    case 3:
        moby_scale_owner_words_by_angles(self, vars + 0x2A4, vars + 0x2A8, 0.06981318f, 0.062831864f, 0.015707966f);
        break;
    case 5: {
        u8 *slot = g_sound_state + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float y;
        *(int *)(vars + 0x2A0) += 1;
        if (*(char **)(slot + 0x88) != self || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = PlayMobySound(0xD, 4, self);
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
            if (*(u8 *)(self + 0x43) != 0xE)
                anim_start_blended_pal(self, 0xE, 0, 2);
        }
        if (*(u8 *)(self + 0x60) & 2) {
            moby_set_state(self, 4, -1);
            if (*(u8 *)(self + 0x43) != 0x1A)
                anim_start_blended_pal(self, 0x1A, 0, 0xc);
        }
        break;
    }
    case 4: {
        float height;
        float above;
        *(int *)(vars + 0x2A0) += 1;
        moby_turn_toward_position(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        math_spring_float_to_goal(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        math_spring_float_to_goal(self + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            math_step_value_toward_target(self + 0x18, vars + 0x280, height, 0.020000001f, 0.19600002f, 0.20000002f);
        } else {
            int index;
            char *child;
            STUB_printf(g_str_flying_enemy_debug, *(int *)(vars + 0x2A0));
            index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *slot = g_sound_state + index * 0x70;
                if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                    snd_stop_voice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            moby_set_state(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                anim_start_blended_pal(self, 0xE, 0, 2);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            child = *(char **)(vars + 0x2AC);
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
            if (*(u8 *)(self + 0x43) != 0xD)
                anim_start_blended_pal(self, 0xD, 0, 0xc);
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
            if (*(u8 *)(self + 0x43) != 0xE)
                anim_start_blended_pal(self, 0xE, 0, 2);
        }
        break;
    }
    case 8:
        if (*(u8 *)(self + 0x60) & 2) {
            moby_set_state(self, 0xC, 4);
            if (*(u8 *)(self + 0x43) != 0x1C)
                anim_start_blended_pal(self, 0x1C, 0, 0xc);
            *(float *)(self + 0x18) = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
        }
        break;
    case 10:
        qcopy(point, vars + 0x380);
        point[2] -= 3.0f;
        FastVecSub(delta, point, self + 0x10);
        *(float *)(self + 0xF8) = mat_fast_helper_a(delta[0], delta[1]);
        *(float *)(self + 0xF4) = mat_fast_helper_a(vec_length_xy(delta), delta[2]);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        vec_spring_to_target(self + 0x10, point, vars + 0x280, 0.020000001f, 0.0f, 0.40000004f);
        if (fast_vec_dist(self + 0x10, point) < 0.4f) {
            if (*(u8 *)(self + 0x43) != 0xD)
                anim_start_blended_pal(self, 0xD, 0, 0x8);
            moby_set_state(self, 7, -1);
        }
        break;
    case 11:
        moby_step_at_own_position_pal(self);
        if (*(u8 *)(self + 0x60) & 2) {
            moby_set_controller_speed_limits(self, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
            moby_set_state(self, 0xC, -1);
            if (*(u8 *)(self + 0x43) != 0x1C)
                anim_start_blended_pal(self, 0x1C, 0, 0xc);
        }
        break;
    case 12:
        moby_set_controller_speed_limits(self, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
        if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
            && FastDiffRots(*(float *)(self + 0xF8),
                             mat_fast_helper_a(*(float *)(vars + 0x230) - *(float *)(self + 0x10),
                                           *(float *)(vars + 0x234) - *(float *)(self + 0x14))) < 0.38397247f) {
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            moby_turn_toward_target_and_step_pal(self, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            moby_step_controller_pal(self, self + 0x10,
                          mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        }
        if (*(u8 *)(self + 0x42) == 0x1C)
            part_spawn_joint_hit_effects_pal(*(float *)(vars + 0x298), self, g_default_vector, 4);
        break;
    case 13: {
        char *target;
        if (*(u8 *)(self + 0x42) == 0xF)
            gfx_register_overlay_draw_callback(robot_draw_joint_flash, self);
        target = *(char **)(vars + 0x240);
        moby_step_controller_pal(self, self + 0x10,
                      mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                    *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        break;
    }
    case 14:
        if (*(u8 *)(self + 0x60) & 2) {
            if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                moby_set_controller_speed_limits(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
                moby_set_state(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0x1C)
                    anim_start_blended_pal(self, 0x1C, 0, 0x8);
            } else {
                moby_set_controller_speed_limits(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                moby_set_state(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 7)
                    anim_start_blended_pal(self, 7, 0, 0x8);
            }
        }
        break;
    }
    robot_update_timers_limbs_pal(self);
    gfx_register_overlay_draw_callback(robot_draw_glow_effects, self);
}
