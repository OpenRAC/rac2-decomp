#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern char g_pad_state[];
extern u8 g_pad_pressed_flags[];
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
extern f32 g_hero_l08_speed_params[][4] MACRO_ADDR;
extern s32 g_hero_l08_input_blocked MACRO_ADDR;
extern u8 g_hero_state_table_b[];
extern s32 g_frame_l08_counter MACRO_ADDR;
extern s32 g_ripple_water_id MACRO_ADDR;
extern s32 g_ripple_water_param MACRO_ADDR;
extern u8 g_hero_l08_extra_state[];
extern u8 g_hero_l08_matrix_block[];
extern u8 g_view_l08_space_height[];
extern u8 g_impact_l08_moby_list[];
extern u8 g_hero_l08_state_copy[];
extern Rec2C g_hero_l08_state_table[];
extern u8 g_hero_l08_blend_table[];
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
extern void ApproachHeroVelocity_pal(f32);
extern void ApplyHeroGravityAndJumpMotion_pal(void);
extern void hero_steer_airborne_by_state_pal(void);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_apply_mode_pose_offsets_pal(void);
extern void UpdateHeroLeanAndSwayParameters(void);
extern void hero_shrink_vector_by_amount(f32);
extern void hero_steer_reference_point_pal(void);
extern f32 hero_get_direction_angle_delta(s32, s32);
extern s32 hero_play_sound(s32, s32);
extern void snd_update_slot_object(s32, s32, s32);
extern void hero_try_surface_push_response(f32, f32, f32);
extern void part_emit_effects_at_nearby_mobys_pal(s32, s32);
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
extern s32 queue_copy_record_by_index(s32);
extern s32 func_L00_002EE4D8(s32, s32, f32);
extern s32 math_lerp_int(s32, s32, f32);
extern void level_init_pending_slot(s32, s32);
extern void level_append_record_to_table(s32, s32, s32, f32);
extern void moby_update_transform_history_followers(s32, s32);
extern void vec_add_offset(s32, s32, f32, f32, f32);
extern s32 math_update_angle_and_blend(s32, s32, s32, f32);
extern f32 ReadPadFloatHistory(s32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern s32 hero_get_weapon_animation_id(s32);
extern void ClipHeroVelocityAgainstWall_pal(s32);
extern char g_impact_effect_data[] MACRO_ADDR;
extern void moby_l00_raise_state_to_8();
extern void moby_raise_state_to_eight_copy();

/* Runs the hero's state handler each frame: walking, jumping, gliding and the other player actions (PAL version). */
void hero_l08_update_state_machine_pal(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 vec_0[4] __attribute__((aligned(16)));
    f32 vec_10[4] __attribute__((aligned(16)));
    f32 vec_20[4] __attribute__((aligned(16)));
    f32 vec_30[4] __attribute__((aligned(16)));
    f32 vec_40[4] __attribute__((aligned(16)));
    f32 vec_50[4] __attribute__((aligned(16)));
    f32 vec_60[4] __attribute__((aligned(16)));
    f32 vec_70[4] __attribute__((aligned(16)));
    f32 mat_80[16] __attribute__((aligned(16)));
    f32 vec_c0[4] __attribute__((aligned(16)));
    f32 vec_d0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* ref_1;
    void* ref_2;
    f32 fval_1;
    void* ref_3;
    s32 ival_1;
    void* ref_4;
    s32 ival_2;
    s32 ival_3;
    void* ref_5;
    s32 ival_4;
    void* ref_6;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 fval_2;
    f32 fval_3;
    f32 fval_4;
    f32 fval_5;
    f32 fval_6;
    f32 fval_7;
    f32 fval_8;
    s32 ival_5;
    f32 fval_9;
    s32 ival_6;
    f32 fval_10;
    f32 fval_11;
    f32 fval_12;
    s32 ival_7;
    s32 ival_8;
    s32 ival_9;
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
    f32 fval_159;
    f32 fval_160;
    f32 fval_161;
    f32 fval_162;
    f32 fval_163;
    f32 fval_164;
    f32 fval_165;
    f32 fval_166;
    f32 fval_167;
    f32 fval_168;
    f32 fval_169;
    s16 ival_10;
    s32 ival_11;
    s16 ival_12;
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
    s32 ival_81;
    s32 ival_82;
    s32 ival_83;
    s32 ival_84;
    s32 ival_85;
    s32* ref_7;
    s32* ref_8;
    u16 ival_86;
    u16 ival_87;
    u16 ival_88;
    u32 ival_89;
    u32 ival_90;
    u32 ival_91;
    u32 ival_92;
    u32 ival_93;
    u32 ival_94;
    u32 ival_95;
    u32 ival_96;
    u32 ival_97;
    u32 ival_98;
    u32 ival_99;
    u32 ival_100;
    u8 ival_101;
    u8 ival_102;
    u8 ival_103;
    u8 ival_104;
    void* ref_9;
    void* ref_10;
    void* ref_11;
    void* ref_12;
    void* ref_13;
    void* ref_14;
    void* ref_15;
    void* ref_16;
    void* ref_17;
    void* ref_18;
    void* ref_19;
    void* ref_20;
    void* ref_21;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* ref_22;
    void* ref_23;
    void* ref_24;
    void* ref_25;
    void* ref_26;
    void* ref_27;
    void* ref_28;
    void* ref_29;
    void* ref_30;
    void* ref_31;
    void* ref_32;
    void* ref_33;
    void* ref_34;
    void* ref_35;
    void* ref_36;
    void* ref_37;
    void* ref_38;
    void* ref_39;
    void* ref_40;
    void* ref_41;
    void* ref_42;
    void* ref_43;
    void* ref_44;
    void* ref_45;
    void* ref_46;
    void* ref_47;
    void* ref_48;
    void* ref_49;
    void* ref_50;
    void* ref_51;
    void* ref_52;
    void* ref_53;
    void* ref_54;
    void* ref_55;
    void* ref_56;
    void* ref_57;
    void* ref_58;
    void* ref_59;
    void* ref_60;
    void* ref_61;

    ival_7 = ((Hero *)g_hero_state)->i[0x2298/4];
    ref_21 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    ival_8 = (s32) M2C_FIELD(ref_21, u8* , 0x43);
    switch (((Hero *)g_hero_state)->u[0x2294/4]) {                              /* switch 1 */
    case 0x0:
    case 0x1:
    case 0x3:
    case 0x4:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x39:
    case 0x6D:
    case 0x6F:
    case 0x7D:
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
        ival_90 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((ival_90 == 1) || (ival_90 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vec_0) = 0;
                vec_0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vec_0), (s32)&g_hero_l08_matrix_block[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_l08_matrix_block)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (ival_102 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (ival_102 == 0xE)) || (ival_102 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.0028800003f, 0.10080001f, 0.13962635f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0069813184f) {
                    ival_16 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    ival_16 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != ival_16) {
                        set_hero_animation_pal(ival_16, 0, 4.0f);
                    }
                    fval_13 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 12.564863f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = fval_13;
                    if (fval_13 < 0.55f) {
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
            ival_99 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (ival_99 == 3) {
                fval_116 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (fval_116 > 1.0f) {
                    fval_116 = 1.0f;
                }
                ref_16 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                fval_142 = fval_116 * 0.0108f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = fval_142;
                if (M2C_FIELD(ref_16, u8* , 0x42) == M2C_FIELD(ref_16, u8* , 0x43)) {
                    fval_137 = ((Hero *)g_hero_state)->f[0x174/4] / fval_142;
                    if ((fval_137 > 4.0f) && ((f32) M2C_FIELD(ref_16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, fval_137, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (ival_99 == 4) {
                fval_142 = 0.0108f;
                if (((Hero *)g_hero_state)->b[0x1492] != 0) {
                    fval_142 = 0.00068000006f;
                }
            } else {
                fval_142 = 0.007080001f;
            }
            hero_approach_speed(0.0f, fval_142);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(fval_142);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                ival_62 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(ival_62, ival_62 + 0x30, 0.0088f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0216f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                ClipHeroVelocityAgainstWall_pal(0);
                if (((Hero *)g_hero_state)->h[0x34E/2] == 0) {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
                } else {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.010000001f);
                    hero_cancel_velocity_into_wall_pal();
                }
            }
        break;
    case 0x7C:
        hero7C = (void*)g_hero_state;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            ival_33 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = ival_33;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)ival_33 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)ival_33 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(ival_33, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            ival_53 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(ival_53, u16* , 0x34) = (u16) (M2C_FIELD(ival_53, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(6.0f);
        ival_55 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(ival_55, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(ival_55, u8* , 0x23) = 0x80U;
        }
        ival_17 = ((Hero *)hero7C)->i[0x7A4/4];
        ref_18 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)ival_17 + 0x10, (u8 *)ref_18 + 0x10);
        qcopy((u8 *)ival_17 + 0xF0, (u8 *)ref_18 + 0xF0);
        func_002A0F48(ival_17);
        }
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.90400004f);
        hero_update_height_offset_pal();
        break;
    case 0x32:
    case 0x33:
    case 0x34:
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x3b) {
                (*(u16*)&g_hero_state_machine_word) = 0xFFFF;
            }
            snd_update_slot_object(5, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xF);
            queue_copy_record_by_index(0x16);
        } else {
            ival_26 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (ival_26 != -1) {
                ref_17 = (ival_26 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(ref_17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ref_17, u8* , 0x74) != 0) {
                        snd_stop_voice(ival_26);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            ival_18 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects_pal((ival_18 >= 9) ? 8 : ival_18, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            fval_59 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (fval_59 > 0.0f) {
                if (fval_59 < 10.0f) {
                    EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ival_56 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (ival_56 < 0xc) {
                    EmitHeroRandomizedMotionEffects_pal(((s32) (0x11 - ival_56) / 3) + 1, 1, 0);
                }
            }
        }
        ival_57 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (ival_57 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == ival_57) {
                part_emit_hero_dust_and_debris_pal(3, 0x10, 0);
                if (g_ripple_water_id != 0) {
                    RippleDisturb(g_ripple_water_id, g_ripple_water_param, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x3a;
            }
            ival_40 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = ival_40;
            if (ival_40 >= 0x22) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.013962637f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.010471976f;
        fval_129 = 0.0f;
        
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            fval_131 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (fval_131 > 1.0f) {
                fval_131 = 1.0f;
            }
            if (fval_131 < 0.2f) {
                fval_131 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                ival_14 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                fval_131 = ((f32) (s16) ival_14 * 0.029411765f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) ival_14;
                if (fval_131 > 1.0f) {
                    fval_131 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (fval_131 < 0.35f)) {
                fval_131 = 0.35f;
            }
            fval_129 = fval_131 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            fval_130 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (fval_130 > 1.0f) {
                fval_130 = 1.0f;
            }
            if (fval_130 < 0.2f) {
                fval_130 = 0.2f;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = cntA40;
                fval_130 = ((f32) (s16) cntA40 * 0.029411765f) + 0.5f;
                if (fval_130 > 1.0f) {
                    fval_130 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                fval_130 = 1.0f;
            }
            fval_129 = fval_130 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                ival_13 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = ival_13;
                if ((s16) ival_13 >= 0x4c) {
                    ival_87 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (ival_87 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (ival_87 + 1);
                    }
                }
                ival_41 = (*(s32*)&g_frame_counter);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) (((s32)ival_41 * 5 + 2) / 6)) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) (((s32)ival_41 * 5 + 2) / 6);
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
            if ((g_frame_l08_counter - hp32->i[0xA54/4]) < 0x3a) {
                hp32->i[0xA50/4]++;
            }
            hp32->i[0xA54/4] = g_frame_l08_counter;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x3b) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            fval_129 = 0.0f;
        }
        fval_67 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), fval_129, (s32) (((void*)g_hero_state) + 0xA28), 0.0216f, 0.28800002f, stick_turn, 0);
        fval_89 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], fval_67);
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
        fval_165 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (fval_165 < 1.0f) {
                fval_165 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            fval_108 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                fval_108 = 0.4f;
            }
            if (fval_165 < fval_108) {
                fval_165 = fval_108;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * fval_165);
        }
        if (math_fast_float_d((s32)(g_hero_state + 0xA30)) != 0) {
            heroA30 = (void*)g_hero_state;
            moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 4, (s32)((TI128*)vec_0));
            (*(TI128*)vec_20) = 0;
            vec_20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), (s32) ((TI128*)vec_20));
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), 0.030000001f);
            FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32) ((TI128*)vec_20));
            vec_10[2] += 0.040000003f;
            part_spawn_bubble_pal((s32)((TI128*)vec_0), (s32) ((TI128*)vec_10), 25200.0f, -1.0f);
            if ((f32) math_random_int_below(0x64) < 40.0f) {
                ival_63 = 3;
                ival_67 = 0x9;
            } else {
                ival_63 = 0x21;
                ival_67 = 0x4b;
            }
            ((Hero *)heroA30)->i[0xA30/4] = math_random_int_range(ival_63, ival_67);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                ref_42 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (ref_42 != 0) {
                    if (M2C_FIELD(ref_42, s16* , 0xAA) == 0x261) {
                        for (ival_71 = 0; ival_71 < 4; ival_71++) {
                            moby_transform_joint_to_world((s32) ref_42, ival_71 % 2, (s32)((TI128*)vec_0));
                            (*(TI128*)vec_20) = 0;
                            vec_20[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), (s32) ((TI128*)vec_20));
                            vec_0[0] += math_random_float_range(0.0f, 0.03f);
                            vec_0[1] += math_random_float_range(0.0f, 0.03f);
                            vec_0[2] += math_random_float_range(0.0f, 0.03f);
                            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x110/16]);
                            vec_add_offset((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), -0.015000001f, ((Hero *)g_hero_state)->f[0x98/4], ((Hero *)g_hero_state)->f[0x94/4]);
                            ((Hero *)g_hero_state)->h[0xA38/2] = FloatToInt((0.14000002f - ((Hero *)g_hero_state)->f[0x1B4/4]) * 28.571424f);
                            part_spawn_bubble_pal((s32)((TI128*)vec_0), (s32) ((TI128*)vec_10), math_random_float_range(6300.0f, 9450.0f), -1.0f);
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
        fval_86 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        ival_91 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (ival_91 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], fval_86);
        } else if (ival_91 == 0x32) {
            fval_132 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l08_blend_table, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) && (fval_132 < 0.09f)) {
                fval_132 = 0.09f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), fval_132, ((Hero *)g_hero_state)->f[0x98/4], fval_86);
        } else if (ival_91 == 0x33) {
            fval_2 = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &fval_2, 0.0f, 0.0032000002f);
            } else {
                ApproachValue((s32) &fval_2, 0.0f, 0.0016000001f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), fval_2);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        ClipHeroVelocityAgainstWall_pal(0);
        fval_87 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(fval_86) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), fval_87, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.024434613f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        fval_93 = fval_89 * 47.0f;
        ((Hero *)g_hero_l08_state_copy)->f[0x114/4] = fval_93;
        ((Hero *)g_hero_l08_state_copy)->f[0x118/4] = (f32) (fval_87 * 1.5f);
        ((Hero *)g_hero_l08_state_copy)->f[0x110/4] = (f32) (fval_87 * 1.4f);
        if (fval_93 > 0.8726647f) {
            ((Hero *)g_hero_l08_state_copy)->f[0x114/4] = 0.8726647f;
        } else if (fval_93 < -0.8726647f) {
            ((Hero *)g_hero_l08_state_copy)->f[0x114/4] = -0.8726647f;
        }
        fval_60 = fval_89 * 40.0f;
        fval_34 = fval_87 * 1.1f;
        ((Hero *)g_hero_l08_state_copy)->f[0x364/4] = 0.03f;
        ((Hero *)g_hero_l08_state_copy)->f[0x368/4] = 0.22f;
        ((Hero *)g_hero_l08_state_copy)->f[0x324/4] = fval_60;
        ((Hero *)g_hero_l08_state_copy)->f[0x328/4] = fval_34;
        ((Hero *)g_hero_l08_state_copy)->f[0x414/4] = 0.03f;
        ((Hero *)g_hero_l08_state_copy)->f[0x418/4] = 0.22f;
        ((Hero *)g_hero_l08_state_copy)->f[0x3D4/4] = fval_60;
        ((Hero *)g_hero_l08_state_copy)->f[0x3D8/4] = fval_34;
        break;
    case 0x73:
        ival_19 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        ref_29 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects_pal((ival_19 >= 9) ? 8 : ival_19, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) ref_29, (s32) ref_29, vec_length_xy((s32) ref_29) * 0.90400004f);
        ClipHeroVelocityAgainstWall_pal(0);
        break;
    case 0x72:
        part_spawn_jittered_after_delay(0xF, 0x1E);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.90400004f);
        ClipHeroVelocityAgainstWall_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x67:
    case 0x7F:
        fval_3 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &fval_3, 0.0f, 0.0016000001f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), fval_3);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            ref_37 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(ref_37, s32* , 0x2290), 4, (s32)((TI128*)vec_0));
            (*(TI128*)vec_20) = 0;
            vec_20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), M2C_FIELD(ref_37, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), (s32) ((TI128*)vec_20));
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), 0.030000001f);
            FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32) ((TI128*)vec_20));
            vec_10[2] += 0.040000003f;
            part_spawn_bubble_pal((s32)((TI128*)vec_0), (s32) ((TI128*)vec_10), 25200.0f, -1.0f);
            ival_42 = M2C_FIELD(ref_37, s32* , 0x1B8);
            if (ival_42 < 0x21) {
                lim67 = 5;
                ival_76 = math_random_int_range(2, 4) + ((s32) M2C_FIELD(ref_37, s32* , 0x1B8) / lim67);
                goto block_224;
            }
            if (ival_42 >= 0x3b) {
                ival_76 = math_random_int_range(0x8, 0x11);
block_224:
                M2C_FIELD(ref_37, s32* , 0xA30) = ival_76;
            }
        }
        if (((Hero *)g_hero_state)->f[0xA3C/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xA3C/4] = 0.0f;
        }
        ApproachValue((s32) (((void*)g_hero_state) + 0xA3C), -0.030000001f, 0.0006f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) ((Hero *)g_hero_state)->f[0xA3C/4];
        break;
    case 0x35:
    case 0x36:
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
            ival_20 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects_pal((ival_20 >= 7) ? 6 : ival_20, 0, 0);
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
            fval_78 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l08_blend_table, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * fval_78);
            fval_36 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * fval_78;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = fval_36;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            fval_61 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((fval_61 > 0.0f) && (fval_61 < 10.0f)) {
                EmitHeroRandomizedMotionEffects_pal(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.00168f);
        ClipHeroVelocityAgainstWall_pal(0);
        hero_update_height_offset_pal();
        break;
    case 0x85:
        ref_19 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)ref_19 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)ref_19 + 0xF0);
        break;
    case 0x2F:
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
            ref_50 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(ref_50, u8* , 0x60) & 2) && (M2C_FIELD(ref_50, u8* , 0x42) == 0x36)) {
                set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 4.0f);
            }
        }
        break;
    case 0x8A:
    case 0x8B:
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
        ref_61 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (ref_61 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ref_61, f32* , 0x10) - M2C_FIELD(ref_21, f32* , 0x10), M2C_FIELD(ref_61, f32* , 0x14) - M2C_FIELD(ref_21, f32* , 0x14));
            hero_steer_heading(0, 0.028800001f, 0.21600002f, 0.12566373f);
        }
        break;
    case 0x23:
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
        ref_1 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (ref_1 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ref_1, f32* , 0x10) - M2C_FIELD(ref_21, f32* , 0x10), M2C_FIELD(ref_1, f32* , 0x14) - M2C_FIELD(ref_21, f32* , 0x14));
            hero_steer_heading(0, 0.028800001f, 0.21600002f, 0.12566373f);
        }
        break;
    case 0x24:
        qcopy(vec_0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        fval_37 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_0));
        ((Hero *)g_hero_state)->f[0xAB0/4] = fval_37;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 5e1f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (fval_37 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        ival_43 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (ival_43 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.54f, 0.032f);
            ref_46 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            fval_147 = mat_fast_helper_a(M2C_FIELD(ref_46, f32* , 0x10) - M2C_FIELD(ref_21, f32* , 0x10), M2C_FIELD(ref_46, f32* , 0x14) - M2C_FIELD(ref_21, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], fval_147) > 1.5707964f) {
                    fval_147 = FastAddRotations(fval_147, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = fval_147;
            hero_steer_heading(0, 0.0432f, 0.21600002f, 0.14660768f);
        } else if (ival_43 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.016800001f);
        }
        if ((math_solve_quadratic((s32) &fval_4, (s32) &fval_5, -0.008400001f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (fval_4 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = fval_4;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 17.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.0767945f);
        } else {
            turn24 = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_0)), vec_0[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn24, 0.12915438f);
        }
        vec_20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        fval_38 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        vec_20[2] = 0;
        vec_20[1] = fval_38;
        FastVecAdd((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)vec_10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vec_20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vec_10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        fval_39 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (fval_39 < 25.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((25.0f - fval_39) * 0.011600001f));
        }
        break;
    case 0x25:
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.20000002f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.006f);
        qcopy(vec_0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)vec_0));
        FastVecAdd((s32) ((TI128*)vec_10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_10), (s32)((TI128*)vec_0));
        vec_scale_to_length((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vec_20), (s32)((TI128*)vec_0), (s32) ((TI128*)vec_30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(ref_21, u8* , 0x43) == 0x34)) {
            set_hero_animation_pal(0x35, 0xA, 1e1f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        ref_51 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        fval_92 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (ref_51 != 0) {
            ref_47 = M2C_FIELD(ref_51, void** , 0x68);
            if ((ref_47 != 0) && (M2C_FIELD(ref_47, s32* , 0x34) != 0)) {
                fval_148 = M2C_FIELD(ref_51, f32* , 0xF8);
                if (FastDiffRots(fval_148, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    fval_148 = FastAddRotations(fval_148, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), fval_148, (s32) (((void*)g_hero_state) + 0xAF8), 0.028800001f, 0.43200004f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.028800001f, 0.43200004f, 0.094247796f);
        FastVecSub((s32)((TI128*)vec_0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), 1.0f);
        if (vec_0[2] < 0.23f) {
            vec_0[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)vec_20));
        vec_20[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vec_40), (s32) ((TI128*)vec_20));
        matrix_from_basis_rows((s32) ((TI128*)mat_80), (s32) ((TI128*)vec_40));
        transform_vector((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), (s32) ((TI128*)mat_80));
        vec_10[0] = -mat_fast_helper_a(square_root((vec_0[0] * vec_0[0]) + (vec_0[2] * vec_0[2])), vec_0[1]);
        fval_40 = mat_fast_helper_a(vec_0[2], vec_0[0]);
        vec_10[1] = fval_40;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), fval_40, (s32) (((void*)g_hero_state) + 0xA4), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), vec_10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        ival_74 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((ival_74 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x22) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                fval_149 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0042000003f;
                if (fval_149 > 0.10000001f) {
                    fval_149 = 0.10000001f;
                }
                vec_30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * fval_149;
                fval_41 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * fval_149;
                ref_9 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vec_30[2]) = 0;
                vec_30[1] = fval_41;
                FastVecAdd((s32) ref_9, (s32) ref_9, (s32) ((TI128*)vec_30));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                ref_38 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) ref_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    ref_30 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) ref_30, (s32) (((void*)g_hero_state) + 0x110), 0.016f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) ref_30) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vec_30), (s32) ref_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) ref_30, (s32) ref_30, 0.0228f);
                    }
                }
                fval_79 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.0003f;
                FastVecScale((s32) ((TI128*)vec_30), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_30), fval_79);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_30));
            }
        }
        ref_48 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (ref_48 != 0) {
            ref_22 = M2C_FIELD(ref_48, void** , 0x68);
            ref_31 = ((void*)g_hero_state) + 0xF0;
            if (ref_22 != 0) {
                fval_42 = FastVecLength((s32) ref_31);
                fval_43 = M2C_FIELD(ref_22, f32* , 0xC);
                fval_6 = fval_42;
                if (fval_43 < fval_42) {
                    ApproachValue((s32) &fval_6, fval_43, 0.006f);
                    vec_scale_to_length((s32) ref_31, (s32) ref_31, fval_6);
                }
            }
        }
        fval_14 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        ref_44 = ((void*)g_hero_state) + 0x80;
        ref_43 = ((void*)g_hero_state) + 0xF0;
        vec_d0[0] = math_fast_sin_or_cos_a(fval_14) * 0.15f;
        fval_15 = math_fast_sin_or_cos_b(fval_14) * 0.15f;
        (*(s32*)&vec_d0[2]) = 0;
        vec_d0[1] = fval_15;
        FastVecAdd((s32) &vec_d0[0], (s32) &vec_d0[0], (s32) ref_44);
        FastVecAdd((s32) ((TI128*)vec_30), (s32) &vec_d0[0], (s32) ref_43);
        FastVecSub((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vec_30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vec_c0));
        FastVecSub((s32) ref_43, (s32) ((TI128*)vec_30), (s32) &vec_d0[0]);
        fval_80 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        fval_81 = ((Hero *)g_hero_state)->f[0xAE4/4] - fval_80;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vec_c0))) {
            vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), fval_81);
            FastVecAdd((s32) ref_44, (s32) ref_44, (s32) ((TI128*)vec_c0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (ival_74 != 0)) {
            min2B = 0.28000003f;
            fval_16 = vec_length_xy((s32) ref_43);
            fval_7 = fval_16;
            if (fval_16 < min2B) {
                math_spring_float_to_goal((s32) &fval_7, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.06768f, 0.43200004f, 0.0f);
                vec_30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                fval_17 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vec_30[2] = 0.0f;
                vec_30[1] = fval_17 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) ref_43, (s32) ref_43, (s32) ((TI128*)vec_30));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((fval_92 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            fval_82 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            ival_12 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (ival_12 != 0) {
                ival_77 = ival_12 == 1;
            } else {
                (*(TI128*)vec_30) = ((Hero *)g_hero_state)->q[0x110/16];
                ival_77 = hero_get_speed_along_forward((s32) ((TI128*)vec_30)) > 0.0f;
            }
            if (ival_77 != 0) {
                if (M2C_FIELD(ref_21, u8* , 0x43) != 0x35) {
                    set_hero_animation_pal(0x35, 6, 14.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    ref_49 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(ref_49, u8* , 0x42) == M2C_FIELD(ref_49, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, fval_82, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(ref_21, u8* , 0x43) != 0x35) {
                set_hero_animation_pal(0x35, 0x15, 7.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                ref_45 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(ref_45, u8* , 0x42) == M2C_FIELD(ref_45, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, fval_82, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l08_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            ival_21 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (ival_21 != 0) {
                fval_62 = vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), ival_21 + 0x10);
                ival_83 = 0;
                if ((((Hero *)g_hero_state)->b[0x1496] != 0) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->b[0x1495] != 0)) {
                    ival_83 = 1;
                }
                if (((fval_62 > 2.0f) && (fval_62 < 5.0f)) || (ival_83 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
                }
                hero_approach_speed(0.0016000001f, 0.0016000001f);
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            } else {
                hero_approach_speed(0.00080000004f, 0.00080000004f);
                ref_10 = ((void*)g_hero_state) + 0xF0;
                cam_set_view_space_vector_length((s32) ref_10, (s32) ref_10, ((Hero *)g_hero_state)->f[0x1B4/4]);
            }
        } else {
            ival_72 = 0;
            if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
                ival_72 = 1;
            }
            ival_22 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (ival_22 != 0) {
                FastVecSub((s32)((TI128*)vec_0), ival_22 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                fval_18 = cam_get_view_space_vector_length((s32)((TI128*)vec_0));
                if (((fval_18 > 2.0f) && (fval_18 < 5.0f)) || (ival_72 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
                }
                hero_approach_speed(0.010000001f, 0.010000001f);
                vec_scale_to_length((s32) ((TI128*)vec_10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
                cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_10));
            } else {
                if ((ival_72 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3a)) {
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
        fval_63 = ((Hero *)g_hero_state)->f[0x31C/4];
        fval_155 = 0.15400001f;
        if (fval_63 > 2.25f) {
            fval_155 = 0.07700001f;
        } else if (fval_63 > 1.8f) {
            fval_155 = 0.10780001f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(vec_0, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), -0.5f);
            vec_scale_to_length((s32) &vec_40[0], (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vec_10), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &vec_40[0]);
            vec_10[3] = 5627.925f;
            (*(u8*)((u8*)vec_20+9)) = 1;
            (*(u16*)((u8*)vec_20+10)) = 0x47;
            (*(u8*)((u8*)vec_20+8)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)vec_0), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vec_10));
        }
        if (math_is_below_plane_within_depth(25.7f) != 0) {
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x2a;
            if (g_hero_override_flag != 0) {
                ((Hero *)g_hero_l08_extra_state)->f[0x180/4] = 0.1f;
                ((Hero *)g_hero_l08_extra_state)->i[0x188/4] = 0x19;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x1d;
                ((Hero *)g_hero_l08_extra_state)->i[0x16C/4] = 0;
            }
        }
        ival_44 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xc;
        if (ival_44 < 7) {
            ref_23 = ((void*)g_hero_state) + 0xF0;
            fval_8 = cam_get_view_space_height((s32) ref_23);
            ApproachValue((s32) &fval_8, fval_155, 0.060000002f);
            cam_set_view_space_height((s32) ref_23, (s32) ref_23, fval_8);
        } else if (ival_44 > lim3) {
            ref_32 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ref_32, (s32) ref_32, 0.052f);
            if (cam_get_view_space_height((s32) ref_32) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            fval_150 = -0.74000007f;
            if (g_hero_l08_input_blocked != 0) {
                fval_150 = -1.4000001f;
            }
            if (cam_get_view_space_height((s32) ref_32) < fval_150) {
                cam_set_view_space_height((s32) ref_32, (s32) ref_32, fval_150);
            }
        }
        break;
    case 0x15:
    case 0x83:
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l08_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ival_65 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x12);
        if (ival_65 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                ival_73 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    ref_24 = ((void*)g_hero_state) + 0xBC0;
                    fval_151 = hero_get_direction_angle_delta((s32) ref_24, 0);
                    fval_109 = hero_get_direction_angle_delta((s32) ref_24, 1);
                } else {
                    fval_151 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    fval_109 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (fval_109 < 4.3633237f) {
                    ival_73 = 1;
                }
                if (fval_151 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (fval_109 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (ival_73 != 0) {
                    hero_steer_heading(1, 0.08208001f, 0.28800002f, 0.33859393f);
                } else {
                    hero_steer_heading(0, 0.08208001f, 0.28800002f, 0.33859393f);
                }
            } else {
                    ival_66 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xa)) {
                        ival_66 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        ival_66 = 0;
                    }
                    if (ival_66 != 0) {
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
                fval_156 = 0.050000004f;
                fval_83 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&g_pad_pressed_flags) & 8) {
                    fval_156 = 0.060000002f;
                }
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(fval_83) * fval_156));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(fval_83) * fval_156));
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
    case 0x13:
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l08_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            hero_steer_reference_point_pal();
            break;
        }
        ival_23 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ref_39 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_l08_state_table;
        if ((ival_23 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 3)) {
            ref_33 = ((void*)g_hero_state) + 0x80;
            fval_119 = vec_distance_xy(ival_23 + 0x10, (s32) ref_33);
            if ((*(s32*)&g_hero_l08_input_blocked) != 0) {
                fval_119 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) ref_33);
            }
            fval_119 = fval_119 - 0.5f;
            if (fval_119 < 0.0f) {
                fval_119 = 0.0f;
            }
            ival_45 = M2C_FIELD(ref_39, s32* , 4);
            if (ival_45 == 0) {
                fval_110 = 0.75f;
                fval_157 = 0.8f;
                fval_162 = 4.0f;
            } else if (ival_45 == 1) {
                fval_110 = 0.6f;
                fval_157 = 1.7f;
                fval_162 = 4.0f;
            } else {
                fval_110 = 1.3f;
                fval_157 = 1.7f;
                fval_162 = 1.9f;
            }
            fval_84 = fval_119 - fval_110;
            if (math_fabs(fval_84) < (fval_157 + 3.0f)) {
                fval_121 = fval_84 * 1.1111112f;
                if (fval_162 < fval_121) {
                    fval_121 = fval_162;
                }
                if (fval_121 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = fval_121;
                }
            }
        }
        ival_46 = M2C_FIELD(ref_39, s32* , 4);
        switch (ival_46) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.08800001f;
            }
            break;
        case 1:
            fval_64 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (fval_64 < 9.0f)) {
                if (fval_64 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.060000002f;
                } else if (fval_64 > 7.0f) {
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
            fval_111 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            fval_111 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        fval_65 = math_fabs(fval_111);
        if ((M2C_FIELD(ref_39, s32* , 4) == 1) && (fval_111 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (fval_65 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
    } else {
        ival_84 = 1;
        if ((M2C_FIELD(ref_39, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            ival_84 = 0;
        }
        if (ival_84 != 0) {
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
            ref_11 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ref_11, (s32) ref_11, 0.0216f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.0096f);
        if ((*(s32*)&g_hero_l08_input_blocked) != 0) {
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
    case 0x1F:
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
        } else if (((Hero *)g_hero_state)->i[0x1B8/4] < 3) {
            hero_l00_select_aim_target(11.0f, 0.8726647f, -1.0f);
        }
        lim = 0x8;
        lim2 = 0xF;
        ival_47 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (ival_47 > lim) {
            if (ival_47 < 0xf) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.36f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 7) && (((Hero *)g_hero_state)->f[0x184/4] < 0.40000004f)) {
            ref_25 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ref_25);
            level_append_record_to_table((s32) ref_25, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) ref_25, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) ref_25, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)g_hero_state)->i[0x1B8/4] > lim2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), sel1F);
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            ival_48 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((ival_48 > lim) && (ival_48 < 0xe) && (((Hero *)g_hero_state)->f[0x178/4] < 0.17000002f)) {
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
            ival_49 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((ival_49 > lim) && (ival_49 < 0x12)) {
                ref_40 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (ref_40 != 0) {
                    ref_34 = ((void*)g_hero_state) + 0x80;
                    vec_30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec_0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vec_30));
                    (*(u8*)((u8*)vec_10+9)) = 3;
                    vec_0[3] = 5627.925f;
                    (*(u8*)((u8*)vec_10+8)) = 0;
                    fval_90 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vec_10+10)) = M2C_FIELD(ref_40, u16* , 0xAA);
                    vec_40[0] = math_fast_sin_or_cos_a(fval_90) * 0.8f;
                    fval_19 = math_fast_sin_or_cos_b(fval_90) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = fval_19;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ref_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ref_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ref_40, (s32)((TI128*)vec_0)));
                    fval_90 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(fval_90) * 0.8f;
                    fval_21 = math_fast_sin_or_cos_b(fval_90) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = fval_21;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ref_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ref_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec_0)));
                    fval_90 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(fval_90) * 0.8f;
                    fval_23 = math_fast_sin_or_cos_b(fval_90) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = fval_23;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ref_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ref_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ref_40, (s32)((TI128*)vec_0)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ClipHeroVelocityAgainstWall_pal(1);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x120, 0.0088f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.0216f);
        break;
    case 0x22:
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
    case 0x2:
    case 0x70:
        ival_60 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            ival_60 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (ival_60 != 0)) {
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
            fval_85 = ReadPadFloatHistory(1);
            if ((FastDiffRots(fval_85, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            (*(TI128*)vec_0) = ((Hero *)g_hero_state)->q[0xA60/16];
            fval_66 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vec_0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = fval_66;
            if (fval_66 < 0.014f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.014f;
            }
            vec_clear_128((s32) pA60);
        }
        fval_152 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim_pal();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.028800001f, 0.24480002f, 0.19896756f);
            } else {
                fval_94 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (fval_94 > 0.78539824f)) {
                    fval_152 = 0.0f;
                }
                hero_set_turn_rates_pal();
            }
        }
        hero_apply_mode_pose_offsets_pal();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            fval_166 = 0.119f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.03501409f);
            if (fval_166 < 0.0f) {
                fval_166 = 0.0f;
            }
            if (fval_166 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = fval_166;
            }
        }
        k005 = fval_152 * 0.0072000003f;
        fval_153 = 0.008f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            fval_138 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (fval_138 > 1.0f) {
                fval_138 = 1.0f;
            }
            if (fval_138 < 0.2f) {
                fval_138 = 0.2f;
            }
            fval_153 = 0.0068000006f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * fval_138);
        }
        fval_95 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (fval_95 > 0.6108653f)) {
            fval_139 = 1.0f - (fval_95 * 0.4f);
            if (fval_139 < 0.0f) {
                fval_139 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * fval_139);
        }
        hero_approach_speed(k005, fval_153);
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
        ClipHeroVelocityAgainstWall_pal(1);
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
    case 0x7B:
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        hero_resolve_stick_direction(1.0f, 0);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.23000002f;
        pad_clamp_stick_to_unit_range((s32)((TI128*)vec_0), (s32) (((void*)g_hero_state) + 0x9F0), 0.24480002f);
        fval_158 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.024434613f) * vec_0[0];
        if ((*(s32*)&g_hero_l08_input_blocked) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x32) {
                fval_158 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.6f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, fval_158);
        }
        hero_approach_speed(0.040000003f, 0.006f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&g_hero_l08_input_blocked) != 0) {
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0xA00), 0.057600003f, 0.43200004f, 0.15f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.057600003f, 0.43200004f, 0.15f);
        }
        FastVecScale((s32) ((TI128*)vec_10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32)(g_hero_state + 0xE0));
        ival_34 = coll_process_hit(0.57f, (s32) ((TI128*)vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (ival_34 != 0) {
            FastVecScale((s32) ((TI128*)vec_20), (s32)(g_hero_state + 0x110), 7.0f);
            for (ival_69 = 0; ival_69 < ival_34; ival_69++) {
                if (moby_is_in_special_class_range(((s32 *)g_impact_l08_moby_list)[ival_69]) != 0) {
                    part_queue_impact_effect(((s32 *)g_impact_l08_moby_list)[ival_69], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.024480002f, 0.43200004f);
        cam_set_limits_third(0.036000002f, 0.43200004f);
        cam_set_limits_fourth(0.0432f, 0.38880002f);
        fval_167 = fval_158 * 27.0f;
        if (fval_167 > 1.7f) {
            fval_167 = 1.7f;
        } else if (fval_167 < -1.7f) {
            fval_167 = -1.7f;
        }
        fval_24 = fval_167 * 0.5f;
        ((Hero *)g_hero_l08_state_copy)->f[0x60/4] = (f32) -fval_167;
        ((Hero *)g_hero_l08_state_copy)->f[0x278/4] = fval_24;
        ((Hero *)g_hero_l08_state_copy)->f[0x1C8/4] = fval_24;
        break;
    case 0x2E:
        hero_steer_reference_point_pal();
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        ival_103 = M2C_FIELD(ref_21, u8* , 0x43);
        if (ival_103 == 0x37) {
            fval_112 = 1.4f;
            fval_154 = ((Hero *)g_hero_state)->f[0x1A8/4];
            if ((fval_154 > 1.4f) || (fval_112 = -1.4f, (fval_154 < -1.4f))) {
                fval_154 = fval_112;
            }
            ((Hero *)g_hero_l08_state_copy)->f[0x60/4] = (f32) (fval_154 * -0.14f);
            ((Hero *)g_hero_l08_state_copy)->f[0x118/4] = (f32) (fval_154 * 0.3f);
            ((Hero *)g_hero_l08_state_copy)->f[0x1C0/4] = (f32) (fval_154 * -0.22f);
            ((Hero *)g_hero_l08_state_copy)->f[0x278/4] = (f32) (fval_154 * 0.4f);
            ((Hero *)g_hero_l08_state_copy)->f[0x274/4] = (f32) (math_fabs(fval_154) * -0.09f);
            ((Hero *)g_hero_l08_state_copy)->f[0x270/4] = (f32) (math_fabs(fval_154) * 0.08f);
        } else if (ival_103 == 0x66) {
            fval_91 = FastAddRotations(fast_subtract_rotations(mat_fast_helper_a(((Hero *)g_hero_state)->f[0x110/4], ((Hero *)g_hero_state)->f[0x114/4]), ((Hero *)g_hero_state)->f[0x98/4]), 3.1415927f);
            fval_159 = ((Hero *)g_hero_state)->f[0x174/4] * 5.8177648f;
            if (fval_159 > 0.43633235f) {
                fval_159 = 0.43633235f;
            }
            fval_68 = math_fast_sin_or_cos_a(fval_91) * fval_159;
            fval_25 = -math_fast_sin_or_cos_b(fval_91);
            ((Hero *)g_hero_l08_state_copy)->f[0x114/4] = fval_68;
            ((Hero *)g_hero_l08_state_copy)->f[0x110/4] = (f32) (fval_25 * fval_159);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            fval_122 = 0.010000001f;
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x110), fval_122);
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.060000002f);
            break;
        }
        break;
    case 0x17:
    case 0x18:
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
    case 0x19:
    case 0x1A:
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
        if ((ProbeLedgeGrab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (ProbeLedgeGrab_pal((s32) &vec_50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec_0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec_0), (s32)(g_hero_state + 0x80));
            ival_81 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            ival_85 = (s32)g_hero_state_table_b;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(ival_81 + ival_85) * 0.5f);
        }
        break;
    case 0x76:
        ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.11000001f;
        ApproachHeroVelocity_pal(0.010000001f);
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.0072000003f);
        break;
    case 0x6:
    case 0x2C:
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2C) {
            fval_124 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                fval_124 = 0.43633235f;
            }
            qcopy(vec_0, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &vec_0[1], fval_124, (s32) (((void*)g_hero_state) + 0xA4), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            math_approach_with_velocity((s32)((TI128*)vec_0), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_update_target_speed_pal();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_steer_airborne_by_state_pal();
        }
        ref_60 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets_pal();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) ref_60, (s32) ref_60, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ref_60) < -1.0000001f) {
            cam_set_view_space_height((s32) ref_60, (s32) ref_60, -1.0000001f);
        }
        break;
    case 0x74:
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        ref_2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0034906592f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0034906592f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ref_2, (s32) ref_2, vec_length_xy((s32) ref_2) * 0.88f);
        hero_apply_mode_transform((s32) ref_2, (s32) ref_2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ref_2) < -1.0000001f) {
            cam_set_view_space_height((s32) ref_2, (s32) ref_2, -1.0000001f);
        }
        break;
    case 0x82:
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.0003490659f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        ival_61 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            ival_61 = 0;
        }
        if (ival_61 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.120000005f);
            ref_13 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) ref_13, (s32) ref_13, 0.036000002f);
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
        fval_46 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x4b) && (fval_46 < 0.0f) && (fval_98 = ((Hero *)g_hero_state)->f[0x31C/4], (fval_98 < 1.2f))) {
            fval_102 = (fval_98 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (fval_102 < 0.0f) {
                fval_102 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), fval_46 * fval_102);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.03888f, 0.43200004f, 0.10000001f);
            }
        } else if (fval_46 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&g_view_l08_space_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets_pal();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.24000001f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.03888f, 0.43200004f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.10471977f);
        fval_125 = 0.002f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            fval_125 = 0.00080000004f;
        }
        ApproachHeroVelocity_pal(fval_125);
        break;
    case 0x8:
        if (hero_slot_item_id(3) == 2) {
            ival_28 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (ival_28 != -1) {
                ref_14 = (ival_28 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ref_14, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ref_14, u8* , 0x74) != 0)) {
                    snd_stop_voice(ival_28);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            ival_29 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (ival_29 != -1) {
                ref_15 = (ival_29 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ref_15, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ref_15, u8* , 0x74) != 0)) {
                    snd_stop_voice(ival_29);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        fval_163 = 0.060000002f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            fval_163 = 0.10000001f;
        }
        fval_164 = 0.72f;
        fval_53 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            fval_163 = 0.15400001f;
            fval_164 = 0.98640007f;
        }
        if (fval_53 != 0.0f) {
            fval_164 = fval_53;
        }
        ref_27 = ((void*)g_hero_state) + 0xF0;
        fval_12 = cam_get_view_space_height((s32) ref_27);
        hero_resolve_stick_direction(fval_163, 0);
        hero_steer_heading(0, 0.036000002f, 0.43200004f, 0.25132746f);
        hero_approach_speed(0.006f, 0.0028000001f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets_pal();
        cam_project_vector_onto_view_plane((s32) ref_27, (s32) ref_27);
        math_spring_float_to_goal((s32) &fval_12, (s32) (((void*)g_hero_state) + 0xA98), -fval_163 * fval_164, 0.036000002f, 0.43200004f, 0.34000003f);
        hero_apply_mode_transform((s32) ref_27, (s32) ref_27, -fval_12);
        fval_47 = ((Hero *)g_hero_state)->f[0x88/4];
        if (fval_47 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), fval_47, 0.080000006f);
        }
        ProbeHeroAirborneWallContact_pal();
        break;
    case 0x7:
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x1B:
    case 0x38:
    case 0x45:
    case 0x48:
    case 0x5B:
    case 0x66:
    case 0x6E:
    case 0x81:
    case 0x89:
    case 0x92:
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
                if (g_ripple_water_id != 0) {
                    RippleDisturb(g_ripple_water_id, g_ripple_water_param, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            fval_54 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((fval_54 >= 4.0f) && (fval_54 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects_pal(7, 0, 0);
            }
        }
        ival_10 = ((Hero *)g_hero_state)->h[0x4AC/2];
        ival_25 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (ival_25 == ival_10) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((ival_25 < ival_10) && (ival_97 = ((Hero *)g_hero_state)->u[0x2294/4], (ival_97 != 0xB)) && (ival_97 != 0x10) && (ival_97 != 0xC) && (ival_97 != 0x11) && (ival_97 != 0x1B) && (ival_97 != 0x89) && (ival_97 != 0x48))) {
            if (((Hero *)g_hero_state)->h[0x528/2] != 0) {
                hero_steer_reference_point_pal();
                if ((((Hero *)g_hero_state)->u[0x2294/4] == 0xA) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x8) && (((Hero *)g_hero_state)->f[0x178/4] < 0.14000002f)) {
                    ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.014f));
                    ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.014f));
                    qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
                }
            } else {
                hero_steer_heading(0, 0.0216f, 0.28800002f, 0.30019668f);
                fval_74 = ((Hero *)g_hero_state)->f[0x1B4/4];
                if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                    ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (fval_74 * 0.4f);
                }
                if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                    hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
                } else {
                    hero_compute_push_direction(99999.0f);
                }
                ((Hero *)g_hero_state)->f[0x1B4/4] = fval_74;
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
                    ival_51 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (ival_51 < (((Hero *)g_hero_state)->h[0x4AC/2] + 3)) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) ival_51 * 0.0064000003f);
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                    ival_52 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (ival_52 < 0x1c) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) ival_52 * 0.021200001f);
                    }
                }
                if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0x8) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                    qcopy(vec_0, &((Hero *)g_hero_state)->q[0x80/16]);
                    cam_offset_point_in_view_space((s32)((TI128*)vec_0), (s32)((TI128*)vec_0), 0.5f);
                    cam_offset_point_by_side_direction((s32) ((TI128*)vec_10), (s32)((TI128*)vec_0), 0.95f);
                    if (CollLine((s32)((TI128*)vec_0), (s32) ((TI128*)vec_10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)g_hero_state)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            hero_steer_airborne_by_state_pal();
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
                ref_28 = ((void*)g_hero_state) + 0xF0;
                fval_103 = vec_length_xy((s32) ref_28);
                if (fval_103 > 0.07400001f) {
                    fval_103 = 0.07400001f;
                }
                vec_fast_normalize_helper((s32) ref_28, (s32) ref_28, fval_103);
            }
        }
        fval_55 = ((Hero *)g_hero_state)->f[0x318/4];
        fval_99 = ((Hero *)g_hero_state)->f[0x490/4];
        if (fval_99 < fval_55) {
            fval_33 = fval_99 + 0.120000005f;
            ((Hero *)g_hero_state)->f[0x490/4] = fval_33;
            if (fval_55 < fval_33) {
                ((Hero *)g_hero_state)->f[0x490/4] = fval_55;
            }
        }
        fval_56 = ((Hero *)g_hero_state)->f[0x88/4];
        if (fval_56 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = fval_56;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xf))) {
            fval_57 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (fval_57 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = fval_57;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets_pal();
        }
        ival_98 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((ival_98 == 0x10) || (ival_98 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xb) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 8) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vec_0), 1, 0.8f, 0.0f, 0.3f);
                    ival_39 = coll_process_hit(0.9f, (s32)((TI128*)vec_0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (ival_39 != 0) {
                        FastVecScale((s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (ival_70 = 0; ival_70 < ival_39; ival_70++) {
                            if (moby_is_in_special_class_range(((s32 *)g_impact_l08_moby_list)[ival_70]) != 0) {
                                part_queue_impact_effect(((s32 *)g_impact_l08_moby_list)[ival_70], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        ApplyHeroGravityAndJumpMotion_pal();
        ProbeHeroAirborneWallContact_pal();
        break;
    case 0x16:
        fval_146 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        fval_104 = 0.0016000001f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x9)) {
            fval_104 = 0.004f;
        }
        fval_146 = fval_146 - fval_104;
        if (fval_146 < 0.0f) {
            fval_146 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ref_59 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) ref_59, (s32) ref_59, fval_146);
        hero_apply_mode_transform((s32) ref_59, (s32) ref_59, 0.004f);
        break;
    case 0x8C:
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.46000004f;
        break;
    case 0x62:
        FastVecSub((s32)((TI128*)vec_0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_0[0], vec_0[1]);
        fval_35 = vec_length_xy((s32)((TI128*)vec_0));
        if (fval_35 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_0[0], vec_0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = fval_35;
            if (fval_35 < g_hero_l08_speed_params[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l08_speed_params[0][1] * 0.020000001f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l08_speed_params[1][1] * 0.020000001f;
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
            ClipHeroVelocityAgainstWall_pal(1);
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
                m = ((s32 *)g_impact_l08_moby_list)[k];
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
    case 0x63:
        FastVecSub((s32)((TI128*)vec_0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)vec_0), (s32)(g_hero_state + 0x160)) < 0.0f) {
            vec_clear_128((s32)(g_hero_state + 0x160));
        }
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.0108f);
        ClipHeroVelocityAgainstWall_pal(0);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0x18A0)) - 0x1790, 0.010000001f);
            hero_cancel_velocity_into_wall_pal();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.0216f);
        break;
    case 0x3C:
    case 0x64:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    case 0x65:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((f32) ((Hero *)g_hero_state)->i[0x18C0/4] * 0.5f) < (((Hero *)g_hero_state)->f[0x334/4] - ((Hero *)g_hero_state)->f[0x88/4])) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.0050000004f;
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.020000001f;
        }
        break;
    case 0x78:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.020000001f;
        break;
    case 0x60:
    case 0x61:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (ival_7 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (ival_8 != M2C_FIELD(ref_21, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
