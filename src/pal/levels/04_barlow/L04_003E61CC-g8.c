#include "common.h"

/* func_PAL_L04_003E61CC, the PAL copy of func_L04_003E2438: the same C at 50 Hz, where turn and move
   rates grow by 36/25 or 6/5, timers and frame numbers become (x * 5 + 2) / 6, the func_002AEB60(arg0, 3.0f)
   test is a written-out frame window, and the random timers are scaled where they are stored.
   Its own -G8 unit with -frac2-hazard-labels, as the template; see the template for how the C was reached. */

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

extern char g_hero_state[];
extern s32 g_barlow_state_flags[];
extern s32 g_game_l04_mode;
extern s32 *g_route_path_table[];
extern u8 *g_linked_record_table[] __attribute__((sda));
extern char g_effect_default_params[] __attribute__((sda));
extern u8 g_creature_light_table[];
extern TI128 g_spark_origin_quad;

extern s32 barlow_enemy_update_core_pal(u8 *);
extern void object_update_age_timer(u8 *);
extern void object_draw_linked_beam(u8 *);
extern void object_move_along_anim_sparks_pal(u8 *, void *);
extern void SelectRandomOtherLiveSlot(u8 *);
extern s32 flag_set_second_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, f32, f32, f32, f32);
extern void moby_set_state(u8 *, s32, s32);
extern void anim_start_blended_pal(u8 *a0, u32 a1, u32 a2, u32 a3);
extern s32 math_random_int_range(s32, s32);
extern s32 math_random_int_below(s32);
extern s32 point_in_path_xy(void *, void *, s32);
extern s32 moby_dispatch_action_by_kind(u8 *, void *);
extern void SetDeathBits_pal(u8 *, s32, s32);
extern void part_queue_moby_for_glow(u8 *, s32, void *);
extern void moby_mark_spawned(void *);
extern f32 math_random_float_range(f32, f32);
extern s32 math_fast_float_d(void *);
extern s32 FastDecTimer(void *);
extern f32 ApproachValue(f32 *, f32, f32);
extern void moby_wander_around_home_point_pal(u8 *, void *, f32, f32);
extern s32 path_follow_nodes_pal(u8 *, void *);
extern s32 path_set_follower_nodes(u8 *, void *, s32, s32);
extern f32 moby_turn_toward_position(u8 *, void *, void *, f32, f32, f32);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern s32 moby_l01_turn_toward_target_pal(u8 *, void *);
extern void moby_transform_joint_to_world(u32 a0, s32 a1, f32 *a2);
extern f32 math_fast_sin_or_cos_a(f32 a0);
extern f32 math_fast_sin_or_cos_b(f32 a0);
extern void FastVecScale(void *, void *, f32);
extern void make_hit_descriptor(void *, void *, s32, f32, void *);
extern int coll_sweep_from_object(void *, void *, s32, f32, f32, f32, s32, s32, s32);
extern s32 coll_process_hit(void *, f32, s32, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 moby_move_to_target_temp_limits_pal(u8 *, void *, f32, s32, f32, f32);
extern f32 moby_get_anim_value(u8 *);
extern void *part_spawn_ground_effect(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern s32 coll_test_hit_at_bone(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern void moby_set_flag_bit(u8 *, s32);
extern s32 part_l00_alloc_effect_slot_2(void *, f32, f32, f32, f32, f32);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 flag_is_third_pending_set(u8 *);
extern void part_l04_spawn_paired_sparks_pal(void *, s32);
extern void gfx_add_draw_callback_third(void *, void *);
extern void gfx_free_point_light(s32);
extern s32 moby_step_controller_pal(u8 *, void *, f32);
extern void object_set_linked_states(u8 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/* Barlow creature update: runs its core, then its state machine (idle, chase, throw, attack and tether states) (PAL). */
void barlow_creature_update_pal(u8 *moby) {
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (g_barlow_state_flags[0] == 1) {
        if (g_game_l04_mode == 2) {
            *(s32 *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        } else {
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
        }
    }
    if (barlow_enemy_update_core_pal(moby) != 0) {
        moby_mark_spawned(moby);
        return;
    }

    switch (moby[0x95]) {
    case 0: {
        s32 link_index;

        link_index = *(s32 *)(vars + 0x2F0);
        if (link_index != -1)
            break;
        if (flag_set_second_pending(moby) != 0) {
            moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (*(f32 *)(vars + 0x2C0) < 0.2f)
                object_set_linked_states(moby, 4, 3, 0, 0xA);
            if (*(s32 *)(vars + 0x2CC) != link_index && *(s32 *)(vars + 0x2C4) == link_index) {
                object_set_linked_states(moby, 5, 4, 0, 0xA);
                moby_set_state(moby, 2, -1);
            }
        }
        if (*(s32 *)(vars + 0x258) == 1 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6F) {
            if (*(s32 *)(vars + 0x2C4) != -1) {
                object_set_linked_states(moby, 6, 5, 0, 8);
                moby_set_controller_speed_limits(moby, 0.024f, 0.6f, 0.0016755164f, 0.12566373f);
                *(f32 *)(vars + 0x164) = 0.008f;
                moby_set_state(moby, 0xD, 2);
            } else if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_state(moby, 0xA, 2);
            } else {
                object_set_linked_states(moby, 0, 2, 0, 8);
                moby_set_state(moby, 0xA, 2);
            }
        } else if (*(s16 *)(vars + 0x2A6) != 0) {
            moby_set_state(moby, 8, 1);
            *(s16 *)(vars + 0x2A6) = 0;
            if (*(s16 *)(vars + 0x2A0) < 0xFA)
                *(s16 *)(vars + 0x2A0) = ((s32)math_random_int_range(0x1E0, 0x258) * 5 + 2) / 6;
            if (*(s32 *)(vars + 0x2CC) != -1) {
                moby_set_state(moby, 8, 1);
                object_set_linked_states(moby, 4, 3, 0, 0xA);
            }
        } else if (*(s32 *)(vars + 0x2DC) != -1 &&
                   point_in_path_xy(vars + 0x230, (u8 *)g_route_path_table[*(s32 *)(vars + 0x2DC)] + 0x10,
                                 *g_route_path_table[*(s32 *)(vars + 0x2DC)]) != 0) {
            object_set_linked_states(moby, 6, 5, 0, 8);
            moby_set_controller_speed_limits(moby, 0.024f, 0.6f, 0.0016755164f, 0.12566373f);
            *(f32 *)(vars + 0x164) = 0.008f;
            moby_set_state(moby, 0xD, 2);
        }
        break;
    }
    case 1:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if (*(s32 *)(vars + 0x258) == 1 || *(s32 *)(vars + 0x25C) == 1) {
            if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_state(moby, 0xA, 2);
            } else {
                object_set_linked_states(moby, 0, 2, 0, 8);
                moby_set_state(moby, 0xA, 2);
            }
        } else if (*(s16 *)(vars + 0x2A0) == 0 && *(s32 *)(vars + 0x30C) == 0) {
            moby_set_state(moby, 1, 0);
            object_set_linked_states(moby, 5, 4, 0, 0xA);
        }
        break;
    case 2:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if ((*(s32 *)(vars + 0x2DC) == -1 ||
             point_in_path_xy(vars + 0x230, (u8 *)g_route_path_table[*(s32 *)(vars + 0x2DC)] + 0x10,
                           *g_route_path_table[*(s32 *)(vars + 0x2DC)]) == 0) &&
            *(s32 *)(vars + 0x258) != 1 && *(s32 *)(vars + 0x25C) != 1) {
            if (moby[0x20] == 0xD || moby[0x20] == 0x10 || moby[0x20] == 0xC) {
            } else if (moby[0x20] == 0xF) {
                object_set_linked_states(moby, 8, 0, 1, 2);
                moby_set_state(moby, 0x10, -1);
            } else if (*(s32 *)(vars + 0x2CC) != -1 && *(s32 *)(vars + 0x2C4) == -1) {
                object_set_linked_states(moby, 5, 4, 0, 0xA);
                moby_set_state(moby, 2, 1);
            } else {
                *(s32 *)(vars + 0x2D0) = 0;
                object_set_linked_states(moby, 3, 1, 0, 0xA);
                moby_set_state(moby, 8, 1);
                if (*(s32 *)(vars + 0x2D4) != -1) {
                    qcopy(vars + 0x110, g_linked_record_table[0] + (*(s32 *)(vars + 0x2D4) << 7) + 0x30);
                    if (*(f32 *)(vars + 0x12C) == 0.0f)
                        *(f32 *)(vars + 0x12C) = 4.0f;
                }
                *(s16 *)(vars + 0x2A0) = ((s32)math_random_int_range(0x4B0, 0x514) * 5 + 2) / 6;
            }
        }
        break;
    case 3: {
        s32 action_flags;
        s32 link_index;

        action_flags = moby_dispatch_action_by_kind(moby, vars + 0x60);
        if (action_flags & 1) {
            SetDeathBits_pal(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, 0);
            return;
        }
        if (action_flags & 2) {
            link_index = *(s32 *)(vars + 0x2F0);
            if (link_index != -1) {
                object_set_linked_states(moby, 6, 5, 0, 8);
                moby_set_state(moby, 7, 0);
                *(s8 *)(vars + 0x307) = 0x64;
            } else if (*(s32 *)(vars + 0x258) == 1 || *(s32 *)(vars + 0x25C) == 1) {
                object_set_linked_states(moby, 6, 5, 0, 8);
                moby_set_state(moby, 0xB, 2);
            } else {
                moby_set_state(moby, 8, 1);
                object_set_linked_states(moby, 1, 1, 0, 8);
                *(s16 *)(vars + 0x2A0) = ((s32)math_random_int_range(0x244, 0x258) * 5 + 2) / 6;
                if (*(s32 *)(vars + 0x2CC) != -1) {
                    moby_set_state(moby, 8, 1);
                    object_set_linked_states(moby, 4, 3, 0, 0xA);
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
            if (*(s32 *)(vars + 0x2BC) >= 0x12)
                *(f32 *)(vars + 0x124) = 0.080000006f;
            else
                ApproachValue((f32 *)(vars + 0x124), 0.0f, 0.0016000001f);
            if (moby[0x43] == 5) {
                if (*(s32 *)(vars + 0x2BC) == 0) {
                    object_set_linked_states(moby, 1, 1, 0, 0xA);
                    if (math_random_int_below(2) == 1)
                        object_set_linked_states(moby, 0, 0, 0, 0xA);
                }
                moby_wander_around_home_point_pal(moby, vars + 0x110, 0.35f, 0.25f);
            } else if (moby[0x43] < 2 && (moby[0x60] & 2)) {
                *(s32 *)(vars + 0x2BC) = math_random_int_range(0x64, 0x247);
                object_set_linked_states(moby, 5, 4, 0, 0xA);
            }
        } else if (*(u8 **)(vars + 0x2AC) != 0 && (*(u8 **)(vars + 0x2AC))[0x43] != 3) {
            object_set_linked_states(moby, 4, 3, 0, 0xA);
        }
        break;
    case 2:
        if (path_follow_nodes_pal(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)]) != 0) {
            moby_set_state(moby, 4, -1);
            object_set_linked_states(moby, 4, 3, 0, 8);
            path_set_follower_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)], 0, 1);
            *(s32 *)(vars + 0x308) = 1;
        }
        break;
    case 3:
        if (path_follow_nodes_pal(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)]) != 0) {
            moby_set_state(moby, 4, -1);
            object_set_linked_states(moby, 4, 3, 0, 8);
            path_set_follower_nodes(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)], 1, 0);
            *(s32 *)(vars + 0x308) = 0;
        }
        break;
    case 4:
        if (moby[0x60] & 2) {
            object_set_linked_states(moby, 0xF, 0x17, 0, 6);
            moby_set_state(moby, 0x15, -1);
        }
        break;
    case 5:
        if (FastDecTimer(vars + 0x300) != 0) {
            object_set_linked_states(moby, 5, 4, 0, 8);
            SelectRandomOtherLiveSlot(moby);
            moby_set_state(moby, 6, 0);
        }
        break;
    case 6: {
        {
        f32 target_pos[4] __attribute__((aligned(16)));

        *(TI128 *)target_pos = *(TI128 *)(vars + 0x280);
        moby_set_controller_speed_limits(moby, 0.00064000004f, 0.032f, 0.0016755164f, 0.12566373f);
        moby_l01_turn_toward_target_pal(moby, target_pos);
        if (vec_distance_xy(moby + 0x10, target_pos) < 1.0f) {
            object_set_linked_states(moby, 1, 1, 0, 8);
            *(s16 *)(vars + 0x300) = ((s32)math_random_int_range(0x4B0, 0xBB8) * 5 + 2) / 6;
            moby_set_state(moby, 5, -1);
        }
        }
        break;
    }
    case 7: {
        {
        f32 target_pos[4] __attribute__((aligned(16)));
        f32 max_speed;

        *(TI128 *)target_pos = *(TI128 *)(vars + 0x280);
        moby_set_controller_speed_limits(moby, 0.0009600001f, 0.048000004f, 0.0016755164f, 0.12566373f);
        object_move_along_anim_sparks_pal(moby, target_pos);
        max_speed = (*(f32 *)(vars + 0x16C) * 150.0f + 2.0f) * 0.16666667f;
        if (max_speed < *(f32 *)(vars + 0x1E8))
            *(f32 *)(vars + 0x1E8) = max_speed;
        if (vec_distance_xy(moby + 0x10, target_pos) < 1.0f || *(s32 *)(vars + 0x1C0) >= 0x33) {
            object_set_linked_states(moby, 1, 1, 0, 8);
            *(s16 *)(vars + 0x300) = ((s32)math_random_int_range(0x4B0, 0xBB8) * 5 + 2) / 6;
            moby_set_state(moby, 5, -1);
        }
        }
        break;
    }
    case 8:
        math_fast_float_d(vars + 0x2BC);
        if (*(s32 *)(vars + 0x2BC) >= 0x12)
            ApproachValue((f32 *)(vars + 0x124), 0.080000006f, 0.0028000001f);
        else
            ApproachValue((f32 *)(vars + 0x124), 0.0f, 0.0028000001f);
        if (moby[0x43] == 6) {
            if (*(s32 *)(vars + 0x2BC) == 0) {
                object_set_linked_states(moby, 3, 2, 0, 0xA);
                if (math_random_int_below(2) == 1)
                    object_set_linked_states(moby, 4, 3, 0, 0xA);
            }
            moby_wander_around_home_point_pal(moby, vars + 0x110, 0.35f, 0.25f);
        } else if ((u8)(moby[0x43] - 3) < 2 && (moby[0x60] & 2)) {
            *(s32 *)(vars + 0x2BC) = math_random_int_range(0x64, 0x247);
            object_set_linked_states(moby, 6, 5, 0, 0xA);
        }
        break;
    case 9:
        if (moby[0x60] & 2) {
            object_set_linked_states(moby, 5, 4, 0, 0xA);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 10:
        moby_turn_toward_position(moby, *(void **)(vars + 0x240), vars + 0x2B4, 0.001f, 0.01f, 0.1f);
        if (*(u8 **)(vars + 0x2AC) != 0) {
            moby_set_state(moby, 0x14, -1);
            object_set_linked_states(moby, 0x10, 4, 0, 8);
        } else if (*(s32 *)(vars + 0x2D8) != 0) {
            moby_set_state(moby, 0xF, -1);
            object_set_linked_states(moby, 7, 5, 0, 8);
        } else {
            moby_set_state(moby, 0xB, -1);
            object_set_linked_states(moby, 6, 5, 0, 8);
        }
        break;
    case 11:
        object_move_along_anim_sparks_pal(moby, vars + 0x230);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (*(u8 **)(vars + 0x2AC) != 0) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 20.0f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.17453295f) {
                object_set_linked_states(moby, 9, 6, 0, 8);
                moby_set_state(moby, 0xE, -1);
            }
        } else {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 2.7f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.3490659f) {
                object_set_linked_states(moby, 0xC, 0, 0, 4);
                moby_set_state(moby, 0x11, -1);
            }
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) > 2.7f && (moby[0x42] == 5 || moby[0x42] == 0x10)) {
                object_set_linked_states(moby, 6, 5, 0, 3);
                moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            }
        }
        break;
    case 15: {
        *(f32 *)(vars + 0x164) = 0.010000001f;
        moby_set_controller_speed_limits(moby, 0.0096f, 0.24000001f, 0.0016755164f, 0.12566373f);
        moby_l01_turn_toward_target_pal(moby, vars + 0x230);
        moby_turn_toward_position(moby, *(void **)(vars + 0x240), vars + 0x2B4, 0.001f, 0.01f, 0.1f);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 3.5f) {
            object_set_linked_states(moby, 8, 0, 1, 2);
            *(f32 *)(moby + 0x48) = 1.0f;
            moby_set_state(moby, 0x10, -1);
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));
        f32 dir_z;

        moby_transform_joint_to_world((u32)moby, 1, pos);
        dir[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8));
        dir[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8));
        dir[2] = 0.0f;
        dir_z = dir[2];
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        FastVecScale(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        make_hit_descriptor(req, moby, 1, *(f32 *)(vars + 0x2E8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
        req[0x18] = 0;
        coll_process_hit(pos, 1.1f, 0, moby, req);
        coll_sweep_from_object(moby, pos, 0x10000, 1.1f, *(f32 *)(vars + 0x2E8) * 4.0f, dir_z, 0, 1, 0);
        }
        break;
    }
    case 16: {
        u8 *position;

        position = moby + 0x10;
        {
        f32 off[4] __attribute__((aligned(16)));
        moby_set_controller_speed_limits(moby, 0.006f, 0.040000003f, 0.0016755164f, 0.12566373f);
        off[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 4.0f;
        off[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 4.0f;
        off[2] = 0.0f;
        FastVecAdd(off, position, off);
        moby_l01_turn_toward_target_pal(moby, vars + 0x230);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (moby[0x60] & 2) {
            object_set_linked_states(moby, 2, 2, 0, 8);
            moby_set_state(moby, 0xC, -1);
            if (vec_distance_xy(position, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.0f) {
                moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                if (moby[0x43] != 0x11)
                    anim_start_blended_pal(moby, 0x11, 0, 8);
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
        moby_set_controller_speed_limits(moby, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
        {
        f32 target_pos[4] __attribute__((aligned(16)));

        vec_scale_to_length(target_pos, moby + 0xC0, -5.5f);
        FastVecAdd(target_pos, target_pos, moby + 0x10);
        moby_move_to_target_temp_limits_pal(moby, target_pos, mat_fast_helper_a(target_pos[0] - *(f32 *)(moby + 0x10), target_pos[1] - *(f32 *)(moby + 0x14)), 0x10, -1.0f, -1.0f);
        }
        if (*(u16 *)(moby + 0x96) >= 0x65) {
            *(f32 *)(vars + 0x164) = 0.0012f;
            if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                object_set_linked_states(moby, 9, 6, 0, 8);
                moby_set_state(moby, 0xE, -1);
            } else {
                moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                object_set_linked_states(moby, 6, 5, 0, 8);
                moby_set_state(moby, 0xB, -1);
            }
        }
        break;
    }
    case 12:
        if (moby[0x60] & 2) {
            *(f32 *)(vars + 0x164) = 0.0012f;
            if (*(u8 **)(vars + 0x2AC) != 0) {
                moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                object_set_linked_states(moby, 9, 6, 0, 8);
                moby_set_state(moby, 0xE, -1);
            } else {
                moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                object_set_linked_states(moby, 6, 5, 0, 8);
                moby_set_state(moby, 0xB, -1);
            }
        }
        break;
    case 13:
        moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if (path_follow_nodes_pal(moby, g_route_path_table[*(s32 *)(vars + 0x2C4)]) != 0) {
            moby_set_state(moby, 0x14, -1);
            object_set_linked_states(moby, 0x10, 4, 0, 8);
            moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            *(s32 *)(vars + 0x2C4) = -1;
            *(f32 *)(vars + 0x164) = 0.0012f;
            *(s32 *)(vars + 0x2DC) = -1;
        }
        break;
    case 14: {
        f32 hand_pos[4] __attribute__((aligned(16)));
        f32 offset_vec[4] __attribute__((aligned(16)));
        f32 f, anim_frame;
        s32 side;

        if (*(u8 **)(vars + 0x2AC) != 0 && moby[0x42] == 9) {
            moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, hand_pos);
            offset_vec[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
            offset_vec[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
            offset_vec[2] = 0.0f;
            FastVecAdd(hand_pos, hand_pos, offset_vec);
            hand_pos[2] -= 0.05f;
            anim_frame = moby_get_anim_value(moby);
            f = math_random_float_range(0.2f, 0.9f) * 0.2f * anim_frame;
            side = math_random_int_below(2);
            if (side == 0)
                side = side - 1;
            part_spawn_ground_effect(hand_pos, 2, f * 0.3f, f, 0x804020FF, 0, side, g_effect_default_params, 0.0f, 0);
            part_spawn_ground_effect(hand_pos, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -side, g_effect_default_params, 0.0f, 0);
            *(f32 *)(vars + 0x2B8) = anim_frame;
        }
        if (*(u16 *)(moby + 0x96) >= 0x2E) {
            object_set_linked_states(moby, 0xA, 7, 0, 8);
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
                object_set_linked_states(moby, 0xC, 0, 0, 8);
                moby_set_state(moby, 0x11, -1);
            } else {
                moby_set_state(moby, 0xB, -1);
                object_set_linked_states(moby, 6, 5, 0, 8);
                moby_set_controller_speed_limits(moby, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            }
        }
        break;
    }
    case 18: {
        f32 t;
        f32 hit_power;

        if (moby[0x60] & 2) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 25.0f && *(u8 **)(vars + 0x2AC) != 0 &&
                *(s32 *)(vars + 0x2D0) < 3) {
                if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                     *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) > 0.087266475f) {
                    moby_set_state(moby, 0x14, -1);
                    object_set_linked_states(moby, 0x10, 4, 0, 8);
                } else {
                    object_set_linked_states(moby, 9, 6, 0, 8);
                    moby_set_state(moby, 0xE, -1);
                }
            } else if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) > 10.0f && *(u8 **)(vars + 0x2AC) != 0 &&
                       *(s32 *)(vars + 0x2D0) >= 3) {
                object_set_linked_states(moby, 3, 2, 0, 8);
                moby_set_state(moby, 0x13, -1);
                *(s32 *)(vars + 0x2D0) = 0;
            } else {
                moby_set_state(moby, 0x14, -1);
                object_set_linked_states(moby, 0x10, 4, 0, 8);
            }
            if (*(u8 **)(vars + 0x2AC) != 0) {
                *(s32 *)(vars + 0x2D0) = *(s32 *)(vars + 0x2D0) + 1;
            } else {
                moby_set_state(moby, 0xB, -1);
                object_set_linked_states(moby, 6, 5, 0, 8);
                break;
            }
        } else if (moby_get_anim_value(moby) >= 2.8333335f && moby_get_anim_value(moby) < 3.25f && *(u8 **)(vars + 0x2AC) != 0) {
            f32 hand_pos[4] __attribute__((aligned(16)));
            f32 offset_vec[4] __attribute__((aligned(16)));

            if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.78539824f) {
                s32 light_id;
                u8 *effect;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, hand_pos);
                offset_vec[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                offset_vec[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                offset_vec[2] = 0.0f;
                FastVecAdd(hand_pos, hand_pos, offset_vec);
                hand_pos[2] -= 0.05f;
                *(TI128 *)(vars + 0x260) = *(TI128 *)hand_pos;
                FastVecSub(vars + 0x280, vars + 0x230, hand_pos);
                *(f32 *)(vars + 0x2C8) = 0.0f;
                moby_set_flag_bit(moby, 0);
                light_id = part_l00_alloc_effect_slot_2(moby + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(vars + 0x2E0) = light_id;
                if (light_id >= 0) {
                    effect = g_creature_light_table + (light_id << 5);
                    qcopy(effect + 0x10, vars + 0x260);
                    *(f32 *)(effect + 0x1C) = 5.0f;
                    *(f32 *)(effect + 0) = 1.0f;
                    *(f32 *)(effect + 4) = 0.0f;
                    *(f32 *)(effect + 0x18) = *(f32 *)(effect + 0x18) + 1.0f;
                    *(f32 *)(effect + 8) = 0.0f;
                    *(f32 *)(effect + 0xC) = 0.0f;
                }
            } else {
                s32 light_id;
                u8 *effect;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, hand_pos);
                offset_vec[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                offset_vec[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                offset_vec[2] = 0.0f;
                FastVecAdd(hand_pos, hand_pos, offset_vec);
                hand_pos[2] -= 0.05f;
                *(TI128 *)(vars + 0x260) = *(TI128 *)hand_pos;
                offset_vec[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 25.0f;
                offset_vec[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 25.0f;
                offset_vec[2] = 0.0f;
                FastVecAdd(offset_vec, offset_vec, moby + 0x10);
                FastVecSub(vars + 0x280, offset_vec, hand_pos);
                *(f32 *)(vars + 0x2C8) = 0.0f;
                moby_set_flag_bit(moby, 0);
                light_id = part_l00_alloc_effect_slot_2(moby + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(vars + 0x2E0) = light_id;
                if (light_id >= 0) {
                    effect = g_creature_light_table + (light_id << 5);
                    qcopy(effect + 0x10, vars + 0x260);
                    *(f32 *)(effect + 0x1C) = 5.0f;
                    *(f32 *)(effect + 0) = 1.0f;
                    *(f32 *)(effect + 4) = 0.0f;
                    *(f32 *)(effect + 0x18) = *(f32 *)(effect + 0x18) + 1.0f;
                    *(f32 *)(effect + 8) = 0.0f;
                    *(f32 *)(effect + 0xC) = 0.0f;
                }
            }
        }
        t = moby_get_anim_value(moby);
        if (t < 2.8333335f || moby[0x42] != 0xA) {
            if (*(u8 **)(vars + 0x2AC) != 0) {
                f32 hand_pos[4] __attribute__((aligned(16)));
                f32 offset_vec[4] __attribute__((aligned(16)));
                f32 f;
                s32 side;

                moby_transform_joint_to_world(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, hand_pos);
                offset_vec[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                offset_vec[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                offset_vec[2] = 0.0f;
                FastVecAdd(hand_pos, hand_pos, offset_vec);
                hand_pos[2] -= 0.05f;
                f = math_random_float_range(0.2f, 0.9f) * 0.2f * *(f32 *)(vars + 0x2B8);
                side = math_random_int_below(2);
                if (side == 0)
                    side = side - 1;
                part_spawn_ground_effect(hand_pos, 2, f * 0.3f, f, 0x804020FF, 0, side, g_effect_default_params, 0.0f, 0);
                part_spawn_ground_effect(hand_pos, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -side, g_effect_default_params, 0.0f, 0);
                *(f32 *)(vars + 0x2B8) = *(f32 *)(vars + 0x2B8) + 1.0f;
            }
        }
        hit_power = (f32)vars[0x35];
        if (t >= 2.8333335f) {
            if (t < 7.8333335f) {
                if (moby[0x42] == 0xA) {
            u8 req[0x30] __attribute__((aligned(16)));
            f32 v30[4] __attribute__((aligned(16)));
                                    u8 *effect;
            f32 f, f3, f04, f4;
            s32 side;

            *(f32 *)(vars + 0x2C8) = *(f32 *)(vars + 0x2C8) + 1.2f;
            vec_scale_to_length(vars + 0x270, vars + 0x280, *(f32 *)(vars + 0x2C8));
            make_hit_descriptor(req, moby, 0x04000001, hit_power, vars + 0x270);
            *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
            FastVecAdd(vars + 0x270, vars + 0x260, vars + 0x270);
            if (CollLine(vars + 0x260, vars + 0x270, 0, moby, req) != 0) {
                *(TI128 *)(vars + 0x270) = g_spark_origin_quad;
                if (flag_is_third_pending_set(moby) == 0) {
                    part_l04_spawn_paired_sparks_pal(&g_spark_origin_quad, 0x1E);
                    moby_set_flag_bit(moby, 1);
                }
            }
            f = math_random_float_range(1.0f, 6.0f);
            side = math_random_int_range(0x19, 0x23);
            if (side == 0)
                side = side - 1;
            qcopy(v30, vars + 0x270);
            v30[2] -= 0.1f;
            f3 = f * 0.3f;
            part_spawn_ground_effect(v30, 0x15, f3, f, 0xFF000080, 0, side, g_effect_default_params, 0.0f, 0);
            side = -side;
            f04 = f * 0.04f;
            f4 = f * 0.4f;
            part_spawn_ground_effect(v30, 4, f04, f4, 0x7F6F6FFF, 1, side, g_effect_default_params, 0.0f, 0);
            part_spawn_ground_effect(v30, 0x11, f4, f * 0.2f, 0xFF4080FF, 1, side, g_effect_default_params, 0.0f, 0);
            part_spawn_ground_effect(vars + 0x260, 8, f3, f, 0x80CA00CB, 0, side, g_effect_default_params, 0.0f, 0);
            part_spawn_ground_effect(vars + 0x260, 8, f04, f4, 0x7F6F6FFF, 1, -side, g_effect_default_params, 0.0f, 0);
            gfx_add_draw_callback_third(object_draw_linked_beam, moby);
            if (*(s32 *)(vars + 0x2E0) >= 0) {
                effect = g_creature_light_table + (*(s32 *)(vars + 0x2E0) << 5);
                qcopy(effect + 0x10, vars + 0x270);
                *(f32 *)(effect + 0x1C) = 5.0f;
                *(f32 *)(effect + 0) = 1.0f;
                *(f32 *)(effect + 4) = 0.0f;
                *(f32 *)(effect + 0x18) = *(f32 *)(effect + 0x18) + 1.0f;
                *(f32 *)(effect + 8) = 0.0f;
                *(f32 *)(effect + 0xC) = 0.0f;
            }
                }
            }
        }
        if (t >= 7.8333335f && t < 12.833334f && moby[0x42] == 0xA) {
                        
            if (vec_distance_xy(vars + 0x260, vars + 0x270) > 0.5f) {
                u8 req[0x30] __attribute__((aligned(16)));
                f32 v30[4] __attribute__((aligned(16)));
                f32 v40[4] __attribute__((aligned(16)));
                u8 *effect;
                f32 f, f4;
                s32 side;

                *(f32 *)(vars + 0x2C8) = *(f32 *)(vars + 0x2C8) + 1.2f;
                vec_scale_to_length(vars + 0x270, vars + 0x280, *(f32 *)(vars + 0x2C8));
                make_hit_descriptor(req, moby, 0x04000001, hit_power, vars + 0x270);
                *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
                FastVecAdd(vars + 0x270, vars + 0x260, vars + 0x270);
                if (CollLine(vars + 0x260, vars + 0x270, 0, moby, req) != 0) {
                    *(TI128 *)(vars + 0x270) = g_spark_origin_quad;
                    if (flag_is_third_pending_set(moby) == 0) {
                        part_l04_spawn_paired_sparks_pal(&g_spark_origin_quad, 0x1E);
                        moby_set_flag_bit(moby, 1);
                    }
                }
                vec_scale_to_length(v30, vars + 0x280, 2.0000002f);
                FastVecAdd(vars + 0x260, vars + 0x260, v30);
                f = math_random_float_range(1.0f, 6.0f);
                side = math_random_int_range(0x19, 0x23);
                if (side == 0)
                    side = side - 1;
                qcopy(v40, vars + 0x270);
                v40[2] -= 0.1f;
                part_spawn_ground_effect(v40, 0x15, f * 0.3f, f, 0xFF000080, 0, side, g_effect_default_params, 0.0f, 0);
                side = -side;
                f4 = f * 0.4f;
                part_spawn_ground_effect(v40, 4, f * 0.04f, f4, 0x7F6F6FFF, 1, side, g_effect_default_params, 0.0f, 0);
                part_spawn_ground_effect(v40, 0x11, f4, f * 0.2f, 0xFF4080FF, 1, side, g_effect_default_params, 0.0f, 0);
                gfx_add_draw_callback_third(object_draw_linked_beam, moby);
                if (*(s32 *)(vars + 0x2E0) >= 0) {
                    effect = g_creature_light_table + (*(s32 *)(vars + 0x2E0) << 5);
                    qcopy(effect + 0x10, vars + 0x270);
                    *(f32 *)(effect + 0x1C) = 5.0f;
                    *(f32 *)(effect + 0) = 1.0f;
                    *(f32 *)(effect + 4) = 0.0f;
                    *(f32 *)(effect + 0x18) = *(f32 *)(effect + 0x18) + 1.0f;
                    *(f32 *)(effect + 8) = 0.0f;
                    *(f32 *)(effect + 0xC) = 0.0f;
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
        u8 *position = moby + 0x10;

        if (moby[0x60] & 2) {
            if (vec_distance_xy(position, *(u8 **)(vars + 0x240) + 0x10) < 25.0f && *(u8 **)(vars + 0x2AC) != 0) {
                moby_set_state(moby, 0x14, -1);
                object_set_linked_states(moby, 5, 4, 0, 8);
            } else {
                moby_set_state(moby, 0xB, -1);
                object_set_linked_states(moby, 6, 5, 0, 8);
            }
        } else if (vec_distance_xy(position, *(u8 **)(vars + 0x240) + 0x10) < 6.0f) {
            object_set_linked_states(moby, 9, 6, 0, 8);
            moby_set_state(moby, 0xE, -1);
        }
        break;
    }
    case 20:
        if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                             *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) <= 0.087266475f) {
            object_set_linked_states(moby, 9, 6, 0, 8);
            moby_set_state(moby, 0xE, -1);
        } else {
            moby_step_controller_pal(moby, moby + 0x10, mat_fast_helper_a(*(f32 *)(*(u8 **)(vars + 0x240) + 0x10) - *(f32 *)(moby + 0x10),
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
            moby_set_controller_speed_limits(moby, 0.16000001f, 0.080000006f, 0.013962637f, 0.8377582f);
            path_follow_nodes_pal(moby, g_route_path_table[*(s32 *)(vars + 0x2CC)]);
        }
        break;
    }
    object_update_age_timer(moby);
    if (*(f32 *)(moby + 0x18) < 40.0f) {
        SetDeathBits_pal(moby, 0, 3);
        moby_mark_spawned(moby);
    }
}
