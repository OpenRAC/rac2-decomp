#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern char g_pad_state[];
extern u8 g_hero_state_flags[];
extern u8 g_sound_state[];
extern char g_hero_state[];
extern char g_drive_velocity_view[];
extern char g_progress_statistics[];
extern u8 g_hero_state_machine_word[];
extern u32 g_frame_counter MACRO_ADDR;
extern s32 g_current_map_index MACRO_ADDR;
extern u8 g_status_flag_b[0x40] MACRO_ADDR;
extern u8 g_hero_override_flag MACRO_ADDR;
extern f32 g_hero_speed_limits[][4] MACRO_ADDR;
extern s32 g_hero_l19_lock_flag MACRO_ADDR;
extern u8 g_hero_state_value_data[];
extern s32 g_hero_l19_busy_flag MACRO_ADDR;
extern s32 g_frame_l19_counter MACRO_ADDR;
extern s32 g_water_l19_ripple_surface MACRO_ADDR;
extern s32 g_water_l19_ripple_param MACRO_ADDR;
extern u8 g_hero_l19_state_block[];
extern u8 g_hero_l19_matrix_block[];
extern u8 g_camera_l19_view_height[];
extern u8 g_impact_l19_moby_table[];
extern u8 g_hero_l19_motion_params[];
extern Rec2C g_hero_l19_state_table[];
extern u8 g_hero_l19_blend_table[];
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
extern void vec_build_spherical_offset(s32, f32, f32, f32);
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
extern s32 ProbeLedgeGrab_pal(s32, s32, s32);
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
extern void hero_approach_velocity_pal(f32);
extern void ApplyHeroGravityAndJumpMotion_pal(void);
extern void UpdateHeroVelocityForStateWithYawSpring_pal(void);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_apply_mode_pose_offsets_pal(void);
extern void UpdateHeroLeanAndSwayParameters(void);
extern void hero_apply_reference_tilt_rotation(s32, s32, s32, f32, f32, f32);
extern void hero_shrink_vector_by_amount(f32);
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
extern void UpdateHeroAimTarget(f32, f32, f32);
extern void hero_update_held_grab_pal(void);
extern s32 shooter_update_ranged_attack_pal(s32);
extern s32 hero_get_anim_id(s32);
extern void hero_detach_from_object_pal(s32);
extern void ClipHeroVelocityAtWall_pal(s32);
extern s32 hero_l19_set_state_pal(s32, s32);
extern char g_impact_effect_data[] MACRO_ADDR;
extern void moby_l00_raise_state_to_8();
extern void moby_raise_state_to_eight_copy();

/* Per-frame update of the hero state machine on Grelbin: reads the pad and runs the current movement state (PAL: 50 Hz speeds). */
void hero_l19_update_state_machine_pal(void) {
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
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* ptr_val_1;
    void* ptr_val_2;
    f32 float_val_1;
    void* ptr_val_3;
    s32 int_val_1;
    void* ptr_val_4;
    s32 int_val_2;
    s32 int_val_3;
    void* ptr_val_5;
    s32 int_val_4;
    void* ptr_val_6;
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
    f32 float_val_2;
    f32 float_val_3;
    f32 float_val_4;
    f32 float_val_5;
    f32 float_val_6;
    f32 float_val_7;
    f32 float_val_8;
    f32 float_val_9;
    f32 float_val_10;
    f32 float_val_11;
    f32 float_val_12;
    f32 float_val_13;
    f32 float_val_14;
    f32 float_val_15;
    f32 float_val_16;
    f32 float_val_17;
    f32 float_val_18;
    f32 float_val_19;
    f32 float_val_20;
    f32 float_val_21;
    f32 float_val_22;
    f32 float_val_23;
    f32 float_val_24;
    f32 float_val_25;
    f32 float_val_26;
    f32 float_val_27;
    f32 float_val_28;
    f32 float_val_29;
    f32 float_val_30;
    f32 float_val_31;
    f32 float_val_32;
    f32 float_val_33;
    f32 float_val_34;
    f32 float_val_35;
    f32 float_val_36;
    f32 float_val_37;
    f32 float_val_38;
    f32 float_val_39;
    f32 float_val_40;
    f32 float_val_41;
    f32 float_val_42;
    f32 float_val_43;
    f32 float_val_44;
    f32 float_val_45;
    f32 float_val_46;
    f32 float_val_47;
    f32 float_val_48;
    f32 float_val_49;
    f32 float_val_50;
    f32 float_val_51;
    f32 float_val_52;
    f32 float_val_53;
    f32 float_val_54;
    f32 float_val_55;
    f32 float_val_56;
    f32 float_val_57;
    f32 float_val_58;
    f32 float_val_59;
    f32 float_val_60;
    f32 float_val_61;
    f32 float_val_62;
    f32 float_val_63;
    f32 float_val_64;
    f32 float_val_65;
    f32 float_val_66;
    f32 float_val_67;
    f32 float_val_68;
    f32 float_val_69;
    f32 float_val_70;
    f32 float_val_71;
    f32 float_val_72;
    f32 float_val_73;
    f32 float_val_74;
    f32 float_val_75;
    f32 float_val_76;
    f32 float_val_77;
    f32 float_val_78;
    f32 float_val_79;
    f32 float_val_80;
    f32 float_val_81;
    f32 float_val_82;
    f32 float_val_83;
    f32 float_val_84;
    f32 float_val_85;
    f32 float_val_86;
    f32 float_val_87;
    f32 float_val_88;
    f32 float_val_89;
    f32 float_val_90;
    f32 float_val_91;
    f32 float_val_92;
    f32 float_val_93;
    f32 float_val_94;
    f32 float_val_95;
    f32 float_val_96;
    f32 float_val_97;
    f32 float_val_98;
    f32 float_val_99;
    f32 float_val_100;
    f32 float_val_101;
    f32 float_val_102;
    f32 float_val_103;
    f32 float_val_104;
    f32 float_val_105;
    f32 float_val_106;
    f32 float_val_107;
    f32 float_val_108;
    f32 float_val_109;
    f32 float_val_110;
    f32 float_val_111;
    f32 float_val_112;
    f32 float_val_113;
    f32 float_val_114;
    f32 float_val_115;
    f32 float_val_116;
    f32 float_val_117;
    f32 float_val_118;
    f32 float_val_119;
    f32 float_val_120;
    f32 float_val_121;
    f32 float_val_122;
    f32 float_val_123;
    f32 float_val_124;
    f32 float_val_125;
    f32 float_val_126;
    f32 float_val_127;
    f32 float_val_128;
    f32 float_val_129;
    f32 float_val_130;
    f32 float_val_131;
    f32 float_val_132;
    f32 float_val_133;
    f32 float_val_134;
    f32 float_val_135;
    f32 float_val_136;
    f32 float_val_137;
    f32 float_val_138;
    f32 float_val_139;
    f32 float_val_140;
    f32 float_val_141;
    f32 float_val_142;
    f32 float_val_143;
    f32 float_val_144;
    f32 float_val_145;
    f32 float_val_146;
    f32 float_val_147;
    f32 float_val_148;
    f32 float_val_149;
    f32 float_val_150;
    f32 float_val_151;
    f32 float_val_152;
    f32 float_val_153;
    f32 float_val_154;
    f32 float_val_155;
    f32 float_val_156;
    f32 float_val_157;
    f32 float_val_158;
    s16 int_val_5;
    s32 int_val_6;
    s16 int_val_7;
    s32 int_val_8;
    s32 int_val_9;
    s32 int_val_10;
    s32 int_val_11;
    s32 int_val_12;
    s32 int_val_13;
    s32 int_val_14;
    s32 int_val_15;
    s32 int_val_16;
    s32 int_val_17;
    s32 int_val_18;
    s32 int_val_19;
    s32 int_val_20;
    s32 int_val_21;
    s32 int_val_22;
    s32 int_val_23;
    s32 int_val_24;
    s32 int_val_25;
    s32 int_val_26;
    s32 int_val_27;
    s32 int_val_28;
    s32 int_val_29;
    s32 int_val_30;
    s32 int_val_31;
    s32 int_val_32;
    s32 int_val_33;
    s32 int_val_34;
    s32 int_val_35;
    s32 int_val_36;
    s32 int_val_37;
    s32 int_val_38;
    s32 int_val_39;
    s32 int_val_40;
    s32 int_val_41;
    s32 int_val_42;
    s32 int_val_43;
    s32 int_val_44;
    s32 int_val_45;
    s32 int_val_46;
    s32 int_val_47;
    s32 int_val_48;
    s32 int_val_49;
    s32 int_val_50;
    s32 int_val_51;
    s32 int_val_52;
    s32 int_val_53;
    s32 int_val_54;
    s32 int_val_55;
    s32 int_val_56;
    s32 int_val_57;
    s32 int_val_58;
    s32 int_val_59;
    s32 int_val_60;
    s32 int_val_61;
    s32 int_val_62;
    s32 int_val_63;
    s32 int_val_64;
    s32 int_val_65;
    s32 int_val_66;
    s32 int_val_67;
    s32 int_val_68;
    s32 int_val_69;
    s32 int_val_70;
    s32 int_val_71;
    s32 int_val_72;
    s32 int_val_73;
    s32 int_val_74;
    s32 int_val_75;
    s32 int_val_76;
    s32 int_val_77;
    s32 int_val_78;
    s32 int_val_79;
    s32 int_val_80;
    s32* ptr_val_7;
    s32* ptr_val_8;
    u16 int_val_81;
    u16 int_val_82;
    u16 int_val_83;
    u32 int_val_84;
    u32 int_val_85;
    u32 int_val_86;
    u32 int_val_87;
    u32 int_val_88;
    u32 int_val_89;
    u32 int_val_90;
    u32 int_val_91;
    u32 int_val_92;
    u32 int_val_93;
    u32 int_val_94;
    u32 int_val_95;
    u8 int_val_96;
    u8 int_val_97;
    u8 int_val_98;
    u8 int_val_99;
    void* ptr_val_9;
    void* ptr_val_10;
    void* ptr_val_11;
    void* ptr_val_12;
    void* ptr_val_13;
    void* ptr_val_14;
    void* ptr_val_15;
    void* ptr_val_16;
    void* ptr_val_17;
    void* ptr_val_18;
    void* ptr_val_19;
    void* ptr_val_20;
    void* ptr_val_21;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* ptr_val_22;
    void* ptr_val_23;
    void* ptr_val_24;
    void* ptr_val_25;
    void* ptr_val_26;
    void* ptr_val_27;
    void* ptr_val_28;
    void* ptr_val_29;
    void* ptr_val_30;
    void* ptr_val_31;
    void* ptr_val_32;
    void* ptr_val_33;
    void* ptr_val_34;
    void* ptr_val_35;
    void* ptr_val_36;
    void* ptr_val_37;
    void* ptr_val_38;
    void* ptr_val_39;
    void* ptr_val_40;
    void* ptr_val_41;
    void* ptr_val_42;
    void* ptr_val_43;
    void* ptr_val_44;
    void* ptr_val_45;
    void* ptr_val_46;
    void* ptr_val_47;
    void* ptr_val_48;
    void* ptr_val_49;
    void* ptr_val_50;
    void* ptr_val_51;
    void* ptr_val_52;
    void* ptr_val_53;
    void* ptr_val_54;
    void* ptr_val_55;
    void* ptr_val_56;
    void* ptr_val_57;
    void* ptr_val_58;
    void* ptr_val_59;
    void* ptr_val_60;
    void* ptr_val_61;

    stack_114 = ((Hero *)g_hero_state)->i[0x2298/4];
    ptr_val_21 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    stack_118 = (s32) M2C_FIELD(ptr_val_21, u8* , 0x43);
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
        hero_build_move_impulse(0.5f, 0.040000003f);
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        int_val_85 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_val_85 == 1) || (int_val_85 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)v0) = 0;
                v0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)v0), (s32)&g_hero_l19_matrix_block[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_l19_matrix_block)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (int_val_97 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (int_val_97 == 0xE)) || (int_val_97 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.0028800003f, 0.10080001f, 0.13962635f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0069813184f) {
                    int_val_11 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    int_val_11 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != int_val_11) {
                        set_hero_animation_pal(int_val_11, 0, 4.0f);
                    }
                    float_val_2 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 12.564863f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = float_val_2;
                    if (float_val_2 < 0.55f) {
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
            int_val_94 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (int_val_94 == 3) {
                float_val_105 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (float_val_105 > 1.0f) {
                    float_val_105 = 1.0f;
                }
                ptr_val_16 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                float_val_131 = float_val_105 * 0.0108f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = float_val_131;
                if (M2C_FIELD(ptr_val_16, u8* , 0x42) == M2C_FIELD(ptr_val_16, u8* , 0x43)) {
                    float_val_126 = ((Hero *)g_hero_state)->f[0x174/4] / float_val_131;
                    if ((float_val_126 > 4.0f) && ((f32) M2C_FIELD(ptr_val_16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, float_val_126, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (int_val_94 == 4) {
                float_val_131 = 0.0108f;
            } else {
                float_val_131 = 0.007080001f;
            }
            hero_approach_speed(0.0f, float_val_131);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(float_val_131);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                int_val_57 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(int_val_57, int_val_57 + 0x30, 0.0088f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0216f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                ClipHeroVelocityAtWall_pal(0);
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
            int_val_28 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = int_val_28;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)int_val_28 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)int_val_28 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(int_val_28, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            int_val_48 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(int_val_48, u16* , 0x34) = (u16) (M2C_FIELD(int_val_48, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(6.0f);
        int_val_50 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(int_val_50, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(int_val_50, u8* , 0x23) = 0x80U;
        }
        int_val_12 = ((Hero *)hero7C)->i[0x7A4/4];
        ptr_val_18 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)int_val_12 + 0x10, (u8 *)ptr_val_18 + 0x10);
        qcopy((u8 *)int_val_12 + 0xF0, (u8 *)ptr_val_18 + 0xF0);
        func_002A0F48(int_val_12);
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
            int_val_21 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (int_val_21 != -1) {
                ptr_val_17 = (int_val_21 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(ptr_val_17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ptr_val_17, u8* , 0x74) != 0) {
                        snd_stop_voice(int_val_21);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            int_val_13 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects_pal((int_val_13 >= 9) ? 8 : int_val_13, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            float_val_48 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (float_val_48 > 0.0f) {
                if (float_val_48 < 10.0f) {
                    EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                int_val_51 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (int_val_51 < 0xc) {
                    EmitHeroRandomizedMotionEffects_pal(((s32) (0x11 - int_val_51) / 3) + 1, 1, 0);
                }
            }
        }
        int_val_52 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (int_val_52 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == int_val_52) {
                part_emit_hero_dust_and_debris_pal(3, 0x10, 0);
                if (g_water_l19_ripple_surface != 0) {
                    RippleDisturb(g_water_l19_ripple_surface, g_water_l19_ripple_param, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x3a;
            }
            int_val_35 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = int_val_35;
            if (int_val_35 >= 0x22) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.013962637f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.010471976f;
        float_val_118 = 0.0f;
        
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            float_val_120 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (float_val_120 > 1.0f) {
                float_val_120 = 1.0f;
            }
            if (float_val_120 < 0.2f) {
                float_val_120 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                int_val_9 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                float_val_120 = ((f32) (s16) int_val_9 * 0.029411765f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) int_val_9;
                if (float_val_120 > 1.0f) {
                    float_val_120 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (float_val_120 < 0.35f)) {
                float_val_120 = 0.35f;
            }
            float_val_118 = float_val_120 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            float_val_119 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (float_val_119 > 1.0f) {
                float_val_119 = 1.0f;
            }
            if (float_val_119 < 0.2f) {
                float_val_119 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = cntA40;
                float_val_119 = ((f32) (s16) cntA40 * 0.029411765f) + 0.5f;
                if (float_val_119 > 1.0f) {
                    float_val_119 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                float_val_119 = 1.0f;
            }
            float_val_118 = float_val_119 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                int_val_8 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = int_val_8;
                if ((s16) int_val_8 >= 0x4c) {
                    int_val_82 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (int_val_82 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (int_val_82 + 1);
                    }
                }
                int_val_36 = (*(s32*)&g_frame_counter);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) (((s32)int_val_36 * 5 + 2) / 6)) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) (((s32)int_val_36 * 5 + 2) / 6);
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
            if ((g_frame_l19_counter - hp32->i[0xA54/4]) < 0x3a) {
                hp32->i[0xA50/4]++;
            }
            hp32->i[0xA54/4] = g_frame_l19_counter;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x3b) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            float_val_118 = 0.0f;
        }
        float_val_56 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), float_val_118, (s32) (((void*)g_hero_state) + 0xA28), 0.0216f, 0.28800002f, stick_turn, 0);
        float_val_78 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], float_val_56);
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
        float_val_154 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (float_val_154 < 1.0f) {
                float_val_154 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            float_val_97 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                float_val_97 = 0.4f;
            }
            if (float_val_154 < float_val_97) {
                float_val_154 = float_val_97;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_val_154);
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
                int_val_58 = 3;
                int_val_62 = 0x9;
            } else {
                int_val_58 = 0x21;
                int_val_62 = 0x4b;
            }
            ((Hero *)heroA30)->i[0xA30/4] = math_random_int_range(int_val_58, int_val_62);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                ptr_val_42 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (ptr_val_42 != 0) {
                    if (M2C_FIELD(ptr_val_42, s16* , 0xAA) == 0x261) {
                        for (int_val_66 = 0; int_val_66 < 4; int_val_66++) {
                            moby_transform_joint_to_world((s32) ptr_val_42, int_val_66 % 2, (s32)((TI128*)v0));
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
        float_val_75 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        int_val_86 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (int_val_86 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], float_val_75);
        } else if (int_val_86 == 0x32) {
            float_val_121 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l19_blend_table, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) && (float_val_121 < 0.09f)) {
                float_val_121 = 0.09f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), float_val_121, ((Hero *)g_hero_state)->f[0x98/4], float_val_75);
        } else if (int_val_86 == 0x33) {
            stack_e0 = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &stack_e0, 0.0f, 0.0032000002f);
            } else {
                ApproachValue((s32) &stack_e0, 0.0f, 0.0016000001f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), stack_e0);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        ClipHeroVelocityAtWall_pal(0);
        float_val_76 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(float_val_75) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), float_val_76, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.024434613f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        float_val_82 = float_val_78 * 47.0f;
        ((Hero *)g_hero_l19_motion_params)->f[0x114/4] = float_val_82;
        ((Hero *)g_hero_l19_motion_params)->f[0x118/4] = (f32) (float_val_76 * 1.5f);
        ((Hero *)g_hero_l19_motion_params)->f[0x110/4] = (f32) (float_val_76 * 1.4f);
        if (float_val_82 > 0.8726647f) {
            ((Hero *)g_hero_l19_motion_params)->f[0x114/4] = 0.8726647f;
        } else if (float_val_82 < -0.8726647f) {
            ((Hero *)g_hero_l19_motion_params)->f[0x114/4] = -0.8726647f;
        }
        float_val_49 = float_val_78 * 40.0f;
        float_val_23 = float_val_76 * 1.1f;
        ((Hero *)g_hero_l19_motion_params)->f[0x364/4] = 0.03f;
        ((Hero *)g_hero_l19_motion_params)->f[0x368/4] = 0.22f;
        ((Hero *)g_hero_l19_motion_params)->f[0x324/4] = float_val_49;
        ((Hero *)g_hero_l19_motion_params)->f[0x328/4] = float_val_23;
        ((Hero *)g_hero_l19_motion_params)->f[0x414/4] = 0.03f;
        ((Hero *)g_hero_l19_motion_params)->f[0x418/4] = 0.22f;
        ((Hero *)g_hero_l19_motion_params)->f[0x3D4/4] = float_val_49;
        ((Hero *)g_hero_l19_motion_params)->f[0x3D8/4] = float_val_23;
        break;
    case 0x73:                                      /* switch 1 */
        int_val_14 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        ptr_val_29 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects_pal((int_val_14 >= 9) ? 8 : int_val_14, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) ptr_val_29, (s32) ptr_val_29, vec_length_xy((s32) ptr_val_29) * 0.90400004f);
        ClipHeroVelocityAtWall_pal(0);
        break;
    case 0x72:                                      /* switch 1 */
        part_spawn_jittered_after_delay(0xF, 0x1E);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.90400004f);
        ClipHeroVelocityAtWall_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x67:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
        stack_e4 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &stack_e4, 0.0f, 0.0016000001f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), stack_e4);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            ptr_val_37 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(ptr_val_37, s32* , 0x2290), 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), M2C_FIELD(ptr_val_37, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.030000001f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.040000003f;
            part_spawn_bubble_pal((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            int_val_37 = M2C_FIELD(ptr_val_37, s32* , 0x1B8);
            if (int_val_37 < 0x21) {
                lim67 = 5;
                int_val_71 = math_random_int_range(2, 4) + ((s32) M2C_FIELD(ptr_val_37, s32* , 0x1B8) / lim67);
                goto block_224;
            }
            if (int_val_37 >= 0x3b) {
                int_val_71 = math_random_int_range(0x8, 0x11);
block_224:
                M2C_FIELD(ptr_val_37, s32* , 0xA30) = int_val_71;
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
            int_val_15 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects_pal((int_val_15 >= 7) ? 6 : int_val_15, 0, 0);
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
            float_val_67 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l19_blend_table, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * float_val_67);
            float_val_25 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * float_val_67;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = float_val_25;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            float_val_50 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((float_val_50 > 0.0f) && (float_val_50 < 10.0f)) {
                EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.00168f);
        ClipHeroVelocityAtWall_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x85:                                      /* switch 1 */
        ptr_val_19 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)ptr_val_19 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)ptr_val_19 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)v0), (s32)(g_hero_state + 0x2C0), -1.0f);
        float_val_122 = 0.0f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            float_val_122 = -((Hero *)g_hero_state)->f[0x1FB4/4] * 0.75f;
        }
        math_spring_float_to_goal((s32)(g_hero_state + 0x7C0), (s32)(g_hero_state + 0x7C4), float_val_122, 0.01008f, 0.43200004f, 0.036000002f);
        FastVecScale((s32) ((TI128*)v10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v10));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        hero_apply_reference_tilt_rotation((s32)((TI128*)v0), (s32) ((TI128*)v30), 0, 0.036000002f, 0.57600003f, 0.0f);
        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.26000002f;
        vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)g_hero_state, 0.26000002f);
        cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
        vec_clear_128((s32)((TI128*)v0));
        v0[1] = -((Hero *)g_hero_state)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(g_hero_state + 0x190), (s32)((TI128*)v0), (s32)&g_hero_l19_matrix_block[0x218]);
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
            ptr_val_50 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr_val_50, u8* , 0x60) & 2) && (M2C_FIELD(ptr_val_50, u8* , 0x42) == 0x36)) {
                set_hero_animation_pal(hero_get_anim_id(0), 0, 4.0f);
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
        ptr_val_61 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (ptr_val_61 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr_val_61, f32* , 0x10) - M2C_FIELD(ptr_val_21, f32* , 0x10), M2C_FIELD(ptr_val_61, f32* , 0x14) - M2C_FIELD(ptr_val_21, f32* , 0x14));
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
        ptr_val_1 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (ptr_val_1 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr_val_1, f32* , 0x10) - M2C_FIELD(ptr_val_21, f32* , 0x10), M2C_FIELD(ptr_val_1, f32* , 0x14) - M2C_FIELD(ptr_val_21, f32* , 0x14));
            hero_steer_heading(0, 0.028800001f, 0.21600002f, 0.12566373f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(v0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        float_val_26 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)v0));
        ((Hero *)g_hero_state)->f[0xAB0/4] = float_val_26;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 5e1f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (float_val_26 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        int_val_38 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (int_val_38 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.54f, 0.032f);
            ptr_val_46 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            float_val_136 = mat_fast_helper_a(M2C_FIELD(ptr_val_46, f32* , 0x10) - M2C_FIELD(ptr_val_21, f32* , 0x10), M2C_FIELD(ptr_val_46, f32* , 0x14) - M2C_FIELD(ptr_val_21, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], float_val_136) > 1.5707964f) {
                    float_val_136 = FastAddRotations(float_val_136, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = float_val_136;
            hero_steer_heading(0, 0.0432f, 0.21600002f, 0.14660768f);
        } else if (int_val_38 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.016800001f);
        }
        if ((math_solve_quadratic((s32) &stack_e8, (s32) &stack_ec, -0.008400001f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (stack_e8 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = stack_e8;
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
        float_val_27 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        v20[2] = 0;
        v20[1] = float_val_27;
        FastVecAdd((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)v10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)v20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)v10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        float_val_28 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (float_val_28 < 25.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((25.0f - float_val_28) * 0.011600001f));
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
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(ptr_val_21, u8* , 0x43) == 0x34)) {
            set_hero_animation_pal(0x35, 0xA, 1e1f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        ptr_val_51 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        float_val_81 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (ptr_val_51 != 0) {
            ptr_val_47 = M2C_FIELD(ptr_val_51, void** , 0x68);
            if ((ptr_val_47 != 0) && (M2C_FIELD(ptr_val_47, s32* , 0x34) != 0)) {
                float_val_137 = M2C_FIELD(ptr_val_51, f32* , 0xF8);
                if (FastDiffRots(float_val_137, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    float_val_137 = FastAddRotations(float_val_137, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), float_val_137, (s32) (((void*)g_hero_state) + 0xAF8), 0.028800001f, 0.43200004f, 0.0f, 0);
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
        float_val_29 = mat_fast_helper_a(v0[2], v0[0]);
        v10[1] = float_val_29;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), float_val_29, (s32) (((void*)g_hero_state) + 0xA4), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), v10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        int_val_69 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((int_val_69 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x22) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                float_val_138 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0042000003f;
                if (float_val_138 > 0.10000001f) {
                    float_val_138 = 0.10000001f;
                }
                vB0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * float_val_138;
                float_val_30 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * float_val_138;
                ptr_val_9 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vB0[2]) = 0;
                vB0[1] = float_val_30;
                FastVecAdd((s32) ptr_val_9, (s32) ptr_val_9, (s32) ((TI128*)vB0));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                ptr_val_38 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) ptr_val_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    ptr_val_30 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) ptr_val_30, (s32) (((void*)g_hero_state) + 0x110), 0.016f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) ptr_val_30) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vB0), (s32) ptr_val_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) ptr_val_30, (s32) ptr_val_30, 0.0228f);
                    }
                }
                float_val_68 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.0003f;
                FastVecScale((s32) ((TI128*)vB0), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vB0), (s32) ((TI128*)vB0), float_val_68);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vB0));
            }
        }
        ptr_val_48 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (ptr_val_48 != 0) {
            ptr_val_22 = M2C_FIELD(ptr_val_48, void** , 0x68);
            ptr_val_31 = ((void*)g_hero_state) + 0xF0;
            if (ptr_val_22 != 0) {
                float_val_31 = FastVecLength((s32) ptr_val_31);
                float_val_32 = M2C_FIELD(ptr_val_22, f32* , 0xC);
                stack_f0 = float_val_31;
                if (float_val_32 < float_val_31) {
                    ApproachValue((s32) &stack_f0, float_val_32, 0.006f);
                    vec_scale_to_length((s32) ptr_val_31, (s32) ptr_val_31, stack_f0);
                }
            }
        }
        float_val_3 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        ptr_val_44 = ((void*)g_hero_state) + 0x80;
        ptr_val_43 = ((void*)g_hero_state) + 0xF0;
        vD0[0] = math_fast_sin_or_cos_a(float_val_3) * 0.15f;
        float_val_4 = math_fast_sin_or_cos_b(float_val_3) * 0.15f;
        (*(s32*)&vD0[2]) = 0;
        vD0[1] = float_val_4;
        FastVecAdd((s32) &vD0[0], (s32) &vD0[0], (s32) ptr_val_44);
        FastVecAdd((s32) ((TI128*)vB0), (s32) &vD0[0], (s32) ptr_val_43);
        FastVecSub((s32) ((TI128*)vC0), (s32) ((TI128*)vB0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vB0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vC0));
        FastVecSub((s32) ptr_val_43, (s32) ((TI128*)vB0), (s32) &vD0[0]);
        float_val_69 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        float_val_70 = ((Hero *)g_hero_state)->f[0xAE4/4] - float_val_69;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vC0))) {
            vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), float_val_70);
            FastVecAdd((s32) ptr_val_44, (s32) ptr_val_44, (s32) ((TI128*)vC0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (int_val_69 != 0)) {
            min2B = 0.28000003f;
            float_val_5 = vec_length_xy((s32) ptr_val_43);
            stack_f4 = float_val_5;
            if (float_val_5 < min2B) {
                math_spring_float_to_goal((s32) &stack_f4, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.06768f, 0.43200004f, 0.0f);
                vB0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                float_val_6 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vB0[2] = 0.0f;
                vB0[1] = float_val_6 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) ptr_val_43, (s32) ptr_val_43, (s32) ((TI128*)vB0));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((float_val_81 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            float_val_71 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            int_val_7 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (int_val_7 != 0) {
                int_val_72 = int_val_7 == 1;
            } else {
                (*(TI128*)vB0) = ((Hero *)g_hero_state)->q[0x110/16];
                int_val_72 = hero_get_speed_along_forward((s32) ((TI128*)vB0)) > 0.0f;
            }
            if (int_val_72 != 0) {
                if (M2C_FIELD(ptr_val_21, u8* , 0x43) != 0x35) {
                    set_hero_animation_pal(0x35, 6, 14.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    ptr_val_49 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(ptr_val_49, u8* , 0x42) == M2C_FIELD(ptr_val_49, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, float_val_71, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(ptr_val_21, u8* , 0x43) != 0x35) {
                set_hero_animation_pal(0x35, 0x15, 7.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                ptr_val_45 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(ptr_val_45, u8* , 0x42) == M2C_FIELD(ptr_val_45, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, float_val_71, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l19_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        int_val_67 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            int_val_67 = 1;
        }
        int_val_17 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (int_val_17 != 0) {
            FastVecSub((s32)((TI128*)v0), int_val_17 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            float_val_7 = cam_get_view_space_vector_length((s32)((TI128*)v0));
            if (((float_val_7 > 2.0f) && (float_val_7 < 5.0f)) || (int_val_67 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
            }
            hero_approach_speed(0.010000001f, 0.010000001f);
            vec_scale_to_length((s32) ((TI128*)v10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)v10));
        } else {
            if ((int_val_67 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3a)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
            }
            hero_approach_speed(0.006f, 0.006f);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4]);
        }
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
            hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
        } else if (((Hero *)g_hero_state)->f[0xC38/4] < 25.0f) {
            hero_l00_select_aim_target(8.0f, 1.0471977f, 1.0471977f);
        }
        float_val_52 = ((Hero *)g_hero_state)->f[0x31C/4];
        float_val_144 = 0.15400001f;
        if (float_val_52 > 2.25f) {
            float_val_144 = 0.07700001f;
        } else if (float_val_52 > 1.8f) {
            float_val_144 = 0.10780001f;
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
                ((Hero *)g_hero_l19_state_block)->f[0x180/4] = 0.1f;
                ((Hero *)g_hero_l19_state_block)->i[0x188/4] = 0x19;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x1d;
                ((Hero *)g_hero_l19_state_block)->i[0x16C/4] = 0;
            }
        }
        int_val_39 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xc;
        if (int_val_39 < 7) {
            ptr_val_23 = ((void*)g_hero_state) + 0xF0;
            stack_f8 = cam_get_view_space_height((s32) ptr_val_23);
            ApproachValue((s32) &stack_f8, float_val_144, 0.060000002f);
            cam_set_view_space_height((s32) ptr_val_23, (s32) ptr_val_23, stack_f8);
        } else if (int_val_39 > lim3) {
            ptr_val_32 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_val_32, (s32) ptr_val_32, 0.052f);
            if (cam_get_view_space_height((s32) ptr_val_32) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            float_val_139 = -0.74000007f;
            if (g_hero_l19_lock_flag != 0) {
                float_val_139 = -1.4000001f;
            }
            if (cam_get_view_space_height((s32) ptr_val_32) < float_val_139) {
                cam_set_view_space_height((s32) ptr_val_32, (s32) ptr_val_32, float_val_139);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l19_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        int_val_60 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x12);
        if (int_val_60 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                int_val_68 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    ptr_val_24 = ((void*)g_hero_state) + 0xBC0;
                    float_val_140 = hero_get_direction_angle_delta((s32) ptr_val_24, 0);
                    float_val_98 = hero_get_direction_angle_delta((s32) ptr_val_24, 1);
                } else {
                    float_val_140 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    float_val_98 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (float_val_98 < 4.3633237f) {
                    int_val_68 = 1;
                }
                if (float_val_140 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (float_val_98 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (int_val_68 != 0) {
                    hero_steer_heading(1, 0.08208001f, 0.28800002f, 0.33859393f);
                } else {
                    hero_steer_heading(0, 0.08208001f, 0.28800002f, 0.33859393f);
                }
            } else {
                    int_val_61 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xa)) {
                        int_val_61 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        int_val_61 = 0;
                    }
                    if (int_val_61 != 0) {
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
                hero_setup_attached_object_transform_pal();
            }
        }
        hero_approach_speed(0.014800001f, 0.0112000005f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
            break;
        }
        break;
    case 0x13:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l19_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        int_val_18 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ptr_val_39 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_l19_state_table;
        if ((int_val_18 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 3)) {
            ptr_val_33 = ((void*)g_hero_state) + 0x80;
            float_val_108 = vec_distance_xy(int_val_18 + 0x10, (s32) ptr_val_33);
            if ((*(s32*)&g_hero_l19_lock_flag) != 0) {
                float_val_108 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) ptr_val_33);
            }
            float_val_108 = float_val_108 - 0.5f;
            if (float_val_108 < 0.0f) {
                float_val_108 = 0.0f;
            }
            int_val_40 = M2C_FIELD(ptr_val_39, s32* , 4);
            if (int_val_40 == 0) {
                float_val_99 = 0.75f;
                float_val_146 = 0.8f;
                float_val_151 = 4.0f;
            } else if (int_val_40 == 1) {
                float_val_99 = 0.6f;
                float_val_146 = 1.7f;
                float_val_151 = 4.0f;
            } else {
                float_val_99 = 1.3f;
                float_val_146 = 1.7f;
                float_val_151 = 1.9f;
            }
            float_val_73 = float_val_108 - float_val_99;
            if (math_fabs(float_val_73) < (float_val_146 + 3.0f)) {
                float_val_110 = float_val_73 * 1.1111112f;
                if (float_val_151 < float_val_110) {
                    float_val_110 = float_val_151;
                }
                if (float_val_110 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = float_val_110;
                }
            }
        }
        int_val_41 = M2C_FIELD(ptr_val_39, s32* , 4);
        switch (int_val_41) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.08800001f;
            }
            break;
        case 1:
            float_val_53 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (float_val_53 < 9.0f)) {
                if (float_val_53 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.060000002f;
                } else if (float_val_53 > 7.0f) {
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
            float_val_100 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            float_val_100 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        float_val_54 = math_fabs(float_val_100);
        if ((M2C_FIELD(ptr_val_39, s32* , 4) == 1) && (float_val_100 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (float_val_54 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
    } else {
        int_val_79 = 1;
        if ((M2C_FIELD(ptr_val_39, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            int_val_79 = 0;
        }
        if (int_val_79 != 0) {
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
            ptr_val_11 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_val_11, (s32) ptr_val_11, 0.0216f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.0096f);
        if ((*(s32*)&g_hero_l19_lock_flag) != 0) {
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
        int_val_42 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (int_val_42 > lim) {
            if (int_val_42 < 0xf) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.36f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 7) && (((Hero *)g_hero_state)->f[0x184/4] < 0.40000004f)) {
            ptr_val_25 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ptr_val_25);
            level_append_record_to_table((s32) ptr_val_25, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) ptr_val_25, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) ptr_val_25, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)g_hero_state)->i[0x1B8/4] > lim2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), sel1F);
        if (((Hero *)g_hero_state)->i[0x1B8/4] > lim) {
            hero_approach_speed(0.076000005f, 0.036000002f);
        }
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x1F) {
            int_val_44 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((int_val_44 > lim) && (int_val_44 < 0x12)) {
                ptr_val_40 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (ptr_val_40 != 0) {
                    ptr_val_34 = ((void*)g_hero_state) + 0x80;
                    v30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)v0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)v30));
                    (*(u8*)((u8*)v10+9)) = 3;
                    v0[3] = 5627.925f;
                    (*(u8*)((u8*)v10+8)) = 0;
                    float_val_79 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)v10+10)) = M2C_FIELD(ptr_val_40, u16* , 0xAA);
                    v40[0] = math_fast_sin_or_cos_a(float_val_79) * 0.8f;
                    float_val_8 = math_fast_sin_or_cos_b(float_val_79) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = float_val_8;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) ptr_val_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ptr_val_40, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) ptr_val_40, (s32)((TI128*)v0)));
                    float_val_79 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(float_val_79) * 0.8f;
                    float_val_10 = math_fast_sin_or_cos_b(float_val_79) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = float_val_10;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) ptr_val_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ptr_val_40, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)v0)));
                    float_val_79 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(float_val_79) * 0.8f;
                    float_val_12 = math_fast_sin_or_cos_b(float_val_79) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = float_val_12;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) ptr_val_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ptr_val_40, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) ptr_val_40, (s32)((TI128*)v0)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ClipHeroVelocityAtWall_pal(1);
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
        int_val_55 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            int_val_55 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (int_val_55 != 0)) {
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
            float_val_74 = ReadPadFloatHistory(1);
            if ((FastDiffRots(float_val_74, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            float_val_55 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)v0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = float_val_55;
            if (float_val_55 < 0.014f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.014f;
            }
            vec_clear_128((s32) pA60);
        }
        float_val_141 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim_pal();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.028800001f, 0.24480002f, 0.19896756f);
            } else {
                float_val_83 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (float_val_83 > 0.78539824f)) {
                    float_val_141 = 0.0f;
                }
                hero_set_turn_rates_pal();
            }
        }
        hero_apply_mode_pose_offsets_pal();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            float_val_155 = 0.119f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.03501409f);
            if (float_val_155 < 0.0f) {
                float_val_155 = 0.0f;
            }
            if (float_val_155 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = float_val_155;
            }
        }
        k005 = float_val_141 * 0.0072000003f;
        float_val_142 = 0.008f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            float_val_127 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (float_val_127 > 1.0f) {
                float_val_127 = 1.0f;
            }
            if (float_val_127 < 0.2f) {
                float_val_127 = 0.2f;
            }
            float_val_142 = 0.0068000006f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_val_127);
        }
        float_val_84 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (float_val_84 > 0.6108653f)) {
            float_val_128 = 1.0f - (float_val_84 * 0.4f);
            if (float_val_128 < 0.0f) {
                float_val_128 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_val_128);
        }
        hero_approach_speed(k005, float_val_142);
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
        ClipHeroVelocityAtWall_pal(1);
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
        float_val_147 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.024434613f) * v0[0];
        if ((*(s32*)&g_hero_l19_lock_flag) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x32) {
                float_val_147 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.6f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, float_val_147);
        }
        hero_approach_speed(0.040000003f, 0.006f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&g_hero_l19_lock_flag) != 0) {
            qcopy(v10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)v10), (s32) ((TI128*)v10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0xA00), 0.057600003f, 0.43200004f, 0.15f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.057600003f, 0.43200004f, 0.15f);
        }
        FastVecScale((s32) ((TI128*)v10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32)(g_hero_state + 0xE0));
        int_val_29 = coll_process_hit(0.57f, (s32) ((TI128*)v10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (int_val_29 != 0) {
            FastVecScale((s32) ((TI128*)v20), (s32)(g_hero_state + 0x110), 7.0f);
            for (int_val_64 = 0; int_val_64 < int_val_29; int_val_64++) {
                if (moby_is_in_special_class_range(((s32 *)g_impact_l19_moby_table)[int_val_64]) != 0) {
                    part_queue_impact_effect(((s32 *)g_impact_l19_moby_table)[int_val_64], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.024480002f, 0.43200004f);
        cam_set_limits_third(0.036000002f, 0.43200004f);
        cam_set_limits_fourth(0.0432f, 0.38880002f);
        float_val_156 = float_val_147 * 27.0f;
        if (float_val_156 > 1.7f) {
            float_val_156 = 1.7f;
        } else if (float_val_156 < -1.7f) {
            float_val_156 = -1.7f;
        }
        float_val_13 = float_val_156 * 0.5f;
        ((Hero *)g_hero_l19_motion_params)->f[0x60/4] = (f32) -float_val_156;
        ((Hero *)g_hero_l19_motion_params)->f[0x278/4] = float_val_13;
        ((Hero *)g_hero_l19_motion_params)->f[0x1C8/4] = float_val_13;
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
        if ((ProbeLedgeGrab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (ProbeLedgeGrab_pal((s32) &v50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)v0), (s32)(g_hero_state + 0x80));
            int_val_76 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            int_val_80 = (s32)g_hero_state_value_data;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(int_val_76 + int_val_80) * 0.5f);
        }
        break;
    case 0x76:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.11000001f;
        hero_approach_velocity_pal(0.010000001f);
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.0072000003f);
        break;
    case 0x6:                                       /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2C) {
            float_val_113 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                float_val_113 = 0.43633235f;
            }
            qcopy(v0, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &v0[1], float_val_113, (s32) (((void*)g_hero_state) + 0xA4), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            math_approach_with_velocity((s32)((TI128*)v0), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_update_target_speed_pal();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            UpdateHeroVelocityForStateWithYawSpring_pal();
        }
        ptr_val_60 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets_pal();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) ptr_val_60, (s32) ptr_val_60, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_val_60) < -1.0000001f) {
            cam_set_view_space_height((s32) ptr_val_60, (s32) ptr_val_60, -1.0000001f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        ptr_val_2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0034906592f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0034906592f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ptr_val_2, (s32) ptr_val_2, vec_length_xy((s32) ptr_val_2) * 0.88f);
        hero_apply_mode_transform((s32) ptr_val_2, (s32) ptr_val_2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_val_2) < -1.0000001f) {
            cam_set_view_space_height((s32) ptr_val_2, (s32) ptr_val_2, -1.0000001f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.0003490659f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        int_val_56 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            int_val_56 = 0;
        }
        if (int_val_56 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.120000005f);
            ptr_val_13 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) ptr_val_13, (s32) ptr_val_13, 0.036000002f);
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
        float_val_35 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x4b) && (float_val_35 < 0.0f) && (float_val_87 = ((Hero *)g_hero_state)->f[0x31C/4], (float_val_87 < 1.2f))) {
            float_val_91 = (float_val_87 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (float_val_91 < 0.0f) {
                float_val_91 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), float_val_35 * float_val_91);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.03888f, 0.43200004f, 0.10000001f);
            }
        } else if (float_val_35 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&g_camera_l19_view_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets_pal();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.24000001f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.03888f, 0.43200004f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.10471977f);
        float_val_114 = 0.002f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            float_val_114 = 0.00080000004f;
        }
        hero_approach_velocity_pal(float_val_114);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            int_val_23 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (int_val_23 != -1) {
                ptr_val_14 = (int_val_23 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_val_14, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_val_14, u8* , 0x74) != 0)) {
                    snd_stop_voice(int_val_23);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            int_val_24 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (int_val_24 != -1) {
                ptr_val_15 = (int_val_24 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_val_15, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_val_15, u8* , 0x74) != 0)) {
                    snd_stop_voice(int_val_24);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        float_val_152 = 0.060000002f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            float_val_152 = 0.10000001f;
        }
        float_val_153 = 0.72f;
        float_val_42 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            float_val_152 = 0.15400001f;
            float_val_153 = 0.98640007f;
        }
        if (float_val_42 != 0.0f) {
            float_val_153 = float_val_42;
        }
        ptr_val_27 = ((void*)g_hero_state) + 0xF0;
        stack_110 = cam_get_view_space_height((s32) ptr_val_27);
        hero_resolve_stick_direction(float_val_152, 0);
        hero_steer_heading(0, 0.036000002f, 0.43200004f, 0.25132746f);
        hero_approach_speed(0.006f, 0.0028000001f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets_pal();
        cam_project_vector_onto_view_plane((s32) ptr_val_27, (s32) ptr_val_27);
        math_spring_float_to_goal((s32) &stack_110, (s32) (((void*)g_hero_state) + 0xA98), -float_val_152 * float_val_153, 0.036000002f, 0.43200004f, 0.34000003f);
        hero_apply_mode_transform((s32) ptr_val_27, (s32) ptr_val_27, -stack_110);
        float_val_36 = ((Hero *)g_hero_state)->f[0x88/4];
        if (float_val_36 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), float_val_36, 0.080000006f);
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
                if (g_water_l19_ripple_surface != 0) {
                    RippleDisturb(g_water_l19_ripple_surface, g_water_l19_ripple_param, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            float_val_43 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((float_val_43 >= 4.0f) && (float_val_43 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects_pal(7, 0, 0);
            }
        }
        int_val_5 = ((Hero *)g_hero_state)->h[0x4AC/2];
        int_val_20 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (int_val_20 == int_val_5) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((int_val_20 < int_val_5) && (int_val_92 = ((Hero *)g_hero_state)->u[0x2294/4], (int_val_92 != 0xB)) && (int_val_92 != 0x10) && (int_val_92 != 0xC) && (int_val_92 != 0x11) && (int_val_92 != 0x1B) && (int_val_92 != 0x89) && (int_val_92 != 0x48))) {
            hero_steer_heading(0, 0.0216f, 0.28800002f, 0.30019668f);
            float_val_63 = ((Hero *)g_hero_state)->f[0x1B4/4];
            if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (float_val_63 * 0.4f);
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
            ((Hero *)g_hero_state)->f[0x1B4/4] = float_val_63;
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
                int_val_46 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (int_val_46 < (((Hero *)g_hero_state)->h[0x4AC/2] + 3)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) int_val_46 * 0.0064000003f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                int_val_47 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (int_val_47 < 0x1c) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) int_val_47 * 0.021200001f);
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
        } else {
            UpdateHeroVelocityForStateWithYawSpring_pal();
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
                ptr_val_28 = ((void*)g_hero_state) + 0xF0;
                float_val_92 = vec_length_xy((s32) ptr_val_28);
                if (float_val_92 > 0.07400001f) {
                    float_val_92 = 0.07400001f;
                }
                vec_fast_normalize_helper((s32) ptr_val_28, (s32) ptr_val_28, float_val_92);
            }
        }
        float_val_44 = ((Hero *)g_hero_state)->f[0x318/4];
        float_val_88 = ((Hero *)g_hero_state)->f[0x490/4];
        if (float_val_88 < float_val_44) {
            float_val_22 = float_val_88 + 0.120000005f;
            ((Hero *)g_hero_state)->f[0x490/4] = float_val_22;
            if (float_val_44 < float_val_22) {
                ((Hero *)g_hero_state)->f[0x490/4] = float_val_44;
            }
        }
        float_val_45 = ((Hero *)g_hero_state)->f[0x88/4];
        if (float_val_45 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = float_val_45;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xf))) {
            float_val_46 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (float_val_46 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = float_val_46;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets_pal();
        }
        int_val_93 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_val_93 == 0x10) || (int_val_93 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xb) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 8) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)v0), 1, 0.8f, 0.0f, 0.3f);
                    int_val_34 = coll_process_hit(0.9f, (s32)((TI128*)v0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (int_val_34 != 0) {
                        FastVecScale((s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (int_val_65 = 0; int_val_65 < int_val_34; int_val_65++) {
                            if (moby_is_in_special_class_range(((s32 *)g_impact_l19_moby_table)[int_val_65]) != 0) {
                                part_queue_impact_effect(((s32 *)g_impact_l19_moby_table)[int_val_65], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), 1.0f);
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
        float_val_135 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        float_val_93 = 0.0016000001f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9)) {
            float_val_93 = 0.004f;
        }
        float_val_135 = float_val_135 - float_val_93;
        if (float_val_135 < 0.0f) {
            float_val_135 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ptr_val_59 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) ptr_val_59, (s32) ptr_val_59, float_val_135);
        hero_apply_mode_transform((s32) ptr_val_59, (s32) ptr_val_59, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.46000004f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)v0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
        float_val_24 = vec_length_xy((s32)((TI128*)v0));
        if (float_val_24 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = float_val_24;
            if (float_val_24 < g_hero_speed_limits[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_speed_limits[0][1] * 0.020000001f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_speed_limits[1][1] * 0.020000001f;
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
            ClipHeroVelocityAtWall_pal(1);
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
                m = ((s32 *)g_impact_l19_moby_table)[k];
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
        ClipHeroVelocityAtWall_pal(0);
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
    case 0x79:                                      /* switch 1 */
        part_emit_hero_radial_particles_pal();
        vec_clear_128((s32)g_drive_velocity_view);
        ((Hero *)g_drive_velocity_view)->f[8/4] = -0.020000001f;
        break;
    case 0x8D:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ptr_val_36 = ((void*)g_hero_state) + 0xF0;
            hero_update_held_grab_pal();
            hero_resolve_stick_direction(1.0f, 0);
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            hero_approach_speed(0.0f, 0.00504f);
            vec_clear_128((s32) ptr_val_36);
            ClipHeroVelocityAtWall_pal(0);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) ptr_val_36, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
                hero_cancel_velocity_into_wall_pal();
                break;
            }
            hero_apply_mode_transform((s32) ptr_val_36, (s32) ptr_val_36, 0.0216f);
            break;
        }
        break;
    case 0x91:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->h[0x1E0/2] < 0x8) {
            if (g_hero_l19_busy_flag == 0) {
                if (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F) {
                    ((Hero *)g_hero_state)->h[0x1E0/2] = 0x21;
                    ((Hero *)g_hero_state)->i[0x229C/4] = 0;
                    ((Hero *)g_hero_state)->i[0x24A0/4] = 0;
                    hero_detach_from_object_pal(0);
                    FadeToBlack(0xd);
                    ((Hero *)g_hero_state)->c[0x22C1] = 1;
                }
            }
        }
        break;
    case 0x93:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
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
            if (shooter_update_ranged_attack_pal((s32) ptr_val_21) != 0) {
                hero_l19_set_state_pal(0x8D, 1);
            }
        }
        break;
    case 0x94:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.11000001f;
            hero_approach_velocity_pal(0.010000001f);
                    hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.0072000003f);
            break;
        }
        break;
    case 0x8F:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_update_held_grab_pal();
            hero_resolve_stick_direction(0.11500001f, 0);
            if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
                UpdateHeroVelocityForStateWithYawSpring_pal();
            }
            hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), 0.0048f);
            if (((Hero *)g_hero_state)->f[0xF8/4] < -0.20000002f) {
                ((Hero *)g_hero_state)->f[0xF8/4] = -0.20000002f;
            }
        }
        break;
    case 0x8E:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_resolve_stick_direction(0.11500001f, 0);
            hero_update_held_grab_pal();
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_update_turn_from_anim_pal();
            } else {
                ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
                qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
                float_val_125 = 0.12915438f;
                float_val_117 = 0.04752f;
                if (((Hero *)g_hero_state)->b[0x40F] != 0) {
                    float_val_125 = 0.16406098f;
                    float_val_117 = 0.053280003f;
                }
                hero_steer_heading(0, float_val_117, 0.21600002f, float_val_125);
            }
            hero_approach_speed(0.0072000003f, 0.008f);
            if (((Hero *)g_hero_state)->f[0x174/4] < 0.014f) {
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
                if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                    ((Hero *)g_hero_state)->b[0x40F] = 1U;
                }
            }
            float_val_66 = ReadPadFloatHistory(0);
            if ((FastDiffRots(float_val_66, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                    float_val_158 = 0.11500001f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.025464792f);
                    if (float_val_158 < 0.0f) {
                        float_val_158 = 0.0f;
                    }
                    if (float_val_158 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                        ((Hero *)g_hero_state)->f[0x1B0/4] = float_val_158;
                    }
                }
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x1440));
            } else {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x190));
            }
            ClipHeroVelocityAtWall_pal(1);
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
        if ((g_hero_l19_busy_flag == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            float_val_38 = vec_length_xy((s32)&((Hero *)g_hero_state)->b[0xF0]);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                float_val_38 = float_val_38 * 0.98800004f;
            } else {
                float_val_38 = float_val_38 * 0.90400004f;
            }
            func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), float_val_38);
            ptr_val_55 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            M2C_FIELD(ptr_val_55, s32* , 0xF8) = 0;
            if (M2C_FIELD(ptr_val_55, s16* , 0x34E) != 0) {
                hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0) + 0x30, 0.0088f);
            } else {
                hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.004f);
            }
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (stack_114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (stack_118 != M2C_FIELD(ptr_val_21, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
