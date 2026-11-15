#include "names.h"
/*
 * func_L18_003F5650 (levels 18, 19, 20), built on its own at -G16. Cases 12 and 13 share
 * the function-scope `grp`, as retail does: one pseudo, so both loops keep it in $a1.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char g_hero_state[];
extern char g_hero_position[];
extern u8 *g_active_attacker_robot[];
extern s32 D_0018C0B4[];
extern s32 D_001A7A00[] __attribute__((section(".sdata")));
extern u8 *D_L18_001BFC18[];
extern u8 *g_nearby_hit_targets[];
extern u32 D_L18_001B2348[] __attribute__((section(".sdata")));
/* The 16-byte offset vector (0, 0, 0.5, 0); its size keeps it $gp-relative at -G16. */
extern float D_L18_001B0420[4] __attribute__((sda));
extern u16 *D_L18_001FB320[];
extern s32 D_L18_001B2838[] __attribute__((section(".sdata")));
extern u8 *g_moby_l18_table[] __attribute__((section(".sdata")));
extern s32 *D_L18_001FE480[];

extern int coll_test_point(void *, int, void *, float);
extern int coll_process_hit(void *, int, void *, int, float);
extern float moby_get_anim_value(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern void func_002A05A8(void *);
extern void SetDeathBits(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern u8 *coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern void part_queue_impact_effect(void *, void *, int, void *, void *, float);
extern void vec_add_random_offset(void *, float);
extern int IsPointInCuboid(void *, int);
extern void ApplyObjectReaction(void *, void *, void *, int);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int path_measure_moby_against_entry(void *, int, float);
extern int path_advance(void *, void *, int, s16 *, int, float);
extern void moby_set_table_entry_byte(void *, int, int);
extern void protopet_start_turn_toward_target(void *, void *);
extern int protopet_is_action_finished(void *);
extern int protopet_is_near_pickup_ready(void *, void *);
extern int protopet_is_target_close_front(void *, void *);
extern int protopet_find_for_group(void *);
extern void protopet_end_action(void *, int);
extern u8 *protopet_count_group(void *, s32 *);
extern void protopet_launch_shot(void *, void *, void *);
extern int protopet_is_in_state_substate(void *);

/* Runs the Protopet state machine: idling, wandering, chasing, attacking, shooting and dying. */
void protopet_run_state_machine(u8 *moby)
{
    float point[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    s32 spawn_limit;
    u8 *vars;
    s32 group_id;

    vars = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            *(s16 *)(vars + 0x2A6) = 0;
            anim_start_blended(moby, 9, 0, 3);
            func_002A05A8(moby);
            moby[0x31] = 1;
            *(float *)(moby + 0x2C) = 0.001f;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            *(s16 *)(vars + 0x294) = 0;
            *(s16 *)(vars + 0x29E) = math_random_int_range(0xB4, 0xB4);
            *(s16 *)(vars + 0x2A4) = math_random_int_range(2, 4);
        } else {
            if (*(s16 *)(vars + 0x2A6) == 0 && *(u16 *)(moby + 0x96) >= 0x1F) {
                *(s16 *)(vars + 0x2A6) = 1;
            }
            if (*(float *)(moby + 0x2C) < *(float *)(vars + 0x268)) {
                *(float *)(moby + 0x2C) += *(float *)(vars + 0x268) * 0.1f;
            }
            if (protopet_is_action_finished(moby) != 0) {
                *(float *)(moby + 0x2C) = *(float *)(vars + 0x268);
                moby_set_state(moby, 6, 2);
                moby_set_state(moby, 7, -1);
            }
        }
        *(TI128 *)offset = 0;
        offset[2] = *(float *)(vars + 0x104) + *(float *)(vars + 0x100);
        *(TI128 *)vec = *(TI128 *)offset;
        FastVecAdd(point, moby + 0x10, vec);
        coll_sweep_from_object(moby, point, 0x4000000, 0, 1, 0, *(float *)(vars + 0x100) + 0.2f, 10.0f, 1.0f);
        break;
    case 2:
        if (flag_set_first_pending(moby) != 0) {
            *(float *)(vars + 0x100) = 0.34f;
            *(float *)(vars + 0x108) = 0.1f;
            *(float *)(vars + 0x104) = 0.0f;
            if (moby[0x43] != 9) {
                anim_start_blended(moby, 9, 0, 0);
            }
            moby[0x31] = 0;
            moby[0xBC] = 0;
            *(u16 *)(moby + 0x34) |= 1;
            break;
        }
        if (moby[0xBC] == 0) {
            if (IsPointInCuboid(g_hero_position, *(s32 *)(vars + 0x270)) != 0) {
                *(u16 *)(moby + 0x96) = 0;
                moby[0xBC] = 1;
            }
            break;
        }
        if (moby[0xBC] != 1) {
            break;
        }
        *(TI128 *)offset = 0;
        offset[2] = *(float *)(vars + 0x104) + *(float *)(vars + 0x100);
        *(TI128 *)vec = *(TI128 *)offset;
        FastVecAdd(point, moby + 0x10, vec);
        coll_sweep_from_object(moby, point, 0x4000000, 0, 1, 0, *(float *)(vars + 0x100) + *(float *)(vars + 0x100), 10.0f,
                      1.0f);
        if (*(u16 *)(moby + 0x96) >= 0xB) {
            vec_scale_to_length(offset, moby + 0xC0, 0.06666667f);
            offset[2] = 0.033333335f;
            protopet_launch_shot(moby, moby + 0x10, offset);
        }
        break;
    case 7:
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x43] != 0) {
                anim_start_blended(moby, 0, 0, 0xA);
            }
        } else if (moby[0x60] & 2) {
            moby_set_state(moby, moby[0x94], -1);
        }
        break;
    case 16: {
        float hero_distance;
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x43] != 2) {
                anim_start_blended(moby, 2, 0, 0xA);
            }
            vec_scale_to_length(vars + 0x1A0, moby + 0xC0, -0.06666667f);
            break;
        }
        hero_distance = moby_get_anim_value(moby);
        if (*(float *)(moby + 0x48) == 1.0f && 23.0f < hero_distance) {
            *(float *)(moby + 0x48) = -0.65f;
            vec_scale_to_length(vars + 0x1A0, moby + 0xC0, 0.13333334f);
            *(float *)(vars + 0x1A8) += 0.1388889f;
        } else if (*(float *)(moby + 0x48) == -0.65f && hero_distance < 3.0f) {
            *(float *)(moby + 0x48) = 1.0f;
            moby_set_state(moby, moby[0x94], -1);
        }
        break;
    }
    case 6:
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x43] != math_random_int_below(2) + 1) {
                anim_start_blended(moby, math_random_int_below(2) + 1, 0, math_random_int_range(9, 0xF));
            }
            *(s32 *)(vars + 0x250) = math_random_int_range(0x1E0, 0x258);
        } else if (*(s32 *)(vars + 0x258) != 0) {
            moby_set_state(moby, 0xB, -1);
        } else if (*(s32 *)(vars + 0x278) != -1) {
            moby_set_state(moby, 0xD, -1);
        } else if (*(s32 *)(vars + 0x248) == 1 && D_0018C0B4[0] != 0x6F) {
            moby_set_state(moby, 0xC, -1);
        }
        if (moby[0x60] & 2) {
            if (math_random_int_below(0x31) == 0) {
                if (moby[0x43] != 0xA) {
                    anim_start_blended(moby, 0xA, 0, math_random_int_range(9, 0xF));
                }
                *(float *)(moby + 0x48) = math_random_float_range(0.85f, 1.15f);
            } else {
                if (moby[0x43] != math_random_int_below(2) + 1) {
                    anim_start_blended(moby, math_random_int_below(2) + 1, 0, math_random_int_range(9, 0xF));
                }
                *(float *)(moby + 0x48) = math_random_float_range(0.85f, 1.15f);
            }
        }
        break;
    case 8:
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x43] != 0xA) {
                anim_start_blended(moby, 0xA, 0, 0xA);
            }
        } else if (moby[0x60] & 2) {
            moby_set_state(moby, moby[0x94], -1);
        }
        break;
    case 9:
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x43] != 6) {
                anim_start_blended(moby, 6, 0, 0xA);
            }
            moby[0xBC] = 0;
            *(s16 *)(vars + 0x298) = 0;
            break;
        }
        if (moby[0xBC] == 0 && (moby[0x60] & 2)) {
            if (moby[0x43] != 7) {
                anim_start_blended(moby, 7, 0, 0xA);
            }
            moby[0xBC] = 1;
        } else if (moby[0xBC] == 1) {
            spawn_limit = 0x32;
            if (*(u16 *)(moby + 0x96) >= 0x15) {
                u8 *spawn;
                *(u16 *)(moby + 0x96) = 0;
                spawn = protopet_count_group(*(u8 **)(vars + 0x25C), &spawn_limit);
                if (spawn != 0) {
                    float wobble;
                    FastVecAdd(point, moby + 0x10, D_L18_001B0420);
                    vec_clear_128(vec);
                    vec[2] = 0.13333334f;
                    wobble = math_random_float_range(2.0f, 3.0f) * 0.016666668f;
                    vec[0] = vec[0] + (math_random_int_below(2) != 0 ? wobble : -wobble);
                    wobble = math_random_float_range(2.0f, 3.0f) * 0.016666668f;
                    vec[1] = vec[1] + (math_random_int_below(2) != 0 ? wobble : -wobble);
                    protopet_launch_shot(spawn, point, vec);
                    *(s32 *)(spawn + 0xB8) = *(s32 *)(moby + 0xB8);
                    (*(s16 *)(vars + 0x298))++;
                }
            }
            if (*(s16 *)(vars + 0x298) >= 3 || spawn_limit == 0) {
                if (moby[0x43] != 8) {
                    anim_start_blended(moby, 8, 0, 0xA);
                }
                moby[0xBC] = 2;
            }
        } else if (moby[0xBC] == 2) {
            if (moby[0x60] & 2) {
                moby_set_state(moby, moby[0x94], -1);
            }
        }
        break;
    case 10: {
        float hero_distance;
        s32 count;
        s32 i;
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x43] != 5) {
                anim_start_blended(moby, 5, 0, 0xA);
            }
            break;
        }
        hero_distance = moby_get_anim_value(moby);
        if (moby[0x42] == 5 && hero_distance < 10.0f) {
            moby_set_controller_speed_limits(moby, 0.083333336f, 0.33333334f, 0.1939255f, 2.9088826f);
            if (moby[0x94] == 0xB && *(u8 **)(vars + 0x258) != 0) {
                protopet_start_turn_toward_target(moby, *(u8 **)(vars + 0x258) + 0x10);
            } else {
                protopet_start_turn_toward_target(moby, vars + 0x1F0);
            }
        }
        if (moby[0x42] == 5 && 10.0f < hero_distance && hero_distance < 17.0f) {
            moby_transform_joint_to_world(moby, 0, point);
            count = coll_process_hit(point, 0, moby, 0, 0.2f);
            if (count != 0) {
                for (i = 0; i < count; i++) {
                    u8 *other = g_nearby_hit_targets[i];
                    char *hero = g_hero_state;
                    if (other == *(u8 **)(hero + 0x2290)) {
                        qcopy(vec, hero + 0x80);
                    } else {
                        qcopy(vec, other + 0x10);
                        if (*(s16 *)(other + 0xAA) == MOBY_CLASS_PROTOPET) {
                            continue;
                        }
                    }
                    FastVecSub(offset, other + 0x10, moby + 0x10);
                    offset[2] = 0.0f;
                    vec_scale_to_length(offset, offset, 2.0f);
                    offset[3] = 5627.925f;
                    part_queue_impact_effect(other, moby, 0x10001, other + 0x10, offset, vars[0x34]);
                }
            }
        }
        if (moby[0x60] & 2) {
            moby_set_controller_speed_limits(moby, 0.0044444446f, 0.13333334f, 0.003490659f, 0.20943955f);
            if (g_active_attacker_robot[0] == moby) {
                u8 next = moby[0x94];
                moby_set_state(moby, 8, -1);
                moby[0x94] = next;
            } else {
                moby_set_state(moby, moby[0x94], -1);
            }
        }
        break;
    }
    case 11: {
        u8 *other;
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x43] != 4) {
                anim_start_blended(moby, 4, 0, 0xA);
            }
            *(float *)(vars + 0x24C) = 0.017453294f;
            break;
        }
        qcopy_nc(vars + 0x230, *(u8 **)(vars + 0x258) + 0x10);
        if (protopet_is_in_state_substate(*(u8 **)(vars + 0x258)) != 0 && protopet_is_target_close_front(moby, *(u8 **)(vars + 0x258) + 0x10) != 0) {
            moby_set_state(moby, 0xA, -1);
            break;
        }
        if (protopet_is_near_pickup_ready(moby, *(u8 **)(vars + 0x258)) != 0) {
            moby_set_state(moby, 8, -1);
            break;
        }
        other = *(u8 **)(vars + 0x258);
        if (other == 0 || other[0x20] == 0xFE || other[0x20] == 0xFD || (*(u16 *)(other + 0x34) & 1)) {
            *(u8 **)(vars + 0x258) = 0;
            moby_set_state(moby, 0xC, -1);
            moby_set_state(moby, 8, -1);
        }
        break;
    }
    case 12: {
        u8 phase;
        if (flag_set_first_pending(moby) != 0) {
            float turn_degrees;
            if (moby[0x43] != 4) {
                anim_start_blended(moby, 4, 0, 0xA);
            }
            turn_degrees = math_random_float_range(15.0f, 30.0f);
            *(float *)(vars + 0x24C) = turn_degrees * (math_random_int_below(2) != 0 ? -0.017453294f : 0.017453294f);
            moby[0xBC] = 0;
        }
        phase = moby[0xBC];
        if (phase == 0) {
            qcopy(vars + 0x230, vars + 0x1F0);
            group_id = *(s32 *)(vars + 0x27C);
            if (group_id != -1 && (D_L18_001B2348[0] & 7) == (((s32)moby >> 8) & 7)) {
                u16 *group_entry;
                float best = 1000.0f;
                s32 lost = 1;
                for (group_entry = D_L18_001FB320[group_id];
                     (u8)group_id != 0xFF && group_id <= D_L18_001B2838[0] && group_entry != 0
                     && ((group_entry != 0 && (s16)group_entry[-1] >= 0) || group_entry == D_L18_001FB320[group_id]);
                     group_id = *(s32 *)(vars + 0x27C), group_entry++) {
                    u8 *other = g_moby_l18_table[0] + ((*group_entry & 0x7FFF) << 8);
                    if (other == 0) {
                        break;
                    }
                    if (other[0x20] != 0xFE) {
                        if (other[0x20] != 0xFD) {
                            float candidate_distance;
                            lost = 0;
                            candidate_distance = vec_distance_xy(moby + 0x10, other + 0x10);
                            if (candidate_distance < best) {
                                best = candidate_distance;
                            }
                        }
                    }
                }
                if (lost) {
                    *(s32 *)(vars + 0x278) = -1;
                    *(s32 *)(vars + 0x27C) = -1;
                }
            }
            if (protopet_is_target_close_front(moby, vars + 0x1F0) != 0) {
                *(u16 *)(moby + 0x96) = 0;
                moby[0xBC] = 1;
                if (moby[0x43] != math_random_int_below(2) + 1) {
                    anim_start_blended(moby, math_random_int_below(2) + 1, 0, 0xA);
                }
            }
        } else if (phase == 1) {
            if (protopet_is_target_close_front(moby, vars + 0x1F0) != 0 && *(s32 *)(vars + 0x180) < 2) {
                moby_set_state(moby, 0xA, -1);
            } else if (*(u16 *)(moby + 0x96) >= 0x3D) {
                moby_set_state(moby, 0xC, -1);
            }
        }
        if (protopet_find_for_group(moby) != 0) {
            moby_set_state(moby, 9, 2);
        }
        if (*(s32 *)(vars + 0x248) != 1) {
            moby_set_state(moby, 6, -1);
        }
        break;
    }
    case 13: {
        u16 *group_entry;
        s32 lost;
        if (flag_set_first_pending(moby) != 0) {
            float turn_degrees;
            if (moby[0x43] != 4) {
                anim_start_blended(moby, 4, 0, 0xA);
            }
            *(s16 *)(vars + 0x29A) = path_measure_moby_against_entry(moby + 0x10, *(s32 *)(vars + 0x278), 0.0f);
            turn_degrees = math_random_float_range(15.0f, 30.0f);
            *(float *)(vars + 0x24C) = turn_degrees * (math_random_int_below(2) != 0 ? -0.017453294f : 0.017453294f);
            moby_set_controller_speed_limits(moby, 0.0016666667f, 0.050000004f, 0.003490659f, 0.10471977f);
            break;
        }
        path_advance(moby, vars + 0x230, *(s32 *)(vars + 0x278), (s16 *)(vars + 0x29A), 0, 3.0f);
        group_id = *(s32 *)(vars + 0x27C);
        if (group_id == -1) {
            break;
        }
        if ((D_L18_001B2348[0] & 0x3F) != (((s32)moby >> 8) & 0x3F)) {
            break;
        }
        lost = 1;
        for (group_entry = D_L18_001FB320[group_id];
             (*(s32 *)(vars + 0x27C) & 0xFF) != 0xFF && *(s32 *)(vars + 0x27C) <= D_L18_001B2838[0] && group_entry != 0
             && ((group_entry != 0 && (s16)group_entry[-1] >= 0) || group_entry == D_L18_001FB320[*(s32 *)(vars + 0x27C)]);
             group_entry++) {
            u8 *other = g_moby_l18_table[0] + ((*group_entry & 0x7FFF) << 8);
            if (other == 0) {
                break;
            }
            if (other[0x20] != 0xFE) {
                if (other[0x20] != 0xFD) {
                    lost = 0;
                    break;
                }
            }
        }
        if (lost) {
            *(s32 *)(vars + 0x278) = -1;
            *(s32 *)(vars + 0x27C) = -1;
            moby_set_state(moby, 0xC, -1);
        }
        break;
    }
    case 14:
        if (flag_set_first_pending(moby) != 0) {
            s32 next;
            s32 *path;
            *(float *)(vars + 0xAC) = 1.0f;
            *(float *)(vars + 0xA8) = 1.0f;
            *(float *)(vars + 0x134) = 0.001f;
            *(s16 *)(vars + 0x29A) = path_measure_moby_against_entry(moby + 0x10, *(s32 *)(vars + 0x26C), 0.0f);
            if (*(s16 *)(vars + 0x29C) != 0) {
                if (*(s16 *)(vars + 0x29A) == 0) {
                    next = *D_L18_001FE480[*(s32 *)(vars + 0x26C)] - 1;
                } else {
                    next = *(s16 *)(vars + 0x29A) - 1;
                }
            } else {
                next = (*(s16 *)(vars + 0x29A) == *D_L18_001FE480[*(s32 *)(vars + 0x26C)] - 1) ? 0
                                                                                           : *(s16 *)(vars + 0x29A) + 1;
            }
            path = D_L18_001FE480[*(s32 *)(vars + 0x26C)];
            FastVecSub(point, path + (next * 4 + 4), path + (*(s16 *)(vars + 0x29A) * 4 + 4));
            FastVecSub(vec, D_L18_001FE480[*(s32 *)(vars + 0x26C)] + (*(s16 *)(vars + 0x29A) * 4 + 4), moby + 0x10);
            if (FastVecDot(vec, point) < 0.0f) {
                *(s16 *)(vars + 0x29A) = next;
            }
            *(s32 *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
            if (moby[0x43] != math_random_int_below(2) + 1) {
                anim_start_blended(moby, math_random_int_below(2) + 1, math_random_int_below(0xA), 0xA);
            }
            moby[0xBC] = 0;
            break;
        }
        if (moby[0xBC] == 0) {
            if (*(s32 *)(vars + 0x270) != -1 && IsPointInCuboid(g_hero_position, *(s32 *)(vars + 0x270)) != 0) {
                moby[0xBC] = 1;
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                moby_set_table_entry_byte(moby, 0, 2);
            }
        } else {
            float target_distance;
            u8 *pos;
            if (path_advance(moby, vars + 0x230, *(s32 *)(vars + 0x26C), (s16 *)(vars + 0x29A),
                                  *(s16 *)(vars + 0x29C), 0.2f) == 0) {
                moby_set_state(moby, 0xF, -1);
            }
            pos = moby + 0x10;
            target_distance = fast_vec_dist(pos, g_hero_position);
            if (target_distance < 8.0f) {
                if (moby[0x43] != 1) {
                    anim_start_blended(moby, 1, 0, 0xA);
                }
                if (target_distance < 2.0f) {
                    u8 *hit;
                    float reach;
                    qcopy(point, pos);
                    point[2] = point[2] + (*(float *)(vars + 0x104) + *(float *)(vars + 0x100));
                    reach = *(float *)(vars + 0x100) + 0.2f;
                    coll_sweep_from_object(moby, point, 1, 0, 1, 0, reach, IntToFloat(D_001A7A00[0]) * 0.25f, 1.0f);
                    if (coll_test_point(point, 1, moby, *(float *)(vars + 0x100) + 0.2f) != 0) {
                        hit = D_L18_001BFC18[0];
                        if (hit != 0 && *(s16 *)(hit + 0xAA) != MOBY_CLASS_PROTOPET) {
                            *(s32 *)(vars + 0x20) = 0;
                            vec_scale_to_length(vec, moby + 0xC0, -1.0f);
                            vec_add_random_offset(vec, 0.3f);
                            ApplyObjectReaction(moby, vars + 0x50, vec, 2);
                            moby_set_state(moby, 0x11, 3);
                        }
                    }
                }
            }
        }
        break;
    case 15:
        if (flag_set_first_pending(moby) != 0) {
            vec_add_random_offset(vars + 0x1A0, 0.050000004f);
            *(float *)(vars + 0x1A8) = 0.083333336f;
            if (moby[0x43] != 0xD) {
                anim_start_blended(moby, 0xD, 0, 0xA);
            }
        } else if (*(u16 *)(moby + 0x96) >= 0x12D) {
            SetDeathBits(moby, 0, 1);
            protopet_end_action(moby, 0);
        }
        break;
    case 17: {
        s32 flags;
        float hero_distance;
        if (flag_set_first_pending(moby) != 0) {
            if (moby[0x42] == 0xC || moby[0x43] == 0xC) {
                *(u16 *)(moby + 0x34) &= 0xEFFF;
            }
            if (moby[0x94] == 0xE) {
                FastVecScale(vars + 0xD0, vars + 0xD0, 3.0f);
            }
        }
        flags = moby_dispatch_action_by_kind(moby, vars + 0x50);
        if (moby[0x94] == 0xE || moby[0x94] == 0xF) {
            hero_distance = moby_get_anim_value(moby);
            if (moby[0x42] == 0xB && 16.0f < hero_distance) {
                moby_set_state(moby, 0xF, -1);
            }
        }
        hero_distance = moby_get_anim_value(moby);
        if ((flags & 1) || (moby[0x42] == 0xC && 15.0f < hero_distance && math_random_int_below(0xF) == 0)) {
            SetDeathBits(moby, 0, 1);
            protopet_end_action(moby, 0);
            break;
        }
        if (flags & 2) {
            u8 mode;
            *(u8 **)(vars + 0x258) = 0;
            mode = moby[0x95];
            moby_set_state(moby, 0xC, 2);
            if (mode == 1) {
                moby_set_state(moby, 7, -1);
            }
        }
        break;
    }
    case 18:
        if (flag_set_first_pending(moby) != 0) {
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            if (moby[0x95] == 2) {
                if (moby[0x43] != 3) {
                    anim_start_blended(moby, 3, 0, 0xA);
                }
            }
            *(float *)(moby + 0x48) = 1.0f;
        }
        if ((moby[0x60] & 2) || *(u16 *)(moby + 0x96) >= 0x3D) {
            *(s32 *)(vars + 0x20) = 0;
            SetDeathBits(moby, 0, 1);
            protopet_end_action(moby, 0);
        }
        break;
    case 0:
    default:
        break;
    }
}
