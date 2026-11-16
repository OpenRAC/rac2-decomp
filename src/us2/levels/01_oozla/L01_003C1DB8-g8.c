#include "names.h"
/* func_US2_L01_003C1DB8, the USA v2.00 copy of func_L01_003C09C0: the same C, where inner state 4
   gains an else branch calling func_L01_003C06E8.
   (Oozla, 7,456 bytes): a moby update with an outer switch on the state byte
   at 0x95 and per-state inner switches.  One function: one prologue, one return.
   Byte offsets into the moby (moby) and its state block (+0x68) go through the UView union so the
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
extern void swamp_monster_hold_hero_us2(void *);
extern u8 *moby_spawn_thrown_object(void *, void *, void *, float);
extern void *SpawnGoldBolt(void *, int, int, int);
extern void camera_pose_trigger_update_us2(void *);
extern int func_001163B0(void);
#define NULL ((void *)0)
extern void moby_mark_table_entry_flagged(u32 a0);
extern void func_002A0F48(void *);
extern void SetDeathBits_us2(void *, int, int);
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
extern s32 hero_set_move_state_us2(s32 action, s32 animate);
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

/* Per-frame update of the swamp monster (moby class 2644): runs its attack states and hit reactions. */
void swamp_monster_update_us2(u8 *moby) {
    float sp[20] __attribute__((aligned(16)));
    f32 float_val_0;
    f32 float_val_0_2;
    f32 float_val_0_3;
    f32 float_val_1;
    f32 float_val_20;
    f32 float_val_20_2;
    f32 float_val_20_3;
    f32 float_val_21;
    f32 float_val_21_2;
    f32 float_val_21_3;
    f32 float_val_22;
    f32 float_val_23;
    f32 float_var_12_2;
    u8 *ptr_val_a0_6;
    s32 int_val_a1;
    s32 int_val_a1_2;
    u8 *ptr_val_a2;
    s32 int_val_v0_4;
    s32 int_val_v1_13;
    s32 int_val_v1_14;
    s32 int_val_v1_15;
    s32 int_val_v1_19;
    s32 int_val_v1_3;
    s32 int_var_s0;
    s32 int_var_s1;
    s32 int_var_s1_2;
    s32 int_var_s2;
    s32 int_var_s5;
    u8 *ptr_val_a0;
    u8 *ptr_val_a0_3;
    u8 *ptr_val_s1;
    u8 *ptr_val_v1_12;
    u8 int_val_s0;
    u8 int_val_v0_2;
    u8 int_val_v1;
    u8 int_val_v1_10;
    u8 int_val_v1_11;
    u8 int_val_v1_17;
    u8 int_val_v1_18;
    u8 int_val_v1_2;
    u8 int_val_v1_5;
    u8 int_val_v1_6;
    u8 int_val_v1_7;
    u8 int_val_v1_8;
    u8 int_val_v1_9;
    u8 *ptr_val_a0_2;
    u8 *ptr_val_a0_4;
    u8 *ptr_val_a0_5;
    u8 *ptr_val_a1_3;
    u8 *ptr_val_s0_2;
    u8 *ptr_val_s0_3;
    u8 *ptr_val_s0_4;
    u8 *ptr_val_s1_2;
    u8 *ptr_val_s1_3;
    u8 *ptr_val_s4;
    u8 *ptr_val_v0;
    u8 *ptr_val_v0_3;
    u8 *ptr_val_v0_5;
    u8 *ptr_val_v0_6;
    u8 *ptr_val_v0_7;
    u8 *ptr_val_v1_16;

    ptr_val_s4 = ((u8 *)((UView *)(moby))->p[0x1A]);
    swamp_monster_update_hit_reaction();
    int_val_v1 = ((UView *)(moby))->b[0x95];
    switch (int_val_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if ((((UView *)(moby))->b[0xB0] != 0xFF) && (g_moby_group_flags[((UView *)(moby))->b[0xB0] + (g_current_map_index * 0x10)] & 0x80)) {
            int_val_v1_3 = ((UView *)(ptr_val_s4))->i[0xC2];
            if (int_val_v1_3 != -1) {
                D_L01_001B255C_sda[(int_val_v1_3 << 8) + 0xBC] = 1;
            }
            moby_mark_spawned(moby);
            return;
        }
        swamp_monster_init(moby);
    default:
        break;
    case 1:                                         /* switch 1 */
        if (((UView *)(ptr_val_s4))->i[0x49] == 1) {
            if (((u8 *)((UView *)(ptr_val_s4))->p[0xB9]) == NULL) {
                script_queue_keyed_request(((UView *)(ptr_val_s4))->i[0xC4], ((UView *)(ptr_val_s4))->i[0xC6]);
                ((u8 *)((UView *)(ptr_val_s4))->p[0xB9]) = cam_alloc_override_slot(5);
            }
            moby_set_state(moby, 0, 2);
        }
        break;
    case 2:                                         /* switch 1 */
        float_val_0 = swamp_monster_move_around_arena(moby);
        if (float_val_0 == -1000.0f) {
            ptr_val_a0 = ((u8 *)((UView *)(ptr_val_s4))->p[0xB9]);
            if (ptr_val_a0 != NULL) {
                cam_end_override(ptr_val_a0);
                ((u8 *)((UView *)(ptr_val_s4))->p[0xB9]) = NULL;
            }
            moby_set_state(moby, 0, 1);
            moby_set_animation_and_speed(moby, 0, 0, 0xA);
        } else {
            ptr_val_v0 = ((u8 *)((UView *)(ptr_val_s4))->p[0x48]);
            float_val_21 = FastDiffRots(((UView *)(moby))->f[0x3E], mat_fast_helper_a(*(f32 *)(ptr_val_v0 + 0x10) - ((UView *)(moby))->f[0x4], *(f32 *)(ptr_val_v0 + 0x14) - ((UView *)(moby))->f[0x5]));
            switch (((UView *)(moby))->b[0xBC]) {                    /* switch 2 */
            case 0:                                 /* switch 2 */
                if ((float_val_0 <= g_swamp_monster_range_near) && (float_val_21 < (g_swamp_monster_aim_angle_near * 0.017453294f)) && (((UView *)(ptr_val_s4))->h[0x16E] == 0)) {
                    int_var_s0 = 1;
                    swamp_monster_start_claw_attack(moby);
                } else {
                    int_var_s0 = g_swamp_monster_attack_threshold < (s32) ((UView *)(moby))->uh[0x4B];
                }
                if (int_var_s0 != 0) {
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(moby))->b[0xBC] = 1U;
                }
                if (((UView *)(ptr_val_s4))->f[0x8] < (2.0f * IntToFloat((s32) ((UView *)(ptr_val_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                    ((UView *)(ptr_val_s4))->b[0x2E1] = 5U;
                    ((UView *)(ptr_val_s4))->c[0x2E2] = 0xE;
                    ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                    ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_c * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(moby))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(moby, 0x10, 0, 0xD);
                    moby_set_state(moby, 0, 5);
                }
            default:                                /* switch 2 */
                break;
            case 1:                                 /* switch 2 */
            case 2:                                 /* switch 2 */
                int_val_v1_5 = ((UView *)(moby))->b[0xBC];
                int_var_s1 = 0;
                switch (int_val_v1_5) {                /* switch 3; irregular */
                case 1:                             /* switch 3 */
                    if ((float_val_0 <= g_swamp_monster_range_near) && (float_val_21 < (g_swamp_monster_aim_angle_near * 0.017453294f))) {
                        if ((math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(ptr_val_s4))->h[0x16E] == 0)) {
                            swamp_monster_start_claw_attack(moby);
                        } else {
                            goto block_36;
                        }
                    } else {
block_36:
                        if ((g_swamp_monster_range_near < float_val_0) && (float_val_0 <= g_swamp_monster_range_b) && (float_val_21 < (g_swamp_monster_aim_angle_mid * 0.017453294f))) {
                            if ((math_random_int_below(g_swamp_monster_attack_odds_b - 1) == 0) && (((UView *)(ptr_val_s4))->h[0x16D] == 0)) {
                                swamp_monster_start_attack_c(moby);
                            } else {
                                goto block_43;
                            }
                        } else {
block_43:
                            if (g_swamp_monster_far_range < float_val_0) {
                                ((UView *)(ptr_val_s4))->b[0x2E1] = 4U;
                                ((UView *)(ptr_val_s4))->c[0x2E2] = 0x16;
                                ((UView *)(ptr_val_s4))->c[0x2E0] = 0;
                                moby_set_controller_speed_limits(moby, g_swamp_monster_alt_limit_speed * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_alt_limit_angular * 0.0000048481375f, g_swamp_monster_alt_limit_turn * 0.00029088825f);
                                ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                                ((UView *)(moby))->b[0xBC] = 2U;
                                ((UView *)(ptr_val_s4))->c[0x71] = 0xF;
                                ((UView *)(ptr_val_s4))->c[0x72] = 0xF;
                                moby_set_animation_and_speed(moby, 3, 0, 0xD);
                                moby_set_state(moby, 0, 5);
                            }
                        }
                    }
                    break;
                case 2:                             /* switch 3 */
                    int_var_s1 = 0x3C;
                    ((UView *)(moby))->i[0x26] = 0;
                    if ((float_val_0 <= g_swamp_monster_range_near) && ((int_val_v1_6 = ((UView *)(moby))->b[0x42], (int_val_v1_6 == 0x16)) || (int_val_v1_6 == 0))) {
                        ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                        ((UView *)(ptr_val_s4))->b[0x2E1] = 1U;
                        ((UView *)(ptr_val_s4))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                        ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                        ((UView *)(moby))->b[0xBC] = 1U;
                        ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                        ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                        moby_set_state(moby, 0, 5);
                    }
                    break;
                }
                if (((UView *)(ptr_val_s4))->f[0x8] < (2.0f * IntToFloat((s32) ((UView *)(ptr_val_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                    ((UView *)(ptr_val_s4))->b[0x2E1] = 5U;
                    ((UView *)(ptr_val_s4))->c[0x2E2] = 0xE;
                    ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                    ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_c * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(moby))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(moby, 0x10, 0, int_var_s1 + 0xD);
                    moby_set_state(moby, 0, 5);
                }
                break;
            case 3:                                 /* switch 2 */
            case 4:                                 /* switch 2 */
            case 5:                                 /* switch 2 */
            case 6:                                 /* switch 2 */
                int_val_s0 = ((UView *)(moby))->b[0xBC];
                switch (int_val_s0) {                  /* switch 4; irregular */
                case 3:                             /* switch 4 */
                    if ((float_val_0 <= g_swamp_monster_range_a) && (float_val_21 < (g_swamp_monster_aim_angle_a * 0.017453294f)) && (((UView *)(ptr_val_s4))->h[0x16F] == 0)) {
                        moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_d * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                        ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_c;
                        ((UView *)(moby))->b[0xBC] = 4U;
                        ((UView *)(ptr_val_s4))->b[0x2E3] = (u8) g_swamp_monster_vars_byte;
                        ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                        ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                        ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                        ((UView *)(ptr_val_s4))->b[0x2E1] = 1U;
                        ((UView *)(ptr_val_s4))->c[0x2E2] = 0;
                        swamp_monster_start_grab_attack(moby);
                    }
                    break;
                case 4:                             /* switch 4 */
                    if ((g_swamp_monster_range_near < float_val_0) && (float_val_0 <= g_swamp_monster_range_c) && (float_val_21 < (g_swamp_monster_aim_angle_b * 0.017453294f)) && (((UView *)(ptr_val_s4))->h[0x16E] == 0)) {
                        if (vec_fast_helper_a(ptr_val_s4 + 0x2E3) != 0) {
                            moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                            ((UView *)(moby))->b[0xBC] = 5U;
                            ((UView *)(ptr_val_s4))->c[0x2E0] = 0;
                            ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                            ((UView *)(ptr_val_s4))->b[0x2E1] = int_val_s0;
                            ((UView *)(ptr_val_s4))->c[0x2E2] = 0x16;
                            ((UView *)(ptr_val_s4))->c[0x71] = 0xF;
                            ((UView *)(ptr_val_s4))->c[0x72] = 0xF;
                            moby_set_animation_and_speed(moby, 3, 0, 0xD);
                            moby_set_state(moby, 0, 5);
                        }
                        swamp_monster_start_attack_b(moby);
                    } else if ((float_val_0 <= g_swamp_monster_range_near) && (float_val_0 <= g_swamp_monster_range_c) && (float_val_21 < (g_swamp_monster_aim_angle_b * 0.017453294f)) && (((UView *)(ptr_val_s4))->h[0x16E] == 0)) {
                        swamp_monster_start_claw_attack(moby);
                    }
                    break;
                case 5:                             /* switch 4 */
                    ((UView *)(moby))->i[0x26] = 0;
                    if (float_val_0 <= g_swamp_monster_range_near) {
                        int_val_v1_7 = ((UView *)(moby))->b[0x42];
                        if (int_val_v1_7 != 0x16) {
                            if (int_val_v1_7 == 0) {
                                goto block_72;
                            }
                        } else {
block_72:
                            ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                            ((UView *)(ptr_val_s4))->b[0x2E1] = 1U;
                            ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                            ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                            ((UView *)(ptr_val_s4))->c[0x2E2] = 0;
                            moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                            ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_c;
                            ((UView *)(moby))->b[0xBC] = 6U;
                            ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                            moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                            moby_set_state(moby, 0, 5);
                        }
                    }
                    break;
                case 6:                             /* switch 4 */
                    ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                    if ((float_val_0 <= g_swamp_monster_range_c) && (float_val_21 < (g_swamp_monster_aim_angle_near * 0.017453294f)) && (math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(ptr_val_s4))->h[0x16E] == 0)) {
                        if ((g_swamp_monster_range_near < float_val_0) && (func_001163B0() & 1)) {
                            swamp_monster_start_attack_b(moby);
                        } else {
                            swamp_monster_start_claw_attack(moby);
                        }
                    }
                    break;
                }
                int_val_v0_2 = ((UView *)(moby))->b[0xBC];
                if ((int_val_v0_2 != 5) && (int_val_v0_2 < 7U) && (g_swamp_monster_far_range < float_val_0)) {
                    moby_set_controller_speed_limits(moby, g_swamp_monster_alt_limit_speed * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_alt_limit_angular * 0.0000048481375f, g_swamp_monster_alt_limit_turn * 0.00029088825f);
                    ((UView *)(moby))->b[0xBC] = 5U;
                    ((UView *)(ptr_val_s4))->c[0x2E0] = 0;
                    ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(ptr_val_s4))->c[0x71] = 0xF;
                    ((UView *)(ptr_val_s4))->c[0x72] = 0xF;
                    ((UView *)(ptr_val_s4))->b[0x2E1] = 4U;
                    ((UView *)(ptr_val_s4))->c[0x2E2] = 0x16;
                }
                if (((UView *)(ptr_val_s4))->f[0x8] < (IntToFloat((s32) ((UView *)(ptr_val_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                    ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(ptr_val_s4))->b[0x2E1] = 5U;
                    ((UView *)(ptr_val_s4))->c[0x2E2] = 0xE;
                    ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                    ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_e * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    ((UView *)(moby))->b[0xBC] = 7U;
                    moby_set_animation_and_speed(moby, 0x10, 0, 0xD);
                    moby_set_state(moby, 0, 5);
                }
                break;
            case 7:                                 /* switch 2 */
                if ((float_val_0 <= g_swamp_monster_range_a) && (float_val_21 < (g_swamp_monster_aim_angle_a * 0.017453294f)) && (((UView *)(ptr_val_s4))->h[0x16F] == 0)) {
                    ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(moby))->b[0xBC] = 9U;
                    ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                    ((UView *)(ptr_val_s4))->b[0x2E1] = 1U;
                    ((UView *)(ptr_val_s4))->c[0x2E2] = 0;
                    ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                    ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_f * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                    swamp_monster_start_grab_attack(moby);
                }
                break;
            case 8:                                 /* switch 2 */
                ((UView *)(moby))->i[0x26] = 0;
                if (float_val_0 <= g_swamp_monster_range_near) {
                    int_val_v1_8 = ((UView *)(moby))->b[0x42];
                    if (int_val_v1_8 != 0x16) {
                        if (int_val_v1_8 == 0) {
                            goto block_95;
                        }
                    } else {
block_95:
                        ((UView *)(ptr_val_s4))->c[0x2E0] = 1;
                        ((UView *)(ptr_val_s4))->b[0x2E1] = 1U;
                        ((UView *)(ptr_val_s4))->c[0x71] = 0x13;
                        ((UView *)(ptr_val_s4))->c[0x72] = 0x13;
                        ((UView *)(ptr_val_s4))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00027777778f, g_swamp_monster_limit_move_b * 0.016666668f, g_swamp_monster_limit_angular_a * 0.0000048481375f, g_swamp_monster_limit_turn_a * 0.00029088825f);
                        ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                        ((UView *)(moby))->b[0xBC] = 9U;
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                        moby_set_state(moby, 0, 5);
                    }
                }
                break;
            case 9:                                 /* switch 2 */
                ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                if ((float_val_0 <= g_swamp_monster_range_near) && (float_val_21 < (g_swamp_monster_aim_angle_near * 0.017453294f))) {
                    if ((math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(ptr_val_s4))->h[0x16E] == 0)) {
                        if (func_001163B0() & 1) {
                            swamp_monster_start_claw_attack(moby);
                        } else {
                            swamp_monster_start_attack_b(moby);
                        }
                    } else {
                        goto block_105;
                    }
                } else {
block_105:
                    if ((g_swamp_monster_range_near < float_val_0) && (float_val_0 <= g_swamp_monster_range_b) && (float_val_21 < (g_swamp_monster_aim_angle_mid * 0.017453294f))) {
                        if ((math_random_int_below(g_swamp_monster_attack_odds_b - 1) == 0) && (((UView *)(ptr_val_s4))->h[0x16D] == 0)) {
                            swamp_monster_start_attack_c(moby);
                        } else {
                            goto block_112;
                        }
                    } else {
block_112:
                        if (g_swamp_monster_far_range < float_val_0) {
                            ((UView *)(ptr_val_s4))->b[0x2E1] = 4U;
                            ((UView *)(ptr_val_s4))->c[0x2E2] = 0x16;
                            ((UView *)(ptr_val_s4))->c[0x2E0] = 0;
                            moby_set_controller_speed_limits(moby, g_swamp_monster_alt_limit_speed * 0.00027777778f, g_swamp_monster_alt_limit_move * 0.016666668f, g_swamp_monster_alt_limit_angular * 0.0000048481375f, g_swamp_monster_alt_limit_turn * 0.00029088825f);
                            ((UView *)(ptr_val_s4))->f[0xBB] = (f32) g_swamp_monster_range_near;
                            ((UView *)(moby))->b[0xBC] = 8U;
                            ((UView *)(ptr_val_s4))->c[0x71] = 0xF;
                            ((UView *)(ptr_val_s4))->c[0x72] = 0xF;
                            moby_set_animation_and_speed(moby, 3, 0, 0xD);
                            moby_set_state(moby, 0, 5);
                        }
                    }
                }
                break;
            }
            if ((((UView *)(moby))->b[0x42] == 0x16) && (((UView *)(moby))->b[0x60] & 2)) {
                ((UView *)(ptr_val_s4))->c[0x2E2] = 0;
                moby_set_animation_and_speed(moby, 0, 0, 0xA);
            }
        }
        break;
    case 3:                                         /* switch 1 */
        float_val_20 = moby_get_anim_value(moby);
        switch (((UView *)(moby))->b[0x20]) {                        /* switch 5; irregular */
        case 1:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if ((float_val_20 > 44.0f) && (float_val_20 < 68.0f)) {
                int_val_v1_10 = ((UView *)(moby))->b[0x42];
                int_var_s5 = -1;
                if (int_val_v1_10 == 6) {
                    int_var_s5 = 0;
                } else if (int_val_v1_10 == 7) {
                    int_var_s5 = 4;
                }
                if (int_var_s5 >= 0) {
                    moby_transform_joint_to_world(moby, int_var_s5, (sp + 4));
                    for (int_var_s1_2 = 1; int_var_s1_2 < 3; int_var_s1_2++) {
                        part_init_effect_record((sp + 8), (s32) moby, 1, (f32) ((UView *)(ptr_val_s4))->b[0x34]);
                        qcopy(sp, sp + 4);
                        moby_transform_joint_to_world(moby, int_var_s5 + int_var_s1_2, sp + 4);
                        coll_process_hit(0.5f, (s32) (sp + 4), 0, (s32) moby, (s32) (sp + 8));
                        sp[4] += math_random_float_range(-0.3f, 0.3f);
                        sp[5] += math_random_float_range(-0.3f, 0.3f);
                        sp[6] += math_random_float_range(-0.3f, 0.3f);
                        CollLine(sp, (sp + 4), 9, moby, (sp + 8));
                    }
                }
            }
            break;
        case 2:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if (math_is_value_within_step_us2((u8 *) moby, 16.0f) != 0) {
                moby_transform_joint_to_world(moby, 0xA, sp);
                FastVecSub((sp + 4), ((u8 *)((UView *)(ptr_val_s4))->p[0x48]) + 0x10, sp);
                vec_scale_to_length((sp + 4), (sp + 4), g_swamp_monster_shot_speed * 0.016666668f);
                sp[6] = weapon_compute_shot_launch_speed(sp, ((u8 *)((UView *)(ptr_val_s4))->p[0x48]) + 0x10, NULL, g_swamp_monster_shot_speed * 0.016666668f, -(g_swamp_monster_shot_gravity * 0.00027777778f));
                moby_spawn_thrown_object(sp, (sp + 4), moby, (f32) ((UView *)(ptr_val_s4))->b[0x34]);
            }
            break;
        case 3:                                     /* switch 5 */
            if ((float_val_20 > 34.0f) && (float_val_20 < 41.0f)) {
                int_val_a1 = (func_001163B0() & 1) | 8;
                coll_test_hit_at_bone(moby, 2.2f, (f32) ((UView *)(ptr_val_s4))->b[0x34], int_val_a1, 1, 1.0f, 0, 1, 0);
            }
            break;
        case 4:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if (((UView *)(ptr_val_s4))->b[0x2F4] == 0) {
                if (float_val_20 > 12.0f) {
                    if (float_val_20 <= 17.0f) {
                        moby_transform_joint_to_world(moby, 0xC, sp);
                        sp[2] -= 2.4f;
                        if ((fast_vec_dist(sp, &((HeroV *)g_hero_state)->x) < g_swamp_monster_hero_close_range) && (*(s32 *)(g_hero_state + 0x2294) != 0x6F)) {
                            ((UView *)(ptr_val_s4))->b[0x2F4] = 1U;
                        }
                    } else {
                        goto block_149;
                    }
                } else {
block_149:
                    if ((float_val_20 > 17.0f) && (float_val_20 < 19.0f)) {
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        int_val_a1 = (func_001163B0() & 1) | 0xC;
                        coll_test_hit_at_bone(moby, 2.0f, (f32) ((UView *)(ptr_val_s4))->b[0x35], int_val_a1, 1, 1.0f, 0, 1, 0);
                    }
                }
            } else if (float_val_20 > 19.0f) {
                ((HeroV *)g_hero_state)->a22b5 = 1;
            }
            break;
        }
        if (((UView *)(ptr_val_s4))->b[0x2F4] != 0) {
            swamp_monster_hold_hero_us2(moby);
            if (((UView *)(moby))->b[0x60] & 2) {
                if (((HeroV *)g_hero_state)->a24cc < 2) {
                    hero_record_play_counters();
                } else {
                    part_init_effect_record(sp, (s32) moby, 1, (f32) ((UView *)(ptr_val_s4))->b[0x36]);
                    QueueMobyImpact(((HeroV *)g_hero_state)->a2290, sp);
                }
                ((HeroV *)g_hero_state)->a22b5 = 1;
                moby_set_animation_and_speed(moby, 0xB, 0, 0x14);
                moby_set_state(moby, 0, 4);
            }
        } else {
            if (((UView *)(moby))->b[0x60] & 2) {
                ((UView *)(moby))->i[0x27] = (s32) (((UView *)(moby))->i[0x27] & ~0x30);
                moby_set_state(moby, 0, 2);
                moby_set_animation_and_speed(moby, 0, 0, 0x14);
            }
        }
        break;
    case 4:                                         /* switch 1 */
        float_val_23 = moby_get_anim_value(moby);
        ptr_val_v0_3 = (u8 *)((((UView *)(ptr_val_s4))->i[0xB3] << 7) + (s32)g_swamp_patrol_positions);
        float_val_0_2 = mat_fast_helper_a(*(f32 *)(ptr_val_v0_3 + 0x30) - ((UView *)(moby))->f[0x4], *(f32 *)(ptr_val_v0_3 + 0x34) - ((UView *)(moby))->f[0x5]);
        float_val_22 = FastAddRotations(float_val_0_2, 1.5707965f);
        float_val_21_2 = fast_subtract_rotations(float_val_0_2, 1.5707965f);
        float_val_20_2 = FastDiffRots(((UView *)(moby))->f[0x3E], float_val_22);
        moby_start_effect_from_entry(moby, float_val_20_2 < FastDiffRots(((UView *)(moby))->f[0x3E], float_val_21_2) ? float_val_22 : float_val_21_2);
        if (((UView *)(moby))->b[0x42] == 0xB) {
            int_var_s2 = 1;
            moby_transform_joint_to_world(moby, 0xE, sp);
            float_val_0_3 = fast_vec_dist(sp, &((Hero *)g_hero_state)->b[0x80]);
            if (!(float_val_0_3 > 13.0f)) {
                int_var_s2 = 0;
            }
            if (((UView *)(ptr_val_s4))->b[0x2F4] != 0) {
                if (float_val_23 > 33.0f) {
                    hero_set_move_state_us2(0x16, 1);
                    ((Hero *)g_hero_state)->i[0x2294 / 4] = 0x6F;
                    ((Hero *)g_hero_state)->i[0x24A0 / 4] = 0;
                    ((Hero *)g_hero_state)->i[0x229C / 4] = 9;
                    ((Hero *)g_hero_state)->c[0x22B5] = 0;
                    ((UView *)(ptr_val_s4))->b[0x2F4] = 0U;
                } else {
                    ((Hero *)g_hero_state)->c[0x22B5] = 1;
                    swamp_monster_hold_hero_us2(moby);
                }
            }
            if ((((UView *)(ptr_val_s4))->b[0x2F4] == 0) && (int_var_s2 == 0)) {
                vec_scale_to_length((sp + 4), moby + 0xC0, g_swamp_monster_scratch_length);
                vec_scale_to_length((sp + 8), (sp + 4), g_swamp_monster_move_speed * 0.016666668f);
                float_val_20_3 = vec_length_xy((sp + 8));
                sp[10] = float_val_20_3 * (math_square(1.0f - (float_val_0_3 * 0.006666667f)) * 0.7f);
                qcopy(&((Hero *)g_hero_state)->b[0xF0], sp + 8);
                qcopy(&((Hero *)g_hero_state)->b[0x110], sp + 8);
                FastVecAdd(&((Hero *)g_hero_state)->b[0x80], &((Hero *)g_hero_state)->b[0x80], (sp + 8));
            }
            if (int_var_s2 != 0) {
                ((UView *)(moby))->i[0x27] = (s32) (((UView *)(moby))->i[0x27] & ~0x30);
                *(s32 *)(moby + 0x98) = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                if (g_game_mode == 0x6F) {
                    hero_set_move_state_us2(0x16, 1);
                }
            }
            if (((UView *)(moby))->b[0x60] & 2) {
                ((UView *)(moby))->i[0x27] = (s32) (((UView *)(moby))->i[0x27] & ~0x30);
                ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                moby_set_animation_and_speed(moby, 0xC, 0, 0x14);
                moby_set_state(moby, 0, 5);
                if (g_game_mode == 0x6F) {
                    hero_set_move_state_us2(0x16, 1);
                }
            }
        } else {
            if (((UView *)(moby))->b[0x95] == 4) {
                int_val_v1_11 = ((UView *)(ptr_val_s4))->b[0x2F4];
                if (int_val_v1_11 == 1) {
                    g_grab_flag = int_val_v1_11;
                }
            }
        }
        break;
    case 5:                                         /* switch 1 */
        if (((UView *)(moby))->b[0x60] & 2) {
            moby_set_state(moby, 0, 2);
            moby_set_animation_and_speed(moby, (s32) ((UView *)(ptr_val_s4))->b[0x2E1], 0, 0x14);
            ((UView *)(moby))->b[0xA8] = 0xFF;
        }
        break;
    case 6:                                         /* switch 1 */
        int_val_v0_4 = moby_dispatch_action_by_kind(moby, ptr_val_s4 + 0x60);
        if (int_val_v0_4 & 1) {
            moby_set_state(moby, 0, 7);
        } else if (int_val_v0_4 & 2) {
            moby_set_animation_and_speed(moby, (s32) ((UView *)(ptr_val_s4))->b[0x2E1], 0, 0xC);
            moby_set_state(moby, 0, 2);
        }
        break;
    case 7:                                         /* switch 1 */
        ((UView *)(moby))->i[0x12] = 0;
        ((UView *)(moby))->uh[0x1A] = (u16) (((UView *)(moby))->uh[0x1A] | 0x41);
        ptr_val_a0_3 = ((u8 *)((UView *)(ptr_val_s4))->p[0xB9]);
        if (ptr_val_a0_3 != NULL) {
            cam_end_override(ptr_val_a0_3);
            ((u8 *)((UView *)(ptr_val_s4))->p[0xB9]) = NULL;
        }
        ptr_val_s1 = moby + 0x10;
        ptr_val_v0_5 = SpawnGoldBolt(ptr_val_s1, 1, -1, -1);
        ((u8 *)((UView *)(ptr_val_s4))->p[0xC0]) = ptr_val_v0_5;
        if (ptr_val_v0_5 != NULL) {
            hero_set_move_state_us2(0x6F, 1);
            ptr_val_s0_2 = ptr_val_s4 + 0x2A0;
            ptr_val_v0_6 = ((u8 *)((UView *)(ptr_val_s4))->p[0xC0]);
            *(f32 *)(ptr_val_v0_6 + 0x18) = (f32) (*(f32 *)(ptr_val_v0_6 + 0x18) - 0.5f);
            FastVecSub(ptr_val_s0_2, ptr_val_s1, g_hero_position);
            ((UView *)(ptr_val_s4))->f[0xAA] = (f32) (((UView *)(ptr_val_s4))->f[0xAA] + 1.0f);
            FastVecScale(ptr_val_s0_2, ptr_val_s0_2, 0.85f);
            ((UView *)(ptr_val_s4))->f[0xAB] = 1.0f;
            moby_set_state(moby, 0, 8);
        }
        break;
    case 8:                                         /* switch 1 */
        int_val_v1_13 = ((UView *)(ptr_val_s4))->i[0xBE];
        float_val_21_3 = ((UView *)(ptr_val_s4))->f[0xAB] - 0.00625f;
        ((UView *)(ptr_val_s4))->f[0xAB] = float_val_21_3;
        if (int_val_v1_13 != -1) {
            int_val_v1_14 = (*(s32 *)((u8 *)((*(u8 **)((u8 *)((int_val_v1_13 << 8) + (s32)g_moby_l01_table) + 0x68))) + 0x28));
            ptr_val_a2 = D_L01_001B264C_sda;
            if (int_val_v1_14 != -1) {
                int_val_a1_2 = int_val_v1_14 << 7;
                qcopy(g_hero_position, (u8 *)(int_val_a1_2 + (s32)ptr_val_a2) + 0x30);
                ptr_val_a1_3 = (u8 *)(int_val_a1_2 + (s32)ptr_val_a2);
                qcopy(g_hero_position + 0x10, (u8 *)ptr_val_a1_3 + 0x70);
            }
        }
        if ((u8) *(u8 *)(((u8 *)((UView *)(ptr_val_s4))->p[0xC0]) + 0x20) < 2U) {
            int_val_v1_15 = ((UView *)(ptr_val_s4))->i[0xBE];
            if (int_val_v1_15 != -1) {
                ptr_val_v1_16 = (u8 *)((int_val_v1_15 << 8) + (s32)D_L01_001B255C_sda);
                if (*(u8 *)(ptr_val_v1_16 + 0xBC) != 0) {
                    *(u8 *)(ptr_val_v1_16 + 0xBC) = 0U;
                    camera_pose_trigger_update_us2(g_moby_l01_table + (((UView *)(ptr_val_s4))->i[0xBE] << 8));
                }
            }
            ptr_val_s1_2 = ptr_val_s4 + 0x2A0;
            ptr_val_s0_3 = ((u8 *)((UView *)(ptr_val_s4))->p[0xC0]) + 0x10;
            vec_scale_to_length(ptr_val_s0_3, ptr_val_s1_2, float_val_21_3 * FastVecLength(ptr_val_s1_2));

            *(f32 *)((((u8 *)((UView *)(ptr_val_s4))->p[0xC0])) + 0x18) = (f32) (*(f32 *)((((u8 *)((UView *)(ptr_val_s4))->p[0xC0])) + 0x18) + (math_fast_sin_or_cos_b(float_val_21_3 * 3.1415927f) * 4.0f));
            ptr_val_a0_4 = ((u8 *)((UView *)(ptr_val_s4))->p[0xC0]) + 0x10;
            FastVecAdd(ptr_val_a0_4, ptr_val_a0_4, g_hero_position);
            ptr_val_s1_3 = *(u8 **)(((u8 *)((UView *)(ptr_val_s4))->p[0xC0]) + 0x68);
            ptr_val_s0_4 = ptr_val_s1_3 + 0x10;
            FastVecSub(ptr_val_s0_4, moby + 0x10, g_hero_position);
            vec_scale_to_length(ptr_val_s0_4, ptr_val_s0_4, 2.5f);
            *(f32 *)(ptr_val_s1_3 + 0x1C) = FastAddRotations(mat_fast_helper_a(*(f32 *)(ptr_val_s1_3 + 0x10), *(f32 *)(ptr_val_s1_3 + 0x14)), 3.1415927f);
            FastVecAdd(ptr_val_s0_4, ptr_val_s0_4, g_hero_position);
            func_002A0F48(((u8 *)((UView *)(ptr_val_s4))->p[0xC0]));
            ((UView *)(ptr_val_s4))->f[0xAB] = float_val_21_3;
        }
        ptr_val_a0_5 = ((u8 *)((UView *)(ptr_val_s4))->p[0xC0]);
        if ((ptr_val_a0_5 == NULL) || (*(s16 *)(ptr_val_a0_5 + 0xAA) != 0x1250) || (int_val_v1_17 = *(u8 *)(ptr_val_a0_5 + 0x20), (int_val_v1_17 == 0xFE)) || (int_val_v1_17 == 0xFD)) {
            SetDeathBits_us2(moby, 0, 3);

            if ((((UView *)(moby))->b[0xB0]) != 0xFF) {
                moby_mark_table_entry_flagged((u32) (((UView *)(moby))->b[0xB0]));
            }
            if (((UView *)(ptr_val_s4))->i[0xC1] != -1) {
                FadeToBlack(0x10);
                load_scene_chunk(0, 0);
                ptr_val_a0_6 = g_swamp_patrol_positions + (((UView *)(ptr_val_s4))->i[0xC1] << 7);
                hero_reset_position_and_direction(ptr_val_a0_6 + 0x30, ptr_val_a0_6 + 0x70, 0, 1);
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
            }
            int_val_v1_19 = ((UView *)(ptr_val_s4))->i[0xC2];
            if (int_val_v1_19 != -1) {
                (*(s8 *)((u8 *)((int_val_v1_19 << 8) + (s32)D_L01_001B255C_sda) + 0xBC)) = 1;
            }
            script_queue_keyed_request(((UView *)(ptr_val_s4))->i[0xC5], ((UView *)(ptr_val_s4))->i[0xC7]);
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
        float_val_1 = level_get_water_height();
        if ((((UView *)(moby))->b[0x95] != 0) && (((HeroV *)g_hero_state)->z < (float_val_1 - 1.8f)) && (((HeroV *)g_hero_state)->z < (((UView *)(moby))->f[0x6] - 1.0f)) && (vec_distance_xy(moby + 0x10, &((HeroV *)g_hero_state)->x) < 10.0f)) {
            hero_record_play_counters();
        }
        swamp_monster_update_timers(moby);
}
