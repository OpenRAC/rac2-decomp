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
extern void hero_update_held_grab_pal(void);
extern s32 shooter_update_ranged_attack_pal(s32);
extern s32 SelectHeroStateAnimation(s32);
extern void hero_exit_vehicle_mode_pal(s32);
extern void hero_slide_along_wall_pal(s32);
extern s32 hero_l20_set_move_state_pal(s32, s32);
extern s32 g_hero_sound_flag_4;
extern char g_impact_effect_data[] MACRO_ADDR;
extern void moby_l00_raise_state_to_8();
extern void moby_raise_state_to_eight_copy();

/* Runs the hero state machine for one frame: one big switch on the hero state decides movement and animation. (PAL version) */
void hero_l20_update_state_machine_pal(void) {
    f32 speed;
    s32 limit_a;
    s32 *frame_counter;
    Hero *hero_view;
    f32 vec_00[4] __attribute__((aligned(16)));
    f32 vec_10[4] __attribute__((aligned(16)));
    f32 vec_20[4] __attribute__((aligned(16)));
    f32 vec_30[4] __attribute__((aligned(16)));
    f32 vec_40[4] __attribute__((aligned(16)));
    f32 vec_50[4] __attribute__((aligned(16)));
    f32 vec_60[4] __attribute__((aligned(16)));
    f32 mat_70[16] __attribute__((aligned(16)));
    f32 vec_b0[4] __attribute__((aligned(16)));
    f32 vec_c0[4] __attribute__((aligned(16)));
    f32 vec_d0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 scale_a;
    f32 scale_b;
    s32 anim_id;
    s32 anim_blend;
    f32 scale_c;
    void *hero_field_a60;
    void* pval_1;
    void* pval_2;
    f32 fval_1;
    void* pval_3;
    s32 ival_1;
    void* pval_4;
    s32 ival_2;
    s32 ival_3;
    void* pval_5;
    s32 ival_4;
    void* pval_6;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 selected;
    f32 scale_d;
    s32 count;

    f32 local_float_e0;
    f32 local_float_e4;
    f32 local_float_e8;
    f32 local_float_ec;
    f32 local_float_f0;
    f32 local_float_f4;
    f32 local_float_f8;
    s32 local_int_fc;
    f32 local_float_100;
    s32 local_int_104;
    f32 local_float_108;
    f32 local_float_10c;
    f32 local_float_110;
    s32 local_int_114;
    s32 local_int_118;
    s32 local_int_11c;
    f32 fval_2;
    f32 fval_3;
    f32 fval_4;
    f32 fval_5;
    f32 fval_6;
    f32 fval_7;
    f32 fval_8;
    f32 fval_9;
    f32 fval_10;
    f32 fval_11;
    f32 fval_12;
    f32 fval_13;
    f32 fval_14;
    f32 fval_15;
    f32 fval_16;
    f32 fval_17;
    f32 fval_18;
    f32 fval_19;
    f32 fval_20;
    f32 fval_21;
    f32 fval_22;
    f32 fval_23;
    f32 fval_24;
    f32 fval_25;
    f32 fval_26;
    f32 fval_27;
    f32 fval_28;
    f32 fval_29;
    f32 fval_30;
    f32 fval_31;
    f32 fval_32;
    f32 fval_33;
    f32 fval_34;
    f32 fval_35;
    f32 fval_36;
    f32 fval_37;
    f32 fval_38;
    f32 fval_39;
    f32 fval_40;
    f32 fval_41;
    f32 fval_42;
    f32 fval_43;
    f32 fval_44;
    f32 fval_45;
    f32 fval_46;
    f32 fval_47;
    f32 fval_48;
    f32 fval_49;
    f32 fval_50;
    f32 fval_51;
    f32 fval_52;
    f32 fval_53;
    f32 fval_54;
    f32 fval_55;
    f32 fval_56;
    f32 fval_57;
    f32 fval_58;
    f32 fval_59;
    f32 fval_60;
    f32 fval_61;
    f32 fval_62;
    f32 fval_63;
    f32 fval_64;
    f32 fval_65;
    f32 fval_66;
    f32 fval_67;
    f32 fval_68;
    f32 fval_69;
    f32 fval_70;
    f32 fval_71;
    f32 fval_72;
    f32 fval_73;
    f32 fval_74;
    f32 fval_75;
    f32 fval_76;
    f32 fval_77;
    f32 fval_78;
    f32 fval_79;
    f32 fval_80;
    f32 fval_81;
    f32 fval_82;
    f32 fval_83;
    f32 fval_84;
    f32 fval_85;
    f32 fval_86;
    f32 fval_87;
    f32 fval_88;
    f32 fval_89;
    f32 fval_90;
    f32 fval_91;
    f32 fval_92;
    f32 fval_93;
    f32 fval_94;
    f32 fval_95;
    f32 fval_96;
    f32 fval_97;
    f32 fval_98;
    f32 fval_99;
    f32 fval_100;
    f32 fval_101;
    f32 fval_102;
    f32 fval_103;
    f32 fval_104;
    f32 fval_105;
    f32 fval_106;
    f32 fval_107;
    f32 fval_108;
    f32 fval_109;
    f32 fval_110;
    f32 fval_111;
    f32 fval_112;
    f32 fval_113;
    f32 fval_114;
    f32 fval_115;
    f32 fval_116;
    f32 fval_117;
    f32 fval_118;
    f32 fval_119;
    f32 fval_120;
    f32 fval_121;
    f32 fval_122;
    f32 fval_123;
    f32 fval_124;
    f32 fval_125;
    f32 fval_126;
    f32 fval_127;
    f32 fval_128;
    f32 fval_129;
    f32 fval_130;
    f32 fval_131;
    f32 fval_132;
    f32 fval_133;
    f32 fval_134;
    f32 fval_135;
    f32 fval_136;
    f32 fval_137;
    f32 fval_138;
    f32 fval_139;
    f32 fval_140;
    f32 fval_141;
    f32 fval_142;
    f32 fval_143;
    f32 fval_144;
    f32 fval_145;
    f32 fval_146;
    f32 fval_147;
    f32 fval_148;
    f32 fval_149;
    f32 fval_150;
    f32 fval_151;
    f32 fval_152;
    f32 fval_153;
    f32 fval_154;
    f32 fval_155;
    f32 fval_156;
    f32 fval_157;
    f32 fval_158;
    s16 ival_5;
    s32 ival_6;
    s16 ival_7;
    s32 ival_8;
    s32 ival_9;
    s32 ival_10;
    s32 ival_11;
    s32 ival_12;
    s32 ival_13;
    s32 ival_14;
    s32 ival_15;
    s32 ival_16;
    s32 ival_17;
    s32 ival_18;
    s32 ival_19;
    s32 ival_20;
    s32 ival_21;
    s32 ival_22;
    s32 ival_23;
    s32 ival_24;
    s32 ival_25;
    s32 ival_26;
    s32 ival_27;
    s32 ival_28;
    s32 ival_29;
    s32 ival_30;
    s32 ival_31;
    s32 ival_32;
    s32 ival_33;
    s32 ival_34;
    s32 ival_35;
    s32 ival_36;
    s32 ival_37;
    s32 ival_38;
    s32 ival_39;
    s32 ival_40;
    s32 ival_41;
    s32 ival_42;
    s32 ival_43;
    s32 ival_44;
    s32 ival_45;
    s32 ival_46;
    s32 ival_47;
    s32 ival_48;
    s32 ival_49;
    s32 ival_50;
    s32 ival_51;
    s32 ival_52;
    s32 ival_53;
    s32 ival_54;
    s32 ival_55;
    s32 ival_56;
    s32 ival_57;
    s32 ival_58;
    s32 ival_59;
    s32 ival_60;
    s32 ival_61;
    s32 ival_62;
    s32 ival_63;
    s32 ival_64;
    s32 ival_65;
    s32 ival_66;
    s32 ival_67;
    s32 ival_68;
    s32 ival_69;
    s32 ival_70;
    s32 ival_71;
    s32 ival_72;
    s32 ival_73;
    s32 ival_74;
    s32 ival_75;
    s32 ival_76;
    s32 ival_77;
    s32 ival_78;
    s32 ival_79;
    s32 ival_80;
    s32* pval_7;
    s32* pval_8;
    u16 ival_81;
    u16 ival_82;
    u16 ival_83;
    u32 ival_84;
    u32 ival_85;
    u32 ival_86;
    u32 ival_87;
    u32 ival_88;
    u32 ival_89;
    u32 ival_90;
    u32 ival_91;
    u32 ival_92;
    u32 ival_93;
    u32 ival_94;
    u32 ival_95;
    u8 ival_96;
    u8 ival_97;
    u8 ival_98;
    u8 ival_99;
    void* pval_9;
    void* pval_10;
    void* pval_11;
    void* pval_12;
    void* pval_13;
    void* pval_14;
    void* pval_15;
    void* pval_16;
    void* pval_17;
    void* pval_18;
    void* pval_19;
    void* pval_20;
    void* pval_21;
    void* hero_field_7c;
    f32 turn;
    f32 angle;
    f32 min_value;
    void* hero_field_a30;
    void* pval_22;
    void* pval_23;
    void* pval_24;
    void* pval_25;
    void* pval_26;
    void* pval_27;
    void* pval_28;
    void* pval_29;
    void* pval_30;
    void* pval_31;
    void* pval_32;
    void* pval_33;
    void* pval_34;
    void* pval_35;
    void* pval_36;
    void* pval_37;
    void* pval_38;
    void* pval_39;
    void* pval_40;
    void* pval_41;
    void* pval_42;
    void* pval_43;
    void* pval_44;
    void* pval_45;
    void* pval_46;
    void* pval_47;
    void* pval_48;
    void* pval_49;
    void* pval_50;
    void* pval_51;
    void* pval_52;
    void* pval_53;
    void* pval_54;
    void* pval_55;
    void* pval_56;
    void* pval_57;
    void* pval_58;
    void* pval_59;
    void* pval_60;
    void* pval_61;

    local_int_114 = ((Hero *)g_hero_state)->i[0x2298/4];
    pval_21 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    local_int_118 = (s32) M2C_FIELD(pval_21, u8* , 0x43);
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
        ival_85 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((ival_85 == 1) || (ival_85 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vec_00) = 0;
                vec_00[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vec_00), (s32)&g_hero_aim_data[0x218]);
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (ival_97 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (ival_97 == 0xE)) || (ival_97 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.0028800003f, 0.10080001f, 0.13962635f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0069813184f) {
                    ival_11 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    ival_11 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != ival_11) {
                        set_hero_animation_pal(ival_11, 0, 4.0f);
                    }
                    fval_2 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 12.564863f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = fval_2;
                    if (fval_2 < 0.55f) {
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
            ival_94 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (ival_94 == 3) {
                fval_105 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (fval_105 > 1.0f) {
                    fval_105 = 1.0f;
                }
                pval_16 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                fval_131 = fval_105 * 0.0108f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = fval_131;
                if (M2C_FIELD(pval_16, u8* , 0x42) == M2C_FIELD(pval_16, u8* , 0x43)) {
                    fval_126 = ((Hero *)g_hero_state)->f[0x174/4] / fval_131;
                    if ((fval_126 > 4.0f) && ((f32) M2C_FIELD(pval_16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, fval_126, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (ival_94 == 4) {
                fval_131 = 0.0108f;
                if (((Hero *)g_hero_state)->b[0x1492] != 0) {
                    fval_131 = 0.00068000006f;
                }
            } else {
                fval_131 = 0.007080001f;
            }
            hero_approach_speed(0.0f, fval_131);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(fval_131);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                ival_57 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(ival_57, ival_57 + 0x30, 0.0088f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0216f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                hero_slide_along_wall_pal(0);
                if (((Hero *)g_hero_state)->h[0x34E/2] == 0) {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
                } else {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
                    hero_cancel_velocity_into_wall_pal();
                }
            }
        break;
    case 0x7C:                                      /* switch 1 */
        hero_field_7c = (void*)g_hero_state;
        if (((Hero *)hero_field_7c)->i[0x7A4/4] == 0) {
            ival_28 = CreateMoby(0x52A);
            ((Hero *)hero_field_7c)->i[0x7A4/4] = ival_28;
            if (((Hero *)hero_field_7c)->i[0x7A4/4] != 0) {
            qcopy((u8 *)ival_28 + 0x10, &((Hero *)hero_field_7c)->q[0x80/16]);
            qcopy((u8 *)ival_28 + 0xF0, &((Hero *)hero_field_7c)->q[0x90/16]);
            M2C_FIELD(ival_28, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero_field_7c)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero_field_7c)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero_field_7c)->i[0x7A4/4], u8* , 0x23) = 0U;
            ival_48 = ((Hero *)hero_field_7c)->i[0x7A4/4];
            M2C_FIELD(ival_48, u16* , 0x34) = (u16) (M2C_FIELD(ival_48, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero_field_7c)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero_field_7c)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero_field_7c)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero_field_7c)->i[0x7A4/4], u8* , 0x23) += FloatToInt(6.0f);
        ival_50 = ((Hero *)hero_field_7c)->i[0x7A4/4];
        if ((u8) M2C_FIELD(ival_50, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(ival_50, u8* , 0x23) = 0x80U;
        }
        ival_12 = ((Hero *)hero_field_7c)->i[0x7A4/4];
        pval_18 = ((Hero *)hero_field_7c)->ptr[0x2290/4];
        qcopy((u8 *)ival_12 + 0x10, (u8 *)pval_18 + 0x10);
        qcopy((u8 *)ival_12 + 0xF0, (u8 *)pval_18 + 0xF0);
        func_002A0F48(ival_12);
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
            ival_21 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (ival_21 != -1) {
                pval_17 = (ival_21 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(pval_17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(pval_17, u8* , 0x74) != 0) {
                        snd_stop_voice(ival_21);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            ival_13 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects_pal((ival_13 >= 9) ? 8 : ival_13, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            fval_48 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (fval_48 > 0.0f) {
                if (fval_48 < 10.0f) {
                    EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ival_51 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (ival_51 < 0xc) {
                    EmitHeroRandomizedMotionEffects_pal(((s32) (0x11 - ival_51) / 3) + 1, 1, 0);
                }
            }
        }
        ival_52 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (ival_52 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == ival_52) {
                part_emit_hero_dust_and_debris_pal(3, 0x10, 0);
                if (g_ripple_surface != 0) {
                    RippleDisturb(g_ripple_surface, g_ripple_surface_data, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x3a;
            }
            ival_35 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = ival_35;
            if (ival_35 >= 0x22) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.013962637f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.010471976f;
        fval_118 = 0.0f;
        
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            fval_120 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (fval_120 > 1.0f) {
                fval_120 = 1.0f;
            }
            if (fval_120 < 0.2f) {
                fval_120 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                ival_9 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                fval_120 = ((f32) (s16) ival_9 * 0.029411765f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) ival_9;
                if (fval_120 > 1.0f) {
                    fval_120 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (fval_120 < 0.35f)) {
                fval_120 = 0.35f;
            }
            fval_118 = fval_120 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            fval_119 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (fval_119 > 1.0f) {
                fval_119 = 1.0f;
            }
            if (fval_119 < 0.2f) {
                fval_119 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                count = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = count;
                fval_119 = ((f32) (s16) count * 0.029411765f) + 0.5f;
                if (fval_119 > 1.0f) {
                    fval_119 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                fval_119 = 1.0f;
            }
            fval_118 = fval_119 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                ival_8 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = ival_8;
                if ((s16) ival_8 >= 0x4c) {
                    ival_82 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (ival_82 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (ival_82 + 1);
                    }
                }
                ival_36 = (*(s32*)&g_frame_counter);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) (((s32)ival_36 * 5 + 2) / 6)) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) (((s32)ival_36 * 5 + 2) / 6);
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
            hero_view = (Hero *)g_hero_state;
            if ((g_frame_l20_counter - hero_view->i[0xA54/4]) < 0x3a) {
                hero_view->i[0xA50/4]++;
            }
            hero_view->i[0xA54/4] = g_frame_l20_counter;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x3b) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            fval_118 = 0.0f;
        }
        fval_56 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), fval_118, (s32) (((void*)g_hero_state) + 0xA28), 0.0216f, 0.28800002f, stick_turn, 0);
        fval_78 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], fval_56);
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
        fval_154 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (fval_154 < 1.0f) {
                fval_154 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            fval_97 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                fval_97 = 0.4f;
            }
            if (fval_154 < fval_97) {
                fval_154 = fval_97;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * fval_154);
        }
        if (math_fast_float_d((s32)(g_hero_state + 0xA30)) != 0) {
            hero_field_a30 = (void*)g_hero_state;
            moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 4, (s32)((TI128*)vec_00));
            (*(TI128*)vec_20) = 0;
            vec_20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_20));
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), 0.030000001f);
            FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32) ((TI128*)vec_20));
            vec_10[2] += 0.040000003f;
            part_spawn_bubble_pal((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), 25200.0f, -1.0f);
            if ((f32) math_random_int_below(0x64) < 40.0f) {
                ival_58 = 3;
                ival_62 = 0x9;
            } else {
                ival_58 = 0x21;
                ival_62 = 0x4b;
            }
            ((Hero *)hero_field_a30)->i[0xA30/4] = math_random_int_range(ival_58, ival_62);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                pval_42 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (pval_42 != 0) {
                    if (M2C_FIELD(pval_42, s16* , 0xAA) == 0x261) {
                        for (ival_66 = 0; ival_66 < 4; ival_66++) {
                            moby_transform_joint_to_world((s32) pval_42, ival_66 % 2, (s32)((TI128*)vec_00));
                            (*(TI128*)vec_20) = 0;
                            vec_20[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_20));
                            vec_00[0] += math_random_float_range(0.0f, 0.03f);
                            vec_00[1] += math_random_float_range(0.0f, 0.03f);
                            vec_00[2] += math_random_float_range(0.0f, 0.03f);
                            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x110/16]);
                            vec_add_offset((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), -0.015000001f, ((Hero *)g_hero_state)->f[0x98/4], ((Hero *)g_hero_state)->f[0x94/4]);
                            ((Hero *)g_hero_state)->h[0xA38/2] = FloatToInt((0.14000002f - ((Hero *)g_hero_state)->f[0x1B4/4]) * 28.571424f);
                            part_spawn_bubble_pal((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), math_random_float_range(6300.0f, 9450.0f), -1.0f);
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
        fval_75 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        ival_86 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (ival_86 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], fval_75);
        } else if (ival_86 == 0x32) {
            fval_121 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l20_blend_table, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) && (fval_121 < 0.09f)) {
                fval_121 = 0.09f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), fval_121, ((Hero *)g_hero_state)->f[0x98/4], fval_75);
        } else if (ival_86 == 0x33) {
            local_float_e0 = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &local_float_e0, 0.0f, 0.0032000002f);
            } else {
                ApproachValue((s32) &local_float_e0, 0.0f, 0.0016000001f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), local_float_e0);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        hero_slide_along_wall_pal(0);
        fval_76 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(fval_75) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), fval_76, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.024434613f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        fval_82 = fval_78 * 47.0f;
        ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = fval_82;
        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = (f32) (fval_76 * 1.5f);
        ((Hero *)g_hero_l20_state_alias)->f[0x110/4] = (f32) (fval_76 * 1.4f);
        if (fval_82 > 0.8726647f) {
            ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = 0.8726647f;
        } else if (fval_82 < -0.8726647f) {
            ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = -0.8726647f;
        }
        fval_49 = fval_78 * 40.0f;
        fval_23 = fval_76 * 1.1f;
        ((Hero *)g_hero_l20_state_alias)->f[0x364/4] = 0.03f;
        ((Hero *)g_hero_l20_state_alias)->f[0x368/4] = 0.22f;
        ((Hero *)g_hero_l20_state_alias)->f[0x324/4] = fval_49;
        ((Hero *)g_hero_l20_state_alias)->f[0x328/4] = fval_23;
        ((Hero *)g_hero_l20_state_alias)->f[0x414/4] = 0.03f;
        ((Hero *)g_hero_l20_state_alias)->f[0x418/4] = 0.22f;
        ((Hero *)g_hero_l20_state_alias)->f[0x3D4/4] = fval_49;
        ((Hero *)g_hero_l20_state_alias)->f[0x3D8/4] = fval_23;
        break;
    case 0x73:                                      /* switch 1 */
        ival_14 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        pval_29 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects_pal((ival_14 >= 9) ? 8 : ival_14, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) pval_29, (s32) pval_29, vec_length_xy((s32) pval_29) * 0.90400004f);
        hero_slide_along_wall_pal(0);
        break;
    case 0x72:                                      /* switch 1 */
        part_spawn_jittered_after_delay(0xF, 0x1E);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.90400004f);
        hero_slide_along_wall_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x67:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
        local_float_e4 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &local_float_e4, 0.0f, 0.0016000001f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), local_float_e4);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            pval_37 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(pval_37, s32* , 0x2290), 4, (s32)((TI128*)vec_00));
            (*(TI128*)vec_20) = 0;
            vec_20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), M2C_FIELD(pval_37, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_20));
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), 0.030000001f);
            FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32) ((TI128*)vec_20));
            vec_10[2] += 0.040000003f;
            part_spawn_bubble_pal((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), 25200.0f, -1.0f);
            ival_37 = M2C_FIELD(pval_37, s32* , 0x1B8);
            if (ival_37 < 0x21) {
                limit_a = 5;
                ival_71 = math_random_int_range(2, 4) + ((s32) M2C_FIELD(pval_37, s32* , 0x1B8) / limit_a);
                goto block_224;
            }
            if (ival_37 >= 0x3b) {
                ival_71 = math_random_int_range(0x8, 0x11);
block_224:
                M2C_FIELD(pval_37, s32* , 0xA30) = ival_71;
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
            ival_15 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects_pal((ival_15 >= 7) ? 6 : ival_15, 0, 0);
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
            fval_67 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l20_blend_table, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * fval_67);
            fval_25 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * fval_67;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = fval_25;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            fval_50 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((fval_50 > 0.0f) && (fval_50 < 10.0f)) {
                EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.00168f);
        hero_slide_along_wall_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x85:                                      /* switch 1 */
        pval_19 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)pval_19 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)pval_19 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)vec_00), (s32)(g_hero_state + 0x2C0), -1.0f);
        fval_122 = 0.0f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            fval_122 = -((Hero *)g_hero_state)->f[0x1FB4/4] * 0.75f;
        }
        math_spring_float_to_goal((s32)(g_hero_state + 0x7C0), (s32)(g_hero_state + 0x7C4), fval_122, 0.01008f, 0.43200004f, 0.036000002f);
        FastVecScale((s32) ((TI128*)vec_10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_10));
        vec_scale_to_length((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), 1.0f);
        hero_apply_reference_tilt_rotation((s32)((TI128*)vec_00), (s32) ((TI128*)vec_30), 0, 0.036000002f, 0.57600003f, 0.0f);
        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.26000002f;
        vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)g_hero_state, 0.26000002f);
        cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
        vec_clear_128((s32)((TI128*)vec_00));
        vec_00[1] = -((Hero *)g_hero_state)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(g_hero_state + 0x190), (s32)((TI128*)vec_00), (s32)&g_hero_aim_data[0x218]);
        hero_steer_heading(0, 0.028800001f, 0.43200004f, 0.04188791f);
        break;
    case 0x2F:                                      /* switch 1 */
        anim_id = -1;
        anim_blend = 0;
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
        if ((anim_id != -1) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation_pal(anim_id, 0, (f32) anim_blend);
        } else {
            pval_50 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(pval_50, u8* , 0x60) & 2) && (M2C_FIELD(pval_50, u8* , 0x42) == 0x36)) {
                set_hero_animation_pal(SelectHeroStateAnimation(0), 0, 4.0f);
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
        pval_61 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (pval_61 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(pval_61, f32* , 0x10) - M2C_FIELD(pval_21, f32* , 0x10), M2C_FIELD(pval_61, f32* , 0x14) - M2C_FIELD(pval_21, f32* , 0x14));
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
        pval_1 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (pval_1 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(pval_1, f32* , 0x10) - M2C_FIELD(pval_21, f32* , 0x10), M2C_FIELD(pval_1, f32* , 0x14) - M2C_FIELD(pval_21, f32* , 0x14));
            hero_steer_heading(0, 0.028800001f, 0.21600002f, 0.12566373f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vec_00, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        fval_26 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_00));
        ((Hero *)g_hero_state)->f[0xAB0/4] = fval_26;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 5e1f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (fval_26 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        ival_38 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (ival_38 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.54f, 0.032f);
            pval_46 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            fval_136 = mat_fast_helper_a(M2C_FIELD(pval_46, f32* , 0x10) - M2C_FIELD(pval_21, f32* , 0x10), M2C_FIELD(pval_46, f32* , 0x14) - M2C_FIELD(pval_21, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], fval_136) > 1.5707964f) {
                    fval_136 = FastAddRotations(fval_136, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = fval_136;
            hero_steer_heading(0, 0.0432f, 0.21600002f, 0.14660768f);
        } else if (ival_38 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.016800001f);
        }
        if ((math_solve_quadratic((s32) &local_float_e8, (s32) &local_float_ec, -0.008400001f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (local_float_e8 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = local_float_e8;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 17.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.0767945f);
        } else {
            turn = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_00)), vec_00[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn, 0.12915438f);
        }
        vec_20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        fval_27 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        vec_20[2] = 0;
        vec_20[1] = fval_27;
        FastVecAdd((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)vec_10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vec_20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vec_10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        fval_28 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (fval_28 < 25.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((25.0f - fval_28) * 0.011600001f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.20000002f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.006f);
        qcopy(vec_00, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)vec_00));
        FastVecAdd((s32) ((TI128*)vec_10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_10), (s32)((TI128*)vec_00));
        vec_scale_to_length((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vec_20), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(pval_21, u8* , 0x43) == 0x34)) {
            set_hero_animation_pal(0x35, 0xA, 1e1f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        pval_51 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        fval_81 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (pval_51 != 0) {
            pval_47 = M2C_FIELD(pval_51, void** , 0x68);
            if ((pval_47 != 0) && (M2C_FIELD(pval_47, s32* , 0x34) != 0)) {
                fval_137 = M2C_FIELD(pval_51, f32* , 0xF8);
                if (FastDiffRots(fval_137, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    fval_137 = FastAddRotations(fval_137, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), fval_137, (s32) (((void*)g_hero_state) + 0xAF8), 0.028800001f, 0.43200004f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.028800001f, 0.43200004f, 0.094247796f);
        FastVecSub((s32)((TI128*)vec_00), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), 1.0f);
        if (vec_00[2] < 0.23f) {
            vec_00[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)vec_60));
        vec_60[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_60));
        matrix_from_basis_rows((s32) ((TI128*)mat_70), (s32) ((TI128*)vec_20));
        transform_vector((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), (s32) ((TI128*)mat_70));
        vec_10[0] = -mat_fast_helper_a(square_root((vec_00[0] * vec_00[0]) + (vec_00[2] * vec_00[2])), vec_00[1]);
        fval_29 = mat_fast_helper_a(vec_00[2], vec_00[0]);
        vec_10[1] = fval_29;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), fval_29, (s32) (((void*)g_hero_state) + 0xA4), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), vec_10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        ival_69 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((ival_69 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x22) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                fval_138 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0042000003f;
                if (fval_138 > 0.10000001f) {
                    fval_138 = 0.10000001f;
                }
                vec_b0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * fval_138;
                fval_30 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * fval_138;
                pval_9 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vec_b0[2]) = 0;
                vec_b0[1] = fval_30;
                FastVecAdd((s32) pval_9, (s32) pval_9, (s32) ((TI128*)vec_b0));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                pval_38 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) pval_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    pval_30 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) pval_30, (s32) (((void*)g_hero_state) + 0x110), 0.016f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) pval_30) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vec_b0), (s32) pval_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) pval_30, (s32) pval_30, 0.0228f);
                    }
                }
                fval_68 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.0003f;
                FastVecScale((s32) ((TI128*)vec_b0), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vec_b0), (s32) ((TI128*)vec_b0), fval_68);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_b0));
            }
        }
        pval_48 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (pval_48 != 0) {
            pval_22 = M2C_FIELD(pval_48, void** , 0x68);
            pval_31 = ((void*)g_hero_state) + 0xF0;
            if (pval_22 != 0) {
                fval_31 = FastVecLength((s32) pval_31);
                fval_32 = M2C_FIELD(pval_22, f32* , 0xC);
                local_float_f0 = fval_31;
                if (fval_32 < fval_31) {
                    ApproachValue((s32) &local_float_f0, fval_32, 0.006f);
                    vec_scale_to_length((s32) pval_31, (s32) pval_31, local_float_f0);
                }
            }
        }
        fval_3 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        pval_44 = ((void*)g_hero_state) + 0x80;
        pval_43 = ((void*)g_hero_state) + 0xF0;
        vec_d0[0] = math_fast_sin_or_cos_a(fval_3) * 0.15f;
        fval_4 = math_fast_sin_or_cos_b(fval_3) * 0.15f;
        (*(s32*)&vec_d0[2]) = 0;
        vec_d0[1] = fval_4;
        FastVecAdd((s32) &vec_d0[0], (s32) &vec_d0[0], (s32) pval_44);
        FastVecAdd((s32) ((TI128*)vec_b0), (s32) &vec_d0[0], (s32) pval_43);
        FastVecSub((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_b0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vec_b0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vec_c0));
        FastVecSub((s32) pval_43, (s32) ((TI128*)vec_b0), (s32) &vec_d0[0]);
        fval_69 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        fval_70 = ((Hero *)g_hero_state)->f[0xAE4/4] - fval_69;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vec_c0))) {
            vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), fval_70);
            FastVecAdd((s32) pval_44, (s32) pval_44, (s32) ((TI128*)vec_c0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (ival_69 != 0)) {
            min_value = 0.28000003f;
            fval_5 = vec_length_xy((s32) pval_43);
            local_float_f4 = fval_5;
            if (fval_5 < min_value) {
                math_spring_float_to_goal((s32) &local_float_f4, (s32) (((void*)g_hero_state) + 0xAF4), min_value, 0.06768f, 0.43200004f, 0.0f);
                vec_b0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                fval_6 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vec_b0[2] = 0.0f;
                vec_b0[1] = fval_6 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) pval_43, (s32) pval_43, (s32) ((TI128*)vec_b0));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((fval_81 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            fval_71 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            ival_7 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (ival_7 != 0) {
                ival_72 = ival_7 == 1;
            } else {
                (*(TI128*)vec_b0) = ((Hero *)g_hero_state)->q[0x110/16];
                ival_72 = hero_get_speed_along_forward((s32) ((TI128*)vec_b0)) > 0.0f;
            }
            if (ival_72 != 0) {
                if (M2C_FIELD(pval_21, u8* , 0x43) != 0x35) {
                    set_hero_animation_pal(0x35, 6, 14.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    pval_49 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(pval_49, u8* , 0x42) == M2C_FIELD(pval_49, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, fval_71, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(pval_21, u8* , 0x43) != 0x35) {
                set_hero_animation_pal(0x35, 0x15, 7.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                pval_45 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(pval_45, u8* , 0x42) == M2C_FIELD(pval_45, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, fval_71, 0.5f, -1.0f);
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
            ival_16 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (ival_16 != 0) {
                fval_51 = vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), ival_16 + 0x10);
                ival_78 = 0;
                if ((((Hero *)g_hero_state)->b[0x1496] != 0) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->b[0x1495] != 0)) {
                    ival_78 = 1;
                }
                if (((fval_51 > 2.0f) && (fval_51 < 5.0f)) || (ival_78 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
                }
                hero_approach_speed(0.0016000001f, 0.0016000001f);
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            } else {
                hero_approach_speed(0.00080000004f, 0.00080000004f);
                pval_10 = ((void*)g_hero_state) + 0xF0;
                cam_set_view_space_vector_length((s32) pval_10, (s32) pval_10, ((Hero *)g_hero_state)->f[0x1B4/4]);
            }
        } else {
            ival_67 = 0;
            if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
                ival_67 = 1;
            }
            ival_17 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (ival_17 != 0) {
                FastVecSub((s32)((TI128*)vec_00), ival_17 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                fval_7 = cam_get_view_space_vector_length((s32)((TI128*)vec_00));
                if (((fval_7 > 2.0f) && (fval_7 < 5.0f)) || (ival_67 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
                }
                hero_approach_speed(0.010000001f, 0.010000001f);
                vec_scale_to_length((s32) ((TI128*)vec_10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
                cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_10));
            } else {
                if ((ival_67 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3a)) {
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
        fval_52 = ((Hero *)g_hero_state)->f[0x31C/4];
        fval_144 = 0.15400001f;
        if (fval_52 > 2.25f) {
            fval_144 = 0.07700001f;
        } else if (fval_52 > 1.8f) {
            fval_144 = 0.10780001f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(vec_00, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), -0.5f);
            vec_scale_to_length((s32) &vec_40[0], (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vec_10), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &vec_40[0]);
            vec_10[3] = 5627.925f;
            (*(u8*)((u8*)vec_20+9)) = 1;
            (*(u16*)((u8*)vec_20+10)) = 0x47;
            (*(u8*)((u8*)vec_20+8)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)vec_00), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vec_10));
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
        ival_39 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xc;
        if (ival_39 < 7) {
            pval_23 = ((void*)g_hero_state) + 0xF0;
            local_float_f8 = cam_get_view_space_height((s32) pval_23);
            ApproachValue((s32) &local_float_f8, fval_144, 0.060000002f);
            cam_set_view_space_height((s32) pval_23, (s32) pval_23, local_float_f8);
        } else if (ival_39 > lim3) {
            pval_32 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) pval_32, (s32) pval_32, 0.052f);
            if (cam_get_view_space_height((s32) pval_32) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            fval_139 = -0.74000007f;
            if (g_hero_l20_lock_flag_a != 0) {
                fval_139 = -1.4000001f;
            }
            if (cam_get_view_space_height((s32) pval_32) < fval_139) {
                cam_set_view_space_height((s32) pval_32, (s32) pval_32, fval_139);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l20_action_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ival_60 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x12);
        if (ival_60 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                ival_68 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    pval_24 = ((void*)g_hero_state) + 0xBC0;
                    fval_140 = hero_get_direction_angle_delta((s32) pval_24, 0);
                    fval_98 = hero_get_direction_angle_delta((s32) pval_24, 1);
                } else {
                    fval_140 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    fval_98 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (fval_98 < 4.3633237f) {
                    ival_68 = 1;
                }
                if (fval_140 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (fval_98 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (ival_68 != 0) {
                    hero_steer_heading(1, 0.08208001f, 0.28800002f, 0.33859393f);
                } else {
                    hero_steer_heading(0, 0.08208001f, 0.28800002f, 0.33859393f);
                }
            } else {
                    ival_61 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xa)) {
                        ival_61 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        ival_61 = 0;
                    }
                    if (ival_61 != 0) {
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
                fval_145 = 0.050000004f;
                fval_72 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&g_pad_pressed_flags) & 8) {
                    fval_145 = 0.060000002f;
                }
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(fval_72) * fval_145));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(fval_72) * fval_145));
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
        ival_18 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        pval_39 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_l20_action_table;
        if ((ival_18 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 3)) {
            pval_33 = ((void*)g_hero_state) + 0x80;
            fval_108 = vec_distance_xy(ival_18 + 0x10, (s32) pval_33);
            if ((*(s32*)&g_hero_l20_lock_flag_a) != 0) {
                fval_108 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) pval_33);
            }
            fval_108 = fval_108 - 0.5f;
            if (fval_108 < 0.0f) {
                fval_108 = 0.0f;
            }
            ival_40 = M2C_FIELD(pval_39, s32* , 4);
            if (ival_40 == 0) {
                fval_99 = 0.75f;
                fval_146 = 0.8f;
                fval_151 = 4.0f;
            } else if (ival_40 == 1) {
                fval_99 = 0.6f;
                fval_146 = 1.7f;
                fval_151 = 4.0f;
            } else {
                fval_99 = 1.3f;
                fval_146 = 1.7f;
                fval_151 = 1.9f;
            }
            fval_73 = fval_108 - fval_99;
            if (math_fabs(fval_73) < (fval_146 + 3.0f)) {
                fval_110 = fval_73 * 1.1111112f;
                if (fval_151 < fval_110) {
                    fval_110 = fval_151;
                }
                if (fval_110 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = fval_110;
                }
            }
        }
        ival_41 = M2C_FIELD(pval_39, s32* , 4);
        switch (ival_41) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.08800001f;
            }
            break;
        case 1:
            fval_53 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (fval_53 < 9.0f)) {
                if (fval_53 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.060000002f;
                } else if (fval_53 > 7.0f) {
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
            fval_100 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            fval_100 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        fval_54 = math_fabs(fval_100);
        if ((M2C_FIELD(pval_39, s32* , 4) == 1) && (fval_100 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (fval_54 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
    } else {
        ival_79 = 1;
        if ((M2C_FIELD(pval_39, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            ival_79 = 0;
        }
        if (ival_79 != 0) {
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
            pval_11 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) pval_11, (s32) pval_11, 0.0216f);
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
        ival_42 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (ival_42 > lim) {
            if (ival_42 < 0xf) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.36f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 7) && (((Hero *)g_hero_state)->f[0x184/4] < 0.40000004f)) {
            pval_25 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) pval_25);
            level_append_record_to_table((s32) pval_25, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) pval_25, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) pval_25, 0xC, 6, 0.0f);
        }
        selected = (((Hero *)g_hero_state)->i[0x1B8/4] > lim2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), selected);
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            ival_43 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((ival_43 > lim) && (ival_43 < 0xe) && (((Hero *)g_hero_state)->f[0x178/4] < 0.17000002f)) {
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
            ival_44 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((ival_44 > lim) && (ival_44 < 0x12)) {
                pval_40 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (pval_40 != 0) {
                    pval_34 = ((void*)g_hero_state) + 0x80;
                    vec_30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec_00), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vec_30));
                    (*(u8*)((u8*)vec_10+9)) = 3;
                    vec_00[3] = 5627.925f;
                    (*(u8*)((u8*)vec_10+8)) = 0;
                    fval_79 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vec_10+10)) = M2C_FIELD(pval_40, u16* , 0xAA);
                    vec_40[0] = math_fast_sin_or_cos_a(fval_79) * 0.8f;
                    fval_8 = math_fast_sin_or_cos_b(fval_79) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = fval_8;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) pval_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) pval_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) pval_40, (s32)((TI128*)vec_00)));
                    fval_79 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(fval_79) * 0.8f;
                    fval_10 = math_fast_sin_or_cos_b(fval_79) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = fval_10;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) pval_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) pval_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec_00)));
                    fval_79 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(fval_79) * 0.8f;
                    fval_12 = math_fast_sin_or_cos_b(fval_79) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = fval_12;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) pval_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) pval_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) pval_40, (s32)((TI128*)vec_00)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        hero_slide_along_wall_pal(1);
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
        ival_55 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            ival_55 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (ival_55 != 0)) {
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
            fval_74 = ReadPadFloatHistory(1);
            if ((FastDiffRots(fval_74, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            hero_field_a60 = ((void*)g_hero_state) + 0xA60;
            hero_build_move_impulse(0.7f, 0.0f);
            (*(TI128*)vec_00) = ((Hero *)g_hero_state)->q[0xA60/16];
            fval_55 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vec_00));
            ((Hero *)g_hero_state)->f[0x1B0/4] = fval_55;
            if (fval_55 < 0.014f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.014f;
            }
            vec_clear_128((s32) hero_field_a60);
        }
        fval_141 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim_pal();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.028800001f, 0.24480002f, 0.19896756f);
            } else {
                fval_83 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (fval_83 > 0.78539824f)) {
                    fval_141 = 0.0f;
                }
                hero_set_turn_rates_pal();
            }
        }
        hero_apply_mode_pose_offsets_pal();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            fval_155 = 0.119f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.03501409f);
            if (fval_155 < 0.0f) {
                fval_155 = 0.0f;
            }
            if (fval_155 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = fval_155;
            }
        }
        scale_c = fval_141 * 0.0072000003f;
        fval_142 = 0.008f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            fval_127 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (fval_127 > 1.0f) {
                fval_127 = 1.0f;
            }
            if (fval_127 < 0.2f) {
                fval_127 = 0.2f;
            }
            fval_142 = 0.0068000006f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * fval_127);
        }
        fval_84 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (fval_84 > 0.6108653f)) {
            fval_128 = 1.0f - (fval_84 * 0.4f);
            if (fval_128 < 0.0f) {
                fval_128 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * fval_128);
        }
        hero_approach_speed(scale_c, fval_142);
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
        hero_slide_along_wall_pal(1);
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
        pad_clamp_stick_to_unit_range((s32)((TI128*)vec_00), (s32) (((void*)g_hero_state) + 0x9F0), 0.24480002f);
        fval_147 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.024434613f) * vec_00[0];
        if ((*(s32*)&g_hero_l20_lock_flag_a) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x32) {
                fval_147 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.6f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, fval_147);
        }
        hero_approach_speed(0.040000003f, 0.006f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&g_hero_l20_lock_flag_a) != 0) {
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0xA00), 0.057600003f, 0.43200004f, 0.15f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.057600003f, 0.43200004f, 0.15f);
        }
        FastVecScale((s32) ((TI128*)vec_10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32)(g_hero_state + 0xE0));
        ival_29 = coll_process_hit(0.57f, (s32) ((TI128*)vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (ival_29 != 0) {
            FastVecScale((s32) ((TI128*)vec_20), (s32)(g_hero_state + 0x110), 7.0f);
            for (ival_64 = 0; ival_64 < ival_29; ival_64++) {
                if (moby_is_in_special_class_range(((s32 *)g_special_moby_table)[ival_64]) != 0) {
                    part_queue_impact_effect(((s32 *)g_special_moby_table)[ival_64], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.024480002f, 0.43200004f);
        cam_set_limits_third(0.036000002f, 0.43200004f);
        cam_set_limits_fourth(0.0432f, 0.38880002f);
        fval_156 = fval_147 * 27.0f;
        if (fval_156 > 1.7f) {
            fval_156 = 1.7f;
        } else if (fval_156 < -1.7f) {
            fval_156 = -1.7f;
        }
        fval_13 = fval_156 * 0.5f;
        ((Hero *)g_hero_l20_state_alias)->f[0x60/4] = (f32) -fval_156;
        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = fval_13;
        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = fval_13;
        break;
    case 0x2E:                                      /* switch 1 */
        hero_steer_reference_point_pal();
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        ival_98 = M2C_FIELD(pval_21, u8* , 0x43);
        if (ival_98 == 0x37) {
            fval_101 = 1.4f;
            fval_143 = ((Hero *)g_hero_state)->f[0x1A8/4];
            if ((fval_143 > 1.4f) || (fval_101 = -1.4f, (fval_143 < -1.4f))) {
                fval_143 = fval_101;
            }
            ((Hero *)g_hero_l20_state_alias)->f[0x60/4] = (f32) (fval_143 * -0.14f);
            ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = (f32) (fval_143 * 0.3f);
            ((Hero *)g_hero_l20_state_alias)->f[0x1C0/4] = (f32) (fval_143 * -0.22f);
            ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = (f32) (fval_143 * 0.4f);
            ((Hero *)g_hero_l20_state_alias)->f[0x274/4] = (f32) (math_fabs(fval_143) * -0.09f);
            ((Hero *)g_hero_l20_state_alias)->f[0x270/4] = (f32) (math_fabs(fval_143) * 0.08f);
        } else if (ival_98 == 0x66) {
            fval_80 = FastAddRotations(fast_subtract_rotations(mat_fast_helper_a(((Hero *)g_hero_state)->f[0x110/4], ((Hero *)g_hero_state)->f[0x114/4]), ((Hero *)g_hero_state)->f[0x98/4]), 3.1415927f);
            fval_148 = ((Hero *)g_hero_state)->f[0x174/4] * 5.8177648f;
            if (fval_148 > 0.43633235f) {
                fval_148 = 0.43633235f;
            }
            fval_57 = math_fast_sin_or_cos_a(fval_80) * fval_148;
            fval_14 = -math_fast_sin_or_cos_b(fval_80);
            ((Hero *)g_hero_l20_state_alias)->f[0x114/4] = fval_57;
            ((Hero *)g_hero_l20_state_alias)->f[0x110/4] = (f32) (fval_14 * fval_148);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            fval_111 = 0.010000001f;
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x110), fval_111);
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.060000002f);
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        ival_45 = (*(s32*)&g_current_map_index);
        if (ival_45 == 0 || (ival_45 == 1 && g_hero_sound_flag_4 == 0)) {
            snd_update_slot_object(2, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x13);
        }
        ival_74 = g_current_map_index;
        if ((u32) ival_74 < 2U) {
            EmitHeroRandomizedMotionEffects_pal(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects_pal(4, 2, 0);
            vec_00[0] = ((Hero *)g_hero_state)->f[0x80/4] + math_random_float_range(-0.25f, 0.25f);
            vec_00[1] = ((Hero *)g_hero_state)->f[0x84/4] + math_random_float_range(-0.25f, 0.25f);
            vec_00[2] = ((Hero *)g_hero_state)->f[0x88/4] + math_random_float_range(-0.1f, 0.4f);
            FastVecScale((s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x110), 0.9f);
            vec_10[0] += math_random_float_range(-0.014f, 0.014f);
            vec_10[1] += math_random_float_range(-0.014f, 0.014f);
            vec_10[2] = M2C_BITWISE(f32, vec_10[2]) + math_random_float_range(0.020000001f, 0.040000003f);
            part_spawn_two_point_effect((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), math_random_float_range(37800.0f, 75600.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xB40/4];
        fval_58 = ((Hero *)g_hero_state)->f[0x98/4];
        hero_steer_heading(0, 0.04752f, 0.43200004f, 0.08377582f);
        fval_149 = FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], fval_58);
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        hero_shrink_vector_by_amount(0.0028000001f);
        fval_15 = ((Hero *)g_hero_state)->f[0x118/4] - 0.020000001f;
        ((Hero *)g_hero_state)->f[0xF8/4] = fval_15;
        if (fval_15 > -0.016f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.016f;
        }
        if (fval_149 > 0.027925273f) {
            fval_149 = 0.027925273f;
        }
        fval_59 = fval_149 * 9.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), fval_59 * 0.5f, (s32) (((void*)g_hero_state) + 0xB54), 0.007f, 0.17f, 0.024434613f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), -((Hero *)g_hero_state)->f[0xB44/4], (s32) (((void*)g_hero_state) + 0xB58), 0.050400004f, 0.43200004f, 0.03839725f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = (f32) (fval_59 * 2.1f);
        ((Hero *)g_hero_l20_state_alias)->f[0x110/4] = (f32) (fval_59 * 3.5f);
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        ival_87 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (((u32) (ival_87 - 0x28) >= 2U) && (ival_87 != 0x3E)) {
            snd_update_slot_object(0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        } else {
            ival_22 = ((Hero *)g_hero_state)->i[0x242C/4];
            if (ival_22 != -1) {
                pval_12 = (ival_22 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(pval_12, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(pval_12, u8* , 0x74) != 0) {
                        snd_stop_voice(ival_22);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x242C/4] = -1;
        }
        ival_88 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((ival_88 == 0x27) || (ival_88 == 0x2A)) {
            qcopy(vec_00, &((Hero *)g_hero_state)->q[0x80/16]);
            fval_60 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.0f, 0.52359885f));
            fval_77 = math_random_float_range(0.080000006f, 0.14000002f);
            vec_10[0] = math_fast_sin_or_cos_a(fval_60) * fval_77;
            fval_16 = math_fast_sin_or_cos_b(fval_60) * fval_77;
            vec_10[2] = 0.0f;
            vec_10[1] = fval_16;
            vec_10[2] = math_random_float_range(0.060000002f, 0.10000001f);
            vec_10[3] = -0.012f;
            part_spawn_white_flash_pal((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), 0, -1.0f);
        }
        pval_20 = ((Hero *)g_hero_state)->ptr[0x1248/4];
        local_int_11c = 0;
        ival_27 = (((LevelInfo *)g_item_l20_record_table)[g_item_slot_to_record[(s32)pval_20]].x1C != 0);
        if ((s32)pval_20 == 0xD) {
            ival_27 = 0;
        }
        if (ival_27 != 0) {
            local_int_11c = ((Hero *)g_hero_state)->b[0x22BA] != 0;
        }
        pval_35 = ((void*)g_hero_state) + 0x80;
        find_nearest_path_point(((Hero *)g_hero_state)->i[0x630/4], (s32) pval_35, (s32) (((void*)g_hero_state) + 0x5D0), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)g_hero_state)->i[0x664/4], (s32) pval_35, (s32) (((void*)g_hero_state) + 0x610), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        ival_63 = 0;
        if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0699999f) {
            ival_89 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((ival_89 != 0x28) && (ival_89 != 0x3E) && (((Hero *)g_hero_state)->i[0x660/4] == 0)) {
                ival_63 = ((Hero *)g_hero_state)->i[0x1BC/4] >= 0x1a;
            }
        }
        if (ival_63 != 0) {
            ((Hero *)g_hero_state)->i[0x6C8/4] = (s32) (((Hero *)g_hero_state)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)g_hero_state)->i[0x6C8/4] = 0;
        }
        ival_30 = ((Hero *)g_hero_state)->i[0x640/4];
        if (((ival_30 != 0) && ((((Hero *)g_hero_state)->i[0x640/4] = ival_30 + 1) != 0)) || (ival_63 != 0)) {
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x120/16]);
            pval_52 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(pval_52, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion_pal();
            } else {
                if (vec_length_xy((s32)(g_hero_state + 0xF0)) < 0.050000004f) {
                    ApproachValue((s32)(g_hero_state + 0xF0) + 0xC4, 0.080000006f, 0.016f);
                    M2C_FIELD(pval_52, f32* , 0xF0) = math_fast_sin_or_cos_a(M2C_FIELD(pval_52, f32* , 0x64C)) * M2C_FIELD(pval_52, f32* , 0x1B4);
                    M2C_FIELD(pval_52, f32* , 0xF4) = math_fast_sin_or_cos_b(M2C_FIELD(pval_52, f32* , 0x64C)) * M2C_FIELD(pval_52, f32* , 0x1B4);
                }
                M2C_FIELD(pval_52, f32* , 0xF8) = (f32) (M2C_FIELD(pval_52, f32* , 0xF8) - 0.0088f);
            }
        } else {
            fval_40 = (f32) ((Hero *)g_hero_state)->i[0x648/4];
            fval_132 = ((Hero *)g_hero_state)->f[0x644/4] * fval_40;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                fval_132 = ((Hero *)g_hero_state)->f[0x69C/4] * fval_40;
            }
            Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32)((TI128*)vec_00), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], fval_132);
            if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x664/4], (s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], fval_132);
            }
            if (((Hero *)g_hero_state)->i[0x1BC/4] >= 0x4c) {
                fval_61 = ((Hero *)g_hero_state)->f[0x170/4] * 25.333334f;
                qcopy(vec_20, &((Hero *)g_hero_state)->q[0x80/16]);
                local_int_fc = ((Hero *)g_hero_state)->i[0x634/4];
                local_float_100 = ((Hero *)g_hero_state)->f[0x638/4];
                ival_25 = Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vec_20), (s32) &local_int_fc, (s32) &local_float_100, ((Hero *)g_hero_state)->i[0x654/4], fval_61);
                qcopy(vec_30, &((Hero *)g_hero_state)->q[0x80/16]);
                local_int_fc = ((Hero *)g_hero_state)->i[0x634/4];
                local_float_100 = ((Hero *)g_hero_state)->f[0x638/4];
                if ((((ival_25 | Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vec_30), (s32) &local_int_fc, (s32) &local_float_100, ((Hero *)g_hero_state)->i[0x654/4], fval_61 + 0.1f)) == 0) || (((Hero *)g_hero_state)->i[0x654/4] != 0)) && (((Hero *)g_hero_state)->u[0x2294/4] == 0x27)) {
                    fval_133 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x64C/4], mat_fast_helper_a(vec_30[0] - vec_20[0], vec_30[1] - vec_20[1])) * 0.47f;
                    if (fval_133 > 0.78539824f) {
                        fval_133 = 0.78539824f;
                    }
                    if (fval_133 < -0.78539824f) {
                        fval_133 = -0.78539824f;
                    }
                    cam_set_limits_first(0.03f, 0.2f);
                    if (((Hero *)g_hero_state)->i[0x65C/4] != 0) {
                        (*(f32*)&g_hero_l20_signed_scalar) = -fval_133;
                    } else {
                        (*(f32*)&g_hero_l20_signed_scalar) = fval_133;
                    }
                }
            }
            ival_90 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((ival_90 != 0x28) && (ival_90 != 0x3E) && (ival_90 != 0x29)) {
                (*(f32*)&g_hero_speed_blend_value) = mat_fast_helper_a(vec_length_xy((s32) (((void*)g_hero_state) + 0x110)), ((Hero *)g_hero_state)->f[0x118/4]);
            }
            if (ival_27 != 0) {
                scale_a = 0.43200004f;
                cam_set_limits_fourth(0.024480002f, scale_a);
                cam_set_limits_second(0.03888f, scale_a);
                cam_set_limits_third(0.03888f, scale_a);
                ival_19 = ((Hero *)g_hero_state)->i[0x6A8/4];
                if (ival_19 != 0) {
                    FastVecSub((s32) ((TI128*)vec_20), ival_19 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((void*)g_hero_state) + 0x40));
                    fval_33 = mat_fast_helper_a(vec_20[0], vec_20[1]);
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        fval_33 = fast_subtract_rotations(fval_33, 1.5707965f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = (f32) (fval_33 * 0.3f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = (f32) (fval_33 * 0.2f);
                    } else {
                        fval_33 = fast_subtract_rotations(fval_33, -1.5707965f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = (f32) (fval_33 * 0.3f);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = (f32) (fval_33 * 0.5f);
                    }
                } else {
                    ival_96 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43);
                    if (ival_96 == 0x31) {
                        fval_150 = 0.58823526f;
                        fval_103 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        fval_134 = 0.73303837f;
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = fval_103;
                        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = FastAddRotations(fval_134, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_150);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = FastAddRotations(fval_134, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_150);
                    } else if (ival_96 == 0x48) {
                        fval_150 = 0.5f;
                        fval_103 = FastAddRotations(0.13962635f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        fval_134 = -0.06981318f;
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = fval_103;
                        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = FastAddRotations(fval_134, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_150);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = FastAddRotations(fval_134, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_150);
                    } else if (ival_96 == 0x47) {
                        fval_150 = 0.58823526f;
                        fval_103 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        fval_134 = 0.73303837f;
                        ((Hero *)g_hero_l20_state_alias)->f[0x278/4] = fval_103;
                        ((Hero *)g_hero_l20_state_alias)->f[0x118/4] = FastAddRotations(fval_134, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_150);
                        ((Hero *)g_hero_l20_state_alias)->f[0x1C8/4] = FastAddRotations(fval_134, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_150);
                    }
                }
            }
            ival_32 = path_advance_index(((Hero *)g_hero_state)->i[0x630/4], ((Hero *)g_hero_state)->i[0x634/4], ((Hero *)g_hero_state)->i[0x648/4], ((Hero *)g_hero_state)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)vec_20), (s32) &((TI128 *)((Hero *)g_hero_state)->ptr[0x630/4])[ival_32 + 1], (s32)((TI128*)vec_00));
            if (FastVecLength((s32) ((TI128*)vec_20)) < 0.001f) {
                if (((Hero *)g_hero_state)->i[0x634/4] == ival_32) {
                    ((Hero *)g_hero_state)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)g_hero_state)->f[0x64C/4] = mat_fast_helper_a(vec_20[0], vec_20[1]);
                ((Hero *)g_hero_state)->f[0x650/4] = mat_fast_helper_a(vec_length_xy((s32) ((TI128*)vec_20)), M2C_BITWISE(f32, vec_20[2]));
block_807:
                ((Hero *)g_hero_state)->f[0x1A0/4] = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], ((Hero *)g_hero_state)->f[0x658/4]);
                hero_steer_heading(0, 0.0216f, 0.21600002f, 0.12566373f);
                ival_91 = ((Hero *)g_hero_state)->u[0x2294/4];
                if ((((u32) (ival_91 - 0x28) < 2U) && (((Hero *)g_hero_state)->b[0x49C] == 0)) || (ival_91 == 0x3E)) {
                    if (((Hero *)g_hero_state)->i[0x694/4] != 0) {
                        fval_20 = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x620/4] - ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x624/4] - ((Hero *)g_hero_state)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], fval_20) < 1.5707965f) {
                            ((Hero *)g_hero_state)->f[0x1A0/4] = fval_20;
                            hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.12566373f);
                        }
                    }
                    if ((((Hero *)g_hero_state)->i[0x660/4] != 0) && (((Hero *)g_hero_state)->i[0x678/4] < 0x29)) {
                        FastVecSub((s32) ((TI128*)vec_20), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_10));
                        ival_33 = ((Hero *)g_hero_state)->i[0x678/4] + 1;
                        ((Hero *)g_hero_state)->i[0x678/4] = ival_33;
                        FastVecScale((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (f32) ival_33 * 0.025f);
                        fval_62 = (f32) (((Hero *)g_hero_state)->i[0x678/4] - 1) * 0.025f;
                        FastVecSub((s32) ((TI128*)vec_30), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_10));
                        FastVecScale((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_30), fval_62);
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + (M2C_BITWISE(f32, vec_20[2]) - vec_30[2]));
                        FastVecAdd((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_10), (s32) ((TI128*)vec_20));
                        FastVecSub((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_30), (s32) (((void*)g_hero_state) + 0x80));
                        ((Hero *)g_hero_state)->f[0xF0/4] = vec_20[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = vec_20[1];
                        FastVecSub((s32) ((TI128*)vec_20), (s32)((TI128*)vec_00), (s32) (((void*)g_hero_state) + 0x5D0));
                        fval_86 = ((Hero *)g_hero_state)->f[0x5D8/4];
                        fval_41 = ((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, vec_20[2]);
                        ((Hero *)g_hero_state)->f[0x88/4] = fval_41;
                        if (fval_41 < fval_86) {
                            if (((Hero *)g_hero_state)->i[0x678/4] < 0x29) {
                                if (fval_41 < fval_86) {
                                    ((Hero *)g_hero_state)->f[0x88/4] = fval_86;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)vec_20), (s32)((TI128*)vec_00), (s32)(g_hero_state + 0x5D0));
                        ((Hero *)g_hero_state)->f[0xF0/4] = vec_20[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = vec_20[1];
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, vec_20[2]));
                        FastVecSub((s32) ((TI128*)vec_30), (s32)(g_hero_state + 0x5D0), (s32)(g_hero_state + 0x80));
                        vec_30[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)vec_30)) > 0.020000001f) {
                            vec_scale_to_length((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_30), 0.020000001f);
                        }
                        ((Hero *)g_hero_state)->f[0x80/4] = (f32) (((Hero *)g_hero_state)->f[0x80/4] + vec_30[0]);
                        ((Hero *)g_hero_state)->f[0x84/4] = (f32) (((Hero *)g_hero_state)->f[0x84/4] + vec_30[1]);
                    }
                    if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.0092f);
                    } else {
                        ApplyHeroGravityAndJumpMotion_pal();
                    }
                } else {
                    ((Hero *)g_hero_state)->i[0x660/4] = 0;
                    fval_104 = 0.0f;
                    if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) && (local_int_11c != 0)) {
                        hero_resolve_stick_direction(1.0f, 0);
                        fval_104 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1A0/4], ((Hero *)g_hero_state)->f[0x64C/4]);
                        if (fval_104 > 0.78539824f) {
                            fval_104 = 0.78539824f;
                        } else if (fval_104 < -0.78539824f) {
                            fval_104 = -0.78539824f;
                        }
                    }
                    math_approach_with_velocity((s32)(g_hero_state + 0x6A0), fval_104, (s32)(g_hero_state + 0x6A4), 0.0216f, 0.43200004f, 0.0f, 0);
                    ApproachValue((s32)(g_hero_state + 0x680), 0.24000001f, 0.006f);
                    local_int_104 = ((Hero *)g_hero_state)->i[0x634/4];
                    local_float_108 = ((Hero *)g_hero_state)->f[0x638/4];
                    scale_b = 0.3f;
                    qcopy(vec_20, &((Hero *)g_hero_state)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vec_20), (s32) &local_int_104, (s32) &local_float_108, ((Hero *)g_hero_state)->i[0x654/4], scale_b);
                    fval_17 = mat_fast_helper_a(vec_distance_xy((s32)(g_hero_state + 0x5D0), (s32) ((TI128*)vec_20)), M2C_BITWISE(f32, vec_20[2]) - ((Hero *)g_hero_state)->f[0x5D8/4]);
                    if (fval_17 > 0.0f) {
                        fval_112 = fval_17 * -0.09549296f;
                        if (fval_17 > 0.26179942f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 0;
                        } else if ((fval_17 < 0.13962635f) && (((Hero *)g_hero_state)->i[0x67C/4] == 0)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    } else {
                        fval_112 = -fval_17 * 0.4583662f;
                        if (fval_17 < -0.19198623f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 1;
                        } else if ((fval_17 > -0.122173056f) && (((Hero *)g_hero_state)->i[0x67C/4] == 1)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < fval_112) {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), fval_112, 0.0032000002f);
                    } else {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), fval_112, 0.00080000004f);
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] > 0.24000001f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = 0.24000001f;
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < -0.050000004f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = -0.050000004f;
                    }
                    fval_18 = ((Hero *)g_hero_state)->f[0x680/4] + ((Hero *)g_hero_state)->f[0x674/4];
                    ((Hero *)g_hero_state)->f[0x644/4] = fval_18;
                    if (fval_18 < 0.0f) {
                        ((Hero *)g_hero_state)->f[0x644/4] = 0.0f;
                    }
                    pval_26 = ((void*)g_hero_state) + 0x5D0;
                    FastVecSub((s32) (((void*)g_hero_state) + 0xF0), (s32)((TI128*)vec_00), (s32) pval_26);
                    pval_41 = ((void*)g_hero_state) + 0x80;
                    FastVecSub((s32) ((TI128*)vec_20), (s32) pval_26, (s32) pval_41);
                    local_float_10c = -FastVecLength((s32) ((TI128*)vec_20));
                    math_spring_float_to_goal((s32) &local_float_10c, (s32) (((void*)g_hero_state) + 0x6AC), 0.0f, 0.0432f, 0.43200004f, 0.14000002f);
                    fval_19 = FastVecLength((s32) ((TI128*)vec_20));
                    if (fval_19 < ((Hero *)g_hero_state)->f[0x6AC/4]) {
                        ((Hero *)g_hero_state)->f[0x6AC/4] = fval_19;
                    }
                    fval_34 = ((Hero *)g_hero_state)->f[0x6AC/4];
                    if (fval_34 < fval_19) {
                        vec_scale_to_length((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), fval_34);
                    }
                    FastVecAdd((s32) pval_41, (s32) pval_41, (s32) ((TI128*)vec_20));
                    fval_89 = ((Hero *)g_hero_state)->f[0x88/4];
                    fval_85 = ((Hero *)g_hero_state)->f[0x5D8/4];
                    if (fval_89 < fval_85) {
                        if (((Hero *)g_hero_state)->f[0x31C/4] < 1.0f) {
                            if (fval_89 < fval_85) {
                                ((Hero *)g_hero_state)->f[0x88/4] = fval_85;
                            }
                        }
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x11) {
                        fval_21 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.3490659f, 0.6108653f));
                        vec_50[0] = math_fast_sin_or_cos_a(fval_21);
                        vec_50[1] = math_fast_sin_or_cos_b(fval_21);
                        vec_50[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)vec_20), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &vec_50[0]);
                        qcopy(vec_60, &((Hero *)g_hero_state)->q[0x80/16]);
                        vec_60[2] += 0.6f;
                        coll_process_hit(1.0f, (s32) ((TI128*)vec_60), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vec_20));
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
        FastVecSub((s32) ((TI128*)vec_60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &vec_40[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)vec_60));
        } else {
            FastVecCross((s32) &vec_40[0], (s32) ((TI128*)vec_60), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &vec_40[0], (s32) &vec_40[0], 0.2f);
        FastVecAdd((s32) &vec_50[0], (s32)(g_hero_state + 0x80), (s32) &vec_40[0]);
        if ((hero_find_ledge_grab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab_pal((s32) &vec_50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec_00)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec_00), (s32)(g_hero_state + 0x80));
            ival_76 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            ival_80 = (s32)g_hero_state_machine_bytes;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(ival_76 + ival_80) * 0.5f);
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
            fval_113 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                fval_113 = 0.43633235f;
            }
            qcopy(vec_00, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &vec_00[1], fval_113, (s32) (((void*)g_hero_state) + 0xA4), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            math_approach_with_velocity((s32)((TI128*)vec_00), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_update_target_speed_pal();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_airborne_steering_pal();
        }
        pval_60 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets_pal();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) pval_60, (s32) pval_60, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) pval_60) < -1.0000001f) {
            cam_set_view_space_height((s32) pval_60, (s32) pval_60, -1.0000001f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        pval_2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0034906592f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0034906592f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) pval_2, (s32) pval_2, vec_length_xy((s32) pval_2) * 0.88f);
        hero_apply_mode_transform((s32) pval_2, (s32) pval_2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) pval_2) < -1.0000001f) {
            cam_set_view_space_height((s32) pval_2, (s32) pval_2, -1.0000001f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        angle = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.0003490659f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, angle), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        ival_56 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            ival_56 = 0;
        }
        if (ival_56 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.120000005f);
            pval_13 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) pval_13, (s32) pval_13, 0.036000002f);
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
        fval_35 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x4b) && (fval_35 < 0.0f) && (fval_87 = ((Hero *)g_hero_state)->f[0x31C/4], (fval_87 < 1.2f))) {
            fval_91 = (fval_87 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (fval_91 < 0.0f) {
                fval_91 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), fval_35 * fval_91);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.03888f, 0.43200004f, 0.10000001f);
            }
        } else if (fval_35 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&g_camera_l20_view_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets_pal();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.24000001f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.03888f, 0.43200004f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.10471977f);
        fval_114 = 0.002f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            fval_114 = 0.00080000004f;
        }
        ApproachHeroVelocity_pal(fval_114);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            ival_23 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (ival_23 != -1) {
                pval_14 = (ival_23 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(pval_14, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(pval_14, u8* , 0x74) != 0)) {
                    snd_stop_voice(ival_23);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            ival_24 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (ival_24 != -1) {
                pval_15 = (ival_24 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(pval_15, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(pval_15, u8* , 0x74) != 0)) {
                    snd_stop_voice(ival_24);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        fval_152 = 0.060000002f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            fval_152 = 0.10000001f;
        }
        fval_153 = 0.72f;
        fval_42 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            fval_152 = 0.15400001f;
            fval_153 = 0.98640007f;
        }
        if (fval_42 != 0.0f) {
            fval_153 = fval_42;
        }
        pval_27 = ((void*)g_hero_state) + 0xF0;
        local_float_110 = cam_get_view_space_height((s32) pval_27);
        hero_resolve_stick_direction(fval_152, 0);
        hero_steer_heading(0, 0.036000002f, 0.43200004f, 0.25132746f);
        hero_approach_speed(0.006f, 0.0028000001f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets_pal();
        cam_project_vector_onto_view_plane((s32) pval_27, (s32) pval_27);
        math_spring_float_to_goal((s32) &local_float_110, (s32) (((void*)g_hero_state) + 0xA98), -fval_152 * fval_153, 0.036000002f, 0.43200004f, 0.34000003f);
        hero_apply_mode_transform((s32) pval_27, (s32) pval_27, -local_float_110);
        fval_36 = ((Hero *)g_hero_state)->f[0x88/4];
        if (fval_36 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), fval_36, 0.080000006f);
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
            fval_43 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((fval_43 >= 4.0f) && (fval_43 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects_pal(7, 0, 0);
            }
        }
        ival_5 = ((Hero *)g_hero_state)->h[0x4AC/2];
        ival_20 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (ival_20 == ival_5) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((ival_20 < ival_5) && (ival_92 = ((Hero *)g_hero_state)->u[0x2294/4], (ival_92 != 0xB)) && (ival_92 != 0x10) && (ival_92 != 0xC) && (ival_92 != 0x11) && (ival_92 != 0x1B) && (ival_92 != 0x89) && (ival_92 != 0x48))) {
            if (((Hero *)g_hero_state)->h[0x528/2] != 0) {
                hero_steer_reference_point_pal();
                if ((((Hero *)g_hero_state)->u[0x2294/4] == 0xA) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x8) && (((Hero *)g_hero_state)->f[0x178/4] < 0.14000002f)) {
                    ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.014f));
                    ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.014f));
                    qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
                }
            } else {
                hero_steer_heading(0, 0.0216f, 0.28800002f, 0.30019668f);
                fval_63 = ((Hero *)g_hero_state)->f[0x1B4/4];
                if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                    ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (fval_63 * 0.4f);
                }
                if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                    hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
                } else {
                    hero_compute_push_direction(99999.0f);
                }
                ((Hero *)g_hero_state)->f[0x1B4/4] = fval_63;
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
                    ival_46 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (ival_46 < (((Hero *)g_hero_state)->h[0x4AC/2] + 3)) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) ival_46 * 0.0064000003f);
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                    ival_47 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (ival_47 < 0x1c) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) ival_47 * 0.021200001f);
                    }
                }
                if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0x8) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                    qcopy(vec_00, &((Hero *)g_hero_state)->q[0x80/16]);
                    cam_offset_point_in_view_space((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), 0.5f);
                    cam_offset_point_by_side_direction((s32) ((TI128*)vec_10), (s32)((TI128*)vec_00), 0.95f);
                    if (CollLine((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)g_hero_state)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            hero_update_airborne_steering_pal();
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
                pval_28 = ((void*)g_hero_state) + 0xF0;
                fval_92 = vec_length_xy((s32) pval_28);
                if (fval_92 > 0.07400001f) {
                    fval_92 = 0.07400001f;
                }
                vec_fast_normalize_helper((s32) pval_28, (s32) pval_28, fval_92);
            }
        }
        fval_44 = ((Hero *)g_hero_state)->f[0x318/4];
        fval_88 = ((Hero *)g_hero_state)->f[0x490/4];
        if (fval_88 < fval_44) {
            fval_22 = fval_88 + 0.120000005f;
            ((Hero *)g_hero_state)->f[0x490/4] = fval_22;
            if (fval_44 < fval_22) {
                ((Hero *)g_hero_state)->f[0x490/4] = fval_44;
            }
        }
        fval_45 = ((Hero *)g_hero_state)->f[0x88/4];
        if (fval_45 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = fval_45;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xf))) {
            fval_46 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (fval_46 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = fval_46;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets_pal();
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters_pal();
        }
        ival_93 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((ival_93 == 0x10) || (ival_93 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xb) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 8) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vec_00), 1, 0.8f, 0.0f, 0.3f);
                    ival_34 = coll_process_hit(0.9f, (s32)((TI128*)vec_00), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (ival_34 != 0) {
                        FastVecScale((s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (ival_65 = 0; ival_65 < ival_34; ival_65++) {
                            if (moby_is_in_special_class_range(((s32 *)g_special_moby_table)[ival_65]) != 0) {
                                part_queue_impact_effect(((s32 *)g_special_moby_table)[ival_65], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), 1.0f);
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
        fval_135 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        fval_93 = 0.0016000001f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9)) {
            fval_93 = 0.004f;
        }
        fval_135 = fval_135 - fval_93;
        if (fval_135 < 0.0f) {
            fval_135 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        pval_59 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) pval_59, (s32) pval_59, fval_135);
        hero_apply_mode_transform((s32) pval_59, (s32) pval_59, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.46000004f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec_00), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_00[0], vec_00[1]);
        fval_24 = vec_length_xy((s32)((TI128*)vec_00));
        if (fval_24 > 0.2f) {
            hero_view = (Hero *)g_hero_state;
            hero_view->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_00[0], vec_00[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = fval_24;
            if (fval_24 < g_hero_l20_speed_params[0][2]) {
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
        speed = 1.0f;
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
        hero_approach_speed(speed * 0.0072000003f, 0.008f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_slide_along_wall_pal(1);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        }
        {
            s32 found, k, m;
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0xE0/16]);
            found = coll_process_hit(((Hero *)g_hero_state)->f[0x264/4] + 0.2f, (s32)((TI128*)vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
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
        FastVecSub((s32)((TI128*)vec_00), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)vec_00), (s32)(g_hero_state + 0x160)) < 0.0f) {
            vec_clear_128((s32)(g_hero_state + 0x160));
        }
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.0108f);
        hero_slide_along_wall_pal(0);
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
        hero_slide_along_wall_pal(0);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.0216f);
        break;
    case 0x4D:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        pval_53 = (s32) &g_hero_l20_action_table[((Hero *)g_hero_state)->h[0xBFC/2]];
        ival_10 = M2C_FIELD(pval_53, s32* , 4);
        switch (ival_10) {
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
            fval_47 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((f32) M2C_FIELD(pval_53, s32* , 0x1C) <= fval_47) {
                if (fval_47 <= (f32) M2C_FIELD(pval_53, s32* , 0x20)) {
                    ival_26 = ((M2C_FIELD(pval_53, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], ival_26, (s32) ((TI128*)vec_10));
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], ival_26 | 1, (s32) ((TI128*)vec_20));
                    FastVecAdd((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), (s32) ((TI128*)vec_20));
                    FastVecScale((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), 0.5f);
                    coll_sweep_from_object((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec_00), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
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
        fval_1 = 0.0072000003f;
        pval_3 = ((void*)g_hero_state) + 0x130;
        hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) pval_3, fval_1);
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
        fval_124 = 0.19896756f;
        fval_116 = 0.04752f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            fval_124 = 0.23387417f;
            fval_116 = 0.053280003f;
        }
        hero_steer_heading(0, fval_116, 0.21600002f, fval_124);
        hero_approach_speed(0.0072000003f, 0.008f);
        if (((Hero *)g_hero_state)->f[0x174/4] < 0.014f) {
            ((Hero *)g_hero_state)->b[0x40C] = 1U;
            if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)g_hero_state)->b[0x40F] = 1U;
            }
        }
        fval_65 = ReadPadFloatHistory(0);
        if ((FastDiffRots(fval_65, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                fval_157 = 0.060000002f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.025464792f);
                if (fval_157 < 0.0f) {
                    fval_157 = 0.0f;
                }
                if (fval_157 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = fval_157;
                }
            }
        }
        if (((Hero *)g_hero_state)->b[0x40C] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1A0/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        hero_slide_along_wall_pal(1);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        }
        break;
    case 0x42:                                      /* switch 1 */
        fval_37 = vec_length_xy((s32)(g_hero_state + 0xF0));
        if (*(s16 *)(g_hero_state + 0x34E) != 0) {
            fval_37 = fval_37 * 0.98800004f;
        } else {
            fval_37 = fval_37 * 0.90400004f;
        }
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), fval_37);
        pval_54 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
        M2C_FIELD(pval_54, s32* , 0xF8) = 0;
        if (M2C_FIELD(pval_54, s16* , 0x34E) != 0) {
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
        FastVecSub((s32) ((TI128*)vec_60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &vec_40[0], (s32) (((void*)g_hero_state) + 0x2C0), (s32) ((TI128*)vec_60));
        } else {
            FastVecCross((s32) &vec_40[0], (s32) ((TI128*)vec_60), (s32) (((void*)g_hero_state) + 0x2C0));
        }
        vec_scale_to_length((s32) &vec_40[0], (s32) &vec_40[0], 0.2f);
        FastVecAdd((s32) &vec_50[0], (s32)(g_hero_state + 0x80), (s32) &vec_40[0]);
        if ((hero_find_ledge_grab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab_pal((s32) &vec_50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec_00)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec_00), (s32)(g_hero_state + 0x80));
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), g_hero_l20_speed_scale_table[FloatToInt(((Hero *)g_hero_state)->f[0xC38/4])] * 0.5f);
            break;
        }
        break;
    case 0x8D:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        if (((*(s32*)&g_hero_hazard_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            pval_36 = ((void*)g_hero_state) + 0xF0;
            hero_update_held_grab_pal();
            hero_resolve_stick_direction(1.0f, 0);
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            hero_approach_speed(0.0f, 0.00504f);
            vec_clear_128((s32) pval_36);
            hero_slide_along_wall_pal(0);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) pval_36, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
                hero_cancel_velocity_into_wall_pal();
                break;
            }
            hero_apply_mode_transform((s32) pval_36, (s32) pval_36, 0.0216f);
            break;
        }
        break;
    case 0x91:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->h[0x1E0/2] < 0x8) {
            if (g_hero_hazard_flag == 0) {
                if (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F) {
                    ((Hero *)g_hero_state)->h[0x1E0/2] = 0x21;
                    ((Hero *)g_hero_state)->i[0x229C/4] = 0;
                    ((Hero *)g_hero_state)->i[0x24A0/4] = 0;
                    hero_exit_vehicle_mode_pal(0);
                    FadeToBlack(0xd);
                    ((Hero *)g_hero_state)->c[0x22C1] = 1;
                }
            }
        }
        break;
    case 0x93:                                      /* switch 1 */
        if (((*(s32*)&g_hero_hazard_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            hero_approach_speed(0.014800001f, 0.0112000005f);
            hero_compute_push_direction(99999.0f);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0x118/4] - 0.010000001f);
                hero_cancel_velocity_into_wall_pal();
            } else {
                ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.0216f);
            }
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            if (shooter_update_ranged_attack_pal((s32) pval_21) != 0) {
                hero_l20_set_move_state_pal(0x8D, 1);
            }
        }
        break;
    case 0x94:                                      /* switch 1 */
        if (((*(s32*)&g_hero_hazard_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.11000001f;
            ApproachHeroVelocity_pal(0.010000001f);
                    hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.0072000003f);
            break;
        }
        break;
    case 0x8F:                                      /* switch 1 */
        if (((*(s32*)&g_hero_hazard_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_update_held_grab_pal();
            hero_resolve_stick_direction(0.11500001f, 0);
            if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
                hero_update_airborne_steering_pal();
            }
            hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), 0.0048f);
            if (((Hero *)g_hero_state)->f[0xF8/4] < -0.20000002f) {
                ((Hero *)g_hero_state)->f[0xF8/4] = -0.20000002f;
            }
        }
        break;
    case 0x8E:                                      /* switch 1 */
        if (((*(s32*)&g_hero_hazard_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_resolve_stick_direction(0.11500001f, 0);
            hero_update_held_grab_pal();
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_update_turn_from_anim_pal();
            } else {
                ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
                qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
                fval_125 = 0.12915438f;
                fval_117 = 0.04752f;
                if (((Hero *)g_hero_state)->b[0x40F] != 0) {
                    fval_125 = 0.16406098f;
                    fval_117 = 0.053280003f;
                }
                hero_steer_heading(0, fval_117, 0.21600002f, fval_125);
            }
            hero_approach_speed(0.0072000003f, 0.008f);
            if (((Hero *)g_hero_state)->f[0x174/4] < 0.014f) {
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
                if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                    ((Hero *)g_hero_state)->b[0x40F] = 1U;
                }
            }
            fval_66 = ReadPadFloatHistory(0);
            if ((FastDiffRots(fval_66, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                    fval_158 = 0.11500001f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.025464792f);
                    if (fval_158 < 0.0f) {
                        fval_158 = 0.0f;
                    }
                    if (fval_158 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                        ((Hero *)g_hero_state)->f[0x1B0/4] = fval_158;
                    }
                }
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x1440));
            } else {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x190));
            }
            hero_slide_along_wall_pal(1);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
                hero_cancel_velocity_into_wall_pal();
                break;
            }
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
            break;
        }
        break;
    case 0x90:                                      /* switch 1 */
        if ((g_hero_hazard_flag == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            fval_38 = vec_length_xy((s32)&((Hero *)g_hero_state)->b[0xF0]);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                fval_38 = fval_38 * 0.98800004f;
            } else {
                fval_38 = fval_38 * 0.90400004f;
            }
            func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), fval_38);
            pval_55 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            M2C_FIELD(pval_55, s32* , 0xF8) = 0;
            if (M2C_FIELD(pval_55, s16* , 0x34E) != 0) {
                hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0) + 0x30, 0.0088f);
            } else {
                hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.004f);
            }
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
    if (local_int_114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (local_int_118 != M2C_FIELD(pval_21, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
