#include "names.h"
/* func_US2_L01_003C1DB8, the USA v2.00 copy of func_L01_003C09C0: the same C, where inner state 4
   gains an else branch calling func_L01_003C06E8.
   (Oozla, 7,456 bytes): a moby update with an outer switch on the state byte
   at 0x95 and per-state inner switches.  One function: one prologue, one return.
   Byte offsets into the moby (arg0) and its state block (+0x68) go through the UView union so the
   accesses are aggregate memory, which lets sched move gp-relative loads over them as retail
   does; the two stores before the D_0018C0B4 test stay plain word accesses (retail keeps that
   load behind them).  Tables are indexed as (index << n) + (s32)base, the operand order retail
   adds in.  Two addressing forms of the 0x1B255C and 0x1B264C pointers: the _sda names are the
   $gp form.  -frac2-hazard-labels gives the forward branch onto the 17.0f compare its hazard nop
   target (docs/build/compiler-notes.md, Labels on hazard nops). */
#include "common.h"
typedef union { u8 b[0x800]; s8 c[0x800]; s16 h[0x400]; u16 uh[0x400]; s32 i[0x200]; u32 u[0x200]; f32 f[0x200]; void *p[0x200]; } UView;
extern int CollLine(void *,void *,int,void *,void *);
extern s32 coll_process_hit(f32, s32, s32, s32, s32);
extern void FadeToBlack(s32);
extern s32 vec_fast_helper_a(void *a0);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern f32 FastVecLength(void *);
extern f32 vec_length_xy(void *);
extern f32 fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern f32 FastDiffRots(f32, f32);
extern float IntToFloat(int);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(char *);
extern void moby_transform_joint_to_world(void *, int, void *);
typedef int TI128 __attribute__((mode(TI)));
extern void swamp_monster_update_hit_reaction(void);
extern void swamp_monster_init(void *);
extern void swamp_monster_update_timers(void *);
extern float swamp_monster_move_around_arena(void *);
extern void swamp_monster_start_claw_attack(void *);
extern void swamp_monster_start_attack_b(void *);
extern void swamp_monster_start_attack_c(void *);
extern void swamp_monster_start_grab_attack(void *);
extern void func_US2_L01_003C1CA8(void *);
extern u8 *moby_spawn_thrown_object(void *, void *, void *, float);
extern void *SpawnGoldBolt(void *, int, int, int);
extern void func_US2_L01_00395620(void *);
extern int func_001163B0(void);
#define NULL ((void *)0)
extern void moby_mark_table_entry_flagged(u32 a0);
extern void func_002A0F48(void *);
extern void func_US2_002A7AA8(void *, int, int);
extern void moby_set_state(char *, int, int);
extern float math_square(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void part_init_effect_record(void *a0, int a1, int a2, float a3);
extern s32 coll_test_hit_at_bone(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern void QueueMobyImpact(s32, void *);
extern s32 math_is_value_within_step_us2(u8 *, f32);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_record_play_counters(void);
extern void hero_reset_position_and_direction(int a0, int a1, int a2, int a3);
extern void * cam_alloc_override_slot(s32 size);
extern void cam_end_override(char *);
extern void load_scene_chunk(int, int);
extern f32 weapon_compute_shot_launch_speed(f32 *a, f32 *b, f32 *out, f32 d, f32 e);
extern s32 func_US2_L01_002BEEA8(s32 action, s32 animate);
extern int moby_start_effect_from_entry(void *, float);
extern void script_queue_keyed_request(int, int);
extern float level_get_water_height(void);
extern void moby_set_animation_and_speed(void *, int, int, int);
typedef struct { u8 pad[0x80]; f32 x; f32 y; f32 z; u8 pad2[0x2204]; s32 a2290; s32 a2294; u8 pad3[4]; s32 a229c; u8 pad4[0x15]; u8 a22b5; u8 pad5[0x1EA]; s32 a24a0; u8 pad6[0x28]; s32 a24cc; } HeroV;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
extern u8 g_hero_state[] NOT_SDA;
extern s32 g_game_mode __attribute__((nosda));
extern u8 g_grab_flag __attribute__((nosda));
extern u8 g_hero_position[] NOT_SDA;

extern s32 g_current_map_index __attribute__((sda));
extern f32 g_swamp_monster_range_a __attribute__((sda));
extern f32 g_swamp_monster_range_c __attribute__((sda));
extern f32 g_swamp_monster_range_near __attribute__((sda));
extern f32 g_swamp_monster_range_b __attribute__((sda));
extern f32 g_swamp_monster_far_range __attribute__((sda));
extern f32 g_swamp_monster_hero_close_range __attribute__((sda));
extern f32 g_swamp_monster_limit_speed_a __attribute__((sda));
extern f32 g_swamp_monster_limit_angular_a __attribute__((sda));
extern f32 g_swamp_monster_limit_turn_a __attribute__((sda));
extern f32 g_swamp_monster_limit_move_b __attribute__((sda));
extern f32 g_swamp_monster_limit_move_c __attribute__((sda));
extern f32 g_swamp_monster_limit_move_d __attribute__((sda));
extern f32 g_swamp_monster_limit_move_e __attribute__((sda));
extern f32 g_swamp_monster_limit_move_f __attribute__((sda));
extern f32 g_swamp_monster_alt_limit_speed __attribute__((sda));
extern f32 g_swamp_monster_alt_limit_move __attribute__((sda));
extern f32 g_swamp_monster_alt_limit_angular __attribute__((sda));
extern f32 g_swamp_monster_alt_limit_turn __attribute__((sda));
extern f32 g_swamp_monster_aim_angle_near __attribute__((sda));
extern f32 g_swamp_monster_aim_angle_mid __attribute__((sda));
extern f32 g_swamp_monster_aim_angle_a __attribute__((sda));
extern f32 g_swamp_monster_aim_angle_b __attribute__((sda));
extern s32 g_swamp_monster_attack_odds_a __attribute__((sda));
extern s32 g_swamp_monster_attack_odds_b __attribute__((sda));
extern u8 g_swamp_monster_vars_byte __attribute__((sda));
extern s32 g_swamp_monster_attack_threshold __attribute__((sda));
extern f32 g_swamp_monster_scratch_length __attribute__((sda));
extern f32 g_swamp_monster_move_speed __attribute__((sda));
extern f32 g_swamp_monster_shot_speed __attribute__((sda));
extern f32 g_swamp_monster_shot_gravity __attribute__((sda));
extern u8 *D_L01_001B255C_sda __attribute__((sda));
extern u8 *D_L01_001B264C_sda __attribute__((sda));
extern u8 g_drive_velocity_view[] NOT_SDA;
extern u8 g_moby_group_flags[] NOT_SDA;
extern u8 *g_moby_l01_table;
extern u8 *g_swamp_patrol_positions;

void func_US2_L01_003C1DB8(u8 *arg0) {
    float sp[20] __attribute__((aligned(16)));
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f1;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f21_3;
    f32 temp_f22;
    f32 temp_f23;
    f32 var_f12_2;
    u8 *temp_a0_6;
    s32 temp_a1;
    s32 temp_a1_2;
    u8 *temp_a2;
    s32 temp_v0_4;
    s32 temp_v1_13;
    s32 temp_v1_14;
    s32 temp_v1_15;
    s32 temp_v1_19;
    s32 temp_v1_3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s5;
    u8 *temp_a0;
    u8 *temp_a0_3;
    u8 *temp_s1;
    u8 *temp_v1_12;
    u8 temp_s0;
    u8 temp_v0_2;
    u8 temp_v1;
    u8 temp_v1_10;
    u8 temp_v1_11;
    u8 temp_v1_17;
    u8 temp_v1_18;
    u8 temp_v1_2;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 temp_v1_7;
    u8 temp_v1_8;
    u8 temp_v1_9;
    u8 *temp_a0_2;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a1_3;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s1_2;
    u8 *temp_s1_3;
    u8 *temp_s4;
    u8 *temp_v0;
    u8 *temp_v0_3;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v1_16;

    temp_s4 = ((u8 *)((UView *)(arg0))->p[0x1A]);
    swamp_monster_update_hit_reaction();
    temp_v1 = ((UView *)(arg0))->b[0x95];
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if ((((UView *)(arg0))->b[0xB0] != 0xFF) && (g_moby_group_flags[((UView *)(arg0))->b[0xB0] + (g_current_map_index * 0x10)] & 0x80)) {
            temp_v1_3 = ((UView *)(temp_s4))->i[0xC2];
            if (temp_v1_3 != -1) {
                D_L01_001B255C_sda[(temp_v1_3 << 8) + 0xBC] = 1;
            }
            moby_mark_spawned(arg0);
            return;
        }
        swamp_monster_init(arg0);
    default:
        break;
    case 1:                                         /* switch 1 */
        if (((UView *)(temp_s4))->i[0x49] == 1) {
            if (((u8 *)((UView *)(temp_s4))->p[0xB9]) == NULL) {
                script_queue_keyed_request(((UView *)(temp_s4))->i[0xC4], ((UView *)(temp_s4))->i[0xC6]);
                ((u8 *)((UView *)(temp_s4))->p[0xB9]) = cam_alloc_override_slot(5);
            }
            moby_set_state(arg0, 0, 2);
        }
        break;
    case 2:                                         /* switch 1 */
        temp_f0 = swamp_monster_move_around_arena(arg0);
        if (temp_f0 == -1000.0f) {
            temp_a0 = ((u8 *)((UView *)(temp_s4))->p[0xB9]);
            if (temp_a0 != NULL) {
                cam_end_override(temp_a0);
                ((u8 *)((UView *)(temp_s4))->p[0xB9]) = NULL;
            }
            moby_set_state(arg0, 0, 1);
            moby_set_animation_and_speed(arg0, 0, 0, 0xA);
        } else {
            temp_v0 = ((u8 *)((UView *)(temp_s4))->p[0x48]);
            temp_f21 = FastDiffRots(((UView *)(arg0))->f[0x3E], mat_fast_helper_a(*(f32 *)(temp_v0 + 0x10) - ((UView *)(arg0))->f[0x4], *(f32 *)(temp_v0 + 0x14) - ((UView *)(arg0))->f[0x5]));
            switch (((UView *)(arg0))->b[0xBC]) {                    /* switch 2 */
            case 0:                                 /* switch 2 */
                if ((temp_f0 <= g_swamp_monster_range_near) && (temp_f21 < (g_swamp_monster_aim_angle_near * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                    var_s0 = 1;
                    swamp_monster_start_claw_attack(arg0);
                } else {
                    var_s0 = g_swamp_monster_attack_threshold < (s32) ((UView *)(arg0))->uh[0x4B];
                }
                if (var_s0 != 0) {
                    moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(arg0))->b[0xBC] = 1U;
                }
                if (((UView *)(temp_s4))->f[0x8] < (2.0f * IntToFloat((s32) ((UView *)(temp_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->b[0x2E1] = 5U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0xE;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_c * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(arg0))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(arg0, 0x10, 0, 0xD);
                    moby_set_state(arg0, 0, 5);
                }
            default:                                /* switch 2 */
                break;
            case 1:                                 /* switch 2 */
            case 2:                                 /* switch 2 */
                temp_v1_5 = ((UView *)(arg0))->b[0xBC];
                var_s1 = 0;
                switch (temp_v1_5) {                /* switch 3; irregular */
                case 1:                             /* switch 3 */
                    if ((temp_f0 <= g_swamp_monster_range_near) && (temp_f21 < (g_swamp_monster_aim_angle_near * 0.017453294f))) {
                        if ((math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                            swamp_monster_start_claw_attack(arg0);
                        } else {
                            goto block_36;
                        }
                    } else {
block_36:
                        if ((g_swamp_monster_range_near < temp_f0) && (temp_f0 <= g_swamp_monster_range_b) && (temp_f21 < (g_swamp_monster_aim_angle_mid * 0.017453294f))) {
                            if ((math_random_int_below(g_swamp_monster_attack_odds_b - 1) == 0) && (((UView *)(temp_s4))->h[0x16D] == 0)) {
                                swamp_monster_start_attack_c(arg0);
                            } else {
                                goto block_43;
                            }
                        } else {
block_43:
                            if (g_swamp_monster_far_range < temp_f0) {
                                ((UView *)(temp_s4))->b[0x2E1] = 4U;
                                ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                                ((UView *)(temp_s4))->c[0x2E0] = 0;
                                moby_set_controller_speed_limits(arg0, g_swamp_monster_alt_limit_speed * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_alt_limit_angular * 0.0000048481375f, g_swamp_monster_alt_limit_turn * 0.00029088825f);
                                ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                                ((UView *)(arg0))->b[0xBC] = 2U;
                                ((UView *)(temp_s4))->c[0x71] = 0xF;
                                ((UView *)(temp_s4))->c[0x72] = 0xF;
                                moby_set_animation_and_speed(arg0, 3, 0, 0xD);
                                moby_set_state(arg0, 0, 5);
                            }
                        }
                    }
                    break;
                case 2:                             /* switch 3 */
                    var_s1 = 0x3C;
                    ((UView *)(arg0))->i[0x26] = 0;
                    if ((temp_f0 <= g_swamp_monster_range_near) && ((temp_v1_6 = ((UView *)(arg0))->b[0x42], (temp_v1_6 == 0x16)) || (temp_v1_6 == 0))) {
                        ((UView *)(temp_s4))->c[0x2E0] = 1;
                        ((UView *)(temp_s4))->b[0x2E1] = 1U;
                        ((UView *)(temp_s4))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                        ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                        ((UView *)(arg0))->b[0xBC] = 1U;
                        ((UView *)(temp_s4))->c[0x71] = 0x13;
                        ((UView *)(temp_s4))->c[0x72] = 0x13;
                        ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                        moby_set_animation_and_speed(arg0, 0x16, 0, 0x14);
                        moby_set_state(arg0, 0, 5);
                    }
                    break;
                }
                if (((UView *)(temp_s4))->f[0x8] < (2.0f * IntToFloat((s32) ((UView *)(temp_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->b[0x2E1] = 5U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0xE;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_c * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(arg0))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(arg0, 0x10, 0, var_s1 + 0xD);
                    moby_set_state(arg0, 0, 5);
                }
                break;
            case 3:                                 /* switch 2 */
            case 4:                                 /* switch 2 */
            case 5:                                 /* switch 2 */
            case 6:                                 /* switch 2 */
                temp_s0 = ((UView *)(arg0))->b[0xBC];
                switch (temp_s0) {                  /* switch 4; irregular */
                case 3:                             /* switch 4 */
                    if ((temp_f0 <= g_swamp_monster_range_a) && (temp_f21 < (g_swamp_monster_aim_angle_a * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16F] == 0)) {
                        moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_d * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                        ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_c;
                        ((UView *)(arg0))->b[0xBC] = 4U;
                        ((UView *)(temp_s4))->b[0x2E3] = (u8) g_swamp_monster_vars_byte;
                        ((UView *)(temp_s4))->c[0x71] = 0x13;
                        ((UView *)(temp_s4))->c[0x2E0] = 1;
                        ((UView *)(temp_s4))->c[0x72] = 0x13;
                        ((UView *)(temp_s4))->b[0x2E1] = 1U;
                        ((UView *)(temp_s4))->c[0x2E2] = 0;
                        swamp_monster_start_grab_attack(arg0);
                    }
                    break;
                case 4:                             /* switch 4 */
                    if ((g_swamp_monster_range_near < temp_f0) && (temp_f0 <= g_swamp_monster_range_c) && (temp_f21 < (g_swamp_monster_aim_angle_b * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                        if (vec_fast_helper_a(temp_s4 + 0x2E3) != 0) {
                            moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                            ((UView *)(arg0))->b[0xBC] = 5U;
                            ((UView *)(temp_s4))->c[0x2E0] = 0;
                            ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                            ((UView *)(temp_s4))->b[0x2E1] = temp_s0;
                            ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                            ((UView *)(temp_s4))->c[0x71] = 0xF;
                            ((UView *)(temp_s4))->c[0x72] = 0xF;
                            moby_set_animation_and_speed(arg0, 3, 0, 0xD);
                            moby_set_state(arg0, 0, 5);
                        }
                        swamp_monster_start_attack_b(arg0);
                    } else if ((temp_f0 <= g_swamp_monster_range_near) && (temp_f0 <= g_swamp_monster_range_c) && (temp_f21 < (g_swamp_monster_aim_angle_b * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                        swamp_monster_start_claw_attack(arg0);
                    }
                    break;
                case 5:                             /* switch 4 */
                    ((UView *)(arg0))->i[0x26] = 0;
                    if (temp_f0 <= g_swamp_monster_range_near) {
                        temp_v1_7 = ((UView *)(arg0))->b[0x42];
                        if (temp_v1_7 != 0x16) {
                            if (temp_v1_7 == 0) {
                                goto block_72;
                            }
                        } else {
block_72:
                            ((UView *)(temp_s4))->c[0x2E0] = 1;
                            ((UView *)(temp_s4))->b[0x2E1] = 1U;
                            ((UView *)(temp_s4))->c[0x71] = 0x13;
                            ((UView *)(temp_s4))->c[0x72] = 0x13;
                            ((UView *)(temp_s4))->c[0x2E2] = 0;
                            moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                            ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_c;
                            ((UView *)(arg0))->b[0xBC] = 6U;
                            ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                            moby_set_animation_and_speed(arg0, 0x16, 0, 0x14);
                            moby_set_state(arg0, 0, 5);
                        }
                    }
                    break;
                case 6:                             /* switch 4 */
                    ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                    if ((temp_f0 <= g_swamp_monster_range_c) && (temp_f21 < (g_swamp_monster_aim_angle_near * 0.017453294f)) && (math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                        if ((g_swamp_monster_range_near < temp_f0) && (func_001163B0() & 1)) {
                            swamp_monster_start_attack_b(arg0);
                        } else {
                            swamp_monster_start_claw_attack(arg0);
                        }
                    }
                    break;
                }
                temp_v0_2 = ((UView *)(arg0))->b[0xBC];
                if ((temp_v0_2 != 5) && (temp_v0_2 < 7U) && (g_swamp_monster_far_range < temp_f0)) {
                    moby_set_controller_speed_limits(arg0, g_swamp_monster_alt_limit_speed * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_alt_limit_angular * 0.0000048481375f, g_swamp_monster_alt_limit_turn * 0.00029088825f);
                    ((UView *)(arg0))->b[0xBC] = 5U;
                    ((UView *)(temp_s4))->c[0x2E0] = 0;
                    ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(temp_s4))->c[0x71] = 0xF;
                    ((UView *)(temp_s4))->c[0x72] = 0xF;
                    ((UView *)(temp_s4))->b[0x2E1] = 4U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                }
                if (((UView *)(temp_s4))->f[0x8] < (IntToFloat((s32) ((UView *)(temp_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(temp_s4))->b[0x2E1] = 5U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0xE;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_e * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(arg0))->b[0xBC] = 7U;
                    moby_set_animation_and_speed(arg0, 0x10, 0, 0xD);
                    moby_set_state(arg0, 0, 5);
                }
                break;
            case 7:                                 /* switch 2 */
                if ((temp_f0 <= g_swamp_monster_range_a) && (temp_f21 < (g_swamp_monster_aim_angle_a * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16F] == 0)) {
                    ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(arg0))->b[0xBC] = 9U;
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->b[0x2E1] = 1U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_f * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    swamp_monster_start_grab_attack(arg0);
                }
                break;
            case 8:                                 /* switch 2 */
                ((UView *)(arg0))->i[0x26] = 0;
                if (temp_f0 <= g_swamp_monster_range_near) {
                    temp_v1_8 = ((UView *)(arg0))->b[0x42];
                    if (temp_v1_8 != 0x16) {
                        if (temp_v1_8 == 0) {
                            goto block_95;
                        }
                    } else {
block_95:
                        ((UView *)(temp_s4))->c[0x2E0] = 1;
                        ((UView *)(temp_s4))->b[0x2E1] = 1U;
                        ((UView *)(temp_s4))->c[0x71] = 0x13;
                        ((UView *)(temp_s4))->c[0x72] = 0x13;
                        ((UView *)(temp_s4))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(arg0, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                        ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                        ((UView *)(arg0))->b[0xBC] = 9U;
                        ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                        moby_set_animation_and_speed(arg0, 0x16, 0, 0x14);
                        moby_set_state(arg0, 0, 5);
                    }
                }
                break;
            case 9:                                 /* switch 2 */
                ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                if ((temp_f0 <= g_swamp_monster_range_near) && (temp_f21 < (g_swamp_monster_aim_angle_near * 0.017453294f))) {
                    if ((math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                        if (func_001163B0() & 1) {
                            swamp_monster_start_claw_attack(arg0);
                        } else {
                            swamp_monster_start_attack_b(arg0);
                        }
                    } else {
                        goto block_105;
                    }
                } else {
block_105:
                    if ((g_swamp_monster_range_near < temp_f0) && (temp_f0 <= g_swamp_monster_range_b) && (temp_f21 < (g_swamp_monster_aim_angle_mid * 0.017453294f))) {
                        if ((math_random_int_below(g_swamp_monster_attack_odds_b - 1) == 0) && (((UView *)(temp_s4))->h[0x16D] == 0)) {
                            swamp_monster_start_attack_c(arg0);
                        } else {
                            goto block_112;
                        }
                    } else {
block_112:
                        if (g_swamp_monster_far_range < temp_f0) {
                            ((UView *)(temp_s4))->b[0x2E1] = 4U;
                            ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                            ((UView *)(temp_s4))->c[0x2E0] = 0;
                            moby_set_controller_speed_limits(arg0, g_swamp_monster_alt_limit_speed * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_alt_limit_angular * 0.0000048481375f, g_swamp_monster_alt_limit_turn * 0.00029088825f);
                            ((UView *)(temp_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                            ((UView *)(arg0))->b[0xBC] = 8U;
                            ((UView *)(temp_s4))->c[0x71] = 0xF;
                            ((UView *)(temp_s4))->c[0x72] = 0xF;
                            moby_set_animation_and_speed(arg0, 3, 0, 0xD);
                            moby_set_state(arg0, 0, 5);
                        }
                    }
                }
                break;
            }
            if ((((UView *)(arg0))->b[0x42] == 0x16) && (((UView *)(arg0))->b[0x60] & 2)) {
                ((UView *)(temp_s4))->c[0x2E2] = 0;
                moby_set_animation_and_speed(arg0, 0, 0, 0xA);
            }
        }
        break;
    case 3:                                         /* switch 1 */
        temp_f20 = moby_get_anim_value(arg0);
        switch (((UView *)(arg0))->b[0x20]) {                        /* switch 5; irregular */
        case 1:                                     /* switch 5 */
            moby_start_effect_from_entry(arg0, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(arg0))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(arg0))->f[0x5]));
            if ((temp_f20 > 44.0f) && (temp_f20 < 68.0f)) {
                temp_v1_10 = ((UView *)(arg0))->b[0x42];
                var_s5 = -1;
                if (temp_v1_10 == 6) {
                    var_s5 = 0;
                } else if (temp_v1_10 == 7) {
                    var_s5 = 4;
                }
                if (var_s5 >= 0) {
                    moby_transform_joint_to_world(arg0, var_s5, (sp + 4));
                    for (var_s1_2 = 1; var_s1_2 < 3; var_s1_2++) {
                        part_init_effect_record((sp + 8), (s32) arg0, 1, (f32) ((UView *)(temp_s4))->b[0x34]);
                        qcopy(sp, sp + 4);
                        moby_transform_joint_to_world(arg0, var_s5 + var_s1_2, sp + 4);
                        coll_process_hit(0.5f, (s32) (sp + 4), 0, (s32) arg0, (s32) (sp + 8));
                        sp[4] += math_random_float_range(-0.3f, 0.3f);
                        sp[5] += math_random_float_range(-0.3f, 0.3f);
                        sp[6] += math_random_float_range(-0.3f, 0.3f);
                        CollLine(sp, (sp + 4), 9, arg0, (sp + 8));
                    }
                }
            }
            break;
        case 2:                                     /* switch 5 */
            moby_start_effect_from_entry(arg0, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(arg0))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(arg0))->f[0x5]));
            if (math_is_value_within_step_us2((u8 *) arg0, 16.0f) != 0) {
                moby_transform_joint_to_world(arg0, 0xA, sp);
                FastVecSub((sp + 4), ((u8 *)((UView *)(temp_s4))->p[0x48]) + 0x10, sp);
                vec_scale_to_length((sp + 4), (sp + 4), g_swamp_monster_shot_speed * 0.016666668f);
                sp[6] = weapon_compute_shot_launch_speed(sp, ((u8 *)((UView *)(temp_s4))->p[0x48]) + 0x10, NULL, g_swamp_monster_shot_speed * 0.016666668f, -(g_swamp_monster_shot_gravity * 0.00027777778f));
                moby_spawn_thrown_object(sp, (sp + 4), arg0, (f32) ((UView *)(temp_s4))->b[0x34]);
            }
            break;
        case 3:                                     /* switch 5 */
            if ((temp_f20 > 34.0f) && (temp_f20 < 41.0f)) {
                temp_a1 = (func_001163B0() & 1) | 8;
                coll_test_hit_at_bone(arg0, 2.2f, (f32) ((UView *)(temp_s4))->b[0x34], temp_a1, 1, 1.0f, 0, 1, 0);
            }
            break;
        case 4:                                     /* switch 5 */
            moby_start_effect_from_entry(arg0, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(arg0))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(arg0))->f[0x5]));
            if (((UView *)(temp_s4))->b[0x2F4] == 0) {
                if (temp_f20 > 12.0f) {
                    if (temp_f20 <= 17.0f) {
                        moby_transform_joint_to_world(arg0, 0xC, sp);
                        sp[2] -= 2.4f;
                        if ((fast_vec_dist(sp, &((HeroV *)g_hero_state)->x) < g_swamp_monster_hero_close_range) && (*(s32 *)(g_hero_state + 0x2294) != 0x6F)) {
                            ((UView *)(temp_s4))->b[0x2F4] = 1U;
                        }
                    } else {
                        goto block_149;
                    }
                } else {
block_149:
                    if ((temp_f20 > 17.0f) && (temp_f20 < 19.0f)) {
                        ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                        temp_a1 = (func_001163B0() & 1) | 0xC;
                        coll_test_hit_at_bone(arg0, 2.0f, (f32) ((UView *)(temp_s4))->b[0x35], temp_a1, 1, 1.0f, 0, 1, 0);
                    }
                }
            } else if (temp_f20 > 19.0f) {
                ((HeroV *)g_hero_state)->a22b5 = 1;
            }
            break;
        }
        if (((UView *)(temp_s4))->b[0x2F4] != 0) {
            func_US2_L01_003C1CA8(arg0);
            if (((UView *)(arg0))->b[0x60] & 2) {
                if (((HeroV *)g_hero_state)->a24cc < 2) {
                    hero_record_play_counters();
                } else {
                    part_init_effect_record(sp, (s32) arg0, 1, (f32) ((UView *)(temp_s4))->b[0x36]);
                    QueueMobyImpact(((HeroV *)g_hero_state)->a2290, sp);
                }
                ((HeroV *)g_hero_state)->a22b5 = 1;
                moby_set_animation_and_speed(arg0, 0xB, 0, 0x14);
                moby_set_state(arg0, 0, 4);
            }
        } else {
            if (((UView *)(arg0))->b[0x60] & 2) {
                ((UView *)(arg0))->i[0x27] = (s32) (((UView *)(arg0))->i[0x27] & ~0x30);
                moby_set_state(arg0, 0, 2);
                moby_set_animation_and_speed(arg0, 0, 0, 0x14);
            }
        }
        break;
    case 4:                                         /* switch 1 */
        temp_f23 = moby_get_anim_value(arg0);
        temp_v0_3 = (u8 *)((((UView *)(temp_s4))->i[0xB3] << 7) + (s32)g_swamp_patrol_positions);
        temp_f0_2 = mat_fast_helper_a(*(f32 *)(temp_v0_3 + 0x30) - ((UView *)(arg0))->f[0x4], *(f32 *)(temp_v0_3 + 0x34) - ((UView *)(arg0))->f[0x5]);
        temp_f22 = FastAddRotations(temp_f0_2, 1.5707965f);
        temp_f21_2 = fast_subtract_rotations(temp_f0_2, 1.5707965f);
        temp_f20_2 = FastDiffRots(((UView *)(arg0))->f[0x3E], temp_f22);
        moby_start_effect_from_entry(arg0, temp_f20_2 < FastDiffRots(((UView *)(arg0))->f[0x3E], temp_f21_2) ? temp_f22 : temp_f21_2);
        if (((UView *)(arg0))->b[0x42] == 0xB) {
            var_s2 = 1;
            moby_transform_joint_to_world(arg0, 0xE, sp);
            temp_f0_3 = fast_vec_dist(sp, &((Hero *)g_hero_state)->b[0x80]);
            if (!(temp_f0_3 > 13.0f)) {
                var_s2 = 0;
            }
            if (((UView *)(temp_s4))->b[0x2F4] != 0) {
                if (temp_f23 > 33.0f) {
                    func_US2_L01_002BEEA8(0x16, 1);
                    ((Hero *)g_hero_state)->i[0x2294 / 4] = 0x6F;
                    ((Hero *)g_hero_state)->i[0x24A0 / 4] = 0;
                    ((Hero *)g_hero_state)->i[0x229C / 4] = 9;
                    ((Hero *)g_hero_state)->c[0x22B5] = 0;
                    ((UView *)(temp_s4))->b[0x2F4] = 0U;
                } else {
                    ((Hero *)g_hero_state)->c[0x22B5] = 1;
                    func_US2_L01_003C1CA8(arg0);
                }
            }
            if ((((UView *)(temp_s4))->b[0x2F4] == 0) && (var_s2 == 0)) {
                vec_scale_to_length((sp + 4), arg0 + 0xC0, g_swamp_monster_scratch_length);
                vec_scale_to_length((sp + 8), (sp + 4), g_swamp_monster_move_speed * 0.016666668f);
                temp_f20_3 = vec_length_xy((sp + 8));
                sp[10] = temp_f20_3 * (math_square(1.0f - (temp_f0_3 * 0.006666667f)) * 0.7f);
                qcopy(&((Hero *)g_hero_state)->b[0xF0], sp + 8);
                qcopy(&((Hero *)g_hero_state)->b[0x110], sp + 8);
                FastVecAdd(&((Hero *)g_hero_state)->b[0x80], &((Hero *)g_hero_state)->b[0x80], (sp + 8));
            }
            if (var_s2 != 0) {
                ((UView *)(arg0))->i[0x27] = (s32) (((UView *)(arg0))->i[0x27] & ~0x30);
                *(s32 *)(arg0 + 0x98) = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                if (g_game_mode == 0x6F) {
                    func_US2_L01_002BEEA8(0x16, 1);
                }
            }
            if (((UView *)(arg0))->b[0x60] & 2) {
                ((UView *)(arg0))->i[0x27] = (s32) (((UView *)(arg0))->i[0x27] & ~0x30);
                ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                moby_set_animation_and_speed(arg0, 0xC, 0, 0x14);
                moby_set_state(arg0, 0, 5);
                if (g_game_mode == 0x6F) {
                    func_US2_L01_002BEEA8(0x16, 1);
                }
            }
        } else {
            if (((UView *)(arg0))->b[0x95] == 4) {
                temp_v1_11 = ((UView *)(temp_s4))->b[0x2F4];
                if (temp_v1_11 == 1) {
                    g_grab_flag = temp_v1_11;
                }
            }
        }
        break;
    case 5:                                         /* switch 1 */
        if (((UView *)(arg0))->b[0x60] & 2) {
            moby_set_state(arg0, 0, 2);
            moby_set_animation_and_speed(arg0, (s32) ((UView *)(temp_s4))->b[0x2E1], 0, 0x14);
            ((UView *)(arg0))->b[0xA8] = 0xFF;
        }
        break;
    case 6:                                         /* switch 1 */
        temp_v0_4 = moby_dispatch_action_by_kind(arg0, temp_s4 + 0x60);
        if (temp_v0_4 & 1) {
            moby_set_state(arg0, 0, 7);
        } else if (temp_v0_4 & 2) {
            moby_set_animation_and_speed(arg0, (s32) ((UView *)(temp_s4))->b[0x2E1], 0, 0xC);
            moby_set_state(arg0, 0, 2);
        }
        break;
    case 7:                                         /* switch 1 */
        ((UView *)(arg0))->i[0x12] = 0;
        ((UView *)(arg0))->uh[0x1A] = (u16) (((UView *)(arg0))->uh[0x1A] | 0x41);
        temp_a0_3 = ((u8 *)((UView *)(temp_s4))->p[0xB9]);
        if (temp_a0_3 != NULL) {
            cam_end_override(temp_a0_3);
            ((u8 *)((UView *)(temp_s4))->p[0xB9]) = NULL;
        }
        temp_s1 = arg0 + 0x10;
        temp_v0_5 = SpawnGoldBolt(temp_s1, 1, -1, -1);
        ((u8 *)((UView *)(temp_s4))->p[0xC0]) = temp_v0_5;
        if (temp_v0_5 != NULL) {
            func_US2_L01_002BEEA8(0x6F, 1);
            temp_s0_2 = temp_s4 + 0x2A0;
            temp_v0_6 = ((u8 *)((UView *)(temp_s4))->p[0xC0]);
            *(f32 *)(temp_v0_6 + 0x18) = (f32) (*(f32 *)(temp_v0_6 + 0x18) - 0.5f);
            FastVecSub(temp_s0_2, temp_s1, g_hero_position);
            ((UView *)(temp_s4))->f[0xAA] = (f32) (((UView *)(temp_s4))->f[0xAA] + 1.0f);
            FastVecScale(temp_s0_2, temp_s0_2, 0.85f);
            ((UView *)(temp_s4))->f[0xAB] = 1.0f;
            moby_set_state(arg0, 0, 8);
        }
        break;
    case 8:                                         /* switch 1 */
        temp_v1_13 = ((UView *)(temp_s4))->i[0xBE];
        temp_f21_3 = ((UView *)(temp_s4))->f[0xAB] - 0.00625f;
        ((UView *)(temp_s4))->f[0xAB] = temp_f21_3;
        if (temp_v1_13 != -1) {
            temp_v1_14 = (*(s32 *)((u8 *)((*(u8 **)((u8 *)((temp_v1_13 << 8) + (s32)g_moby_l01_table) + 0x68))) + 0x28));
            temp_a2 = D_L01_001B264C_sda;
            if (temp_v1_14 != -1) {
                temp_a1_2 = temp_v1_14 << 7;
                qcopy(g_hero_position, (u8 *)(temp_a1_2 + (s32)temp_a2) + 0x30);
                temp_a1_3 = (u8 *)(temp_a1_2 + (s32)temp_a2);
                qcopy(g_hero_position + 0x10, (u8 *)temp_a1_3 + 0x70);
            }
        }
        if ((u8) *(u8 *)(((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x20) < 2U) {
            temp_v1_15 = ((UView *)(temp_s4))->i[0xBE];
            if (temp_v1_15 != -1) {
                temp_v1_16 = (u8 *)((temp_v1_15 << 8) + (s32)D_L01_001B255C_sda);
                if (*(u8 *)(temp_v1_16 + 0xBC) != 0) {
                    *(u8 *)(temp_v1_16 + 0xBC) = 0U;
                    func_US2_L01_00395620(g_moby_l01_table + (((UView *)(temp_s4))->i[0xBE] << 8));
                }
            }
            temp_s1_2 = temp_s4 + 0x2A0;
            temp_s0_3 = ((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x10;
            vec_scale_to_length(temp_s0_3, temp_s1_2, temp_f21_3 * FastVecLength(temp_s1_2));

            *(f32 *)((((u8 *)((UView *)(temp_s4))->p[0xC0])) + 0x18) = (f32) (*(f32 *)((((u8 *)((UView *)(temp_s4))->p[0xC0])) + 0x18) + (math_fast_sin_or_cos_b(temp_f21_3 * 3.1415927f) * 4.0f));
            temp_a0_4 = ((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x10;
            FastVecAdd(temp_a0_4, temp_a0_4, g_hero_position);
            temp_s1_3 = *(u8 **)(((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x68);
            temp_s0_4 = temp_s1_3 + 0x10;
            FastVecSub(temp_s0_4, arg0 + 0x10, g_hero_position);
            vec_scale_to_length(temp_s0_4, temp_s0_4, 2.5f);
            *(f32 *)(temp_s1_3 + 0x1C) = FastAddRotations(mat_fast_helper_a(*(f32 *)(temp_s1_3 + 0x10), *(f32 *)(temp_s1_3 + 0x14)), 3.1415927f);
            FastVecAdd(temp_s0_4, temp_s0_4, g_hero_position);
            func_002A0F48(((u8 *)((UView *)(temp_s4))->p[0xC0]));
            ((UView *)(temp_s4))->f[0xAB] = temp_f21_3;
        }
        temp_a0_5 = ((u8 *)((UView *)(temp_s4))->p[0xC0]);
        if ((temp_a0_5 == NULL) || (*(s16 *)(temp_a0_5 + 0xAA) != 0x1250) || (temp_v1_17 = *(u8 *)(temp_a0_5 + 0x20), (temp_v1_17 == 0xFE)) || (temp_v1_17 == 0xFD)) {
            func_US2_002A7AA8(arg0, 0, 3);

            if ((((UView *)(arg0))->b[0xB0]) != 0xFF) {
                moby_mark_table_entry_flagged((u32) (((UView *)(arg0))->b[0xB0]));
            }
            if (((UView *)(temp_s4))->i[0xC1] != -1) {
                FadeToBlack(0x10);
                load_scene_chunk(0, 0);
                temp_a0_6 = g_swamp_patrol_positions + (((UView *)(temp_s4))->i[0xC1] << 7);
                hero_reset_position_and_direction(temp_a0_6 + 0x30, temp_a0_6 + 0x70, 0, 1);
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
            }
            temp_v1_19 = ((UView *)(temp_s4))->i[0xC2];
            if (temp_v1_19 != -1) {
                (*(s8 *)((u8 *)((temp_v1_19 << 8) + (s32)D_L01_001B255C_sda) + 0xBC)) = 1;
            }
            script_queue_keyed_request(((UView *)(temp_s4))->i[0xC5], ((UView *)(temp_s4))->i[0xC7]);
            moby_mark_spawned(arg0);
            return;
        }
        break;
    }
        temp_f1 = level_get_water_height();
        if ((((UView *)(arg0))->b[0x95] != 0) && (((HeroV *)g_hero_state)->z < (temp_f1 - 1.8f)) && (((HeroV *)g_hero_state)->z < (((UView *)(arg0))->f[0x6] - 1.0f)) && (vec_distance_xy(arg0 + 0x10, &((HeroV *)g_hero_state)->x) < 10.0f)) {
            hero_record_play_counters();
        }
        swamp_monster_update_timers(arg0);
}
