/* func_US2_L13_0040BC84, the USA v2.00 copy of func_L13_0040A720: the same C, except that
   states 21 and 22 call func_L12_00408050 unconditionally, without the func_002761F8 test
   and its hit-object fallback. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* A 0x80-byte record of the level table at D_L13_001B2A0C; its point is at +0x30. */
typedef struct { u8 pad0[0x30]; TI128 v; u8 pad40[0x40]; } L13Cam;

extern char g_hero_state[];
extern float g_hero_position[];
extern u8 *g_hero_moby;
extern u8 *D_L13_001B291C __attribute__((section(".sdata")));
extern u8 *D_L13_001B2A0C __attribute__((section(".sdata")));
extern char D_L13_001BFD00[];
extern s32 *D_L13_001FE580[];
extern char D_L13_001B11F8[];
extern char D_L13_001B1200[];
extern char D_L13_001B1208[];
extern char D_L13_001B1218[];
extern s32 g_current_map_index[] __attribute__((section(".sdata")));

extern void STUB_printf(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void SetDeathBits(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int CollLine(void *, void *, int, void *, int);
extern int math_is_value_within_step(void *, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int path_follow_nodes(void *, void *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int moby_l01_turn_toward_target(void *, void *);
extern int moby_start_effect_from_entry(void *, float);
extern void part_queue_moby_for_glow(void *, int, void *);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
extern int rps_judge_round(void *);
extern int guard_alt_init_check(void *);
extern void guard_alt_update_hit_timer(void *);
extern u8 *blast_projectile_spawn(void *, void *, void *, int, float);
extern int moby_step_at_own_position(void *);
extern int flag_set_second_pending(void *);
extern void moby_mark_spawned(void *);
extern int creature_move_along_ground(char *, char *);
extern int AdvancePathWaypoint(void *, void *);
extern void moby_turn_toward_hero(void *);

/* The per-frame update of the second level-13 guard kind, built like func_L13_00406F18:
   the action states (+0x95), the animation states (+0x20), then the shared timer update. */
void func_US2_L13_0040BC84(u8 *a0)
{
    float m[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    u8 *st;

    st = *(u8 **)(a0 + 0x68);
    if (guard_alt_init_check(a0) != 0) {
        part_queue_moby_for_glow(a0, 0, 0);
    }
    switch (a0[0x95]) {
    case 0: {
        s32 r;
        r = *(s32 *)(st + 0x250);
        if (r == 1 && math_fast_float_d(st + 0x248) != 0) {
            if (*(s32 *)(st + 0x2A8) == 0 || ((Hero *)g_hero_state)->h[0x348 / 2] == r) {
                *(s32 *)(st + 0x288) = r;
                moby_set_state(a0, 0x17, 2);
                if (a0[0x43] != 6) {
                    anim_start_blended(a0, 6, 0, 0xA);
                }
                if (math_random_int_below(2) == r) {
                    if (a0[0x43] != 7) {
                        anim_start_blended(a0, 7, 0, 0xA);
                    }
                }
                if (*(s32 *)(st + 0x268) != -1) {
                    moby_set_state(a0, 0x12, 2);
                    if (a0[0x43] != 3) {
                        anim_start_blended(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x294) != -1) {
                    moby_set_state(a0, 0xF, 2);
                    if (a0[0x43] != 3) {
                        anim_start_blended(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
                }
            }
        } else if (*(s64 *)(st + 0x280) == 1 && math_fast_float_d(st + 0x248) != 0) {
            if (*(s32 *)(st + 0x278) != -1) {
                moby_set_state(a0, 0xE, -1);
                if (a0[0x43] != 3) {
                    anim_start_blended(a0, 3, 0, 0xA);
                }
                *(s32 *)(st + 0x284) = 1;
            }
        } else if (*(s32 *)(st + 0x24C) != 0) {
            if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
                *(s32 *)(st + 0x288) = 1;
                if (a0[0x43] != 0xF) {
                    anim_start_blended(a0, 0xF, 0, 0x19);
                }
                moby_set_state(a0, 0x13, 2);
                if (*(s32 *)(st + 0x268) != -1) {
                    moby_set_state(a0, 0x12, 2);
                    if (a0[0x43] != 3) {
                        anim_start_blended(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x294) != -1) {
                    moby_set_state(a0, 0xF, 2);
                    if (a0[0x43] != 3) {
                        anim_start_blended(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
                }
            }
            *(s32 *)(st + 0x24C) = 0;
            if (*(s32 *)(st + 0x240) < 0x12C) {
                *(s32 *)(st + 0x240) = math_random_int_range(0x1E0, 0x258);
            }
        }
        break;
    }
    case 8: {
        s32 r;
        s32 i;
        u8 *e;
        if (*(s32 *)(st + 0x298) != 0 && (i = *(s32 *)(st + 0x29C)) != -1) {
            e = D_L13_001B291C + (i << 8);
            if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD) {
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) &= 0xFFBE;
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) |= 0x1000;
                *(s32 *)(*(u8 **)(st + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(st + 0x25C) + 0x24) + 0x10);
                moby_fuse_linked_objects(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
                *(s32 *)(st + 0x298) = 0;
                if (*(s32 *)(st + 0x2A0) != -1) {
                    moby_set_state(a0, 0x1B, 7);
                    if (a0[0x43] != 3) {
                        anim_start_blended(a0, 3, 0, 0xF);
                    }
                } else {
                    if (a0[0x43] != 5) {
                        anim_start_blended(a0, 5, 0, 0xA);
                    }
                    if (*(s32 *)(st + 0x290) == 1) {
                        if (a0[0x43] != 0xC) {
                            anim_start_blended(a0, 0xC, 0, 0xA);
                        }
                    }
                    moby_set_state(a0, 0x15, 2);
                }
            }
        } else {
            r = *(s32 *)(st + 0x250);
            if (r == 1 && math_fast_float_d(st + 0x248) != 0) {
                *(s32 *)(st + 0x288) = r;
                if (a0[0x43] != 5) {
                    anim_start_blended(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == r) {
                    if (a0[0x43] != 0xC) {
                        anim_start_blended(a0, 0xC, 0, 0xA);
                    }
                }
                moby_set_state(a0, 0x15, 2);
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) &= 0xFFBE;
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) |= 0x1000;
                *(s32 *)(*(u8 **)(st + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(st + 0x25C) + 0x24) + 0x10);
                moby_fuse_linked_objects(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
            } else {
                r = a0[0xBC];
                if (r == 1) {
                    *(s32 *)(st + 0x288) = r;
                    if (a0[0x43] != 5) {
                        anim_start_blended(a0, 5, 0, 0xA);
                    }
                    if (*(s32 *)(st + 0x290) == r) {
                        if (a0[0x43] != 0xC) {
                            anim_start_blended(a0, 0xC, 0, 0xA);
                        }
                    }
                    moby_set_state(a0, 0x15, 2);
                    *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                    *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) &= 0xFFBE;
                    *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) |= 0x1000;
                    *(s32 *)(*(u8 **)(st + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(st + 0x25C) + 0x24) + 0x10);
                    moby_fuse_linked_objects(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
                }
            }
        }
        break;
    }
    case 6: {
        u8 *e;
        e = D_L13_001B291C + (*(s32 *)(st + 0x29C) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD || *(s32 *)(st + 0x2B8) == 1) {
            *(s32 *)(st + 0x298) = 0;
            if (*(s32 *)(st + 0x2A0) != -1) {
                moby_set_state(a0, 0x1B, 7);
                if (a0[0x43] != 3) {
                    anim_start_blended(a0, 3, 0, 0xF);
                }
            } else {
                moby_set_state(a0, 0x15, 2);
                if (a0[0x43] != 5) {
                    anim_start_blended(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        anim_start_blended(a0, 0xC, 0, 0xA);
                    }
                }
            }
        }
        break;
    }
    case 4:
        moby_step_at_own_position(a0);
        if (*(s32 *)(st + 0x250) == 1) {
            moby_set_state(a0, 0x13, 5);
            if (a0[0x43] != 0xF) {
                anim_start_blended(a0, 0xF, 0, 0x28);
            }
        }
        break;
    case 5:
        moby_step_at_own_position(a0);
        if (*(s32 *)(st + 0x250) != 1 && *(s32 *)(st + 0x254) != 1 && a0[0x20] != 0x12) {
            moby_set_state(a0, 1, 4);
            if (a0[0x43] != 0xD) {
                anim_start_blended(a0, 0xD, 0, 0x1E);
            }
        }
        break;
    case 1:
        if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
            *(s32 *)(st + 0x288) = 1;
            if (a0[0x43] != 0xF) {
                anim_start_blended(a0, 0xF, 0, 0x19);
            }
            moby_set_state(a0, 0x13, 2);
            if (*(s32 *)(st + 0x268) != -1) {
                moby_set_state(a0, 0x12, 2);
                if (a0[0x43] != 3) {
                    anim_start_blended(a0, 3, 0, 0xF);
                }
            }
            if (*(s32 *)(st + 0x294) != -1) {
                moby_set_state(a0, 0xF, 2);
                if (a0[0x43] != 3) {
                    anim_start_blended(a0, 3, 0, 0xF);
                }
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                e[0x20] = 3;
                *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
            }
        } else if (*(s32 *)(st + 0x240) == 0) {
            moby_set_state(a0, 1, 0);
        }
        break;
    case 2: {
        s32 r;
        if (flag_set_second_pending(a0) != 0) {
            moby_set_controller_speed_limits(a0, 0.0033333334f, 0.10000001f, 0.006981318f, 0.8377582f);
        }
        if (*(s32 *)(st + 0x250) != 1 && *(s32 *)(st + 0x254) != 1 && a0[0x20] != 0x12) {
            moby_set_state(a0, 0xD, 1);
            if (a0[0x43] != 0xD) {
                anim_start_blended(a0, 0xD, 0, 0x1E);
            }
            *(s32 *)(st + 0x240) = math_random_int_range(0x244, 0x258);
            r = math_random_int_below(4);
            *(s32 *)(st + 0x26C) = 0;
            *(s32 *)(st + 0x274) = *(s32 *)(st + 0x270) + r;
        }
        break;
    }
    case 3: {
        s32 r;
        r = moby_dispatch_action_by_kind(a0, st + 0x140);
        if (r & 1) {
            u8 *p = *(u8 **)(st + 0x25C);
            if (p != 0 && *(s16 *)(p + 0xAA) == 0xEA9) {
                moby_mark_spawned(p);
            }
            SetDeathBits(a0, 0, 3);
            part_queue_moby_for_glow(a0, 0, 0);
            return;
        }
        if (r & 2) {
            if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
                if (a0[0x43] != 5) {
                    anim_start_blended(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        anim_start_blended(a0, 0xC, 0, 0xA);
                    }
                }
                moby_set_state(a0, 0x15, 2);
            } else {
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        anim_start_blended(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        anim_start_blended(a0, 0, 0, 0x14);
                    }
                }
                if (math_random_int_below(5) == 1) {
                    if (a0[0x43] != 0xE) {
                        anim_start_blended(a0, 0xE, 0, 0x1E);
                    }
                }
                moby_set_state(a0, 0xD, 1);
                *(s32 *)(st + 0x240) = math_random_int_range(0x244, 0x258);
            }
            if (*(s32 *)(st + 0x278) != -1 && *(s32 *)(st + 0x288) == 0) {
                moby_set_state(a0, 0x10, -1);
                if (a0[0x43] != 3) {
                    anim_start_blended(a0, 3, 0, 0xA);
                }
            }
            if (*(s32 *)(st + 0x294) != -1) {
                moby_set_state(a0, 0xF, 2);
                if (a0[0x43] != 3) {
                    anim_start_blended(a0, 3, 0, 0xF);
                }
            }
        }
        break;
    }
    }

    switch (a0[0x20]) {
    case 9:
        if (*(u16 *)(a0 + 0x96) >= 0x38) {
            moby_set_state(a0, 0xA, -1);
            if (a0[0x43] != math_random_int_below(3) + 0x13) {
                anim_start_blended(a0, math_random_int_below(3) + 0x13, 0, 3);
            }
            if (a0[0x43] == 0x13) {
                *(s32 *)(st + 0x2C4) = 0;
                STUB_printf(D_L13_001B11F8);
            } else if (a0[0x43] == 0x15) {
                *(s32 *)(st + 0x2C4) = 1;
                STUB_printf(D_L13_001B1200);
            } else {
                *(s32 *)(st + 0x2C4) = 2;
                STUB_printf(D_L13_001B1208);
            }
        }
        break;
    case 12:
        if (*(u16 *)(a0 + 0x96) >= 0x47) {
            moby_set_state(a0, 0xA, -1);
            if (a0[0x43] != math_random_int_below(3) + 0x13) {
                anim_start_blended(a0, math_random_int_below(3) + 0x13, 0, 3);
            }
            if (a0[0x43] == 0x13) {
                *(s32 *)(st + 0x2C4) = 0;
                STUB_printf(D_L13_001B11F8);
            } else if (a0[0x43] == 0x15) {
                *(s32 *)(st + 0x2C4) = 1;
                STUB_printf(D_L13_001B1200);
            } else {
                *(s32 *)(st + 0x2C4) = 2;
                STUB_printf(D_L13_001B1208);
            }
        }
        break;
    case 10: {
        s32 r;
        if (*(u16 *)(a0 + 0x96) >= 0x3D) {
            r = rps_judge_round(a0);
            if (r == 2) {
                moby_set_state(a0, 9, -1);
                if (a0[0x43] != 0x12) {
                    anim_start_blended(a0, 0x12, 0, 3);
                }
            } else if (r == 0) {
                moby_set_state(a0, 0xB, -1);
                if (a0[0x43] != 7) {
                    anim_start_blended(a0, 7, 0, 0xA);
                }
            } else {
                moby_set_state(a0, 0xB, -1);
                if (a0[0x43] != 0x16) {
                    anim_start_blended(a0, 0x16, 0, 0xA);
                }
            }
        }
        break;
    }
    case 11:
        if (*(u16 *)(a0 + 0x96) >= 0x49) {
            moby_set_state(a0, 0xC, -1);
            if (a0[0x43] != 0x12) {
                anim_start_blended(a0, 0x12, 0, 0x12);
            }
        }
        break;
    case 7:
        if (*(s32 *)(st + 0x2A4) != 0) {
            if (AdvancePathWaypoint(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)]) != 0) {
                moby_set_state(a0, 8, -1);
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        anim_start_blended(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        anim_start_blended(a0, 0, 0, 0x14);
                    }
                }
                if (math_random_int_below(5) == 1) {
                    if (a0[0x43] != 0xE) {
                        anim_start_blended(a0, 0xE, 0, 0x1E);
                    }
                }
            }
        } else {
            if (path_follow_nodes(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)]) != 0) {
                moby_set_state(a0, 8, -1);
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        anim_start_blended(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        anim_start_blended(a0, 0, 0, 0x14);
                    }
                }
                if (math_random_int_below(5) == 1) {
                    if (a0[0x43] != 0xE) {
                        anim_start_blended(a0, 0xE, 0, 0x1E);
                    }
                }
            }
        }
        break;
    case 8: {
        s32 *path;
        float d;
        if (a0[0x60] & 2) {
            path = D_L13_001FE580[*(s32 *)(st + 0x2B0)];
            d = vec_distance_xy(a0 + 0x10, path + 4);
            if (vec_distance_xy(a0 + 0x10, path + *path * 4) < d) {
                path_set_follower_nodes(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)], 0, *path - 1);
            } else {
                path_set_follower_nodes(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)], *path - 1, 0);
            }
            moby_set_state(a0, 7, -1);
            if (a0[0x43] != 2) {
                anim_start_blended(a0, 2, 0, 0x14);
            }
        }
        break;
    }
    case 5:
        if (a0[0x60] & 2) {
            moby_set_state(a0, 6, 0);
            if (a0[0x43] != 0xD) {
                anim_start_blended(a0, 0xD, 0, 0x28);
            }
        }
        break;
    case 4:
        if (a0[0x60] & 2) {
            moby_set_state(a0, 1, 0);
            if (a0[0x43] != 0xD) {
                anim_start_blended(a0, 0xD, 0, 0x14);
            }
        }
        break;
    case 6: {
        u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x264) << 8);
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(e + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(e + 0x14) - *(float *)(a0 + 0x14)));
        break;
    }
    case 13:
        if (a0[0x60] & 2) {
            if (a0[0x43] != 0xD) {
                anim_start_blended(a0, 0xD, 0, 0xA);
            }
            moby_set_state(a0, 1, -1);
        }
        break;
    case 27: {
        s32 r;
        if (*(s32 *)(st + 0x2A4) != 0) {
            r = AdvancePathWaypoint(a0, D_L13_001FE580[*(s32 *)(st + 0x2A0)]);
        } else {
            r = path_follow_nodes(a0, D_L13_001FE580[*(s32 *)(st + 0x2A0)]);
        }
        if (r != 0 || vec_distance_xy(a0 + 0x10, *(u8 **)(st + 0x200) + 0x10) < 8.0f) {
            if (a0[0x43] != 5) {
                anim_start_blended(a0, 5, 0, 0xA);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    anim_start_blended(a0, 0xC, 0, 0xA);
                }
            }
            moby_set_state(a0, 0x15, -1);
        }
        break;
    }
    case 14:
        moby_set_state(a0, 0x10, -1);
        if (a0[0x43] != 3) {
            anim_start_blended(a0, 3, 0, 0xA);
        }
        break;
    case 16:
        if (path_follow_nodes(a0, D_L13_001FE580[*(s32 *)(st + 0x278)]) != 0) {
            *(s32 *)(st + 0x288) = 1;
            moby_set_state(a0, 0x11, -1);
            if (a0[0x43] != 0xD) {
                anim_start_blended(a0, 0xD, 0, 0xA);
            }
        }
        break;
    case 17:
        STUB_printf(D_L13_001B1218);
        moby_set_state(a0, 1, -1);
        break;
    case 18: {
        s32 i;
        s32 j;
        if (flag_set_first_pending(a0) != 0 && *(s32 *)(st + 0x2A8) != 0) {
            i = *(s32 *)(st + 0x350);
            if (i != -1) {
                j = *(s32 *)(st + 0x354);
                if (j != -1) {
                    u8 *base = D_L13_001B291C;
                    (base + (i << 8))[0x20] = 4;
                    (base + (j << 8))[0x20] = 4;
                    *(s32 *)(st + 0x350) = -1;
                    *(s32 *)(st + 0x354) = -1;
                }
            }
        }
        *(TI128 *)m = ((L13Cam *)D_L13_001B2A0C)[*(s32 *)(st + 0x268)].v;
        if (*(s32 *)(st + 0x2A4) != 0) {
            creature_move_along_ground(a0, m);
        } else {
            moby_l01_turn_toward_target(a0, m);
        }
        if (vec_distance_xy(a0 + 0x10, m) < 0.5f) {
            moby_set_state(a0, 0x15, -1);
            if (a0[0x43] != 5) {
                anim_start_blended(a0, 5, 0, 0xF);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    anim_start_blended(a0, 0xC, 0, 0xA);
                }
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                moby_set_state(a0, 0x18, -1);
                if (a0[0x43] != 0x10) {
                    anim_start_blended(a0, 0x10, 0, 0x14);
                }
            }
        }
        break;
    }
    case 29:
        *(TI128 *)m = *(TI128 *)(st + 0x360);
        if (*(s32 *)(st + 0x2A4) != 0) {
            creature_move_along_ground(a0, m);
        } else {
            moby_l01_turn_toward_target(a0, m);
        }
        if (vec_distance_xy(a0 + 0x10, m) < 0.5f) {
            moby_set_state(a0, 0x15, -1);
            if (a0[0x43] != 5) {
                anim_start_blended(a0, 5, 0, 0xF);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    anim_start_blended(a0, 0xC, 0, 0xA);
                }
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                moby_set_state(a0, 0x18, -1);
                if (a0[0x43] != 0x10) {
                    anim_start_blended(a0, 0x10, 0, 0x14);
                }
            }
        }
        break;
    case 15:
        if (*(s32 *)(st + 0x2A4) != 0) {
            if (AdvancePathWaypoint(a0, D_L13_001FE580[*(s32 *)(st + 0x294)]) != 0) {
                moby_set_state(a0, 0x15, -1);
                if (a0[0x43] != 5) {
                    anim_start_blended(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        anim_start_blended(a0, 0xC, 0, 0xA);
                    }
                }
                *(s32 *)(st + 0x294) = -1;
            }
        } else if (path_follow_nodes(a0, D_L13_001FE580[*(s32 *)(st + 0x294)]) != 0
                   || vec_distance_xy(a0 + 0x10, *(u8 **)(st + 0x200) + 0x10) < 8.0f) {
            moby_set_state(a0, 0x15, -1);
            if (a0[0x43] != 5) {
                anim_start_blended(a0, 5, 0, 0xA);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    anim_start_blended(a0, 0xC, 0, 0xA);
                }
            }
            *(s32 *)(st + 0x294) = -1;
        }
        break;
    case 19:
        if (a0[0x60] & 2) {
            if (a0[0x43] != 5) {
                anim_start_blended(a0, 5, 0, 0xA);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    anim_start_blended(a0, 0xC, 0, 0xA);
                }
            }
            moby_set_state(a0, 0x15, -1);
        }
        break;
    case 25: {
        u8 *hit;
        if (FastDiffRots(*(float *)(a0 + 0xF8),
                          mat_fast_helper_a(*(float *)(st + 0x1F0) - *(float *)(a0 + 0x10),
                                        *(float *)(st + 0x1F4) - *(float *)(a0 + 0x14))) < 0.78539824f) {
            moby_transform_joint_to_world(a0, 2, m);
            FastVecSub(v, st + 0x1F0, m);
            vec_scale_to_length(v, v, 0.5f);
            if (CollLine(m, st + 0x1F0, 0, a0, 0) == 0) {
                if (a0[0x43] != 5) {
                    anim_start_blended(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        anim_start_blended(a0, 0xC, 0, 0xA);
                    }
                }
                moby_set_state(a0, 0x15, -1);
            } else {
                hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(st + 0x200)
                                 || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                 || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x200
                                 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                    if (a0[0x43] != 5) {
                        anim_start_blended(a0, 5, 0, 0xA);
                    }
                    if (*(s32 *)(st + 0x290) == 1) {
                        if (a0[0x43] != 0xC) {
                            anim_start_blended(a0, 0xC, 0, 0xA);
                        }
                    }
                    moby_set_state(a0, 0x15, -1);
                }
            }
        }
        if (a0[0x60] & 2) {
            if (a0[0x42] == 4) {
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        anim_start_blended(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        anim_start_blended(a0, 0, 0, 0x14);
                    }
                }
            } else {
                if (a0[0x43] != 4) {
                    anim_start_blended(a0, 4, 0, 0x14);
                }
            }
        }
        break;
    }
    case 21:
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A4) != 0) {
            moby_turn_toward_hero(a0);
        }
        if (math_is_value_within_step(a0, 1.0f) != 0) {
            if (FastDiffRots(*(float *)(a0 + 0xF8),
                              mat_fast_helper_a(*(float *)(st + 0x1F0) - *(float *)(a0 + 0x10),
                                            *(float *)(st + 0x1F4) - *(float *)(a0 + 0x14))) < 0.78539824f) {
                moby_transform_joint_to_world(*(u8 **)(st + 0x25C), 0, m);
                FastVecSub(v, st + 0x1F0, m);
                vec_scale_to_length(v, v, 0.5f);
                blast_projectile_spawn(a0, v, m, 0, st[0x34]);
                (*(s32 *)(st + 0x26C))++;
            }
        }
        if (a0[0x60] & 2) {
            if (*(s32 *)(st + 0x26C) <= 0) {
                moby_set_state(a0, 0x19, -1);
                if (a0[0x43] != 4) {
                    anim_start_blended(a0, 4, 0, 0xA);
                }
            } else {
                s32 r;
                moby_set_state(a0, 0x17, -1);
                if (a0[0x43] != 6) {
                    anim_start_blended(a0, 6, 0, 0xA);
                }
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 7) {
                        anim_start_blended(a0, 7, 0, 0xA);
                    }
                }
                r = math_random_int_below(4);
                *(s32 *)(st + 0x26C) = 0;
                *(s32 *)(st + 0x274) = *(s32 *)(st + 0x270) + r;
            }
        }
        break;
    case 24:
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A4) != 0) {
            moby_turn_toward_hero(a0);
        }
        if (math_is_value_within_step(a0, 1.0f) != 0) {
            if (FastDiffRots(*(float *)(a0 + 0xF8),
                              mat_fast_helper_a(*(float *)(st + 0x1F0) - *(float *)(a0 + 0x10),
                                            *(float *)(st + 0x1F4) - *(float *)(a0 + 0x14))) < 0.78539824f) {
                (*(s32 *)(st + 0x26C))++;
                moby_transform_joint_to_world(*(u8 **)(st + 0x25C), 0, m);
                FastVecSub(v, st + 0x1F0, m);
                vec_scale_to_length(v, v, 0.5f);
                blast_projectile_spawn(a0, v, m, 0, st[0x34]);
            }
        }
        if ((a0[0x60] & 2) && *(s32 *)(st + 0x26C) > 0) {
            s32 r;
            moby_set_state(a0, 0x17, -1);
            if (a0[0x43] != 6) {
                anim_start_blended(a0, 6, 0, 0xA);
            }
            if (math_random_int_below(2) == 1) {
                if (a0[0x43] != 7) {
                    anim_start_blended(a0, 7, 0, 0xA);
                }
            }
            r = math_random_int_below(4);
            *(s32 *)(st + 0x26C) = 0;
            *(s32 *)(st + 0x274) = *(s32 *)(st + 0x270) + r;
        }
        break;
    case 22:
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A4) != 0) {
            moby_turn_toward_hero(a0);
        }
        if (math_is_value_within_step(a0, 1.0f) != 0) {
            moby_transform_joint_to_world(*(u8 **)(st + 0x25C), 0, m);
            FastVecSub(v, st + 0x1F0, m);
            vec_scale_to_length(v, v, 0.4166667f);
            blast_projectile_spawn(a0, v, m, 0, st[0x34]);
            (*(s32 *)(st + 0x26C))++;
        }
        break;
    case 23:
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (g_current_map_index[0] != 0x10) {
            if (a0[0x60] & 2) {
                moby_set_state(a0, 0x19, -1);
                if (a0[0x43] != 4) {
                    anim_start_blended(a0, 4, 0, 0xA);
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    moby_set_state(a0, 0x18, -1);
                    if (a0[0x43] != 0x10) {
                        anim_start_blended(a0, 0x10, 0, 0x14);
                    }
                }
                if (*(s32 *)(st + 0x358) != 0 && vec_distance_xy(a0 + 0x10, st + 0x360) > 4.0f) {
                    moby_set_state(a0, 0x1D, -1);
                    if (a0[0x43] != 3) {
                        anim_start_blended(a0, 3, 0, 0xA);
                    }
                }
            }
        } else {
            if (*(u16 *)(a0 + 0x96) >= 0xB5) {
                moby_set_state(a0, 0x15, -1);
                if (a0[0x43] != 5) {
                    anim_start_blended(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        anim_start_blended(a0, 0xC, 0, 0xA);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    moby_set_state(a0, 0x18, -1);
                    if (a0[0x43] != 0x10) {
                        anim_start_blended(a0, 0x10, 0, 0x14);
                    }
                }
            }
            if (a0[0x60] & 2) {
                if (a0[0x43] != 4) {
                    anim_start_blended(a0, 4, 0, 5);
                }
            }
        }
        break;
    case 1:
    default:
        break;
    }
    guard_alt_update_hit_timer(a0);
}
