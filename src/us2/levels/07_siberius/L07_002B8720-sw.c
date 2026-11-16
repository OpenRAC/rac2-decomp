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
extern f32 g_hero_l07_speed_thresholds[][4] MACRO_ADDR;
extern s32 g_hero_l07_lock_flag MACRO_ADDR;
extern u8 g_hero_state_bytes[];
extern s32 g_beam_uv_offsets MACRO_ADDR;
extern s32 g_level_unused_word_a MACRO_ADDR;
extern s32 g_level_unused_word_b MACRO_ADDR;
extern s32 g_level_unused_word_c MACRO_ADDR;
extern u8 g_hero_l07_state_block[];
extern u8 g_hero_state_block_b[];
extern u8 g_hero_l07_view_height[];
extern u8 g_hit_object_list[];
extern u8 g_hero_l07_tuning_params[];
extern u8 g_level_unused_bytes_a[];
extern u8 g_level_unused_bytes_b[];
extern Rec2C g_hero_state_info_table[];
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
extern void func_002A0F48(s32);
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
extern void UpdateHeroVelocityForStateWithYawSpring(void);
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
extern s32 g_hero_sound_flag;
extern char g_impact_effect_data[] MACRO_ADDR;
extern void moby_raise_state_to_eight();
extern void moby_raise_state_to_eight_copy();

/* Runs the hero's behaviour every frame for the current state, such as walking, jumping, swimming or falling (USA v2.00). */
void hero_l07_update_state_machine_us2(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 vec_00[4] __attribute__((aligned(16)));
    f32 vec_10[4] __attribute__((aligned(16)));
    f32 vec_20[4] __attribute__((aligned(16)));
    f32 vec_30[4] __attribute__((aligned(16)));
    f32 vec_40[4] __attribute__((aligned(16)));
    f32 vec_50[4] __attribute__((aligned(16)));
    f32 vec_60[8] __attribute__((aligned(16)));
    f32 mat_70[16] __attribute__((aligned(16)));
    f32 vec_c0[4] __attribute__((aligned(16)));
    f32 vec_d0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* ptr_1;
    void* ptr_2;
    f32 float_1;
    void* ptr_3;
    s32 int_1;
    void* ptr_4;
    s32 int_2;
    s32 int_3;
    void* ptr_5;
    s32 int_4;
    void* ptr_6;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 float_2;
    f32 float_3;
    f32 float_4;
    f32 float_5;
    f32 float_6;
    f32 float_7;
    f32 float_8;
    s32 int_5;
    f32 float_9;
    s32 int_6;
    f32 float_10;
    f32 float_11;
    f32 float_12;
    s32 int_7;
    s32 int_8;
    s32 int_9;
    f32 float_13;
    f32 float_14;
    f32 float_15;
    f32 float_16;
    f32 float_17;
    f32 float_18;
    f32 float_19;
    f32 float_20;
    f32 float_21;
    f32 float_22;
    f32 float_23;
    f32 float_24;
    f32 float_25;
    f32 float_26;
    f32 float_27;
    f32 float_28;
    f32 float_29;
    f32 float_30;
    f32 float_31;
    f32 float_32;
    f32 float_33;
    f32 float_34;
    f32 float_35;
    f32 float_36;
    f32 float_37;
    f32 float_38;
    f32 float_39;
    f32 float_40;
    f32 float_41;
    f32 float_42;
    f32 float_43;
    f32 float_44;
    f32 float_45;
    f32 float_46;
    f32 float_47;
    f32 float_48;
    f32 float_49;
    f32 float_50;
    f32 float_51;
    f32 float_52;
    f32 float_53;
    f32 float_54;
    f32 float_55;
    f32 float_56;
    f32 float_57;
    f32 float_58;
    f32 float_59;
    f32 float_60;
    f32 float_61;
    f32 float_62;
    f32 float_63;
    f32 float_64;
    f32 float_65;
    f32 float_66;
    f32 float_67;
    f32 float_68;
    f32 float_69;
    f32 float_70;
    f32 float_71;
    f32 float_72;
    f32 float_73;
    f32 float_74;
    f32 float_75;
    f32 float_76;
    f32 float_77;
    f32 float_78;
    f32 float_79;
    f32 float_80;
    f32 float_81;
    f32 float_82;
    f32 float_83;
    f32 float_84;
    f32 float_85;
    f32 float_86;
    f32 float_87;
    f32 float_88;
    f32 float_89;
    f32 float_90;
    f32 float_91;
    f32 float_92;
    f32 float_93;
    f32 float_94;
    f32 float_95;
    f32 float_96;
    f32 float_97;
    f32 float_98;
    f32 float_99;
    f32 float_100;
    f32 float_101;
    f32 float_102;
    f32 float_103;
    f32 float_104;
    f32 float_105;
    f32 float_106;
    f32 float_107;
    f32 float_108;
    f32 float_109;
    f32 float_110;
    f32 float_111;
    f32 float_112;
    f32 float_113;
    f32 float_114;
    f32 float_115;
    f32 float_116;
    f32 float_117;
    f32 float_118;
    f32 float_119;
    f32 float_120;
    f32 float_121;
    f32 float_122;
    f32 float_123;
    f32 float_124;
    f32 float_125;
    f32 float_126;
    f32 float_127;
    f32 float_128;
    f32 float_129;
    f32 float_130;
    f32 float_131;
    f32 float_132;
    f32 float_133;
    f32 float_134;
    f32 float_135;
    f32 float_136;
    f32 float_137;
    f32 float_138;
    f32 float_139;
    f32 float_140;
    f32 float_141;
    f32 float_142;
    f32 float_143;
    f32 float_144;
    f32 float_145;
    f32 float_146;
    f32 float_147;
    f32 float_148;
    f32 float_149;
    f32 float_150;
    f32 float_151;
    f32 float_152;
    f32 float_153;
    f32 float_154;
    f32 float_155;
    f32 float_156;
    f32 float_157;
    f32 float_158;
    f32 float_159;
    f32 float_160;
    f32 float_161;
    f32 float_162;
    f32 float_163;
    f32 float_164;
    f32 float_165;
    f32 float_166;
    f32 float_167;
    f32 float_168;
    f32 float_169;
    s16 short_1;
    s32 int_10;
    s16 short_2;
    s32 int_11;
    s32 int_12;
    s32 int_13;
    s32 int_14;
    s32 int_15;
    s32 int_16;
    s32 int_17;
    s32 int_18;
    s32 int_19;
    s32 int_20;
    s32 int_21;
    s32 int_22;
    s32 int_23;
    s32 int_24;
    s32 int_25;
    s32 int_26;
    s32 int_27;
    s32 int_28;
    s32 int_29;
    s32 int_30;
    s32 int_31;
    s32 int_32;
    s32 int_33;
    s32 int_34;
    s32 int_35;
    s32 int_36;
    s32 int_37;
    s32 int_38;
    s32 int_39;
    s32 int_40;
    s32 int_41;
    s32 int_42;
    s32 int_43;
    s32 int_44;
    s32 int_45;
    s32 int_46;
    s32 int_47;
    s32 int_48;
    s32 int_49;
    s32 int_50;
    s32 int_51;
    s32 int_52;
    s32 int_53;
    s32 int_54;
    s32 int_55;
    s32 int_56;
    s32 int_57;
    s32 int_58;
    s32 int_59;
    s32 int_60;
    s32 int_61;
    s32 int_62;
    s32 int_63;
    s32 int_64;
    s32 int_65;
    s32 int_66;
    s32 int_67;
    s32 int_68;
    s32 int_69;
    s32 int_70;
    s32 int_71;
    s32 int_72;
    s32 int_73;
    s32 int_74;
    s32 int_75;
    s32 int_76;
    s32 int_77;
    s32 int_78;
    s32 int_79;
    s32 int_80;
    s32 int_81;
    s32 int_82;
    s32 int_83;
    s32* ptr_7;
    s32* ptr_8;
    u16 short_3;
    u16 short_4;
    u16 short_5;
    u32 int_84;
    u32 int_85;
    u32 int_86;
    u32 int_87;
    u32 int_88;
    u32 int_89;
    u32 int_90;
    u32 int_91;
    u32 int_92;
    u32 int_93;
    u32 int_94;
    u32 int_95;
    u8 byte_1;
    u8 byte_2;
    u8 byte_3;
    u8 byte_4;
    void* ptr_9;
    void* ptr_10;
    void* ptr_11;
    void* ptr_12;
    void* ptr_13;
    void* ptr_14;
    void* ptr_15;
    void* ptr_16;
    void* ptr_17;
    void* ptr_18;
    void* ptr_19;
    void* ptr_20;
    void* ptr_21;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* ptr_22;
    void* ptr_23;
    void* ptr_24;
    void* ptr_25;
    void* ptr_26;
    void* ptr_27;
    void* ptr_28;
    void* ptr_29;
    void* ptr_30;
    void* ptr_31;
    void* ptr_32;
    void* ptr_33;
    void* ptr_34;
    void* ptr_35;
    void* ptr_36;
    void* ptr_37;
    void* ptr_38;
    void* ptr_39;
    void* ptr_40;
    void* ptr_41;
    void* ptr_42;
    void* ptr_43;
    void* ptr_44;
    void* ptr_45;
    void* ptr_46;
    void* ptr_47;
    void* ptr_48;
    void* ptr_49;
    void* ptr_50;
    void* ptr_51;
    void* ptr_52;
    void* ptr_53;
    void* ptr_54;
    void* ptr_55;
    void* ptr_56;
    void* ptr_57;
    void* ptr_58;
    void* ptr_59;
    void* ptr_60;
    void* ptr_61;

    int_7 = ((Hero *)g_hero_state)->i[0x2298/4];
    ptr_21 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    int_8 = (s32) M2C_FIELD(ptr_21, u8* , 0x43);
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
        int_85 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_85 == 1) || (int_85 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vec_00) = 0;
                vec_00[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vec_00), (s32)&g_hero_state_block_b[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state_block_b)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (byte_2 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (byte_2 == 0xE)) || (byte_2 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    int_14 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    int_14 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != int_14) {
                        set_hero_animation(int_14, 0, 5.0f);
                    }
                    float_13 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = float_13;
                    if (float_13 < 0.55f) {
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
            int_94 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (int_94 == 3) {
                float_116 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (float_116 > 1.0f) {
                    float_116 = 1.0f;
                }
                ptr_16 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                float_142 = float_116 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = float_142;
                if (M2C_FIELD(ptr_16, u8* , 0x42) == M2C_FIELD(ptr_16, u8* , 0x43)) {
                    float_137 = ((Hero *)g_hero_state)->f[0x174/4] / float_142;
                    if ((float_137 > 5.0f) && ((f32) M2C_FIELD(ptr_16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, float_137, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (int_94 == 4) {
                float_142 = 0.0075000003f;
            } else {
                float_142 = 0.004916667f;
            }
            hero_approach_speed(0.0f, float_142);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(float_142);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                int_60 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(int_60, int_60 + 0x30, 0.0061111115f);
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
    case 0x7C:                                      /* switch 1 */
        hero7C = (void*)g_hero_state;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            int_31 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = int_31;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)int_31 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)int_31 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(int_31, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            int_51 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(int_51, u16* , 0x34) = (u16) (M2C_FIELD(int_51, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        int_53 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(int_53, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(int_53, u8* , 0x23) = 0x80U;
        }
        int_15 = ((Hero *)hero7C)->i[0x7A4/4];
        ptr_18 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)int_15 + 0x10, (u8 *)ptr_18 + 0x10);
        qcopy((u8 *)int_15 + 0xF0, (u8 *)ptr_18 + 0xF0);
        func_002A0F48(int_15);
        }
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.92f);
        hero_update_height_offset();
        break;
    case 0x85:                                      /* switch 1 */
        ptr_19 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)ptr_19 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)ptr_19 + 0xF0);
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
            ptr_50 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr_50, u8* , 0x60) & 2) && (M2C_FIELD(ptr_50, u8* , 0x42) == 0x36)) {
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
        ptr_61 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (ptr_61 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr_61, f32* , 0x10) - M2C_FIELD(ptr_21, f32* , 0x10), M2C_FIELD(ptr_61, f32* , 0x14) - M2C_FIELD(ptr_21, f32* , 0x14));
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
        ptr_1 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (ptr_1 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr_1, f32* , 0x10) - M2C_FIELD(ptr_21, f32* , 0x10), M2C_FIELD(ptr_1, f32* , 0x14) - M2C_FIELD(ptr_21, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vec_00, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        float_37 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_00));
        ((Hero *)g_hero_state)->f[0xAB0/4] = float_37;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 60.0f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (float_37 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        int_41 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (int_41 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.45000002f, 0.022222223f);
            ptr_46 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            float_147 = mat_fast_helper_a(M2C_FIELD(ptr_46, f32* , 0x10) - M2C_FIELD(ptr_21, f32* , 0x10), M2C_FIELD(ptr_46, f32* , 0x14) - M2C_FIELD(ptr_21, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], float_147) > 1.5707964f) {
                    float_147 = FastAddRotations(float_147, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = float_147;
            hero_steer_heading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (int_41 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((math_solve_quadratic((s32) &float_4, (s32) &float_5, -0.0058333334f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (float_4 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = float_4;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 20.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn24 = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_00)), vec_00[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn24, 0.10762865f);
        }
        vec_20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        float_38 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        vec_20[2] = 0;
        vec_20[1] = float_38;
        FastVecAdd((s32) ((TI128*)vec_20), (s32) ((TI128*)vec_20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)vec_10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vec_20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vec_10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        float_39 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (float_39 < 30.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((30.0f - float_39) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.004166667f);
        qcopy(vec_00, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)vec_00));
        FastVecAdd((s32) ((TI128*)vec_10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_10), (s32)((TI128*)vec_00));
        vec_scale_to_length((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vec_20), (s32)((TI128*)vec_00), (s32) ((TI128*)vec_30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(ptr_21, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        ptr_51 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        float_92 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (ptr_51 != 0) {
            ptr_47 = M2C_FIELD(ptr_51, void** , 0x68);
            if ((ptr_47 != 0) && (M2C_FIELD(ptr_47, s32* , 0x34) != 0)) {
                float_148 = M2C_FIELD(ptr_51, f32* , 0xF8);
                if (FastDiffRots(float_148, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    float_148 = FastAddRotations(float_148, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), float_148, (s32) (((void*)g_hero_state) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)vec_00), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), 1.0f);
        if (vec_00[2] < 0.23f) {
            vec_00[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)vec_20));
        vec_20[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vec_40), (s32) ((TI128*)vec_20));
        matrix_from_basis_rows((s32) ((TI128*)mat_70), (s32) ((TI128*)vec_40));
        transform_vector((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), (s32) ((TI128*)mat_70));
        vec_10[0] = -mat_fast_helper_a(square_root((vec_00[0] * vec_00[0]) + (vec_00[2] * vec_00[2])), vec_00[1]);
        float_40 = mat_fast_helper_a(vec_00[2], vec_00[0]);
        vec_10[1] = float_40;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), float_40, (s32) (((void*)g_hero_state) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), vec_10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        int_72 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((int_72 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x29) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                float_149 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0035f;
                if (float_149 > 0.083333336f) {
                    float_149 = 0.083333336f;
                }
                vec_30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * float_149;
                float_41 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * float_149;
                ptr_9 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vec_30[2]) = 0;
                vec_30[1] = float_41;
                FastVecAdd((s32) ptr_9, (s32) ptr_9, (s32) ((TI128*)vec_30));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                ptr_38 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) ptr_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    ptr_30 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) ptr_30, (s32) (((void*)g_hero_state) + 0x110), 0.011111111f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) ptr_30) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vec_30), (s32) ptr_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) ptr_30, (s32) ptr_30, 0.015833333f);
                    }
                }
                float_79 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vec_30), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vec_30), (s32) ((TI128*)vec_30), float_79);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_30));
            }
        }
        ptr_48 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (ptr_48 != 0) {
            ptr_22 = M2C_FIELD(ptr_48, void** , 0x68);
            ptr_31 = ((void*)g_hero_state) + 0xF0;
            if (ptr_22 != 0) {
                float_42 = FastVecLength((s32) ptr_31);
                float_43 = M2C_FIELD(ptr_22, f32* , 0xC);
                float_6 = float_42;
                if (float_43 < float_42) {
                    ApproachValue((s32) &float_6, float_43, 0.004166667f);
                    vec_scale_to_length((s32) ptr_31, (s32) ptr_31, float_6);
                }
            }
        }
        float_14 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        ptr_44 = ((void*)g_hero_state) + 0x80;
        ptr_43 = ((void*)g_hero_state) + 0xF0;
        vec_d0[0] = math_fast_sin_or_cos_a(float_14) * 0.15f;
        float_15 = math_fast_sin_or_cos_b(float_14) * 0.15f;
        (*(s32*)&vec_d0[2]) = 0;
        vec_d0[1] = float_15;
        FastVecAdd((s32) &vec_d0[0], (s32) &vec_d0[0], (s32) ptr_44);
        FastVecAdd((s32) ((TI128*)vec_30), (s32) &vec_d0[0], (s32) ptr_43);
        FastVecSub((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vec_30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vec_c0));
        FastVecSub((s32) ptr_43, (s32) ((TI128*)vec_30), (s32) &vec_d0[0]);
        float_80 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        float_81 = ((Hero *)g_hero_state)->f[0xAE4/4] - float_80;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vec_c0))) {
            vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), float_81);
            FastVecAdd((s32) ptr_44, (s32) ptr_44, (s32) ((TI128*)vec_c0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (int_72 != 0)) {
            min2B = 0.23333335f;
            float_16 = vec_length_xy((s32) ptr_43);
            float_7 = float_16;
            if (float_16 < min2B) {
                math_spring_float_to_goal((s32) &float_7, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                vec_30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                float_17 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vec_30[2] = 0.0f;
                vec_30[1] = float_17 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) ptr_43, (s32) ptr_43, (s32) ((TI128*)vec_30));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((float_92 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            float_82 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            short_2 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (short_2 != 0) {
                int_75 = short_2 == 1;
            } else {
                (*(TI128*)vec_30) = ((Hero *)g_hero_state)->q[0x110/16];
                int_75 = hero_get_speed_along_forward((s32) ((TI128*)vec_30)) > 0.0f;
            }
            if (int_75 != 0) {
                if (M2C_FIELD(ptr_21, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    ptr_49 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(ptr_49, u8* , 0x42) == M2C_FIELD(ptr_49, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, float_82, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(ptr_21, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                ptr_45 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(ptr_45, u8* , 0x42) == M2C_FIELD(ptr_45, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, float_82, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_state_info_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        int_70 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            int_70 = 1;
        }
        int_20 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (int_20 != 0) {
            FastVecSub((s32)((TI128*)vec_00), int_20 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            float_18 = cam_get_view_space_vector_length((s32)((TI128*)vec_00));
            if (((float_18 > 2.0f) && (float_18 < 5.0f)) || (int_70 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
            }
            hero_approach_speed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length((s32) ((TI128*)vec_10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_10));
        } else {
            if ((int_70 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
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
        float_63 = ((Hero *)g_hero_state)->f[0x31C/4];
        float_155 = 0.12833333f;
        if (float_63 > 2.25f) {
            float_155 = 0.064166665f;
        } else if (float_63 > 1.8f) {
            float_155 = 0.08983333f;
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
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (g_hero_override_flag != 0) {
                ((Hero *)g_hero_l07_state_block)->f[0x180/4] = 0.1f;
                ((Hero *)g_hero_l07_state_block)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)g_hero_l07_state_block)->i[0x16C/4] = 0;
            }
        }
        int_42 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xE;
        if (int_42 < 9) {
            ptr_23 = ((void*)g_hero_state) + 0xF0;
            float_8 = cam_get_view_space_height((s32) ptr_23);
            ApproachValue((s32) &float_8, float_155, 0.041666668f);
            cam_set_view_space_height((s32) ptr_23, (s32) ptr_23, float_8);
        } else if (int_42 > lim3) {
            ptr_32 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_32, (s32) ptr_32, 0.036111113f);
            if (cam_get_view_space_height((s32) ptr_32) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            float_150 = -0.6166667f;
            if (g_hero_l07_lock_flag != 0) {
                float_150 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) ptr_32) < float_150) {
                cam_set_view_space_height((s32) ptr_32, (s32) ptr_32, float_150);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_state_info_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        int_63 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (int_63 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                int_71 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    ptr_24 = ((void*)g_hero_state) + 0xBC0;
                    float_151 = hero_get_direction_angle_delta((s32) ptr_24, 0);
                    float_109 = hero_get_direction_angle_delta((s32) ptr_24, 1);
                } else {
                    float_151 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    float_109 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (float_109 < 4.3633237f) {
                    int_71 = 1;
                }
                if (float_151 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (float_109 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (int_71 != 0) {
                    hero_steer_heading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    hero_steer_heading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    int_64 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xC)) {
                        int_64 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        int_64 = 0;
                    }
                    if (int_64 != 0) {
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
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_state_info_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        int_21 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ptr_39 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_state_info_table;
        if ((int_21 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            ptr_33 = ((void*)g_hero_state) + 0x80;
            float_119 = vec_distance_xy(int_21 + 0x10, (s32) ptr_33);
            if ((*(s32*)&g_hero_l07_lock_flag) != 0) {
                float_119 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) ptr_33);
            }
            float_119 = float_119 - 0.5f;
            if (float_119 < 0.0f) {
                float_119 = 0.0f;
            }
            int_43 = M2C_FIELD(ptr_39, s32* , 4);
            if (int_43 == 0) {
                float_110 = 0.75f;
                float_157 = 0.8f;
                float_162 = 4.0f;
            } else if (int_43 == 1) {
                float_110 = 0.6f;
                float_157 = 1.7f;
                float_162 = 4.0f;
            } else {
                float_110 = 1.3f;
                float_157 = 1.7f;
                float_162 = 1.9f;
            }
            float_84 = float_119 - float_110;
            if (math_fabs(float_84) < (float_157 + 3.0f)) {
                float_121 = float_84 * 1.1111112f;
                if (float_162 < float_121) {
                    float_121 = float_162;
                }
                if (float_121 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = float_121;
                }
            }
        }
        int_44 = M2C_FIELD(ptr_39, s32* , 4);
        switch (int_44) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            float_64 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (float_64 < 9.0f)) {
                if (float_64 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (float_64 > 7.0f) {
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
            float_111 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            float_111 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        float_65 = math_fabs(float_111);
        if ((M2C_FIELD(ptr_39, s32* , 4) == 1) && (float_111 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (float_65 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        int_82 = 1;
        if ((M2C_FIELD(ptr_39, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            int_82 = 0;
        }
        if (int_82 != 0) {
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
            ptr_11 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_11, (s32) ptr_11, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&g_hero_l07_lock_flag) != 0) {
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
        int_45 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (int_45 > lim) {
            if (int_45 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            ptr_25 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ptr_25);
            level_append_record_to_table((s32) ptr_25, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) ptr_25, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) ptr_25, 0xC, 6, 0.0f);
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
            int_47 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((int_47 > lim) && (int_47 < 0x16)) {
                ptr_40 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (ptr_40 != 0) {
                    ptr_34 = ((void*)g_hero_state) + 0x80;
                    vec_30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec_00), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vec_30));
                    (*(u8*)((u8*)vec_10+9)) = 3;
                    vec_00[3] = 5627.925f;
                    (*(u8*)((u8*)vec_10+8)) = 0;
                    float_90 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vec_10+10)) = M2C_FIELD(ptr_40, u16* , 0xAA);
                    vec_40[0] = math_fast_sin_or_cos_a(float_90) * 0.8f;
                    float_19 = math_fast_sin_or_cos_b(float_90) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = float_19;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ptr_34);
                    part_emit_effects_at_nearby_mobys((s32) ptr_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ptr_40, (s32)((TI128*)vec_00)));
                    float_90 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(float_90) * 0.8f;
                    float_21 = math_fast_sin_or_cos_b(float_90) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = float_21;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ptr_34);
                    part_emit_effects_at_nearby_mobys((s32) ptr_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec_00)));
                    float_90 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vec_40[0] = math_fast_sin_or_cos_a(float_90) * 0.8f;
                    float_23 = math_fast_sin_or_cos_b(float_90) * 0.8f;
                    vec_40[2] = 0.55f;
                    vec_40[1] = float_23;
                    FastVecAdd((s32) &vec_40[0], (s32) &vec_40[0], (s32) ptr_34);
                    part_emit_effects_at_nearby_mobys((s32) ptr_40, coll_process_hit(0.8f, (s32) &vec_40[0], 0, (s32) ptr_40, (s32)((TI128*)vec_00)));
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
            float_85 = ReadPadFloatHistory(1);
            if ((FastDiffRots(float_85, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            (*(TI128*)vec_00) = ((Hero *)g_hero_state)->q[0xA60/16];
            float_66 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vec_00));
            ((Hero *)g_hero_state)->f[0x1B0/4] = float_66;
            if (float_66 < 0.011666667f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.011666667f;
            }
            vec_clear_128((s32) pA60);
        }
        float_152 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                float_94 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (float_94 > 0.78539824f)) {
                    float_152 = 0.0f;
                }
                hero_set_turn_rates();
            }
        }
        hero_apply_mode_pose_offsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            float_166 = 0.09916667f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.029178405f);
            if (float_166 < 0.0f) {
                float_166 = 0.0f;
            }
            if (float_166 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = float_166;
            }
        }
        k005 = float_152 * 0.005f;
        float_153 = 0.0055555557f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            float_138 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (float_138 > 1.0f) {
                float_138 = 1.0f;
            }
            if (float_138 < 0.2f) {
                float_138 = 0.2f;
            }
            float_153 = 0.004722222f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_138);
        }
        float_95 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (float_95 > 0.6108653f)) {
            float_139 = 1.0f - (float_95 * 0.4f);
            if (float_139 < 0.0f) {
                float_139 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_139);
        }
        hero_approach_speed(k005, float_153);
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
        pad_clamp_stick_to_unit_range((s32)((TI128*)vec_00), (s32) (((void*)g_hero_state) + 0x9F0), 0.17f);
        float_158 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * vec_00[0];
        if ((*(s32*)&g_hero_l07_lock_flag) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3C) {
                float_158 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, float_158);
        }
        hero_approach_speed(0.027777778f, 0.004166667f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&g_hero_l07_lock_flag) != 0) {
            qcopy(vec_10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vec_10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec_10), (s32) ((TI128*)vec_10), (s32)(g_hero_state + 0xE0));
        int_32 = coll_process_hit(0.57f, (s32) ((TI128*)vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (int_32 != 0) {
            FastVecScale((s32) ((TI128*)vec_20), (s32)(g_hero_state + 0x110), 7.0f);
            for (int_67 = 0; int_67 < int_32; int_67++) {
                if (moby_is_in_special_class_range(((s32 *)g_hit_object_list)[int_67]) != 0) {
                    part_queue_impact_effect(((s32 *)g_hit_object_list)[int_67], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.017f, 0.3f);
        cam_set_limits_third(0.025f, 0.3f);
        cam_set_limits_fourth(0.03f, 0.27f);
        float_167 = float_158 * 27.0f;
        if (float_167 > 1.7f) {
            float_167 = 1.7f;
        } else if (float_167 < -1.7f) {
            float_167 = -1.7f;
        }
        float_24 = float_167 * 0.5f;
        ((Hero *)g_hero_l07_tuning_params)->f[0x60/4] = (f32) -float_167;
        ((Hero *)g_hero_l07_tuning_params)->f[0x278/4] = float_24;
        ((Hero *)g_hero_l07_tuning_params)->f[0x1C8/4] = float_24;
        break;
    case 0x30:                                      /* switch 1 */
        int_48 = (*(s32*)&g_current_map_index);
        if (int_48 == 0 || (int_48 == 1 && g_hero_sound_flag == 0)) {
            snd_update_slot_object(2, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x13);
        }
        int_77 = g_current_map_index;
        if ((u32) int_77 < 2U) {
            EmitHeroRandomizedMotionEffects(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects(4, 2, 0);
            vec_00[0] = ((Hero *)g_hero_state)->f[0x80/4] + math_random_float_range(-0.25f, 0.25f);
            vec_00[1] = ((Hero *)g_hero_state)->f[0x84/4] + math_random_float_range(-0.25f, 0.25f);
            vec_00[2] = ((Hero *)g_hero_state)->f[0x88/4] + math_random_float_range(-0.1f, 0.4f);
            FastVecScale((s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x110), 0.9f);
            vec_10[0] += math_random_float_range(-0.011666667f, 0.011666667f);
            vec_10[1] += math_random_float_range(-0.011666667f, 0.011666667f);
            vec_10[2] = M2C_BITWISE(f32, vec_10[2]) + math_random_float_range(0.016666668f, 0.033333335f);
            part_spawn_two_point_effect((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), math_random_float_range(37800.0f, 75600.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xB40/4];
        float_69 = ((Hero *)g_hero_state)->f[0x98/4];
        hero_steer_heading(0, 0.033f, 0.3f, 0.069813184f);
        float_160 = FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], float_69);
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        hero_shrink_vector_by_amount(0.0019444445f);
        float_26 = ((Hero *)g_hero_state)->f[0x118/4] - 0.013888889f;
        ((Hero *)g_hero_state)->f[0xF8/4] = float_26;
        if (float_26 > -0.011111111f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.011111111f;
        }
        if (float_160 > 0.023271061f) {
            float_160 = 0.023271061f;
        }
        float_70 = float_160 * 9.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), float_70 * 0.5f, (s32) (((void*)g_hero_state) + 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), -((Hero *)g_hero_state)->f[0xB44/4], (s32) (((void*)g_hero_state) + 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        ((Hero *)g_hero_l07_tuning_params)->f[0x118/4] = (f32) (float_70 * 2.1f);
        ((Hero *)g_hero_l07_tuning_params)->f[0x110/4] = (f32) (float_70 * 3.5f);
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
        if ((ProbeLedgeGrab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (ProbeLedgeGrab((s32) &vec_50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec_00)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec_00), (s32)(g_hero_state + 0x80));
            int_79 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            int_83 = (s32)g_hero_state_bytes;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(int_79 + int_83) * 0.5f);
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
            float_124 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                float_124 = 0.43633235f;
            }
            qcopy(vec_00, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &vec_00[1], float_124, (s32) (((void*)g_hero_state) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            math_approach_with_velocity((s32)((TI128*)vec_00), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_refresh_speed_from_timer();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            UpdateHeroVelocityForStateWithYawSpring();
        }
        ptr_60 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) ptr_60, (s32) ptr_60, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_60) < -0.8333334f) {
            cam_set_view_space_height((s32) ptr_60, (s32) ptr_60, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        ptr_2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ptr_2, (s32) ptr_2, vec_length_xy((s32) ptr_2) * 0.9f);
        hero_apply_mode_transform((s32) ptr_2, (s32) ptr_2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_2) < -0.8333334f) {
            cam_set_view_space_height((s32) ptr_2, (s32) ptr_2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        int_59 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            int_59 = 0;
        }
        if (int_59 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            ptr_13 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) ptr_13, (s32) ptr_13, 0.025f);
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
        float_46 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (float_46 < 0.0f) && (float_98 = ((Hero *)g_hero_state)->f[0x31C/4], (float_98 < 1.2f))) {
            float_102 = (float_98 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (float_102 < 0.0f) {
                float_102 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), float_46 * float_102);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (float_46 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&g_hero_l07_view_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.027f, 0.3f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.087266475f);
        float_125 = 0.0013888889f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            float_125 = 0.00055555557f;
        }
        hero_approach_velocity(float_125);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            int_26 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (int_26 != -1) {
                ptr_14 = (int_26 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_14, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_14, u8* , 0x74) != 0)) {
                    snd_stop_voice(int_26);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            int_27 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (int_27 != -1) {
                ptr_15 = (int_27 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_15, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_15, u8* , 0x74) != 0)) {
                    snd_stop_voice(int_27);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        float_163 = 0.050000004f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            float_163 = 0.083333336f;
        }
        float_164 = 0.72f;
        float_53 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            float_163 = 0.12833333f;
            float_164 = 0.98640007f;
        }
        if (float_53 != 0.0f) {
            float_164 = float_53;
        }
        ptr_27 = ((void*)g_hero_state) + 0xF0;
        float_12 = cam_get_view_space_height((s32) ptr_27);
        hero_resolve_stick_direction(float_163, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) ptr_27, (s32) ptr_27);
        math_spring_float_to_goal((s32) &float_12, (s32) (((void*)g_hero_state) + 0xA98), -float_163 * float_164, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) ptr_27, (s32) ptr_27, -float_12);
        float_47 = ((Hero *)g_hero_state)->f[0x88/4];
        if (float_47 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), float_47, 0.06666667f);
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
        short_1 = ((Hero *)g_hero_state)->h[0x4AC/2];
        int_23 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (int_23 == short_1) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((int_23 < short_1) && (int_92 = ((Hero *)g_hero_state)->u[0x2294/4], (int_92 != 0xB)) && (int_92 != 0x10) && (int_92 != 0xC) && (int_92 != 0x11) && (int_92 != 0x1B) && (int_92 != 0x89) && (int_92 != 0x48))) {
            hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
            float_74 = ((Hero *)g_hero_state)->f[0x1B4/4];
            if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (float_74 * 0.4f);
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
            ((Hero *)g_hero_state)->f[0x1B4/4] = float_74;
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
                int_49 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (int_49 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) int_49 * 0.0044444446f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                int_50 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (int_50 < 0x22) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) int_50 * 0.014722222f);
                }
            }
            if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                qcopy(vec_00, &((Hero *)g_hero_state)->q[0x80/16]);
                cam_offset_point_in_view_space((s32)((TI128*)vec_00), (s32)((TI128*)vec_00), 0.5f);
                cam_offset_point_by_side_direction((s32) ((TI128*)vec_10), (s32)((TI128*)vec_00), 0.95f);
                if (CollLine((s32)((TI128*)vec_00), (s32) ((TI128*)vec_10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                    ((Hero *)g_hero_state)->h[0x524/2] = 1;
                }
            }
        } else {
            UpdateHeroVelocityForStateWithYawSpring();
        }
        float_55 = ((Hero *)g_hero_state)->f[0x318/4];
        float_99 = ((Hero *)g_hero_state)->f[0x490/4];
        if (float_99 < float_55) {
            float_33 = float_99 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = float_33;
            if (float_55 < float_33) {
                ((Hero *)g_hero_state)->f[0x490/4] = float_55;
            }
        }
        float_56 = ((Hero *)g_hero_state)->f[0x88/4];
        if (float_56 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = float_56;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            float_57 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (float_57 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = float_57;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        int_93 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_93 == 0x10) || (int_93 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vec_00), 1, 0.8f, 0.0f, 0.3f);
                    int_37 = coll_process_hit(0.9f, (s32)((TI128*)vec_00), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (int_37 != 0) {
                        FastVecScale((s32) ((TI128*)vec_10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (int_68 = 0; int_68 < int_37; int_68++) {
                            if (moby_is_in_special_class_range(((s32 *)g_hit_object_list)[int_68]) != 0) {
                                part_queue_impact_effect(((s32 *)g_hit_object_list)[int_68], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_10), 1.0f);
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
        float_146 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        float_104 = 0.0011111111f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB)) {
            float_104 = 0.0027777778f;
        }
        float_146 = float_146 - float_104;
        if (float_146 < 0.0f) {
            float_146 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ptr_59 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) ptr_59, (s32) ptr_59, float_146);
        hero_apply_mode_transform((s32) ptr_59, (s32) ptr_59, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec_00), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_00[0], vec_00[1]);
        float_35 = vec_length_xy((s32)((TI128*)vec_00));
        if (float_35 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_00[0], vec_00[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = float_35;
            if (float_35 < g_hero_l07_speed_thresholds[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l07_speed_thresholds[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l07_speed_thresholds[1][1] * 0.016666668f;
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
                m = ((s32 *)g_hit_object_list)[k];
                if (m != 0) {
                    switch (*(s16 *)(m + 0xAA)) {
                    case 0xCB:
                        part_queue_impact_effect(m, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0xE0), (s32) g_impact_effect_data, 100.0f);
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
        FastVecSub((s32)((TI128*)vec_00), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)vec_00), (s32)(g_hero_state + 0x160)) < 0.0f) {
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
    case 0x37:                                      /* switch 1 */
        if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) == 0x44) {
            hero_steer_heading(0, 0.137f, 0.25f, 0.20362177f);
        } else {
            hero_steer_heading(0, 1.0f, 0.1f, 0.40724355f);
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (int_7 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (int_8 != M2C_FIELD(ptr_21, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
