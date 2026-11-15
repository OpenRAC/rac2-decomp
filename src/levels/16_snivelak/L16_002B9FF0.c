#include "names.h"
/* func_L16_002B9FF0 (Snivelak): the hero state handler, a 147-way switch on the state at
   0x2294 over 36 bodies (22316 bytes, level 16 only).  One function: one prologue, one
   return.  It is func_L03_002BF8F0 (Endako) with the states 0x3F-0x44, 0x46, 0x47, 0x49-0x4E
   and 0x7A left to the common tail, and with states 0x65 and 0x78 as in
   func_L20_002CD928.  Ported from that match by renaming the per-level symbols and pruning.

   Flags (config/cflags.txt) are the same as Endako: -g, -ffast-math, -frac2-zero-ti-por,
   -frac2-hazard-labels. */

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
extern f32 D_L16_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L16_001A8FF0 MACRO_ADDR;
extern u8 D_L16_001ACE68[];
extern s32 D_L16_001AFF00 MACRO_ADDR;
extern s32 D_L16_001B2AC8 MACRO_ADDR;
extern s32 D_L16_001B3730 MACRO_ADDR;
extern s32 D_L16_001B3738 MACRO_ADDR;
extern u8 D_L16_001B99C0[];
extern u8 D_L16_001B9B18[];
extern u8 D_L16_001B9D88[];
extern u8 D_L16_001C3FC0[];
extern u8 D_L16_0025D710[];
extern u8 D_L16_0025D770[];
extern u8 D_L16_0025D774[];
extern Rec2C D_L16_0025F290[];
extern u8 D_L16_00263DA0[];
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
extern void UpdateHeroVelocityForStateWithYawSpring(void);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_apply_mode_pose_offsets(void);
extern void hero_apply_mode_pose_offsets(void);
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
extern void hero_update_held_grab(void);
extern s32 shooter_update_ranged_attack(s32);
extern s32 hero_get_weapon_anim_id(s32);
extern void hero_exit_vehicle_mode(s32);
extern void ClipHeroVelocityAgainstWall(s32);
extern void hero_l20_set_state(s32, s32);
/* Runs the player's per-frame behaviour for the current action (walking, jumping, swinging, swimming and so on). */
void hero_update_state_handler(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 vecA[4] __attribute__((aligned(16)));
    f32 vecB[4] __attribute__((aligned(16)));
    f32 vecC[4] __attribute__((aligned(16)));
    f32 vecD[4] __attribute__((aligned(16)));
    f32 vecE[4] __attribute__((aligned(16)));
    f32 vecF[4] __attribute__((aligned(16)));
    f32 vecG[8] __attribute__((aligned(16)));
    f32 matrixA[16] __attribute__((aligned(16)));
    f32 vecH[4] __attribute__((aligned(16)));
    f32 vecI[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* varV0N3Uu2;
    void* varS1N5Uu2;
    f32 varF12N16Uu2;
    void* varA1N5Uu2;
    s32 varA0N2Uu2;
    void* varS0N3Uu2;
    s32 varV0N8Uu2;
    s32 varV1N4Uu2;
    void* varA0N13Uu2;
    s32 varA0N2Uu3;
    void* varS0N3Uu3;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 stackE0;
    f32 stackE4;
    f32 stackE8;
    f32 stackEC;
    f32 stackF0;
    f32 stackF4;
    f32 stackF8;
    s32 stackFC;
    f32 stack100;
    s32 stack104;
    f32 stack108;
    f32 stack10C;
    f32 stack110;
    s32 stack114;
    s32 stack118;
    s32 stack11C;
    f32 tempF0;
    f32 tempF0N10;
    f32 tempF0N11;
    f32 tempF0N12;
    f32 tempF0N13;
    f32 tempF0N14;
    f32 tempF0N15;
    f32 tempF0N16;
    f32 tempF0N17;
    f32 tempF0N18;
    f32 tempF0N19;
    f32 tempF0N20;
    f32 tempF0N21;
    f32 tempF0N22;
    f32 tempF0N23;
    f32 tempF0N24;
    f32 tempF0N25;
    f32 tempF0N26;
    f32 tempF0N27;
    f32 tempF0N28;
    f32 tempF0N29;
    f32 tempF0N2;
    f32 tempF0N30;
    f32 tempF0N3;
    f32 tempF0N4;
    f32 tempF0N5;
    f32 tempF0N6;
    f32 tempF0N7;
    f32 tempF0N8;
    f32 tempF0N9;
    f32 tempF12;
    f32 tempF12N2;
    f32 tempF12N3;
    f32 tempF12N4;
    f32 tempF12N5;
    f32 tempF12N6;
    f32 tempF12N7;
    f32 tempF1;
    f32 tempF1N10;
    f32 tempF1N11;
    f32 tempF1N12;
    f32 tempF1N13;
    f32 tempF1N14;
    f32 tempF1N15;
    f32 tempF1N16;
    f32 tempF1N17;
    f32 tempF1N2;
    f32 tempF1N3;
    f32 tempF1N4;
    f32 tempF1N5;
    f32 tempF1N6;
    f32 tempF1N7;
    f32 tempF1N8;
    f32 tempF1N9;
    f32 tempF20;
    f32 tempF20N10;
    f32 tempF20N11;
    f32 tempF20N12;
    f32 tempF20N13;
    f32 tempF20N14;
    f32 tempF20N15;
    f32 tempF20N16;
    f32 tempF20N17;
    f32 tempF20N18;
    f32 tempF20N19;
    f32 tempF20N2;
    f32 tempF20N3;
    f32 tempF20N4;
    f32 tempF20N5;
    f32 tempF20N6;
    f32 tempF20N7;
    f32 tempF20N8;
    f32 tempF20N9;
    f32 tempF21;
    f32 tempF21N2;
    f32 tempF21N3;
    f32 tempF22;
    f32 tempF22N2;
    f32 tempF22N3;
    f32 tempF24;
    f32 tempF2;
    f32 tempF2N2;
    f32 tempF2N3;
    f32 tempF2N4;
    f32 tempF2N5;
    f32 tempF2N6;
    f32 tempF2N7;
    f32 tempF3;
    f32 varF0;
    f32 varF0N10;
    f32 varF0N11;
    f32 varF0N12;
    f32 varF0N13;
    f32 varF0N14;
    f32 varF0N15;
    f32 varF0N2;
    f32 varF0N3;
    f32 varF0N4;
    f32 varF0N5;
    f32 varF0N6;
    f32 varF0N7;
    f32 varF0N8;
    f32 varF0N9;
    f32 varF12;
    f32 varF12N10;
    f32 varF12N11;
    f32 varF12N13;
    f32 varF12N14;
    f32 varF12N15;
    f32 varF12N16;
    f32 varF12N17;
    f32 varF12N18;
    f32 varF12N19;
    f32 varF12N20;
    f32 varF12N21;
    f32 varF12N22;
    f32 varF12N4;
    f32 varF12N5;
    f32 varF12N6;
    f32 varF12N7;
    f32 varF12N8;
    f32 varF12N9;
    f32 varF14;
    f32 varF14N2;
    f32 varF1;
    f32 varF1N2;
    f32 varF1N3;
    f32 varF1N4;
    f32 varF1N5;
    f32 varF20;
    f32 varF20N10;
    f32 varF20N11;
    f32 varF20N12;
    f32 varF20N13;
    f32 varF20N2;
    f32 varF20N3;
    f32 varF20N4;
    f32 varF20N5;
    f32 varF20N6;
    f32 varF20N7;
    f32 varF20N8;
    f32 varF20N9;
    f32 varF21;
    f32 varF21N2;
    f32 varF21N3;
    f32 varF21N4;
    f32 varF21N5;
    f32 varF21N6;
    f32 varF21N7;
    f32 varF22;
    f32 varF22N2;
    f32 varF23;
    f32 varF2;
    f32 varF2N2;
    f32 varF2N3;
    f32 varF2N4;
    f32 varF2N5;
    s16 tempA2N5;
    s32 tempV0N4;
    s16 tempV0N8;
    s32 tempV1N10;
    s32 tempV1N9;
    s32 tempA0N21;
    s32 tempA0N3;
    s32 tempA0N5;
    s32 tempA0N7;
    s32 tempA0N8;
    s32 tempA0N9;
    s32 tempA1N3;
    s32 tempA1N4;
    s32 tempA1N5;
    s32 tempA1N7;
    s32 tempA1N8;
    s32 tempA2;
    s32 tempA2N2;
    s32 tempA2N3;
    s32 tempA2N4;
    s32 tempS0N5;
    s32 tempS0N9;
    s32 tempS7;
    s32 tempV0;
    s32 tempV0N12;
    s32 tempV0N13;
    s32 tempV0N14;
    s32 tempV0N15;
    s32 tempV0N16;
    s32 tempV0N17;
    s32 tempV0N2;
    s32 tempV1N12;
    s32 tempV1N14;
    s32 tempV1N16;
    s32 tempV1N18;
    s32 tempV1N20;
    s32 tempV1N21;
    s32 tempV1N22;
    s32 tempV1N23;
    s32 tempV1N24;
    s32 tempV1N26;
    s32 tempV1N34;
    s32 tempV1N35;
    s32 tempV1N4;
    s32 tempV1N5;
    s32 tempV1N6;
    s32 tempV1N7;
    s32 tempV1N8;
    s32 varA0;
    s32 varA0N10;
    s32 varA0N11;
    s32 varA0N12;
    s32 varA0N2;
    s32 varA0N4;
    s32 varA0N5;
    s32 varA0N8;
    s32 varA0N9;
    s32 varA1N2;
    s32 varA2;
    s32 varS0;
    s32 varS0N2;
    s32 varS1;
    s32 varS1N2;
    s32 varS1N3;
    s32 varS7;
    s32 varV0;
    s32 varV0N2;
    s32 varV0N4;
    s32 varV0N5;
    s32 varV0N6;
    s32 varV0N7;
    s32 varV0N8;
    s32 varV1;
    s32 varV1N2;
    s32 varV1N3;
    s32 varV1N4;
    s32* varS1N4;
    s32* varS1N6;
    u16 tempV0N3;
    u16 tempV1N11;
    u16 tempV1N2;
    u32 tempA0;
    u32 tempV1;
    u32 tempV1N13;
    u32 tempV1N27;
    u32 tempV1N28;
    u32 tempV1N29;
    u32 tempV1N30;
    u32 tempV1N31;
    u32 tempV1N33;
    u32 tempV1N36;
    u32 tempV1N3;
    u32 varA1N3;
    u8 tempA0N14;
    u8 tempA0N2;
    u8 tempV1N25;
    u8 varA0N6;
    void* tempA0N10;
    void* tempA0N11;
    void* tempA0N12;
    void* tempA0N13;
    void* tempA0N15;
    void* tempA0N16;
    void* tempA0N17;
    void* tempA0N4;
    void* tempA0N6;
    void* tempA1;
    void* tempA1N2;
    void* tempA1N6;
    void* tempFp;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* tempS0;
    void* tempS0N2;
    void* tempS0N3;
    void* tempS0N4;
    void* tempS0N6;
    void* tempS0N7;
    void* tempS0N8;
    void* tempS1;
    void* tempS1N2;
    void* tempS1N3;
    void* tempS1N4;
    void* tempS1N5;
    void* tempS1N6;
    void* tempS1N7;
    void* tempS1N8;
    void* tempS2;
    void* tempS2N2;
    void* tempS2N3;
    void* tempS2N4;
    void* tempS2N5;
    void* tempS4;
    void* tempS4N2;
    void* tempS5;
    void* tempV0N10;
    void* tempV0N5;
    void* tempV0N6;
    void* tempV0N7;
    void* tempV0N9;
    void* tempV1N15;
    void* tempV1N17;
    void* tempV1N32;
    void* tempV1N37;
    void* tempV1N38;
    void* tempV1N39;
    void* varA0N13;
    void* varA0N7;
    void* varA1N5;
    void* varS0N3;
    void* varS1N5;
    void* varV0N3;

    stack114 = ((Hero *)g_hero_state)->i[0x2298/4];
    tempFp = ((Hero *)g_hero_state)->ptr[0x2290/4];
    stack118 = (s32) M2C_FIELD(tempFp, u8* , 0x43);
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
        tempV1 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((tempV1 == 1) || (tempV1 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vecA) = 0;
                vecA[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vecA), (s32)&D_L16_001B9B18[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)D_L16_001B9B18)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (tempA0N2 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (tempA0N2 == 0xE)) || (tempA0N2 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    tempA0N3 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    tempA0N3 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != tempA0N3) {
                        set_hero_animation(tempA0N3, 0, 5.0f);
                    }
                    tempF0 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = tempF0;
                    if (tempF0 < 0.55f) {
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
            tempV1N3 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (tempV1N3 == 3) {
                varF12 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (varF12 > 1.0f) {
                    varF12 = 1.0f;
                }
                tempA0N4 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                varF20 = varF12 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = varF20;
                if (M2C_FIELD(tempA0N4, u8* , 0x42) == M2C_FIELD(tempA0N4, u8* , 0x43)) {
                    varF1 = ((Hero *)g_hero_state)->f[0x174/4] / varF20;
                    if ((varF1 > 5.0f) && ((f32) M2C_FIELD(tempA0N4, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, varF1, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (tempV1N3 == 4) {
                varF20 = 0.0075000003f;
            } else {
                varF20 = 0.004916667f;
            }
            hero_approach_speed(0.0f, varF20);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(varF20);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                varA0N2 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(varA0N2, varA0N2 + 0x30, 0.0061111115f);
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
        tempA1N2 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)tempA1N2 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)tempA1N2 + 0xF0);
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
            tempV1N15 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(tempV1N15, u8* , 0x60) & 2) && (M2C_FIELD(tempV1N15, u8* , 0x42) == 0x36)) {
                set_hero_animation(hero_get_weapon_anim_id(0), 0, 5.0f);
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
        varV0N3 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (varV0N3 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(varV0N3, f32* , 0x10) - M2C_FIELD(tempFp, f32* , 0x10), M2C_FIELD(varV0N3, f32* , 0x14) - M2C_FIELD(tempFp, f32* , 0x14));
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
        varV0N3Uu2 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (varV0N3Uu2 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(varV0N3Uu2, f32* , 0x10) - M2C_FIELD(tempFp, f32* , 0x10), M2C_FIELD(varV0N3Uu2, f32* , 0x14) - M2C_FIELD(tempFp, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vecA, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        tempF0N4 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vecA));
        ((Hero *)g_hero_state)->f[0xAB0/4] = tempF0N4;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 60.0f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (tempF0N4 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        tempV1N16 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (tempV1N16 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.45000002f, 0.022222223f);
            tempV0N5 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            varF20N2 = mat_fast_helper_a(M2C_FIELD(tempV0N5, f32* , 0x10) - M2C_FIELD(tempFp, f32* , 0x10), M2C_FIELD(tempV0N5, f32* , 0x14) - M2C_FIELD(tempFp, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], varF20N2) > 1.5707964f) {
                    varF20N2 = FastAddRotations(varF20N2, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = varF20N2;
            hero_steer_heading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (tempV1N16 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((math_solve_quadratic((s32) &stackE8, (s32) &stackEC, -0.0058333334f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (stackE8 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = stackE8;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 20.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn24 = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vecA)), vecA[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn24, 0.10762865f);
        }
        vecC[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        tempF0N5 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        vecC[2] = 0;
        vecC[1] = tempF0N5;
        FastVecAdd((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)vecB), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vecC));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vecB), ((Hero *)g_hero_state)->f[0xAA0/4]);
        tempF0N6 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (tempF0N6 < 30.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((30.0f - tempF0N6) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.004166667f);
        qcopy(vecA, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)vecA));
        FastVecAdd((s32) ((TI128*)vecB), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)vecD), (s32) ((TI128*)vecB), (s32)((TI128*)vecA));
        vec_scale_to_length((s32) ((TI128*)vecD), (s32) ((TI128*)vecD), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32) ((TI128*)vecD));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)vecC), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(tempFp, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        tempV1N17 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        tempF24 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (tempV1N17 != 0) {
            tempV0N6 = M2C_FIELD(tempV1N17, void** , 0x68);
            if ((tempV0N6 != 0) && (M2C_FIELD(tempV0N6, s32* , 0x34) != 0)) {
                varF20N3 = M2C_FIELD(tempV1N17, f32* , 0xF8);
                if (FastDiffRots(varF20N3, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    varF20N3 = FastAddRotations(varF20N3, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), varF20N3, (s32) (((void*)g_hero_state) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)vecA), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)vecA), (s32)((TI128*)vecA), 1.0f);
        if (vecA[2] < 0.23f) {
            vecA[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)vecC));
        vecC[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vecE), (s32) ((TI128*)vecC));
        matrix_from_basis_rows((s32) ((TI128*)matrixA), (s32) ((TI128*)vecE));
        transform_vector((s32)((TI128*)vecA), (s32)((TI128*)vecA), (s32) ((TI128*)matrixA));
        vecB[0] = -mat_fast_helper_a(square_root((vecA[0] * vecA[0]) + (vecA[2] * vecA[2])), vecA[1]);
        tempF0N7 = mat_fast_helper_a(vecA[2], vecA[0]);
        vecB[1] = tempF0N7;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), tempF0N7, (s32) (((void*)g_hero_state) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), vecB[0], (s32) (((void*)g_hero_state) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        varS7 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((varS7 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x29) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                varF20N4 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0035f;
                if (varF20N4 > 0.083333336f) {
                    varF20N4 = 0.083333336f;
                }
                vecD[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * varF20N4;
                tempF0N8 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * varF20N4;
                tempA0N10 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vecD[2]) = 0;
                vecD[1] = tempF0N8;
                FastVecAdd((s32) tempA0N10, (s32) tempA0N10, (s32) ((TI128*)vecD));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                tempS2N2 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) tempS2N2, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    tempS1N2 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) tempS1N2, (s32) (((void*)g_hero_state) + 0x110), 0.011111111f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) tempS1N2) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vecD), (s32) tempS2N2, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) tempS1N2, (s32) tempS1N2, 0.015833333f);
                    }
                }
                tempF20N3 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vecD), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vecD), (s32) ((TI128*)vecD), tempF20N3);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vecD));
            }
        }
        tempV0N7 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (tempV0N7 != 0) {
            tempS0 = M2C_FIELD(tempV0N7, void** , 0x68);
            tempS1N3 = ((void*)g_hero_state) + 0xF0;
            if (tempS0 != 0) {
                tempF0N9 = FastVecLength((s32) tempS1N3);
                tempF12 = M2C_FIELD(tempS0, f32* , 0xC);
                stackF0 = tempF0N9;
                if (tempF12 < tempF0N9) {
                    ApproachValue((s32) &stackF0, tempF12, 0.004166667f);
                    vec_scale_to_length((s32) tempS1N3, (s32) tempS1N3, stackF0);
                }
            }
        }
        tempF0N10 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        tempS5 = ((void*)g_hero_state) + 0x80;
        tempS4N2 = ((void*)g_hero_state) + 0xF0;
        vecI[0] = math_fast_sin_or_cos_a(tempF0N10) * 0.15f;
        tempF0N11 = math_fast_sin_or_cos_b(tempF0N10) * 0.15f;
        (*(s32*)&vecI[2]) = 0;
        vecI[1] = tempF0N11;
        FastVecAdd((s32) &vecI[0], (s32) &vecI[0], (s32) tempS5);
        FastVecAdd((s32) ((TI128*)vecD), (s32) &vecI[0], (s32) tempS4N2);
        FastVecSub((s32) ((TI128*)vecH), (s32) ((TI128*)vecD), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vecH), (s32) ((TI128*)vecH), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vecD), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vecH));
        FastVecSub((s32) tempS4N2, (s32) ((TI128*)vecD), (s32) &vecI[0]);
        tempF20N4 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        tempF20N5 = ((Hero *)g_hero_state)->f[0xAE4/4] - tempF20N4;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vecH))) {
            vec_scale_to_length((s32) ((TI128*)vecH), (s32) ((TI128*)vecH), tempF20N5);
            FastVecAdd((s32) tempS5, (s32) tempS5, (s32) ((TI128*)vecH));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (varS7 != 0)) {
            min2B = 0.23333335f;
            tempF0N12 = vec_length_xy((s32) tempS4N2);
            stackF4 = tempF0N12;
            if (tempF0N12 < min2B) {
                math_spring_float_to_goal((s32) &stackF4, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                vecD[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                tempF0N13 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vecD[2] = 0.0f;
                vecD[1] = tempF0N13 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) tempS4N2, (s32) tempS4N2, (s32) ((TI128*)vecD));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((tempF24 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            tempF20N6 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            tempV0N8 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (tempV0N8 != 0) {
                varV0N4 = tempV0N8 == 1;
            } else {
                (*(TI128*)vecD) = ((Hero *)g_hero_state)->q[0x110/16];
                varV0N4 = hero_get_speed_along_forward((s32) ((TI128*)vecD)) > 0.0f;
            }
            if (varV0N4 != 0) {
                if (M2C_FIELD(tempFp, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    tempV0N9 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(tempV0N9, u8* , 0x42) == M2C_FIELD(tempV0N9, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, tempF20N6, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(tempFp, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                tempV0N10 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(tempV0N10, u8* , 0x42) == M2C_FIELD(tempV0N10, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, tempF20N6, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L16_0025F290[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        varS1N2 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            varS1N2 = 1;
        }
        tempA1N4 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (tempA1N4 != 0) {
            FastVecSub((s32)((TI128*)vecA), tempA1N4 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            tempF0N14 = cam_get_view_space_vector_length((s32)((TI128*)vecA));
            if (((tempF0N14 > 2.0f) && (tempF0N14 < 5.0f)) || (varS1N2 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
            }
            hero_approach_speed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length((s32) ((TI128*)vecB), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vecB));
        } else {
            if ((varS1N2 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
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
        tempF1N6 = ((Hero *)g_hero_state)->f[0x31C/4];
        varF21 = 0.12833333f;
        if (tempF1N6 > 2.25f) {
            varF21 = 0.064166665f;
        } else if (tempF1N6 > 1.8f) {
            varF21 = 0.08983333f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(vecA, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)vecA), (s32)((TI128*)vecA), -0.5f);
            vec_scale_to_length((s32) &vecE[0], (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vecB), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &vecE[0]);
            vecB[3] = 5627.925f;
            (*(u8*)((u8*)vecC+9)) = 1;
            (*(u16*)((u8*)vecC+10)) = 0x47;
            (*(u8*)((u8*)vecC+8)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)vecA), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vecB));
        }
        if (math_is_below_plane_within_depth(25.7f) != 0) {
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L16_001B99C0)->f[0x180/4] = 0.1f;
                ((Hero *)D_L16_001B99C0)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)D_L16_001B99C0)->i[0x16C/4] = 0;
            }
        }
        tempV1N18 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xE;
        if (tempV1N18 < 9) {
            tempS0N2 = ((void*)g_hero_state) + 0xF0;
            stackF8 = cam_get_view_space_height((s32) tempS0N2);
            ApproachValue((s32) &stackF8, varF21, 0.041666668f);
            cam_set_view_space_height((s32) tempS0N2, (s32) tempS0N2, stackF8);
        } else if (tempV1N18 > lim3) {
            tempS1N4 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) tempS1N4, (s32) tempS1N4, 0.036111113f);
            if (cam_get_view_space_height((s32) tempS1N4) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            varF20N5 = -0.6166667f;
            if (D_L16_001A8FF0 != 0) {
                varF20N5 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) tempS1N4) < varF20N5) {
                cam_set_view_space_height((s32) tempS1N4, (s32) tempS1N4, varF20N5);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L16_0025F290[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        varA0N8 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (varA0N8 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                varS1N3 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    tempS0N3 = ((void*)g_hero_state) + 0xBC0;
                    varF20N6 = hero_get_direction_angle_delta((s32) tempS0N3, 0);
                    varF0N3 = hero_get_direction_angle_delta((s32) tempS0N3, 1);
                } else {
                    varF20N6 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    varF0N3 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (varF0N3 < 4.3633237f) {
                    varS1N3 = 1;
                }
                if (varF20N6 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (varF0N3 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (varS1N3 != 0) {
                    hero_steer_heading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    hero_steer_heading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    varA0N9 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xC)) {
                        varA0N9 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        varA0N9 = 0;
                    }
                    if (varA0N9 != 0) {
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
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L16_0025F290[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        tempA1N5 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        tempS2N3 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)D_L16_0025F290;
        if ((tempA1N5 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            tempS1N5 = ((void*)g_hero_state) + 0x80;
            varF12N13 = vec_distance_xy(tempA1N5 + 0x10, (s32) tempS1N5);
            if ((*(s32*)&D_L16_001A8FF0) != 0) {
                varF12N13 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) tempS1N5);
            }
            varF12N13 = varF12N13 - 0.5f;
            if (varF12N13 < 0.0f) {
                varF12N13 = 0.0f;
            }
            tempV1N20 = M2C_FIELD(tempS2N3, s32* , 4);
            if (tempV1N20 == 0) {
                varF0N4 = 0.75f;
                varF21N3 = 0.8f;
                varF22 = 4.0f;
            } else if (tempV1N20 == 1) {
                varF0N4 = 0.6f;
                varF21N3 = 1.7f;
                varF22 = 4.0f;
            } else {
                varF0N4 = 1.3f;
                varF21N3 = 1.7f;
                varF22 = 1.9f;
            }
            tempF20N8 = varF12N13 - varF0N4;
            if (math_fabs(tempF20N8) < (varF21N3 + 3.0f)) {
                varF12N15 = tempF20N8 * 1.1111112f;
                if (varF22 < varF12N15) {
                    varF12N15 = varF22;
                }
                if (varF12N15 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = varF12N15;
                }
            }
        }
        tempV1N21 = M2C_FIELD(tempS2N3, s32* , 4);
        switch (tempV1N21) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            tempF1N7 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (tempF1N7 < 9.0f)) {
                if (tempF1N7 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (tempF1N7 > 7.0f) {
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
            varF0N5 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            varF0N5 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        tempF1N8 = math_fabs(varF0N5);
        if ((M2C_FIELD(tempS2N3, s32* , 4) == 1) && (varF0N5 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (tempF1N8 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        varV1N3 = 1;
        if ((M2C_FIELD(tempS2N3, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            varV1N3 = 0;
        }
        if (varV1N3 != 0) {
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
            tempA0N12 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) tempA0N12, (s32) tempA0N12, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L16_001A8FF0) != 0) {
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
        tempV1N22 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (tempV1N22 > lim) {
            if (tempV1N22 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            tempS0N4 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) tempS0N4);
            level_append_record_to_table((s32) tempS0N4, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) tempS0N4, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) tempS0N4, 0xC, 6, 0.0f);
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
            tempV1N24 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((tempV1N24 > lim) && (tempV1N24 < 0x16)) {
                tempS2N4 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (tempS2N4 != 0) {
                    tempS1N6 = ((void*)g_hero_state) + 0x80;
                    vecD[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vecD[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vecD[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vecA), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vecD));
                    (*(u8*)((u8*)vecB+9)) = 3;
                    vecA[3] = 5627.925f;
                    (*(u8*)((u8*)vecB+8)) = 0;
                    tempF22N2 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vecB+10)) = M2C_FIELD(tempS2N4, u16* , 0xAA);
                    vecE[0] = math_fast_sin_or_cos_a(tempF22N2) * 0.8f;
                    tempF0N15 = math_fast_sin_or_cos_b(tempF22N2) * 0.8f;
                    vecE[2] = 0.55f;
                    vecE[1] = tempF0N15;
                    FastVecAdd((s32) &vecE[0], (s32) &vecE[0], (s32) tempS1N6);
                    part_emit_effects_at_nearby_mobys((s32) tempS2N4, coll_process_hit(0.8f, (s32) &vecE[0], 0, (s32) tempS2N4, (s32)((TI128*)vecA)));
                    tempF22N2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vecE[0] = math_fast_sin_or_cos_a(tempF22N2) * 0.8f;
                    tempF0N17 = math_fast_sin_or_cos_b(tempF22N2) * 0.8f;
                    vecE[2] = 0.55f;
                    vecE[1] = tempF0N17;
                    FastVecAdd((s32) &vecE[0], (s32) &vecE[0], (s32) tempS1N6);
                    part_emit_effects_at_nearby_mobys((s32) tempS2N4, coll_process_hit(0.8f, (s32) &vecE[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vecA)));
                    tempF22N2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vecE[0] = math_fast_sin_or_cos_a(tempF22N2) * 0.8f;
                    tempF0N19 = math_fast_sin_or_cos_b(tempF22N2) * 0.8f;
                    vecE[2] = 0.55f;
                    vecE[1] = tempF0N19;
                    FastVecAdd((s32) &vecE[0], (s32) &vecE[0], (s32) tempS1N6);
                    part_emit_effects_at_nearby_mobys((s32) tempS2N4, coll_process_hit(0.8f, (s32) &vecE[0], 0, (s32) tempS2N4, (s32)((TI128*)vecA)));
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
            tempF20N9 = ReadPadFloatHistory(1);
            if ((FastDiffRots(tempF20N9, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            (*(TI128*)vecA) = ((Hero *)g_hero_state)->q[0xA60/16];
            tempF1N9 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vecA));
            ((Hero *)g_hero_state)->f[0x1B0/4] = tempF1N9;
            if (tempF1N9 < 0.011666667f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.011666667f;
            }
            vec_clear_128((s32) pA60);
        }
        varF20N7 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                tempF2N2 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (tempF2N2 > 0.78539824f)) {
                    varF20N7 = 0.0f;
                }
                hero_set_turn_rates();
            }
        }
        hero_apply_mode_pose_offsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            varF2N2 = 0.09916667f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.029178405f);
            if (varF2N2 < 0.0f) {
                varF2N2 = 0.0f;
            }
            if (varF2N2 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = varF2N2;
            }
        }
        k005 = varF20N7 * 0.005f;
        varF20N8 = 0.0055555557f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            varF1N2 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (varF1N2 > 1.0f) {
                varF1N2 = 1.0f;
            }
            if (varF1N2 < 0.2f) {
                varF1N2 = 0.2f;
            }
            varF20N8 = 0.004722222f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * varF1N2);
        }
        tempF2N3 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (tempF2N3 > 0.6108653f)) {
            varF1N3 = 1.0f - (tempF2N3 * 0.4f);
            if (varF1N3 < 0.0f) {
                varF1N3 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * varF1N3);
        }
        hero_approach_speed(k005, varF20N8);
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
        pad_clamp_stick_to_unit_range((s32)((TI128*)vecA), (s32) (((void*)g_hero_state) + 0x9F0), 0.17f);
        varF21N4 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * vecA[0];
        if ((*(s32*)&D_L16_001A8FF0) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3C) {
                varF21N4 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, varF21N4);
        }
        hero_approach_speed(0.027777778f, 0.004166667f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&D_L16_001A8FF0) != 0) {
            qcopy(vecB, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vecB), (s32) ((TI128*)vecB), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vecB), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vecB), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vecB), (s32) ((TI128*)vecB), (s32)(g_hero_state + 0xE0));
        tempV0N12 = coll_process_hit(0.57f, (s32) ((TI128*)vecB), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (tempV0N12 != 0) {
            FastVecScale((s32) ((TI128*)vecC), (s32)(g_hero_state + 0x110), 7.0f);
            for (varS0 = 0; varS0 < tempV0N12; varS0++) {
                if (moby_is_in_special_class_range(((s32 *)D_L16_001C3FC0)[varS0]) != 0) {
                    part_queue_impact_effect(((s32 *)D_L16_001C3FC0)[varS0], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vecC), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.017f, 0.3f);
        cam_set_limits_third(0.025f, 0.3f);
        cam_set_limits_fourth(0.03f, 0.27f);
        varF2N3 = varF21N4 * 27.0f;
        if (varF2N3 > 1.7f) {
            varF2N3 = 1.7f;
        } else if (varF2N3 < -1.7f) {
            varF2N3 = -1.7f;
        }
        tempF0N20 = varF2N3 * 0.5f;
        ((Hero *)D_L16_0025D710)->f[0x60/4] = (f32) -varF2N3;
        ((Hero *)D_L16_0025D710)->f[0x278/4] = tempF0N20;
        ((Hero *)D_L16_0025D710)->f[0x1C8/4] = tempF0N20;
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        tempV1N27 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (((u32) (tempV1N27 - 0x28) >= 2U) && (tempV1N27 != 0x3E)) {
            snd_update_slot_object(0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        } else {
            tempA2N2 = ((Hero *)g_hero_state)->i[0x242C/4];
            if (tempA2N2 != -1) {
                tempA0N13 = (tempA2N2 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(tempA0N13, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(tempA0N13, u8* , 0x74) != 0) {
                        snd_stop_voice(tempA2N2);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x242C/4] = -1;
        }
        tempV1N28 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((tempV1N28 == 0x27) || (tempV1N28 == 0x2A)) {
            qcopy(vecA, &((Hero *)g_hero_state)->q[0x80/16]);
            tempF20N13 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.0f, 0.52359885f));
            tempF21N3 = math_random_float_range(0.06666667f, 0.116666675f);
            vecB[0] = math_fast_sin_or_cos_a(tempF20N13) * tempF21N3;
            tempF0N23 = math_fast_sin_or_cos_b(tempF20N13) * tempF21N3;
            vecB[2] = 0.0f;
            vecB[1] = tempF0N23;
            vecB[2] = math_random_float_range(0.050000004f, 0.083333336f);
            vecB[3] = -0.008333334f;
            part_spawn_white_flash((s32)((TI128*)vecA), (s32) ((TI128*)vecB), 0, -1.0f);
        }
        tempA1N6 = ((Hero *)g_hero_state)->ptr[0x1248/4];
        stack11C = 0;
        tempS7 = (((LevelInfo *)D_L16_00263DA0)[g_item_slot_to_record[(s32)tempA1N6]].x1C != 0);
        if ((s32)tempA1N6 == 0xD) {
            tempS7 = 0;
        }
        if (tempS7 != 0) {
            stack11C = ((Hero *)g_hero_state)->b[0x22BA] != 0;
        }
        tempS1N7 = ((void*)g_hero_state) + 0x80;
        find_nearest_path_point(((Hero *)g_hero_state)->i[0x630/4], (s32) tempS1N7, (s32) (((void*)g_hero_state) + 0x5D0), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)g_hero_state)->i[0x664/4], (s32) tempS1N7, (s32) (((void*)g_hero_state) + 0x610), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        varA2 = 0;
        if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0699999f) {
            tempV1N29 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((tempV1N29 != 0x28) && (tempV1N29 != 0x3E) && (((Hero *)g_hero_state)->i[0x660/4] == 0)) {
                varA2 = ((Hero *)g_hero_state)->i[0x1BC/4] >= 0x1F;
            }
        }
        if (varA2 != 0) {
            ((Hero *)g_hero_state)->i[0x6C8/4] = (s32) (((Hero *)g_hero_state)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)g_hero_state)->i[0x6C8/4] = 0;
        }
        tempV0N13 = ((Hero *)g_hero_state)->i[0x640/4];
        if (((tempV0N13 != 0) && ((((Hero *)g_hero_state)->i[0x640/4] = tempV0N13 + 1) != 0)) || (varA2 != 0)) {
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x120/16]);
            tempV1N32 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(tempV1N32, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion();
            } else {
                M2C_FIELD(tempV1N32, f32* , 0xF8) = (f32) (M2C_FIELD(tempV1N32, f32* , 0xF8) - 0.0061111115f);
            }
        } else {
            tempF1N10 = (f32) ((Hero *)g_hero_state)->i[0x648/4];
            varF20N10 = ((Hero *)g_hero_state)->f[0x644/4] * tempF1N10;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                varF20N10 = ((Hero *)g_hero_state)->f[0x69C/4] * tempF1N10;
            }
            Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32)((TI128*)vecA), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], varF20N10);
            if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x664/4], (s32) ((TI128*)vecB), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], varF20N10);
            }
            if (((Hero *)g_hero_state)->i[0x1BC/4] >= 0x5B) {
                tempF20N14 = ((Hero *)g_hero_state)->f[0x170/4] * 30.0f;
                qcopy(vecC, &((Hero *)g_hero_state)->q[0x80/16]);
                stackFC = ((Hero *)g_hero_state)->i[0x634/4];
                stack100 = ((Hero *)g_hero_state)->f[0x638/4];
                tempS0N5 = Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vecC), (s32) &stackFC, (s32) &stack100, ((Hero *)g_hero_state)->i[0x654/4], tempF20N14);
                qcopy(vecD, &((Hero *)g_hero_state)->q[0x80/16]);
                stackFC = ((Hero *)g_hero_state)->i[0x634/4];
                stack100 = ((Hero *)g_hero_state)->f[0x638/4];
                if ((((tempS0N5 | Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vecD), (s32) &stackFC, (s32) &stack100, ((Hero *)g_hero_state)->i[0x654/4], tempF20N14 + 0.1f)) == 0) || (((Hero *)g_hero_state)->i[0x654/4] != 0)) && (((Hero *)g_hero_state)->u[0x2294/4] == 0x27)) {
                    varF20N11 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x64C/4], mat_fast_helper_a(vecD[0] - vecC[0], vecD[1] - vecC[1])) * 0.47f;
                    if (varF20N11 > 0.78539824f) {
                        varF20N11 = 0.78539824f;
                    }
                    if (varF20N11 < -0.78539824f) {
                        varF20N11 = -0.78539824f;
                    }
                    cam_set_limits_first(0.03f, 0.2f);
                    if (((Hero *)g_hero_state)->i[0x65C/4] != 0) {
                        (*(f32*)&D_L16_0025D774) = -varF20N11;
                    } else {
                        (*(f32*)&D_L16_0025D774) = varF20N11;
                    }
                }
            }
            tempV1N30 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((tempV1N30 != 0x28) && (tempV1N30 != 0x3E) && (tempV1N30 != 0x29)) {
                (*(f32*)&D_L16_0025D770) = mat_fast_helper_a(vec_length_xy((s32) (((void*)g_hero_state) + 0x110)), ((Hero *)g_hero_state)->f[0x118/4]);
            }
            if (tempS7 != 0) {
                k03 = 0.3f;
                cam_set_limits_fourth(0.017f, k03);
                cam_set_limits_second(0.027f, k03);
                cam_set_limits_third(0.027f, k03);
                tempA1N7 = ((Hero *)g_hero_state)->i[0x6A8/4];
                if (tempA1N7 != 0) {
                    FastVecSub((s32) ((TI128*)vecC), tempA1N7 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (s32) (((void*)g_hero_state) + 0x40));
                    tempF12N2 = mat_fast_helper_a(vecC[0], vecC[1]);
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        tempF12N2 = fast_subtract_rotations(tempF12N2, 1.5707965f);
                        varF1N4 = 0.2f;
                    } else {
                        tempF12N2 = fast_subtract_rotations(tempF12N2, -1.5707965f);
                        varF1N4 = 0.5f;
                    }
                    ((Hero *)D_L16_0025D710)->f[0x1C8/4] = (f32) (tempF12N2 * varF1N4);
                    ((Hero *)D_L16_0025D710)->f[0x278/4] = (f32) (tempF12N2 * k03);
                } else {
                    tempA0N14 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43);
                    if (tempA0N14 == 0x31) {
                        varF21N7 = 0.58823526f;
                        varF0N8 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        varF20N12 = 0.73303837f;
                        ((Hero *)D_L16_0025D710)->f[0x278/4] = varF0N8;
                        ((Hero *)D_L16_0025D710)->f[0x118/4] = FastAddRotations(varF20N12, ((Hero *)g_hero_state)->f[0x6A0/4] * varF21N7);
                        ((Hero *)D_L16_0025D710)->f[0x1C8/4] = FastAddRotations(varF20N12, ((Hero *)g_hero_state)->f[0x6A0/4] * varF21N7);
                    } else if (tempA0N14 == 0x48) {
                        varF21N7 = 0.5f;
                        varF0N8 = FastAddRotations(0.13962635f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        varF20N12 = -0.06981318f;
                        ((Hero *)D_L16_0025D710)->f[0x278/4] = varF0N8;
                        ((Hero *)D_L16_0025D710)->f[0x118/4] = FastAddRotations(varF20N12, ((Hero *)g_hero_state)->f[0x6A0/4] * varF21N7);
                        ((Hero *)D_L16_0025D710)->f[0x1C8/4] = FastAddRotations(varF20N12, ((Hero *)g_hero_state)->f[0x6A0/4] * varF21N7);
                    } else if (tempA0N14 == 0x47) {
                        varF21N7 = 0.58823526f;
                        varF0N8 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        varF20N12 = 0.73303837f;
                        ((Hero *)D_L16_0025D710)->f[0x278/4] = varF0N8;
                        ((Hero *)D_L16_0025D710)->f[0x118/4] = FastAddRotations(varF20N12, ((Hero *)g_hero_state)->f[0x6A0/4] * varF21N7);
                        ((Hero *)D_L16_0025D710)->f[0x1C8/4] = FastAddRotations(varF20N12, ((Hero *)g_hero_state)->f[0x6A0/4] * varF21N7);
                    }
                }
            }
            tempV0N15 = path_advance_index(((Hero *)g_hero_state)->i[0x630/4], ((Hero *)g_hero_state)->i[0x634/4], ((Hero *)g_hero_state)->i[0x648/4], ((Hero *)g_hero_state)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)vecC), (s32) &((TI128 *)((Hero *)g_hero_state)->ptr[0x630/4])[tempV0N15 + 1], (s32)((TI128*)vecA));
            if (FastVecLength((s32) ((TI128*)vecC)) < 0.001f) {
                if (((Hero *)g_hero_state)->i[0x634/4] == tempV0N15) {
                    ((Hero *)g_hero_state)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)g_hero_state)->f[0x64C/4] = mat_fast_helper_a(vecC[0], vecC[1]);
                ((Hero *)g_hero_state)->f[0x650/4] = mat_fast_helper_a(vec_length_xy((s32) ((TI128*)vecC)), M2C_BITWISE(f32, vecC[2]));
block_807:
                ((Hero *)g_hero_state)->f[0x1A0/4] = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], ((Hero *)g_hero_state)->f[0x658/4]);
                hero_steer_heading(0, 0.015f, 0.15f, 0.10471977f);
                tempV1N31 = ((Hero *)g_hero_state)->u[0x2294/4];
                if ((((u32) (tempV1N31 - 0x28) < 2U) && (((Hero *)g_hero_state)->b[0x49C] == 0)) || (tempV1N31 == 0x3E)) {
                    if (((Hero *)g_hero_state)->i[0x694/4] != 0) {
                        tempF0N27 = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x620/4] - ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x624/4] - ((Hero *)g_hero_state)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], tempF0N27) < 1.5707965f) {
                            ((Hero *)g_hero_state)->f[0x1A0/4] = tempF0N27;
                            hero_steer_heading(0, 0.04f, 0.2f, 0.10471977f);
                        }
                    }
                    if ((((Hero *)g_hero_state)->i[0x660/4] != 0) && (((Hero *)g_hero_state)->i[0x678/4] < 0x31)) {
                        FastVecSub((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32) ((TI128*)vecB));
                        tempV0N16 = ((Hero *)g_hero_state)->i[0x678/4] + 1;
                        ((Hero *)g_hero_state)->i[0x678/4] = tempV0N16;
                        FastVecScale((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (f32) tempV0N16 * 0.020833334f);
                        tempF20N15 = (f32) (((Hero *)g_hero_state)->i[0x678/4] - 1) * 0.020833334f;
                        FastVecSub((s32) ((TI128*)vecD), (s32)((TI128*)vecA), (s32) ((TI128*)vecB));
                        FastVecScale((s32) ((TI128*)vecD), (s32) ((TI128*)vecD), tempF20N15);
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + (M2C_BITWISE(f32, vecC[2]) - vecD[2]));
                        FastVecAdd((s32) ((TI128*)vecD), (s32) ((TI128*)vecB), (s32) ((TI128*)vecC));
                        FastVecSub((s32) ((TI128*)vecC), (s32) ((TI128*)vecD), (s32) (((void*)g_hero_state) + 0x80));
                        ((Hero *)g_hero_state)->f[0xF0/4] = vecC[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = vecC[1];
                        FastVecSub((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32) (((void*)g_hero_state) + 0x5D0));
                        tempF2N5 = ((Hero *)g_hero_state)->f[0x5D8/4];
                        tempF1N11 = ((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, vecC[2]);
                        ((Hero *)g_hero_state)->f[0x88/4] = tempF1N11;
                        if (tempF1N11 < tempF2N5) {
                            if (((Hero *)g_hero_state)->i[0x678/4] < 0x31) {
                                if (tempF1N11 < tempF2N5) {
                                    ((Hero *)g_hero_state)->f[0x88/4] = tempF2N5;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32)(g_hero_state + 0x5D0));
                        ((Hero *)g_hero_state)->f[0xF0/4] = vecC[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = vecC[1];
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, vecC[2]));
                        FastVecSub((s32) ((TI128*)vecD), (s32)(g_hero_state + 0x5D0), (s32)(g_hero_state + 0x80));
                        vecD[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)vecD)) > 0.016666668f) {
                            vec_scale_to_length((s32) ((TI128*)vecD), (s32) ((TI128*)vecD), 0.016666668f);
                        }
                        ((Hero *)g_hero_state)->f[0x80/4] = (f32) (((Hero *)g_hero_state)->f[0x80/4] + vecD[0]);
                        ((Hero *)g_hero_state)->f[0x84/4] = (f32) (((Hero *)g_hero_state)->f[0x84/4] + vecD[1]);
                    }
                    if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.006388889f);
                    } else {
                        ApplyHeroGravityAndJumpMotion();
                    }
                } else {
                    ((Hero *)g_hero_state)->i[0x660/4] = 0;
                    varF0N9 = 0.0f;
                    if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) && (stack11C != 0)) {
                        hero_resolve_stick_direction(1.0f, 0);
                        varF0N9 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1A0/4], ((Hero *)g_hero_state)->f[0x64C/4]);
                        if (varF0N9 > 0.78539824f) {
                            varF0N9 = 0.78539824f;
                        } else if (varF0N9 < -0.78539824f) {
                            varF0N9 = -0.78539824f;
                        }
                    }
                    math_approach_with_velocity((s32)(g_hero_state + 0x6A0), varF0N9, (s32)(g_hero_state + 0x6A4), 0.015f, 0.3f, 0.0f, 0);
                    ApproachValue((s32)(g_hero_state + 0x680), 0.20000002f, 0.004166667f);
                    stack104 = ((Hero *)g_hero_state)->i[0x634/4];
                    stack108 = ((Hero *)g_hero_state)->f[0x638/4];
                    qcopy(vecC, &((Hero *)g_hero_state)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vecC), (s32) &stack104, (s32) &stack108, ((Hero *)g_hero_state)->i[0x654/4], 0.3f);
                    tempF0N24 = mat_fast_helper_a(vec_distance_xy((s32)(g_hero_state + 0x5D0), (s32) ((TI128*)vecC)), M2C_BITWISE(f32, vecC[2]) - ((Hero *)g_hero_state)->f[0x5D8/4]);
                    if (tempF0N24 > 0.0f) {
                        varF12N17 = tempF0N24 * -0.07957746f;
                        if (tempF0N24 > 0.26179942f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 0;
                        } else if ((tempF0N24 < 0.13962635f) && (((Hero *)g_hero_state)->i[0x67C/4] == 0)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    } else {
                        varF12N17 = -tempF0N24 * 0.38197184f;
                        if (tempF0N24 < -0.19198623f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 1;
                        } else if ((tempF0N24 > -0.122173056f) && (((Hero *)g_hero_state)->i[0x67C/4] == 1)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < varF12N17) {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), varF12N17, 0.0022222223f);
                    } else {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), varF12N17, 0.00055555557f);
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] > 0.20000002f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = 0.20000002f;
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < -0.041666668f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = -0.041666668f;
                    }
                    tempF0N25 = ((Hero *)g_hero_state)->f[0x680/4] + ((Hero *)g_hero_state)->f[0x674/4];
                    ((Hero *)g_hero_state)->f[0x644/4] = tempF0N25;
                    if (tempF0N25 < 0.0f) {
                        ((Hero *)g_hero_state)->f[0x644/4] = 0.0f;
                    }
                    tempS0N6 = ((void*)g_hero_state) + 0x5D0;
                    FastVecSub((s32) (((void*)g_hero_state) + 0xF0), (s32)((TI128*)vecA), (s32) tempS0N6);
                    tempS2N5 = ((void*)g_hero_state) + 0x80;
                    FastVecSub((s32) ((TI128*)vecC), (s32) tempS0N6, (s32) tempS2N5);
                    stack10C = -FastVecLength((s32) ((TI128*)vecC));
                    math_spring_float_to_goal((s32) &stack10C, (s32) (((void*)g_hero_state) + 0x6AC), 0.0f, 0.03f, 0.3f, 0.116666675f);
                    tempF0N26 = FastVecLength((s32) ((TI128*)vecC));
                    if (tempF0N26 < ((Hero *)g_hero_state)->f[0x6AC/4]) {
                        ((Hero *)g_hero_state)->f[0x6AC/4] = tempF0N26;
                    }
                    tempF12N3 = ((Hero *)g_hero_state)->f[0x6AC/4];
                    if (tempF12N3 < tempF0N26) {
                        vec_scale_to_length((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), tempF12N3);
                    }
                    FastVecAdd((s32) tempS2N5, (s32) tempS2N5, (s32) ((TI128*)vecC));
                    tempF3 = ((Hero *)g_hero_state)->f[0x88/4];
                    tempF2N4 = ((Hero *)g_hero_state)->f[0x5D8/4];
                    if (tempF3 < tempF2N4) {
                        if (((Hero *)g_hero_state)->f[0x31C/4] < 1.0f) {
                            if (tempF3 < tempF2N4) {
                                ((Hero *)g_hero_state)->f[0x88/4] = tempF2N4;
                            }
                        }
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x14) {
                        tempF0N28 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.3490659f, 0.6108653f));
                        vecF[0] = math_fast_sin_or_cos_a(tempF0N28);
                        vecF[1] = math_fast_sin_or_cos_b(tempF0N28);
                        vecF[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)vecC), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &vecF[0]);
                        qcopy(vecG, &((Hero *)g_hero_state)->q[0x80/16]);
                        vecG[2] += 0.6f;
                        coll_process_hit(1.0f, (s32) ((TI128*)vecG), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vecC));
                    }
                }
            }
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
    case 0x19:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)vecG), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &vecE[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)vecG));
        } else {
            FastVecCross((s32) &vecE[0], (s32) ((TI128*)vecG), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &vecE[0], (s32) &vecE[0], 0.2f);
        FastVecAdd((s32) &vecF[0], (s32)(g_hero_state + 0x80), (s32) &vecE[0]);
        if ((ProbeLedgeGrab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (ProbeLedgeGrab((s32) &vecF[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vecA)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vecA), (s32)(g_hero_state + 0x80));
            varV0N8 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            varV1N4 = (s32)D_L16_001ACE68;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(varV0N8 + varV1N4) * 0.5f);
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
            varF12N18 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                varF12N18 = 0.43633235f;
            }
            qcopy(vecA, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &vecA[1], varF12N18, (s32) (((void*)g_hero_state) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            math_approach_with_velocity((s32)((TI128*)vecA), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_refresh_speed_from_timer();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            UpdateHeroVelocityForStateWithYawSpring();
        }
        varS1N5 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) varS1N5, (s32) varS1N5, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) varS1N5) < -0.8333334f) {
            cam_set_view_space_height((s32) varS1N5, (s32) varS1N5, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        varS1N5Uu2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) varS1N5Uu2, (s32) varS1N5Uu2, vec_length_xy((s32) varS1N5Uu2) * 0.9f);
        hero_apply_mode_transform((s32) varS1N5Uu2, (s32) varS1N5Uu2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) varS1N5Uu2) < -0.8333334f) {
            cam_set_view_space_height((s32) varS1N5Uu2, (s32) varS1N5Uu2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        varA0N12 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            varA0N12 = 0;
        }
        if (varA0N12 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            tempA0N15 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) tempA0N15, (s32) tempA0N15, 0.025f);
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
        tempF12N4 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (tempF12N4 < 0.0f) && (tempF2N6 = ((Hero *)g_hero_state)->f[0x31C/4], (tempF2N6 < 1.2f))) {
            varF0N10 = (tempF2N6 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (varF0N10 < 0.0f) {
                varF0N10 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), tempF12N4 * varF0N10);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (tempF12N4 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L16_001B9D88) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.027f, 0.3f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.087266475f);
        varF12N19 = 0.0013888889f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            varF12N19 = 0.00055555557f;
        }
        hero_approach_velocity(varF12N19);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            tempA2N3 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (tempA2N3 != -1) {
                tempA0N16 = (tempA2N3 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(tempA0N16, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(tempA0N16, u8* , 0x74) != 0)) {
                    snd_stop_voice(tempA2N3);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            tempA2N4 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (tempA2N4 != -1) {
                tempA0N17 = (tempA2N4 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(tempA0N17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(tempA0N17, u8* , 0x74) != 0)) {
                    snd_stop_voice(tempA2N4);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        varF22N2 = 0.050000004f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            varF22N2 = 0.083333336f;
        }
        varF23 = 0.72f;
        tempF1N12 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            varF22N2 = 0.12833333f;
            varF23 = 0.98640007f;
        }
        if (tempF1N12 != 0.0f) {
            varF23 = tempF1N12;
        }
        tempS0N7 = ((void*)g_hero_state) + 0xF0;
        stack110 = cam_get_view_space_height((s32) tempS0N7);
        hero_resolve_stick_direction(varF22N2, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) tempS0N7, (s32) tempS0N7);
        math_spring_float_to_goal((s32) &stack110, (s32) (((void*)g_hero_state) + 0xA98), -varF22N2 * varF23, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) tempS0N7, (s32) tempS0N7, -stack110);
        tempF12N5 = ((Hero *)g_hero_state)->f[0x88/4];
        if (tempF12N5 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), tempF12N5, 0.06666667f);
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
        tempA2N5 = ((Hero *)g_hero_state)->h[0x4AC/2];
        tempA1N8 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (tempA1N8 == tempA2N5) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((tempA1N8 < tempA2N5) && (tempV1N33 = ((Hero *)g_hero_state)->u[0x2294/4], (tempV1N33 != 0xB)) && (tempV1N33 != 0x10) && (tempV1N33 != 0xC) && (tempV1N33 != 0x11) && (tempV1N33 != 0x1B) && (tempV1N33 != 0x89) && (tempV1N33 != 0x48))) {
            hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
            tempF20N16 = ((Hero *)g_hero_state)->f[0x1B4/4];
            if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (tempF20N16 * 0.4f);
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
            ((Hero *)g_hero_state)->f[0x1B4/4] = tempF20N16;
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
                tempV1N34 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (tempV1N34 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) tempV1N34 * 0.0044444446f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                tempV1N35 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (tempV1N35 < 0x22) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) tempV1N35 * 0.014722222f);
                }
            }
            if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                qcopy(vecA, &((Hero *)g_hero_state)->q[0x80/16]);
                cam_offset_point_in_view_space((s32)((TI128*)vecA), (s32)((TI128*)vecA), 0.5f);
                cam_offset_point_by_side_direction((s32) ((TI128*)vecB), (s32)((TI128*)vecA), 0.95f);
                if (CollLine((s32)((TI128*)vecA), (s32) ((TI128*)vecB), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                    ((Hero *)g_hero_state)->h[0x524/2] = 1;
                }
            }
        } else {
            UpdateHeroVelocityForStateWithYawSpring();
        }
        tempF1N14 = ((Hero *)g_hero_state)->f[0x318/4];
        tempF2N7 = ((Hero *)g_hero_state)->f[0x490/4];
        if (tempF2N7 < tempF1N14) {
            tempF0N29 = tempF2N7 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = tempF0N29;
            if (tempF1N14 < tempF0N29) {
                ((Hero *)g_hero_state)->f[0x490/4] = tempF1N14;
            }
        }
        tempF1N15 = ((Hero *)g_hero_state)->f[0x88/4];
        if (tempF1N15 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = tempF1N15;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            tempF1N16 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (tempF1N16 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = tempF1N16;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        tempV1N36 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((tempV1N36 == 0x10) || (tempV1N36 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vecA), 1, 0.8f, 0.0f, 0.3f);
                    tempV0N17 = coll_process_hit(0.9f, (s32)((TI128*)vecA), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (tempV0N17 != 0) {
                        FastVecScale((s32) ((TI128*)vecB), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (varS0N2 = 0; varS0N2 < tempV0N17; varS0N2++) {
                            if (moby_is_in_special_class_range(((s32 *)D_L16_001C3FC0)[varS0N2]) != 0) {
                                part_queue_impact_effect(((s32 *)D_L16_001C3FC0)[varS0N2], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vecB), 1.0f);
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
        varF20N13 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        varF0N12 = 0.0011111111f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB)) {
            varF0N12 = 0.0027777778f;
        }
        varF20N13 = varF20N13 - varF0N12;
        if (varF20N13 < 0.0f) {
            varF20N13 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        varS0N3 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) varS0N3, (s32) varS0N3, varF20N13);
        hero_apply_mode_transform((s32) varS0N3, (s32) varS0N3, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vecA), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vecA[0], vecA[1]);
        tempF0N30 = vec_length_xy((s32)((TI128*)vecA));
        if (tempF0N30 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vecA[0], vecA[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = tempF0N30;
            if (tempF0N30 < D_L16_001A7DAC[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L16_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L16_001A7DAC[1][1] * 0.016666668f;
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
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        break;
    case 0x63:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vecA), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)vecA), (s32)(g_hero_state + 0x160)) < 0.0f) {
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
    case 0x79:                                      /* switch 1 */
        part_emit_hero_radial_particles();
        /* fallthrough */
    case 0x78:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.016666668f;
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (stack114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (stack118 != M2C_FIELD(tempFp, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}

