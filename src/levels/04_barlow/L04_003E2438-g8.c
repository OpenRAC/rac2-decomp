#include "common.h"

/* func_L04_003E2438: the level's state-machine update (switch on 0x95), twin of func_L11_0042F018.
   Its own -G8 unit with -frac2-hazard-labels (retail keeps the branch label on the mtc1 hazard
   nop before the 9.0f compare). What it took:
   - the hero block through the Hero union view; switch bodies in retail address order;
     addressed block locals scoped so their stack slots are reused as retail does;
   - func_002C2210 declared with its float parameters interleaved
     (pos, size, f, f, color, mode, flag, vector, f, counter) and func_00277F48 as
     (pos, f, flag, obj, req): EABI passes floats in their own registers, so only the
     parameter order of the argument moves changes, and retail's order of those moves
     follows this prototype;
   - arg0 + 0x10 written out at each use in the 0x60 & 2 / 0x2AC|0x27C block instead of a
     local, so gcse gives the expression one reaching register with several sets; with a
     single set sched1's birthing-insn priority boost puts the reaching copy before the
     argument move and local-alloc ties the value to $a0 (retail: $v0, copied to $a0 and $s0). */

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

extern char g_hero_state[];
extern s32 D_L04_001C9C00[];
extern s32 D_L04_001A8F00;
extern s32 *g_route_path_table[];
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern char D_L04_001A8F20[] __attribute__((sda));
extern u8 D_L04_001C7800[];
extern TI128 D_L04_001BFAE0;

extern s32 barlow_enemy_update_core(u8 *);
extern void object_update_age_timer(u8 *);
extern void object_draw_linked_beam(u8 *);
extern void object_move_along_anim_sparks(u8 *, void *);
extern void SelectRandomOtherLiveSlot(u8 *);
extern s32 flag_set_second_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, f32, f32, f32, f32);
extern void moby_set_state(u8 *, s32, s32);
extern void anim_start_blended(u8 *a0, u32 a1, u32 a2, u32 a3);
extern s32 math_random_int_range(s32, s32);
extern s32 math_random_int_below(s32);
extern s32 point_in_path_xy(void *, void *, s32);
extern s32 moby_dispatch_action_by_kind(u8 *, void *);
extern void SetDeathBits(u8 *, s32, s32);
extern void part_queue_moby_for_glow(u8 *, s32, void *);
extern void moby_mark_spawned(void *);
extern f32 math_random_float_range(f32, f32);
extern s32 math_fast_float_d(void *);
extern s32 FastDecTimer(void *);
extern f32 ApproachValue(f32 *, f32, f32);
extern void moby_wander_around_home_point(u8 *, void *, f32, f32);
extern s32 path_follow_nodes(u8 *, void *);
extern s32 path_set_follower_nodes(u8 *, void *, s32, s32);
extern f32 moby_turn_toward_position(u8 *, void *, void *, f32, f32, f32);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern s32 moby_l01_turn_toward_target(u8 *, void *);
extern void moby_transform_joint_to_world(u32 a0, s32 a1, f32 *a2);
extern f32 math_fast_sin_or_cos_a(f32 a0);
extern f32 math_fast_sin_or_cos_b(f32 a0);
extern void FastVecScale(void *, void *, f32);
extern void make_hit_descriptor(void *, void *, s32, f32, void *);
extern void coll_sweep_from_object(void *, void *, s32, f32, f32, f32, s32, s32, s32);
extern s32 coll_process_hit(void *, f32, s32, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 moby_move_to_target_temp_limits(u8 *, void *, f32, s32, f32, f32);
extern f32 moby_get_anim_value(u8 *);
extern void part_spawn_ground_effect(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern s32 coll_test_hit_at_bone(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern s32 math_is_value_within_step(u8 *, f32);
extern void moby_set_flag_bit(u8 *, s32);
extern s32 part_l00_alloc_effect_slot_2(void *, f32, f32, f32, f32, f32);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 flag_is_third_pending_set(u8 *);
extern void part_l04_spawn_paired_sparks(void *, s32);
extern void gfx_add_draw_callback_third(void *, void *);
extern void gfx_free_point_light(s32);
extern s32 moby_step_controller(u8 *, void *, f32);
extern void object_set_linked_states(u8 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/* Updates the main creature on this level. It picks its next action (idle, walk, chase, attack) based on the player and plays the matching animations and sounds. */
void barlow_creature_update(u8 *moby) {
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (D_L04_001C9C00[0] == 1) {
        if (D_L04_001A8F00 == 2) {
            *(s32 *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        } else {
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
        }
    }
    if (barlow_enemy_update_core(moby) != 0) {
        moby_mark_spawned(moby);
        return;
    }

    switch (moby[0x95]) {
    case 0: {
        s32 home_slot;

        home_slot = *(s32 *)(vars + 0x2F0);
        if (home_slot != -1)
            break;
        if (flag_set_second_pending(moby) != 0) {
            moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            if (*(f32 *)(vars + 0x2C0) < 0.2f)
                object_set_linked_states(moby, 4, 3, 0, 0xC);
            if (*(s32 *)(vars + 0x2CC) != home_slot && *(s32 *)(vars + 0x2C4) == home_slot) {
                object_set_linked_states(moby, 5, 4, 0, 0xC);
                moby_set_state(moby, 2, -1);
            }
        }
        if (*(s32 *)(vars + 0x258) == 1 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6F) {
            if (*(s32 *)(vars + 0x2C4) != -1) {
                object_set_linked_states(moby, 6, 5, 0, 0xA);
                moby_set_controller_speed_limits(moby, 0.016666668f, 0.5f, 0.001163553f, 0.10471977f);
                *(f32 *)(vars + 0x164) = 0.0055555557f;
                moby_set_state(moby, 0xD, 2);
            } else if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_state(moby, 0xA, 2);
            } else {
                object_set_linked_states(moby, 0, 2, 0, 0xA);
                moby_set_state(moby, 0xA, 2);
            }
        } else if (*(s16 *)(vars + 0x2A6) != 0) {
            moby_set_state(moby, 8, 1);
            *(s16 *)(vars + 0x2A6) = 0;
            if (*(s16 *)(vars + 0x2A0) < 0x12C)
                *(s16 *)(vars + 0x2A0) = math_random_int_range(0x1E0, 0x258);
            if (*(s32 *)(vars + 0x2CC) != -1) {
                moby_set_state(moby, 8, 1);
                object_set_linked_states(moby, 4, 3, 0, 0xC);
            }
        } else if (*(s32 *)(vars + 0x2DC) != -1 &&
                   point_in_path_xy(vars + 0x230, (u8 *)g_route_path_table[*(s32 *)(vars + 0x2DC)] + 0x10,
                                 *g_route_path_table[*(s32 *)(vars + 0x2DC)]) != 0) {
            object_set_linked_states(moby, 6, 5, 0, 0xA);
            moby_set_controller_speed_limits(moby, 0.016666668f, 0.5f, 0.001163553f, 0.10471977f);
            *(f32 *)(vars + 0x164) = 0.0055555557f;
            moby_set_state(moby, 0xD, 2);
        }
        break;
    }
    case 1:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(vars + 0x258) == 1 || *(s32 *)(vars + 0x25C) == 1) {
            if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_state(moby, 0xA, 2);
            } else {
                object_set_linked_states(moby, 0, 2, 0, 0xA);
                moby_set_state(moby, 0xA, 2);
            }
        } else if (*(s16 *)(vars + 0x2A0) == 0 && *(s32 *)(vars + 0x30C) == 0) {
            moby_set_state(moby, 1, 0);
            object_set_linked_states(moby, 5, 4, 0, 0xC);
        }
        break;
    case 2:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if ((*(s32 *)(vars + 0x2DC) == -1 ||
             point_in_path_xy(vars + 0x230, (u8 *)g_route_path_table[*(s32 *)(vars + 0x2DC)] + 0x10,
                           *g_route_path_table[*(s32 *)(vars + 0x2DC)]) == 0) &&
            *(s32 *)(vars + 0x258) != 1 && *(s32 *)(vars + 0x25C) != 1) {
            if (moby[0x20] == 0xD || moby[0x20] == 0x10 || moby[0x20] == 0xC) {
            } else if (moby[0x20] == 0xF) {
                object_set_linked_states(moby, 8, 0, 1, 3);
                moby_set_state(moby, 0x10, -1);
            } else if (*(s32 *)(vars + 0x2CC) != -1 && *(s32 *)(vars + 0x2C4) == -1) {
                object_set_linked_states(moby, 5, 4, 0, 0xC);
                moby_set_state(moby, 2, 1);
            } else {
                *(s32 *)(vars + 0x2D0) = 0;
                object_set_linked_states(moby, 3, 1, 0, 0xC);
                moby_set_state(moby, 8, 1);
                if (*(s32 *)(vars + 0x2D4) != -1) {
                    qcopy(vars + 0x110, D_L04_001B25CC[0] + (*(s32 *)(vars + 0x2D4) << 7) + 0x30);
                    if (*(f32 *)(vars + 0x12C) == 0.0f)
                        *(f32 *)(vars + 0x12C) = 4.0f;
                }
                *(s16 *)(vars + 0x2A0) = math_random_int_range(0x4B0, 0x514);
            }
        }
        break;
    case 3: {
        s32 move_flags;
        s32 home_slot;

        move_flags = moby_dispatch_action_by_kind(moby, vars + 0x60);
        if (move_flags & 1) {
            SetDeathBits(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, 0);
            return;
        }
        if (move_flags & 2) {
            home_slot = *(s32 *)(vars + 0x2F0);
            if (home_slot != -1) {
                object_set_linked_states(moby, 6, 5, 0, 0xA);
                moby_set_state(moby, 7, 0);
                *(s8 *)(vars + 0x307) = 0x78;
            } else if (*(s32 *)(vars + 0x258) == 1 || *(s32 *)(vars + 0x25C) == 1) {
                object_set_linked_states(moby, 6, 5, 0, 0xA);
                moby_set_state(moby, 0xB, 2);
            } else {
                moby_set_state(moby, 8, 1);
                object_set_linked_states(moby, 1, 1, 0, 0xA);
                *(s16 *)(vars + 0x2A0) = math_random_int_range(0x244, 0x258);
                if (*(s32 *)(vars + 0x2CC) != -1) {
                    moby_set_state(moby, 8, 1);
                    object_set_linked_states(moby, 4, 3, 0, 0xC);
                }
            }
        }
        break;
    }
    }

    switch (moby[0x20]) {
    case 1:
        if (*(f32 *)(vars + 0x2C0) > 0.2f) {
            math_fast_float_d(vars + 0x2BC);
            if (*(s32 *)(vars + 0x2BC) >= 0x15)
                *(f32 *)(vars + 0x124) = 0.06666667f;
            else
                ApproachValue((f32 *)(vars + 0x124), 0.0f, 0.0011111111f);
            if (moby[0x43] == 5) {
                if (*(s32 *)(vars + 0x2BC) == 0) {
                    object_set_linked_states(moby, 1, 1, 0, 0xC);
                    if (math_random_int_below(2) == 1)
                        object_set_linked_states(moby, 0, 0, 0, 0xC);
                }
                moby_wander_around_home_point(moby, vars + 0x110, 0.35f, 0.25f);
            } else if (moby[0x43] < 2 && (moby[0x60] & 2)) {
                *(s32 *)(vars + 0x2BC) = math_random_int_range(0x78, 0x2BC);
                object_set_linked_states(moby, 5, 4, 0, 0xC);
            }
        } else if (*(u8 **)(vars + 0x2AC) != 0 && (*(u8 **)(vars + 0x2AC))[0x43] != 3) {
            object_set_linked_states(moby, 4, 3, 0, 0xC);
        }
        break;
    case 2:
        if (path_follow_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)]) != 0) {
            moby_set_state(moby, 4, -1);
            object_set_linked_states(moby, 4, 3, 0, 0xA);
            path_set_follower_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)], 0, 1);
            *(s32 *)(vars + 0x308) = 1;
        }
        break;
    case 3:
        if (path_follow_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)]) != 0) {
            moby_set_state(moby, 4, -1);
            object_set_linked_states(moby, 4, 3, 0, 0xA);
            path_set_follower_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)], 1, 0);
            *(s32 *)(vars + 0x308) = 0;
        }
        break;
    case 4:
        if (moby[0x60] & 2) {
            object_set_linked_states(moby, 0xF, 0x17, 0, 7);
            moby_set_state(moby, 0x15, -1);
        }
        break;
    case 5:
        if (FastDecTimer(vars + 0x300) != 0) {
            object_set_linked_states(moby, 5, 4, 0, 0xA);
            SelectRandomOtherLiveSlot(moby);
            moby_set_state(moby, 6, 0);
        }
        break;
    case 6: {
        {
        f32 home_point[4] __attribute__((aligned(16)));

        *(TI128 *)home_point = *(TI128 *)(vars + 0x280);
        moby_set_controller_speed_limits(moby, 0.00044444445f, 0.02666667f, 0.001163553f, 0.10471977f);
        moby_l01_turn_toward_target(moby, home_point);
        if (vec_distance_xy(moby + 0x10, home_point) < 1.0f) {
            object_set_linked_states(moby, 1, 1, 0, 0xA);
            *(s16 *)(vars + 0x300) = math_random_int_range(0x4B0, 0xBB8);
            moby_set_state(moby, 5, -1);
        }
        }
        break;
    }
    case 7: {
        {
        f32 home_point[4] __attribute__((aligned(16)));
        f32 m;

        *(TI128 *)home_point = *(TI128 *)(vars + 0x280);
        moby_set_controller_speed_limits(moby, 0.0006666667f, 0.040000003f, 0.001163553f, 0.10471977f);
        object_move_along_anim_sparks(moby, home_point);
        m = *(f32 *)(vars + 0x16C) * 30.0f;
        if (m < *(f32 *)(vars + 0x1E8))
            *(f32 *)(vars + 0x1E8) = m;
        if (vec_distance_xy(moby + 0x10, home_point) < 1.0f || *(s32 *)(vars + 0x1C0) >= 0x3D) {
            object_set_linked_states(moby, 1, 1, 0, 0xA);
            *(s16 *)(vars + 0x300) = math_random_int_range(0x4B0, 0xBB8);
            moby_set_state(moby, 5, -1);
        }
        }
        break;
    }
    case 8:
        math_fast_float_d(vars + 0x2BC);
        if (*(s32 *)(vars + 0x2BC) >= 0x15)
            ApproachValue((f32 *)(vars + 0x124), 0.06666667f, 0.0019444445f);
        else
            ApproachValue((f32 *)(vars + 0x124), 0.0f, 0.0019444445f);
        if (moby[0x43] == 6) {
            if (*(s32 *)(vars + 0x2BC) == 0) {
                object_set_linked_states(moby, 3, 2, 0, 0xC);
                if (math_random_int_below(2) == 1)
                    object_set_linked_states(moby, 4, 3, 0, 0xC);
            }
            moby_wander_around_home_point(moby, vars + 0x110, 0.35f, 0.25f);
        } else if ((u8)(moby[0x43] - 3) < 2 && (moby[0x60] & 2)) {
            *(s32 *)(vars + 0x2BC) = math_random_int_range(0x78, 0x2BC);
            object_set_linked_states(moby, 6, 5, 0, 0xC);
        }
        break;
    case 9:
        if (moby[0x60] & 2) {
            object_set_linked_states(moby, 5, 4, 0, 0xC);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 10:
        moby_turn_toward_position(moby, *(void **)(vars + 0x240), vars + 0x2B4, 0.001f, 0.01f, 0.1f);
        if (*(u8 **)(vars + 0x2AC) != 0) {
            moby_set_state(moby, 0x14, -1);
            object_set_linked_states(moby, 0x10, 4, 0, 0xA);
        } else if (*(s32 *)(vars + 0x2D8) != 0) {
            moby_set_state(moby, 0xF, -1);
            object_set_linked_states(moby, 7, 5, 0, 0xA);
        } else {
            moby_set_state(moby, 0xB, -1);
            object_set_linked_states(moby, 6, 5, 0, 0xA);
        }
        break;
    case 11:
        object_move_along_anim_sparks(moby, vars + 0x230);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (*(u8 **)(vars + 0x2AC) != 0) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 20.0f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.17453295f) {
                object_set_linked_states(moby, 9, 6, 0, 0xA);
                moby_set_state(moby, 0xE, -1);
            }
        } else {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 2.7f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.3490659f) {
                object_set_linked_states(moby, 0xC, 0, 0, 5);
                moby_set_state(moby, 0x11, -1);
            }
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) > 2.7f && (moby[0x42] == 5 || moby[0x42] == 0x10)) {
                object_set_linked_states(moby, 6, 5, 0, 4);
                moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            }
        }
        break;
    case 15: {
        *(f32 *)(vars + 0x164) = 0.0069444445f;
        moby_set_controller_speed_limits(moby, 0.006666667f, 0.20000002f, 0.001163553f, 0.10471977f);
        moby_l01_turn_toward_target(moby, vars + 0x230);
        moby_turn_toward_position(moby, *(void **)(vars + 0x240), vars + 0x2B4, 0.001f, 0.01f, 0.1f);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 3.5f) {
            object_set_linked_states(moby, 8, 0, 1, 3);
            *(f32 *)(moby + 0x48) = 1.0f;
            moby_set_state(moby, 0x10, -1);
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));
        f32 z;

        moby_transform_joint_to_world((u32)moby, 1, pos);
        dir[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8));
        dir[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8));
        dir[2] = 0.0f;
        z = dir[2];
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        FastVecScale(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        make_hit_descriptor(req, moby, 1, *(f32 *)(vars + 0x2E8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
        req[0x18] = 0;
        coll_process_hit(pos, 1.1f, 0, moby, req);
        coll_sweep_from_object(moby, pos, 0x10000, 1.1f, *(f32 *)(vars + 0x2E8) * 4.0f, z, 0, 1, 0);
        }
        break;
    }
    case 16: {
        u8 *p;

        p = moby + 0x10;
        {
        f32 off[4] __attribute__((aligned(16)));
        moby_set_controller_speed_limits(moby, 0.004166667f, 0.033333335f, 0.001163553f, 0.10471977f);
        off[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 4.0f;
        off[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 4.0f;
        off[2] = 0.0f;
        FastVecAdd(off, p, off);
        moby_l01_turn_toward_target(moby, vars + 0x230);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (moby[0x60] & 2) {
            object_set_linked_states(moby, 2, 2, 0, 0xA);
            moby_set_state(moby, 0xC, -1);
            if (vec_distance_xy(p, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.0f) {
                moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                if (moby[0x43] != 0x11)
                    anim_start_blended(moby, 0x11, 0, 0xA);
                moby_set_state(moby, 0x17, -1);
            }
        }
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));

        moby_transform_joint_to_world((u32)moby, 1, pos);
        dir[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8));
        dir[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8));
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        FastVecScale(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        make_hit_descriptor(req, moby, 0x04000001, *(f32 *)(vars + 0x2E8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
        req[0x18] = 0;
        coll_process_hit(pos, 1.3f, 0, moby, req);
        }
        break;
    }
    case 23: {
        moby_set_controller_speed_limits(moby, 0.0011111111f, 0.033333335f, 0.001163553f, 0.10471977f);
        {
        f32 home_point[4] __attribute__((aligned(16)));

        vec_scale_to_length(home_point, moby + 0xC0, -5.5f);
        FastVecAdd(home_point, home_point, moby + 0x10);
        moby_move_to_target_temp_limits(moby, home_point, mat_fast_helper_a(home_point[0] - *(f32 *)(moby + 0x10), home_point[1] - *(f32 *)(moby + 0x14)), 0x10, -1.0f, -1.0f);
        }
        if (*(u16 *)(moby + 0x96) >= 0x79) {
            *(f32 *)(vars + 0x164) = 0.00083333335f;
            if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                object_set_linked_states(moby, 9, 6, 0, 0xA);
                moby_set_state(moby, 0xE, -1);
            } else {
                moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                object_set_linked_states(moby, 6, 5, 0, 0xA);
                moby_set_state(moby, 0xB, -1);
            }
        }
        break;
    }
    case 12:
        if (moby[0x60] & 2) {
            *(f32 *)(vars + 0x164) = 0.00083333335f;
            if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                object_set_linked_states(moby, 9, 6, 0, 0xA);
                moby_set_state(moby, 0xE, -1);
            } else {
                moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                object_set_linked_states(moby, 6, 5, 0, 0xA);
                moby_set_state(moby, 0xB, -1);
            }
        }
        break;
    case 13:
        moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if (path_follow_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2C4)]) != 0) {
            moby_set_state(moby, 0x14, -1);
            object_set_linked_states(moby, 0x10, 4, 0, 0xA);
            moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            *(s32 *)(vars + 0x2C4) = -1;
            *(f32 *)(vars + 0x164) = 0.00083333335f;
            *(s32 *)(vars + 0x2DC) = -1;
        }
        break;
    case 14: {
        f32 v0[4] __attribute__((aligned(16)));
        f32 v10[4] __attribute__((aligned(16)));
        f32 f, g;
        s32 n;

        if (*(u8 **)(vars + 0x2AC) != 0 && moby[0x42] == 9) {
            moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
            v10[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
            v10[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
            v10[2] = 0.0f;
            FastVecAdd(v0, v0, v10);
            v0[2] -= 0.05f;
            g = moby_get_anim_value(moby);
            f = math_random_float_range(0.2f, 0.9f) * 0.2f * g;
            n = math_random_int_below(2);
            if (n == 0)
                n = n - 1;
            part_spawn_ground_effect(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L04_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
            *(f32 *)(vars + 0x2B8) = g;
        }
        if (*(u16 *)(moby + 0x96) >= 0x2E) {
            object_set_linked_states(moby, 0xA, 7, 0, 0xA);
            moby_set_state(moby, 0x12, -1);
        }
        break;
    }
    case 17: {
        f32 f;

        f = moby_get_anim_value(moby);
        if (moby[0x42] == 0xC && f >= 10.0f && f <= 15.0f)
            coll_test_hit_at_bone(moby, 1.0f, *(f32 *)(vars + 0x2E4), 1, 0x04000001, 1.0f, 0, 1, 0);
        if (moby[0x60] & 2) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 2.7f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.3490659f) {
                object_set_linked_states(moby, 0xC, 0, 0, 0xA);
                moby_set_state(moby, 0x11, -1);
            } else {
                moby_set_state(moby, 0xB, -1);
                object_set_linked_states(moby, 6, 5, 0, 0xA);
                moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            }
        }
        break;
    }
    case 18: {
        f32 t;
        f32 hp;

        if (moby[0x60] & 2) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 25.0f && *(u8 **)(vars + 0x2AC) != 0 &&
                *(s32 *)(vars + 0x2D0) < 3) {
                if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                     *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) > 0.087266475f) {
                    moby_set_state(moby, 0x14, -1);
                    object_set_linked_states(moby, 0x10, 4, 0, 0xA);
                } else {
                    object_set_linked_states(moby, 9, 6, 0, 0xA);
                    moby_set_state(moby, 0xE, -1);
                }
            } else if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) > 10.0f && *(u8 **)(vars + 0x2AC) != 0 &&
                       *(s32 *)(vars + 0x2D0) >= 3) {
                object_set_linked_states(moby, 3, 2, 0, 0xA);
                moby_set_state(moby, 0x13, -1);
                *(s32 *)(vars + 0x2D0) = 0;
            } else {
                moby_set_state(moby, 0x14, -1);
                object_set_linked_states(moby, 0x10, 4, 0, 0xA);
            }
            if (*(u8 **)(vars + 0x2AC) != 0) {
                *(s32 *)(vars + 0x2D0) = *(s32 *)(vars + 0x2D0) + 1;
            } else {
                moby_set_state(moby, 0xB, -1);
                object_set_linked_states(moby, 6, 5, 0, 0xA);
                break;
            }
        } else if (math_is_value_within_step(moby, 3.0f) != 0 && *(u8 **)(vars + 0x2AC) != 0) {
            f32 v0[4] __attribute__((aligned(16)));
            f32 v10[4] __attribute__((aligned(16)));

            if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.78539824f) {
                s32 k;
                u8 *l;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(vars + 0x260) = *(TI128 *)v0;
                FastVecSub(vars + 0x280, vars + 0x230, v0);
                *(f32 *)(vars + 0x2C8) = 0.0f;
                moby_set_flag_bit(moby, 0);
                k = part_l00_alloc_effect_slot_2(moby + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(vars + 0x2E0) = k;
                if (k >= 0) {
                    l = D_L04_001C7800 + (k << 5);
                    qcopy(l + 0x10, vars + 0x260);
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

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(vars + 0x260) = *(TI128 *)v0;
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 25.0f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 25.0f;
                v10[2] = 0.0f;
                FastVecAdd(v10, v10, moby + 0x10);
                FastVecSub(vars + 0x280, v10, v0);
                *(f32 *)(vars + 0x2C8) = 0.0f;
                moby_set_flag_bit(moby, 0);
                k = part_l00_alloc_effect_slot_2(moby + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(vars + 0x2E0) = k;
                if (k >= 0) {
                    l = D_L04_001C7800 + (k << 5);
                    qcopy(l + 0x10, vars + 0x260);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            }
        }
        t = moby_get_anim_value(moby);
        if (t < 3.0f || moby[0x42] != 0xA) {
            if (*(u8 **)(vars + 0x2AC) != 0) {
                f32 v0[4] __attribute__((aligned(16)));
                f32 v10[4] __attribute__((aligned(16)));
                f32 f;
                s32 n;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                f = math_random_float_range(0.2f, 0.9f) * 0.2f * *(f32 *)(vars + 0x2B8);
                n = math_random_int_below(2);
                if (n == 0)
                    n = n - 1;
                part_spawn_ground_effect(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L04_001A8F20, 0.0f, 0);
                part_spawn_ground_effect(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
                *(f32 *)(vars + 0x2B8) = *(f32 *)(vars + 0x2B8) + 1.0f;
            }
        }
        hp = (f32)vars[0x35];
        if (t >= 3.0f) {
            if (t < 9.0f) {
                if (moby[0x42] == 0xA) {
            u8 req[0x30] __attribute__((aligned(16)));
            f32 v30[4] __attribute__((aligned(16)));
                                    u8 *l;
            f32 f, f3, f04, f4;
            s32 n;

            *(f32 *)(vars + 0x2C8) = *(f32 *)(vars + 0x2C8) + 1.0f;
            vec_scale_to_length(vars + 0x270, vars + 0x280, *(f32 *)(vars + 0x2C8));
            make_hit_descriptor(req, moby, 0x04000001, hp, vars + 0x270);
            *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
            FastVecAdd(vars + 0x270, vars + 0x260, vars + 0x270);
            if (CollLine(vars + 0x260, vars + 0x270, 0, moby, req) != 0) {
                *(TI128 *)(vars + 0x270) = D_L04_001BFAE0;
                if (flag_is_third_pending_set(moby) == 0) {
                    part_l04_spawn_paired_sparks(&D_L04_001BFAE0, 0x1E);
                    moby_set_flag_bit(moby, 1);
                }
            }
            f = math_random_float_range(1.0f, 6.0f);
            n = math_random_int_range(0x19, 0x23);
            if (n == 0)
                n = n - 1;
            qcopy(v30, vars + 0x270);
            v30[2] -= 0.1f;
            f3 = f * 0.3f;
            part_spawn_ground_effect(v30, 0x19, f3, f, 0xFF000080, 0, n, D_L04_001A8F20, 0.0f, 0);
            n = -n;
            f04 = f * 0.04f;
            f4 = f * 0.4f;
            part_spawn_ground_effect(v30, 5, f04, f4, 0x7F6F6FFF, 1, n, D_L04_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(v30, 0x14, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L04_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(vars + 0x260, 0xA, f3, f, 0x80CA00CB, 0, n, D_L04_001A8F20, 0.0f, 0);
            part_spawn_ground_effect(vars + 0x260, 0xA, f04, f4, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
            gfx_add_draw_callback_third(object_draw_linked_beam, moby);
            if (*(s32 *)(vars + 0x2E0) >= 0) {
                l = D_L04_001C7800 + (*(s32 *)(vars + 0x2E0) << 5);
                qcopy(l + 0x10, vars + 0x270);
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
        if (t >= 9.0f && t < 15.0f && moby[0x42] == 0xA) {
                        
            if (vec_distance_xy(vars + 0x260, vars + 0x270) > 0.5f) {
                u8 req[0x30] __attribute__((aligned(16)));
                f32 v30[4] __attribute__((aligned(16)));
                f32 v40[4] __attribute__((aligned(16)));
                u8 *l;
                f32 f, f4;
                s32 n;

                *(f32 *)(vars + 0x2C8) = *(f32 *)(vars + 0x2C8) + 1.0f;
                vec_scale_to_length(vars + 0x270, vars + 0x280, *(f32 *)(vars + 0x2C8));
                make_hit_descriptor(req, moby, 0x04000001, hp, vars + 0x270);
                *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
                FastVecAdd(vars + 0x270, vars + 0x260, vars + 0x270);
                if (CollLine(vars + 0x260, vars + 0x270, 0, moby, req) != 0) {
                    *(TI128 *)(vars + 0x270) = D_L04_001BFAE0;
                    if (flag_is_third_pending_set(moby) == 0) {
                        part_l04_spawn_paired_sparks(&D_L04_001BFAE0, 0x1E);
                        moby_set_flag_bit(moby, 1);
                    }
                }
                vec_scale_to_length(v30, vars + 0x280, 1.6666667f);
                FastVecAdd(vars + 0x260, vars + 0x260, v30);
                f = math_random_float_range(1.0f, 6.0f);
                n = math_random_int_range(0x19, 0x23);
                if (n == 0)
                    n = n - 1;
                qcopy(v40, vars + 0x270);
                v40[2] -= 0.1f;
                part_spawn_ground_effect(v40, 0x19, f * 0.3f, f, 0xFF000080, 0, n, D_L04_001A8F20, 0.0f, 0);
                n = -n;
                f4 = f * 0.4f;
                part_spawn_ground_effect(v40, 5, f * 0.04f, f4, 0x7F6F6FFF, 1, n, D_L04_001A8F20, 0.0f, 0);
                part_spawn_ground_effect(v40, 0x14, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L04_001A8F20, 0.0f, 0);
                gfx_add_draw_callback_third(object_draw_linked_beam, moby);
                if (*(s32 *)(vars + 0x2E0) >= 0) {
                    l = D_L04_001C7800 + (*(s32 *)(vars + 0x2E0) << 5);
                    qcopy(l + 0x10, vars + 0x270);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            } else if (*(s32 *)(vars + 0x2E0) >= 0) {
                gfx_free_point_light(*(s32 *)(vars + 0x2E0));
                *(s32 *)(vars + 0x2E0) = -1;
            }
        } else if (t > 15.0f && moby[0x42] == 0xA) {
            if (*(s32 *)(vars + 0x2E0) >= 0) {
                gfx_free_point_light(*(s32 *)(vars + 0x2E0));
                *(s32 *)(vars + 0x2E0) = -1;
            }
        }
        break;
    }
    case 19: {
        u8 *p = moby + 0x10;

        if (moby[0x60] & 2) {
            if (vec_distance_xy(p, *(u8 **)(vars + 0x240) + 0x10) < 25.0f && *(u8 **)(vars + 0x2AC) != 0) {
                moby_set_state(moby, 0x14, -1);
                object_set_linked_states(moby, 5, 4, 0, 0xA);
            } else {
                moby_set_state(moby, 0xB, -1);
                object_set_linked_states(moby, 6, 5, 0, 0xA);
            }
        } else if (vec_distance_xy(p, *(u8 **)(vars + 0x240) + 0x10) < 6.0f) {
            object_set_linked_states(moby, 9, 6, 0, 0xA);
            moby_set_state(moby, 0xE, -1);
        }
        break;
    }
    case 20:
        if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                             *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) <= 0.087266475f) {
            object_set_linked_states(moby, 9, 6, 0, 0xA);
            moby_set_state(moby, 0xE, -1);
        } else {
            moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(*(f32 *)(*(u8 **)(vars + 0x240) + 0x10) - *(f32 *)(moby + 0x10),
                                                           *(f32 *)(*(u8 **)(vars + 0x240) + 0x14) - *(f32 *)(moby + 0x14)));
        }
        break;
    case 21:
        if (moby[0x60] & 2) {
            if (*(s32 *)(vars + 0x308) == 0) {
                object_set_linked_states(moby, 5, 4, 0, 0);
                moby_set_state(moby, 2, -1);
            } else {
                object_set_linked_states(moby, 5, 4, 0, 0);
                moby_set_state(moby, 3, -1);
            }
        } else if (moby[0x43] == 0xF) {
            moby_set_controller_speed_limits(moby, 0.13333334f, 0.06666667f, 0.009696275f, 0.6981318f);
            path_follow_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)]);
        }
        break;
    }
    object_update_age_timer(moby);
    if (*(f32 *)(moby + 0x18) < 40.0f) {
        SetDeathBits(moby, 0, 3);
        moby_mark_spawned(moby);
    }
}
