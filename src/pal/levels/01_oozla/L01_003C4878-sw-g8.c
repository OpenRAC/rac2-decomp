#include "names.h"
/* func_PAL_L01_003C4878, the PAL copy of func_L01_003C09C0: the same C, with the 50 Hz rates and
   the 50 Hz scale on one timer limit; state 4 gains a nearer-range retreat test, and state 5
   compares the range without the degrees-to-radians factor.
   (Oozla, 7,488 bytes): a moby update with an outer switch on the state byte
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
extern void swamp_monster_init_pal(void *);
extern void swamp_monster_update_timers(void *);
extern float swamp_monster_move_around_arena_pal(void *);
extern void swamp_monster_start_claw_attack_pal(void *);
extern void swamp_monster_start_attack_b_pal(void *);
extern void swamp_monster_start_attack_c_pal(void *);
extern void swamp_monster_start_grab_attack_pal(void *);
extern void swamp_monster_hold_hero_pal(void *);
extern u8 *moby_spawn_thrown_object(void *, void *, void *, float);
extern void *SpawnGoldBolt_pal(void *, int, int, int);
extern void update_camera_pose_trigger_pal(void *);
extern int func_001163B0(void);
#define NULL ((void *)0)
extern void moby_mark_table_entry_flagged(u32 a0);
extern void func_002A0F48(void *);
extern void SetDeathBits_pal(void *, int, int);
extern void moby_set_state(char *, int, int);
extern float math_square(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void part_init_effect_record(void *a0, int a1, int a2, float a3);
extern s32 coll_test_hit_at_bone(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern void QueueMobyImpact(s32, void *);
extern s32 math_is_value_within_step_pal(u8 *, f32);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_record_play_counters_pal(void);
extern void hero_reset_position_and_direction_pal(int a0, int a1, int a2, int a3);
extern void * cam_alloc_override_slot_pal(s32 size);
extern void cam_end_override(char *);
extern void load_scene_chunk_pal(int, int);
extern f32 weapon_compute_shot_launch_speed(f32 *a, f32 *b, f32 *out, f32 d, f32 e);
extern s32 SetHeroMoveState_pal(s32 action, s32 animate);
extern int moby_start_effect_from_entry(void *, float);
extern void script_queue_keyed_request(int, int);
extern float level_get_water_height_pal(void);
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

/* Updates one swamp monster each frame: runs its state machine (idle, attack, grab, throw, retreat) with the 50 Hz timings (PAL). */
void swamp_monster_update_pal(u8 *moby) {
    float scratch[20] __attribute__((aligned(16)));
    f32 distance_to_hero;
    f32 angle_to_arena;
    f32 hand_distance;
    f32 water_height;
    f32 anim_frame;
    f32 turn_a;
    f32 velocity_length;
    f32 turn_to_hero;
    f32 angle_minus;
    f32 pull_progress;
    f32 angle_plus;
    f32 grab_anim_frame;
    f32 unused_float;
    u8 *region_row;
    s32 hit_flags;
    s32 row_offset;
    u8 *region_table;
    s32 hit_result;
    s32 held_link_id;
    s32 region_id;
    s32 held_link_id2;
    s32 linked_moby_id2;
    s32 linked_moby_id;
    s32 can_attack;
    s32 timer;
    s32 extra_blend;
    s32 joint_step;
    s32 hand_far;
    s32 joint_base;
    u8 *idle_sound_handle;
    u8 *sound_handle;
    u8 *moby_position;
    u8 *unused_ptr3;
    u8 attack_stage;
    u8 attack_stage_now;
    u8 moby_state;
    u8 grab_anim;
    u8 grab_flag;
    u8 held_state;
    u8 unused_byte3;
    u8 unused_byte1;
    u8 attack_stage2;
    u8 anim_now;
    u8 anim_now2;
    u8 anim_now3;
    u8 unused_byte2;
    u8 *unused_ptr1;
    u8 *effect_position;
    u8 *held_moby;
    u8 *row_pointer;
    u8 *throw_velocity;
    u8 *held_position;
    u8 *held_velocity;
    u8 *throw_velocity_ptr;
    u8 *held_vars;
    u8 *vars;
    u8 *target_moby;
    u8 *arena_row;
    u8 *new_held_moby;
    u8 *held_moby_ptr;
    u8 *unused_ptr2;
    u8 *linked_moby;

    vars = ((u8 *)((UView *)(moby))->p[0x1A]);
    swamp_monster_update_hit_reaction();
    moby_state = ((UView *)(moby))->b[0x95];
    switch (moby_state) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if ((((UView *)(moby))->b[0xB0] != 0xFF) && (g_moby_group_flags[((UView *)(moby))->b[0xB0] + (g_current_map_index * 0x10)] & 0x80)) {
            linked_moby_id = ((UView *)(vars))->i[0xC2];
            if (linked_moby_id != -1) {
                D_L01_001B255C_sda[(linked_moby_id << 8) + 0xBC] = 1;
            }
            moby_mark_spawned(moby);
            return;
        }
        swamp_monster_init_pal(moby);
    default:
        break;
    case 1:                                         /* switch 1 */
        if (((UView *)(vars))->i[0x49] == 1) {
            if (((u8 *)((UView *)(vars))->p[0xB9]) == NULL) {
                script_queue_keyed_request(((UView *)(vars))->i[0xC4], ((UView *)(vars))->i[0xC6]);
                ((u8 *)((UView *)(vars))->p[0xB9]) = cam_alloc_override_slot_pal(5);
            }
            moby_set_state(moby, 0, 2);
        }
        break;
    case 2:                                         /* switch 1 */
        distance_to_hero = swamp_monster_move_around_arena_pal(moby);
        if (distance_to_hero == -1000.0f) {
            idle_sound_handle = ((u8 *)((UView *)(vars))->p[0xB9]);
            if (idle_sound_handle != NULL) {
                cam_end_override(idle_sound_handle);
                ((u8 *)((UView *)(vars))->p[0xB9]) = NULL;
            }
            moby_set_state(moby, 0, 1);
            moby_set_animation_and_speed(moby, 0, 0, 0xA);
        } else {
            target_moby = ((u8 *)((UView *)(vars))->p[0x48]);
            turn_to_hero = FastDiffRots(((UView *)(moby))->f[0x3E], mat_fast_helper_a(*(f32 *)(target_moby + 0x10) - ((UView *)(moby))->f[0x4], *(f32 *)(target_moby + 0x14) - ((UView *)(moby))->f[0x5]));
            switch (((UView *)(moby))->b[0xBC]) {                    /* switch 2 */
            case 0:                                 /* switch 2 */
                if ((distance_to_hero <= g_swamp_monster_range_near) && (turn_to_hero < (g_swamp_monster_aim_angle_near * 0.017453294f)) && (((UView *)(vars))->h[0x16E] == 0)) {
                    can_attack = 1;
                    swamp_monster_start_claw_attack_pal(moby);
                } else {
                    timer = ((UView *)(moby))->uh[0x4B];
                    can_attack = (((int)(g_swamp_monster_attack_threshold) * 5 + 2) / 6) < timer;
                }
                if (can_attack != 0) {
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_b * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                    ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(moby))->b[0xBC] = 1U;
                }
                if (((UView *)(vars))->f[0x8] < (2.0f * IntToFloat((s32) ((UView *)(vars))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(vars))->c[0x2E0] = 1;
                    ((UView *)(vars))->b[0x2E1] = 5U;
                    ((UView *)(vars))->c[0x2E2] = 0xE;
                    ((UView *)(vars))->c[0x71] = 0x13;
                    ((UView *)(vars))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_c * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                    ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(moby))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(moby, 0x10, 0, 0xD);
                    moby_set_state(moby, 0, 5);
                }
            default:                                /* switch 2 */
                break;
            case 1:                                 /* switch 2 */
            case 2:                                 /* switch 2 */
                attack_stage2 = ((UView *)(moby))->b[0xBC];
                extra_blend = 0;
                switch (attack_stage2) {                /* switch 3; irregular */
                case 1:                             /* switch 3 */
                    if ((distance_to_hero <= g_swamp_monster_range_near) && (turn_to_hero < (g_swamp_monster_aim_angle_near * 0.017453294f))) {
                        if ((math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(vars))->h[0x16E] == 0)) {
                            swamp_monster_start_claw_attack_pal(moby);
                        } else {
                            goto block_36;
                        }
                    } else {
block_36:
                        if ((g_swamp_monster_range_near < distance_to_hero) && (distance_to_hero <= g_swamp_monster_range_b) && (turn_to_hero < (g_swamp_monster_aim_angle_mid * 0.017453294f))) {
                            if ((math_random_int_below(g_swamp_monster_attack_odds_b - 1) == 0) && (((UView *)(vars))->h[0x16D] == 0)) {
                                swamp_monster_start_attack_c_pal(moby);
                            } else {
                                goto block_43;
                            }
                        } else {
block_43:
                            if (g_swamp_monster_far_range < distance_to_hero) {
                                ((UView *)(vars))->b[0x2E1] = 4U;
                                ((UView *)(vars))->c[0x2E2] = 0x16;
                                ((UView *)(vars))->c[0x2E0] = 0;
                                moby_set_controller_speed_limits(moby, g_swamp_monster_alt_limit_speed * 0.00040000002f, g_swamp_monster_alt_limit_move * 0.020000001f, g_swamp_monster_alt_limit_angular * 6.981318e-06f, g_swamp_monster_alt_limit_turn * 0.0003490659f);
                                ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                                ((UView *)(moby))->b[0xBC] = 2U;
                                ((UView *)(vars))->c[0x71] = 0xF;
                                ((UView *)(vars))->c[0x72] = 0xF;
                                moby_set_animation_and_speed(moby, 3, 0, 0xD);
                                moby_set_state(moby, 0, 5);
                            }
                        }
                    }
                    break;
                case 2:                             /* switch 3 */
                    extra_blend = 0x3C;
                    ((UView *)(moby))->i[0x26] = 0;
                    if ((distance_to_hero <= g_swamp_monster_range_near) && ((anim_now = ((UView *)(moby))->b[0x42], (anim_now == 0x16)) || (anim_now == 0))) {
                        ((UView *)(vars))->c[0x2E0] = 1;
                        ((UView *)(vars))->b[0x2E1] = 1U;
                        ((UView *)(vars))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_b * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                        ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                        ((UView *)(moby))->b[0xBC] = 1U;
                        ((UView *)(vars))->c[0x71] = 0x13;
                        ((UView *)(vars))->c[0x72] = 0x13;
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                        moby_set_state(moby, 0, 5);
                    }
                    break;
                }
                if (((UView *)(vars))->f[0x8] < (2.0f * IntToFloat((s32) ((UView *)(vars))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(vars))->c[0x2E0] = 1;
                    ((UView *)(vars))->b[0x2E1] = 5U;
                    ((UView *)(vars))->c[0x2E2] = 0xE;
                    ((UView *)(vars))->c[0x71] = 0x13;
                    ((UView *)(vars))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_c * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                    ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(moby))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(moby, 0x10, 0, extra_blend + 0xD);
                    moby_set_state(moby, 0, 5);
                }
                break;
            case 3:                                 /* switch 2 */
            case 4:                                 /* switch 2 */
            case 5:                                 /* switch 2 */
            case 6:                                 /* switch 2 */
                attack_stage = ((UView *)(moby))->b[0xBC];
                switch (attack_stage) {                  /* switch 4; irregular */
                case 3:                             /* switch 4 */
                    if ((distance_to_hero <= g_swamp_monster_range_a) && (turn_to_hero < (g_swamp_monster_aim_angle_a * 0.017453294f)) && (((UView *)(vars))->h[0x16F] == 0)) {
                        moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_d * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                        ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_c;
                        ((UView *)(moby))->b[0xBC] = 4U;
                        ((UView *)(vars))->b[0x2E3] = (u8) g_swamp_monster_vars_byte;
                        ((UView *)(vars))->c[0x71] = 0x13;
                        ((UView *)(vars))->c[0x2E0] = 1;
                        ((UView *)(vars))->c[0x72] = 0x13;
                        ((UView *)(vars))->b[0x2E1] = 1U;
                        ((UView *)(vars))->c[0x2E2] = 0;
                        swamp_monster_start_grab_attack_pal(moby);
                    }
                    break;
                case 4:                             /* switch 4 */
                    if ((g_swamp_monster_range_near < distance_to_hero) && (distance_to_hero <= g_swamp_monster_range_c) && (turn_to_hero < (g_swamp_monster_aim_angle_b * 0.017453294f)) && (((UView *)(vars))->h[0x16E] == 0)) {
                        if (vec_fast_helper_a(vars + 0x2E3) != 0) {
                            moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_alt_limit_move * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                            ((UView *)(moby))->b[0xBC] = 5U;
                            ((UView *)(vars))->c[0x2E0] = 0;
                            ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                            ((UView *)(vars))->b[0x2E1] = attack_stage;
                            ((UView *)(vars))->c[0x2E2] = 0x16;
                            ((UView *)(vars))->c[0x71] = 0xF;
                            ((UView *)(vars))->c[0x72] = 0xF;
                            moby_set_animation_and_speed(moby, 3, 0, 0xD);
                            moby_set_state(moby, 0, 5);
                        }
                        swamp_monster_start_attack_b_pal(moby);
                    } else if ((distance_to_hero <= g_swamp_monster_range_near) && (distance_to_hero <= g_swamp_monster_range_c) && (turn_to_hero < (g_swamp_monster_aim_angle_b * 0.017453294f)) && (((UView *)(vars))->h[0x16E] == 0)) {
                        swamp_monster_start_claw_attack_pal(moby);
                    }
                    break;
                case 5:                             /* switch 4 */
                    ((UView *)(moby))->i[0x26] = 0;
                    if (distance_to_hero <= g_swamp_monster_range_near) {
                        anim_now2 = ((UView *)(moby))->b[0x42];
                        if (anim_now2 != 0x16) {
                            if (anim_now2 == 0) {
                                goto block_72;
                            }
                        } else {
block_72:
                            ((UView *)(vars))->c[0x2E0] = 1;
                            ((UView *)(vars))->b[0x2E1] = 1U;
                            ((UView *)(vars))->c[0x71] = 0x13;
                            ((UView *)(vars))->c[0x72] = 0x13;
                            ((UView *)(vars))->c[0x2E2] = 0;
                            moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_b * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                            ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_c;
                            ((UView *)(moby))->b[0xBC] = 6U;
                            ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                            moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                            moby_set_state(moby, 0, 5);
                        }
                    }
                    break;
                case 6:                             /* switch 4 */
                    ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                    if ((distance_to_hero <= g_swamp_monster_range_c) && (turn_to_hero < (g_swamp_monster_aim_angle_near * 0.017453294f)) && (math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(vars))->h[0x16E] == 0)) {
                        if ((g_swamp_monster_range_near < distance_to_hero) && (func_001163B0() & 1)) {
                            swamp_monster_start_attack_b_pal(moby);
                        } else {
                            swamp_monster_start_claw_attack_pal(moby);
                        }
                    }
                    break;
                }
                attack_stage_now = ((UView *)(moby))->b[0xBC];
                if ((attack_stage_now != 5) && (attack_stage_now < 7U) && (g_swamp_monster_far_range < distance_to_hero)) {
                    moby_set_controller_speed_limits(moby, g_swamp_monster_alt_limit_speed * 0.00040000002f, g_swamp_monster_alt_limit_move * 0.020000001f, g_swamp_monster_alt_limit_angular * 6.981318e-06f, g_swamp_monster_alt_limit_turn * 0.0003490659f);
                    ((UView *)(moby))->b[0xBC] = 5U;
                    ((UView *)(vars))->c[0x2E0] = 0;
                    ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(vars))->c[0x71] = 0xF;
                    ((UView *)(vars))->c[0x72] = 0xF;
                    ((UView *)(vars))->b[0x2E1] = 4U;
                    ((UView *)(vars))->c[0x2E2] = 0x16;
                }
                if (((UView *)(vars))->f[0x8] < (IntToFloat((s32) ((UView *)(vars))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(vars))->c[0x2E0] = 1;
                    ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_a;
                    ((UView *)(vars))->b[0x2E1] = 5U;
                    ((UView *)(vars))->c[0x2E2] = 0xE;
                    ((UView *)(vars))->c[0x71] = 0x13;
                    ((UView *)(vars))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_e * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                    ((UView *)(moby))->b[0xBC] = 7U;
                    moby_set_animation_and_speed(moby, 0x10, 0, 0xD);
                    moby_set_state(moby, 0, 5);
                }
                break;
            case 7:                                 /* switch 2 */
                if ((distance_to_hero <= g_swamp_monster_range_a) && (turn_to_hero < (g_swamp_monster_aim_angle_a * 0.017453294f)) && (((UView *)(vars))->h[0x16F] == 0)) {
                    ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                    ((UView *)(moby))->b[0xBC] = 9U;
                    ((UView *)(vars))->c[0x2E0] = 1;
                    ((UView *)(vars))->b[0x2E1] = 1U;
                    ((UView *)(vars))->c[0x2E2] = 0;
                    ((UView *)(vars))->c[0x71] = 0x13;
                    ((UView *)(vars))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_f * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                    swamp_monster_start_grab_attack_pal(moby);
                }
                break;
            case 8:                                 /* switch 2 */
                ((UView *)(moby))->i[0x26] = 0;
                if (distance_to_hero <= g_swamp_monster_range_near) {
                    anim_now3 = ((UView *)(moby))->b[0x42];
                    if (anim_now3 != 0x16) {
                        if (anim_now3 == 0) {
                            goto block_95;
                        }
                    } else {
block_95:
                        ((UView *)(vars))->c[0x2E0] = 1;
                        ((UView *)(vars))->b[0x2E1] = 1U;
                        ((UView *)(vars))->c[0x71] = 0x13;
                        ((UView *)(vars))->c[0x72] = 0x13;
                        ((UView *)(vars))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f, g_swamp_monster_limit_move_b * 0.020000001f, g_swamp_monster_limit_angular_a * 6.981318e-06f, g_swamp_monster_limit_turn_a * 0.0003490659f);
                        ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                        ((UView *)(moby))->b[0xBC] = 9U;
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                        moby_set_state(moby, 0, 5);
                    }
                }
                break;
            case 9:                                 /* switch 2 */
                ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                if ((distance_to_hero <= g_swamp_monster_range_near) && (turn_to_hero < (g_swamp_monster_aim_angle_near * 0.017453294f))) {
                    if ((math_random_int_below(g_swamp_monster_attack_odds_a - 1) == 0) && (((UView *)(vars))->h[0x16E] == 0)) {
                        if (func_001163B0() & 1) {
                            swamp_monster_start_claw_attack_pal(moby);
                        } else {
                            swamp_monster_start_attack_b_pal(moby);
                        }
                    } else {
                        goto block_105;
                    }
                } else {
block_105:
                    if ((g_swamp_monster_range_near < distance_to_hero) && (distance_to_hero <= g_swamp_monster_range_b) && (turn_to_hero < (g_swamp_monster_aim_angle_mid * 0.017453294f))) {
                        if ((math_random_int_below(g_swamp_monster_attack_odds_b - 1) == 0) && (((UView *)(vars))->h[0x16D] == 0)) {
                            swamp_monster_start_attack_c_pal(moby);
                        } else {
                            goto block_112;
                        }
                    } else {
block_112:
                        if (g_swamp_monster_far_range < distance_to_hero) {
                            ((UView *)(vars))->b[0x2E1] = 4U;
                            ((UView *)(vars))->c[0x2E2] = 0x16;
                            ((UView *)(vars))->c[0x2E0] = 0;
                            moby_set_controller_speed_limits(moby, g_swamp_monster_alt_limit_speed * 0.00040000002f, g_swamp_monster_alt_limit_move * 0.020000001f, g_swamp_monster_alt_limit_angular * 6.981318e-06f, g_swamp_monster_alt_limit_turn * 0.0003490659f);
                            ((UView *)(vars))->f[0xBB] = (f32) g_swamp_monster_range_near;
                            ((UView *)(moby))->b[0xBC] = 8U;
                            ((UView *)(vars))->c[0x71] = 0xF;
                            ((UView *)(vars))->c[0x72] = 0xF;
                            moby_set_animation_and_speed(moby, 3, 0, 0xD);
                            moby_set_state(moby, 0, 5);
                        }
                    }
                }
                break;
            }
            if ((((UView *)(moby))->b[0x42] == 0x16) && (((UView *)(moby))->b[0x60] & 2)) {
                ((UView *)(vars))->c[0x2E2] = 0;
                moby_set_animation_and_speed(moby, 0, 0, 0xA);
            }
        }
        break;
    case 3:                                         /* switch 1 */
        anim_frame = moby_get_anim_value(moby);
        switch (((UView *)(moby))->b[0x20]) {                        /* switch 5; irregular */
        case 1:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if ((anim_frame > 44.0f) && (anim_frame < 68.0f)) {
                grab_anim = ((UView *)(moby))->b[0x42];
                joint_base = -1;
                if (grab_anim == 6) {
                    joint_base = 0;
                } else if (grab_anim == 7) {
                    joint_base = 4;
                }
                if (joint_base >= 0) {
                    moby_transform_joint_to_world(moby, joint_base, (scratch + 4));
                    for (joint_step = 1; joint_step < 3; joint_step++) {
                        part_init_effect_record((scratch + 8), (s32) moby, 1, (f32) ((UView *)(vars))->b[0x34]);
                        qcopy(scratch, scratch + 4);
                        moby_transform_joint_to_world(moby, joint_base + joint_step, scratch + 4);
                        coll_process_hit(0.5f, (s32) (scratch + 4), 0, (s32) moby, (s32) (scratch + 8));
                        scratch[4] += math_random_float_range(-0.3f, 0.3f);
                        scratch[5] += math_random_float_range(-0.3f, 0.3f);
                        scratch[6] += math_random_float_range(-0.3f, 0.3f);
                        CollLine(scratch, (scratch + 4), 9, moby, (scratch + 8));
                    }
                }
            }
            break;
        case 2:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if (math_is_value_within_step_pal((u8 *) moby, 16.0f) != 0) {
                moby_transform_joint_to_world(moby, 0xA, scratch);
                FastVecSub((scratch + 4), ((u8 *)((UView *)(vars))->p[0x48]) + 0x10, scratch);
                vec_scale_to_length((scratch + 4), (scratch + 4), g_swamp_monster_shot_speed * 0.020000001f);
                scratch[6] = weapon_compute_shot_launch_speed(scratch, ((u8 *)((UView *)(vars))->p[0x48]) + 0x10, NULL, g_swamp_monster_shot_speed * 0.020000001f, -(g_swamp_monster_shot_gravity * 0.00040000002f));
                moby_spawn_thrown_object(scratch, (scratch + 4), moby, (f32) ((UView *)(vars))->b[0x34]);
            }
            break;
        case 3:                                     /* switch 5 */
            if ((anim_frame > 34.0f) && (anim_frame < 41.0f)) {
                hit_flags = (func_001163B0() & 1) | 8;
                coll_test_hit_at_bone(moby, 2.2f, (f32) ((UView *)(vars))->b[0x34], hit_flags, 1, 1.0f, 0, 1, 0);
            }
            break;
        case 4:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if (((UView *)(vars))->b[0x2F4] == 0) {
                if (anim_frame > 12.0f) {
                    if (anim_frame <= 17.0f) {
                        moby_transform_joint_to_world(moby, 0xC, scratch);
                        scratch[2] -= 2.4f;
                        if ((fast_vec_dist(scratch, &((HeroV *)g_hero_state)->x) < g_swamp_monster_hero_close_range) && (*(s32 *)(g_hero_state + 0x2294) != 0x6F)) {
                            ((UView *)(vars))->b[0x2F4] = 1U;
                        }
                    } else {
                        goto block_149;
                    }
                } else {
block_149:
                    if ((anim_frame > 17.0f) && (anim_frame < 19.0f)) {
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        hit_flags = (func_001163B0() & 1) | 0xC;
                        coll_test_hit_at_bone(moby, 2.0f, (f32) ((UView *)(vars))->b[0x35], hit_flags, 1, 1.0f, 0, 1, 0);
                    }
                }
            } else if (anim_frame > 19.0f) {
                ((HeroV *)g_hero_state)->a22b5 = 1;
            }
            break;
        }
        if (((UView *)(vars))->b[0x2F4] != 0) {
            swamp_monster_hold_hero_pal(moby);
            if (((UView *)(moby))->b[0x60] & 2) {
                if (((HeroV *)g_hero_state)->a24cc < 2) {
                    hero_record_play_counters_pal();
                } else {
                    part_init_effect_record(scratch, (s32) moby, 1, (f32) ((UView *)(vars))->b[0x36]);
                    QueueMobyImpact(((HeroV *)g_hero_state)->a2290, scratch);
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
        grab_anim_frame = moby_get_anim_value(moby);
        arena_row = (u8 *)((((UView *)(vars))->i[0xB3] << 7) + (s32)g_swamp_patrol_positions);
        angle_to_arena = mat_fast_helper_a(*(f32 *)(arena_row + 0x30) - ((UView *)(moby))->f[0x4], *(f32 *)(arena_row + 0x34) - ((UView *)(moby))->f[0x5]);
        angle_plus = FastAddRotations(angle_to_arena, 1.5707965f);
        angle_minus = fast_subtract_rotations(angle_to_arena, 1.5707965f);
        turn_a = FastDiffRots(((UView *)(moby))->f[0x3E], angle_plus);
        moby_start_effect_from_entry(moby, turn_a < FastDiffRots(((UView *)(moby))->f[0x3E], angle_minus) ? angle_plus : angle_minus);
        if (((UView *)(moby))->b[0x42] == 0xB) {
            hand_far = 1;
            moby_transform_joint_to_world(moby, 0xE, scratch);
            hand_distance = fast_vec_dist(scratch, &((Hero *)g_hero_state)->b[0x80]);
            if (!(hand_distance > 13.0f)) {
                hand_far = 0;
            }
            if (((UView *)(vars))->b[0x2F4] != 0) {
                if (grab_anim_frame > 33.0f) {
                    SetHeroMoveState_pal(0x16, 1);
                    ((Hero *)g_hero_state)->i[0x2294 / 4] = 0x6F;
                    ((Hero *)g_hero_state)->i[0x24A0 / 4] = 0;
                    ((Hero *)g_hero_state)->i[0x229C / 4] = 9;
                    ((Hero *)g_hero_state)->c[0x22B5] = 0;
                    ((UView *)(vars))->b[0x2F4] = 0U;
                } else {
                    ((Hero *)g_hero_state)->c[0x22B5] = 1;
                    swamp_monster_hold_hero_pal(moby);
                }
            }
            if ((((UView *)(vars))->b[0x2F4] == 0) && (hand_far == 0)) {
                vec_scale_to_length((scratch + 4), moby + 0xC0, g_swamp_monster_scratch_length);
                vec_scale_to_length((scratch + 8), (scratch + 4), g_swamp_monster_move_speed * 0.020000001f);
                velocity_length = vec_length_xy((scratch + 8));
                scratch[10] = velocity_length * (math_square(1.0f - (hand_distance * 0.006666667f)) * 0.7f);
                qcopy(&((Hero *)g_hero_state)->b[0xF0], scratch + 8);
                qcopy(&((Hero *)g_hero_state)->b[0x110], scratch + 8);
                FastVecAdd(&((Hero *)g_hero_state)->b[0x80], &((Hero *)g_hero_state)->b[0x80], (scratch + 8));
            }
            if (hand_far != 0) {
                ((UView *)(moby))->i[0x27] = (s32) (((UView *)(moby))->i[0x27] & ~0x30);
                *(s32 *)(moby + 0x98) = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                if (g_game_mode == 0x6F) {
                    SetHeroMoveState_pal(0x16, 1);
                }
            }
            if (((UView *)(moby))->b[0x60] & 2) {
                ((UView *)(moby))->i[0x27] = (s32) (((UView *)(moby))->i[0x27] & ~0x30);
                ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                moby_set_animation_and_speed(moby, 0xC, 0, 0x14);
                moby_set_state(moby, 0, 5);
                if (g_game_mode == 0x6F) {
                    SetHeroMoveState_pal(0x16, 1);
                }
            }
        } else {
            if (((UView *)(moby))->b[0x95] == 4) {
                grab_flag = ((UView *)(vars))->b[0x2F4];
                if (grab_flag == 1) {
                    g_grab_flag = grab_flag;
                }
            }
        }
        break;
    case 5:                                         /* switch 1 */
        if (((UView *)(moby))->b[0x60] & 2) {
            moby_set_state(moby, 0, 2);
            moby_set_animation_and_speed(moby, (s32) ((UView *)(vars))->b[0x2E1], 0, 0x14);
            ((UView *)(moby))->b[0xA8] = 0xFF;
        }
        break;
    case 6:                                         /* switch 1 */
        hit_result = moby_dispatch_action_by_kind(moby, vars + 0x60);
        if (hit_result & 1) {
            moby_set_state(moby, 0, 7);
        } else if (hit_result & 2) {
            moby_set_animation_and_speed(moby, (s32) ((UView *)(vars))->b[0x2E1], 0, 0xC);
            moby_set_state(moby, 0, 2);
        }
        break;
    case 7:                                         /* switch 1 */
        ((UView *)(moby))->i[0x12] = 0;
        ((UView *)(moby))->uh[0x1A] = (u16) (((UView *)(moby))->uh[0x1A] | 0x41);
        sound_handle = ((u8 *)((UView *)(vars))->p[0xB9]);
        if (sound_handle != NULL) {
            cam_end_override(sound_handle);
            ((u8 *)((UView *)(vars))->p[0xB9]) = NULL;
        }
        moby_position = moby + 0x10;
        new_held_moby = SpawnGoldBolt_pal(moby_position, 1, -1, -1);
        ((u8 *)((UView *)(vars))->p[0xC0]) = new_held_moby;
        if (new_held_moby != NULL) {
            SetHeroMoveState_pal(0x6F, 1);
            throw_velocity = vars + 0x2A0;
            held_moby_ptr = ((u8 *)((UView *)(vars))->p[0xC0]);
            *(f32 *)(held_moby_ptr + 0x18) = (f32) (*(f32 *)(held_moby_ptr + 0x18) - 0.5f);
            FastVecSub(throw_velocity, moby_position, g_hero_position);
            ((UView *)(vars))->f[0xAA] = (f32) (((UView *)(vars))->f[0xAA] + 1.0f);
            FastVecScale(throw_velocity, throw_velocity, 0.85f);
            ((UView *)(vars))->f[0xAB] = 1.0f;
            moby_set_state(moby, 0, 8);
        }
        break;
    case 8:                                         /* switch 1 */
        held_link_id = ((UView *)(vars))->i[0xBE];
        pull_progress = ((UView *)(vars))->f[0xAB] - 0.0075000003f;
        ((UView *)(vars))->f[0xAB] = pull_progress;
        if (held_link_id != -1) {
            region_id = (*(s32 *)((u8 *)((*(u8 **)((u8 *)((held_link_id << 8) + (s32)g_moby_l01_table) + 0x68))) + 0x28));
            region_table = D_L01_001B264C_sda;
            if (region_id != -1) {
                row_offset = region_id << 7;
                qcopy(g_hero_position, (u8 *)(row_offset + (s32)region_table) + 0x30);
                row_pointer = (u8 *)(row_offset + (s32)region_table);
                qcopy(g_hero_position + 0x10, (u8 *)row_pointer + 0x70);
            }
        }
        if ((u8) *(u8 *)(((u8 *)((UView *)(vars))->p[0xC0]) + 0x20) < 2U) {
            held_link_id2 = ((UView *)(vars))->i[0xBE];
            if (held_link_id2 != -1) {
                linked_moby = (u8 *)((held_link_id2 << 8) + (s32)D_L01_001B255C_sda);
                if (*(u8 *)(linked_moby + 0xBC) != 0) {
                    *(u8 *)(linked_moby + 0xBC) = 0U;
                    update_camera_pose_trigger_pal(g_moby_l01_table + (((UView *)(vars))->i[0xBE] << 8));
                }
            }
            throw_velocity_ptr = vars + 0x2A0;
            held_position = ((u8 *)((UView *)(vars))->p[0xC0]) + 0x10;
            vec_scale_to_length(held_position, throw_velocity_ptr, pull_progress * FastVecLength(throw_velocity_ptr));

            *(f32 *)((((u8 *)((UView *)(vars))->p[0xC0])) + 0x18) = (f32) (*(f32 *)((((u8 *)((UView *)(vars))->p[0xC0])) + 0x18) + (math_fast_sin_or_cos_b(pull_progress * 3.1415927f) * 4.0f));
            effect_position = ((u8 *)((UView *)(vars))->p[0xC0]) + 0x10;
            FastVecAdd(effect_position, effect_position, g_hero_position);
            held_vars = *(u8 **)(((u8 *)((UView *)(vars))->p[0xC0]) + 0x68);
            held_velocity = held_vars + 0x10;
            FastVecSub(held_velocity, moby + 0x10, g_hero_position);
            vec_scale_to_length(held_velocity, held_velocity, 2.5f);
            *(f32 *)(held_vars + 0x1C) = FastAddRotations(mat_fast_helper_a(*(f32 *)(held_vars + 0x10), *(f32 *)(held_vars + 0x14)), 3.1415927f);
            FastVecAdd(held_velocity, held_velocity, g_hero_position);
            func_002A0F48(((u8 *)((UView *)(vars))->p[0xC0]));
            ((UView *)(vars))->f[0xAB] = pull_progress;
        }
        held_moby = ((u8 *)((UView *)(vars))->p[0xC0]);
        if ((held_moby == NULL) || (*(s16 *)(held_moby + 0xAA) != 0x1250) || (held_state = *(u8 *)(held_moby + 0x20), (held_state == 0xFE)) || (held_state == 0xFD)) {
            SetDeathBits_pal(moby, 0, 3);

            if ((((UView *)(moby))->b[0xB0]) != 0xFF) {
                moby_mark_table_entry_flagged((u32) (((UView *)(moby))->b[0xB0]));
            }
            if (((UView *)(vars))->i[0xC1] != -1) {
                FadeToBlack(0xd);
                load_scene_chunk_pal(0, 0);
                region_row = g_swamp_patrol_positions + (((UView *)(vars))->i[0xC1] << 7);
                hero_reset_position_and_direction_pal(region_row + 0x30, region_row + 0x70, 0, 1);
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
            }
            linked_moby_id2 = ((UView *)(vars))->i[0xC2];
            if (linked_moby_id2 != -1) {
                (*(s8 *)((u8 *)((linked_moby_id2 << 8) + (s32)D_L01_001B255C_sda) + 0xBC)) = 1;
            }
            script_queue_keyed_request(((UView *)(vars))->i[0xC5], ((UView *)(vars))->i[0xC7]);
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
        water_height = level_get_water_height_pal();
        if ((((UView *)(moby))->b[0x95] != 0) && (((HeroV *)g_hero_state)->z < (water_height - 1.8f)) && (((HeroV *)g_hero_state)->z < (((UView *)(moby))->f[0x6] - 1.0f)) && (vec_distance_xy(moby + 0x10, &((HeroV *)g_hero_state)->x) < 10.0f)) {
            hero_record_play_counters_pal();
        }
        swamp_monster_update_timers(moby);
}
