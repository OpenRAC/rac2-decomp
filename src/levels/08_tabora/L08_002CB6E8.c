#include "names.h"
/* func_L08_002CB6E8 (Tabora): the hero's per-frame state handler, a 147-way switch on the
   state at 0x2294 over 40 bodies (25416 bytes, level 8 only).  One function: one prologue,
   one return.  It is func_L20_002CD928's state machine with 23 of that level's bodies
   (the ones the jump table sends to the common tail here) left out; the C was derived from
   func_L20_002CD928's by the jump tables.  Level 4's func_L04_002E04A8 is the same
   function again (identical opcodes).

   The unit's flags (config/cflags.txt) are the ones func_L20_002CD928 needs, and each is
   needed by retail's code here too:
   -ffast-math      max.s;
   -g               the line labels that put the nop pairs before the div.s;
   -frac2-zero-ti-por           the por+sq clears of 0($sp);
   -frac2-keep-block-order and  no Cygnus block counting before cse;
   -frac2-no-null-pointer-checks
   (the quadword clears' zero in $a0 is the compiler's one-GPR TImode reload);
   -frac2-hazard-labels         branch targets on the mtc1 hazard nops.
   See docs/build/compiler-notes.md for each option.

   Stack: retail keeps the 0x20-byte vector at 0x20/0x40/0x30 and the matrix at 0x80 in
   case 0x2B, so that case uses v20, v40, v30 and m80 (v70 only reserves the 0x70 slot). */


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
extern u8 g_sound_state[];
extern char g_hero_state[];
extern char D_00189F10[];
extern char g_progress_statistics[];
extern u8 D_0018CF10[];
extern u32 D_001A7390 MACRO_ADDR;
extern s32 g_current_map_index MACRO_ADDR;
extern u8 D_001A7B08[0x40] MACRO_ADDR;
extern u8 D_001A7B2A MACRO_ADDR;
extern f32 D_L08_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L08_001A8FF0 MACRO_ADDR;
extern u8 D_L08_001ACF28[];
extern s32 D_L08_001B2508 MACRO_ADDR;
extern s32 D_L08_001B3170 MACRO_ADDR;
extern s32 D_L08_001B3178 MACRO_ADDR;
extern u8 D_L08_001B99C0[];
extern u8 D_L08_001B9B18[];
extern u8 D_L08_001B9D88[];
extern u8 D_L08_001C3FC0[];
extern u8 D_L08_00266590[];
extern Rec2C D_L08_00268110[];
extern u8 D_L08_00268490[];
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
extern s32 CreateMoby(s32);
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
extern void hero_shrink_vector_by_amount(f32);
extern void hero_steer_reference_point(void);
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
extern void vec_add_offset(s32, s32, f32, f32, f32);
extern s32 math_update_angle_and_blend(s32, s32, s32, f32);
extern f32 ReadPadFloatHistory(s32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern s32 hero_get_weapon_animation_id(s32);
extern void ClipHeroVelocityAgainstWall(s32);
/* Runs the hero's state handler each frame: walking, jumping, gliding and the other player actions. */
void hero_l08_update_state_machine(void) {
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
    f32 v70[4] __attribute__((aligned(16)));
    f32 m80[16] __attribute__((aligned(16)));
    f32 vC0[4] __attribute__((aligned(16)));
    f32 vD0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* varV0N3U2;
    void* varS1N5U2;
    f32 varF12N16U2;
    void* varA1N5U2;
    s32 varA0N2U2;
    void* varS0N3U2;
    s32 varV0N8U2;
    s32 varV1N4U2;
    void* varA0N13U2;
    s32 varA0N2U3;
    void* varS0N3U3;
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
    f32 tmpF0;
    f32 tmpF0N10;
    f32 tmpF0N11;
    f32 tmpF0N12;
    f32 tmpF0N13;
    f32 tmpF0N14;
    f32 tmpF0N15;
    f32 tmpF0N16;
    f32 tmpF0N17;
    f32 tmpF0N18;
    f32 tmpF0N19;
    f32 tmpF0N20;
    f32 tmpF0N21;
    f32 tmpF0N22;
    f32 tmpF0N23;
    f32 tmpF0N24;
    f32 tmpF0N25;
    f32 tmpF0N26;
    f32 tmpF0N27;
    f32 tmpF0N28;
    f32 tmpF0N29;
    f32 tmpF0N2;
    f32 tmpF0N30;
    f32 tmpF0N3;
    f32 tmpF0N4;
    f32 tmpF0N5;
    f32 tmpF0N6;
    f32 tmpF0N7;
    f32 tmpF0N8;
    f32 tmpF0N9;
    f32 tmpF12;
    f32 tmpF12N2;
    f32 tmpF12N3;
    f32 tmpF12N4;
    f32 tmpF12N5;
    f32 tmpF12N6;
    f32 tmpF12N7;
    f32 tmpF1;
    f32 tmpF1N10;
    f32 tmpF1N11;
    f32 tmpF1N12;
    f32 tmpF1N13;
    f32 tmpF1N14;
    f32 tmpF1N15;
    f32 tmpF1N16;
    f32 tmpF1N17;
    f32 tmpF1N2;
    f32 tmpF1N3;
    f32 tmpF1N4;
    f32 tmpF1N5;
    f32 tmpF1N6;
    f32 tmpF1N7;
    f32 tmpF1N8;
    f32 tmpF1N9;
    f32 tmpF20;
    f32 tmpF20N10;
    f32 tmpF20N11;
    f32 tmpF20N12;
    f32 tmpF20N13;
    f32 tmpF20N14;
    f32 tmpF20N15;
    f32 tmpF20N16;
    f32 tmpF20N17;
    f32 tmpF20N18;
    f32 tmpF20N19;
    f32 tmpF20N2;
    f32 tmpF20N3;
    f32 tmpF20N4;
    f32 tmpF20N5;
    f32 tmpF20N6;
    f32 tmpF20N7;
    f32 tmpF20N8;
    f32 tmpF20N9;
    f32 tmpF21;
    f32 tmpF21N2;
    f32 tmpF21N3;
    f32 tmpF22;
    f32 tmpF22N2;
    f32 tmpF22N3;
    f32 tmpF24;
    f32 tmpF2;
    f32 tmpF2N2;
    f32 tmpF2N3;
    f32 tmpF2N4;
    f32 tmpF2N5;
    f32 tmpF2N6;
    f32 tmpF2N7;
    f32 tmpF3;
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
    s16 tmpA2N5;
    s32 tmpV0N4;
    s16 tmpV0N8;
    s32 tmpV1N10;
    s32 tmpV1N9;
    s32 tmpA0N21;
    s32 tmpA0N3;
    s32 tmpA0N5;
    s32 tmpA0N7;
    s32 tmpA0N8;
    s32 tmpA0N9;
    s32 tmpA1N3;
    s32 tmpA1N4;
    s32 tmpA1N5;
    s32 tmpA1N7;
    s32 tmpA1N8;
    s32 tmpA2;
    s32 tmpA2N2;
    s32 tmpA2N3;
    s32 tmpA2N4;
    s32 tmpS0N5;
    s32 tmpS0N9;
    s32 tmpS7;
    s32 tmpV0;
    s32 tmpV0N12;
    s32 tmpV0N13;
    s32 tmpV0N14;
    s32 tmpV0N15;
    s32 tmpV0N16;
    s32 tmpV0N17;
    s32 tmpV0N2;
    s32 tmpV1N12;
    s32 tmpV1N14;
    s32 tmpV1N16;
    s32 tmpV1N18;
    s32 tmpV1N20;
    s32 tmpV1N21;
    s32 tmpV1N22;
    s32 tmpV1N23;
    s32 tmpV1N24;
    s32 tmpV1N26;
    s32 tmpV1N34;
    s32 tmpV1N35;
    s32 tmpV1N4;
    s32 tmpV1N5;
    s32 tmpV1N6;
    s32 tmpV1N7;
    s32 tmpV1N8;
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
    u16 tmpV0N3;
    u16 tmpV1N11;
    u16 tmpV1N2;
    u32 tmpA0;
    u32 tmpV1;
    u32 tmpV1N13;
    u32 tmpV1N27;
    u32 tmpV1N28;
    u32 tmpV1N29;
    u32 tmpV1N30;
    u32 tmpV1N31;
    u32 tmpV1N33;
    u32 tmpV1N36;
    u32 tmpV1N3;
    u32 varA1N3;
    u8 tmpA0N14;
    u8 tmpA0N2;
    u8 tmpV1N25;
    u8 varA0N6;
    void* tmpA0N10;
    void* tmpA0N11;
    void* tmpA0N12;
    void* tmpA0N13;
    void* tmpA0N15;
    void* tmpA0N16;
    void* tmpA0N17;
    void* tmpA0N4;
    void* tmpA0N6;
    void* tmpA1;
    void* tmpA1N2;
    void* tmpA1N6;
    void* tmpFp;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* tmpS0;
    void* tmpS0N2;
    void* tmpS0N3;
    void* tmpS0N4;
    void* tmpS0N6;
    void* tmpS0N7;
    void* tmpS0N8;
    void* tmpS1;
    void* tmpS1N2;
    void* tmpS1N3;
    void* tmpS1N4;
    void* tmpS1N5;
    void* tmpS1N6;
    void* tmpS1N7;
    void* tmpS1N8;
    void* tmpS2;
    void* tmpS2N2;
    void* tmpS2N3;
    void* tmpS2N4;
    void* tmpS2N5;
    void* tmpS4;
    void* tmpS4N2;
    void* tmpS5;
    void* tmpV0N10;
    void* tmpV0N5;
    void* tmpV0N6;
    void* tmpV0N7;
    void* tmpV0N9;
    void* tmpV1N15;
    void* tmpV1N17;
    void* tmpV1N32;
    void* tmpV1N37;
    void* tmpV1N38;
    void* tmpV1N39;
    void* varA0N13;
    void* varA0N7;
    void* varA1N5;
    void* varS0N3;
    void* varS1N5;
    void* varV0N3;

    stack114 = ((Hero *)g_hero_state)->i[0x2298/4];
    tmpFp = ((Hero *)g_hero_state)->ptr[0x2290/4];
    stack118 = (s32) M2C_FIELD(tmpFp, u8* , 0x43);
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
            hero_build_move_impulse(0.5f, 0.033333335f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
        hero_resolve_stick_direction(1.0f, 0);
        tmpV1 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((tmpV1 == 1) || (tmpV1 == 0x1D)) {
            if (((Hero *)g_hero_state)->b[0x22B5] != 0) {
                (*(TI128*)v0) = 0;
                v0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)g_hero_state) + 0x190), (s32)((TI128*)v0), (s32)&D_L08_001B9B18[0x218]);
                ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)D_L08_001B9B18)->f[0];
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
            if ((((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f) || (tmpA0N2 = M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43), (tmpA0N2 == 0xE)) || (tmpA0N2 == 0xF)) {
                if (((Hero *)g_hero_state)->u[0x2294/4] == 4) {
                    hero_steer_heading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) > 0.0058177654f) {
                    tmpA0N3 = ((Hero *)g_hero_state)->f[0x1A4/4] < 0.0f;
                    tmpA0N3 += 0xE;
                    if (M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x43) != tmpA0N3) {
                        set_hero_animation(tmpA0N3, 0, 5.0f);
                    }
                    tmpF0 = math_fabs(((Hero *)g_hero_state)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)g_hero_state)->f[0xC20/4] = tmpF0;
                    if (tmpF0 < 0.55f) {
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
            tmpV1N3 = ((Hero *)g_hero_state)->u[0x2294/4];
            ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
            if (tmpV1N3 == 3) {
                varF12 = ((Hero *)g_hero_state)->f[0x17C/4] + 1.0f;
                if (varF12 > 1.0f) {
                    varF12 = 1.0f;
                }
                tmpA0N4 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                varF20 = varF12 * 0.0075000003f;
                ((Hero *)g_hero_state)->f[0x24AC/4] = varF20;
                if (M2C_FIELD(tmpA0N4, u8* , 0x42) == M2C_FIELD(tmpA0N4, u8* , 0x43)) {
                    varF1 = ((Hero *)g_hero_state)->f[0x174/4] / varF20;
                    if ((varF1 > 5.0f) && ((f32) M2C_FIELD(tmpA0N4, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, varF1, 0.5f, -1.0f);
                        if (((Hero *)g_hero_state)->f[0xC20/4] > 1.1f) {
                            ((Hero *)g_hero_state)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)g_hero_state)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)g_hero_state)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (tmpV1N3 == 4) {
                varF20 = 0.0075000003f;
                if (((Hero *)g_hero_state)->b[0x1492] != 0) {
                    varF20 = 0.00047222225f;
                }
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
    case 0x7C:
        hero7C = (void*)g_hero_state;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            tmpV0 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = tmpV0;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)tmpV0 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)tmpV0 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(tmpV0, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            tmpV1N4 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(tmpV1N4, u16* , 0x34) = (u16) (M2C_FIELD(tmpV1N4, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        tmpV1N6 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(tmpV1N6, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(tmpV1N6, u8* , 0x23) = 0x80U;
        }
        tmpA0N5 = ((Hero *)hero7C)->i[0x7A4/4];
        tmpA1 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)tmpA0N5 + 0x10, (u8 *)tmpA1 + 0x10);
        qcopy((u8 *)tmpA0N5 + 0xF0, (u8 *)tmpA1 + 0xF0);
        func_002A0F48(tmpA0N5);
        }
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.92f);
        hero_update_height_offset();
        break;
    case 0x32:
    case 0x33:
    case 0x34:
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x47) {
                (*(u16*)&D_0018CF10) = 0xFFFF;
            }
            snd_update_slot_object(5, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xF);
            queue_copy_record_by_index(0x16);
        } else {
            tmpA2 = ((Hero *)g_hero_state)->i[0x2440/4];
            if (tmpA2 != -1) {
                tmpA0N6 = (tmpA2 * 0x70) + (s32)g_sound_state;
                if (M2C_FIELD(tmpA0N6, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) {
                    if (M2C_FIELD(tmpA0N6, u8* , 0x74) != 0) {
                        snd_stop_voice(tmpA2);
                    }
                }
            }
            ((Hero *)g_hero_state)->i[0x2440/4] = -1;
        }
        if (((Hero *)g_hero_state)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)g_hero_state) + 0xA4A));
            tmpA0N7 = (s32) ((u16) ((Hero *)g_hero_state)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects((tmpA0N7 >= 9) ? 8 : tmpA0N7, 0, 0);
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x32) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            tmpF1N2 = ((Hero *)g_hero_state)->f[0xC38/4];
            if (tmpF1N2 > 0.0f) {
                if (tmpF1N2 < 10.0f) {
                    EmitHeroRandomizedMotionEffects(4, 1, 0);
                }
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                tmpV1N7 = ((Hero *)g_hero_state)->i[0x1B8/4];
                if (tmpV1N7 < 0xF) {
                    EmitHeroRandomizedMotionEffects(((s32) (0x14 - tmpV1N7) / 3) + 1, 1, 0);
                }
            }
        }
        tmpV1N8 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (tmpV1N8 == 1) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == tmpV1N8) {
                part_emit_hero_dust_and_debris(3, 0x10, 0);
                if (D_L08_001B3170 != 0) {
                    RippleDisturb(D_L08_001B3170, D_L08_001B3178, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)g_hero_state)->h[0xA4A/2] = 0x46;
            }
            tmpV0N2 = ((Hero *)g_hero_state)->i[0xA20/4] + 1;
            ((Hero *)g_hero_state)->i[0xA20/4] = tmpV0N2;
            if (tmpV0N2 >= 0x29) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.011635531f;
        stick_turn += (((Hero *)g_pad_state)->f[0x12C/4] > ((Hero *)g_pad_state)->f[0x128/4] ? ((Hero *)g_pad_state)->f[0x12C/4] : ((Hero *)g_pad_state)->f[0x128/4]) * 0.008726647f;
        varF12N4 = 0.0f;
        k02 = 0.2f;
        if ((((((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            varF12N6 = ((Hero *)g_pad_state)->f[0x12C/4] * 1.5f;
            if (varF12N6 > 1.0f) {
                varF12N6 = 1.0f;
            }
            if (varF12N6 < k02) {
                varF12N6 = k02;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                tmpV1N9 = ((Hero *)g_hero_state)->uh[0xA42/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
                varF12N6 = ((f32) (s16) tmpV1N9 * 0.025f) + 0.5f;
                ((Hero *)g_hero_state)->uh[0xA42/2] = (u16) tmpV1N9;
                if (varF12N6 > 1.0f) {
                    varF12N6 = 1.0f;
                }
            }
            if ((((Hero *)g_hero_state)->i[0x2298/4] == 1) && (varF12N6 < 0.35f)) {
                varF12N6 = 0.35f;
            }
            varF12N4 = varF12N6 * 1.361357f;
        } else if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            varF12N5 = ((Hero *)g_pad_state)->f[0x128/4] * 1.5f;
            if (varF12N5 > 1.0f) {
                varF12N5 = 1.0f;
            }
            if (varF12N5 < k02) {
                varF12N5 = k02;
            }
            if (((Hero *)g_pad_state)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)g_hero_state)->uh[0xA40/2] + 1;
                ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
                ((Hero *)g_hero_state)->h[0xA40/2] = cntA40;
                varF12N5 = ((f32) (s16) cntA40 * 0.025f) + 0.5f;
                if (varF12N5 > 1.0f) {
                    varF12N5 = 1.0f;
                }
            }
            if ((f32) ((Hero *)g_hero_state)->i[0x24C0/4] < 1500.0f) {
                varF12N5 = 1.0f;
            }
            varF12N4 = varF12N5 * -1.361357f;
        } else {
            ((Hero *)g_hero_state)->uh[0xA40/2] = 0U;
            ((Hero *)g_hero_state)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40) {
            ((Hero *)g_hero_state)->uh[0xA4E/2] = (u16) (((Hero *)g_hero_state)->uh[0xA4E/2] + 1);
            if (((Hero *)g_pad_state)->f[0x128/4] > 0.75f) {
                tmpV1N10 = ((Hero *)g_hero_state)->uh[0xA4C/2] + 1;
                ((Hero *)g_hero_state)->h[0xA4C/2] = tmpV1N10;
                if ((s16) tmpV1N10 >= 0x5B) {
                    tmpV1N11 = ((Hero *)g_progress_statistics)->uh[0x84/2];
                    if (tmpV1N11 <= 0xFFFEU) {
                        ((Hero *)g_progress_statistics)->uh[0x84/2] = (u16) (tmpV1N11 + 1);
                    }
                }
                tmpV1N12 = (*(s32*)&D_001A7390);
                if ((u32) ((Hero *)g_progress_statistics)->u[0x88/4] < (u32) tmpV1N12) {
                    ((Hero *)g_progress_statistics)->u[0x88/4] = (u32) tmpV1N12;
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
            if ((D_L08_001B2508 - hp32->i[0xA54/4]) < 0x46) {
                hp32->i[0xA50/4]++;
            }
            hp32->i[0xA54/4] = D_L08_001B2508;
        }
        if ((s16) ((Hero *)g_hero_state)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x80) {
            ((Hero *)g_hero_state)->i[0xA50/4] = 0;
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x33) {
            varF12N4 = 0.0f;
        }
        tmpF20 = ((Hero *)g_hero_state)->f[0x94/4];
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), varF12N4, (s32) (((void*)g_hero_state) + 0xA28), 0.015f, 0.2f, stick_turn, 0);
        tmpF22 = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x94/4], tmpF20);
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
        varF2 = ((Hero *)g_hero_state)->f[0x24B8/4];
        if (((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xC0) || (((Hero *)g_hero_state)->i[0x2298/4] == 1)) {
            if (varF2 < 1.0f) {
                varF2 = 1.0f;
            }
        }
        if (((Hero *)g_hero_state)->f[0x24B8/4] > 0.15f) {
            varF0N2 = 0.35f;
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
                varF0N2 = 0.4f;
            }
            if (varF2 < varF0N2) {
                varF2 = varF0N2;
            }
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0xA)) {
            ((Hero *)g_hero_state)->f[0x1B0/4] = (f32) (((Hero *)g_hero_state)->f[0x1B0/4] * varF2);
        }
        if (math_fast_float_d((s32)(g_hero_state + 0xA30)) != 0) {
            heroA30 = (void*)g_hero_state;
            moby_transform_joint_to_world((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.033333335f;
            part_spawn_bubble((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            if ((f32) math_random_int_below(0x64) < 40.0f) {
                varA0N4 = 4;
                varA1N2 = 0xB;
            } else {
                varA0N4 = 0x28;
                varA1N2 = 0x5A;
            }
            ((Hero *)heroA30)->i[0xA30/4] = math_random_int_range(varA0N4, varA1N2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)g_hero_state) + 0xA38)) != 0) {
                tmpS4 = ((Hero *)g_hero_state)->ptr[0x1310/4];
                if (tmpS4 != 0) {
                    if (M2C_FIELD(tmpS4, s16* , 0xAA) == 0x261) {
                        for (varS1 = 0; varS1 < 4; varS1++) {
                            moby_transform_joint_to_world((s32) tmpS4, varS1 % 2, (s32)((TI128*)v0));
                            (*(TI128*)v20) = 0;
                            v20[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)g_hero_state)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
                            v0[0] += math_random_float_range(0.0f, 0.03f);
                            v0[1] += math_random_float_range(0.0f, 0.03f);
                            v0[2] += math_random_float_range(0.0f, 0.03f);
                            qcopy(v10, &((Hero *)g_hero_state)->q[0x110/16]);
                            vec_add_offset((s32) ((TI128*)v10), (s32) ((TI128*)v10), -0.012500001f, ((Hero *)g_hero_state)->f[0x98/4], ((Hero *)g_hero_state)->f[0x94/4]);
                            ((Hero *)g_hero_state)->h[0xA38/2] = FloatToInt((0.116666675f - ((Hero *)g_hero_state)->f[0x1B4/4]) * 42.85714f);
                            part_spawn_bubble((s32)((TI128*)v0), (s32) ((TI128*)v10), math_random_float_range(6300.0f, 9450.0f), -1.0f);
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
        tmpF21 = FastAddRotations(-((Hero *)g_hero_state)->f[0x94/4], 0.0f);
        tmpV1N13 = ((Hero *)g_hero_state)->u[0x2294/4];
        if (tmpV1N13 == 0x34) {
            vec_build_spherical_offset((s32) (((void*)g_hero_state) + 0xF0), ((Hero *)g_hero_state)->f[0x1B4/4], ((Hero *)g_hero_state)->f[0x98/4], tmpF21);
        } else if (tmpV1N13 == 0x32) {
            varF12N7 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)D_L08_00268490, 0x1E) * 5.0f;
            if ((((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xF) && (varF12N7 < 0.075f)) {
                varF12N7 = 0.075f;
            }
            vec_build_spherical_offset((s32)(g_hero_state + 0xF0), varF12N7, ((Hero *)g_hero_state)->f[0x98/4], tmpF21);
        } else if (tmpV1N13 == 0x33) {
            stackE0 = FastVecLength((s32) (((void*)g_hero_state) + 0x160));
            if (((Hero *)g_hero_state)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &stackE0, 0.0f, 0.0022222223f);
            } else {
                ApproachValue((s32) &stackE0, 0.0f, 0.0011111111f);
            }
            vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), stackE0);
            qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        }
        ClipHeroVelocityAgainstWall(0);
        tmpF21N2 = ((Hero *)g_hero_state)->f[0xA2C/4] * math_fast_sin_or_cos_a(tmpF21) * -7.0f;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), tmpF21N2, (s32) (((void*)g_hero_state) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        cam_set_limits_second(0.009f, 0.22f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        tmpF2 = tmpF22 * 47.0f;
        ((Hero *)D_L08_00266590)->f[0x114/4] = tmpF2;
        ((Hero *)D_L08_00266590)->f[0x118/4] = (f32) (tmpF21N2 * 1.5f);
        ((Hero *)D_L08_00266590)->f[0x110/4] = (f32) (tmpF21N2 * 1.4f);
        if (tmpF2 > 0.8726647f) {
            ((Hero *)D_L08_00266590)->f[0x114/4] = 0.8726647f;
        } else if (tmpF2 < -0.8726647f) {
            ((Hero *)D_L08_00266590)->f[0x114/4] = -0.8726647f;
        }
        tmpF1N3 = tmpF22 * 40.0f;
        tmpF0N2 = tmpF21N2 * 1.1f;
        ((Hero *)D_L08_00266590)->f[0x364/4] = 0.03f;
        ((Hero *)D_L08_00266590)->f[0x368/4] = 0.22f;
        ((Hero *)D_L08_00266590)->f[0x324/4] = tmpF1N3;
        ((Hero *)D_L08_00266590)->f[0x328/4] = tmpF0N2;
        ((Hero *)D_L08_00266590)->f[0x414/4] = 0.03f;
        ((Hero *)D_L08_00266590)->f[0x418/4] = 0.22f;
        ((Hero *)D_L08_00266590)->f[0x3D4/4] = tmpF1N3;
        ((Hero *)D_L08_00266590)->f[0x3D8/4] = tmpF0N2;
        break;
    case 0x73:
        tmpA0N8 = 0xA - ((s32) ((Hero *)g_hero_state)->i[0x1B8/4] / 3);
        tmpS1 = ((void*)g_hero_state) + 0xF0;
        EmitHeroRandomizedMotionEffects((tmpA0N8 >= 9) ? 8 : tmpA0N8, 0, 0);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) tmpS1, (s32) tmpS1, vec_length_xy((s32) tmpS1) * 0.92f);
        ClipHeroVelocityAgainstWall(0);
        break;
    case 0x72:
        part_spawn_jittered_after_delay(0xF, 0x1E);
        ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), vec_length_xy((s32)(g_hero_state + 0xF0)) * 0.92f);
        ClipHeroVelocityAgainstWall(0);
        hero_update_height_offset();
        break;
    case 0x67:
    case 0x7F:
        stackE4 = FastVecLength((s32)(g_hero_state + 0x160));
        ApproachValue((s32) &stackE4, 0.0f, 0.0011111111f);
        vec_scale_to_length((s32)(g_hero_state + 0x160), (s32)(g_hero_state + 0x160), stackE4);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x160/16]);
        if (math_fast_float_d((s32) (((void*)(g_hero_state + 0x160)) + 0x8D0)) == 2) {
            tmpS2 = ((void*)(g_hero_state + 0x160)) - 0x160;
            moby_transform_joint_to_world(M2C_FIELD(tmpS2, s32* , 0x2290), 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), M2C_FIELD(tmpS2, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)g_hero_state)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.033333335f;
            part_spawn_bubble((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            tmpV1N14 = M2C_FIELD(tmpS2, s32* , 0x1B8);
            if (tmpV1N14 < 0x28) {
                lim67 = 5;
                varV0N2 = math_random_int_range(2, lim67) + ((s32) M2C_FIELD(tmpS2, s32* , 0x1B8) / lim67);
                goto block_224;
            }
            if (tmpV1N14 >= 0x47) {
                varV0N2 = math_random_int_range(0xA, 0x14);
block_224:
                M2C_FIELD(tmpS2, s32* , 0xA30) = varV0N2;
            }
        }
        if (((Hero *)g_hero_state)->f[0xA3C/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xA3C/4] = 0.0f;
        }
        ApproachValue((s32) (((void*)g_hero_state) + 0xA3C), -0.025000002f, 0.00041666668f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) ((Hero *)g_hero_state)->f[0xA3C/4];
        break;
    case 0x35:
    case 0x36:
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
            tmpA0N9 = ((Hero *)g_hero_state)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects((tmpA0N9 >= 7) ? 6 : tmpA0N9, 0, 0);
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
            tmpF20N2 = ((Hero *)g_hero_state)->f[0x1B4/4] * math_blend_table_entries_by_clock((s32)D_L08_00268490, 0x1E) * 5.5f;
            ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * tmpF20N2);
            tmpF0N3 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * tmpF20N2;
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            ((Hero *)g_hero_state)->f[0xF4/4] = tmpF0N3;
        } else {
            ((Hero *)g_hero_state)->f[0x1B4/4] = 0.0f;
            vec_clear_128((s32)(g_hero_state + 0xF0));
        }
        if ((((Hero *)g_hero_state)->u[0x2294/4] == 0x35) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0)) {
            tmpF1N4 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((tmpF1N4 > 0.0f) && (tmpF1N4 < 10.0f)) {
                EmitHeroRandomizedMotionEffects(4, 1, 0);
            }
        }
        hero_shrink_vector_by_amount(0.0011666666f);
        ClipHeroVelocityAgainstWall(0);
        hero_update_height_offset();
        break;
    case 0x85:
        tmpA1N2 = ((Hero *)g_hero_state)->ptr[0x1830/4];
        qcopy(&((Hero *)g_hero_state)->q[0x80/16], (u8 *)tmpA1N2 + 0x10);
        qcopy(&((Hero *)g_hero_state)->q[0x90/16], (u8 *)tmpA1N2 + 0xF0);
        break;
    case 0x2F:
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
            tmpV1N15 = ((Hero *)g_hero_state)->ptr[0x2290/4];
            if ((M2C_FIELD(tmpV1N15, u8* , 0x60) & 2) && (M2C_FIELD(tmpV1N15, u8* , 0x42) == 0x36)) {
                set_hero_animation(hero_get_weapon_animation_id(0), 0, 5.0f);
            }
        }
        break;
    case 0x8A:
    case 0x8B:
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
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(varV0N3, f32* , 0x10) - M2C_FIELD(tmpFp, f32* , 0x10), M2C_FIELD(varV0N3, f32* , 0x14) - M2C_FIELD(tmpFp, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x23:
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
        varV0N3U2 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
        if (varV0N3U2 != 0) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(M2C_FIELD(varV0N3U2, f32* , 0x10) - M2C_FIELD(tmpFp, f32* , 0x10), M2C_FIELD(varV0N3U2, f32* , 0x14) - M2C_FIELD(tmpFp, f32* , 0x14));
            hero_steer_heading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:
        qcopy(v0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        tmpF0N4 = fast_vec_dist((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)v0));
        ((Hero *)g_hero_state)->f[0xAB0/4] = tmpF0N4;
        ((Hero *)g_hero_state)->f[0xAAC/4] = 60.0f;
        if (((Hero *)g_hero_state)->f[0xAA0/4] > 0.0f) {
            ((Hero *)g_hero_state)->f[0xAAC/4] = (f32) (tmpF0N4 / ((Hero *)g_hero_state)->f[0x170/4]);
        }
        tmpV1N16 = ((Hero *)g_hero_state)->i[0x2298/4];
        if (tmpV1N16 == 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0xAA0), 0.45000002f, 0.022222223f);
            tmpV0N5 = ((Hero *)g_hero_state)->ptr[0xAA4/4];
            varF20N2 = mat_fast_helper_a(M2C_FIELD(tmpV0N5, f32* , 0x10) - M2C_FIELD(tmpFp, f32* , 0x10), M2C_FIELD(tmpV0N5, f32* , 0x14) - M2C_FIELD(tmpFp, f32* , 0x14));
            if (((Hero *)g_hero_state)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)g_hero_state)->f[0x98/4], varF20N2) > 1.5707964f) {
                    varF20N2 = FastAddRotations(varF20N2, 3.1415927f);
                }
            }
            ((Hero *)g_hero_state)->f[0x1A0/4] = varF20N2;
            hero_steer_heading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (tmpV1N16 == 1) {
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
            turn24 = FastAddRotations(-mat_fast_helper_a(vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), (s32)((TI128*)v0)), v0[2] - ((Hero *)g_hero_state)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)g_hero_state) + 0x94), 0, turn24, 0.10762865f);
        }
        v20[0] = math_fast_sin_or_cos_a(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        tmpF0N5 = math_fast_sin_or_cos_b(FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f)) * -0.57f;
        v20[2] = 0;
        v20[1] = tmpF0N5;
        FastVecAdd((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)g_hero_state) + 0x80));
        FastVecSub((s32) ((TI128*)v10), (s32) (((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)v20));
        vec_scale_to_length((s32) (((void*)g_hero_state) + 0xF0), (s32) ((TI128*)v10), ((Hero *)g_hero_state)->f[0xAA0/4]);
        tmpF0N6 = ((Hero *)g_hero_state)->f[0xAAC/4];
        if (tmpF0N6 < 30.0f) {
            ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - ((30.0f - tmpF0N6) * 0.008055556f));
        }
        break;
    case 0x25:
        ApproachValue((s32)(g_hero_state + 0xABC), ((Hero *)g_hero_state)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)g_hero_state)->q[0xF0/16], &((Hero *)g_hero_state)->q[0x110/16]);
        FastVecScale((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.9f);
        ((Hero *)g_hero_state)->f[0xF8/4] = (f32) (((Hero *)g_hero_state)->f[0xF8/4] - 0.004166667f);
        qcopy(v0, (u8 *)((Hero *)g_hero_state)->ptr[0xAA4/4] + 0x10);
        ((Hero *)g_hero_state)->f[0xAB0/4] = fast_vec_dist((s32)(g_hero_state + 0x80), (s32)((TI128*)v0));
        FastVecAdd((s32) ((TI128*)v10), (s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0xF0));
        FastVecSub((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32)((TI128*)v0));
        vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), ((Hero *)g_hero_state)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v30));
        FastVecSub((s32)(g_hero_state + 0xF0), (s32) ((TI128*)v20), (s32)(g_hero_state + 0x80));
        break;
    case 0x2B:
        if ((((Hero *)g_hero_state)->i[0xC28/4] & 2) && (M2C_FIELD(tmpFp, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)g_hero_state)->f[0xC20/4] = 0.3f;
        }
        tmpV1N17 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        tmpF24 = ((Hero *)g_hero_state)->f[0xF8/4];
        if (tmpV1N17 != 0) {
            tmpV0N6 = M2C_FIELD(tmpV1N17, void** , 0x68);
            if ((tmpV0N6 != 0) && (M2C_FIELD(tmpV0N6, s32* , 0x34) != 0)) {
                varF20N3 = M2C_FIELD(tmpV1N17, f32* , 0xF8);
                if (FastDiffRots(varF20N3, ((Hero *)g_hero_state)->f[0x98/4]) > 90.0f) {
                    varF20N3 = FastAddRotations(varF20N3, 3.1415927f);
                }
                math_approach_with_velocity((s32) (((void*)g_hero_state) + 0xAEC), varF20N3, (s32) (((void*)g_hero_state) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xAEC/4];
        hero_steer_heading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)v0), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) (((void*)g_hero_state) + 0x80));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        if (v0[2] < 0.23f) {
            v0[2] = 0.23f;
        }
        vec_clear_128((s32) ((TI128*)v20));
        v20[2] = ((Hero *)g_hero_state)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)v40), (s32) ((TI128*)v20));
        matrix_from_basis_rows((s32) ((TI128*)m80), (s32) ((TI128*)v40));
        transform_vector((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)m80));
        v10[0] = -mat_fast_helper_a(square_root((v0[0] * v0[0]) + (v0[2] * v0[2])), v0[1]);
        tmpF0N7 = mat_fast_helper_a(v0[2], v0[0]);
        v10[1] = tmpF0N7;
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x94), tmpF0N7, (s32) (((void*)g_hero_state) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        math_approach_with_velocity((s32) (((void*)g_hero_state) + 0x90), v10[0], (s32) (((void*)g_hero_state) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        varS7 = ((Hero *)g_hero_state)->f[0x88/4] < M2C_FIELD(((Hero *)g_hero_state)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
            if ((varS7 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x29) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.25f)) {
                hero_resolve_stick_direction(1.0f, 0);
                varF20N4 = ((Hero *)g_hero_state)->f[0x24B8/4] * 0.0035f;
                if (varF20N4 > 0.083333336f) {
                    varF20N4 = 0.083333336f;
                }
                v30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x1A0/4]) * varF20N4;
                tmpF0N8 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x1A0/4]) * varF20N4;
                tmpA0N10 = ((void*)g_hero_state) + 0xF0;
                (*(s32*)&v30[2]) = 0;
                v30[1] = tmpF0N8;
                FastVecAdd((s32) tmpA0N10, (s32) tmpA0N10, (s32) ((TI128*)v30));
            }
            if (((Hero *)g_hero_state)->h[0xADC/2] != 0) {
                tmpS2N2 = ((void*)g_hero_state) + 0x80;
                if ((vec_distance_xy((s32) tmpS2N2, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10)) < (((Hero *)g_hero_state)->f[0xAE0/4] * 1.57f)) || (((Hero *)g_hero_state)->f[0x31C/4] > 1.5f)) {
                    tmpS1N2 = ((void*)g_hero_state) + 0xF0;
                    hero_apply_mode_transform((s32) tmpS1N2, (s32) (((void*)g_hero_state) + 0x110), 0.011111111f);
                    if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (cam_get_view_space_height((s32) tmpS1N2) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)v30), (s32) tmpS2N2, (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
                        hero_apply_mode_transform((s32) tmpS1N2, (s32) tmpS1N2, 0.015833333f);
                    }
                }
                tmpF20N3 = FastVecLength((s32)(g_hero_state + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)v30), (s32)(g_hero_state + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), tmpF20N3);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)v30));
            }
        }
        tmpV0N7 = ((Hero *)g_hero_state)->ptr[0xAD4/4];
        if (tmpV0N7 != 0) {
            tmpS0 = M2C_FIELD(tmpV0N7, void** , 0x68);
            tmpS1N3 = ((void*)g_hero_state) + 0xF0;
            if (tmpS0 != 0) {
                tmpF0N9 = FastVecLength((s32) tmpS1N3);
                tmpF12 = M2C_FIELD(tmpS0, f32* , 0xC);
                stackF0 = tmpF0N9;
                if (tmpF12 < tmpF0N9) {
                    ApproachValue((s32) &stackF0, tmpF12, 0.004166667f);
                    vec_scale_to_length((s32) tmpS1N3, (s32) tmpS1N3, stackF0);
                }
            }
        }
        tmpF0N10 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -1.5707965f);
        tmpS5 = ((void*)g_hero_state) + 0x80;
        tmpS4N2 = ((void*)g_hero_state) + 0xF0;
        vD0[0] = math_fast_sin_or_cos_a(tmpF0N10) * 0.15f;
        tmpF0N11 = math_fast_sin_or_cos_b(tmpF0N10) * 0.15f;
        (*(s32*)&vD0[2]) = 0;
        vD0[1] = tmpF0N11;
        FastVecAdd((s32) &vD0[0], (s32) &vD0[0], (s32) tmpS5);
        FastVecAdd((s32) ((TI128*)v30), (s32) &vD0[0], (s32) tmpS4N2);
        FastVecSub((s32) ((TI128*)vC0), (s32) ((TI128*)v30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), ((Hero *)g_hero_state)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)v30), (s32) (((Hero *)g_hero_state)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vC0));
        FastVecSub((s32) tmpS4N2, (s32) ((TI128*)v30), (s32) &vD0[0]);
        tmpF20N4 = ((Hero *)g_hero_state)->f[0xAE4/4];
        math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0xAE4), (s32) (((void*)g_hero_state) + 0xAE8), ((Hero *)g_hero_state)->f[0xAE0/4], ((Hero *)g_hero_state)->f[0xB04/4], ((Hero *)g_hero_state)->f[0xB08/4], ((Hero *)g_hero_state)->f[0xB0C/4]);
        tmpF20N5 = ((Hero *)g_hero_state)->f[0xAE4/4] - tmpF20N4;
        if (((Hero *)g_hero_state)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vC0))) {
            vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), tmpF20N5);
            FastVecAdd((s32) tmpS5, (s32) tmpS5, (s32) ((TI128*)vC0));
        }
        if ((((Hero *)g_hero_state)->h[0xAFE/2] != 0) && (varS7 != 0)) {
            min2B = 0.23333335f;
            tmpF0N12 = vec_length_xy((s32) tmpS4N2);
            stackF4 = tmpF0N12;
            if (tmpF0N12 < min2B) {
                math_spring_float_to_goal((s32) &stackF4, (s32) (((void*)g_hero_state) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                v30[0] = math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0xAEC/4]) * ((Hero *)g_hero_state)->f[0xAF4/4];
                tmpF0N13 = math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0xAEC/4]);
                v30[2] = 0.0f;
                v30[1] = tmpF0N13 * ((Hero *)g_hero_state)->f[0xAF4/4];
                FastVecAdd((s32) tmpS4N2, (s32) tmpS4N2, (s32) ((TI128*)v30));
            }
        }
        if ((((Hero *)g_hero_state)->h[0xADC/2] != 0) && (((Hero *)g_hero_state)->h[0x34E/2] != 0) && (((tmpF24 < 0.0f) && (((Hero *)g_hero_state)->f[0xF8/4] > 0.0f)) || (((Hero *)g_hero_state)->h[0xAFC/2] != 0))) {
            ((Hero *)g_hero_state)->h[0xAFE/2] = 0;
            tmpF20N6 = square_root(((Hero *)g_hero_state)->f[0xAE0/4] / ((Hero *)g_hero_state)->f[0xAF0/4]) * 3.1415927f;
            tmpV0N8 = ((Hero *)g_hero_state)->h[0xAFC/2];
            if (tmpV0N8 != 0) {
                varV0N4 = tmpV0N8 == 1;
            } else {
                (*(TI128*)v30) = ((Hero *)g_hero_state)->q[0x110/16];
                varV0N4 = hero_get_speed_along_forward((s32) ((TI128*)v30)) > 0.0f;
            }
            if (varV0N4 != 0) {
                if (M2C_FIELD(tmpFp, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 1;
                } else {
                    tmpV0N9 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                    if (M2C_FIELD(tmpV0N9, u8* , 0x42) == M2C_FIELD(tmpV0N9, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, tmpF20N6, 0.5f, -1.0f);
                        ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(tmpFp, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)g_hero_state)->h[0xAFC/2] = 2;
            } else {
                tmpV0N10 = ((Hero *)g_hero_state)->ptr[0x2290/4];
                if (M2C_FIELD(tmpV0N10, u8* , 0x42) == M2C_FIELD(tmpV0N10, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, tmpF20N6, 0.5f, -1.0f);
                    ((Hero *)g_hero_state)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L08_00268110[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            tmpA1N3 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (tmpA1N3 != 0) {
                tmpF1N5 = vec_distance_xy((s32) (((void*)g_hero_state) + 0x80), tmpA1N3 + 0x10);
                varV1N2 = 0;
                if ((((Hero *)g_hero_state)->b[0x1496] != 0) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->b[0x1495] != 0)) {
                    varV1N2 = 1;
                }
                if (((tmpF1N5 > 2.0f) && (tmpF1N5 < 5.0f)) || (varV1N2 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
                }
                hero_approach_speed(0.0011111111f, 0.0011111111f);
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * ((Hero *)g_hero_state)->f[0x1B4/4]);
            } else {
                hero_approach_speed(0.00055555557f, 0.00055555557f);
                tmpA0N11 = ((void*)g_hero_state) + 0xF0;
                cam_set_view_space_vector_length((s32) tmpA0N11, (s32) tmpA0N11, ((Hero *)g_hero_state)->f[0x1B4/4]);
            }
        } else {
            varS1N2 = 0;
            if ((((Hero *)g_hero_state)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)g_hero_state)->b[0x149B] != 0) || (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f)) {
                varS1N2 = 1;
            }
            tmpA1N4 = ((Hero *)g_hero_state)->i[0xBE4/4];
            if (tmpA1N4 != 0) {
                FastVecSub((s32)((TI128*)v0), tmpA1N4 + 0x10, (s32) (((void*)g_hero_state) + 0x80));
                tmpF0N14 = cam_get_view_space_vector_length((s32)((TI128*)v0));
                if (((tmpF0N14 > 2.0f) && (tmpF0N14 < 5.0f)) || (varS1N2 != 0)) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = 0.075f;
                }
                hero_approach_speed(0.0069444445f, 0.0069444445f);
                vec_scale_to_length((s32) ((TI128*)v10), (s32)g_hero_state, ((Hero *)g_hero_state)->f[0x1B4/4]);
                cam_set_view_space_vector_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), 0.0f);
                FastVecAdd((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), (s32) ((TI128*)v10));
            } else {
                if ((varS1N2 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0x46)) {
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
        tmpF1N6 = ((Hero *)g_hero_state)->f[0x31C/4];
        varF21 = 0.12833333f;
        if (tmpF1N6 > 2.25f) {
            varF21 = 0.064166665f;
        } else if (tmpF1N6 > 1.8f) {
            varF21 = 0.08983333f;
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
            queue_copy_record_by_index(0x19);
            ((Hero *)g_hero_state)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L08_001B99C0)->f[0x180/4] = 0.1f;
                ((Hero *)D_L08_001B99C0)->i[0x188/4] = 0x1E;
                ((Hero *)g_hero_state)->h[0x224/2] = 0x23;
                ((Hero *)D_L08_001B99C0)->i[0x16C/4] = 0;
            }
        }
        tmpV1N18 = ((Hero *)g_hero_state)->i[0x1B8/4];
        lim3 = 0xE;
        if (tmpV1N18 < 9) {
            tmpS0N2 = ((void*)g_hero_state) + 0xF0;
            stackF8 = cam_get_view_space_height((s32) tmpS0N2);
            ApproachValue((s32) &stackF8, varF21, 0.041666668f);
            cam_set_view_space_height((s32) tmpS0N2, (s32) tmpS0N2, stackF8);
        } else if (tmpV1N18 > lim3) {
            tmpS1N4 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) tmpS1N4, (s32) tmpS1N4, 0.036111113f);
            if (cam_get_view_space_height((s32) tmpS1N4) < 0.0f) {
                ((Hero *)g_hero_state)->f[0xC00/4] = 1.0f;
            }
            varF20N5 = -0.6166667f;
            if (D_L08_001A8FF0 != 0) {
                varF20N5 = -1.1666667f;
            }
            if (cam_get_view_space_height((s32) tmpS1N4) < varF20N5) {
                cam_set_view_space_height((s32) tmpS1N4, (s32) tmpS1N4, varF20N5);
            }
        }
        break;
    case 0x15:
    case 0x83:
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L08_00268110[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        varA0N8 = (((Hero *)g_hero_state)->i[0x22A0/4] == 1) && (((Hero *)g_hero_state)->i[0x22A8/4] >= 0x15);
        if (varA0N8 == 0) {
            if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
                varS1N3 = 0;
                if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                    tmpS0N3 = ((void*)g_hero_state) + 0xBC0;
                    varF20N6 = hero_get_direction_angle_delta((s32) tmpS0N3, 0);
                    varF0N3 = hero_get_direction_angle_delta((s32) tmpS0N3, 1);
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
                varF21N2 = 0.041666668f;
                tmpF20N7 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&D_00138320) & 8) {
                    varF21N2 = 0.050000004f;
                }
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(tmpF20N7) * varF21N2));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(tmpF20N7) * varF21N2));
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
    case 0x13:
        if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (((Hero *)g_hero_state)->f[0xC38/4] < (f32) D_L08_00268110[((Hero *)g_hero_state)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)g_hero_state)->c[0x1239] = 2;
        }
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            hero_steer_reference_point();
            break;
        }
        tmpA1N5 = ((Hero *)g_hero_state)->i[0xBE4/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        tmpS2N3 = (((Hero *)g_hero_state)->h[0xBFC/2] * 0x2C) + (s32)D_L08_00268110;
        if ((tmpA1N5 != 0) && (((Hero *)g_hero_state)->i[0x1B8/4] < 4)) {
            tmpS1N5 = ((void*)g_hero_state) + 0x80;
            varF12N13 = vec_distance_xy(tmpA1N5 + 0x10, (s32) tmpS1N5);
            if ((*(s32*)&D_L08_001A8FF0) != 0) {
                varF12N13 = fast_vec_dist(((Hero *)g_hero_state)->i[0xBE4/4] + 0x10, (s32) tmpS1N5);
            }
            varF12N13 = varF12N13 - 0.5f;
            if (varF12N13 < 0.0f) {
                varF12N13 = 0.0f;
            }
            tmpV1N20 = M2C_FIELD(tmpS2N3, s32* , 4);
            if (tmpV1N20 == 0) {
                varF0N4 = 0.75f;
                varF21N3 = 0.8f;
                varF22 = 4.0f;
            } else if (tmpV1N20 == 1) {
                varF0N4 = 0.6f;
                varF21N3 = 1.7f;
                varF22 = 4.0f;
            } else {
                varF0N4 = 1.3f;
                varF21N3 = 1.7f;
                varF22 = 1.9f;
            }
            tmpF20N8 = varF12N13 - varF0N4;
            if (math_fabs(tmpF20N8) < (varF21N3 + 3.0f)) {
                varF12N15 = tmpF20N8 * 1.1111112f;
                if (varF22 < varF12N15) {
                    varF12N15 = varF22;
                }
                if (varF12N15 > 1.0f) {
                    ((Hero *)g_hero_state)->f[0xBF4/4] = varF12N15;
                }
            }
        }
        tmpV1N21 = M2C_FIELD(tmpS2N3, s32* , 4);
        switch (tmpV1N21) {
        case 0:
            if (((Hero *)g_hero_state)->f[0xC38/4] < 18.0f) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            tmpF1N7 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((((Hero *)g_hero_state)->i[0xC2C/4] != 0) || (tmpF1N7 < 9.0f)) {
                if (tmpF1N7 > 8.0f) {
                    ((Hero *)g_hero_state)->f[0x1B0/4] = ((Hero *)g_hero_state)->f[0xBF4/4] * 0.050000004f;
                } else if (tmpF1N7 > 7.0f) {
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
        tmpF1N8 = math_fabs(varF0N5);
        if ((M2C_FIELD(tmpS2N3, s32* , 4) == 1) && (varF0N5 > 0.0f)) {
            ((Hero *)g_hero_state)->f[0xC20/4] = (f32) (1.0f / (tmpF1N8 + 1.0f));
        }
        ((Hero *)g_hero_state)->f[0x1A0/4] = (f32) ((Hero *)g_hero_state)->f[0xBEC/4];
        qcopy(&((Hero *)g_hero_state)->q[0x190/16], &((Hero *)g_hero_state)->q[0xBC0/16]);
        hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        varV1N3 = 1;
        if ((M2C_FIELD(tmpS2N3, s32* , 4) == 1) && (((Hero *)g_hero_state)->i[0xC2C/4] == 0) && (((Hero *)g_hero_state)->f[0xC38/4] > 7.0f)) {
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
            tmpA0N12 = ((void*)g_hero_state) + 0xF0;
            hero_apply_mode_transform((s32) tmpA0N12, (s32) tmpA0N12, 0.015000001f);
        }
        hero_try_surface_push_response(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:
        ApproachValue((s32)(g_hero_state + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L08_001A8FF0) != 0) {
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
    case 0x1F:
        if ((((Hero *)g_hero_state)->i[0xBE8/4] != 0) || (((Hero *)g_hero_state)->i[0xBE4/4] != 0)) {
            ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0xBEC/4];
            hero_steer_heading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)g_hero_state)->i[0x1B8/4] < 4) {
            hero_l00_select_aim_target(11.0f, 0.8726647f, -1.0f);
        }
        lim = 0xA;
        lim2 = 0x12;
        tmpV1N22 = ((Hero *)g_hero_state)->i[0x1B8/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.0f;
        if (tmpV1N22 > lim) {
            if (tmpV1N22 < 0x12) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)g_hero_state)->i[0x1B8/4] == 8) && (((Hero *)g_hero_state)->f[0x184/4] < 0.33333334f)) {
            tmpS0N4 = ((void*)g_hero_state) + 0x18E0;
            level_init_pending_slot((s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32) tmpS0N4);
            level_append_record_to_table((s32) tmpS0N4, 0x30, 2, 0.0f);
            level_append_record_to_table((s32) tmpS0N4, 0x17, 4, 0.0f);
            level_append_record_to_table((s32) tmpS0N4, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)g_hero_state)->i[0x1B8/4] > lim2) ? 5 : 0;
        moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), sel1F);
        if (((Hero *)g_hero_state)->b[0x1492] != 0) {
            tmpV1N23 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((tmpV1N23 > lim) && (tmpV1N23 < 0x11) && (((Hero *)g_hero_state)->f[0x178/4] < 0.14166668f)) {
                ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.020000001f));
                ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.020000001f));
                qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
            }
            hero_steer_reference_point();
        } else {
            if (((Hero *)g_hero_state)->i[0x1B8/4] > lim) {
                hero_approach_speed(0.05277778f, 0.025f);
            }
            if (((Hero *)g_hero_state)->i[0xBE8/4] != 0) {
                hero_compute_push_direction(((Hero *)g_hero_state)->f[0xBEC/4]);
            } else {
                hero_compute_push_direction(99999.0f);
            }
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x1F) {
            tmpV1N24 = ((Hero *)g_hero_state)->i[0x1B8/4];
            if ((tmpV1N24 > lim) && (tmpV1N24 < 0x16)) {
                tmpS2N4 = ((Hero *)g_hero_state)->ptr[0x1220/4];
                if (tmpS2N4 != 0) {
                    tmpS1N6 = ((void*)g_hero_state) + 0x80;
                    v30[0] = 2.0f * math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[1] = 2.0f * math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]);
                    v30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)v0), (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)v30));
                    (*(u8*)((u8*)v10+9)) = 3;
                    v0[3] = 5627.925f;
                    (*(u8*)((u8*)v10+8)) = 0;
                    tmpF22N2 = ((Hero *)g_hero_state)->f[0x98/4];
                    (*(u16*)((u8*)v10+10)) = M2C_FIELD(tmpS2N4, u16* , 0xAA);
                    v40[0] = math_fast_sin_or_cos_a(tmpF22N2) * 0.8f;
                    tmpF0N15 = math_fast_sin_or_cos_b(tmpF22N2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = tmpF0N15;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) tmpS1N6);
                    part_emit_effects_at_nearby_mobys((s32) tmpS2N4, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) tmpS2N4, (s32)((TI128*)v0)));
                    tmpF22N2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], -0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(tmpF22N2) * 0.8f;
                    tmpF0N17 = math_fast_sin_or_cos_b(tmpF22N2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = tmpF0N17;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) tmpS1N6);
                    part_emit_effects_at_nearby_mobys((s32) tmpS2N4, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], (s32)((TI128*)v0)));
                    tmpF22N2 = FastAddRotations(((Hero *)g_hero_state)->f[0x98/4], 0.8726647f);
                    v40[0] = math_fast_sin_or_cos_a(tmpF22N2) * 0.8f;
                    tmpF0N19 = math_fast_sin_or_cos_b(tmpF22N2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = tmpF0N19;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) tmpS1N6);
                    part_emit_effects_at_nearby_mobys((s32) tmpS2N4, coll_process_hit(0.8f, (s32) &v40[0], 0, (s32) tmpS2N4, (s32)((TI128*)v0)));
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
    case 0x22:
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
    case 0x2:
    case 0x70:
        varA0N11 = 0;
        if ((((Hero *)g_hero_state)->b[0x1494] != 0) && (((Hero *)g_hero_state)->f[0x24C4/4] < 0.25f)) {
            varA0N11 = 1;
        }
        if ((((Hero *)g_hero_state)->b[0x22B9] != 0) || (varA0N11 != 0)) {
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
            tmpF20N9 = ReadPadFloatHistory(1);
            if ((FastDiffRots(tmpF20N9, ReadPadFloatHistory(7)) > 1.9198624f) && (math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)g_hero_state)->f[0x24B8/4] == 1.0f)) {
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
            (*(TI128*)v0) = ((Hero *)g_hero_state)->q[0xA60/16];
            tmpF1N9 = ((Hero *)g_hero_state)->f[0x1B0/4] + hero_get_speed_along_forward((s32)((TI128*)v0));
            ((Hero *)g_hero_state)->f[0x1B0/4] = tmpF1N9;
            if (tmpF1N9 < 0.011666667f) {
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
                tmpF2N2 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
                if (((((Hero *)g_hero_state)->f[0x24B8/4] < 0.9f) || ((((Hero *)g_hero_state)->b[0x22BA] != 0) && (((Hero *)g_hero_state)->b[0x40F] == 0))) && (tmpF2N2 > 0.78539824f)) {
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
        tmpF2N3 = math_fabs(((Hero *)g_hero_state)->f[0x1A8/4]);
        if ((((Hero *)g_hero_state)->f[0x24B8/4] < 0.75f) && (tmpF2N3 > 0.6108653f)) {
            varF1N3 = 1.0f - (tmpF2N3 * 0.4f);
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
    case 0x7B:
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        hero_resolve_stick_direction(1.0f, 0);
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.19166668f;
        pad_clamp_stick_to_unit_range((s32)((TI128*)v0), (s32) (((void*)g_hero_state) + 0x9F0), 0.17f);
        varF21N4 = (((Hero *)g_hero_state)->f[0x24B8/4] * 0.020362178f) * v0[0];
        if ((*(s32*)&D_L08_001A8FF0) == 0) {
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
        if ((*(s32*)&D_L08_001A8FF0) != 0) {
            qcopy(v10, &((Hero *)g_hero_state)->q[0x2D0/16]);
            hero_apply_mode_transform_reversed((s32) ((TI128*)v10), (s32) ((TI128*)v10), 0.17f);
            vec_spring_to_target((s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            math_spring_float_to_goal((s32) (((void*)g_hero_state) + 0x88), (s32) (((void*)g_hero_state) + 0xA00), ((Hero *)g_hero_state)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)v10), (s32)(g_hero_state + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32)(g_hero_state + 0xE0));
        tmpV0N12 = coll_process_hit(0.57f, (s32) ((TI128*)v10), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
        if (tmpV0N12 != 0) {
            FastVecScale((s32) ((TI128*)v20), (s32)(g_hero_state + 0x110), 7.0f);
            for (varS0 = 0; varS0 < tmpV0N12; varS0++) {
                if (moby_is_in_special_class_range(((s32 *)D_L08_001C3FC0)[varS0]) != 0) {
                    part_queue_impact_effect(((s32 *)D_L08_001C3FC0)[varS0], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v20), 1.0f);
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
        tmpF0N20 = varF2N3 * 0.5f;
        ((Hero *)D_L08_00266590)->f[0x60/4] = (f32) -varF2N3;
        ((Hero *)D_L08_00266590)->f[0x278/4] = tmpF0N20;
        ((Hero *)D_L08_00266590)->f[0x1C8/4] = tmpF0N20;
        break;
    case 0x2E:
        hero_steer_reference_point();
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        tmpV1N25 = M2C_FIELD(tmpFp, u8* , 0x43);
        if (tmpV1N25 == 0x37) {
            varF0N6 = 1.4f;
            varF20N9 = ((Hero *)g_hero_state)->f[0x1A8/4];
            if ((varF20N9 > 1.4f) || (varF0N6 = -1.4f, (varF20N9 < -1.4f))) {
                varF20N9 = varF0N6;
            }
            ((Hero *)D_L08_00266590)->f[0x60/4] = (f32) (varF20N9 * -0.14f);
            ((Hero *)D_L08_00266590)->f[0x118/4] = (f32) (varF20N9 * 0.3f);
            ((Hero *)D_L08_00266590)->f[0x1C0/4] = (f32) (varF20N9 * -0.22f);
            ((Hero *)D_L08_00266590)->f[0x278/4] = (f32) (varF20N9 * 0.4f);
            ((Hero *)D_L08_00266590)->f[0x274/4] = (f32) (math_fabs(varF20N9) * -0.09f);
            ((Hero *)D_L08_00266590)->f[0x270/4] = (f32) (math_fabs(varF20N9) * 0.08f);
        } else if (tmpV1N25 == 0x66) {
            tmpF22N3 = FastAddRotations(fast_subtract_rotations(mat_fast_helper_a(((Hero *)g_hero_state)->f[0x110/4], ((Hero *)g_hero_state)->f[0x114/4]), ((Hero *)g_hero_state)->f[0x98/4]), 3.1415927f);
            varF21N5 = ((Hero *)g_hero_state)->f[0x174/4] * 6.9813175f;
            if (varF21N5 > 0.43633235f) {
                varF21N5 = 0.43633235f;
            }
            tmpF20N10 = math_fast_sin_or_cos_a(tmpF22N3) * varF21N5;
            tmpF0N21 = -math_fast_sin_or_cos_b(tmpF22N3);
            ((Hero *)D_L08_00266590)->f[0x114/4] = tmpF20N10;
            ((Hero *)D_L08_00266590)->f[0x110/4] = (f32) (tmpF0N21 * varF21N5);
        }
        if (((Hero *)g_hero_state)->h[0x34E/2] != 0) {
            varF12N16 = 0.0069444445f;
            hero_apply_mode_transform((s32)(g_hero_state + 0xF0), (s32) (((void*)g_hero_state) + 0x110), varF12N16);
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = 0.0f;
            hero_apply_mode_transform((s32) ((void*)g_hero_state) + 0xF0, (s32) ((void*)g_hero_state) + 0xF0, 0.041666668f);
            break;
        }
        break;
    case 0x17:
    case 0x18:
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
    case 0x19:
    case 0x1A:
        FastVecSub((s32)(g_hero_state + 0x190), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x190/4], ((Hero *)g_hero_state)->f[0x194/4]);
        hero_steer_heading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)v60), (s32)(g_hero_state + 0x560), (s32)(g_hero_state + 0x550));
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &v40[0], (s32)(g_hero_state + 0x2C0), (s32) ((TI128*)v60));
        } else {
            FastVecCross((s32) &v40[0], (s32) ((TI128*)v60), (s32)(g_hero_state + 0x2C0));
        }
        vec_scale_to_length((s32) &v40[0], (s32) &v40[0], 0.2f);
        FastVecAdd((s32) &v50[0], (s32)(g_hero_state + 0x80), (s32) &v40[0]);
        if ((hero_find_ledge_grab((s32)(g_hero_state + 0x80), (s32)(g_hero_state + 0x90), 0) != 0) && (hero_find_ledge_grab((s32) &v50[0], (s32)(g_hero_state + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(g_hero_state + 0xF0), (s32)((TI128*)v0), (s32)(g_hero_state + 0x80));
            varV0N8 = FloatToInt(((Hero *)g_hero_state)->f[0xC38/4]) * 4;
            varV1N4 = (s32)D_L08_001ACF28;
            vec_scale_to_length((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), *(f32*)(varV0N8 + varV1N4) * 0.5f);
        }
        break;
    case 0x76:
        ((Hero *)g_hero_state)->f[0x1A0/4] = ((Hero *)g_hero_state)->f[0x32C/4];
        ((Hero *)g_hero_state)->f[0x1B0/4] = 0.09166667f;
        ApproachHeroVelocity(0.0069444445f);
        hero_apply_mode_transform((s32) (((void*)g_hero_state) + 0xF0), (s32) ((void*)g_hero_state) + 0x130, 0.005f);
        break;
    case 0x6:
    case 0x2C:
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x2C) {
            varF12N18 = 0.0f;
            if (((Hero *)g_hero_state)->f[0x31C/4] > 4.0f) {
                varF12N18 = 0.43633235f;
            }
            qcopy(v0, &((Hero *)g_hero_state)->q[0x90/16]);
            math_approach_with_velocity((s32) &v0[1], varF12N18, (s32) (((void*)g_hero_state) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            math_approach_with_velocity((s32)((TI128*)v0), 0.0f, (s32) (((void*)g_hero_state) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA0/4], ((Hero *)g_hero_state)->f[0xA4/4], 0.0f);
            if (((Hero *)g_hero_state)->f[0x31C/4] > 1.0f) {
                ((Hero *)g_hero_state)->i[0x2298/4] = 1;
            }
        }
        hero_update_target_speed();
        if (((Hero *)g_hero_state)->h[0x1E0/2] == 0) {
            hero_update_airborne_steering();
        }
        varS1N5 = ((void*)g_hero_state) + 0xF0;
        hero_apply_mode_pose_offsets();
        hero_build_move_impulse(0.7f, 0.0f);
        hero_apply_mode_transform((s32) varS1N5, (s32) varS1N5, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) varS1N5) < -0.8333334f) {
            cam_set_view_space_height((s32) varS1N5, (s32) varS1N5, -0.8333334f);
        }
        break;
    case 0x74:
        ((Hero *)g_hero_state)->c[0x22BC] = 1;
        varS1N5U2 = ((void*)g_hero_state) + 0xF0;
        ApproachValue((s32) (((void*)g_hero_state) + 0xA88), ((Hero *)g_hero_state)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)g_hero_state) + 0xA8C), ((Hero *)g_hero_state)->f[0xA94/4], 0.0024240687f);
        hero_start_pose_offset(((Hero *)g_hero_state)->f[0xA88/4], ((Hero *)g_hero_state)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) varS1N5U2, (s32) varS1N5U2, vec_length_xy((s32) varS1N5U2) * 0.9f);
        hero_apply_mode_transform((s32) varS1N5U2, (s32) varS1N5U2, ((Hero *)g_hero_state)->f[0xA80/4]);
        if (cam_get_view_space_height((s32) varS1N5U2) < -0.8333334f) {
            cam_set_view_space_height((s32) varS1N5U2, (s32) varS1N5U2, -0.8333334f);
        }
        break;
    case 0x82:
        snd_update_slot_object(4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0xD);
        ang82 = (f32) math_lerp_int(0x2D0, 0xB4, ((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        gauge_popup_show(2, math_update_angle_and_blend((s32) (((void*)g_hero_state) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)g_hero_state)->f[0x5B0/4] * 0.02f));
        varA0N12 = (s32) ((Hero *)g_pad_state)->d[0x1A0/8] & 0x40;
        if (((Hero *)g_hero_state)->f[0x5B0/4] == 0.0f) {
            varA0N12 = 0;
        }
        if (varA0N12 != 0) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x5B0), 0.0f, 0.1f);
            tmpA0N15 = ((void*)g_hero_state) + 0xF0;
            cam_offset_point_in_view_space((s32) tmpA0N15, (s32) tmpA0N15, 0.025f);
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
        tmpF12N4 = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
        if ((((Hero *)g_hero_state)->f[0x5B0/4] > 25.0f) && (((Hero *)g_hero_state)->h[0x5BE/2] < 0x5A) && (tmpF12N4 < 0.0f) && (tmpF2N6 = ((Hero *)g_hero_state)->f[0x31C/4], (tmpF2N6 < 1.2f))) {
            varF0N10 = (tmpF2N6 - 0.25f) * 1.0526315f;
            ((Hero *)g_hero_state)->h[0x5BE/2] = (s16) ((u16) ((Hero *)g_hero_state)->h[0x5BE/2] + 1);
            if (varF0N10 < 0.0f) {
                varF0N10 = 0.0f;
            }
            cam_set_view_space_height((s32)(g_hero_state + 0xF0), (s32)(g_hero_state + 0xF0), tmpF12N4 * varF0N10);
            if (((Hero *)g_hero_state)->f[0x31C/4] < 0.25f) {
                math_spring_float_to_goal((s32)(g_hero_state + 0x88), (s32)(g_hero_state + 0x5B4), ((Hero *)g_hero_state)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (tmpF12N4 > 0.0f) {
            ((Hero *)g_hero_state)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L08_001B9D88) = cam_get_view_space_height((s32)(g_hero_state + 0xF0));
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
        ApproachHeroVelocity(varF12N19);
        break;
    case 0x8:
        if (hero_slot_item_id(3) == 2) {
            tmpA2N3 = ((Hero *)g_hero_state)->i[0x243C/4];
            if (tmpA2N3 != -1) {
                tmpA0N16 = (tmpA2N3 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(tmpA0N16, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(tmpA0N16, u8* , 0x74) != 0)) {
                    snd_stop_voice(tmpA2N3);
                }
            }
            ((Hero *)g_hero_state)->i[0x243C/4] = -1;
            snd_update_slot_object(3, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 2);
        } else {
            tmpA2N4 = ((Hero *)g_hero_state)->i[0x2438/4];
            if (tmpA2N4 != -1) {
                tmpA0N17 = (tmpA2N4 * 0x70) + (s32)g_sound_state;
                if ((M2C_FIELD(tmpA0N17, s32* , 0x88) == ((Hero *)g_hero_state)->ptr[0x2290/4]) && (M2C_FIELD(tmpA0N17, u8* , 0x74) != 0)) {
                    snd_stop_voice(tmpA2N4);
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
        tmpF1N12 = ((Hero *)g_hero_state)->f[0x24C8/4];
        if (((Hero *)g_hero_state)->b[0x24EF] != 0) {
            varF22N2 = 0.12833333f;
            varF23 = 0.98640007f;
        }
        if (tmpF1N12 != 0.0f) {
            varF23 = tmpF1N12;
        }
        tmpS0N7 = ((void*)g_hero_state) + 0xF0;
        stack110 = cam_get_view_space_height((s32) tmpS0N7);
        hero_resolve_stick_direction(varF22N2, 0);
        hero_steer_heading(0, 0.025f, 0.3f, 0.20943955f);
        hero_approach_speed(0.004166667f, 0.0019444445f);
        hero_compute_push_direction(99999.0f);
        hero_apply_mode_pose_offsets();
        cam_project_vector_onto_view_plane((s32) tmpS0N7, (s32) tmpS0N7);
        math_spring_float_to_goal((s32) &stack110, (s32) (((void*)g_hero_state) + 0xA98), -varF22N2 * varF23, 0.025f, 0.3f, 0.28333336f);
        hero_apply_mode_transform((s32) tmpS0N7, (s32) tmpS0N7, -stack110);
        tmpF12N5 = ((Hero *)g_hero_state)->f[0x88/4];
        if (tmpF12N5 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ApproachValue((s32) (((void*)g_hero_state) + 0x490), tmpF12N5, 0.06666667f);
        }
        ProbeHeroAirborneWallContact();
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
                hero_resolve_stick_direction(0.09916667f, 0);
            }
            hero_resolve_stick_direction(((Hero *)g_hero_state)->f[0x4A4/4], 0);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] == 0x14) {
                part_emit_hero_dust_and_debris(3, 0x10, 1);
                if (D_L08_001B3170 != 0) {
                    RippleDisturb(D_L08_001B3170, D_L08_001B3178, 0, ((Hero *)g_hero_state)->f[0x80/4], ((Hero *)g_hero_state)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            tmpF1N13 = ((Hero *)g_hero_state)->f[0xC38/4];
            if ((tmpF1N13 >= 4.0f) && (tmpF1N13 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects(7, 0, 0);
            }
        }
        tmpA2N5 = ((Hero *)g_hero_state)->h[0x4AC/2];
        tmpA1N8 = ((Hero *)g_hero_state)->i[0x1B8/4];
        if (tmpA1N8 == tmpA2N5) {
            qcopy(&((Hero *)g_hero_state)->q[0x460/16], &((Hero *)g_hero_state)->q[0x80/16]);
        }
        if ((((Hero *)g_hero_state)->b[0x49C] != 0) || ((tmpA1N8 < tmpA2N5) && (tmpV1N33 = ((Hero *)g_hero_state)->u[0x2294/4], (tmpV1N33 != 0xB)) && (tmpV1N33 != 0x10) && (tmpV1N33 != 0xC) && (tmpV1N33 != 0x11) && (tmpV1N33 != 0x1B) && (tmpV1N33 != 0x89) && (tmpV1N33 != 0x48))) {
            if (((Hero *)g_hero_state)->h[0x528/2] != 0) {
                hero_steer_reference_point();
                if ((((Hero *)g_hero_state)->u[0x2294/4] == 0xA) && (((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x178/4] < 0.116666675f)) {
                    ((Hero *)g_hero_state)->f[0xF0/4] = (f32) (((Hero *)g_hero_state)->f[0xF0/4] + (math_fast_sin_or_cos_a(((Hero *)g_hero_state)->f[0x98/4]) * 0.011666667f));
                    ((Hero *)g_hero_state)->f[0xF4/4] = (f32) (((Hero *)g_hero_state)->f[0xF4/4] + (math_fast_sin_or_cos_b(((Hero *)g_hero_state)->f[0x98/4]) * 0.011666667f));
                    qcopy(&((Hero *)g_hero_state)->q[0x140/16], &((Hero *)g_hero_state)->q[0xF0/16]);
                }
            } else {
                hero_steer_heading(0, 0.015f, 0.2f, 0.2501639f);
                tmpF20N16 = ((Hero *)g_hero_state)->f[0x1B4/4];
                if ((u8) ((Hero *)g_hero_state)->b[0x49C] >= 2U) {
                    ((Hero *)g_hero_state)->f[0x1B4/4] = (f32) (tmpF20N16 * 0.4f);
                }
                if (((Hero *)g_hero_state)->h[0x1454/2] != 0) {
                    hero_compute_push_direction(((Hero *)g_hero_state)->f[0x1458/4]);
                } else {
                    hero_compute_push_direction(99999.0f);
                }
                ((Hero *)g_hero_state)->f[0x1B4/4] = tmpF20N16;
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
                    tmpV1N34 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (tmpV1N34 < (((Hero *)g_hero_state)->h[0x4AC/2] + 4)) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) tmpV1N34 * 0.0044444446f);
                    }
                }
                if (((Hero *)g_hero_state)->u[0x2294/4] == 0xA) {
                    tmpV1N35 = ((Hero *)g_hero_state)->i[0x1B8/4];
                    if (tmpV1N35 < 0x22) {
                        cam_offset_point_by_side_direction((s32) (((void*)g_hero_state) + 0xF0), (s32) (((void*)g_hero_state) + 0xF0), (f32) tmpV1N35 * 0.014722222f);
                    }
                }
                if ((((Hero *)g_hero_state)->i[0x1B8/4] < 0xA) && (((Hero *)g_hero_state)->f[0x24B8/4] > 0.2f)) {
                    qcopy(v0, &((Hero *)g_hero_state)->q[0x80/16]);
                    cam_offset_point_in_view_space((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    cam_offset_point_by_side_direction((s32) ((TI128*)v10), (s32)((TI128*)v0), 0.95f);
                    if (CollLine((s32)((TI128*)v0), (s32) ((TI128*)v10), 4, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)g_hero_state)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            hero_update_airborne_steering();
            if (((Hero *)g_hero_state)->u[0x2294/4] == 0x12) {
                tmpS0N8 = ((void*)g_hero_state) + 0xF0;
                varF0N11 = vec_length_xy((s32) tmpS0N8);
                if (varF0N11 > 0.06166667f) {
                    varF0N11 = 0.06166667f;
                }
                vec_fast_normalize_helper((s32) tmpS0N8, (s32) tmpS0N8, varF0N11);
            }
        }
        tmpF1N14 = ((Hero *)g_hero_state)->f[0x318/4];
        tmpF2N7 = ((Hero *)g_hero_state)->f[0x490/4];
        if (tmpF2N7 < tmpF1N14) {
            tmpF0N29 = tmpF2N7 + 0.10000001f;
            ((Hero *)g_hero_state)->f[0x490/4] = tmpF0N29;
            if (tmpF1N14 < tmpF0N29) {
                ((Hero *)g_hero_state)->f[0x490/4] = tmpF1N14;
            }
        }
        tmpF1N15 = ((Hero *)g_hero_state)->f[0x88/4];
        if (tmpF1N15 < ((Hero *)g_hero_state)->f[0x490/4]) {
            ((Hero *)g_hero_state)->f[0x490/4] = tmpF1N15;
        }
        if ((((Hero *)g_hero_state)->h[0x4AC/2] < ((Hero *)g_hero_state)->i[0x1B8/4]) && (cam_get_view_space_height((s32) (((void*)g_hero_state) + 0xF0)) < 0.001f) && ((((Hero *)g_hero_state)->b[0x49D] == 0) || (((Hero *)g_hero_state)->i[0x1B8/4] > ((Hero *)g_hero_state)->i[0x434/4])) && ((((Hero *)g_hero_state)->u[0x2294/4] != 0xE) || (((Hero *)g_hero_state)->i[0x1B8/4] >= 0x12))) {
            tmpF1N16 = ((Hero *)g_hero_state)->f[0x458/4];
            ((Hero *)g_hero_state)->b[0x49E] = 1U;
            if (tmpF1N16 != 0.0f) {
                ((Hero *)g_hero_state)->f[0x520/4] = tmpF1N16;
            }
        }
        if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
            hero_apply_mode_pose_offsets();
        }
        tmpV1N36 = ((Hero *)g_hero_state)->u[0x2294/4];
        if ((tmpV1N36 == 0x10) || (tmpV1N36 == 0xD)) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x81) {
            moby_update_transform_history_followers((s32) (((void*)g_hero_state) + 0x18E0), (((Hero *)g_hero_state)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)g_hero_state)->u[0x2294/4] == 0x10) {
            if (((Hero *)g_hero_state)->i[0x1B8/4] >= 9) {
                if (((Hero *)g_hero_state)->f[0xC38/4] < 28.0f) {
                    hero_build_relative_point((s32)((TI128*)v0), 1, 0.8f, 0.0f, 0.3f);
                    tmpV0N17 = coll_process_hit(0.9f, (s32)((TI128*)v0), 0, (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0);
                    if (tmpV0N17 != 0) {
                        FastVecScale((s32) ((TI128*)v10), (s32) (((void*)g_hero_state) + 0x110), 7.0f);
                        for (varS0N2 = 0; varS0N2 < tmpV0N17; varS0N2++) {
                            if (moby_is_in_special_class_range(((s32 *)D_L08_001C3FC0)[varS0N2]) != 0) {
                                part_queue_impact_effect(((s32 *)D_L08_001C3FC0)[varS0N2], (s32) ((Hero *)g_hero_state)->ptr[0x2290/4], 0x10000, (s32) (((void*)g_hero_state) + 0x80), (s32) ((TI128*)v10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        ApplyHeroGravityAndJumpMotion();
        ProbeHeroAirborneWallContact();
        break;
    case 0x16:
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
    case 0x8C:
        qzero(D_00189F10);
        ((Hero *)g_hero_state)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:
        FastVecSub((s32)((TI128*)v0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
        tmpF0N30 = vec_length_xy((s32)((TI128*)v0));
        if (tmpF0N30 > 0.2f) {
            hp32 = (Hero *)g_hero_state;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)g_hero_state)->f[0x1A0/4] = mat_fast_helper_a(v0[0], v0[1]);
            ((Hero *)g_hero_state)->f[0x1B0/4] = tmpF0N30;
            if (tmpF0N30 < D_L08_001A7DAC[0][2]) {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L08_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)g_hero_state)->f[0x1B0/4] = D_L08_001A7DAC[1][1] * 0.016666668f;
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
    case 0x63:
        FastVecSub((s32)((TI128*)v0), (s32)(g_hero_state + 0x18A0), (s32)(g_hero_state + 0x80));
        if (FastVecDot((s32)((TI128*)v0), (s32)(g_hero_state + 0x160)) < 0.0f) {
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
    case 0x3C:
    case 0x64:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    case 0x65:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        if (((f32) ((Hero *)g_hero_state)->i[0x18C0/4] * 0.5f) < (((Hero *)g_hero_state)->f[0x334/4] - ((Hero *)g_hero_state)->f[0x88/4])) {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.004166667f;
        } else {
            ((Hero *)g_hero_state)->f[0xF8/4] = -0.016666668f;
        }
        break;
    case 0x78:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        M2C_FIELD(((void*)(g_hero_state + 0xF0)), f32* , 8) = -0.016666668f;
        break;
    case 0x60:
    case 0x61:
        vec_clear_128((s32)(g_hero_state + 0xF0));
        break;
    }
    if (stack114 != ((Hero *)g_hero_state)->i[0x2298/4]) {
        ((Hero *)g_hero_state)->i[0x1C0/4] = 0;
    }
    if (stack118 != M2C_FIELD(tmpFp, u8* , 0x43)) {
        ((Hero *)g_hero_state)->i[0x1C4/4] = 0;
    }
}

