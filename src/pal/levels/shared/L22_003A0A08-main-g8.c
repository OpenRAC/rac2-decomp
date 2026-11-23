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
extern void anim_start_blended_pal(void *, int, int, int);
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
extern int math_is_value_within_step_pal(void *, float);
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
extern int actuator_play_pattern(int);
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
extern int hero_l22_set_action_pal(int, int);
extern void math_steer_along_direction(void *, void *, void *, void *, float, float, float);
extern void moby_update_timed(void *);
extern void arena_push_point_out(void *, float);
extern void table_decrement_timer(void);
extern void lane_store_nearest_point_as_current(void *, int);
extern void lane_find_nearest_point(void *, void *, void *, int);
extern void orbit_update_pal(void *, int, int, int, int, float);
extern void space_ship_run_attached_part_effect(void *, int, int, int, int);
extern int list_has_key(int, int);
extern void lane_find_point_ahead_of_ship(void *);
extern int space_ship_is_aligned_with_target_pal(void *);
extern void keyed_object_place(void *, void *, int);
extern void player_slot_clear_object(int);
extern void * effect_create_attached(void *, void *);
extern void space_ship_init_and_update_pal(s8 *);
extern void WalkPathUpdate_pal(s8 *);
extern s32 WalkPathIsClear(s8 *, s8 *, s128 *);
extern void WalkPathPickNext(s8 *, s32, s32, f32);
extern void pickup_update_spawned(s8 *);
extern s32 pickup_find_nearest_needed(s8 *, s128 *);
extern void space_ship_align_parts_at_end(s8 *);
extern void space_ship_pick_next_lane_to_check(s8 *);
extern void space_ship_tilt_attached_part_pal(s8 *);
extern void part_spray_thruster_pal(s8 *, s32, s32);
extern void stat_restore_random(s8 *);
extern void part_spawn_scatter_pal(s32, s32, s32, f32);
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
/* Updates the space ship moby each frame: flight, boosting, pickups, path following and
 * collisions. (PAL: 50 Hz timings) */
void space_ship_update_pal(s8 *moby) {
    /* The two matrices and the collision record reuse these eight vectors.
     * Component stores must address their vectors, not unrelated scalar locals. */
    union {
        ScratchD708 vectors[8];
        struct { FirstD708 first; MatrixD708 second; } pair;
        struct { ScratchD708 rotation; MatrixD708 basis; } shifted;
        struct { MatrixD708 basis; ScratchD708 rotation; QueryD708 query; } collision;
    } workspace;
#define scratch workspace.vectors
    ScratchD708 work_vec_a;
    ScratchD708 work_vec_b;
    s32 work_int0;
    f32 work_float;
    s32 work_int1;
    s32 **ptr1;
    s32 **ptr2;
    f32 flt1;
    f32 flt2;
    f32 flt3;
    f32 flt4;
    f32 flt5;
    f32 flt6;
    f32 flt7;
    f32 flt8;
    f32 flt9;
    f32 flt10;
    f32 flt11;
    f32 flt12;
    f32 flt13;
    f32 flt14;
    f32 flt15;
    f32 flt16;
    f32 flt17;
    s128 *vec1;
    s128 *vec2;
    s128 *vec3;
    s128 *vec4;
    s128 *vec5;
    s128 *vec6;
    s128 vec7;
    u8 *base9;
    u8 *base10;
    f32 frame;
    void *hit;
    s32 mode3A6;
    f32 len8;
    s32 saved398;
    u8 *game;
    u8 *game10;
    s32 val1;
    f32 flt18;
    s16 val2;
    s16 val3;
    s32 val4;
    s16 val5;
    s16 val6;
    s16 val7;
    s32 *ptr3;
    s32 val8;
    s32 val9;
    s32 val10;
    s32 val11;
    s32 val12;
    s32 val13;
    s32 val14;
    s32 val15;
    s32 val16;
    s32 val17;
    s32 val18;
    s32 val19;
    s32 val20;
    s32 val21;
    s32 val22;
    s32 val23;
    s32 val24;
    s32 val25;
    s8 **paths;
    s32 val26;
    s32 val27;
    s32 val28;
    s32 val29;
    s32 val30;
    s32 val31;
    s32 val32;
    s32 val33;
    s32 val34;
    s8 *near;
    s32 val35;
    s32 val36;
    s32 val37;
    s32 val38;
    s32 val39;
    s32 val40;
    s32 val41;
    s32 val42;
    s8 *ptr4;
    s8 *pos_ptr;
    s8 *ptr5;
    s8 *ptr6;
    u16 val43;
    u16 val44;
    u16 val45;
    u16 val46;
    u16 val47;
    u16 val48;
    u16 val49;
    u16 val50;
    u8 val51;
    u8 val52;
    s32 val53;
    u8 val54;
    s32 val55;
    u8 val56;
    u8 val57;
    u8 val58;
    void *ptr7;
    void *ptr8;
    void *ptr9;
    void *ptr10;
    void *ptr11;
    void *ptr12;
    void *ptr13;
    void *ptr14;
    void *ptr15;
    void *ptr16;
    void *ptr17;
    void *ptr18;
    void *probe;
    void *ptr19;
    void *ptr20;
    void *ptr21;
    void *vars;
    void *ptr22;
    void *ptr23;
    void *ptr24;
    void *ptr25;
    void *ptr26;
    void *ptr27;

    if (g_space_ship_init_flag == 0) {
        g_pad_held_flags = 0;
        if ((g_space_ship_target_moby == NULL) && (g_hero_l22_mode_state != 2) && (M2C_FIELD(moby, u8 *, 0x20) == 0)) {
            for (ptr26 = g_trigger_event_list_head; ptr26 != NULL; ptr26 = M2C_FIELD(ptr26, void **, 0x28)) {
                if (M2C_FIELD(ptr26, s16 *, 0xAA) == 0xF6E) {
                    g_space_ship_target_moby = ptr26;
                    M2C_FIELD(ptr26, u8 *, 0x30) = 0xFF;
                    ptr22 = M2C_FIELD(g_space_ship_target_moby, void **, 0x68);
                    M2C_FIELD(ptr22, s8 *, 8) = 0;
                    M2C_FIELD(ptr22, s8 *, 0xA) = 0;
                    M2C_FIELD(ptr22, s8 *, 0xC) = -1;
                }
            }
            M2C_FIELD(M2C_FIELD(g_space_ship_target_moby, void **, 0x68), s8 *, 8) = 0;
            moby_set_flag_bit(g_space_ship_target_moby, 1);
            moby_set_state(moby, 0x27, 0xB);
            FadeToBlack(0);
            M2C_FIELD(moby, u16 *, 0x34) = (u16) (M2C_FIELD(moby, u16 *, 0x34) | 0x41);
            return;
        }
        if (M2C_FIELD(moby, u8 *, 0x20) == 0x27) {
            for (ptr27 = g_trigger_event_list_head; ptr27 != NULL; ptr27 = M2C_FIELD(ptr27, void **, 0x28)) {
                if (M2C_FIELD(ptr27, s16 *, 0xAA) == 0xF6E) {
                    return;
                }
            }
            g_space_ship_target_moby = NULL;
            g_space_ship_init_flag = 1;
            moby_set_state(moby, 0, -1);
            M2C_FIELD(moby, u16 *, 0x34) = (u16) (M2C_FIELD(moby, u16 *, 0x34) & 0xFFBE);
            return;
        }
    }
    {
        vars = M2C_FIELD(moby, void **, 0x68);
        math_fast_float_d(&g_space_ship_boost_timer);
        if (g_space_ship_boost_timer != 0) {
            M2C_FIELD(moby, u8 *, 0xA8) = 0xFF;
        }
        probe = part_find_owned_effect_slot(moby, 0x30000, 1);
        space_ship_init_and_update_pal(moby);
        if (g_space_ship_timer >= 0xC9) {
            space_ship_align_parts_at_end(moby);
        } else {
            if (g_space_ship_timer == 0) {
                g_space_ship_difficulty += 1;
            }
            if (M2C_FIELD(moby, u8 *, 0x20) != 0) {
                {
                    f32 x = M2C_FIELD(vars, f32 *, 0x330);
                    f32 y = M2C_FIELD(vars, f32 *, 0x334);
                    f32 z = M2C_FIELD(vars, f32 *, 0x338);
                    f32 w = M2C_FIELD(vars, f32 *, 0x33C);
                    g_space_ship_param_x = x;
                    g_space_ship_param_y = y;
                    g_space_ship_param_z = z;
                    g_space_ship_param_w = w;
                }
                space_ship_pick_next_lane_to_check(moby);
                if (g_space_ship_pending_flag != 0) {
                    vec_scale_to_length(&scratch[3].q, moby + 0xC0, -10.0f);
                    scratch[3].f[3] = 5627.925f;
                    make_hit_descriptor((s32) &workspace.pair.first.query_view.query, g_hero_moby, 0x10000, 20.0f, (s32) &scratch[3].q);
                    QueueMobyImpact(moby, &workspace.pair.first.query_view.query);
                    g_space_ship_pending_flag = 0;
                }
            }
            val16 = (s32) M2C_FIELD(vars, f32 *, 0x20);
            g_space_ship_active_flag = 0;
            M2C_FIELD(vars, s16 *, 0x41C) = (val16 < ((s32) (g_space_ship_max_health * 2) / 3)) && (((s32) g_space_ship_max_health / 6) < val16);
            if ((probe != NULL) && (M2C_FIELD(probe, s32 *, 0x20) != g_hero_moby)) {
                M2C_FIELD(vars, s32 *, 0x4EC) = 0;
            }
            if (((u32) (M2C_FIELD(moby, u8 *, 0x95) - 4) < 2U) && (((u32) (M2C_FIELD(moby, u8 *, 0x43) - 0xB) < 2U) == 0)) {
                val18 = moby_check_target_point_from_offset(moby, (s128 *) (g_hero_state + 0x80));
                M2C_FIELD(vars, s32 *, 0x3D0) = val18;
            } else {
                FastVecSub(&scratch[0].q, (s128 *) (g_hero_state + 0x80), moby + 0x10);
                flt5 = moby_measure_step_angle(moby, &scratch[0].q, NULL);
                M2C_FIELD(vars, s32 *, 0x3D4) = 0;
                M2C_FIELD(vars, s32 *, 0x3D0) = 0;
                if (flt5 <= 0.7853982f) {
                    M2C_FIELD(vars, s32 *, 0x3D0) = 1;
                }
                if (flt5 <= 1.0471976f) {
                    M2C_FIELD(vars, s32 *, 0x3D4) = 1;
                }
            }
            if ((probe != NULL) && (M2C_FIELD(vars, s32 *, 0x3D0) == 0)) {
                M2C_FIELD(vars, s16 *, 0x350) = 0;
            }
            vec2 = (s128 *) (g_hero_state + 0x80);
            ptr18 = vars + 0x3F0;
            M2C_FIELD(vars, s128 *, 0x3F0) = (s128) M2C_FIELD(vec2, s128 *, 0);
            ptr15 = vars + 0x400;
            arena_push_point_out(ptr18, 0.0f);
            M2C_FIELD(vars, s128 *, 0x400) = *(s128 *)(moby + 0x10);
            arena_push_point_out(ptr15, 0.0f);
            M2C_FIELD(vars, f32 *, 0x410) = gravity_get_center_distance((moby + 0x10));
            M2C_FIELD(vars, f32 *, 0x414) = gravity_get_center_distance(M2C_FIELD(vec2, s32 *, 0x2210) + 0x10);
            M2C_FIELD(vars, f32 *, 0x3DC) = fast_vec_dist(vec2, (moby + 0x10));
            M2C_FIELD(vars, f32 *, 0x3E0) = fast_vec_dist(ptr18, ptr15);
            if (M2C_FIELD(vars, f32 *, 0x3DC) < 50.0f) {
                M2C_FIELD(vars, s32 *, 0x3D8) = WalkPathIsClear(moby, (moby + 0x10), vec2);
            } else {
                M2C_FIELD(vars, s32 *, 0x3D8) = 0;
            }
            if (M2C_FIELD(vars, s32 *, 0x344) != 0) {
                game = g_hero_state;
                M2C_FIELD(game, s16 *, 0x1DC) = 0x7D00;
                moby_set_state(moby, 0x26, 0xA);
                M2C_FIELD(game, s32 *, 0x2294) = 0;
                cancel_hero_item_animation_pal();
                release_moby_animation_slot(M2C_FIELD(game, void **, 0x2290), game + 0x1870);
                M2C_FIELD(game, s32 *, 0x187C) = 0;
                hero_l22_set_action_pal(0, 1);
                M2C_FIELD(vars, s32 *, 0x344) = 0;
            }
            val43 = M2C_FIELD(vars, u16 *, 0x41E);
            if ((M2C_FIELD(vars, s16 *, 0x41E) == 0) && (M2C_FIELD(vars, f32 *, 0x20) < (f32) ((s32) (g_space_ship_max_health * 2) / 3)) && (M2C_FIELD(vars, s16 *, 0x468) == 0)) {
                M2C_FIELD(vars, s16 *, 0x41E) = 1;
                g_space_ship_mode = 1;
                g_space_ship_active_flag = 1;
                M2C_FIELD(vars, s16 *, 0x468) = 1;
            } else if (((s16) val43 == 1) && (M2C_FIELD(vars, f32 *, 0x20) < (f32) ((s32) g_space_ship_max_health / 3)) && (M2C_FIELD(vars, s16 *, 0x46A) == 0)) {
                saved398 = g_space_ship_saved_word;
                M2C_FIELD(vars, s16 *, 0x41E) = 2;
                g_space_ship_mode = 2;
                {
                    s32 one = (s16) val43;
                    g_space_ship_active_flag = one;
                    M2C_FIELD(vars, s32 *, 0x464) = (saved398 * 5 + 2) / 6;
                    M2C_FIELD(vars, s16 *, 0x46A) = one;
                }
            }
            val11 = M2C_FIELD(vars, s32 *, 0x440);
            coll_sweep_from_object(val11, val11 + 0x10, 0x04000000, 5.4f, 1.0f, 1.0f, 0, 1, 0);
            val54 = M2C_FIELD(moby, u8 *, 0x95);
            switch (val54) {                    /* switch 1 */
            case 0:                                 /* switch 1 */
                if ((M2C_FIELD(vars, f32 *, 0x3DC) < 35.0f) && (M2C_FIELD(vars, s32 *, 0x3D4) != 0) && (M2C_FIELD(vars, s32 *, 0x3D8) != 0)) {
                    if ((M2C_FIELD(vars, s32 *, 0x418) != 0) && (M2C_FIELD(moby, u8 *, 0x20) != 0xF)) {
                        moby_set_state(moby, 6, 4);
                    } else if ((M2C_FIELD(vars, s32 *, 0x464) != 0) && (M2C_FIELD(vars, s16 *, 0x41E) == 2)) {
                        moby_set_state(moby, 0x13, 9);
                    } else if (M2C_FIELD(vars, s16 *, 0x41C) == 0) {
                        if ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0)) {
                            moby_set_state(moby, 0x1D, 3);
                        } else if (math_random_int_below(2) == 0) {
                            moby_set_state(moby, 0x12, 9);
                        } else if (M2C_FIELD(vars, s16 *, 0x41E) == 0) {
                            moby_set_state(moby, 0x1C, 3);
                        } else {
                            moby_set_state(moby, 0x12, 9);
                        }
                    } else if (M2C_FIELD(vars, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6)) {
                        moby_set_state(moby, 0x12, 9);
                    } else if ((M2C_FIELD(vars, s16 *, 0x32A) / 2 < M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC)) || (M2C_FIELD(vars, s16 *, 0x32E) / 2 < M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8))) {
                        moby_set_state(moby, 0x1D, 3);
                    } else if ((math_random_int_below(2) == 0) && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0))) {
                        moby_set_state(moby, 0x1D, 3);
                    } else if ((math_random_int_below(2) != 0) && (M2C_FIELD(vars, s16 *, 0x41E) == 0)) {
                        moby_set_state(moby, 0x1C, 3);
                    } else if (M2C_FIELD(vars, f32 *, 0x3DC) < 55.0f) {
                        moby_set_state(moby, 0x12, 9);
                    }
                }
                break;
            case 9:                                 /* switch 1 */
                if (((u16) M2C_FIELD(moby, u16 *, 0x96) >= 0x26) && (space_ship_is_aligned_with_target_pal(moby) != 0)) {
                    if ((M2C_FIELD(vars, s16 *, 0x41E) != 2) || (M2C_FIELD(vars, s32 *, 0x464) == 0)) {
                        orbit_update_pal(moby, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                        moby_set_state(moby, 0x1F, 4);
                    }
                }
                break;
            case 3:                                 /* switch 1 */
                if (M2C_FIELD(vars, s32 *, 0x418) != 0) {
                    moby_set_state(moby, 6, 4);
                } else if (M2C_FIELD(vars, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6)) {
                    moby_set_state(moby, 0x12, 9);
                }
                break;
            case 4:                                 /* switch 1 */
                if (M2C_FIELD(vars, s32 *, 0x418) != 0) {
                    moby_set_state(moby, 6, 4);
                } else if (((M2C_FIELD(vars, s32 *, 0x464) != 0) && (M2C_FIELD(vars, s16 *, 0x41E) == 2))
                        || (M2C_FIELD(vars, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6))
                        || ((g_platform_mode >= 0x12) && (M2C_FIELD(moby, u8 *, 0x20) == 0x1E))) {
                    moby_set_state(moby, 0x12, 9);
                }
                break;
            case 6:                                 /* switch 1 */
                if (M2C_FIELD(vars, s32 *, 0x418) == 0) {
                    moby_set_state(moby, 0x1E, 4);
                }
                break;
            case 5:                                 /* switch 1 */
                part_spray_thruster_pal(moby, 2, 1);
                part_spray_thruster_pal(moby, 3, 0);
                break;
            case 8:                                 /* switch 1 */
                len8 = FastVecLength(((s128 *) (vars + 0xE0)));
                if (len8 > 0.0f) {
                    vec7 = 0;
                    if (M2C_FIELD(vars, f32 *, 0x410) < g_planet_radius) {
                        arena_push_point_out((moby + 0x10), 0.0f);
                        vec7 = 0;
                    }
                    scratch[2].q = vec7;
                    scratch[2].f[2] = M2C_FIELD(vars, f32 *, 0x94);
                    vec7 = scratch[2].q;
                    scratch[1].q = vec7;
                    matrix_mul_vec3(&scratch[1].q, &scratch[1].q, moby + 0xC0);
                    FastVecAdd(&scratch[1].q, &scratch[1].q, (moby + 0x10));
                    vec_scale_to_length(&scratch[0].q, ((s128 *) (vars + 0xE0)), 4.0f);
                    FastVecAdd(&scratch[1].q, &scratch[1].q, &scratch[0].q);
                    coll_sweep_from_object((s32) moby, (s32) &scratch[1].q, 0x90000, 5.0f, 100.0f, 0.0f, 0, 1, 0);
                }
                if (flag_set_second_pending(moby) != 0) {
                    M2C_FIELD(vars, s16 *, 0x26) = 0x19;
                    if (probe != NULL) {
                        if ((FastVecLength(((s128 *) (vars + 0xE0))) > 0.0f) && ((M2C_FIELD(vars, f32 *, 0x20) - M2C_FIELD(probe, f32 *, 0x2C)) <= 0.0f)) {
                            vec_scale_to_length(((s128 *) (vars + 0xE0)), ((s128 *) (vars + 0xE0)), 0.6f);
                        }
                        if (M2C_FIELD(probe, f32 *, 0x2C) == 50.0f) {
                            snd_start_in_slot(0x13, 0, 0);
                        }
                        if ((M2C_FIELD(g_hero_moby, u8 *, 0x43) == 4) && (M2C_FIELD(probe, s32 *, 0x20) == g_hero_moby)) {
                            FastVecSub(&scratch[0].q, vars + 0x400, vars + 0x3F0);
                            vec_scale_to_length(((s128 *) (vars + 0xE0)), &scratch[0].q, g_space_ship_move_length);
                            SpawnExplosion_pal(M2C_FIELD(vars, s32 *, 0x440) + 0x10, 1, 0xA, 0xA, 0xA, 0x14, 0x32, 0, 1.2f, 20.0f, 0, 1, 0, 0);
                        }
                    }
                    orbit_update_pal(moby, (s32) M2C_FIELD(moby, u8 *, 0x43), 0, 3, 2, 1.0f);
                    anim_start_blended_pal(((VarsD708 *) vars)->p448, 6, 0, 3);
                    M2C_FIELD(M2C_FIELD(vars, s32 *, 0x440), f32 *, 0x48) = 0.9f;
                    M2C_FIELD(moby, f32 *, 0x48) = 0.9f;
                    val51 = M2C_FIELD(moby, u8 *, 0x43);
                    if ((val51 == 4) || (val51 == 8)) {
                        player_slot_clear_object((s32) moby);
                    }
                } else if ((M2C_FIELD(((VarsD708 *) vars)->p448, u8 *, 0x60) & 2) && (math_random_int_below(3) == 0)) {
                    anim_start_blended_pal(((VarsD708 *) vars)->p448, 7, 0, 3);
                }
                if (M2C_FIELD(vars, s16 *, 0x43A) == 0) {
                    M2C_FIELD(vars, s16 *, 0x350) = 0;
                }
                M2C_FIELD(vars, f32 *, 0x3E4) = M2C_FIELD(vars, f32 *, 0x3E8) = 0.0f;
                val21 = moby_dispatch_action_by_kind(moby, vars + 0x60);
                if (val21 & 1) {
                    M2C_FIELD(vars, s32 *, 0x344) = 1;
                } else if (val21 & 2) {
                    M2C_FIELD(vars, s32 *, 0x37C) = 0xc8;
                    moby_set_state(moby, 5, 0);
                    orbit_update_pal(moby, 0, 0, 3, 3, 1.0f);
                }
                goto block_184;
            case 10:                                /* switch 1 */
                game10 = g_hero_state;
                M2C_FIELD(game10, s16 *, 0x1E0) = 0x8;
                ptr23 = M2C_FIELD(vars, void **, 0x388);
                M2C_FIELD(ptr23, u16 *, 0x34) = (u16) (M2C_FIELD(ptr23, u16 *, 0x34) | 0x41);
                if (flag_set_first_pending(moby) != 0) {
                    if ((M2C_FIELD(vars, s32 *, 0x4EC) != 0) && (g_item_enabled_flags[8] == 0)) {
                        g_item_enabled_flags[8] = 1;
                        snd_play_from_global_bank(1, 0, NULL);
                        value_set_entry_by_index_pal(0x1233, -1);
                        g_trigger_event_flag = 1;
                    }
                    FadeToBlack(g_space_ship_fade_time);
                    goto block_183;
                }
                val44 = M2C_FIELD(moby, u16 *, 0x96);
                val22 = (s32) g_space_ship_fade_time / 2;
                if (val22 < (s32) val44) {
                    if ((math_is_value_within_step_pal(moby, 27.0f) != 0) && ((M2C_FIELD(moby, u16 *, 0x34) ^ 1) & 1) && ((((s32) g_space_ship_fade_time / 2) - 4) < (s32) M2C_FIELD(moby, u16 *, 0x96))) {
                        coll_sweep_from_object((s32) moby, (s32) (moby + 0x10), 0x90000, 25.0f, 100.0f, 0.0f, 0, 1, 0);
                        moby_aim_at_target_offset_pal(moby, game10 + 0x80);

                        SetDeathBits_pal(moby, 0, 3);
                        part_spawn_explosion_with_sparks_pal(moby, (moby + 0x10), 2.0f, 7.0f, -1);
                        for (val36 = 0; val36 < 5; val36++) {
                            vec_random_direction(&scratch[0].q, g_space_ship_random_dir_a * 0.020000001f, g_space_ship_random_dir_b * 0.020000001f);
                            scratch[0].f[2] = math_fabs(scratch[0].f[2]) * g_space_ship_z_scale;
                            matrix_mul_vec3(&scratch[0].q, &scratch[0].q, M2C_FIELD(vars, s32 *, 0x440) + 0xC0);
                            val9 = M2C_FIELD(vars, s32 *, 0x440);
                            ptr1 = cam_moby_create_pal((void *) val9, 1, (s32) M2C_FIELD(val9, s16 *, 0xAA), val36, val9 + 0x10, val9 + 0xF0, &scratch[0].q, 0xFF, 30.0f, 15.0f);
                            *(s32 **)((s8 *)ptr1 + 0x64) = &g_ship_model_marker;
                        }
                        for (val37 = 0; val37 < 2; val37++) {
                            vec_random_direction(&scratch[0].q, g_space_ship_random_dir_a * 0.020000001f, g_space_ship_random_dir_b * 0.020000001f);
                            scratch[0].f[2] = math_fabs(scratch[0].f[2]) * g_space_ship_z_scale;
                            matrix_mul_vec3(&scratch[0].q, &scratch[0].q, ((void *) (moby + 0xC0)));
                            ptr2 = cam_moby_create_pal(moby, 1, (s32) M2C_FIELD(moby, s16 *, 0xAA), val37, (moby + 0x10), ((void *) (moby + 0xF0)), &scratch[0].q, 0xFF, 30.0f, 15.0f);
                            *(s32 **)((s8 *)ptr2 + 0x64) = &g_ship_model_marker;
                        }
                        SpawnExplosion_pal(M2C_FIELD(vars, s32 *, 0x440) + 0x10, 0, 0x73, 0x50, 0x46, 0x4E, 0x4B, 1, 7.5f, 20.0f, 1, 1, 0, 0);
                        SpawnExplosion_pal((moby + 0x10), 1, 0x2D, 0x28, 0x28, 0x28, 0x3A, 1, 3.0f, 20.0f, 1, 1, 0, 0);
                        M2C_FIELD(moby, u16 *, 0x34) = (u16) (M2C_FIELD(moby, u16 *, 0x34) | 0x41);
                        ptr8 = M2C_FIELD(vars, void **, 0x388);
                        M2C_FIELD(ptr8, u16 *, 0x34) = (u16) (M2C_FIELD(ptr8, u16 *, 0x34) | 0x41);
                        val24 = M2C_FIELD(vars, s32 *, 0x440);
                        M2C_FIELD(val24, u16 *, 0x34) = (u16) (M2C_FIELD(val24, u16 *, 0x34) | 0x41);
                        ptr9 = M2C_FIELD(vars, void **, 0x444);
                        M2C_FIELD(ptr9, u16 *, 0x34) = (u16) (M2C_FIELD(ptr9, u16 *, 0x34) | 0x41);
                        ptr10 = ((VarsD708 *) vars)->p448;
                        M2C_FIELD(ptr10, s128 *, 0x10) = *(s128 *)(moby + 0x10);
                        anim_start_blended_pal(ptr10, 6, 0, 3);
                        {
                            f32 v = g_space_ship_float_param_a;
                            M2C_FIELD(((VarsD708 *) vars)->p448, f32 *, 0x48) = 3.2f;
                            g_space_ship_speed_param = v;
                            arena_push_point_out(((VarsD708 *) vars)->p448 + 0x10, v);
                        }
                        goto block_183;
                    }
                    val48 = M2C_FIELD(moby, u16 *, 0x96);
                    if (val48 >= 0x12d) {
                        moby_mark_spawned(M2C_FIELD(vars, void **, 0x388));
                        M2C_FIELD(vars, void **, 0x388) = NULL;
                        moby_mark_spawned((void *) M2C_FIELD(vars, s32 *, 0x440));
                        M2C_FIELD(vars, s32 *, 0x440) = 0;
                        moby_mark_spawned(M2C_FIELD(vars, void **, 0x444));
                        M2C_FIELD(vars, void **, 0x444) = NULL;
                        moby_mark_spawned(((VarsD708 *) vars)->p448);
                        ((VarsD708 *) vars)->p448 = NULL;
                        level_store_value_pair_pal(0, 0);
                        g_space_ship_flag = 1;
                        level_set_dependent_value();
                        moby_mark_spawned(moby);
                        return;
                    } else {
                        if ((val48 >= 0xda) && (M2C_FIELD(moby, u16 *, 0x34) & 1) && (ptr11 = ((VarsD708 *) vars)->p448, (((M2C_FIELD(ptr11, u16 *, 0x34) ^ 1) & 1) != 0))) {
                            flt4 = g_space_ship_speed_param - g_space_ship_float_param_b;
                            g_space_ship_speed_param = flt4;
                            if (flt4 > 0.0f) {
                                arena_push_point_out(ptr11 + 0x10, flt4);
                                M2C_FIELD(((VarsD708 *) vars)->p448, f32 *, 0x48) = 3.2f;
                                func_PAL_002A0F68(((VarsD708 *) vars)->p448);
                                func_002A0F48(((VarsD708 *) vars)->p448);
                            } else {
                                if ((M2C_FIELD(ptr11, u16 *, 0x34) ^ 1) & 1) {
                                    FastVecScale(&scratch[0].q, ptr11 + 0xC0, 2.2f);
                                    FastVecAdd(&scratch[0].q, &scratch[0].q, ((VarsD708 *) vars)->p448 + 0x10);
                                    arena_push_point_out(&scratch[0].q, 0.5f);
                                    SpawnExplosion_pal(&scratch[0].q, 1, 0xA, 0xA, 0xA, 0xA, 0x14, 0, 0.9f, 20.0f, 0, 0, 0, 0);
                                    PlayMobySound(g_space_ship_sound_a, 0, moby);
                                    ptr24 = ((VarsD708 *) vars)->p448;
                                    M2C_FIELD(ptr24, u16 *, 0x34) = (u16) (M2C_FIELD(ptr24, u16 *, 0x34) | 0x41);
                                }
                            }
                        } else {
                            if (!(M2C_FIELD(moby, u16 *, 0x96) & 7) && ((M2C_FIELD(moby, u16 *, 0x34) ^ 1) & 1)) {
                                if (math_random_int_below(2) != 0) {
                                    moby_transform_joint_to_world((s32) moby, math_random_int_below(4), (s32) &scratch[0].q);
                                } else {
                                    moby_transform_joint_to_world(M2C_FIELD(vars, s32 *, 0x440), math_random_int_below(6), (s32) &scratch[0].q);
                                }
                                SpawnExplosion_pal(&scratch[0].q, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, math_random_float_range(1.0f, 1.9f), 20.0f, 0, 0, 0, 0);
                            }
                            if (!(M2C_FIELD(moby, u16 *, 0x96) & 0xF) && ((M2C_FIELD(moby, u16 *, 0x34) ^ 1) & 1)) {
                                PlayMobySound(g_space_ship_sound_b, 0, moby);
                            }
                        }
                        goto block_183;
                    }
                } else {
                    val19 = val22 - 4;
                    if (val44 == val19) {
                        FadeToBlack(1);
                        arena_push_point_out((moby + 0x10), 0.0f);
                        scratch[4].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0);
                        scratch[5].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x10);
                        scratch[6].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x20);
                        qzero_nc(&scratch[7].q);
                        mat_get_euler_angles(&workspace.pair.second, &scratch[0].q);
                        pos_ptr = (moby + 0x10);
                        SetCamera5Pose(g_tether_origin, &scratch[0].q, 1, 0, 0);
                        orbit_update_pal(moby, 0xE, 0, 3, 3, 0.6f);
                        M2C_FIELD(vars, f32 *, 0x138) = 0.012f;
                        FastVecSub(&scratch[7].q, vars + 0x3F0, pos_ptr);
                        vec_scale_to_length(&scratch[6].q, &scratch[7].q, -(g_space_ship_scale * 33.0f));
                        FastVecAdd(&scratch[6].q, &scratch[6].q, pos_ptr);
                        arena_push_point_out(&scratch[6].q, 2.0f);
                        vec_scale_to_length(&scratch[5].q, &scratch[7].q, -(g_space_ship_scale * 55.0f));
                        FastVecAdd(&scratch[5].q, &scratch[5].q, pos_ptr);
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
                    } else if (val19 < (s32) val44) {
                        scratch[1].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0);
                        scratch[2].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x10);
                        scratch[3].q = M2C_FIELD(g_space_ship_scratch_vectors, s128 *, 0x20);
                        qzero_nc(&scratch[4].q);
                        mat_get_euler_angles(&workspace.shifted.basis, &workspace.shifted.rotation);
                        SetCamera5Pose(g_tether_origin, &scratch[0].q, 1, 0, 0);
                        FastVecSub(&scratch[0].q, (moby + 0x10), g_tether_origin);
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, 1.0f);
                        scratch[2].q = M2C_FIELD(moby, s128 *, 0xE0);
                        qzero_nc(&scratch[3].q);
                        ptr19 = g_hero_state;
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, 1.0f);
                        vec_scale_to_length(&scratch[2].q, &scratch[2].q, 1.0f);
                        FastVecCross(&scratch[1].q, &scratch[0].q, &scratch[2].q);
                        vec_scale_to_length(&scratch[1].q, &scratch[1].q, 1.0f);
                        mat_get_euler_angles(&workspace.pair.first.matrix, &scratch[4].q);
                        cam_set_state_rotation(&scratch[4].q);
                        FadeToBlack(1);
                        part_init_effect_record(&workspace.collision.query, M2C_FIELD(ptr19, s32 *, 0x2290), 0xB0000, 50.0f);
                        scratch[6].b[8] = 7;
                        scratch[6].b[9] = 1;

                        scratch[6].h[5] = M2C_FIELD(M2C_FIELD(ptr19, s32 *, 0x2290), u16 *, 0xAA);
                        coll_sweep_from_object((s32) moby, (s32) g_tether_origin, 0x90000, 10.0f, 100.0f, 0.0f, 0, 1, 0);
                        ptr20 = g_tether_origin + 0x240;
                        CollLine(g_tether_origin, M2C_FIELD(vars, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        ptr21 = g_tether_origin + 0x250;
                        FastVecScale(&work_vec_a, M2C_FIELD(ptr19, s32 *, 0x2290) + 0xE0, 4.0f);
                        FastVecAdd(&work_vec_a, &work_vec_a, ptr19 + 0x80);
                        CollLine(&work_vec_a, M2C_FIELD(vars, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        flt13 = g_space_ship_scale * 6.875f;
                        flt14 = -flt13;
                        FastVecScale(&work_vec_b, ptr20, flt13);
                        FastVecAdd(&work_vec_b, &work_vec_b, g_tether_origin);
                        CollLine(&work_vec_b, M2C_FIELD(vars, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        FastVecScale(&work_vec_b, ptr20, flt14);
                        FastVecAdd(&work_vec_b, &work_vec_b, g_tether_origin);
                        CollLine(&work_vec_b, M2C_FIELD(vars, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        FastVecScale(&work_vec_b, ptr21, flt13);
                        FastVecAdd(&work_vec_b, &work_vec_b, g_tether_origin);
                        CollLine(&work_vec_b, M2C_FIELD(vars, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        FastVecScale(&work_vec_b, ptr21, flt14);
                        FastVecAdd(&work_vec_b, &work_vec_b, g_tether_origin);
                        CollLine(&work_vec_b, M2C_FIELD(vars, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                    } else {
                        FadeToBlack(1);
                    }
block_183:
                    qzero_nc(((s128 *) (vars + 0xE0)));
                    moby_call_helper_with_blocks_pal(moby);
                    goto block_184;
                }
                break;
            }
block_184:
                val52 = M2C_FIELD(moby, u8 *, 0x20);
                switch (val52) {                /* switch 2 */
                case 5:                             /* switch 2 */
                    if ((M2C_FIELD(vars, s32 *, 0x464) == 0) || (M2C_FIELD(vars, s16 *, 0x41E) != 2)) {
                        if (M2C_FIELD(vars, s16 *, 0x380) != 0) {
                            FastDecTimer((s32) (vars + 0x380));
                        } else {
                            flt8 = g_space_ship_threshold;
                            M2C_FIELD(vars, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                            if ((M2C_FIELD(vars, f32 *, 0x3E0) < flt8) && (M2C_FIELD(vars, s16 *, 0x41E) == 0)) {
                                moby_set_state(moby, 6, 0);
                            } else {
                                moby_set_state(moby, 7, 0);
                            }
                        }
                        M2C_FIELD(vars, s32 *, 0x190) = 0;
                        orbit_update_pal(moby, 0xC, 0, 3, 3, 1.0f);
                    } else {
                    case 18:                        /* switch 2 */
                        if ((M2C_FIELD(moby, u8 *, 0x94) != 0x12) && (M2C_FIELD(moby, u8 *, 0x43) != 0xB)) {
                            orbit_update_pal(moby, 0xB, 0, 3, 3, 1.0f);
                        }
                        lane_find_point_ahead_of_ship(moby);
                        moby_set_state(moby, 0x13, 9);
                    }
                    break;
                case 19:                            /* switch 2 */
                    val12 = M2C_FIELD(vars, s32 *, 0x440);
                    if (M2C_FIELD(val12, u8 *, 0x43) == 3) {
                        if ((M2C_FIELD(val12, u8 *, 0x60) & 2) && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) || (M2C_FIELD(vars, f32 *, 0x3DC) > 70.0f))) {
                            orbit_update_pal(moby, 0xB, (s32) moby_get_anim_value(moby), 3, 2, 1.0f);
                        } else if ((moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) >= 4.0f) && (M2C_FIELD(vars, f32 *, 0x44C) < 4.0f)) {
                            space_ship_run_attached_part_effect(moby, 1, g_hero_moby, 0, 0);
                        } else if ((moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(vars, f32 *, 0x44C) < 2.0f)) {
                            space_ship_run_attached_part_effect(moby, 2, g_hero_moby, 0, 0);
                        }
                    } else if ((M2C_FIELD(vars, f32 *, 0x3DC) < 70.0f) && (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0) && (M2C_FIELD(vars, s32 *, 0x464) == 0)) {
                        orbit_update_pal(moby, 3, 0, 3, 2, 1.0f);
                        anim_start_blended_pal(((VarsD708 *) vars)->p448, 7, 0, 3);
                    }
                    if (fast_vec_dist((moby + 0x10), M2C_FIELD(vars, s128 **, 0x3AC)) < 8.0f) {
                        moby_set_state(moby, 0x14, 9);
                        break;
                    }
                    WalkPathUpdate_pal(moby);
                    if (((u16) M2C_FIELD(moby, u16 *, 0x96) >= 0x1a) && (M2C_FIELD(vars, f32 *, 0x43C) <= M2C_FIELD(vars, f32 *, 0x140))) {
                        FastVecSub(&scratch[0].q, (moby + 0x10), (s128 *) (g_hero_state + 0x80));
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, 1.0f);
                        if ((FastVecDot(moby + 0xC0, &scratch[0].q) < -0.5f) && (FastVecLength(&scratch[0].q) < 10.0f)) {
                            moby_set_state(moby, 0x21, 9);
                            if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) {
                                M2C_FIELD(vars, s16 *, 0x3A6) = 3;
                            } else if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0) {
                                M2C_FIELD(vars, s16 *, 0x3A6) = 3;
                            } else {
                                M2C_FIELD(vars, s16 *, 0x3A6) = 2;
                            }
                            M2C_FIELD(vars, s16 *, 0x350) = 0;
                        }
                    }
                    break;
                case 20:                            /* switch 2 */
                    if ((flag_set_first_pending(moby) != 0) && (M2C_FIELD(moby, u8 *, 0x43) == 4)) {
                        orbit_update_pal(moby, 0, 0, 0x11, 3, 1.0f);
                    } else if ((u16) M2C_FIELD(moby, u16 *, 0x96) >= 0x1a) {
                        if (pickup_find_nearest_needed(moby, &scratch[0].q) != 0) {
                            M2C_FIELD(vars, s128 *, 0x3B0) = (s128) scratch[0].q;
                            M2C_FIELD(vars, s128 **, 0x3AC) = (s128 *) (vars + 0x3B0);
                            moby_set_state(moby, 0x15, 9);
                            orbit_update_pal(moby, 0xB, 0, 3, 3, 1.0f);
                        } else {
                            stat_restore_random(moby);
                            if ((((f32) ((s32) (g_space_ship_max_health * 2) / 3) <= M2C_FIELD(vars, f32 *, 0x20)) || (M2C_FIELD(vars, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6))
                                    || ((math_random_int_below(2) == 0) && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0))))
                                && ((M2C_FIELD(vars, s32 *, 0x464) == 0) || (M2C_FIELD(vars, s16 *, 0x41E) != 2))) {
                                if (((f32) ((s32) g_space_ship_max_health / 6) < M2C_FIELD(vars, f32 *, 0x20))
                                        && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0))
                                        && (math_random_int_below(5) == 0)) {
                                    moby_set_state(moby, 0x1D, 3);
                                } else {
                                    moby_set_state(moby, 5, 0);
                                }
                            } else if (M2C_FIELD(vars, f32 *, 0x3DC) < 55.0f) {
                                moby_set_state(moby, 0x12, 9);
                            }
                        }
                    }
                    break;
                case 21:                            /* switch 2 */
                    if (fast_vec_dist((moby + 0x10), M2C_FIELD(vars, s128 **, 0x3AC)) < 8.0f) {
                        moby_set_state(moby, 0x16, 9);
                        orbit_update_pal(moby, 0, 0, 0x11, 3, 1.0f);
                        break;
                    }
                    WalkPathUpdate_pal(moby);
                    break;
                case 22:                            /* switch 2 */
                    if ((u16) M2C_FIELD(moby, u16 *, 0x96) >= 0x1a) {
                        if (((f32) ((s32) (g_space_ship_max_health * 2) / 3) <= M2C_FIELD(vars, f32 *, 0x20)) || (M2C_FIELD(vars, f32 *, 0x20) <= (f32) ((s32) g_space_ship_max_health / 6))) {
                            moby_set_state(moby, 5, 0);
                        } else if (M2C_FIELD(vars, f32 *, 0x3DC) < 55.0f) {
                            moby_set_state(moby, 0x12, 9);
                        } else {
                            moby_set_state(moby, 0x14, 9);
                        }
                    }
                    break;
                case 7:                             /* switch 2 */
                    if (M2C_FIELD(vars, f32 *, 0x3E0) < 33.0f) {
                        moby_set_state(moby, 0x1E, 4);
                    } else {
                        WalkPathUpdate_pal(moby);
                    }
                    break;
                case 6:                             /* switch 2 */
                    flt8 = M2C_FIELD(vars, f32 *, 0x3E0);
                    if (M2C_FIELD(vars, s32 *, 0x418) != 0) {
                        if (flt8 < 20.0f) {
                            moby_set_state(moby, 0xF, 6);
                        } else {
                            WalkPathUpdate_pal(moby);
                        }
                    } else if (flt8 < g_space_ship_threshold) {
                        moby_set_state(moby, 0x1E, 4);
                    } else {
                        WalkPathUpdate_pal(moby);
                    }
                    break;
                case 28:                            /* switch 2 */
                    if (flag_set_first_pending(moby) != 0) {
                        orbit_update_pal(moby, 0xB, 0, 5, 3, 1.0f);
                    }
                    if ((M2C_FIELD(vars, f32 *, 0x3E0) < g_space_ship_threshold) && (M2C_FIELD(vars, s32 *, 0x3D8) != 0)) {
                        moby_set_state(moby, 0x1E, 4);
                    }
                    M2C_FIELD(vars, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                    WalkPathUpdate_pal(moby);
                    break;
                case 29:                            /* switch 2 */
                    if (flag_set_first_pending(moby) != 0) {
                        orbit_update_pal(moby, 0xC, 0, 0x11, 3, 1.0f);
                    }
                    if ((M2C_FIELD(vars, f32 *, 0x3E0) < 29.0f) && (M2C_FIELD(vars, s32 *, 0x3D8) != 0)) {
                        moby_set_state(moby, 0x1E, 4);
                    }
                    M2C_FIELD(vars, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                    WalkPathUpdate_pal(moby);
                    break;
                case 31:                            /* switch 2 */
                    val55 = M2C_FIELD(moby, u8 *, 0x43);
                    switch (val55) {            /* switch 3; irregular */
                    case 9:                         /* switch 3 */
                        if ((moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(moby, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(vars, s32 *, 0x440), 3, 4.0f, 10.0f, 0x10007, 1.0f, 0, 2, 0);
                            M2C_FIELD(moby, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(moby, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(moby, u8 *, 0x60) & 2) {
                            WalkPathUpdate_pal(moby);
                            orbit_update_pal(moby, 0xA, 0, 3, 3, g_space_ship_orbit_arg);
                        }
                        if ((moby_get_anim_value(moby) > 0.0f) && (moby_get_anim_value(moby) < 23.0f)) {
                            moby_aim_at_target_offset_pal(moby, (s128 *) (g_hero_state + 0x80));
                        }
                        break;
                    case 10:                        /* switch 3 */
                        if ((moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(moby, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(vars, s32 *, 0x440), 4, 4.0f, 10.0f, 0x10007, 1.0f, 0, 2, 0);
                            M2C_FIELD(moby, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(moby, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(moby, u8 *, 0x60) & 2) {
                            orbit_update_pal(moby, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                        }
                        moby_aim_at_target_offset_pal(moby, (s128 *) (g_hero_state + 0x80));
                        break;
                    case 13:                        /* switch 3 */
                        if (flag_set_first_pending(moby) != 0) {
                            g_space_ship_boost_timer = 0;
                        }
                        if (M2C_FIELD(moby, u8 *, 0x60) & 2) {
                            if ((g_space_ship_boost_timer != 0) && ((math_random_int_below(4) == 0) || ((f32) (g_ship_progress_count * 7) < M2C_FIELD(vars, f32 *, 0x20)))) {
                                if ((M2C_FIELD(vars, f32 *, 0x20) == (f32) M2C_FIELD(vars, s16 *, 0x326)) && (g_ship_progress_count < 0x64)) {
                                    moby_set_state(moby, 4, 2);
                                } else {
                                    moby_set_state(moby, 3, 2);
                                }
                            } else if (space_ship_is_aligned_with_target_pal(moby) != 0) {
                                orbit_update_pal(moby, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                                moby_set_state(moby, 0x1F, 4);
                            } else {
                                moby_set_state(moby, 0x12, 9);
                            }
                        } else if (g_space_ship_anim_max < moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440))) {
                            if (moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) < g_space_ship_anim_min) {
                                moby_transform_joint_to_world(M2C_FIELD(vars, s32 *, 0x440), 4, (s32) &scratch[1].q);
                                moby_transform_joint_to_world(M2C_FIELD(vars, s32 *, 0x440), 3, (s32) &scratch[0].q);
                                FastVecAdd(&scratch[2].q, &scratch[0].q, &scratch[1].q);
                                FastVecScale(&scratch[2].q, &scratch[2].q, 0.5f);
                                M2C_FIELD(moby, s32 *, 0x98) = 0;
                                coll_sweep_from_object((s32) moby, (s32) &scratch[2].q, 0x10007, 4.0f, 100.0f, 14.5f, 0, 2, 0);
                                {
                                    u8 *g = g_hero_state;
                                    f32 reach = g_space_ship_reach;
                                    M2C_FIELD(moby, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(moby, void **, 0x24), s32 *, 0x10);
                                    FastVecScale(&scratch[3].q, M2C_FIELD(g, void **, 0x2290) + 0xE0, reach);
                                    FastVecAdd(&scratch[3].q, &scratch[3].q, g + 0x80);
                                }

                                if (fast_vec_dist(&scratch[2].q, &scratch[3].q) < g_space_ship_trigger_distance) {
                                    actuator_play_pattern(0x2B);
                                    g_space_ship_boost_timer = (g_space_ship_state_default * 5 + 2) / 6;
                                }
                            }
                        }
                        moby_set_controller_speed_limits(moby, g_space_ship_speed_limit_a * 0.00040000002f, g_space_ship_speed_limit_b * 0.020000001f, g_orbit_param_e * 6.981318e-06f, g_orbit_param_f * 0.0003490659f);
                        moby_aim_at_target_offset_pal(moby, (s128 *) (g_hero_state + 0x80));
                        break;
                    }
                    if ((M2C_FIELD(moby, u8 *, 0x95) != 6) && (M2C_FIELD(vars, f32 *, 0x3DC) > g_space_ship_threshold) && (g_space_ship_boost_timer == 0)) {
                        moby_set_state(moby, 0x12, 9);
                    }
                    break;
                case 15:                            /* switch 2 */
                    moby_aim_at_target_offset_pal(moby, (s128 *) (g_hero_state + 0x80));
                    FastVecScale(&scratch[0].q, moby + 0xC0, 3.0f);
                    FastVecAdd(&scratch[0].q, &scratch[0].q, (moby + 0x10));
                    if (WalkPathIsClear(moby, (moby + 0x10), &scratch[0].q) == 0) {
                        orbit_update_pal(moby, 9, 0, 3, 3, g_space_ship_orbit_arg);
                        moby_set_state(moby, 0x1F, 6);
                        break;
                    }
                    break;
                case 32:                            /* switch 2 */
                    if (flag_set_first_pending(moby) != 0) {
                        orbit_update_pal(moby, 3, 0, 3, 2, 1.0f);
                        anim_start_blended_pal(((VarsD708 *) vars)->p448, 1, 0, 3);
                        M2C_FIELD(vars, s16 *, 0x384) = math_random_int_range(0x64, 0xc8);
                        M2C_FIELD(vars, s16 *, 0x386) = 0;
                    } else if (M2C_FIELD(((VarsD708 *) vars)->p448, u8 *, 0x60) & 2) {
                        if (math_random_int_below(4) == 0) {
                            anim_start_blended_pal(((VarsD708 *) vars)->p448, 7, 0, 3);
                        } else {
                            anim_start_blended_pal(((VarsD708 *) vars)->p448, 1, 0, 3);
                        }
                    }
                    if ((M2C_FIELD(vars, s16 *, 0x384) <= 0) || (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) || (M2C_FIELD(vars, s32 *, 0x3D8) == 0)
                        || ((flt9 = M2C_FIELD(vars, f32 *, 0x3DC)) > 60.0f)
                        || ((val13 = M2C_FIELD(vars, s32 *, 0x440), (M2C_FIELD(val13, u8 *, 0x60) & 2)) && (flt9 < g_space_ship_threshold))) {
                        moby_set_state(moby, 5, 0);
                    } else if (M2C_FIELD(val13, u8 *, 0x60) & 2) {
                        M2C_FIELD(vars, s16 *, 0x386) = 0;
                    } else if (M2C_FIELD(val13, u8 *, 0x43) == 3) {
                        if ((moby_get_anim_value((void *) val13) >= 4.0f) && (M2C_FIELD(vars, f32 *, 0x44C) < 4.0f)) {
                            space_ship_run_attached_part_effect(moby, 1, g_hero_moby, 0, 0);
                        } else if ((moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(vars, f32 *, 0x44C) < 2.0f)) {
                            space_ship_run_attached_part_effect(moby, 2, g_hero_moby, 0, 0);
                        }
                    } else {
                        FastDecTimer((s32) (vars + 0x386));
                        if (M2C_FIELD(vars, s16 *, 0x386) <= 0) {
                            orbit_update_pal(moby, 3, 0, 3, 2, 1.0f);
                            anim_start_blended_pal(((VarsD708 *) vars)->p448, 1, 0, 3);
                        }
                    }
                    if (M2C_FIELD(vars, f32 *, 0x3E0) < g_space_ship_threshold) {
                        orbit_update_pal(moby, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                        moby_set_state(moby, 0x1F, 4);
                        break;
                    }
                    val56 = M2C_FIELD(moby, u8 *, 0x43);
                    if (val56 == 0xC) {
                        if (M2C_FIELD(vars, f32 *, 0x3DC) < 37.0f) {
                            orbit_update_pal(moby, 0, 0, 3, 1, 1.0f);
                        } else {
                            WalkPathUpdate_pal(moby);
                        }
                    } else if (val56 == 0xB) {
                        if ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) >= M2C_FIELD(vars, s16 *, 0x430)) && (M2C_FIELD(vars, f32 *, 0x3DC) > 32.0f)) {
                            orbit_update_pal(moby, 0, 0, 3, 1, 1.0f);
                        } else {
                            WalkPathUpdate_pal(moby);
                        }
                    } else {
                        if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) < M2C_FIELD(vars, s16 *, 0x430)) {
                            orbit_update_pal(moby, 0xB, 0, 3, 1, 1.0f);
                            M2C_FIELD(vars, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                            M2C_FIELD(vars, s16 *, 0x430) = 0x3E8;
                        }
                        flt10 = M2C_FIELD(vars, f32 *, 0x3DC);
                        if (flt10 > 42.0f) {
                            orbit_update_pal(moby, 0xC, 0, 3, 1, 1.0f);
                            M2C_FIELD(vars, s128 **, 0x3AC) = (s128 *) (g_hero_state + 0x80);
                        } else if (flt10 < 25.0f) {
                            orbit_update_pal(moby, 0xB, 0, 3, 1, 1.0f);
                            vec1 = vars + 0x3B0;
                            FastVecSub(&scratch[0].q, (moby + 0x10), (s128 *) (g_hero_state + 0x80));
                            FastVecScale(&scratch[0].q, &scratch[0].q, 20.0f);
                            FastVecAdd(&scratch[0].q, (moby + 0x10), &scratch[0].q);
                            lane_find_nearest_point(moby, vec1, &scratch[0].q, 1);
                            M2C_FIELD(vars, s128 **, 0x3AC) = vec1;
                        } else {
                            moby_call_helper_with_blocks_pal(moby);
                        }
                    }
                    break;
                case 33:                            /* switch 2 */
                    if (flag_set_first_pending(moby) != 0) {
                        orbit_update_pal(moby, 5, 0, 3, 3, 1.0f);
                        anim_start_blended_pal(((VarsD708 *) vars)->p448, 0, 0, 3);
                    }
                    lane_store_nearest_point_as_current(moby, 1);
                    ptr16 = vars + 0x360;
                    M2C_FIELD(vars, s128 *, 0x360) = (s128) M2C_FIELD(((M2C_FIELD(vars, s16 *, 0x356) * 0x10) + g_ship_path_table[((OwnerD708 *) vars)->paths[M2C_FIELD(vars, s16 *, 0x354)]]), s128 *, 0x10);
                    arena_push_point_out(ptr16, 8.0f);
                    M2C_FIELD(vars, f32 *, 0x3A0) = fast_vec_dist((moby + 0x10), ptr16);
                    moby_set_state(moby, 0x22, 5);
                    M2C_FIELD(vars, u16 *, 0x3A4) = 0U;
                    if (M2C_FIELD(vars, s16 *, 0x3A6) == 3) {
                        if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) {
                            M2C_FIELD(vars, s16 *, 0x3A6) = 0;
                        } else {
                            M2C_FIELD(vars, s16 *, 0x3A6) = 1;
                        }
                    }
                    break;
                case 34:                            /* switch 2 */
                    ptr17 = vars + 0x360;
                    if (fast_vec_dist((moby + 0x10), ptr17) < 2.0f) {
                        *(s128 *)(moby + 0x10) = M2C_FIELD(vars, s128 *, 0x360);
                        moby_set_state(moby, 0x23, 5);
                        orbit_update_pal(moby, 6, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(vars, s16 *, 0x384) = math_random_int_range(0x12c, 0x1f4);
                        M2C_FIELD(vars, s16 *, 0x386) = 0;
                        M2C_FIELD(vars, f32 *, 0x3A8) = 0.0f;
                    } else {
                        FastVecSub(&scratch[0].q, ptr17, (moby + 0x10));
                        work_int0 = 0;
                        flt18 = FastVecLength(&scratch[0].q);
                        math_step_value_toward_target(&work_int0, vars + 0x3A8, flt18, 0.016f, 0.008f, 0.40000004f);
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, M2C_FIELD(vars, f32 *, 0x3A8));
                        FastVecAdd((moby + 0x10), (moby + 0x10), &scratch[0].q);
                        if ((M2C_FIELD(moby, u8 *, 0x60) & 2) && (M2C_FIELD(moby, u8 *, 0x43) == 5)) {
                            orbit_update_pal(moby, 6, 0, 0x11, 3, 1.0f);
                        }
                    }
                    break;
                case 35:                            /* switch 2 */
                    if ((M2C_FIELD(vars, s16 *, 0x384) <= 0) || (M2C_FIELD(vars, s32 *, 0x3D8) == 0) || (M2C_FIELD(vars, s32 *, 0x418) != 0)
                        || ((M2C_FIELD(vars, s32 *, 0x464) != 0) && (M2C_FIELD(vars, s16 *, 0x41E) == 2))
                        || ((val45 = (u16) M2C_FIELD(vars, s16 *, 0x3A6), (M2C_FIELD(vars, s16 *, 0x3A6) == 1))
                            && ((M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) == 0) || ((u16) M2C_FIELD(moby, u16 *, 0x96) >= 0x65)))) {
                        ptr6 = moby + 0xE0;
                        moby_set_state(moby, 0x24, 5);
                        orbit_update_pal(moby, 2, 0, 3, 2, 1.0f);
                        M2C_FIELD(vars, f32 *, 0x3A8) = 0.0f;
                    } else {
                                val14 = M2C_FIELD(vars, s32 *, 0x440);
                                if (M2C_FIELD(val14, u8 *, 0x60) & 2) {
                                    mode3A6 = (s16) val45;
                                    if (mode3A6 == 0) {
                                        if (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) == 0) {
                                            ptr6 = moby + 0xE0;
                                            moby_set_state(moby, 0x24, 5);
                                            orbit_update_pal(moby, 6, 0, 3, 3, 1.0f);
                                            M2C_FIELD(vars, f32 *, 0x3A8) = 0.0f;
                                        } else {
                                        ptr6 = moby + 0xE0;
                                        table_decrement_timer();
                                        }
                                    } else if (mode3A6 == 1) {
                                        orbit_update_pal(moby, 2, 0, 3, 2, 1.0f);
                                        ptr6 = moby + 0xE0;
                                        M2C_FIELD(vars, s16 *, 0x386) = 0;
                                    } else {
                                        ptr6 = moby + 0xE0;
                                        if (mode3A6 == 2) {
                                            if (M2C_FIELD(vars, f32 *, 0x3DC) > 30.0f) {
                                                moby_set_state(moby, 0x24, 5);
                                                M2C_FIELD(vars, f32 *, 0x3A8) = 0.0f;
                                            }
                                        }
                                    }
                                } else {
                                    val57 = M2C_FIELD(val14, u8 *, 0x43);
                                    if (val57 == 3) {
                                        if ((moby_get_anim_value((void *) val14) >= 4.0f) && (M2C_FIELD(vars, f32 *, 0x44C) < 4.0f)) {
                                            space_ship_run_attached_part_effect(moby, 1, g_hero_moby, 0, 0);
                                            ptr6 = moby + 0xE0;
                                        } else {
                                            ptr6 = moby + 0xE0;
                                            if ((moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(vars, f32 *, 0x44C) < 2.0f)) {
                                                space_ship_run_attached_part_effect(moby, 2, g_hero_moby, 0, 0);
                                            }
                                        }
                                    } else if (val57 == 14) {
                                        if ((moby_get_anim_value((void *) val14) > 22.0f) && (moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) < 55.0f)) {
                                            ptr6 = moby + 0xE0;
                                            M2C_FIELD(M2C_FIELD(vars, s32 *, 0x440), f32 *, 0x48) = 1.0f;
                                        } else {
                                            ptr6 = moby + 0xE0;
                                            if (moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) >= 10.0f) {
                                                f32 t = moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440));
                                                s128 *d = &scratch[0].q;
                                                if (t <= 22.0f) {
                                                *d = *(s128 *)(moby + 0x10);
                                                vec_scale_to_length(&scratch[1].q, ptr6, 3.0f);
                                                FastVecAdd(&scratch[1].q, &scratch[1].q, moby + 0xC0);
                                                FastVecAdd(d, d, &scratch[1].q);
                                                keyed_object_place(moby, d, 0);
                                                M2C_FIELD(M2C_FIELD(vars, s32 *, 0x440), f32 *, 0x48) = 0.35f;
                                                }
                                            }
                                        }
                                    } else {
                                        ptr6 = moby + 0xE0;
                                        FastDecTimer((s32) (vars + 0x386));
                                        if (M2C_FIELD(vars, s16 *, 0x386) <= 0) {
                                            val3 = M2C_FIELD(vars, s16 *, 0x3A6);
                                            if (val3 == 1) {
                                                orbit_update_pal(moby, 3, 0, 3, 2, 1.0f);
                                                anim_start_blended_pal(((VarsD708 *) vars)->p448, 5, 0, 3);
                                            } else if (val3 == 0) {
                                                val20 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC);
                                                if (val20 > 0) {
                                                    M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) = (s32) (val20 - 1);
                                                }
                                                orbit_update_pal(moby, 0xE, 0, 3, 2, 1.0f);
                                                anim_start_blended_pal(((VarsD708 *) vars)->p448, 5, 0, 3);
                                            }
                                        }
                                    }
                                }
                    }
                    if ((M2C_FIELD(vars, f32 *, 0x3DC) >= 38.0f) || (M2C_FIELD(vars, f32 *, 0x3DC) <= 32.0f)) {
                        work_int1 = 0;
                        if (M2C_FIELD(vars, f32 *, 0x3DC) > 32.0f) {
                            val34 = 3;
                            flt16 = math_fabs(M2C_FIELD(vars, f32 *, 0x3DC) - 35.0f);
                            if ((u16) M2C_FIELD(vars, u16 *, 0x3A4) >= 2U) {
                                work_int1 = 1;
                                M2C_FIELD(vars, u16 *, 0x352) = (u16) -(s32) M2C_FIELD(vars, u16 *, 0x352);
                            }
                            val49 = 1;
                        } else {
                            val34 = 2;
                            flt16 = math_fabs(M2C_FIELD(vars, f32 *, 0x3DC) - 35.0f);
                            val2 = (s16) M2C_FIELD(vars, u16 *, 0x3A4);

                            if ((val2 != 0) && (val2 != 2)) {
                                work_int1 = 1;
                                M2C_FIELD(vars, u16 *, 0x352) = (u16) -(s32) M2C_FIELD(vars, u16 *, 0x352);
                            }
                            val49 = 2;
                        }
                        M2C_FIELD(vars, u16 *, 0x3A4) = val49;
                        if ((u16) M2C_FIELD(moby, u16 *, 0x96) < 0x32) {
                            ptr3 = (s32 *) g_ship_path_table[((OwnerD708 *) vars)->paths[M2C_FIELD(vars, s16 *, 0x354)]];
                            if (work_int1 == 0) {
                                val40 = M2C_FIELD(vars, s16 *, 0x356) + 1;
                                if (val40 >= *ptr3) {
                                    val40 = -1;
                                    M2C_FIELD(vars, u16 *, 0x352) = 1U;
                                } else {
                                    {
                                        s128 next = M2C_FIELD(((s8 *) ptr3 + (val40 * 0x10)), s128 *, 0x10);
                                        scratch[0].q = next;
                                    }
                                    arena_push_point_out(&scratch[0].q, 8.0f);
                                }
                                val39 = M2C_FIELD(vars, s16 *, 0x356) - 1;
                                if (val39 < 0) {
                                    val39 = -1;
                                    M2C_FIELD(vars, s16 *, 0x352) = -1;
                                } else {
                                    {
                                        s128 prev = M2C_FIELD(((s8 *) ptr3 + (val39 * 0x10)), s128 *, 0x10);
                                        scratch[1].q = prev;
                                    }
                                    arena_push_point_out(&scratch[1].q, 8.0f);
                                }
                                if (val40 != -1) {
                                    FastVecSub(&scratch[3].q, &scratch[0].q, (moby + 0x10));
                                    FastVecSub(&scratch[4].q, (s128 *) (g_hero_state + 0x80), (moby + 0x10));
                                    scratch[2].f[0] = FastVecDot(&scratch[3].q, &scratch[4].q);
                                }
                                if (val39 != -1) {
                                    FastVecSub(&scratch[3].q, &scratch[1].q, (moby + 0x10));
                                    FastVecSub(&scratch[4].q, (s128 *) (g_hero_state + 0x80), (moby + 0x10));
                                    scratch[2].f[1] = FastVecDot(&scratch[3].q, &scratch[4].q);
                                }
                                if (val34 == 3) {
                                    if ((val40 != -1) && (val39 != -1)) {
                                        if ((scratch[2].f[0] > scratch[2].f[1]) && (scratch[2].f[0] > 0.0f)) {
                                            M2C_FIELD(vars, u16 *, 0x352) = 1;
                                        }
                                    } else if ((val40 == -1) && (scratch[2].f[1] > 0.0f)) {
                                        M2C_FIELD(vars, s16 *, 0x352) = -1;
                                    } else if ((val39 == -1) && (scratch[2].f[0] > 0.0f)) {
                                        M2C_FIELD(vars, u16 *, 0x352) = 1;
                                    }
                                } else if (val34 == 2) {
                                    if ((val40 != -1) && (val39 != -1)) {
                                        if (scratch[2].f[0] < scratch[2].f[1]) {
                                            M2C_FIELD(vars, u16 *, 0x352) = 1;
                                        } else {
                                            M2C_FIELD(vars, s16 *, 0x352) = -1;
                                        }
                                    } else if ((val40 == -1) && (scratch[2].f[1] < 0.0f)) {
                                        M2C_FIELD(vars, s16 *, 0x352) = -1;
                                    } else if ((val39 == -1) && (scratch[2].f[0] < 0.0f)) {
                                        M2C_FIELD(vars, u16 *, 0x352) = 1;
                                    }
                                }
                            }
                        }
                        if ((work_int1 != 0) || (near = ((s128 *) (vars + 0x360)), fast_vec_dist((moby + 0x10), near) < 2.0f)) {
                            val1 = M2C_FIELD(vars, s16 *, 0x356) + M2C_FIELD(vars, s16 *, 0x352);
                            ptr14 = g_ship_path_table[((OwnerD708 *) vars)->paths[M2C_FIELD(vars, s16 *, 0x354)]];
                            if (val1 < 0) {
                                WalkPathPickNext(moby, val34, 1, M2C_FIELD(ptr14, f32 *, 0x1C));
                            } else {
                                val25 = M2C_FIELD(ptr14, s32 *, 0);
                                if (val1 >= val25) {
                                    WalkPathPickNext(moby, val34, 1, ((PathD708 *) ptr14)->points[val25 - 1].f[3]);
                                } else {
                                    M2C_FIELD(vars, s16 *, 0x356) = val1;
                                }
                            }
                            *((s128 *) (vars + 0x360)) = M2C_FIELD(((M2C_FIELD(vars, s16 *, 0x356) * 0x10) + g_ship_path_table[((OwnerD708 *) vars)->paths[M2C_FIELD(vars, s16 *, 0x354)]]), s128 *, 0x10);
                            arena_push_point_out(((s128 *) (vars + 0x360)), 8.0f);
                        } else {
                            FastVecSub(&scratch[0].q, near, (moby + 0x10));
                            flt16 = flt16 * 0.0625f;
                            if (flt16 > 0.5f) {
                                flt16 = 0.5f;
                            }
                            vec_scale_to_length(&scratch[0].q, &scratch[0].q, flt16);
                            FastVecAdd((moby + 0x10), (moby + 0x10), &scratch[0].q);
                            arena_push_point_out((moby + 0x10), 8.0f);
                            M2C_FIELD(vars, s32 *, 0x3E8) = 0;
                        }
                    }
                    math_steer_along_direction(moby, vars + 0x3E4, vars + 0x3E8, ptr6, g_space_ship_steer_param_a, g_space_ship_steer_param_b, -1.0f);
                    break;
                case 36:                            /* switch 2 */
                    if (gravity_get_center_distance((moby + 0x10)) <= g_planet_radius) {
                        moby_set_state(moby, 5, 0);
                        M2C_FIELD(vars, s16 *, 0x350) = 0;
                        M2C_FIELD(vars, f32 *, 0x3E4) = M2C_FIELD(vars, f32 *, 0x3E8) = 0.0f;
                    } else {
                        work_float = gravity_get_center_distance((moby + 0x10)) - g_planet_radius;
                        scratch[1].q = *(s128 *)(moby + 0x10);
                        arena_push_point_out(&scratch[1].q, 0.0f);
                        FastVecSub(&scratch[0].q, &scratch[1].q, (moby + 0x10));
                        math_step_value_toward_target(&work_float, vars + 0x3A8, 0.0f, 0.016f, 0.016f, 0.40000004f);
                        vec_scale_to_length(&scratch[0].q, &scratch[0].q, -M2C_FIELD(vars, f32 *, 0x3A8));
                        FastVecAdd((moby + 0x10), (moby + 0x10), &scratch[0].q);
                    }
                    break;
                case 30:                            /* switch 2 */
                    if (M2C_FIELD(moby, u8 *, 0x20) == 0x1E) {
                        if ((M2C_FIELD(vars, s32 *, 0x3D0) != 0) && (M2C_FIELD(vars, s32 *, 0x3D8) != 0)) {
                            flt11 = M2C_FIELD(vars, f32 *, 0x3DC);
                            if (flt11 < g_space_ship_threshold) {
                                if ((math_random_int_below(5) == 0) && (M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0)) {
                                    moby_set_state(moby, 0x21, 5);
                                    M2C_FIELD(vars, s16 *, 0x3A6) = 3;
                                } else {
                                    orbit_update_pal(moby, 0xD, 0, 3, 3, g_space_ship_orbit_arg);
                                    moby_set_state(moby, 0x1F, 4);
                                }
                            } else if (flt11 < 33.0f) {
                                val38 = 0;
                                val35 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) != 0;
                                if (M2C_FIELD(vars, s16 *, 0x41E) > 0) {
                                    val38 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 0xC) != 0;
                                }
                                if ((val35 != 0) && (val38 != 0)) {
                                    if (math_random_int_below(2) != 0) {
                                        val35 = 0;
                                    } else {
                                        val38 = 0;
                                    }
                                }
                                if (val35 != 0) {
                                    val17 = M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8);
                                    if (val17 >= 0x32) {
                                        M2C_FIELD(vars, s16 *, 0x430) = (s16) ((u16) M2C_FIELD(g_space_ship_pickup_slots, s32 *, 8) - math_random_int_below(0x23));
                                    } else {
                                        if (val17 >= 3) {
                                            M2C_FIELD(vars, s16 *, 0x430) = (s16) math_random_int_below(val17 / 2);
                                        } else {
                                            M2C_FIELD(vars, s16 *, 0x430) = 1;
                                        }
                                    }
                                    if (math_random_int_below(4) != 0) {
                                        moby_set_state(moby, 0x20, 4);
                                    } else {
                                        moby_set_state(moby, 0x21, 5);
                                        M2C_FIELD(vars, s16 *, 0x3A6) = 1;
                                    }
                                } else if (val38 != 0) {
                                    moby_set_state(moby, 0x21, 5);
                                    M2C_FIELD(vars, s16 *, 0x3A6) = 0;
                                } else {
                                    moby_set_state(moby, 0x12, 9);
                                }
                            } else {
                                WalkPathUpdate_pal(moby);
                            }
                        } else {
                            WalkPathUpdate_pal(moby);
                        }
                    }
                    break;
                case 1:                             /* switch 2 */
                    if (g_space_ship_timer < 0xC8) {
                        moby_check_target_point_from_offset(moby, (s128 *) (g_hero_state + 0x80));
                        if (flag_set_first_pending(moby) != 0) {
                            orbit_update_pal(moby, 0, 0, 0, 3, 1.0f);
                            anim_start_blended_pal(((VarsD708 *) vars)->p448, 7, 0, 0);
                        }
                        if (M2C_FIELD(vars, s16 *, 0x1D0) == 0) {
                            moby_call_helper_with_blocks_pal(moby);
                        }
                    }
                    break;
                case 2:                             /* switch 2 */
                    moby_check_target_point_from_offset(moby, (s128 *) (g_hero_state + 0x80));
                    if (flag_set_first_pending(moby) != 0) {
                        orbit_update_pal(moby, 0, 0, 3, 3, 1.0f);
                        anim_start_blended_pal(((VarsD708 *) vars)->p448, 4, 0, 3);
                    } else if (M2C_FIELD(vars, s16 *, 0x384) <= 0) {
                        orbit_update_pal(moby, 0, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(vars, s16 *, 0x384) = (s16) (math_random_int_below(7) + 0x16);
                    }
                    FastDecTimer((s32) (vars + 0x384));
                    if (M2C_FIELD(vars, s16 *, 0x1D0) == 0) {
                        moby_call_helper_with_blocks_pal(moby);
                    }
                    break;
                case 3:                             /* switch 2 */
                    moby_check_target_point_from_offset(moby, (s128 *) (g_hero_state + 0x80));
                    if (flag_set_first_pending(moby) != 0) {
                        orbit_update_pal(moby, 0, 0, 3, 3, 1.0f);
                        anim_start_blended_pal(((VarsD708 *) vars)->p448, 4, 0, 3);
                    }
                    if ((u16) M2C_FIELD(moby, u16 *, 0x96) >= 0x77) {
                        moby_set_state(moby, 0x12, 9);
                    } else if (M2C_FIELD(vars, s16 *, 0x384) <= 0) {
                        orbit_update_pal(moby, 0, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(vars, s16 *, 0x384) = (s16) (math_random_int_below(7) + 0x16);
                    }
                    FastDecTimer((s32) (vars + 0x384));
                    if (M2C_FIELD(vars, s16 *, 0x1D0) == 0) {
                        moby_call_helper_with_blocks_pal(moby);
                    }
                    break;
                case 4:                             /* switch 2 */
                    if (flag_set_first_pending(moby) != 0) {
                        orbit_update_pal(moby, 0, 0, 3, 3, 1.0f);
                        anim_start_blended_pal(((VarsD708 *) vars)->p448, 4, 0, 3);
                    }
                    if ((u16) M2C_FIELD(moby, u16 *, 0x96) >= 0x4B1U) {
                        moby_set_state(moby, 0x12, 9);
                    } else if (M2C_FIELD(vars, s16 *, 0x384) <= 0) {
                        orbit_update_pal(moby, 0, 0, 0x11, 3, 1.0f);
                        M2C_FIELD(vars, s16 *, 0x384) = (s16) (math_random_int_below(7) + 0x16);
                    }
                    FastDecTimer((s32) (vars + 0x384));
                    if (M2C_FIELD(vars, s16 *, 0x1D0) == 0) {
                        moby_call_helper_with_blocks_pal(moby);
                    }
                    break;
                case 37:                            /* switch 2 */
                    break;
                }
                ptr13 = M2C_FIELD(vars, void **, 0x388);

                if (ptr13 == NULL) {
                    M2C_FIELD(vars, void **, 0x388) = effect_create_attached(moby, (moby + 0x10));
                } else {
                    moby_store_position_private(ptr13, (moby + 0x10));
                }
                M2C_FIELD(vars, f32 *, 0x38C) = moby_get_anim_value(moby);
                M2C_FIELD(vars, f32 *, 0x44C) = moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440));
                space_ship_align_parts_at_end(moby);
                pickup_update_spawned(moby);
                moby_update_timed(moby);
                space_ship_tilt_attached_part_pal(moby);
                if (M2C_FIELD(vars, s16 *, 0x350) == 3) {
                if ((list_has_key((s32) moby, (s32) M2C_FIELD(vars, s16 *, 0x354)) != 0) && ((u32) (M2C_FIELD(moby, u8 *, 0x43) - 0xB) < 2U)) {
                    val15 = M2C_FIELD(vars, s32 *, 0x440);
                    val58 = M2C_FIELD(val15, u8 *, 0x43);
                    switch (val58) {
                    case 0xA:
                        if ((moby_get_anim_value((void *) val15) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(moby, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(vars, s32 *, 0x440), 3, 4.0f, 50.0f, 0x8B0000, 0.0f, 0, 2, 0);
                            M2C_FIELD(moby, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(moby, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(M2C_FIELD(vars, s32 *, 0x440), u8 *, 0x60) & 2) {
                            M2C_FIELD(vars, s16 *, 0x34C) = 0;
                            orbit_update_pal(moby, 9, 0, 3, 2, 1.0f);
                            M2C_FIELD(vars, s16 *, 0x34C) = 1;
                        }
                        break;
                    case 9:
                        if ((moby_get_anim_value((void *) val15) > 7.0f) && (moby_get_anim_value((void *) M2C_FIELD(vars, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(moby, s32 *, 0x98) = 0;
                            coll_test_hit_at_bone((void *) M2C_FIELD(vars, s32 *, 0x440), 4, 4.0f, 50.0f, 0x8B0000, 0.0f, 0, 2, 0);
                            M2C_FIELD(moby, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(moby, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(M2C_FIELD(vars, s32 *, 0x440), u8 *, 0x60) & 2) {
                            M2C_FIELD(vars, s16 *, 0x34C) = 0;
                            orbit_update_pal(moby, 0xA, 0, 3, 2, 1.0f);
                            M2C_FIELD(vars, s16 *, 0x34C) = 1;
                        }
                        break;
                    default:
                        M2C_FIELD(vars, s16 *, 0x34C) = 0;
                        orbit_update_pal(moby, 9, 0, 3, 2, 1.0f);
                        M2C_FIELD(vars, s16 *, 0x34C) = 1;
                        break;
                    }
                    M2C_FIELD(vars, s16 *, 0x43A) = 1;
                } else if ((M2C_FIELD(vars, s16 *, 0x43A) != 0) && (M2C_FIELD(M2C_FIELD(vars, s32 *, 0x440), u8 *, 0x60) & 2)) {
                    M2C_FIELD(vars, s16 *, 0x43A) = 0;
                    M2C_FIELD(vars, s16 *, 0x34C) = 0;
                    frame = moby_get_anim_value(moby);
                    orbit_update_pal(moby, (s32) M2C_FIELD(moby, u8 *, 0x43), (s32) frame, 3, 2, 1.0f);
                }
                } else {
                    M2C_FIELD(vars, s16 *, 0x43A) = 0;
                    M2C_FIELD(vars, s16 *, 0x34C) = 0;
                }
                ptr7 = ((VarsD708 *) vars)->p448;
                if (M2C_FIELD(ptr7, u8 *, 0x60) & 2) {
                    val53 = M2C_FIELD(moby, u8 *, 0x95);
                    if ((u32) (val53 - 4) >= 2U) {
                        val23 = val53 & 0xFF;
                        if ((val23 != 8) && (val23 != 1) && (val23 != 2) && (M2C_FIELD(moby, u8 *, 0x20) != 0x26)) {
                            if (math_random_int_below(5) != 0) {
                                anim_start_blended_pal(((VarsD708 *) vars)->p448, 0, 0, 0x8);
                            } else {
                                anim_start_blended_pal(((VarsD708 *) vars)->p448, 7, 0, 0x8);
                            }
                        }
                    }
                } else if ((M2C_FIELD(ptr7, u8 *, 0x43) == 6) && (M2C_FIELD(moby, u8 *, 0x95) != 8) && (M2C_FIELD(moby, u8 *, 0x20) != 0x26)) {
                    anim_start_blended_pal(ptr7, 7, 0, 0x8);
                }
                if ((u32) (M2C_FIELD(moby, u8 *, 0x43) - 0xB) < 2U) {
                    s128 *d = &scratch[0].q;
                    qcopy(d, (s128 *)(moby + 0x10));
                    vec_scale_to_length(&scratch[1].q, vars + 0x200, 12.0f);
                    FastVecAdd(&scratch[1].q, &scratch[1].q, d);
                    if (CollLine(d, &scratch[1].q, 0x12, 0, 0) != 0) {
                        *(s128 *)(moby + 0x10) = g_spawn_point;
                    }
                }
                if (M2C_FIELD(moby, u8 *, 0x20) != 0x26) {
                    flt12 = (f32) ((s16) M2C_FIELD(vars, s16 *, 0x24) / 3);
                    flt1 = M2C_FIELD(vars, f32 *, 0x20);
                    if (flt1 < flt12) {
                        if (g_space_ship_blended_value == 0) {
                            {
                                f32 ratio = flt1 / (f32) ((s16) M2C_FIELD(vars, s16 *, 0x24) / 3);
                                g_space_ship_blended_value = g_space_ship_value_min + (s32) ((f32) (g_space_ship_value_max - g_space_ship_value_min) * ratio);
                            }
                            if (math_random_int_below(2) != 0) {
                                part_spawn_scatter_pal((s32) moby, math_random_int_below(4), 0, g_space_ship_scatter_param);
                            } else {
                                part_spawn_scatter_pal(M2C_FIELD(vars, s32 *, 0x440), math_random_int_below(6), 0, g_space_ship_scatter_param);
                            }
                        } else {
                            math_fast_float_d(&g_space_ship_blended_value);
                        }
                    }
                }
        }
    }
}
