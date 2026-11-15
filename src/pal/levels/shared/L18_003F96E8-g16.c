#include "names.h"
/*
 * func_PAL_L18_003F96E8 (levels 18, 19, 20), the PAL copy of func_L18_003F5650, built on its
 * own at -G16: the same C, with its frame counts and per-frame rates rescaled for 50 Hz. Cases
 * 12 and 13 share the function-scope `grp`, as retail does: one pseudo, so both loops keep it
 * in $a1.
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
extern void func_PAL_002A0F68(void *);
extern void func_PAL_002A7650(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern void part_queue_impact_effect(void *, void *, int, void *, void *, float);
extern void vec_add_random_offset(void *, float);
extern int IsPointInCuboid(void *, int);
extern int func_PAL_002B1EE8(void *, void *, void *, int);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int path_measure_moby_against_entry(void *, int, float);
extern int path_advance(void *, void *, int, s16 *, int, float);
extern int moby_set_table_entry_byte(void *, int, int);
extern void protopet_start_turn_toward_target(void *, void *);
extern int func_PAL_L18_003FB3D8(void *);
extern int protopet_is_near_pickup_ready(void *, void *);
extern int protopet_is_target_close_front(void *, void *);
extern int func_PAL_L18_003FB528(void *);
extern void protopet_end_action(void *, int);
extern u8 *protopet_count_group(void *, s32 *);
extern void protopet_launch_shot(void *, void *, void *);
extern int protopet_is_in_state_substate(void *);

void func_PAL_L18_003F96E8(u8 *a0)
{
    float p[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    float r[4] __attribute__((aligned(16)));
    s32 n;
    u8 *st;
    s32 grp;

    st = *(u8 **)(a0 + 0x68);
    switch (a0[0x20]) {
    case 3:
        if (flag_set_first_pending(a0) != 0) {
            *(s16 *)(st + 0x2A6) = 0;
            func_PAL_002A7E68(a0, 9, 0, 3);
            func_PAL_002A0F68(a0);
            a0[0x31] = 1;
            *(float *)(a0 + 0x2C) = 0.001f;
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
            *(s16 *)(st + 0x294) = 0;
            *(s16 *)(st + 0x29E) = math_random_int_range(0xB4, 0xB4);
            *(s16 *)(st + 0x2A4) = math_random_int_range(2, 4);
        } else {
            if (*(s16 *)(st + 0x2A6) == 0 && *(u16 *)(a0 + 0x96) >= 0x1A) {
                *(s16 *)(st + 0x2A6) = 1;
            }
            if (*(float *)(a0 + 0x2C) < *(float *)(st + 0x268)) {
                *(float *)(a0 + 0x2C) += *(float *)(st + 0x268) * 0.1f;
            }
            if (func_PAL_L18_003FB3D8(a0) != 0) {
                *(float *)(a0 + 0x2C) = *(float *)(st + 0x268);
                moby_set_state(a0, 6, 2);
                moby_set_state(a0, 7, -1);
            }
        }
        *(TI128 *)r = 0;
        r[2] = *(float *)(st + 0x104) + *(float *)(st + 0x100);
        *(TI128 *)q = *(TI128 *)r;
        FastVecAdd(p, a0 + 0x10, q);
        coll_sweep_from_object(a0, p, 0x4000000, 0, 1, 0, *(float *)(st + 0x100) + 0.2f, 10.0f, 1.0f);
        break;
    case 2:
        if (flag_set_first_pending(a0) != 0) {
            *(float *)(st + 0x100) = 0.34f;
            *(float *)(st + 0x108) = 0.1f;
            *(float *)(st + 0x104) = 0.0f;
            if (a0[0x43] != 9) {
                func_PAL_002A7E68(a0, 9, 0, 0);
            }
            a0[0x31] = 0;
            a0[0xBC] = 0;
            *(u16 *)(a0 + 0x34) |= 1;
            break;
        }
        if (a0[0xBC] == 0) {
            if (IsPointInCuboid(g_hero_position, *(s32 *)(st + 0x270)) != 0) {
                *(u16 *)(a0 + 0x96) = 0;
                a0[0xBC] = 1;
            }
            break;
        }
        if (a0[0xBC] != 1) {
            break;
        }
        *(TI128 *)r = 0;
        r[2] = *(float *)(st + 0x104) + *(float *)(st + 0x100);
        *(TI128 *)q = *(TI128 *)r;
        FastVecAdd(p, a0 + 0x10, q);
        coll_sweep_from_object(a0, p, 0x4000000, 0, 1, 0, *(float *)(st + 0x100) + *(float *)(st + 0x100), 10.0f,
                      1.0f);
        if (*(u16 *)(a0 + 0x96) >= 0x9) {
            vec_scale_to_length(r, a0 + 0xC0, 0.080000006f);
            r[2] = 0.040000003f;
            protopet_launch_shot(a0, a0 + 0x10, r);
        }
        break;
    case 7:
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x43] != 0) {
                func_PAL_002A7E68(a0, 0, 0, 0x8);
            }
        } else if (a0[0x60] & 2) {
            moby_set_state(a0, a0[0x94], -1);
        }
        break;
    case 16: {
        float f;
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x43] != 2) {
                func_PAL_002A7E68(a0, 2, 0, 0x8);
            }
            vec_scale_to_length(st + 0x1A0, a0 + 0xC0, -0.080000006f);
            break;
        }
        f = moby_get_anim_value(a0);
        if (*(float *)(a0 + 0x48) == 1.0f && 23.0f < f) {
            *(float *)(a0 + 0x48) = -0.65f;
            vec_scale_to_length(st + 0x1A0, a0 + 0xC0, 0.16000001f);
            *(float *)(st + 0x1A8) += 0.2f;
        } else if (*(float *)(a0 + 0x48) == -0.65f && f < 3.0f) {
            *(float *)(a0 + 0x48) = 1.0f;
            moby_set_state(a0, a0[0x94], -1);
        }
        break;
    }
    case 6:
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x43] != math_random_int_below(2) + 1) {
                func_PAL_002A7E68(a0, math_random_int_below(2) + 1, 0, math_random_int_range(9, 0xF));
            }
            *(s32 *)(st + 0x250) = ((s32)(math_random_int_range(0x1E0, 0x258)) * 5 + 2) / 6;
        } else if (*(s32 *)(st + 0x258) != 0) {
            moby_set_state(a0, 0xB, -1);
        } else if (*(s32 *)(st + 0x278) != -1) {
            moby_set_state(a0, 0xD, -1);
        } else if (*(s32 *)(st + 0x248) == 1 && D_0018C0B4[0] != 0x6F) {
            moby_set_state(a0, 0xC, -1);
        }
        if (a0[0x60] & 2) {
            if (math_random_int_below(0x31) == 0) {
                if (a0[0x43] != 0xA) {
                    func_PAL_002A7E68(a0, 0xA, 0, math_random_int_range(9, 0xF));
                }
                *(float *)(a0 + 0x48) = math_random_float_range(0.85f, 1.15f);
            } else {
                if (a0[0x43] != math_random_int_below(2) + 1) {
                    func_PAL_002A7E68(a0, math_random_int_below(2) + 1, 0, math_random_int_range(9, 0xF));
                }
                *(float *)(a0 + 0x48) = math_random_float_range(0.85f, 1.15f);
            }
        }
        break;
    case 8:
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x43] != 0xA) {
                func_PAL_002A7E68(a0, 0xA, 0, 0x8);
            }
        } else if (a0[0x60] & 2) {
            moby_set_state(a0, a0[0x94], -1);
        }
        break;
    case 9:
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x43] != 6) {
                func_PAL_002A7E68(a0, 6, 0, 0x8);
            }
            a0[0xBC] = 0;
            *(s16 *)(st + 0x298) = 0;
            break;
        }
        if (a0[0xBC] == 0 && (a0[0x60] & 2)) {
            if (a0[0x43] != 7) {
                func_PAL_002A7E68(a0, 7, 0, 0x8);
            }
            a0[0xBC] = 1;
        } else if (a0[0xBC] == 1) {
            n = 0x32;
            if (*(u16 *)(a0 + 0x96) >= 0x12) {
                u8 *spawn;
                *(u16 *)(a0 + 0x96) = 0;
                spawn = protopet_count_group(*(u8 **)(st + 0x25C), &n);
                if (spawn != 0) {
                    float d;
                    FastVecAdd(p, a0 + 0x10, D_L18_001B0420);
                    vec_clear_128(q);
                    q[2] = 0.16000001f;
                    d = math_random_float_range(2.0f, 3.0f) * 0.020000001f;
                    q[0] = q[0] + (math_random_int_below(2) != 0 ? d : -d);
                    d = math_random_float_range(2.0f, 3.0f) * 0.020000001f;
                    q[1] = q[1] + (math_random_int_below(2) != 0 ? d : -d);
                    protopet_launch_shot(spawn, p, q);
                    *(s32 *)(spawn + 0xB8) = *(s32 *)(a0 + 0xB8);
                    (*(s16 *)(st + 0x298))++;
                }
            }
            if (*(s16 *)(st + 0x298) >= 3 || n == 0) {
                if (a0[0x43] != 8) {
                    func_PAL_002A7E68(a0, 8, 0, 0x8);
                }
                a0[0xBC] = 2;
            }
        } else if (a0[0xBC] == 2) {
            if (a0[0x60] & 2) {
                moby_set_state(a0, a0[0x94], -1);
            }
        }
        break;
    case 10: {
        float f;
        s32 count;
        s32 i;
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x43] != 5) {
                func_PAL_002A7E68(a0, 5, 0, 0x8);
            }
            break;
        }
        f = moby_get_anim_value(a0);
        if (a0[0x42] == 5 && f < 10.0f) {
            moby_set_controller_speed_limits(a0, 0.120000005f, 0.40000004f, 0.27925274f, 3.4906592f);
            if (a0[0x94] == 0xB && *(u8 **)(st + 0x258) != 0) {
                protopet_start_turn_toward_target(a0, *(u8 **)(st + 0x258) + 0x10);
            } else {
                protopet_start_turn_toward_target(a0, st + 0x1F0);
            }
        }
        if (a0[0x42] == 5 && 10.0f < f && f < 17.0f) {
            moby_transform_joint_to_world(a0, 0, p);
            count = coll_process_hit(p, 0, a0, 0, 0.2f);
            if (count != 0) {
                for (i = 0; i < count; i++) {
                    u8 *e = g_nearby_hit_targets[i];
                    char *h = g_hero_state;
                    if (e == *(u8 **)(h + 0x2290)) {
                        qcopy(q, h + 0x80);
                    } else {
                        qcopy(q, e + 0x10);
                        if (*(s16 *)(e + 0xAA) == 0xB69) {
                            continue;
                        }
                    }
                    FastVecSub(r, e + 0x10, a0 + 0x10);
                    r[2] = 0.0f;
                    vec_scale_to_length(r, r, 2.0f);
                    r[3] = 5627.925f;
                    part_queue_impact_effect(e, a0, 0x10001, e + 0x10, r, st[0x34]);
                }
            }
        }
        if (a0[0x60] & 2) {
            moby_set_controller_speed_limits(a0, 0.0064000003f, 0.16000001f, 0.005026549f, 0.25132746f);
            if (g_active_attacker_robot[0] == a0) {
                u8 next = a0[0x94];
                moby_set_state(a0, 8, -1);
                a0[0x94] = next;
            } else {
                moby_set_state(a0, a0[0x94], -1);
            }
        }
        break;
    }
    case 11: {
        u8 *e;
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x43] != 4) {
                func_PAL_002A7E68(a0, 4, 0, 0x8);
            }
            *(float *)(st + 0x24C) = 0.017453294f;
            break;
        }
        qcopy_nc(st + 0x230, *(u8 **)(st + 0x258) + 0x10);
        if (protopet_is_in_state_substate(*(u8 **)(st + 0x258)) != 0 && protopet_is_target_close_front(a0, *(u8 **)(st + 0x258) + 0x10) != 0) {
            moby_set_state(a0, 0xA, -1);
            break;
        }
        if (protopet_is_near_pickup_ready(a0, *(u8 **)(st + 0x258)) != 0) {
            moby_set_state(a0, 8, -1);
            break;
        }
        e = *(u8 **)(st + 0x258);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD || (*(u16 *)(e + 0x34) & 1)) {
            *(u8 **)(st + 0x258) = 0;
            moby_set_state(a0, 0xC, -1);
            moby_set_state(a0, 8, -1);
        }
        break;
    }
    case 12: {
        u8 phase;
        if (flag_set_first_pending(a0) != 0) {
            float f;
            if (a0[0x43] != 4) {
                func_PAL_002A7E68(a0, 4, 0, 0x8);
            }
            f = math_random_float_range(15.0f, 30.0f);
            *(float *)(st + 0x24C) = f * (math_random_int_below(2) != 0 ? -0.017453294f : 0.017453294f);
            a0[0xBC] = 0;
        }
        phase = a0[0xBC];
        if (phase == 0) {
            qcopy(st + 0x230, st + 0x1F0);
            grp = *(s32 *)(st + 0x27C);
            if (grp != -1 && (D_L18_001B2348[0] & 7) == (((s32)a0 >> 8) & 7)) {
                u16 *g;
                float best = 1000.0f;
                s32 lost = 1;
                for (g = D_L18_001FB320[grp];
                     (u8)grp != 0xFF && grp <= D_L18_001B2838[0] && g != 0
                     && ((g != 0 && (s16)g[-1] >= 0) || g == D_L18_001FB320[grp]);
                     grp = *(s32 *)(st + 0x27C), g++) {
                    u8 *e = g_moby_l18_table[0] + ((*g & 0x7FFF) << 8);
                    if (e == 0) {
                        break;
                    }
                    if (e[0x20] != 0xFE) {
                        if (e[0x20] != 0xFD) {
                            float d;
                            lost = 0;
                            d = vec_distance_xy(a0 + 0x10, e + 0x10);
                            if (d < best) {
                                best = d;
                            }
                        }
                    }
                }
                if (lost) {
                    *(s32 *)(st + 0x278) = -1;
                    *(s32 *)(st + 0x27C) = -1;
                }
            }
            if (protopet_is_target_close_front(a0, st + 0x1F0) != 0) {
                *(u16 *)(a0 + 0x96) = 0;
                a0[0xBC] = 1;
                if (a0[0x43] != math_random_int_below(2) + 1) {
                    func_PAL_002A7E68(a0, math_random_int_below(2) + 1, 0, 0x8);
                }
            }
        } else if (phase == 1) {
            if (protopet_is_target_close_front(a0, st + 0x1F0) != 0 && *(s32 *)(st + 0x180) < 2) {
                moby_set_state(a0, 0xA, -1);
            } else if (*(u16 *)(a0 + 0x96) >= 0x33) {
                moby_set_state(a0, 0xC, -1);
            }
        }
        if (func_PAL_L18_003FB528(a0) != 0) {
            moby_set_state(a0, 9, 2);
        }
        if (*(s32 *)(st + 0x248) != 1) {
            moby_set_state(a0, 6, -1);
        }
        break;
    }
    case 13: {
        u16 *g;
        s32 lost;
        if (flag_set_first_pending(a0) != 0) {
            float f;
            if (a0[0x43] != 4) {
                func_PAL_002A7E68(a0, 4, 0, 0x8);
            }
            *(s16 *)(st + 0x29A) = path_measure_moby_against_entry(a0 + 0x10, *(s32 *)(st + 0x278), 0.0f);
            f = math_random_float_range(15.0f, 30.0f);
            *(float *)(st + 0x24C) = f * (math_random_int_below(2) != 0 ? -0.017453294f : 0.017453294f);
            moby_set_controller_speed_limits(a0, 0.0024f, 0.060000002f, 0.005026549f, 0.12566373f);
            break;
        }
        path_advance(a0, st + 0x230, *(s32 *)(st + 0x278), (s16 *)(st + 0x29A), 0, 3.0f);
        grp = *(s32 *)(st + 0x27C);
        if (grp == -1) {
            break;
        }
        if ((D_L18_001B2348[0] & 0x3F) != (((s32)a0 >> 8) & 0x3F)) {
            break;
        }
        lost = 1;
        for (g = D_L18_001FB320[grp];
             (*(s32 *)(st + 0x27C) & 0xFF) != 0xFF && *(s32 *)(st + 0x27C) <= D_L18_001B2838[0] && g != 0
             && ((g != 0 && (s16)g[-1] >= 0) || g == D_L18_001FB320[*(s32 *)(st + 0x27C)]);
             g++) {
            u8 *e = g_moby_l18_table[0] + ((*g & 0x7FFF) << 8);
            if (e == 0) {
                break;
            }
            if (e[0x20] != 0xFE) {
                if (e[0x20] != 0xFD) {
                    lost = 0;
                    break;
                }
            }
        }
        if (lost) {
            *(s32 *)(st + 0x278) = -1;
            *(s32 *)(st + 0x27C) = -1;
            moby_set_state(a0, 0xC, -1);
        }
        break;
    }
    case 14:
        if (flag_set_first_pending(a0) != 0) {
            s32 next;
            s32 *path;
            *(float *)(st + 0xAC) = 1.0f;
            *(float *)(st + 0xA8) = 1.0f;
            *(float *)(st + 0x134) = 0.001f;
            *(s16 *)(st + 0x29A) = path_measure_moby_against_entry(a0 + 0x10, *(s32 *)(st + 0x26C), 0.0f);
            if (*(s16 *)(st + 0x29C) != 0) {
                if (*(s16 *)(st + 0x29A) == 0) {
                    next = *D_L18_001FE480[*(s32 *)(st + 0x26C)] - 1;
                } else {
                    next = *(s16 *)(st + 0x29A) - 1;
                }
            } else {
                next = (*(s16 *)(st + 0x29A) == *D_L18_001FE480[*(s32 *)(st + 0x26C)] - 1) ? 0
                                                                                           : *(s16 *)(st + 0x29A) + 1;
            }
            path = D_L18_001FE480[*(s32 *)(st + 0x26C)];
            FastVecSub(p, path + (next * 4 + 4), path + (*(s16 *)(st + 0x29A) * 4 + 4));
            FastVecSub(q, D_L18_001FE480[*(s32 *)(st + 0x26C)] + (*(s16 *)(st + 0x29A) * 4 + 4), a0 + 0x10);
            if (FastVecDot(q, p) < 0.0f) {
                *(s16 *)(st + 0x29A) = next;
            }
            *(s32 *)(a0 + 0x98) = 0;
            *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
            if (a0[0x43] != math_random_int_below(2) + 1) {
                func_PAL_002A7E68(a0, math_random_int_below(2) + 1, math_random_int_below(0xA), 0x8);
            }
            a0[0xBC] = 0;
            break;
        }
        if (a0[0xBC] == 0) {
            if (*(s32 *)(st + 0x270) != -1 && IsPointInCuboid(g_hero_position, *(s32 *)(st + 0x270)) != 0) {
                a0[0xBC] = 1;
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                moby_set_table_entry_byte(a0, 0, 2);
            }
        } else {
            float d;
            u8 *pos;
            if (path_advance(a0, st + 0x230, *(s32 *)(st + 0x26C), (s16 *)(st + 0x29A),
                                  *(s16 *)(st + 0x29C), 0.2f) == 0) {
                moby_set_state(a0, 0xF, -1);
            }
            pos = a0 + 0x10;
            d = fast_vec_dist(pos, g_hero_position);
            if (d < 8.0f) {
                if (a0[0x43] != 1) {
                    func_PAL_002A7E68(a0, 1, 0, 0x8);
                }
                if (d < 2.0f) {
                    u8 *hit;
                    float reach;
                    qcopy(p, pos);
                    p[2] = p[2] + (*(float *)(st + 0x104) + *(float *)(st + 0x100));
                    reach = *(float *)(st + 0x100) + 0.2f;
                    coll_sweep_from_object(a0, p, 1, 0, 1, 0, reach, IntToFloat(D_001A7A00[0]) * 0.25f, 1.0f);
                    if (coll_test_point(p, 1, a0, *(float *)(st + 0x100) + 0.2f) != 0) {
                        hit = D_L18_001BFC18[0];
                        if (hit != 0 && *(s16 *)(hit + 0xAA) != 0xB69) {
                            *(s32 *)(st + 0x20) = 0;
                            vec_scale_to_length(q, a0 + 0xC0, -1.0f);
                            vec_add_random_offset(q, 0.3f);
                            func_PAL_002B1EE8(a0, st + 0x50, q, 2);
                            moby_set_state(a0, 0x11, 3);
                        }
                    }
                }
            }
        }
        break;
    case 15:
        if (flag_set_first_pending(a0) != 0) {
            vec_add_random_offset(st + 0x1A0, 0.060000002f);
            *(float *)(st + 0x1A8) = 0.10000001f;
            if (a0[0x43] != 0xD) {
                func_PAL_002A7E68(a0, 0xD, 0, 0x8);
            }
        } else if (*(u16 *)(a0 + 0x96) >= 0xFB) {
            func_PAL_002A7650(a0, 0, 1);
            protopet_end_action(a0, 0);
        }
        break;
    case 17: {
        s32 flags;
        float f;
        if (flag_set_first_pending(a0) != 0) {
            if (a0[0x42] == 0xC || a0[0x43] == 0xC) {
                *(u16 *)(a0 + 0x34) &= 0xEFFF;
            }
            if (a0[0x94] == 0xE) {
                FastVecScale(st + 0xD0, st + 0xD0, 3.0f);
            }
        }
        flags = moby_dispatch_action_by_kind(a0, st + 0x50);
        if (a0[0x94] == 0xE || a0[0x94] == 0xF) {
            f = moby_get_anim_value(a0);
            if (a0[0x42] == 0xB && 16.0f < f) {
                moby_set_state(a0, 0xF, -1);
            }
        }
        f = moby_get_anim_value(a0);
        if ((flags & 1) || (a0[0x42] == 0xC && 15.0f < f && math_random_int_below(0xF) == 0)) {
            func_PAL_002A7650(a0, 0, 1);
            protopet_end_action(a0, 0);
            break;
        }
        if (flags & 2) {
            u8 mode;
            *(u8 **)(st + 0x258) = 0;
            mode = a0[0x95];
            moby_set_state(a0, 0xC, 2);
            if (mode == 1) {
                moby_set_state(a0, 7, -1);
            }
        }
        break;
    }
    case 18:
        if (flag_set_first_pending(a0) != 0) {
            *(u16 *)(a0 + 0x34) &= 0xEFFF;
            if (a0[0x95] == 2) {
                if (a0[0x43] != 3) {
                    func_PAL_002A7E68(a0, 3, 0, 0x8);
                }
            }
            *(float *)(a0 + 0x48) = 1.0f;
        }
        if ((a0[0x60] & 2) || *(u16 *)(a0 + 0x96) >= 0x33) {
            *(s32 *)(st + 0x20) = 0;
            func_PAL_002A7650(a0, 0, 1);
            protopet_end_action(a0, 0);
        }
        break;
    case 0:
    default:
        break;
    }
}
