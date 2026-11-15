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
extern char D_L13_001B11C0[];
extern char D_L13_001B11C8[];
extern char D_L13_001B11D0[];
extern char D_L13_001B11D8[];
extern char D_L13_001B11E8[];

extern void STUB_printf(void *);
extern void moby_transform_joint_point(void *, int, void *);
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
extern int moby_turn_toward_target_and_step(void *, void *, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int path_follow_nodes(void *, void *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int moby_l01_turn_toward_target(void *, void *);
extern int moby_start_effect_from_entry(void *, float);
extern void part_queue_moby_for_glow(void *, int, void *);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
extern int path_check_entry_for_moby(void *, int);
extern int rps_judge(void *);
extern int guard_init_check(void *);
extern int creature_move_along_ground(char *, char *);
extern int AdvancePathWaypoint(void *, void *);
extern void moby_turn_toward_hero(void *);
extern void guard_update_hit_timer(void *);
extern u8 *SpawnEA7Moby(void *, void *, void *, int, float);

/* The per-frame update of the level-13 guard: the action states (+0x95) first, then the
   animation states (+0x20), then the shared timer update. */
void guard_l13_update(u8 *moby)
{
    float m[16] __attribute__((aligned(16)));
    float v[4];
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (guard_init_check(moby) != 0) {
        part_queue_moby_for_glow(moby, 0, 0);
    }
    switch (moby[0x95]) {
    case 0: {
        s32 r;
        r = *(s32 *)(vars + 0x250);
        if (r == 1 && math_fast_float_d(vars + 0x248) != 0) {
            if (*(s32 *)(vars + 0x2A8) == 0 || ((Hero *)g_hero_state)->h[0x348 / 2] == r) {
                *(s32 *)(vars + 0x26C) = r;
                moby_set_state(moby, 0x18, 2);
                if (moby[0x43] != 6) {
                    anim_start_blended(moby, 6, 0, 0xA);
                }
                if (*(s32 *)(vars + 0x25C) != -1) {
                    moby_set_state(moby, 0xF, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended(moby, 0xD, 0, 0xF);
                    }
                }
                if (*(s32 *)(vars + 0x290) != -1) {
                    moby_set_state(moby, 0xE, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended(moby, 0xD, 0, 0xF);
                    }
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(vars + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = moby;
                }
                if (*(s32 *)(vars + 0x2BC) != 0) {
                    moby_set_state(moby, 0xA, 7);
                    if (moby[0x43] != 3) {
                        anim_start_blended(moby, 3, 0, 0xF);
                    }
                    moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.006981318f, 0.8377582f);
                }
            }
        } else if (*(s64 *)(vars + 0x278) == 1) {
            if (*(s32 *)(vars + 0x270) != -1) {
                moby_set_state(moby, 0x10, -1);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xA);
                }
                *(s32 *)(vars + 0x27C) = 1;
            }
        } else if (*(s32 *)(vars + 0x24C) != 0) {
            if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
                *(s32 *)(vars + 0x26C) = 1;
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, 0xA);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
                if (*(s32 *)(vars + 0x25C) != -1) {
                    moby_set_state(moby, 0xF, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended(moby, 0xD, 0, 0xF);
                    }
                }
                if (*(s32 *)(vars + 0x290) != -1) {
                    moby_set_state(moby, 0xE, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended(moby, 0xD, 0, 0xF);
                    }
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(vars + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = moby;
                }
                if (*(s32 *)(vars + 0x2BC) != 0) {
                    moby_set_state(moby, 0xA, 7);
                    if (moby[0x43] != 3) {
                        anim_start_blended(moby, 3, 0, 0xF);
                    }
                    moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.006981318f, 0.8377582f);
                }
            }
            *(s32 *)(vars + 0x24C) = 0;
            if (*(s32 *)(vars + 0x240) < 0x12C) {
                *(s32 *)(vars + 0x240) = math_random_int_range(0x1E0, 0x258);
            }
        }
        break;
    }
    case 8: {
        s32 r;
        s32 i;
        u8 *e;
        if (*(s32 *)(vars + 0x294) != 0 && (i = *(s32 *)(vars + 0x298)) != -1) {
            e = D_L13_001B291C + (i << 8);
            if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD) {
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
                *(s32 *)(vars + 0x294) = 0;
                if (*(s32 *)(vars + 0x29C) != -1) {
                    moby_set_state(moby, 0x1C, 6);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended(moby, 0xD, 0, 0xF);
                    }
                } else {
                    if (moby[0x43] != 5) {
                        anim_start_blended(moby, 5, 0, 0xA);
                    }
                    moby_set_state(moby, 0x16, 2);
                    if (*(s32 *)(vars + 0x280) == 1) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended(moby, 0x13, 0, 0xA);
                        }
                        moby_set_state(moby, 0x14, 2);
                    }
                }
            }
        } else {
            r = *(s32 *)(vars + 0x250);
            if (r == 1 && math_fast_float_d(vars + 0x248) != 0) {
                *(s32 *)(vars + 0x26C) = r;
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, 0xA);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == r) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
            } else {
                r = moby[0xBC];
                if (r == 1) {
                    *(s32 *)(vars + 0x26C) = r;
                    if (moby[0x43] != 5) {
                        anim_start_blended(moby, 5, 0, 0xA);
                    }
                    moby_set_state(moby, 0x16, 2);
                    if (*(s32 *)(vars + 0x280) == r) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended(moby, 0x13, 0, 0xA);
                        }
                        moby_set_state(moby, 0x14, 2);
                    }
                    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                    moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
                }
            }
        }
        break;
    }
    case 1:
        if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
            *(s32 *)(vars + 0x26C) = 1;
            if (moby[0x43] != 5) {
                anim_start_blended(moby, 5, 0, 0xA);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xA);
                }
                moby_set_state(moby, 0x14, 2);
            }
            if (*(s32 *)(vars + 0x25C) != -1) {
                moby_set_state(moby, 0xF, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xF);
                }
            }
            if (*(s32 *)(vars + 0x290) != -1) {
                moby_set_state(moby, 0xE, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xF);
                }
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                u8 *e = D_L13_001B291C + (*(s32 *)(vars + 0x2AC) << 8);
                e[0x20] = 3;
                *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = moby;
            }
        }
        break;
    case 2: {
        s32 r;
        if (*(s32 *)(vars + 0x250) != 1 && *(s32 *)(vars + 0x254) != 1 && moby[0x20] != 0xF) {
            moby_set_state(moby, 9, 1);
            if (moby[0x43] != 0x15) {
                anim_start_blended(moby, 0x15, 0, 0x1E);
            }
            *(s32 *)(vars + 0x240) = math_random_int_range(0x244, 0x258);
            r = math_random_int_below(2);
            *(s32 *)(vars + 0x28C) = 0;
            *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + r;
        }
        if (*(s32 *)(vars + 0x264) == 1 && *(s32 *)(vars + 0x26C) == 0) {
            moby_set_state(moby, 0x17, 3);
            if (moby[0x43] != 0xD) {
                anim_start_blended(moby, 0xD, 0, 0x14);
            }
            r = math_random_int_below(2);
            *(s32 *)(vars + 0x28C) = 0;
            *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + r;
        }
        break;
    }
    case 5: {
        u8 *e;
        e = D_L13_001B291C + (*(s32 *)(vars + 0x298) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD || *(s32 *)(vars + 0x2B8) == 1) {
            *(s32 *)(vars + 0x294) = 0;
            if (*(s32 *)(vars + 0x29C) != -1) {
                moby_set_state(moby, 0x1C, 6);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xF);
                }
            } else {
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, 0xA);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            }
        }
        break;
    }
    case 4: {
        s32 r;
        u8 *e;
        r = moby_dispatch_action_by_kind(moby, vars + 0x140);
        if (r & 1) {
            SetDeathBits(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, 0);
            return;
        }
        if (r & 2) {
            if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xA);
                }
                moby_set_state(moby, 0x14, 2);
            } else {
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended(moby, 1, 0, 0x14);
                    }
                } else {
                    if (moby[0x43] != 4) {
                        anim_start_blended(moby, 4, 0, 0xA);
                    }
                }
                moby_set_state(moby, 9, 1);
                *(s32 *)(vars + 0x240) = math_random_int_range(0x244, 0x258);
            }
            if (*(s32 *)(vars + 0x290) != -1) {
                moby_set_state(moby, 0xE, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xF);
                }
            }
            if (*(s32 *)(vars + 0x270) != -1 && *(s32 *)(vars + 0x26C) == 0) {
                moby_set_state(moby, 0x10, -1);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xA);
                }
            }
            if (*(s32 *)(vars + 0x294) != 0) {
                if (moby[0x43] != 0x15) {
                    anim_start_blended(moby, 0x15, 0, 0xA);
                }
                moby_set_state(moby, 0x1B, 5);
            }
            e = D_L13_001B291C + (*(s32 *)(vars + 0x2D4) << 8);
            if (*(s32 *)(vars + 0x2BC) != 0 && e != 0 && e[0x20] != 0xFE && e[0x20] != 0xFD) {
                moby_set_state(moby, 0xA, 7);
                if (moby[0x43] != 3) {
                    anim_start_blended(moby, 3, 0, 0xF);
                }
                moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.006981318f, 0.8377582f);
            }
        }
        if (*(float *)(vars + 0x20) <= 0.0f && *(u16 *)(moby + 0x96) == 0x28) {
            STUB_printf(D_L13_001B11C0);
            moby_transform_joint_point(moby, 0, m);
            vec_scale_to_length(v, &m[4], -0.8333334f);
            SpawnEA7Moby(moby, v, &m[12], 0, vars[0x34]);
        }
        break;
    }
    }

    switch (moby[0x20]) {
    case 5:
        if (*(u16 *)(moby + 0x96) >= 0x38) {
            moby_set_state(moby, 6, -1);
            if (moby[0x43] != math_random_int_below(3) + 0x19) {
                anim_start_blended(moby, math_random_int_below(3) + 0x19, 0, 3);
            }
            if (moby[0x43] == 0x19) {
                *(s32 *)(vars + 0x2CC) = 0;
                STUB_printf(D_L13_001B11C8);
            } else if (moby[0x43] == 0x1B) {
                *(s32 *)(vars + 0x2CC) = 1;
                STUB_printf(D_L13_001B11D0);
            } else {
                *(s32 *)(vars + 0x2CC) = 2;
                STUB_printf(D_L13_001B11D8);
            }
        }
        break;
    case 8:
        if (*(u16 *)(moby + 0x96) >= 0x47) {
            moby_set_state(moby, 6, -1);
            if (moby[0x43] != math_random_int_below(3) + 0x19) {
                anim_start_blended(moby, math_random_int_below(3) + 0x19, 0, 3);
            }
            if (moby[0x43] == 0x19) {
                *(s32 *)(vars + 0x2CC) = 0;
                STUB_printf(D_L13_001B11C8);
            } else if (moby[0x43] == 0x1B) {
                *(s32 *)(vars + 0x2CC) = 1;
                STUB_printf(D_L13_001B11D0);
            } else {
                *(s32 *)(vars + 0x2CC) = 2;
                STUB_printf(D_L13_001B11D8);
            }
        }
        break;
    case 6: {
        s32 r;
        if (*(u16 *)(moby + 0x96) >= 0x3D) {
            r = rps_judge(moby);
            if (r == 2) {
                moby_set_state(moby, 5, -1);
                if (moby[0x43] != 0x18) {
                    anim_start_blended(moby, 0x18, 0, 3);
                }
            } else if (r == 0) {
                moby_set_state(moby, 7, -1);
                if (moby[0x43] != 7) {
                    anim_start_blended(moby, 7, 2, 0x1B);
                }
            } else {
                moby_set_state(moby, 7, -1);
                if (moby[0x43] != 0x1C) {
                    anim_start_blended(moby, 0x1C, 0, 0xA);
                }
            }
        }
        break;
    }
    case 7:
        if (*(u16 *)(moby + 0x96) >= 0x49) {
            moby_set_state(moby, 8, -1);
            if (moby[0x43] != 0x18) {
                anim_start_blended(moby, 0x18, 0, 0x12);
            }
        }
        break;
    case 3:
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (AdvancePathWaypoint(moby, D_L13_001FE580[*(s32 *)(vars + 0x2B0)]) != 0) {
                moby_set_state(moby, 4, -1);
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended(moby, 1, 0, 0x14);
                    }
                } else {
                    if (moby[0x43] != 0x16) {
                        anim_start_blended(moby, 0x16, 0, 0xA);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (moby[0x43] != 4) {
                        anim_start_blended(moby, 4, 0, 0xA);
                    }
                }
            }
        } else {
            if (path_follow_nodes(moby, D_L13_001FE580[*(s32 *)(vars + 0x2B0)]) != 0) {
                moby_set_state(moby, 4, -1);
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended(moby, 1, 0, 0x14);
                    }
                } else {
                    if (moby[0x43] != 0x16) {
                        anim_start_blended(moby, 0x16, 0, 0xA);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (moby[0x43] != 4) {
                        anim_start_blended(moby, 4, 0, 0xA);
                    }
                }
            }
        }
        break;
    case 4: {
        s32 *path;
        float d;
        if (moby[0x60] & 2) {
            path = D_L13_001FE580[*(s32 *)(vars + 0x2B0)];
            d = vec_distance_xy(moby + 0x10, path + 4);
            if (vec_distance_xy(moby + 0x10, path + *path * 4) < d) {
                path_set_follower_nodes(moby, D_L13_001FE580[*(s32 *)(vars + 0x2B0)], 0, *path - 1);
            } else {
                path_set_follower_nodes(moby, D_L13_001FE580[*(s32 *)(vars + 0x2B0)], *path - 1, 0);
            }
            moby_set_state(moby, 3, -1);
            if (moby[0x43] != 3) {
                anim_start_blended(moby, 3, 0, 0x14);
            }
        }
        break;
    }
    case 16:
        if (path_follow_nodes(moby, D_L13_001FE580[*(s32 *)(vars + 0x270)]) != 0) {
            *(s32 *)(vars + 0x26C) = 1;
            moby_set_state(moby, 2, -1);
            if (moby[0x43] != 0x15) {
                anim_start_blended(moby, 0x15, 0, 0xA);
            }
        }
        break;
    case 2:
        STUB_printf(D_L13_001B11E8);
        moby_set_state(moby, 1, -1);
        break;
    case 9:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x15) {
                anim_start_blended(moby, 0x15, 0, 0xA);
            }
            moby_set_state(moby, 1, -1);
        }
        break;
    case 10: {
        u8 *e;
        if (path_check_entry_for_moby(moby, *(s32 *)(vars + 0x2C0)) != 0) {
            if (moby[0x43] != 0x15) {
                anim_start_blended(moby, 0x15, 0, 0xA);
            }
            moby_set_state(moby, 0xD, -1);
        }
        e = D_L13_001B291C + (*(s32 *)(vars + 0x2D4) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD
            || FastDiffRots(*(float *)(moby + 0xF8),
                             mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                           *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14))) > 1.7453294f) {
            if (moby[0x43] != 5) {
                anim_start_blended(moby, 5, 0, 0xA);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xA);
                }
                moby_set_state(moby, 0x14, 2);
            }
            if (*(s32 *)(vars + 0x2D8) != 0) {
                moby_set_state(moby, 0xB, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xA);
                }
                moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.006981318f, 0.8377582f);
            }
        }
        break;
    }
    case 11:
        moby_turn_toward_target_and_step(moby, vars + 0x1F0, *(float *)(vars + 0x2DC) * 0.017453294f);
        if (*(u16 *)(moby + 0x96) >= 0x65) {
            if (math_random_int_below(0xA) == 1) {
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, 0xA);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            }
        }
        break;
    case 28: {
        s32 r;
        if (*(s32 *)(vars + 0x2A0) != 0) {
            r = AdvancePathWaypoint(moby, D_L13_001FE580[*(s32 *)(vars + 0x29C)]);
        } else {
            r = path_follow_nodes(moby, D_L13_001FE580[*(s32 *)(vars + 0x29C)]);
        }
        if (r != 0 || vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x200) + 0x10) < 8.0f) {
            if (moby[0x43] != 5) {
                anim_start_blended(moby, 5, 0, 0xA);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xA);
                }
                moby_set_state(moby, 0x14, 2);
            }
        }
        break;
    }
    case 15: {
        s32 i;
        s32 j;
        if (flag_set_first_pending(moby) != 0 && *(s32 *)(vars + 0x2A8) != 0) {
            i = *(s32 *)(vars + 0x360);
            if (i != -1) {
                j = *(s32 *)(vars + 0x364);
                if (j != -1) {
                    u8 *base = D_L13_001B291C;
                    (base + (i << 8))[0x20] = 4;
                    (base + (j << 8))[0x20] = 4;
                    *(s32 *)(vars + 0x360) = -1;
                    *(s32 *)(vars + 0x364) = -1;
                }
            }
        }
        *(TI128 *)m = ((L13Cam *)D_L13_001B2A0C)[*(s32 *)(vars + 0x25C)].v;
        if (*(s32 *)(vars + 0x2A0) != 0) {
            creature_move_along_ground(moby, m);
        } else {
            moby_l01_turn_toward_target(moby, m);
        }
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (vec_distance_xy(moby + 0x10, m) < 0.9f) {
                moby_set_state(moby, 0x14, -1);
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xF);
                }
            }
        } else if (vec_distance_xy(moby + 0x10, m) < 0.5f) {
            moby_set_state(moby, 0x14, -1);
            if (moby[0x43] != 0x13) {
                anim_start_blended(moby, 0x13, 0, 0xF);
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
            }
        }
        break;
    }
    case 29:
        *(TI128 *)m = *(TI128 *)(vars + 0x370);
        if (*(s32 *)(vars + 0x2A0) != 0) {
            creature_move_along_ground(moby, m);
        } else {
            moby_l01_turn_toward_target(moby, m);
        }
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (vec_distance_xy(moby + 0x10, m) < 0.9f) {
                moby_set_state(moby, 0x14, -1);
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xF);
                }
            }
        } else if (vec_distance_xy(moby + 0x10, m) < 0.5f) {
            moby_set_state(moby, 0x14, -1);
            if (moby[0x43] != 0x13) {
                anim_start_blended(moby, 0x13, 0, 0xF);
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
            }
        }
        break;
    case 13: {
        u8 *e;
        u8 *hit;
        e = D_L13_001B291C + (*(s32 *)(vars + 0x2D4) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD) {
            if (moby[0x43] != 5) {
                anim_start_blended(moby, 5, 0, 0xA);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xA);
                }
                moby_set_state(moby, 0x14, 2);
            }
            if (*(s32 *)(vars + 0x2D8) != 0) {
                moby_set_state(moby, 0xB, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xA);
                }
                moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.006981318f, 0.8377582f);
            }
        } else {
            moby_transform_joint_to_world(moby, 0, m);
            if (CollLine(m, vars + 0x1F0, 0, moby, 0) == 0) {
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, 0xA);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            } else {
                hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                if (hit != 0 && (hit == g_hero_moby || *(s16 *)(hit + 0xAA) == 0xC87
                                 || hit == *(u8 **)(vars + 0x200))) {
                    if (moby[0x43] != 5) {
                        anim_start_blended(moby, 5, 0, 0xA);
                    }
                    moby_set_state(moby, 0x16, 2);
                    if (*(s32 *)(vars + 0x280) == 1) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended(moby, 0x13, 0, 0xA);
                        }
                        moby_set_state(moby, 0x14, 2);
                    }
                }
            }
        }
        break;
    }
    case 18:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x13) {
                anim_start_blended(moby, 0x13, 0, 0xA);
            }
            moby_set_state(moby, 0x14, -1);
        }
        break;
    case 14:
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (AdvancePathWaypoint(moby, D_L13_001FE580[*(s32 *)(vars + 0x290)]) != 0) {
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, 0xA);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
                *(s32 *)(vars + 0x290) = -1;
            }
        } else if (path_follow_nodes(moby, D_L13_001FE580[*(s32 *)(vars + 0x290)]) != 0
                   || vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x200) + 0x10) < 8.0f) {
            moby_set_state(moby, 0x18, 2);
            if (moby[0x43] != 6) {
                anim_start_blended(moby, 6, 0, 0xA);
            }
            *(s32 *)(vars + 0x290) = -1;
        }
        break;
    case 19: {
        u8 *hit;
        moby_transform_joint_to_world(moby, 0, m);
        FastVecSub(&m[4], vars + 0x1F0, m);
        vec_scale_to_length(&m[4], &m[4], 0.6666667f);
        if (CollLine(m, vars + 0x1F0, 0, moby, 0) == 0) {
            if (moby[0x43] != 5) {
                anim_start_blended(moby, 5, 0, 1);
            }
            moby_set_state(moby, 0x16, -1);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended(moby, 0x13, 0, 0xA);
                }
                moby_set_state(moby, 0x14, 2);
            }
        } else {
            hit = *(u8 **)(D_L13_001BFD00 + 0x18);
            if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(vars + 0x200)
                             || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                             || *(s16 *)(hit + 0xAA) == 0x1F4 /* Crate */ || *(s16 *)(hit + 0xAA) == 0x10CE
                             || *(s16 *)(hit + 0xAA) == 0x200 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, math_random_int_below(0xF));
                }
                moby_set_state(moby, 0x16, -1);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            }
        }
        if (moby[0x60] & 2) {
            if (moby[0x42] == 0xE) {
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended(moby, 1, 0, 0x14);
                    }
                } else {
                    if (moby[0x43] != 0x16) {
                        anim_start_blended(moby, 0x16, 0, 0xA);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (moby[0x43] != 4) {
                        anim_start_blended(moby, 4, 0, 0xA);
                    }
                }
            } else {
                if (moby[0x43] != 0xE) {
                    anim_start_blended(moby, 0xE, 0, 0x14);
                }
            }
        }
        break;
    }
    case 20:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A0) != 0) {
            moby_turn_toward_hero(moby);
        }
        if (math_is_value_within_step(moby, 1.0f) != 0) {
            moby_transform_joint_to_world(moby, 0, m);
            FastVecSub(&m[4], vars + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.6666667f);
            SpawnEA7Moby(moby, &m[4], m, 0, vars[0x34]);
            (*(s32 *)(vars + 0x28C))++;
        }
        if (moby[0x60] & 2) {
            if (*(s32 *)(vars + 0x288) == *(s32 *)(vars + 0x28C)) {
                s32 r;
                moby_set_state(moby, 0x18, -1);
                if (moby[0x43] != 6) {
                    anim_start_blended(moby, 6, 0, 0xA);
                }
                r = math_random_int_below(4);
                *(s32 *)(vars + 0x28C) = 0;
                *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + r;
            } else {
                if (moby[0x43] != 0xE) {
                    anim_start_blended(moby, 0xE, 0, math_random_int_below(5) + 0xA);
                }
                moby_set_state(moby, 0x13, -1);
            }
        }
        break;
    case 21: {
        u8 *hit;
        if (*(u16 *)(moby + 0x96) >= 0x79) {
            moby_transform_joint_to_world(moby, 0, m);
            FastVecSub(&m[4], vars + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.6666667f);
            if (CollLine(m, vars + 0x1F0, 0, moby, 0) == 0) {
                if (moby[0x43] != 5) {
                    anim_start_blended(moby, 5, 0, 1);
                }
                moby_set_state(moby, 0x16, -1);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended(moby, 0x13, 0, 0xA);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            } else {
                hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(vars + 0x200)
                                 || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                 || *(s16 *)(hit + 0xAA) == 0x1F4 /* Crate */ || *(s16 *)(hit + 0xAA) == 0x10CE
                                 || *(s16 *)(hit + 0xAA) == 0x200 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                    if (moby[0x43] != 5) {
                        anim_start_blended(moby, 5, 0, math_random_int_below(0xF));
                    }
                    moby_set_state(moby, 0x16, -1);
                    if (*(s32 *)(vars + 0x280) == 1) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended(moby, 0x13, 0, 0xA);
                        }
                        moby_set_state(moby, 0x14, 2);
                    }
                }
            }
        }
        break;
    }
    case 22:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A0) != 0) {
            moby_turn_toward_hero(moby);
        }
        if (math_is_value_within_step(moby, 3.0f) != 0) {
            moby_transform_joint_to_world(moby, 0, m);
            FastVecSub(&m[4], vars + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.6666667f);
            SpawnEA7Moby(moby, &m[4], m, 0, vars[0x34]);
            (*(s32 *)(vars + 0x28C))++;
        }
        if (moby[0x60] & 2) {
            if (*(s32 *)(vars + 0x288) == *(s32 *)(vars + 0x28C)) {
                moby_set_state(moby, 0x18, -1);
                if (moby[0x43] != 6) {
                    anim_start_blended(moby, 6, 0, 0xA);
                }
                if (math_random_int_below(2) == 1) {
                    *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + math_random_int_below(4);
                }
                *(s32 *)(vars + 0x28C) = 0;
            } else {
                if (moby[0x43] != 0xE) {
                    anim_start_blended(moby, 0xE, 0, math_random_int_below(5) + 0xA);
                }
                moby_set_state(moby, 0x15, -1);
            }
        }
        break;
    case 25:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A0) != 0) {
            moby_turn_toward_hero(moby);
        }
        if (math_is_value_within_step(moby, 3.0f) != 0) {
            moby_transform_joint_to_world(moby, 0, m);
            FastVecSub(&m[4], vars + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.6666667f);
            SpawnEA7Moby(moby, &m[4], m, 0, vars[0x34]);
            (*(s32 *)(vars + 0x28C))++;
        }
        if ((moby[0x60] & 2) && *(s32 *)(vars + 0x288) == *(s32 *)(vars + 0x28C)) {
            moby_set_state(moby, 0x18, -1);
            if (moby[0x43] != 6) {
                anim_start_blended(moby, 6, 0, 0x14);
            }
            if (math_random_int_below(2) == 1) {
                *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + math_random_int_below(4);
            }
            *(s32 *)(vars + 0x28C) = 0;
        }
        break;
    case 23:
        *(TI128 *)m = ((L13Cam *)D_L13_001B2A0C)[*(s32 *)(vars + 0x268)].v;
        moby_l01_turn_toward_target(moby, m);
        if (vec_distance_xy(moby + 0x10, m) < 0.5f) {
            *(s32 *)(vars + 0x26C) = 1;
            moby_set_state(moby, 0x14, 2);
            if (moby[0x43] != 0x13) {
                anim_start_blended(moby, 0x13, 0, 0xF);
            }
        }
        break;
    case 24:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0xE) {
                anim_start_blended(moby, 0xE, 0, 0xA);
            }
            moby_set_state(moby, 0x15, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0xE) {
                    anim_start_blended(moby, 0xE, 0, 0xA);
                }
                moby_set_state(moby, 0x13, 2);
            }
            if (*(s32 *)(vars + 0x2A8) != 0 && g_hero_position[2] - *(float *)(moby + 0x18) > 6.0f) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
            }
            if (*(s32 *)(vars + 0x368) != 0 && vec_distance_xy(moby + 0x10, vars + 0x370) > 4.0f) {
                moby_set_state(moby, 0x1D, -1);
                if (moby[0x43] != 0xD) {
                    anim_start_blended(moby, 0xD, 0, 0xA);
                }
            }
        }
        break;
    case 1:
    default:
        break;
    }
    guard_update_hit_timer(moby);
}
