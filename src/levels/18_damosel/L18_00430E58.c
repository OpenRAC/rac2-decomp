#include "names.h"
/* func_L18_00430E58: own unit for -frac2-keep-block-order (the class-switch default stays last)
 * and -frac2-hazard-labels (case 9 branches to the hazard nop of a shared c.lt.s).
 * D_L18_001B290C is a MACRO_ADDR scalar (tied lui/lw); arms that end in a call repeat the
 * following store so the tails cross-jump as in retail. */
#include "common.h"

extern u8 *g_waypoint_table MACRO_ADDR;

extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern void FastVecAdd(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void SetDeathBits(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int coll_test_hit_at_bone(void *, float, float, int, int, float, int, int, int);
extern float ApproachValue(void *, float, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern void SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_aim_move_record_at_target(void *, void *, float, float);
extern int hero_adjust_jump_speed_to_target(void *, float, float, float);
extern void extermibot_set_aim_toward_point(void *, void *, int);
extern int extermibot_is_position_short(void *, void *);
extern float extermibot_get_position_length_offset(void *, void *);
extern float extermibot_get_turn_angle_to_point(void *, void *);
extern int extermibot_is_path_to_point_clear(void *, void *);
extern int extermibot_is_cooldown_finished(void *);
extern int extermibot_is_facing_point(void *, void *);
extern int extermibot_find_nearest_protopet(void *);
extern void extermibot_set_slow_limits(void *);
extern void extermibot_set_fast_limits(void *);
extern void extermibot_destroy_piece_and_parts(void *);
extern void extermibot_set_anim_on_parts(void *, int, int, int);
extern void extermibot_fire_shot_at_target(void *);
extern void extermibot_start_attack_timer(void *);
extern void extermibot_clear_attack_counters(void *);

/* Runs the Extermibot's main behaviour: it idles, picks a target, walks toward it, attacks and finally blows up. Each state starts an animation and moves on when the animation ends. */
void extermibot_update_states(u8 *self)
{
    float vec[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(self + 0x68);

    switch (self[0x20]) {
    case 0:
    case 1:
        break;
    case 2:
        if (flag_set_first_pending(self) != 0)
            extermibot_set_anim_on_parts(self, 1, 0, 0xA);
        break;
    case 3:
        if (flag_set_first_pending(self) != 0) {
            self[0xBC] = 0;
            *(s16 *)(vars + 0x80C) = math_random_int_below(30);
        } else {
            if (self[0xBC] == 0 && *(u16 *)(self + 0x96) > *(s16 *)(vars + 0x80C)) {
                *(int *)(vars + 0x188) = 0;
                extermibot_set_anim_on_parts(self, 2, 0, 3);
                self[0xBC] = 1;
                vec_scale_to_length(vec, self + 0xC0, 2.0f);
                FastVecAdd(vec, vec, self + 0x10);
                vec[2] -= 6.0f;
                moby_aim_move_record_at_target(self, vec, 0.033333335f, 0.0055555557f);
            }
            if (self[0xBC] == 1) {
                ApproachValue(self + 0xF0, 0.0f, 0.052359886f);
                ApproachValue(self + 0xF4, 0.0f, 0.052359886f);
                *(int *)(vars + 0x138) |= 2;
                if (*(u8 **)(vars + 0x7EC) != 0)
                    *(int *)(*(u8 **)(vars + 0x7EC) + 0x98) = 0;
                if (hero_adjust_jump_speed_to_target(self, 11.0f, 18.0f, 27.0f) != 0) {
                    extermibot_set_fast_limits(self);
                    extermibot_set_anim_on_parts(self, 9, 0, 0xA);
                    *(float *)(vars + 0x134) = 0.2f;
                    if (*(int *)(vars + 0x7D0) != -1) {
                        self[0xBC] = 2;
                        qcopy(vars + 0x750, (u8 *)((*(int *)(vars + 0x7D0) << 7) + (s32)g_waypoint_table) + 0x30);
                    } else {
                        moby_set_state(self, 4, 1);
                    }
                }
                *(int *)(vars + 0x138) &= ~2;
                if (*(u8 **)(vars + 0x7EC) != 0)
                    *(int *)(*(u8 **)(vars + 0x7EC) + 0x98) = *(int *)(*(u8 **)(*(u8 **)(vars + 0x7EC) + 0x24) + 0x10);
            } else if (self[0xBC] == 2) {
                if (vec_distance_xy(self + 0x10, g_waypoint_table + (*(int *)(vars + 0x7D0) << 7) + 0x30) < 0.5f)
                    moby_set_state(self, 4, 1);
            }
        }
        break;
    case 4:
        if (flag_set_first_pending(self) != 0) {
            extermibot_set_anim_on_parts(self, math_random_int_below(2) + 3, 0, 0xA);
            if (self[0x94] != 4)
                *(int *)(vars + 0x7AC) = math_random_int_range(0, 30);
        } else if (self[0x60] & 2) {
            moby_set_state(self, 4, -1);
        } else if (*(s16 *)(vars + 0x7FA) == 0 && *(int *)(vars + 0x79C) == 1 && math_fast_float_d(vars + 0x7AC) != 0) {
            moby_set_state(self, 6, -1);
            moby_set_state(self, 5, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(self) != 0)
            extermibot_set_anim_on_parts(self, 5, 0, 0xA);
        else if (self[0x60] & 2)
            moby_set_state(self, self[0x94], -1);
        break;
    case 6:
        if (flag_set_first_pending(self) != 0) {
            extermibot_set_anim_on_parts(self, math_random_int_below(2) + 6, 0, 0xA);
            *(int *)(vars + 0x7A8) = math_random_int_range(480, 600);
        } else if (*(int *)(vars + 0x79C) == 1) {
            if (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))
                moby_set_state(self, 8, -1);
            else if (extermibot_find_nearest_protopet(self) != 0)
                moby_set_state(self, 7, 1);
        } else if (*(int *)(vars + 0x7A8) <= 0) {
            moby_set_state(self, 4, -1);
        }
        math_fast_float_d(vars + 0x7A8);
        break;
    case 9: {
        float frame;
        if (flag_set_first_pending(self) != 0) {
            *(float *)(vars + 0x134) = 2.0f;
            switch (self[0x42]) {
            case 8:
                extermibot_set_slow_limits(self);
                self[0xBC] = 1;
                break;
            case 9:
                extermibot_set_fast_limits(self);
                self[0xBC] = 2;
                break;
            default:
                extermibot_set_slow_limits(self);
                self[0xBC] = 1;
                extermibot_set_anim_on_parts(self, 8, 0, 0xA);
                break;
            }
        }
        if (*(u8 **)(vars + 0x7BC) != 0) {
            u8 *target = *(u8 **)(vars + 0x7BC);
            if (target[0x20] != 0xFE && (*(u8 **)(vars + 0x7BC))[0x20] != 0xFD && ((*(u16 *)(target + 0x34) ^ 1) & 1))
                qcopy(vars + 0x750, target + 0x10);
            else
                moby_set_state(self, self[0x94], -1);
        } else {
            qcopy(vars + 0x750, vars + 0x1F0);
        }
        extermibot_set_aim_toward_point(self, vars + 0x750, 0);
        frame = moby_get_anim_value(self);
        if (self[0xBC] == 2) {
            if (extermibot_get_position_length_offset(self, vars + 0x750) < 4.0f && (self[0x60] & 2)) {
                extermibot_set_slow_limits(self);
                self[0xBC] = 1;
                extermibot_set_anim_on_parts(self, 8, 0, 0xA);
            }
        } else if (self[0xBC] == 1) {
            if (extermibot_get_position_length_offset(self, vars + 0x750) > 7.0f && frame > 4.0f && frame < 9.0f) {
                extermibot_set_fast_limits(self);
                self[0xBC] = 2;
                extermibot_set_anim_on_parts(self, 9, 6, 0xA);
            }
            if (((frame > 4.0f && frame < 9.0f) || (frame > 21.0f && frame < 26.0f))
                && extermibot_get_position_length_offset(self, vars + 0x750) < 0.0f && extermibot_get_turn_angle_to_point(self, vars + 0x750) < 0.0f
                && extermibot_is_path_to_point_clear(self, vars + 0x750) != 0) {
                extermibot_set_anim_on_parts(self, math_random_int_below(2) + 6, 0, 0xA);
                moby_set_state(self, self[0x94], -1);
            }
        } else {
            if ((self[0x60] & 2) && *(u16 *)(self + 0x96) >= 0x79) {
                extermibot_set_slow_limits(self);
                self[0xBC] = 1;
                extermibot_set_anim_on_parts(self, 8, 0, 0xA);
            }
            if (extermibot_get_position_length_offset(self, vars + 0x750) < 0.0f && extermibot_get_turn_angle_to_point(self, vars + 0x750) < 0.0f
                && extermibot_is_path_to_point_clear(self, vars + 0x750) != 0) {
                extermibot_set_anim_on_parts(self, math_random_int_below(2) + 6, 0, 0xA);
                moby_set_state(self, self[0x94], -1);
            }
        }
        if ((self[0xBC] == 1 || self[0xBC] == 2)
            && (*(int *)(vars + 0x180) >= 2 || (*(int *)(vars + 0x194) & 0xF))) {
            self[0xBC] = 0;
            extermibot_set_anim_on_parts(self, math_random_int_below(2) + 6, 0, 0xA);
            *(u16 *)(self + 0x96) = 0;
        }
        if (self[0x94] == 7 && *(int *)(vars + 0x79C) == 1
            && (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))) {
            *(u8 **)(vars + 0x7BC) = 0;
            moby_set_state(self, 8, -1);
        }
        break;
    }
    case 7:
        if (flag_set_first_pending(self) != 0 && extermibot_find_nearest_protopet(self) == 0) {
            moby_set_state(self, 6, -1);
        } else if (extermibot_get_position_length_offset(self, *(u8 **)(vars + 0x7B8) + 0x10) >= 0.0f
                   || extermibot_get_turn_angle_to_point(self, *(u8 **)(vars + 0x7B8) + 0x10) >= 0.0f
                   || extermibot_is_path_to_point_clear(self, *(u8 **)(vars + 0x7B8) + 0x10) == 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            moby_set_state(self, 9, -1);
        } else if (*(int *)(vars + 0x79C) == 1
                   && (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))) {
            *(u8 **)(vars + 0x7BC) = 0;
            moby_set_state(self, 6, -1);
        } else if (extermibot_is_position_short(self, *(u8 **)(vars + 0x7B8) + 0x10) != 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            moby_set_state(self, 0xB, -1);
        } else if (extermibot_is_cooldown_finished(self) != 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            moby_set_state(self, 0xA, -1);
        }
        break;
    case 8: {
        u8 *home_point;
        if (flag_set_first_pending(self) != 0)
            extermibot_set_anim_on_parts(self, math_random_int_below(2) + 6, 0, 0xA);
        if (*(int *)(vars + 0x79C) != 1) {
            moby_set_state(self, 6, -1);
            break;
        }
        home_point = vars + 0x1F0;
        if (extermibot_is_position_short(self, home_point) != 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            moby_set_state(self, 0xB, -1);
        } else if (extermibot_get_position_length_offset(self, home_point) >= 0.0f || extermibot_get_turn_angle_to_point(self, home_point) >= 0.0f
                   || extermibot_is_path_to_point_clear(self, home_point) == 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            moby_set_state(self, 9, -1);
        } else if (extermibot_is_cooldown_finished(self) != 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            moby_set_state(self, 0xA, -1);
        }
        break;
    }
    case 10:
        if (flag_set_first_pending(self) != 0) {
            extermibot_set_anim_on_parts(self, 0xA, 0, 0xA);
            self[0xBC] = 0;
            *(float *)(self + 0x48) = 2.0f;
            if (*(s16 *)(vars + 0x7FC) != 0)
                *(s16 *)(vars + 0x806) = 0;
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            qcopy(vec, *(u8 **)(vars + 0x7BC) + 0x10);
        else
            qcopy(vec, vars + 0x1F0);
        extermibot_set_aim_toward_point(self, vec, 0);
        if (self[0xBC] == 0) {
            if (extermibot_is_position_short(self, vec) != 0) {
                u8 saved_anim = self[0x94];
                moby_set_state(self, 0xB, -1);
                self[0x94] = saved_anim;
                break;
            }
            if (self[0x60] & 2) {
                if (extermibot_is_facing_point(self, vec) != 0) {
                    self[0xBC] = 2;
                    if (*(s16 *)(vars + 0x7FC) != 0) {
                        extermibot_set_anim_on_parts(self, 0xC, 0, 0xA);
                        *(float *)(self + 0x48) = 1.0f;
                    } else {
                        extermibot_set_anim_on_parts(self, 0xD, 0, 0xA);
                        *(float *)(self + 0x48) = 1.0f;
                    }
                } else {
                    self[0xBC] = 1;
                    extermibot_set_anim_on_parts(self, 0xB, 0, 0xA);
                    *(float *)(self + 0x48) = 1.0f;
                }
            }
        }
        if (self[0xBC] == 1) {
            if (extermibot_is_position_short(self, vec) != 0) {
                u8 saved_anim = self[0x94];
                moby_set_state(self, 0xB, -1);
                self[0x94] = saved_anim;
                break;
            }
            if (extermibot_is_facing_point(self, vec) != 0) {
                self[0xBC] = 2;
                if (*(s16 *)(vars + 0x7FC) != 0)
                    extermibot_set_anim_on_parts(self, 0xC, 0, 0xA);
                else
                    extermibot_set_anim_on_parts(self, 0xD, 0, 0xA);
                *(float *)(self + 0x48) = 1.0f;
            }
        } else if (self[0xBC] == 2) {
            float frame = moby_get_anim_value(self);
            if (*(s16 *)(vars + 0x7FC) != 0) {
                if (frame < 2.0f && *(s16 *)(vars + 0x806) == 0) {
                    qcopy(vars + 0x760, vec);
                    extermibot_fire_shot_at_target(self);
                    *(s16 *)(vars + 0x806) = 1;
                }
            } else if (frame < 5.0f && *(s16 *)(vars + 0x806) == 0) {
                extermibot_start_attack_timer(self);
            }
            if (self[0x60] & 2) {
                if (*(u8 **)(vars + 0x7BC) == 0) {
                    if (extermibot_is_position_short(self, vec) != 0) {
                        u8 saved_anim = self[0x94];
                        moby_set_state(self, 0xB, -1);
                        self[0x94] = saved_anim;
                        break;
                    }
                    if (extermibot_is_cooldown_finished(self) != 0 && extermibot_get_position_length_offset(self, vec) < 0.0f
                        && extermibot_is_facing_point(self, vec) != 0) {
                        self[0xBC] = 2;
                        if (*(s16 *)(vars + 0x7FC) != 0) {
                            extermibot_set_anim_on_parts(self, 0xC, 0, 0xA);
                            *(float *)(self + 0x48) = 1.0f;
                        } else {
                            extermibot_set_anim_on_parts(self, 0xD, 0, 0xA);
                            *(float *)(self + 0x48) = 1.0f;
                        }
                    }
                }
                self[0xBC] = 3;
                extermibot_set_anim_on_parts(self, 0xE, 0, 0xA);
                *(float *)(self + 0x48) = 1.0f;
            }
        } else if (self[0xBC] == 3) {
            if (self[0x60] & 2) {
                extermibot_set_anim_on_parts(self, 8, 0, 0xA);
                moby_set_state(self, self[0x94], -1);
                *(float *)(self + 0x48) = 1.0f;
            }
        }
        break;
    case 11: {
        float frame;
        if (flag_set_first_pending(self) != 0) {
            extermibot_set_anim_on_parts(self, 0xF, 0, 0xA);
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            extermibot_set_aim_toward_point(self, *(u8 **)(vars + 0x7BC) + 0x10, 1);
        else
            extermibot_set_aim_toward_point(self, vars + 0x1F0, 1);
        frame = moby_get_anim_value(self);
        if (frame > 11.0f && frame < 17.0f)
            coll_test_hit_at_bone(self, 0.8f, (float)vars[0x36], 2, 0x10001, 4.0f, 0, 1, 0);
        if (self[0x60] & 2)
            moby_set_state(self, self[0x94], -1);
        break;
    }
    case 12: {
        float frame;
        if (flag_set_first_pending(self) != 0) {
            extermibot_set_anim_on_parts(self, 0xF, 2, 0xA);
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            extermibot_set_aim_toward_point(self, *(u8 **)(vars + 0x7BC) + 0x10, 1);
        else
            extermibot_set_aim_toward_point(self, vars + 0x1F0, 1);
        frame = moby_get_anim_value(self);
        if (frame > 11.0f && frame < 17.0f)
            coll_test_hit_at_bone(self, 0.8f, (float)vars[0x36], 2, 0x10001, 4.0f, 0, 1, 0);
        if (self[0x60] & 2)
            moby_set_state(self, self[0x94], -1);
        break;
    }
    case 13: {
        int flags;
        float frame;
        if (flag_set_first_pending(self) != 0) {
            extermibot_clear_attack_counters(self);
            *(s16 *)(vars + 0x804) = 0;
            *(s16 *)(vars + 0x80E) = 1;
        }
        flags = moby_dispatch_action_by_kind(self, vars + 0x50);
        frame = moby_get_anim_value(self);
        if (*(u16 *)(self + 0x96) >= 0xB5 || (flags & 1)) {
            SetDeathBits(self, 0, 3);
            extermibot_destroy_piece_and_parts(self);
        } else if ((self[0x42] == 0x10 && frame > 27.0f) || (self[0x42] == 0x11 && frame > 47.0f) || (flags & 2)) {
            if (*(u8 **)(vars + 0x7C0) != 0) {
                if (extermibot_is_position_short(self, vars + 0x1F0) != 0) {
                    *(float *)(self + 0x48) = 0.0f;
                    *(u8 **)(vars + 0x7BC) = 0;
                    moby_set_state(self, 8, 1);
                    moby_set_state(self, 0xB, -1);
                } else {
                    extermibot_set_anim_on_parts(self, math_random_int_below(2) + 6, 0, 0xA);
                    moby_set_state(self, 8, 1);
                }
                break;
            }
            moby_set_state(self, 0xE, 1);
        }
        if (*(s16 *)(vars + 0x80E) != 0 && *(u8 **)(vars + 0x38) != 0
            && *(s16 *)(*(u8 **)(vars + 0x38) + 0xAA) == 0x47 /* moby class 71 */ && *(u8 **)(vars + 0x7C0) != 0
            && self[0x42] == 0x10 && frame > 13.0f) {
            *(float *)(self + 0x48) = 0.0f;
            *(u8 **)(vars + 0x7BC) = 0;
            moby_set_state(self, 8, 1);
            moby_set_state(self, 0xC, -1);
        }
        break;
    }
    case 14:
        if (flag_set_first_pending(self) != 0) {
            if (*(s16 *)(vars + 0x80A) == 0)
                *(s16 *)(vars + 0x80A) = 600;
            if (*(u8 **)(vars + 0x7C0) != 0) {
                moby_transform_joint_to_world(self, 0, vec);
                SpawnExplosion(vec, 1, 10, 30, 0, 10, 45, 1, 0.5f, 20.0f, 0, 0, 0, 0);
                moby_mark_spawned(*(u8 **)(vars + 0x7C0));
                *(u8 **)(vars + 0x7C0) = 0;
            }
            if (*(u8 **)(vars + 0x7C4) != 0) {
                moby_mark_spawned(*(u8 **)(vars + 0x7C4));
                *(u8 **)(vars + 0x7C4) = 0;
            }
            if (*(u8 **)(vars + 0x7C8) != 0) {
                moby_mark_spawned(*(u8 **)(vars + 0x7C8));
                *(u8 **)(vars + 0x7C8) = 0;
            }
            if (self[0x43] != 8)
                anim_start_blended(self, 8, 0, 0xA);
        } else {
            qcopy(vars + 0x750, vars + 0x1F0);
            if (extermibot_is_position_short(self, vars + 0x1F0) != 0) {
                moby_set_state(self, 0xB, -1);
            } else if (FastDecTimer(vars + 0x80A) != 0) {
                SetDeathBits(self, 0, 3);
                extermibot_destroy_piece_and_parts(self);
            }
        }
        break;
    }
}
