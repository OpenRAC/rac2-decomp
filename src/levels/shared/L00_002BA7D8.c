/* func_L00_002BA7D8: the hero's per-frame state handler, the twin of func_L20_002CD928 (see
   src/levels/20_yeedil/L20_002CD928.c for what each flag in this unit's config/cflags.txt line is for).
   One function: one prologue, one return, a switch on the state at 0x2294. */

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
extern f32 D_L20_00298970[];
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
extern f32 D_L20_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L20_001A8FF0 MACRO_ADDR;
extern u8 D_L20_001ACEE8[];
extern s32 D_L20_001AFF00 MACRO_ADDR;
extern s32 D_L20_001B2AC8 MACRO_ADDR;
extern s32 D_L20_001B3730 MACRO_ADDR;
extern s32 D_L20_001B3738 MACRO_ADDR;
extern u8 D_L20_001B9E80[];
extern u8 D_L20_001B9FD8[];
extern u8 D_L20_001BA248[];
extern u8 D_L20_001C4480[];
extern u8 D_L20_00267210[];
extern u8 D_L20_00267270[];
extern u8 D_L20_00267274[];
extern Rec2C D_L20_00268D90[];
extern u8 D_L20_00269110[];
extern u8 D_L20_0026D970[];
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
extern void part_spawn_white_flash(s32, s32, s32, f32);
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
extern s32 hero_find_ledge_grab(s32, s32, s32);
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
extern void ApproachHeroVelocity(f32);
extern void ApplyHeroGravityAndJumpMotion(void);
extern void hero_update_airborne_steering(void);
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
extern void *part_spawn_two_point_effect(s32, s32, f32);
extern s32 path_advance_index(s32, s32, s32, s32);
extern s32 Spline_AdvanceByDistance(s32, s32, s32, s32, s32, f32);
extern s32 find_nearest_path_point(s32, s32, s32, s32, s32, s32, f32, f32, f32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern void hero_update_held_grab(void);
extern s32 shooter_update_ranged_attack(s32);
extern s32 SelectHeroStateAnimation(s32);
extern void hero_exit_vehicle_mode(s32);
extern void hero_slide_along_wall(s32);
extern s32 hero_l20_set_state(s32, s32);
extern s32 ref_L00_002BA7D8_00 MACRO_ADDR;
extern void hero_get_offset_vector(f32 *);
/* Runs the hero's state machine once per frame. It picks the code for the current state (walk, jump,
 * swing, swim, hurt and so on) and moves, animates and steers the hero accordingly. */
void hero_l00_update_state_machine(void) {
    Hero *hero_ptr_a;
    s32 index_a;
    s32 count_a;
    f32 scalar1;
    f32 scalar2;
    f32 scalar3;
    f32 speed;
    s32 limit_a;
    s32 *count_ptr;
    Hero *hero_ptr_b;
    f32 vec_a[4] __attribute__((aligned(16)));
    f32 vec_b[4] __attribute__((aligned(16)));
    f32 vec_c[4] __attribute__((aligned(16)));
    f32 vec_d[4] __attribute__((aligned(16)));
    f32 vec_e[4] __attribute__((aligned(16)));
    f32 vec_f[4] __attribute__((aligned(16)));
    f32 vec_g[4] __attribute__((aligned(16)));
    f32 matrix_a[16] __attribute__((aligned(16)));
    f32 vec_h[4] __attribute__((aligned(16)));
    f32 vec_i[4] __attribute__((aligned(16)));
    f32 vec_j[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 const_a;
    s32 anim_id_a;
    s32 blend_a;
    f32 const_b;
    void *ptr_a60;
    void* ptr1;
    void* ptr2;
    f32 scalar4;
    void* ptr3;
    s32 value1;
    void* ptr4;
    s32 value2;
    s32 value3;
    void* ptr5;
    s32 value4;
    void* ptr6;
    s32 limit;
    s32 limit2;
    s32 limit3;
    s32 selection_a;
    f32 const_c;
    s32 count_b;

    f32 scalar5;
    f32 scalar6;
    f32 scalar7;
    f32 scalar8;
    f32 scalar9;
    f32 scalar10;
    f32 scalar11;
    s32 value5;
    f32 scalar12;
    s32 value6;
    f32 scalar13;
    f32 scalar14;
    f32 scalar_sp_n;
    f32 scalar15;
    s32 saved_sub_state;
    s32 saved_anim_id;
    s32 flag_a;
    f32 scalar16;
    f32 scalar17;
    f32 scalar18;
    f32 scalar19;
    f32 scalar20;
    f32 scalar21;
    f32 scalar22;
    f32 scalar23;
    f32 scalar24;
    f32 scalar25;
    f32 scalar26;
    f32 scalar27;
    f32 scalar28;
    f32 scalar29;
    f32 scalar30;
    f32 scalar31;
    f32 scalar32;
    f32 scalar33;
    f32 scalar34;
    f32 scalar35;
    f32 scalar36;
    f32 scalar37;
    f32 scalar38;
    f32 scalar39;
    f32 scalar40;
    f32 scalar41;
    f32 scalar42;
    f32 scalar43;
    f32 scalar44;
    f32 scalar45;
    f32 scalar46;
    f32 scalar47;
    f32 scalar48;
    f32 scalar49;
    f32 scalar50;
    f32 scalar51;
    f32 scalar52;
    f32 scalar53;
    f32 scalar54;
    f32 scalar55;
    f32 scalar56;
    f32 scalar57;
    f32 scalar58;
    f32 scalar59;
    f32 scalar60;
    f32 scalar61;
    f32 scalar62;
    f32 scalar63;
    f32 scalar64;
    f32 scalar65;
    f32 scalar66;
    f32 scalar67;
    f32 scalar68;
    f32 scalar69;
    f32 scalar70;
    f32 scalar71;
    f32 scalar72;
    f32 scalar73;
    f32 scalar74;
    f32 scalar75;
    f32 scalar76;
    f32 scalar77;
    f32 scalar78;
    f32 scalar79;
    f32 scalar80;
    f32 scalar81;
    f32 scalar82;
    f32 scalar83;
    f32 scalar84;
    f32 scalar85;
    f32 scalar86;
    f32 scalar87;
    f32 scalar88;
    f32 scalar89;
    f32 scalar90;
    f32 scalar91;
    f32 scalar92;
    f32 scalar93;
    f32 scalar94;
    f32 scalar95;
    f32 scalar96;
    f32 scalar97;
    f32 scalar98;
    f32 scalar99;
    f32 scalar100;
    f32 scalar101;
    f32 scalar102;
    f32 scalar103;
    f32 scalar104;
    f32 scalar105;
    f32 scalar106;
    f32 scalar107;
    f32 scalar108;
    f32 scalar109;
    f32 scalar110;
    f32 scalar111;
    f32 scalar112;
    f32 scalar113;
    f32 scalar114;
    f32 scalar115;
    f32 scalar116;
    f32 scalar117;
    f32 scalar118;
    f32 scalar119;
    f32 scalar120;
    f32 scalar121;
    f32 scalar122;
    f32 scalar123;
    f32 scalar124;
    f32 scalar125;
    f32 scalar126;
    f32 scalar127;
    f32 scalar128;
    f32 scalar129;
    f32 scalar130;
    f32 scalar131;
    f32 scalar132;
    f32 scalar133;
    f32 scalar134;
    f32 scalar135;
    f32 scalar136;
    f32 scalar137;
    f32 scalar138;
    f32 scalar139;
    f32 scalar140;
    f32 scalar141;
    f32 scalar142;
    f32 scalar143;
    f32 scalar144;
    f32 scalar145;
    f32 scalar146;
    f32 scalar147;
    f32 scalar148;
    f32 scalar149;
    f32 scalar150;
    f32 scalar151;
    f32 scalar152;
    f32 scalar153;
    f32 scalar154;
    f32 scalar155;
    f32 scalar156;
    f32 scalar157;
    f32 scalar158;
    f32 scalar159;
    f32 scalar160;
    f32 scalar161;
    f32 scalar162;
    f32 scalar163;
    f32 scalar164;
    f32 scalar165;
    f32 scalar166;
    f32 scalar167;
    f32 scalar168;
    f32 scalar169;
    f32 scalar170;
    f32 scalar171;
    f32 scalar172;
    s16 short_val1;
    s32 value7;
    s16 short_val2;
    s32 value8;
    s32 value9;
    s32 value10;
    s32 value11;
    s32 value12;
    s32 value13;
    s32 value14;
    s32 value15;
    s32 value16;
    s32 value17;
    s32 value18;
    s32 value19;
    s32 value20;
    s32 value21;
    s32 value22;
    s32 value23;
    s32 value24;
    s32 value25;
    s32 value26;
    s32 value27;
    s32 value28;
    s32 value29;
    s32 value30;
    s32 value31;
    s32 value32;
    s32 value33;
    s32 value34;
    s32 value35;
    s32 value36;
    s32 value37;
    s32 value38;
    s32 value39;
    s32 value40;
    s32 value41;
    s32 value42;
    s32 value43;
    s32 value44;
    s32 value45;
    s32 value46;
    s32 value47;
    s32 value48;
    s32 value49;
    s32 value50;
    s32 value51;
    s32 value52;
    s32 value53;
    s32 value54;
    s32 value55;
    s32 value56;
    s32 value57;
    s32 value58;
    s32 value59;
    s32 value60;
    s32 value61;
    s32 value62;
    s32 value63;
    s32 value64;
    s32 value65;
    s32 value66;
    s32 value67;
    s32 value68;
    s32 value69;
    s32 value70;
    s32 value71;
    s32 value72;
    s32 value73;
    s32 value74;
    s32 value75;
    s32 value76;
    s32 value77;
    s32 value78;
    s32 value79;
    s32 value80;
    s32* ptr7;
    s32* ptr8;
    u16 short_val3;
    u16 short_val4;
    u16 short_val5;
    u32 value81;
    u32 value82;
    u32 value83;
    u32 value84;
    u32 value85;
    u32 value86;
    u32 value87;
    u32 value88;
    u32 value89;
    u32 value90;
    u32 value91;
    u32 value92;
    u8 byte_val1;
    u8 byte_val2;
    u8 byte_val3;
    u8 byte_val4;
    void* ptr9;
    void* ptr10;
    void* ptr11;
    void* ptr12;
    void* ptr13;
    void* ptr14;
    void* ptr15;
    void* ptr16;
    void* ptr17;
    void* ptr18;
    void* ptr19;
    void* ptr20;
    void* hero_object;
    void* hero_block;
    f32 turn_amount;
    f32 angle_a;
    f32 min_value_a;
    void* hero_block_a30;
    void* ptr21;
    void* ptr22;
    void* ptr23;
    void* ptr24;
    void* ptr25;
    void* ptr26;
    void* ptr27;
    void* ptr28;
    void* ptr29;
    void* ptr30;
    void* ptr31;
    void* ptr32;
    void* ptr33;
    void* ptr34;
    void* ptr35;
    void* ptr36;
    void* ptr37;
    void* ptr38;
    void* ptr39;
    void* ptr40;
    void* ptr41;
    void* ptr42;
    void* ptr43;
    void* ptr44;
    void* ptr45;
    void* ptr46;
    void* ptr47;
    void* ptr48;
    void* ptr49;
    void* ptr50;
    void* ptr51;
    void* ptr52;
    void* ptr53;
    void* ptr54;
    void* ptr55;
    void* ptr56;
    void* ptr57;
    void* ptr58;
    void* ptr59;
    void* ptr60;

    saved_sub_state = ((Hero *)g_hero_state)->i[0x2298/4];
    hero_object = ((Hero *)g_hero_state)->ptr[0x2290/4];
    saved_anim_id = (s32) M2C_FIELD(hero_object, u8* , 0x43);
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
            hero_build_move_impulse(0.5f, 0.033333335f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        value82 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((value82 == 1) || (value82 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vec_a) = 0;
                vec_a[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vec_a), (s32)&D_L20_001B9FD8[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)D_L20_001B9FD8)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (byte_val2 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (byte_val2 == 0xE)) || (byte_val2 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    value11 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    value11 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != value11) {
                        set_hero_animation(value11, 0, 5.0f);
                    }
                    scalar16 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = scalar16;
                    if (scalar16 < 0.55f) {
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
            value91 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (value91 == 3) {
                scalar119 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (scalar119 > 1.0f) {
                    scalar119 = 1.0f;
                }
                ptr16 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                scalar145 = scalar119 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = scalar145;
                if (M2C_FIELD(ptr16, u8* , 0x42) == M2C_FIELD(ptr16, u8* , 0x43)) {
                    scalar140 = ((Hero *)g_hero_state)->f[0x174/4] / scalar145;
                    if ((scalar140 > 5.0f) && ((f32) M2C_FIELD(ptr16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, scalar140, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (value91 == 4) {
                scalar145 = 0.0075000003f;
                if (((Hero *)g_hero_state)->b[0x1492] != 0) {
                    scalar145 = 0.00047222225f;
                }
            } else {
                scalar145 = 0.004916667f;
            }
            hero_approach_speed(0.0f, scalar145);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(scalar145);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                value57 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(value57, value57 + 0x30, 0.0061111115f);
                } else {
                    hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.015000001f);
                    if (((Hero *)g_hero_state)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)g_hero_state)->q[0x80/16], &((Hero *)g_hero_state)->q[0x2D0/16]);
                        ((Hero *)g_hero_state)->f[0x31C/4] = 0.0f;
                        ((Hero *)g_hero_state)->h[0x34E/2] = 0;
                    }
                }
            } else {
                hero_slide_along_wall(0);
                if (((Hero *)g_hero_state)->h[0x34E/2] == 0) {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
                } else {
                    hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
                    hero_cancel_velocity_into_wall();
                }
            }
        break;
    case 0x7C:                                      /* switch 1 */
        hero_block = (void*)g_hero_state;
        if (((Hero *)hero_block)->i[0x7A4/4] == 0) {
            value28 = CreateMoby(0x52A /* moby class 1322 */);
            ((Hero *)hero_block)->i[0x7A4/4] = value28;
            if (((Hero *)hero_block)->i[0x7A4/4] != 0) {
            qcopy((u8 *)value28 + 0x10, &((Hero *)hero_block)->q[0x80/16]);
            qcopy((u8 *)value28 + 0xF0, &((Hero *)hero_block)->q[0x90/16]);
            M2C_FIELD(value28, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero_block)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero_block)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero_block)->i[0x7A4/4], u8* , 0x23) = 0U;
            value48 = ((Hero *)hero_block)->i[0x7A4/4];
            M2C_FIELD(value48, u16* , 0x34) = (u16) (M2C_FIELD(value48, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero_block)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero_block)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero_block)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero_block)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        value50 = ((Hero *)hero_block)->i[0x7A4/4];
        if ((u8) M2C_FIELD(value50, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(value50, u8* , 0x23) = 0x80U;
        }
        value12 = ((Hero *)hero_block)->i[0x7A4/4];
        ptr18 = ((Hero *)hero_block)->ptr[0x2290/4];
        qcopy((u8 *)value12 + 0x10, (u8 *)ptr18 + 0x10);
        qcopy((u8 *)value12 + 0xF0, (u8 *)ptr18 + 0xF0);
        func_002A0F48(value12);
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
                (*(u16*)&D_0018CF10) = 0xFFFF;
            }
            snd_update_slot_object(5, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xF);
            queue_copy_record_by_index(0x16);
        } else {
            value21 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (value21 != -1) {
                ptr17 = (value21 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(ptr17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ptr17, u8* , 0x74) != 0) {
                        snd_stop_voice(value21);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            value13 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects((value13 >= 9) ? 8 : value13, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            scalar62 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (scalar62 > 0.0f) {
                if (scalar62 < 10.0f) {
                    EmitHeroRandomizedMotionEffects(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                value51 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (value51 < 0xF) {
                    EmitHeroRandomizedMotionEffects(((s32) (0x14 - value51) / 3) + 1, 1, 0);
                }
            }
        }
        value52 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (value52 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == value52) {
                part_emit_hero_dust_and_debris(3, 0x10, 0);
                if (D_L20_001B3730 != 0) {
                    RippleDisturb(D_L20_001B3730, D_L20_001B3738, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x46;
            }
            value35 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = value35;
            if (value35 >= 0x29) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.011635531f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.008726647f;
        scalar132 = 0.0f;
        const_c = 0.2f;
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            scalar134 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (scalar134 > 1.0f) {
                scalar134 = 1.0f;
            }
            if (scalar134 < const_c) {
                scalar134 = const_c;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                value9 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                scalar134 = ((f32) (s16) value9 * 0.025f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) value9;
                if (scalar134 > 1.0f) {
                    scalar134 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (scalar134 < 0.35f)) {
                scalar134 = 0.35f;
            }
            scalar132 = scalar134 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            scalar133 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (scalar133 > 1.0f) {
                scalar133 = 1.0f;
            }
            if (scalar133 < const_c) {
                scalar133 = const_c;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                count_b = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = count_b;
                scalar133 = ((f32) (s16) count_b * 0.025f) + 0.5f;
                if (scalar133 > 1.0f) {
                    scalar133 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                scalar133 = 1.0f;
            }
            scalar132 = scalar133 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                value8 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = value8;
                if ((s16) value8 >= 0x5B) {
                    short_val4 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (short_val4 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (short_val4 + 1);
                    }
                }
                value36 = (*(s32*)&D_001A7390);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) value36) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) value36;
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
            hero_ptr_b = (Hero *)g_hero_state;
            if ((D_L20_001B2AC8 - hero_ptr_b->i[0xA54/4]) < 0x46) {
                hero_ptr_b->i[0xA50/4]++;
            }
            hero_ptr_b->i[0xA54/4] = D_L20_001B2AC8;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            scalar132 = 0.0f;
        }
        scalar70 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), scalar132, (s32) (((void*)g_hero_state) + 0xA28), 0.015f, 0.2f, stick_turn, 0);
        scalar92 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], scalar70);
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
        scalar168 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (scalar168 < 1.0f) {
                scalar168 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            scalar111 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                scalar111 = 0.4f;
            }
            if (scalar168 < scalar111) {
                scalar168 = scalar111;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * scalar168);
        }
        if (math_fast_float_d((s32)(g_hero_state + 0xA30)) != 0) {
            hero_block_a30 = (void*)g_hero_state;
            moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 4, (s32)((TI128*)vec_a));
            (*(TI128*)vec_c) = 0;
            vec_c[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), (s32) ((TI128*)vec_c));
            qcopy(vec_b, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), 0.025000002f);
            FastVecAdd((s32) ((TI128*)vec_b), (s32) ((TI128*)vec_b), (s32) ((TI128*)vec_c));
            vec_b[2] += 0.033333335f;
            part_spawn_bubble((s32)((TI128*)vec_a), (s32) ((TI128*)vec_b), 25200.0f, -1.0f);
            if ((f32) math_random_int_below(0x64) < 40.0f) {
                value58 = 4;
                value62 = 0xB;
            } else {
                value58 = 0x28;
                value62 = 0x5A;
            }
            ((Hero *)hero_block_a30)->i[0xA30/4] = math_random_int_range(value58, value62);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                ptr41 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (ptr41 != 0) {
                    if (M2C_FIELD(ptr41, s16* , 0xAA) == 0x261 /* moby class 609 */) {
                        for (value66 = 0; value66 < 4; value66++) {
                            moby_transform_joint_to_world((s32) ptr41, value66 % 2, (s32)((TI128*)vec_a));
                            (*(TI128*)vec_c) = 0;
                            vec_c[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), (s32) ((TI128*)vec_c));
                            vec_a[0] += math_random_float_range(0.0f, 0.03f);
                            vec_a[1] += math_random_float_range(0.0f, 0.03f);
                            vec_a[2] += math_random_float_range(0.0f, 0.03f);
                            qcopy(vec_b, &((Hero *)g_hero_state)->q[0x110/16]);
                            vec_add_offset((s32) ((TI128*)vec_b), (s32) ((TI128*)vec_b), -0.012500001f, ((Hero *)g_hero_state)->f[0x98/4], ((Hero *)g_hero_state)->f[0x94/4]);
                            ((Hero *)g_hero_state)->h[0xA38/2] = FloatToInt((0.116666675f - ((Hero *)g_hero_state)->f[0x1B4/4]) * 42.85714f);
                            part_spawn_bubble((s32)((TI128*)vec_a), (s32) ((TI128*)vec_b), math_random_float_range(6300.0f, 9450.0f), -1.0f);
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
        scalar89 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        value83 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (value83 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], scalar89);
        } else if (value83 == 0x32) {
            scalar135 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)D_L20_00269110, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xF) && (scalar135 < 0.075f)) {
                scalar135 = 0.075f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), scalar135, ((Hero *)g_hero_state)->f[0x98/4], scalar89);
        } else if (value83 == 0x33) {
            scalar5 = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &scalar5, 0.0f, 0.0022222223f);
            } else {
                ApproachValue((s32) &scalar5, 0.0f, 0.0011111111f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), scalar5);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        hero_slide_along_wall(0);
        scalar90 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(scalar89) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), scalar90, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        scalar96 = scalar92 * 47.0f;
        ((Hero *)D_L20_00267210)->f[0x114/4] = scalar96;
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (scalar90 * 1.5f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (scalar90 * 1.4f);
        if (scalar96 > 0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = 0.8726647f;
        } else if (scalar96 < -0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = -0.8726647f;
        }
        scalar63 = scalar92 * 40.0f;
        scalar37 = scalar90 * 1.1f;
        ((Hero *)D_L20_00267210)->f[0x364/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x368/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x324/4] = scalar63;
        ((Hero *)D_L20_00267210)->f[0x328/4] = scalar37;
        ((Hero *)D_L20_00267210)->f[0x414/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x418/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x3D4/4] = scalar63;
        ((Hero *)D_L20_00267210)->f[0x3D8/4] = scalar37;
        break;
    case 0x73:                                      /* switch 1 */
        value14 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        ptr28 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects((value14 >= 9) ? 8 : value14, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) ptr28, (s32) ptr28, vec_length_xy((s32) ptr28) * 0.92f);
        hero_slide_along_wall(0);
        break;
    case 0x72:                                      /* switch 1 */
        part_spawn_jittered_after_delay(0xF, 0x1E);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.92f);
        hero_slide_along_wall(0);
        hero_update_height_offset();
        break;
    case 0x67:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
        scalar6 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &scalar6, 0.0f, 0.0011111111f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), scalar6);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            ptr36 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(ptr36, s32* , 0x2290), 4, (s32)((TI128*)vec_a));
            (*(TI128*)vec_c) = 0;
            vec_c[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), M2C_FIELD(ptr36, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), (s32) ((TI128*)vec_c));
            qcopy(vec_b, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), 0.025000002f);
            FastVecAdd((s32) ((TI128*)vec_b), (s32) ((TI128*)vec_b), (s32) ((TI128*)vec_c));
            vec_b[2] += 0.033333335f;
            part_spawn_bubble((s32)((TI128*)vec_a), (s32) ((TI128*)vec_b), 25200.0f, -1.0f);
            value37 = M2C_FIELD(ptr36, s32* , 0x1B8);
            if (value37 < 0x28) {
                limit_a = 5;
                value71 = math_random_int_range(2, limit_a) + ((s32) M2C_FIELD(ptr36, s32* , 0x1B8) / limit_a);
                goto block_224;
            }
            if (value37 >= 0x47) {
                value71 = math_random_int_range(0xA, 0x14);
block_224:
                M2C_FIELD(ptr36, s32* , 0xA30) = value71;
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
            value15 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects((value15 >= 7) ? 6 : value15, 0, 0);
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
            scalar81 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)D_L20_00269110, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * scalar81);
            scalar39 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * scalar81;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = scalar39;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            scalar64 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((scalar64 > 0.0f) && (scalar64 < 10.0f)) {
                EmitHeroRandomizedMotionEffects(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.0011666666f);
        hero_slide_along_wall(0);
        hero_update_height_offset();
        break;
    case 0x85:                                      /* switch 1 */
        ptr19 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)ptr19 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)ptr19 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)vec_a), (s32)(g_hero_state + 0x2C0), -1.0f);
        scalar136 = 0.0f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            scalar136 = -((Hero *)g_hero_state)->f[0x1FB4/4] * 0.75f;
        }
        math_spring_float_to_goal((s32)(g_hero_state + 0x7C0), (s32)(g_hero_state + 0x7C4), scalar136, 0.007f, 0.3f, 0.03f);
        FastVecScale((s32) ((TI128*)vec_b), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), (s32) ((TI128*)vec_b));
        vec_scale_to_length((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), 1.0f);
        hero_apply_reference_tilt_rotation((s32)((TI128*)vec_a), (s32) ((TI128*)vec_d), 0, 0.025f, 0.4f, 0.0f);
        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.21666668f;
        vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)g_hero_state, 0.21666668f);
        cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
        vec_clear_128((s32)((TI128*)vec_a));
        vec_a[1] = -((Hero *)g_hero_state)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(g_hero_state + 0x190), (s32)((TI128*)vec_a), (s32)&D_L20_001B9FD8[0x218]);
        hero_steer_heading(0, 0.02f, 0.3f, 0.034906592f);
        break;
    case 0x2F:                                      /* switch 1 */
        anim_id_a = -1;
        blend_a = 0;
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
        if ((anim_id_a != -1) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation(anim_id_a, 0, (f32) blend_a);
        } else {
            ptr49 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr49, u8* , 0x60) & 2) && (M2C_FIELD(ptr49, u8* , 0x42) == 0x36)) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, 5.0f);
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
        ptr60 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (ptr60 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr60, f32* , 0x10) - M2C_FIELD(hero_object, f32* , 0x10), M2C_FIELD(ptr60, f32* , 0x14) - M2C_FIELD(hero_object, f32* , 0x14));
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
        ptr1 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (ptr1 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr1, f32* , 0x10) - M2C_FIELD(hero_object, f32* , 0x10), M2C_FIELD(ptr1, f32* , 0x14) - M2C_FIELD(hero_object, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vec_a, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        scalar40 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_a));
        ((Hero *)g_hero_state)->f[0xAB0/4] = scalar40;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 60.0f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (scalar40 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        value38 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (value38 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.45000002f, 0.022222223f);
            ptr45 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            scalar150 = mat_fast_helper_a(M2C_FIELD(ptr45, f32* , 0x10) - M2C_FIELD(hero_object, f32* , 0x10), M2C_FIELD(ptr45, f32* , 0x14) - M2C_FIELD(hero_object, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], scalar150) > 1.5707964f) {
                    scalar150 = FastAddRotations(scalar150, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = scalar150;
            hero_steer_heading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (value38 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((math_solve_quadratic((s32) &scalar7, (s32) &scalar8, -0.0058333334f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (scalar7 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = scalar7;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 20.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn_amount = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec_a)), vec_a[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn_amount, 0.10762865f);
        }
        vec_c[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        scalar41 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        vec_c[2] = 0;
        vec_c[1] = scalar41;
        FastVecAdd((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)vec_b), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vec_c));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vec_b), ((Hero *)g_hero_state)->f[0xAA0/4]);
        scalar42 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (scalar42 < 30.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((30.0f - scalar42) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.004166667f);
        qcopy(vec_a, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)vec_a));
        FastVecAdd((s32) ((TI128*)vec_b), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)vec_d), (s32) ((TI128*)vec_b), (s32)((TI128*)vec_a));
        vec_scale_to_length((s32) ((TI128*)vec_d), (s32) ((TI128*)vec_d), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vec_c), (s32)((TI128*)vec_a), (s32) ((TI128*)vec_d));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_c), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(hero_object, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        ptr50 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        scalar95 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (ptr50 != 0) {
            ptr46 = M2C_FIELD(ptr50, void** , 0x68);
            if ((ptr46 != 0) && (M2C_FIELD(ptr46, s32* , 0x34) != 0)) {
                scalar151 = M2C_FIELD(ptr50, f32* , 0xF8);
                if (FastDiffRots(scalar151, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    scalar151 = FastAddRotations(scalar151, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), scalar151, (s32) (((void*)g_hero_state) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)vec_a), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), 1.0f);
        if (vec_a[2] < 0.23f) {
            vec_a[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)vec_g));
        vec_g[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_g));
        matrix_from_basis_rows((s32) ((TI128*)matrix_a), (s32) ((TI128*)vec_c));
        transform_vector((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), (s32) ((TI128*)matrix_a));
        vec_b[0] = -mat_fast_helper_a(square_root((vec_a[0] * vec_a[0]) + (vec_a[2] * vec_a[2])), vec_a[1]);
        scalar43 = mat_fast_helper_a(vec_a[2], vec_a[0]);
        vec_b[1] = scalar43;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), scalar43, (s32) (((void*)g_hero_state) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), vec_b[0], (s32) (((void*)g_hero_state) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        value69 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((value69 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x29) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                scalar152 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0035f;
                if (scalar152 > 0.083333336f) {
                    scalar152 = 0.083333336f;
                }
                vec_h[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * scalar152;
                scalar44 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * scalar152;
                ptr9 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vec_h[2]) = 0;
                vec_h[1] = scalar44;
                FastVecAdd((s32) ptr9, (s32) ptr9, (s32) ((TI128*)vec_h));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                ptr37 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) ptr37, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    ptr29 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) ptr29, (s32) (((void*)g_hero_state) + 0x110), 0.011111111f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) ptr29) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vec_h), (s32) ptr37, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) ptr29, (s32) ptr29, 0.015833333f);
                    }
                }
                scalar82 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vec_h), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vec_h), (s32) ((TI128*)vec_h), scalar82);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_h));
            }
        }
        ptr47 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (ptr47 != 0) {
            ptr21 = M2C_FIELD(ptr47, void** , 0x68);
            ptr30 = ((void*)g_hero_state) + 0xF0;
            if (ptr21 != 0) {
                scalar45 = FastVecLength((s32) ptr30);
                scalar46 = M2C_FIELD(ptr21, f32* , 0xC);
                scalar9 = scalar45;
                if (scalar46 < scalar45) {
                    ApproachValue((s32) &scalar9, scalar46, 0.004166667f);
                    vec_scale_to_length((s32) ptr30, (s32) ptr30, scalar9);
                }
            }
        }
        scalar17 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        ptr43 = ((void*)g_hero_state) + 0x80;
        ptr42 = ((void*)g_hero_state) + 0xF0;
        vec_j[0] = math_fast_sin_or_cos_a(scalar17) * 0.15f;
        scalar18 = math_fast_sin_or_cos_b(scalar17) * 0.15f;
        (*(s32*)&vec_j[2]) = 0;
        vec_j[1] = scalar18;
        FastVecAdd((s32) &vec_j[0], (s32) &vec_j[0], (s32) ptr43);
        FastVecAdd((s32) ((TI128*)vec_h), (s32) &vec_j[0], (s32) ptr42);
        FastVecSub((s32) ((TI128*)vec_i), (s32) ((TI128*)vec_h), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vec_i), (s32) ((TI128*)vec_i), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vec_h), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vec_i));
        FastVecSub((s32) ptr42, (s32) ((TI128*)vec_h), (s32) &vec_j[0]);
        scalar83 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        scalar84 = ((Hero *)g_hero_state)->f[0xAE4/4] - scalar83;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vec_i))) {
            vec_scale_to_length((s32) ((TI128*)vec_i), (s32) ((TI128*)vec_i), scalar84);
            FastVecAdd((s32) ptr43, (s32) ptr43, (s32) ((TI128*)vec_i));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (value69 != 0)) {
            min_value_a = 0.23333335f;
            scalar19 = vec_length_xy((s32) ptr42);
            scalar10 = scalar19;
            if (scalar19 < min_value_a) {
                math_spring_float_to_goal((s32) &scalar10, (s32) (((void*)g_hero_state) + 0xAF4), min_value_a, 0.047f, 0.3f, 0.0f);
                vec_h[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                scalar20 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vec_h[2] = 0.0f;
                vec_h[1] = scalar20 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) ptr42, (s32) ptr42, (s32) ((TI128*)vec_h));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((scalar95 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            scalar85 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            short_val2 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (short_val2 != 0) {
                value72 = short_val2 == 1;
            } else {
                (*(TI128*)vec_h) = ((Hero *)g_hero_state)->q[0x110/16];
                value72 = hero_get_speed_along_forward((s32) ((TI128*)vec_h)) > 0.0f;
            }
            if (value72 != 0) {
                if (M2C_FIELD(hero_object, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    ptr48 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(ptr48, u8* , 0x42) == M2C_FIELD(ptr48, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, scalar85, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(hero_object, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                ptr44 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(ptr44, u8* , 0x42) == M2C_FIELD(ptr44, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, scalar85, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            value16 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (value16 != 0) {
                scalar65 = vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), value16 + 0x10);
                value78 = 0;
                if ((((Hero *)g_hero_state)->b[0x1496] != 0) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->b[0x1495] != 0)) {
                    value78 = 1;
                }
                if (((scalar65 > 2.0f) && (scalar65 < 5.0f)) || (value78 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
                }
                hero_approach_speed(0.0011111111f, 0.0011111111f);
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            } else {
                hero_approach_speed(0.00055555557f, 0.00055555557f);
                ptr10 = ((void*)g_hero_state) + 0xF0;
                cam_set_view_space_vector_length((s32) ptr10, (s32) ptr10, ((Hero *)g_hero_state)->f[0x1B4/4]);
            }
        } else {
            value67 = 0;
            if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
                value67 = 1;
            }
            value17 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (value17 != 0) {
                FastVecSub((s32)((TI128*)vec_a), value17 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                scalar21 = cam_get_view_space_vector_length((s32)((TI128*)vec_a));
                if (((scalar21 > 2.0f) && (scalar21 < 5.0f)) || (value67 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
                }
                hero_approach_speed(0.0069444445f, 0.0069444445f);
                vec_scale_to_length((s32) ((TI128*)vec_b), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
                cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_b));
            } else {
                if ((value67 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
                }
                hero_approach_speed(0.004166667f, 0.004166667f);
                cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4]);
            }
        }
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
            hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)g_hero_state)->f[0xC38/4] < 25.0f) {
            hero_l00_select_aim_target(8.0f, 1.0471977f, 1.0471977f);
        }
        scalar66 = ((Hero *)g_hero_state)->f[0x31C/4];
        scalar158 = 0.12833333f;
        if (scalar66 > 2.25f) {
            scalar158 = 0.064166665f;
        } else if (scalar66 > 1.8f) {
            scalar158 = 0.08983333f;
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 23.5f) && (((Hero *)g_hero_state)->f[0x118/4] < 0.0f) && (((Hero *)g_hero_state)->h[0x34E/2] != 0)) {
            qcopy(vec_a, &((Hero *)g_hero_state)->q[0x80/16]);
            hero_apply_mode_transform_reversed((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), -0.5f);
            vec_scale_to_length((s32) &vec_e[0], (s32)g_hero_state, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vec_b), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &vec_e[0]);
            vec_b[3] = 5627.925f;
            (*(u8*)((u8*)vec_c+9)) = 1;
            (*(u16*)((u8*)vec_c+10)) = 0x47;
            (*(u8*)((u8*)vec_c+8)) = 0;
            coll_process_hit(0.4f, (s32)((TI128*)vec_a), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vec_b));
        }
        if (math_is_below_plane_within_depth(25.7f) != 0) {
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L20_001B9E80)->f[0x180/4] = 0.1f;
                ((Hero *)D_L20_001B9E80)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)D_L20_001B9E80)->i[0x16C/4] = 0;
            }
        }
        value39 = ((Hero *)g_hero_state)->i[0x1B8/4];
        limit3 = 0xE;
        if (value39 < 9) {
            ptr22 = ((void*)g_hero_state) + 0xF0;
            scalar11 = cam_get_view_space_height((s32) ptr22);
            ApproachValue((s32) &scalar11, scalar158, 0.041666668f);
            cam_set_view_space_height((s32) ptr22, (s32) ptr22, scalar11);
        } else if (value39 > limit3) {
            ptr31 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr31, (s32) ptr31, 0.036111113f);
            if (cam_get_view_space_height((s32) ptr31) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            scalar153 = -0.6166667f;
            if (D_L20_001A8FF0 != 0) {
                scalar153 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) ptr31) < scalar153) {
                cam_set_view_space_height((s32) ptr31, (s32) ptr31, scalar153);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        value60 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (value60 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                value68 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    ptr23 = ((void*)g_hero_state) + 0xBC0;
                    scalar154 = hero_get_direction_angle_delta((s32) ptr23, 0);
                    scalar112 = hero_get_direction_angle_delta((s32) ptr23, 1);
                } else {
                    scalar154 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    scalar112 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (scalar112 < 4.3633237f) {
                    value68 = 1;
                }
                if (scalar154 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (scalar112 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (value68 != 0) {
                    hero_steer_heading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    hero_steer_heading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    value61 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xC)) {
                        value61 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        value61 = 0;
                    }
                    if (value61 != 0) {
                        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x15) {
                            hero_l00_select_aim_target(14.0f, 0.52359885f, 0.78539824f);
                        } else {
                            UpdateHeroAimTarget(64.0f, 0.17453295f, 0.3490659f);
                        }
                    }
                }
        }
        if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) == 0x1A) && (math_is_below_plane_within_depth(33.0f) != 0)) {
            if ((((Hero *)g_hero_state)->b[0x1492] != 0) && (((Hero *)g_hero_state)->f[0x170/4] < 0.033333335f)) {
                {
                    ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.021666666f));
                    ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.021666666f));
                    qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x15) {
                hero_setup_attached_object_transform();
            }
        }
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            if (math_is_below_plane_within_depth(84.0f) != 0) {
                scalar159 = 0.041666668f;
                scalar86 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&D_00138320) & 8) {
                    scalar159 = 0.050000004f;
                }
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(scalar86) * scalar159));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(scalar86) * scalar159));
                qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
            }
            hero_steer_reference_point();
        } else {
            hero_approach_speed(0.010277778f, 0.007777778f);
            hero_compute_push_direction(99999.0f);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
            } else {
                hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
                break;
            }
        }
        break;
    case 0x13:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            hero_steer_reference_point();
            break;
        }
        value18 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ptr38 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)D_L20_00268D90;
        if ((value18 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            ptr32 = ((void*)g_hero_state) + 0x80;
            scalar122 = vec_distance_xy(value18 + 0x10, (s32) ptr32);
            if ((*(s32*)&D_L20_001A8FF0) != 0) {
                scalar122 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) ptr32);
            }
            scalar122 = scalar122 - 0.5f;
            if (scalar122 < 0.0f) {
                scalar122 = 0.0f;
            }
            value40 = M2C_FIELD(ptr38, s32* , 4);
            if (value40 == 0) {
                scalar113 = 0.75f;
                scalar160 = 0.8f;
                scalar165 = 4.0f;
            } else if (value40 == 1) {
                scalar113 = 0.6f;
                scalar160 = 1.7f;
                scalar165 = 4.0f;
            } else {
                scalar113 = 1.3f;
                scalar160 = 1.7f;
                scalar165 = 1.9f;
            }
            scalar87 = scalar122 - scalar113;
            if (math_fabs(scalar87) < (scalar160 + 3.0f)) {
                scalar124 = scalar87 * 1.1111112f;
                if (scalar165 < scalar124) {
                    scalar124 = scalar165;
                }
                if (scalar124 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = scalar124;
                }
            }
        }
        value41 = M2C_FIELD(ptr38, s32* , 4);
        switch (value41) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            scalar67 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (scalar67 < 9.0f)) {
                if (scalar67 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (scalar67 > 7.0f) {
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
            scalar114 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            scalar114 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        scalar68 = math_fabs(scalar114);
        if ((M2C_FIELD(ptr38, s32* , 4) == 1) && (scalar114 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (scalar68 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        value79 = 1;
        if ((M2C_FIELD(ptr38, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            value79 = 0;
        }
        if (value79 != 0) {
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
            ptr11 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr11, (s32) ptr11, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L20_001A8FF0) != 0) {
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
        limit = 0xA;
        limit2 = 0x12;
        value42 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (value42 > limit) {
            if (value42 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            ptr24 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ptr24);
            level_append_record_to_table((s32) ptr24, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) ptr24, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) ptr24, 0xC, 6, 0.0f);
        }
        selection_a = (((Hero *)g_hero_state)->i[0x1B8/4] > limit2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), selection_a);
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            value43 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((value43 > limit) && (value43 < 0x11) && (((Hero *)g_hero_state)->f[0x178/4] < 0.14166668f)) {
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.020000001f));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.020000001f));
                qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
            }
            hero_steer_reference_point();
        } else {
            if (((Hero *)g_hero_state)->i[0x1B8/4] > limit) {
                hero_approach_speed(0.05277778f, 0.025f);
            }
            if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x1F) {
            value44 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((value44 > limit) && (value44 < 0x16)) {
                ptr39 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (ptr39 != 0) {
                    ptr33 = ((void*)g_hero_state) + 0x80;
                    vec_d[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_d[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vec_d[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec_a), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vec_d));
                    (*(u8*)((u8*)vec_b+9)) = 3;
                    vec_a[3] = 5627.925f;
                    (*(u8*)((u8*)vec_b+8)) = 0;
                    scalar93 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vec_b+10)) = M2C_FIELD(ptr39, u16* , 0xAA);
                    vec_e[0] = math_fast_sin_or_cos_a(scalar93) * 0.8f;
                    scalar22 = math_fast_sin_or_cos_b(scalar93) * 0.8f;
                    vec_e[2] = 0.55f;
                    vec_e[1] = scalar22;
                    FastVecAdd((s32) &vec_e[0], (s32) &vec_e[0], (s32) ptr33);
                    part_emit_effects_at_nearby_mobys((s32) ptr39, coll_process_hit(0.8f, (s32) &vec_e[0], 0, (s32) ptr39, (s32)((TI128*)vec_a)));
                    scalar93 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vec_e[0] = math_fast_sin_or_cos_a(scalar93) * 0.8f;
                    scalar24 = math_fast_sin_or_cos_b(scalar93) * 0.8f;
                    vec_e[2] = 0.55f;
                    vec_e[1] = scalar24;
                    FastVecAdd((s32) &vec_e[0], (s32) &vec_e[0], (s32) ptr33);
                    part_emit_effects_at_nearby_mobys((s32) ptr39, coll_process_hit(0.8f, (s32) &vec_e[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec_a)));
                    scalar93 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vec_e[0] = math_fast_sin_or_cos_a(scalar93) * 0.8f;
                    scalar26 = math_fast_sin_or_cos_b(scalar93) * 0.8f;
                    vec_e[2] = 0.55f;
                    vec_e[1] = scalar26;
                    FastVecAdd((s32) &vec_e[0], (s32) &vec_e[0], (s32) ptr33);
                    part_emit_effects_at_nearby_mobys((s32) ptr39, coll_process_hit(0.8f, (s32) &vec_e[0], 0, (s32) ptr39, (s32)((TI128*)vec_a)));
                }
            }
        }
        if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        hero_slide_along_wall(1);
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
        value55 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            value55 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (value55 != 0)) {
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
            scalar88 = ReadPadFloatHistory(1);
            if ((FastDiffRots(scalar88, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            ptr_a60 = ((void*)g_hero_state) + 0xA60;
            hero_build_move_impulse(0.7f, 0.0f);
            (*(TI128*)vec_a) = ((Hero *)g_hero_state)->q[0xA60/16];
            scalar69 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vec_a));
            ((Hero *)g_hero_state)->f[0x1B0/4] = scalar69;
            if (scalar69 < 0.011666667f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.011666667f;
            }
            vec_clear_128((s32) ptr_a60);
        }
        scalar155 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                scalar97 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (scalar97 > 0.78539824f)) {
                    scalar155 = 0.0f;
                }
                hero_set_turn_rates();
            }
        }
        hero_apply_mode_pose_offsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            scalar169 = 0.09916667f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.029178405f);
            if (scalar169 < 0.0f) {
                scalar169 = 0.0f;
            }
            if (scalar169 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = scalar169;
            }
        }
        const_b = scalar155 * 0.005f;
        scalar156 = 0.0055555557f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            scalar141 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (scalar141 > 1.0f) {
                scalar141 = 1.0f;
            }
            if (scalar141 < 0.2f) {
                scalar141 = 0.2f;
            }
            scalar156 = 0.004722222f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * scalar141);
        }
        scalar98 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (scalar98 > 0.6108653f)) {
            scalar142 = 1.0f - (scalar98 * 0.4f);
            if (scalar142 < 0.0f) {
                scalar142 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * scalar142);
        }
        hero_approach_speed(const_b, scalar156);
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
        hero_slide_along_wall(1);
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
        pad_clamp_stick_to_unit_range((s32)((TI128*)vec_a), (s32) (((void*)g_hero_state) + 0x9F0), 0.17f);
        scalar161 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * vec_a[0];
        if ((*(s32*)&D_L20_001A8FF0) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3C) {
                scalar161 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, scalar161);
        }
        hero_approach_speed(0.027777778f, 0.004166667f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&D_L20_001A8FF0) != 0) {
            qcopy(vec_b, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vec_b), (s32) ((TI128*)vec_b), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_b), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vec_b), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec_b), (s32) ((TI128*)vec_b), (s32)(g_hero_state + 0xE0));
        value29 = coll_process_hit(0.57f, (s32) ((TI128*)vec_b), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (value29 != 0) {
            FastVecScale((s32) ((TI128*)vec_c), (s32)(g_hero_state + 0x110), 7.0f);
            for (value64 = 0; value64 < value29; value64++) {
                if (moby_is_in_special_class_range(((s32 *)D_L20_001C4480)[value64]) != 0) {
                    part_queue_impact_effect(((s32 *)D_L20_001C4480)[value64], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_c), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.017f, 0.3f);
        cam_set_limits_third(0.025f, 0.3f);
        cam_set_limits_fourth(0.03f, 0.27f);
        scalar170 = scalar161 * 27.0f;
        if (scalar170 > 1.7f) {
            scalar170 = 1.7f;
        } else if (scalar170 < -1.7f) {
            scalar170 = -1.7f;
        }
        scalar27 = scalar170 * 0.5f;
        ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) -scalar170;
        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar27;
        ((Hero *)D_L20_00267210)->f[0x1C8/4] = scalar27;
        break;
    case 0x2E:                                      /* switch 1 */
        hero_steer_reference_point();
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        byte_val3 = M2C_FIELD(hero_object, u8* , 0x43);
        if (byte_val3 == 0x37) {
            scalar115 = 1.4f;
            scalar157 = ((Hero *)g_hero_state)->f[0x1A8/4];
            if ((scalar157 > 1.4f) || (scalar115 = -1.4f, (scalar157 < -1.4f))) {
                scalar157 = scalar115;
            }
            ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) (scalar157 * -0.14f);
            ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (scalar157 * 0.3f);
            ((Hero *)D_L20_00267210)->f[0x1C0/4] = (f32) (scalar157 * -0.22f);
            ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (scalar157 * 0.4f);
            ((Hero *)D_L20_00267210)->f[0x274/4] = (f32) (math_fabs(scalar157) * -0.09f);
            ((Hero *)D_L20_00267210)->f[0x270/4] = (f32) (math_fabs(scalar157) * 0.08f);
        } else if (byte_val3 == 0x66) {
            scalar94 = FastAddRotations(fast_subtract_rotations(mat_fast_helper_a(((Hero *)g_hero_state)->f[0x110/4], ((Hero *)g_hero_state)->f[0x114/4]), ((Hero *)g_hero_state)->f[0x98/4]), 3.1415927f);
            scalar162 = ((Hero *)g_hero_state)->f[0x174/4] * 6.9813175f;
            if (scalar162 > 0.43633235f) {
                scalar162 = 0.43633235f;
            }
            scalar71 = math_fast_sin_or_cos_a(scalar94) * scalar162;
            scalar28 = -math_fast_sin_or_cos_b(scalar94);
            ((Hero *)D_L20_00267210)->f[0x114/4] = scalar71;
            ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (scalar28 * scalar162);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            scalar125 = 0.0069444445f;
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x110), scalar125);
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.041666668f);
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        value45 = (*(s32*)&g_current_map_index);
        if (value45 == 0) {
            snd_update_slot_object(2, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x13);
            value74 = g_current_map_index;
        } else {
            if (value45 != 1) {
                snd_update_slot_object(2, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 6);
            }
            value74 = (*(s32*)&g_current_map_index);
        }
        if ((u32) value74 < 2U) {
            EmitHeroRandomizedMotionEffects(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects(4, 2, 0);
            vec_a[0] = ((Hero *)g_hero_state)->f[0x80/4] + math_random_float_range(-0.25f, 0.25f);
            vec_a[1] = ((Hero *)g_hero_state)->f[0x84/4] + math_random_float_range(-0.25f, 0.25f);
            vec_a[2] = ((Hero *)g_hero_state)->f[0x88/4] + math_random_float_range(-0.1f, 0.4f);
            FastVecScale((s32) ((TI128*)vec_b), (s32) (((void*)g_hero_state) + 0x110), 0.9f);
            vec_b[0] += math_random_float_range(-0.011666667f, 0.011666667f);
            vec_b[1] += math_random_float_range(-0.011666667f, 0.011666667f);
            vec_b[2] = M2C_BITWISE(f32, vec_b[2]) + math_random_float_range(0.016666668f, 0.033333335f);
            part_spawn_two_point_effect((s32)((TI128*)vec_a), (s32) ((TI128*)vec_b), math_random_float_range(37800.0f, 75600.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xB40/4];
        scalar72 = ((Hero *)g_hero_state)->f[0x98/4];
        hero_steer_heading(0, 0.033f, 0.3f, 0.069813184f);
        scalar163 = FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], scalar72);
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        hero_shrink_vector_by_amount(0.0019444445f);
        scalar29 = ((Hero *)g_hero_state)->f[0x118/4] - 0.013888889f;
        ((Hero *)g_hero_state)->f[0xF8/4] = scalar29;
        if (scalar29 > -0.011111111f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.011111111f;
        }
        if (scalar163 > 0.023271061f) {
            scalar163 = 0.023271061f;
        }
        scalar73 = scalar163 * 9.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), scalar73 * 0.5f, (s32) (((void*)g_hero_state) + 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), -((Hero *)g_hero_state)->f[0xB44/4], (s32) (((void*)g_hero_state) + 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (scalar73 * 2.1f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (scalar73 * 3.5f);
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        value84 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (((u32) (value84 - 0x28) >= 2U) && (value84 != 0x3E)) {
            snd_update_slot_object(0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        } else {
            value22 = ((Hero *)g_hero_state)->i[0x242C/4];
            if (value22 != -1) {
                ptr12 = (value22 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(ptr12, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ptr12, u8* , 0x74) != 0) {
                        snd_stop_voice(value22);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x242C/4] = -1;
        }
        value85 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((value85 == 0x27) || (value85 == 0x2A)) {
            qcopy(vec_a, &((Hero *)g_hero_state)->q[0x80/16]);
            scalar74 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.0f, 0.52359885f));
            scalar91 = math_random_float_range(0.06666667f, 0.116666675f);
            vec_b[0] = math_fast_sin_or_cos_a(scalar74) * scalar91;
            scalar30 = math_fast_sin_or_cos_b(scalar74) * scalar91;
            vec_b[2] = 0.0f;
            vec_b[1] = scalar30;
            vec_b[2] = math_random_float_range(0.050000004f, 0.083333336f);
            vec_b[3] = -0.008333334f;
            part_spawn_white_flash((s32)((TI128*)vec_a), (s32) ((TI128*)vec_b), 0, -1.0f);
        }
        ptr20 = ((Hero *)g_hero_state)->ptr[0x1248/4];
        flag_a = 0;
        value27 = (((LevelInfo *)D_L20_0026D970)[g_item_slot_to_record[(s32)ptr20]].x1C != 0);
        if ((s32)ptr20 == 0xD) {
            value27 = 0;
        }
        if (value27 != 0) {
            flag_a = ((Hero *)g_hero_state)->b[0x22BA] != 0;
        }
        ptr34 = ((void*)g_hero_state) + 0x80;
        find_nearest_path_point(((Hero *)g_hero_state)->i[0x630/4], (s32) ptr34, (s32) (((void*)g_hero_state) + 0x5D0), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)g_hero_state)->i[0x664/4], (s32) ptr34, (s32) (((void*)g_hero_state) + 0x610), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        value63 = 0;
        if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0699999f) {
            value86 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((value86 != 0x28) && (value86 != 0x3E) && (((Hero *)g_hero_state)->i[0x660/4] == 0)) {
                value63 = ((Hero *)g_hero_state)->i[0x1BC/4] >= 0x1F;
            }
        }
        if (value63 != 0) {
            ((Hero *)g_hero_state)->i[0x6C8/4] = (s32) (((Hero *)g_hero_state)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)g_hero_state)->i[0x6C8/4] = 0;
        }
        value30 = ((Hero *)g_hero_state)->i[0x640/4];
        if (((value30 != 0) && ((((Hero *)g_hero_state)->i[0x640/4] = value30 + 1) != 0)) || (value63 != 0)) {
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x120/16]);
            ptr51 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(ptr51, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion();
            } else {
                M2C_FIELD(ptr51, f32* , 0xF8) = (f32) (M2C_FIELD(ptr51, f32* , 0xF8) - 0.0061111115f);
            }
        } else {
            scalar54 = (f32) ((Hero *)g_hero_state)->i[0x648/4];
            scalar146 = ((Hero *)g_hero_state)->f[0x644/4] * scalar54;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                scalar146 = ((Hero *)g_hero_state)->f[0x69C/4] * scalar54;
            }
            Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32)((TI128*)vec_a), (s32) (((void*)g_hero_state) + 0x634), (s32) (((void*)g_hero_state) + 0x638), ((Hero *)g_hero_state)->i[0x654/4], scalar146);
            if (((Hero *)g_hero_state)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x664/4], (s32) ((TI128*)vec_b), (s32) (((void*)g_hero_state) + 0x668), (s32) (((void*)g_hero_state) + 0x66C), ((Hero *)g_hero_state)->i[0x670/4], scalar146);
            }
            if (((Hero *)g_hero_state)->i[0x1BC/4] >= 0x5B) {
                scalar75 = ((Hero *)g_hero_state)->f[0x170/4] * 30.0f;
                qcopy(vec_c, &((Hero *)g_hero_state)->q[0x80/16]);
                value5 = ((Hero *)g_hero_state)->i[0x634/4];
                scalar12 = ((Hero *)g_hero_state)->f[0x638/4];
                value25 = Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vec_c), (s32) &value5, (s32) &scalar12, ((Hero *)g_hero_state)->i[0x654/4], scalar75);
                qcopy(vec_d, &((Hero *)g_hero_state)->q[0x80/16]);
                value5 = ((Hero *)g_hero_state)->i[0x634/4];
                scalar12 = ((Hero *)g_hero_state)->f[0x638/4];
                if ((((value25 | Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vec_d), (s32) &value5, (s32) &scalar12, ((Hero *)g_hero_state)->i[0x654/4], scalar75 + 0.1f)) == 0) || (((Hero *)g_hero_state)->i[0x654/4] != 0)) && (((Hero *)g_hero_state)->u[0x2294/4] == 0x27)) {
                    scalar147 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x64C/4], mat_fast_helper_a(vec_d[0] - vec_c[0], vec_d[1] - vec_c[1])) * 0.47f;
                    if (scalar147 > 0.78539824f) {
                        scalar147 = 0.78539824f;
                    }
                    if (scalar147 < -0.78539824f) {
                        scalar147 = -0.78539824f;
                    }
                    cam_set_limits_first(0.03f, 0.2f);
                    if (((Hero *)g_hero_state)->i[0x65C/4] != 0) {
                        (*(f32*)&D_L20_00267274) = -scalar147;
                    } else {
                        (*(f32*)&D_L20_00267274) = scalar147;
                    }
                }
            }
            value87 = ((Hero *)g_hero_state)->u[0x2294/4];
            if ((value87 != 0x28) && (value87 != 0x3E) && (value87 != 0x29)) {
                (*(f32*)&D_L20_00267270) = mat_fast_helper_a(vec_length_xy((s32) (((void*)g_hero_state) + 0x110)), ((Hero *)g_hero_state)->f[0x118/4]);
            }
            if (value27 != 0) {
                const_a = 0.3f;
                cam_set_limits_fourth(0.017f, const_a);
                cam_set_limits_second(0.027f, const_a);
                cam_set_limits_third(0.027f, const_a);
                value19 = ((Hero *)g_hero_state)->i[0x6A8/4];
                if (value19 != 0) {
                    FastVecSub((s32) ((TI128*)vec_c), value19 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), (s32) (((void*)g_hero_state) + 0x40));
                    scalar47 = mat_fast_helper_a(vec_c[0], vec_c[1]);
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        scalar47 = fast_subtract_rotations(scalar47, 1.5707965f);
                        scalar143 = 0.2f;
                    } else {
                        scalar47 = fast_subtract_rotations(scalar47, -1.5707965f);
                        scalar143 = 0.5f;
                    }
                    ((Hero *)D_L20_00267210)->f[0x1C8/4] = (f32) (scalar47 * scalar143);
                    ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (scalar47 * const_a);
                } else {
                    byte_val1 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43);
                    if (byte_val1 == 0x31) {
                        scalar164 = 0.58823526f;
                        scalar117 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        scalar148 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar117;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(scalar148, ((Hero *)g_hero_state)->f[0x6A0/4] * scalar164);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(scalar148, ((Hero *)g_hero_state)->f[0x6A0/4] * scalar164);
                    } else if (byte_val1 == 0x48) {
                        scalar164 = 0.5f;
                        scalar117 = FastAddRotations(0.13962635f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        scalar148 = -0.06981318f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar117;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(scalar148, ((Hero *)g_hero_state)->f[0x6A0/4] * scalar164);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(scalar148, ((Hero *)g_hero_state)->f[0x6A0/4] * scalar164);
                    } else if (byte_val1 == 0x47) {
                        scalar164 = 0.58823526f;
                        scalar117 = FastAddRotations(-0.8203048f, ((Hero *)g_hero_state)->f[0x6A0/4]);
                        scalar148 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar117;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(scalar148, ((Hero *)g_hero_state)->f[0x6A0/4] * scalar164);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(scalar148, ((Hero *)g_hero_state)->f[0x6A0/4] * scalar164);
                    }
                }
            }
            value32 = path_advance_index(((Hero *)g_hero_state)->i[0x630/4], ((Hero *)g_hero_state)->i[0x634/4], ((Hero *)g_hero_state)->i[0x648/4], ((Hero *)g_hero_state)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)vec_c), (s32) &((TI128 *)((Hero *)g_hero_state)->ptr[0x630/4])[value32 + 1], (s32)((TI128*)vec_a));
            if (FastVecLength((s32) ((TI128*)vec_c)) < 0.001f) {
                if (((Hero *)g_hero_state)->i[0x634/4] == value32) {
                    ((Hero *)g_hero_state)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)g_hero_state)->f[0x64C/4] = mat_fast_helper_a(vec_c[0], vec_c[1]);
                ((Hero *)g_hero_state)->f[0x650/4] = mat_fast_helper_a(vec_length_xy((s32) ((TI128*)vec_c)), M2C_BITWISE(f32, vec_c[2]));
block_807:
                ((Hero *)g_hero_state)->f[0x1A0/4] = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], ((Hero *)g_hero_state)->f[0x658/4]);
                hero_steer_heading(0, 0.015f, 0.15f, 0.10471977f);
                value88 = ((Hero *)g_hero_state)->u[0x2294/4];
                if ((((u32) (value88 - 0x28) < 2U) && (((Hero *)g_hero_state)->b[0x49C] == 0)) || (value88 == 0x3E)) {
                    if (((Hero *)g_hero_state)->i[0x694/4] != 0) {
                        scalar34 = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x620/4] - ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x624/4] - ((Hero *)g_hero_state)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], scalar34) < 1.5707965f) {
                            ((Hero *)g_hero_state)->f[0x1A0/4] = scalar34;
                            hero_steer_heading(0, 0.04f, 0.2f, 0.10471977f);
                        }
                    }
                    if ((((Hero *)g_hero_state)->i[0x660/4] != 0) && (((Hero *)g_hero_state)->i[0x678/4] < 0x31)) {
                        FastVecSub((s32) ((TI128*)vec_c), (s32)((TI128*)vec_a), (s32) ((TI128*)vec_b));
                        value33 = ((Hero *)g_hero_state)->i[0x678/4] + 1;
                        ((Hero *)g_hero_state)->i[0x678/4] = value33;
                        FastVecScale((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), (f32) value33 * 0.020833334f);
                        scalar76 = (f32) (((Hero *)g_hero_state)->i[0x678/4] - 1) * 0.020833334f;
                        FastVecSub((s32) ((TI128*)vec_d), (s32)((TI128*)vec_a), (s32) ((TI128*)vec_b));
                        FastVecScale((s32) ((TI128*)vec_d), (s32) ((TI128*)vec_d), scalar76);
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + (M2C_BITWISE(f32, vec_c[2]) - vec_d[2]));
                        FastVecAdd((s32) ((TI128*)vec_d), (s32) ((TI128*)vec_b), (s32) ((TI128*)vec_c));
                        FastVecSub((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_d), (s32) (((void*)g_hero_state) + 0x80));
                        ((Hero *)g_hero_state)->f[0xF0/4] = vec_c[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = vec_c[1];
                        FastVecSub((s32) ((TI128*)vec_c), (s32)((TI128*)vec_a), (s32) (((void*)g_hero_state) + 0x5D0));
                        scalar100 = ((Hero *)g_hero_state)->f[0x5D8/4];
                        scalar55 = ((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, vec_c[2]);
                        ((Hero *)g_hero_state)->f[0x88/4] = scalar55;
                        if (scalar55 < scalar100) {
                            if (((Hero *)g_hero_state)->i[0x678/4] < 0x31) {
                                if (scalar55 < scalar100) {
                                    ((Hero *)g_hero_state)->f[0x88/4] = scalar100;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)vec_c), (s32)((TI128*)vec_a), (s32)(g_hero_state + 0x5D0));
                        ((Hero *)g_hero_state)->f[0xF0/4] = vec_c[0];
                        ((Hero *)g_hero_state)->f[0xF4/4] = vec_c[1];
                        ((Hero *)g_hero_state)->f[0x88/4] = (f32) (((Hero *)g_hero_state)->f[0x88/4] + M2C_BITWISE(f32, vec_c[2]));
                        FastVecSub((s32) ((TI128*)vec_d), (s32)(g_hero_state + 0x5D0), (s32)(g_hero_state + 0x80));
                        vec_d[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)vec_d)) > 0.016666668f) {
                            vec_scale_to_length((s32) ((TI128*)vec_d), (s32) ((TI128*)vec_d), 0.016666668f);
                        }
                        ((Hero *)g_hero_state)->f[0x80/4] = (f32) (((Hero *)g_hero_state)->f[0x80/4] + vec_d[0]);
                        ((Hero *)g_hero_state)->f[0x84/4] = (f32) (((Hero *)g_hero_state)->f[0x84/4] + vec_d[1]);
                    }
                    if (((Hero *)g_hero_state)->u[0x2294/4] == 0x3E) {
                        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.006388889f);
                    } else {
                        ApplyHeroGravityAndJumpMotion();
                    }
                } else {
                    ((Hero *)g_hero_state)->i[0x660/4] = 0;
                    scalar118 = 0.0f;
                    if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) && (flag_a != 0)) {
                        hero_resolve_stick_direction(1.0f, 0);
                        scalar118 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1A0/4], ((Hero *)g_hero_state)->f[0x64C/4]);
                        if (scalar118 > 0.78539824f) {
                            scalar118 = 0.78539824f;
                        } else if (scalar118 < -0.78539824f) {
                            scalar118 = -0.78539824f;
                        }
                    }
                    math_approach_with_velocity((s32)(g_hero_state + 0x6A0), scalar118, (s32)(g_hero_state + 0x6A4), 0.015f, 0.3f, 0.0f, 0);
                    ApproachValue((s32)(g_hero_state + 0x680), 0.20000002f, 0.004166667f);
                    value6 = ((Hero *)g_hero_state)->i[0x634/4];
                    scalar13 = ((Hero *)g_hero_state)->f[0x638/4];
                    qcopy(vec_c, &((Hero *)g_hero_state)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)g_hero_state)->i[0x630/4], (s32) ((TI128*)vec_c), (s32) &value6, (s32) &scalar13, ((Hero *)g_hero_state)->i[0x654/4], 0.3f);
                    scalar31 = mat_fast_helper_a(vec_distance_xy((s32)(g_hero_state + 0x5D0), (s32) ((TI128*)vec_c)), M2C_BITWISE(f32, vec_c[2]) - ((Hero *)g_hero_state)->f[0x5D8/4]);
                    if (scalar31 > 0.0f) {
                        scalar126 = scalar31 * -0.07957746f;
                        if (scalar31 > 0.26179942f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 0;
                        } else if ((scalar31 < 0.13962635f) && (((Hero *)g_hero_state)->i[0x67C/4] == 0)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    } else {
                        scalar126 = -scalar31 * 0.38197184f;
                        if (scalar31 < -0.19198623f) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = 1;
                        } else if ((scalar31 > -0.122173056f) && (((Hero *)g_hero_state)->i[0x67C/4] == 1)) {
                            ((Hero *)g_hero_state)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < scalar126) {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), scalar126, 0.0022222223f);
                    } else {
                        ApproachValue((s32) (((void*)g_hero_state) + 0x674), scalar126, 0.00055555557f);
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] > 0.20000002f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = 0.20000002f;
                    }
                    if (((Hero *)g_hero_state)->f[0x674/4] < -0.041666668f) {
                        ((Hero *)g_hero_state)->f[0x674/4] = -0.041666668f;
                    }
                    scalar32 = ((Hero *)g_hero_state)->f[0x680/4] + ((Hero *)g_hero_state)->f[0x674/4];
                    ((Hero *)g_hero_state)->f[0x644/4] = scalar32;
                    if (scalar32 < 0.0f) {
                        ((Hero *)g_hero_state)->f[0x644/4] = 0.0f;
                    }
                    ptr25 = ((void*)g_hero_state) + 0x5D0;
                    FastVecSub((s32) (((void*)g_hero_state) + 0xF0), (s32)((TI128*)vec_a), (s32) ptr25);
                    ptr40 = ((void*)g_hero_state) + 0x80;
                    FastVecSub((s32) ((TI128*)vec_c), (s32) ptr25, (s32) ptr40);
                    scalar14 = -FastVecLength((s32) ((TI128*)vec_c));
                    math_spring_float_to_goal((s32) &scalar14, (s32) (((void*)g_hero_state) + 0x6AC), 0.0f, 0.03f, 0.3f, 0.116666675f);
                    scalar33 = FastVecLength((s32) ((TI128*)vec_c));
                    if (scalar33 < ((Hero *)g_hero_state)->f[0x6AC/4]) {
                        ((Hero *)g_hero_state)->f[0x6AC/4] = scalar33;
                    }
                    scalar48 = ((Hero *)g_hero_state)->f[0x6AC/4];
                    if (scalar48 < scalar33) {
                        vec_scale_to_length((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), scalar48);
                    }
                    FastVecAdd((s32) ptr40, (s32) ptr40, (s32) ((TI128*)vec_c));
                    scalar103 = ((Hero *)g_hero_state)->f[0x88/4];
                    scalar99 = ((Hero *)g_hero_state)->f[0x5D8/4];
                    if (scalar103 < scalar99) {
                        if (((Hero *)g_hero_state)->f[0x31C/4] < 1.0f) {
                            if (scalar103 < scalar99) {
                                ((Hero *)g_hero_state)->f[0x88/4] = scalar99;
                            }
                        }
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x14) {
                        scalar35 = FastAddRotations(((Hero *)g_hero_state)->f[0x64C/4], math_random_signed_float_range(0.3490659f, 0.6108653f));
                        vec_f[0] = math_fast_sin_or_cos_a(scalar35);
                        vec_f[1] = math_fast_sin_or_cos_b(scalar35);
                        vec_f[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)vec_c), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &vec_f[0]);
                        qcopy(vec_g, &((Hero *)g_hero_state)->q[0x80/16]);
                        vec_g[2] += 0.6f;
                        coll_process_hit(1.0f, (s32) ((TI128*)vec_g), 0x10, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ((TI128*)vec_c));
                    }
                }
            }
        }
        break;
    case 0x71:                                      /* switch 1 */
        hero_get_offset_vector(vec_a);
        hero_ptr_a = (Hero *)g_hero_state;
        if (M2C_FIELD(hero_ptr_a->ptr[0x2290/4], u8* , 0x43) == 0x5F) {
            snd_update_slot_object(0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
            if (ref_L00_002BA7D8_00 & 1) {
                qcopy(vec_b, vec_a);
                FastVecScale((s32) ((TI128*)vec_c), (s32) (((void*)g_hero_state) + 0x110), 0.4f);
                scalar1 = FastAddRotations(((Hero *)g_hero_state)->f[0x700/4], math_random_signed_float_range(0.0f, 0.52359885f));
                scalar2 = math_random_float_range(0.0f, 0.06666667f);
                vec_c[0] += math_fast_sin_or_cos_a(scalar1) * scalar2;
                vec_c[1] += math_fast_sin_or_cos_b(scalar1) * scalar2;
                vec_c[2] = math_random_float_range(0.050000004f, 0.083333336f);
                vec_c[3] = -0.009722223f;
                part_spawn_white_flash((s32) ((TI128*)vec_b), (s32) ((TI128*)vec_c), 0, -1.0f);
            }
        }
        find_nearest_path_point(((Hero *)g_hero_state)->i[0x6E0/4], (s32) ((TI128*)vec_a), (s32) (((void*)g_hero_state) + 0x6D0), (s32) (((void*)g_hero_state) + 0x6E4), (s32) (((void*)g_hero_state) + 0x6E8), ((Hero *)g_hero_state)->i[0x6FC/4], 999.0f, 8.0f, 2.5f);
        count_a = ((Hero *)g_hero_state)->i[0x6F0/4];
        if (count_a != 0) {
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x120/16]);
            ((Hero *)g_hero_state)->i[0x6F0/4] = count_a + 1;
            ((Hero *)g_hero_state)->f[0xF8/4] = ((Hero *)g_hero_state)->f[0xF8/4] - 0.0061111115f;
        } else {
            scalar3 = ((Hero *)g_hero_state)->f[0x6F4/4];
            /* retail evaluates the float (fifth) argument first */
            ((s32 (*)(s32, s32, s32, s32, f32, s32))Spline_AdvanceByDistance)(((Hero *)g_hero_state)->i[0x6E0/4], (s32) ((TI128*)vec_b), (s32) (((void*)g_hero_state) + 0x6E4), (s32) (((void*)g_hero_state) + 0x6E8), scalar3, ((Hero *)g_hero_state)->i[0x6FC/4]);
            index_a = path_advance_index(((Hero *)g_hero_state)->i[0x6E0/4], ((Hero *)g_hero_state)->i[0x6E4/4], 1, ((Hero *)g_hero_state)->i[0x6FC/4]);
            FastVecSub((s32) ((TI128*)vec_c), (s32)((u8 *)((Hero *)g_hero_state)->ptr[0x6E0/4] + (index_a * 16 + 0x10)), (s32) ((TI128*)vec_b));
            if (FastVecLength((s32) ((TI128*)vec_c)) < 0.001f) {
                if (((Hero *)g_hero_state)->i[0x6E4/4] == index_a) {
                    ((Hero *)g_hero_state)->i[0x6F0/4] = 1;
                    break;
                }
            } else {
                ((Hero *)g_hero_state)->f[0x700/4] = mat_fast_helper_a(vec_c[0], vec_c[1]);
                ((Hero *)g_hero_state)->f[0x704/4] = mat_fast_helper_a(vec_length_xy((s32) ((TI128*)vec_c)), vec_c[2]);
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x700/4];
            hero_steer_heading(0, 0.018f, 0.2f, 0.10762865f);
            ApproachValue((s32) (((void*)g_hero_state) + 0x6F4), 0.23333335f, 0.0025f);
            FastVecSub((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vec_b), (s32) (((void*)g_hero_state) + 0x6D0));
            FastVecSub((s32) ((TI128*)vec_c), (s32) (((void*)g_hero_state) + 0x6D0), (s32) ((TI128*)vec_a));
            scalar_sp_n = -FastVecLength((s32) ((TI128*)vec_c));
            math_spring_float_to_goal((s32) &scalar_sp_n, (s32) (((void*)g_hero_state) + 0x708), 0.0f, 0.05f, 0.3f, 0.16666667f);
            scalar3 = FastVecLength((s32) ((TI128*)vec_c));
            if (scalar3 < ((Hero *)g_hero_state)->f[0x708/4]) {
                ((Hero *)g_hero_state)->f[0x708/4] = scalar3;
            }
            if (((Hero *)g_hero_state)->f[0x708/4] < scalar3) {
                vec_scale_to_length((s32) ((TI128*)vec_c), (s32) ((TI128*)vec_c), ((Hero *)g_hero_state)->f[0x708/4]);
            }
            FastVecAdd((s32) (((void*)g_hero_state) + 0x80), (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_c));
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
        FastVecSub((s32) ((TI128*)vec_g), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &vec_e[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)vec_g));
        } else {
            FastVecCross((s32) &vec_e[0], (s32) ((TI128*)vec_g), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &vec_e[0], (s32) &vec_e[0], 0.2f);
        FastVecAdd((s32) &vec_f[0], (s32)(g_hero_state + 0x80), (s32) &vec_e[0]);
        if ((hero_find_ledge_grab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab((s32) &vec_f[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec_a)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec_a), (s32)(g_hero_state + 0x80));
            value76 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            value80 = (s32)D_L20_001ACEE8;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(value76 + value80) * 0.5f);
        }
        break;
    case 0x76:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09166667f;
        ApproachHeroVelocity(0.0069444445f);
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.005f);
        break;
    case 0x6:                                       /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2C) {
            scalar127 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                scalar127 = 0.43633235f;
            }
            qcopy(vec_a, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &vec_a[1], scalar127, (s32) (((void*)g_hero_state) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            math_approach_with_velocity((s32)((TI128*)vec_a), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_update_target_speed();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_airborne_steering();
        }
        ptr59 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) ptr59, (s32) ptr59, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr59) < -0.8333334f) {
            cam_set_view_space_height((s32) ptr59, (s32) ptr59, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        ptr2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ptr2, (s32) ptr2, vec_length_xy((s32) ptr2) * 0.9f);
        hero_apply_mode_transform((s32) ptr2, (s32) ptr2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr2) < -0.8333334f) {
            cam_set_view_space_height((s32) ptr2, (s32) ptr2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        angle_a = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, angle_a), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        value56 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            value56 = 0;
        }
        if (value56 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            ptr13 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) ptr13, (s32) ptr13, 0.025f);
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
        scalar49 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (scalar49 < 0.0f) && (scalar101 = ((Hero *)g_hero_state)->f[0x31C/4], (scalar101 < 1.2f))) {
            scalar105 = (scalar101 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (scalar105 < 0.0f) {
                scalar105 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), scalar49 * scalar105);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (scalar49 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L20_001BA248) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.027f, 0.3f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.087266475f);
        scalar128 = 0.0013888889f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            scalar128 = 0.00055555557f;
        }
        ApproachHeroVelocity(scalar128);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            value23 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (value23 != -1) {
                ptr14 = (value23 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr14, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr14, u8* , 0x74) != 0)) {
                    snd_stop_voice(value23);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            value24 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (value24 != -1) {
                ptr15 = (value24 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr15, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr15, u8* , 0x74) != 0)) {
                    snd_stop_voice(value24);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        scalar166 = 0.050000004f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            scalar166 = 0.083333336f;
        }
        scalar167 = 0.72f;
        scalar56 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            scalar166 = 0.12833333f;
            scalar167 = 0.98640007f;
        }
        if (scalar56 != 0.0f) {
            scalar167 = scalar56;
        }
        ptr26 = ((void*)g_hero_state) + 0xF0;
        scalar15 = cam_get_view_space_height((s32) ptr26);
        hero_resolve_stick_direction(scalar166, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) ptr26, (s32) ptr26);
        math_spring_float_to_goal((s32) &scalar15, (s32) (((void*)g_hero_state) + 0xA98), -scalar166 * scalar167, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) ptr26, (s32) ptr26, -scalar15);
        scalar50 = ((Hero *)g_hero_state)->f[0x88/4];
        if (scalar50 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), scalar50, 0.06666667f);
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
                if (D_L20_001B3730 != 0) {
                    RippleDisturb(D_L20_001B3730, D_L20_001B3738, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            scalar57 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((scalar57 >= 4.0f) && (scalar57 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects(7, 0, 0);
            }
        }
        short_val1 = ((Hero *)g_hero_state)->h[0x4AC/2];
        value20 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (value20 == short_val1) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((value20 < short_val1) && (value89 = ((Hero *)g_hero_state)->u[0x2294/4], (value89 != 0xB)) && (value89 != 0x10) && (value89 != 0xC) && (value89 != 0x11) && (value89 != 0x1B) && (value89 != 0x89) && (value89 != 0x48))) {
            if (((Hero *)g_hero_state)->h[0x528/2] != 0) {
                hero_steer_reference_point();
                if ((((Hero *)g_hero_state)->u[0x2294/4] == 0xA) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x178/4] < 0.116666675f)) {
                    ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.011666667f));
                    ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.011666667f));
                    qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
                }
            } else {
                hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
                scalar77 = ((Hero *)g_hero_state)->f[0x1B4/4];
                if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                    ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (scalar77 * 0.4f);
                }
                if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                    hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
                } else {
                    hero_compute_push_direction(99999.0f);
                }
                ((Hero *)g_hero_state)->f[0x1B4/4] = scalar77;
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
                    value46 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (value46 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) value46 * 0.0044444446f);
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                    value47 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (value47 < 0x22) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) value47 * 0.014722222f);
                    }
                }
                if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                    qcopy(vec_a, &((Hero *)g_hero_state)->q[0x80/16]);
                    cam_offset_point_in_view_space((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), 0.5f);
                    cam_offset_point_by_side_direction((s32) ((TI128*)vec_b), (s32)((TI128*)vec_a), 0.95f);
                    if (CollLine((s32)((TI128*)vec_a), (s32) ((TI128*)vec_b), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)g_hero_state)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            hero_update_airborne_steering();
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
                ptr27 = ((void*)g_hero_state) + 0xF0;
                scalar106 = vec_length_xy((s32) ptr27);
                if (scalar106 > 0.06166667f) {
                    scalar106 = 0.06166667f;
                }
                vec_fast_normalize_helper((s32) ptr27, (s32) ptr27, scalar106);
            }
        }
        scalar58 = ((Hero *)g_hero_state)->f[0x318/4];
        scalar102 = ((Hero *)g_hero_state)->f[0x490/4];
        if (scalar102 < scalar58) {
            scalar36 = scalar102 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = scalar36;
            if (scalar58 < scalar36) {
                ((Hero *)g_hero_state)->f[0x490/4] = scalar58;
            }
        }
        scalar59 = ((Hero *)g_hero_state)->f[0x88/4];
        if (scalar59 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = scalar59;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            scalar60 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (scalar60 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = scalar60;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters();
        }
        value90 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((value90 == 0x10) || (value90 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vec_a), 1, 0.8f, 0.0f, 0.3f);
                    value34 = coll_process_hit(0.9f, (s32)((TI128*)vec_a), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (value34 != 0) {
                        FastVecScale((s32) ((TI128*)vec_b), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (value65 = 0; value65 < value34; value65++) {
                            if (moby_is_in_special_class_range(((s32 *)D_L20_001C4480)[value65]) != 0) {
                                part_queue_impact_effect(((s32 *)D_L20_001C4480)[value65], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec_b), 1.0f);
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
        scalar149 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        scalar107 = 0.0011111111f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB)) {
            scalar107 = 0.0027777778f;
        }
        scalar149 = scalar149 - scalar107;
        if (scalar149 < 0.0f) {
            scalar149 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ptr58 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) ptr58, (s32) ptr58, scalar149);
        hero_apply_mode_transform((s32) ptr58, (s32) ptr58, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec_a), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_a[0], vec_a[1]);
        scalar38 = vec_length_xy((s32)((TI128*)vec_a));
        if (scalar38 > 0.2f) {
            hero_ptr_b = (Hero *)g_hero_state;
            hero_ptr_b->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec_a[0], vec_a[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = scalar38;
            if (scalar38 < D_L20_001A7DAC[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L20_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L20_001A7DAC[1][1] * 0.016666668f;
            }
            if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.015000001f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x18AC/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        }
        speed = 1.0f;
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
        hero_approach_speed(speed * 0.005f, 0.0055555557f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_slide_along_wall(1);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.0069444445f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        break;
    case 0x63:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec_a), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)vec_a), (s32)(g_hero_state + 0x160)) < 0.0f) {
            vec_clear_128((s32)(g_hero_state + 0x160));
        }
        vec_clear_128((s32)(g_hero_state + 0xF0));
        hero_shrink_vector_by_amount(0.0075000003f);
        hero_slide_along_wall(0);
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
        hero_slide_along_wall(0);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)(g_hero_state + 0xF0)), (s32) ((void*)(g_hero_state + 0xF0)), 0.015000001f);
        break;
    case 0x4D:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ptr52 = (s32) &D_L20_00268D90[((Hero *)g_hero_state)->h[0xBFC/2]];
        value10 = M2C_FIELD(ptr52, s32* , 4);
        switch (value10) {
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
            scalar61 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((f32) M2C_FIELD(ptr52, s32* , 0x1C) <= scalar61) {
                if (scalar61 <= (f32) M2C_FIELD(ptr52, s32* , 0x20)) {
                    value26 = ((M2C_FIELD(ptr52, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], value26, (s32) ((TI128*)vec_b));
                    moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], value26 | 1, (s32) ((TI128*)vec_c));
                    FastVecAdd((s32)((TI128*)vec_a), (s32) ((TI128*)vec_b), (s32) ((TI128*)vec_c));
                    FastVecScale((s32)((TI128*)vec_a), (s32)((TI128*)vec_a), 0.5f);
                    coll_sweep_from_object((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec_a), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
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
        ApproachHeroVelocity(0.0069444445f);
        scalar4 = 0.005f;
        ptr3 = ((void*)g_hero_state) + 0x130;
        hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) ptr3, scalar4);
        break;
    case 0x41:                                      /* switch 1 */
        hero_resolve_stick_direction(0.050000004f, 0);
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_airborne_steering();
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
        scalar138 = 0.16580631f;
        scalar130 = 0.033f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            scalar138 = 0.19489513f;
            scalar130 = 0.037f;
        }
        hero_steer_heading(0, scalar130, 0.15f, scalar138);
        hero_approach_speed(0.005f, 0.0055555557f);
        if (((Hero *)g_hero_state)->f[0x174/4] < 0.011666667f) {
            ((Hero *)g_hero_state)->b[0x40C] = 1U;
            if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)g_hero_state)->b[0x40F] = 1U;
            }
        }
        scalar79 = ReadPadFloatHistory(0);
        if ((FastDiffRots(scalar79, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                scalar171 = 0.050000004f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.02122066f);
                if (scalar171 < 0.0f) {
                    scalar171 = 0.0f;
                }
                if (scalar171 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = scalar171;
                }
            }
        }
        if (((Hero *)g_hero_state)->b[0x40C] != 0) {
            hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1A0/4]);
        } else {
            hero_compute_push_direction(99999.0f);
        }
        hero_slide_along_wall(1);
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
            hero_cancel_velocity_into_wall();
        } else {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
        }
        break;
    case 0x42:                                      /* switch 1 */
        scalar51 = vec_length_xy((s32)(g_hero_state + 0xF0));
        if (*(s16 *)(g_hero_state + 0x34E) != 0) {
            scalar51 = scalar51 * 0.99f;
        } else {
            scalar51 = scalar51 * 0.92f;
        }
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), scalar51);
        ptr53 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
        M2C_FIELD(ptr53, s32* , 0xF8) = 0;
        if (M2C_FIELD(ptr53, s16* , 0x34E) != 0) {
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
        FastVecSub((s32) ((TI128*)vec_g), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32) (((void*)g_hero_state) + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &vec_e[0], (s32) (((void*)g_hero_state) + 0x2C0), (s32) ((TI128*)vec_g));
        } else {
            FastVecCross((s32) &vec_e[0], (s32) ((TI128*)vec_g), (s32) (((void*)g_hero_state) + 0x2C0));
        }
        vec_scale_to_length((s32) &vec_e[0], (s32) &vec_e[0], 0.2f);
        FastVecAdd((s32) &vec_f[0], (s32)(g_hero_state + 0x80), (s32) &vec_e[0]);
        if ((hero_find_ledge_grab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab((s32) &vec_f[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)vec_a)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)vec_a), (s32)(g_hero_state + 0x80));
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), D_L20_00298970[FloatToInt(((Hero *)g_hero_state)->f[0xC38/4])] * 0.5f);
            break;
        }
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
    if (saved_sub_state != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (saved_anim_id != M2C_FIELD(hero_object, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}

