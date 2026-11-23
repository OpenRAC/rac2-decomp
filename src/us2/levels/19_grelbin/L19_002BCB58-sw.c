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
extern void *part_spawn_bubble(s32, s32, f32, f32);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, s32);
extern void RippleDisturb(s32, s32, void *, f32, f32, f32, f32);
extern void pad_clamp_stick_to_unit_range(s32, s32, f32);
extern float AdjustHeroAnimationSpeedForTargetFrame(f32, f32, f32, f32);
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
extern void hero_update_target_speed(void);
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
extern void UpdateHeroLeanAndSwayParameters(void);
extern void hero_apply_reference_tilt_rotation(s32, s32, s32, f32, f32, f32);
extern void hero_shrink_vector_by_amount(f32);
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
extern void hero_update_held_grab(void);
extern s32 shooter_update_ranged_attack(s32);
extern s32 hero_get_anim_id(s32);
extern void hero_detach_from_object_us2(s32);
extern void ClipHeroVelocityAtWall(s32);
extern s32 hero_l19_set_state_us2(s32, s32);
extern char g_impact_effect_data[] MACRO_ADDR;
extern void moby_raise_state_to_eight();
extern void moby_raise_state_to_eight_copy();

/* Runs the hero's state machine once per frame in Grelbin: walking, jumping, gliding, swinging and the rest (USA v2.00 copy). */
void hero_l19_update_state_machine_us2(void) {
    f32 move_speed;
    s32 random_limit;
    s32 *counter_ptr;
    Hero *hero_ptr;
    f32 vec0[4] __attribute__((aligned(16)));
    f32 vec10[4] __attribute__((aligned(16)));
    f32 vec20[4] __attribute__((aligned(16)));
    f32 vec30[4] __attribute__((aligned(16)));
    f32 vec40[4] __attribute__((aligned(16)));
    f32 vec50[4] __attribute__((aligned(16)));
    f32 vec60[4] __attribute__((aligned(16)));
    f32 matrix70[16] __attribute__((aligned(16)));
    f32 vec_b0[4] __attribute__((aligned(16)));
    f32 vec_c0[4] __attribute__((aligned(16)));
    f32 vec_d0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 cam_limit_scale;
    s32 queued_anim;
    s32 queued_blend;
    f32 scaled_speed;
    void *cleared_vec;
    void* object_ptr;
    void* hero_part;
    f32 float_value;
    void* object_ptr_2;
    s32 int_value;
    void* object_ptr_3;
    s32 int_value_2;
    s32 int_value_3;
    void* object_ptr_4;
    s32 int_value_4;
    void* object_ptr_5;
    s32 frame_limit;
    s32 frame_limit_2;
    s32 frame_limit_3;
    s32 follower_mode;
    f32 min_value;
    s32 anim_counter;

    f32 length;
    f32 length_2;
    f32 float_value_2;
    f32 float_value_3;
    f32 float_value_4;
    f32 float_value_5;
    f32 view_height;
    s32 int_value_5;
    f32 float_value_6;
    s32 int_value_6;
    f32 float_value_7;
    f32 float_value_8;
    f32 view_height_2;
    s32 hero_word;
    s32 int_value_7;
    s32 int_value_8;
    f32 abs_value;
    f32 angle;
    f32 trig;
    f32 length_3;
    f32 trig_2;
    f32 view_height_3;
    f32 trig_3;
    f32 float_value_9;
    f32 trig_4;
    f32 float_value_10;
    f32 trig_5;
    f32 float_value_11;
    f32 float_value_12;
    f32 float_value_13;
    f32 float_value_14;
    f32 float_value_15;
    f32 float_value_16;
    f32 float_value_17;
    f32 float_value_18;
    f32 float_value_19;
    f32 float_value_20;
    f32 float_value_21;
    f32 length_4;
    f32 trig_6;
    f32 length_5;
    f32 trig_7;
    f32 hero_value;
    f32 angle_2;
    f32 trig_8;
    f32 length_6;
    f32 float_value_22;
    f32 float_value_23;
    f32 float_value_24;
    f32 view_height_4;
    f32 hero_value_2;
    f32 float_value_25;
    f32 length_7;
    f32 float_value_26;
    f32 float_value_27;
    f32 float_value_28;
    f32 hero_value_3;
    f32 hero_value_4;
    f32 hero_value_5;
    f32 hero_value_6;
    f32 hero_value_7;
    f32 float_value_29;
    f32 hero_value_8;
    f32 float_value_30;
    f32 hero_value_9;
    f32 float_value_31;
    f32 hero_value_10;
    f32 hero_value_11;
    f32 abs_value_2;
    f32 hero_value_12;
    f32 hero_value_13;
    f32 float_value_32;
    f32 float_value_33;
    f32 float_value_34;
    f32 float_value_35;
    f32 float_value_36;
    f32 float_value_37;
    f32 hero_value_14;
    f32 float_value_38;
    f32 float_value_39;
    f32 stick_input;
    f32 hero_value_15;
    f32 length_8;
    f32 hero_value_16;
    f32 hero_value_17;
    f32 length_9;
    f32 float_value_40;
    f32 float_value_41;
    f32 stick_input_2;
    f32 angle_3;
    f32 trig_9;
    f32 float_value_42;
    f32 hero_value_18;
    f32 angle_4;
    f32 float_value_43;
    f32 hero_value_19;
    f32 float_value_44;
    f32 abs_value_3;
    f32 abs_value_4;
    f32 float_value_45;
    f32 float_value_46;
    f32 float_value_47;
    f32 hero_value_20;
    f32 float_value_48;
    f32 float_value_49;
    f32 float_value_50;
    f32 length_10;
    f32 float_value_51;
    f32 float_value_52;
    f32 float_value_53;
    f32 float_value_54;
    f32 float_value_55;
    f32 hero_value_21;
    f32 float_value_56;
    f32 hero_value_22;
    f32 float_value_57;
    f32 float_value_58;
    f32 float_value_59;
    f32 float_value_60;
    f32 hero_value_23;
    f32 float_value_61;
    f32 float_value_62;
    f32 length_11;
    f32 float_value_63;
    f32 float_value_64;
    f32 float_value_65;
    f32 float_value_66;
    f32 float_value_67;
    f32 float_value_68;
    f32 float_value_69;
    f32 float_value_70;
    f32 float_value_71;
    f32 float_value_72;
    f32 hero_value_24;
    f32 hero_value_25;
    f32 hero_value_26;
    f32 hero_value_27;
    f32 float_value_73;
    f32 float_value_74;
    f32 float_value_75;
    f32 hero_value_28;
    f32 hero_value_29;
    f32 float_value_76;
    f32 float_value_77;
    f32 float_value_78;
    f32 float_value_79;
    f32 float_value_80;
    f32 float_value_81;
    f32 float_value_82;
    f32 view_height_5;
    f32 angle_5;
    f32 angle_6;
    f32 hero_value_30;
    f32 float_value_83;
    f32 hero_value_31;
    f32 float_value_84;
    f32 float_value_85;
    f32 float_value_86;
    f32 float_value_87;
    f32 float_value_88;
    f32 float_value_89;
    f32 hero_value_32;
    f32 float_value_90;
    f32 float_value_91;
    f32 float_value_92;
    f32 float_value_93;
    f32 float_value_94;
    f32 float_value_95;
    f32 hero_value_33;
    f32 abs_value_5;
    f32 float_value_96;
    f32 float_value_97;
    f32 abs_value_6;
    s16 hero_word_2;
    s32 int_value_9;
    s16 hero_word_3;
    s32 int_value_10;
    s32 int_value_11;
    s32 int_value_12;
    s32 int_value_13;
    s32 hero_word_4;
    s32 hero_word_5;
    s32 hero_word_6;
    s32 hero_word_7;
    s32 int_value_14;
    s32 hero_word_8;
    s32 hero_word_9;
    s32 int_value_15;
    s32 hero_word_10;
    s32 hero_word_11;
    s32 int_value_16;
    s32 hero_word_12;
    s32 hero_word_13;
    s32 int_value_17;
    s32 int_value_18;
    s32 int_value_19;
    s32 int_value_20;
    s32 int_value_21;
    s32 int_value_22;
    s32 int_value_23;
    s32 int_value_24;
    s32 int_value_25;
    s32 int_value_26;
    s32 hero_word_14;
    s32 int_value_27;
    s32 int_value_28;
    s32 hero_word_15;
    s32 hero_word_16;
    s32 int_value_29;
    s32 int_value_30;
    s32 hero_word_17;
    s32 int_value_31;
    s32 hero_word_18;
    s32 int_value_32;
    s32 hero_word_19;
    s32 hero_word_20;
    s32 hero_word_21;
    s32 int_value_33;
    s32 hero_word_22;
    s32 hero_word_23;
    s32 hero_word_24;
    s32 int_value_34;
    s32 int_value_35;
    s32 int_value_36;
    s32 int_value_37;
    s32 int_value_38;
    s32 int_value_39;
    s32 int_value_40;
    s32 hero_word_25;
    s32 int_value_41;
    s32 int_value_42;
    s32 int_value_43;
    s32 int_value_44;
    s32 int_value_45;
    s32 int_value_46;
    s32 int_value_47;
    s32 int_value_48;
    s32 int_value_49;
    s32 int_value_50;
    s32 int_value_51;
    s32 int_value_52;
    s32 int_value_53;
    s32 int_value_54;
    s32 int_value_55;
    s32 int_value_56;
    s32 int_value_57;
    s32 int_value_58;
    s32 int_value_59;
    s32 int_value_60;
    s32* object_ptr_6;
    s32* object_ptr_7;
    u16 int_value_61;
    u16 int_value_62;
    u16 int_value_63;
    u32 int_value_64;
    u32 int_value_65;
    u32 int_value_66;
    u32 int_value_67;
    u32 int_value_68;
    u32 int_value_69;
    u32 int_value_70;
    u32 int_value_71;
    u32 int_value_72;
    u32 int_value_73;
    u32 int_value_74;
    u32 int_value_75;
    u8 int_value_76;
    u8 int_value_77;
    u8 int_value_78;
    u8 int_value_79;
    void* hero_part_2;
    void* object_ptr_8;
    void* hero_part_3;
    void* object_ptr_9;
    void* hero_part_4;
    void* sound_voice;
    void* sound_voice_2;
    void* hero_moby;
    void* sound_voice_3;
    void* hero_moby_2;
    void* object_ptr_10;
    void* object_ptr_11;
    void* hero_moby_3;
    void* hero_local;
    f32 turn_angle;
    f32 gauge_angle;
    f32 min_distance;
    void* hero_record;
    void* object_ptr_12;
    void* hero_part_5;
    void* hero_part_6;
    void* hero_part_7;
    void* object_ptr_13;
    void* hero_part_8;
    void* hero_part_9;
    void* hero_part_10;
    void* hero_part_11;
    void* hero_part_12;
    void* hero_part_13;
    void* hero_part_14;
    void* hero_part_15;
    void* object_ptr_14;
    void* hero_part_16;
    void* hero_part_17;
    void* hero_part_18;
    void* object_ptr_15;
    void* object_ptr_16;
    void* object_ptr_17;
    void* object_ptr_18;
    void* hero_part_19;
    void* hero_part_20;
    void* hero_moby_4;
    void* object_ptr_19;
    void* object_ptr_20;
    void* object_ptr_21;
    void* hero_moby_5;
    void* hero_moby_6;
    void* object_ptr_22;
    void* object_ptr_23;
    void* object_ptr_24;
    void* object_ptr_25;
    void* hero_part_21;
    void* object_ptr_26;
    void* object_ptr_27;
    void* object_ptr_28;
    void* hero_part_22;
    void* hero_part_23;
    void* object_ptr_29;

    hero_word = ((Hero *)g_hero_state)->i[0x2298/4];
    hero_moby_3 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    int_value_7 = (s32) M2C_FIELD(hero_moby_3, u8* , 0x43);
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
        hero_build_move_impulse(0.5f, 0.033333335f);
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        int_value_65 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_value_65 == 1) || (int_value_65 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vec0) = 0;
                vec0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vec0), (s32)&g_hero_l19_matrix_block[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_l19_matrix_block)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (int_value_77 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (int_value_77 == 0xE)) || (int_value_77 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    int_value_13 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    int_value_13 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != int_value_13) {
                        set_hero_animation(int_value_13, 0, 5.0f);
                    }
                    abs_value = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = abs_value;
                    if (abs_value < 0.55f) {
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
            int_value_74 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (int_value_74 == 3) {
                hero_value_23 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (hero_value_23 > 1.0f) {
                    hero_value_23 = 1.0f;
                }
                hero_moby = ((Hero *)g_hero_state)->ptr[0x2290/4];
                float_value_79 = hero_value_23 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = float_value_79;
                if (M2C_FIELD(hero_moby, u8* , 0x42) == M2C_FIELD(hero_moby, u8* , 0x43)) {
                    hero_value_28 = ((Hero *)g_hero_state)->f[0x174/4] / float_value_79;
                    if ((hero_value_28 > 5.0f) && ((f32) M2C_FIELD(hero_moby, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, hero_value_28, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (int_value_74 == 4) {
                float_value_79 = 0.0075000003f;
            } else {
                float_value_79 = 0.004916667f;
            }
            hero_approach_speed(0.0f, float_value_79);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(float_value_79);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (g_status_flag_b[3] != 0)) {
                int_value_38 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(int_value_38, int_value_38 + 0x30, 0.0061111115f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.015000001f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                ClipHeroVelocityAtWall(0);
                if (((Hero *)g_hero_state)->h[0x34E/2] == 0) {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
                } else {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
                    hero_cancel_velocity_into_wall();
                }
            }
        break;
    case 0x7C:                                      /* switch 1 */
        hero_local = (void*)g_hero_state;
        if (((Hero *)hero_local)->i[0x7A4/4] == 0) {
            int_value_20 = CreateMoby(0x52A);
            ((Hero *)hero_local)->i[0x7A4/4] = int_value_20;
            if (((Hero *)hero_local)->i[0x7A4/4] != 0) {
            qcopy((u8 *)int_value_20 + 0x10, &((Hero *)hero_local)->q[0x80/16]);
            qcopy((u8 *)int_value_20 + 0xF0, &((Hero *)hero_local)->q[0x90/16]);
            M2C_FIELD(int_value_20, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero_local)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero_local)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero_local)->i[0x7A4/4], u8* , 0x23) = 0U;
            hero_word_21 = ((Hero *)hero_local)->i[0x7A4/4];
            M2C_FIELD(hero_word_21, u16* , 0x34) = (u16) (M2C_FIELD(hero_word_21, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero_local)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero_local)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero_local)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero_local)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        hero_word_22 = ((Hero *)hero_local)->i[0x7A4/4];
        if ((u8) M2C_FIELD(hero_word_22, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(hero_word_22, u8* , 0x23) = 0x80U;
        }
        hero_word_4 = ((Hero *)hero_local)->i[0x7A4/4];
        hero_moby_2 = ((Hero *)hero_local)->ptr[0x2290/4];
        qcopy((u8 *)hero_word_4 + 0x10, (u8 *)hero_moby_2 + 0x10);
        qcopy((u8 *)hero_word_4 + 0xF0, (u8 *)hero_moby_2 + 0xF0);
        func_002A0F48(hero_word_4);
        }
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.92f);
        hero_update_height_offset();
        break;
    case 0x32:                                      /* switch 1 */
    case 0x33:                                      /* switch 1 */
    case 0x34:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x47) {
                (*(u16*)&g_hero_state_machine_word) = 0xFFFF;
            }
            snd_update_slot_object(5, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xF);
            actuator_play_pattern(0x16);
        } else {
            hero_word_11 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (hero_word_11 != -1) {
                sound_voice_3 = (hero_word_11 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(sound_voice_3, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(sound_voice_3, u8* , 0x74) != 0) {
                        snd_stop_voice(hero_word_11);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            hero_word_5 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects((hero_word_5 >= 9) ? 8 : hero_word_5, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            hero_value_8 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (hero_value_8 > 0.0f) {
                if (hero_value_8 < 10.0f) {
                    EmitHeroRandomizedMotionEffects(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                hero_word_23 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (hero_word_23 < 0xF) {
                    EmitHeroRandomizedMotionEffects(((s32) (0x14 - hero_word_23) / 3) + 1, 1, 0);
                }
            }
        }
        hero_word_24 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (hero_word_24 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == hero_word_24) {
                part_emit_hero_dust_and_debris(3, 0x10, 0);
                if (g_water_l19_ripple_surface != 0) {
                    RippleDisturb(g_water_l19_ripple_surface, g_water_l19_ripple_param, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x46;
            }
            hero_word_14 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = hero_word_14;
            if (hero_word_14 >= 0x29) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.011635531f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.008726647f;
        float_value_72 = 0.0f;
        min_value = 0.2f;
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            hero_value_25 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (hero_value_25 > 1.0f) {
                hero_value_25 = 1.0f;
            }
            if (hero_value_25 < min_value) {
                hero_value_25 = min_value;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                int_value_11 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                hero_value_25 = ((f32) (s16) int_value_11 * 0.025f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) int_value_11;
                if (hero_value_25 > 1.0f) {
                    hero_value_25 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (hero_value_25 < 0.35f)) {
                hero_value_25 = 0.35f;
            }
            float_value_72 = hero_value_25 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            hero_value_24 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (hero_value_24 > 1.0f) {
                hero_value_24 = 1.0f;
            }
            if (hero_value_24 < min_value) {
                hero_value_24 = min_value;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                anim_counter = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = anim_counter;
                hero_value_24 = ((f32) (s16) anim_counter * 0.025f) + 0.5f;
                if (hero_value_24 > 1.0f) {
                    hero_value_24 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                hero_value_24 = 1.0f;
            }
            float_value_72 = hero_value_24 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                int_value_10 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = int_value_10;
                if ((s16) int_value_10 >= 0x5B) {
                    int_value_62 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (int_value_62 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (int_value_62 + 1);
                    }
                }
                int_value_27 = (*(s32*)&g_frame_counter);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) int_value_27) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) int_value_27;
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
            hero_ptr = (Hero *)g_hero_state;
            if ((g_frame_l19_counter - hero_ptr->i[0xA54/4]) < 0x46) {
                hero_ptr->i[0xA50/4]++;
            }
            hero_ptr->i[0xA54/4] = g_frame_l19_counter;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            float_value_72 = 0.0f;
        }
        hero_value_13 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), float_value_72, (s32) (((void*)g_hero_state) + 0xA28), 0.015f, 0.2f, stick_turn, 0);
        hero_value_18 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], hero_value_13);
        hero_resolve_stick_direction(1.0f, 0);
        hero_steer_heading(0, 0.007f, 0.08f, 0.087266475f);
        ((Hero *)g_hero_state)->f[0xA2C/4] = (f32) ((Hero *)g_hero_state)->f[0x1A4/4];
        math_fast_float_d((s32) (((void*)g_hero_state) + 0xA34));
        if (((Hero *)g_hero_state)->i[0x2298/4] == 1) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.10000001f;
        } else if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.116666675f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.04666667f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.050000004f;
        }
        hero_value_33 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (hero_value_33 < 1.0f) {
                hero_value_33 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            float_value_55 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                float_value_55 = 0.4f;
            }
            if (hero_value_33 < float_value_55) {
                hero_value_33 = float_value_55;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * hero_value_33);
        }
        if (math_fast_float_d((s32)(g_hero_state + 0xA30)) != 0) {
            hero_record = (void*)g_hero_state;
            moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 4, (s32)((TI128*)vec0));
            (*(TI128*)vec20) = 0;
            vec20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)vec20));
            qcopy(vec10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), (s32) ((TI128*)vec20));
            vec10[2] += 0.033333335f;
            part_spawn_bubble((s32)((TI128*)vec0), (s32) ((TI128*)vec10), 25200.0f, -1.0f);
            if ((f32) math_random_int_below(0x64) < 40.0f) {
                int_value_39 = 4;
                int_value_42 = 0xB;
            } else {
                int_value_39 = 0x28;
                int_value_42 = 0x5A;
            }
            ((Hero *)hero_record)->i[0xA30/4] = math_random_int_range(int_value_39, int_value_42);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                object_ptr_18 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (object_ptr_18 != 0) {
                    if (M2C_FIELD(object_ptr_18, s16* , 0xAA) == 0x261) {
                        for (int_value_46 = 0; int_value_46 < 4; int_value_46++) {
                            moby_transform_joint_to_world((s32) object_ptr_18, int_value_46 % 2, (s32)((TI128*)vec0));
                            (*(TI128*)vec20) = 0;
                            vec20[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)vec20));
                            vec0[0] += math_random_float_range(0.0f, 0.03f);
                            vec0[1] += math_random_float_range(0.0f, 0.03f);
                            vec0[2] += math_random_float_range(0.0f, 0.03f);
                            qcopy(vec10, &((Hero *)g_hero_state)->q[0x110/16]);
                            vec_add_offset((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), -0.012500001f, ((Hero *)g_hero_state)->f[0x98/4], ((Hero *)g_hero_state)->f[0x94/4]);
                            ((Hero *)g_hero_state)->h[0xA38/2] = FloatToInt((0.116666675f - ((Hero *)g_hero_state)->f[0x1B4/4]) * 42.85714f);
                            part_spawn_bubble((s32)((TI128*)vec0), (s32) ((TI128*)vec10), math_random_float_range(6300.0f, 9450.0f), -1.0f);
                        }
                    }
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                hero_approach_speed(0.003611111f, 0.0022222223f);
            } else {
                goto block_198;
            }
        } else {
block_198:
            hero_approach_speed(0.0019444445f, 0.0011111111f);
        }
        angle_3 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        int_value_66 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (int_value_66 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], angle_3);
        } else if (int_value_66 == 0x32) {
            hero_value_26 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l19_blend_table, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xF) && (hero_value_26 < 0.075f)) {
                hero_value_26 = 0.075f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), hero_value_26, ((Hero *)g_hero_state)->f[0x98/4], angle_3);
        } else if (int_value_66 == 0x33) {
            length = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &length, 0.0f, 0.0022222223f);
            } else {
                ApproachValue((s32) &length, 0.0f, 0.0011111111f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), length);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        ClipHeroVelocityAtWall(0);
        trig_9 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(angle_3) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), trig_9, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        float_value_44 = hero_value_18 * 47.0f;
        ((Hero *)g_hero_l19_motion_params)->f[0x114/4] = float_value_44;
        ((Hero *)g_hero_l19_motion_params)->f[0x118/4] = (f32) (trig_9 * 1.5f);
        ((Hero *)g_hero_l19_motion_params)->f[0x110/4] = (f32) (trig_9 * 1.4f);
        if (float_value_44 > 0.8726647f) {
            ((Hero *)g_hero_l19_motion_params)->f[0x114/4] = 0.8726647f;
        } else if (float_value_44 < -0.8726647f) {
            ((Hero *)g_hero_l19_motion_params)->f[0x114/4] = -0.8726647f;
        }
        float_value_30 = hero_value_18 * 40.0f;
        float_value_21 = trig_9 * 1.1f;
        ((Hero *)g_hero_l19_motion_params)->f[0x364/4] = 0.03f;
        ((Hero *)g_hero_l19_motion_params)->f[0x368/4] = 0.22f;
        ((Hero *)g_hero_l19_motion_params)->f[0x324/4] = float_value_30;
        ((Hero *)g_hero_l19_motion_params)->f[0x328/4] = float_value_21;
        ((Hero *)g_hero_l19_motion_params)->f[0x414/4] = 0.03f;
        ((Hero *)g_hero_l19_motion_params)->f[0x418/4] = 0.22f;
        ((Hero *)g_hero_l19_motion_params)->f[0x3D4/4] = float_value_30;
        ((Hero *)g_hero_l19_motion_params)->f[0x3D8/4] = float_value_21;
        break;
    case 0x73:                                      /* switch 1 */
        hero_word_6 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        hero_part_10 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects((hero_word_6 >= 9) ? 8 : hero_word_6, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) hero_part_10, (s32) hero_part_10, vec_length_xy((s32) hero_part_10) * 0.92f);
        ClipHeroVelocityAtWall(0);
        break;
    case 0x72:                                      /* switch 1 */
        part_spawn_jittered_after_delay(0xF, 0x1E);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.92f);
        ClipHeroVelocityAtWall(0);
        hero_update_height_offset();
        break;
    case 0x67:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
        length_2 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &length_2, 0.0f, 0.0011111111f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), length_2);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            hero_part_17 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(hero_part_17, s32* , 0x2290), 4, (s32)((TI128*)vec0));
            (*(TI128*)vec20) = 0;
            vec20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), M2C_FIELD(hero_part_17, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)vec20));
            qcopy(vec10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), (s32) ((TI128*)vec20));
            vec10[2] += 0.033333335f;
            part_spawn_bubble((s32)((TI128*)vec0), (s32) ((TI128*)vec10), 25200.0f, -1.0f);
            int_value_28 = M2C_FIELD(hero_part_17, s32* , 0x1B8);
            if (int_value_28 < 0x28) {
                random_limit = 5;
                int_value_51 = math_random_int_range(2, random_limit) + ((s32) M2C_FIELD(hero_part_17, s32* , 0x1B8) / random_limit);
                goto block_224;
            }
            if (int_value_28 >= 0x47) {
                int_value_51 = math_random_int_range(0xA, 0x14);
block_224:
                M2C_FIELD(hero_part_17, s32* , 0xA30) = int_value_51;
            }
        }
        if (((Hero *)g_hero_state)->f[0xA3C/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xA3C/4] = 0.0f;
        }
        ApproachValue((s32) (((void*)g_hero_state) + 0xA3C), -0.025000002f, 0.00041666668f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) ((Hero *)g_hero_state)->f[0xA3C/4];
        break;
    case 0x35:                                      /* switch 1 */
    case 0x36:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x36) {
            part_spawn_jittered_after_delay(0xF, 0x1E);
        }
        if (((Hero *)g_hero_state)->f[0x174/4] > 0.025000002f) {
            part_emit_hero_trail_spark(4, 0xC);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->f[0x174/4] > 0.016666668f)) {
            part_emit_hero_side_particles(0, 1);
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            ((Hero *)g_hero_state)->h[0xA4A/2] -= 1;
            hero_word_7 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects((hero_word_7 >= 7) ? 6 : hero_word_7, 0, 0);
        }
        ((Hero *)g_hero_state)->f[0xC20/4] = 0.6f;
        hero_resolve_stick_direction(0.050000004f, 0);
        if ((((Hero *)g_pad_state)->i[0x1D4/4] == 0) && (((Hero *)g_hero_state)->f[0x1B0/4] < 0.025000002f)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.025000002f;
        }
        hero_steer_heading(0, 0.007f, 0.08f, 0.087266475f);
        math_fast_float_d((s32)(g_hero_state + 0x798));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x35) {
            if ((((Hero *)g_pad_state)->i[0x1D4/4] != 0) && (((Hero *)g_hero_state)->i[0x798/4] != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.050000004f;
            }
            if (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 0.78539824f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            }
            hero_approach_speed(0.0011111111f, 0.0013888889f);
            hero_value_15 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)g_hero_l19_blend_table, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * hero_value_15);
            trig_6 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * hero_value_15;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = trig_6;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            hero_value_9 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((hero_value_9 > 0.0f) && (hero_value_9 < 10.0f)) {
                EmitHeroRandomizedMotionEffects(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.0011666666f);
        ClipHeroVelocityAtWall(0);
        hero_update_height_offset();
        break;
    case 0x85:                                      /* switch 1 */
        object_ptr_10 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)object_ptr_10 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)object_ptr_10 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)vec0), (s32)(g_hero_state + 0x2C0), -1.0f);
        hero_value_27 = 0.0f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_value_27 = -((Hero *)g_hero_state)->f[0x1FB4/4] * 0.75f;
        }
        math_spring_float_to_goal((s32)(g_hero_state + 0x7C0), (s32)(g_hero_state + 0x7C4), hero_value_27, 0.007f, 0.3f, 0.03f);
        FastVecScale((s32) ((TI128*)vec10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)vec10));
        vec_scale_to_length((s32)((TI128*)vec0), (s32)((TI128*)vec0), 1.0f);
        hero_apply_reference_tilt_rotation((s32)((TI128*)vec0), (s32) ((TI128*)vec30), 0, 0.025f, 0.4f, 0.0f);
        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.21666668f;
        vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)g_hero_state, 0.21666668f);
        cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
        vec_clear_128((s32)((TI128*)vec0));
        vec0[1] = -((Hero *)g_hero_state)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(g_hero_state + 0x190), (s32)((TI128*)vec0), (s32)&g_hero_l19_matrix_block[0x218]);
        hero_steer_heading(0, 0.02f, 0.3f, 0.034906592f);
        break;
    case 0x2F:                                      /* switch 1 */
        queued_anim = -1;
        queued_blend = 0;
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
        if ((queued_anim != -1) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation(queued_anim, 0, (f32) queued_blend);
        } else {
            hero_moby_6 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(hero_moby_6, u8* , 0x60) & 2) && (M2C_FIELD(hero_moby_6, u8* , 0x42) == 0x36)) {
                set_hero_animation(hero_get_anim_id(0), 0, 5.0f);
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
        object_ptr_29 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (object_ptr_29 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(object_ptr_29, f32* , 0x10) - M2C_FIELD(hero_moby_3, f32* , 0x10), M2C_FIELD(object_ptr_29, f32* , 0x14) - M2C_FIELD(hero_moby_3, f32* , 0x14));
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
        object_ptr = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (object_ptr != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(object_ptr, f32* , 0x10) - M2C_FIELD(hero_moby_3, f32* , 0x10), M2C_FIELD(object_ptr, f32* , 0x14) - M2C_FIELD(hero_moby_3, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vec0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        length_5 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec0));
        ((Hero *)g_hero_state)->f[0xAB0/4] = length_5;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 60.0f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (length_5 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        hero_word_15 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (hero_word_15 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.45000002f, 0.022222223f);
            object_ptr_19 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            angle_5 = mat_fast_helper_a(M2C_FIELD(object_ptr_19, f32* , 0x10) - M2C_FIELD(hero_moby_3, f32* , 0x10), M2C_FIELD(object_ptr_19, f32* , 0x14) - M2C_FIELD(hero_moby_3, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], angle_5) > 1.5707964f) {
                    angle_5 = FastAddRotations(angle_5, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = angle_5;
            hero_steer_heading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (hero_word_15 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((math_solve_quadratic((s32) &float_value_2, (s32) &float_value_3, -0.0058333334f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (float_value_2 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = float_value_2;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 20.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn_angle = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec0)), vec0[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn_angle, 0.10762865f);
        }
        vec20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        trig_7 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        vec20[2] = 0;
        vec20[1] = trig_7;
        FastVecAdd((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)vec10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vec20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vec10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        hero_value = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (hero_value < 30.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((30.0f - hero_value) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.004166667f);
        qcopy(vec0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)vec0));
        FastVecAdd((s32) ((TI128*)vec10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)vec30), (s32) ((TI128*)vec10), (s32)((TI128*)vec0));
        vec_scale_to_length((s32) ((TI128*)vec30), (s32) ((TI128*)vec30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vec20), (s32)((TI128*)vec0), (s32) ((TI128*)vec30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(hero_moby_3, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        object_ptr_22 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        hero_value_19 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (object_ptr_22 != 0) {
            object_ptr_20 = M2C_FIELD(object_ptr_22, void** , 0x68);
            if ((object_ptr_20 != 0) && (M2C_FIELD(object_ptr_20, s32* , 0x34) != 0)) {
                angle_6 = M2C_FIELD(object_ptr_22, f32* , 0xF8);
                if (FastDiffRots(angle_6, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    angle_6 = FastAddRotations(angle_6, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), angle_6, (s32) (((void*)g_hero_state) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)vec0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)vec0), (s32)((TI128*)vec0), 1.0f);
        if (vec0[2] < 0.23f) {
            vec0[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)vec60));
        vec60[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vec20), (s32) ((TI128*)vec60));
        matrix_from_basis_rows((s32) ((TI128*)matrix70), (s32) ((TI128*)vec20));
        transform_vector((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)matrix70));
        vec10[0] = -mat_fast_helper_a(square_root((vec0[0] * vec0[0]) + (vec0[2] * vec0[2])), vec0[1]);
        angle_2 = mat_fast_helper_a(vec0[2], vec0[0]);
        vec10[1] = angle_2;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), angle_2, (s32) (((void*)g_hero_state) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), vec10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        int_value_49 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((int_value_49 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x29) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                hero_value_30 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0035f;
                if (hero_value_30 > 0.083333336f) {
                    hero_value_30 = 0.083333336f;
                }
                vec_b0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * hero_value_30;
                trig_8 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * hero_value_30;
                hero_part_2 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vec_b0[2]) = 0;
                vec_b0[1] = trig_8;
                FastVecAdd((s32) hero_part_2, (s32) hero_part_2, (s32) ((TI128*)vec_b0));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                hero_part_18 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) hero_part_18, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    hero_part_11 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) hero_part_11, (s32) (((void*)g_hero_state) + 0x110), 0.011111111f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) hero_part_11) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vec_b0), (s32) hero_part_18, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) hero_part_11, (s32) hero_part_11, 0.015833333f);
                    }
                }
                length_8 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vec_b0), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vec_b0), (s32) ((TI128*)vec_b0), length_8);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_b0));
            }
        }
        object_ptr_21 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (object_ptr_21 != 0) {
            object_ptr_12 = M2C_FIELD(object_ptr_21, void** , 0x68);
            hero_part_12 = ((void*)g_hero_state) + 0xF0;
            if (object_ptr_12 != 0) {
                length_6 = FastVecLength((s32) hero_part_12);
                float_value_22 = M2C_FIELD(object_ptr_12, f32* , 0xC);
                float_value_4 = length_6;
                if (float_value_22 < length_6) {
                    ApproachValue((s32) &float_value_4, float_value_22, 0.004166667f);
                    vec_scale_to_length((s32) hero_part_12, (s32) hero_part_12, float_value_4);
                }
            }
        }
        angle = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        hero_part_20 = ((void*)g_hero_state) + 0x80;
        hero_part_19 = ((void*)g_hero_state) + 0xF0;
        vec_d0[0] = math_fast_sin_or_cos_a(angle) * 0.15f;
        trig = math_fast_sin_or_cos_b(angle) * 0.15f;
        (*(s32*)&vec_d0[2]) = 0;
        vec_d0[1] = trig;
        FastVecAdd((s32) &vec_d0[0], (s32) &vec_d0[0], (s32) hero_part_20);
        FastVecAdd((s32) ((TI128*)vec_b0), (s32) &vec_d0[0], (s32) hero_part_19);
        FastVecSub((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_b0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vec_b0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vec_c0));
        FastVecSub((s32) hero_part_19, (s32) ((TI128*)vec_b0), (s32) &vec_d0[0]);
        hero_value_16 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        hero_value_17 = ((Hero *)g_hero_state)->f[0xAE4/4] - hero_value_16;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vec_c0))) {
            vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), hero_value_17);
            FastVecAdd((s32) hero_part_20, (s32) hero_part_20, (s32) ((TI128*)vec_c0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (int_value_49 != 0)) {
            min_distance = 0.23333335f;
            length_3 = vec_length_xy((s32) hero_part_19);
            float_value_5 = length_3;
            if (length_3 < min_distance) {
                math_spring_float_to_goal((s32) &float_value_5, (s32) (((void*)g_hero_state) + 0xAF4), min_distance, 0.047f, 0.3f, 0.0f);
                vec_b0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                trig_2 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vec_b0[2] = 0.0f;
                vec_b0[1] = trig_2 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) hero_part_19, (s32) hero_part_19, (s32) ((TI128*)vec_b0));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((hero_value_19 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            length_9 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            hero_word_3 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (hero_word_3 != 0) {
                int_value_52 = hero_word_3 == 1;
            } else {
                (*(TI128*)vec_b0) = ((Hero *)g_hero_state)->q[0x110/16];
                int_value_52 = hero_get_speed_along_forward((s32) ((TI128*)vec_b0)) > 0.0f;
            }
            if (int_value_52 != 0) {
                if (M2C_FIELD(hero_moby_3, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    hero_moby_5 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(hero_moby_5, u8* , 0x42) == M2C_FIELD(hero_moby_5, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, length_9, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(hero_moby_3, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                hero_moby_4 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(hero_moby_4, u8* , 0x42) == M2C_FIELD(hero_moby_4, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, length_9, 0.5f, -1.0f);
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
        int_value_47 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            int_value_47 = 1;
        }
        hero_word_8 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (hero_word_8 != 0) {
            FastVecSub((s32)((TI128*)vec0), hero_word_8 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            view_height_3 = cam_get_view_space_vector_length((s32)((TI128*)vec0));
            if (((view_height_3 > 2.0f) && (view_height_3 < 5.0f)) || (int_value_47 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
            }
            hero_approach_speed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length((s32) ((TI128*)vec10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec10));
        } else {
            if ((int_value_47 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
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
        hero_value_10 = ((Hero *)g_hero_state)->f[0x31C/4];
        float_value_87 = 0.12833333f;
        if (hero_value_10 > 2.25f) {
            float_value_87 = 0.064166665f;
        } else if (hero_value_10 > 1.8f) {
            float_value_87 = 0.08983333f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(vec0, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)vec0), (s32)((TI128*)vec0), -0.5f);
            vec_scale_to_length((s32) &vec40[0], (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vec10), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &vec40[0]);
            vec10[3] = 5627.925f;
            (*(u8*)((u8*)vec20+9)) = 1;
            (*(u16*)((u8*)vec20+10)) = 0x47;
            (*(u8*)((u8*)vec20+8)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)vec0), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vec10));
        }
        if (math_is_below_plane_within_depth(25.7f) != 0) {
            actuator_play_pattern(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (g_hero_override_flag != 0) {
                ((Hero *)g_hero_l19_state_block)->f[0x180/4] = 0.1f;
                ((Hero *)g_hero_l19_state_block)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)g_hero_l19_state_block)->i[0x16C/4] = 0;
            }
        }
        hero_word_16 = ((Hero *)g_hero_state)->i[0x1B8/4];
        frame_limit_3 = 0xE;
        if (hero_word_16 < 9) {
            hero_part_5 = ((void*)g_hero_state) + 0xF0;
            view_height = cam_get_view_space_height((s32) hero_part_5);
            ApproachValue((s32) &view_height, float_value_87, 0.041666668f);
            cam_set_view_space_height((s32) hero_part_5, (s32) hero_part_5, view_height);
        } else if (hero_word_16 > frame_limit_3) {
            hero_part_13 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) hero_part_13, (s32) hero_part_13, 0.036111113f);
            if (cam_get_view_space_height((s32) hero_part_13) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            float_value_83 = -0.6166667f;
            if (g_hero_l19_lock_flag != 0) {
                float_value_83 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) hero_part_13) < float_value_83) {
                cam_set_view_space_height((s32) hero_part_13, (s32) hero_part_13, float_value_83);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l19_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        hero_word_25 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (hero_word_25 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                int_value_48 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    hero_part_6 = ((void*)g_hero_state) + 0xBC0;
                    hero_value_31 = hero_get_direction_angle_delta((s32) hero_part_6, 0);
                    hero_value_21 = hero_get_direction_angle_delta((s32) hero_part_6, 1);
                } else {
                    hero_value_31 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    hero_value_21 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (hero_value_21 < 4.3633237f) {
                    int_value_48 = 1;
                }
                if (hero_value_31 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (hero_value_21 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (int_value_48 != 0) {
                    hero_steer_heading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    hero_steer_heading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    int_value_41 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xC)) {
                        int_value_41 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        int_value_41 = 0;
                    }
                    if (int_value_41 != 0) {
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
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) g_hero_l19_state_table[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        hero_word_9 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        object_ptr_15 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)g_hero_l19_state_table;
        if ((hero_word_9 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            hero_part_14 = ((void*)g_hero_state) + 0x80;
            length_11 = vec_distance_xy(hero_word_9 + 0x10, (s32) hero_part_14);
            if ((*(s32*)&g_hero_l19_lock_flag) != 0) {
                length_11 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) hero_part_14);
            }
            length_11 = length_11 - 0.5f;
            if (length_11 < 0.0f) {
                length_11 = 0.0f;
            }
            int_value_29 = M2C_FIELD(object_ptr_15, s32* , 4);
            if (int_value_29 == 0) {
                float_value_56 = 0.75f;
                float_value_89 = 0.8f;
                float_value_93 = 4.0f;
            } else if (int_value_29 == 1) {
                float_value_56 = 0.6f;
                float_value_89 = 1.7f;
                float_value_93 = 4.0f;
            } else {
                float_value_56 = 1.3f;
                float_value_89 = 1.7f;
                float_value_93 = 1.9f;
            }
            float_value_41 = length_11 - float_value_56;
            if (math_fabs(float_value_41) < (float_value_89 + 3.0f)) {
                float_value_64 = float_value_41 * 1.1111112f;
                if (float_value_93 < float_value_64) {
                    float_value_64 = float_value_93;
                }
                if (float_value_64 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = float_value_64;
                }
            }
        }
        int_value_30 = M2C_FIELD(object_ptr_15, s32* , 4);
        switch (int_value_30) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            hero_value_11 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (hero_value_11 < 9.0f)) {
                if (hero_value_11 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (hero_value_11 > 7.0f) {
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
            hero_value_22 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            hero_value_22 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        abs_value_2 = math_fabs(hero_value_22);
        if ((M2C_FIELD(object_ptr_15, s32* , 4) == 1) && (hero_value_22 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (abs_value_2 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        int_value_59 = 1;
        if ((M2C_FIELD(object_ptr_15, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            int_value_59 = 0;
        }
        if (int_value_59 != 0) {
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
            hero_part_3 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) hero_part_3, (s32) hero_part_3, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&g_hero_l19_lock_flag) != 0) {
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
        frame_limit = 0xA;
        frame_limit_2 = 0x12;
        hero_word_17 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (hero_word_17 > frame_limit) {
            if (hero_word_17 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            hero_part_7 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) hero_part_7);
            level_append_record_to_table((s32) hero_part_7, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) hero_part_7, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) hero_part_7, 0xC, 6, 0.0f);
        }
        follower_mode = (((Hero *)g_hero_state)->i[0x1B8/4] > frame_limit_2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), follower_mode);
        if (((Hero *)g_hero_state)->i[0x1B8/4] > frame_limit) {
            hero_approach_speed(0.05277778f, 0.025f);
        }
        if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x1F) {
            hero_word_18 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((hero_word_18 > frame_limit) && (hero_word_18 < 0x16)) {
                object_ptr_16 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (object_ptr_16 != 0) {
                    hero_part_15 = ((void*)g_hero_state) + 0x80;
                    vec30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vec30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vec30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vec30));
                    (*(u8*)((u8*)vec10+9)) = 3;
                    vec0[3] = 5627.925f;
                    (*(u8*)((u8*)vec10+8)) = 0;
                    angle_4 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vec10+10)) = M2C_FIELD(object_ptr_16, u16* , 0xAA);
                    vec40[0] = math_fast_sin_or_cos_a(angle_4) * 0.8f;
                    trig_3 = math_fast_sin_or_cos_b(angle_4) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = trig_3;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) hero_part_15);
                    part_emit_effects_at_nearby_mobys((s32) object_ptr_16, coll_process_hit(0.8f, (s32) &vec40[0], 0, (s32) object_ptr_16, (s32)((TI128*)vec0)));
                    angle_4 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vec40[0] = math_fast_sin_or_cos_a(angle_4) * 0.8f;
                    trig_4 = math_fast_sin_or_cos_b(angle_4) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = trig_4;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) hero_part_15);
                    part_emit_effects_at_nearby_mobys((s32) object_ptr_16, coll_process_hit(0.8f, (s32) &vec40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec0)));
                    angle_4 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vec40[0] = math_fast_sin_or_cos_a(angle_4) * 0.8f;
                    trig_5 = math_fast_sin_or_cos_b(angle_4) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = trig_5;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) hero_part_15);
                    part_emit_effects_at_nearby_mobys((s32) object_ptr_16, coll_process_hit(0.8f, (s32) &vec40[0], 0, (s32) object_ptr_16, (s32)((TI128*)vec0)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ClipHeroVelocityAtWall(1);
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
        int_value_36 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            int_value_36 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (int_value_36 != 0)) {
            if (((Hero *)g_hero_state)->f[0x174/4] > 0.016666668f) {
                part_emit_hero_side_particles(0, 2);
            }
            if (((Hero *)g_hero_state)->f[0x174/4] > 0.008333334f) {
                part_emit_hero_trail_spark(2, 4);
            }
            EmitHeroRandomizedMotionEffects(5, 2, 0);
        }
        if (((Hero *)g_hero_state)->h[0x1454/2] == 0) {
            if (((Hero *)g_hero_state)->f[0x174/4] < 0.028333336f) {
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
                if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 2.0943954f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
                    ((Hero *)g_hero_state)->b[0x40F] = 1U;
                }
            }
            stick_input_2 = ReadPadFloatHistory(1);
            if ((FastDiffRots(stick_input_2, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            hero_update_target_speed();
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
            cleared_vec = ((void*)g_hero_state) + 0xA60;
            hero_build_move_impulse(0.7f, 0.0f);
            (*(TI128*)vec0) = ((Hero *)g_hero_state)->q[0xA60/16];
            hero_value_12 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vec0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = hero_value_12;
            if (hero_value_12 < 0.011666667f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.011666667f;
            }
            vec_clear_128((s32) cleared_vec);
        }
        float_value_84 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                abs_value_3 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (abs_value_3 > 0.78539824f)) {
                    float_value_84 = 0.0f;
                }
                hero_set_turn_rates();
            }
        }
        hero_apply_mode_pose_offsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            abs_value_5 = 0.09916667f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.029178405f);
            if (abs_value_5 < 0.0f) {
                abs_value_5 = 0.0f;
            }
            if (abs_value_5 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = abs_value_5;
            }
        }
        scaled_speed = float_value_84 * 0.005f;
        float_value_85 = 0.0055555557f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            hero_value_29 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (hero_value_29 > 1.0f) {
                hero_value_29 = 1.0f;
            }
            if (hero_value_29 < 0.2f) {
                hero_value_29 = 0.2f;
            }
            float_value_85 = 0.004722222f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * hero_value_29);
        }
        abs_value_4 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (abs_value_4 > 0.6108653f)) {
            float_value_76 = 1.0f - (abs_value_4 * 0.4f);
            if (float_value_76 < 0.0f) {
                float_value_76 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * float_value_76);
        }
        hero_approach_speed(scaled_speed, float_value_85);
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
        ClipHeroVelocityAtWall(1);
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
        pad_clamp_stick_to_unit_range((s32)((TI128*)vec0), (s32) (((void*)g_hero_state) + 0x9F0), 0.17f);
        hero_value_32 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * vec0[0];
        if ((*(s32*)&g_hero_l19_lock_flag) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3C) {
                hero_value_32 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, hero_value_32);
        }
        hero_approach_speed(0.027777778f, 0.004166667f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&g_hero_l19_lock_flag) != 0) {
            qcopy(vec10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec10), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vec10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), (s32)(g_hero_state + 0xE0));
        int_value_21 = coll_process_hit(0.57f, (s32) ((TI128*)vec10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (int_value_21 != 0) {
            FastVecScale((s32) ((TI128*)vec20), (s32)(g_hero_state + 0x110), 7.0f);
            for (int_value_44 = 0; int_value_44 < int_value_21; int_value_44++) {
                if (moby_is_in_special_class_range(((s32 *)g_impact_l19_moby_table)[int_value_44]) != 0) {
                    part_queue_impact_effect(((s32 *)g_impact_l19_moby_table)[int_value_44], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.017f, 0.3f);
        cam_set_limits_third(0.025f, 0.3f);
        cam_set_limits_fourth(0.03f, 0.27f);
        float_value_96 = hero_value_32 * 27.0f;
        if (float_value_96 > 1.7f) {
            float_value_96 = 1.7f;
        } else if (float_value_96 < -1.7f) {
            float_value_96 = -1.7f;
        }
        float_value_11 = float_value_96 * 0.5f;
        ((Hero *)g_hero_l19_motion_params)->f[0x60/4] = (f32) -float_value_96;
        ((Hero *)g_hero_l19_motion_params)->f[0x278/4] = float_value_11;
        ((Hero *)g_hero_l19_motion_params)->f[0x1C8/4] = float_value_11;
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
        FastVecSub((s32) ((TI128*)vec60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &vec40[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)vec60));
        } else {
            FastVecCross((s32) &vec40[0], (s32) ((TI128*)vec60), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &vec40[0], (s32) &vec40[0], 0.2f);
        FastVecAdd((s32) &vec50[0], (s32)(g_hero_state + 0x80), (s32) &vec40[0]);
        if ((ProbeLedgeGrab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (ProbeLedgeGrab((s32) &vec50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec0), (s32)(g_hero_state + 0x80));
            int_value_56 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            int_value_60 = (s32)g_hero_state_value_data;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(int_value_56 + int_value_60) * 0.5f);
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
            float_value_67 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                float_value_67 = 0.43633235f;
            }
            qcopy(vec0, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &vec0[1], float_value_67, (s32) (((void*)g_hero_state) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            math_approach_with_velocity((s32)((TI128*)vec0), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_update_target_speed();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            UpdateHeroVelocityForStateWithYawSpring();
        }
        hero_part_23 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) hero_part_23, (s32) hero_part_23, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) hero_part_23) < -0.8333334f) {
            cam_set_view_space_height((s32) hero_part_23, (s32) hero_part_23, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        hero_part = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) hero_part, (s32) hero_part, vec_length_xy((s32) hero_part) * 0.9f);
        hero_apply_mode_transform((s32) hero_part, (s32) hero_part, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) hero_part) < -0.8333334f) {
            cam_set_view_space_height((s32) hero_part, (s32) hero_part, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        gauge_angle = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, gauge_angle), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        int_value_37 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            int_value_37 = 0;
        }
        if (int_value_37 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            hero_part_4 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) hero_part_4, (s32) hero_part_4, 0.025f);
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
        view_height_4 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (view_height_4 < 0.0f) && (float_value_47 = ((Hero *)g_hero_state)->f[0x31C/4], (float_value_47 < 1.2f))) {
            float_value_50 = (float_value_47 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (float_value_50 < 0.0f) {
                float_value_50 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), view_height_4 * float_value_50);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (view_height_4 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&g_camera_l19_view_height) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.027f, 0.3f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.087266475f);
        float_value_68 = 0.0013888889f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            float_value_68 = 0.00055555557f;
        }
        hero_approach_velocity(float_value_68);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            hero_word_12 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (hero_word_12 != -1) {
                sound_voice = (hero_word_12 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(sound_voice, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(sound_voice, u8* , 0x74) != 0)) {
                    snd_stop_voice(hero_word_12);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            hero_word_13 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (hero_word_13 != -1) {
                sound_voice_2 = (hero_word_13 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(sound_voice_2, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(sound_voice_2, u8* , 0x74) != 0)) {
                    snd_stop_voice(hero_word_13);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        float_value_94 = 0.050000004f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            float_value_94 = 0.083333336f;
        }
        float_value_95 = 0.72f;
        hero_value_3 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            float_value_94 = 0.12833333f;
            float_value_95 = 0.98640007f;
        }
        if (hero_value_3 != 0.0f) {
            float_value_95 = hero_value_3;
        }
        hero_part_8 = ((void*)g_hero_state) + 0xF0;
        view_height_2 = cam_get_view_space_height((s32) hero_part_8);
        hero_resolve_stick_direction(float_value_94, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) hero_part_8, (s32) hero_part_8);
        math_spring_float_to_goal((s32) &view_height_2, (s32) (((void*)g_hero_state) + 0xA98), -float_value_94 * float_value_95, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) hero_part_8, (s32) hero_part_8, -view_height_2);
        hero_value_2 = ((Hero *)g_hero_state)->f[0x88/4];
        if (hero_value_2 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), hero_value_2, 0.06666667f);
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
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == 0x14) {
                part_emit_hero_dust_and_debris(3, 0x10, 1);
                if (g_water_l19_ripple_surface != 0) {
                    RippleDisturb(g_water_l19_ripple_surface, g_water_l19_ripple_param, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            hero_value_4 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((hero_value_4 >= 4.0f) && (hero_value_4 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects(7, 0, 0);
            }
        }
        hero_word_2 = ((Hero *)g_hero_state)->h[0x4AC/2];
        hero_word_10 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (hero_word_10 == hero_word_2) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((hero_word_10 < hero_word_2) && (int_value_72 = ((Hero *)g_hero_state)->u[0x2294/4], (int_value_72 != 0xB)) && (int_value_72 != 0x10) && (int_value_72 != 0xC) && (int_value_72 != 0x11) && (int_value_72 != 0x1B) && (int_value_72 != 0x89) && (int_value_72 != 0x48))) {
            hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
            hero_value_14 = ((Hero *)g_hero_state)->f[0x1B4/4];
            if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (hero_value_14 * 0.4f);
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
            ((Hero *)g_hero_state)->f[0x1B4/4] = hero_value_14;
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
                hero_word_19 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (hero_word_19 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) hero_word_19 * 0.0044444446f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                hero_word_20 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (hero_word_20 < 0x22) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) hero_word_20 * 0.014722222f);
                }
            }
            if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                qcopy(vec0, &((Hero *)g_hero_state)->q[0x80/16]);
                cam_offset_point_in_view_space((s32)((TI128*)vec0), (s32)((TI128*)vec0), 0.5f);
                cam_offset_point_by_side_direction((s32) ((TI128*)vec10), (s32)((TI128*)vec0), 0.95f);
                if (CollLine((s32)((TI128*)vec0), (s32) ((TI128*)vec10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                    ((Hero *)g_hero_state)->h[0x524/2] = 1;
                }
            }
        } else {
            UpdateHeroVelocityForStateWithYawSpring();
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
                hero_part_9 = ((void*)g_hero_state) + 0xF0;
                length_10 = vec_length_xy((s32) hero_part_9);
                if (length_10 > 0.06166667f) {
                    length_10 = 0.06166667f;
                }
                vec_fast_normalize_helper((s32) hero_part_9, (s32) hero_part_9, length_10);
            }
        }
        hero_value_5 = ((Hero *)g_hero_state)->f[0x318/4];
        hero_value_20 = ((Hero *)g_hero_state)->f[0x490/4];
        if (hero_value_20 < hero_value_5) {
            float_value_20 = hero_value_20 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = float_value_20;
            if (hero_value_5 < float_value_20) {
                ((Hero *)g_hero_state)->f[0x490/4] = hero_value_5;
            }
        }
        hero_value_6 = ((Hero *)g_hero_state)->f[0x88/4];
        if (hero_value_6 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = hero_value_6;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            hero_value_7 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (hero_value_7 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = hero_value_7;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        int_value_73 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((int_value_73 == 0x10) || (int_value_73 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vec0), 1, 0.8f, 0.0f, 0.3f);
                    int_value_26 = coll_process_hit(0.9f, (s32)((TI128*)vec0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (int_value_26 != 0) {
                        FastVecScale((s32) ((TI128*)vec10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (int_value_45 = 0; int_value_45 < int_value_26; int_value_45++) {
                            if (moby_is_in_special_class_range(((s32 *)g_impact_l19_moby_table)[int_value_45]) != 0) {
                                part_queue_impact_effect(((s32 *)g_impact_l19_moby_table)[int_value_45], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec10), 1.0f);
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
        view_height_5 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        float_value_51 = 0.0011111111f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB)) {
            float_value_51 = 0.0027777778f;
        }
        view_height_5 = view_height_5 - float_value_51;
        if (view_height_5 < 0.0f) {
            view_height_5 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        hero_part_22 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) hero_part_22, (s32) hero_part_22, view_height_5);
        hero_apply_mode_transform((s32) hero_part_22, (s32) hero_part_22, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(g_drive_velocity_view);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec0[0], vec0[1]);
        length_4 = vec_length_xy((s32)((TI128*)vec0));
        if (length_4 > 0.2f) {
            hero_ptr = (Hero *)g_hero_state;
            hero_ptr->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec0[0], vec0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = length_4;
            if (length_4 < g_hero_speed_limits[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_speed_limits[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = g_hero_speed_limits[1][1] * 0.016666668f;
            }
            if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.015000001f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x18AC/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        }
        move_speed = 1.0f;
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
        hero_approach_speed(move_speed * 0.005f, 0.0055555557f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            ClipHeroVelocityAtWall(1);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.0069444445f);
            hero_cancel_velocity_into_wall();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        }
        {
            s32 found, k, m;
            qcopy(vec10, &((Hero *)g_hero_state)->q[0xE0/16]);
            found = coll_process_hit(((Hero *)g_hero_state)->f[0x264/4] + 0.2f, (s32)((TI128*)vec10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
            for (k = 0; k < found; k++) {
                m = ((s32 *)g_impact_l19_moby_table)[k];
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
        FastVecSub((s32)((TI128*)vec0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)vec0), (s32)(g_hero_state + 0x160)) < 0.0f) {
            vec_clear_128((s32)(g_hero_state + 0x160));
        }
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.0075000003f);
        ClipHeroVelocityAtWall(0);
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
    case 0x79:                                      /* switch 1 */
        part_emit_hero_radial_particles();
        vec_clear_128((s32)g_drive_velocity_view);
        ((Hero *)g_drive_velocity_view)->f[8/4] = -0.016666668f;
        break;
    case 0x8D:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_part_16 = ((void*)g_hero_state) + 0xF0;
            hero_update_held_grab();
            hero_resolve_stick_direction(1.0f, 0);
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            hero_approach_speed(0.0f, 0.0035f);
            vec_clear_128((s32) hero_part_16);
            ClipHeroVelocityAtWall(0);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) hero_part_16, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
                hero_cancel_velocity_into_wall();
                break;
            }
            hero_apply_mode_transform((s32) hero_part_16, (s32) hero_part_16, 0.015000001f);
            break;
        }
        break;
    case 0x91:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->h[0x1E0/2] < 0xA) {
            if (g_hero_l19_busy_flag == 0) {
                if (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F) {
                    ((Hero *)g_hero_state)->h[0x1E0/2] = 0x28;
                    ((Hero *)g_hero_state)->i[0x229C/4] = 0;
                    ((Hero *)g_hero_state)->i[0x24A0/4] = 0;
                    hero_detach_from_object_us2(0);
                    FadeToBlack(0x10);
                    ((Hero *)g_hero_state)->c[0x22C1] = 1;
                }
            }
        }
        break;
    case 0x93:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            hero_approach_speed(0.010277778f, 0.007777778f);
            hero_compute_push_direction(99999.0f);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0x118/4] - 0.0069444445f);
                hero_cancel_velocity_into_wall();
            } else {
                ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.015000001f);
            }
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            if (shooter_update_ranged_attack((s32) hero_moby_3) != 0) {
                hero_l19_set_state_us2(0x8D, 1);
            }
        }
        break;
    case 0x94:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09166667f;
            hero_approach_velocity(0.0069444445f);
                    hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.005f);
            break;
        }
        break;
    case 0x8F:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_update_held_grab();
            hero_resolve_stick_direction(0.09583334f, 0);
            if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
                UpdateHeroVelocityForStateWithYawSpring();
            }
            hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), 0.0033333334f);
            if (((Hero *)g_hero_state)->f[0xF8/4] < -0.16666667f) {
                ((Hero *)g_hero_state)->f[0xF8/4] = -0.16666667f;
            }
        }
        break;
    case 0x8E:                                      /* switch 1 */
        if (((*(s32*)&g_hero_l19_busy_flag) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_resolve_stick_direction(0.09583334f, 0);
            hero_update_held_grab();
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_update_turn_from_anim();
            } else {
                ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
                qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
                float_value_75 = 0.10762865f;
                float_value_71 = 0.033f;
                if (((Hero *)g_hero_state)->b[0x40F] != 0) {
                    float_value_75 = 0.13671748f;
                    float_value_71 = 0.037f;
                }
                hero_steer_heading(0, float_value_71, 0.15f, float_value_75);
            }
            hero_approach_speed(0.005f, 0.0055555557f);
            if (((Hero *)g_hero_state)->f[0x174/4] < 0.011666667f) {
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
                if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                    ((Hero *)g_hero_state)->b[0x40F] = 1U;
                }
            }
            stick_input = ReadPadFloatHistory(0);
            if ((FastDiffRots(stick_input, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                    abs_value_6 = 0.09583334f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.02122066f);
                    if (abs_value_6 < 0.0f) {
                        abs_value_6 = 0.0f;
                    }
                    if (abs_value_6 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                        ((Hero *)g_hero_state)->f[0x1B0/4] = abs_value_6;
                    }
                }
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x1440));
            } else {
                hero_set_push_direction((s32) (((void*)g_hero_state) + 0x190));
            }
            ClipHeroVelocityAtWall(1);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
                hero_cancel_velocity_into_wall();
                break;
            }
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
            break;
        }
        break;
    case 0x90:                                      /* switch 1 */
        if ((g_hero_l19_busy_flag == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            length_7 = vec_length_xy((s32)&((Hero *)g_hero_state)->b[0xF0]);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                length_7 = length_7 * 0.99f;
            } else {
                length_7 = length_7 * 0.92f;
            }
            func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), length_7);
            hero_part_21 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            M2C_FIELD(hero_part_21, s32* , 0xF8) = 0;
            if (M2C_FIELD(hero_part_21, s16* , 0x34E) != 0) {
                hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0) + 0x30, 0.0061111115f);
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
    if (hero_word != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (int_value_7 != M2C_FIELD(hero_moby_3, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}
