#include "names.h"
/* func_PAL_L22_003A0A08, the PAL copy of func_L22_0039D708: the same C, with the PAL
 * callees, the 50 Hz step (D_L22_001AF398 and D_L22_001AF354 as (x * 5 + 2) / 6), and
 * PAL constants at every cross-jumped call site: func_PAL_L22_003A7930's argument 4 -> 3
 * (six sites), 0x14 -> 0x11 (five) and func_002A77E0(7) + 0x1B -> + 0x16 (two).
 * It needs its own unit for the template's flags: -G8 (sda reads), -frac2-qcopy with
 * -frac2-qcopy-barrier, -frac2-keep-block-order, -frac2-gcse-unsplit-edges,
 * -frac2-sticky-volatile-refs (case 3's a0 in the bc1f slot) and
 * -frac2-hazard-labels (two branches target the nop before a bc1f).
 * The 0x43 copy uses qcopy: retail fills the beqz slot with the addiu of sp+32, ahead
 * of the reload, as sched2 orders it around a volatile asm. The template's one-pass group
 * gives that order in USA, but here its loop note would align the join at 0x3A47F4 with
 * a nop retail does not have.
 */
#include "common.h"
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; unsigned char b[16]; unsigned short h[8]; } ScratchD708;
typedef struct { ScratchD708 rows[4]; } MatrixD708;
typedef struct { s32 count; s32 pad[3]; ScratchD708 points[1]; } PathD708;
typedef struct { s8 pad[0x2A0]; s32 paths[44]; } OwnerD708;
typedef struct {
    ScratchD708 direction;
    s32 owner, flags;
    u8 first, second;
    u16 objectId;
    float amount;
    s32 enabled;
    u32 opaque;
} QueryD708;
typedef union {
    MatrixD708 matrix;
    struct { QueryD708 query; ScratchD708 direction; } query_view;
} FirstD708;
#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))
#define NULL ((void *)0)

extern void STUB_printf(void *, ...);
extern void * cam_moby_create_pal(void *, int, int, int, void *, void *, void *, int, float, float);
extern void FadeToBlack(int);
extern int math_fast_float_d(void *);
extern int FastDecTimer(int);
extern float math_fabs(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern void euler_rotation_basis(void *, void *);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastDiffRots(float, float);
extern void level_store_value_pair_pal(int, int);
extern void level_set_dependent_value(void);
extern void * CreateMoby(int);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(void *);
extern void moby_transform_joint_to_world(int, int, int);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void SetDeathBits_pal(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern float MobySpringTurn(void *, void *, float, float, float, float);
extern float moby_turn_toward_position(void *, void *, void *, float, float, float);
extern int moby_move_over_ground(void *, void *, void *, float, float, float, float, int);
extern int moby_count_group_not_in_state(int, int);
extern float coll_probe_ground_height_below(void *, int, float);
extern void part_init_effect_record(void *, int, int, float);
extern void make_hit_descriptor(int, int, int, float, int);
extern int coll_sweep_from_object(int, int, int, float, float, float, int, int, int);
extern int coll_test_hit_at_bone(void *, int, float, float, int, float, int, int, int);
extern void QueueMobyImpact(void *, void *);
extern void * part_find_owned_effect_slot(void *, int, int);
extern float math_spring_float_to_goal(int, int, float, float, float, float);
extern float vec_spring_to_target(int, int, int, float, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void mat_get_euler_angles(void *, void *);
extern void part_spawn_explosion_with_sparks_pal(void *, void *, float, float, int);
extern int func_PAL_002AF6C0(void *, float);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void vec_build_spherical_offset(int, float, float, float);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern float gravity_get_center_distance(void *);
extern void value_set_entry_by_index_pal(int, int);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern int flag_set_second_pending(void *);
extern int flag_is_third_pending_set(void *);
extern int moby_turn_toward_target_and_step(void *, void *, float);
extern int moby_step_controller(void *, void *, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int path_follow_nodes(void *, int);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int CollLine(void *, void *, int, void *, void *);
extern int PlayMobySound(int, int, void *);
extern int snd_play_from_global_bank(int, int, void *);
extern int game_is_id_in_list(int);
extern void * SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern void cancel_hero_item_animation_pal(void);
extern int queue_copy_record_by_index(int);
extern void release_moby_animation_slot(void *, void *);
extern void moby_set_flag_bit(void *, int);
extern int snd_start_in_slot(int, int, int);
extern int moby_l01_turn_toward_target(void *, void *);
extern void part_queue_moby_for_glow(void *, int, void *);
extern float moby_measure_step_angle(void *, void *, void *);
extern int moby_check_target_point_from_offset(void *, void *);
extern void moby_aim_at_target_offset_pal(void *, void *);
extern u8 *moby_find_linked_object(void *);
extern void moby_store_position_private(void *, void *);
extern int moby_call_helper_with_blocks_pal(void *);
extern int joba_enemy_apply_source_damage(void *);
extern int tribesman_turn_toward_point(void *, void *, float, float, float, float);
extern void tribesman_rearm_guard_nodes(void *);
extern int func_PAL_L22_002C99C8(int, int);
extern void math_steer_along_direction(void *, void *, void *, void *, float, float, float);
extern void moby_update_timed(void *);
extern void arena_push_point_out(void *, float);
extern void table_decrement_timer(void);
extern void lane_store_nearest_point_as_current(void *, int);
extern void lane_find_nearest_point(void *, void *, void *, int);
extern void func_PAL_L22_003A7930(void *, int, int, int, int, float);
extern void space_ship_run_attached_part_effect(void *, int, int, int, int);
extern int list_has_key(int, int);
extern void lane_find_point_ahead_of_ship(void *);
extern int space_ship_is_aligned_with_target_pal(void *);
extern void keyed_object_place(void *, void *, int);
extern void player_slot_clear_object(int);
extern void * effect_create_attached(void *, void *);
extern void func_PAL_L22_003A4910(s8 *);
extern void WalkPathUpdate_pal(s8 *);
extern s32 WalkPathIsClear(s8 *, s8 *, s128 *);
extern void WalkPathPickNext(s8 *, s32, s32, f32);
extern void pickup_update_spawned(s8 *);
extern s32 pickup_find_nearest_needed(s8 *, s128 *);
extern void space_ship_align_parts_at_end(s8 *);
extern void space_ship_pick_next_lane_to_check(s8 *);
extern void func_PAL_L22_003A7FF0(s8 *);
extern void func_PAL_L22_003A8F68(s8 *, s32, s32);
extern void stat_restore_random(s8 *);
extern void func_PAL_L22_003A99D8(s32, s32, s32, f32);
extern s32 g_pad_held_flags __attribute__((nosda));
extern s8 g_space_ship_flag __attribute__((nosda));
extern unsigned char g_hero_state[];
extern s16 g_platform_mode __attribute__((nosda));
extern s32 g_ship_progress_count __attribute__((nosda));
extern s32 g_hero_moby __attribute__((nosda));
extern unsigned char g_item_enabled_flags[] MACRO_ADDR;
extern s32 g_hero_l22_mode_state MACRO_ADDR;
extern s32 g_trigger_event_flag MACRO_ADDR;
extern void * g_space_ship_target_moby __attribute__((sda));
extern s32 g_space_ship_init_flag __attribute__((sda));
extern s32 g_space_ship_difficulty __attribute__((sda));
extern f32 g_space_ship_scale __attribute__((sda));
extern s32 g_space_ship_fade_time __attribute__((sda));
extern s32 g_space_ship_sound_a __attribute__((sda));
extern s32 g_space_ship_sound_b __attribute__((sda));
extern s32 g_space_ship_timer __attribute__((sda));
extern f32 g_space_ship_float_param_a __attribute__((sda));
extern f32 g_space_ship_float_param_b __attribute__((sda));
extern s32 g_space_ship_pending_flag __attribute__((sda));
extern s32 g_space_ship_state_default __attribute__((sda));
extern f32 g_space_ship_reach __attribute__((sda));
extern f32 g_space_ship_trigger_distance __attribute__((sda));
extern s32 g_space_ship_value_max __attribute__((sda));
extern s32 g_space_ship_value_min __attribute__((sda));
extern s32 g_space_ship_blended_value __attribute__((sda));
extern f32 g_space_ship_scatter_param __attribute__((sda));
extern f32 g_space_ship_random_dir_a __attribute__((sda));
extern f32 g_space_ship_random_dir_b __attribute__((sda));
extern f32 g_space_ship_z_scale __attribute__((sda));
extern s32 g_space_ship_active_flag __attribute__((sda));
extern s32 g_space_ship_saved_word __attribute__((sda));
extern f32 g_orbit_param_e __attribute__((sda));
extern f32 g_orbit_param_f __attribute__((sda));
extern f32 g_space_ship_speed_limit_a __attribute__((sda));
extern f32 g_space_ship_speed_limit_b __attribute__((sda));
extern f32 g_space_ship_orbit_arg __attribute__((sda));
extern f32 g_space_ship_threshold __attribute__((sda));
extern f32 g_space_ship_anim_max __attribute__((sda));
extern f32 g_space_ship_anim_min __attribute__((sda));
extern f32 g_space_ship_move_length __attribute__((sda));
extern f32 g_space_ship_steer_param_a __attribute__((sda));
extern f32 g_space_ship_steer_param_b __attribute__((sda));
extern void * g_trigger_event_list_head MACRO_ADDR;
extern s16 g_space_ship_mode MACRO_ADDR;
extern f32 g_space_ship_param_x MACRO_ADDR;
extern f32 g_space_ship_param_y MACRO_ADDR;
extern f32 g_space_ship_param_z MACRO_ADDR;
extern f32 g_space_ship_param_w MACRO_ADDR;
extern f32 g_planet_radius MACRO_ADDR;
extern s32 g_space_ship_max_health MACRO_ADDR;
extern f32 g_space_ship_speed_param MACRO_ADDR;
extern s32 g_space_ship_boost_timer MACRO_ADDR;
extern void * g_space_ship_pickup_slots MACRO_ADDR;
extern unsigned char g_tether_origin[];
extern unsigned char g_space_ship_scratch_vectors[];
extern s128 g_spawn_point __attribute__((nosda));
extern s8 *g_ship_path_table[];
extern s32 g_ship_model_marker __attribute__((nosda));

/* The moby vars block (temp_s6): only the 0x448 member is named. */
typedef struct { u8 pad[0x448]; void *p448; } VarsD708;
void func_PAL_L22_003A0A08(s8 *arg0) {
    /* The two matrices and the collision record reuse these eight vectors.
     * Component stores must address their vectors, not unrelated scalar locals. */
    union {
        ScratchD708 vectors[8];
        struct { FirstD708 first; MatrixD708 second; } pair;
        struct { ScratchD708 rotation; MatrixD708 basis; } shifted;
        struct { MatrixD708 basis; ScratchD708 rotation; QueryD708 query; } collision;
    } workspace;
#define scratch workspace.vectors
    ScratchD708 spA0;
    ScratchD708 spB0;
    s32 spC0;
    f32 spC4;
    s32 spC8;
    s32 **temp_v0_11;
    s32 **temp_v0_12;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f20;
    f32 temp_f21;
    f32 var_f12;
    f32 var_f20;
    f32 var_f20_2;
    s128 *temp_s0_3;
    s128 *var_a0_2;
    s128 *var_a0_3;
    s128 *var_v0_3;
    s128 *var_v0_6;
    s128 *var_v1_2;
    s128 var_v0_10;
    u8 *base9;
    u8 *base10;
    f32 frame;
    void *hit;
    s32 mode3A6;
    f32 len8;
    s32 saved398;
    u8 *game;
    u8 *game10;
    s32 temp_a1_3;
    f32 temp_f_dist;
    s16 temp_v0_6;
    s16 temp_v1_6;
    s32 var_a2;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_5;
    s32 *temp_s0_6;
    s32 temp_a0_12;
    s32 temp_a0_14;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a0_9;
    s32 temp_a1;
    s32 temp_a1_4;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_5;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_11;
    s32 temp_v1_13;
    s32 temp_v1_8;
    s8 **paths;
    s32 var_a1;
    s32 var_a1_10;
    s32 var_a1_13;
    s32 var_a1_14;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_9;
    s32 var_condition_bit;
    s32 var_fp;
    s8 *near;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0_4;
    s32 var_v0_9;
    s8 *temp_s0;
    s8 *temp_s2;
    s8 *var_a0_4;
    s8 *var_s5;
    u16 temp_a0;
    u16 temp_a0_13;
    u16 temp_a1_2;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v1_14;
    u16 var_v0_7;
    u16 var_v0_8;
    u8 temp_a0_11;
    u8 temp_v0_4;
    s32 temp_v1_10;
    u8 temp_v1_2;
    s32 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_9;
    void *temp_a0_10;
    void *temp_a0_15;
    void *temp_a0_16;
    void *temp_a0_17;
    void *temp_a0_18;
    void *temp_a0_5;
    void *temp_a0_8;
    void *temp_a2;
    void *temp_s0_2;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s1;
    void *temp_s3;
    void *temp_s3_2;
    void *temp_s4;
    void *temp_s5;
    void *temp_s6;
    void *temp_v1;
    void *temp_v1_12;
    void *temp_v1_15;
    void *temp_v1_7;
    void *var_a0;
    void *var_v1;

    if (g_space_ship_init_flag == 0) {
        g_pad_held_flags = 0;
        if ((g_space_ship_target_moby == NULL) && (g_hero_l22_mode_state != 2) && (M2C_FIELD(arg0, u8 *, 0x20) == 0)) {
            for (var_a0 = g_trigger_event_list_head; var_a0 != NULL; var_a0 = M2C_FIELD(var_a0, void **, 0x28)) {
                if (M2C_FIELD(var_a0, s16 *, 0xAA) == 0xF6E) {
                    g_space_ship_target_moby = var_a0;
                    M2C_FIELD(var_a0, u8 *, 0x30) = 0xFF;
                    temp_v1 = M2C_FIELD(g_space_ship_target_moby, void **, 0x68);
                    M2C_FIELD(temp_v1, s8 *, 8) = 0;
                    M2C_FIELD(temp_v1, s8 *, 0xA) = 0;
                    M2C_FIELD(temp_v1, s8 *, 0xC) = -1;
                }
            }
            M2C_FIELD(M2C_FIELD(g_space_ship_target_moby, void **, 0x68), s8 *, 8) = 0;
            moby_set_flag_bit(g_space_ship_target_moby, 1);
            moby_set_state(arg0, 0x27, 0xB);
            FadeToBlack(0);
            M2C_FIELD(arg0, u16 *, 0x34) = (u16) (M2C_FIELD(arg0, u16 *, 0x34) | 0x41);
            return;
        }
        if (M2C_FIELD(arg0, u8 *, 0x20) == 0x27) {
            for (var_v1 = g_trigger_event_list_head; var_v1 != NULL; var_v1 = M2C_FIELD(var_v1, void **, 0x28)) {
                if (M2C_FIELD(var_v1, s16 *, 0xAA) == 0xF6E) {
                    return;
                }
            }
            g_space_ship_target_moby = NULL;
            g_space_ship_init_flag = 1;
            moby_set_state(arg0, 0, -1);
            M2C_FIELD(arg0, u16 *, 0x34) = (u16) (M2C_FIELD(arg0, u16 *, 0x34) & 0xFFBE);
            return;
        }
    }
    {
        temp_s6 = M2C_FIELD(arg0, void **, 0x68);
        math_fast_float_d(&g_space_ship_boost_timer);
        if (g_space_ship_boost_timer != 0) {
            M2C_FIELD(arg0, u8 *, 0xA8) = 0xFF;
        }
        temp_s3 = part_find_owned_effect_slot(arg0, 0x30000, 1);
        func_PAL_L22_003A4910(arg0);
        if (g_space_ship_timer >= 0xC9) {
            space_ship_align_parts_at_end(arg0);
        } else {
            if (g_space_ship_timer == 0) {
                g_space_ship_difficulty += 1;
            }
            if (M2C_FIELD(arg0, u8 *, 0x20) != 0) {
                {
                    f32 x = M2C_FIELD(temp_s6, f32 *, 0x330);
                    f32 y = M2C_FIELD(temp_s6, f32 *, 0x334);
                    f32 z = M2C_FIELD(temp_s6, f32 *, 0x338);
                    f32 w = M2C_FIELD(temp_s6, f32 *, 0x33C);
                    g_space_ship_param_x = x;
                    g_space_ship_param_y = y;
                    g_space_ship_param_z = z;
                    g_space_ship_param_w = w;
                }
                space_ship_pick_next_lane_to_check(arg0);
                if (g_space_ship_pending_flag != 0) {
                    vec_scale_to_length(&scratch[3].q, arg0 + 0xC0, -10.0f);
                    scratch[3].f[3] = 5627.925f;
                    make_hit_descriptor((s32) &workspace.pair.first.query_view.query, g_hero_moby, 0x10000, 20.0f, (s32) &scratch[3].q);
                    QueueMobyImpact(arg0, &workspace.pair.first.query_view.query);
                    g_space_ship_pending_flag = 0;
                }
            }
            temp_a1 = (s32) M2C_FIELD(temp_s6, f32 *, 0x20);
            g_space_ship_active_flag = 0;
            M2C_FIELD(temp_s6, s16 *, 0x41C) = (temp_a1 < ((s32) (g_space_ship_max_health * 2) / 3)) && (((s32) g_space_ship_max_health / 6) < temp_a1);
            if ((temp_s3 != NULL) && (M2C_FIELD(temp_s3, s32 *, 0x20) != g_hero_moby)) {
                M2C_FIELD(temp_s6, s32 *, 0x4EC) = 0;
            }
            if (((u32) (M2C_FIELD(arg0, u8 *, 0x95) - 4) < 2U) && (((u32) (M2C_FIELD(arg0, u8 *, 0x43) - 0xB) < 2U) == 0)) {
                temp_v0 = moby_check_target_point_from_offset(arg0, (s128 *) (g_hero_state + 0x80));
                M2C_FIELD(temp_s6, s32 *, 0x3D0) = temp_v0;
            } else {
                FastVecSub(&scratch[0].q, (s128 *) (g_hero_state + 0x80), arg0 + 0x10);
                temp_f1 = moby_measure_step_angle(arg0, &scratch[0].q, NULL);
                M2C_FIELD(temp_s6, s32 *, 0x3D4) = 0;
                M2C_FIELD(temp_s6, s32 *, 0x3D0) = 0;
                if (temp_f1 <= 0.7853982f) {
                    M2C_FIELD(temp_s6, s32 *, 0x3D0) = 1;
                }
                if (temp_f1 <= 1.0471976f) {
                    M2C_FIELD(temp_s6, s32 *, 0x3D4) = 1;
                }
            }
            if ((temp_s3 != NULL) && (M2C_FIELD(temp_s6, s32 *, 0x3D0) == 0)) {
                M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
            }
            var_a0_2 = (s128 *) (g_hero_state + 0x80);
            temp_s1 = temp_s6 + 0x3F0;
            M2C_FIELD(temp_s6, s128 *, 0x3F0) = (s128) M2C_FIELD(var_a0_2, s128 *, 0);
            temp_s0_2 = temp_s6 + 0x400;
            arena_push_point_out(temp_s1, 0.0f);
            M2C_FIELD(temp_s6, s128 *, 0x400) = *(s128 *)(arg0 + 0x10);
            arena_push_point_out(temp_s0_2, 0.0f);
            M2C_FIELD(temp_s6, f32 *, 0x410) = gravity_get_center_distance((arg0 + 0x10));
            M2C_FIELD(temp_s6, f32 *, 0x414) = gravity_get_center_distance(M2C_FIELD(var_a0_2, s32 *, 0x2210) + 0x10);
            M2C_FIELD(temp_s6, f32 *, 0x3DC) = fast_vec_dist(var_a0_2, (arg0 + 0x10));
            M2C_FIELD(temp_s6, f32 *, 0x3E0) = fast_vec_dist(temp_s1, temp_s0_2);
            if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 50.0f) {
                M2C_FIELD(temp_s6, s32 *, 0x3D8) = WalkPathIsClear(arg0, (arg0 + 0x10), var_a0_2);
            } else {
                M2C_FIELD(temp_s6, s32 *, 0x3D8) = 0;
            }
            if (M2C_FIELD(temp_s6, s32 *, 0x344) != 0) {
                game = g_hero_state;
                M2C_FIELD(game, s16 *, 0x1DC) = 0x7D00;
                moby_set_state(arg0, 0x26, 0xA);
                M2C_FIELD(game, s32 *, 0x2294) = 0;
                cancel_hero_item_animation_pal();
                release_moby_animation_slot(M2C_FIELD(game, void **, 0x2290), game + 0x1870);
                M2C_FIELD(game, s32 *, 0x187C) = 0;
                func_PAL_L22_002C99C8(0, 1);
                M2C_FIELD(temp_s6, s32 *, 0x344) = 0;
            }
            temp_a0 = M2C_FIELD(temp_s6, u16 *, 0x41E);
            if ((M2C_FIELD(temp_s6, s16 *, 0x41E) == 0) && (M2C_FIELD(temp_s6, f32 *, 0x20) < (f32) ((s32) (g_space_ship_max_health * 2) / 3)) && (M2C_FIELD(temp_s6, s16 *, 0x468) == 0)) {
                M2C_FIELD(temp_s6, s16 *, 0x41E) = 1;
                g_space_ship_mode = 1;
                g_space_ship_active_flag = 1;
                M2C_FIELD(temp_s6, s16 *, 0x468) = 1;
            } else if (((s16) temp_a0 == 1) && (M2C_FIELD(temp_s6, f32 *, 0x20) < (f32) ((s32) g_space_ship_max_health / 3)) && (M2C_FIELD(temp_s6, s16 *, 0x46A) == 0)) {
                saved398 = g_space_ship_saved_word;
                M2C_FIELD(temp_s6, s16 *, 0x41E) = 2;
                g_space_ship_mode = 2;
                {
                    s32 one = (s16) temp_a0;
                    g_space_ship_active_flag = one;
                    M2C_FIELD(temp_s6, s32 *, 0x464) = (saved398 * 5 + 2) / 6;
                    M2C_FIELD(temp_s6, s16 *, 0x46A) = one;
                }
            }
            temp_a0_3 = M2C_FIELD(temp_s6, s32 *, 0x440);
            coll_sweep_from_object(temp_a0_3, temp_a0_3 + 0x10, 0x04000000, 5.4f, 1.0f, 1.0f, 0, 1, 0);
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x95);
            switch (temp_v1_2) {                    /* switch 1 */
            case 0:                                 /* switch 1 */
                if ((M2C_FIELD(temp_s6, f32 *, 0x3DC) < 35.0f) && (M2C_FIELD(temp_s6, s32 *, 0x3D4) != 0) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                    if ((M2C_FIELD(temp_s6, s32 *, 0x418) != 0) && (M2C_FIELD(arg0, u8 *, 0x20) != 0xF)) {
                        moby_set_state(arg0, 6, 4);
                    } else if ((M2C_FIELD(temp_s6, s32 *, 0x464) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 2)) {
                        moby_set_state(arg0, 0x13, 9);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x41C) == 0) {
                        if ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0)) {
                            moby_set_state(arg0, 0x1D, 3);
                        } else if (math_random_int_below(2) == 0) {
                            moby_set_state(arg0, 0x12, 9);
                        } else if (M2C_FIELD(temp_s6, s16 *, 0x41E) == 0) {
                            moby_set_state(arg0, 0x1C, 3);
                        } else {
                            moby_set_state(arg0, 0x12, 9);
                        }
                    } else if (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6)) {
                        moby_set_state(arg0, 0x12, 9);
                    } else if ((M2C_FIELD(temp_s6, s16 *, 0x32A) / 2 < M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC)) || (M2C_FIELD(temp_s6, s16 *, 0x32E) / 2 < M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8))) {
                        moby_set_state(arg0, 0x1D, 3);
                    } else if ((math_random_int_below(2) == 0) && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0))) {
                        moby_set_state(arg0, 0x1D, 3);
                    } else if ((math_random_int_below(2) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 0)) {
                        moby_set_state(arg0, 0x1C, 3);
                    } else if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 55.0f) {
                        moby_set_state(arg0, 0x12, 9);
                    }
                }
                break;
            case 9:                                 /* switch 1 */
                if (((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x26) && (space_ship_is_aligned_with_target_pal(arg0) != 0)) {
                    if ((M2C_FIELD(temp_s6, s16 *, 0x41E) != 2) || (M2C_FIELD(temp_s6, s32 *, 0x464) == 0)) {
                        func_PAL_L22_003A7930(arg0, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                        moby_set_state(arg0, 0x1F, 4);
                    }
                }
                break;
            case 3:                                 /* switch 1 */
                if (M2C_FIELD(temp_s6, s32 *, 0x418) != 0) {
                    moby_set_state(arg0, 6, 4);
                } else if (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6)) {
                    moby_set_state(arg0, 0x12, 9);
                }
                break;
            case 4:                                 /* switch 1 */
                if (M2C_FIELD(temp_s6, s32 *, 0x418) != 0) {
                    moby_set_state(arg0, 6, 4);
                } else if (((M2C_FIELD(temp_s6, s32 *, 0x464) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 2))
                        || (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6))
                        || ((g_platform_mode >= 0x12) && (M2C_FIELD(arg0, u8 *, 0x20) == 0x1E))) {
                    moby_set_state(arg0, 0x12, 9);
                }
                break;
            case 6:                                 /* switch 1 */
                if (M2C_FIELD(temp_s6, s32 *, 0x418) == 0) {
                    moby_set_state(arg0, 0x1E, 4);
                }
                break;
            case 5:                                 /* switch 1 */
                func_PAL_L22_003A8F68(arg0, 2, 1);
                func_PAL_L22_003A8F68(arg0, 3, 0);
                break;
            case 8:                                 /* switch 1 */
                len8 = FastVecLength(((s128 *) (temp_s6 + 0xE0)));
                if (len8 > 0.0f) {
                    var_v0_10 = 0;
                    if (M2C_FIELD(temp_s6, f32 *, 0x410) < g_planet_radius) {
                        arena_push_point_out((arg0 + 0x10), 0.0f);
                        var_v0_10 = 0;
                    }
                    scratch[2].q = var_v0_10;
                    scratch[2].f[2] = M2C_FIELD(temp_s6, f32 *, 0x94);
                    var_v0_10 = scratch[2].q;
                    scratch[1].q = var_v0_10;
                    matrix_mul_vec3(&scratch[1].q, &scratch[1].q, arg0 + 0xC0);
                    FastVecAdd(&scratch[1].q, &scratch[1].q, (arg0 + 0x10));
                    vec_scale_to_length(&scratch[0].q, ((s128 *) (temp_s6 + 0xE0)), 4.0f);
                    FastVecAdd(&scratch[1].q, &scratch[1].q, &scratch[0].q);
                    coll_sweep_from_object((s32) arg0, (s32) &scratch[1].q, 0x90000, 5.0f, 100.0f, 0.0f, 0, 1, 0);
                }
                if (flag_set_second_pending(arg0) != 0) {
                    M2C_FIELD(temp_s6, s16 *, 0x26) = 0x19;
                    if (temp_s3 != NULL) {
                        if ((FastVecLength(((s128 *) (temp_s6 + 0xE0))) > 0.0f) && ((M2C_FIELD(temp_s6, f32 *, 0x20) - M2C_FIELD(temp_s3, f32 *, 0x2C)) <= 0.0f)) {
                            vec_scale_to_length(((s128 *) (temp_s6 + 0xE0)), ((s128 *) (temp_s6 + 0xE0)), 0.6f);
                        }
                        if (M2C_FIELD(temp_s3, f32 *, 0x2C) == 50.0f) {
                            snd_start_in_slot(0x13, 0, 0);
                        }
                        if ((M2C_FIELD(g_hero_moby, u8 *, 0x43) == 4) && (M2C_FIELD(temp_s3, s32 *, 0x20) == g_hero_moby)) {
                            FastVecSub(&scratch[0].q, temp_s6 + 0x400, temp_s6 + 0x3F0);
                            vec_scale_to_length(((s128 *) (temp_s6 + 0xE0)), &scratch[0].q, g_space_ship_move_length);
                            SpawnExplosion_pal(M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 1, 0xA, 0xA, 0xA, 0x14, 0x32, 0, 1.2f, 20.0f, 0, 1, 0, 0);
                        }
                    }
                    func_PAL_L22_003A7930(arg0, (s32) M2C_FIELD(arg0, u8 *, 0x43), 0, 3, 2, 1.0f);
                    func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 6, 0, 3);
                    M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), f32 *, 0x48) = 0.9f;
                    M2C_FIELD(arg0, f32 *, 0x48) = 0.9f;
                    temp_a0_11 = M2C_FIELD(arg0, u8 *, 0x43);
                    if ((temp_a0_11 == 4) || (temp_a0_11 == 8)) {
                        player_slot_clear_object((s32) arg0);
                    }
                } else if ((M2C_FIELD(((VarsD708 *) temp_s6)->p448, u8 *, 0x60) & 2) && (math_random_int_below(3) == 0)) {
                    func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 7, 0, 3);
                }
                if (M2C_FIELD(temp_s6, s16 *, 0x43A) == 0) {
                    M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
                }
                M2C_FIELD(temp_s6, f32 *, 0x3E4) = M2C_FIELD(temp_s6, f32 *, 0x3E8) = 0.0f;
                temp_v0_8 = moby_dispatch_action_by_kind(arg0, temp_s6 + 0x60);
                if (temp_v0_8 & 1) {
                    M2C_FIELD(temp_s6, s32 *, 0x344) = 1;
                } else if (temp_v0_8 & 2) {
                    M2C_FIELD(temp_s6, s32 *, 0x37C) = 0xc8;
                    moby_set_state(arg0, 5, 0);
                    func_PAL_L22_003A7930(arg0, 0, 0, 3, 3, 1.0f);
                }
                goto block_184;
            case 10:                                /* switch 1 */
                game10 = g_hero_state;
                M2C_FIELD(game10, s16 *, 0x1E0) = 0x8;
                temp_v1_12 = M2C_FIELD(temp_s6, void **, 0x388);
                M2C_FIELD(temp_v1_12, u16 *, 0x34) = (u16) (M2C_FIELD(temp_v1_12, u16 *, 0x34) | 0x41);
                if (flag_set_first_pending(arg0) != 0) {
                    if ((M2C_FIELD(temp_s6, s32 *, 0x4EC) != 0) && (g_item_enabled_flags[8] == 0)) {
                        g_item_enabled_flags[8] = 1;
                        snd_play_from_global_bank(1, 0, NULL);
                        value_set_entry_by_index_pal(0x1233, -1);
                        g_trigger_event_flag = 1;
                    }
                    FadeToBlack(g_space_ship_fade_time);
                    goto block_183;
                }
                temp_a0_13 = M2C_FIELD(arg0, u16 *, 0x96);
                temp_v0_9 = (s32) g_space_ship_fade_time / 2;
                if (temp_v0_9 < (s32) temp_a0_13) {
                    if ((func_PAL_002AF6C0(arg0, 27.0f) != 0) && ((M2C_FIELD(arg0, u16 *, 0x34) ^ 1) & 1) && ((((s32) g_space_ship_fade_time / 2) - 4) < (s32) M2C_FIELD(arg0, u16 *, 0x96))) {
                        coll_sweep_from_object((s32) arg0, (s32) (arg0 + 0x10), 0x90000, 25.0f, 100.0f, 0.0f, 0, 1, 0);
                        moby_aim_at_target_offset_pal(arg0, game10 + 0x80);

                        SetDeathBits_pal(arg0, 0, 3);
                        part_spawn_explosion_with_sparks_pal(arg0, (arg0 + 0x10), 2.0f, 7.0f, -1);
                        for (var_s0_2 = 0; var_s0_2 < 5; var_s0_2++) {
                            vec_random_direction(&scratch[0].q, g_space_ship_random_dir_a * 0.020000001f, g_space_ship_random_dir_b * 0.020000001f);
                            scratch[0].f[2] = math_fabs(scratch[0].f[2]) * g_space_ship_z_scale;
                            matrix_mul_vec3(&scratch[0].q, &scratch[0].q, M2C_FIELD(temp_s6, s32 *, 0x440) + 0xC0);
                            temp_a0_14 = M2C_FIELD(temp_s6, s32 *, 0x440);
                            temp_v0_11 = cam_moby_create_pal((void *) temp_a0_14, 1, (s32) M2C_FIELD(temp_a0_14, s16 *, 0xAA), var_s0_2, temp_a0_14 + 0x10, temp_a0_14 + 0xF0, &scratch[0].q, 0xFF, 30.0f, 15.0f);
                            *(s32 **)((s8 *)temp_v0_11 + 0x64) = &g_ship_model_marker;
                        }
                        for (var_s0_3 = 0; var_s0_3 < 2; var_s0_3++) {
                            vec_random_direction(&scratch[0].q, g_space_ship_random_dir_a * 0.020000001f, g_space_ship_random_dir_b * 0.020000001f);
                            scratch[0].f[2] = math_fabs(scratch[0].f[2]) * g_space_ship_z_scale;
                            matrix_mul_vec3(&scratch[0].q, &scratch[0].q, ((void *) (arg0 + 0xC0)));
                            temp_v0_12 = cam_moby_create_pal(arg0, 1, (s32) M2C_FIELD(arg0, s16 *, 0xAA), var_s0_3, (arg0 + 0x10), ((void *) (arg0 + 0xF0)), &scratch[0].q, 0xFF, 30.0f, 15.0f);
                            *(s32 **)((s8 *)temp_v0_12 + 0x64) = &g_ship_model_marker;
                        }
                        SpawnExplosion_pal(M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0, 0x73, 0x50, 0x46, 0x4E, 0x4B, 1, 7.5f, 20.0f, 1, 1, 0, 0);
                        SpawnExplosion_pal((arg0 + 0x10), 1, 0x2D, 0x28, 0x28, 0x28, 0x3A, 1, 3.0f, 20.0f, 1, 1, 0, 0);
                        M2C_FIELD(arg0, u16 *, 0x34) = (u16) (M2C_FIELD(arg0, u16 *, 0x34) | 0x41);
                        temp_a0_15 = M2C_FIELD(temp_s6, void **, 0x388);
                        M2C_FIELD(temp_a0_15, u16 *, 0x34) = (u16) (M2C_FIELD(temp_a0_15, u16 *, 0x34) | 0x41);
                        temp_v1_13 = M2C_FIELD(temp_s6, s32 *, 0x440);
                        M2C_FIELD(temp_v1_13, u16 *, 0x34) = (u16) (M2C_FIELD(temp_v1_13, u16 *, 0x34) | 0x41);
                        temp_a0_16 = M2C_FIELD(temp_s6, void **, 0x444);
                        M2C_FIELD(temp_a0_16, u16 *, 0x34) = (u16) (M2C_FIELD(temp_a0_16, u16 *, 0x34) | 0x41);
                        temp_a0_17 = ((VarsD708 *) temp_s6)->p448;
                        M2C_FIELD(temp_a0_17, s128 *, 0x10) = *(s128 *)(arg0 + 0x10);
                        func_PAL_002A7E68(temp_a0_17, 6, 0, 3);
                        {
                            f32 v = g_space_ship_float_param_a;
                            M2C_FIELD(((VarsD708 *) temp_s6)->p448, f32 *, 0x48) = 3.2f;
                            g_space_ship_speed_param = v;
                            arena_push_point_out(((VarsD708 *) temp_s6)->p448 + 0x10, v);
                        }
                        goto block_183;
                    }
                    temp_v1_14 = M2C_FIELD(arg0, u16 *, 0x96);
                    if (temp_v1_14 >= 0x12d) {
                        moby_mark_spawned(M2C_FIELD(temp_s6, void **, 0x388));
                        M2C_FIELD(temp_s6, void **, 0x388) = NULL;
                        moby_mark_spawned((void *) M2C_FIELD(temp_s6, s32 *, 0x440));
                        M2C_FIELD(temp_s6, s32 *, 0x440) = 0;
                        moby_mark_spawned(M2C_FIELD(temp_s6, void **, 0x444));
                        M2C_FIELD(temp_s6, void **, 0x444) = NULL;
                        moby_mark_spawned(((VarsD708 *) temp_s6)->p448);
                        ((VarsD708 *) temp_s6)->p448 = NULL;
                        level_store_value_pair_pal(0, 0);
                        g_space_ship_flag = 1;
                        level_set_dependent_value();
                        moby_mark_spawned(arg0);
                        return;
                    } else {
                        if ((temp_v1_14 >= 0xda) && (M2C_FIELD(arg0, u16 *, 0x34) & 1) && (temp_a0_18 = ((VarsD708 *) temp_s6)->p448, (((M2C_FIELD(temp_a0_18, u16 *, 0x34) ^ 1) & 1) != 0))) {
                            temp_f12_3 = g_space_ship_speed_param - g_space_ship_float_param_b;
                            g_space_ship_speed_param = temp_f12_3;
                            if (temp_f12_3 > 0.0f) {
                                arena_push_point_out(temp_a0_18 + 0x10, temp_f12_3);
                                M2C_FIELD(((VarsD708 *) temp_s6)->p448, f32 *, 0x48) = 3.2f;
                                func_PAL_002A0F68(((VarsD708 *) temp_s6)->p448);
                                func_002A0F48(((VarsD708 *) temp_s6)->p448);
                            } else {
                                if ((M2C_FIELD(temp_a0_18, u16 *, 0x34) ^ 1) & 1) {
                                    FastVecScale(&scratch[0].q, temp_a0_18 + 0xC0, 2.2f);
                                    FastVecAdd(&scratch[0].q, &scratch[0].q, ((VarsD708 *) temp_s6)->p448 + 0x10);
                                    arena_push_point_out(&scratch[0].q, 0.5f);
                                    SpawnExplosion_pal(&scratch[0].q, 1, 0xA, 0xA, 0xA, 0xA, 0x14, 0, 0.9f, 20.0f, 0, 0, 0, 0);
                                    PlayMobySound(g_space_ship_sound_a, 0, arg0);
                                    temp_v1_15 = ((VarsD708 *) temp_s6)->p448;
                                    M2C_FIELD(temp_v1_15, u16 *, 0x34) = (u16) (M2C_FIELD(temp_v1_15, u16 *, 0x34) | 0x41);
                                }
                            }
                        } else {
                            if (!(M2C_FIELD(arg0, u16 *, 0x96) & 7) && ((M2C_FIELD(arg0, u16 *, 0x34) ^ 1) & 1)) {
                                if (math_random_int_below(2) != 0) {
                                    moby_transform_joint_to_world((s32) arg0, math_random_int_below(4), (s32) &scratch[0].q);
                                } else {
                                    moby_transform_joint_to_world(M2C_FIELD(temp_s6, s32 *, 0x440), math_random_int_below(6), (s32) &scratch[0].q);
                                }
                                SpawnExplosion_pal(&scratch[0].q, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, math_random_float_range(1.0f, 1.9f), 20.0f, 0, 0, 0, 0);
                            }
                            if (!(M2C_FIELD(arg0, u16 *, 0x96) & 0xF) && ((M2C_FIELD(arg0, u16 *, 0x34) ^ 1) & 1)) {
                                PlayMobySound(g_space_ship_sound_b, 0, arg0);
                            }
                        }
                        goto block_183;
                    }
                } else {
                    temp_v0_10 = temp_v0_9 - 4;
                    if (temp_a0_13 == temp_v0_10) {
                        FadeToBlack(1);
                        arena_push_point_out((arg0 + 0x10), 0.0f);
                        scratch[4].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0);
                        scratch[5].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x10);
                        scratch[6].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x20);
                        qzero_nc(&scratch[7].q);
                        mat_get_euler_angles(&workspace.pair.second, &scratch[0].q);
                        temp_s2 = (arg0 + 0x10);
                        SetCamera5Pose(g_tether_origin, &scratch[0].q, 1, 0, 0);
                        func_PAL_L22_003A7930(arg0, 0xE, 0, 3, 3, 0.6f);
                        M2C_FIELD(temp_s6, f32 *, 0x138) = 0.012f;
                        FastVecSub(&scratch[7].q, temp_s6 + 0x3F0, temp_s2);
                        vec_scale_to_length(&scratch[6].q, &scratch[7].q, -(g_space_ship_scale * 33.0f));
                        FastVecAdd(&scratch[6].q, &scratch[6].q, temp_s2);
                        arena_push_point_out(&scratch[6].q, 2.0f);
                        vec_scale_to_length(&scratch[5].q, &scratch[7].q, -(g_space_ship_scale * 55.0f));
                        FastVecAdd(&scratch[5].q, &scratch[5].q, temp_s2);
                        arena_push_point_out(&scratch[5].q, g_space_ship_scale * 45.0f);
                        vec_scale_to_length(&scratch[7].q, &scratch[7].q, 1.0f);
                        scratch[0].q = scratch[7].q;
                        {
                            u8 *g = g_hero_state;
                            scratch[1].q = M2C_FIELD(M2C_FIELD(g, void **, 0x2290), s128 *, 0xD0);
                        }

                        qzero_nc(&scratch[3].q);
                        FastVecCross(&scratch[2].q, &scratch[0].q, &scratch[1].q);
                        mat_get_euler_angles(&workspace.pair.first.matrix, &scratch[4].q);
                        cam_set_state_rotation(&scratch[4].q);
                        object_copy_vector_to_selected(&scratch[5].q);
                    } else if (temp_v0_10 < (s32) temp_a0_13) {
                        scratch[1].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0);
                        scratch[2].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x10);
                        scratch[3].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x20);
                        qzero_nc(&scratch[4].q);
                        mat_get_euler_angles(&workspace.shifted.basis, &workspace.shifted.rotation);
                        SetCamera5Pose(g_tether_origin, &scratch[0].q, 1, 0, 0);
                        FastVecSub(&scratch[0].q, (arg0 + 0x10), g_tether_origin);
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, 1.0f);
                        scratch[2].q = M2C_FIELD(arg0, s128 *, 0xE0);
                        qzero_nc(&scratch[3].q);
                        temp_s3_2 = g_hero_state;
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, 1.0f);
                        vec_scale_to_length(&scratch[2].q, &scratch[2].q, 1.0f);
                        FastVecCross(&scratch[1].q, &scratch[0].q, &scratch[2].q);
                        vec_scale_to_length(&scratch[1].q, &scratch[1].q, 1.0f);
                        mat_get_euler_angles(&workspace.pair.first.matrix, &scratch[4].q);
                        cam_set_state_rotation(&scratch[4].q);
                        FadeToBlack(1);
                        part_init_effect_record(&workspace.collision.query, M2C_FIELD(temp_s3_2, s32 *, 0x2290), 0xB0000, 50.0f);
                        scratch[6].b[8] = 7;
                        scratch[6].b[9] = 1;

                        scratch[6].h[5] = M2C_FIELD(M2C_FIELD(temp_s3_2, s32 *, 0x2290), u16 *, 0xAA);
                        coll_sweep_from_object((s32) arg0, (s32) g_tether_origin, 0x90000, 10.0f, 100.0f, 0.0f, 0, 1, 0);
                        temp_s4 = g_tether_origin + 0x240;
                        CollLine(g_tether_origin, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        temp_s5 = g_tether_origin + 0x250;
                        FastVecScale(&spA0, M2C_FIELD(temp_s3_2, s32 *, 0x2290) + 0xE0, 4.0f);
                        FastVecAdd(&spA0, &spA0, temp_s3_2 + 0x80);
                        CollLine(&spA0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        temp_f20 = g_space_ship_scale * 6.875f;
                        temp_f21 = -temp_f20;
                        FastVecScale(&spB0, temp_s4, temp_f20);
                        FastVecAdd(&spB0, &spB0, g_tether_origin);
                        CollLine(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        FastVecScale(&spB0, temp_s4, temp_f21);
                        FastVecAdd(&spB0, &spB0, g_tether_origin);
                        CollLine(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        FastVecScale(&spB0, temp_s5, temp_f20);
                        FastVecAdd(&spB0, &spB0, g_tether_origin);
                        CollLine(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        FastVecScale(&spB0, temp_s5, temp_f21);
                        FastVecAdd(&spB0, &spB0, g_tether_origin);
                        CollLine(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                    } else {
                        FadeToBlack(1);
                    }
block_183:
                    qzero_nc(((s128 *) (temp_s6 + 0xE0)));
                    moby_call_helper_with_blocks_pal(arg0);
                    goto block_184;
                }
                break;
            }
block_184:
                temp_v0_4 = M2C_FIELD(arg0, u8 *, 0x20);
                switch (temp_v0_4) {                /* switch 2 */
                case 5:                             /* switch 2 */
                    if ((M2C_FIELD(temp_s6, s32 *, 0x464) == 0) || (M2C_FIELD(temp_s6, s16 *, 0x41E) != 2)) {
                        if (M2C_FIELD(temp_s6, s16 *, 0x380) != 0) {
                            FastDecTimer((s32) (temp_s6 + 0x380));
                        } else {
                            temp_f1_4 = g_space_ship_threshold;
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                            if ((M2C_FIELD(temp_s6, f32 *, 0x3E0) < temp_f1_4) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 0)) {
                                moby_set_state(arg0, 6, 0);
                            } else {
                                moby_set_state(arg0, 7, 0);
                            }
                        }
                        M2C_FIELD(temp_s6, s32 *, 0x190) = 0;
                        func_PAL_L22_003A7930(arg0, 0xC, 0, 3, 3, 1.0f);
                    } else {
                    case 18:                        /* switch 2 */
                        if ((M2C_FIELD(arg0, u8 *, 0x94) != 0x12) && (M2C_FIELD(arg0, u8 *, 0x43) != 0xB)) {
                            func_PAL_L22_003A7930(arg0, 0xB, 0, 3, 3, 1.0f);
                        }
                        lane_find_point_ahead_of_ship(arg0);
                        moby_set_state(arg0, 0x13, 9);
                    }
                    break;
                case 19:                            /* switch 2 */
                    temp_a0_4 = M2C_FIELD(temp_s6, s32 *, 0x440);
                    if (M2C_FIELD(temp_a0_4, u8 *, 0x43) == 3) {
                        if ((M2C_FIELD(temp_a0_4, u8 *, 0x60) & 2) && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) || (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 70.0f))) {
                            func_PAL_L22_003A7930(arg0, 0xB, (s32) moby_get_anim_value(arg0), 3, 2, 1.0f);
                        } else if ((moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 4.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 4.0f)) {
                            space_ship_run_attached_part_effect(arg0, 1, g_hero_moby, 0, 0);
                        } else if ((moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 2.0f)) {
                            space_ship_run_attached_part_effect(arg0, 2, g_hero_moby, 0, 0);
                        }
                    } else if ((M2C_FIELD(temp_s6, f32 *, 0x3DC) < 70.0f) && (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0) && (M2C_FIELD(temp_s6, s32 *, 0x464) == 0)) {
                        func_PAL_L22_003A7930(arg0, 3, 0, 3, 2, 1.0f);
                        func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 7, 0, 3);
                    }
                    if (fast_vec_dist((arg0 + 0x10), M2C_FIELD(temp_s6, s128 **, 0x3AC)) < 8.0f) {
                        moby_set_state(arg0, 0x14, 9);
                        break;
                    }
                    WalkPathUpdate_pal(arg0);
                    if (((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x1a) && (M2C_FIELD(temp_s6, f32 *, 0x43C) <= M2C_FIELD(temp_s6, f32 *, 0x140))) {
                        FastVecSub(&scratch[0].q, (arg0 + 0x10), (s128 *) (g_hero_state + 0x80));
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, 1.0f);
                        if ((FastVecDot(arg0 + 0xC0, &scratch[0].q) < -0.5f) && (FastVecLength(&scratch[0].q) < 10.0f)) {
                            moby_set_state(arg0, 0x21, 9);
                            if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) {
                                M2C_FIELD(temp_s6, s16 *, 0x3A6) = 3;
                            } else if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0) {
                                M2C_FIELD(temp_s6, s16 *, 0x3A6) = 3;
                            } else {
                                M2C_FIELD(temp_s6, s16 *, 0x3A6) = 2;
                            }
                            M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
                        }
                    }
                    break;
                case 20:                            /* switch 2 */
                    if ((flag_set_first_pending(arg0) != 0) && (M2C_FIELD(arg0, u8 *, 0x43) == 4)) {
                        func_PAL_L22_003A7930(arg0, 0, 0, 0x11, 3, 1.0f);
                    } else if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x1a) {
                        if (pickup_find_nearest_needed(arg0, &scratch[0].q) != 0) {
                            M2C_FIELD(temp_s6, s128 *, 0x3B0) = (s128) scratch[0].q;
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (temp_s6 + 0x3B0);
                            moby_set_state(arg0, 0x15, 9);
                            func_PAL_L22_003A7930(arg0, 0xB, 0, 3, 3, 1.0f);
                        } else {
                            stat_restore_random(arg0);
                            if ((((f32) ((s32) (g_space_ship_max_health * 2) / 3) <= M2C_FIELD(temp_s6, f32 *, 0x20)) || (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6))
                                    || ((math_random_int_below(2) == 0) && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0))))
                                && ((M2C_FIELD(temp_s6, s32 *, 0x464) == 0) || (M2C_FIELD(temp_s6, s16 *, 0x41E) != 2))) {
                                if (((f32) ((s32) g_space_ship_max_health / 6) < M2C_FIELD(temp_s6, f32 *, 0x20))
                                        && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0))
                                        && (math_random_int_below(5) == 0)) {
                                    moby_set_state(arg0, 0x1D, 3);
                                } else {
                                    moby_set_state(arg0, 5, 0);
                                }
                            } else if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 55.0f) {
                                moby_set_state(arg0, 0x12, 9);
                            }
                        }
                    }
                    break;
                case 21:                            /* switch 2 */
                    if (fast_vec_dist((arg0 + 0x10), M2C_FIELD(temp_s6, s128 **, 0x3AC)) < 8.0f) {
                        moby_set_state(arg0, 0x16, 9);
                        func_PAL_L22_003A7930(arg0, 0, 0, 0x11, 3, 1.0f);
                        break;
                    }
                    WalkPathUpdate_pal(arg0);
                    break;
                case 22:                            /* switch 2 */
                    if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x1a) {
                        if (((f32) ((s32) (g_space_ship_max_health * 2) / 3) <= M2C_FIELD(temp_s6, f32 *, 0x20)) || (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6))) {
                            moby_set_state(arg0, 5, 0);
                        } else if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 55.0f) {
                            moby_set_state(arg0, 0x12, 9);
                        } else {
                            moby_set_state(arg0, 0x14, 9);
                        }
                    }
                    break;
                case 7:                             /* switch 2 */
                    if (M2C_FIELD(temp_s6, f32 *, 0x3E0) < 33.0f) {
                        moby_set_state(arg0, 0x1E, 4);
                    } else {
                        WalkPathUpdate_pal(arg0);
                    }
                    break;
                case 6:                             /* switch 2 */
                    temp_f1_4 = M2C_FIELD(temp_s6, f32 *, 0x3E0);
                    if (M2C_FIELD(temp_s6, s32 *, 0x418) != 0) {
                        if (temp_f1_4 < 20.0f) {
                            moby_set_state(arg0, 0xF, 6);
                        } else {
                            WalkPathUpdate_pal(arg0);
                        }
                    } else if (temp_f1_4 < g_space_ship_threshold) {
                        moby_set_state(arg0, 0x1E, 4);
                    } else {
                        WalkPathUpdate_pal(arg0);
                    }
                    break;
                case 28:                            /* switch 2 */
                    if (flag_set_first_pending(arg0) != 0) {
                        func_PAL_L22_003A7930(arg0, 0xB, 0, 5, 3, 1.0f);
                    }
                    if ((M2C_FIELD(temp_s6, f32 *, 0x3E0) < g_space_ship_threshold) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                        moby_set_state(arg0, 0x1E, 4);
                    }
                    M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                    WalkPathUpdate_pal(arg0);
                    break;
                case 29:                            /* switch 2 */
                    if (flag_set_first_pending(arg0) != 0) {
                        func_PAL_L22_003A7930(arg0, 0xC, 0, 0x11, 3, 1.0f);
                    }
                    if ((M2C_FIELD(temp_s6, f32 *, 0x3E0) < 29.0f) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                        moby_set_state(arg0, 0x1E, 4);
                    }
                    M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                    WalkPathUpdate_pal(arg0);
                    break;
                case 31:                            /* switch 2 */
                    temp_v1_3 = M2C_FIELD(arg0, u8 *, 0x43);
                    switch (temp_v1_3) {            /* switch 3; irregular */
                    case 9:                         /* switch 3 */
                        if ((moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 3, 4.0f, 10.0f, 0x10007, 1.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(arg0, u8 *, 0x60) & 2) {
                            WalkPathUpdate_pal(arg0);
                            func_PAL_L22_003A7930(arg0, 0xA, 0, 3, 3, g_space_ship_orbit_arg);
                        }
                        if ((moby_get_anim_value(arg0) > 0.0f) && (moby_get_anim_value(arg0) < 23.0f)) {
                            moby_aim_at_target_offset_pal(arg0, (s128 *) (g_hero_state + 0x80));
                        }
                        break;
                    case 10:                        /* switch 3 */
                        if ((moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 4, 4.0f, 10.0f, 0x10007, 1.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(arg0, u8 *, 0x60) & 2) {
                            func_PAL_L22_003A7930(arg0, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                        }
                        moby_aim_at_target_offset_pal(arg0, (s128 *) (g_hero_state + 0x80));
                        break;
                    case 13:                        /* switch 3 */
                        if (flag_set_first_pending(arg0) != 0) {
                            g_space_ship_boost_timer = 0;
                        }
                        if (M2C_FIELD(arg0, u8 *, 0x60) & 2) {
                            if ((g_space_ship_boost_timer != 0) && ((math_random_int_below(4) == 0) || ((f32) (g_ship_progress_count * 7) < M2C_FIELD(temp_s6, f32 *, 0x20)))) {
                                if ((M2C_FIELD(temp_s6, f32 *, 0x20) == (f32) M2C_FIELD(temp_s6, s16 *, 0x326)) && (g_ship_progress_count < 0x64)) {
                                    moby_set_state(arg0, 4, 2);
                                } else {
                                    moby_set_state(arg0, 3, 2);
                                }
                            } else if (space_ship_is_aligned_with_target_pal(arg0) != 0) {
                                func_PAL_L22_003A7930(arg0, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                                moby_set_state(arg0, 0x1F, 4);
                            } else {
                                moby_set_state(arg0, 0x12, 9);
                            }
                        } else if (g_space_ship_anim_max < moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440))) {
                            if (moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < g_space_ship_anim_min) {
                                moby_transform_joint_to_world(M2C_FIELD(temp_s6, s32 *, 0x440), 4, (s32) &scratch[1].q);
                                moby_transform_joint_to_world(M2C_FIELD(temp_s6, s32 *, 0x440), 3, (s32) &scratch[0].q);
                                FastVecAdd(&scratch[2].q, &scratch[0].q, &scratch[1].q);
                                FastVecScale(&scratch[2].q, &scratch[2].q, 0.5f);
                                M2C_FIELD(arg0, s32 *, 0x98) = 0;
                                coll_sweep_from_object((s32) arg0, (s32) &scratch[2].q, 0x10007, 4.0f, 100.0f, 14.5f, 0, 2, 0);
                                {
                                    u8 *g = g_hero_state;
                                    f32 reach = g_space_ship_reach;
                                    M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                                    FastVecScale(&scratch[3].q, M2C_FIELD(g, void **, 0x2290) + 0xE0, reach);
                                    FastVecAdd(&scratch[3].q, &scratch[3].q, g + 0x80);
                                }

                                if (fast_vec_dist(&scratch[2].q, &scratch[3].q) < g_space_ship_trigger_distance) {
                                    queue_copy_record_by_index(0x2B);
                                    g_space_ship_boost_timer = (g_space_ship_state_default * 5 + 2) / 6;
                                }
                            }
                        }
                        moby_set_controller_speed_limits(arg0, g_space_ship_speed_limit_a * 0.00040000002f, g_space_ship_speed_limit_b * 0.020000001f, g_orbit_param_e * 6.981318e-06f, g_orbit_param_f * 0.0003490659f);
                        moby_aim_at_target_offset_pal(arg0, (s128 *) (g_hero_state + 0x80));
                        break;
                    }
                    if ((M2C_FIELD(arg0, u8 *, 0x95) != 6) && (M2C_FIELD(temp_s6, f32 *, 0x3DC) > g_space_ship_threshold) && (g_space_ship_boost_timer == 0)) {
                        moby_set_state(arg0, 0x12, 9);
                    }
                    break;
                case 15:                            /* switch 2 */
                    moby_aim_at_target_offset_pal(arg0, (s128 *) (g_hero_state + 0x80));
                    FastVecScale(&scratch[0].q, arg0 + 0xC0, 3.0f);
                    FastVecAdd(&scratch[0].q, &scratch[0].q, (arg0 + 0x10));
                    if (WalkPathIsClear(arg0, (arg0 + 0x10), &scratch[0].q) == 0) {
                        func_PAL_L22_003A7930(arg0, 9, 0, 3, 3, g_space_ship_orbit_arg);
                        moby_set_state(arg0, 0x1F, 6);
                        break;
                    }
                    break;
                case 32:                            /* switch 2 */
                    if (flag_set_first_pending(arg0) != 0) {
                        func_PAL_L22_003A7930(arg0, 3, 0, 3, 2, 1.0f);
                        func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 1, 0, 3);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = math_random_int_range(0x64, 0xc8);
                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                    } else if (M2C_FIELD(((VarsD708 *) temp_s6)->p448, u8 *, 0x60) & 2) {
                        if (math_random_int_below(4) == 0) {
                            func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 7, 0, 3);
                        } else {
                            func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 1, 0, 3);
                        }
                    }
                    if ((M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) || (M2C_FIELD(temp_s6, s32 *, 0x3D8) == 0)
                        || ((temp_f1_5 = M2C_FIELD(temp_s6, f32 *, 0x3DC)) > 60.0f)
                        || ((temp_a0_6 = M2C_FIELD(temp_s6, s32 *, 0x440), (M2C_FIELD(temp_a0_6, u8 *, 0x60) & 2)) && (temp_f1_5 < g_space_ship_threshold))) {
                        moby_set_state(arg0, 5, 0);
                    } else if (M2C_FIELD(temp_a0_6, u8 *, 0x60) & 2) {
                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                    } else if (M2C_FIELD(temp_a0_6, u8 *, 0x43) == 3) {
                        if ((moby_get_anim_value((void *) temp_a0_6) >= 4.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 4.0f)) {
                            space_ship_run_attached_part_effect(arg0, 1, g_hero_moby, 0, 0);
                        } else if ((moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 2.0f)) {
                            space_ship_run_attached_part_effect(arg0, 2, g_hero_moby, 0, 0);
                        }
                    } else {
                        FastDecTimer((s32) (temp_s6 + 0x386));
                        if (M2C_FIELD(temp_s6, s16 *, 0x386) <= 0) {
                            func_PAL_L22_003A7930(arg0, 3, 0, 3, 2, 1.0f);
                            func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 1, 0, 3);
                        }
                    }
                    if (M2C_FIELD(temp_s6, f32 *, 0x3E0) < g_space_ship_threshold) {
                        func_PAL_L22_003A7930(arg0, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                        moby_set_state(arg0, 0x1F, 4);
                        break;
                    }
                    temp_v1_4 = M2C_FIELD(arg0, u8 *, 0x43);
                    if (temp_v1_4 == 0xC) {
                        if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 37.0f) {
                            func_PAL_L22_003A7930(arg0, 0, 0, 3, 1, 1.0f);
                        } else {
                            WalkPathUpdate_pal(arg0);
                        }
                    } else if (temp_v1_4 == 0xB) {
                        if ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) >= M2C_FIELD(temp_s6, s16 *, 0x430)) && (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 32.0f)) {
                            func_PAL_L22_003A7930(arg0, 0, 0, 3, 1, 1.0f);
                        } else {
                            WalkPathUpdate_pal(arg0);
                        }
                    } else {
                        if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) < M2C_FIELD(temp_s6, s16 *, 0x430)) {
                            func_PAL_L22_003A7930(arg0, 0xB, 0, 3, 1, 1.0f);
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                            M2C_FIELD(temp_s6, s16 *, 0x430) = 0x3E8;
                        }
                        temp_f1_6 = M2C_FIELD(temp_s6, f32 *, 0x3DC);
                        if (temp_f1_6 > 42.0f) {
                            func_PAL_L22_003A7930(arg0, 0xC, 0, 3, 1, 1.0f);
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                        } else if (temp_f1_6 < 25.0f) {
                            func_PAL_L22_003A7930(arg0, 0xB, 0, 3, 1, 1.0f);
                            temp_s0_3 = temp_s6 + 0x3B0;
                            FastVecSub(&scratch[0].q, (arg0 + 0x10), (s128 *) (g_hero_state + 0x80));
                            FastVecScale(&scratch[0].q, &scratch[0].q, 20.0f);
                            FastVecAdd(&scratch[0].q, (arg0 + 0x10), &scratch[0].q);
                            lane_find_nearest_point(arg0, temp_s0_3, &scratch[0].q, 1);
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = temp_s0_3;
                        } else {
                            moby_call_helper_with_blocks_pal(arg0);
                        }
                    }
                    break;
                case 33:                            /* switch 2 */
                    if (flag_set_first_pending(arg0) != 0) {
                        func_PAL_L22_003A7930(arg0, 5, 0, 3, 3, 1.0f);
                        func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 0, 0, 3);
                    }
                    lane_store_nearest_point_as_current(arg0, 1);
                    temp_s0_4 = temp_s6 + 0x360;
                    M2C_FIELD(temp_s6, s128 *, 0x360) = (s128) M2C_FIELD(((M2C_FIELD(temp_s6, s16 *, 0x356) * 0x10) + g_ship_path_table[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]]), s128 *, 0x10);
                    arena_push_point_out(temp_s0_4, 8.0f);
                    M2C_FIELD(temp_s6, f32 *, 0x3A0) = fast_vec_dist((arg0 + 0x10), temp_s0_4);
                    moby_set_state(arg0, 0x22, 5);
                    M2C_FIELD(temp_s6, u16 *, 0x3A4) = 0U;
                    if (M2C_FIELD(temp_s6, s16 *, 0x3A6) == 3) {
                        if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) {
                            M2C_FIELD(temp_s6, s16 *, 0x3A6) = 0;
                        } else {
                            M2C_FIELD(temp_s6, s16 *, 0x3A6) = 1;
                        }
                    }
                    break;
                case 34:                            /* switch 2 */
                    temp_s0_5 = temp_s6 + 0x360;
                    if (fast_vec_dist((arg0 + 0x10), temp_s0_5) < 2.0f) {
                        *(s128 *)(arg0 + 0x10) = M2C_FIELD(temp_s6, s128 *, 0x360);
                        moby_set_state(arg0, 0x23, 5);
                        func_PAL_L22_003A7930(arg0, 6, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = math_random_int_range(0x12c, 0x1f4);
                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                        M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                    } else {
                        FastVecSub(&scratch[0].q, temp_s0_5, (arg0 + 0x10));
                        spC0 = 0;
                        temp_f_dist = FastVecLength(&scratch[0].q);
                        math_step_value_toward_target(&spC0, temp_s6 + 0x3A8, temp_f_dist, 0.016f, 0.008f, 0.40000004f);
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, M2C_FIELD(temp_s6, f32 *, 0x3A8));
                        FastVecAdd((arg0 + 0x10), (arg0 + 0x10), &scratch[0].q);
                        if ((M2C_FIELD(arg0, u8 *, 0x60) & 2) && (M2C_FIELD(arg0, u8 *, 0x43) == 5)) {
                            func_PAL_L22_003A7930(arg0, 6, 0, 0x11, 3, 1.0f);
                        }
                    }
                    break;
                case 35:                            /* switch 2 */
                    if ((M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) || (M2C_FIELD(temp_s6, s32 *, 0x3D8) == 0) || (M2C_FIELD(temp_s6, s32 *, 0x418) != 0)
                        || ((M2C_FIELD(temp_s6, s32 *, 0x464) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 2))
                        || ((temp_a1_2 = (u16) M2C_FIELD(temp_s6, s16 *, 0x3A6), (M2C_FIELD(temp_s6, s16 *, 0x3A6) == 1))
                            && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) || ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x65)))) {
                        var_s5 = arg0 + 0xE0;
                        moby_set_state(arg0, 0x24, 5);
                        func_PAL_L22_003A7930(arg0, 2, 0, 3, 2, 1.0f);
                        M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                    } else {
                                temp_a0_7 = M2C_FIELD(temp_s6, s32 *, 0x440);
                                if (M2C_FIELD(temp_a0_7, u8 *, 0x60) & 2) {
                                    mode3A6 = (s16) temp_a1_2;
                                    if (mode3A6 == 0) {
                                        if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) == 0) {
                                            var_s5 = arg0 + 0xE0;
                                            moby_set_state(arg0, 0x24, 5);
                                            func_PAL_L22_003A7930(arg0, 6, 0, 3, 3, 1.0f);
                                            M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                                        } else {
                                        var_s5 = arg0 + 0xE0;
                                        table_decrement_timer();
                                        }
                                    } else if (mode3A6 == 1) {
                                        func_PAL_L22_003A7930(arg0, 2, 0, 3, 2, 1.0f);
                                        var_s5 = arg0 + 0xE0;
                                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                                    } else {
                                        var_s5 = arg0 + 0xE0;
                                        if (mode3A6 == 2) {
                                            if (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 30.0f) {
                                                moby_set_state(arg0, 0x24, 5);
                                                M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                                            }
                                        }
                                    }
                                } else {
                                    temp_v1_5 = M2C_FIELD(temp_a0_7, u8 *, 0x43);
                                    if (temp_v1_5 == 3) {
                                        if ((moby_get_anim_value((void *) temp_a0_7) >= 4.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 4.0f)) {
                                            space_ship_run_attached_part_effect(arg0, 1, g_hero_moby, 0, 0);
                                            var_s5 = arg0 + 0xE0;
                                        } else {
                                            var_s5 = arg0 + 0xE0;
                                            if ((moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 2.0f)) {
                                                space_ship_run_attached_part_effect(arg0, 2, g_hero_moby, 0, 0);
                                            }
                                        }
                                    } else if (temp_v1_5 == 14) {
                                        if ((moby_get_anim_value((void *) temp_a0_7) > 22.0f) && (moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 55.0f)) {
                                            var_s5 = arg0 + 0xE0;
                                            M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), f32 *, 0x48) = 1.0f;
                                        } else {
                                            var_s5 = arg0 + 0xE0;
                                            if (moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 10.0f) {
                                                f32 t = moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440));
                                                s128 *d = &scratch[0].q;
                                                if (t <= 22.0f) {
                                                *d = *(s128 *)(arg0 + 0x10);
                                                vec_scale_to_length(&scratch[1].q, var_s5, 3.0f);
                                                FastVecAdd(&scratch[1].q, &scratch[1].q, arg0 + 0xC0);
                                                FastVecAdd(d, d, &scratch[1].q);
                                                keyed_object_place(arg0, d, 0);
                                                M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), f32 *, 0x48) = 0.35f;
                                                }
                                            }
                                        }
                                    } else {
                                        var_s5 = arg0 + 0xE0;
                                        FastDecTimer((s32) (temp_s6 + 0x386));
                                        if (M2C_FIELD(temp_s6, s16 *, 0x386) <= 0) {
                                            temp_v1_6 = M2C_FIELD(temp_s6, s16 *, 0x3A6);
                                            if (temp_v1_6 == 1) {
                                                func_PAL_L22_003A7930(arg0, 3, 0, 3, 2, 1.0f);
                                                func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 5, 0, 3);
                                            } else if (temp_v1_6 == 0) {
                                                temp_v0_5 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC);
                                                if (temp_v0_5 > 0) {
                                                    M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) = (s32) (temp_v0_5 - 1);
                                                }
                                                func_PAL_L22_003A7930(arg0, 0xE, 0, 3, 2, 1.0f);
                                                func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 5, 0, 3);
                                            }
                                        }
                                    }
                                }
                    }
                    if ((M2C_FIELD(temp_s6, f32 *, 0x3DC) >= 38.0f) || (M2C_FIELD(temp_s6, f32 *, 0x3DC) <= 32.0f)) {
                        spC8 = 0;
                        if (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 32.0f) {
                            var_fp = 3;
                            var_f20 = math_fabs(M2C_FIELD(temp_s6, f32 *, 0x3DC) - 35.0f);
                            if ((u16) M2C_FIELD(temp_s6, u16 *, 0x3A4) >= 2U) {
                                spC8 = 1;
                                M2C_FIELD(temp_s6, u16 *, 0x352) = (u16) -(s32) M2C_FIELD(temp_s6, u16 *, 0x352);
                            }
                            var_v0_7 = 1;
                        } else {
                            var_fp = 2;
                            var_f20 = math_fabs(M2C_FIELD(temp_s6, f32 *, 0x3DC) - 35.0f);
                            temp_v0_6 = (s16) M2C_FIELD(temp_s6, u16 *, 0x3A4);

                            if ((temp_v0_6 != 0) && (temp_v0_6 != 2)) {
                                spC8 = 1;
                                M2C_FIELD(temp_s6, u16 *, 0x352) = (u16) -(s32) M2C_FIELD(temp_s6, u16 *, 0x352);
                            }
                            var_v0_7 = 2;
                        }
                        M2C_FIELD(temp_s6, u16 *, 0x3A4) = var_v0_7;
                        if ((u16) M2C_FIELD(arg0, u16 *, 0x96) < 0x32) {
                            temp_s0_6 = (s32 *) g_ship_path_table[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]];
                            if (spC8 == 0) {
                                var_s3 = M2C_FIELD(temp_s6, s16 *, 0x356) + 1;
                                if (var_s3 >= *temp_s0_6) {
                                    var_s3 = -1;
                                    M2C_FIELD(temp_s6, u16 *, 0x352) = 1U;
                                } else {
                                    {
                                        s128 next = M2C_FIELD(((s8 *) temp_s0_6 + (var_s3 * 0x10)), s128 *, 0x10);
                                        scratch[0].q = next;
                                    }
                                    arena_push_point_out(&scratch[0].q, 8.0f);
                                }
                                var_s2 = M2C_FIELD(temp_s6, s16 *, 0x356) - 1;
                                if (var_s2 < 0) {
                                    var_s2 = -1;
                                    M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                } else {
                                    {
                                        s128 prev = M2C_FIELD(((s8 *) temp_s0_6 + (var_s2 * 0x10)), s128 *, 0x10);
                                        scratch[1].q = prev;
                                    }
                                    arena_push_point_out(&scratch[1].q, 8.0f);
                                }
                                if (var_s3 != -1) {
                                    FastVecSub(&scratch[3].q, &scratch[0].q, (arg0 + 0x10));
                                    FastVecSub(&scratch[4].q, (s128 *) (g_hero_state + 0x80), (arg0 + 0x10));
                                    scratch[2].f[0] = FastVecDot(&scratch[3].q, &scratch[4].q);
                                }
                                if (var_s2 != -1) {
                                    FastVecSub(&scratch[3].q, &scratch[1].q, (arg0 + 0x10));
                                    FastVecSub(&scratch[4].q, (s128 *) (g_hero_state + 0x80), (arg0 + 0x10));
                                    scratch[2].f[1] = FastVecDot(&scratch[3].q, &scratch[4].q);
                                }
                                if (var_fp == 3) {
                                    if ((var_s3 != -1) && (var_s2 != -1)) {
                                        if ((scratch[2].f[0] > scratch[2].f[1]) && (scratch[2].f[0] > 0.0f)) {
                                            M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                        }
                                    } else if ((var_s3 == -1) && (scratch[2].f[1] > 0.0f)) {
                                        M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                    } else if ((var_s2 == -1) && (scratch[2].f[0] > 0.0f)) {
                                        M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                    }
                                } else if (var_fp == 2) {
                                    if ((var_s3 != -1) && (var_s2 != -1)) {
                                        if (scratch[2].f[0] < scratch[2].f[1]) {
                                            M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                        } else {
                                            M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                        }
                                    } else if ((var_s3 == -1) && (scratch[2].f[1] < 0.0f)) {
                                        M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                    } else if ((var_s2 == -1) && (scratch[2].f[0] < 0.0f)) {
                                        M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                    }
                                }
                            }
                        }
                        if ((spC8 != 0) || (near = ((s128 *) (temp_s6 + 0x360)), fast_vec_dist((arg0 + 0x10), near) < 2.0f)) {
                            temp_a1_3 = M2C_FIELD(temp_s6, s16 *, 0x356) + M2C_FIELD(temp_s6, s16 *, 0x352);
                            temp_a2 = g_ship_path_table[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]];
                            if (temp_a1_3 < 0) {
                                WalkPathPickNext(arg0, var_fp, 1, M2C_FIELD(temp_a2, f32 *, 0x1C));
                            } else {
                                temp_v1_8 = M2C_FIELD(temp_a2, s32 *, 0);
                                if (temp_a1_3 >= temp_v1_8) {
                                    WalkPathPickNext(arg0, var_fp, 1, ((PathD708 *) temp_a2)->points[temp_v1_8 - 1].f[3]);
                                } else {
                                    M2C_FIELD(temp_s6, s16 *, 0x356) = temp_a1_3;
                                }
                            }
                            *((s128 *) (temp_s6 + 0x360)) = M2C_FIELD(((M2C_FIELD(temp_s6, s16 *, 0x356) * 0x10) + g_ship_path_table[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]]), s128 *, 0x10);
                            arena_push_point_out(((s128 *) (temp_s6 + 0x360)), 8.0f);
                        } else {
                            FastVecSub(&scratch[0].q, near, (arg0 + 0x10));
                            var_f20 = var_f20 * 0.0625f;
                            if (var_f20 > 0.5f) {
                                var_f20 = 0.5f;
                            }
                            vec_scale_to_length(&scratch[0].q, &scratch[0].q, var_f20);
                            FastVecAdd((arg0 + 0x10), (arg0 + 0x10), &scratch[0].q);
                            arena_push_point_out((arg0 + 0x10), 8.0f);
                            M2C_FIELD(temp_s6, s32 *, 0x3E8) = 0;
                        }
                    }
                    math_steer_along_direction(arg0, temp_s6 + 0x3E4, temp_s6 + 0x3E8, var_s5, g_space_ship_steer_param_a, g_space_ship_steer_param_b, -1.0f);
                    break;
                case 36:                            /* switch 2 */
                    if (gravity_get_center_distance((arg0 + 0x10)) <= g_planet_radius) {
                        moby_set_state(arg0, 5, 0);
                        M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
                        M2C_FIELD(temp_s6, f32 *, 0x3E4) = M2C_FIELD(temp_s6, f32 *, 0x3E8) = 0.0f;
                    } else {
                        spC4 = gravity_get_center_distance((arg0 + 0x10)) - g_planet_radius;
                        scratch[1].q = *(s128 *)(arg0 + 0x10);
                        arena_push_point_out(&scratch[1].q, 0.0f);
                        FastVecSub(&scratch[0].q, &scratch[1].q, (arg0 + 0x10));
                        math_step_value_toward_target(&spC4, temp_s6 + 0x3A8, 0.0f, 0.016f, 0.016f, 0.40000004f);
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, -M2C_FIELD(temp_s6, f32 *, 0x3A8));
                        FastVecAdd((arg0 + 0x10), (arg0 + 0x10), &scratch[0].q);
                    }
                    break;
                case 30:                            /* switch 2 */
                    if (M2C_FIELD(arg0, u8 *, 0x20) == 0x1E) {
                        if ((M2C_FIELD(temp_s6, s32 *, 0x3D0) != 0) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                            temp_f1_7 = M2C_FIELD(temp_s6, f32 *, 0x3DC);
                            if (temp_f1_7 < g_space_ship_threshold) {
                                if ((math_random_int_below(5) == 0) && (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0)) {
                                    moby_set_state(arg0, 0x21, 5);
                                    M2C_FIELD(temp_s6, s16 *, 0x3A6) = 3;
                                } else {
                                    func_PAL_L22_003A7930(arg0, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                                    moby_set_state(arg0, 0x1F, 4);
                                }
                            } else if (temp_f1_7 < 33.0f) {
                                var_s1_2 = 0;
                                var_s0 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0;
                                if (M2C_FIELD(temp_s6, s16 *, 0x41E) > 0) {
                                    var_s1_2 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0;
                                }
                                if ((var_s0 != 0) && (var_s1_2 != 0)) {
                                    if (math_random_int_below(2) != 0) {
                                        var_s0 = 0;
                                    } else {
                                        var_s1_2 = 0;
                                    }
                                }
                                if (var_s0 != 0) {
                                    temp_a1_4 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8);
                                    if (temp_a1_4 >= 0x32) {
                                        M2C_FIELD(temp_s6, s16 *, 0x430) = (s16) ((u16) M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) - math_random_int_below(0x23));
                                    } else {
                                        if (temp_a1_4 >= 3) {
                                            M2C_FIELD(temp_s6, s16 *, 0x430) = (s16) math_random_int_below(temp_a1_4 / 2);
                                        } else {
                                            M2C_FIELD(temp_s6, s16 *, 0x430) = 1;
                                        }
                                    }
                                    if (math_random_int_below(4) != 0) {
                                        moby_set_state(arg0, 0x20, 4);
                                    } else {
                                        moby_set_state(arg0, 0x21, 5);
                                        M2C_FIELD(temp_s6, s16 *, 0x3A6) = 1;
                                    }
                                } else if (var_s1_2 != 0) {
                                    moby_set_state(arg0, 0x21, 5);
                                    M2C_FIELD(temp_s6, s16 *, 0x3A6) = 0;
                                } else {
                                    moby_set_state(arg0, 0x12, 9);
                                }
                            } else {
                                WalkPathUpdate_pal(arg0);
                            }
                        } else {
                            WalkPathUpdate_pal(arg0);
                        }
                    }
                    break;
                case 1:                             /* switch 2 */
                    if (g_space_ship_timer < 0xC8) {
                        moby_check_target_point_from_offset(arg0, (s128 *) (g_hero_state + 0x80));
                        if (flag_set_first_pending(arg0) != 0) {
                            func_PAL_L22_003A7930(arg0, 0, 0, 0, 3, 1.0f);
                            func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 7, 0, 0);
                        }
                        if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                            moby_call_helper_with_blocks_pal(arg0);
                        }
                    }
                    break;
                case 2:                             /* switch 2 */
                    moby_check_target_point_from_offset(arg0, (s128 *) (g_hero_state + 0x80));
                    if (flag_set_first_pending(arg0) != 0) {
                        func_PAL_L22_003A7930(arg0, 0, 0, 3, 3, 1.0f);
                        func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 4, 0, 3);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) {
                        func_PAL_L22_003A7930(arg0, 0, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = (s16) (math_random_int_below(7) + 0x16);
                    }
                    FastDecTimer((s32) (temp_s6 + 0x384));
                    if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                        moby_call_helper_with_blocks_pal(arg0);
                    }
                    break;
                case 3:                             /* switch 2 */
                    moby_check_target_point_from_offset(arg0, (s128 *) (g_hero_state + 0x80));
                    if (flag_set_first_pending(arg0) != 0) {
                        func_PAL_L22_003A7930(arg0, 0, 0, 3, 3, 1.0f);
                        func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 4, 0, 3);
                    }
                    if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x77) {
                        moby_set_state(arg0, 0x12, 9);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) {
                        func_PAL_L22_003A7930(arg0, 0, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = (s16) (math_random_int_below(7) + 0x16);
                    }
                    FastDecTimer((s32) (temp_s6 + 0x384));
                    if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                        moby_call_helper_with_blocks_pal(arg0);
                    }
                    break;
                case 4:                             /* switch 2 */
                    if (flag_set_first_pending(arg0) != 0) {
                        func_PAL_L22_003A7930(arg0, 0, 0, 3, 3, 1.0f);
                        func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 4, 0, 3);
                    }
                    if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x4B1U) {
                        moby_set_state(arg0, 0x12, 9);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) {
                        func_PAL_L22_003A7930(arg0, 0, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = (s16) (math_random_int_below(7) + 0x16);
                    }
                    FastDecTimer((s32) (temp_s6 + 0x384));
                    if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                        moby_call_helper_with_blocks_pal(arg0);
                    }
                    break;
                case 37:                            /* switch 2 */
                    break;
                }
                temp_a0_8 = M2C_FIELD(temp_s6, void **, 0x388);

                if (temp_a0_8 == NULL) {
                    M2C_FIELD(temp_s6, void **, 0x388) = effect_create_attached(arg0, (arg0 + 0x10));
                } else {
                    moby_store_position_private(temp_a0_8, (arg0 + 0x10));
                }
                M2C_FIELD(temp_s6, f32 *, 0x38C) = moby_get_anim_value(arg0);
                M2C_FIELD(temp_s6, f32 *, 0x44C) = moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440));
                space_ship_align_parts_at_end(arg0);
                pickup_update_spawned(arg0);
                moby_update_timed(arg0);
                func_PAL_L22_003A7FF0(arg0);
                if (M2C_FIELD(temp_s6, s16 *, 0x350) == 3) {
                if ((list_has_key((s32) arg0, (s32) M2C_FIELD(temp_s6, s16 *, 0x354)) != 0) && ((u32) (M2C_FIELD(arg0, u8 *, 0x43) - 0xB) < 2U)) {
                    temp_a0_9 = M2C_FIELD(temp_s6, s32 *, 0x440);
                    temp_v1_9 = M2C_FIELD(temp_a0_9, u8 *, 0x43);
                    switch (temp_v1_9) {
                    case 0xA:
                        if ((moby_get_anim_value((void *) temp_a0_9) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 3, 4.0f, 50.0f, 0x8B0000, 0.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), u8 *, 0x60) & 2) {
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                            func_PAL_L22_003A7930(arg0, 9, 0, 3, 2, 1.0f);
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 1;
                        }
                        break;
                    case 9:
                        if ((moby_get_anim_value((void *) temp_a0_9) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 4, 4.0f, 50.0f, 0x8B0000, 0.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), u8 *, 0x60) & 2) {
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                            func_PAL_L22_003A7930(arg0, 0xA, 0, 3, 2, 1.0f);
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 1;
                        }
                        break;
                    default:
                        M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                        func_PAL_L22_003A7930(arg0, 9, 0, 3, 2, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x34C) = 1;
                        break;
                    }
                    M2C_FIELD(temp_s6, s16 *, 0x43A) = 1;
                } else if ((M2C_FIELD(temp_s6, s16 *, 0x43A) != 0) && (M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), u8 *, 0x60) & 2)) {
                    M2C_FIELD(temp_s6, s16 *, 0x43A) = 0;
                    M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                    frame = moby_get_anim_value(arg0);
                    func_PAL_L22_003A7930(arg0, (s32) M2C_FIELD(arg0, u8 *, 0x43), (s32) frame, 3, 2, 1.0f);
                }
                } else {
                    M2C_FIELD(temp_s6, s16 *, 0x43A) = 0;
                    M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                }
                temp_a0_10 = ((VarsD708 *) temp_s6)->p448;
                if (M2C_FIELD(temp_a0_10, u8 *, 0x60) & 2) {
                    temp_v1_10 = M2C_FIELD(arg0, u8 *, 0x95);
                    if ((u32) (temp_v1_10 - 4) >= 2U) {
                        temp_v1_11 = temp_v1_10 & 0xFF;
                        if ((temp_v1_11 != 8) && (temp_v1_11 != 1) && (temp_v1_11 != 2) && (M2C_FIELD(arg0, u8 *, 0x20) != 0x26)) {
                            if (math_random_int_below(5) != 0) {
                                func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 0, 0, 0x8);
                            } else {
                                func_PAL_002A7E68(((VarsD708 *) temp_s6)->p448, 7, 0, 0x8);
                            }
                        }
                    }
                } else if ((M2C_FIELD(temp_a0_10, u8 *, 0x43) == 6) && (M2C_FIELD(arg0, u8 *, 0x95) != 8) && (M2C_FIELD(arg0, u8 *, 0x20) != 0x26)) {
                    func_PAL_002A7E68(temp_a0_10, 7, 0, 0x8);
                }
                if ((u32) (M2C_FIELD(arg0, u8 *, 0x43) - 0xB) < 2U) {
                    s128 *d = &scratch[0].q;
                    qcopy(d, (s128 *)(arg0 + 0x10));
                    vec_scale_to_length(&scratch[1].q, temp_s6 + 0x200, 12.0f);
                    FastVecAdd(&scratch[1].q, &scratch[1].q, d);
                    if (CollLine(d, &scratch[1].q, 0x12, 0, 0) != 0) {
                        *(s128 *)(arg0 + 0x10) = g_spawn_point;
                    }
                }
                if (M2C_FIELD(arg0, u8 *, 0x20) != 0x26) {
                    temp_f1_8 = (f32) ((s16) M2C_FIELD(temp_s6, s16 *, 0x24) / 3);
                    temp_f0 = M2C_FIELD(temp_s6, f32 *, 0x20);
                    if (temp_f0 < temp_f1_8) {
                        if (g_space_ship_blended_value == 0) {
                            {
                                f32 ratio = temp_f0 / (f32) ((s16) M2C_FIELD(temp_s6, s16 *, 0x24) / 3);
                                g_space_ship_blended_value = g_space_ship_value_min + (s32) ((f32) (g_space_ship_value_max - g_space_ship_value_min) * ratio);
                            }
                            if (math_random_int_below(2) != 0) {
                                func_PAL_L22_003A99D8((s32) arg0, math_random_int_below(4), 0, g_space_ship_scatter_param);
                            } else {
                                func_PAL_L22_003A99D8(M2C_FIELD(temp_s6, s32 *, 0x440), math_random_int_below(6), 0, g_space_ship_scatter_param);
                            }
                        } else {
                            math_fast_float_d(&g_space_ship_blended_value);
                        }
                    }
                }
        }
    }
}
