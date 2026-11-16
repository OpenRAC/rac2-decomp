#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
extern char g_pad_state[];
extern u8 g_pad_pressed_flags[];
extern f32 g_hero_scale_table[];
extern u8 g_hero_state_flags[];
extern u8 g_item_slot_to_record[];
extern u8 g_sound_state[];
extern char g_hero_state[];
extern char g_drive_velocity_view[];
extern char g_progress_statistics[];
extern u8 g_hero_state_machine_word[];
extern u32 g_frame_counter MACRO_ADDR;
extern s32 g_current_map_index MACRO_ADDR;
extern u8 g_status_flag_b[0x40] MACRO_ADDR;
extern u8 g_hero_override_flag MACRO_ADDR;
extern f32 g_hero_speed_param_table[][4] MACRO_ADDR;
extern s32 g_hero_input_lock MACRO_ADDR;
extern u8 g_hero_l01_state_machine_table[];
extern s32 g_str_swamp_monster_hold_debug MACRO_ADDR;
extern s32 g_level_word_unused MACRO_ADDR;
extern s32 g_level_word_unused_a MACRO_ADDR;
extern s32 g_level_word_unused_b MACRO_ADDR;
extern u8 g_drive_settings[];
extern u8 g_hero_matrix_work[];
extern u8 g_view_l01_space_height[];
extern u8 g_contact_moby_list[];
extern u8 g_hero_l01_state_copy[];
extern u8 g_level_byte_buffer[];
extern u8 g_level_byte_data[];
extern Rec2C g_hero_anim_timing_table[];
extern u8 g_level_data_buffer[];
extern u8 g_item_l16_record_table[];
extern s32 CollLine(s32, s32, s32, s32, s32);
extern s32 coll_process_hit(f32, s32, s32, s32, s32);
extern s32 math_fast_float_d(s32);
extern s32 FastDecTimer(s32);
extern f32 square_root(f32);
extern f32 math_fabs(f32);
extern void vec_clear_128(s32);
extern void FastVecAdd(s32, s32, s32);
extern void FastVecSub(s32, s32, s32);
extern void FastVecScale(s32, s32, f32);
extern f32 FastVecDot(s32, s32);
extern void FastVecCross(s32, s32, s32);
extern f32 FastVecLength(s32);
extern f32 vec_length_xy(s32);
extern f32 fast_vec_dist(s32, s32);
extern f32 vec_distance_xy(s32, s32);
extern void vec_scale_to_length(s32, s32, f32);
extern void matrix_mul_vec3(s32, s32, s32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern s32 FloatToInt(f32);
extern void gauge_popup_show(s32, s32, s32, f32);
extern char *CreateMoby(s32);
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_signed_float_range(f32, f32);
extern s32 math_solve_quadratic(s32, s32, f32, f32, f32);
extern void make_hit_descriptor(s32, s32, s32, f32, s32);
extern void part_queue_impact_effect(s32, s32, s32, s32, s32, f32);
extern f32 ApproachValue(s32, f32, f32);
extern f32 math_spring_float_to_goal(s32, s32, f32, f32, f32, f32);
extern f32 vec_spring_to_target(s32, s32, s32, f32, f32, f32);
extern f32 math_shortest_angle_delta(s32, f32, f32);
extern void StepAngleTowardTarget(s32, s32, f32, f32);
extern f32 math_approach_with_velocity(s32, f32, s32, f32, f32, f32, s32);
extern s32 moby_is_in_special_class_range(s32);
extern void vec_clamp_length(s32, f32);
extern void *part_spawn_bubble(s32, s32, f32, f32);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, s32);
extern void pad_clamp_stick_to_unit_range(s32, s32, f32);
extern float AdjustHeroAnimationSpeedForTargetFrame(f32, f32, f32, f32);
extern f32 math_blend_table_entries_by_clock(s32, s32);
extern void hero_start_pose_offset(f32, f32, f32);
extern void EmitHeroRandomizedMotionEffects(s32, s32, s32);
extern void cam_set_limits_first(f32, f32);
extern void cam_set_limits_second(f32, f32);
extern void cam_set_limits_third(f32, f32);
extern void cam_set_limits_fourth(f32, f32);
extern void ProbeHeroAirborneWallContact(void);
extern s32 ProbeLedgeGrab(s32, s32, s32);
extern s32 hero_slot_item_id(s32);
extern void hero_update_turn_from_anim(void);
extern s32 math_is_below_plane_within_depth(f32);
extern void hero_resolve_stick_direction(f32, s32);
extern void hero_refresh_speed_from_timer(void);
extern void hero_rotate_matrix(f32, f32, f32);
extern void hero_steer_heading(s32, f32, f32, f32);
extern void hero_set_turn_rates(void);
extern void hero_approach_speed(f32, f32);
extern void hero_compute_push_direction(f32);
extern void hero_set_push_direction(s32);
extern void hero_cancel_velocity_into_wall(void);
extern void hero_build_move_impulse(f32, f32);
extern f32 hero_get_speed_along_forward(s32);
extern void hero_approach_velocity(f32);
extern void ApplyHeroGravityAndJumpMotion(void);
extern void UpdateHeroVelocityForState(void);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_apply_mode_pose_offsets(void);
extern void hero_apply_mode_pose_offsets(void);
extern void UpdateHeroLeanAndSwayParameters(void);
extern void hero_shrink_vector_by_amount(f32);
extern f32 hero_get_direction_angle_delta(s32, s32);
extern s32 hero_play_sound(s32, s32);
extern void snd_update_slot_object(s32, s32, s32);
extern void hero_try_surface_push_response(f32, f32, f32);
extern void part_emit_effects_at_nearby_mobys(s32, s32);
extern void hero_setup_attached_object_transform(void);
extern s32 hero_try_start_grab(void);
extern void set_hero_animation(s32, s32, f32);
extern void hero_apply_mode_transform(s32, s32, f32);
extern void hero_build_relative_point(s32, s32, f32, f32, f32);
extern void hero_apply_mode_transform_reversed(s32, s32, f32);
extern void cam_offset_point_by_side_direction(s32, s32, f32);
extern void cam_offset_point_in_view_space(s32, s32, f32);
extern void cam_project_vector_onto_view_plane(s32, s32);
extern f32 cam_get_view_space_vector_length(s32);
extern f32 cam_get_view_space_height(s32);
extern void cam_set_view_space_height(s32, s32, f32);
extern void cam_set_view_space_vector_length(s32, s32, f32);
extern s32 queue_copy_record_by_index(s32);
extern s32 func_L00_002EE4D8(s32, s32, f32);
extern s32 math_lerp_int(s32, s32, f32);
extern void level_init_pending_slot(s32, s32);
extern void level_append_record_to_table(s32, s32, s32, f32);
extern void moby_update_transform_history_followers(s32, s32);
extern s32 math_update_angle_and_blend(s32, s32, s32, f32);
extern f32 ReadPadFloatHistory(s32);
extern void *part_spawn_two_point_effect(s32, s32, f32);
extern s32 path_advance_index(s32, s32, s32, s32);
extern s32 Spline_AdvanceByDistance(s32, s32, s32, s32, s32, f32);
extern s32 find_nearest_path_point(s32, s32, s32, s32, s32, s32, f32, f32, f32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern s32 shooter_update_ranged_attack(s32);
extern s32 hero_get_weapon_anim_id(s32);
extern void ClipHeroVelocityAgainstWall(s32);
extern s32 g_hero_sound_flag_2;
extern char g_impact_effect_data_alt[] MACRO_ADDR;
extern void moby_raise_state_to_eight();
extern void moby_raise_state_to_eight_copy();

/* Updates the hero's state machine each frame: reads the stick and buttons and runs the movement for the current state. */
void hero_l01_update_state_machine_us2(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 vec_0[4] __attribute__((aligned(16)));
    f32 vec_10[4] __attribute__((aligned(16)));
    f32 vec_20[8] __attribute__((aligned(16)));
    f32 vec_40[4] __attribute__((aligned(16)));
    f32 vec_50[4] __attribute__((aligned(16)));
    f32 vec_60[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* ptr_var_v0_3_u2;
    void* ptr_var_s1_5_u2;
    f32 float_var_12_16_u2;
    void* ptr_var_a1_5_u2;
    s32 int_var_a0_2_u2;
    void* ptr_var_s0_3_u2;
    s32 int_var_v0_8_u2;
    s32 int_var_v1_4_u2;
    void* ptr_var_a0_13_u2;
    s32 int_var_a0_2_u3;
    void* ptr_var_s0_3_u3;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 stack_e0;
    f32 stack_e4;
    f32 stack_e8;
    f32 stack_ec;
    f32 stack_f0;
    f32 stack_f4;
    f32 stack_f8;
    s32 stack_fc;
    f32 stack_100;
    s32 stack_104;
    f32 stack_108;
    f32 stack_10c;
    f32 stack_110;
    s32 stack_114;
    s32 stack_118;
    s32 stack_11c;
    f32 float_val_0;
    f32 float_val_0_10;
    f32 float_val_0_11;
    f32 float_val_0_12;
    f32 float_val_0_13;
    f32 float_val_0_14;
    f32 float_val_0_15;
    f32 float_val_0_16;
    f32 float_val_0_17;
    f32 float_val_0_18;
    f32 float_val_0_19;
    f32 float_val_0_20;
    f32 float_val_0_21;
    f32 float_val_0_22;
    f32 float_val_0_23;
    f32 float_val_0_24;
    f32 float_val_0_25;
    f32 float_val_0_26;
    f32 float_val_0_27;
    f32 float_val_0_28;
    f32 float_val_0_29;
    f32 float_val_0_2;
    f32 float_val_0_30;
    f32 float_val_0_3;
    f32 float_val_0_4;
    f32 float_val_0_5;
    f32 float_val_0_6;
    f32 float_val_0_7;
    f32 float_val_0_8;
    f32 float_val_0_9;
    f32 float_val_12;
    f32 float_val_12_2;
    f32 float_val_12_3;
    f32 float_val_12_4;
    f32 float_val_12_5;
    f32 float_val_12_6;
    f32 float_val_12_7;
    f32 float_val_1;
    f32 float_val_1_10;
    f32 float_val_1_11;
    f32 float_val_1_12;
    f32 float_val_1_13;
    f32 float_val_1_14;
    f32 float_val_1_15;
    f32 float_val_1_16;
    f32 float_val_1_17;
    f32 float_val_1_2;
    f32 float_val_1_3;
    f32 float_val_1_4;
    f32 float_val_1_5;
    f32 float_val_1_6;
    f32 float_val_1_7;
    f32 float_val_1_8;
    f32 float_val_1_9;
    f32 float_val_20;
    f32 float_val_20_10;
    f32 float_val_20_11;
    f32 float_val_20_12;
    f32 float_val_20_13;
    f32 float_val_20_14;
    f32 float_val_20_15;
    f32 float_val_20_16;
    f32 float_val_20_17;
    f32 float_val_20_18;
    f32 float_val_20_19;
    f32 float_val_20_2;
    f32 float_val_20_3;
    f32 float_val_20_4;
    f32 float_val_20_5;
    f32 float_val_20_6;
    f32 float_val_20_7;
    f32 float_val_20_8;
    f32 float_val_20_9;
    f32 float_val_21;
    f32 float_val_21_2;
    f32 float_val_21_3;
    f32 float_val_22;
    f32 float_val_22_2;
    f32 float_val_22_3;
    f32 float_val_24;
    f32 float_val_2;
    f32 float_val_2_2;
    f32 float_val_2_3;
    f32 float_val_2_4;
    f32 float_val_2_5;
    f32 float_val_2_6;
    f32 float_val_2_7;
    f32 float_val_3;
    f32 float_var_0;
    f32 float_var_0_10;
    f32 float_var_0_11;
    f32 float_var_0_12;
    f32 float_var_0_13;
    f32 float_var_0_14;
    f32 float_var_0_15;
    f32 float_var_0_2;
    f32 float_var_0_3;
    f32 float_var_0_4;
    f32 float_var_0_5;
    f32 float_var_0_6;
    f32 float_var_0_7;
    f32 float_var_0_8;
    f32 float_var_0_9;
    f32 float_var_12;
    f32 float_var_12_10;
    f32 float_var_12_11;
    f32 float_var_12_13;
    f32 float_var_12_14;
    f32 float_var_12_15;
    f32 float_var_12_16;
    f32 float_var_12_17;
    f32 float_var_12_18;
    f32 float_var_12_19;
    f32 float_var_12_20;
    f32 float_var_12_21;
    f32 float_var_12_22;
    f32 float_var_12_4;
    f32 float_var_12_5;
    f32 float_var_12_6;
    f32 float_var_12_7;
    f32 float_var_12_8;
    f32 float_var_12_9;
    f32 float_var_14;
    f32 float_var_14_2;
    f32 float_var_1;
    f32 float_var_1_2;
    f32 float_var_1_3;
    f32 float_var_1_4;
    f32 float_var_1_5;
    f32 float_var_20;
    f32 float_var_20_10;
    f32 float_var_20_11;
    f32 float_var_20_12;
    f32 float_var_20_13;
    f32 float_var_20_2;
    f32 float_var_20_3;
    f32 float_var_20_4;
    f32 float_var_20_5;
    f32 float_var_20_6;
    f32 float_var_20_7;
    f32 float_var_20_8;
    f32 float_var_20_9;
    f32 float_var_21;
    f32 float_var_21_2;
    f32 float_var_21_3;
    f32 float_var_21_4;
    f32 float_var_21_5;
    f32 float_var_21_6;
    f32 float_var_21_7;
    f32 float_var_22;
    f32 float_var_22_2;
    f32 float_var_23;
    f32 float_var_2;
    f32 float_var_2_2;
    f32 float_var_2_3;
    f32 float_var_2_4;
    f32 float_var_2_5;
    s16 int_val_a2_5;
    s32 int_val_v0_4;
    s16 int_val_v0_8;
    s32 int_val_v1_10;
    s32 int_val_v1_9;
    s32 int_val_a0_21;
    s32 int_val_a0_3;
    s32 int_val_a0_5;
    s32 int_val_a0_7;
    s32 int_val_a0_8;
    s32 int_val_a0_9;
    s32 int_val_a1_3;
    s32 int_val_a1_4;
    s32 int_val_a1_5;
    s32 int_val_a1_7;
    s32 int_val_a1_8;
    s32 int_val_a2;
    s32 int_val_a2_2;
    s32 int_val_a2_3;
    s32 int_val_a2_4;
    s32 int_val_s0_5;
    s32 int_val_s0_9;
    s32 int_val_s7;
    s32 int_val_v0;
    s32 int_val_v0_12;
    s32 int_val_v0_13;
    s32 int_val_v0_14;
    s32 int_val_v0_15;
    s32 int_val_v0_16;
    s32 int_val_v0_17;
    s32 int_val_v0_2;
    s32 int_val_v1_12;
    s32 int_val_v1_14;
    s32 int_val_v1_16;
    s32 int_val_v1_18;
    s32 int_val_v1_20;
    s32 int_val_v1_21;
    s32 int_val_v1_22;
    s32 int_val_v1_23;
    s32 int_val_v1_24;
    s32 int_val_v1_26;
    s32 int_val_v1_34;
    s32 int_val_v1_35;
    s32 int_val_v1_4;
    s32 int_val_v1_5;
    s32 int_val_v1_6;
    s32 int_val_v1_7;
    s32 int_val_v1_8;
    s32 int_var_a0;
    s32 int_var_a0_10;
    s32 int_var_a0_11;
    s32 int_var_a0_12;
    s32 int_var_a0_2;
    s32 int_var_a0_4;
    s32 int_var_a0_5;
    s32 int_var_a0_8;
    s32 int_var_a0_9;
    s32 int_var_a1_2;
    s32 int_var_a2;
    s32 int_var_s0;
    s32 int_var_s0_2;
    s32 int_var_s1;
    s32 int_var_s1_2;
    s32 int_var_s1_3;
    s32 int_var_s7;
    s32 int_var_v0;
    s32 int_var_v0_2;
    s32 int_var_v0_4;
    s32 int_var_v0_5;
    s32 int_var_v0_6;
    s32 int_var_v0_7;
    s32 int_var_v0_8;
    s32 int_var_v1;
    s32 int_var_v1_2;
    s32 int_var_v1_3;
    s32 int_var_v1_4;
    s32* ptr_var_s1_4;
    s32* ptr_var_s1_6;
    u16 int_val_v0_3;
    u16 int_val_v1_11;
    u16 int_val_v1_2;
    u32 int_val_a0;
    u32 int_val_v1;
    u32 int_val_v1_13;
    u32 int_val_v1_27;
    u32 int_val_v1_28;
    u32 int_val_v1_29;
    u32 int_val_v1_30;
    u32 int_val_v1_31;
    u32 int_val_v1_33;
    u32 int_val_v1_36;
    u32 int_val_v1_3;
    u32 int_var_a1_3;
    u8 int_val_a0_14;
    u8 int_val_a0_2;
    u8 int_val_v1_25;
    u8 int_var_a0_6;
    void* ptr_val_a0_10;
    void* ptr_val_a0_11;
    void* ptr_val_a0_12;
    void* ptr_val_a0_13;
    void* ptr_val_a0_15;
    void* ptr_val_a0_16;
    void* ptr_val_a0_17;
    void* ptr_val_a0_4;
    void* ptr_val_a0_6;
    void* ptr_val_a1;
    void* ptr_val_a1_2;
    void* ptr_val_a1_6;
    void* ptr_val_fp;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* ptr_val_s0;
    void* ptr_val_s0_2;
    void* ptr_val_s0_3;
    void* ptr_val_s0_4;
    void* ptr_val_s0_6;
    void* ptr_val_s0_7;
    void* ptr_val_s0_8;
    void* ptr_val_s1;
    void* ptr_val_s1_2;
    void* ptr_val_s1_3;
    void* ptr_val_s1_4;
    void* ptr_val_s1_5;
    void* ptr_val_s1_6;
    void* ptr_val_s1_7;
    void* ptr_val_s1_8;
    void* ptr_val_s2;
    void* ptr_val_s2_2;
    void* ptr_val_s2_3;
    void* ptr_val_s2_4;
    void* ptr_val_s2_5;
    void* ptr_val_s4;
    void* ptr_val_s4_2;
    void* ptr_val_s5;
    void* ptr_val_v0_10;
    void* ptr_val_v0_5;
    void* ptr_val_v0_6;
    void* ptr_val_v0_7;
    void* ptr_val_v0_9;
    void* ptr_val_v1_15;
    void* ptr_val_v1_17;
    void* ptr_val_v1_32;
    void* ptr_val_v1_37;
    void* ptr_val_v1_38;
    void* ptr_val_v1_39;
    void* ptr_var_a0_13;
    void* ptr_var_a0_7;
    void* ptr_var_a1_5;
    void* ptr_var_s0_3;
    void* ptr_var_s1_5;
    void* ptr_var_v0_3;

    stack_114 = ((Hero *)g_hero_state)->i[0x2298/4];
    ptr_val_fp = ((Hero *)g_hero_state)->ptr[0x2290/4];
    stack_118 = (s32) M2C_FIELD(ptr_val_fp, u8* , 0x43);
    switch (((Hero *)g_hero_state)->u[0x2294/4]) {                              /* switch 1 */
    case 0x0:                                       /* switch 1 */
    case 0x1:                                       /* switch 1 */
    case 0x3:                                       /* switch 1 */
    case 0x4:                                       /* switch 1 */
    case 0x1C:                                      /* switch 1 */
    case 0x1D:                                      /* switch 1 */
    case 0x1E:                                      /* switch 1 */
    case 0x39:                                      /* switch 1 */
    case 0x6D:                                      /* switch 1 */
    case 0x6F:                                      /* switch 1 */
    case 0x7D:                                      /* switch 1 */
        hero_build_move_impulse(0.5f, 0.033333335f);
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        int_val_v1 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_val_v1 == 1) || (int_val_v1 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vec_0) = 0;
                vec_0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vec_0), (s32)&g_hero_matrix_work[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_matrix_work)->f[0];
                hero_steer_heading(0, 1.0f, 0.0f, 2.9088826f);
                if ((((Hero *)g_hero_state)->b[0x22BB] != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] == 0x78)) {
                    if (((Hero *)g_progress_statistics)->uh[0xD8/2] < 0xFFFF) {
                        ((Hero *)g_progress_statistics)->uh[0xD8/2]++;
                    }
                    if (g_frame_counter > ((Hero *)g_progress_statistics)->u[0xDC/4]) {
                        ((Hero *)g_progress_statistics)->u[0xDC/4] = g_frame_counter;
                    }
                    ((Hero *)g_progress_statistics)->u[0xE0/4] = ((Hero *)g_progress_statistics)->u[0xE0/4] | (1 << g_current_map_index) | 0x80000000;
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 3) {
            if (hero_try_start_grab() != 0) {
                break;
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (int_val_a0_2 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (int_val_a0_2 == 0xE)) || (int_val_a0_2 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    int_val_a0_3 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    int_val_a0_3 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != int_val_a0_3) {
                        set_hero_animation(int_val_a0_3, 0, 5.0f);
                    }
                    float_val_0 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = float_val_0;
                    if (float_val_0 < 0.55f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 0.55f;
                    }
                    if (((Hero *)g_hero_state)->f[0xC20/4] > 2.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 2.5f;
                    }
                } else if (((Hero *)g_hero_state)->f[0x1A4/4] == 0.0f) {
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != 0xD) {
                        set_hero_animation(0xD, 0, 7.0f);
                    }
                }
            }
        }
            int_val_v1_3 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (int_val_v1_3 == 3) {
                float_var_12 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (float_var_12 > 1.0f) {
                    float_var_12 = 1.0f;
                }
                ptr_val_a0_4 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                float_var_20 = float_var_12 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = float_var_20;
                if (M2C_FIELD(ptr_val_a0_4, u8* , 0x42) == M2C_FIELD(ptr_val_a0_4, u8* , 0x43)) {
                    float_var_1 = ((Hero *)g_hero_state)->f[0x174/4] / float_var_20;
                    if ((float_var_1 > 5.0f) && ((f32) M2C_FIELD(ptr_val_a0_4, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, float_var_1, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (int_val_v1_3 == 4) {
                float_var_20 = 0.0075000003f;
            } else {
                float_var_20 = 0.004916667f;
            }
            hero_approach_speed(0.0f, float_var_20);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(float_var_20);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                int_var_a0_2 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(int_var_a0_2, int_var_a0_2 + 0x30, 0.0061111115f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.015000001f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                ClipHeroVelocityAgainstWall(0);
                if (((Hero *)g_hero_state)->h[0x34E/2] == 0) {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
                } else {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
                    hero_cancel_velocity_into_wall();
                }
            }
        break;
    case 0x85:                                      /* switch 1 */
        ptr_val_a1_2 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)ptr_val_a1_2 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)ptr_val_a1_2 + 0xF0);
        break;
    case 0x2F:                                      /* switch 1 */
        anim2F = -1;
        blend2F = 0;
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            hero_build_move_impulse(0.7f, 0.0f);
        } else {
            hero_build_move_impulse(0.5f, 0.033333335f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        hero_approach_speed(0.004916667f, 0.004916667f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.004916667f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)(g_hero_state + 0xF0)) + 0x20), 0.0069444445f);
            hero_cancel_velocity_into_wall();
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.015000001f);
        }
        if ((anim2F != -1) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation(anim2F, 0, (f32) blend2F);
        } else {
            ptr_val_v1_15 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr_val_v1_15, u8* , 0x60) & 2) && (M2C_FIELD(ptr_val_v1_15, u8* , 0x42) == 0x36)) {
                set_hero_animation(hero_get_weapon_anim_id(0), 0, 5.0f);
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_anim_timing_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        int_var_s1_2 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            int_var_s1_2 = 1;
        }
        int_val_a1_4 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (int_val_a1_4 != 0) {
            FastVecSub((s32)((TI128*)vec_0), int_val_a1_4 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            float_val_0_14 = cam_get_view_space_vector_length((s32)((TI128*)vec_0));
            if (((float_val_0_14 > 2.0f) && (float_val_0_14 < 5.0f)) || (int_var_s1_2 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
            }
            hero_approach_speed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length((s32) ((TI128*)vec_10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_10));
        } else {
            if ((int_var_s1_2 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
            }
            hero_approach_speed(0.004166667f, 0.004166667f);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4]);
        }
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
            hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)g_hero_state)->f[0xC38/4] < 25.0f) {
            hero_l00_select_aim_target(8.0f, 1.0471977f, 1.0471977f);
        }
        float_val_1_6 = ((Hero *)g_hero_state)->f[0x31C/4];
        float_var_21 = 0.12833333f;
        if (float_val_1_6 > 2.25f) {
            float_var_21 = 0.064166665f;
        } else if (float_val_1_6 > 1.8f) {
            float_var_21 = 0.08983333f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(vec_0, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), -0.5f);
            vec_scale_to_length((s32) (TI128*)vec_10, (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vec_20), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) (TI128*)vec_10);
            vec_20[3] = 5627.925f;
            (*(u8*)((u8*)vec_20+0x19)) = 1;
            (*(u16*)((u8*)vec_20+0x1A)) = 0x47;
            (*(u8*)((u8*)vec_20+0x18)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)vec_0), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vec_20));
        }
        if (math_is_below_plane_within_depth(25.7f) != 0) {
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (g_hero_override_flag != 0) {
                ((Hero *)g_drive_settings)->f[0x180/4] = 0.1f;
                ((Hero *)g_drive_settings)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)g_drive_settings)->i[0x16C/4] = 0;
            }
        }
        int_val_v1_18 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xE;
        if (int_val_v1_18 < 9) {
            ptr_val_s0_2 = ((void*)g_hero_state) + 0xF0;
            stack_f8 = cam_get_view_space_height((s32) ptr_val_s0_2);
            ApproachValue((s32) &stack_f8, float_var_21, 0.041666668f);
            cam_set_view_space_height((s32) ptr_val_s0_2, (s32) ptr_val_s0_2, stack_f8);
        } else if (int_val_v1_18 > lim3) {
            ptr_val_s1_4 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_val_s1_4, (s32) ptr_val_s1_4, 0.036111113f);
            if (cam_get_view_space_height((s32) ptr_val_s1_4) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            float_var_20_5 = -0.6166667f;
            if (g_hero_input_lock != 0) {
                float_var_20_5 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) ptr_val_s1_4) < float_var_20_5) {
                cam_set_view_space_height((s32) ptr_val_s1_4, (s32) ptr_val_s1_4, float_var_20_5);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_anim_timing_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        int_var_a0_8 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (int_var_a0_8 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                int_var_s1_3 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    ptr_val_s0_3 = ((void*)g_hero_state) + 0xBC0;
                    float_var_20_6 = hero_get_direction_angle_delta((s32) ptr_val_s0_3, 0);
                    float_var_0_3 = hero_get_direction_angle_delta((s32) ptr_val_s0_3, 1);
                } else {
                    float_var_20_6 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    float_var_0_3 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (float_var_0_3 < 4.3633237f) {
                    int_var_s1_3 = 1;
                }
                if (float_var_20_6 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (float_var_0_3 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (int_var_s1_3 != 0) {
                    hero_steer_heading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    hero_steer_heading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    int_var_a0_9 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xC)) {
                        int_var_a0_9 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        int_var_a0_9 = 0;
                    }
                    if (int_var_a0_9 != 0) {
                        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x15) {
                            hero_l00_select_aim_target(14.0f, 0.52359885f, 0.78539824f);
                        } else {
                            UpdateHeroAimTarget(64.0f, 0.17453295f, 0.3490659f);
                        }
                    }
                }
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) == 0x1A) && (math_is_below_plane_within_depth(33.0f) != 0)) {
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x15) {
                hero_setup_attached_object_transform();
            }
        }
        hero_approach_speed(0.010277778f, 0.007777778f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
            break;
        }
        break;
    case 0x13:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_anim_timing_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        int_val_a1_5 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ptr_val_s2_3 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_anim_timing_table;
        if ((int_val_a1_5 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            ptr_val_s1_5 = ((void*)g_hero_state) + 0x80;
            float_var_12_13 = vec_distance_xy(int_val_a1_5 + 0x10, (s32) ptr_val_s1_5);
            if ((*(s32*)&g_hero_input_lock) != 0) {
                float_var_12_13 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) ptr_val_s1_5);
            }
            float_var_12_13 = float_var_12_13 - 0.5f;
            if (float_var_12_13 < 0.0f) {
                float_var_12_13 = 0.0f;
            }
            int_val_v1_20 = M2C_FIELD(ptr_val_s2_3, s32* , 4);
            if (int_val_v1_20 == 0) {
                float_var_0_4 = 0.75f;
                float_var_21_3 = 0.8f;
                float_var_22 = 4.0f;
            } else if (int_val_v1_20 == 1) {
                float_var_0_4 = 0.6f;
                float_var_21_3 = 1.7f;
                float_var_22 = 4.0f;
            } else {
                float_var_0_4 = 1.3f;
                float_var_21_3 = 1.7f;
                float_var_22 = 1.9f;
            }
            float_val_20_8 = float_var_12_13 - float_var_0_4;
            if (math_fabs(float_val_20_8) < (float_var_21_3 + 3.0f)) {
                float_var_12_15 = float_val_20_8 * 1.1111112f;
                if (float_var_22 < float_var_12_15) {
                    float_var_12_15 = float_var_22;
                }
                if (float_var_12_15 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = float_var_12_15;
                }
            }
        }
        int_val_v1_21 = M2C_FIELD(ptr_val_s2_3, s32* , 4);
        switch (int_val_v1_21) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            float_val_1_7 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (float_val_1_7 < 9.0f)) {
                if (float_val_1_7 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (float_val_1_7 > 7.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.075f;
                } else {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.095f;
                }
            }
            break;
        case 2:
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < 12.0f)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.06166667f;
            }
            break;
        }
        ApproachValue((s32)(g_hero_state + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
        if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
            float_var_0_5 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            float_var_0_5 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        float_val_1_8 = math_fabs(float_var_0_5);
        if ((M2C_FIELD(ptr_val_s2_3, s32* , 4) == 1) && (float_var_0_5 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (float_val_1_8 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        int_var_v1_3 = 1;
        if ((M2C_FIELD(ptr_val_s2_3, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            int_var_v1_3 = 0;
        }
        if (int_var_v1_3 != 0) {
            hero_l00_select_aim_target(5.0f, 0.78539824f, 0.78539824f);
        }
    }
        hero_approach_speed(0.010277778f, 0.007777778f);
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0xBC0));
            } else {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
            }
        } else {
            hero_compute_push_direction(99999.0f);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0x130), 0.0069444445f);
        } else {
            ptr_val_a0_12 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_val_a0_12, (s32) ptr_val_a0_12, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&g_hero_input_lock) != 0) {
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xBD0), ((Hero *)g_hero_state)->f[0x1B4/4]);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 0.0f) {
                hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0x130), 0.0069444445f);
            } else {
                cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            }
            FastVecScale((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0xBD0), -1.0f);
        } else {
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xBF0/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xBF0/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 0.0f) {
                ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0x128/4] - 0.0069444445f);
            } else {
                ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = FastAddRotations(((Hero *)g_hero_state)->f[0xBF0/4], 3.1415927f);
        }
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
        break;
    case 0x1F:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)g_hero_state)->i[0x1B8/4] < 4) {
            hero_l00_select_aim_target(11.0f, 0.8726647f, -1.0f);
        }
        lim = 0xA;
        lim2 = 0x12;
        int_val_v1_22 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (int_val_v1_22 > lim) {
            if (int_val_v1_22 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            ptr_val_s0_4 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ptr_val_s0_4);
            level_append_record_to_table((s32) ptr_val_s0_4, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) ptr_val_s0_4, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) ptr_val_s0_4, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)g_hero_state)->i[0x1B8/4] > lim2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), sel1F);
        if (((Hero *)g_hero_state)->i[0x1B8/4] > lim) {
            hero_approach_speed(0.05277778f, 0.025f);
        }
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x1F) {
            int_val_v1_24 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((int_val_v1_24 > lim) && (int_val_v1_24 < 0x16)) {
                ptr_val_s2_4 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (ptr_val_s2_4 != 0) {
                    ptr_val_s1_6 = ((void*)g_hero_state) + 0x80;
                    vec_20[4] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_20[5] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_20[6] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec_0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)&vec_20[4]));
                    (*(u8*)((u8*)vec_10+9)) = 3;
                    vec_0[3] = 5627.925f;
                    (*(u8*)((u8*)vec_10+8)) = 0;
                    float_val_22_2 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vec_10+10)) = M2C_FIELD(ptr_val_s2_4, u16* , 0xAA);
                    vec_40[0] = math_fast_sin_or_cos_a(float_val_22_2) * 0.8f;
                    float_val_0_15 = math_fast_sin_or_cos_b(float_val_22_2) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = float_val_0_15;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ptr_val_s1_6);
                    part_emit_effects_at_nearby_mobys((s32) ptr_val_s2_4, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ptr_val_s2_4, (s32)((TI128*)vec_0)));
                    float_val_22_2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(float_val_22_2) * 0.8f;
                    float_val_0_17 = math_fast_sin_or_cos_b(float_val_22_2) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = float_val_0_17;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ptr_val_s1_6);
                    part_emit_effects_at_nearby_mobys((s32) ptr_val_s2_4, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec_0)));
                    float_val_22_2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(float_val_22_2) * 0.8f;
                    float_val_0_19 = math_fast_sin_or_cos_b(float_val_22_2) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = float_val_0_19;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ptr_val_s1_6);
                    part_emit_effects_at_nearby_mobys((s32) ptr_val_s2_4, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ptr_val_s2_4, (s32)((TI128*)vec_0)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ClipHeroVelocityAgainstWall(1);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x120, 0.0061111115f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        break;
    case 0x22:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
            qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
            hero_steer_heading(0, 0.04f, 0.2f, 0.2821616f);
        } else {
            hero_l00_select_aim_target(11.0f, 0.8726647f, -1.0f);
        }
        hero_approach_speed(0.008333334f, 0.009722223f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.015000001f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        break;
    case 0x2:                                       /* switch 1 */
    case 0x70:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->h[0x1454/2] == 0) {
            if (((Hero *)g_hero_state)->f[0x174/4] < 0.028333336f) {
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
                if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 2.0943954f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
                    ((Hero *)g_hero_state)->b[0x40F] = 1U;
                }
            }
            float_val_20_9 = ReadPadFloatHistory(1);
            if ((FastDiffRots(float_val_20_9, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
                ((Hero *)g_hero_state)->b[0x40F] = 1U;
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
            }
            if (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) < 0.087266475f) {
                ((Hero *)g_hero_state)->b[0x40C] = 0U;
            }
        }
        if ((((Hero *)g_hero_state)->b[0x40F] != 0) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) < 0.06981318f)) {
            ((Hero *)g_hero_state)->b[0x40F] = 0U;
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            if (((Hero *)g_hero_state)->i[0x410/4] != 0) {
                ((Hero *)g_hero_state)->b[0x40F] = 1U;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0x3F0/16]);
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x408/4];
        } else {
            hero_refresh_speed_from_timer();
            if ((hero_slot_item_id(0) == 0xA) && ((((Hero *)g_hero_state)->f[0x24BC/4] == 1.0f) || (((Hero *)g_hero_state)->i[0x410/4] != 0)) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                qcopy(&((Hero *)g_hero_state)->q[0x3F0/16], &((Hero *)g_hero_state)->q[0x190/16]);
                ((Hero *)g_hero_state)->i[0x410/4] = 1;
                ((Hero *)g_hero_state)->f[0x408/4] = ((Hero *)g_hero_state)->f[0x1A0/4];
            } else {
                qcopy(&((Hero *)g_hero_state)->q[0x3F0/16], &((Hero *)g_hero_state)->q[0x0/16]);
                ((Hero *)g_hero_state)->f[0x408/4] = ((Hero *)g_hero_state)->f[0x98/4];
            }
        }
        if (((Hero *)g_hero_state)->f[0xA70/4] > 0.0f) {
            pA60 = ((void*)g_hero_state) + 0xA60;
            hero_build_move_impulse(0.7f, 0.0f);
            (*(TI128*)vec_0) = ((Hero *)g_hero_state)->q[0xA60/16];
            float_val_1_9 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vec_0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = float_val_1_9;
            if (float_val_1_9 < 0.011666667f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.011666667f;
            }
            vec_clear_128((s32) pA60);
        }
        float_var_20_7 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                float_val_2_2 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (float_val_2_2 > 0.78539824f)) {
                    float_var_20_7 = 0.0f;
                }
                hero_set_turn_rates();
            }
        }
        hero_apply_mode_pose_offsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            float_var_2_2 = 0.09916667f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.029178405f);
            if (float_var_2_2 < 0.0f) {
                float_var_2_2 = 0.0f;
            }
            if (float_var_2_2 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = float_var_2_2;
            }
        }
        k005 = float_var_20_7 * 0.005f;
        float_var_20_8 = 0.0055555557f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            float_var_1_2 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (float_var_1_2 > 1.0f) {
                float_var_1_2 = 1.0f;
            }
            if (float_var_1_2 < 0.2f) {
                float_var_1_2 = 0.2f;
            }
            float_var_20_8 = 0.004722222f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_var_1_2);
        }
        float_val_2_3 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (float_val_2_3 > 0.6108653f)) {
            float_var_1_3 = 1.0f - (float_val_2_3 * 0.4f);
            if (float_var_1_3 < 0.0f) {
                float_var_1_3 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_var_1_3);
        }
        hero_approach_speed(k005, float_var_20_8);
        if ((((Hero *)g_hero_state)->b[0x40C] != 0) || (((Hero *)g_hero_state)->h[0x1454/2] != 0)) {
            if (((Hero *)g_hero_state)->b[0x22C3] == 0) {
                if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                    hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
                } else {
                    hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1A0/4]);
                }
            } else if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x1440));
            } else {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x190));
            }
        } else {
            hero_compute_push_direction(99999.0f);
        }
        ClipHeroVelocityAgainstWall(1);
        if (((Hero *)g_hero_state)->h[0x214/2] != 0) {
            hero_try_surface_push_response(5.0f, 0.2f, 0.35f);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        break;
    case 0x7B:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        hero_resolve_stick_direction(1.0f, 0);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.19166668f;
        pad_clamp_stick_to_unit_range((s32)((TI128*)vec_0), (s32) (((void*)g_hero_state) + 0x9F0), 0.17f);
        float_var_21_4 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * vec_0[0];
        if ((*(s32*)&g_hero_input_lock) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3C) {
                float_var_21_4 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, float_var_21_4);
        }
        hero_approach_speed(0.027777778f, 0.004166667f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&g_hero_input_lock) != 0) {
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vec_10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32)(g_hero_state + 0xE0));
        int_val_v0_12 = coll_process_hit(0.57f, (s32) ((TI128*)vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (int_val_v0_12 != 0) {
            FastVecScale((s32) ((TI128*)vec_20), (s32)(g_hero_state + 0x110), 7.0f);
            for (int_var_s0 = 0; int_var_s0 < int_val_v0_12; int_var_s0++) {
                if (moby_is_in_special_class_range(((s32 *)g_contact_moby_list)[int_var_s0]) != 0) {
                    part_queue_impact_effect(((s32 *)g_contact_moby_list)[int_var_s0], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.017f, 0.3f);
        cam_set_limits_third(0.025f, 0.3f);
        cam_set_limits_fourth(0.03f, 0.27f);
        float_var_2_3 = float_var_21_4 * 27.0f;
        if (float_var_2_3 > 1.7f) {
            float_var_2_3 = 1.7f;
        } else if (float_var_2_3 < -1.7f) {
            float_var_2_3 = -1.7f;
        }
        float_val_0_20 = float_var_2_3 * 0.5f;
        ((Hero *)g_hero_l01_state_copy)->f[0x60/4] = (f32) -float_var_2_3;
        ((Hero *)g_hero_l01_state_copy)->f[0x278/4] = float_val_0_20;
        ((Hero *)g_hero_l01_state_copy)->f[0x1C8/4] = float_val_0_20;
        break;
    case 0x30:                                      /* switch 1 */
        int_val_v1_26 = (*(s32*)&g_current_map_index);
        if (int_val_v1_26 == 0 || (int_val_v1_26 == 1 && g_hero_sound_flag_2 == 0)) {
            snd_update_slot_object(2, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x13);
        }
        int_var_v0_6 = g_current_map_index;
        if ((u32) int_var_v0_6 < 2U) {
            EmitHeroRandomizedMotionEffects(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects(4, 2, 0);
            vec_0[0] = ((Hero *)g_hero_state)->f[0x80/4] + math_random_float_range(-0.25f, 0.25f);
            vec_0[1] = ((Hero *)g_hero_state)->f[0x84/4] + math_random_float_range(-0.25f, 0.25f);
            vec_0[2] = ((Hero *)g_hero_state)->f[0x88/4] + math_random_float_range(-0.1f, 0.4f);
            FastVecScale((s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x110), 0.9f);
            vec_10[0] += math_random_float_range(-0.011666667f, 0.011666667f);
            vec_10[1] += math_random_float_range(-0.011666667f, 0.011666667f);
            vec_10[2] = M2C_BITWISE(f32, vec_10[2]) + math_random_float_range(0.016666668f, 0.033333335f);
            part_spawn_two_point_effect((s32)((TI128*)vec_0), (s32) ((TI128*)vec_10), math_random_float_range(37800.0f, 75600.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xB40/4];
        float_val_20_11 = ((Hero *)g_hero_state)->f[0x98/4];
        hero_steer_heading(0, 0.033f, 0.3f, 0.069813184f);
        float_var_21_6 = FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], float_val_20_11);
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        hero_shrink_vector_by_amount(0.0019444445f);
        float_val_0_22 = ((Hero *)g_hero_state)->f[0x118/4] - 0.013888889f;
        ((Hero *)g_hero_state)->f[0xF8/4] = float_val_0_22;
        if (float_val_0_22 > -0.011111111f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.011111111f;
        }
        if (float_var_21_6 > 0.023271061f) {
            float_var_21_6 = 0.023271061f;
        }
        float_val_20_12 = float_var_21_6 * 9.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), float_val_20_12 * 0.5f, (s32) (((void*)g_hero_state) + 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), -((Hero *)g_hero_state)->f[0xB44/4], (s32) (((void*)g_hero_state) + 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        ((Hero *)g_hero_l01_state_copy)->f[0x118/4] = (f32) (float_val_20_12 * 2.1f);
        ((Hero *)g_hero_l01_state_copy)->f[0x110/4] = (f32) (float_val_20_12 * 3.5f);
        break;
    case 0x17:                                      /* switch 1 */
    case 0x18:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.04f, 0.2f, 0.10471977f);
        if (((Hero *)g_hero_state)->b[0x22C3] != 2) {
            StepAngleTowardTarget((s32)(g_hero_state + 0x94), 0, 0.0f, 0.078539826f);
        }
        FastVecSub((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0x550), (s32)(g_hero_state + 0x80));
        vec_clamp_length((s32)(g_hero_state + 0xF0), 0.06666667f);
        ApproachValue((s32)(g_hero_state + 0x580), ((Hero *)g_hero_state)->f[0x88/4], 0.050000004f);
        break;
    case 0x19:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)vec_60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &vec_40[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)vec_60));
        } else {
            FastVecCross((s32) &vec_40[0], (s32) ((TI128*)vec_60), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &vec_40[0], (s32) &vec_40[0], 0.2f);
        FastVecAdd((s32) &vec_50[0], (s32)(g_hero_state + 0x80), (s32) &vec_40[0]);
        if ((ProbeLedgeGrab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (ProbeLedgeGrab((s32) &vec_50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec_0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec_0), (s32)(g_hero_state + 0x80));
            int_var_v0_8 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            int_var_v1_4 = (s32)g_hero_l01_state_machine_table;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(int_var_v0_8 + int_var_v1_4) * 0.5f);
        }
        break;
    case 0x76:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09166667f;
        hero_approach_velocity(0.0069444445f);
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.005f);
        break;
    case 0x6:                                       /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        hero_refresh_speed_from_timer();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            UpdateHeroVelocityForState();
        }
        ptr_var_s1_5 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) ptr_var_s1_5, (s32) ptr_var_s1_5, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_var_s1_5) < -0.8333334f) {
            cam_set_view_space_height((s32) ptr_var_s1_5, (s32) ptr_var_s1_5, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        ptr_var_s1_5_u2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ptr_var_s1_5_u2, (s32) ptr_var_s1_5_u2, vec_length_xy((s32) ptr_var_s1_5_u2) * 0.9f);
        hero_apply_mode_transform((s32) ptr_var_s1_5_u2, (s32) ptr_var_s1_5_u2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_var_s1_5_u2) < -0.8333334f) {
            cam_set_view_space_height((s32) ptr_var_s1_5_u2, (s32) ptr_var_s1_5_u2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        int_var_a0_12 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            int_var_a0_12 = 0;
        }
        if (int_var_a0_12 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            ptr_val_a0_15 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) ptr_val_a0_15, (s32) ptr_val_a0_15, 0.025f);
        } else {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.02f);
        }
        if (((Hero *)g_pad_state)->i[0x1A4/4] & 0x40) {
            ApproachValue((s32)(g_hero_state + 0x5B0), 0.0f, 0.5f);
        }
        hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0075000003f);
        if (cam_get_view_space_height((s32)(g_hero_state + 0xF0)) > 0.10000001f) {
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.10000001f);
        }
        if (cam_get_view_space_height((s32)(g_hero_state + 0xF0)) < -0.20000002f) {
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), -0.20000002f);
        }
        float_val_12_4 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (float_val_12_4 < 0.0f) && (float_val_2_6 = ((Hero *)g_hero_state)->f[0x31C/4], (float_val_2_6 < 1.2f))) {
            float_var_0_10 = (float_val_2_6 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (float_var_0_10 < 0.0f) {
                float_var_0_10 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), float_val_12_4 * float_var_0_10);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (float_val_12_4 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&g_view_l01_space_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.027f, 0.3f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.087266475f);
        float_var_12_19 = 0.0013888889f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            float_var_12_19 = 0.00055555557f;
        }
        hero_approach_velocity(float_var_12_19);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            int_val_a2_3 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (int_val_a2_3 != -1) {
                ptr_val_a0_16 = (int_val_a2_3 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_val_a0_16, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_val_a0_16, u8* , 0x74) != 0)) {
                    snd_stop_voice(int_val_a2_3);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            int_val_a2_4 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (int_val_a2_4 != -1) {
                ptr_val_a0_17 = (int_val_a2_4 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_val_a0_17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_val_a0_17, u8* , 0x74) != 0)) {
                    snd_stop_voice(int_val_a2_4);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        float_var_22_2 = 0.050000004f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            float_var_22_2 = 0.083333336f;
        }
        float_var_23 = 0.72f;
        float_val_1_12 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            float_var_22_2 = 0.12833333f;
            float_var_23 = 0.98640007f;
        }
        if (float_val_1_12 != 0.0f) {
            float_var_23 = float_val_1_12;
        }
        ptr_val_s0_7 = ((void*)g_hero_state) + 0xF0;
        stack_110 = cam_get_view_space_height((s32) ptr_val_s0_7);
        hero_resolve_stick_direction(float_var_22_2, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) ptr_val_s0_7, (s32) ptr_val_s0_7);
        math_spring_float_to_goal((s32) &stack_110, (s32) (((void*)g_hero_state) + 0xA98), -float_var_22_2 * float_var_23, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) ptr_val_s0_7, (s32) ptr_val_s0_7, -stack_110);
        float_val_12_5 = ((Hero *)g_hero_state)->f[0x88/4];
        if (float_val_12_5 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), float_val_12_5, 0.06666667f);
        }
        ProbeHeroAirborneWallContact();
        break;
    case 0x7:                                       /* switch 1 */
    case 0x9:                                       /* switch 1 */
    case 0xA:                                       /* switch 1 */
    case 0xB:                                       /* switch 1 */
    case 0xC:                                       /* switch 1 */
    case 0xD:                                       /* switch 1 */
    case 0xE:                                       /* switch 1 */
    case 0xF:                                       /* switch 1 */
    case 0x10:                                      /* switch 1 */
    case 0x11:                                      /* switch 1 */
    case 0x12:                                      /* switch 1 */
    case 0x1B:                                      /* switch 1 */
    case 0x38:                                      /* switch 1 */
    case 0x45:                                      /* switch 1 */
    case 0x48:                                      /* switch 1 */
    case 0x5B:                                      /* switch 1 */
    case 0x66:                                      /* switch 1 */
    case 0x6E:                                      /* switch 1 */
    case 0x81:                                      /* switch 1 */
    case 0x89:                                      /* switch 1 */
    case 0x92:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x1B) && (((Hero *)g_hero_state)->h[0x24FC/2] == 0) && (((Hero *)g_hero_state)->i[0x1338/4] == 3)) {
            if (math_is_below_plane_within_depth(10.0f) != 0) {
                hero_play_sound(4, 0);
            }
        }
        if ((((Hero *)g_hero_state)->h[0x528/2] != 0) && (((Hero *)g_hero_state)->b[0x1492] != 0)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) ((Hero *)g_hero_state)->f[0x1B4/4];
        } else {
            if (((Hero *)g_hero_state)->b[0x49C] != 0) {
                hero_resolve_stick_direction(0.09916667f, 0);
            }
            hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x4A4/4], 0);
        }
        int_val_a2_5 = ((Hero *)g_hero_state)->h[0x4AC/2];
        int_val_a1_8 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (int_val_a1_8 == int_val_a2_5) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((int_val_a1_8 < int_val_a2_5) && (int_val_v1_33 = ((Hero *)g_hero_state)->u[0x2294/4], (int_val_v1_33 != 0xB)) && (int_val_v1_33 != 0x10) && (int_val_v1_33 != 0xC) && (int_val_v1_33 != 0x11) && (int_val_v1_33 != 0x1B) && (int_val_v1_33 != 0x89) && (int_val_v1_33 != 0x48))) {
            hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
            float_val_20_16 = ((Hero *)g_hero_state)->f[0x1B4/4];
            if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (float_val_20_16 * 0.4f);
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
            ((Hero *)g_hero_state)->f[0x1B4/4] = float_val_20_16;
            if (((Hero *)g_hero_state)->b[0x49C] != 1) {
                hero_approach_speed(((Hero *)g_hero_state)->f[0x500/4], ((Hero *)g_hero_state)->f[0x504/4]);
            }
            if (((Hero *)g_hero_state)->b[0x49C] != 0) {
                if ((*(s32*)&g_hero_state_flags) != 0) {
                    if (((Hero *)g_hero_state)->h[0x34A/2] != 0) {
                        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
                    }
                }
                if (((Hero *)g_hero_state)->b[0x49C] != 0) {
                    hero_shrink_vector_by_amount(((Hero *)g_hero_state)->f[0x504/4]);
                }
            }
            hero_build_move_impulse(0.5f, 0.033333335f);
            if (((Hero *)g_hero_state)->u[0x2294/4] == 9) {
                int_val_v1_34 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (int_val_v1_34 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) int_val_v1_34 * 0.0044444446f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                int_val_v1_35 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (int_val_v1_35 < 0x22) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) int_val_v1_35 * 0.014722222f);
                }
            }
            if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                qcopy(vec_0, &((Hero *)g_hero_state)->q[0x80/16]);
                cam_offset_point_in_view_space((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), 0.5f);
                cam_offset_point_by_side_direction((s32) ((TI128*)vec_10), (s32)((TI128*)vec_0), 0.95f);
                if (CollLine((s32)((TI128*)vec_0), (s32) ((TI128*)vec_10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                    ((Hero *)g_hero_state)->h[0x524/2] = 1;
                }
            }
        } else {
            UpdateHeroVelocityForState();
        }
        float_val_1_14 = ((Hero *)g_hero_state)->f[0x318/4];
        float_val_2_7 = ((Hero *)g_hero_state)->f[0x490/4];
        if (float_val_2_7 < float_val_1_14) {
            float_val_0_29 = float_val_2_7 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = float_val_0_29;
            if (float_val_1_14 < float_val_0_29) {
                ((Hero *)g_hero_state)->f[0x490/4] = float_val_1_14;
            }
        }
        float_val_1_15 = ((Hero *)g_hero_state)->f[0x88/4];
        if (float_val_1_15 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = float_val_1_15;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            float_val_1_16 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (float_val_1_16 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = float_val_1_16;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        int_val_v1_36 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_val_v1_36 == 0x10) || (int_val_v1_36 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vec_0), 1, 0.8f, 0.0f, 0.3f);
                    int_val_v0_17 = coll_process_hit(0.9f, (s32)((TI128*)vec_0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (int_val_v0_17 != 0) {
                        FastVecScale((s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (int_var_s0_2 = 0; int_var_s0_2 < int_val_v0_17; int_var_s0_2++) {
                            if (moby_is_in_special_class_range(((s32 *)g_contact_moby_list)[int_var_s0_2]) != 0) {
                                part_queue_impact_effect(((s32 *)g_contact_moby_list)[int_var_s0_2], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        ApplyHeroGravityAndJumpMotion();
        ProbeHeroAirborneWallContact();
        break;
    case 0x16:                                      /* switch 1 */
        float_var_20_13 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        float_var_0_12 = 0.0011111111f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB)) {
            float_var_0_12 = 0.0027777778f;
        }
        float_var_20_13 = float_var_20_13 - float_var_0_12;
        if (float_var_20_13 < 0.0f) {
            float_var_20_13 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ptr_var_s0_3 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) ptr_var_s0_3, (s32) ptr_var_s0_3, float_var_20_13);
        hero_apply_mode_transform((s32) ptr_var_s0_3, (s32) ptr_var_s0_3, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec_0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_0[0], vec_0[1]);
        float_val_0_30 = vec_length_xy((s32)((TI128*)vec_0));
        if (float_val_0_30 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_0[0], vec_0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = float_val_0_30;
            if (float_val_0_30 < g_hero_speed_param_table[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_speed_param_table[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_speed_param_table[1][1] * 0.016666668f;
            }
            if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.015000001f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x18AC/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        }
        speed62 = 1.0f;
        if (((Hero *)g_hero_state)->b[0x22B4] == 3) {
            hero_steer_heading(0, 0.03f, 0.3f, 0.093084246f);
        } else if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
            hero_steer_heading(0, 0.03f, 0.3f, 0.13089971f);
        } else if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_steer_heading(0, 0.03f, 0.3f, 0.13089971f);
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        hero_approach_speed(speed62 * 0.005f, 0.0055555557f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            ClipHeroVelocityAgainstWall(1);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.0069444445f);
            hero_cancel_velocity_into_wall();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        }
        {
            s32 found, k, m;
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0xE0/16]);
            found = coll_process_hit(((Hero *)g_hero_state)->f[0x264/4] + 0.2f, (s32)((TI128*)vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
            for (k = 0; k < found; k++) {
                m = ((s32 *)g_contact_moby_list)[k];
                if (m != 0) {
                    switch (*(s16 *)(m + 0xAA)) {
                    case 0xCB:
                        part_queue_impact_effect(m, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0xE0), (s32) g_impact_effect_data_alt, 100.0f);
                        break;
                    case 0x1366:
                        moby_raise_state_to_eight();
                        break;
                    case 0x1367:
                        moby_raise_state_to_eight_copy();
                        break;
                    }
                }
            }
        }
        break;
    case 0x63:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec_0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)vec_0), (s32)(g_hero_state + 0x160)) < 0.0f) {
            vec_clear_128((s32)(g_hero_state + 0x160));
        }
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.0075000003f);
        ClipHeroVelocityAgainstWall(0);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0x18A0)) - 0x1790, 0.0069444445f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.015000001f);
        break;
    case 0x3C:                                      /* switch 1 */
    case 0x64:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    case 0x65:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((f32) ((Hero *)g_hero_state)->i[0x18C0/4] * 0.5f) < (((Hero *)g_hero_state)->f[0x334/4] - ((Hero *)g_hero_state)->f[0x88/4])) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.004166667f;
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.016666668f;
        }
        break;
    case 0x78:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.016666668f;
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (stack_114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (stack_118 != M2C_FIELD(ptr_val_fp, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
