/* func_L11_002D22C8 (Joba): the hero's per-frame state handler, a 148-way switch on the
   state at 0x2294 over 47 bodies (22324 bytes, level 11 only).  One function: one prologue,
   one return.  Same routine as the Yeedil, Grelbin and Dobbo handlers with a different set of
   states; state 0x71 comes from the Todano/Damosel copy.

   The unit takes the Yeedil unit's flags (config/cflags.txt); see docs/build/compiler-notes.md for
   each option. */

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 x0[7]; s32 x1C; u8 x20[0xC0]; } LevelInfo;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(d) (0)
extern char g_pad_state[];
extern u8 D_00138320[];
extern f32 D_L11_002A4BB0[];
extern u8 D_00138354[];
extern u8 g_item_slot_to_record[];
extern u8 g_sound_state[];
extern char g_hero_state[];
extern char D_00189F10[];
extern char g_progress_statistics[];
extern u8 D_0018CF10[];
extern u32 D_001A7390 MACRO_ADDR;
extern s32 g_current_map_index MACRO_ADDR;
extern u8 D_001A7B08[0x40] MACRO_ADDR;
extern u8 D_001A7B2A MACRO_ADDR;
extern f32 D_L11_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L11_001A8FF0 MACRO_ADDR;
extern u8 D_L11_001ACEE8[];
extern s32 D_L11_001AFF00 MACRO_ADDR;
extern s32 D_L11_001B2AC8 MACRO_ADDR;
extern s32 D_L11_001B3730 MACRO_ADDR;
extern s32 D_L11_001B3738 MACRO_ADDR;
extern s32 D_L11_001B30C8 MACRO_ADDR;
extern u8 D_L11_001BA780[];
extern u8 D_L11_001BA8D8[];
extern u8 D_L11_001BAB48[];
extern u8 D_L11_001C4D80[];
extern u8 D_L11_00273510[];
extern Rec2C D_L11_00275090[];
extern s32 CollLine(s32, s32, s32, s32, s32);
extern s32 coll_process_hit(f32, s32, s32, s32, s32);
extern void FadeToBlack(s32);
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
extern void vec_fast_normalize_helper(s32, s32, f32);
extern void matrix_mul_vec3(s32, s32, s32);
extern void transform_vector(s32, s32, s32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 mat_fast_helper_a(f32, f32);
extern void euler_to_matrix(s32, s32);
extern void matrix_from_basis_rows(s32, s32);
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern s32 FloatToInt(f32);
extern void gauge_popup_show(s32, s32, s32, f32);
extern s32 CreateMoby(s32);
extern void moby_transform_joint_to_world(s32, s32, s32);
extern void func_002A0F48(s32);
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_signed_float_range(f32, f32);
extern s32 math_solve_quadratic(s32, s32, f32, f32, f32);
extern void make_hit_descriptor(s32, s32, s32, f32, s32);
extern void coll_sweep_from_object(s32, s32, s32, f32, f32, f32, s32, s32, s32);
extern void part_queue_impact_effect(s32, s32, s32, s32, s32, f32);
extern f32 ApproachValue(s32, f32, f32);
extern f32 math_spring_float_to_goal(s32, s32, f32, f32, f32, f32);
extern f32 vec_spring_to_target(s32, s32, s32, f32, f32, f32);
extern f32 math_shortest_angle_delta(s32, f32, f32);
extern void StepAngleTowardTarget(s32, s32, f32, f32);
extern f32 math_approach_with_velocity(s32, f32, s32, f32, f32, f32, s32);
extern s32 moby_is_in_special_class_range(s32);
extern void vec_clamp_length(s32, f32);
extern void vec_build_spherical_offset(s32, f32, f32, f32);
extern void part_spawn_white_flash(s32, s32, s32, f32);
extern s32 part_spawn_bubble(s32, s32, f32, f32);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, s32);
extern void RippleDisturb(s32, s32, void *, f32, f32, f32, f32);
extern void pad_clamp_stick_to_unit_range(s32, s32, f32);
extern void AdjustHeroAnimationSpeedForTargetFrame(f32, f32, f32, f32);
extern f32 math_blend_table_entries_by_clock(s32, s32);
extern void hero_start_pose_offset(f32, f32, f32);
extern void part_spawn_jittered_after_delay(s32, s32);
extern void part_emit_hero_side_particles(s32, s32);
extern void part_emit_hero_trail_spark(s32, s32);
extern void EmitHeroRandomizedMotionEffects(s32, s32, s32);
extern void part_emit_hero_dust_and_debris(s32, s32, s32);
extern void EmitHeroTimedEffects(void);
extern void cam_set_limits_first(f32, f32);
extern void cam_set_limits_second(f32, f32);
extern void cam_set_limits_third(f32, f32);
extern void cam_set_limits_fourth(f32, f32);
extern void ProbeHeroAirborneWallContact(void);
extern s32 hero_find_ledge_grab(s32, s32, s32);
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
extern void HeroUpdateHopVelocity(void);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_apply_mode_pose_offsets(void);
extern void UpdateHeroMotionResponseParameters(void);
extern void UpdateHeroLeanAndSwayParameters(void);
extern void hero_apply_reference_tilt_rotation(s32, s32, s32, f32, f32, f32);
extern void hero_shrink_vector_by_amount(f32);
extern void hero_steer_reference_point(void);
extern f32 hero_get_direction_angle_delta(s32, s32);
extern s32 hero_play_sound(s32, s32);
extern void snd_update_slot_object(s32, s32, s32);
extern void hero_try_surface_push_response(f32, f32, f32);
extern void part_emit_effects_at_nearby_mobys(s32, s32);
extern void part_emit_hero_radial_particles(void);
extern void hero_setup_attached_object_transform(void);
extern void hero_update_height_offset(void);
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
extern void vec_add_offset(s32, s32, f32, f32, f32);
extern s32 math_update_angle_and_blend(s32, s32, s32, f32);
extern f32 ReadPadFloatHistory(s32);
extern s32 part_spawn_two_point_effect(s32, s32, f32);
extern s32 path_advance_index(s32, s32, s32, s32);
extern s32 Spline_AdvanceByDistance(s32, s32, s32, s32, s32, f32);
extern s32 find_nearest_path_point(s32, s32, s32, s32, s32, s32, f32, f32, f32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern s32 hero_get_gadget_value(s32);
extern void DeflectHeroOffSteepSurface(s32);
/* Runs every frame for the hero. It looks at the current hero state and moves, animates and switches the hero accordingly. */
void hero_l11_update_state_machine(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 f20_71;
    f32 f21_71;
    f32 f1_71;
    f32 spFCf;
    s32 idx71;
    s32 cnt71;
    f32 v0[4] __attribute__((aligned(16)));
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    f32 v50[4] __attribute__((aligned(16)));
    f32 m60[16] __attribute__((aligned(16)));
    f32 vA0[4] __attribute__((aligned(16)));
    f32 vB0[4] __attribute__((aligned(16)));
    f32 vC0[4] __attribute__((aligned(16)));
    f32 vD0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* var_v0_3_u2;
    void* var_s1_5_u2;
    f32 var_f12_16_u2;
    void* var_a1_5_u2;
    s32 var_a0_2_u2;
    void* var_s0_3_u2;
    s32 var_v0_8_u2;
    s32 var_v1_4_u2;
    void* var_a0_13_u2;
    s32 var_a0_2_u3;
    void* var_s0_3_u3;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 spE0;
    f32 spE4;
    f32 spE8;
    f32 spEC;
    f32 spF0;
    f32 spF4;
    f32 spF8;
    s32 spFC;
    f32 sp100;
    s32 sp104;
    f32 sp108;
    f32 sp10C;
    f32 sp110;
    s32 sp114;
    s32 sp118;
    s32 sp11C;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_19;
    f32 temp_f0_20;
    f32 temp_f0_21;
    f32 temp_f0_22;
    f32 temp_f0_23;
    f32 temp_f0_24;
    f32 temp_f0_25;
    f32 temp_f0_26;
    f32 temp_f0_27;
    f32 temp_f0_28;
    f32 temp_f0_29;
    f32 temp_f0_2;
    f32 temp_f0_30;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f12_7;
    f32 temp_f1;
    f32 temp_f1_10;
    f32 temp_f1_11;
    f32 temp_f1_12;
    f32 temp_f1_13;
    f32 temp_f1_14;
    f32 temp_f1_15;
    f32 temp_f1_16;
    f32 temp_f1_17;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f1_9;
    f32 temp_f20;
    f32 temp_f20_10;
    f32 temp_f20_11;
    f32 temp_f20_12;
    f32 temp_f20_13;
    f32 temp_f20_14;
    f32 temp_f20_15;
    f32 temp_f20_16;
    f32 temp_f20_17;
    f32 temp_f20_18;
    f32 temp_f20_19;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f20_4;
    f32 temp_f20_5;
    f32 temp_f20_6;
    f32 temp_f20_7;
    f32 temp_f20_8;
    f32 temp_f20_9;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f21_3;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f3;
    f32 var_f0;
    f32 var_f0_10;
    f32 var_f0_11;
    f32 var_f0_12;
    f32 var_f0_13;
    f32 var_f0_14;
    f32 var_f0_15;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f0_7;
    f32 var_f0_8;
    f32 var_f0_9;
    f32 var_f12;
    f32 var_f12_10;
    f32 var_f12_11;
    f32 var_f12_13;
    f32 var_f12_14;
    f32 var_f12_15;
    f32 var_f12_16;
    f32 var_f12_17;
    f32 var_f12_18;
    f32 var_f12_19;
    f32 var_f12_20;
    f32 var_f12_21;
    f32 var_f12_22;
    f32 var_f12_4;
    f32 var_f12_5;
    f32 var_f12_6;
    f32 var_f12_7;
    f32 var_f12_8;
    f32 var_f12_9;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f20;
    f32 var_f20_10;
    f32 var_f20_11;
    f32 var_f20_12;
    f32 var_f20_13;
    f32 var_f20_2;
    f32 var_f20_3;
    f32 var_f20_4;
    f32 var_f20_5;
    f32 var_f20_6;
    f32 var_f20_7;
    f32 var_f20_8;
    f32 var_f20_9;
    f32 var_f21;
    f32 var_f21_2;
    f32 var_f21_3;
    f32 var_f21_4;
    f32 var_f21_5;
    f32 var_f21_6;
    f32 var_f21_7;
    f32 var_f22;
    f32 var_f22_2;
    f32 var_f23;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    f32 var_f2_4;
    f32 var_f2_5;
    s16 temp_a2_5;
    s32 temp_v0_4;
    s16 temp_v0_8;
    s32 temp_v1_10;
    s32 temp_v1_9;
    s32 temp_a0_21;
    s32 temp_a0_3;
    s32 temp_a0_5;
    s32 temp_a0_7;
    s32 temp_a0_8;
    s32 temp_a0_9;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_a1_5;
    s32 temp_a1_7;
    s32 temp_a1_8;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_s0_5;
    s32 temp_s0_9;
    s32 temp_s7;
    s32 temp_v0;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_16;
    s32 temp_v0_17;
    s32 temp_v0_2;
    s32 temp_v1_12;
    s32 temp_v1_14;
    s32 temp_v1_16;
    s32 temp_v1_18;
    s32 temp_v1_20;
    s32 temp_v1_21;
    s32 temp_v1_22;
    s32 temp_v1_23;
    s32 temp_v1_24;
    s32 temp_v1_26;
    s32 temp_v1_34;
    s32 temp_v1_35;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 var_a0;
    s32 var_a0_10;
    s32 var_a0_11;
    s32 var_a0_12;
    s32 var_a0_2;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_8;
    s32 var_a0_9;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32* var_s1_4;
    s32* var_s1_6;
    u16 temp_v0_3;
    u16 temp_v1_11;
    u16 temp_v1_2;
    u32 temp_a0;
    u32 temp_v1;
    u32 temp_v1_13;
    u32 temp_v1_27;
    u32 temp_v1_28;
    u32 temp_v1_29;
    u32 temp_v1_30;
    u32 temp_v1_31;
    u32 temp_v1_33;
    u32 temp_v1_36;
    u32 temp_v1_3;
    u32 var_a1_3;
    u8 temp_a0_14;
    u8 temp_a0_2;
    u8 temp_v1_25;
    u8 var_a0_6;
    void* temp_a0_10;
    void* temp_a0_11;
    void* temp_a0_12;
    void* temp_a0_13;
    void* temp_a0_15;
    void* temp_a0_16;
    void* temp_a0_17;
    void* temp_a0_4;
    void* temp_a0_6;
    void* temp_a1;
    void* temp_a1_2;
    void* temp_a1_6;
    void* temp_fp;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* temp_s0;
    void* temp_s0_2;
    void* temp_s0_3;
    void* temp_s0_4;
    void* temp_s0_6;
    void* temp_s0_7;
    void* temp_s0_8;
    void* temp_s1;
    void* temp_s1_2;
    void* temp_s1_3;
    void* temp_s1_4;
    void* temp_s1_5;
    void* temp_s1_6;
    void* temp_s1_7;
    void* temp_s1_8;
    void* temp_s2;
    void* temp_s2_2;
    void* temp_s2_3;
    void* temp_s2_4;
    void* temp_s2_5;
    void* temp_s4;
    void* temp_s4_2;
    void* temp_s5;
    void* temp_v0_10;
    void* temp_v0_5;
    void* temp_v0_6;
    void* temp_v0_7;
    void* temp_v0_9;
    void* temp_v1_15;
    void* temp_v1_17;
    void* temp_v1_32;
    void* temp_v1_37;
    void* temp_v1_38;
    void* temp_v1_39;
    void* var_a0_13;
    void* var_a0_7;
    void* var_a1_5;
    void* var_s0_3;
    void* var_s1_5;
    void* var_v0_3;

    sp114 = ((Hero *)g_hero_state)->i[0x2298/4];
    temp_fp = ((Hero *)g_hero_state)->ptr[0x2290/4];
    sp118 = (s32) M2C_FIELD(temp_fp, u8* , 0x43);
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
        temp_v1 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((temp_v1 == 1) || (temp_v1 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)v0) = 0;
                v0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)v0), (s32)&D_L11_001BA8D8[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)D_L11_001BA8D8)->f[0];
                hero_steer_heading(0, 1.0f, 0.0f, 2.9088826f);
                if ((((Hero *)g_hero_state)->b[0x22BB] != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] == 0x78)) {
                    if (((Hero *)g_progress_statistics)->uh[0xD8/2] < 0xFFFF) {
                        ((Hero *)g_progress_statistics)->uh[0xD8/2]++;
                    }
                    if (D_001A7390 > ((Hero *)g_progress_statistics)->u[0xDC/4]) {
                        ((Hero *)g_progress_statistics)->u[0xDC/4] = D_001A7390;
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (temp_a0_2 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (temp_a0_2 == 0xE)) || (temp_a0_2 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    temp_a0_3 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    temp_a0_3 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != temp_a0_3) {
                        set_hero_animation(temp_a0_3, 0, 5.0f);
                    }
                    temp_f0 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = temp_f0;
                    if (temp_f0 < 0.55f) {
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
            temp_v1_3 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (temp_v1_3 == 3) {
                var_f12 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (var_f12 > 1.0f) {
                    var_f12 = 1.0f;
                }
                temp_a0_4 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                var_f20 = var_f12 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = var_f20;
                if (M2C_FIELD(temp_a0_4, u8* , 0x42) == M2C_FIELD(temp_a0_4, u8* , 0x43)) {
                    var_f1 = ((Hero *)g_hero_state)->f[0x174/4] / var_f20;
                    if ((var_f1 > 5.0f) && ((f32) M2C_FIELD(temp_a0_4, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, var_f1, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else {
                var_f20 = (temp_v1_3 == 4) ? 0.0075000003f : 0.004916667f;
            }
            hero_approach_speed(0.0f, var_f20);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(var_f20);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                var_a0_2 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(var_a0_2, var_a0_2 + 0x30, 0.0061111115f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.015000001f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                DeflectHeroOffSteepSurface(0);
                if (((Hero *)g_hero_state)->h[0x34E/2] == 0) {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
                } else {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
                    hero_cancel_velocity_into_wall();
                }
            }
        break;
    case 0x85:                                      /* switch 1 */
        temp_a1_2 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)temp_a1_2 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)temp_a1_2 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)v0), (s32)(g_hero_state + 0x2C0), -1.0f);
        var_f12_8 = 0.0f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            var_f12_8 = -((Hero *)g_hero_state)->f[0x1FB4/4] * 0.75f;
        }
        math_spring_float_to_goal((s32)(g_hero_state + 0x7C0), (s32)(g_hero_state + 0x7C4), var_f12_8, 0.007f, 0.3f, 0.03f);
        FastVecScale((s32) ((TI128*)v50), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v50));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        hero_apply_reference_tilt_rotation((s32)((TI128*)v0), (s32) ((TI128*)v10), 0, 0.025f, 0.4f, 0.0f);
        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.21666668f;
        vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)g_hero_state, 0.21666668f);
        cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
        vec_clear_128((s32)((TI128*)v0));
        v0[1] = -((Hero *)g_hero_state)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(g_hero_state + 0x190), (s32)((TI128*)v0), (s32)&D_L11_001BA8D8[0x218]);
        hero_steer_heading(0, 0.02f, 0.3f, 0.034906592f);
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
            temp_v1_15 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(temp_v1_15, u8* , 0x60) & 2) && (M2C_FIELD(temp_v1_15, u8* , 0x42) == 0x36)) {
                set_hero_animation(hero_get_gadget_value(0), 0, 5.0f);
            }
        }
        break;
    case 0x8A:                                      /* switch 1 */
    case 0x8B:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        hero_approach_speed(0.004916667f, 0.004916667f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.004916667f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x120), 0.0061111115f);
            hero_cancel_velocity_into_wall();
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.015000001f);
        }
        var_v0_3 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (var_v0_3 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(var_v0_3, f32* , 0x10) - M2C_FIELD(temp_fp, f32* , 0x10), M2C_FIELD(var_v0_3, f32* , 0x14) - M2C_FIELD(temp_fp, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x23:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        hero_approach_speed(0.004916667f, 0.004916667f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.004916667f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x120), 0.0061111115f);
            hero_cancel_velocity_into_wall();
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.015000001f);
        }
        var_v0_3_u2 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (var_v0_3_u2 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(var_v0_3_u2, f32* , 0x10) - M2C_FIELD(temp_fp, f32* , 0x10), M2C_FIELD(var_v0_3_u2, f32* , 0x14) - M2C_FIELD(temp_fp, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(v0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        temp_f0_4 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)v0));
        ((Hero *)g_hero_state)->f[0xAB0/4] = temp_f0_4;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 60.0f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (temp_f0_4 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        temp_v1_16 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (temp_v1_16 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.45000002f, 0.022222223f);
            temp_v0_5 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            var_f20_2 = mat_fast_helper_a(M2C_FIELD(temp_v0_5, f32* , 0x10) - M2C_FIELD(temp_fp, f32* , 0x10), M2C_FIELD(temp_v0_5, f32* , 0x14) - M2C_FIELD(temp_fp, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], var_f20_2) > 1.5707964f) {
                    var_f20_2 = FastAddRotations(var_f20_2, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = var_f20_2;
            hero_steer_heading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (temp_v1_16 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((math_solve_quadratic((s32) &spE8, (s32) &spEC, -0.0058333334f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (spE8 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = spE8;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 20.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn24 = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)v0)), v0[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn24, 0.10762865f);
        }
        v20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        temp_f0_5 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        v20[2] = 0;
        v20[1] = temp_f0_5;
        FastVecAdd((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)v10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)v20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)v10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        temp_f0_6 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (temp_f0_6 < 30.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((30.0f - temp_f0_6) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.004166667f);
        qcopy(v0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)v0));
        FastVecAdd((s32) ((TI128*)v10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32)((TI128*)v0));
        vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)v20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(temp_fp, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        temp_v1_17 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        temp_f24 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (temp_v1_17 != 0) {
            temp_v0_6 = M2C_FIELD(temp_v1_17, void** , 0x68);
            if ((temp_v0_6 != 0) && (M2C_FIELD(temp_v0_6, s32* , 0x34) != 0)) {
                var_f20_3 = M2C_FIELD(temp_v1_17, f32* , 0xF8);
                if (FastDiffRots(var_f20_3, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    var_f20_3 = FastAddRotations(var_f20_3, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), var_f20_3, (s32) (((void*)g_hero_state) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)v0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        if (v0[2] < 0.23f) {
            v0[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)vA0));
        vA0[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)v20), (s32) ((TI128*)vA0));
        matrix_from_basis_rows((s32) ((TI128*)m60), (s32) ((TI128*)v20));
        transform_vector((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)m60));
        v10[0] = -mat_fast_helper_a(square_root((v0[0] * v0[0]) + (v0[2] * v0[2])), v0[1]);
        temp_f0_7 = mat_fast_helper_a(v0[2], v0[0]);
        v10[1] = temp_f0_7;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), temp_f0_7, (s32) (((void*)g_hero_state) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), v10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        var_s7 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((var_s7 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x29) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                var_f20_4 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0035f;
                if (var_f20_4 > 0.083333336f) {
                    var_f20_4 = 0.083333336f;
                }
                vB0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * var_f20_4;
                temp_f0_8 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * var_f20_4;
                temp_a0_10 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vB0[2]) = 0;
                vB0[1] = temp_f0_8;
                FastVecAdd((s32) temp_a0_10, (s32) temp_a0_10, (s32) ((TI128*)vB0));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                temp_s2_2 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) temp_s2_2, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    temp_s1_2 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) temp_s1_2, (s32) (((void*)g_hero_state) + 0x110), 0.011111111f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) temp_s1_2) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vB0), (s32) temp_s2_2, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) temp_s1_2, (s32) temp_s1_2, 0.015833333f);
                    }
                }
                temp_f20_3 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vB0), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vB0), (s32) ((TI128*)vB0), temp_f20_3);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vB0));
            }
        }
        temp_v0_7 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (temp_v0_7 != 0) {
            temp_s0 = M2C_FIELD(temp_v0_7, void** , 0x68);
            temp_s1_3 = ((void*)g_hero_state) + 0xF0;
            if (temp_s0 != 0) {
                temp_f0_9 = FastVecLength((s32) temp_s1_3);
                temp_f12 = M2C_FIELD(temp_s0, f32* , 0xC);
                spF0 = temp_f0_9;
                if (temp_f12 < temp_f0_9) {
                    ApproachValue((s32) &spF0, temp_f12, 0.004166667f);
                    vec_scale_to_length((s32) temp_s1_3, (s32) temp_s1_3, spF0);
                }
            }
        }
        temp_f0_10 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        temp_s5 = ((void*)g_hero_state) + 0x80;
        temp_s4_2 = ((void*)g_hero_state) + 0xF0;
        vD0[0] = math_fast_sin_or_cos_a(temp_f0_10) * 0.15f;
        temp_f0_11 = math_fast_sin_or_cos_b(temp_f0_10) * 0.15f;
        (*(s32*)&vD0[2]) = 0;
        vD0[1] = temp_f0_11;
        FastVecAdd((s32) &vD0[0], (s32) &vD0[0], (s32) temp_s5);
        FastVecAdd((s32) ((TI128*)vB0), (s32) &vD0[0], (s32) temp_s4_2);
        FastVecSub((s32) ((TI128*)vC0), (s32) ((TI128*)vB0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vB0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vC0));
        FastVecSub((s32) temp_s4_2, (s32) ((TI128*)vB0), (s32) &vD0[0]);
        temp_f20_4 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        temp_f20_5 = ((Hero *)g_hero_state)->f[0xAE4/4] - temp_f20_4;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vC0))) {
            vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), temp_f20_5);
            FastVecAdd((s32) temp_s5, (s32) temp_s5, (s32) ((TI128*)vC0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (var_s7 != 0)) {
            min2B = 0.23333335f;
            temp_f0_12 = vec_length_xy((s32) temp_s4_2);
            spF4 = temp_f0_12;
            if (temp_f0_12 < min2B) {
                math_spring_float_to_goal((s32) &spF4, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                vB0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                temp_f0_13 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vB0[2] = 0.0f;
                vB0[1] = temp_f0_13 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) temp_s4_2, (s32) temp_s4_2, (s32) ((TI128*)vB0));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((temp_f24 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            temp_f20_6 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            temp_v0_8 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (temp_v0_8 != 0) {
                var_v0_4 = temp_v0_8 == 1;
            } else {
                (*(TI128*)vB0) = ((Hero *)g_hero_state)->q[0x110/16];
                var_v0_4 = hero_get_speed_along_forward((s32) ((TI128*)vB0)) > 0.0f;
            }
            if (var_v0_4 != 0) {
                if (M2C_FIELD(temp_fp, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    temp_v0_9 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(temp_v0_9, u8* , 0x42) == M2C_FIELD(temp_v0_9, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, temp_f20_6, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(temp_fp, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                temp_v0_10 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(temp_v0_10, u8* , 0x42) == M2C_FIELD(temp_v0_10, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, temp_f20_6, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L11_00275090[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        var_s1_2 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            var_s1_2 = 1;
        }
        temp_a1_4 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (temp_a1_4 != 0) {
            FastVecSub((s32)((TI128*)v0), temp_a1_4 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            temp_f0_14 = cam_get_view_space_vector_length((s32)((TI128*)v0));
            if (((temp_f0_14 > 2.0f) && (temp_f0_14 < 5.0f)) || (var_s1_2 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
            }
            hero_approach_speed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length((s32) ((TI128*)v10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)v10));
        } else {
            if ((var_s1_2 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
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
        temp_f1_6 = ((Hero *)g_hero_state)->f[0x31C/4];
        var_f21 = 0.12833333f;
        if (temp_f1_6 > 2.25f) {
            var_f21 = 0.064166665f;
        } else if (temp_f1_6 > 1.8f) {
            var_f21 = 0.08983333f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(v0, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)v0), (s32)((TI128*)v0), -0.5f);
            vec_scale_to_length((s32) &v40[0], (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)v10), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &v40[0]);
            v10[3] = 5627.925f;
            (*(u8*)((u8*)v20+9)) = 1;
            (*(u16*)((u8*)v20+10)) = 0x47;
            (*(u8*)((u8*)v20+8)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)v0), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)v10));
        }
        if (math_is_below_plane_within_depth(25.7f) != 0) {
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L11_001BA780)->f[0x180/4] = 0.1f;
                ((Hero *)D_L11_001BA780)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)D_L11_001BA780)->i[0x16C/4] = 0;
            }
        }
        temp_v1_18 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xE;
        if (temp_v1_18 < 9) {
            temp_s0_2 = ((void*)g_hero_state) + 0xF0;
            spF8 = cam_get_view_space_height((s32) temp_s0_2);
            ApproachValue((s32) &spF8, var_f21, 0.041666668f);
            cam_set_view_space_height((s32) temp_s0_2, (s32) temp_s0_2, spF8);
        } else if (temp_v1_18 > lim3) {
            temp_s1_4 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) temp_s1_4, (s32) temp_s1_4, 0.036111113f);
            if (cam_get_view_space_height((s32) temp_s1_4) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            var_f20_5 = -0.6166667f;
            if (D_L11_001A8FF0 != 0) {
                var_f20_5 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) temp_s1_4) < var_f20_5) {
                cam_set_view_space_height((s32) temp_s1_4, (s32) temp_s1_4, var_f20_5);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L11_00275090[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        var_a0_8 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (var_a0_8 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                var_s1_3 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    temp_s0_3 = ((void*)g_hero_state) + 0xBC0;
                    var_f20_6 = hero_get_direction_angle_delta((s32) temp_s0_3, 0);
                    var_f0_3 = hero_get_direction_angle_delta((s32) temp_s0_3, 1);
                } else {
                    var_f20_6 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    var_f0_3 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (var_f0_3 < 4.3633237f) {
                    var_s1_3 = 1;
                }
                if (var_f20_6 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (var_f0_3 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (var_s1_3 != 0) {
                    hero_steer_heading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    hero_steer_heading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    var_a0_9 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xC)) {
                        var_a0_9 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        var_a0_9 = 0;
                    }
                    if (var_a0_9 != 0) {
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
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L11_00275090[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        temp_a1_5 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        temp_s2_3 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)D_L11_00275090;
        if ((temp_a1_5 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            temp_s1_5 = ((void*)g_hero_state) + 0x80;
            var_f12_13 = vec_distance_xy(temp_a1_5 + 0x10, (s32) temp_s1_5);
            if ((*(s32*)&D_L11_001A8FF0) != 0) {
                var_f12_13 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) temp_s1_5);
            }
            var_f12_13 = var_f12_13 - 0.5f;
            if (var_f12_13 < 0.0f) {
                var_f12_13 = 0.0f;
            }
            temp_v1_20 = M2C_FIELD(temp_s2_3, s32* , 4);
            if (temp_v1_20 == 0) {
                var_f0_4 = 0.75f;
                var_f21_3 = 0.8f;
                var_f22 = 4.0f;
            } else if (temp_v1_20 == 1) {
                var_f0_4 = 0.6f;
                var_f21_3 = 1.7f;
                var_f22 = 4.0f;
            } else {
                var_f0_4 = 1.3f;
                var_f21_3 = 1.7f;
                var_f22 = 1.9f;
            }
            temp_f20_8 = var_f12_13 - var_f0_4;
            if (math_fabs(temp_f20_8) < (var_f21_3 + 3.0f)) {
                var_f12_15 = temp_f20_8 * 1.1111112f;
                if (var_f22 < var_f12_15) {
                    var_f12_15 = var_f22;
                }
                if (var_f12_15 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = var_f12_15;
                }
            }
        }
        temp_v1_21 = M2C_FIELD(temp_s2_3, s32* , 4);
        switch (temp_v1_21) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            temp_f1_7 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (temp_f1_7 < 9.0f)) {
                if (temp_f1_7 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (temp_f1_7 > 7.0f) {
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
            var_f0_5 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            var_f0_5 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        temp_f1_8 = math_fabs(var_f0_5);
        if ((M2C_FIELD(temp_s2_3, s32* , 4) == 1) && (var_f0_5 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (temp_f1_8 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        var_v1_3 = 1;
        if ((M2C_FIELD(temp_s2_3, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            var_v1_3 = 0;
        }
        if (var_v1_3 != 0) {
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
            temp_a0_12 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) temp_a0_12, (s32) temp_a0_12, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L11_001A8FF0) != 0) {
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
        temp_v1_22 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (temp_v1_22 > lim) {
            if (temp_v1_22 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            temp_s0_4 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) temp_s0_4);
            level_append_record_to_table((s32) temp_s0_4, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) temp_s0_4, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) temp_s0_4, 0xC, 6, 0.0f);
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
            temp_v1_24 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((temp_v1_24 > lim) && (temp_v1_24 < 0x16)) {
                temp_s2_4 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (temp_s2_4 != 0) {
                    temp_s1_6 = ((void*)g_hero_state) + 0x80;
                    v30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)v0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)v30));
                    (*(u8*)((u8*)v10+9)) = 3;
                    v0[3] = 5627.925f;
                    (*(u8*)((u8*)v10+8)) = 0;
                    temp_f22_2 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)v10+10)) = M2C_FIELD(temp_s2_4, u16* , 0xAA);
                    v40[0] = math_fast_sin_or_cos_a(temp_f22_2) * 0.8f;
                    temp_f0_15 = math_fast_sin_or_cos_b(temp_f22_2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = temp_f0_15;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) temp_s1_6);
                    part_emit_effects_at_nearby_mobys((s32) temp_s2_4, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) temp_s2_4, (s32)((TI128*)v0)));
                    temp_f22_2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(temp_f22_2) * 0.8f;
                    temp_f0_17 = math_fast_sin_or_cos_b(temp_f22_2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = temp_f0_17;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) temp_s1_6);
                    part_emit_effects_at_nearby_mobys((s32) temp_s2_4, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)v0)));
                    temp_f22_2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(temp_f22_2) * 0.8f;
                    temp_f0_19 = math_fast_sin_or_cos_b(temp_f22_2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = temp_f0_19;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) temp_s1_6);
                    part_emit_effects_at_nearby_mobys((s32) temp_s2_4, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) temp_s2_4, (s32)((TI128*)v0)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        DeflectHeroOffSteepSurface(1);
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
            temp_f20_9 = ReadPadFloatHistory(1);
            if ((FastDiffRots(temp_f20_9, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            (*(TI128*)v0) = ((Hero *)g_hero_state)->q[0xA60/16];
            temp_f1_9 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)v0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = temp_f1_9;
            if (temp_f1_9 < 0.011666667f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.011666667f;
            }
            vec_clear_128((s32) pA60);
        }
        var_f20_7 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                temp_f2_2 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (temp_f2_2 > 0.78539824f)) {
                    var_f20_7 = 0.0f;
                }
                hero_set_turn_rates();
            }
        }
        hero_apply_mode_pose_offsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            var_f2_2 = 0.09916667f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.029178405f);
            if (var_f2_2 < 0.0f) {
                var_f2_2 = 0.0f;
            }
            if (var_f2_2 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = var_f2_2;
            }
        }
        k005 = var_f20_7 * 0.005f;
        var_f20_8 = 0.0055555557f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            var_f1_2 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (var_f1_2 > 1.0f) {
                var_f1_2 = 1.0f;
            }
            if (var_f1_2 < 0.2f) {
                var_f1_2 = 0.2f;
            }
            var_f20_8 = 0.004722222f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * var_f1_2);
        }
        temp_f2_3 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (temp_f2_3 > 0.6108653f)) {
            var_f1_3 = 1.0f - (temp_f2_3 * 0.4f);
            if (var_f1_3 < 0.0f) {
                var_f1_3 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * var_f1_3);
        }
        hero_approach_speed(k005, var_f20_8);
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
        DeflectHeroOffSteepSurface(1);
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
        pad_clamp_stick_to_unit_range((s32)((TI128*)v0), (s32) (((void*)g_hero_state) + 0x9F0), 0.17f);
        var_f21_4 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * v0[0];
        if ((*(s32*)&D_L11_001A8FF0) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3C) {
                var_f21_4 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, var_f21_4);
        }
        hero_approach_speed(0.027777778f, 0.004166667f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&D_L11_001A8FF0) != 0) {
            qcopy(v10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)v10), (s32) ((TI128*)v10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)v10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32)(g_hero_state + 0xE0));
        temp_v0_12 = coll_process_hit(0.57f, (s32) ((TI128*)v10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (temp_v0_12 != 0) {
            FastVecScale((s32) ((TI128*)v20), (s32)(g_hero_state + 0x110), 7.0f);
            for (var_s0 = 0; var_s0 < temp_v0_12; var_s0++) {
                if (moby_is_in_special_class_range(((s32 *)D_L11_001C4D80)[var_s0]) != 0) {
                    part_queue_impact_effect(((s32 *)D_L11_001C4D80)[var_s0], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.017f, 0.3f);
        cam_set_limits_third(0.025f, 0.3f);
        cam_set_limits_fourth(0.03f, 0.27f);
        var_f2_3 = var_f21_4 * 27.0f;
        if (var_f2_3 > 1.7f) {
            var_f2_3 = 1.7f;
        } else if (var_f2_3 < -1.7f) {
            var_f2_3 = -1.7f;
        }
        temp_f0_20 = var_f2_3 * 0.5f;
        ((Hero *)D_L11_00273510)->f[0x60/4] = (f32) -var_f2_3;
        ((Hero *)D_L11_00273510)->f[0x278/4] = temp_f0_20;
        ((Hero *)D_L11_00273510)->f[0x1C8/4] = temp_f0_20;
        break;
    case 0x71:
        hero_get_offset_vector((s32)v0);
        if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) == 0x5F) {
            snd_update_slot_object(0, (s32)((Hero *)g_hero_state)->ptr[0x2290/4], 0);
            if (D_L11_001B30C8 & 1) {
                qcopy(&v10, &v0);
                FastVecScale((s32)v20, (s32)(g_hero_state + 0x110), 0.4f);
                f20_71 = math_random_signed_float_range(0.0f, 0.52359885f);
                f20_71 = FastAddRotations(((Hero *)g_hero_state)->f[0x700/4], f20_71);
                f21_71 = math_random_float_range(0.0f, 0.06666667f);
                v20[0] += math_fast_sin_or_cos_a(f20_71) * f21_71;
                v20[1] += math_fast_sin_or_cos_b(f20_71) * f21_71;
                v20[2] = math_random_float_range(0.050000004f, 0.083333336f);
                v20[3] = -0.009722223f;
                part_spawn_white_flash((s32)v10, (s32)v20, 0, -1.0f);
            }
        }
        find_nearest_path_point(((Hero *)g_hero_state)->i[0x6E0/4], (s32)v0, (s32)(g_hero_state + 0x6D0), (s32)(g_hero_state + 0x6E4), (s32)(g_hero_state + 0x6E8), ((Hero *)g_hero_state)->i[0x6FC/4], 999.0f, 8.0f, 2.5f);
        cnt71 = ((Hero *)g_hero_state)->i[0x6F0/4];
        if (cnt71 != 0) {
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x120/16]);
            ((Hero *)g_hero_state)->f[0xF8/4] -= 0.0061111115f;
            ((Hero *)g_hero_state)->i[0x6F0/4] = cnt71 + 1;
        } else {
            /* retail evaluates the float (fifth) argument first */
            ((s32 (*)(s32, s32, s32, s32, f32, s32))Spline_AdvanceByDistance)(((Hero *)g_hero_state)->i[0x6E0/4], (s32)v10, (s32)(g_hero_state + 0x6E4), (s32)(g_hero_state + 0x6E8), ((Hero *)g_hero_state)->f[0x6F4/4], ((Hero *)g_hero_state)->i[0x6FC/4]);
            idx71 = path_advance_index(((Hero *)g_hero_state)->i[0x6E0/4], ((Hero *)g_hero_state)->i[0x6E4/4], 1, ((Hero *)g_hero_state)->i[0x6FC/4]);
            FastVecSub((s32)v20, (s32)((u8 *)((Hero *)g_hero_state)->ptr[0x6E0/4] + (idx71 * 16 + 0x10)), (s32)v10);
            if (FastVecLength((s32)v20) < 0.001f) {
                if (((Hero *)g_hero_state)->i[0x6E4/4] == idx71) {
                    ((Hero *)g_hero_state)->i[0x6F0/4] = 1;
                    break;
                }
            } else {
                ((Hero *)g_hero_state)->f[0x700/4] = mat_fast_helper_a(v20[0], v20[1]);
                ((Hero *)g_hero_state)->f[0x704/4] = mat_fast_helper_a(vec_length_xy((s32)v20), v20[2]);
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x700/4];
            hero_steer_heading(0, 0.018f, 0.2f, 0.10762865f);
            ApproachValue((s32)(g_hero_state + 0x6F4), 0.23333335f, 0.0025f);
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)v10, (s32)(g_hero_state + 0x6D0));
            FastVecSub((s32)v20, (s32)(g_hero_state + 0x6D0), (s32)v0);
            spFCf = -FastVecLength((s32)v20);
            math_spring_float_to_goal((s32)&spFCf, (s32)(g_hero_state + 0x708), 0.0f, 0.05f, 0.3f, 0.16666667f);
            f1_71 = FastVecLength((s32)v20);
            if (f1_71 < ((Hero *)g_hero_state)->f[0x708/4]) {
                ((Hero *)g_hero_state)->f[0x708/4] = f1_71;
            }
            if (((Hero *)g_hero_state)->f[0x708/4] < f1_71) {
                vec_scale_to_length((s32)v20, (s32)v20, ((Hero *)g_hero_state)->f[0x708/4]);
            }
            FastVecAdd((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x80), (s32)v20);
        }
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
    case 0x46:                                      /* switch 1 */
    case 0x47:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0x550), (s32)(g_hero_state + 0x80));
        vec_clamp_length((s32)(g_hero_state + 0xF0), 0.028333336f);
        ApproachValue((s32)(g_hero_state + 0x580), ((Hero *)g_hero_state)->f[0x88/4], 0.050000004f);
        break;
    case 0x19:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)m60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &v40[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)m60));
        } else {
            FastVecCross((s32) &v40[0], (s32) ((TI128*)m60), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &v40[0], (s32) &v40[0], 0.2f);
        FastVecAdd((s32) &v50[0], (s32)(g_hero_state + 0x80), (s32) &v40[0]);
        if ((hero_find_ledge_grab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab((s32) &v50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)v0), (s32)(g_hero_state + 0x80));
            var_v0_8 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            var_v1_4 = (s32)D_L11_001ACEE8;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(var_v0_8 + var_v1_4) * 0.5f);
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
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2C) {
            var_f12_18 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                var_f12_18 = 0.43633235f;
            }
            qcopy(v0, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &v0[1], var_f12_18, (s32) (((void*)g_hero_state) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            math_approach_with_velocity((s32)((TI128*)v0), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_refresh_speed_from_timer();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            HeroUpdateHopVelocity();
        }
        var_s1_5 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) var_s1_5, (s32) var_s1_5, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) var_s1_5) < -0.8333334f) {
            cam_set_view_space_height((s32) var_s1_5, (s32) var_s1_5, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        var_s1_5_u2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) var_s1_5_u2, (s32) var_s1_5_u2, vec_length_xy((s32) var_s1_5_u2) * 0.9f);
        hero_apply_mode_transform((s32) var_s1_5_u2, (s32) var_s1_5_u2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) var_s1_5_u2) < -0.8333334f) {
            cam_set_view_space_height((s32) var_s1_5_u2, (s32) var_s1_5_u2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        var_a0_12 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            var_a0_12 = 0;
        }
        if (var_a0_12 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            temp_a0_15 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) temp_a0_15, (s32) temp_a0_15, 0.025f);
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
        temp_f12_4 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (temp_f12_4 < 0.0f) && (temp_f2_6 = ((Hero *)g_hero_state)->f[0x31C/4], (temp_f2_6 < 1.2f))) {
            var_f0_10 = (temp_f2_6 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (var_f0_10 < 0.0f) {
                var_f0_10 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), temp_f12_4 * var_f0_10);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (temp_f12_4 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L11_001BAB48) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.027f, 0.3f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.087266475f);
        var_f12_19 = 0.0013888889f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            var_f12_19 = 0.00055555557f;
        }
        hero_approach_velocity(var_f12_19);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            temp_a2_3 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (temp_a2_3 != -1) {
                temp_a0_16 = (temp_a2_3 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(temp_a0_16, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(temp_a0_16, u8* , 0x74) != 0)) {
                    snd_stop_voice(temp_a2_3);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            temp_a2_4 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (temp_a2_4 != -1) {
                temp_a0_17 = (temp_a2_4 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(temp_a0_17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(temp_a0_17, u8* , 0x74) != 0)) {
                    snd_stop_voice(temp_a2_4);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        var_f22_2 = 0.050000004f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            var_f22_2 = 0.083333336f;
        }
        var_f23 = 0.72f;
        temp_f1_12 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            var_f22_2 = 0.12833333f;
            var_f23 = 0.98640007f;
        }
        if (temp_f1_12 != 0.0f) {
            var_f23 = temp_f1_12;
        }
        temp_s0_7 = ((void*)g_hero_state) + 0xF0;
        sp110 = cam_get_view_space_height((s32) temp_s0_7);
        hero_resolve_stick_direction(var_f22_2, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) temp_s0_7, (s32) temp_s0_7);
        math_spring_float_to_goal((s32) &sp110, (s32) (((void*)g_hero_state) + 0xA98), -var_f22_2 * var_f23, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) temp_s0_7, (s32) temp_s0_7, -sp110);
        temp_f12_5 = ((Hero *)g_hero_state)->f[0x88/4];
        if (temp_f12_5 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), temp_f12_5, 0.06666667f);
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
        temp_a2_5 = ((Hero *)g_hero_state)->h[0x4AC/2];
        temp_a1_8 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (temp_a1_8 == temp_a2_5) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((temp_a1_8 < temp_a2_5) && (temp_v1_33 = ((Hero *)g_hero_state)->u[0x2294/4], (temp_v1_33 != 0xB)) && (temp_v1_33 != 0x10) && (temp_v1_33 != 0xC) && (temp_v1_33 != 0x11) && (temp_v1_33 != 0x1B) && (temp_v1_33 != 0x89) && (temp_v1_33 != 0x48))) {
            hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
            temp_f20_16 = ((Hero *)g_hero_state)->f[0x1B4/4];
            if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (temp_f20_16 * 0.4f);
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
            ((Hero *)g_hero_state)->f[0x1B4/4] = temp_f20_16;
            if (((Hero *)g_hero_state)->b[0x49C] != 1) {
                hero_approach_speed(((Hero *)g_hero_state)->f[0x500/4], ((Hero *)g_hero_state)->f[0x504/4]);
            }
            if (((Hero *)g_hero_state)->b[0x49C] != 0) {
                if ((*(s32*)&D_00138354) != 0) {
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
                temp_v1_34 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (temp_v1_34 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) temp_v1_34 * 0.0044444446f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                temp_v1_35 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (temp_v1_35 < 0x22) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) temp_v1_35 * 0.014722222f);
                }
            }
            if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                qcopy(v0, &((Hero *)g_hero_state)->q[0x80/16]);
                cam_offset_point_in_view_space((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                cam_offset_point_by_side_direction((s32) ((TI128*)v10), (s32)((TI128*)v0), 0.95f);
                if (CollLine((s32)((TI128*)v0), (s32) ((TI128*)v10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                    ((Hero *)g_hero_state)->h[0x524/2] = 1;
                }
            }
        } else {
            HeroUpdateHopVelocity();
        }
        temp_f1_14 = ((Hero *)g_hero_state)->f[0x318/4];
        temp_f2_7 = ((Hero *)g_hero_state)->f[0x490/4];
        if (temp_f2_7 < temp_f1_14) {
            temp_f0_29 = temp_f2_7 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = temp_f0_29;
            if (temp_f1_14 < temp_f0_29) {
                ((Hero *)g_hero_state)->f[0x490/4] = temp_f1_14;
            }
        }
        temp_f1_15 = ((Hero *)g_hero_state)->f[0x88/4];
        if (temp_f1_15 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = temp_f1_15;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            temp_f1_16 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (temp_f1_16 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = temp_f1_16;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters();
        }
        temp_v1_36 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((temp_v1_36 == 0x10) || (temp_v1_36 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)v0), 1, 0.8f, 0.0f, 0.3f);
                    temp_v0_17 = coll_process_hit(0.9f, (s32)((TI128*)v0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (temp_v0_17 != 0) {
                        FastVecScale((s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (var_s0_2 = 0; var_s0_2 < temp_v0_17; var_s0_2++) {
                            if (moby_is_in_special_class_range(((s32 *)D_L11_001C4D80)[var_s0_2]) != 0) {
                                part_queue_impact_effect(((s32 *)D_L11_001C4D80)[var_s0_2], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x38) && (((Hero *)g_hero_state)->b[0x49E] == 0) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.025000002f)) {
            EmitHeroTimedEffects();
        }
        ApplyHeroGravityAndJumpMotion();
        ProbeHeroAirborneWallContact();
        break;
    case 0x16:                                      /* switch 1 */
        var_f20_13 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        var_f0_12 = 0.0011111111f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB)) {
            var_f0_12 = 0.0027777778f;
        }
        var_f20_13 = var_f20_13 - var_f0_12;
        if (var_f20_13 < 0.0f) {
            var_f20_13 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        var_s0_3 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) var_s0_3, (s32) var_s0_3, var_f20_13);
        hero_apply_mode_transform((s32) var_s0_3, (s32) var_s0_3, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)v0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
        temp_f0_30 = vec_length_xy((s32)((TI128*)v0));
        if (temp_f0_30 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = temp_f0_30;
            if (temp_f0_30 < D_L11_001A7DAC[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L11_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L11_001A7DAC[1][1] * 0.016666668f;
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
            DeflectHeroOffSteepSurface(1);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.0069444445f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        break;
    case 0x63:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)v0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)v0), (s32)(g_hero_state + 0x160)) < 0.0f) {
            vec_clear_128((s32)(g_hero_state + 0x160));
        }
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.0075000003f);
        DeflectHeroOffSteepSurface(0);
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
    case 0x79:                                      /* switch 1 */
        part_emit_hero_radial_particles();
        /* fallthrough */
    case 0x78:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.016666668f;
        break;
    case 0x7A:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.0058333334f;
        break;
    case 0x3F:                                      /* switch 1 */
    case 0x43:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        hero_approach_speed(0.0f, 0.0035f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        DeflectHeroOffSteepSurface(0);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.015000001f);
        break;
    case 0x4D:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        temp_v1_37 = (s32) &D_L11_00275090[((Hero *)g_hero_state)->h[0xBFC/2]];
        temp_a0_21 = M2C_FIELD(temp_v1_37, s32* , 4);
        switch (temp_a0_21) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 5.5f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.058333337f;
            }
            break;
        case 1:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 5.5f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.058333337f;
            }
            break;
        }
        if (((Hero *)g_hero_state)->i[0xC2C/4] == 0) {
            temp_f1_17 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((f32) M2C_FIELD(temp_v1_37, s32* , 0x1C) <= temp_f1_17) {
                if (temp_f1_17 <= (f32) M2C_FIELD(temp_v1_37, s32* , 0x20)) {
                    temp_s0_9 = ((M2C_FIELD(temp_v1_37, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], temp_s0_9, (s32) ((TI128*)v10));
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], temp_s0_9 | 1, (s32) ((TI128*)v20));
                    FastVecAdd((s32)((TI128*)v0), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
                    FastVecScale((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    coll_sweep_from_object((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)v0), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
                }
            }
        }
        ApproachValue((s32)(g_hero_state + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
            hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
        } else {
            hero_l00_select_aim_target(5.0f, 0.78539824f, 0.78539824f);
        }
        hero_approach_speed(0.010277778f, 0.007777778f);
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            if (((Hero *)g_hero_state)->b[0x22C3] == 2) {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0xBC0));
            } else {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
            }
        } else {
            hero_compute_push_direction(99999.0f);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0x118/4] - 0.0069444445f);
            hero_cancel_velocity_into_wall();
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.015000001f);
        }
        hero_try_surface_push_response(0.7f, 0.0f, 0.3f);
        break;
    case 0x4B:                                      /* switch 1 */
        hero_resolve_stick_direction(0.033333335f, 0);
        hero_steer_heading(0, 0.04f, 0.2f, 0.14544412f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        cam_project_vector_onto_view_plane((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0));
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.024000002f);
        break;
    case 0x4E:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09166667f;
        hero_approach_velocity(0.0069444445f);
        var_f12_16_u2 = 0.005f;
        var_a1_5_u2 = ((void*)g_hero_state) + 0x130;
        hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) var_a1_5_u2, var_f12_16_u2);
        break;
    case 0x41:                                      /* switch 1 */
        hero_resolve_stick_direction(0.050000004f, 0);
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            HeroUpdateHopVelocity();
        }
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), 0.0033333334f);
        if (((Hero *)g_hero_state)->f[0xF8/4] < -0.16666667f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.16666667f;
        }
        break;
    case 0x44:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f) {
            hero_start_pose_offset(0.0f, 0.20943955f, 0.0f);
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0055555557f);
        break;
    case 0x40:                                      /* switch 1 */
    case 0x4C:                                      /* switch 1 */
        hero_resolve_stick_direction(0.050000004f, 0);
        var_f14 = 0.16580631f;
        var_f12_21 = 0.033f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            var_f14 = 0.19489513f;
            var_f12_21 = 0.037f;
        }
        hero_steer_heading(0, var_f12_21, 0.15f, var_f14);
        hero_approach_speed(0.005f, 0.0055555557f);
        if (((Hero *)g_hero_state)->f[0x174/4] < 0.011666667f) {
            ((Hero *)g_hero_state)->b[0x40C] = 1U;
            if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)g_hero_state)->b[0x40F] = 1U;
            }
        }
        temp_f20_18 = ReadPadFloatHistory(0);
        if ((FastDiffRots(temp_f20_18, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
            ((Hero *)g_hero_state)->b[0x40F] = 1U;
            ((Hero *)g_hero_state)->b[0x40C] = 1U;
        }
        if (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) < 0.087266475f) {
            ((Hero *)g_hero_state)->b[0x40C] = 0U;
        }
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            if (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) < 0.06981318f) {
                ((Hero *)g_hero_state)->b[0x40F] = 0U;
            }
            if (((Hero *)g_hero_state)->b[0x40F] != 0) {
                var_f2_4 = 0.050000004f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.02122066f);
                if (var_f2_4 < 0.0f) {
                    var_f2_4 = 0.0f;
                }
                if (var_f2_4 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = var_f2_4;
                }
            }
        }
        if (((Hero *)g_hero_state)->b[0x40C] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1A0/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        DeflectHeroOffSteepSurface(1);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
            hero_cancel_velocity_into_wall();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        }
        break;
    case 0x42:                                      /* switch 1 */
        temp_f12_6 = vec_length_xy((s32)(g_hero_state + 0xF0));
        if (*(s16 *)(g_hero_state + 0x34E) != 0) {
            temp_f12_6 = temp_f12_6 * 0.99f;
        } else {
            temp_f12_6 = temp_f12_6 * 0.92f;
        }
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), temp_f12_6);
        temp_v1_38 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
        M2C_FIELD(temp_v1_38, s32* , 0xF8) = 0;
        if (M2C_FIELD(temp_v1_38, s16* , 0x34E) != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0) + 0x30, 0.0061111115f);
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.004f);
        }
        break;
    case 0x49:                                      /* switch 1 */
    case 0x4A:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0xC20/4] = 1.3f;
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)m60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &v40[0], (s32) (((void*)g_hero_state) + 0x2C0), (s32) ((TI128*)m60));
        } else {
            FastVecCross((s32) &v40[0], (s32) ((TI128*)m60), (s32) (((void*)g_hero_state) + 0x2C0));
        }
        vec_scale_to_length((s32) &v40[0], (s32) &v40[0], 0.2f);
        FastVecAdd((s32) &v50[0], (s32)(g_hero_state + 0x80), (s32) &v40[0]);
        if ((hero_find_ledge_grab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab((s32) &v50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)v0), (s32)(g_hero_state + 0x80));
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), D_L11_002A4BB0[FloatToInt(((Hero *)g_hero_state)->f[0xC38/4])] * 0.5f);
            break;
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (sp114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (sp118 != M2C_FIELD(temp_fp, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}

