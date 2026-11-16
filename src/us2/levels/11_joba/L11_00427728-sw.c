#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
extern char g_hero_state[];
extern u8 *const g_moby_l11_table[] __attribute__((sda));
extern u8 *g_arena_camera_table[] __attribute__((sda));
extern void *g_group_id_lists[];
extern s32 *g_path_l11_table[];
extern s32 g_enemy_freeze_flag[];
extern s32 g_active_rider_count[] __attribute__((sda));
extern s32 g_tribe_group_limit __attribute__((sda));
extern s32 g_tribe_fighter_spark_color_a __attribute__((sda));
extern s32 g_tribe_fighter_spark_color_b __attribute__((sda));
extern f32 g_tribe_fighter_spark_frame_scale __attribute__((sda));
extern char g_identity_l11_matrix[] __attribute__((sda));
extern void anim_start_blended(u8 *a0, u32 a1, u32 a2, u32 a3);
extern void moby_transform_joint_to_world(u32 a0, s32 a1, f32 *a2);
extern f32 math_fast_sin_or_cos_a(f32 a0);
extern f32 math_fast_sin_or_cos_b(f32 a0);
extern void FastVecAdd(void *, void *, void *);
extern s32 jobian_lieutenant_update_us2(u8 *);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern s32 flag_is_third_pending_set(u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern f32 moby_get_anim_value(u8 *);
extern f32 coll_probe_ground_height_below(void *, s32, f32);
extern s32 math_random_int_below(s32);
extern void moby_set_controller_speed_limits(u8 *, f32, f32, f32, f32);
extern s32 moby_count_group_not_in_state(s32, s32);
extern u8 *moby_find_linked_object(u8 *);
extern s32 moby_step_controller(u8 *, void *, f32);
extern s32 path_follow_nodes(u8 *, void *);
extern s32 path_set_follower_nodes(u8 *, void *, s32, s32);
extern s32 moby_l01_turn_toward_target(u8 *, void *);
extern s32 moby_turn_toward_target_and_step(u8 *, void *, f32);
extern f32 vec_spring_to_target(void *, void *, void *, f32, f32, f32);
extern void euler_rotation_basis(void *, void *);
extern f32 math_spring_float_to_goal(void *, void *, f32, f32, f32, f32);
extern f32 math_fabs(f32);
extern s32 math_is_value_within_step_us2(u8 *, f32);
extern char *SpawnStateVectorMoby(u8 *, f32 *, f32 *, f32);
extern f32 math_random_float_range(f32, f32);
extern void *part_spawn_ground_effect(void *, u32, u32, u32, s32, void *, f32, f32, f32, s32);
extern f32 moby_turn_toward_position(u8 *, void *, void *, f32, f32, f32);
extern void moby_set_flag_bit(u8 *, s32);
extern int coll_sweep_from_object(void *, void *, s32, f32, f32, f32, s32, s32, s32);
extern s32 flag_set_second_pending(u8 *);
extern void moby_mark_spawned(void *);
extern s32 moby_dispatch_action_by_kind(u8 *, void *);
extern void SetDeathBits_us2(u8 *, s32, s32);
extern void part_queue_moby_for_glow(u8 *, s32, void *);
extern void moby_copy_joint_transform_to_object(u8 *, void *, s32, s32);
extern void part_spawn_explosion_with_sparks(u8 *, void *, f32, f32, s32);
extern s32 tribesman_tick_linked_clock(u8 *);
extern u8 *CreateMoby(s32);
extern void func_002A0F48(void *);
extern void build_axis_rotation_quaternion(void *, s32, f32);
extern void saur_beast_prepare_two_stage_anim(u8 *arg0);
extern int saur_beast_walk_to_target(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin);
extern void FastVecSub(void *, void *, void *);
extern f32 FastDiffRots(f32, f32);
extern void vec_scale_to_length(void *, void *, f32);
extern int moby_move_over_ground(void *, void *, void *, f32, f32, f32, f32, int);

/* Updates one of the Joba tribe fighters (a sibling of the Tribesman). It picks animations from its mode, chases and faces the hero, throws spark shots, rides or follows a linked partner, and removes itself when it is done. (USA v2.00) */
void tribe_fighter_update_us2(u8 *moby) {
    f32 vec_a[4] __attribute__((aligned(16)));
    f32 vec_b[4] __attribute__((aligned(16)));
    f32 vec_c[4] __attribute__((aligned(16)));
    f32 vec_d[4] __attribute__((aligned(16)));
    u8 *data;
    f32 z0;
    f32 lim1_9;
    f32 a1_9;
    s32 i1_9;
    s32 r1_0;
    f32 d1_1;
    s32 i1_1;
    s32 best1_1;
    f32 f1_1;
    s32 i1_2;
    s32 i1_8;
    f32 f1_4;
    s32 r1_4;
    u8 *p1_5;
    u8 *q1_5;
    u8 *p1_6;
    u8 *p1_7;
    u8 *q1_7;
    f32 a1_7;
    f32 f1_7;
    f32 f2_2;
    f32 f2_3;
    s32 r2_5;
    s32 n2_5;
    u8 *p2_5;
    u8 c2_5;
    s32 *path2_12;
    f32 d2_12;
    s32 *path2_18;
    f32 d2_18;
    f32 f2_23;
    u8 c2_23;
    u16 *list2_23;
    u8 *base2_23;
    u8 *o2_23;
    u8 *q2_23;
    f32 d2_23;
    u8 *p2_25;
    u8 *q2_25;
    u8 *p2_32;
    f32 f2_32;
    u8 *p2_33;
    s32 *path2_34;
    s32 *pathb2_34;
    u8 *p2_34;
    f32 f2_19;
    f32 f2_20;
    s32 n2_20;
    f32 f2_22;
    f32 f2_27;
    f32 a2_27;
    s32 n2_27;
    f32 f2_28;
    f32 f2_29, g2_29;
    f32 a2_29;
    s32 n2_29;

    if (g_enemy_freeze_flag[0] != 0)
        return;
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x6F && moby[0x95] != 4)
        return;
    z0 = *(f32 *)(moby + 0x18);
    data = *(u8 **)(moby + 0x68);
    if (jobian_lieutenant_update_us2(moby) != 0) {
        moby_mark_spawned(moby);
        return;
    }
    switch (moby[0x95]) {
    case 9:
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 6.0f) {
            lim1_9 = 1.5707965f;
            a1_9 = fast_subtract_rotations(mat_fast_helper_a(*(f32 *)(((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x10) - *(f32 *)(moby + 0x10),
                                            *(f32 *)(((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x14) - *(f32 *)(moby + 0x14)),
                              *(f32 *)(moby + 0xF8));
            if (flag_is_third_pending_set(moby) != 0)
                a1_9 = -a1_9;
            if (a1_9 > lim1_9)
                a1_9 = lim1_9;
            else if (a1_9 < -lim1_9)
                a1_9 = -lim1_9;
            *(f32 *)(data + 0x308) = a1_9;
        }
        if (((Hero *)g_hero_state)->i[0x1248 / 4] != 0x41)
            moby[0x95] = 0;
        break;
    case 0:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0015277779f, 0.045833334f, 0.001163553f, 0.10471977f);
        if (*(s16 *)(data + 0x264) == 2) {
            if (*(s32 *)(data + 0x284) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x1A, 2);
            }
            if (*(s32 *)(data + 0x548) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x19, 2);
            } else if (*(s32 *)(data + 0x294) == 1) {
                if (moby[0x43] != 0xA)
                    anim_start_blended(moby, 0xA, math_random_int_below(4), math_random_int_range(7, 0x14));
                moby_set_state(moby, 0x13, 2);
            } else {
                if (*(s32 *)(data + 0x570) != 0) {
                    if (moby[0x43] != 2)
                        anim_start_blended(moby, 2, 0, 0xA);
                    moby_set_state(moby, 0x13, 3);
                } else {
                    *(s32 *)(data + 0x290) = 1;
                    if (moby[0x43] != 2)
                        anim_start_blended(moby, 2, 0, 0x28);
                    moby_set_state(moby, 0x13, 3);
                }
            }
        } else if (*(s16 *)(data + 0x266) != 0) {
            if (*(s32 *)(data + 0x558) != -1) {
                r1_0 = *(s32 *)(data + 0x560);
                if (r1_0 == 1) {
                    if (moby[0x43] != 9)
                        anim_start_blended(moby, 9, 0, math_random_int_range(5, 0xF));
                    moby_set_state(moby, 6, -1);
                } else if (r1_0 >= 2) {
                    if (moby[0x43] != 3)
                        anim_start_blended(moby, 3, 0, math_random_int_range(5, 0xF));
                    moby_set_state(moby, 7, -1);
                    moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
                }
            }
            if (*(s32 *)(data + 0x548) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x19, 2);
            }
            if ((u16)(*(s16 *)(data + 0x264) - 1) < 2) {
                if (*(s32 *)(data + 0x294) == 1) {
                    if (moby[0x43] != 0xA)
                        anim_start_blended(moby, 0xA, 0, math_random_int_range(0xA, 0x14));
                    moby_set_state(moby, 0x13, 2);
                } else if (*(s32 *)(data + 0x570) != 0) {
                    if (moby[0x43] != 2)
                        anim_start_blended(moby, 2, 0, 0x28);
                    moby_set_state(moby, 0x13, 3);
                } else {
                    *(s32 *)(data + 0x290) = 1;
                    if (moby[0x43] != 2)
                        anim_start_blended(moby, 2, 0, 0xA);
                    moby_set_state(moby, 0x13, 3);
                }
            }
            *(s16 *)(data + 0x266) = 0;
        }
        break;
    case 1:
        if (flag_set_second_pending(moby) != 0) {
            moby_set_controller_speed_limits(moby, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
            *(f32 *)(data + 0x12C) = 6.0f;
        }
        if ((u16)(*(s16 *)(data + 0x264) - 1) < 2) {
            if (*(s32 *)(data + 0x284) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                d1_1 = 100.0f;
                moby_set_state(moby, 0x1A, 2);
                i1_1 = 0;
                best1_1 = 0;
                for (; i1_1 < *g_path_l11_table[*(s32 *)(data + 0x284)]; ) {
                    f1_1 = vec_distance_xy(moby + 0x10, (u8 *)g_path_l11_table[*(s32 *)(data + 0x284)] + 0x10 + i1_1 * 0x10);
                    if (f1_1 < d1_1) {
                        d1_1 = f1_1;
                        best1_1 = i1_1;
                    }
                    i1_1++;
                }
                path_set_follower_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x284)], -1, best1_1);
            }
            if (*(s32 *)(data + 0x548) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x19, 2);
            } else if (*(s32 *)(data + 0x294) == 1) {
                if (moby[0x43] != 0xA)
                    anim_start_blended(moby, 0xA, math_random_int_below(4), math_random_int_range(7, 0x14));
                moby_set_state(moby, 0x13, 2);
            } else {
                *(s32 *)(data + 0x290) = 1;
                if (moby[0x43] != 2)
                    anim_start_blended(moby, 2, 0, 0x28);
                moby_set_state(moby, 0x13, 3);
            }
        }
        break;
    case 2:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.003781547f, 0.29670602f);
        if ((u16)(*(s16 *)(data + 0x264) - 1) >= 2 && moby[0x20] != 0x19 && math_random_int_below(4) == 1) {
            *(f32 *)(moby + 0x48) = 1.0f;
            if (moby[0x43] != 2)
                anim_start_blended(moby, 2, 0, 0xA);
            moby_set_state(moby, 0xE, 1);
            *(s32 *)(data + 0x560) = 0;
            *(s16 *)(data + 0x260) = math_random_int_range(0x244, 0x258);
        }
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x31 && *(s32 *)(data + 0x558) != -1) {
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, math_random_int_range(5, 0xF));
            moby_set_state(moby, 7, 8);
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
        }
        break;
    case 8:
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x31) {
            if (*(s32 *)(data + 0x548) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x19, 2);
            } else {
                if (moby[0x43] != 0xA)
                    anim_start_blended(moby, 0xA, 0, 0xA);
                moby_set_state(moby, 0x13, 2);
            }
        }
        break;
    case 4:
        if (*(f32 *)(data + 0x20) > 0.0f)
            moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        r1_4 = moby_dispatch_action_by_kind(moby, data + 0x60);
        if (r1_4 & 1) {
            moby_mark_spawned(*(u8 **)(data + 0x278));
            g_active_rider_count[0] = g_active_rider_count[0] - 1;
            SetDeathBits_us2(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, 0);
            return;
        }
        if (r1_4 & 2) {
            *(s16 *)(data + 0x26) = 0;
            if ((u16)(*(s16 *)(data + 0x264) - 1) < 2) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x17, 2);
                if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 6.5f &&
                    FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                     ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.6108653f) {
                    if (moby[0x43] != 5)
                        anim_start_blended(moby, 5, 1, 4);
                    moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
                    moby_set_state(moby, 0x1D, 2);
                }
            } else if (*(s32 *)(data + 0x558) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, math_random_int_range(5, 0xF));
                moby_set_state(moby, 7, 0);
                moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
            } else {
                if (moby[0x43] != 0)
                    anim_start_blended(moby, 0, 0, 0xA);
                moby_set_state(moby, 0xE, 1);
                *(s16 *)(data + 0x260) = math_random_int_range(0x244, 0x258);
            }
        }
        break;
    case 3:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(data + 0x294) == 1) {
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 0xA);
            moby_set_state(moby, 0x17, 2);
            if (*(s32 *)(data + 0x284) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x1A, 2);
            }
        }
        if ((u16)(*(s16 *)(data + 0x264) - 1) >= 2) {
            if (moby[0x43] != 0xB)
                anim_start_blended(moby, 0xB, 0, 0x1E);
            moby_set_state(moby, 0xE, 1);
            *(s16 *)(data + 0x260) = math_random_int_range(0x244, 0x258);
            *(s32 *)(data + 0x560) = 0;
        }
        break;
    case 5:
        if (*(u8 **)(data + 0x278) != 0)
            moby_copy_joint_transform_to_object(moby, *(u8 **)(data + 0x278), 1, 0);
        p1_5 = *(u8 **)(data + 0x274);
        qcopy(moby + 0x10, p1_5 + 0x10);
        qcopy(moby + 0xF0, p1_5 + 0xF0);
        q1_5 = *(u8 **)(data + 0x280);
        qcopy(q1_5 + 0x10, moby + 0x10);
        qcopy(q1_5 + 0xF0, moby + 0xF0);
        qcopy(q1_5 + 0x10, moby + 0x10);
        *(f32 *)(q1_5 + 0x18) = *(f32 *)(q1_5 + 0x18) + 0.65f;
        if (*(s32 *)(data + 0x26C) == 0) {
            part_spawn_explosion_with_sparks(moby, *(u8 **)(data + 0x278) + 0x10, 0.5f, 3.0f, -1);
            moby_mark_spawned(*(u8 **)(data + 0x278));
            moby_mark_spawned(*(u8 **)(data + 0x280));
            *(s32 *)(*(u8 **)(*(u8 **)(data + 0x274) + 0x68) + 0x27C) = 0;
            moby_set_state(moby, 2, 6);
        } else if (tribesman_tick_linked_clock(moby) != 0) {
            part_spawn_explosion_with_sparks(moby, *(u8 **)(data + 0x278) + 0x10, 0.5f, 3.0f, -1);
            moby_mark_spawned(*(u8 **)(data + 0x278));
            moby_mark_spawned(*(u8 **)(data + 0x280));
            *(s32 *)(*(u8 **)(*(u8 **)(data + 0x274) + 0x68) + 0x27C) = 0;
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 0);
            moby_set_state(moby, 3, 6);
        }
        break;
    case 6:
        if (flag_set_second_pending(moby) != 0) {
            p1_6 = CreateMoby(0x9AC);
            *(u8 **)(data + 0x29C) = p1_6;
            if (p1_6 != 0) {
                p1_6[0x30] = moby[0x30];
                *(u16 *)(*(u8 **)(data + 0x29C) + 0x32) = *(u16 *)(moby + 0x32);
                (*(u8 **)(data + 0x29C))[0x31] = 1;
                *(s64 *)(*(u8 **)(data + 0x29C) + 0x38) = *(s64 *)(moby + 0x38);
                func_002A0F48(*(u8 **)(data + 0x29C));
                *(s32 *)(*(u8 **)(data + 0x29C) + 0x98) = 0;
                moby_copy_joint_transform_to_object(moby, *(u8 **)(data + 0x29C), 3, 0);
                *(s32 *)(data + 0x290) = 1;
                *(f32 *)(moby + 0xF0) = 0.0f;
                *(f32 *)(moby + 0xF4) = 0.0f;
                euler_rotation_basis(moby + 0xC0, moby + 0xF0);
            } else {
                moby_mark_spawned(moby);
                return;
            }
        }
        break;
    case 7:
        *(s32 *)(data + 0x290) = 0;
        p1_7 = g_moby_l11_table[0] + (*(s32 *)(data + 0x548) << 8);
        q1_7 = *(u8 **)(p1_7 + 0x68);
        if (moby[0x20] != 0x22) {
            moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
            a1_7 = mat_fast_helper_a(vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0xD0 / 4]),
                                 ((Hero *)g_hero_state)->f[0xD8 / 4] - *(f32 *)(moby + 0x18));
            build_axis_rotation_quaternion(q1_7 + 0x10, 1, -a1_7);
        }
        *(f32 *)(moby + 0x10) = *(f32 *)(p1_7 + 0x10);
        *(f32 *)(moby + 0x14) = *(f32 *)(p1_7 + 0x14);
        *(f32 *)(moby + 0x18) = *(f32 *)(p1_7 + 0x18) + 1.5f;
        euler_rotation_basis(p1_7 + 0xC0, moby + 0xF0);
        if ((u16)(*(s16 *)(data + 0x264) - 1) >= 2 && moby[0x20] != 0x20) {
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 0xA);
            anim_start_blended(p1_7, 0, 0, 0xA);
            moby_set_state(moby, 0x22, -1);
        }
        if (moby[0x20] == 0x22 && *(s16 *)(data + 0x264) == 2) {
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 0xA);
            moby_set_state(moby, 0x21, -1);
            anim_start_blended(p1_7, 1, 0, 0xA);
        }
        break;
    }

    switch (moby[0x20]) {
    case 1:
        break;
    case 2:
        if (moby[0x60] & 2) {
            *(u16 *)(moby + 0x34) |= 0x5000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            moby_set_state(moby, 0xE, 1);
            if (*(s16 *)(data + 0x260) < 0x12C)
                *(s16 *)(data + 0x260) = math_random_int_range(0x1E0, 0x258);
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 0xA);
        }
        f2_2 = moby_get_anim_value(moby);
        if (f2_2 >= 10.0f)
            *(f32 *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        if (f2_2 >= 1.5f && f2_2 <= 17.0f) {
            vec_a[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            vec_a[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            vec_a[2] = 0.0f;
            FastVecAdd(moby + 0x10, moby + 0x10, vec_a);
            vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            vec_b[2] = 0.0f;
            FastVecAdd(moby + 0x10, moby + 0x10, vec_b);
        }
        break;
    case 3:
        if (moby[0x60] & 2) {
            *(u16 *)(moby + 0x34) |= 0x5000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            moby_set_state(moby, 0xE, 1);
            if (*(s16 *)(data + 0x260) < 0x12C)
                *(s16 *)(data + 0x260) = math_random_int_range(0x1E0, 0x258);
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 0xA);
        }
        f2_3 = moby_get_anim_value(moby);
        if (f2_3 >= 10.0f)
            *(f32 *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        if (f2_3 >= 1.5f && f2_3 <= 17.0f) {
            vec_a[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            vec_a[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            vec_a[2] = 0.0f;
            vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            vec_b[2] = 0.0f;
            qcopy(vec_c, moby + 0x10);
            FastVecAdd(vec_c, moby + 0x10, vec_b);
            FastVecAdd(vec_c, moby + 0x10, vec_a);
            moby_move_over_ground(moby, moby + 0x10, vec_c, 0.5f, 0.55f, 0.5f, 0.523598849773407f, 0);
        }
        break;
    case 5:
        if (*(u8 **)(data + 0x55C) != 0) {
            r2_5 = *(s32 *)(data + 0x540);
            if (r2_5 == 1 && moby[0x42] == 0xD) {
                n2_5 = math_random_int_below(0xC8);
                if (n2_5 == r2_5) {
                    if (moby[0x43] != 0xC)
                        anim_start_blended(moby, 0xC, 0, 0x1E);
                    if (math_random_int_below(3) == n2_5 && moby[0x43] != 0xB)
                        anim_start_blended(moby, 0xB, 0, 0x1E);
                }
            }
            if ((u8)(moby[0x42] - 0xB) < 2 && (moby[0x60] & 2)) {
                if (moby[0x43] != 0xE)
                    anim_start_blended(moby, 0xE, 0, 0x1E);
                p2_5 = *(u8 **)(data + 0x55C);
                if (*(s16 *)(p2_5 + 0xAA) == 0xCF6) {
                    *(s32 *)(*(u8 **)(p2_5 + 0x68) + 0x540) = 1;
                    *(s32 *)(data + 0x540) = 2;
                }
            }
            if (moby[0x42] == 0xE && (moby[0x60] & 2)) {
                if (moby[0x43] != 0xF)
                    anim_start_blended(moby, 0xF, 0, 0x1E);
                if (*(s32 *)(data + 0x540) == 1 && moby[0x43] != 0xD)
                    anim_start_blended(moby, 0xD, 0, 0x1E);
            }
            if (*(s32 *)(data + 0x540) == 1 && moby[0x42] == 0xF && moby[0x43] != 0xE)
                anim_start_blended(moby, 0xE, 0, 0x14);
            if (*(s32 *)(data + 0x540) == 3) {
                c2_5 = (*(u8 **)(data + 0x55C))[0x42];
                if (c2_5 == 0xE && moby[0x43] != c2_5)
                    anim_start_blended(moby, 0xE, 0, 0x23);
            }
        }
        break;
    case 6:
        *(s32 *)(data + 0x290) = 1;
        if (moby[0x60] & 2) {
            moby_set_state(moby, 7, -1);
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 0x1E);
            *(s32 *)(data + 0x290) = 0;
        }
        break;
    case 7:
        if (path_follow_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x558)]) != 0) {
            moby_set_state(moby, 8, -1);
            if (moby[0x43] != 9)
                anim_start_blended(moby, 9, 0, 0x14);
        }
        break;
    case 8:
        if (moby[0x60] & 2) {
            moby_set_controller_speed_limits(moby, 0.0015277779f, 0.045833334f, 0.001163553f, 0.10471977f);
            if (moby_count_group_not_in_state(moby[0x21], -1) >= 2) {
                *(u8 **)(data + 0x55C) = moby_find_linked_object(moby);
                moby_set_state(moby, 0xA, -1);
                if (moby[0x43] != 0xD)
                    anim_start_blended(moby, 0xD, 0, 0x1E);
                *(s32 *)(data + 0x540) = 1;
                if ((*(u8 **)(data + 0x55C))[0x42] == 0xD) {
                    if (moby[0x43] != 0xF)
                        anim_start_blended(moby, 0xF, 0, 0x1E);
                    *(s32 *)(data + 0x540) = 2;
                }
            }
        }
        break;
    case 10:
        moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(*(f32 *)(*(u8 **)(data + 0x55C) + 0x10) - *(f32 *)(moby + 0x10),
                                                       *(f32 *)(*(u8 **)(data + 0x55C) + 0x14) - *(f32 *)(moby + 0x14)));
        if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(*(f32 *)(*(u8 **)(data + 0x55C) + 0x10) - *(f32 *)(moby + 0x10),
                                                              *(f32 *)(*(u8 **)(data + 0x55C) + 0x14) - *(f32 *)(moby + 0x14))) < 0.087266475f)
            moby_set_state(moby, 5, -1);
        break;
    case 11:
        moby_set_controller_speed_limits(moby, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
        if (path_follow_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x54C)]) != 0) {
            moby_set_state(moby, 0xC, -1);
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 0x14);
        }
        break;
    case 12:
        if (moby[0x60] & 2) {
            path2_12 = g_path_l11_table[*(s32 *)(data + 0x54C)];
            d2_12 = vec_distance_xy(moby + 0x10, path2_12 + 4);
            if (vec_distance_xy(moby + 0x10, (u8 *)path2_12 + *path2_12 * 0x10) < d2_12)
                path_set_follower_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x54C)], 0, *path2_12 - 1);
            else
                path_set_follower_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x54C)], *path2_12 - 1, 0);
            moby_set_state(moby, 0xB, -1);
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 0x14);
        }
        break;
    case 14:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 0x14);
            moby_set_state(moby, 0xF, -1);
            if (*(s32 *)(data + 0x56C) != -1)
                moby_set_state(moby, 0x11, -1);
        }
        break;
    case 15:
        moby_l01_turn_toward_target(moby, data + 0x110);
        if (vec_distance_xy(moby + 0x10, data + 0x110) < 2.0f) {
            moby_set_state(moby, 0x10, -1);
            if (moby[0x43] != 9)
                anim_start_blended(moby, 9, 0, 0x14);
        }
        break;
    case 17:
        moby_set_controller_speed_limits(moby, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
        if (path_follow_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x56C)]) != 0) {
            moby_set_state(moby, 0x12, -1);
            if (moby[0x43] != 9)
                anim_start_blended(moby, 9, 0, 0x14);
        }
        break;
    case 18:
        if (moby[0x60] & 2) {
            path2_18 = g_path_l11_table[*(s32 *)(data + 0x56C)];
            d2_18 = vec_distance_xy(moby + 0x10, path2_18 + 4);
            if (vec_distance_xy(moby + 0x10, (u8 *)path2_18 + *path2_18 * 0x10) < d2_18)
                path_set_follower_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x56C)], 0, *path2_18 - 1);
            else
                path_set_follower_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x56C)], *path2_18 - 1, 0);
            moby_set_state(moby, 0x11, -1);
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 0x14);
        }
        break;
    case 23:
        if (*(s32 *)(data + 0x57C) != -1) {
            moby_set_state(moby, 0x18, -1);
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f &&
                   FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                    ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.3490659f) {
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 6);
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            moby_set_state(moby, 0x1C, 2);
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
            moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        } else if (*(s32 *)(data + 0x528) != 0) {
            if (saur_beast_walk_to_target(moby, &((Hero *)g_hero_state)->f[0x80 / 4], *(f32 *)(moby + 0xF8), 7.0f, 0.25f, *(f32 *)(data + 0x298)) != 0) {
                c2_23 = moby[0x21];
                if (g_tribe_group_limit >= c2_23 && moby_count_group_not_in_state(c2_23, -1) >= 2) {
                    base2_23 = g_moby_l11_table[0];
                    list2_23 = g_group_id_lists[moby[0x21]];
                    do {
                        o2_23 = base2_23 + ((*list2_23 & 0x7FFF) << 8);
                        q2_23 = *(u8 **)(o2_23 + 0x68);
                        if (*(s32 *)(q2_23 + 0x294) == 0) {
                            d2_23 = vec_distance_xy(o2_23 + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]);
                            if (d2_23 < vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) && *(f32 *)(q2_23 + 0x20) > 0.0f) {
                                *(s32 *)(q2_23 + 0x294) = 1;
                                *(s32 *)(data + 0x294) = 0;
                                if (moby[0x43] != 2)
                                    anim_start_blended(moby, 2, 0, 0xA);
                                moby_set_state(moby, 0x13, 3);
                            }
                            break;
                        }
                    } while (*(s16 *)list2_23++ >= 0);
                }
            }
        } else {
            moby_turn_toward_target_and_step(moby, &((Hero *)g_hero_state)->f[0x80 / 4], *(f32 *)(data + 0x298));
        }
        break;
    case 24:
        *(s32 *)(data + 0x290) = 0;
        moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.27925274f);
        *(TI128 *)vec_a = *(TI128 *)&g_arena_camera_table[0][(*(s32 *)(data + 0x57C) << 7) + 0x30];
        moby_l01_turn_toward_target(moby, vec_a);
        if (vec_distance_xy(moby + 0x10, vec_a) < 1.5f) {
            if (moby[0x43] != 0x12)
                anim_start_blended(moby, 0x12, 0, 0x10);
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            moby_set_state(moby, 0x1B, 2);
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 6);
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            moby_set_state(moby, 0x1D, 2);
        }
        break;
    case 25:
        p2_25 = g_moby_l11_table[0] + (*(s32 *)(data + 0x548) << 8);
        q2_25 = *(u8 **)(p2_25 + 0x68);
        if (p2_25[0x20] != 5) {
            vec_spring_to_target(p2_25 + 0xF0, moby + 0xF0, data + 0x550, 0.001163553f, 0.0023271059f, 0.10471977f);
            euler_rotation_basis(p2_25 + 0xC0, p2_25 + 0xF0);
            *(f32 *)(p2_25 + 0x18) = *(f32 *)(p2_25 + 0x18) + ((*(f32 *)(q2_25 + 0x5C) - 1.2f) - *(f32 *)(p2_25 + 0x18)) * 0.11f;
        }
        moby_l01_turn_toward_target(moby, p2_25 + 0x10);
        if (vec_distance_xy(moby + 0x10, p2_25 + 0x10) < 1.5f && p2_25[0x20] != 5) {
            p2_25[0x20] = 6;
            *(f32 *)(moby + 0x10) = *(f32 *)(p2_25 + 0x10);
            *(f32 *)(moby + 0x14) = *(f32 *)(p2_25 + 0x14);
            *(f32 *)(moby + 0x18) = *(f32 *)(p2_25 + 0x18) + 1.5f;
            *(f32 *)(data + 0x554) = *(f32 *)(p2_25 + 0x18) + 0.75f;
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 0x19);
            moby_set_state(moby, 0x20, 7);
            moby[0xBC] = 1;
        }
        break;
    case 32:
        p2_32 = g_moby_l11_table[0] + (*(s32 *)(data + 0x548) << 8);
        math_spring_float_to_goal(p2_32 + 0x18, data + 0x550, *(f32 *)(data + 0x554), 0.00027777778f, 0.0016666667f, 0.033333335f);
        *(f32 *)(moby + 0x18) = *(f32 *)(p2_32 + 0x18) + 1.5f;
        if (math_fabs(*(f32 *)(p2_32 + 0x18) - *(f32 *)(data + 0x554)) < 0.1f) {
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 5);
            moby_set_state(moby, 0x21, -1);
            if (p2_32[0x43] != 1)
                anim_start_blended(p2_32, 1, 0, 5);
        }
        if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                              ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.26179942f &&
            p2_32[0x43] != 1) {
            anim_start_blended(p2_32, 1, 0, 5);
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 5);
        } else if (p2_32[0x42] == 1) {
            if (math_is_value_within_step_us2(p2_32, 6.0f) != 0 || math_is_value_within_step_us2(p2_32, 12.0f) != 0 || math_is_value_within_step_us2(p2_32, 0.0f) != 0) {
                moby_transform_joint_to_world((u32)p2_32, 1, vec_a);
                FastVecSub(vec_b, &((Hero *)g_hero_state)->f[0xD0 / 4], vec_a);
                vec_scale_to_length(vec_b, vec_b, 0.5f);
                SpawnStateVectorMoby(p2_32, vec_b, vec_a, 1.0f);
            } else if (math_is_value_within_step_us2(p2_32, 3.0f) != 0 || math_is_value_within_step_us2(p2_32, 9.0f) != 0 || math_is_value_within_step_us2(p2_32, 15.0f) != 0) {
                moby_transform_joint_to_world((u32)p2_32, 0, vec_a);
                FastVecSub(vec_b, &((Hero *)g_hero_state)->f[0xD0 / 4], vec_a);
                vec_scale_to_length(vec_b, vec_b, 0.5f);
                SpawnStateVectorMoby(p2_32, vec_b, vec_a, 1.0f);
            }
        }
        break;
    case 33:
        p2_33 = g_moby_l11_table[0] + (*(s32 *)(data + 0x548) << 8);
        if (math_is_value_within_step_us2(p2_33, 6.0f) != 0 || math_is_value_within_step_us2(p2_33, 12.0f) != 0 || math_is_value_within_step_us2(p2_33, 0.0f) != 0) {
            moby_transform_joint_to_world((u32)p2_33, 1, vec_a);
            FastVecSub(vec_b, &((Hero *)g_hero_state)->f[0xD0 / 4], vec_a);
            vec_scale_to_length(vec_b, vec_b, 0.5f);
            SpawnStateVectorMoby(p2_33, vec_b, vec_a, 1.0f);
        } else if (math_is_value_within_step_us2(p2_33, 3.0f) != 0 || math_is_value_within_step_us2(p2_33, 9.0f) != 0 || math_is_value_within_step_us2(p2_33, 15.0f) != 0) {
            moby_transform_joint_to_world((u32)p2_33, 0, vec_a);
            FastVecSub(vec_b, &((Hero *)g_hero_state)->f[0xD0 / 4], vec_a);
            vec_scale_to_length(vec_b, vec_b, 0.5f);
            SpawnStateVectorMoby(p2_33, vec_b, vec_a, 1.0f);
        }
        break;
    case 34:
        if (*(s32 *)(data + 0x564) != -1) {
            path2_34 = (s32 *)((u8 *)g_path_l11_table[*(s32 *)(data + 0x564)] + *(s32 *)(data + 0x568) * 0x10);
            p2_34 = g_moby_l11_table[0] + (*(s32 *)(data + 0x548) << 8);
            moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(*(f32 *)((u8 *)path2_34 + 0x10) - *(f32 *)(moby + 0x10),
                                                           *(f32 *)((u8 *)path2_34 + 0x14) - *(f32 *)(moby + 0x14)));
            *(f32 *)(moby + 0x10) = *(f32 *)(p2_34 + 0x10);
            *(f32 *)(moby + 0x14) = *(f32 *)(p2_34 + 0x14);
            *(f32 *)(moby + 0x18) = *(f32 *)(p2_34 + 0x18) + 1.5f;
            euler_rotation_basis(p2_34 + 0xC0, moby + 0xF0);
            pathb2_34 = (s32 *)((u8 *)g_path_l11_table[*(s32 *)(data + 0x564)] + *(s32 *)(data + 0x568) * 0x10);
            if (mat_fast_helper_a(*(f32 *)((u8 *)pathb2_34 + 0x10) - *(f32 *)(moby + 0x10),
                              *(f32 *)((u8 *)pathb2_34 + 0x14) - *(f32 *)(moby + 0x14)) <= 0.6108653f) {
                if (++*(s32 *)(data + 0x568) >= 2)
                    *(s32 *)(data + 0x568) = 0;
            }
        }
        break;
    case 19:
        *(s32 *)(data + 0x290) = 0;
        moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        if (*(s32 *)(data + 0x294) == 0) {
            *(s32 *)(data + 0x290) = 1;
            if (moby[0x43] != 0x11)
                anim_start_blended(moby, 0x11, 0, 0xA);
            moby_set_state(moby, 0x14, -1);
        } else {
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 0xA);
            moby_set_state(moby, 0x17, 2);
            if (*(s32 *)(data + 0x284) != -1) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x1A, 2);
            }
        }
        break;
    case 20:
        moby_turn_toward_position(moby, ((Hero *)g_hero_state)->ptr[0x2290 / 4], data + 0x27C, 0.001f, 0.01f, 0.1f);
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 0xA);
            moby_set_state(moby, 0x1C, -1);
        }
        n2_20 = math_random_int_below(3);
        if (n2_20 == 1 && (moby[0x60] & 2)) {
            if (moby[0x43] != 0xA)
                anim_start_blended(moby, 0xA, 0, 0xA);
            if (math_random_int_below(3) == n2_20 && moby[0x43] != 9)
                anim_start_blended(moby, 9, 0, 0xA);
            moby_set_state(moby, 0x13, 3);
        }
        break;
    case 21:
        if (*(s32 *)(data + 0x528) != 0) {
            if (saur_beast_walk_to_target(moby, &((Hero *)g_hero_state)->f[0x80 / 4], *(f32 *)(moby + 0xF8), 7.0f, 0.25f, *(f32 *)(data + 0x298)) != 0) {
                if (moby[0x43] != 0x11)
                    anim_start_blended(moby, 0x11, 0, 0xA);
                moby_set_state(moby, 0x14, -1);
            }
        } else {
            moby_turn_toward_target_and_step(moby, &((Hero *)g_hero_state)->f[0x80 / 4], *(f32 *)(data + 0x298));
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 8.0f) {
            if (moby[0x43] != 0x11)
                anim_start_blended(moby, 0x11, 0, 0xA);
            moby_set_state(moby, 0x14, -1);
        }
        break;
    case 22:
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f &&
            FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                             ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.3490659f) {
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 6);
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            moby_set_state(moby, 0x1C, 2);
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
            moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) > 6.0f) {
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 0xA);
            moby_set_state(moby, 0x17, -1);
        } else {
            moby_set_controller_speed_limits(moby, 0.00055555557f, 0.016666668f, 0.001163553f, 0.10471977f);
            moby_turn_toward_target_and_step(moby, &((Hero *)g_hero_state)->f[0x80 / 4], *(f32 *)(data + 0x298));
        }
        break;
    case 26:
        *(f32 *)(data + 0x174) = 1.5f;
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 2);
            moby_set_state(moby, 0x1C, -1);
            *(s32 *)(data + 0x284) = -1;
            *(f32 *)(data + 0x164) = 0.00083333335f;
        } else {
            *(f32 *)(data + 0x164) = 0.004166667f;
            if (path_follow_nodes(moby, g_path_l11_table[*(s32 *)(data + 0x284)]) != 0) {
                if (*(s32 *)(data + 0x294) == 1) {
                    if (moby[0x43] != 3)
                        anim_start_blended(moby, 3, 0, 0xA);
                    moby_set_state(moby, 0x17, 2);
                } else {
                    *(s32 *)(data + 0x290) = 1;
                    if (math_random_int_below(3) == 1) {
                        if (moby[0x43] != 2)
                            anim_start_blended(moby, 2, 0, 0xA);
                        moby_set_state(moby, 0x13, 3);
                    } else {
                        if (moby[0x43] != 3)
                            anim_start_blended(moby, 3, 0, 0xA);
                        moby_set_state(moby, 0x15, 3);
                    }
                }
                *(s32 *)(data + 0x284) = -1;
            }
        }
        break;
    case 27:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x13)
                anim_start_blended(moby, 0x13, 0, 6);
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            moby_set_state(moby, 0x1C, 2);
        }
        moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        if (moby[0x42] == 0x12) {
            a2_27 = moby_get_anim_value(moby);
            moby_transform_joint_to_world(*(u32 *)(data + 0x278), 0, vec_a);
            vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
            vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
            vec_b[2] = 0.0f;
            FastVecAdd(vec_a, vec_a, vec_b);
            vec_a[2] = vec_a[2] - 0.05f;
            f2_27 = math_random_float_range(0.2f, 0.9f) * (a2_27 / g_tribe_fighter_spark_frame_scale);
            n2_27 = math_random_int_below(2);
            if (n2_27 == 0) n2_27 = n2_27 - 1;
            part_spawn_ground_effect(vec_a, 2, g_tribe_fighter_spark_color_a, 0, n2_27, g_identity_l11_matrix, f2_27 * 0.3f, f2_27, 0.0f, 0);
            part_spawn_ground_effect(vec_a, 2, g_tribe_fighter_spark_color_b, 1, -n2_27, g_identity_l11_matrix, f2_27 * 0.04f, f2_27 * 0.4f, 0.0f, 0);
            *(f32 *)(data + 0x574) = *(f32 *)(data + 0x574) + 1.0f;
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 6);
            moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            moby_set_state(moby, 0x1D, 2);
        }
        break;
    case 28:
        moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        *(s32 *)(data + 0x290) = 0;
        if (math_is_value_within_step_us2(moby, 1.0f) != 0 || math_is_value_within_step_us2(moby, 7.0f) != 0 || math_is_value_within_step_us2(moby, 14.0f) != 0) {
            if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                  ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.78539824f) {
                moby_transform_joint_to_world(*(u32 *)(data + 0x278), 0, vec_a);
                vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[2] = 0.0f;
                FastVecAdd(vec_a, vec_a, vec_b);
                vec_a[2] = vec_a[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)vec_a;
                FastVecSub(data + 0x5A0, &((Hero *)g_hero_state)->f[0xD0 / 4], vec_a);
                *(s32 *)(data + 0x578) = 0;
                moby_set_flag_bit(moby, 0);
                *(TI128 *)vec_c = *(TI128 *)(data + 0x580);
                *(TI128 *)vec_d = *(TI128 *)(data + 0x5A0);
                SpawnStateVectorMoby(moby, vec_c, vec_d, *(f32 *)(data + 0x28C));
                FastVecSub(vec_c, &((Hero *)g_hero_state)->f[0xD0 / 4], vec_a);
                vec_scale_to_length(vec_c, vec_c, 0.8333334f);
            } else {
                moby_transform_joint_to_world(*(u32 *)(data + 0x278), 0, vec_a);
                vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[2] = 0.0f;
                FastVecAdd(vec_a, vec_a, vec_b);
                vec_a[2] = vec_a[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)vec_a;
                vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 25.0f;
                vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 25.0f;
                vec_b[2] = 0.0f;
                FastVecAdd(vec_b, vec_b, moby + 0x10);
                FastVecSub(data + 0x5A0, vec_b, vec_a);
                *(s32 *)(data + 0x578) = 0;
                moby_set_flag_bit(moby, 0);
                *(TI128 *)vec_c = *(TI128 *)(data + 0x580);
                *(TI128 *)vec_d = *(TI128 *)(data + 0x5A0);
                SpawnStateVectorMoby(moby, vec_c, vec_d, *(f32 *)(data + 0x28C));
            }
        }
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x14)
                anim_start_blended(moby, 0x14, 0, 0x14);
            if (*(s32 *)(data + 0x5B4) != 0 && moby[0x43] != 0xA)
                anim_start_blended(moby, 0xA, 0, 0x14);
            moby_set_state(moby, 0x1E, -1);
            if (moby[0x95] != 2) {
                moby_set_state(moby, 0x14, -1);
                if (moby[0x43] != 0x11)
                    anim_start_blended(moby, 0x11, 0, 0xA);
            }
            *(f32 *)(data + 0x574) = 0.0f;
        }
        break;
    case 29:
        moby_step_controller(moby, moby + 0x10, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        *(s32 *)(data + 0x290) = 0;
        if (moby[0x42] == 5 && moby_get_anim_value(moby) < 11.0f) {
            a2_29 = moby_get_anim_value(moby);
            moby_transform_joint_to_world(*(u32 *)(data + 0x278), 0, vec_a);
            vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
            vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
            vec_b[2] = 0.0f;
            FastVecAdd(vec_a, vec_a, vec_b);
            vec_a[2] = vec_a[2] - 0.05f;
            f2_29 = math_random_float_range(0.2f, 0.9f) * (a2_29 / g_tribe_fighter_spark_frame_scale);
            n2_29 = math_random_int_below(2);
            if (n2_29 == 0) n2_29 = n2_29 - 1;
            part_spawn_ground_effect(vec_a, 2, g_tribe_fighter_spark_color_a, 0, n2_29, g_identity_l11_matrix, f2_29 * 0.3f, f2_29, 0.0f, 0);
            part_spawn_ground_effect(vec_a, 2, g_tribe_fighter_spark_color_b, 1, -n2_29, g_identity_l11_matrix, f2_29 * 0.04f, f2_29 * 0.4f, 0.0f, 0);
            *(f32 *)(data + 0x574) = *(f32 *)(data + 0x574) + 1.0f;
        }
        if (math_is_value_within_step_us2(moby, 11.0f) != 0) {
            if (FastDiffRots(*(f32 *)(moby + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                  ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.78539824f) {
                moby_transform_joint_to_world(*(u32 *)(data + 0x278), 0, vec_a);
                vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[2] = 0.0f;
                FastVecAdd(vec_a, vec_a, vec_b);
                vec_a[2] = vec_a[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)vec_a;
                FastVecSub(data + 0x5A0, &((Hero *)g_hero_state)->f[0xD0 / 4], vec_a);
                *(s32 *)(data + 0x578) = 0;
                moby_set_flag_bit(moby, 0);
                *(TI128 *)vec_c = *(TI128 *)(data + 0x580);
                *(TI128 *)vec_d = *(TI128 *)(data + 0x5A0);
                SpawnStateVectorMoby(moby, vec_c, vec_d, *(f32 *)(data + 0x28C));
            } else {
                moby_transform_joint_to_world(*(u32 *)(data + 0x278), 0, vec_a);
                vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 0.1f;
                vec_b[2] = 0.0f;
                FastVecAdd(vec_a, vec_a, vec_b);
                vec_a[2] = vec_a[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)vec_a;
                vec_b[0] = math_fast_sin_or_cos_a(*(f32 *)(moby + 0xF8)) * 25.0f;
                vec_b[1] = math_fast_sin_or_cos_b(*(f32 *)(moby + 0xF8)) * 25.0f;
                vec_b[2] = 0.0f;
                FastVecAdd(vec_b, vec_b, moby + 0x10);
                FastVecSub(data + 0x5A0, vec_b, vec_a);
                *(s32 *)(data + 0x578) = 0;
                moby_set_flag_bit(moby, 0);
                *(TI128 *)vec_c = *(TI128 *)(data + 0x580);
                *(TI128 *)vec_d = *(TI128 *)(data + 0x5A0);
                SpawnStateVectorMoby(moby, vec_c, vec_d, *(f32 *)(data + 0x28C));
            }
        }
        g2_29 = moby_get_anim_value(moby);
        if (moby[0x42] == 5 && g2_29 >= 10.0f && g2_29 <= 15.0f) {
            moby_transform_joint_to_world(*(u32 *)(data + 0x278), 0, vec_a);
            coll_sweep_from_object(moby, vec_a, 1, 0.4f, *(f32 *)(data + 0x28C), 1.0f, 0, 1, 0);
        }
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x11)
                anim_start_blended(moby, 0x11, 0, 0x14);
            math_random_int_below(3);
            moby_set_state(moby, 0x1E, -1);
            if (moby[0x95] != 2) {
                moby_set_state(moby, 0x14, -1);
                if (moby[0x43] != 0x11)
                    anim_start_blended(moby, 0x11, 0, 0xA);
            }
            *(f32 *)(data + 0x574) = 0.0f;
        }
        break;
    case 30:
        if (moby[0x60] & 2) {
            *(s32 *)(data + 0x5B0) = 0;
            if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x17, -1);
            } else {
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 0xA);
                moby_set_state(moby, 0x17, -1);
            }
            *(TI128 *)vec_a = *(TI128 *)&g_arena_camera_table[0][(*(s32 *)(data + 0x57C) << 7) + 0x30];
            moby_l01_turn_toward_target(moby, vec_a);
            if (vec_distance_xy(moby + 0x10, vec_a) < 1.5f) {
                if (*(s32 *)(data + 0x5B4) != 0) {
                    if (moby[0x43] != 0x12)
                        anim_start_blended(moby, 0x12, 0, 0x14);
                } else if (moby[0x43] != 0x12) {
                    anim_start_blended(moby, 0x12, 0, 6);
                }
                moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
                moby_set_state(moby, 0x1B, 2);
            }
            if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x80 / 4]) < 3.5f) {
                if (moby[0x43] != 5)
                    anim_start_blended(moby, 5, 0, 6);
                moby_set_controller_speed_limits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
                moby_set_state(moby, 0x1D, 2);
            }
        }
        break;
    }
    saur_beast_prepare_two_stage_anim(moby);
    if (math_fabs(*(f32 *)(moby + 0x18) - z0) < 0.005f)
        *(f32 *)(moby + 0x18) = z0;
}
