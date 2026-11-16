#include "names.h"
/* func_PAL_L13_0040F08C, the PAL copy of func_L13_0040A720: the same C, where blend frame counts are
   scaled by 5/6, the +0x240 timer reloads are scaled and its limit 300 becomes 250, func_002B60B0's
   arguments and func_00282F20's factors take PAL's values, and states 21 and 22 call
   func_PAL_L12_0040CBA0 unconditionally, as in USA v2.00. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* A 0x80-byte record of the level table at D_L13_001B2A0C; its point is at +0x30. */
typedef struct { u8 pad0[0x30]; TI128 point; u8 pad40[0x40]; } L13Cam;

extern char g_hero_state[];
extern float g_hero_position[];
extern u8 *g_hero_moby;
extern u8 *g_object_table_base __attribute__((section(".sdata")));
extern u8 *g_moby_slot_table __attribute__((section(".sdata")));
extern char g_collision_l13_result[];
extern s32 *g_guard_path_table[];
extern char g_str_guard_alt_msg_a[];
extern char g_str_guard_alt_msg_b[];
extern char g_str_guard_alt_msg_c[];
extern char g_str_guard_alt_msg_d[];
extern s32 g_current_map_index[] __attribute__((section(".sdata")));

extern void STUB_printf(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void SetDeathBits_pal(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int CollLine(void *, void *, int, void *, int);
extern int math_is_value_within_step_pal(void *, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int path_follow_nodes_pal(void *, void *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int moby_start_effect_from_entry(void *, float);
extern void part_queue_moby_for_glow(void *, int, void *);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
extern int rps_judge_round(void *);
extern int guard_alt_init_check_pal(void *);
extern void guard_alt_update_hit_timer(void *);
extern u8 *blast_projectile_spawn_pal(void *, void *, void *, int, float);
extern int moby_step_at_own_position_pal(void *);
extern int flag_set_second_pending(void *);
extern void moby_mark_spawned(void *);
extern int creature_move_along_ground_pal(char *, char *);
extern int AdvancePathWaypoint_pal(void *, void *);
extern void moby_turn_toward_hero_pal(void *);

/* The per-frame update of the second level-13 guard kind, built like func_L13_00406F18:
   the action states (+0x95), the animation states (+0x20), then the shared timer update. */
void guard_alt_update_pal(u8 *moby)
{
    float mat[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (guard_alt_init_check_pal(moby) != 0) {
        part_queue_moby_for_glow(moby, 0, 0);
    }
    switch (moby[0x95]) {
    case 0: {
        s32 flag;
        flag = *(s32 *)(vars + 0x250);
        if (flag == 1 && math_fast_float_d(vars + 0x248) != 0) {
            if (*(s32 *)(vars + 0x2A8) == 0 || ((Hero *)g_hero_state)->h[0x348 / 2] == flag) {
                *(s32 *)(vars + 0x288) = flag;
                moby_set_state(moby, 0x17, 2);
                if (moby[0x43] != 6) {
                    anim_start_blended_pal(moby, 6, 0, 0x8);
                }
                if (math_random_int_below(2) == flag) {
                    if (moby[0x43] != 7) {
                        anim_start_blended_pal(moby, 7, 0, 0x8);
                    }
                }
                if (*(s32 *)(vars + 0x268) != -1) {
                    moby_set_state(moby, 0x12, 2);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x294) != -1) {
                    moby_set_state(moby, 0xF, 2);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    u8 *linked = g_object_table_base + (*(s32 *)(vars + 0x2AC) << 8);
                    linked[0x20] = 3;
                    *(u8 **)(*(u8 **)(linked + 0x68) + 0xC) = moby;
                }
            }
        } else if (*(s64 *)(vars + 0x280) == 1 && math_fast_float_d(vars + 0x248) != 0) {
            if (*(s32 *)(vars + 0x278) != -1) {
                moby_set_state(moby, 0xE, -1);
                if (moby[0x43] != 3) {
                    anim_start_blended_pal(moby, 3, 0, 0x8);
                }
                *(s32 *)(vars + 0x284) = 1;
            }
        } else if (*(s32 *)(vars + 0x24C) != 0) {
            if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
                *(s32 *)(vars + 0x288) = 1;
                if (moby[0x43] != 0xF) {
                    anim_start_blended_pal(moby, 0xF, 0, 0x15);
                }
                moby_set_state(moby, 0x13, 2);
                if (*(s32 *)(vars + 0x268) != -1) {
                    moby_set_state(moby, 0x12, 2);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x294) != -1) {
                    moby_set_state(moby, 0xF, 2);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    u8 *linked = g_object_table_base + (*(s32 *)(vars + 0x2AC) << 8);
                    linked[0x20] = 3;
                    *(u8 **)(*(u8 **)(linked + 0x68) + 0xC) = moby;
                }
            }
            *(s32 *)(vars + 0x24C) = 0;
            if (*(s32 *)(vars + 0x240) < 0xFA) {
                *(s32 *)(vars + 0x240) = (math_random_int_range(0x1E0, 0x258) * 5 + 2) / 6;
            }
        }
        break;
    }
    case 8: {
        s32 flag;
        s32 i;
        u8 *linked;
        if (*(s32 *)(vars + 0x298) != 0 && (i = *(s32 *)(vars + 0x29C)) != -1) {
            linked = g_object_table_base + (i << 8);
            if (linked == 0 || linked[0x20] == 0xFE || linked[0x20] == 0xFD) {
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                *(u16 *)(*(u8 **)(vars + 0x25C) + 0x34) &= 0xFFBE;
                *(u16 *)(*(u8 **)(vars + 0x25C) + 0x34) |= 0x1000;
                *(s32 *)(*(u8 **)(vars + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(vars + 0x25C) + 0x24) + 0x10);
                moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
                *(s32 *)(vars + 0x298) = 0;
                if (*(s32 *)(vars + 0x2A0) != -1) {
                    moby_set_state(moby, 0x1B, 7);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0xC);
                    }
                } else {
                    if (moby[0x43] != 5) {
                        anim_start_blended_pal(moby, 5, 0, 0x8);
                    }
                    if (*(s32 *)(vars + 0x290) == 1) {
                        if (moby[0x43] != 0xC) {
                            anim_start_blended_pal(moby, 0xC, 0, 0x8);
                        }
                    }
                    moby_set_state(moby, 0x15, 2);
                }
            }
        } else {
            flag = *(s32 *)(vars + 0x250);
            if (flag == 1 && math_fast_float_d(vars + 0x248) != 0) {
                *(s32 *)(vars + 0x288) = flag;
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 0x8);
                }
                if (*(s32 *)(vars + 0x290) == flag) {
                    if (moby[0x43] != 0xC) {
                        anim_start_blended_pal(moby, 0xC, 0, 0x8);
                    }
                }
                moby_set_state(moby, 0x15, 2);
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                *(u16 *)(*(u8 **)(vars + 0x25C) + 0x34) &= 0xFFBE;
                *(u16 *)(*(u8 **)(vars + 0x25C) + 0x34) |= 0x1000;
                *(s32 *)(*(u8 **)(vars + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(vars + 0x25C) + 0x24) + 0x10);
                moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
            } else {
                flag = moby[0xBC];
                if (flag == 1) {
                    *(s32 *)(vars + 0x288) = flag;
                    if (moby[0x43] != 5) {
                        anim_start_blended_pal(moby, 5, 0, 0x8);
                    }
                    if (*(s32 *)(vars + 0x290) == flag) {
                        if (moby[0x43] != 0xC) {
                            anim_start_blended_pal(moby, 0xC, 0, 0x8);
                        }
                    }
                    moby_set_state(moby, 0x15, 2);
                    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                    *(u16 *)(*(u8 **)(vars + 0x25C) + 0x34) &= 0xFFBE;
                    *(u16 *)(*(u8 **)(vars + 0x25C) + 0x34) |= 0x1000;
                    *(s32 *)(*(u8 **)(vars + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(vars + 0x25C) + 0x24) + 0x10);
                    moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
                }
            }
        }
        break;
    }
    case 6: {
        u8 *linked;
        linked = g_object_table_base + (*(s32 *)(vars + 0x29C) << 8);
        if (linked == 0 || linked[0x20] == 0xFE || linked[0x20] == 0xFD || *(s32 *)(vars + 0x2B8) == 1) {
            *(s32 *)(vars + 0x298) = 0;
            if (*(s32 *)(vars + 0x2A0) != -1) {
                moby_set_state(moby, 0x1B, 7);
                if (moby[0x43] != 3) {
                    anim_start_blended_pal(moby, 3, 0, 0xC);
                }
            } else {
                moby_set_state(moby, 0x15, 2);
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 0x8);
                }
                if (*(s32 *)(vars + 0x290) == 1) {
                    if (moby[0x43] != 0xC) {
                        anim_start_blended_pal(moby, 0xC, 0, 0x8);
                    }
                }
            }
        }
        break;
    }
    case 4:
        moby_step_at_own_position_pal(moby);
        if (*(s32 *)(vars + 0x250) == 1) {
            moby_set_state(moby, 0x13, 5);
            if (moby[0x43] != 0xF) {
                anim_start_blended_pal(moby, 0xF, 0, 0x21);
            }
        }
        break;
    case 5:
        moby_step_at_own_position_pal(moby);
        if (*(s32 *)(vars + 0x250) != 1 && *(s32 *)(vars + 0x254) != 1 && moby[0x20] != 0x12) {
            moby_set_state(moby, 1, 4);
            if (moby[0x43] != 0xD) {
                anim_start_blended_pal(moby, 0xD, 0, 0x19);
            }
        }
        break;
    case 1:
        if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
            *(s32 *)(vars + 0x288) = 1;
            if (moby[0x43] != 0xF) {
                anim_start_blended_pal(moby, 0xF, 0, 0x15);
            }
            moby_set_state(moby, 0x13, 2);
            if (*(s32 *)(vars + 0x268) != -1) {
                moby_set_state(moby, 0x12, 2);
                if (moby[0x43] != 3) {
                    anim_start_blended_pal(moby, 3, 0, 0xC);
                }
            }
            if (*(s32 *)(vars + 0x294) != -1) {
                moby_set_state(moby, 0xF, 2);
                if (moby[0x43] != 3) {
                    anim_start_blended_pal(moby, 3, 0, 0xC);
                }
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                u8 *linked = g_object_table_base + (*(s32 *)(vars + 0x2AC) << 8);
                linked[0x20] = 3;
                *(u8 **)(*(u8 **)(linked + 0x68) + 0xC) = moby;
            }
        } else if (*(s32 *)(vars + 0x240) == 0) {
            moby_set_state(moby, 1, 0);
        }
        break;
    case 2: {
        s32 flag;
        if (flag_set_second_pending(moby) != 0) {
            moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.010053098f, 1.0053098f);
        }
        if (*(s32 *)(vars + 0x250) != 1 && *(s32 *)(vars + 0x254) != 1 && moby[0x20] != 0x12) {
            moby_set_state(moby, 0xD, 1);
            if (moby[0x43] != 0xD) {
                anim_start_blended_pal(moby, 0xD, 0, 0x19);
            }
            *(s32 *)(vars + 0x240) = (math_random_int_range(0x244, 0x258) * 5 + 2) / 6;
            flag = math_random_int_below(4);
            *(s32 *)(vars + 0x26C) = 0;
            *(s32 *)(vars + 0x274) = *(s32 *)(vars + 0x270) + flag;
        }
        break;
    }
    case 3: {
        s32 flag;
        flag = moby_dispatch_action_by_kind(moby, vars + 0x140);
        if (flag & 1) {
            u8 *child = *(u8 **)(vars + 0x25C);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xEA9) {
                moby_mark_spawned(child);
            }
            SetDeathBits_pal(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, 0);
            return;
        }
        if (flag & 2) {
            if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 0x8);
                }
                if (*(s32 *)(vars + 0x290) == 1) {
                    if (moby[0x43] != 0xC) {
                        anim_start_blended_pal(moby, 0xC, 0, 0x8);
                    }
                }
                moby_set_state(moby, 0x15, 2);
            } else {
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 0) {
                        anim_start_blended_pal(moby, 0, 0, 0x11);
                    }
                }
                if (math_random_int_below(5) == 1) {
                    if (moby[0x43] != 0xE) {
                        anim_start_blended_pal(moby, 0xE, 0, 0x19);
                    }
                }
                moby_set_state(moby, 0xD, 1);
                *(s32 *)(vars + 0x240) = (math_random_int_range(0x244, 0x258) * 5 + 2) / 6;
            }
            if (*(s32 *)(vars + 0x278) != -1 && *(s32 *)(vars + 0x288) == 0) {
                moby_set_state(moby, 0x10, -1);
                if (moby[0x43] != 3) {
                    anim_start_blended_pal(moby, 3, 0, 0x8);
                }
            }
            if (*(s32 *)(vars + 0x294) != -1) {
                moby_set_state(moby, 0xF, 2);
                if (moby[0x43] != 3) {
                    anim_start_blended_pal(moby, 3, 0, 0xC);
                }
            }
        }
        break;
    }
    }

    switch (moby[0x20]) {
    case 9:
        if (*(u16 *)(moby + 0x96) >= 0x38) {
            moby_set_state(moby, 0xA, -1);
            if (moby[0x43] != math_random_int_below(3) + 0x13) {
                anim_start_blended_pal(moby, math_random_int_below(3) + 0x13, 0, 2);
            }
            if (moby[0x43] == 0x13) {
                *(s32 *)(vars + 0x2C4) = 0;
                STUB_printf(g_str_guard_alt_msg_a);
            } else if (moby[0x43] == 0x15) {
                *(s32 *)(vars + 0x2C4) = 1;
                STUB_printf(g_str_guard_alt_msg_b);
            } else {
                *(s32 *)(vars + 0x2C4) = 2;
                STUB_printf(g_str_guard_alt_msg_c);
            }
        }
        break;
    case 12:
        if (*(u16 *)(moby + 0x96) >= 0x47) {
            moby_set_state(moby, 0xA, -1);
            if (moby[0x43] != math_random_int_below(3) + 0x13) {
                anim_start_blended_pal(moby, math_random_int_below(3) + 0x13, 0, 2);
            }
            if (moby[0x43] == 0x13) {
                *(s32 *)(vars + 0x2C4) = 0;
                STUB_printf(g_str_guard_alt_msg_a);
            } else if (moby[0x43] == 0x15) {
                *(s32 *)(vars + 0x2C4) = 1;
                STUB_printf(g_str_guard_alt_msg_b);
            } else {
                *(s32 *)(vars + 0x2C4) = 2;
                STUB_printf(g_str_guard_alt_msg_c);
            }
        }
        break;
    case 10: {
        s32 flag;
        if (*(u16 *)(moby + 0x96) >= 0x3D) {
            flag = rps_judge_round(moby);
            if (flag == 2) {
                moby_set_state(moby, 9, -1);
                if (moby[0x43] != 0x12) {
                    anim_start_blended_pal(moby, 0x12, 0, 2);
                }
            } else if (flag == 0) {
                moby_set_state(moby, 0xB, -1);
                if (moby[0x43] != 7) {
                    anim_start_blended_pal(moby, 7, 0, 0x8);
                }
            } else {
                moby_set_state(moby, 0xB, -1);
                if (moby[0x43] != 0x16) {
                    anim_start_blended_pal(moby, 0x16, 0, 0x8);
                }
            }
        }
        break;
    }
    case 11:
        if (*(u16 *)(moby + 0x96) >= 0x49) {
            moby_set_state(moby, 0xC, -1);
            if (moby[0x43] != 0x12) {
                anim_start_blended_pal(moby, 0x12, 0, 0xF);
            }
        }
        break;
    case 7:
        if (*(s32 *)(vars + 0x2A4) != 0) {
            if (AdvancePathWaypoint_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x2B0)]) != 0) {
                moby_set_state(moby, 8, -1);
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 0) {
                        anim_start_blended_pal(moby, 0, 0, 0x11);
                    }
                }
                if (math_random_int_below(5) == 1) {
                    if (moby[0x43] != 0xE) {
                        anim_start_blended_pal(moby, 0xE, 0, 0x19);
                    }
                }
            }
        } else {
            if (path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x2B0)]) != 0) {
                moby_set_state(moby, 8, -1);
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 0) {
                        anim_start_blended_pal(moby, 0, 0, 0x11);
                    }
                }
                if (math_random_int_below(5) == 1) {
                    if (moby[0x43] != 0xE) {
                        anim_start_blended_pal(moby, 0xE, 0, 0x19);
                    }
                }
            }
        }
        break;
    case 8: {
        s32 *path;
        float dist;
        if (moby[0x60] & 2) {
            path = g_guard_path_table[*(s32 *)(vars + 0x2B0)];
            dist = vec_distance_xy(moby + 0x10, path + 4);
            if (vec_distance_xy(moby + 0x10, path + *path * 4) < dist) {
                path_set_follower_nodes(moby, g_guard_path_table[*(s32 *)(vars + 0x2B0)], 0, *path - 1);
            } else {
                path_set_follower_nodes(moby, g_guard_path_table[*(s32 *)(vars + 0x2B0)], *path - 1, 0);
            }
            moby_set_state(moby, 7, -1);
            if (moby[0x43] != 2) {
                anim_start_blended_pal(moby, 2, 0, 0x11);
            }
        }
        break;
    }
    case 5:
        if (moby[0x60] & 2) {
            moby_set_state(moby, 6, 0);
            if (moby[0x43] != 0xD) {
                anim_start_blended_pal(moby, 0xD, 0, 0x21);
            }
        }
        break;
    case 4:
        if (moby[0x60] & 2) {
            moby_set_state(moby, 1, 0);
            if (moby[0x43] != 0xD) {
                anim_start_blended_pal(moby, 0xD, 0, 0x11);
            }
        }
        break;
    case 6: {
        u8 *linked = g_object_table_base + (*(s32 *)(vars + 0x264) << 8);
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(linked + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(linked + 0x14) - *(float *)(moby + 0x14)));
        break;
    }
    case 13:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0xD) {
                anim_start_blended_pal(moby, 0xD, 0, 0x8);
            }
            moby_set_state(moby, 1, -1);
        }
        break;
    case 27: {
        s32 flag;
        if (*(s32 *)(vars + 0x2A4) != 0) {
            flag = AdvancePathWaypoint_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x2A0)]);
        } else {
            flag = path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x2A0)]);
        }
        if (flag != 0 || vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x200) + 0x10) < 8.0f) {
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 0x8);
            }
            if (*(s32 *)(vars + 0x290) == 1) {
                if (moby[0x43] != 0xC) {
                    anim_start_blended_pal(moby, 0xC, 0, 0x8);
                }
            }
            moby_set_state(moby, 0x15, -1);
        }
        break;
    }
    case 14:
        moby_set_state(moby, 0x10, -1);
        if (moby[0x43] != 3) {
            anim_start_blended_pal(moby, 3, 0, 0x8);
        }
        break;
    case 16:
        if (path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x278)]) != 0) {
            *(s32 *)(vars + 0x288) = 1;
            moby_set_state(moby, 0x11, -1);
            if (moby[0x43] != 0xD) {
                anim_start_blended_pal(moby, 0xD, 0, 0x8);
            }
        }
        break;
    case 17:
        STUB_printf(g_str_guard_alt_msg_d);
        moby_set_state(moby, 1, -1);
        break;
    case 18: {
        s32 i;
        s32 j;
        if (flag_set_first_pending(moby) != 0 && *(s32 *)(vars + 0x2A8) != 0) {
            i = *(s32 *)(vars + 0x350);
            if (i != -1) {
                j = *(s32 *)(vars + 0x354);
                if (j != -1) {
                    u8 *base = g_object_table_base;
                    (base + (i << 8))[0x20] = 4;
                    (base + (j << 8))[0x20] = 4;
                    *(s32 *)(vars + 0x350) = -1;
                    *(s32 *)(vars + 0x354) = -1;
                }
            }
        }
        *(TI128 *)mat = ((L13Cam *)g_moby_slot_table)[*(s32 *)(vars + 0x268)].point;
        if (*(s32 *)(vars + 0x2A4) != 0) {
            creature_move_along_ground_pal(moby, mat);
        } else {
            moby_l01_turn_toward_target_pal(moby, mat);
        }
        if (vec_distance_xy(moby + 0x10, mat) < 0.5f) {
            moby_set_state(moby, 0x15, -1);
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 0xC);
            }
            if (*(s32 *)(vars + 0x290) == 1) {
                if (moby[0x43] != 0xC) {
                    anim_start_blended_pal(moby, 0xC, 0, 0x8);
                }
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                moby_set_state(moby, 0x18, -1);
                if (moby[0x43] != 0x10) {
                    anim_start_blended_pal(moby, 0x10, 0, 0x11);
                }
            }
        }
        break;
    }
    case 29:
        *(TI128 *)mat = *(TI128 *)(vars + 0x360);
        if (*(s32 *)(vars + 0x2A4) != 0) {
            creature_move_along_ground_pal(moby, mat);
        } else {
            moby_l01_turn_toward_target_pal(moby, mat);
        }
        if (vec_distance_xy(moby + 0x10, mat) < 0.5f) {
            moby_set_state(moby, 0x15, -1);
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 0xC);
            }
            if (*(s32 *)(vars + 0x290) == 1) {
                if (moby[0x43] != 0xC) {
                    anim_start_blended_pal(moby, 0xC, 0, 0x8);
                }
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                moby_set_state(moby, 0x18, -1);
                if (moby[0x43] != 0x10) {
                    anim_start_blended_pal(moby, 0x10, 0, 0x11);
                }
            }
        }
        break;
    case 15:
        if (*(s32 *)(vars + 0x2A4) != 0) {
            if (AdvancePathWaypoint_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x294)]) != 0) {
                moby_set_state(moby, 0x15, -1);
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 0x8);
                }
                if (*(s32 *)(vars + 0x290) == 1) {
                    if (moby[0x43] != 0xC) {
                        anim_start_blended_pal(moby, 0xC, 0, 0x8);
                    }
                }
                *(s32 *)(vars + 0x294) = -1;
            }
        } else if (path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x294)]) != 0
                   || vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x200) + 0x10) < 8.0f) {
            moby_set_state(moby, 0x15, -1);
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 0x8);
            }
            if (*(s32 *)(vars + 0x290) == 1) {
                if (moby[0x43] != 0xC) {
                    anim_start_blended_pal(moby, 0xC, 0, 0x8);
                }
            }
            *(s32 *)(vars + 0x294) = -1;
        }
        break;
    case 19:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 0x8);
            }
            if (*(s32 *)(vars + 0x290) == 1) {
                if (moby[0x43] != 0xC) {
                    anim_start_blended_pal(moby, 0xC, 0, 0x8);
                }
            }
            moby_set_state(moby, 0x15, -1);
        }
        break;
    case 25: {
        u8 *hit;
        if (FastDiffRots(*(float *)(moby + 0xF8),
                          mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                        *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14))) < 0.78539824f) {
            moby_transform_joint_to_world(moby, 2, mat);
            FastVecSub(vec, vars + 0x1F0, mat);
            vec_scale_to_length(vec, vec, 0.6f);
            if (CollLine(mat, vars + 0x1F0, 0, moby, 0) == 0) {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 0x8);
                }
                if (*(s32 *)(vars + 0x290) == 1) {
                    if (moby[0x43] != 0xC) {
                        anim_start_blended_pal(moby, 0xC, 0, 0x8);
                    }
                }
                moby_set_state(moby, 0x15, -1);
            } else {
                hit = *(u8 **)(g_collision_l13_result + 0x18);
                if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(vars + 0x200)
                                 || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                 || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x200
                                 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                    if (moby[0x43] != 5) {
                        anim_start_blended_pal(moby, 5, 0, 0x8);
                    }
                    if (*(s32 *)(vars + 0x290) == 1) {
                        if (moby[0x43] != 0xC) {
                            anim_start_blended_pal(moby, 0xC, 0, 0x8);
                        }
                    }
                    moby_set_state(moby, 0x15, -1);
                }
            }
        }
        if (moby[0x60] & 2) {
            if (moby[0x42] == 4) {
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 0) {
                        anim_start_blended_pal(moby, 0, 0, 0x11);
                    }
                }
            } else {
                if (moby[0x43] != 4) {
                    anim_start_blended_pal(moby, 4, 0, 0x11);
                }
            }
        }
        break;
    }
    case 21:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A4) != 0) {
            moby_turn_toward_hero_pal(moby);
        }
        if (math_is_value_within_step_pal(moby, 1.0f) != 0) {
            if (FastDiffRots(*(float *)(moby + 0xF8),
                              mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                            *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14))) < 0.78539824f) {
                moby_transform_joint_to_world(*(u8 **)(vars + 0x25C), 0, mat);
                FastVecSub(vec, vars + 0x1F0, mat);
                vec_scale_to_length(vec, vec, 0.6f);
                blast_projectile_spawn_pal(moby, vec, mat, 0, vars[0x34]);
                (*(s32 *)(vars + 0x26C))++;
            }
        }
        if (moby[0x60] & 2) {
            if (*(s32 *)(vars + 0x26C) <= 0) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 4) {
                    anim_start_blended_pal(moby, 4, 0, 0x8);
                }
            } else {
                s32 flag;
                moby_set_state(moby, 0x17, -1);
                if (moby[0x43] != 6) {
                    anim_start_blended_pal(moby, 6, 0, 0x8);
                }
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 7) {
                        anim_start_blended_pal(moby, 7, 0, 0x8);
                    }
                }
                flag = math_random_int_below(4);
                *(s32 *)(vars + 0x26C) = 0;
                *(s32 *)(vars + 0x274) = *(s32 *)(vars + 0x270) + flag;
            }
        }
        break;
    case 24:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A4) != 0) {
            moby_turn_toward_hero_pal(moby);
        }
        if (math_is_value_within_step_pal(moby, 1.0f) != 0) {
            if (FastDiffRots(*(float *)(moby + 0xF8),
                              mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                            *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14))) < 0.78539824f) {
                (*(s32 *)(vars + 0x26C))++;
                moby_transform_joint_to_world(*(u8 **)(vars + 0x25C), 0, mat);
                FastVecSub(vec, vars + 0x1F0, mat);
                vec_scale_to_length(vec, vec, 0.6f);
                blast_projectile_spawn_pal(moby, vec, mat, 0, vars[0x34]);
            }
        }
        if ((moby[0x60] & 2) && *(s32 *)(vars + 0x26C) > 0) {
            s32 flag;
            moby_set_state(moby, 0x17, -1);
            if (moby[0x43] != 6) {
                anim_start_blended_pal(moby, 6, 0, 0x8);
            }
            if (math_random_int_below(2) == 1) {
                if (moby[0x43] != 7) {
                    anim_start_blended_pal(moby, 7, 0, 0x8);
                }
            }
            flag = math_random_int_below(4);
            *(s32 *)(vars + 0x26C) = 0;
            *(s32 *)(vars + 0x274) = *(s32 *)(vars + 0x270) + flag;
        }
        break;
    case 22:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A4) != 0) {
            moby_turn_toward_hero_pal(moby);
        }
        if (math_is_value_within_step_pal(moby, 1.0f) != 0) {
            moby_transform_joint_to_world(*(u8 **)(vars + 0x25C), 0, mat);
            FastVecSub(vec, vars + 0x1F0, mat);
            vec_scale_to_length(vec, vec, 0.50000006f);
            blast_projectile_spawn_pal(moby, vec, mat, 0, vars[0x34]);
            (*(s32 *)(vars + 0x26C))++;
        }
        break;
    case 23:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (g_current_map_index[0] != 0x10) {
            if (moby[0x60] & 2) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 4) {
                    anim_start_blended_pal(moby, 4, 0, 0x8);
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    moby_set_state(moby, 0x18, -1);
                    if (moby[0x43] != 0x10) {
                        anim_start_blended_pal(moby, 0x10, 0, 0x11);
                    }
                }
                if (*(s32 *)(vars + 0x358) != 0 && vec_distance_xy(moby + 0x10, vars + 0x360) > 4.0f) {
                    moby_set_state(moby, 0x1D, -1);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0x8);
                    }
                }
            }
        } else {
            if (*(u16 *)(moby + 0x96) >= 0xB5) {
                moby_set_state(moby, 0x15, -1);
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 0x8);
                }
                if (*(s32 *)(vars + 0x290) == 1) {
                    if (moby[0x43] != 0xC) {
                        anim_start_blended_pal(moby, 0xC, 0, 0x8);
                    }
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    moby_set_state(moby, 0x18, -1);
                    if (moby[0x43] != 0x10) {
                        anim_start_blended_pal(moby, 0x10, 0, 0x11);
                    }
                }
            }
            if (moby[0x60] & 2) {
                if (moby[0x43] != 4) {
                    anim_start_blended_pal(moby, 4, 0, 4);
                }
            }
        }
        break;
    case 1:
    default:
        break;
    }
    guard_alt_update_hit_timer(moby);
}
