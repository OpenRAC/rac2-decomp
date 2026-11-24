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
extern f32 g_hero_l03_speed_params[][4] MACRO_ADDR;
extern s32 g_hero_l03_block_flag MACRO_ADDR;
extern u8 g_hero_state_buffer[];
extern s32 g_bot_child_value MACRO_ADDR;
extern s32 g_level_flag_word_a MACRO_ADDR;
extern s32 g_level_flag_word_b MACRO_ADDR;
extern s32 g_level_flag_word_c MACRO_ADDR;
extern u8 g_hero_l03_state_alias[];
extern u8 g_hero_l03_aux_state[];
extern u8 g_hero_l03_view_space_height[];
extern u8 g_nearby_l03_moby_list[];
extern u8 g_hero_l03_motion_params[];
extern u8 g_hero_l03_speed_value[];
extern u8 g_hero_l03_signed_scalar[];
extern Rec2C g_hero_state_params[];
extern u8 g_level_data_buffer[];
extern u8 g_item_l03_record_table[];
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
extern void moby_transform_joint_to_world(s32, s32, s32);
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
extern void part_spawn_white_flash_pal(s32, s32, s32, f32);
extern void *part_spawn_bubble(s32, s32, f32, f32);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, s32);
extern void pad_clamp_stick_to_unit_range(s32, s32, f32);
extern float AdjustHeroAnimationSpeedForTargetFrame(f32, f32, f32, f32);
extern f32 math_blend_table_entries_by_clock(s32, s32);
extern void hero_start_pose_offset(f32, f32, f32);
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
extern void hero_refresh_speed_from_timer_pal(void);
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
extern void hero_update_hop_velocity_pal(void);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_apply_mode_pose_offsets_pal(void);
extern void UpdateHeroMotionResponseParameters_pal(void);
extern void UpdateHeroLeanAndSwayParameters(void);
extern void hero_shrink_vector_by_amount(f32);
extern f32 hero_get_direction_angle_delta(s32, s32);
extern s32 hero_play_sound(s32, s32);
extern void snd_update_slot_object(s32, s32, s32);
extern void hero_try_surface_push_response(f32, f32, f32);
extern void part_emit_effects_at_nearby_mobys_pal(s32, s32);
extern void part_emit_hero_radial_particles_pal(void);
extern void hero_setup_attached_object_transform_pal(void);
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
extern s32 math_update_angle_and_blend(s32, s32, s32, f32);
extern f32 ReadPadFloatHistory(s32);
extern void *part_spawn_two_point_effect(s32, s32, f32);
extern s32 path_advance_index(s32, s32, s32, s32);
extern s32 Spline_AdvanceByDistance(s32, s32, s32, s32, s32, f32);
extern s32 find_nearest_path_point(s32, s32, s32, s32, s32, s32, f32, f32, f32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern s32 shooter_update_ranged_attack(s32);
extern s32 hero_get_gadget_value(s32);
extern void DeflectHeroOffSteepSurface_pal(s32);
extern char g_impact_effect_data[] MACRO_ADDR;
extern void moby_l00_raise_state_to_8();
extern void moby_raise_state_to_eight_copy();

/* Runs the hero's current move state each frame: movement, aiming, camera limits and animation. (PAL: 50 Hz timings) */
void hero_l03_update_state_machine_pal(void) {
    f32 speed_scale;
    s32 frame_limit;
    s32 *counter_ptr;
    Hero *hero_view;
    f32 tmp_vec_00[4] __attribute__((aligned(16)));
    f32 tmp_vec_10[4] __attribute__((aligned(16)));
    f32 tmp_vec_20[4] __attribute__((aligned(16)));
    f32 tmp_vec_30[4] __attribute__((aligned(16)));
    f32 tmp_vec_40[4] __attribute__((aligned(16)));
    f32 tmp_vec_50[4] __attribute__((aligned(16)));
    f32 tmp_vec_60[8] __attribute__((aligned(16)));
    f32 tmp_matrix_70[16] __attribute__((aligned(16)));
    f32 tmp_vec_c0[4] __attribute__((aligned(16)));
    f32 tmp_vec_d0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 cam_limit;
    f32 ratio;
    s32 anim_id;
    s32 anim_blend;
    f32 approach_speed;
    void *vec_ptr;
    void* ptr_1;
    void* ptr_2;
    f32 fval_1;
    void* ptr_3;
    s32 val_1;
    void* ptr_4;
    s32 val_2;
    s32 val_3;
    void* ptr_5;
    s32 val_4;
    void* ptr_6;
    s32 limit_a;
    s32 limit_b;
    s32 limit_c;
    s32 follower_count;
    f32 ratio_b;
    s32 counter;

    f32 local_e0;
    f32 local_e4;
    f32 local_e8;
    f32 local_ec;
    f32 local_f0;
    f32 local_f4;
    f32 local_f8;
    s32 local_fc;
    f32 local_100;
    s32 local_104;
    f32 local_108;
    f32 local_10c;
    f32 local_110;
    s32 local_114;
    s32 local_118;
    s32 local_11c;
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
    s16 val_10;
    s32 val_11;
    s16 val_12;
    s32 val_13;
    s32 val_14;
    s32 val_15;
    s32 val_16;
    s32 val_17;
    s32 val_18;
    s32 val_19;
    s32 val_20;
    s32 val_21;
    s32 val_22;
    s32 val_23;
    s32 val_24;
    s32 val_25;
    s32 val_26;
    s32 val_27;
    s32 val_28;
    s32 val_29;
    s32 val_30;
    s32 val_31;
    s32 val_32;
    s32 val_33;
    s32 val_34;
    s32 val_35;
    s32 val_36;
    s32 val_37;
    s32 val_38;
    s32 val_39;
    s32 val_40;
    s32 val_41;
    s32 val_42;
    s32 val_43;
    s32 val_44;
    s32 val_45;
    s32 val_46;
    s32 val_47;
    s32 val_48;
    s32 val_49;
    s32 val_50;
    s32 val_51;
    s32 val_52;
    s32 val_53;
    s32 val_54;
    s32 val_55;
    s32 val_56;
    s32 val_57;
    s32 val_58;
    s32 val_59;
    s32 val_60;
    s32 val_61;
    s32 val_62;
    s32 val_63;
    s32 val_64;
    s32 val_65;
    s32 val_66;
    s32 val_67;
    s32 val_68;
    s32 val_69;
    s32 val_70;
    s32 val_71;
    s32 val_72;
    s32 val_73;
    s32 val_74;
    s32 val_75;
    s32 val_76;
    s32 val_77;
    s32 val_78;
    s32 val_79;
    s32 val_80;
    s32 val_81;
    s32 val_82;
    s32 val_83;
    s32 val_84;
    s32 val_85;
    s32* ptr_7;
    s32* ptr_8;
    u16 val_86;
    u16 val_87;
    u16 val_88;
    u32 val_89;
    u32 val_90;
    u32 val_91;
    u32 val_92;
    u32 val_93;
    u32 val_94;
    u32 val_95;
    u32 val_96;
    u32 val_97;
    u32 val_98;
    u32 val_99;
    u32 val_100;
    u8 val_101;
    u8 val_102;
    u8 val_103;
    u8 val_104;
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
    void* hero_moby;
    f32 turn_target;
    f32 lerp_angle;
    f32 min_value;
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

    local_114 = ((Hero *)g_hero_state)->i[0x2298/4];
    ptr_21 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    local_118 = (s32) M2C_FIELD(ptr_21, u8* , 0x43);
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
        hero_build_move_impulse(0.5f, 0.040000003f);
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        val_90 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((val_90 == 1) || (val_90 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)tmp_vec_00) = 0;
                tmp_vec_00[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)tmp_vec_00), (s32)&g_hero_l03_aux_state[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_l03_aux_state)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (val_102 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (val_102 == 0xE)) || (val_102 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.0028800003f, 0.10080001f, 0.13962635f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0069813184f) {
                    val_16 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    val_16 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != val_16) {
                        set_hero_animation_pal(val_16, 0, 4.0f);
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
            val_99 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (val_99 == 3) {
                fval_116 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (fval_116 > 1.0f) {
                    fval_116 = 1.0f;
                }
                ptr_16 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                fval_142 = fval_116 * 0.0108f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = fval_142;
                if (M2C_FIELD(ptr_16, u8* , 0x42) == M2C_FIELD(ptr_16, u8* , 0x43)) {
                    fval_137 = ((Hero *)g_hero_state)->f[0x174/4] / fval_142;
                    if ((fval_137 > 4.0f) && ((f32) M2C_FIELD(ptr_16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, fval_137, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (val_99 == 4) {
                fval_142 = 0.0108f;
            } else {
                fval_142 = 0.007080001f;
            }
            hero_approach_speed(0.0f, fval_142);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(fval_142);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                val_62 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(val_62, val_62 + 0x30, 0.0088f);
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
    case 0x85:                                      /* switch 1 */
        ptr_19 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)ptr_19 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)ptr_19 + 0xF0);
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
            ptr_50 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr_50, u8* , 0x60) & 2) && (M2C_FIELD(ptr_50, u8* , 0x42) == 0x36)) {
                set_hero_animation_pal(hero_get_gadget_value(0), 0, 4.0f);
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
        ptr_61 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (ptr_61 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr_61, f32* , 0x10) - M2C_FIELD(ptr_21, f32* , 0x10), M2C_FIELD(ptr_61, f32* , 0x14) - M2C_FIELD(ptr_21, f32* , 0x14));
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
        ptr_1 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (ptr_1 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr_1, f32* , 0x10) - M2C_FIELD(ptr_21, f32* , 0x10), M2C_FIELD(ptr_1, f32* , 0x14) - M2C_FIELD(ptr_21, f32* , 0x14));
            hero_steer_heading(0, 0.028800001f, 0.21600002f, 0.12566373f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(tmp_vec_00, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        fval_37 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)tmp_vec_00));
        ((Hero *)g_hero_state)->f[0xAB0/4] = fval_37;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 5e1f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (fval_37 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        val_43 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (val_43 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.54f, 0.032f);
            ptr_46 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            fval_147 = mat_fast_helper_a(M2C_FIELD(ptr_46, f32* , 0x10) - M2C_FIELD(ptr_21, f32* , 0x10), M2C_FIELD(ptr_46, f32* , 0x14) - M2C_FIELD(ptr_21, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], fval_147) > 1.5707964f) {
                    fval_147 = FastAddRotations(fval_147, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = fval_147;
            hero_steer_heading(0, 0.0432f, 0.21600002f, 0.14660768f);
        } else if (val_43 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.016800001f);
        }
        if ((math_solve_quadratic((s32) &local_e8, (s32) &local_ec, -0.008400001f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (local_e8 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = local_e8;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 17.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.0767945f);
        } else {
            turn_target = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)tmp_vec_00)), tmp_vec_00[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn_target, 0.12915438f);
        }
        tmp_vec_20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        fval_38 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        tmp_vec_20[2] = 0;
        tmp_vec_20[1] = fval_38;
        FastVecAdd((s32) ((TI128*)tmp_vec_20), (s32) ((TI128*)tmp_vec_20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)tmp_vec_10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)tmp_vec_20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)tmp_vec_10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        fval_39 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (fval_39 < 25.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((25.0f - fval_39) * 0.011600001f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.20000002f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.006f);
        qcopy(tmp_vec_00, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)tmp_vec_00));
        FastVecAdd((s32) ((TI128*)tmp_vec_10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)tmp_vec_30), (s32) ((TI128*)tmp_vec_10), (s32)((TI128*)tmp_vec_00));
        vec_scale_to_length((s32) ((TI128*)tmp_vec_30), (s32) ((TI128*)tmp_vec_30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)tmp_vec_20), (s32)((TI128*)tmp_vec_00), (s32) ((TI128*)tmp_vec_30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)tmp_vec_20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(ptr_21, u8* , 0x43) == 0x34)) {
            set_hero_animation_pal(0x35, 0xA, 1e1f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        ptr_51 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        fval_92 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (ptr_51 != 0) {
            ptr_47 = M2C_FIELD(ptr_51, void** , 0x68);
            if ((ptr_47 != 0) && (M2C_FIELD(ptr_47, s32* , 0x34) != 0)) {
                fval_148 = M2C_FIELD(ptr_51, f32* , 0xF8);
                if (FastDiffRots(fval_148, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    fval_148 = FastAddRotations(fval_148, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), fval_148, (s32) (((void*)g_hero_state) + 0xAF8), 0.028800001f, 0.43200004f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.028800001f, 0.43200004f, 0.094247796f);
        FastVecSub((s32)((TI128*)tmp_vec_00), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)tmp_vec_00), (s32)((TI128*)tmp_vec_00), 1.0f);
        if (tmp_vec_00[2] < 0.23f) {
            tmp_vec_00[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)tmp_vec_20));
        tmp_vec_20[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)tmp_vec_40), (s32) ((TI128*)tmp_vec_20));
        matrix_from_basis_rows((s32) ((TI128*)tmp_matrix_70), (s32) ((TI128*)tmp_vec_40));
        transform_vector((s32)((TI128*)tmp_vec_00), (s32)((TI128*)tmp_vec_00), (s32) ((TI128*)tmp_matrix_70));
        tmp_vec_10[0] = -mat_fast_helper_a(square_root((tmp_vec_00[0] * tmp_vec_00[0]) + (tmp_vec_00[2] * tmp_vec_00[2])), tmp_vec_00[1]);
        fval_40 = mat_fast_helper_a(tmp_vec_00[2], tmp_vec_00[0]);
        tmp_vec_10[1] = fval_40;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), fval_40, (s32) (((void*)g_hero_state) + 0xA4), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), tmp_vec_10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.057600003f, 0.28800002f, 0.19198625f, 0);
        val_74 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((val_74 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x22) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                fval_149 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0042000003f;
                if (fval_149 > 0.10000001f) {
                    fval_149 = 0.10000001f;
                }
                tmp_vec_30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * fval_149;
                fval_41 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * fval_149;
                ptr_9 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&tmp_vec_30[2]) = 0;
                tmp_vec_30[1] = fval_41;
                FastVecAdd((s32) ptr_9, (s32) ptr_9, (s32) ((TI128*)tmp_vec_30));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                ptr_38 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) ptr_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    ptr_30 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) ptr_30, (s32) (((void*)g_hero_state) + 0x110), 0.016f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) ptr_30) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)tmp_vec_30), (s32) ptr_38, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) ptr_30, (s32) ptr_30, 0.0228f);
                    }
                }
                fval_79 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.0003f;
                FastVecScale((s32) ((TI128*)tmp_vec_30), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)tmp_vec_30), (s32) ((TI128*)tmp_vec_30), fval_79);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)tmp_vec_30));
            }
        }
        ptr_48 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (ptr_48 != 0) {
            ptr_22 = M2C_FIELD(ptr_48, void** , 0x68);
            ptr_31 = ((void*)g_hero_state) + 0xF0;
            if (ptr_22 != 0) {
                fval_42 = FastVecLength((s32) ptr_31);
                fval_43 = M2C_FIELD(ptr_22, f32* , 0xC);
                local_f0 = fval_42;
                if (fval_43 < fval_42) {
                    ApproachValue((s32) &local_f0, fval_43, 0.006f);
                    vec_scale_to_length((s32) ptr_31, (s32) ptr_31, local_f0);
                }
            }
        }
        fval_14 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        ptr_44 = ((void*)g_hero_state) + 0x80;
        ptr_43 = ((void*)g_hero_state) + 0xF0;
        tmp_vec_d0[0] = math_fast_sin_or_cos_a(fval_14) * 0.15f;
        fval_15 = math_fast_sin_or_cos_b(fval_14) * 0.15f;
        (*(s32*)&tmp_vec_d0[2]) = 0;
        tmp_vec_d0[1] = fval_15;
        FastVecAdd((s32) &tmp_vec_d0[0], (s32) &tmp_vec_d0[0], (s32) ptr_44);
        FastVecAdd((s32) ((TI128*)tmp_vec_30), (s32) &tmp_vec_d0[0], (s32) ptr_43);
        FastVecSub((s32) ((TI128*)tmp_vec_c0), (s32) ((TI128*)tmp_vec_30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)tmp_vec_c0), (s32) ((TI128*)tmp_vec_c0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)tmp_vec_30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)tmp_vec_c0));
        FastVecSub((s32) ptr_43, (s32) ((TI128*)tmp_vec_30), (s32) &tmp_vec_d0[0]);
        fval_80 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        fval_81 = ((Hero *)g_hero_state)->f[0xAE4/4] - fval_80;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)tmp_vec_c0))) {
            vec_scale_to_length((s32) ((TI128*)tmp_vec_c0), (s32) ((TI128*)tmp_vec_c0), fval_81);
            FastVecAdd((s32) ptr_44, (s32) ptr_44, (s32) ((TI128*)tmp_vec_c0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (val_74 != 0)) {
            min_value = 0.28000003f;
            fval_16 = vec_length_xy((s32) ptr_43);
            local_f4 = fval_16;
            if (fval_16 < min_value) {
                math_spring_float_to_goal((s32) &local_f4, (s32) (((void*)g_hero_state) + 0xAF4), min_value, 0.06768f, 0.43200004f, 0.0f);
                tmp_vec_30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                fval_17 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                tmp_vec_30[2] = 0.0f;
                tmp_vec_30[1] = fval_17 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) ptr_43, (s32) ptr_43, (s32) ((TI128*)tmp_vec_30));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((fval_92 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            fval_82 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            val_12 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (val_12 != 0) {
                val_77 = val_12 == 1;
            } else {
                (*(TI128*)tmp_vec_30) = ((Hero *)g_hero_state)->q[0x110/16];
                val_77 = hero_get_speed_along_forward((s32) ((TI128*)tmp_vec_30)) > 0.0f;
            }
            if (val_77 != 0) {
                if (M2C_FIELD(ptr_21, u8* , 0x43) != 0x35) {
                    set_hero_animation_pal(0x35, 6, 14.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    ptr_49 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(ptr_49, u8* , 0x42) == M2C_FIELD(ptr_49, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, fval_82, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(ptr_21, u8* , 0x43) != 0x35) {
                set_hero_animation_pal(0x35, 0x15, 7.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                ptr_45 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(ptr_45, u8* , 0x42) == M2C_FIELD(ptr_45, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, fval_82, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_state_params[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        val_72 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            val_72 = 1;
        }
        val_22 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (val_22 != 0) {
            FastVecSub((s32)((TI128*)tmp_vec_00), val_22 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            fval_18 = cam_get_view_space_vector_length((s32)((TI128*)tmp_vec_00));
            if (((fval_18 > 2.0f) && (fval_18 < 5.0f)) || (val_72 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09f;
            }
            hero_approach_speed(0.010000001f, 0.010000001f);
            vec_scale_to_length((s32) ((TI128*)tmp_vec_10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)tmp_vec_10));
        } else {
            if ((val_72 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3a)) {
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
        fval_63 = ((Hero *)g_hero_state)->f[0x31C/4];
        fval_155 = 0.15400001f;
        if (fval_63 > 2.25f) {
            fval_155 = 0.07700001f;
        } else if (fval_63 > 1.8f) {
            fval_155 = 0.10780001f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(tmp_vec_00, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)tmp_vec_00), (s32)((TI128*)tmp_vec_00), -0.5f);
            vec_scale_to_length((s32) &tmp_vec_40[0], (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)tmp_vec_10), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &tmp_vec_40[0]);
            tmp_vec_10[3] = 5627.925f;
            (*(u8*)((u8*)tmp_vec_20+9)) = 1;
            (*(u16*)((u8*)tmp_vec_20+10)) = 0x47;
            (*(u8*)((u8*)tmp_vec_20+8)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)tmp_vec_00), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)tmp_vec_10));
        }
        if (math_is_below_plane_within_depth(25.7f) != 0) {
            actuator_play_pattern(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x2a;
            if (g_hero_override_flag != 0) {
                ((Hero *)g_hero_l03_state_alias)->f[0x180/4] = 0.1f;
                ((Hero *)g_hero_l03_state_alias)->i[0x188/4] = 0x19;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x1d;
                ((Hero *)g_hero_l03_state_alias)->i[0x16C/4] = 0;
            }
        }
        val_44 = ((Hero *)g_hero_state)->i[0x1B8/4];
        limit_c = 0xc;
        if (val_44 < 7) {
            ptr_23 = ((void*)g_hero_state) + 0xF0;
            local_f8 = cam_get_view_space_height((s32) ptr_23);
            ApproachValue((s32) &local_f8, fval_155, 0.060000002f);
            cam_set_view_space_height((s32) ptr_23, (s32) ptr_23, local_f8);
        } else if (val_44 > limit_c) {
            ptr_32 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_32, (s32) ptr_32, 0.052f);
            if (cam_get_view_space_height((s32) ptr_32) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            fval_150 = -0.74000007f;
            if (g_hero_l03_block_flag != 0) {
                fval_150 = -1.4000001f;
            }
            if (cam_get_view_space_height((s32) ptr_32) < fval_150) {
                cam_set_view_space_height((s32) ptr_32, (s32) ptr_32, fval_150);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_state_params[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        val_65 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x12);
        if (val_65 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                val_73 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    ptr_24 = ((void*)g_hero_state) + 0xBC0;
                    fval_151 = hero_get_direction_angle_delta((s32) ptr_24, 0);
                    fval_109 = hero_get_direction_angle_delta((s32) ptr_24, 1);
                } else {
                    fval_151 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    fval_109 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (fval_109 < 4.3633237f) {
                    val_73 = 1;
                }
                if (fval_151 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (fval_109 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (val_73 != 0) {
                    hero_steer_heading(1, 0.08208001f, 0.28800002f, 0.33859393f);
                } else {
                    hero_steer_heading(0, 0.08208001f, 0.28800002f, 0.33859393f);
                }
            } else {
                    val_66 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xa)) {
                        val_66 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        val_66 = 0;
                    }
                    if (val_66 != 0) {
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
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_state_params[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        val_23 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ptr_39 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_state_params;
        if ((val_23 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 3)) {
            ptr_33 = ((void*)g_hero_state) + 0x80;
            fval_119 = vec_distance_xy(val_23 + 0x10, (s32) ptr_33);
            if ((*(s32*)&g_hero_l03_block_flag) != 0) {
                fval_119 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) ptr_33);
            }
            fval_119 = fval_119 - 0.5f;
            if (fval_119 < 0.0f) {
                fval_119 = 0.0f;
            }
            val_45 = M2C_FIELD(ptr_39, s32* , 4);
            if (val_45 == 0) {
                fval_110 = 0.75f;
                fval_157 = 0.8f;
                fval_162 = 4.0f;
            } else if (val_45 == 1) {
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
        val_46 = M2C_FIELD(ptr_39, s32* , 4);
        switch (val_46) {
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
        if ((M2C_FIELD(ptr_39, s32* , 4) == 1) && (fval_111 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (fval_65 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.072000004f, 0.28800002f, 0.33859393f);
    } else {
        val_84 = 1;
        if ((M2C_FIELD(ptr_39, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            val_84 = 0;
        }
        if (val_84 != 0) {
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
            ptr_11 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr_11, (s32) ptr_11, 0.0216f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.0096f);
        if ((*(s32*)&g_hero_l03_block_flag) != 0) {
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
        limit_a = 0x8;
        limit_b = 0xF;
        val_47 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (val_47 > limit_a) {
            if (val_47 < 0xf) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.36f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 7) && (((Hero *)g_hero_state)->f[0x184/4] < 0.40000004f)) {
            ptr_25 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ptr_25);
            level_append_record_to_table((s32) ptr_25, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) ptr_25, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) ptr_25, 0xC, 6, 0.0f);
        }
        follower_count = (((Hero *)g_hero_state)->i[0x1B8/4] > limit_b) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), follower_count);
        if (((Hero *)g_hero_state)->i[0x1B8/4] > limit_a) {
            hero_approach_speed(0.076000005f, 0.036000002f);
        }
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x1F) {
            val_49 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((val_49 > limit_a) && (val_49 < 0x12)) {
                ptr_40 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (ptr_40 != 0) {
                    ptr_34 = ((void*)g_hero_state) + 0x80;
                    tmp_vec_30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    tmp_vec_30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    tmp_vec_30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)tmp_vec_00), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)tmp_vec_30));
                    (*(u8*)((u8*)tmp_vec_10+9)) = 3;
                    tmp_vec_00[3] = 5627.925f;
                    (*(u8*)((u8*)tmp_vec_10+8)) = 0;
                    fval_90 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)tmp_vec_10+10)) = M2C_FIELD(ptr_40, u16* , 0xAA);
                    tmp_vec_40[0] = math_fast_sin_or_cos_a(fval_90) * 0.8f;
                    fval_19 = math_fast_sin_or_cos_b(fval_90) * 0.8f;
                    tmp_vec_40[2] = 0.55f;
                    tmp_vec_40[1] = fval_19;
                    FastVecAdd((s32) &tmp_vec_40[0], (s32) &tmp_vec_40[0], (s32) ptr_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ptr_40, coll_process_hit(0.8f, (s32) &tmp_vec_40[0], 0, (s32) ptr_40, (s32)((TI128*)tmp_vec_00)));
                    fval_90 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    tmp_vec_40[0] = math_fast_sin_or_cos_a(fval_90) * 0.8f;
                    fval_21 = math_fast_sin_or_cos_b(fval_90) * 0.8f;
                    tmp_vec_40[2] = 0.55f;
                    tmp_vec_40[1] = fval_21;
                    FastVecAdd((s32) &tmp_vec_40[0], (s32) &tmp_vec_40[0], (s32) ptr_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ptr_40, coll_process_hit(0.8f, (s32) &tmp_vec_40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)tmp_vec_00)));
                    fval_90 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    tmp_vec_40[0] = math_fast_sin_or_cos_a(fval_90) * 0.8f;
                    fval_23 = math_fast_sin_or_cos_b(fval_90) * 0.8f;
                    tmp_vec_40[2] = 0.55f;
                    tmp_vec_40[1] = fval_23;
                    FastVecAdd((s32) &tmp_vec_40[0], (s32) &tmp_vec_40[0], (s32) ptr_34);
                    part_emit_effects_at_nearby_mobys_pal((s32) ptr_40, coll_process_hit(0.8f, (s32) &tmp_vec_40[0], 0, (s32) ptr_40, (s32)((TI128*)tmp_vec_00)));
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
            hero_refresh_speed_from_timer_pal();
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
            vec_ptr = ((void*)g_hero_state) + 0xA60;
            hero_build_move_impulse(0.7f, 0.0f);
            (*(TI128*)tmp_vec_00) = ((Hero *)g_hero_state)->q[0xA60/16];
            fval_66 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)tmp_vec_00));
            ((Hero *)g_hero_state)->f[0x1B0/4] = fval_66;
            if (fval_66 < 0.014f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.014f;
            }
            vec_clear_128((s32) vec_ptr);
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
        approach_speed = fval_152 * 0.0072000003f;
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
        hero_approach_speed(approach_speed, fval_153);
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
        pad_clamp_stick_to_unit_range((s32)((TI128*)tmp_vec_00), (s32) (((void*)g_hero_state) + 0x9F0), 0.24480002f);
        fval_158 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.024434613f) * tmp_vec_00[0];
        if ((*(s32*)&g_hero_l03_block_flag) == 0) {
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
        if ((*(s32*)&g_hero_l03_block_flag) != 0) {
            qcopy(tmp_vec_10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)tmp_vec_10), (s32) ((TI128*)tmp_vec_10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)tmp_vec_10), (s32) (((void*)g_hero_state) + 0xA00), 0.057600003f, 0.43200004f, 0.15f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.057600003f, 0.43200004f, 0.15f);
        }
        FastVecScale((s32) ((TI128*)tmp_vec_10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)tmp_vec_10), (s32) ((TI128*)tmp_vec_10), (s32)(g_hero_state + 0xE0));
        val_34 = coll_process_hit(0.57f, (s32) ((TI128*)tmp_vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (val_34 != 0) {
            FastVecScale((s32) ((TI128*)tmp_vec_20), (s32)(g_hero_state + 0x110), 7.0f);
            for (val_69 = 0; val_69 < val_34; val_69++) {
                if (moby_is_in_special_class_range(((s32 *)g_nearby_l03_moby_list)[val_69]) != 0) {
                    part_queue_impact_effect(((s32 *)g_nearby_l03_moby_list)[val_69], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)tmp_vec_20), 1.0f);
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
        ((Hero *)g_hero_l03_motion_params)->f[0x60/4] = (f32) -fval_167;
        ((Hero *)g_hero_l03_motion_params)->f[0x278/4] = fval_24;
        ((Hero *)g_hero_l03_motion_params)->f[0x1C8/4] = fval_24;
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        val_92 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (((u32) (val_92 - 0x28) >= 2U) && (val_92 != 0x3E)) {
            snd_update_slot_object(0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        } else {
            val_27 = ((Hero *)g_hero_state)->i[0x242C/4];
            if (val_27 != -1) {
                ptr_12 = (val_27 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(ptr_12, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ptr_12, u8* , 0x74) != 0) {
                        snd_stop_voice(val_27);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x242C/4] = -1;
        }
        val_93 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((val_93 == 0x27) || (val_93 == 0x2A)) {
            qcopy(tmp_vec_00, &((Hero *)g_hero_state)->q[0x80/16]);
            fval_71 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.0f, 0.52359885f));
            fval_88 = math_random_float_range(0.080000006f, 0.14000002f);
            tmp_vec_10[0] = math_fast_sin_or_cos_a(fval_71) * fval_88;
            fval_27 = math_fast_sin_or_cos_b(fval_71) * fval_88;
            tmp_vec_10[2] = 0.0f;
            tmp_vec_10[1] = fval_27;
            tmp_vec_10[2] = math_random_float_range(0.060000002f, 0.10000001f);
            tmp_vec_10[3] = -0.012f;
            part_spawn_white_flash_pal((s32)((TI128*)tmp_vec_00), (s32) ((TI128*)tmp_vec_10), 0, -1.0f);
        }
        ptr_20 = ((Hero *)g_hero_state)->ptr[0x1248/4];
        local_11c = 0;
        val_32 = (((LevelInfo *)g_item_l03_record_table)[g_item_slot_to_record[(s32)ptr_20]].x1C != 0);
        if ((s32)ptr_20 == 0xD) {
            val_32 = 0;
        }
        if (val_32 != 0) {
            local_11c = ((Hero *)g_hero_state)->b[0x22BA] != 0;
        }
        ptr_35 = ((void*)g_hero_state) + 0x80;
        find_nearest_path_point(((Hero *)g_hero_state)->i[0x630/4], (s32) ptr_35, (s32) (((void*)g_hero_state) + 0x5D0), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)g_hero_state)->i[0x664/4], (s32) ptr_35, (s32) (((void*)g_hero_state) + 0x610), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        val_68 = 0;
        if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0699999f) {
            val_94 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((val_94 != 0x28) && (val_94 != 0x3E) && (((Hero *)g_hero_state)->i[0x660/4] == 0)) {
                val_68 = ((Hero *)g_hero_state)->i[0x1BC/4] >= 0x1a;
            }
        }
        if (val_68 != 0) {
            ((Hero *)g_hero_state)->i[0x6C8/4] = (s32) (((Hero *)g_hero_state)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)g_hero_state)->i[0x6C8/4] = 0;
        }
        val_35 = ((Hero *)g_hero_state)->i[0x640/4];
        if (((val_35 != 0) && ((((Hero *)g_hero_state)->i[0x640/4] = val_35 + 1) != 0)) || (val_68 != 0)) {
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x120/16]);
            ptr_52 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(ptr_52, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion_pal();
            } else {
                if (vec_length_xy((s32)(g_hero_state + 0xF0)) < 0.050000004f) {
                    ApproachValue((s32)(g_hero_state + 0xF0) + 0xC4, 0.080000006f, 0.016f);
                    M2C_FIELD(ptr_52, f32* , 0xF0) = math_fast_sin_or_cos_a(M2C_FIELD(ptr_52, f32* , 0x64C)) * M2C_FIELD(ptr_52, f32* , 0x1B4);
                    M2C_FIELD(ptr_52, f32* , 0xF4) = math_fast_sin_or_cos_b(M2C_FIELD(ptr_52, f32* , 0x64C)) * M2C_FIELD(ptr_52, f32* , 0x1B4);
                }
                M2C_FIELD(ptr_52, f32* , 0xF8) = (f32) (M2C_FIELD(ptr_52, f32* , 0xF8) - 0.0088f);
            }
        } else {
            fval_51 = (f32) ((Hero *)g_hero_state)->i[0x648/4];
            fval_143 = ((Hero *)g_hero_state)->f[0x644/4] * fval_51;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                fval_143 = ((Hero *)g_hero_state)->f[0x69C/4] * fval_51;
            }
            Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32)((TI128*)tmp_vec_00), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], fval_143);
            if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x664/4], (s32) ((TI128*)tmp_vec_10), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], fval_143);
            }
            if (((Hero *)g_hero_state)->i[0x1BC/4] >= 0x4c) {
                fval_72 = ((Hero *)g_hero_state)->f[0x170/4] * 25.333334f;
                qcopy(tmp_vec_20, &((Hero *)g_hero_state)->q[0x80/16]);
                local_fc = ((Hero *)g_hero_state)->i[0x634/4];
                local_100 = ((Hero *)g_hero_state)->f[0x638/4];
                val_30 = Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)tmp_vec_20), (s32) &local_fc, (s32) &local_100, ((Hero *)g_hero_state)->i[0x654/4], fval_72);
                qcopy(tmp_vec_30, &((Hero *)g_hero_state)->q[0x80/16]);
                local_fc = ((Hero *)g_hero_state)->i[0x634/4];
                local_100 = ((Hero *)g_hero_state)->f[0x638/4];
                if ((((val_30 | Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)tmp_vec_30), (s32) &local_fc, (s32) &local_100, ((Hero *)g_hero_state)->i[0x654/4], fval_72 + 0.1f)) == 0) || (((Hero *)g_hero_state)->i[0x654/4] != 0)) && (((Hero *)g_hero_state)->u[0x2294/4] == 0x27)) {
                    fval_144 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x64C/4], mat_fast_helper_a(tmp_vec_30[0] - tmp_vec_20[0], tmp_vec_30[1] - tmp_vec_20[1])) * 0.47f;
                    if (fval_144 > 0.78539824f) {
                        fval_144 = 0.78539824f;
                    }
                    if (fval_144 < -0.78539824f) {
                        fval_144 = -0.78539824f;
                    }
                    cam_set_limits_first(0.03f, 0.2f);
                    if (((Hero *)g_hero_state)->i[0x65C/4] != 0) {
                        (*(f32*)&g_hero_l03_signed_scalar) = -fval_144;
                    } else {
                        (*(f32*)&g_hero_l03_signed_scalar) = fval_144;
                    }
                }
            }
            val_95 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((val_95 != 0x28) && (val_95 != 0x3E) && (val_95 != 0x29)) {
                (*(f32*)&g_hero_l03_speed_value) = mat_fast_helper_a(vec_length_xy((s32) (((void*)g_hero_state) + 0x110)), ((Hero *)g_hero_state)->f[0x118/4]);
            }
            if (val_32 != 0) {
                cam_limit = 0.43200004f;
                cam_set_limits_fourth(0.024480002f, cam_limit);
                cam_set_limits_second(0.03888f, cam_limit);
                cam_set_limits_third(0.03888f, cam_limit);
                val_24 = ((Hero *)g_hero_state)->i[0x6A8/4];
                if (val_24 != 0) {
                    FastVecSub((s32) ((TI128*)tmp_vec_20), val_24 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)tmp_vec_20), (s32) ((TI128*)tmp_vec_20), (s32) (((void*)g_hero_state) + 0x40));
                    fval_44 = mat_fast_helper_a(tmp_vec_20[0], tmp_vec_20[1]);
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        fval_44 = fast_subtract_rotations(fval_44, 1.5707965f);
                        ((Hero *)g_hero_l03_motion_params)->f[0x278/4] = (f32) (fval_44 * 0.3f);
                        ((Hero *)g_hero_l03_motion_params)->f[0x1C8/4] = (f32) (fval_44 * 0.2f);
                    } else {
                        fval_44 = fast_subtract_rotations(fval_44, -1.5707965f);
                        ((Hero *)g_hero_l03_motion_params)->f[0x278/4] = (f32) (fval_44 * 0.3f);
                        ((Hero *)g_hero_l03_motion_params)->f[0x1C8/4] = (f32) (fval_44 * 0.5f);
                    }
                } else {
                    val_101 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43);
                    if (val_101 == 0x31) {
                        fval_161 = 0.58823526f;
                        fval_114 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        fval_145 = 0.73303837f;
                        ((Hero *)g_hero_l03_motion_params)->f[0x278/4] = fval_114;
                        ((Hero *)g_hero_l03_motion_params)->f[0x118/4] = FastAddRotations(fval_145, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_161);
                        ((Hero *)g_hero_l03_motion_params)->f[0x1C8/4] = FastAddRotations(fval_145, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_161);
                    } else if (val_101 == 0x48) {
                        fval_161 = 0.5f;
                        fval_114 = FastAddRotations(0.13962635f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        fval_145 = -0.06981318f;
                        ((Hero *)g_hero_l03_motion_params)->f[0x278/4] = fval_114;
                        ((Hero *)g_hero_l03_motion_params)->f[0x118/4] = FastAddRotations(fval_145, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_161);
                        ((Hero *)g_hero_l03_motion_params)->f[0x1C8/4] = FastAddRotations(fval_145, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_161);
                    } else if (val_101 == 0x47) {
                        fval_161 = 0.58823526f;
                        fval_114 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        fval_145 = 0.73303837f;
                        ((Hero *)g_hero_l03_motion_params)->f[0x278/4] = fval_114;
                        ((Hero *)g_hero_l03_motion_params)->f[0x118/4] = FastAddRotations(fval_145, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_161);
                        ((Hero *)g_hero_l03_motion_params)->f[0x1C8/4] = FastAddRotations(fval_145, ((Hero *)g_hero_state)->f[0x6A0/4] * fval_161);
                    }
                }
            }
            val_37 = path_advance_index(((Hero *)g_hero_state)->i[0x630/4], ((Hero *)g_hero_state)->i[0x634/4], ((Hero *)g_hero_state)->i[0x648/4], ((Hero *)g_hero_state)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)tmp_vec_20), (s32) &((TI128 *)((Hero *)g_hero_state)->ptr[0x630/4])[val_37 + 1], (s32)((TI128*)tmp_vec_00));
            if (FastVecLength((s32) ((TI128*)tmp_vec_20)) < 0.001f) {
                if (((Hero *)g_hero_state)->i[0x634/4] == val_37) {
                    ((Hero *)g_hero_state)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)g_hero_state)->f[0x64C/4] = mat_fast_helper_a(tmp_vec_20[0], tmp_vec_20[1]);
                ((Hero *)g_hero_state)->f[0x650/4] = mat_fast_helper_a(vec_length_xy((s32) ((TI128*)tmp_vec_20)), M2C_BITWISE(f32, tmp_vec_20[2]));
block_807:
                ((Hero *)g_hero_state)->f[0x1A0/4] = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], ((Hero *)g_hero_state)->f[0x658/4]);
                hero_steer_heading(0, 0.0216f, 0.21600002f, 0.12566373f);
                val_96 = ((Hero *)g_hero_state)->u[0x2294/4];
                if ((((u32) (val_96 - 0x28) < 2U) && (((Hero *)g_hero_state)->b[0x49C] == 0)) || (val_96 == 0x3E)) {
                    if (((Hero *)g_hero_state)->i[0x694/4] != 0) {
                        fval_31 = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x620/4] - ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x624/4] - ((Hero *)g_hero_state)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], fval_31) < 1.5707965f) {
                            ((Hero *)g_hero_state)->f[0x1A0/4] = fval_31;
                            hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.12566373f);
                        }
                    }
                    if ((((Hero *)g_hero_state)->i[0x660/4] != 0) && (((Hero *)g_hero_state)->i[0x678/4] < 0x29)) {
                        FastVecSub((s32) ((TI128*)tmp_vec_20), (s32)((TI128*)tmp_vec_00), (s32) ((TI128*)tmp_vec_10));
                        val_38 = ((Hero *)g_hero_state)->i[0x678/4] + 1;
                        ((Hero *)g_hero_state)->i[0x678/4] = val_38;
                        FastVecScale((s32) ((TI128*)tmp_vec_20), (s32) ((TI128*)tmp_vec_20), (f32) val_38 * 0.025f);
                        fval_73 = (f32) (((Hero *)g_hero_state)->i[0x678/4] - 1) * 0.025f;
                        FastVecSub((s32) ((TI128*)tmp_vec_30), (s32)((TI128*)tmp_vec_00), (s32) ((TI128*)tmp_vec_10));
                        FastVecScale((s32) ((TI128*)tmp_vec_30), (s32) ((TI128*)tmp_vec_30), fval_73);
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + (M2C_BITWISE(f32, tmp_vec_20[2]) - tmp_vec_30[2]));
                        FastVecAdd((s32) ((TI128*)tmp_vec_30), (s32) ((TI128*)tmp_vec_10), (s32) ((TI128*)tmp_vec_20));
                        FastVecSub((s32) ((TI128*)tmp_vec_20), (s32) ((TI128*)tmp_vec_30), (s32) (((void*)g_hero_state) + 0x80));
                        ((Hero *)g_hero_state)->f[0xF0/4] = tmp_vec_20[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = tmp_vec_20[1];
                        FastVecSub((s32) ((TI128*)tmp_vec_20), (s32)((TI128*)tmp_vec_00), (s32) (((void*)g_hero_state) + 0x5D0));
                        fval_97 = ((Hero *)g_hero_state)->f[0x5D8/4];
                        fval_52 = ((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, tmp_vec_20[2]);
                        ((Hero *)g_hero_state)->f[0x88/4] = fval_52;
                        if (fval_52 < fval_97) {
                            if (((Hero *)g_hero_state)->i[0x678/4] < 0x29) {
                                if (fval_52 < fval_97) {
                                    ((Hero *)g_hero_state)->f[0x88/4] = fval_97;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)tmp_vec_20), (s32)((TI128*)tmp_vec_00), (s32)(g_hero_state + 0x5D0));
                        ((Hero *)g_hero_state)->f[0xF0/4] = tmp_vec_20[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = tmp_vec_20[1];
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, tmp_vec_20[2]));
                        FastVecSub((s32) ((TI128*)tmp_vec_30), (s32)(g_hero_state + 0x5D0), (s32)(g_hero_state + 0x80));
                        tmp_vec_30[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)tmp_vec_30)) > 0.020000001f) {
                            vec_scale_to_length((s32) ((TI128*)tmp_vec_30), (s32) ((TI128*)tmp_vec_30), 0.020000001f);
                        }
                        ((Hero *)g_hero_state)->f[0x80/4] = (f32) (((Hero *)g_hero_state)->f[0x80/4] + tmp_vec_30[0]);
                        ((Hero *)g_hero_state)->f[0x84/4] = (f32) (((Hero *)g_hero_state)->f[0x84/4] + tmp_vec_30[1]);
                    }
                    if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.0092f);
                    } else {
                        ApplyHeroGravityAndJumpMotion_pal();
                    }
                } else {
                    ((Hero *)g_hero_state)->i[0x660/4] = 0;
                    fval_115 = 0.0f;
                    if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) && (local_11c != 0)) {
                        hero_resolve_stick_direction(1.0f, 0);
                        fval_115 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1A0/4], ((Hero *)g_hero_state)->f[0x64C/4]);
                        if (fval_115 > 0.78539824f) {
                            fval_115 = 0.78539824f;
                        } else if (fval_115 < -0.78539824f) {
                            fval_115 = -0.78539824f;
                        }
                    }
                    math_approach_with_velocity((s32)(g_hero_state + 0x6A0), fval_115, (s32)(g_hero_state + 0x6A4), 0.0216f, 0.43200004f, 0.0f, 0);
                    ApproachValue((s32)(g_hero_state + 0x680), 0.24000001f, 0.006f);
                    local_104 = ((Hero *)g_hero_state)->i[0x634/4];
                    local_108 = ((Hero *)g_hero_state)->f[0x638/4];
                    ratio = 0.3f;
                    qcopy(tmp_vec_20, &((Hero *)g_hero_state)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)tmp_vec_20), (s32) &local_104, (s32) &local_108, ((Hero *)g_hero_state)->i[0x654/4], ratio);
                    fval_28 = mat_fast_helper_a(vec_distance_xy((s32)(g_hero_state + 0x5D0), (s32) ((TI128*)tmp_vec_20)), M2C_BITWISE(f32, tmp_vec_20[2]) - ((Hero *)g_hero_state)->f[0x5D8/4]);
                    if (fval_28 > 0.0f) {
                        fval_123 = fval_28 * -0.09549296f;
                        if (fval_28 > 0.26179942f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 0;
                        } else if ((fval_28 < 0.13962635f) && (((Hero *)g_hero_state)->i[0x67C/4] == 0)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    } else {
                        fval_123 = -fval_28 * 0.4583662f;
                        if (fval_28 < -0.19198623f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 1;
                        } else if ((fval_28 > -0.122173056f) && (((Hero *)g_hero_state)->i[0x67C/4] == 1)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < fval_123) {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), fval_123, 0.0032000002f);
                    } else {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), fval_123, 0.00080000004f);
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] > 0.24000001f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = 0.24000001f;
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < -0.050000004f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = -0.050000004f;
                    }
                    fval_29 = ((Hero *)g_hero_state)->f[0x680/4] + ((Hero *)g_hero_state)->f[0x674/4];
                    ((Hero *)g_hero_state)->f[0x644/4] = fval_29;
                    if (fval_29 < 0.0f) {
                        ((Hero *)g_hero_state)->f[0x644/4] = 0.0f;
                    }
                    ptr_26 = ((void*)g_hero_state) + 0x5D0;
                    FastVecSub((s32) (((void*)g_hero_state) + 0xF0), (s32)((TI128*)tmp_vec_00), (s32) ptr_26);
                    ptr_41 = ((void*)g_hero_state) + 0x80;
                    FastVecSub((s32) ((TI128*)tmp_vec_20), (s32) ptr_26, (s32) ptr_41);
                    local_10c = -FastVecLength((s32) ((TI128*)tmp_vec_20));
                    math_spring_float_to_goal((s32) &local_10c, (s32) (((void*)g_hero_state) + 0x6AC), 0.0f, 0.0432f, 0.43200004f, 0.14000002f);
                    fval_30 = FastVecLength((s32) ((TI128*)tmp_vec_20));
                    if (fval_30 < ((Hero *)g_hero_state)->f[0x6AC/4]) {
                        ((Hero *)g_hero_state)->f[0x6AC/4] = fval_30;
                    }
                    fval_45 = ((Hero *)g_hero_state)->f[0x6AC/4];
                    if (fval_45 < fval_30) {
                        vec_scale_to_length((s32) ((TI128*)tmp_vec_20), (s32) ((TI128*)tmp_vec_20), fval_45);
                    }
                    FastVecAdd((s32) ptr_41, (s32) ptr_41, (s32) ((TI128*)tmp_vec_20));
                    fval_100 = ((Hero *)g_hero_state)->f[0x88/4];
                    fval_96 = ((Hero *)g_hero_state)->f[0x5D8/4];
                    if (fval_100 < fval_96) {
                        if (((Hero *)g_hero_state)->f[0x31C/4] < 1.0f) {
                            if (fval_100 < fval_96) {
                                ((Hero *)g_hero_state)->f[0x88/4] = fval_96;
                            }
                        }
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x11) {
                        fval_32 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.3490659f, 0.6108653f));
                        tmp_vec_50[0] = math_fast_sin_or_cos_a(fval_32);
                        tmp_vec_50[1] = math_fast_sin_or_cos_b(fval_32);
                        tmp_vec_50[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)tmp_vec_20), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &tmp_vec_50[0]);
                        qcopy(tmp_vec_60, &((Hero *)g_hero_state)->q[0x80/16]);
                        tmp_vec_60[2] += 0.6f;
                        coll_process_hit(1.0f, (s32) ((TI128*)tmp_vec_60), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)tmp_vec_20));
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
        FastVecSub((s32) ((TI128*)tmp_vec_60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &tmp_vec_40[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)tmp_vec_60));
        } else {
            FastVecCross((s32) &tmp_vec_40[0], (s32) ((TI128*)tmp_vec_60), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &tmp_vec_40[0], (s32) &tmp_vec_40[0], 0.2f);
        FastVecAdd((s32) &tmp_vec_50[0], (s32)(g_hero_state + 0x80), (s32) &tmp_vec_40[0]);
        if ((hero_find_ledge_grab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab_pal((s32) &tmp_vec_50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)tmp_vec_00)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)tmp_vec_00), (s32)(g_hero_state + 0x80));
            val_81 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            val_85 = (s32)g_hero_state_buffer;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(val_81 + val_85) * 0.5f);
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
            fval_124 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                fval_124 = 0.43633235f;
            }
            qcopy(tmp_vec_00, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &tmp_vec_00[1], fval_124, (s32) (((void*)g_hero_state) + 0xA4), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            math_approach_with_velocity((s32)((TI128*)tmp_vec_00), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.028800001f, 0.43200004f, 0.052359886f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_refresh_speed_from_timer_pal();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_hop_velocity_pal();
        }
        ptr_60 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets_pal();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) ptr_60, (s32) ptr_60, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_60) < -1.0000001f) {
            cam_set_view_space_height((s32) ptr_60, (s32) ptr_60, -1.0000001f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        ptr_2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0034906592f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0034906592f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ptr_2, (s32) ptr_2, vec_length_xy((s32) ptr_2) * 0.88f);
        hero_apply_mode_transform((s32) ptr_2, (s32) ptr_2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr_2) < -1.0000001f) {
            cam_set_view_space_height((s32) ptr_2, (s32) ptr_2, -1.0000001f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        lerp_angle = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.0003490659f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, lerp_angle), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        val_61 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            val_61 = 0;
        }
        if (val_61 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.120000005f);
            ptr_13 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) ptr_13, (s32) ptr_13, 0.036000002f);
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
        (*(f32*)&g_hero_l03_view_space_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
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
        hero_approach_velocity_pal(fval_125);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            val_28 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (val_28 != -1) {
                ptr_14 = (val_28 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_14, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_14, u8* , 0x74) != 0)) {
                    snd_stop_voice(val_28);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            val_29 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (val_29 != -1) {
                ptr_15 = (val_29 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr_15, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr_15, u8* , 0x74) != 0)) {
                    snd_stop_voice(val_29);
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
        ptr_27 = ((void*)g_hero_state) + 0xF0;
        local_110 = cam_get_view_space_height((s32) ptr_27);
        hero_resolve_stick_direction(fval_163, 0);
        hero_steer_heading(0, 0.036000002f, 0.43200004f, 0.25132746f);
        hero_approach_speed(0.006f, 0.0028000001f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets_pal();
        cam_project_vector_onto_view_plane((s32) ptr_27, (s32) ptr_27);
        math_spring_float_to_goal((s32) &local_110, (s32) (((void*)g_hero_state) + 0xA98), -fval_163 * fval_164, 0.036000002f, 0.43200004f, 0.34000003f);
        hero_apply_mode_transform((s32) ptr_27, (s32) ptr_27, -local_110);
        fval_47 = ((Hero *)g_hero_state)->f[0x88/4];
        if (fval_47 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), fval_47, 0.080000006f);
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
        val_10 = ((Hero *)g_hero_state)->h[0x4AC/2];
        val_25 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (val_25 == val_10) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((val_25 < val_10) && (val_97 = ((Hero *)g_hero_state)->u[0x2294/4], (val_97 != 0xB)) && (val_97 != 0x10) && (val_97 != 0xC) && (val_97 != 0x11) && (val_97 != 0x1B) && (val_97 != 0x89) && (val_97 != 0x48))) {
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
                val_51 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (val_51 < (((Hero *)g_hero_state)->h[0x4AC/2] + 3)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) val_51 * 0.0064000003f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                val_52 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (val_52 < 0x1c) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) val_52 * 0.021200001f);
                }
            }
            if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0x8) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                qcopy(tmp_vec_00, &((Hero *)g_hero_state)->q[0x80/16]);
                cam_offset_point_in_view_space((s32)((TI128*)tmp_vec_00), (s32)((TI128*)tmp_vec_00), 0.5f);
                cam_offset_point_by_side_direction((s32) ((TI128*)tmp_vec_10), (s32)((TI128*)tmp_vec_00), 0.95f);
                if (CollLine((s32)((TI128*)tmp_vec_00), (s32) ((TI128*)tmp_vec_10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                    ((Hero *)g_hero_state)->h[0x524/2] = 1;
                }
            }
        } else {
            hero_update_hop_velocity_pal();
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
        if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters_pal();
        }
        val_98 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((val_98 == 0x10) || (val_98 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xb) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xc) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 8) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)tmp_vec_00), 1, 0.8f, 0.0f, 0.3f);
                    val_39 = coll_process_hit(0.9f, (s32)((TI128*)tmp_vec_00), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (val_39 != 0) {
                        FastVecScale((s32) ((TI128*)tmp_vec_10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (val_70 = 0; val_70 < val_39; val_70++) {
                            if (moby_is_in_special_class_range(((s32 *)g_nearby_l03_moby_list)[val_70]) != 0) {
                                part_queue_impact_effect(((s32 *)g_nearby_l03_moby_list)[val_70], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)tmp_vec_10), 1.0f);
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
        ptr_59 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) ptr_59, (s32) ptr_59, fval_146);
        hero_apply_mode_transform((s32) ptr_59, (s32) ptr_59, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.46000004f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)tmp_vec_00), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(tmp_vec_00[0], tmp_vec_00[1]);
        fval_35 = vec_length_xy((s32)((TI128*)tmp_vec_00));
        if (fval_35 > 0.2f) {
            hero_view = (Hero *)g_hero_state;
            hero_view->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(tmp_vec_00[0], tmp_vec_00[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = fval_35;
            if (fval_35 < g_hero_l03_speed_params[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l03_speed_params[0][1] * 0.020000001f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_l03_speed_params[1][1] * 0.020000001f;
            }
            if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.018000001f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x18AC/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        }
        speed_scale = 1.0f;
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
        hero_approach_speed(speed_scale * 0.0072000003f, 0.008f);
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
            qcopy(tmp_vec_10, &((Hero *)g_hero_state)->q[0xE0/16]);
            found = coll_process_hit(((Hero *)g_hero_state)->f[0x264/4] + 0.2f, (s32)((TI128*)tmp_vec_10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
            for (k = 0; k < found; k++) {
                m = ((s32 *)g_nearby_l03_moby_list)[k];
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
        FastVecSub((s32)((TI128*)tmp_vec_00), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)tmp_vec_00), (s32)(g_hero_state + 0x160)) < 0.0f) {
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
    case 0x79:                                      /* switch 1 */
        part_emit_hero_radial_particles_pal();
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
        ptr_53 = (s32) &g_hero_state_params[((Hero *)g_hero_state)->h[0xBFC/2]];
        val_15 = M2C_FIELD(ptr_53, s32* , 4);
        switch (val_15) {
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
            fval_58 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((f32) M2C_FIELD(ptr_53, s32* , 0x1C) <= fval_58) {
                if (fval_58 <= (f32) M2C_FIELD(ptr_53, s32* , 0x20)) {
                    val_31 = ((M2C_FIELD(ptr_53, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], val_31, (s32) ((TI128*)tmp_vec_10));
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], val_31 | 1, (s32) ((TI128*)tmp_vec_20));
                    FastVecAdd((s32)((TI128*)tmp_vec_00), (s32) ((TI128*)tmp_vec_10), (s32) ((TI128*)tmp_vec_20));
                    FastVecScale((s32)((TI128*)tmp_vec_00), (s32)((TI128*)tmp_vec_00), 0.5f);
                    coll_sweep_from_object((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)tmp_vec_00), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
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
        hero_approach_velocity_pal(0.010000001f);
        fval_1 = 0.0072000003f;
        ptr_3 = ((void*)g_hero_state) + 0x130;
        hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) ptr_3, fval_1);
        break;
    case 0x41:                                      /* switch 1 */
        hero_resolve_stick_direction(0.060000002f, 0);
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_hop_velocity_pal();
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
        fval_135 = 0.19896756f;
        fval_127 = 0.04752f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            fval_135 = 0.23387417f;
            fval_127 = 0.053280003f;
        }
        hero_steer_heading(0, fval_127, 0.21600002f, fval_135);
        hero_approach_speed(0.0072000003f, 0.008f);
        if (((Hero *)g_hero_state)->f[0x174/4] < 0.014f) {
            ((Hero *)g_hero_state)->b[0x40C] = 1U;
            if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)g_hero_state)->b[0x40F] = 1U;
            }
        }
        fval_76 = ReadPadFloatHistory(0);
        if ((FastDiffRots(fval_76, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                fval_168 = 0.060000002f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.025464792f);
                if (fval_168 < 0.0f) {
                    fval_168 = 0.0f;
                }
                if (fval_168 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = fval_168;
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
        fval_48 = vec_length_xy((s32)(g_hero_state + 0xF0));
        if (*(s16 *)(g_hero_state + 0x34E) != 0) {
            fval_48 = fval_48 * 0.98800004f;
        } else {
            fval_48 = fval_48 * 0.90400004f;
        }
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), fval_48);
        ptr_54 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
        M2C_FIELD(ptr_54, s32* , 0xF8) = 0;
        if (M2C_FIELD(ptr_54, s16* , 0x34E) != 0) {
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
        FastVecSub((s32) ((TI128*)tmp_vec_60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &tmp_vec_40[0], (s32) (((void*)g_hero_state) + 0x2C0), (s32) ((TI128*)tmp_vec_60));
        } else {
            FastVecCross((s32) &tmp_vec_40[0], (s32) ((TI128*)tmp_vec_60), (s32) (((void*)g_hero_state) + 0x2C0));
        }
        vec_scale_to_length((s32) &tmp_vec_40[0], (s32) &tmp_vec_40[0], 0.2f);
        FastVecAdd((s32) &tmp_vec_50[0], (s32)(g_hero_state + 0x80), (s32) &tmp_vec_40[0]);
        if ((hero_find_ledge_grab_pal((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab_pal((s32) &tmp_vec_50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)tmp_vec_00)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)tmp_vec_00), (s32)(g_hero_state + 0x80));
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), g_hero_scale_table[FloatToInt(((Hero *)g_hero_state)->f[0xC38/4])] * 0.5f);
            break;
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (local_114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (local_118 != M2C_FIELD(ptr_21, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
