#include "names.h"
/* func_L19_002BCA50 (Grelbin): the hero's per-frame state handler, a 149-way switch on the
   state at 0x2294 over 46 bodies (25944 bytes, level 19 only).  One function: one prologue
   (frame 0x190), one return.

   Derived from func_L20_002CD928 (src/levels/20_yeedil/L20_002CD928.c), the same engine
   routine: Grelbin's jump table (jtbl_002A3AE0) is Yeedil's minus 17 bodies, 0x27-0x2A/0x3E,
   0x2E, 0x30, 0x37, 0x3F-0x44, 0x46, 0x47, 0x49-0x4E, 0x65, 0x78 and 0x7A, which fall to the
   common exit here.  Inside the bodies that stay, Yeedil's b[0x1492] branches are gone from the
   0x0/0x1/0x3/... group, state 4, 0x14, 0x15/0x83 (two), 0x13 and 0x1F, and so is the h[0x528]
   branch inside the 0x7-0x12 group; state 0x2F and the 0x7-0x12 group's first test keep
   theirs.  State 0x79 does not fall into 0x8D here (it clears D_00189F10 and stores -1/60 at
   +8), and the call on b[0x22B4] == 1 is absent.

   The unit's flags (config/cflags.txt) are those of the Yeedil unit, each needed by retail's
   code here too:
   -ffast-math      max.s;
   -g               the line labels that put retail's nop pairs before the div.s;
   -frac2-zero-ti-por           the por+sq clears of 0($sp);
   -frac2-keep-block-order and  no Cygnus block counting before cse;
   -frac2-no-null-pointer-checks
   (the quadword clears' zero in $a0 is the compiler's one-GPR TImode reload);
   -frac2-hazard-labels         branch targets on the mtc1 hazard nops.
   See docs/build/compiler-notes.md for each option. */

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 x0[7]; s32 x1C; u8 x20[0xC0]; } LevelInfo;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(d) (0)
extern char g_pad_state[];
extern u8 D_00138354[];
extern u8 g_sound_state[];
extern char g_hero_state[];
extern char D_00189F10[];
extern char g_progress_statistics[];
extern u8 D_0018CF10[];
extern u32 D_001A7390 MACRO_ADDR;
extern s32 g_current_map_index MACRO_ADDR;
extern u8 D_001A7B08[0x40] MACRO_ADDR;
extern u8 D_001A7B2A MACRO_ADDR;
extern f32 D_L19_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L19_001A8FF0 MACRO_ADDR;
extern u8 D_L19_001ACE68[];
extern s32 D_L19_001B0040 MACRO_ADDR;
extern s32 g_frame_l19_counter MACRO_ADDR;
extern s32 D_L19_001B31B0 MACRO_ADDR;
extern s32 D_L19_001B31B8 MACRO_ADDR;
extern u8 D_L19_001B9900[];
extern u8 D_L19_001B9A58[];
extern u8 D_L19_001B9CC8[];
extern u8 D_L19_001C3F00[];
extern u8 D_L19_0025F110[];
extern Rec2C D_L19_00260C90[];
extern u8 D_L19_00261010[];
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
extern void hero_update_held_grab(void);
extern s32 shooter_update_ranged_attack(s32);
extern s32 hero_get_anim_id(s32);
extern void hero_detach_from_object(s32);
extern void ClipHeroVelocityAtWall(s32);
extern s32 hero_l19_set_state(s32, s32);
/* Runs the hero's state machine once per frame in Grelbin: walking, jumping, gliding, swinging and the rest. */
void hero_l19_update_state_machine(void) {
    f32 frame_floateed62;
    s32 value1;
    s32 *ptr1;
    Hero *ptr2;
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
    f32 k03;
    s32 animation2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* ptr63;
    void* ptr60;
    f32 scalar112;
    void* ptr54;
    s32 value64;
    void* ptr56;
    s32 value86;
    s32 value91;
    void* ptr51;
    s32 value65;
    void* ptr57;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 frame_float_e0;
    f32 frame_float_e4;
    f32 frame_float_e8;
    f32 frame_float_ec;
    f32 frame_float_f0;
    f32 frame_float_f4;
    f32 frame_float_f8;
    s32 frame_int_fc;
    f32 frame_float100;
    s32 frame_int104;
    f32 frame_float108;
    f32 frame_float10_c;
    f32 frame_float110;
    s32 frame_int114;
    s32 frame_int118;
    s32 frame_int11_c;
    f32 scalar1;
    f32 scalar2;
    f32 scalar3;
    f32 scalar4;
    f32 scalar5;
    f32 scalar6;
    f32 scalar7;
    f32 scalar8;
    f32 scalar9;
    f32 scalar10;
    f32 scalar11;
    f32 scalar13;
    f32 scalar14;
    f32 scalar15;
    f32 scalar16;
    f32 scalar17;
    f32 scalar18;
    f32 scalar19;
    f32 scalar20;
    f32 scalar21;
    f32 scalar22;
    f32 scalar12;
    f32 scalar24;
    f32 scalar23;
    f32 scalar25;
    f32 scalar26;
    f32 scalar27;
    f32 scalar28;
    f32 scalar29;
    f32 scalar30;
    f32 scalar32;
    f32 scalar33;
    f32 scalar34;
    f32 scalar35;
    f32 scalar36;
    f32 scalar37;
    f32 scalar38;
    f32 scalar31;
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
    f32 scalar55;
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
    f32 scalar105;
    f32 scalar106;
    f32 scalar107;
    f32 scalar108;
    f32 scalar109;
    f32 scalar110;
    f32 scalar111;
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
    f32 scalar104;
    f32 scalar127;
    f32 scalar128;
    f32 scalar129;
    f32 scalar130;
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
    f32 scalar131;
    f32 scalar155;
    f32 scalar156;
    f32 scalar157;
    f32 scalar158;
    s16 small3;
    s32 value29;
    s16 small5;
    s32 value31;
    s32 value58;
    s32 value3;
    s32 value4;
    s32 value5;
    s32 value6;
    s32 value7;
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
    s32 value32;
    s32 value34;
    s32 value35;
    s32 value36;
    s32 value37;
    s32 value38;
    s32 value39;
    s32 value40;
    s32 value41;
    s32 value42;
    s32 value50;
    s32 value51;
    s32 value53;
    s32 value54;
    s32 value55;
    s32 value56;
    s32 value57;
    s32 value59;
    s32 value60;
    s32 value61;
    s32 value62;
    s32 value63;
    s32 value66;
    s32 value67;
    s32 value68;
    s32 value69;
    s32 value70;
    s32 value72;
    s32 value73;
    s32 value74;
    s32 value75;
    s32 value76;
    s32 value77;
    s32 value78;
    s32 value79;
    s32 value80;
    s32 value81;
    s32 value82;
    s32 value83;
    s32 value84;
    s32 value85;
    s32 value87;
    s32 value88;
    s32 value89;
    s32 value90;
    s32* ptr58;
    s32* ptr61;
    u16 small4;
    u16 small6;
    u16 small7;
    u32 value2;
    u32 value30;
    u32 value33;
    u32 value43;
    u32 value44;
    u32 value45;
    u32 value47;
    u32 value48;
    u32 value49;
    u32 value52;
    u32 value46;
    u32 value71;
    u8 small1;
    u8 small2;
    u8 small8;
    u8 small9;
    void* ptr3;
    void* ptr4;
    void* ptr5;
    void* ptr6;
    void* ptr7;
    void* ptr8;
    void* ptr9;
    void* ptr10;
    void* ptr11;
    void* ptr12;
    void* ptr13;
    void* ptr14;
    void* ptr15;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* ptr16;
    void* ptr17;
    void* ptr18;
    void* ptr19;
    void* ptr20;
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
    void* ptr52;
    void* ptr53;
    void* ptr55;
    void* ptr59;
    void* ptr62;

    frame_int114 = ((Hero *)g_hero_state)->i[0x2298/4];
    ptr15 = ((Hero *)g_hero_state)->ptr[0x2290/4];
    frame_int118 = (s32) M2C_FIELD(ptr15, u8* , 0x43);
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
        value30 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((value30 == 1) || (value30 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)vec0) = 0;
                vec0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)vec0), (s32)&D_L19_001B9A58[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)D_L19_001B9A58)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (small2 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (small2 == 0xE)) || (small2 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    value4 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    value4 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != value4) {
                        set_hero_animation(value4, 0, 5.0f);
                    }
                    scalar1 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = scalar1;
                    if (scalar1 < 0.55f) {
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
            value46 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (value46 == 3) {
                scalar105 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (scalar105 > 1.0f) {
                    scalar105 = 1.0f;
                }
                ptr10 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                scalar132 = scalar105 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = scalar132;
                if (M2C_FIELD(ptr10, u8* , 0x42) == M2C_FIELD(ptr10, u8* , 0x43)) {
                    scalar104 = ((Hero *)g_hero_state)->f[0x174/4] / scalar132;
                    if ((scalar104 > 5.0f) && ((f32) M2C_FIELD(ptr10, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, scalar104, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (value46 == 4) {
                scalar132 = 0.0075000003f;
            } else {
                scalar132 = 0.004916667f;
            }
            hero_approach_speed(0.0f, scalar132);
            vec_clear_128((s32)(g_hero_state + 0xF0));
            hero_shrink_vector_by_amount(scalar132);
            if ((((Hero *)g_hero_state)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                value63 = (s32)(g_hero_state + 0xF0);
                if (((Hero *)g_hero_state)->f[0x31C/4] > 0.2f) {
                    hero_apply_mode_transform(value63, value63 + 0x30, 0.0061111115f);
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
        hero7C = (void*)g_hero_state;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            value21 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = value21;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)value21 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)value21 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(value21, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            value53 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(value53, u16* , 0x34) = (u16) (M2C_FIELD(value53, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        value55 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(value55, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(value55, u8* , 0x23) = 0x80U;
        }
        value5 = ((Hero *)hero7C)->i[0x7A4/4];
        ptr12 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)value5 + 0x10, (u8 *)ptr12 + 0x10);
        qcopy((u8 *)value5 + 0xF0, (u8 *)ptr12 + 0xF0);
        func_002A0F48(value5);
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
            value14 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (value14 != -1) {
                ptr11 = (value14 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(ptr11, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ptr11, u8* , 0x74) != 0) {
                        snd_stop_voice(value14);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            value6 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects((value6 >= 9) ? 8 : value6, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            scalar47 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (scalar47 > 0.0f) {
                if (scalar47 < 10.0f) {
                    EmitHeroRandomizedMotionEffects(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                value56 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (value56 < 0xF) {
                    EmitHeroRandomizedMotionEffects(((s32) (0x14 - value56) / 3) + 1, 1, 0);
                }
            }
        }
        value57 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (value57 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == value57) {
                part_emit_hero_dust_and_debris(3, 0x10, 0);
                if (D_L19_001B31B0 != 0) {
                    RippleDisturb(D_L19_001B31B0, D_L19_001B31B8, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x46;
            }
            value28 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = value28;
            if (value28 >= 0x29) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.011635531f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.008726647f;
        scalar119 = 0.0f;
        k02 = 0.2f;
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            scalar121 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (scalar121 > 1.0f) {
                scalar121 = 1.0f;
            }
            if (scalar121 < k02) {
                scalar121 = k02;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                value58 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                scalar121 = ((f32) (s16) value58 * 0.025f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) value58;
                if (scalar121 > 1.0f) {
                    scalar121 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (scalar121 < 0.35f)) {
                scalar121 = 0.35f;
            }
            scalar119 = scalar121 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            scalar120 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (scalar120 > 1.0f) {
                scalar120 = 1.0f;
            }
            if (scalar120 < k02) {
                scalar120 = k02;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = cntA40;
                scalar120 = ((f32) (s16) cntA40 * 0.025f) + 0.5f;
                if (scalar120 > 1.0f) {
                    scalar120 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                scalar120 = 1.0f;
            }
            scalar119 = scalar120 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                value31 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = value31;
                if ((s16) value31 >= 0x5B) {
                    small6 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (small6 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (small6 + 1);
                    }
                }
                value32 = (*(s32*)&D_001A7390);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) value32) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) value32;
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
            ptr2 = (Hero *)g_hero_state;
            if ((g_frame_l19_counter - ptr2->i[0xA54/4]) < 0x46) {
                ptr2->i[0xA50/4]++;
            }
            ptr2->i[0xA54/4] = g_frame_l19_counter;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            scalar119 = 0.0f;
        }
        scalar56 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), scalar119, (s32) (((void*)g_hero_state) + 0xA28), 0.015f, 0.2f, stick_turn, 0);
        scalar78 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], scalar56);
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
        scalar131 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (scalar131 < 1.0f) {
                scalar131 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            scalar96 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                scalar96 = 0.4f;
            }
            if (scalar131 < scalar96) {
                scalar131 = scalar96;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * scalar131);
        }
        if (math_fast_float_d((s32)(g_hero_state + 0xA30)) != 0) {
            heroA30 = (void*)g_hero_state;
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
                value66 = 4;
                value70 = 0xB;
            } else {
                value66 = 0x28;
                value70 = 0x5A;
            }
            ((Hero *)heroA30)->i[0xA30/4] = math_random_int_range(value66, value70);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                ptr36 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (ptr36 != 0) {
                    if (M2C_FIELD(ptr36, s16* , 0xAA) == 0x261 /* moby class 609 */) {
                        for (value75 = 0; value75 < 4; value75++) {
                            moby_transform_joint_to_world((s32) ptr36, value75 % 2, (s32)((TI128*)vec0));
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
        scalar75 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        value33 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (value33 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], scalar75);
        } else if (value33 == 0x32) {
            scalar122 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)D_L19_00261010, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xF) && (scalar122 < 0.075f)) {
                scalar122 = 0.075f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), scalar122, ((Hero *)g_hero_state)->f[0x98/4], scalar75);
        } else if (value33 == 0x33) {
            frame_float_e0 = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &frame_float_e0, 0.0f, 0.0022222223f);
            } else {
                ApproachValue((s32) &frame_float_e0, 0.0f, 0.0011111111f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), frame_float_e0);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        ClipHeroVelocityAtWall(0);
        scalar76 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(scalar75) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), scalar76, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        scalar55 = scalar78 * 47.0f;
        ((Hero *)D_L19_0025F110)->f[0x114/4] = scalar55;
        ((Hero *)D_L19_0025F110)->f[0x118/4] = (f32) (scalar76 * 1.5f);
        ((Hero *)D_L19_0025F110)->f[0x110/4] = (f32) (scalar76 * 1.4f);
        if (scalar55 > 0.8726647f) {
            ((Hero *)D_L19_0025F110)->f[0x114/4] = 0.8726647f;
        } else if (scalar55 < -0.8726647f) {
            ((Hero *)D_L19_0025F110)->f[0x114/4] = -0.8726647f;
        }
        scalar48 = scalar78 * 40.0f;
        scalar12 = scalar76 * 1.1f;
        ((Hero *)D_L19_0025F110)->f[0x364/4] = 0.03f;
        ((Hero *)D_L19_0025F110)->f[0x368/4] = 0.22f;
        ((Hero *)D_L19_0025F110)->f[0x324/4] = scalar48;
        ((Hero *)D_L19_0025F110)->f[0x328/4] = scalar12;
        ((Hero *)D_L19_0025F110)->f[0x414/4] = 0.03f;
        ((Hero *)D_L19_0025F110)->f[0x418/4] = 0.22f;
        ((Hero *)D_L19_0025F110)->f[0x3D4/4] = scalar48;
        ((Hero *)D_L19_0025F110)->f[0x3D8/4] = scalar12;
        break;
    case 0x73:                                      /* switch 1 */
        value7 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        ptr23 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects((value7 >= 9) ? 8 : value7, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) ptr23, (s32) ptr23, vec_length_xy((s32) ptr23) * 0.92f);
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
        frame_float_e4 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &frame_float_e4, 0.0f, 0.0011111111f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), frame_float_e4);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            ptr31 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(ptr31, s32* , 0x2290), 4, (s32)((TI128*)vec0));
            (*(TI128*)vec20) = 0;
            vec20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), M2C_FIELD(ptr31, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)vec20));
            qcopy(vec10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), (s32) ((TI128*)vec20));
            vec10[2] += 0.033333335f;
            part_spawn_bubble((s32)((TI128*)vec0), (s32) ((TI128*)vec10), 25200.0f, -1.0f);
            value34 = M2C_FIELD(ptr31, s32* , 0x1B8);
            if (value34 < 0x28) {
                value1 = 5;
                value80 = math_random_int_range(2, value1) + ((s32) M2C_FIELD(ptr31, s32* , 0x1B8) / value1);
                goto block_224;
            }
            if (value34 >= 0x47) {
                value80 = math_random_int_range(0xA, 0x14);
block_224:
                M2C_FIELD(ptr31, s32* , 0xA30) = value80;
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
            value8 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects((value8 >= 7) ? 6 : value8, 0, 0);
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
            scalar67 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)D_L19_00261010, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * scalar67);
            scalar23 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * scalar67;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = scalar23;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            scalar49 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((scalar49 > 0.0f) && (scalar49 < 10.0f)) {
                EmitHeroRandomizedMotionEffects(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.0011666666f);
        ClipHeroVelocityAtWall(0);
        hero_update_height_offset();
        break;
    case 0x85:                                      /* switch 1 */
        ptr13 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)ptr13 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)ptr13 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)vec0), (s32)(g_hero_state + 0x2C0), -1.0f);
        scalar123 = 0.0f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            scalar123 = -((Hero *)g_hero_state)->f[0x1FB4/4] * 0.75f;
        }
        math_spring_float_to_goal((s32)(g_hero_state + 0x7C0), (s32)(g_hero_state + 0x7C4), scalar123, 0.007f, 0.3f, 0.03f);
        FastVecScale((s32) ((TI128*)vec10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)vec10));
        vec_scale_to_length((s32)((TI128*)vec0), (s32)((TI128*)vec0), 1.0f);
        hero_apply_reference_tilt_rotation((s32)((TI128*)vec0), (s32) ((TI128*)vec30), 0, 0.025f, 0.4f, 0.0f);
        ((Hero *)g_hero_state)->f[0x1B4/4] = 0.21666668f;
        vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)g_hero_state, 0.21666668f);
        cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
        vec_clear_128((s32)((TI128*)vec0));
        vec0[1] = -((Hero *)g_hero_state)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(g_hero_state + 0x190), (s32)((TI128*)vec0), (s32)&D_L19_001B9A58[0x218]);
        hero_steer_heading(0, 0.02f, 0.3f, 0.034906592f);
        break;
    case 0x2F:                                      /* switch 1 */
        animation2F = -1;
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
        if ((animation2F != -1) && (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation(animation2F, 0, (f32) blend2F);
        } else {
            ptr44 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr44, u8* , 0x60) & 2) && (M2C_FIELD(ptr44, u8* , 0x42) == 0x36)) {
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
        ptr62 = ((Hero *)g_hero_state)->ptr[0xB10/4];
        if (ptr62 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr62, f32* , 0x10) - M2C_FIELD(ptr15, f32* , 0x10), M2C_FIELD(ptr62, f32* , 0x14) - M2C_FIELD(ptr15, f32* , 0x14));
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
        ptr63 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (ptr63 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(ptr63, f32* , 0x10) - M2C_FIELD(ptr15, f32* , 0x10), M2C_FIELD(ptr63, f32* , 0x14) - M2C_FIELD(ptr15, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vec0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        scalar25 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec0));
        ((Hero *)g_hero_state)->f[0xAB0/4] = scalar25;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 60.0f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (scalar25 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        value35 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (value35 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.45000002f, 0.022222223f);
            ptr40 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            scalar137 = mat_fast_helper_a(M2C_FIELD(ptr40, f32* , 0x10) - M2C_FIELD(ptr15, f32* , 0x10), M2C_FIELD(ptr40, f32* , 0x14) - M2C_FIELD(ptr15, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], scalar137) > 1.5707964f) {
                    scalar137 = FastAddRotations(scalar137, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = scalar137;
            hero_steer_heading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (value35 == 1) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((math_solve_quadratic((s32) &frame_float_e8, (s32) &frame_float_ec, -0.0058333334f, ((Hero *)g_hero_state)->f[0xAA0/4], 1.9f - ((Hero *)g_hero_state)->f[0xAB0/4]) > 0) && (frame_float_e8 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = frame_float_e8;
            ((Hero *)g_hero_state)->i[0x2298/4] = 1;
        }
        ((Hero *)g_hero_state)->h[0x226/2] = 3;
        if (((Hero *)g_hero_state)->f[0xAAC/4] < 20.0f) {
            ((Hero *)g_hero_state)->i[0xAB4/4] = 1;
        }
        if (((Hero *)g_hero_state)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn24 = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)vec0)), vec0[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn24, 0.10762865f);
        }
        vec20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        scalar26 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        vec20[2] = 0;
        vec20[1] = scalar26;
        FastVecAdd((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)vec10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vec20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)vec10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        scalar27 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (scalar27 < 30.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((30.0f - scalar27) * 0.008055556f));
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
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(ptr15, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        ptr45 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        scalar81 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (ptr45 != 0) {
            ptr41 = M2C_FIELD(ptr45, void** , 0x68);
            if ((ptr41 != 0) && (M2C_FIELD(ptr41, s32* , 0x34) != 0)) {
                scalar138 = M2C_FIELD(ptr45, f32* , 0xF8);
                if (FastDiffRots(scalar138, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    scalar138 = FastAddRotations(scalar138, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), scalar138, (s32) (((void*)g_hero_state) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
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
        scalar28 = mat_fast_helper_a(vec0[2], vec0[0]);
        vec10[1] = scalar28;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), scalar28, (s32) (((void*)g_hero_state) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), vec10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        value78 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((value78 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x29) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                scalar139 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0035f;
                if (scalar139 > 0.083333336f) {
                    scalar139 = 0.083333336f;
                }
                vec_b0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * scalar139;
                scalar29 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * scalar139;
                ptr3 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&vec_b0[2]) = 0;
                vec_b0[1] = scalar29;
                FastVecAdd((s32) ptr3, (s32) ptr3, (s32) ((TI128*)vec_b0));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                ptr32 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) ptr32, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    ptr24 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) ptr24, (s32) (((void*)g_hero_state) + 0x110), 0.011111111f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) ptr24) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vec_b0), (s32) ptr32, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) ptr24, (s32) ptr24, 0.015833333f);
                    }
                }
                scalar68 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vec_b0), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vec_b0), (s32) ((TI128*)vec_b0), scalar68);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec_b0));
            }
        }
        ptr42 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (ptr42 != 0) {
            ptr16 = M2C_FIELD(ptr42, void** , 0x68);
            ptr25 = ((void*)g_hero_state) + 0xF0;
            if (ptr16 != 0) {
                scalar30 = FastVecLength((s32) ptr25);
                scalar32 = M2C_FIELD(ptr16, f32* , 0xC);
                frame_float_f0 = scalar30;
                if (scalar32 < scalar30) {
                    ApproachValue((s32) &frame_float_f0, scalar32, 0.004166667f);
                    vec_scale_to_length((s32) ptr25, (s32) ptr25, frame_float_f0);
                }
            }
        }
        scalar2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        ptr38 = ((void*)g_hero_state) + 0x80;
        ptr37 = ((void*)g_hero_state) + 0xF0;
        vec_d0[0] = math_fast_sin_or_cos_a(scalar2) * 0.15f;
        scalar3 = math_fast_sin_or_cos_b(scalar2) * 0.15f;
        (*(s32*)&vec_d0[2]) = 0;
        vec_d0[1] = scalar3;
        FastVecAdd((s32) &vec_d0[0], (s32) &vec_d0[0], (s32) ptr38);
        FastVecAdd((s32) ((TI128*)vec_b0), (s32) &vec_d0[0], (s32) ptr37);
        FastVecSub((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_b0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vec_b0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vec_c0));
        FastVecSub((s32) ptr37, (s32) ((TI128*)vec_b0), (s32) &vec_d0[0]);
        scalar69 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        scalar70 = ((Hero *)g_hero_state)->f[0xAE4/4] - scalar69;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vec_c0))) {
            vec_scale_to_length((s32) ((TI128*)vec_c0), (s32) ((TI128*)vec_c0), scalar70);
            FastVecAdd((s32) ptr38, (s32) ptr38, (s32) ((TI128*)vec_c0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (value78 != 0)) {
            min2B = 0.23333335f;
            scalar4 = vec_length_xy((s32) ptr37);
            frame_float_f4 = scalar4;
            if (scalar4 < min2B) {
                math_spring_float_to_goal((s32) &frame_float_f4, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                vec_b0[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                scalar5 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                vec_b0[2] = 0.0f;
                vec_b0[1] = scalar5 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) ptr37, (s32) ptr37, (s32) ((TI128*)vec_b0));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((scalar81 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            scalar71 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            small5 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (small5 != 0) {
                value81 = small5 == 1;
            } else {
                (*(TI128*)vec_b0) = ((Hero *)g_hero_state)->q[0x110/16];
                value81 = hero_get_speed_along_forward((s32) ((TI128*)vec_b0)) > 0.0f;
            }
            if (value81 != 0) {
                if (M2C_FIELD(ptr15, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    ptr43 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(ptr43, u8* , 0x42) == M2C_FIELD(ptr43, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, scalar71, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(ptr15, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                ptr39 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(ptr39, u8* , 0x42) == M2C_FIELD(ptr39, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, scalar71, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L19_00260C90[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        value76 = 0;
        if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
            value76 = 1;
        }
        value10 = ((Hero *)g_hero_state)->i[0xBE4/4];
        if (value10 != 0) {
            FastVecSub((s32)((TI128*)vec0), value10 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
            scalar6 = cam_get_view_space_vector_length((s32)((TI128*)vec0));
            if (((scalar6 > 2.0f) && (scalar6 < 5.0f)) || (value76 != 0)) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
            }
            hero_approach_speed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length((s32) ((TI128*)vec10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
            cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
            FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)vec10));
        } else {
            if ((value76 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
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
        scalar51 = ((Hero *)g_hero_state)->f[0x31C/4];
        scalar145 = 0.12833333f;
        if (scalar51 > 2.25f) {
            scalar145 = 0.064166665f;
        } else if (scalar51 > 1.8f) {
            scalar145 = 0.08983333f;
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
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L19_001B9900)->f[0x180/4] = 0.1f;
                ((Hero *)D_L19_001B9900)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)D_L19_001B9900)->i[0x16C/4] = 0;
            }
        }
        value36 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xE;
        if (value36 < 9) {
            ptr17 = ((void*)g_hero_state) + 0xF0;
            frame_float_f8 = cam_get_view_space_height((s32) ptr17);
            ApproachValue((s32) &frame_float_f8, scalar145, 0.041666668f);
            cam_set_view_space_height((s32) ptr17, (s32) ptr17, frame_float_f8);
        } else if (value36 > lim3) {
            ptr26 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr26, (s32) ptr26, 0.036111113f);
            if (cam_get_view_space_height((s32) ptr26) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            scalar140 = -0.6166667f;
            if (D_L19_001A8FF0 != 0) {
                scalar140 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) ptr26) < scalar140) {
                cam_set_view_space_height((s32) ptr26, (s32) ptr26, scalar140);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L19_00260C90[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        value68 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (value68 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                value77 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    ptr18 = ((void*)g_hero_state) + 0xBC0;
                    scalar141 = hero_get_direction_angle_delta((s32) ptr18, 0);
                    scalar97 = hero_get_direction_angle_delta((s32) ptr18, 1);
                } else {
                    scalar141 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                    scalar97 = math_shortest_angle_delta(1, ((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
                }
                if (scalar97 < 4.3633237f) {
                    value77 = 1;
                }
                if (scalar141 > 0.0f) {
                    ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (scalar97 + 1.0f));
                }
                ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
                qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
                if (value77 != 0) {
                    hero_steer_heading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    hero_steer_heading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    value69 = 1;
                    if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x83) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xC)) {
                        value69 = 0;
                    } else if ((((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 6.0f)) {
                        value69 = 0;
                    }
                    if (value69 != 0) {
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
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L19_00260C90[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        value11 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        ptr33 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)D_L19_00260C90;
        if ((value11 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            ptr27 = ((void*)g_hero_state) + 0x80;
            scalar108 = vec_distance_xy(value11 + 0x10, (s32) ptr27);
            if ((*(s32*)&D_L19_001A8FF0) != 0) {
                scalar108 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) ptr27);
            }
            scalar108 = scalar108 - 0.5f;
            if (scalar108 < 0.0f) {
                scalar108 = 0.0f;
            }
            value37 = M2C_FIELD(ptr33, s32* , 4);
            if (value37 == 0) {
                scalar98 = 0.75f;
                scalar147 = 0.8f;
                scalar152 = 4.0f;
            } else if (value37 == 1) {
                scalar98 = 0.6f;
                scalar147 = 1.7f;
                scalar152 = 4.0f;
            } else {
                scalar98 = 1.3f;
                scalar147 = 1.7f;
                scalar152 = 1.9f;
            }
            scalar73 = scalar108 - scalar98;
            if (math_fabs(scalar73) < (scalar147 + 3.0f)) {
                scalar110 = scalar73 * 1.1111112f;
                if (scalar152 < scalar110) {
                    scalar110 = scalar152;
                }
                if (scalar110 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = scalar110;
                }
            }
        }
        value38 = M2C_FIELD(ptr33, s32* , 4);
        switch (value38) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            scalar52 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (scalar52 < 9.0f)) {
                if (scalar52 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (scalar52 > 7.0f) {
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
            scalar99 = hero_get_direction_angle_delta((s32)(g_hero_state + 0xBC0), 0);
        } else {
            scalar99 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0xBEC/4], ((Hero *)g_hero_state)->f[0x98/4]);
        }
        scalar53 = math_fabs(scalar99);
        if ((M2C_FIELD(ptr33, s32* , 4) == 1) && (scalar99 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (scalar53 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        value89 = 1;
        if ((M2C_FIELD(ptr33, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
            value89 = 0;
        }
        if (value89 != 0) {
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
            ptr5 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) ptr5, (s32) ptr5, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L19_001A8FF0) != 0) {
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
        value39 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (value39 > lim) {
            if (value39 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            ptr19 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) ptr19);
            level_append_record_to_table((s32) ptr19, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) ptr19, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) ptr19, 0xC, 6, 0.0f);
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
            value41 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((value41 > lim) && (value41 < 0x16)) {
                ptr34 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (ptr34 != 0) {
                    ptr28 = ((void*)g_hero_state) + 0x80;
                    vec30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    vec30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    vec30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vec30));
                    (*(u8*)((u8*)vec10+9)) = 3;
                    vec0[3] = 5627.925f;
                    (*(u8*)((u8*)vec10+8)) = 0;
                    scalar79 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)vec10+10)) = M2C_FIELD(ptr34, u16* , 0xAA);
                    vec40[0] = math_fast_sin_or_cos_a(scalar79) * 0.8f;
                    scalar7 = math_fast_sin_or_cos_b(scalar79) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = scalar7;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) ptr28);
                    part_emit_effects_at_nearby_mobys((s32) ptr34, coll_process_hit(0.8f, (s32) &vec40[0], 0, (s32) ptr34, (s32)((TI128*)vec0)));
                    scalar79 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    vec40[0] = math_fast_sin_or_cos_a(scalar79) * 0.8f;
                    scalar9 = math_fast_sin_or_cos_b(scalar79) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = scalar9;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) ptr28);
                    part_emit_effects_at_nearby_mobys((s32) ptr34, coll_process_hit(0.8f, (s32) &vec40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)vec0)));
                    scalar79 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    vec40[0] = math_fast_sin_or_cos_a(scalar79) * 0.8f;
                    scalar11 = math_fast_sin_or_cos_b(scalar79) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = scalar11;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) ptr28);
                    part_emit_effects_at_nearby_mobys((s32) ptr34, coll_process_hit(0.8f, (s32) &vec40[0], 0, (s32) ptr34, (s32)((TI128*)vec0)));
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
        value61 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            value61 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (value61 != 0)) {
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
            scalar74 = ReadPadFloatHistory(1);
            if ((FastDiffRots(scalar74, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            pA60 = ((void*)g_hero_state) + 0xA60;
            hero_build_move_impulse(0.7f, 0.0f);
            (*(TI128*)vec0) = ((Hero *)g_hero_state)->q[0xA60/16];
            scalar54 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)vec0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = scalar54;
            if (scalar54 < 0.011666667f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.011666667f;
            }
            vec_clear_128((s32) pA60);
        }
        scalar142 = 1.0f;
        if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
            hero_update_turn_from_anim();
        } else {
            ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
            qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (((Hero *)g_hero_state)->b[0x40F] == 0) && (((Hero *)g_hero_state)->b[0x22BA] == 0)) {
                hero_steer_heading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                scalar82 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (scalar82 > 0.78539824f)) {
                    scalar142 = 0.0f;
                }
                hero_set_turn_rates();
            }
        }
        hero_apply_mode_pose_offsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            scalar155 = 0.09916667f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.029178405f);
            if (scalar155 < 0.0f) {
                scalar155 = 0.0f;
            }
            if (scalar155 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = scalar155;
            }
        }
        k005 = scalar142 * 0.005f;
        scalar143 = 0.0055555557f;
        if (((Hero *)g_hero_state)->b[0x40F] != 0) {
            scalar127 = 2.617994f - ((Hero *)g_hero_state)->f[0x1A8/4];
            if (scalar127 > 1.0f) {
                scalar127 = 1.0f;
            }
            if (scalar127 < 0.2f) {
                scalar127 = 0.2f;
            }
            scalar143 = 0.004722222f;
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * scalar127);
        }
        scalar83 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (scalar83 > 0.6108653f)) {
            scalar128 = 1.0f - (scalar83 * 0.4f);
            if (scalar128 < 0.0f) {
                scalar128 = 0.0f;
            }
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * scalar128);
        }
        hero_approach_speed(k005, scalar143);
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
        scalar148 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * vec0[0];
        if ((*(s32*)&D_L19_001A8FF0) == 0) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] < 0x3C) {
                scalar148 *= 0.1f;
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) {
            hero_rotate_matrix(0.0f, 0.0f, scalar148);
        }
        hero_approach_speed(0.027777778f, 0.004166667f);
        hero_compute_push_direction(99999.0f);
        if ((*(s32*)&D_L19_001A8FF0) != 0) {
            qcopy(vec10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec10), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vec10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), (s32)(g_hero_state + 0xE0));
        value22 = coll_process_hit(0.57f, (s32) ((TI128*)vec10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (value22 != 0) {
            FastVecScale((s32) ((TI128*)vec20), (s32)(g_hero_state + 0x110), 7.0f);
            for (value73 = 0; value73 < value22; value73++) {
                if (moby_is_in_special_class_range(((s32 *)D_L19_001C3F00)[value73]) != 0) {
                    part_queue_impact_effect(((s32 *)D_L19_001C3F00)[value73], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec20), 1.0f);
                }
            }
        }
        cam_set_limits_first(0.017f, 0.3f);
        cam_set_limits_third(0.025f, 0.3f);
        cam_set_limits_fourth(0.03f, 0.27f);
        scalar156 = scalar148 * 27.0f;
        if (scalar156 > 1.7f) {
            scalar156 = 1.7f;
        } else if (scalar156 < -1.7f) {
            scalar156 = -1.7f;
        }
        scalar13 = scalar156 * 0.5f;
        ((Hero *)D_L19_0025F110)->f[0x60/4] = (f32) -scalar156;
        ((Hero *)D_L19_0025F110)->f[0x278/4] = scalar13;
        ((Hero *)D_L19_0025F110)->f[0x1C8/4] = scalar13;
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
            value85 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            value90 = (s32)D_L19_001ACE68;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(value85 + value90) * 0.5f);
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
            scalar114 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                scalar114 = 0.43633235f;
            }
            qcopy(vec0, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &vec0[1], scalar114, (s32) (((void*)g_hero_state) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
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
        ptr60 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ptr60, (s32) ptr60, vec_length_xy((s32) ptr60) * 0.9f);
        hero_apply_mode_transform((s32) ptr60, (s32) ptr60, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) ptr60) < -0.8333334f) {
            cam_set_view_space_height((s32) ptr60, (s32) ptr60, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        value62 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            value62 = 0;
        }
        if (value62 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            ptr7 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) ptr7, (s32) ptr7, 0.025f);
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
        scalar35 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (scalar35 < 0.0f) && (scalar86 = ((Hero *)g_hero_state)->f[0x31C/4], (scalar86 < 1.2f))) {
            scalar90 = (scalar86 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (scalar90 < 0.0f) {
                scalar90 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), scalar35 * scalar90);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (scalar35 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L19_001B9CC8) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        hero_apply_mode_pose_offsets();
        hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
        }
        hero_steer_heading(0, 0.027f, 0.3f, ((Hero *)g_hero_state)->f[0x24B8/4] * 0.087266475f);
        scalar115 = 0.0013888889f;
        if (((Hero *)g_hero_state)->f[0x24B8/4] < 0.2f) {
            scalar115 = 0.00055555557f;
        }
        hero_approach_velocity(scalar115);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            value16 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (value16 != -1) {
                ptr8 = (value16 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr8, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr8, u8* , 0x74) != 0)) {
                    snd_stop_voice(value16);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            value17 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (value17 != -1) {
                ptr9 = (value17 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(ptr9, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(ptr9, u8* , 0x74) != 0)) {
                    snd_stop_voice(value17);
                }
            }
            ((Hero *)g_hero_state)->i[0x2438/4] = -1;
            snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        }
        scalar153 = 0.050000004f;
        if (((Hero *)g_hero_state)->i[0x1338/4] == 3) {
            scalar153 = 0.083333336f;
        }
        scalar154 = 0.72f;
        scalar41 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            scalar153 = 0.12833333f;
            scalar154 = 0.98640007f;
        }
        if (scalar41 != 0.0f) {
            scalar154 = scalar41;
        }
        ptr21 = ((void*)g_hero_state) + 0xF0;
        frame_float110 = cam_get_view_space_height((s32) ptr21);
        hero_resolve_stick_direction(scalar153, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) ptr21, (s32) ptr21);
        math_spring_float_to_goal((s32) &frame_float110, (s32) (((void*)g_hero_state) + 0xA98), -scalar153 * scalar154, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) ptr21, (s32) ptr21, -frame_float110);
        scalar36 = ((Hero *)g_hero_state)->f[0x88/4];
        if (scalar36 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), scalar36, 0.06666667f);
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
                if (D_L19_001B31B0 != 0) {
                    RippleDisturb(D_L19_001B31B0, D_L19_001B31B8, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            scalar42 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((scalar42 >= 4.0f) && (scalar42 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects(7, 0, 0);
            }
        }
        small3 = ((Hero *)g_hero_state)->h[0x4AC/2];
        value13 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (value13 == small3) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((value13 < small3) && (value49 = ((Hero *)g_hero_state)->u[0x2294/4], (value49 != 0xB)) && (value49 != 0x10) && (value49 != 0xC) && (value49 != 0x11) && (value49 != 0x1B) && (value49 != 0x89) && (value49 != 0x48))) {
            hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
            scalar63 = ((Hero *)g_hero_state)->f[0x1B4/4];
            if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (scalar63 * 0.4f);
            }
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
            ((Hero *)g_hero_state)->f[0x1B4/4] = scalar63;
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
                value50 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (value50 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) value50 * 0.0044444446f);
                }
            }
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                value51 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (value51 < 0x22) {
                    cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) value51 * 0.014722222f);
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
                ptr22 = ((void*)g_hero_state) + 0xF0;
                scalar91 = vec_length_xy((s32) ptr22);
                if (scalar91 > 0.06166667f) {
                    scalar91 = 0.06166667f;
                }
                vec_fast_normalize_helper((s32) ptr22, (s32) ptr22, scalar91);
            }
        }
        scalar43 = ((Hero *)g_hero_state)->f[0x318/4];
        scalar87 = ((Hero *)g_hero_state)->f[0x490/4];
        if (scalar87 < scalar43) {
            scalar22 = scalar87 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = scalar22;
            if (scalar43 < scalar22) {
                ((Hero *)g_hero_state)->f[0x490/4] = scalar43;
            }
        }
        scalar44 = ((Hero *)g_hero_state)->f[0x88/4];
        if (scalar44 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = scalar44;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            scalar45 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (scalar45 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = scalar45;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        value52 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((value52 == 0x10) || (value52 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)vec0), 1, 0.8f, 0.0f, 0.3f);
                    value27 = coll_process_hit(0.9f, (s32)((TI128*)vec0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (value27 != 0) {
                        FastVecScale((s32) ((TI128*)vec10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (value74 = 0; value74 < value27; value74++) {
                            if (moby_is_in_special_class_range(((s32 *)D_L19_001C3F00)[value74]) != 0) {
                                part_queue_impact_effect(((s32 *)D_L19_001C3F00)[value74], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)vec10), 1.0f);
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
        scalar136 = cam_get_view_space_vector_length((s32)(g_hero_state + 0xF0));
        scalar92 = 0.0011111111f;
        if ((((Hero *)g_hero_state)->h[0x34E/2] == 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0xB)) {
            scalar92 = 0.0027777778f;
        }
        scalar136 = scalar136 - scalar92;
        if (scalar136 < 0.0f) {
            scalar136 = 0.0f;
        }
        if (((Hero *)g_hero_state)->b[0x1497] != 0) {
            hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        }
        ptr55 = ((void*)g_hero_state) + 0xF0;
        cam_set_view_space_vector_length((s32) ptr55, (s32) ptr55, scalar136);
        hero_apply_mode_transform((s32) ptr55, (s32) ptr55, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec0[0], vec0[1]);
        scalar24 = vec_length_xy((s32)((TI128*)vec0));
        if (scalar24 > 0.2f) {
            ptr2 = (Hero *)g_hero_state;
            ptr2->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(vec0[0], vec0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = scalar24;
            if (scalar24 < D_L19_001A7DAC[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L19_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L19_001A7DAC[1][1] * 0.016666668f;
            }
            if (((Hero *)g_hero_state)->b[0x22B4] == 1) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.015000001f;
            }
        } else {
            ((Hero *)g_hero_state)->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0x18AC/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        }
        frame_floateed62 = 1.0f;
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
        hero_approach_speed(frame_floateed62 * 0.005f, 0.0055555557f);
        hero_compute_push_direction(99999.0f);
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            ClipHeroVelocityAtWall(1);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0x110, 0.0069444445f);
            hero_cancel_velocity_into_wall();
            break;
        }
        hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.015000001f);
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
        vec_clear_128((s32)D_00189F10);
        ((Hero *)D_00189F10)->f[8/4] = -0.016666668f;
        break;
    case 0x8D:                                      /* switch 1 */
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        if (((*(s32*)&D_L19_001B0040) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ptr30 = ((void*)g_hero_state) + 0xF0;
            hero_update_held_grab();
            hero_resolve_stick_direction(1.0f, 0);
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            hero_approach_speed(0.0f, 0.0035f);
            vec_clear_128((s32) ptr30);
            ClipHeroVelocityAtWall(0);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                hero_apply_mode_transform((s32) ptr30, (s32) ((void*)g_hero_state) + 0x130, 0.0069444445f);
                hero_cancel_velocity_into_wall();
                break;
            }
            hero_apply_mode_transform((s32) ptr30, (s32) ptr30, 0.015000001f);
            break;
        }
        break;
    case 0x91:                                      /* switch 1 */
        if (((Hero *)g_hero_state)->h[0x1E0/2] < 0xA) {
            if (D_L19_001B0040 == 0) {
                if (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F) {
                    ((Hero *)g_hero_state)->h[0x1E0/2] = 0x28;
                    ((Hero *)g_hero_state)->i[0x229C/4] = 0;
                    ((Hero *)g_hero_state)->i[0x24A0/4] = 0;
                    hero_detach_from_object(0);
                    FadeToBlack(0x10);
                    ((Hero *)g_hero_state)->c[0x22C1] = 1;
                }
            }
        }
        break;
    case 0x93:                                      /* switch 1 */
        if (((*(s32*)&D_L19_001B0040) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
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
            if (shooter_update_ranged_attack((s32) ptr15) != 0) {
                hero_l19_set_state(0x8D, 1);
            }
        }
        break;
    case 0x94:                                      /* switch 1 */
        if (((*(s32*)&D_L19_001B0040) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09166667f;
            hero_approach_velocity(0.0069444445f);
                    hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.005f);
            break;
        }
        break;
    case 0x8F:                                      /* switch 1 */
        if (((*(s32*)&D_L19_001B0040) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
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
        if (((*(s32*)&D_L19_001B0040) == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            hero_resolve_stick_direction(0.09583334f, 0);
            hero_update_held_grab();
            if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                hero_update_turn_from_anim();
            } else {
                ((Hero *)g_hero_state)->f[0x1458/4] = (f32) ((Hero *)g_hero_state)->f[0x98/4];
                qcopy(&((Hero *)g_hero_state)->q[0x1440/16], &((Hero *)g_hero_state)->q[0x0/16]);
                scalar126 = 0.10762865f;
                scalar118 = 0.033f;
                if (((Hero *)g_hero_state)->b[0x40F] != 0) {
                    scalar126 = 0.13671748f;
                    scalar118 = 0.037f;
                }
                hero_steer_heading(0, scalar118, 0.15f, scalar126);
            }
            hero_approach_speed(0.005f, 0.0055555557f);
            if (((Hero *)g_hero_state)->f[0x174/4] < 0.011666667f) {
                ((Hero *)g_hero_state)->b[0x40C] = 1U;
                if ((math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
                    ((Hero *)g_hero_state)->b[0x40F] = 1U;
                }
            }
            scalar66 = ReadPadFloatHistory(0);
            if ((FastDiffRots(scalar66, ReadPadFloatHistory(2)) > 2.617994f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.8f)) {
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
                    scalar158 = 0.09583334f - (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) * 0.02122066f);
                    if (scalar158 < 0.0f) {
                        scalar158 = 0.0f;
                    }
                    if (scalar158 < ((Hero *)g_hero_state)->f[0x1B0/4]) {
                        ((Hero *)g_hero_state)->f[0x1B0/4] = scalar158;
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
        if ((D_L19_001B0040 == 0) && (((Hero *)g_hero_state)->u[0x2294/4] != 0x6F)) {
            scalar38 = vec_length_xy((s32)&((Hero *)g_hero_state)->b[0xF0]);
            if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
                scalar38 = scalar38 * 0.99f;
            } else {
                scalar38 = scalar38 * 0.92f;
            }
            func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), scalar38);
            ptr49 = ((void*)(g_hero_state + 0xF0)) - 0xF0;
            M2C_FIELD(ptr49, s32* , 0xF8) = 0;
            if (M2C_FIELD(ptr49, s16* , 0x34E) != 0) {
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
    if (frame_int114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (frame_int118 != M2C_FIELD(ptr15, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}

