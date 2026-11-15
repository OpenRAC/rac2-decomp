#include "common.h"

/* func_PAL_L11_00434418, the PAL copy of func_L11_0042F018: the same C (see that unit for what it
   took), where frame counts become ((s32)(x) * 5 + 2) / 6, speeds gain 6/5 and accelerations 36/25,
   and the func_002AEB60(arg0, 3.0f) call is replaced by a 2.8333335f..3.25f window on two
   func_0029F530 calls. Its own -G8 unit with -frac2-hazard-labels, as USA's. */

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

extern char g_hero_state[];
extern s32 D_L11_001CAE40[];
extern s32 *D_L11_001FF580[];
extern u8 *const g_moby_l11_table[] __attribute__((sda));
extern u8 *D_L11_001B368C[] __attribute__((sda));
extern s32 D_L11_001AED04[] __attribute__((sda));
extern char D_L11_001A8F20[] __attribute__((sda));
extern u8 D_L11_001C8A40[];
extern TI128 D_L11_001C0D20;

extern void func_PAL_L11_00436D20(u8 *);
extern void saur_beast_step_timer_clear_flags(u8 *);
extern void saur_beast_draw_beam(u8 *);
extern void func_PAL_L11_00437B08(u8 *, void *);
extern s32 flag_set_second_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, f32, f32, f32, f32);
extern void moby_set_state(u8 *, s32, s32);
extern void func_PAL_002A7E68(u8 *a0, u32 a1, u32 a2, u32 a3);
extern s32 math_random_int_range(s32, s32);
extern s32 math_random_int_below(s32);
extern s32 point_in_path_xy(void *, void *, s32);
extern s32 moby_dispatch_action_by_kind(u8 *, void *);
extern void func_PAL_002A7650(u8 *, s32, s32);
extern void part_queue_moby_for_glow(u8 *, s32, void *);
extern void moby_mark_spawned(void *);
extern f32 math_random_float_range(f32, f32);
extern s32 math_fast_float_d(void *);
extern f32 ApproachValue(f32 *, f32, f32);
extern void func_PAL_002AF420(u8 *, void *, f32, f32);
extern s32 func_PAL_002B6CD8(u8 *, void *);
extern s32 path_set_follower_nodes(u8 *, void *, s32, s32);
extern f32 moby_turn_toward_position(u8 *, void *, void *, f32, f32, f32);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern s32 func_PAL_L01_00323068(u8 *, void *);
extern void moby_transform_joint_to_world(u32 a0, s32 a1, f32 *a2);
extern f32 math_fast_sin_or_cos_a(f32 a0);
extern f32 math_fast_sin_or_cos_b(f32 a0);
extern void FastVecScale(void *, void *, f32);
extern void make_hit_descriptor(void *, void *, s32, f32, void *);
extern s32 coll_process_hit(void *, f32, s32, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 func_PAL_L02_00333638(u8 *, void *, f32, s32, f32, f32);
extern f32 moby_get_anim_value(u8 *);
extern void part_spawn_ground_effect(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern s32 coll_test_hit_at_bone(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern void moby_set_flag_bit(u8 *, s32);
extern s32 part_l00_alloc_effect_slot_2(void *, f32, f32, f32, f32, f32);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 flag_is_third_pending_set(u8 *);
extern void func_PAL_L04_003E96E0(void *, s32);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_free_point_light(s32);
extern s32 func_PAL_002B5C98(u8 *, void *, f32);
extern void anim_play_on_self_and_owner(u8 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

void func_PAL_L11_00434418(u8 *arg0) {
    u8 *data;

    if (D_L11_001CAE40[0] != 0 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x6F) {
        arg0[0xBC] = 1;
        *(s32 *)(arg0 + 0x98) = 0;
        *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    if (arg0[0xBC] != 0) {
        *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) & 0xFFBE) | 0x1000;
        *(s32 *)(arg0 + 0x98) = *(s32 *)(*(u8 **)(arg0 + 0x24) + 0x10);
        arg0[0xBC] = 0;
    }
    data = *(u8 **)(arg0 + 0x68);
    func_PAL_L11_00436D20(arg0);

    switch (arg0[0x95]) {
    case 0:
        if (flag_set_second_pending(arg0) != 0) {
            moby_set_controller_speed_limits(arg0, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (*(f32 *)(data + 0x290) < 0.2f)
                anim_play_on_self_and_owner(arg0, 0, 0, 0, 0xA);
            if (*(s32 *)(data + 0x29C) != -1) {
                anim_play_on_self_and_owner(arg0, 5, 4, 0, 0xA);
                moby_set_state(arg0, 5, -1);
            }
        }
        if (*(s16 *)(data + 0x274) == 2 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6F && *(s32 *)(data + 0x2C8) == 0) {
            if (*(s32 *)(data + 0x294) != -1) {
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
                moby_set_controller_speed_limits(arg0, 0.024f, 0.6f, 0.0016755164f, 0.12566373f);
                *(f32 *)(data + 0x164) = 0.008f;
                moby_set_state(arg0, 0x11, 2);
            } else if (*(u8 **)(data + 0x27C) != 0) {
                moby_set_state(arg0, 0xE, 2);
            } else {
                anim_play_on_self_and_owner(arg0, 2, 2, 0, 8);
                moby_set_state(arg0, 0xE, 2);
            }
        } else if (*(s16 *)(data + 0x276) != 0) {
            moby_set_state(arg0, 0xB, 1);
            *(s16 *)(data + 0x276) = 0;
            if (*(s16 *)(data + 0x270) < 0xFA)
                *(s16 *)(data + 0x270) = ((s32)(math_random_int_range(0x1E0, 0x258)) * 5 + 2) / 6;
            if (*(s32 *)(data + 0x29C) != -1) {
                moby_set_state(arg0, 0xB, 0xC);
                anim_play_on_self_and_owner(arg0, 4, 3, 0, 0xA);
            }
        } else if (*(s32 *)(data + 0x2AC) != -1 &&
                   point_in_path_xy(&((Hero *)g_hero_state)->f[0x80 / 4], (u8 *)D_L11_001FF580[*(s32 *)(data + 0x2AC)] + 0x10,
                                 *D_L11_001FF580[*(s32 *)(data + 0x2AC)]) != 0) {
            anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
            moby_set_controller_speed_limits(arg0, 0.024f, 0.6f, 0.0016755164f, 0.12566373f);
            *(f32 *)(data + 0x164) = 0.008f;
            moby_set_state(arg0, 0x11, 2);
        }
        break;
    case 1:
        if (flag_set_second_pending(arg0) != 0)
            moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if ((u16)(*(s16 *)(data + 0x274) - 1) < 2) {
            if (*(u8 **)(data + 0x27C) != 0) {
                moby_set_state(arg0, 0xE, 2);
            } else if (*(s32 *)(data + 0x294) != -1) {
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
                moby_set_controller_speed_limits(arg0, 0.024f, 0.6f, 0.0016755164f, 0.12566373f);
                *(f32 *)(data + 0x164) = 0.008f;
                moby_set_state(arg0, 0x11, 2);
            } else {
                anim_play_on_self_and_owner(arg0, 2, 2, 0, 8);
                moby_set_state(arg0, 0xE, 2);
            }
        } else if (*(s16 *)(data + 0x270) == 0) {
            moby_set_state(arg0, 1, 0);
            anim_play_on_self_and_owner(arg0, 5, 4, 0, 0xA);
        }
        break;
    case 2:
        if (flag_set_second_pending(arg0) != 0)
            moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if (*(s32 *)(data + 0x2AC) == -1 ||
            point_in_path_xy(&((Hero *)g_hero_state)->f[0x80 / 4], (u8 *)D_L11_001FF580[*(s32 *)(data + 0x2AC)] + 0x10,
                          *D_L11_001FF580[*(s32 *)(data + 0x2AC)]) == 0) {
            if ((u16)(*(s16 *)(data + 0x274) - 1) >= 2) {
                if (arg0[0x20] == 0x11 || arg0[0x20] == 0x14 || arg0[0x20] == 0x10) {
                } else if (arg0[0x20] == 0x13) {
                    anim_play_on_self_and_owner(arg0, 8, 0, 1, 2);
                    moby_set_state(arg0, 0x14, -1);
                } else if (*(s32 *)(data + 0x29C) != -1 && *(s32 *)(data + 0x294) == -1) {
                    anim_play_on_self_and_owner(arg0, 5, 4, 0, 0xA);
                    moby_set_state(arg0, 5, 1);
                } else {
                    *(s32 *)(data + 0x2A0) = 0;
                    anim_play_on_self_and_owner(arg0, 3, 1, 0, 0xA);
                    moby_set_state(arg0, 0xB, 1);
                    if (*(s32 *)(data + 0x2A4) != -1) {
                        qcopy(data + 0x110, D_L11_001B368C[0] + (*(s32 *)(data + 0x2A4) << 7) + 0x30);
                        if (*(f32 *)(data + 0x12C) == 0.0f)
                            *(f32 *)(data + 0x12C) = 4.0f;
                    }
                    *(s16 *)(data + 0x270) = ((s32)(math_random_int_range(0x4B0, 0x514)) * 5 + 2) / 6;
                }
            }
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x31 && *(s32 *)(data + 0x2C4) != -1) {
                if (arg0[0x43] != 6)
                    func_PAL_002A7E68(arg0, 6, 0, ((s32)(math_random_int_range(5, 0xF)) * 5 + 2) / 6);
                moby_set_state(arg0, 0xD, 4);
                moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.004886923f, 0.31415933f);
            }
            if (*(s32 *)(data + 0x2BC) != -1 && *(s16 *)(data + 0x274) != 2 && *(u8 **)(data + 0x27C) != 0 &&
                (g_moby_l11_table[0] + (*(s32 *)(data + 0x2BC) << 8))[0x20] != 2) {
                moby_set_state(arg0, 2, 0);
                anim_play_on_self_and_owner(arg0, 4, 1, 0, 0xC);
                *(f32 *)(arg0 + 0x48) = math_random_float_range(0.5f, 1.25f);
            }
        }
        break;
    case 4:
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x31) {
            if (arg0[0x43] != 6)
                func_PAL_002A7E68(arg0, 6, 0, 8);
            moby_set_state(arg0, 0xF, 2);
        }
        break;
    case 3: {
        s32 r;

        r = moby_dispatch_action_by_kind(arg0, data + 0x60);
        if (r & 1) {
            D_L11_001AED04[0] = D_L11_001AED04[0] - 1;
            func_PAL_002A7650(arg0, 0, 3);
            part_queue_moby_for_glow(arg0, 0, 0);
            return;
        }
        if (r & 2) {
            if ((u16)(*(s16 *)(data + 0x274) - 1) < 2) {
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
                moby_set_state(arg0, 0xF, 2);
                if (*(s32 *)(data + 0x2BC) != -1) {
                    moby_set_state(arg0, 0x18, -1);
                    anim_play_on_self_and_owner(arg0, 0xF, 4, 0, 8);
                }
            } else {
                moby_set_state(arg0, 0xB, 1);
                anim_play_on_self_and_owner(arg0, 1, 1, 0, 8);
                *(s16 *)(data + 0x270) = ((s32)(math_random_int_range(0x244, 0x258)) * 5 + 2) / 6;
                if (*(s32 *)(data + 0x29C) != -1) {
                    moby_set_state(arg0, 0xB, 0xC);
                    anim_play_on_self_and_owner(arg0, 4, 3, 0, 0xA);
                }
            }
        }
        break;
    }
    }

    switch (arg0[0x20]) {
    case 1:
        if (*(f32 *)(data + 0x290) > 0.2f) {
            math_fast_float_d(data + 0x28C);
            if (*(s32 *)(data + 0x28C) >= 0x12)
                *(f32 *)(data + 0x124) = 0.080000006f;
            else
                ApproachValue((f32 *)(data + 0x124), 0.0f, 0.0016000001f);
            if (arg0[0x43] == 5) {
                if (*(s32 *)(data + 0x28C) == 0) {
                    anim_play_on_self_and_owner(arg0, 1, 1, 0, 0xA);
                    if (math_random_int_below(2) == 1)
                        anim_play_on_self_and_owner(arg0, 0, 0, 0, 0xA);
                }
                func_PAL_002AF420(arg0, data + 0x110, 0.35f, 0.25f);
            } else if (arg0[0x43] < 2 && (arg0[0x60] & 2)) {
                *(s32 *)(data + 0x28C) = math_random_int_range(0x64, 0x247);
                anim_play_on_self_and_owner(arg0, 5, 4, 0, 0xA);
            }
        } else if (*(u8 **)(data + 0x27C) != 0 && (*(u8 **)(data + 0x27C))[0x43] != 0) {
            anim_play_on_self_and_owner(arg0, 0, 0, 0, 0xA);
        }
        break;
    case 2:
        if ((g_moby_l11_table[0] + (*(s32 *)(data + 0x2BC) << 8))[0x20] == 2 && *(u8 **)(data + 0x27C) != 0) {
            moby_set_state(arg0, 3, -1);
            func_PAL_002A7E68(*(u8 **)(data + 0x27C), 0xB, 0, 0xC);
        }
        break;
    case 3: {
        u8 *p;

        p = *(u8 **)(data + 0x27C);
        if ((p[0x60] & 2) || p == 0)
            moby_set_state(arg0, 0xE, 2);
        break;
    }
    case 5:
        if (*(s32 *)(data + 0x29C) != -1 && func_PAL_002B6CD8(arg0, D_L11_001FF580[*(s32 *)(data + 0x29C)]) != 0) {
            moby_set_state(arg0, 7, -1);
            anim_play_on_self_and_owner(arg0, 4, 3, 0, 8);
            path_set_follower_nodes(arg0, D_L11_001FF580[*(s32 *)(data + 0x29C)], 0, 1);
            *(s32 *)(data + 0x2C0) = 1;
        }
        break;
    case 6:
        if (*(s32 *)(data + 0x29C) != -1 && func_PAL_002B6CD8(arg0, D_L11_001FF580[*(s32 *)(data + 0x29C)]) != 0) {
            moby_set_state(arg0, 7, -1);
            anim_play_on_self_and_owner(arg0, 4, 3, 0, 8);
            path_set_follower_nodes(arg0, D_L11_001FF580[*(s32 *)(data + 0x29C)], 1, 0);
            *(s32 *)(data + 0x2C0) = 0;
        }
        break;
    case 7:
        if (arg0[0x60] & 2) {
            anim_play_on_self_and_owner(arg0, 0xE, 0xA, 0, 6);
            moby_set_state(arg0, 0x19, -1);
        }
        break;
    case 13:
        func_PAL_002B6CD8(arg0, D_L11_001FF580[*(s32 *)(data + 0x2C4)]);
        break;
    case 11:
        math_fast_float_d(data + 0x28C);
        if (*(s32 *)(data + 0x28C) >= 0x12)
            ApproachValue((f32 *)(data + 0x124), 0.080000006f, 0.0028000001f);
        else
            ApproachValue((f32 *)(data + 0x124), 0.0f, 0.0028000001f);
        if (arg0[0x43] == 6) {
            if (*(s32 *)(data + 0x28C) == 0) {
                anim_play_on_self_and_owner(arg0, 3, 2, 0, 0xA);
                if (math_random_int_below(2) == 1)
                    anim_play_on_self_and_owner(arg0, 4, 3, 0, 0xA);
            }
            func_PAL_002AF420(arg0, data + 0x110, 0.35f, 0.25f);
        } else if ((u8)(arg0[0x43] - 3) < 2 && (arg0[0x60] & 2)) {
            *(s32 *)(data + 0x28C) = math_random_int_range(0x64, 0x247);
            anim_play_on_self_and_owner(arg0, 6, 5, 0, 0xA);
        }
        break;
    case 12:
        if (arg0[0x60] & 2) {
            anim_play_on_self_and_owner(arg0, 5, 4, 0, 0xA);
            moby_set_state(arg0, 5, -1);
        }
        break;
    case 14:
        moby_turn_toward_position(arg0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], data + 0x284, 0.001f, 0.01f, 0.1f);
        if (*(u8 **)(data + 0x27C) != 0) {
            moby_set_state(arg0, 0x18, -1);
            anim_play_on_self_and_owner(arg0, 0xF, 4, 0, 8);
        } else if (*(s32 *)(data + 0x2A8) != 0) {
            moby_set_state(arg0, 0x13, -1);
            anim_play_on_self_and_owner(arg0, 7, 5, 0, 8);
        } else {
            moby_set_state(arg0, 0xF, -1);
            anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
        }
        break;
    case 15:
        func_PAL_L11_00437B08(arg0, &((Hero *)g_hero_state)->f[0x80 / 4]);
        *(s32 *)(data + 0x280) = *(s32 *)(data + 0x280) + 1;
        if (*(u8 **)(data + 0x27C) != 0) {
            if (vec_distance_xy(arg0 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 20.0f &&
                FastDiffRots(*(f32 *)(arg0 + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                 ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.17453295f) {
                anim_play_on_self_and_owner(arg0, 9, 6, 0, 8);
                moby_set_state(arg0, 0x12, -1);
            }
        } else {
            if (vec_distance_xy(arg0 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 2.7f &&
                FastDiffRots(*(f32 *)(arg0 + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                 ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.3490659f) {
                anim_play_on_self_and_owner(arg0, 0xC, 0, 0, 4);
                moby_set_state(arg0, 0x15, -1);
            }
            if (vec_distance_xy(arg0 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) > 2.7f && (arg0[0x42] == 5 || arg0[0x42] == 0xF)) {
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 3);
                moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            }
        }
        break;
    case 19: {
        *(f32 *)(data + 0x164) = 0.010000001f;
        moby_set_controller_speed_limits(arg0, 0.0096f, 0.24000001f, 0.0016755164f, 0.12566373f);
        func_PAL_L01_00323068(arg0, &((Hero *)g_hero_state)->f[0x80 / 4]);
        moby_turn_toward_position(arg0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], data + 0x284, 0.001f, 0.01f, 0.1f);
        *(s32 *)(data + 0x280) = *(s32 *)(data + 0x280) + 1;
        if (vec_distance_xy(arg0 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 2.1f) {
            anim_play_on_self_and_owner(arg0, 8, 0, 1, 2);
            *(f32 *)(arg0 + 0x48) = 1.0f;
            moby_set_state(arg0, 0x14, -1);
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));

        moby_transform_joint_to_world((u32)arg0, 1, pos);
        dir[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8));
        dir[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8));
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        FastVecScale(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        make_hit_descriptor(req, arg0, 0x10001, *(f32 *)(data + 0x2B8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
        req[0x18] = 0;
        coll_process_hit(pos, 1.3f, 0, arg0, req);
        }
        break;
    }
    case 20: {
        u8 *p;

        p = arg0 + 0x10;
        {
        f32 off[4] __attribute__((aligned(16)));
        moby_set_controller_speed_limits(arg0, 0.006f, 0.040000003f, 0.0016755164f, 0.12566373f);
        off[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8)) * 4.0f;
        off[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8)) * 4.0f;
        off[2] = 0.0f;
        FastVecAdd(off, p, off);
        func_PAL_L01_00323068(arg0, &((Hero *)g_hero_state)->f[0x80 / 4]);
        *(s32 *)(data + 0x280) = *(s32 *)(data + 0x280) + 1;
        if (arg0[0x60] & 2) {
            anim_play_on_self_and_owner(arg0, 2, 2, 0, 8);
            moby_set_state(arg0, 0x10, -1);
            if (vec_distance_xy(p, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.0f) {
                moby_set_controller_speed_limits(arg0, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                if (arg0[0x43] != 0x10)
                    func_PAL_002A7E68(arg0, 0x10, 0, 8);
                moby_set_state(arg0, 0x1B, -1);
            }
        }
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));

        moby_transform_joint_to_world((u32)arg0, 1, pos);
        dir[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8));
        dir[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8));
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        FastVecScale(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        make_hit_descriptor(req, arg0, 0x10001, *(f32 *)(data + 0x2B8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
        req[0x18] = 0;
        coll_process_hit(pos, 1.3f, 0, arg0, req);
        }
        break;
    }
    case 27: {
        moby_set_controller_speed_limits(arg0, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
        {
        f32 v[4] __attribute__((aligned(16)));

        vec_scale_to_length(v, arg0 + 0xC0, -5.5f);
        FastVecAdd(v, v, arg0 + 0x10);
        func_PAL_L02_00333638(arg0, v, mat_fast_helper_a(v[0] - *(f32 *)(arg0 + 0x10), v[1] - *(f32 *)(arg0 + 0x14)), 0x10, -1.0f, -1.0f);
        }
        if (*(u16 *)(arg0 + 0x96) >= 0x65) {
            *(f32 *)(data + 0x164) = 0.0012f;
            if (*(u8 **)(data + 0x27C) != 0) {
                moby_set_controller_speed_limits(arg0, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                anim_play_on_self_and_owner(arg0, 9, 6, 0, 8);
                moby_set_state(arg0, 0x12, -1);
            } else {
                moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
                moby_set_state(arg0, 0xF, -1);
            }
        }
        break;
    }
    case 16:
        if (arg0[0x60] & 2) {
            *(f32 *)(data + 0x164) = 0.0012f;
            if (*(u8 **)(data + 0x27C) != 0) {
                moby_set_controller_speed_limits(arg0, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                anim_play_on_self_and_owner(arg0, 9, 6, 0, 8);
                moby_set_state(arg0, 0x12, -1);
            } else {
                moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
                moby_set_state(arg0, 0xF, -1);
            }
        }
        break;
    case 17:
        moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if (func_PAL_002B6CD8(arg0, D_L11_001FF580[*(s32 *)(data + 0x294)]) != 0) {
            moby_set_state(arg0, 0x18, -1);
            anim_play_on_self_and_owner(arg0, 0xF, 4, 0, 8);
            moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            *(f32 *)(data + 0x164) = 0.0012f;
            *(s32 *)(data + 0x294) = -1;
            *(s32 *)(data + 0x2AC) = -1;
            if (*(u8 **)(data + 0x27C) == 0)
                moby_set_state(arg0, 0xE, 2);
        }
        break;
    case 18: {
        f32 v0[4] __attribute__((aligned(16)));
        f32 v10[4] __attribute__((aligned(16)));
        f32 f, g;
        s32 n;

        if (*(u8 **)(data + 0x27C) != 0 && arg0[0x42] == 9) {
            moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x27C) + 0x68) + 0x278), 0, v0);
            v10[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[2] = 0.0f;
            FastVecAdd(v0, v0, v10);
            v0[2] -= 0.05f;
            g = moby_get_anim_value(arg0);
            f = math_random_float_range(0.2f, 0.9f) * 0.2f * g;
            n = math_random_int_below(2);
            if (n == 0)
                n = n - 1;
            part_spawn_ground_effect(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L11_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L11_001A8F20, 0.0f, 0);
            *(f32 *)(data + 0x288) = g;
        }
        if (arg0[0x60] & 2) {
            anim_play_on_self_and_owner(arg0, 0xA, 7, 0, 8);
            moby_set_state(arg0, 0x16, -1);
        }
        break;
    }
    case 21: {
        f32 f;

        f = moby_get_anim_value(arg0);
        if (arg0[0x42] == 0xC && f >= 10.0f && f <= 15.0f)
            coll_test_hit_at_bone(arg0, 1.0f, *(f32 *)(data + 0x2B4), 1, 1, 1.0f, 0, 1, 0);
        if (arg0[0x60] & 2) {
            if (vec_distance_xy(arg0 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 2.7f &&
                FastDiffRots(*(f32 *)(arg0 + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                 ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.3490659f) {
                anim_play_on_self_and_owner(arg0, 0xC, 0, 0, 8);
                moby_set_state(arg0, 0x15, -1);
            } else {
                moby_set_state(arg0, 0xF, -1);
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
                moby_set_controller_speed_limits(arg0, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            }
        }
        break;
    }
    case 22: {
        f32 t;
        f32 hp;

        if (*(u8 **)(data + 0x27C) == 0) {
            moby_set_state(arg0, 0xF, -1);
            anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
        }
        if (arg0[0x60] & 2) {
            if (vec_distance_xy(arg0 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 25.0f && *(u8 **)(data + 0x27C) != 0 &&
                *(s32 *)(data + 0x2A0) < 3) {
                if (FastDiffRots(*(f32 *)(arg0 + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                     ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) > 0.087266475f) {
                    moby_set_state(arg0, 0x18, -1);
                    anim_play_on_self_and_owner(arg0, 0xF, 4, 0, 8);
                } else {
                    anim_play_on_self_and_owner(arg0, 9, 6, 0, 8);
                    moby_set_state(arg0, 0x12, -1);
                }
            } else if (vec_distance_xy(arg0 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) > 10.0f && *(u8 **)(data + 0x27C) != 0 &&
                       *(s32 *)(data + 0x2A0) >= 3 && *(s32 *)(data + 0x2BC) == -1) {
                anim_play_on_self_and_owner(arg0, 3, 2, 0, 8);
                moby_set_state(arg0, 0x17, -1);
                *(s32 *)(data + 0x2A0) = 0;
            } else {
                moby_set_state(arg0, 0x18, -1);
                anim_play_on_self_and_owner(arg0, 0xF, 4, 0, 8);
            }
            if (*(u8 **)(data + 0x27C) != 0) {
                *(s32 *)(data + 0x2A0) = *(s32 *)(data + 0x2A0) + 1;
            } else {
                moby_set_state(arg0, 0xF, -1);
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
                break;
            }
        } else if (moby_get_anim_value(arg0) >= 2.8333335f && moby_get_anim_value(arg0) < 3.25f && *(u8 **)(data + 0x27C) != 0) {
            f32 v0[4] __attribute__((aligned(16)));
            f32 v10[4] __attribute__((aligned(16)));

            if (FastDiffRots(*(f32 *)(arg0 + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                 ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.78539824f) {
                s32 k;
                u8 *l;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x27C) + 0x68) + 0x278), 0, v0);
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(data + 0x230) = *(TI128 *)v0;
                FastVecSub(data + 0x250, &((Hero *)g_hero_state)->f[0xD0 / 4], v0);
                *(f32 *)(data + 0x298) = 0.0f;
                moby_set_flag_bit(arg0, 0);
                k = part_l00_alloc_effect_slot_2(arg0 + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(data + 0x2B0) = k;
                if (k >= 0) {
                    l = D_L11_001C8A40 + (k << 5);
                    qcopy(l + 0x10, data + 0x230);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            } else {
                s32 k;
                u8 *l;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x27C) + 0x68) + 0x278), 0, v0);
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(data + 0x230) = *(TI128 *)v0;
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[2] = 0.0f;
                FastVecAdd(v10, v10, arg0 + 0x10);
                FastVecSub(data + 0x250, v10, v0);
                *(f32 *)(data + 0x298) = 0.0f;
                moby_set_flag_bit(arg0, 0);
                k = part_l00_alloc_effect_slot_2(arg0 + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(data + 0x2B0) = k;
                if (k >= 0) {
                    l = D_L11_001C8A40 + (k << 5);
                    qcopy(l + 0x10, data + 0x230);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            }
        }
        t = moby_get_anim_value(arg0);
        if (t < 3.0f || arg0[0x42] != 0xA) {
            if (*(u8 **)(data + 0x27C) != 0) {
                f32 v0[4] __attribute__((aligned(16)));
                f32 v10[4] __attribute__((aligned(16)));
                f32 f;
                s32 n;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x27C) + 0x68) + 0x278), 0, v0);
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                f = math_random_float_range(0.2f, 0.9f) * 0.2f * *(f32 *)(data + 0x288);
                n = math_random_int_below(2);
                if (n == 0)
                    n = n - 1;
                part_spawn_ground_effect(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L11_001A8F20, 0.0f, 0);
                part_spawn_ground_effect(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L11_001A8F20, 0.0f, 0);
                *(f32 *)(data + 0x288) = *(f32 *)(data + 0x288) + 1.0f;
            }
        }
        hp = (f32)data[0x35];
        if (t >= 3.0f) {
            if (t < 9.0f) {
                if (arg0[0x42] == 0xA) {
            u8 req[0x30] __attribute__((aligned(16)));
            f32 v30[4] __attribute__((aligned(16)));
                                    u8 *l;
            f32 f, f3, f04, f4;
            s32 n;

            *(f32 *)(data + 0x298) = *(f32 *)(data + 0x298) + 1.2f;
            vec_scale_to_length(data + 0x240, data + 0x250, *(f32 *)(data + 0x298));
            make_hit_descriptor(req, arg0, 1, hp, data + 0x240);
            *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
            FastVecAdd(data + 0x240, data + 0x230, data + 0x240);
            if (CollLine(data + 0x230, data + 0x240, 0, arg0, req) != 0) {
                *(TI128 *)(data + 0x240) = D_L11_001C0D20;
                if (flag_is_third_pending_set(arg0) == 0) {
                    func_PAL_L04_003E96E0(&D_L11_001C0D20, 6);
                    moby_set_flag_bit(arg0, 1);
                }
            }
            f = math_random_float_range(1.0f, 6.0f);
            n = math_random_int_range(0x19, 0x23);
            if (n == 0)
                n = n - 1;
            qcopy(v30, data + 0x240);
            v30[2] -= 0.1f;
            f3 = f * 0.3f;
            part_spawn_ground_effect(v30, 0x15, f3, f, 0xFF000080, 0, n, D_L11_001A8F20, 0.0f, 0);
            n = -n;
            f04 = f * 0.04f;
            f4 = f * 0.4f;
            part_spawn_ground_effect(v30, 4, f04, f4, 0x7F6F6FFF, 1, n, D_L11_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(v30, 0x11, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L11_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(data + 0x230, 8, f3, f, 0x80CA00CB, 0, n, D_L11_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(data + 0x230, 8, f04, f4, 0x7F6F6FFF, 1, -n, D_L11_001A8F20, 0.0f, 0);
            gfx_add_draw_callback_first(saur_beast_draw_beam, arg0);
            if (*(s32 *)(data + 0x2B0) >= 0) {
                l = D_L11_001C8A40 + (*(s32 *)(data + 0x2B0) << 5);
                qcopy(l + 0x10, data + 0x240);
                *(f32 *)(l + 0x1C) = 5.0f;
                *(f32 *)(l + 0) = 1.0f;
                *(f32 *)(l + 4) = 0.0f;
                *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                *(f32 *)(l + 8) = 0.0f;
                *(f32 *)(l + 0xC) = 0.0f;
            }
                }
            }
        }
        if (t >= 9.0f && t < 15.0f && arg0[0x42] == 0xA) {
                        
            if (vec_distance_xy(data + 0x230, data + 0x240) > 2.0000002f) {
                u8 req[0x30] __attribute__((aligned(16)));
                f32 v30[4] __attribute__((aligned(16)));
                f32 v40[4] __attribute__((aligned(16)));
                u8 *l;
                f32 f, f4;
                s32 n;

                *(f32 *)(data + 0x298) = *(f32 *)(data + 0x298) + 1.2f;
                vec_scale_to_length(data + 0x240, data + 0x250, *(f32 *)(data + 0x298));
                make_hit_descriptor(req, arg0, 1, hp, data + 0x240);
                *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
                FastVecAdd(data + 0x240, data + 0x230, data + 0x240);
                if (CollLine(data + 0x230, data + 0x240, 0, arg0, req) != 0) {
                    *(TI128 *)(data + 0x240) = D_L11_001C0D20;
                    if (flag_is_third_pending_set(arg0) == 0) {
                        func_PAL_L04_003E96E0(&D_L11_001C0D20, 6);
                        moby_set_flag_bit(arg0, 1);
                    }
                }
                vec_scale_to_length(v30, data + 0x250, 2.0000002f);
                FastVecAdd(data + 0x230, data + 0x230, v30);
                f = math_random_float_range(1.0f, 6.0f);
                n = math_random_int_range(0x19, 0x23);
                if (n == 0)
                    n = n - 1;
                qcopy(v40, data + 0x240);
                v40[2] -= 0.1f;
                part_spawn_ground_effect(v40, 0x15, f * 0.3f, f, 0xFF000080, 0, n, D_L11_001A8F20, 0.0f, 0);
                n = -n;
                f4 = f * 0.4f;
                part_spawn_ground_effect(v40, 4, f * 0.04f, f4, 0x7F6F6FFF, 1, n, D_L11_001A8F20, 0.0f, 0);
                part_spawn_ground_effect(v40, 0x11, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L11_001A8F20, 0.0f, 0);
                gfx_add_draw_callback_first(saur_beast_draw_beam, arg0);
                if (*(s32 *)(data + 0x2B0) >= 0) {
                    l = D_L11_001C8A40 + (*(s32 *)(data + 0x2B0) << 5);
                    qcopy(l + 0x10, data + 0x240);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            } else if (*(s32 *)(data + 0x2B0) >= 0) {
                gfx_free_point_light(*(s32 *)(data + 0x2B0));
                *(s32 *)(data + 0x2B0) = -1;
            }
        } else if (t > 15.0f && arg0[0x42] == 0xA) {
            if (*(s32 *)(data + 0x2B0) >= 0) {
                gfx_free_point_light(*(s32 *)(data + 0x2B0));
                *(s32 *)(data + 0x2B0) = -1;
            }
        }
        break;
    }
    case 23: {
        u8 *p = arg0 + 0x10;

        if (arg0[0x60] & 2) {
            if (vec_distance_xy(p, &((Hero *)g_hero_state)->f[0x80 / 4]) < 25.0f && *(u8 **)(data + 0x27C) != 0) {
                moby_set_state(arg0, 0x18, -1);
                anim_play_on_self_and_owner(arg0, 5, 4, 0, 8);
            } else {
                moby_set_state(arg0, 0xF, -1);
                anim_play_on_self_and_owner(arg0, 6, 5, 0, 8);
            }
        } else if (vec_distance_xy(p, &((Hero *)g_hero_state)->f[0x80 / 4]) < 6.0f) {
            anim_play_on_self_and_owner(arg0, 9, 6, 0, 8);
            moby_set_state(arg0, 0x12, -1);
        }
        break;
    }
    case 24:
        if (FastDiffRots(*(f32 *)(arg0 + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                             ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) <= 0.087266475f) {
            anim_play_on_self_and_owner(arg0, 9, 6, 0, 8);
            moby_set_state(arg0, 0x12, -1);
        } else {
            func_PAL_002B5C98(arg0, arg0 + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                           ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        }
        break;
    case 25:
        if (arg0[0x60] & 2) {
            if (*(s32 *)(data + 0x2C0) == 0) {
                anim_play_on_self_and_owner(arg0, 5, 4, 0, 0);
                moby_set_state(arg0, 5, -1);
            } else {
                anim_play_on_self_and_owner(arg0, 5, 4, 0, 0);
                moby_set_state(arg0, 6, -1);
            }
        } else if (arg0[0x43] == 0xE) {
            moby_set_controller_speed_limits(arg0, 0.16000001f, 0.080000006f, 0.013962637f, 0.8377582f);
            func_PAL_002B6CD8(arg0, D_L11_001FF580[*(s32 *)(data + 0x29C)]);
        }
        break;
    }
    saur_beast_step_timer_clear_flags(arg0);
    if (*(f32 *)(arg0 + 0x18) < 74.0f) {
        func_PAL_002A7650(arg0, 0, 3);
        D_L11_001AED04[0] = D_L11_001AED04[0] - 1;
        moby_mark_spawned(arg0);
    }
}
