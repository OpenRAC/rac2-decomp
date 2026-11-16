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
extern void anim_start_blended_pal(char *,int,int,int);
extern int FloatToInt(float);
extern void moby_update_ground_check(char *);
extern int moby_apply_damage_to_object_pal(char *,char *,int);
extern int weapon_select_aim_target(char *,int,float,float,int,int);
extern void SetDeathBits_pal(char *,int,int);
extern char g_camera_l13_position[];
extern float fast_vec_dist(void *, void *);
extern void guard_alert_nearby(u8 *);
extern u8 *g_object_table_base __attribute__((section(".sdata")));
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
/* A 0x80-byte record of the level table at D_L13_001B2A0C; its point is at +0x30. */
typedef struct { u8 pad0[0x30]; TI128 point; u8 pad40[0x40]; } L13Cam;
extern char g_hero_state[];
extern float g_hero_position[];
extern u8 *g_hero_moby;
extern u8 *g_moby_slot_table __attribute__((section(".sdata")));
extern char g_collision_l13_result[];
extern s32 *g_guard_path_table[];
extern char g_str_guard_msg_a[];
extern char g_str_guard_msg_b[];
extern char g_str_guard_msg_c[];
extern char g_str_guard_msg_d[];
extern char g_str_guard_msg_e[];
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
extern int math_is_value_within_step_pal(void *, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern int moby_turn_toward_target_and_step_pal(void *, void *, float);
extern int path_follow_nodes_pal(void *, void *);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int moby_start_effect_from_entry(void *, float);
extern void part_queue_moby_for_glow(void *, int, void *);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
extern int path_check_entry_for_moby_pal(void *, int);
extern int rps_judge(void *);
extern int guard_init_check_pal(char *);
extern int creature_move_along_ground_pal(char *, char *);
extern int AdvancePathWaypoint_pal(void *, void *);
extern void moby_turn_toward_hero_pal(void *);
extern void guard_update_hit_timer(void *);
extern u8 *SpawnEA7Moby_pal(void *, void *, void *, int, float);

/* func_PAL_L13_0040B7AC, the PAL copy of func_L13_00406F18: the same C, where frame counts are scaled to 50 Hz,
   ((s32)(x) * 5 + 2) / 6, and per-frame rates grow by 6/5. */
/* The per-frame update of the level-13 guard: the action states (+0x95) first, then the
   animation states (+0x20), then the shared timer update. */
void guard_l13_update_pal(u8 *moby)
{
    float mat[16] __attribute__((aligned(16)));
    float vec[4];
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (guard_init_check_pal(moby) != 0) {
        part_queue_moby_for_glow(moby, 0, 0);
    }
    switch (moby[0x95]) {
    case 0: {
        s32 flag;
        flag = *(s32 *)(vars + 0x250);
        if (flag == 1 && math_fast_float_d(vars + 0x248) != 0) {
            if (*(s32 *)(vars + 0x2A8) == 0 || ((Hero *)g_hero_state)->h[0x348 / 2] == flag) {
                *(s32 *)(vars + 0x26C) = flag;
                moby_set_state(moby, 0x18, 2);
                if (moby[0x43] != 6) {
                    anim_start_blended_pal(moby, 6, 0, 8);
                }
                if (*(s32 *)(vars + 0x25C) != -1) {
                    moby_set_state(moby, 0xF, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended_pal(moby, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x290) != -1) {
                    moby_set_state(moby, 0xE, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended_pal(moby, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    u8 *linked = g_object_table_base + (*(s32 *)(vars + 0x2AC) << 8);
                    linked[0x20] = 3;
                    *(u8 **)(*(u8 **)(linked + 0x68) + 0xC) = moby;
                }
                if (*(s32 *)(vars + 0x2BC) != 0) {
                    moby_set_state(moby, 0xA, 7);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0xC);
                    }
                    moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.010053098f, 1.0053098f);
                }
            }
        } else if (*(s64 *)(vars + 0x278) == 1) {
            if (*(s32 *)(vars + 0x270) != -1) {
                moby_set_state(moby, 0x10, -1);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 8);
                }
                *(s32 *)(vars + 0x27C) = 1;
            }
        } else if (*(s32 *)(vars + 0x24C) != 0) {
            if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
                *(s32 *)(vars + 0x26C) = 1;
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 8);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
                if (*(s32 *)(vars + 0x25C) != -1) {
                    moby_set_state(moby, 0xF, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended_pal(moby, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x290) != -1) {
                    moby_set_state(moby, 0xE, 2);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended_pal(moby, 0xD, 0, 0xC);
                    }
                }
                if (*(s32 *)(vars + 0x2A8) != 0) {
                    u8 *linked = g_object_table_base + (*(s32 *)(vars + 0x2AC) << 8);
                    linked[0x20] = 3;
                    *(u8 **)(*(u8 **)(linked + 0x68) + 0xC) = moby;
                }
                if (*(s32 *)(vars + 0x2BC) != 0) {
                    moby_set_state(moby, 0xA, 7);
                    if (moby[0x43] != 3) {
                        anim_start_blended_pal(moby, 3, 0, 0xC);
                    }
                    moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.010053098f, 1.0053098f);
                }
            }
            *(s32 *)(vars + 0x24C) = 0;
            if (*(s32 *)(vars + 0x240) < 0xFA) {
                *(s32 *)(vars + 0x240) = ((s32)(math_random_int_range(0x1E0, 0x258)) * 5 + 2) / 6;
            }
        }
        break;
    }
    case 8: {
        s32 flag;
        s32 i;
        u8 *linked;
        if (*(s32 *)(vars + 0x294) != 0 && (i = *(s32 *)(vars + 0x298)) != -1) {
            linked = g_object_table_base + (i << 8);
            if (linked == 0 || linked[0x20] == 0xFE || linked[0x20] == 0xFD) {
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
                *(s32 *)(vars + 0x294) = 0;
                if (*(s32 *)(vars + 0x29C) != -1) {
                    moby_set_state(moby, 0x1C, 6);
                    if (moby[0x43] != 0xD) {
                        anim_start_blended_pal(moby, 0xD, 0, 0xC);
                    }
                } else {
                    if (moby[0x43] != 5) {
                        anim_start_blended_pal(moby, 5, 0, 8);
                    }
                    moby_set_state(moby, 0x16, 2);
                    if (*(s32 *)(vars + 0x280) == 1) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended_pal(moby, 0x13, 0, 8);
                        }
                        moby_set_state(moby, 0x14, 2);
                    }
                }
            }
        } else {
            flag = *(s32 *)(vars + 0x250);
            if (flag == 1 && math_fast_float_d(vars + 0x248) != 0) {
                *(s32 *)(vars + 0x26C) = flag;
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 8);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == flag) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
            } else {
                flag = moby[0xBC];
                if (flag == 1) {
                    *(s32 *)(vars + 0x26C) = flag;
                    if (moby[0x43] != 5) {
                        anim_start_blended_pal(moby, 5, 0, 8);
                    }
                    moby_set_state(moby, 0x16, 2);
                    if (*(s32 *)(vars + 0x280) == flag) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended_pal(moby, 0x13, 0, 8);
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
                anim_start_blended_pal(moby, 5, 0, 8);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 8);
                }
                moby_set_state(moby, 0x14, 2);
            }
            if (*(s32 *)(vars + 0x25C) != -1) {
                moby_set_state(moby, 0xF, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 0xC);
                }
            }
            if (*(s32 *)(vars + 0x290) != -1) {
                moby_set_state(moby, 0xE, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 0xC);
                }
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                u8 *linked = g_object_table_base + (*(s32 *)(vars + 0x2AC) << 8);
                linked[0x20] = 3;
                *(u8 **)(*(u8 **)(linked + 0x68) + 0xC) = moby;
            }
        }
        break;
    case 2: {
        s32 flag;
        if (*(s32 *)(vars + 0x250) != 1 && *(s32 *)(vars + 0x254) != 1 && moby[0x20] != 0xF) {
            moby_set_state(moby, 9, 1);
            if (moby[0x43] != 0x15) {
                anim_start_blended_pal(moby, 0x15, 0, 0x19);
            }
            *(s32 *)(vars + 0x240) = ((s32)(math_random_int_range(0x244, 0x258)) * 5 + 2) / 6;
            flag = math_random_int_below(2);
            *(s32 *)(vars + 0x28C) = 0;
            *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + flag;
        }
        if (*(s32 *)(vars + 0x264) == 1 && *(s32 *)(vars + 0x26C) == 0) {
            moby_set_state(moby, 0x17, 3);
            if (moby[0x43] != 0xD) {
                anim_start_blended_pal(moby, 0xD, 0, 0x11);
            }
            flag = math_random_int_below(2);
            *(s32 *)(vars + 0x28C) = 0;
            *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + flag;
        }
        break;
    }
    case 5: {
        u8 *linked;
        linked = g_object_table_base + (*(s32 *)(vars + 0x298) << 8);
        if (linked == 0 || linked[0x20] == 0xFE || linked[0x20] == 0xFD || *(s32 *)(vars + 0x2B8) == 1) {
            *(s32 *)(vars + 0x294) = 0;
            if (*(s32 *)(vars + 0x29C) != -1) {
                moby_set_state(moby, 0x1C, 6);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 0xC);
                }
            } else {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 8);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            }
        }
        break;
    }
    case 4: {
        s32 flag;
        u8 *linked;
        flag = moby_dispatch_action_by_kind(moby, vars + 0x140);
        if (flag & 1) {
            SetDeathBits_pal(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, 0);
            return;
        }
        if (flag & 2) {
            if (*(s32 *)(vars + 0x250) == 1 || *(s32 *)(vars + 0x254) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 8);
                }
                moby_set_state(moby, 0x14, 2);
            } else {
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 4) {
                        anim_start_blended_pal(moby, 4, 0, 8);
                    }
                }
                moby_set_state(moby, 9, 1);
                *(s32 *)(vars + 0x240) = ((s32)(math_random_int_range(0x244, 0x258)) * 5 + 2) / 6;
            }
            if (*(s32 *)(vars + 0x290) != -1) {
                moby_set_state(moby, 0xE, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 0xC);
                }
            }
            if (*(s32 *)(vars + 0x270) != -1 && *(s32 *)(vars + 0x26C) == 0) {
                moby_set_state(moby, 0x10, -1);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 8);
                }
            }
            if (*(s32 *)(vars + 0x294) != 0) {
                if (moby[0x43] != 0x15) {
                    anim_start_blended_pal(moby, 0x15, 0, 8);
                }
                moby_set_state(moby, 0x1B, 5);
            }
            linked = g_object_table_base + (*(s32 *)(vars + 0x2D4) << 8);
            if (*(s32 *)(vars + 0x2BC) != 0 && linked != 0 && linked[0x20] != 0xFE && linked[0x20] != 0xFD) {
                moby_set_state(moby, 0xA, 7);
                if (moby[0x43] != 3) {
                    anim_start_blended_pal(moby, 3, 0, 0xC);
                }
                moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.010053098f, 1.0053098f);
            }
        }
        if (*(float *)(vars + 0x20) <= 0.0f && *(u16 *)(moby + 0x96) == 0x28) {
            STUB_printf(g_str_guard_msg_a);
            moby_transform_joint_point(moby, 0, mat);
            vec_scale_to_length(vec, &mat[4], -1.0000001f);
            SpawnEA7Moby_pal(moby, vec, &mat[12], 0, vars[0x34]);
        }
        break;
    }
    }

    switch (moby[0x20]) {
    case 5:
        if (*(u16 *)(moby + 0x96) >= 0x38) {
            moby_set_state(moby, 6, -1);
            if (moby[0x43] != math_random_int_below(3) + 0x19) {
                anim_start_blended_pal(moby, math_random_int_below(3) + 0x19, 0, 2);
            }
            if (moby[0x43] == 0x19) {
                *(s32 *)(vars + 0x2CC) = 0;
                STUB_printf(g_str_guard_msg_b);
            } else if (moby[0x43] == 0x1B) {
                *(s32 *)(vars + 0x2CC) = 1;
                STUB_printf(g_str_guard_msg_c);
            } else {
                *(s32 *)(vars + 0x2CC) = 2;
                STUB_printf(g_str_guard_msg_d);
            }
        }
        break;
    case 8:
        if (*(u16 *)(moby + 0x96) >= 0x47) {
            moby_set_state(moby, 6, -1);
            if (moby[0x43] != math_random_int_below(3) + 0x19) {
                anim_start_blended_pal(moby, math_random_int_below(3) + 0x19, 0, 2);
            }
            if (moby[0x43] == 0x19) {
                *(s32 *)(vars + 0x2CC) = 0;
                STUB_printf(g_str_guard_msg_b);
            } else if (moby[0x43] == 0x1B) {
                *(s32 *)(vars + 0x2CC) = 1;
                STUB_printf(g_str_guard_msg_c);
            } else {
                *(s32 *)(vars + 0x2CC) = 2;
                STUB_printf(g_str_guard_msg_d);
            }
        }
        break;
    case 6: {
        s32 flag;
        if (*(u16 *)(moby + 0x96) >= 0x3D) {
            flag = rps_judge(moby);
            if (flag == 2) {
                moby_set_state(moby, 5, -1);
                if (moby[0x43] != 0x18) {
                    anim_start_blended_pal(moby, 0x18, 0, 2);
                }
            } else if (flag == 0) {
                moby_set_state(moby, 7, -1);
                if (moby[0x43] != 7) {
                    anim_start_blended_pal(moby, 7, 2, 0x16);
                }
            } else {
                moby_set_state(moby, 7, -1);
                if (moby[0x43] != 0x1C) {
                    anim_start_blended_pal(moby, 0x1C, 0, 8);
                }
            }
        }
        break;
    }
    case 7:
        if (*(u16 *)(moby + 0x96) >= 0x49) {
            moby_set_state(moby, 8, -1);
            if (moby[0x43] != 0x18) {
                anim_start_blended_pal(moby, 0x18, 0, 0xF);
            }
        }
        break;
    case 3:
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (AdvancePathWaypoint_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x2B0)]) != 0) {
                moby_set_state(moby, 4, -1);
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 0x16) {
                        anim_start_blended_pal(moby, 0x16, 0, 8);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (moby[0x43] != 4) {
                        anim_start_blended_pal(moby, 4, 0, 8);
                    }
                }
            }
        } else {
            if (path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x2B0)]) != 0) {
                moby_set_state(moby, 4, -1);
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 0x16) {
                        anim_start_blended_pal(moby, 0x16, 0, 8);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (moby[0x43] != 4) {
                        anim_start_blended_pal(moby, 4, 0, 8);
                    }
                }
            }
        }
        break;
    case 4: {
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
            moby_set_state(moby, 3, -1);
            if (moby[0x43] != 3) {
                anim_start_blended_pal(moby, 3, 0, 0x11);
            }
        }
        break;
    }
    case 16:
        if (path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x270)]) != 0) {
            *(s32 *)(vars + 0x26C) = 1;
            moby_set_state(moby, 2, -1);
            if (moby[0x43] != 0x15) {
                anim_start_blended_pal(moby, 0x15, 0, 8);
            }
        }
        break;
    case 2:
        STUB_printf(g_str_guard_msg_e);
        moby_set_state(moby, 1, -1);
        break;
    case 9:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x15) {
                anim_start_blended_pal(moby, 0x15, 0, 8);
            }
            moby_set_state(moby, 1, -1);
        }
        break;
    case 10: {
        u8 *linked;
        if (path_check_entry_for_moby_pal(moby, *(s32 *)(vars + 0x2C0)) != 0) {
            if (moby[0x43] != 0x15) {
                anim_start_blended_pal(moby, 0x15, 0, 8);
            }
            moby_set_state(moby, 0xD, -1);
        }
        linked = g_object_table_base + (*(s32 *)(vars + 0x2D4) << 8);
        if (linked == 0 || linked[0x20] == 0xFE || linked[0x20] == 0xFD
            || FastDiffRots(*(float *)(moby + 0xF8),
                             mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                           *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14))) > 1.7453294f) {
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 8);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 8);
                }
                moby_set_state(moby, 0x14, 2);
            }
            if (*(s32 *)(vars + 0x2D8) != 0) {
                moby_set_state(moby, 0xB, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 8);
                }
                moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.010053098f, 1.0053098f);
            }
        }
        break;
    }
    case 11:
        moby_turn_toward_target_and_step_pal(moby, vars + 0x1F0, *(float *)(vars + 0x2DC) * 0.017453294f);
        if (*(u16 *)(moby + 0x96) >= 0x65) {
            if (math_random_int_below(0xA) == 1) {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 8);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            }
        }
        break;
    case 28: {
        s32 flag;
        if (*(s32 *)(vars + 0x2A0) != 0) {
            flag = AdvancePathWaypoint_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x29C)]);
        } else {
            flag = path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x29C)]);
        }
        if (flag != 0 || vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x200) + 0x10) < 8.0f) {
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 8);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 8);
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
                    u8 *base = g_object_table_base;
                    (base + (i << 8))[0x20] = 4;
                    (base + (j << 8))[0x20] = 4;
                    *(s32 *)(vars + 0x360) = -1;
                    *(s32 *)(vars + 0x364) = -1;
                }
            }
        }
        *(TI128 *)mat = ((L13Cam *)g_moby_slot_table)[*(s32 *)(vars + 0x25C)].point;
        if (*(s32 *)(vars + 0x2A0) != 0) {
            creature_move_along_ground_pal(moby, mat);
        } else {
            moby_l01_turn_toward_target_pal(moby, mat);
        }
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (vec_distance_xy(moby + 0x10, mat) < 0.9f) {
                moby_set_state(moby, 0x14, -1);
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 0xC);
                }
            }
        } else if (vec_distance_xy(moby + 0x10, mat) < 0.5f) {
            moby_set_state(moby, 0x14, -1);
            if (moby[0x43] != 0x13) {
                anim_start_blended_pal(moby, 0x13, 0, 0xC);
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 0x11) {
                    anim_start_blended_pal(moby, 0x11, 0, 0x11);
                }
            }
        }
        break;
    }
    case 29:
        *(TI128 *)mat = *(TI128 *)(vars + 0x370);
        if (*(s32 *)(vars + 0x2A0) != 0) {
            creature_move_along_ground_pal(moby, mat);
        } else {
            moby_l01_turn_toward_target_pal(moby, mat);
        }
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (vec_distance_xy(moby + 0x10, mat) < 0.9f) {
                moby_set_state(moby, 0x14, -1);
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 0xC);
                }
            }
        } else if (vec_distance_xy(moby + 0x10, mat) < 0.5f) {
            moby_set_state(moby, 0x14, -1);
            if (moby[0x43] != 0x13) {
                anim_start_blended_pal(moby, 0x13, 0, 0xC);
            }
            if (*(s32 *)(vars + 0x2A8) != 0) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 0x11) {
                    anim_start_blended_pal(moby, 0x11, 0, 0x11);
                }
            }
        }
        break;
    case 13: {
        u8 *linked;
        u8 *hit;
        linked = g_object_table_base + (*(s32 *)(vars + 0x2D4) << 8);
        if (linked == 0 || linked[0x20] == 0xFE || linked[0x20] == 0xFD) {
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 8);
            }
            moby_set_state(moby, 0x16, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 8);
                }
                moby_set_state(moby, 0x14, 2);
            }
            if (*(s32 *)(vars + 0x2D8) != 0) {
                moby_set_state(moby, 0xB, 2);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 8);
                }
                moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.010053098f, 1.0053098f);
            }
        } else {
            moby_transform_joint_to_world(moby, 0, mat);
            if (CollLine(mat, vars + 0x1F0, 0, moby, 0) == 0) {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 8);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            } else {
                hit = *(u8 **)(g_collision_l13_result + 0x18);
                if (hit != 0 && (hit == g_hero_moby || *(s16 *)(hit + 0xAA) == 0xC87
                                 || hit == *(u8 **)(vars + 0x200))) {
                    if (moby[0x43] != 5) {
                        anim_start_blended_pal(moby, 5, 0, 8);
                    }
                    moby_set_state(moby, 0x16, 2);
                    if (*(s32 *)(vars + 0x280) == 1) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended_pal(moby, 0x13, 0, 8);
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
                anim_start_blended_pal(moby, 0x13, 0, 8);
            }
            moby_set_state(moby, 0x14, -1);
        }
        break;
    case 14:
        if (*(s32 *)(vars + 0x2A0) != 0) {
            if (AdvancePathWaypoint_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x290)]) != 0) {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 8);
                }
                moby_set_state(moby, 0x16, 2);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
                *(s32 *)(vars + 0x290) = -1;
            }
        } else if (path_follow_nodes_pal(moby, g_guard_path_table[*(s32 *)(vars + 0x290)]) != 0
                   || vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x200) + 0x10) < 8.0f) {
            moby_set_state(moby, 0x18, 2);
            if (moby[0x43] != 6) {
                anim_start_blended_pal(moby, 6, 0, 8);
            }
            *(s32 *)(vars + 0x290) = -1;
        }
        break;
    case 19: {
        u8 *hit;
        moby_transform_joint_to_world(moby, 0, mat);
        FastVecSub(&mat[4], vars + 0x1F0, mat);
        vec_scale_to_length(&mat[4], &mat[4], 0.8000001f);
        if (CollLine(mat, vars + 0x1F0, 0, moby, 0) == 0) {
            if (moby[0x43] != 5) {
                anim_start_blended_pal(moby, 5, 0, 1);
            }
            moby_set_state(moby, 0x16, -1);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0x13) {
                    anim_start_blended_pal(moby, 0x13, 0, 8);
                }
                moby_set_state(moby, 0x14, 2);
            }
        } else {
            hit = *(u8 **)(g_collision_l13_result + 0x18);
            if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(vars + 0x200)
                             || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                             || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x10CE
                             || *(s16 *)(hit + 0xAA) == 0x200 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, ((s32)(math_random_int_below(0xF)) * 5 + 2) / 6);
                }
                moby_set_state(moby, 0x16, -1);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            }
        }
        if (moby[0x60] & 2) {
            if (moby[0x42] == 0xE) {
                if (math_random_int_below(2) == 1) {
                    if (moby[0x43] != 1) {
                        anim_start_blended_pal(moby, 1, 0, 0x11);
                    }
                } else {
                    if (moby[0x43] != 0x16) {
                        anim_start_blended_pal(moby, 0x16, 0, 8);
                    }
                }
                if (math_random_int_below(3) == 1) {
                    if (moby[0x43] != 4) {
                        anim_start_blended_pal(moby, 4, 0, 8);
                    }
                }
            } else {
                if (moby[0x43] != 0xE) {
                    anim_start_blended_pal(moby, 0xE, 0, 0x11);
                }
            }
        }
        break;
    }
    case 20:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A0) != 0) {
            moby_turn_toward_hero_pal(moby);
        }
        if (math_is_value_within_step_pal(moby, 1.0f) != 0) {
            moby_transform_joint_to_world(moby, 0, mat);
            FastVecSub(&mat[4], vars + 0x1F0, mat);
            vec_scale_to_length(&mat[4], &mat[4], 0.8000001f);
            SpawnEA7Moby_pal(moby, &mat[4], mat, 0, vars[0x34]);
            (*(s32 *)(vars + 0x28C))++;
        }
        if (moby[0x60] & 2) {
            if (*(s32 *)(vars + 0x288) == *(s32 *)(vars + 0x28C)) {
                s32 flag;
                moby_set_state(moby, 0x18, -1);
                if (moby[0x43] != 6) {
                    anim_start_blended_pal(moby, 6, 0, 8);
                }
                flag = math_random_int_below(4);
                *(s32 *)(vars + 0x28C) = 0;
                *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + flag;
            } else {
                if (moby[0x43] != 0xE) {
                    anim_start_blended_pal(moby, 0xE, 0, ((s32)(math_random_int_below(5) + 0xA) * 5 + 2) / 6);
                }
                moby_set_state(moby, 0x13, -1);
            }
        }
        break;
    case 21: {
        u8 *hit;
        if (*(u16 *)(moby + 0x96) >= 0x79) {
            moby_transform_joint_to_world(moby, 0, mat);
            FastVecSub(&mat[4], vars + 0x1F0, mat);
            vec_scale_to_length(&mat[4], &mat[4], 0.8000001f);
            if (CollLine(mat, vars + 0x1F0, 0, moby, 0) == 0) {
                if (moby[0x43] != 5) {
                    anim_start_blended_pal(moby, 5, 0, 1);
                }
                moby_set_state(moby, 0x16, -1);
                if (*(s32 *)(vars + 0x280) == 1) {
                    if (moby[0x43] != 0x13) {
                        anim_start_blended_pal(moby, 0x13, 0, 8);
                    }
                    moby_set_state(moby, 0x14, 2);
                }
            } else {
                hit = *(u8 **)(g_collision_l13_result + 0x18);
                if (hit != 0 && (hit == g_hero_moby || hit == *(u8 **)(vars + 0x200)
                                 || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                 || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x10CE
                                 || *(s16 *)(hit + 0xAA) == 0x200 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                    if (moby[0x43] != 5) {
                        anim_start_blended_pal(moby, 5, 0, ((s32)(math_random_int_below(0xF)) * 5 + 2) / 6);
                    }
                    moby_set_state(moby, 0x16, -1);
                    if (*(s32 *)(vars + 0x280) == 1) {
                        if (moby[0x43] != 0x13) {
                            anim_start_blended_pal(moby, 0x13, 0, 8);
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
            moby_turn_toward_hero_pal(moby);
        }
        if (math_is_value_within_step_pal(moby, 3.0f) != 0) {
            moby_transform_joint_to_world(moby, 0, mat);
            FastVecSub(&mat[4], vars + 0x1F0, mat);
            vec_scale_to_length(&mat[4], &mat[4], 0.8000001f);
            SpawnEA7Moby_pal(moby, &mat[4], mat, 0, vars[0x34]);
            (*(s32 *)(vars + 0x28C))++;
        }
        if (moby[0x60] & 2) {
            if (*(s32 *)(vars + 0x288) == *(s32 *)(vars + 0x28C)) {
                moby_set_state(moby, 0x18, -1);
                if (moby[0x43] != 6) {
                    anim_start_blended_pal(moby, 6, 0, 8);
                }
                if (math_random_int_below(2) == 1) {
                    *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + math_random_int_below(4);
                }
                *(s32 *)(vars + 0x28C) = 0;
            } else {
                if (moby[0x43] != 0xE) {
                    anim_start_blended_pal(moby, 0xE, 0, ((s32)(math_random_int_below(5) + 0xA) * 5 + 2) / 6);
                }
                moby_set_state(moby, 0x15, -1);
            }
        }
        break;
    case 25:
        moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(*(u8 **)(vars + 0x200) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(vars + 0x200) + 0x14) - *(float *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x2A0) != 0) {
            moby_turn_toward_hero_pal(moby);
        }
        if (math_is_value_within_step_pal(moby, 3.0f) != 0) {
            moby_transform_joint_to_world(moby, 0, mat);
            FastVecSub(&mat[4], vars + 0x1F0, mat);
            vec_scale_to_length(&mat[4], &mat[4], 0.8000001f);
            SpawnEA7Moby_pal(moby, &mat[4], mat, 0, vars[0x34]);
            (*(s32 *)(vars + 0x28C))++;
        }
        if ((moby[0x60] & 2) && *(s32 *)(vars + 0x288) == *(s32 *)(vars + 0x28C)) {
            moby_set_state(moby, 0x18, -1);
            if (moby[0x43] != 6) {
                anim_start_blended_pal(moby, 6, 0, 0x11);
            }
            if (math_random_int_below(2) == 1) {
                *(s32 *)(vars + 0x288) = *(s32 *)(vars + 0x284) + math_random_int_below(4);
            }
            *(s32 *)(vars + 0x28C) = 0;
        }
        break;
    case 23:
        *(TI128 *)mat = ((L13Cam *)g_moby_slot_table)[*(s32 *)(vars + 0x268)].point;
        moby_l01_turn_toward_target_pal(moby, mat);
        if (vec_distance_xy(moby + 0x10, mat) < 0.5f) {
            *(s32 *)(vars + 0x26C) = 1;
            moby_set_state(moby, 0x14, 2);
            if (moby[0x43] != 0x13) {
                anim_start_blended_pal(moby, 0x13, 0, 0xC);
            }
        }
        break;
    case 24:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0xE) {
                anim_start_blended_pal(moby, 0xE, 0, 8);
            }
            moby_set_state(moby, 0x15, 2);
            if (*(s32 *)(vars + 0x280) == 1) {
                if (moby[0x43] != 0xE) {
                    anim_start_blended_pal(moby, 0xE, 0, 8);
                }
                moby_set_state(moby, 0x13, 2);
            }
            if (*(s32 *)(vars + 0x2A8) != 0 && g_hero_position[2] - *(float *)(moby + 0x18) > 6.0f) {
                moby_set_state(moby, 0x19, -1);
                if (moby[0x43] != 0x11) {
                    anim_start_blended_pal(moby, 0x11, 0, 0x11);
                }
            }
            if (*(s32 *)(vars + 0x368) != 0 && vec_distance_xy(moby + 0x10, vars + 0x370) > 4.0f) {
                moby_set_state(moby, 0x1D, -1);
                if (moby[0x43] != 0xD) {
                    anim_start_blended_pal(moby, 0xD, 0, 8);
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

/* Sets up a guard on its first frame from its path and settings, then keeps its ground check
 * and aim targets up to date; returns 1 when the guard is gone. (PAL) */
int guard_init_check_pal(char *moby) {
    char *vars = P(moby,0x68);
    if (!B(moby,0x20)) {
        qcopy(vars+0x370,moby+0x10);
        F(vars,0x30)=1.25f;
        if (math_random_int_below(2)) H(moby,0x34)|=0x8000;
        I(vars,0x288)=I(vars,0x284)+math_random_int_below(2);
        B(vars,0x150)=0x1a; I(vars,0x188)=4;
        F(vars,0x17c)=0.15f; B(vars,0x155)=12;
        I(vars,0x28c)=0; I(vars,0x26c)=0;
        F(vars,0x174)=F(vars,0x170)=0.5f;
        if (I(vars,0x36c)!=-1) I(vars,0x1bc)=I(vars,0x36c);
        if (!S(vars,0x24)) { S(vars,0x24)=1; F(vars,0x20)=1.0f; }
        F(vars,0x84)=0.5f; F(vars,0x54)=0.2f; F(vars,0x50)=0.825f;
        F(vars,0x5c)=F(vars,0x58)=0.75f;
        F(vars,0x60)=1.5707964897155762f; F(vars,0x80)=0.523598849773407f;
        if (I(vars,0x2a0)) {
            ((L13C3Flags *)vars)->flags|=4; F(vars,0x5c)=F(vars,0x58)=0.7f;
            H(moby,0x34)|=0x100; F(vars,0x60)=12.56637191772461f;
            ((L13C3Flags *)vars)->flags|=1;
        }
        if (I(vars,0x2a8)) { ((L13C3Flags *)vars)->flags|=5; F(vars,0x50)=0; F(vars,0x180)=97.5f; }
        moby_set_controller_speed_limits(moby,0.0048f,0.120000005f,0.010053098f,1.0053098f);
        moby_set_state(moby,1,0);
        if (B(moby,0x43)!=21) anim_start_blended_pal(moby,21,0,0);
        if (I(vars,0x2b0)!=-1) {
            moby_set_state(moby,3,0); if (B(moby,0x43)!=3) anim_start_blended_pal(moby,3,0,0);
            moby_set_controller_speed_limits(moby,0.0032000002f,0.080000006f,0.010053098f,1.0053098f);
        }
        if (I(vars,0x294) && I(vars,0x298)!=-1) moby_set_state(moby,27,5);
        if (I(vars,0x2c4)) { moby_set_state(moby,5,0); if (B(moby,0x43)!=24) anim_start_blended_pal(moby,24,0,0); }
        if (I(vars,0x2d0)) {
            I(moby,0x98)=0; H(moby,0x34)=(H(moby,0x34)|0x41)&0xefff;
            moby_set_state(moby,1,8);
        }
        B(vars,0x48)=FloatToInt(17.0f); B(vars,0x4a)=FloatToInt(12.0f); B(vars,0x29)=1;
    }
    if (B(moby,0x31) && fast_vec_dist(moby+0x10,g_camera_l13_position)<24.0f) { moby_update_ground_check(moby); B(moby,0x6f)=22; }
    if (moby_apply_damage_to_object_pal(moby,vars+0x140,0)) guard_alert_nearby((u8 *)moby);
    I(vars,0x264)=weapon_select_aim_target(moby,I(vars,0x260),0.0f,0.0f,0,0);
    I(vars,0x278)=weapon_select_aim_target(moby,I(vars,0x274),0.0f,0.0f,0,0);
    I(vars,0x2b8)=weapon_select_aim_target(moby,I(vars,0x2b4),0.0f,0.0f,0,0);
    I(vars,0x250)=weapon_select_aim_target(moby,I(vars,0x230),F(vars,0x238),0.0f,0,0);
    I(vars,0x254)=weapon_select_aim_target(moby,I(vars,0x234),F(vars,0x23c),0.0f,0,0);
    if (F(moby,0x18)<89.0f || (I(vars,0x2a8) && F(moby,0x18)<98.0f)) {
        F(vars,0x20)=0; SetDeathBits_pal(moby,0,3); return 1;
    }
    return 0;
}

