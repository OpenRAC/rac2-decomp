#include "include_asm.h"

#include "common.h"
typedef struct L13C3Flags { char pad[0x88]; volatile int flags; } L13C3Flags;
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define S(p,o) (*(short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
extern int math_random_int_below(int);
extern void moby_set_controller_speed_limits(char *,float,float,float,float);
extern void moby_set_state(char *,int,int);
extern void func_PAL_002A7E68(char *,int,int,int);
extern int FloatToInt(float);
extern void moby_update_ground_check(char *);
extern int func_PAL_002B1A50(char *,char *,int);
extern int weapon_select_aim_target(char *,int,float,float,int,int);
extern void func_PAL_002A7650(char *,int,int);
extern char D_L13_001B98C0[];
extern float fast_vec_dist(void *, void *);
extern void guard_alert_nearby(u8 *);
extern u8 *D_L13_001B291C __attribute__((section(".sdata")));
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
/* A 0x80-byte record of the level table at D_L13_001B2A0C; its point is at +0x30. */
typedef struct { u8 pad0[0x30]; TI128 v; u8 pad40[0x40]; } L13Cam;
extern char g_hero_state[];
extern float g_hero_position[];
extern u8 *g_hero_moby;
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
extern int math_random_int_range(int, int);
extern int CollLine(void *, void *, int, void *, int);
extern int func_PAL_002AF6C0(void *, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern int func_PAL_002B5BA8(void *, void *, float);
extern int func_PAL_002B6CD8(void *, void *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int func_PAL_L01_00323068(void *, void *);
extern int moby_start_effect_from_entry(void *, float);
extern void part_queue_moby_for_glow(void *, int, void *);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
extern int func_PAL_L09_0032B088(void *, int);
extern int rps_judge(void *);
extern int func_PAL_L13_0040D978(char *);
extern int func_PAL_L13_0040DF68(char *, char *);
extern int func_PAL_L13_0040E1B0(void *, void *);
extern void func_PAL_L13_0040EDF0(void *);
extern void guard_update_hit_timer(void *);
extern u8 *func_PAL_L13_00412518(void *, void *, void *, int, float);

/* func_PAL_L13_0040B7AC, the PAL copy of func_L13_00406F18: the same C, where frame counts are scaled to 50 Hz,
   ((s32)(x) * 5 + 2) / 6, and per-frame rates grow by 6/5. */
/* The per-frame update of the level-13 guard: the action states (+0x95) first, then the
   animation states (+0x20), then the shared timer update. */
void func_PAL_L13_0040B7AC(u8 *a0)
{
    float m[16] __attribute__((aligned(16)));
    float v[4];
    u8 *st;

    st = *(u8 **)(a0 + 0x68);
    if (func_PAL_L13_0040D978(a0) != 0) {
        part_queue_moby_for_glow(a0, 0, 0);
    }
    switch (a0[0x95]) {
    case 0: {
        s32 r;
        r = *(s32 *)(st + 0x250);
        if (r == 1 && math_fast_float_d(st + 0x248) != 0) {
            if (*(s32 *)(st + 0x2A8) == 0 || ((Hero *)g_hero_state)->h[0x348 / 2] == r) {
                *(s32 *)(st + 0x26C) = r;
                moby_set_state(a0, 0x18, 2);
                if (a0[0x43] != 6) {
                    func_PAL_002A7E68(a0, 6, 0, 8);
                }
                if (*(s32 *)(st + 0x25C) != -1) {
                    moby_set_state(a0, 0xF, 2);
                    if (a0[0x43] != 0xD) {
                        func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(st + 0x290) != -1) {
                    moby_set_state(a0, 0xE, 2);
                    if (a0[0x43] != 0xD) {
                        func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
                }
                if (*(s32 *)(st + 0x2BC) != 0) {
                    moby_set_state(a0, 0xA, 7);
                    if (a0[0x43] != 3) {
                        func_PAL_002A7E68(a0, 3, 0, 0xC);
                    }
                    moby_set_controller_speed_limits(a0, 0.0032000002f, 0.080000006f, 0.010053098f, 1.0053098f);
                }
            }
        } else if (*(s64 *)(st + 0x278) == 1) {
            if (*(s32 *)(st + 0x270) != -1) {
                moby_set_state(a0, 0x10, -1);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 8);
                }
                *(s32 *)(st + 0x27C) = 1;
            }
        } else if (*(s32 *)(st + 0x24C) != 0) {
            if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
                *(s32 *)(st + 0x26C) = 1;
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, 8);
                }
                moby_set_state(a0, 0x16, 2);
                if (*(s32 *)(st + 0x280) == 1) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
                if (*(s32 *)(st + 0x25C) != -1) {
                    moby_set_state(a0, 0xF, 2);
                    if (a0[0x43] != 0xD) {
                        func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(st + 0x290) != -1) {
                    moby_set_state(a0, 0xE, 2);
                    if (a0[0x43] != 0xD) {
                        func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
                }
                if (*(s32 *)(st + 0x2BC) != 0) {
                    moby_set_state(a0, 0xA, 7);
                    if (a0[0x43] != 3) {
                        func_PAL_002A7E68(a0, 3, 0, 0xC);
                    }
                    moby_set_controller_speed_limits(a0, 0.0032000002f, 0.080000006f, 0.010053098f, 1.0053098f);
                }
            }
            *(s32 *)(st + 0x24C) = 0;
            if (*(s32 *)(st + 0x240) < 0xFA) {
                *(s32 *)(st + 0x240) = ((s32)(math_random_int_range(0x1E0, 0x258)) * 5 + 2) / 6;
            }
        }
        break;
    }
    case 8: {
        s32 r;
        s32 i;
        u8 *e;
        if (*(s32 *)(st + 0x294) != 0 && (i = *(s32 *)(st + 0x298)) != -1) {
            e = D_L13_001B291C + (i << 8);
            if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD) {
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                moby_fuse_linked_objects(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
                *(s32 *)(st + 0x294) = 0;
                if (*(s32 *)(st + 0x29C) != -1) {
                    moby_set_state(a0, 0x1C, 6);
                    if (a0[0x43] != 0xD) {
                        func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                    }
                } else {
                    if (a0[0x43] != 5) {
                        func_PAL_002A7E68(a0, 5, 0, 8);
                    }
                    moby_set_state(a0, 0x16, 2);
                    if (*(s32 *)(st + 0x280) == 1) {
                        if (a0[0x43] != 0x13) {
                            func_PAL_002A7E68(a0, 0x13, 0, 8);
                        }
                        moby_set_state(a0, 0x14, 2);
                    }
                }
            }
        } else {
            r = *(s32 *)(st + 0x250);
            if (r == 1 && math_fast_float_d(st + 0x248) != 0) {
                *(s32 *)(st + 0x26C) = r;
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, 8);
                }
                moby_set_state(a0, 0x16, 2);
                if (*(s32 *)(st + 0x280) == r) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                moby_fuse_linked_objects(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
            } else {
                r = a0[0xBC];
                if (r == 1) {
                    *(s32 *)(st + 0x26C) = r;
                    if (a0[0x43] != 5) {
                        func_PAL_002A7E68(a0, 5, 0, 8);
                    }
                    moby_set_state(a0, 0x16, 2);
                    if (*(s32 *)(st + 0x280) == r) {
                        if (a0[0x43] != 0x13) {
                            func_PAL_002A7E68(a0, 0x13, 0, 8);
                        }
                        moby_set_state(a0, 0x14, 2);
                    }
                    *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                    moby_fuse_linked_objects(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
                }
            }
        }
        break;
    }
    case 1:
        if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
            *(s32 *)(st + 0x26C) = 1;
            if (a0[0x43] != 5) {
                func_PAL_002A7E68(a0, 5, 0, 8);
            }
            moby_set_state(a0, 0x16, 2);
            if (*(s32 *)(st + 0x280) == 1) {
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 8);
                }
                moby_set_state(a0, 0x14, 2);
            }
            if (*(s32 *)(st + 0x25C) != -1) {
                moby_set_state(a0, 0xF, 2);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                }
            }
            if (*(s32 *)(st + 0x290) != -1) {
                moby_set_state(a0, 0xE, 2);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                }
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                e[0x20] = 3;
                *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
            }
        }
        break;
    case 2: {
        s32 r;
        if (*(s32 *)(st + 0x250) != 1 && *(s32 *)(st + 0x254) != 1 && a0[0x20] != 0xF) {
            moby_set_state(a0, 9, 1);
            if (a0[0x43] != 0x15) {
                func_PAL_002A7E68(a0, 0x15, 0, 0x19);
            }
            *(s32 *)(st + 0x240) = ((s32)(math_random_int_range(0x244, 0x258)) * 5 + 2) / 6;
            r = math_random_int_below(2);
            *(s32 *)(st + 0x28C) = 0;
            *(s32 *)(st + 0x288) = *(s32 *)(st + 0x284) + r;
        }
        if (*(s32 *)(st + 0x264) == 1 && *(s32 *)(st + 0x26C) == 0) {
            moby_set_state(a0, 0x17, 3);
            if (a0[0x43] != 0xD) {
                func_PAL_002A7E68(a0, 0xD, 0, 0x11);
            }
            r = math_random_int_below(2);
            *(s32 *)(st + 0x28C) = 0;
            *(s32 *)(st + 0x288) = *(s32 *)(st + 0x284) + r;
        }
        break;
    }
    case 5: {
        u8 *e;
        e = D_L13_001B291C + (*(s32 *)(st + 0x298) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD || *(s32 *)(st + 0x2B8) == 1) {
            *(s32 *)(st + 0x294) = 0;
            if (*(s32 *)(st + 0x29C) != -1) {
                moby_set_state(a0, 0x1C, 6);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                }
            } else {
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, 8);
                }
                moby_set_state(a0, 0x16, 2);
                if (*(s32 *)(st + 0x280) == 1) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
            }
        }
        break;
    }
    case 4: {
        s32 r;
        u8 *e;
        r = moby_dispatch_action_by_kind(a0, st + 0x140);
        if (r & 1) {
            func_PAL_002A7650(a0, 0, 3);
            part_queue_moby_for_glow(a0, 0, 0);
            return;
        }
        if (r & 2) {
            if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 8);
                }
                moby_set_state(a0, 0x14, 2);
            } else {
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_PAL_002A7E68(a0, 1, 0, 0x11);
                    }
                } else {
                    if (a0[0x43] != 4) {
                        func_PAL_002A7E68(a0, 4, 0, 8);
                    }
                }
                moby_set_state(a0, 9, 1);
                *(s32 *)(st + 0x240) = ((s32)(math_random_int_range(0x244, 0x258)) * 5 + 2) / 6;
            }
            if (*(s32 *)(st + 0x290) != -1) {
                moby_set_state(a0, 0xE, 2);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 0xC);
                }
            }
            if (*(s32 *)(st + 0x270) != -1 && *(s32 *)(st + 0x26C) == 0) {
                moby_set_state(a0, 0x10, -1);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 8);
                }
            }
            if (*(s32 *)(st + 0x294) != 0) {
                if (a0[0x43] != 0x15) {
                    func_PAL_002A7E68(a0, 0x15, 0, 8);
                }
                moby_set_state(a0, 0x1B, 5);
            }
            e = D_L13_001B291C + (*(s32 *)(st + 0x2D4) << 8);
            if (*(s32 *)(st + 0x2BC) != 0 && e != 0 && e[0x20] != 0xFE && e[0x20] != 0xFD) {
                moby_set_state(a0, 0xA, 7);
                if (a0[0x43] != 3) {
                    func_PAL_002A7E68(a0, 3, 0, 0xC);
                }
                moby_set_controller_speed_limits(a0, 0.0032000002f, 0.080000006f, 0.010053098f, 1.0053098f);
            }
        }
        if (*(float *)(st + 0x20) <= 0.0f && *(u16 *)(a0 + 0x96) == 0x28) {
            STUB_printf(D_L13_001B11C0);
            moby_transform_joint_point(a0, 0, m);
            vec_scale_to_length(v, &m[4], -1.0000001f);
            func_PAL_L13_00412518(a0, v, &m[12], 0, st[0x34]);
        }
        break;
    }
    }

    switch (a0[0x20]) {
    case 5:
        if (*(u16 *)(a0 + 0x96) >= 0x38) {
            moby_set_state(a0, 6, -1);
            if (a0[0x43] != math_random_int_below(3) + 0x19) {
                func_PAL_002A7E68(a0, math_random_int_below(3) + 0x19, 0, 2);
            }
            if (a0[0x43] == 0x19) {
                *(s32 *)(st + 0x2CC) = 0;
                STUB_printf(D_L13_001B11C8);
            } else if (a0[0x43] == 0x1B) {
                *(s32 *)(st + 0x2CC) = 1;
                STUB_printf(D_L13_001B11D0);
            } else {
                *(s32 *)(st + 0x2CC) = 2;
                STUB_printf(D_L13_001B11D8);
            }
        }
        break;
    case 8:
        if (*(u16 *)(a0 + 0x96) >= 0x47) {
            moby_set_state(a0, 6, -1);
            if (a0[0x43] != math_random_int_below(3) + 0x19) {
                func_PAL_002A7E68(a0, math_random_int_below(3) + 0x19, 0, 2);
            }
            if (a0[0x43] == 0x19) {
                *(s32 *)(st + 0x2CC) = 0;
                STUB_printf(D_L13_001B11C8);
            } else if (a0[0x43] == 0x1B) {
                *(s32 *)(st + 0x2CC) = 1;
                STUB_printf(D_L13_001B11D0);
            } else {
                *(s32 *)(st + 0x2CC) = 2;
                STUB_printf(D_L13_001B11D8);
            }
        }
        break;
    case 6: {
        s32 r;
        if (*(u16 *)(a0 + 0x96) >= 0x3D) {
            r = rps_judge(a0);
            if (r == 2) {
                moby_set_state(a0, 5, -1);
                if (a0[0x43] != 0x18) {
                    func_PAL_002A7E68(a0, 0x18, 0, 2);
                }
            } else if (r == 0) {
                moby_set_state(a0, 7, -1);
                if (a0[0x43] != 7) {
                    func_PAL_002A7E68(a0, 7, 2, 0x16);
                }
            } else {
                moby_set_state(a0, 7, -1);
                if (a0[0x43] != 0x1C) {
                    func_PAL_002A7E68(a0, 0x1C, 0, 8);
                }
            }
        }
        break;
    }
    case 7:
        if (*(u16 *)(a0 + 0x96) >= 0x49) {
            moby_set_state(a0, 8, -1);
            if (a0[0x43] != 0x18) {
                func_PAL_002A7E68(a0, 0x18, 0, 0xF);
            }
        }
        break;
    case 3:
        if (*(s32 *)(st + 0x2A0) != 0) {
            if (func_PAL_L13_0040E1B0(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)]) != 0) {
                moby_set_state(a0, 4, -1);
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_PAL_002A7E68(a0, 1, 0, 0x11);
                    }
                } else {
                    if (a0[0x43] != 0x16) {
                        func_PAL_002A7E68(a0, 0x16, 0, 8);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (a0[0x43] != 4) {
                        func_PAL_002A7E68(a0, 4, 0, 8);
                    }
                }
            }
        } else {
            if (func_PAL_002B6CD8(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)]) != 0) {
                moby_set_state(a0, 4, -1);
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_PAL_002A7E68(a0, 1, 0, 0x11);
                    }
                } else {
                    if (a0[0x43] != 0x16) {
                        func_PAL_002A7E68(a0, 0x16, 0, 8);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (a0[0x43] != 4) {
                        func_PAL_002A7E68(a0, 4, 0, 8);
                    }
                }
            }
        }
        break;
    case 4: {
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
            moby_set_state(a0, 3, -1);
            if (a0[0x43] != 3) {
                func_PAL_002A7E68(a0, 3, 0, 0x11);
            }
        }
        break;
    }
    case 16:
        if (func_PAL_002B6CD8(a0, D_L13_001FE580[*(s32 *)(st + 0x270)]) != 0) {
            *(s32 *)(st + 0x26C) = 1;
            moby_set_state(a0, 2, -1);
            if (a0[0x43] != 0x15) {
                func_PAL_002A7E68(a0, 0x15, 0, 8);
            }
        }
        break;
    case 2:
        STUB_printf(D_L13_001B11E8);
        moby_set_state(a0, 1, -1);
        break;
    case 9:
        if (a0[0x60] & 2) {
            if (a0[0x43] != 0x15) {
                func_PAL_002A7E68(a0, 0x15, 0, 8);
            }
            moby_set_state(a0, 1, -1);
        }
        break;
    case 10: {
        u8 *e;
        if (func_PAL_L09_0032B088(a0, *(s32 *)(st + 0x2C0)) != 0) {
            if (a0[0x43] != 0x15) {
                func_PAL_002A7E68(a0, 0x15, 0, 8);
            }
            moby_set_state(a0, 0xD, -1);
        }
        e = D_L13_001B291C + (*(s32 *)(st + 0x2D4) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD
            || FastDiffRots(*(float *)(a0 + 0xF8),
                             mat_fast_helper_a(*(float *)(st + 0x1F0) - *(float *)(a0 + 0x10),
                                           *(float *)(st + 0x1F4) - *(float *)(a0 + 0x14))) > 1.7453294f) {
            if (a0[0x43] != 5) {
                func_PAL_002A7E68(a0, 5, 0, 8);
            }
            moby_set_state(a0, 0x16, 2);
            if (*(s32 *)(st + 0x280) == 1) {
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 8);
                }
                moby_set_state(a0, 0x14, 2);
            }
            if (*(s32 *)(st + 0x2D8) != 0) {
                moby_set_state(a0, 0xB, 2);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 8);
                }
                moby_set_controller_speed_limits(a0, 0.0048f, 0.120000005f, 0.010053098f, 1.0053098f);
            }
        }
        break;
    }
    case 11:
        func_PAL_002B5BA8(a0, st + 0x1F0, *(float *)(st + 0x2DC) * 0.017453294f);
        if (*(u16 *)(a0 + 0x96) >= 0x65) {
            if (math_random_int_below(0xA) == 1) {
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, 8);
                }
                moby_set_state(a0, 0x16, 2);
                if (*(s32 *)(st + 0x280) == 1) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
            }
        }
        break;
    case 28: {
        s32 r;
        if (*(s32 *)(st + 0x2A0) != 0) {
            r = func_PAL_L13_0040E1B0(a0, D_L13_001FE580[*(s32 *)(st + 0x29C)]);
        } else {
            r = func_PAL_002B6CD8(a0, D_L13_001FE580[*(s32 *)(st + 0x29C)]);
        }
        if (r != 0 || vec_distance_xy(a0 + 0x10, *(u8 **)(st + 0x200) + 0x10) < 8.0f) {
            if (a0[0x43] != 5) {
                func_PAL_002A7E68(a0, 5, 0, 8);
            }
            moby_set_state(a0, 0x16, 2);
            if (*(s32 *)(st + 0x280) == 1) {
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 8);
                }
                moby_set_state(a0, 0x14, 2);
            }
        }
        break;
    }
    case 15: {
        s32 i;
        s32 j;
        if (flag_set_first_pending(a0) != 0 && *(s32 *)(st + 0x2A8) != 0) {
            i = *(s32 *)(st + 0x360);
            if (i != -1) {
                j = *(s32 *)(st + 0x364);
                if (j != -1) {
                    u8 *base = D_L13_001B291C;
                    (base + (i << 8))[0x20] = 4;
                    (base + (j << 8))[0x20] = 4;
                    *(s32 *)(st + 0x360) = -1;
                    *(s32 *)(st + 0x364) = -1;
                }
            }
        }
        *(TI128 *)m = ((L13Cam *)D_L13_001B2A0C)[*(s32 *)(st + 0x25C)].v;
        if (*(s32 *)(st + 0x2A0) != 0) {
            func_PAL_L13_0040DF68(a0, m);
        } else {
            func_PAL_L01_00323068(a0, m);
        }
        if (*(s32 *)(st + 0x2A0) != 0) {
            if (vec_distance_xy(a0 + 0x10, m) < 0.9f) {
                moby_set_state(a0, 0x14, -1);
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 0xC);
                }
            }
        } else if (vec_distance_xy(a0 + 0x10, m) < 0.5f) {
            moby_set_state(a0, 0x14, -1);
            if (a0[0x43] != 0x13) {
                func_PAL_002A7E68(a0, 0x13, 0, 0xC);
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                moby_set_state(a0, 0x19, -1);
                if (a0[0x43] != 0x11) {
                    func_PAL_002A7E68(a0, 0x11, 0, 0x11);
                }
            }
        }
        break;
    }
    case 29:
        *(TI128 *)m = *(TI128 *)(st + 0x370);
        if (*(s32 *)(st + 0x2A0) != 0) {
            func_PAL_L13_0040DF68(a0, m);
        } else {
            func_PAL_L01_00323068(a0, m);
        }
        if (*(s32 *)(st + 0x2A0) != 0) {
            if (vec_distance_xy(a0 + 0x10, m) < 0.9f) {
                moby_set_state(a0, 0x14, -1);
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 0xC);
                }
            }
        } else if (vec_distance_xy(a0 + 0x10, m) < 0.5f) {
            moby_set_state(a0, 0x14, -1);
            if (a0[0x43] != 0x13) {
                func_PAL_002A7E68(a0, 0x13, 0, 0xC);
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                moby_set_state(a0, 0x19, -1);
                if (a0[0x43] != 0x11) {
                    func_PAL_002A7E68(a0, 0x11, 0, 0x11);
                }
            }
        }
        break;
    case 13: {
        u8 *e;
        u8 *hit;
        e = D_L13_001B291C + (*(s32 *)(st + 0x2D4) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD) {
            if (a0[0x43] != 5) {
                func_PAL_002A7E68(a0, 5, 0, 8);
            }
            moby_set_state(a0, 0x16, 2);
            if (*(s32 *)(st + 0x280) == 1) {
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 8);
                }
                moby_set_state(a0, 0x14, 2);
            }
            if (*(s32 *)(st + 0x2D8) != 0) {
                moby_set_state(a0, 0xB, 2);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 8);
                }
                moby_set_controller_speed_limits(a0, 0.0048f, 0.120000005f, 0.010053098f, 1.0053098f);
            }
        } else {
            moby_transform_joint_to_world(a0, 0, m);
            if (CollLine(m, st + 0x1F0, 0, a0, 0) == 0) {
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, 8);
                }
                moby_set_state(a0, 0x16, 2);
                if (*(s32 *)(st + 0x280) == 1) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
            } else {
                hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                if (hit != 0 && (hit == g_hero_moby || *(s16 *)(hit + 0xAA) == 0xC87
                                 || hit == *(u8 **)(st + 0x200))) {
                    if (a0[0x43] != 5) {
                        func_PAL_002A7E68(a0, 5, 0, 8);
                    }
                    moby_set_state(a0, 0x16, 2);
                    if (*(s32 *)(st + 0x280) == 1) {
                        if (a0[0x43] != 0x13) {
                            func_PAL_002A7E68(a0, 0x13, 0, 8);
                        }
                        moby_set_state(a0, 0x14, 2);
                    }
                }
            }
        }
        break;
    }
    case 18:
        if (a0[0x60] & 2) {
            if (a0[0x43] != 0x13) {
                func_PAL_002A7E68(a0, 0x13, 0, 8);
            }
            moby_set_state(a0, 0x14, -1);
        }
        break;
    case 14:
        if (*(s32 *)(st + 0x2A0) != 0) {
            if (func_PAL_L13_0040E1B0(a0, D_L13_001FE580[*(s32 *)(st + 0x290)]) != 0) {
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, 8);
                }
                moby_set_state(a0, 0x16, 2);
                if (*(s32 *)(st + 0x280) == 1) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
                *(s32 *)(st + 0x290) = -1;
            }
        } else if (func_PAL_002B6CD8(a0, D_L13_001FE580[*(s32 *)(st + 0x290)]) != 0
                   || vec_distance_xy(a0 + 0x10, *(u8 **)(st + 0x200) + 0x10) < 8.0f) {
            moby_set_state(a0, 0x18, 2);
            if (a0[0x43] != 6) {
                func_PAL_002A7E68(a0, 6, 0, 8);
            }
            *(s32 *)(st + 0x290) = -1;
        }
        break;
    case 19: {
        u8 *hit;
        moby_transform_joint_to_world(a0, 0, m);
        FastVecSub(&m[4], st + 0x1F0, m);
        vec_scale_to_length(&m[4], &m[4], 0.8000001f);
        if (CollLine(m, st + 0x1F0, 0, a0, 0) == 0) {
            if (a0[0x43] != 5) {
                func_PAL_002A7E68(a0, 5, 0, 1);
            }
            moby_set_state(a0, 0x16, -1);
            if (*(s32 *)(st + 0x280) == 1) {
                if (a0[0x43] != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 8);
                }
                moby_set_state(a0, 0x14, 2);
            }
        } else {
            hit = *(u8 **)(D_L13_001BFD00 + 0x18);
            if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(st + 0x200)
                             || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                             || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x10CE
                             || *(s16 *)(hit + 0xAA) == 0x200 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, ((s32)(math_random_int_below(0xF)) * 5 + 2) / 6);
                }
                moby_set_state(a0, 0x16, -1);
                if (*(s32 *)(st + 0x280) == 1) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
            }
        }
        if (a0[0x60] & 2) {
            if (a0[0x42] == 0xE) {
                if (math_random_int_below(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_PAL_002A7E68(a0, 1, 0, 0x11);
                    }
                } else {
                    if (a0[0x43] != 0x16) {
                        func_PAL_002A7E68(a0, 0x16, 0, 8);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (a0[0x43] != 4) {
                        func_PAL_002A7E68(a0, 4, 0, 8);
                    }
                }
            } else {
                if (a0[0x43] != 0xE) {
                    func_PAL_002A7E68(a0, 0xE, 0, 0x11);
                }
            }
        }
        break;
    }
    case 20:
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A0) != 0) {
            func_PAL_L13_0040EDF0(a0);
        }
        if (func_PAL_002AF6C0(a0, 1.0f) != 0) {
            moby_transform_joint_to_world(a0, 0, m);
            FastVecSub(&m[4], st + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.8000001f);
            func_PAL_L13_00412518(a0, &m[4], m, 0, st[0x34]);
            (*(s32 *)(st + 0x28C))++;
        }
        if (a0[0x60] & 2) {
            if (*(s32 *)(st + 0x288) == *(s32 *)(st + 0x28C)) {
                s32 r;
                moby_set_state(a0, 0x18, -1);
                if (a0[0x43] != 6) {
                    func_PAL_002A7E68(a0, 6, 0, 8);
                }
                r = math_random_int_below(4);
                *(s32 *)(st + 0x28C) = 0;
                *(s32 *)(st + 0x288) = *(s32 *)(st + 0x284) + r;
            } else {
                if (a0[0x43] != 0xE) {
                    func_PAL_002A7E68(a0, 0xE, 0, ((s32)(math_random_int_below(5) + 0xA) * 5 + 2) / 6);
                }
                moby_set_state(a0, 0x13, -1);
            }
        }
        break;
    case 21: {
        u8 *hit;
        if (*(u16 *)(a0 + 0x96) >= 0x79) {
            moby_transform_joint_to_world(a0, 0, m);
            FastVecSub(&m[4], st + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.8000001f);
            if (CollLine(m, st + 0x1F0, 0, a0, 0) == 0) {
                if (a0[0x43] != 5) {
                    func_PAL_002A7E68(a0, 5, 0, 1);
                }
                moby_set_state(a0, 0x16, -1);
                if (*(s32 *)(st + 0x280) == 1) {
                    if (a0[0x43] != 0x13) {
                        func_PAL_002A7E68(a0, 0x13, 0, 8);
                    }
                    moby_set_state(a0, 0x14, 2);
                }
            } else {
                hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(st + 0x200)
                                 || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                 || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x10CE
                                 || *(s16 *)(hit + 0xAA) == 0x200 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                    if (a0[0x43] != 5) {
                        func_PAL_002A7E68(a0, 5, 0, ((s32)(math_random_int_below(0xF)) * 5 + 2) / 6);
                    }
                    moby_set_state(a0, 0x16, -1);
                    if (*(s32 *)(st + 0x280) == 1) {
                        if (a0[0x43] != 0x13) {
                            func_PAL_002A7E68(a0, 0x13, 0, 8);
                        }
                        moby_set_state(a0, 0x14, 2);
                    }
                }
            }
        }
        break;
    }
    case 22:
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A0) != 0) {
            func_PAL_L13_0040EDF0(a0);
        }
        if (func_PAL_002AF6C0(a0, 3.0f) != 0) {
            moby_transform_joint_to_world(a0, 0, m);
            FastVecSub(&m[4], st + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.8000001f);
            func_PAL_L13_00412518(a0, &m[4], m, 0, st[0x34]);
            (*(s32 *)(st + 0x28C))++;
        }
        if (a0[0x60] & 2) {
            if (*(s32 *)(st + 0x288) == *(s32 *)(st + 0x28C)) {
                moby_set_state(a0, 0x18, -1);
                if (a0[0x43] != 6) {
                    func_PAL_002A7E68(a0, 6, 0, 8);
                }
                if (math_random_int_below(2) == 1) {
                    *(s32 *)(st + 0x288) = *(s32 *)(st + 0x284) + math_random_int_below(4);
                }
                *(s32 *)(st + 0x28C) = 0;
            } else {
                if (a0[0x43] != 0xE) {
                    func_PAL_002A7E68(a0, 0xE, 0, ((s32)(math_random_int_below(5) + 0xA) * 5 + 2) / 6);
                }
                moby_set_state(a0, 0x15, -1);
            }
        }
        break;
    case 25:
        moby_start_effect_from_entry(a0, mat_fast_helper_a(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A0) != 0) {
            func_PAL_L13_0040EDF0(a0);
        }
        if (func_PAL_002AF6C0(a0, 3.0f) != 0) {
            moby_transform_joint_to_world(a0, 0, m);
            FastVecSub(&m[4], st + 0x1F0, m);
            vec_scale_to_length(&m[4], &m[4], 0.8000001f);
            func_PAL_L13_00412518(a0, &m[4], m, 0, st[0x34]);
            (*(s32 *)(st + 0x28C))++;
        }
        if ((a0[0x60] & 2) && *(s32 *)(st + 0x288) == *(s32 *)(st + 0x28C)) {
            moby_set_state(a0, 0x18, -1);
            if (a0[0x43] != 6) {
                func_PAL_002A7E68(a0, 6, 0, 0x11);
            }
            if (math_random_int_below(2) == 1) {
                *(s32 *)(st + 0x288) = *(s32 *)(st + 0x284) + math_random_int_below(4);
            }
            *(s32 *)(st + 0x28C) = 0;
        }
        break;
    case 23:
        *(TI128 *)m = ((L13Cam *)D_L13_001B2A0C)[*(s32 *)(st + 0x268)].v;
        func_PAL_L01_00323068(a0, m);
        if (vec_distance_xy(a0 + 0x10, m) < 0.5f) {
            *(s32 *)(st + 0x26C) = 1;
            moby_set_state(a0, 0x14, 2);
            if (a0[0x43] != 0x13) {
                func_PAL_002A7E68(a0, 0x13, 0, 0xC);
            }
        }
        break;
    case 24:
        if (a0[0x60] & 2) {
            if (a0[0x43] != 0xE) {
                func_PAL_002A7E68(a0, 0xE, 0, 8);
            }
            moby_set_state(a0, 0x15, 2);
            if (*(s32 *)(st + 0x280) == 1) {
                if (a0[0x43] != 0xE) {
                    func_PAL_002A7E68(a0, 0xE, 0, 8);
                }
                moby_set_state(a0, 0x13, 2);
            }
            if (*(s32 *)(st + 0x2A8) != 0 && g_hero_position[2] - *(float *)(a0 + 0x18) > 6.0f) {
                moby_set_state(a0, 0x19, -1);
                if (a0[0x43] != 0x11) {
                    func_PAL_002A7E68(a0, 0x11, 0, 0x11);
                }
            }
            if (*(s32 *)(st + 0x368) != 0 && vec_distance_xy(a0 + 0x10, st + 0x370) > 4.0f) {
                moby_set_state(a0, 0x1D, -1);
                if (a0[0x43] != 0xD) {
                    func_PAL_002A7E68(a0, 0xD, 0, 8);
                }
            }
        }
        break;
    case 1:
    default:
        break;
    }
    guard_update_hit_timer(a0);
}

int func_PAL_L13_0040D978(char *obj) {
    char *s = P(obj,0x68);
    if (!B(obj,0x20)) {
        qcopy(s+0x370,obj+0x10);
        F(s,0x30)=1.25f;
        if (math_random_int_below(2)) H(obj,0x34)|=0x8000;
        I(s,0x288)=I(s,0x284)+math_random_int_below(2);
        B(s,0x150)=0x1a; I(s,0x188)=4;
        F(s,0x17c)=0.15f; B(s,0x155)=12;
        I(s,0x28c)=0; I(s,0x26c)=0;
        F(s,0x174)=F(s,0x170)=0.5f;
        if (I(s,0x36c)!=-1) I(s,0x1bc)=I(s,0x36c);
        if (!S(s,0x24)) { S(s,0x24)=1; F(s,0x20)=1.0f; }
        F(s,0x84)=0.5f; F(s,0x54)=0.2f; F(s,0x50)=0.825f;
        F(s,0x5c)=F(s,0x58)=0.75f;
        F(s,0x60)=1.5707964897155762f; F(s,0x80)=0.523598849773407f;
        if (I(s,0x2a0)) {
            ((L13C3Flags *)s)->flags|=4; F(s,0x5c)=F(s,0x58)=0.7f;
            H(obj,0x34)|=0x100; F(s,0x60)=12.56637191772461f;
            ((L13C3Flags *)s)->flags|=1;
        }
        if (I(s,0x2a8)) { ((L13C3Flags *)s)->flags|=5; F(s,0x50)=0; F(s,0x180)=97.5f; }
        moby_set_controller_speed_limits(obj,0.0048f,0.120000005f,0.010053098f,1.0053098f);
        moby_set_state(obj,1,0);
        if (B(obj,0x43)!=21) func_PAL_002A7E68(obj,21,0,0);
        if (I(s,0x2b0)!=-1) {
            moby_set_state(obj,3,0); if (B(obj,0x43)!=3) func_PAL_002A7E68(obj,3,0,0);
            moby_set_controller_speed_limits(obj,0.0032000002f,0.080000006f,0.010053098f,1.0053098f);
        }
        if (I(s,0x294) && I(s,0x298)!=-1) moby_set_state(obj,27,5);
        if (I(s,0x2c4)) { moby_set_state(obj,5,0); if (B(obj,0x43)!=24) func_PAL_002A7E68(obj,24,0,0); }
        if (I(s,0x2d0)) {
            I(obj,0x98)=0; H(obj,0x34)=(H(obj,0x34)|0x41)&0xefff;
            moby_set_state(obj,1,8);
        }
        B(s,0x48)=FloatToInt(17.0f); B(s,0x4a)=FloatToInt(12.0f); B(s,0x29)=1;
    }
    if (B(obj,0x31) && fast_vec_dist(obj+0x10,D_L13_001B98C0)<24.0f) { moby_update_ground_check(obj); B(obj,0x6f)=22; }
    if (func_PAL_002B1A50(obj,s+0x140,0)) guard_alert_nearby((u8 *)obj);
    I(s,0x264)=weapon_select_aim_target(obj,I(s,0x260),0.0f,0.0f,0,0);
    I(s,0x278)=weapon_select_aim_target(obj,I(s,0x274),0.0f,0.0f,0,0);
    I(s,0x2b8)=weapon_select_aim_target(obj,I(s,0x2b4),0.0f,0.0f,0,0);
    I(s,0x250)=weapon_select_aim_target(obj,I(s,0x230),F(s,0x238),0.0f,0,0);
    I(s,0x254)=weapon_select_aim_target(obj,I(s,0x234),F(s,0x23c),0.0f,0,0);
    if (F(obj,0x18)<89.0f || (I(s,0x2a8) && F(obj,0x18)<98.0f)) {
        F(s,0x20)=0; func_PAL_002A7650(obj,0,3); return 1;
    }
    return 0;
}

