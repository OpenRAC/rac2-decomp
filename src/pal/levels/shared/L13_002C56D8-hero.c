#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 x0[7]; s32 x1C; u8 x20[0xC0]; } LevelInfo;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
extern char g_pad_state[];
extern u8 g_pad_pressed_flags[];
extern f32 g_hero_l20_speed_scale_table[];
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
extern f32 g_hero_l20_speed_params[][4] MACRO_ADDR;
extern s32 g_hero_l20_lock_flag_a MACRO_ADDR;
extern u8 g_hero_state_machine_bytes[];
extern s32 g_hero_hazard_flag MACRO_ADDR;
extern s32 g_frame_l20_counter MACRO_ADDR;
extern s32 g_ripple_surface MACRO_ADDR;
extern s32 g_ripple_surface_data MACRO_ADDR;
extern u8 g_hero_l20_extra_state[];
extern u8 g_hero_aim_data[];
extern u8 g_camera_l20_view_height[];
extern u8 g_special_moby_table[];
extern u8 g_hero_l20_state_alias[];
extern u8 g_hero_speed_blend_value[];
extern u8 g_hero_l20_signed_scalar[];
extern Rec2C g_hero_l20_action_table[];
extern u8 g_hero_l20_blend_table[];
extern u8 g_item_l20_record_table[];
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
extern char *CreateMoby(s32);
extern void moby_transform_joint_to_world(s32, s32, s32);
extern void func_002A0F48(s32);
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_signed_float_range(f32, f32);
extern s32 math_solve_quadratic(s32, s32, f32, f32, f32);
extern void make_hit_descriptor(s32, s32, s32, f32, s32);
extern int coll_sweep_from_object(s32, s32, s32, f32, f32, f32, s32, s32, s32);
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
extern void part_spawn_white_flash_pal(s32, s32, s32, f32);
extern void *part_spawn_bubble_pal(s32, s32, f32, f32);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, s32);
extern void RippleDisturb(s32, s32, void *, f32, f32, f32, f32);
extern void pad_clamp_stick_to_unit_range(s32, s32, f32);
extern float AdjustHeroAnimationSpeedForTargetFrame(f32, f32, f32, f32);
extern f32 math_blend_table_entries_by_clock(s32, s32);
extern void hero_start_pose_offset(f32, f32, f32);
extern void part_spawn_jittered_after_delay(s32, s32);
extern void part_emit_hero_side_particles_pal(s32, s32);
extern void part_emit_hero_trail_spark_pal(s32, s32);
extern void EmitHeroRandomizedMotionEffects_pal(s32, s32, s32);
extern void part_emit_hero_dust_and_debris_pal(s32, s32, s32);
extern void EmitHeroTimedEffects_pal(void);
extern void cam_set_limits_first(f32, f32);
extern void cam_set_limits_second(f32, f32);
extern void cam_set_limits_third(f32, f32);
extern void cam_set_limits_fourth(f32, f32);
extern void ProbeHeroAirborneWallContact_pal(void);
extern s32 hero_find_ledge_grab_pal(s32, s32, s32);
extern s32 hero_slot_item_id(s32);
extern void hero_update_turn_from_anim_pal(void);
extern s32 math_is_below_plane_within_depth(f32);
extern void hero_resolve_stick_direction(f32, s32);
extern void hero_update_target_speed_pal(void);
extern void hero_rotate_matrix(f32, f32, f32);
extern void hero_steer_heading(s32, f32, f32, f32);
extern void hero_set_turn_rates_pal(void);
extern void hero_approach_speed(f32, f32);
extern void hero_compute_push_direction(f32);
extern void hero_set_push_direction(s32);
extern void hero_cancel_velocity_into_wall_pal(void);
extern void hero_build_move_impulse(f32, f32);
extern f32 hero_get_speed_along_forward(s32);
extern void ApproachHeroVelocity_pal(f32);
extern void ApplyHeroGravityAndJumpMotion_pal(void);
extern void hero_update_airborne_steering_pal(void);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_apply_mode_pose_offsets_pal(void);
extern void UpdateHeroMotionResponseParameters_pal(void);
extern void UpdateHeroLeanAndSwayParameters(void);
extern void hero_apply_reference_tilt_rotation(s32, s32, s32, f32, f32, f32);
extern void hero_shrink_vector_by_amount(f32);
extern void hero_steer_reference_point_pal(void);
extern f32 hero_get_direction_angle_delta(s32, s32);
extern s32 hero_play_sound(s32, s32);
extern void snd_update_slot_object(s32, s32, s32);
extern void hero_try_surface_push_response(f32, f32, f32);
extern void part_emit_effects_at_nearby_mobys_pal(s32, s32);
extern void part_emit_hero_radial_particles_pal(void);
extern void hero_setup_attached_object_transform_pal(void);
extern void hero_update_height_offset_pal(void);
extern s32 hero_try_start_grab_pal(void);
extern void set_hero_animation_pal(s32, s32, f32);
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
extern s32 actuator_play_pattern(s32);
extern s32 func_L00_002EE4D8(s32, s32, f32);
extern s32 math_lerp_int(s32, s32, f32);
extern void level_init_pending_slot(s32, s32);
extern void level_append_record_to_table(s32, s32, s32, f32);
extern void moby_update_transform_history_followers(s32, s32);
extern void vec_add_offset(s32, s32, f32, f32, f32);
extern s32 math_update_angle_and_blend(s32, s32, s32, f32);
extern f32 ReadPadFloatHistory(s32);
extern void *part_spawn_two_point_effect(s32, s32, f32);
extern s32 path_advance_index(s32, s32, s32, s32);
extern s32 Spline_AdvanceByDistance(s32, s32, s32, s32, s32, f32);
extern s32 find_nearest_path_point(s32, s32, s32, s32, s32, s32, f32, f32, f32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern s32 shooter_update_ranged_attack(s32);
extern s32 hero_get_weapon_or_form_id(s32);
extern void DeflectHeroOffSteepSurface_pal(s32);
extern s32 ref_US2_L13_002C58E8_01;
extern char g_impact_effect_data[] MACRO_ADDR;
extern void moby_l00_raise_state_to_8();
extern void moby_raise_state_to_eight_copy();

/* Per-frame update of the hero (Ratchet): reads the controller and runs the hero's state machine
   (walking, jumping, swimming, weapons and so on) for this level (PAL release). */
void hero_l13_update_state_machine_pal(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 v0[4] __attribute__((aligned(16)));
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    f32 v50[4] __attribute__((aligned(16)));
    f32 v60[4] __attribute__((aligned(16)));
    f32 m70[16] __attribute__((aligned(16)));
    f32 vB0[4] __attribute__((aligned(16)));
    f32 vC0[4] __attribute__((aligned(16)));
    f32 vD0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    f32 k30;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* i_val1;
    void* i_val2;
    f32 f_val1;
    void* i_val3;
    s32 i_val4;
    void* i_val5;
    s32 i_val6;
    s32 i_val7;
    void* i_val8;
    s32 i_val9;
    void* i_val10;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 i_stack1;
    f32 i_stack2;
    f32 i_stack3;
    f32 i_stack4;
    f32 i_stack5;
    f32 i_stack6;
    f32 i_stack7;
    s32 i_stack8;
    f32 i_stack9;
    s32 i_stack10;
    f32 i_stack11;
    f32 i_stack12;
    f32 i_stack13;
    s32 i_stack14;
    s32 i_stack15;
    s32 i_stack16;
    f32 f_temp1;
    f32 f_temp2;
    f32 f_temp3;
    f32 f_temp4;
    f32 f_temp5;
    f32 f_temp6;
    f32 f_temp7;
    f32 f_temp8;
    f32 f_temp9;
    f32 f_temp10;
    f32 f_temp11;
    f32 f_temp12;
    f32 f_temp13;
    f32 f_temp14;
    f32 f_temp15;
    f32 f_temp16;
    f32 f_temp17;
    f32 f_temp18;
    f32 f_temp19;
    f32 f_temp20;
    f32 f_temp21;
    f32 f_temp22;
    f32 f_temp23;
    f32 f_temp24;
    f32 f_temp25;
    f32 f_temp26;
    f32 f_temp27;
    f32 f_temp28;
    f32 f_temp29;
    f32 f_temp30;
    f32 f_temp31;
    f32 f_temp32;
    f32 f_temp33;
    f32 f_temp34;
    f32 f_temp35;
    f32 f_temp36;
    f32 f_temp37;
    f32 f_temp38;
    f32 f_temp39;
    f32 f_temp40;
    f32 f_temp41;
    f32 f_temp42;
    f32 f_temp43;
    f32 f_temp44;
    f32 f_temp45;
    f32 f_temp46;
    f32 f_temp47;
    f32 f_temp48;
    f32 f_temp49;
    f32 f_temp50;
    f32 f_temp51;
    f32 f_temp52;
    f32 f_temp53;
    f32 f_temp54;
    f32 f_temp55;
    f32 f_temp56;
    f32 f_temp57;
    f32 f_temp58;
    f32 f_temp59;
    f32 f_temp60;
    f32 f_temp61;
    f32 f_temp62;
    f32 f_temp63;
    f32 f_temp64;
    f32 f_temp65;
    f32 f_temp66;
    f32 f_temp67;
    f32 f_temp68;
    f32 f_temp69;
    f32 f_temp70;
    f32 f_temp71;
    f32 f_temp72;
    f32 f_temp73;
    f32 f_temp74;
    f32 f_temp75;
    f32 f_temp76;
    f32 f_temp77;
    f32 f_temp78;
    f32 f_temp79;
    f32 f_temp80;
    f32 f_temp81;
    f32 f_temp82;
    f32 f_temp83;
    f32 f_temp84;
    f32 f_temp85;
    f32 f_temp86;
    f32 f_temp87;
    f32 f_temp88;
    f32 f_val2;
    f32 f_val3;
    f32 f_val4;
    f32 f_val5;
    f32 f_val6;
    f32 f_val7;
    f32 f_val8;
    f32 f_val9;
    f32 f_val10;
    f32 f_val11;
    f32 f_val12;
    f32 f_val13;
    f32 f_val14;
    f32 f_val15;
    f32 f_val16;
    f32 f_val17;
    f32 f_val18;
    f32 f_val19;
    f32 f_val20;
    f32 f_val21;
    f32 f_val22;
    f32 f_val23;
    f32 f_val24;
    f32 f_val25;
    f32 f_val26;
    f32 f_val27;
    f32 f_val28;
    f32 f_val29;
    f32 f_val30;
    f32 f_val31;
    f32 f_val32;
    f32 f_val33;
    f32 f_val34;
    f32 f_val35;
    f32 f_val36;
    f32 f_val37;
    f32 f_val38;
    f32 f_val39;
    f32 f_val40;
    f32 f_val41;
    f32 f_val42;
    f32 f_val43;
    f32 f_val44;
    f32 f_val45;
    f32 f_val46;
    f32 f_val47;
    f32 f_val48;
    f32 f_val49;
    f32 f_val50;
    f32 f_val51;
    f32 f_val52;
    f32 f_val53;
    f32 f_val54;
    f32 f_val55;
    f32 f_val56;
    f32 f_val57;
    f32 f_val58;
    f32 f_val59;
    f32 f_val60;
    f32 f_val61;
    f32 f_val62;
    f32 f_val63;
    f32 f_val64;
    f32 f_val65;
    f32 f_val66;
    f32 f_val67;
    f32 f_val68;
    f32 f_val69;
    f32 f_val70;
    s16 i_temp1;
    s32 i_temp2;
    s16 i_temp3;
    s32 i_temp4;
    s32 i_temp5;
    s32 i_temp6;
    s32 i_temp7;
    s32 i_temp8;
    s32 i_temp9;
    s32 i_temp10;
    s32 i_temp11;
    s32 i_temp12;
    s32 i_temp13;
    s32 i_temp14;
    s32 i_temp15;
    s32 i_temp16;
    s32 i_temp17;
    s32 i_temp18;
    s32 i_temp19;
    s32 i_temp20;
    s32 i_temp21;
    s32 i_temp22;
    s32 i_temp23;
    s32 i_temp24;
    s32 i_temp25;
    s32 i_temp26;
    s32 i_temp27;
    s32 i_temp28;
    s32 i_temp29;
    s32 i_temp30;
    s32 i_temp31;
    s32 i_temp32;
    s32 i_temp33;
    s32 i_temp34;
    s32 i_temp35;
    s32 i_temp36;
    s32 i_temp37;
    s32 i_temp38;
    s32 i_temp39;
    s32 i_temp40;
    s32 i_temp41;
    s32 i_temp42;
    s32 i_temp43;
    s32 i_temp44;
    s32 i_temp45;
    s32 i_temp46;
    s32 i_temp47;
    s32 i_temp48;
    s32 i_val11;
    s32 i_val12;
    s32 i_val13;
    s32 i_val14;
    s32 i_val15;
    s32 i_val16;
    s32 i_val17;
    s32 i_val18;
    s32 i_val19;
    s32 i_val20;
    s32 i_val21;
    s32 i_val22;
    s32 i_val23;
    s32 i_val24;
    s32 i_val25;
    s32 i_val26;
    s32 i_val27;
    s32 i_val28;
    s32 i_val29;
    s32 i_val30;
    s32 i_val31;
    s32 i_val32;
    s32 i_val33;
    s32 i_val34;
    s32 i_val35;
    s32 i_val36;
    s32 i_val37;
    s32 i_val38;
    s32* i_val39;
    s32* i_val40;
    u16 i_temp49;
    u16 i_temp50;
    u16 i_temp51;
    u32 i_temp52;
    u32 i_temp53;
    u32 i_temp54;
    u32 i_temp55;
    u32 i_temp56;
    u32 i_temp57;
    u32 i_temp58;
    u32 i_temp59;
    u32 i_temp60;
    u32 i_temp61;
    u32 i_temp62;
    u32 i_val41;
    u8 i_temp63;
    u8 i_temp64;
    u8 i_temp65;
    u8 i_val42;
    void* i_temp66;
    void* i_temp67;
    void* i_temp68;
    void* i_temp69;
    void* i_temp70;
    void* i_temp71;
    void* i_temp72;
    void* i_temp73;
    void* i_temp74;
    void* i_temp75;
    void* i_temp76;
    void* i_temp77;
    void* f_temp89;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* i_temp78;
    void* i_temp79;
    void* i_temp80;
    void* i_temp81;
    void* i_temp82;
    void* i_temp83;
    void* i_temp84;
    void* i_temp85;
    void* i_temp86;
    void* i_temp87;
    void* i_temp88;
    void* i_temp89;
    void* i_temp90;
    void* i_temp91;
    void* i_temp92;
    void* i_temp93;
    void* i_temp94;
    void* i_temp95;
    void* i_temp96;
    void* i_temp97;
    void* i_temp98;
    void* i_temp99;
    void* i_temp100;
    void* i_temp101;
    void* i_temp102;
    void* i_temp103;
    void* i_temp104;
    void* i_temp105;
    void* i_temp106;
    void* i_temp107;
    void* i_temp108;
    void* i_temp109;
    void* i_temp110;
    void* i_temp111;
    void* i_val43;
    void* i_val44;
    void* i_val45;
    void* i_val46;
    void* i_val47;
    void* i_val48;

    i_stack14 = ((Hero *)g_hero_state)->i[0x2298/4];
    f_temp89 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    i_stack15 = (s32) M2C_FIELD(f_temp89, u8* , 0x43);
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
        if (((Hero *)g_hero_state)->b[0x22B9] != 0) {
            part_spawn_jittered_after_delay(0xF, 0x1E);
        }
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            hero_build_move_impulse(0.7f, 0.0f);
        } else {
            hero_build_move_impulse(0.5f, 0.040000003f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        i_temp53 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((i_temp53 == 1) || (i_temp53 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)v0) = 0;
                v0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)v0), (s32)&g_hero_aim_data[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_aim_data)->f[0];
                hero_steer_heading(0, 1.44f, 0.0f, 3.4906592f);
                if ((((Hero *)g_hero_state)->b[0x22BB] != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] == 0x64)) {
                    if (((Hero *)g_progress_statistics)->uh[0xD8/2] < 0xFFFF) {
                        ((Hero *)g_progress_statistics)->uh[0xD8/2]++;
                    }
                    if (((s32)g_frame_counter * 5 + 2) / 6 > ((Hero *)g_progress_statistics)->u[0xDC/4]) {
                        ((Hero *)g_progress_statistics)->u[0xDC/4] = ((s32)g_frame_counter * 5 + 2) / 6;
                    }
                    ((Hero *)g_progress_statistics)->u[0xE0/4] = ((Hero *)g_progress_statistics)->u[0xE0/4] | (1 << g_current_map_index) | 0x80000000;
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 3) {
            if (hero_try_start_grab_pal() != 0) {
                break;
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (i_temp64 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (i_temp64 == 0xE)) || (i_temp64 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.0028800003f, 0.10080001f, 0.13962635f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0069813184f) {
                    i_temp7 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    i_temp7 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != i_temp7) {
                        set_hero_animation_pal(i_temp7, 0, 4.0f);
                    }
                    f_temp1 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 12.564863f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = f_temp1;
                    if (f_temp1 < 0.55f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 0.55f;
                    }
                    if (((Hero *)g_hero_state)->f[0xC20/4] > 2.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 2.5f;
                    }
                } else if (((Hero *)g_hero_state)->f[0x1A4/4] == 0.0f) {
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != 0xD) {
                        set_hero_animation_pal(0xD, 0, 6.0f);
                    }
                }
            }
        }
            i_temp62 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (i_temp62 == 3) {
                f_val17 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (f_val17 > 1.0f) {
                    f_val17 = 1.0f;
                }
                i_temp73 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                f_val43 = f_val17 * 0.0108f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = f_val43;
                if (M2C_FIELD(i_temp73, u8* , 0x42) == M2C_FIELD(i_temp73, u8* , 0x43)) {
                    f_val38 = ((Hero *)g_hero_state)->f[0x174/4] / f_val43;
                    if ((f_val38 > 4.0f) && ((f32) M2C_FIELD(i_temp73, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, f_val38, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (i_temp62 == 4) {
                f_val43 = 0.0108f;
                if (((Hero *)g_hero_state)->b[0x1492] != 0) {
                    f_val43 = 0.00068000006f;
                }
            } else {
                f_val43 = 0.007080001f;
            }
            hero_approach_speed(0.0f, f_val43);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(f_val43);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                i_val15 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(i_val15, i_val15 + 0x30, 0.0088f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0216f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                DeflectHeroOffSteepSurface_pal(0);
                if (((Hero *)g_hero_state)->h[0x34E/2] == 0) {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
                } else {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
                    hero_cancel_velocity_into_wall_pal();
                }
            }
        break;
    case 0x7C:                                      /* switch 1 */
        hero7C = (void*)g_hero_state;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            i_temp24 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = i_temp24;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)i_temp24 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)i_temp24 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(i_temp24, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            i_temp44 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(i_temp44, u16* , 0x34) = (u16) (M2C_FIELD(i_temp44, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(6.0f);
        i_temp46 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(i_temp46, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(i_temp46, u8* , 0x23) = 0x80U;
        }
        i_temp8 = ((Hero *)hero7C)->i[0x7A4/4];
        i_temp75 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)i_temp8 + 0x10, (u8 *)i_temp75 + 0x10);
        qcopy((u8 *)i_temp8 + 0xF0, (u8 *)i_temp75 + 0xF0);
        func_002A0F48(i_temp8);
        }
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.90400004f);
        hero_update_height_offset_pal();
        break;
    case 0x32:                                      /* switch 1 */
    case 0x33:                                      /* switch 1 */
    case 0x34:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x3b) {
                (*(u16*)&g_hero_state_machine_word) = 0xFFFF;
            }
            snd_update_slot_object(5, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xF);
            actuator_play_pattern(0x16);
        } else {
            i_temp17 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (i_temp17 != -1) {
                i_temp74 = (i_temp17 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(i_temp74, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(i_temp74, u8* , 0x74) != 0) {
                        snd_stop_voice(i_temp17);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            i_temp9 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects_pal((i_temp9 >= 9) ? 8 : i_temp9, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            f_temp47 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (f_temp47 > 0.0f) {
                if (f_temp47 < 10.0f) {
                    EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                i_temp47 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (i_temp47 < 0xc) {
                    EmitHeroRandomizedMotionEffects_pal(((s32) (0x11 - i_temp47) / 3) + 1, 1, 0);
                }
            }
        }
        i_temp48 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (i_temp48 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == i_temp48) {
                part_emit_hero_dust_and_debris_pal(3, 0x10, 0);
                if (g_ripple_surface != 0) {
                    RippleDisturb(g_ripple_surface, g_ripple_surface_data, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x3a;
            }
            i_temp31 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = i_temp31;
            if (i_temp31 >= 0x22) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.013962637f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.010471976f;
        f_val30 = 0.0f;
        
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            f_val32 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (f_val32 > 1.0f) {
                f_val32 = 1.0f;
            }
            if (f_val32 < 0.2f) {
                f_val32 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                i_temp5 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                f_val32 = ((f32) (s16) i_temp5 * 0.029411765f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) i_temp5;
                if (f_val32 > 1.0f) {
                    f_val32 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (f_val32 < 0.35f)) {
                f_val32 = 0.35f;
            }
            f_val30 = f_val32 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            f_val31 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (f_val31 > 1.0f) {
                f_val31 = 1.0f;
            }
            if (f_val31 < 0.2f) {
                f_val31 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = cntA40;
                f_val31 = ((f32) (s16) cntA40 * 0.029411765f) + 0.5f;
                if (f_val31 > 1.0f) {
                    f_val31 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                f_val31 = 1.0f;
            }
            f_val30 = f_val31 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                i_temp4 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = i_temp4;
                if ((s16) i_temp4 >= 0x4c) {
                    i_temp50 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (i_temp50 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (i_temp50 + 1);
                    }
                }
                i_temp32 = (*(s32*)&g_frame_counter);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) (((s32)i_temp32 * 5 + 2) / 6)) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) (((s32)i_temp32 * 5 + 2) / 6);
                }
                ((Hero *)g_progress_statistics)->i[0x8C/4] = (s32) (((Hero *)g_progress_statistics)->i[0x8C/4] | (1 << (*(s32*)&g_current_map_index)) | 0x80000000);
            } else {
                ((Hero *)g_hero_state)->uh[0xA4C/2] = 0U;
            }
        } else {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA4C/2] = 0U;
        }
        if (((Hero *)g_pad_state)->i[0x1A4/4] & 0x40) {
            hp32 = (Hero *)g_hero_state;
            if ((g_frame_l20_counter - hp32->i[0xA54/4]) < 0x3a) {
                hp32->i[0xA50/4]++;
            }
            hp32->i[0xA54/4] = g_frame_l20_counter;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x3b) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            f_val30 = 0.0f;
        }
        f_temp55 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), f_val30, (s32) (((void*)g_hero_state) + 0xA28), 0.0216f, 0.28800002f, stick_turn, 0);
        f_temp77 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], f_temp55);
        hero_resolve_stick_direction(1.0f, 0);
        hero_steer_heading(0, 0.01008f, 0.115200005f, 0.10471977f);
        ((Hero *)g_hero_state)->f[0xA2C/4] = (f32) ((Hero *)g_hero_state)->f[0x1A4/4];
        math_fast_float_d((s32) (((void*)g_hero_state) + 0xA34));
        if (((Hero *)g_hero_state)->i[0x2298/4] == 1) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.120000005f;
        } else if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.14000002f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.056000005f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.060000002f;
        }
        f_val66 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (f_val66 < 1.0f) {
                f_val66 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            f_val9 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                f_val9 = 0.4f;
            }
            if (f_val66 < f_val9) {
                f_val66 = f_val9;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * f_val66);
        }
        if (math_fast_float_d((s32)(g_hero_state + 0xA30)) != 0) {
            heroA30 = (void*)g_hero_state;
            moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.030000001f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.040000003f;
            part_spawn_bubble_pal((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            if ((f32) math_random_int_below(0x64) < 40.0f) {
                i_val16 = 3;
                i_val20 = 0x9;
            } else {
                i_val16 = 0x21;
                i_val20 = 0x4b;
            }
            ((Hero *)heroA30)->i[0xA30/4] = math_random_int_range(i_val16, i_val20);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                i_temp98 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (i_temp98 != 0) {
                    if (M2C_FIELD(i_temp98, s16* , 0xAA) == 0x261) {
                        for (i_val24 = 0; i_val24 < 4; i_val24++) {
                            moby_transform_joint_to_world((s32) i_temp98, i_val24 % 2, (s32)((TI128*)v0));
                            (*(TI128*)v20) = 0;
                            v20[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
                            v0[0] += math_random_float_range(0.0f, 0.03f);
                            v0[1] += math_random_float_range(0.0f, 0.03f);
                            v0[2] += math_random_float_range(0.0f, 0.03f);
                            qcopy(v10, &((Hero *)g_hero_state)->q[0x110/16]);
                            vec_add_offset((s32) ((TI128*)v10), (s32) ((TI128*)v10), -0.015000001f, ((Hero *)g_hero_state)->f[0x98/4], ((Hero *)g_hero_state)->f[0x94/4]);
                            ((Hero *)g_hero_state)->h[0xA38/2] = FloatToInt((0.14000002f - ((Hero *)g_hero_state)->f[0x1B4/4]) * 28.571424f);
                            part_spawn_bubble_pal((s32)((TI128*)v0), (s32) ((TI128*)v10), math_random_float_range(6300.0f, 9450.0f), -1.0f);
                        }
                    }
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                hero_approach_speed(0.0052000005f, 0.0032000002f);
            } else {
                goto block_198;
            }
        } else {
block_198:
            hero_approach_speed(0.0028000001f, 0.0016000001f);
        }
        f_temp74 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        i_temp54 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (i_temp54 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], f_temp74);
        } else if (i_temp54 == 0x32) {
            f_val33 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l20_blend_table, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) && (f_val33 < 0.09f)) {
                f_val33 = 0.09f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), f_val33, ((Hero *)g_hero_state)->f[0x98/4], f_temp74);
        } else if (i_temp54 == 0x33) {
            i_stack1 = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &i_stack1, 0.0f, 0.0032000002f);
            } else {
                ApproachValue((s32) &i_stack1, 0.0f, 0.0016000001f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), i_stack1);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        DeflectHeroOffSteepSurface_pal(0);
        f_temp75 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(f_temp74) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), f_temp75, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.024434613f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        f_temp81 = f_temp77 * 47.0f;
        ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = f_temp81;
        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = (f32) (f_temp75 * 1.5f);
        ((Hero *)g_hero_l20_state_alias)->f[0x110/4] = (f32) (f_temp75 * 1.4f);
        if (f_temp81 > 0.8726647f) {
            ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = 0.8726647f;
        } else if (f_temp81 < -0.8726647f) {
            ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = -0.8726647f;
        }
        f_temp48 = f_temp77 * 40.0f;
        f_temp22 = f_temp75 * 1.1f;
        ((Hero *)g_hero_l20_state_alias)->f[0x364/4] = 0.03f;
        ((Hero *)g_hero_l20_state_alias)->f[0x368/4] = 0.22f;
        ((Hero *)g_hero_l20_state_alias)->f[0x324/4] = f_temp48;
        ((Hero *)g_hero_l20_state_alias)->f[0x328/4] = f_temp22;
        ((Hero *)g_hero_l20_state_alias)->f[0x414/4] = 0.03f;
        ((Hero *)g_hero_l20_state_alias)->f[0x418/4] = 0.22f;
        ((Hero *)g_hero_l20_state_alias)->f[0x3D4/4] = f_temp48;
        ((Hero *)g_hero_l20_state_alias)->f[0x3D8/4] = f_temp22;
        break;
    case 0x73:                                      /* switch 1 */
        i_temp10 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        i_temp85 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects_pal((i_temp10 >= 9) ? 8 : i_temp10, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) i_temp85, (s32) i_temp85, vec_length_xy((s32) i_temp85) * 0.90400004f);
        DeflectHeroOffSteepSurface_pal(0);
        break;
    case 0x72:                                      /* switch 1 */
        part_spawn_jittered_after_delay(0xF, 0x1E);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.90400004f);
        DeflectHeroOffSteepSurface_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x67:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
        i_stack2 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &i_stack2, 0.0f, 0.0016000001f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), i_stack2);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            i_temp93 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(i_temp93, s32* , 0x2290), 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), M2C_FIELD(i_temp93, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.030000001f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.040000003f;
            part_spawn_bubble_pal((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            i_temp33 = M2C_FIELD(i_temp93, s32* , 0x1B8);
            if (i_temp33 < 0x21) {
                lim67 = 5;
                i_val29 = math_random_int_range(2, 4) + ((s32) M2C_FIELD(i_temp93, s32* , 0x1B8) / lim67);
                goto block_224;
            }
            if (i_temp33 >= 0x3b) {
                i_val29 = math_random_int_range(0x8, 0x11);
block_224:
                M2C_FIELD(i_temp93, s32* , 0xA30) = i_val29;
            }
        }
        if (((Hero *)g_hero_state)->f[0xA3C/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xA3C/4] = 0.0f;
        }
        ApproachValue((s32) (((void*)g_hero_state) + 0xA3C), -0.030000001f, 0.0006f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) ((Hero *)g_hero_state)->f[0xA3C/4];
        break;
    case 0x35:                                      /* switch 1 */
    case 0x36:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x36) {
            part_spawn_jittered_after_delay(0xF, 0x1E);
        }
        if (((Hero *)g_hero_state)->f[0x174/4] > 0.030000001f) {
            part_emit_hero_trail_spark_pal(4, 0xC);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->f[0x174/4] > 0.020000001f)) {
            part_emit_hero_side_particles_pal(0, 1);
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            ((Hero *)g_hero_state)->h[0xA4A/2] -= 1;
            i_temp11 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects_pal((i_temp11 >= 7) ? 6 : i_temp11, 0, 0);
        }
        ((Hero *)g_hero_state)->f[0xC20/4] = 0.6f;
        hero_resolve_stick_direction(0.060000002f, 0);
        if ((((Hero *)g_pad_state)->i[0x1D4/4] == 0) && (((Hero *)g_hero_state)->f[0x1B0/4] < 0.030000001f)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.030000001f;
        }
        hero_steer_heading(0, 0.01008f, 0.115200005f, 0.10471977f);
        math_fast_float_d((s32)(g_hero_state + 0x798));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x35) {
            if ((((Hero *)g_pad_state)->i[0x1D4/4] != 0) && (((Hero *)g_hero_state)->i[0x798/4] != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.060000002f;
            }
            if (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 0.78539824f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            }
            hero_approach_speed(0.0016000001f, 0.002f);
            f_temp66 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l20_blend_table, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * f_temp66);
            f_temp24 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * f_temp66;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = f_temp24;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            f_temp49 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((f_temp49 > 0.0f) && (f_temp49 < 10.0f)) {
                EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.00168f);
        DeflectHeroOffSteepSurface_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x85:                                      /* switch 1 */
        i_temp76 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)i_temp76 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)i_temp76 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)v0), (s32)(g_hero_state + 0x2C0), -1.0f);
        f_val34 = 0.0f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            f_val34 = -((Hero *)g_hero_state)->f[0x1FB4/4] * 0.75f;
        }
        math_spring_float_to_goal((s32)(g_hero_state + 0x7C0), (s32)(g_hero_state + 0x7C4), f_val34, 0.01008f, 0.43200004f, 0.036000002f);
        FastVecScale((s32) ((TI128*)v10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v10));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        hero_apply_reference_tilt_rotation((s32)((TI128*)v0), (s32) ((TI128*)v30), 0, 0.036000002f, 0.57600003f, 0.0f);
        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.26000002f;
        vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)g_hero_state, 0.26000002f);
        cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
        vec_clear_128((s32)((TI128*)v0));
        v0[1] = -((Hero *)g_hero_state)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(g_hero_state + 0x190), (s32)((TI128*)v0), (s32)&g_hero_aim_data[0x218]);
        hero_steer_heading(0, 0.028800001f, 0.43200004f, 0.04188791f);
        break;
    case 0x2F:                                      /* switch 1 */
        anim2F = -1;
        blend2F = 0;
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            hero_build_move_impulse(0.7f, 0.0f);
        } else {
            hero_build_move_impulse(0.5f, 0.040000003f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        hero_approach_speed(0.007080001f, 0.007080001f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.007080001f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)(g_hero_state + 0xF0)) + 0x20), 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0216f);
        }
        if ((anim2F != -1) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation_pal(anim2F, 0, (f32) blend2F);
        } else {
            i_temp106 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(i_temp106, u8* , 0x60) & 2) && (M2C_FIELD(i_temp106, u8* , 0x42) == 0x36)) {
                set_hero_animation_pal(hero_get_weapon_or_form_id(0), 0, 4.0f);
            }
        }
        break;
    case 0x8A:                                      /* switch 1 */
    case 0x8B:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        hero_approach_speed(0.007080001f, 0.007080001f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.007080001f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x120), 0.0088f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0216f);
        }
        i_val48 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (i_val48 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(i_val48, f32* , 0x10) - M2C_FIELD(f_temp89, f32* , 0x10), M2C_FIELD(i_val48, f32* , 0x14) - M2C_FIELD(f_temp89, f32* , 0x14));
            hero_steer_heading(0, 0.028800001f, 0.21600002f, 0.12566373f);
        }
        break;
    case 0x23:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        hero_approach_speed(0.007080001f, 0.007080001f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.007080001f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x120), 0.0088f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0216f);
        }
        i_val1 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (i_val1 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(i_val1, f32* , 0x10) - M2C_FIELD(f_temp89, f32* , 0x10), M2C_FIELD(i_val1, f32* , 0x14) - M2C_FIELD(f_temp89, f32* , 0x14));
            hero_steer_heading(0, 0.028800001f, 0.21600002f, 0.12566373f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(v0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        f_temp25 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)v0));
        ((Hero *)g_hero_state)->f[0xAB0/4] = f_temp25;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 5e1f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (f_temp25 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        i_temp34 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (i_temp34 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.54f, 0.032f);
            i_temp102 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            f_val48 = mat_fast_helper_a(M2C_FIELD(i_temp102, f32* , 0x10) - M2C_FIELD(f_temp89, f32* , 0x10), M2C_FIELD(i_temp102, f32* , 0x14) - M2C_FIELD(f_temp89, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], f_val48) > 1.5707964f) {
                    f_val48 = FastAddRotations(f_val48, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = f_val48;
            hero_steer_heading(0, 0.0432f, 0.21600002f, 0.14660768f);
        } else if (i_temp34 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.016800001f);
        }
        if ((math_solve_quadratic((s32) &i_stack3, (s32) &i_stack4, -0.008400001f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (i_stack3 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = i_stack3;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 17.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.0767945f);
        } else {
            turn24 = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)v0)), v0[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn24, 0.12915438f);
        }
        v20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        f_temp26 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        v20[2] = 0;
        v20[1] = f_temp26;
        FastVecAdd((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)v10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)v20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)v10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        f_temp27 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (f_temp27 < 25.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((25.0f - f_temp27) * 0.011600001f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.20000002f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.006f);
        qcopy(v0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)v0));
        FastVecAdd((s32) ((TI128*)v10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32)((TI128*)v0));
        vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)v20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(f_temp89, u8* , 0x43) == 0x34)) {
            set_hero_animation_pal(0x35, 0xA, 1e1f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        i_temp107 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        f_temp80 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (i_temp107 != 0) {
            i_temp103 = M2C_FIELD(i_temp107, void** , 0x68);
            if ((i_temp103 != 0) && (M2C_FIELD(i_temp103, s32* , 0x34) != 0)) {
                f_val49 = M2C_FIELD(i_temp107, f32* , 0xF8);
                if (FastDiffRots(f_val49, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    f_val49 = FastAddRotations(f_val49, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), f_val49, (s32) (((void*)g_hero_state) + 0xAF8), 0.028800001f, 0.43200004f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.028800001f, 0.43200004f, 0.094247796f);
        FastVecSub((s32)((TI128*)v0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        if (v0[2] < 0.23f) {
            v0[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)v60));
        v60[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)v20), (s32) ((TI128*)v60));
        matrix_from_basis_rows((s32) ((TI128*)m70), (s32) ((TI128*)v20));
        transform_vector((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)m70));
        v10[0] = -mat_fast_helper_a(square_root((v0[0] * v0[0]) + (v0[2] * v0[2])), v0[1]);
        f_temp28 = mat_fast_helper_a(v0[2], v0[0]);
        v10[1] = f_temp28;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), f_temp28, (s32) (((void*)g_hero_state) + 0xA4), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), v10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        i_val27 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((i_val27 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x22) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                f_val50 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0042000003f;
                if (f_val50 > 0.10000001f) {
                    f_val50 = 0.10000001f;
                }
                vB0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * f_val50;
                f_temp29 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * f_val50;
                i_temp66 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vB0[2]) = 0;
                vB0[1] = f_temp29;
                FastVecAdd((s32) i_temp66, (s32) i_temp66, (s32) ((TI128*)vB0));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                i_temp94 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) i_temp94, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    i_temp86 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) i_temp86, (s32) (((void*)g_hero_state) + 0x110), 0.016f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) i_temp86) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vB0), (s32) i_temp94, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) i_temp86, (s32) i_temp86, 0.0228f);
                    }
                }
                f_temp67 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.0003f;
                FastVecScale((s32) ((TI128*)vB0), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vB0), (s32) ((TI128*)vB0), f_temp67);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vB0));
            }
        }
        i_temp104 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (i_temp104 != 0) {
            i_temp78 = M2C_FIELD(i_temp104, void** , 0x68);
            i_temp87 = ((void*)g_hero_state) + 0xF0;
            if (i_temp78 != 0) {
                f_temp30 = FastVecLength((s32) i_temp87);
                f_temp31 = M2C_FIELD(i_temp78, f32* , 0xC);
                i_stack5 = f_temp30;
                if (f_temp31 < f_temp30) {
                    ApproachValue((s32) &i_stack5, f_temp31, 0.006f);
                    vec_scale_to_length((s32) i_temp87, (s32) i_temp87, i_stack5);
                }
            }
        }
        f_temp2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        i_temp100 = ((void*)g_hero_state) + 0x80;
        i_temp99 = ((void*)g_hero_state) + 0xF0;
        vD0[0] = math_fast_sin_or_cos_a(f_temp2) * 0.15f;
        f_temp3 = math_fast_sin_or_cos_b(f_temp2) * 0.15f;
        (*(s32*)&vD0[2]) = 0;
        vD0[1] = f_temp3;
        FastVecAdd((s32) &vD0[0], (s32) &vD0[0], (s32) i_temp100);
        FastVecAdd((s32) ((TI128*)vB0), (s32) &vD0[0], (s32) i_temp99);
        FastVecSub((s32) ((TI128*)vC0), (s32) ((TI128*)vB0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vB0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vC0));
        FastVecSub((s32) i_temp99, (s32) ((TI128*)vB0), (s32) &vD0[0]);
        f_temp68 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        f_temp69 = ((Hero *)g_hero_state)->f[0xAE4/4] - f_temp68;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vC0))) {
            vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), f_temp69);
            FastVecAdd((s32) i_temp100, (s32) i_temp100, (s32) ((TI128*)vC0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (i_val27 != 0)) {
            min2B = 0.28000003f;
            f_temp4 = vec_length_xy((s32) i_temp99);
            i_stack6 = f_temp4;
            if (f_temp4 < min2B) {
                math_spring_float_to_goal((s32) &i_stack6, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.06768f, 0.43200004f, 0.0f);
                vB0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                f_temp5 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vB0[2] = 0.0f;
                vB0[1] = f_temp5 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) i_temp99, (s32) i_temp99, (s32) ((TI128*)vB0));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((f_temp80 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            f_temp70 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            i_temp3 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (i_temp3 != 0) {
                i_val30 = i_temp3 == 1;
            } else {
                (*(TI128*)vB0) = ((Hero *)g_hero_state)->q[0x110/16];
                i_val30 = hero_get_speed_along_forward((s32) ((TI128*)vB0)) > 0.0f;
            }
            if (i_val30 != 0) {
                if (M2C_FIELD(f_temp89, u8* , 0x43) != 0x35) {
                    set_hero_animation_pal(0x35, 6, 14.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    i_temp105 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(i_temp105, u8* , 0x42) == M2C_FIELD(i_temp105, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, f_temp70, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(f_temp89, u8* , 0x43) != 0x35) {
                set_hero_animation_pal(0x35, 0x15, 7.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                i_temp101 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(i_temp101, u8* , 0x42) == M2C_FIELD(i_temp101, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, f_temp70, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l20_action_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            i_temp12 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (i_temp12 != 0) {
                f_temp50 = vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), i_temp12 + 0x10);
                i_val36 = 0;
                if ((((Hero *)g_hero_state)->b[0x1496] != 0) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->b[0x1495] != 0)) {
                    i_val36 = 1;
                }
                if (((f_temp50 > 2.0f) && (f_temp50 < 5.0f)) || (i_val36 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
                }
                hero_approach_speed(0.0016000001f, 0.0016000001f);
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            } else {
                hero_approach_speed(0.00080000004f, 0.00080000004f);
                i_temp67 = ((void*)g_hero_state) + 0xF0;
                cam_set_view_space_vector_length((s32) i_temp67, (s32) i_temp67, ((Hero *)g_hero_state)->f[0x1B4/4]);
            }
        } else {
            i_val25 = 0;
            if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
                i_val25 = 1;
            }
            i_temp13 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (i_temp13 != 0) {
                FastVecSub((s32)((TI128*)v0), i_temp13 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                f_temp6 = cam_get_view_space_vector_length((s32)((TI128*)v0));
                if (((f_temp6 > 2.0f) && (f_temp6 < 5.0f)) || (i_val25 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
                }
                hero_approach_speed(0.010000001f, 0.010000001f);
                vec_scale_to_length((s32) ((TI128*)v10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
                cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)v10));
            } else {
                if ((i_val25 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3a)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
                }
                hero_approach_speed(0.006f, 0.006f);
                cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4]);
            }
        }
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
            hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
        } else if (((Hero *)g_hero_state)->f[0xC38/4] < 25.0f) {
            hero_l00_select_aim_target(8.0f, 1.0471977f, 1.0471977f);
        }
        f_temp51 = ((Hero *)g_hero_state)->f[0x31C/4];
        f_val56 = 0.15400001f;
        if (f_temp51 > 2.25f) {
            f_val56 = 0.07700001f;
        } else if (f_temp51 > 1.8f) {
            f_val56 = 0.10780001f;
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
            actuator_play_pattern(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x2a;
            if (g_hero_override_flag != 0) {
                ((Hero *)g_hero_l20_extra_state)->f[0x180/4] = 0.1f;
                ((Hero *)g_hero_l20_extra_state)->i[0x188/4] = 0x19;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x1d;
                ((Hero *)g_hero_l20_extra_state)->i[0x16C/4] = 0;
            }
        }
        i_temp35 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xc;
        if (i_temp35 < 7) {
            i_temp79 = ((void*)g_hero_state) + 0xF0;
            i_stack7 = cam_get_view_space_height((s32) i_temp79);
            ApproachValue((s32) &i_stack7, f_val56, 0.060000002f);
            cam_set_view_space_height((s32) i_temp79, (s32) i_temp79, i_stack7);
        } else if (i_temp35 > lim3) {
            i_temp88 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) i_temp88, (s32) i_temp88, 0.052f);
            if (cam_get_view_space_height((s32) i_temp88) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            f_val51 = -0.74000007f;
            if (g_hero_l20_lock_flag_a != 0) {
                f_val51 = -1.4000001f;
            }
            if (cam_get_view_space_height((s32) i_temp88) < f_val51) {
                cam_set_view_space_height((s32) i_temp88, (s32) i_temp88, f_val51);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l20_action_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        i_val18 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x12);
        if (i_val18 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                i_val26 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    i_temp80 = ((void*)g_hero_state) + 0xBC0;
                    f_val52 = hero_get_direction_angle_delta((s32) i_temp80, 0);
                    f_val10 = hero_get_direction_angle_delta((s32) i_temp80, 1);
                } else {
                    f_val52 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    f_val10 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (f_val10 < 4.3633237f) {
                    i_val26 = 1;
                }
                if (f_val52 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (f_val10 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (i_val26 != 0) {
                    hero_steer_heading(1, 0.08208001f, 0.28800002f, 0.33859393f);
                } else {
                    hero_steer_heading(0, 0.08208001f, 0.28800002f, 0.33859393f);
                }
            } else {
                    i_val19 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xa)) {
                        i_val19 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        i_val19 = 0;
                    }
                    if (i_val19 != 0) {
                        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x15) {
                            hero_l00_select_aim_target(14.0f, 0.52359885f, 0.78539824f);
                        } else {
                            UpdateHeroAimTarget(64.0f, 0.17453295f, 0.3490659f);
                        }
                    }
                }
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) == 0x1A) && (math_is_below_plane_within_depth(33.0f) != 0)) {
            if ((((Hero *)g_hero_state)->b[0x1492] != 0) && (((Hero *)g_hero_state)->f[0x170/4] < 0.040000003f)) {
                {
                    ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.026f));
                    ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.026f));
                    qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x15) {
                hero_setup_attached_object_transform_pal();
            }
        }
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            if (math_is_below_plane_within_depth(84.0f) != 0) {
                f_val57 = 0.050000004f;
                f_temp71 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&g_pad_pressed_flags) & 8) {
                    f_val57 = 0.060000002f;
                }
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(f_temp71) * f_val57));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(f_temp71) * f_val57));
                qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
            }
            hero_steer_reference_point_pal();
        } else {
            hero_approach_speed(0.014800001f, 0.0112000005f);
            hero_compute_push_direction(99999.0f);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
            } else {
                hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
                break;
            }
        }
        break;
    case 0x13:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l20_action_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            hero_steer_reference_point_pal();
            break;
        }
        i_temp14 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        i_temp95 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_l20_action_table;
        if ((i_temp14 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 3)) {
            i_temp89 = ((void*)g_hero_state) + 0x80;
            f_val20 = vec_distance_xy(i_temp14 + 0x10, (s32) i_temp89);
            if ((*(s32*)&g_hero_l20_lock_flag_a) != 0) {
                f_val20 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) i_temp89);
            }
            f_val20 = f_val20 - 0.5f;
            if (f_val20 < 0.0f) {
                f_val20 = 0.0f;
            }
            i_temp36 = M2C_FIELD(i_temp95, s32* , 4);
            if (i_temp36 == 0) {
                f_val11 = 0.75f;
                f_val58 = 0.8f;
                f_val63 = 4.0f;
            } else if (i_temp36 == 1) {
                f_val11 = 0.6f;
                f_val58 = 1.7f;
                f_val63 = 4.0f;
            } else {
                f_val11 = 1.3f;
                f_val58 = 1.7f;
                f_val63 = 1.9f;
            }
            f_temp72 = f_val20 - f_val11;
            if (math_fabs(f_temp72) < (f_val58 + 3.0f)) {
                f_val22 = f_temp72 * 1.1111112f;
                if (f_val63 < f_val22) {
                    f_val22 = f_val63;
                }
                if (f_val22 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = f_val22;
                }
            }
        }
        i_temp37 = M2C_FIELD(i_temp95, s32* , 4);
        switch (i_temp37) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.08800001f;
            }
            break;
        case 1:
            f_temp52 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (f_temp52 < 9.0f)) {
                if (f_temp52 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.060000002f;
                } else if (f_temp52 > 7.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.09f;
                } else {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.11400001f;
                }
            }
            break;
        case 2:
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < 12.0f)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07400001f;
            }
            break;
        }
        ApproachValue((s32)(g_hero_state + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
        if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
            f_val12 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            f_val12 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        f_temp53 = math_fabs(f_val12);
        if ((M2C_FIELD(i_temp95, s32* , 4) == 1) && (f_val12 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (f_temp53 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
    } else {
        i_val37 = 1;
        if ((M2C_FIELD(i_temp95, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            i_val37 = 0;
        }
        if (i_val37 != 0) {
            hero_l00_select_aim_target(5.0f, 0.78539824f, 0.78539824f);
        }
    }
        hero_approach_speed(0.014800001f, 0.0112000005f);
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
            hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0x130), 0.010000001f);
        } else {
            i_temp68 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) i_temp68, (s32) i_temp68, 0.0216f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.0096f);
        if ((*(s32*)&g_hero_l20_lock_flag_a) != 0) {
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xBD0), ((Hero *)g_hero_state)->f[0x1B4/4]);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 0.0f) {
                hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0x130), 0.010000001f);
            } else {
                cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            }
            FastVecScale((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0xBD0), -1.0f);
        } else {
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xBF0/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xBF0/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 0.0f) {
                ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0x128/4] - 0.010000001f);
            } else {
                ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = FastAddRotations(((Hero *)g_hero_state)->f[0xBF0/4], 3.1415927f);
        }
        hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
        break;
    case 0x1F:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
        } else if (((Hero *)g_hero_state)->i[0x1B8/4] < 3) {
            hero_l00_select_aim_target(11.0f, 0.8726647f, -1.0f);
        }
        lim = 0x8;
        lim2 = 0xF;
        i_temp38 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (i_temp38 > lim) {
            if (i_temp38 < 0xf) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.36f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 7) && (((Hero *)g_hero_state)->f[0x184/4] < 0.40000004f)) {
            i_temp81 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) i_temp81);
            level_append_record_to_table((s32) i_temp81, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) i_temp81, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) i_temp81, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)g_hero_state)->i[0x1B8/4] > lim2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), sel1F);
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            i_temp39 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((i_temp39 > lim) && (i_temp39 < 0xe) && (((Hero *)g_hero_state)->f[0x178/4] < 0.17000002f)) {
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.024000002f));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.024000002f));
                qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
            }
            hero_steer_reference_point_pal();
        } else {
            if (((Hero *)g_hero_state)->i[0x1B8/4] > lim) {
                hero_approach_speed(0.076000005f, 0.036000002f);
            }
            if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x1F) {
            i_temp40 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((i_temp40 > lim) && (i_temp40 < 0x12)) {
                i_temp96 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (i_temp96 != 0) {
                    i_temp90 = ((void*)g_hero_state) + 0x80;
                    v30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)v0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)v30));
                    (*(u8*)((u8*)v10+9)) = 3;
                    v0[3] = 5627.925f;
                    (*(u8*)((u8*)v10+8)) = 0;
                    f_temp78 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)v10+10)) = M2C_FIELD(i_temp96, u16* , 0xAA);
                    v40[0] = math_fast_sin_or_cos_a(f_temp78) * 0.8f;
                    f_temp7 = math_fast_sin_or_cos_b(f_temp78) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = f_temp7;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) i_temp90);
                    part_emit_effects_at_nearby_mobys_pal((s32) i_temp96, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) i_temp96, (s32)((TI128*)v0)));
                    f_temp78 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(f_temp78) * 0.8f;
                    f_temp9 = math_fast_sin_or_cos_b(f_temp78) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = f_temp9;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) i_temp90);
                    part_emit_effects_at_nearby_mobys_pal((s32) i_temp96, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)v0)));
                    f_temp78 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(f_temp78) * 0.8f;
                    f_temp11 = math_fast_sin_or_cos_b(f_temp78) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = f_temp11;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) i_temp90);
                    part_emit_effects_at_nearby_mobys_pal((s32) i_temp96, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) i_temp96, (s32)((TI128*)v0)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        DeflectHeroOffSteepSurface_pal(1);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x120, 0.0088f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        break;
    case 0x22:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
            qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
            hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.33859393f);
        } else {
            hero_l00_select_aim_target(11.0f, 0.8726647f, -1.0f);
        }
        hero_approach_speed(0.012f, 0.014f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.0216f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        break;
    case 0x2:                                       /* switch 1 */
    case 0x70:                                      /* switch 1 */
        i_val13 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            i_val13 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (i_val13 != 0)) {
            if (((Hero *)g_hero_state)->f[0x174/4] > 0.020000001f) {
                part_emit_hero_side_particles_pal(0, 2);
            }
            if (((Hero *)g_hero_state)->f[0x174/4] > 0.010000001f) {
                part_emit_hero_trail_spark_pal(2, 4);
            }
            EmitHeroRandomizedMotionEffects_pal(5, 2, 0);
        }
        if (((Hero *)g_hero_state)->h[0x1454/2] == 0) {
            if (((Hero *)g_hero_state)->f[0x174/4] < 0.034f) {
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
                if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 2.0943954f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
                    ((Hero *)g_hero_state)->b[0x40F] = 1U;
                }
            }
            f_temp73 = ReadPadFloatHistory(1);
            if ((FastDiffRots(f_temp73, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            hero_update_target_speed_pal();
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
            f_temp54 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)v0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = f_temp54;
            if (f_temp54 < 0.014f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.014f;
            }
            vec_clear_128((s32) pA60);
        }
        f_val53 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim_pal();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.028800001f, 0.24480002f, 0.19896756f);
            } else {
                f_temp82 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (f_temp82 > 0.78539824f)) {
                    f_val53 = 0.0f;
                }
                hero_set_turn_rates_pal();
            }
        }
        hero_apply_mode_pose_offsets_pal();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            f_val67 = 0.119f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.03501409f);
            if (f_val67 < 0.0f) {
                f_val67 = 0.0f;
            }
            if (f_val67 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = f_val67;
            }
        }
        k005 = f_val53 * 0.0072000003f;
        f_val54 = 0.008f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            f_val39 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (f_val39 > 1.0f) {
                f_val39 = 1.0f;
            }
            if (f_val39 < 0.2f) {
                f_val39 = 0.2f;
            }
            f_val54 = 0.0068000006f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * f_val39);
        }
        f_temp83 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (f_temp83 > 0.6108653f)) {
            f_val40 = 1.0f - (f_temp83 * 0.4f);
            if (f_val40 < 0.0f) {
                f_val40 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * f_val40);
        }
        hero_approach_speed(k005, f_val54);
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
        DeflectHeroOffSteepSurface_pal(1);
        if (((Hero *)g_hero_state)->h[0x214/2] != 0) {
            hero_try_surface_push_response(5.0f, 0.2f, 0.35f);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        break;
    case 0x7B:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        hero_resolve_stick_direction(1.0f, 0);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.23000002f;
        pad_clamp_stick_to_unit_range((s32)((TI128*)v0), (s32) (((void*)g_hero_state) + 0x9F0), 0.24480002f);
        f_val59 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.024434613f) * v0[0];
        if ((*(s32*)&g_hero_l20_lock_flag_a) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x32) {
                f_val59 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.6f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, f_val59);
        }
        hero_approach_speed(0.040000003f, 0.006f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&g_hero_l20_lock_flag_a) != 0) {
            qcopy(v10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)v10), (s32) ((TI128*)v10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0xA00), 0.057600003f, 0.43200004f, 0.15f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.057600003f, 0.43200004f, 0.15f);
        }
        FastVecScale((s32) ((TI128*)v10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32)(g_hero_state + 0xE0));
        i_temp25 = coll_process_hit(0.57f, (s32) ((TI128*)v10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (i_temp25 != 0) {
            FastVecScale((s32) ((TI128*)v20), (s32)(g_hero_state + 0x110), 7.0f);
            for (i_val22 = 0; i_val22 < i_temp25; i_val22++) {
                if (moby_is_in_special_class_range(((s32 *)g_special_moby_table)[i_val22]) != 0) {
                    part_queue_impact_effect(((s32 *)g_special_moby_table)[i_val22], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.024480002f, 0.43200004f);
        cam_set_limits_third(0.036000002f, 0.43200004f);
        cam_set_limits_fourth(0.0432f, 0.38880002f);
        f_val68 = f_val59 * 27.0f;
        if (f_val68 > 1.7f) {
            f_val68 = 1.7f;
        } else if (f_val68 < -1.7f) {
            f_val68 = -1.7f;
        }
        f_temp12 = f_val68 * 0.5f;
        ((Hero *)g_hero_l20_state_alias)->f[0x60/4] = (f32) -f_val68;
        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = f_temp12;
        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = f_temp12;
        break;
    case 0x2E:                                      /* switch 1 */
        hero_steer_reference_point_pal();
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        i_temp65 = M2C_FIELD(f_temp89, u8* , 0x43);
        if (i_temp65 == 0x37) {
            f_val13 = 1.4f;
            f_val55 = ((Hero *)g_hero_state)->f[0x1A8/4];
            if ((f_val55 > 1.4f) || (f_val13 = -1.4f, (f_val55 < -1.4f))) {
                f_val55 = f_val13;
            }
            ((Hero *)g_hero_l20_state_alias)->f[0x60/4] = (f32) (f_val55 * -0.14f);
            ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = (f32) (f_val55 * 0.3f);
            ((Hero *)g_hero_l20_state_alias)->f[0x1C0/4] = (f32) (f_val55 * -0.22f);
            ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = (f32) (f_val55 * 0.4f);
            ((Hero *)g_hero_l20_state_alias)->f[0x274/4] = (f32) (math_fabs(f_val55) * -0.09f);
            ((Hero *)g_hero_l20_state_alias)->f[0x270/4] = (f32) (math_fabs(f_val55) * 0.08f);
        } else if (i_temp65 == 0x66) {
            f_temp79 = FastAddRotations(fast_subtract_rotations(mat_fast_helper_a(((Hero *)g_hero_state)->f[0x110/4], ((Hero *)g_hero_state)->f[0x114/4]), ((Hero *)g_hero_state)->f[0x98/4]), 3.1415927f);
            f_val60 = ((Hero *)g_hero_state)->f[0x174/4] * 5.8177648f;
            if (f_val60 > 0.43633235f) {
                f_val60 = 0.43633235f;
            }
            f_temp56 = math_fast_sin_or_cos_a(f_temp79) * f_val60;
            f_temp13 = -math_fast_sin_or_cos_b(f_temp79);
            ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = f_temp56;
            ((Hero *)g_hero_l20_state_alias)->f[0x110/4] = (f32) (f_temp13 * f_val60);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            f_val23 = 0.010000001f;
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x110), f_val23);
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.060000002f);
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        i_temp41 = (*(s32*)&g_current_map_index);
        if (i_temp41 == 0 || (i_temp41 == 1 && ref_US2_L13_002C58E8_01 == 0)) {
            snd_update_slot_object(2, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x13);
        }
        i_val32 = g_current_map_index;
        if ((u32) i_val32 < 2U) {
            EmitHeroRandomizedMotionEffects_pal(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects_pal(4, 2, 0);
            v0[0] = ((Hero *)g_hero_state)->f[0x80/4] + math_random_float_range(-0.25f, 0.25f);
            v0[1] = ((Hero *)g_hero_state)->f[0x84/4] + math_random_float_range(-0.25f, 0.25f);
            v0[2] = ((Hero *)g_hero_state)->f[0x88/4] + math_random_float_range(-0.1f, 0.4f);
            FastVecScale((s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0x110), 0.9f);
            v10[0] += math_random_float_range(-0.014f, 0.014f);
            v10[1] += math_random_float_range(-0.014f, 0.014f);
            v10[2] = M2C_BITWISE(f32, v10[2]) + math_random_float_range(0.020000001f, 0.040000003f);
            part_spawn_two_point_effect((s32)((TI128*)v0), (s32) ((TI128*)v10), math_random_float_range(37800.0f, 75600.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xB40/4];
        f_temp57 = ((Hero *)g_hero_state)->f[0x98/4];
        hero_steer_heading(0, 0.04752f, 0.43200004f, 0.08377582f);
        f_val61 = FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], f_temp57);
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        hero_shrink_vector_by_amount(0.0028000001f);
        f_temp14 = ((Hero *)g_hero_state)->f[0x118/4] - 0.020000001f;
        ((Hero *)g_hero_state)->f[0xF8/4] = f_temp14;
        if (f_temp14 > -0.016f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.016f;
        }
        if (f_val61 > 0.027925273f) {
            f_val61 = 0.027925273f;
        }
        f_temp58 = f_val61 * 9.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), f_temp58 * 0.5f, (s32) (((void*)g_hero_state) + 0xB54), 0.007f, 0.17f, 0.024434613f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), -((Hero *)g_hero_state)->f[0xB44/4], (s32) (((void*)g_hero_state) + 0xB58), 0.050400004f, 0.43200004f, 0.03839725f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = (f32) (f_temp58 * 2.1f);
        ((Hero *)g_hero_l20_state_alias)->f[0x110/4] = (f32) (f_temp58 * 3.5f);
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        i_temp55 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (((u32) (i_temp55 - 0x28) >= 2U) && (i_temp55 != 0x3E)) {
            snd_update_slot_object(0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        } else {
            i_temp18 = ((Hero *)g_hero_state)->i[0x242C/4];
            if (i_temp18 != -1) {
                i_temp69 = (i_temp18 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(i_temp69, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(i_temp69, u8* , 0x74) != 0) {
                        snd_stop_voice(i_temp18);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x242C/4] = -1;
        }
        i_temp56 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((i_temp56 == 0x27) || (i_temp56 == 0x2A)) {
            qcopy(v0, &((Hero *)g_hero_state)->q[0x80/16]);
            f_temp59 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.0f, 0.52359885f));
            f_temp76 = math_random_float_range(0.080000006f, 0.14000002f);
            v10[0] = math_fast_sin_or_cos_a(f_temp59) * f_temp76;
            f_temp15 = math_fast_sin_or_cos_b(f_temp59) * f_temp76;
            v10[2] = 0.0f;
            v10[1] = f_temp15;
            v10[2] = math_random_float_range(0.060000002f, 0.10000001f);
            v10[3] = -0.012f;
            part_spawn_white_flash_pal((s32)((TI128*)v0), (s32) ((TI128*)v10), 0, -1.0f);
        }
        i_temp77 = ((Hero *)g_hero_state)->ptr[0x1248/4];
        i_stack16 = 0;
        i_temp23 = (((LevelInfo *)g_item_l20_record_table)[g_item_slot_to_record[(s32)i_temp77]].x1C != 0);
        if ((s32)i_temp77 == 0xD) {
            i_temp23 = 0;
        }
        if (i_temp23 != 0) {
            i_stack16 = ((Hero *)g_hero_state)->b[0x22BA] != 0;
        }
        i_temp91 = ((void*)g_hero_state) + 0x80;
        find_nearest_path_point(((Hero *)g_hero_state)->i[0x630/4], (s32) i_temp91, (s32) (((void*)g_hero_state) + 0x5D0), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)g_hero_state)->i[0x664/4], (s32) i_temp91, (s32) (((void*)g_hero_state) + 0x610), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        i_val21 = 0;
        if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0699999f) {
            i_temp57 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((i_temp57 != 0x28) && (i_temp57 != 0x3E) && (((Hero *)g_hero_state)->i[0x660/4] == 0)) {
                i_val21 = ((Hero *)g_hero_state)->i[0x1BC/4] >= 0x1a;
            }
        }
        if (i_val21 != 0) {
            ((Hero *)g_hero_state)->i[0x6C8/4] = (s32) (((Hero *)g_hero_state)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)g_hero_state)->i[0x6C8/4] = 0;
        }
        i_temp26 = ((Hero *)g_hero_state)->i[0x640/4];
        if (((i_temp26 != 0) && ((((Hero *)g_hero_state)->i[0x640/4] = i_temp26 + 1) != 0)) || (i_val21 != 0)) {
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x120/16]);
            i_temp108 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(i_temp108, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion_pal();
            } else {
                if (vec_length_xy((s32)(g_hero_state + 0xF0)) < 0.050000004f) {
                    ApproachValue((s32)(g_hero_state + 0xF0) + 0xC4, 0.080000006f, 0.016f);
                    M2C_FIELD(i_temp108, f32* , 0xF0) = math_fast_sin_or_cos_a(M2C_FIELD(i_temp108, f32* , 0x64C)) * M2C_FIELD(i_temp108, f32* , 0x1B4);
                    M2C_FIELD(i_temp108, f32* , 0xF4) = math_fast_sin_or_cos_b(M2C_FIELD(i_temp108, f32* , 0x64C)) * M2C_FIELD(i_temp108, f32* , 0x1B4);
                }
                M2C_FIELD(i_temp108, f32* , 0xF8) = (f32) (M2C_FIELD(i_temp108, f32* , 0xF8) - 0.0088f);
            }
        } else {
            f_temp39 = (f32) ((Hero *)g_hero_state)->i[0x648/4];
            f_val44 = ((Hero *)g_hero_state)->f[0x644/4] * f_temp39;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                f_val44 = ((Hero *)g_hero_state)->f[0x69C/4] * f_temp39;
            }
            Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32)((TI128*)v0), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], f_val44);
            if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x664/4], (s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], f_val44);
            }
            if (((Hero *)g_hero_state)->i[0x1BC/4] >= 0x4c) {
                f_temp60 = ((Hero *)g_hero_state)->f[0x170/4] * 25.333334f;
                qcopy(v20, &((Hero *)g_hero_state)->q[0x80/16]);
                i_stack8 = ((Hero *)g_hero_state)->i[0x634/4];
                i_stack9 = ((Hero *)g_hero_state)->f[0x638/4];
                i_temp21 = Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)v20), (s32) &i_stack8, (s32) &i_stack9, ((Hero *)g_hero_state)->i[0x654/4], f_temp60);
                qcopy(v30, &((Hero *)g_hero_state)->q[0x80/16]);
                i_stack8 = ((Hero *)g_hero_state)->i[0x634/4];
                i_stack9 = ((Hero *)g_hero_state)->f[0x638/4];
                if ((((i_temp21 | Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)v30), (s32) &i_stack8, (s32) &i_stack9, ((Hero *)g_hero_state)->i[0x654/4], f_temp60 + 0.1f)) == 0) || (((Hero *)g_hero_state)->i[0x654/4] != 0)) && (((Hero *)g_hero_state)->u[0x2294/4] == 0x27)) {
                    f_val45 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x64C/4], mat_fast_helper_a(v30[0] - v20[0], v30[1] - v20[1])) * 0.47f;
                    if (f_val45 > 0.78539824f) {
                        f_val45 = 0.78539824f;
                    }
                    if (f_val45 < -0.78539824f) {
                        f_val45 = -0.78539824f;
                    }
                    cam_set_limits_first(0.03f, 0.2f);
                    if (((Hero *)g_hero_state)->i[0x65C/4] != 0) {
                        (*(f32*)&g_hero_l20_signed_scalar) = -f_val45;
                    } else {
                        (*(f32*)&g_hero_l20_signed_scalar) = f_val45;
                    }
                }
            }
            i_temp58 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((i_temp58 != 0x28) && (i_temp58 != 0x3E) && (i_temp58 != 0x29)) {
                (*(f32*)&g_hero_speed_blend_value) = mat_fast_helper_a(vec_length_xy((s32) (((void*)g_hero_state) + 0x110)), ((Hero *)g_hero_state)->f[0x118/4]);
            }
            if (i_temp23 != 0) {
                k03 = 0.43200004f;
                cam_set_limits_fourth(0.024480002f, k03);
                cam_set_limits_second(0.03888f, k03);
                cam_set_limits_third(0.03888f, k03);
                i_temp15 = ((Hero *)g_hero_state)->i[0x6A8/4];
                if (i_temp15 != 0) {
                    FastVecSub((s32) ((TI128*)v20), i_temp15 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)g_hero_state) + 0x40));
                    f_temp32 = mat_fast_helper_a(v20[0], v20[1]);
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        f_temp32 = fast_subtract_rotations(f_temp32, 1.5707965f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = (f32) (f_temp32 * 0.3f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = (f32) (f_temp32 * 0.2f);
                    } else {
                        f_temp32 = fast_subtract_rotations(f_temp32, -1.5707965f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = (f32) (f_temp32 * 0.3f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = (f32) (f_temp32 * 0.5f);
                    }
                } else {
                    i_temp63 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43);
                    if (i_temp63 == 0x31) {
                        f_val62 = 0.58823526f;
                        f_val15 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        f_val46 = 0.73303837f;
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = f_val15;
                        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = FastAddRotations(f_val46, ((Hero *)g_hero_state)->f[0x6A0/4] * f_val62);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = FastAddRotations(f_val46, ((Hero *)g_hero_state)->f[0x6A0/4] * f_val62);
                    } else if (i_temp63 == 0x48) {
                        f_val62 = 0.5f;
                        f_val15 = FastAddRotations(0.13962635f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        f_val46 = -0.06981318f;
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = f_val15;
                        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = FastAddRotations(f_val46, ((Hero *)g_hero_state)->f[0x6A0/4] * f_val62);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = FastAddRotations(f_val46, ((Hero *)g_hero_state)->f[0x6A0/4] * f_val62);
                    } else if (i_temp63 == 0x47) {
                        f_val62 = 0.58823526f;
                        f_val15 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        f_val46 = 0.73303837f;
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = f_val15;
                        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = FastAddRotations(f_val46, ((Hero *)g_hero_state)->f[0x6A0/4] * f_val62);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = FastAddRotations(f_val46, ((Hero *)g_hero_state)->f[0x6A0/4] * f_val62);
                    }
                }
            }
            i_temp28 = path_advance_index(((Hero *)g_hero_state)->i[0x630/4], ((Hero *)g_hero_state)->i[0x634/4], ((Hero *)g_hero_state)->i[0x648/4], ((Hero *)g_hero_state)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)v20), (s32) &((TI128 *)((Hero *)g_hero_state)->ptr[0x630/4])[i_temp28 + 1], (s32)((TI128*)v0));
            if (FastVecLength((s32) ((TI128*)v20)) < 0.001f) {
                if (((Hero *)g_hero_state)->i[0x634/4] == i_temp28) {
                    ((Hero *)g_hero_state)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)g_hero_state)->f[0x64C/4] = mat_fast_helper_a(v20[0], v20[1]);
                ((Hero *)g_hero_state)->f[0x650/4] = mat_fast_helper_a(vec_length_xy((s32) ((TI128*)v20)), M2C_BITWISE(f32, v20[2]));
block_807:
                ((Hero *)g_hero_state)->f[0x1A0/4] = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], ((Hero *)g_hero_state)->f[0x658/4]);
                hero_steer_heading(0, 0.0216f, 0.21600002f, 0.12566373f);
                i_temp59 = ((Hero *)g_hero_state)->u[0x2294/4];
                if ((((u32) (i_temp59 - 0x28) < 2U) && (((Hero *)g_hero_state)->b[0x49C] == 0)) || (i_temp59 == 0x3E)) {
                    if (((Hero *)g_hero_state)->i[0x694/4] != 0) {
                        f_temp19 = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x620/4] - ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x624/4] - ((Hero *)g_hero_state)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], f_temp19) < 1.5707965f) {
                            ((Hero *)g_hero_state)->f[0x1A0/4] = f_temp19;
                            hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.12566373f);
                        }
                    }
                    if ((((Hero *)g_hero_state)->i[0x660/4] != 0) && (((Hero *)g_hero_state)->i[0x678/4] < 0x29)) {
                        FastVecSub((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v10));
                        i_temp29 = ((Hero *)g_hero_state)->i[0x678/4] + 1;
                        ((Hero *)g_hero_state)->i[0x678/4] = i_temp29;
                        FastVecScale((s32) ((TI128*)v20), (s32) ((TI128*)v20), (f32) i_temp29 * 0.025f);
                        f_temp61 = (f32) (((Hero *)g_hero_state)->i[0x678/4] - 1) * 0.025f;
                        FastVecSub((s32) ((TI128*)v30), (s32)((TI128*)v0), (s32) ((TI128*)v10));
                        FastVecScale((s32) ((TI128*)v30), (s32) ((TI128*)v30), f_temp61);
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + (M2C_BITWISE(f32, v20[2]) - v30[2]));
                        FastVecAdd((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
                        FastVecSub((s32) ((TI128*)v20), (s32) ((TI128*)v30), (s32) (((void*)g_hero_state) + 0x80));
                        ((Hero *)g_hero_state)->f[0xF0/4] = v20[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = v20[1];
                        FastVecSub((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) (((void*)g_hero_state) + 0x5D0));
                        f_temp85 = ((Hero *)g_hero_state)->f[0x5D8/4];
                        f_temp40 = ((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, v20[2]);
                        ((Hero *)g_hero_state)->f[0x88/4] = f_temp40;
                        if (f_temp40 < f_temp85) {
                            if (((Hero *)g_hero_state)->i[0x678/4] < 0x29) {
                                if (f_temp40 < f_temp85) {
                                    ((Hero *)g_hero_state)->f[0x88/4] = f_temp85;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32)(g_hero_state + 0x5D0));
                        ((Hero *)g_hero_state)->f[0xF0/4] = v20[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = v20[1];
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, v20[2]));
                        FastVecSub((s32) ((TI128*)v30), (s32)(g_hero_state + 0x5D0), (s32)(g_hero_state + 0x80));
                        v30[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)v30)) > 0.020000001f) {
                            vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), 0.020000001f);
                        }
                        ((Hero *)g_hero_state)->f[0x80/4] = (f32) (((Hero *)g_hero_state)->f[0x80/4] + v30[0]);
                        ((Hero *)g_hero_state)->f[0x84/4] = (f32) (((Hero *)g_hero_state)->f[0x84/4] + v30[1]);
                    }
                    if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.0092f);
                    } else {
                        ApplyHeroGravityAndJumpMotion_pal();
                    }
                } else {
                    ((Hero *)g_hero_state)->i[0x660/4] = 0;
                    f_val16 = 0.0f;
                    if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) && (i_stack16 != 0)) {
                        hero_resolve_stick_direction(1.0f, 0);
                        f_val16 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1A0/4], ((Hero *)g_hero_state)->f[0x64C/4]);
                        if (f_val16 > 0.78539824f) {
                            f_val16 = 0.78539824f;
                        } else if (f_val16 < -0.78539824f) {
                            f_val16 = -0.78539824f;
                        }
                    }
                    math_approach_with_velocity((s32)(g_hero_state + 0x6A0), f_val16, (s32)(g_hero_state + 0x6A4), 0.0216f, 0.43200004f, 0.0f, 0);
                    ApproachValue((s32)(g_hero_state + 0x680), 0.24000001f, 0.006f);
                    i_stack10 = ((Hero *)g_hero_state)->i[0x634/4];
                    i_stack11 = ((Hero *)g_hero_state)->f[0x638/4];
                    k30 = 0.3f;
                    qcopy(v20, &((Hero *)g_hero_state)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)v20), (s32) &i_stack10, (s32) &i_stack11, ((Hero *)g_hero_state)->i[0x654/4], k30);
                    f_temp16 = mat_fast_helper_a(vec_distance_xy((s32)(g_hero_state + 0x5D0), (s32) ((TI128*)v20)), M2C_BITWISE(f32, v20[2]) - ((Hero *)g_hero_state)->f[0x5D8/4]);
                    if (f_temp16 > 0.0f) {
                        f_val24 = f_temp16 * -0.09549296f;
                        if (f_temp16 > 0.26179942f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 0;
                        } else if ((f_temp16 < 0.13962635f) && (((Hero *)g_hero_state)->i[0x67C/4] == 0)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    } else {
                        f_val24 = -f_temp16 * 0.4583662f;
                        if (f_temp16 < -0.19198623f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 1;
                        } else if ((f_temp16 > -0.122173056f) && (((Hero *)g_hero_state)->i[0x67C/4] == 1)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < f_val24) {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), f_val24, 0.0032000002f);
                    } else {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), f_val24, 0.00080000004f);
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] > 0.24000001f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = 0.24000001f;
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < -0.050000004f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = -0.050000004f;
                    }
                    f_temp17 = ((Hero *)g_hero_state)->f[0x680/4] + ((Hero *)g_hero_state)->f[0x674/4];
                    ((Hero *)g_hero_state)->f[0x644/4] = f_temp17;
                    if (f_temp17 < 0.0f) {
                        ((Hero *)g_hero_state)->f[0x644/4] = 0.0f;
                    }
                    i_temp82 = ((void*)g_hero_state) + 0x5D0;
                    FastVecSub((s32) (((void*)g_hero_state) + 0xF0), (s32)((TI128*)v0), (s32) i_temp82);
                    i_temp97 = ((void*)g_hero_state) + 0x80;
                    FastVecSub((s32) ((TI128*)v20), (s32) i_temp82, (s32) i_temp97);
                    i_stack12 = -FastVecLength((s32) ((TI128*)v20));
                    math_spring_float_to_goal((s32) &i_stack12, (s32) (((void*)g_hero_state) + 0x6AC), 0.0f, 0.0432f, 0.43200004f, 0.14000002f);
                    f_temp18 = FastVecLength((s32) ((TI128*)v20));
                    if (f_temp18 < ((Hero *)g_hero_state)->f[0x6AC/4]) {
                        ((Hero *)g_hero_state)->f[0x6AC/4] = f_temp18;
                    }
                    f_temp33 = ((Hero *)g_hero_state)->f[0x6AC/4];
                    if (f_temp33 < f_temp18) {
                        vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), f_temp33);
                    }
                    FastVecAdd((s32) i_temp97, (s32) i_temp97, (s32) ((TI128*)v20));
                    f_temp88 = ((Hero *)g_hero_state)->f[0x88/4];
                    f_temp84 = ((Hero *)g_hero_state)->f[0x5D8/4];
                    if (f_temp88 < f_temp84) {
                        if (((Hero *)g_hero_state)->f[0x31C/4] < 1.0f) {
                            if (f_temp88 < f_temp84) {
                                ((Hero *)g_hero_state)->f[0x88/4] = f_temp84;
                            }
                        }
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x11) {
                        f_temp20 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.3490659f, 0.6108653f));
                        v50[0] = math_fast_sin_or_cos_a(f_temp20);
                        v50[1] = math_fast_sin_or_cos_b(f_temp20);
                        v50[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)v20), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &v50[0]);
                        qcopy(v60, &((Hero *)g_hero_state)->q[0x80/16]);
                        v60[2] += 0.6f;
                        coll_process_hit(1.0f, (s32) ((TI128*)v60), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)v20));
                    }
                }
            }
        }
        break;
    case 0x17:                                      /* switch 1 */
    case 0x18:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.12566373f);
        if (((Hero *)g_hero_state)->b[0x22C3] != 2) {
            StepAngleTowardTarget((s32)(g_hero_state + 0x94), 0, 0.0f, 0.094247796f);
        }
        FastVecSub((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0x550), (s32)(g_hero_state + 0x80));
        vec_clamp_length((s32)(g_hero_state + 0xF0), 0.080000006f);
        ApproachValue((s32)(g_hero_state + 0x580), ((Hero *)g_hero_state)->f[0x88/4], 0.060000002f);
        break;
    case 0x46:                                      /* switch 1 */
    case 0x47:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.028800001f, 0.28800002f, 0.094247796f);
        FastVecSub((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0x550), (s32)(g_hero_state + 0x80));
        vec_clamp_length((s32)(g_hero_state + 0xF0), 0.034f);
        ApproachValue((s32)(g_hero_state + 0x580), ((Hero *)g_hero_state)->f[0x88/4], 0.060000002f);
        break;
    case 0x19:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.028800001f, 0.28800002f, 0.094247796f);
        FastVecSub((s32) ((TI128*)v60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &v40[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)v60));
        } else {
            FastVecCross((s32) &v40[0], (s32) ((TI128*)v60), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &v40[0], (s32) &v40[0], 0.2f);
        FastVecAdd((s32) &v50[0], (s32)(g_hero_state + 0x80), (s32) &v40[0]);
        if ((hero_find_ledge_grab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab_pal((s32) &v50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)v0), (s32)(g_hero_state + 0x80));
            i_val34 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            i_val38 = (s32)g_hero_state_machine_bytes;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(i_val34 + i_val38) * 0.5f);
        }
        break;
    case 0x76:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.11000001f;
        ApproachHeroVelocity_pal(0.010000001f);
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.0072000003f);
        break;
    case 0x6:                                       /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2C) {
            f_val25 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                f_val25 = 0.43633235f;
            }
            qcopy(v0, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &v0[1], f_val25, (s32) (((void*)g_hero_state) + 0xA4), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            math_approach_with_velocity((s32)((TI128*)v0), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_update_target_speed_pal();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_airborne_steering_pal();
        }
        i_val47 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets_pal();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) i_val47, (s32) i_val47, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) i_val47) < -1.0000001f) {
            cam_set_view_space_height((s32) i_val47, (s32) i_val47, -1.0000001f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        i_val2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0034906592f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0034906592f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) i_val2, (s32) i_val2, vec_length_xy((s32) i_val2) * 0.88f);
        hero_apply_mode_transform((s32) i_val2, (s32) i_val2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) i_val2) < -1.0000001f) {
            cam_set_view_space_height((s32) i_val2, (s32) i_val2, -1.0000001f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.0003490659f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        i_val14 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            i_val14 = 0;
        }
        if (i_val14 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.120000005f);
            i_temp70 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) i_temp70, (s32) i_temp70, 0.036000002f);
        } else {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.024f);
        }
        if (((Hero *)g_pad_state)->i[0x1A4/4] & 0x40) {
            ApproachValue((s32)(g_hero_state + 0x5B0), 0.0f, 0.6f);
        }
        hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0108f);
        if (cam_get_view_space_height((s32)(g_hero_state + 0xF0)) > 0.120000005f) {
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.120000005f);
        }
        if (cam_get_view_space_height((s32)(g_hero_state + 0xF0)) < -0.24000001f) {
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), -0.24000001f);
        }
        f_temp34 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x4b) && (f_temp34 < 0.0f) && (f_temp86 = ((Hero *)g_hero_state)->f[0x31C/4], (f_temp86 < 1.2f))) {
            f_val3 = (f_temp86 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (f_val3 < 0.0f) {
                f_val3 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), f_temp34 * f_val3);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.03888f, 0.43200004f, 0.10000001f);
            }
        } else if (f_temp34 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&g_camera_l20_view_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets_pal();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.24000001f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.03888f, 0.43200004f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.10471977f);
        f_val26 = 0.002f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            f_val26 = 0.00080000004f;
        }
        ApproachHeroVelocity_pal(f_val26);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            i_temp19 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (i_temp19 != -1) {
                i_temp71 = (i_temp19 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(i_temp71, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(i_temp71, u8* , 0x74) != 0)) {
                    snd_stop_voice(i_temp19);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            i_temp20 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (i_temp20 != -1) {
                i_temp72 = (i_temp20 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(i_temp72, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(i_temp72, u8* , 0x74) != 0)) {
                    snd_stop_voice(i_temp20);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        f_val64 = 0.060000002f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            f_val64 = 0.10000001f;
        }
        f_val65 = 0.72f;
        f_temp41 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            f_val64 = 0.15400001f;
            f_val65 = 0.98640007f;
        }
        if (f_temp41 != 0.0f) {
            f_val65 = f_temp41;
        }
        i_temp83 = ((void*)g_hero_state) + 0xF0;
        i_stack13 = cam_get_view_space_height((s32) i_temp83);
        hero_resolve_stick_direction(f_val64, 0);
        hero_steer_heading(0, 0.036000002f, 0.43200004f, 0.25132746f);
        hero_approach_speed(0.006f, 0.0028000001f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets_pal();
        cam_project_vector_onto_view_plane((s32) i_temp83, (s32) i_temp83);
        math_spring_float_to_goal((s32) &i_stack13, (s32) (((void*)g_hero_state) + 0xA98), -f_val64 * f_val65, 0.036000002f, 0.43200004f, 0.34000003f);
        hero_apply_mode_transform((s32) i_temp83, (s32) i_temp83, -i_stack13);
        f_temp35 = ((Hero *)g_hero_state)->f[0x88/4];
        if (f_temp35 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), f_temp35, 0.080000006f);
        }
        ProbeHeroAirborneWallContact_pal();
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
                hero_resolve_stick_direction(0.119f, 0);
            }
            hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x4A4/4], 0);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == 0x11) {
                part_emit_hero_dust_and_debris_pal(3, 0x10, 1);
                if (g_ripple_surface != 0) {
                    RippleDisturb(g_ripple_surface, g_ripple_surface_data, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            f_temp42 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((f_temp42 >= 4.0f) && (f_temp42 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects_pal(7, 0, 0);
            }
        }
        i_temp1 = ((Hero *)g_hero_state)->h[0x4AC/2];
        i_temp16 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (i_temp16 == i_temp1) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((i_temp16 < i_temp1) && (i_temp60 = ((Hero *)g_hero_state)->u[0x2294/4], (i_temp60 != 0xB)) && (i_temp60 != 0x10) && (i_temp60 != 0xC) && (i_temp60 != 0x11) && (i_temp60 != 0x1B) && (i_temp60 != 0x89) && (i_temp60 != 0x48))) {
            if (((Hero *)g_hero_state)->h[0x528/2] != 0) {
                hero_steer_reference_point_pal();
                if ((((Hero *)g_hero_state)->u[0x2294/4] == 0xA) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x8) && (((Hero *)g_hero_state)->f[0x178/4] < 0.14000002f)) {
                    ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.014f));
                    ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.014f));
                    qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
                }
            } else {
                hero_steer_heading(0, 0.0216f, 0.28800002f, 0.30019668f);
                f_temp62 = ((Hero *)g_hero_state)->f[0x1B4/4];
                if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                    ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (f_temp62 * 0.4f);
                }
                if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                    hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
                } else {
                    hero_compute_push_direction(99999.0f);
                }
                ((Hero *)g_hero_state)->f[0x1B4/4] = f_temp62;
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
                hero_build_move_impulse(0.5f, 0.040000003f);
                if (((Hero *)g_hero_state)->u[0x2294/4] == 9) {
                    i_temp42 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (i_temp42 < (((Hero *)g_hero_state)->h[0x4AC/2] + 3)) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) i_temp42 * 0.0064000003f);
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                    i_temp43 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (i_temp43 < 0x1c) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) i_temp43 * 0.021200001f);
                    }
                }
                if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0x8) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                    qcopy(v0, &((Hero *)g_hero_state)->q[0x80/16]);
                    cam_offset_point_in_view_space((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    cam_offset_point_by_side_direction((s32) ((TI128*)v10), (s32)((TI128*)v0), 0.95f);
                    if (CollLine((s32)((TI128*)v0), (s32) ((TI128*)v10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)g_hero_state)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            hero_update_airborne_steering_pal();
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
                i_temp84 = ((void*)g_hero_state) + 0xF0;
                f_val4 = vec_length_xy((s32) i_temp84);
                if (f_val4 > 0.07400001f) {
                    f_val4 = 0.07400001f;
                }
                vec_fast_normalize_helper((s32) i_temp84, (s32) i_temp84, f_val4);
            }
        }
        f_temp43 = ((Hero *)g_hero_state)->f[0x318/4];
        f_temp87 = ((Hero *)g_hero_state)->f[0x490/4];
        if (f_temp87 < f_temp43) {
            f_temp21 = f_temp87 + 0.120000005f;
            ((Hero *)g_hero_state)->f[0x490/4] = f_temp21;
            if (f_temp43 < f_temp21) {
                ((Hero *)g_hero_state)->f[0x490/4] = f_temp43;
            }
        }
        f_temp44 = ((Hero *)g_hero_state)->f[0x88/4];
        if (f_temp44 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = f_temp44;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xf))) {
            f_temp45 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (f_temp45 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = f_temp45;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets_pal();
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters_pal();
        }
        i_temp61 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((i_temp61 == 0x10) || (i_temp61 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xb) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 8) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)v0), 1, 0.8f, 0.0f, 0.3f);
                    i_temp30 = coll_process_hit(0.9f, (s32)((TI128*)v0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (i_temp30 != 0) {
                        FastVecScale((s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (i_val23 = 0; i_val23 < i_temp30; i_val23++) {
                            if (moby_is_in_special_class_range(((s32 *)g_special_moby_table)[i_val23]) != 0) {
                                part_queue_impact_effect(((s32 *)g_special_moby_table)[i_val23], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x38) && (((Hero *)g_hero_state)->b[0x49E] == 0) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.030000001f)) {
            EmitHeroTimedEffects_pal();
        }
        ApplyHeroGravityAndJumpMotion_pal();
        ProbeHeroAirborneWallContact_pal();
        break;
    case 0x16:                                      /* switch 1 */
        f_val47 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        f_val5 = 0.0016000001f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9)) {
            f_val5 = 0.004f;
        }
        f_val47 = f_val47 - f_val5;
        if (f_val47 < 0.0f) {
            f_val47 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        i_val46 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) i_val46, (s32) i_val46, f_val47);
        hero_apply_mode_transform((s32) i_val46, (s32) i_val46, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.46000004f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)v0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
        f_temp23 = vec_length_xy((s32)((TI128*)v0));
        if (f_temp23 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = f_temp23;
            if (f_temp23 < g_hero_l20_speed_params[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l20_speed_params[0][1] * 0.020000001f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l20_speed_params[1][1] * 0.020000001f;
            }
            if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.018000001f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x18AC/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        }
        speed62 = 1.0f;
        if (((Hero *)g_hero_state)->b[0x22B4] == 3) {
            hero_steer_heading(0, 0.0432f, 0.43200004f, 0.11170109f);
        } else if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
            hero_steer_heading(0, 0.0432f, 0.43200004f, 0.15707967f);
        } else if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_steer_heading(0, 0.0432f, 0.43200004f, 0.15707967f);
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets_pal();
        }
        hero_approach_speed(speed62 * 0.0072000003f, 0.008f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            DeflectHeroOffSteepSurface_pal(1);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        }
        {
            s32 found, k, m;
            qcopy(v10, &((Hero *)g_hero_state)->q[0xE0/16]);
            found = coll_process_hit(((Hero *)g_hero_state)->f[0x264/4] + 0.2f, (s32)((TI128*)v10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
            for (k = 0; k < found; k++) {
                m = ((s32 *)g_special_moby_table)[k];
                if (m != 0) {
                    switch (*(s16 *)(m + 0xAA)) {
                    case 0xCB:
                        part_queue_impact_effect(m, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0xE0), (s32) g_impact_effect_data, 100.0f);
                        break;
                    case 0x1366:
                        moby_l00_raise_state_to_8();
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
        FastVecSub((s32)((TI128*)v0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)v0), (s32)(g_hero_state + 0x160)) < 0.0f) {
            vec_clear_128((s32)(g_hero_state + 0x160));
        }
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.0108f);
        DeflectHeroOffSteepSurface_pal(0);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0x18A0)) - 0x1790, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.0216f);
        break;
    case 0x3C:                                      /* switch 1 */
    case 0x64:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    case 0x65:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((f32) ((Hero *)g_hero_state)->i[0x18C0/4] * 0.5f) < (((Hero *)g_hero_state)->f[0x334/4] - ((Hero *)g_hero_state)->f[0x88/4])) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.0050000004f;
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.020000001f;
        }
        break;
    case 0x79:                                      /* switch 1 */
        part_emit_hero_radial_particles_pal();
        /* fallthrough */
    case 0x78:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.020000001f;
        break;
    case 0x7A:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.007f;
        break;
    case 0x3F:                                      /* switch 1 */
    case 0x43:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        hero_approach_speed(0.0f, 0.00504f);
        vec_clear_128((s32)(g_hero_state + 0xF0));
        DeflectHeroOffSteepSurface_pal(0);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.0216f);
        break;
    case 0x4D:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        i_temp109 = (s32) &g_hero_l20_action_table[((Hero *)g_hero_state)->h[0xBFC/2]];
        i_temp6 = M2C_FIELD(i_temp109, s32* , 4);
        switch (i_temp6) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 5.5f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.07000001f;
            }
            break;
        case 1:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 5.5f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.07000001f;
            }
            break;
        }
        if (((Hero *)g_hero_state)->i[0xC2C/4] == 0) {
            f_temp46 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((f32) M2C_FIELD(i_temp109, s32* , 0x1C) <= f_temp46) {
                if (f_temp46 <= (f32) M2C_FIELD(i_temp109, s32* , 0x20)) {
                    i_temp22 = ((M2C_FIELD(i_temp109, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], i_temp22, (s32) ((TI128*)v10));
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], i_temp22 | 1, (s32) ((TI128*)v20));
                    FastVecAdd((s32)((TI128*)v0), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
                    FastVecScale((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    coll_sweep_from_object((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)v0), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
                }
            }
        }
        ApproachValue((s32)(g_hero_state + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
            hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
        } else {
            hero_l00_select_aim_target(5.0f, 0.78539824f, 0.78539824f);
        }
        hero_approach_speed(0.014800001f, 0.0112000005f);
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
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0x118/4] - 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.0216f);
        }
        hero_try_surface_push_response(0.7f, 0.0f, 0.3f);
        break;
    case 0x4B:                                      /* switch 1 */
        hero_resolve_stick_direction(0.040000003f, 0);
        hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.17453296f);
        hero_approach_speed(0.006f, 0.0028000001f);
        hero_compute_push_direction(99999.0f);
        cam_project_vector_onto_view_plane((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0));
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.028800003f);
        break;
    case 0x4E:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.11000001f;
        ApproachHeroVelocity_pal(0.010000001f);
        f_val1 = 0.0072000003f;
        i_val3 = ((void*)g_hero_state) + 0x130;
        hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) i_val3, f_val1);
        break;
    case 0x41:                                      /* switch 1 */
        hero_resolve_stick_direction(0.060000002f, 0);
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_airborne_steering_pal();
        }
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), 0.0048f);
        if (((Hero *)g_hero_state)->f[0xF8/4] < -0.20000002f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.20000002f;
        }
        break;
    case 0x44:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f) {
            hero_start_pose_offset(0.0f, 0.25132746f, 0.0f);
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.008f);
        break;
    case 0x40:                                      /* switch 1 */
    case 0x4C:                                      /* switch 1 */
        hero_resolve_stick_direction(0.060000002f, 0);
        f_val36 = 0.19896756f;
        f_val28 = 0.04752f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            f_val36 = 0.23387417f;
            f_val28 = 0.053280003f;
        }
        hero_steer_heading(0, f_val28, 0.21600002f, f_val36);
        hero_approach_speed(0.0072000003f, 0.008f);
        if (((Hero *)g_hero_state)->f[0x174/4] < 0.014f) {
            ((Hero *)g_hero_state)->b[0x40C] = 1U;
            if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)g_hero_state)->b[0x40F] = 1U;
            }
        }
        f_temp64 = ReadPadFloatHistory(0);
        if ((FastDiffRots(f_temp64, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                f_val69 = 0.060000002f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.025464792f);
                if (f_val69 < 0.0f) {
                    f_val69 = 0.0f;
                }
                if (f_val69 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = f_val69;
                }
            }
        }
        if (((Hero *)g_hero_state)->b[0x40C] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1A0/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        DeflectHeroOffSteepSurface_pal(1);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        }
        break;
    case 0x42:                                      /* switch 1 */
        f_temp36 = vec_length_xy((s32)(g_hero_state + 0xF0));
        if (*(s16 *)(g_hero_state + 0x34E) != 0) {
            f_temp36 = f_temp36 * 0.98800004f;
        } else {
            f_temp36 = f_temp36 * 0.90400004f;
        }
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), f_temp36);
        i_temp110 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
        M2C_FIELD(i_temp110, s32* , 0xF8) = 0;
        if (M2C_FIELD(i_temp110, s16* , 0x34E) != 0) {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0) + 0x30, 0.0088f);
        } else {
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.004f);
        }
        break;
    case 0x49:                                      /* switch 1 */
    case 0x4A:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0xC20/4] = 1.3f;
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.028800001f, 0.28800002f, 0.094247796f);
        FastVecSub((s32) ((TI128*)v60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &v40[0], (s32) (((void*)g_hero_state) + 0x2C0), (s32) ((TI128*)v60));
        } else {
            FastVecCross((s32) &v40[0], (s32) ((TI128*)v60), (s32) (((void*)g_hero_state) + 0x2C0));
        }
        vec_scale_to_length((s32) &v40[0], (s32) &v40[0], 0.2f);
        FastVecAdd((s32) &v50[0], (s32)(g_hero_state + 0x80), (s32) &v40[0]);
        if ((hero_find_ledge_grab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab_pal((s32) &v50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)v0), (s32)(g_hero_state + 0x80));
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), g_hero_l20_speed_scale_table[FloatToInt(((Hero *)g_hero_state)->f[0xC38/4])] * 0.5f);
            break;
        }
        break;
    case 0x37:                                      /* switch 1 */
        if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) == 0x44) {
            hero_steer_heading(0, 0.19728f, 0.36f, 0.24434614f);
        } else {
            hero_steer_heading(0, 1.44f, 0.14400001f, 0.48869228f);
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (i_stack14 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (i_stack15 != M2C_FIELD(f_temp89, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
