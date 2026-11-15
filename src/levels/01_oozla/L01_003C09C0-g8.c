#include "names.h"
/* func_L01_003C09C0 (Oozla, 7,360 bytes): a moby update with an outer switch on the state byte
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
extern void swamp_monster_hold_hero(void *);
extern void moby_spawn_thrown_object(void *, void *, void *, float);
extern void *SpawnGoldBolt(void *, int, int, int);
extern void UpdateCameraPoseTrigger(void *);
extern int func_001163B0(void);
#define NULL ((void *)0)
extern void moby_mark_table_entry_flagged(u32 a0);
extern void func_002A0F48(void *);
extern void SetDeathBits(void *, int, int);
extern void moby_set_state(char *, int, int);
extern float math_square(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void part_init_effect_record(void *a0, int a1, int a2, float a3);
extern s32 coll_test_hit_at_bone(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern void QueueMobyImpact(s32, void *);
extern s32 math_is_value_within_step(u8 *, f32);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_record_play_counters(void);
extern void hero_reset_position_and_direction(int a0, int a1, int a2, int a3);
extern void * cam_alloc_override_slot(s32 size);
extern void cam_end_override(char *);
extern void load_scene_chunk(int, int);
extern f32 weapon_compute_shot_launch_speed(f32 *a, f32 *b, f32 *out, f32 d, f32 e);
extern s32 SetHeroMoveState(s32 action, s32 animate);
extern int moby_start_effect_from_entry(void *, float);
extern void script_queue_keyed_request(int, int);
extern float level_get_water_height(void);
extern void moby_set_animation_and_speed(void *, int, int, int);
typedef struct { u8 pad[0x80]; f32 x; f32 y; f32 z; u8 pad2[0x2204]; s32 a2290; s32 a2294; u8 pad3[4]; s32 a229c; u8 pad4[0x15]; u8 a22b5; u8 pad5[0x1EA]; s32 a24a0; u8 pad6[0x28]; s32 a24cc; } HeroV;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
extern u8 g_hero_state[] NOT_SDA;
extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_0018C0D5 __attribute__((nosda));
extern u8 g_hero_position[] NOT_SDA;

extern s32 g_current_map_index __attribute__((sda));
extern f32 D_L01_001AFE54 __attribute__((sda));
extern f32 D_L01_001AFE58 __attribute__((sda));
extern f32 D_L01_001AFE5C __attribute__((sda));
extern f32 D_L01_001AFE60 __attribute__((sda));
extern f32 D_L01_001AFE68 __attribute__((sda));
extern f32 D_L01_001AFE6C __attribute__((sda));
extern f32 D_L01_001AFE74 __attribute__((sda));
extern f32 D_L01_001AFE78 __attribute__((sda));
extern f32 D_L01_001AFE7C __attribute__((sda));
extern f32 D_L01_001AFE84 __attribute__((sda));
extern f32 D_L01_001AFE88 __attribute__((sda));
extern f32 D_L01_001AFE8C __attribute__((sda));
extern f32 D_L01_001AFE94 __attribute__((sda));
extern f32 D_L01_001AFE98 __attribute__((sda));
extern f32 D_L01_001AFE9C __attribute__((sda));
extern f32 D_L01_001AFEA0 __attribute__((sda));
extern f32 D_L01_001AFEA4 __attribute__((sda));
extern f32 D_L01_001AFEA8 __attribute__((sda));
extern f32 D_L01_001AFEAC __attribute__((sda));
extern f32 D_L01_001AFEB0 __attribute__((sda));
extern f32 D_L01_001AFEB4 __attribute__((sda));
extern f32 D_L01_001AFEB8 __attribute__((sda));
extern s32 D_L01_001AFEC0 __attribute__((sda));
extern s32 D_L01_001AFEC4 __attribute__((sda));
extern u8 D_L01_001AFEC8 __attribute__((sda));
extern s32 D_L01_001AFECC __attribute__((sda));
extern f32 D_L01_001AFEEC __attribute__((sda));
extern f32 D_L01_001AFEF0 __attribute__((sda));
extern f32 D_L01_001AFEF4 __attribute__((sda));
extern f32 D_L01_001AFEF8 __attribute__((sda));
extern u8 *D_L01_001B255C_sda __attribute__((sda));
extern u8 *D_L01_001B264C_sda __attribute__((sda));
extern u8 D_00189F10[] NOT_SDA;
extern u8 D_0019B2E8[] NOT_SDA;
extern u8 *g_moby_l01_table;
extern u8 *D_L01_001B264C;

/* Updates the Swamp Monster II. It chases and attacks the player, can grab him and throw him, and is removed when it is defeated. */
void swamp_monster_update(u8 *moby) {
    float scratch[20] __attribute__((aligned(16)));
    f32 distanceToHero;
    f32 angleToArena;
    f32 handDistance;
    f32 waterHeight;
    f32 animFrame;
    f32 turnA;
    f32 velocityLength;
    f32 turnToHero;
    f32 angleMinus;
    f32 pullProgress;
    f32 anglePlus;
    f32 grabAnimFrame;
    f32 unusedFloat;
    u8 *regionRow;
    s32 hitFlags;
    s32 rowOffset;
    u8 *regionTable;
    s32 hitResult;
    s32 heldLinkId;
    s32 regionId;
    s32 heldLinkId2;
    s32 linkedMobyId2;
    s32 linkedMobyId;
    s32 canAttack;
    s32 extraBlend;
    s32 jointStep;
    s32 handFar;
    s32 jointBase;
    u8 *idleSoundHandle;
    u8 *soundHandle;
    u8 *mobyPosition;
    u8 *unusedPtr3;
    u8 attackStage;
    u8 attackStageNow;
    u8 mobyState;
    u8 grabAnim;
    u8 grabFlag;
    u8 heldState;
    u8 unusedByte3;
    u8 unusedByte1;
    u8 attackStage2;
    u8 animNow;
    u8 animNow2;
    u8 animNow3;
    u8 unusedByte2;
    u8 *unusedPtr1;
    u8 *effectPosition;
    u8 *heldMoby;
    u8 *rowPointer;
    u8 *throwVelocity;
    u8 *heldPosition;
    u8 *heldVelocity;
    u8 *throwVelocityPtr;
    u8 *heldVars;
    u8 *vars;
    u8 *targetMoby;
    u8 *arenaRow;
    u8 *newHeldMoby;
    u8 *heldMobyPtr;
    u8 *unusedPtr2;
    u8 *linkedMoby;

    vars = ((u8 *)((UView *)(moby))->p[0x1A]);
    swamp_monster_update_hit_reaction();
    mobyState = ((UView *)(moby))->b[0x95];
    switch (mobyState) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if ((((UView *)(moby))->b[0xB0] != 0xFF) && (D_0019B2E8[((UView *)(moby))->b[0xB0] + (g_current_map_index * 0x10)] & 0x80)) {
            linkedMobyId = ((UView *)(vars))->i[0xC2];
            if (linkedMobyId != -1) {
                D_L01_001B255C_sda[(linkedMobyId << 8) + 0xBC] = 1;
            }
            moby_mark_spawned(moby);
            return;
        }
        swamp_monster_init(moby);
    default:
        break;
    case 1:                                         /* switch 1 */
        if (((UView *)(vars))->i[0x49] == 1) {
            if (((u8 *)((UView *)(vars))->p[0xB9]) == NULL) {
                script_queue_keyed_request(((UView *)(vars))->i[0xC4], ((UView *)(vars))->i[0xC6]);
                ((u8 *)((UView *)(vars))->p[0xB9]) = cam_alloc_override_slot(5);
            }
            moby_set_state(moby, 0, 2);
        }
        break;
    case 2:                                         /* switch 1 */
        distanceToHero = swamp_monster_move_around_arena(moby);
        if (distanceToHero == -1000.0f) {
            idleSoundHandle = ((u8 *)((UView *)(vars))->p[0xB9]);
            if (idleSoundHandle != NULL) {
                cam_end_override(idleSoundHandle);
                ((u8 *)((UView *)(vars))->p[0xB9]) = NULL;
            }
            moby_set_state(moby, 0, 1);
            moby_set_animation_and_speed(moby, 0, 0, 0xA);
        } else {
            targetMoby = ((u8 *)((UView *)(vars))->p[0x48]);
            turnToHero = FastDiffRots(((UView *)(moby))->f[0x3E], mat_fast_helper_a(*(f32 *)(targetMoby + 0x10) - ((UView *)(moby))->f[0x4], *(f32 *)(targetMoby + 0x14) - ((UView *)(moby))->f[0x5]));
            switch (((UView *)(moby))->b[0xBC]) {                    /* switch 2 */
            case 0:                                 /* switch 2 */
                if ((distanceToHero <= D_L01_001AFE5C) && (turnToHero < (D_L01_001AFEAC * 0.017453294f)) && (((UView *)(vars))->h[0x16E] == 0)) {
                    canAttack = 1;
                    swamp_monster_start_claw_attack(moby);
                } else {
                    canAttack = D_L01_001AFECC < (s32) ((UView *)(moby))->uh[0x4B];
                }
                if (canAttack != 0) {
                    moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
                    ((UView *)(moby))->b[0xBC] = 1U;
                }
                if (((UView *)(vars))->f[0x8] < (2.0f * IntToFloat((s32) ((UView *)(vars))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(vars))->c[0x2E0] = 1;
                    ((UView *)(vars))->b[0x2E1] = 5U;
                    ((UView *)(vars))->c[0x2E2] = 0xE;
                    ((UView *)(vars))->c[0x71] = 0x13;
                    ((UView *)(vars))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE88 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE54;
                    ((UView *)(moby))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(moby, 0x10, 0, 0xD);
                    moby_set_state(moby, 0, 5);
                }
            default:                                /* switch 2 */
                break;
            case 1:                                 /* switch 2 */
            case 2:                                 /* switch 2 */
                attackStage2 = ((UView *)(moby))->b[0xBC];
                extraBlend = 0;
                switch (attackStage2) {                /* switch 3; irregular */
                case 1:                             /* switch 3 */
                    if ((distanceToHero <= D_L01_001AFE5C) && (turnToHero < (D_L01_001AFEAC * 0.017453294f))) {
                        if ((math_random_int_below(D_L01_001AFEC0 - 1) == 0) && (((UView *)(vars))->h[0x16E] == 0)) {
                            swamp_monster_start_claw_attack(moby);
                        } else {
                            goto block_36;
                        }
                    } else {
block_36:
                        if ((D_L01_001AFE5C < distanceToHero) && (distanceToHero <= D_L01_001AFE60) && (turnToHero < (D_L01_001AFEB0 * 0.017453294f))) {
                            if ((math_random_int_below(D_L01_001AFEC4 - 1) == 0) && (((UView *)(vars))->h[0x16D] == 0)) {
                                swamp_monster_start_attack_c(moby);
                            } else {
                                goto block_43;
                            }
                        } else {
block_43:
                            if (D_L01_001AFE68 < distanceToHero) {
                                ((UView *)(vars))->b[0x2E1] = 4U;
                                ((UView *)(vars))->c[0x2E2] = 0x16;
                                ((UView *)(vars))->c[0x2E0] = 0;
                                moby_set_controller_speed_limits(moby, D_L01_001AFE9C * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFEA4 * 0.0000048481375f, D_L01_001AFEA8 * 0.00029088825f);
                                ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
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
                    extraBlend = 0x3C;
                    ((UView *)(moby))->i[0x26] = 0;
                    if ((distanceToHero <= D_L01_001AFE5C) && ((animNow = ((UView *)(moby))->b[0x42], (animNow == 0x16)) || (animNow == 0))) {
                        ((UView *)(vars))->c[0x2E0] = 1;
                        ((UView *)(vars))->b[0x2E1] = 1U;
                        ((UView *)(vars))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                        ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
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
                    moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE88 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE54;
                    ((UView *)(moby))->b[0xBC] = 3U;
                    moby_set_animation_and_speed(moby, 0x10, 0, extraBlend + 0xD);
                    moby_set_state(moby, 0, 5);
                }
                break;
            case 3:                                 /* switch 2 */
            case 4:                                 /* switch 2 */
            case 5:                                 /* switch 2 */
            case 6:                                 /* switch 2 */
                attackStage = ((UView *)(moby))->b[0xBC];
                switch (attackStage) {                  /* switch 4; irregular */
                case 3:                             /* switch 4 */
                    if ((distanceToHero <= D_L01_001AFE54) && (turnToHero < (D_L01_001AFEB4 * 0.017453294f)) && (((UView *)(vars))->h[0x16F] == 0)) {
                        moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE8C * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                        ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE58;
                        ((UView *)(moby))->b[0xBC] = 4U;
                        ((UView *)(vars))->b[0x2E3] = (u8) D_L01_001AFEC8;
                        ((UView *)(vars))->c[0x71] = 0x13;
                        ((UView *)(vars))->c[0x2E0] = 1;
                        ((UView *)(vars))->c[0x72] = 0x13;
                        ((UView *)(vars))->b[0x2E1] = 1U;
                        ((UView *)(vars))->c[0x2E2] = 0;
                        swamp_monster_start_grab_attack(moby);
                    }
                    break;
                case 4:                             /* switch 4 */
                    if ((D_L01_001AFE5C < distanceToHero) && (distanceToHero <= D_L01_001AFE58) && (turnToHero < (D_L01_001AFEB8 * 0.017453294f)) && (((UView *)(vars))->h[0x16E] == 0)) {
                        if (vec_fast_helper_a(vars + 0x2E3) != 0) {
                            moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                            ((UView *)(moby))->b[0xBC] = 5U;
                            ((UView *)(vars))->c[0x2E0] = 0;
                            ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
                            ((UView *)(vars))->b[0x2E1] = attackStage;
                            ((UView *)(vars))->c[0x2E2] = 0x16;
                            ((UView *)(vars))->c[0x71] = 0xF;
                            ((UView *)(vars))->c[0x72] = 0xF;
                            moby_set_animation_and_speed(moby, 3, 0, 0xD);
                            moby_set_state(moby, 0, 5);
                        }
                        swamp_monster_start_attack_b(moby);
                    }
                    break;
                case 5:                             /* switch 4 */
                    ((UView *)(moby))->i[0x26] = 0;
                    if (distanceToHero <= D_L01_001AFE5C) {
                        animNow2 = ((UView *)(moby))->b[0x42];
                        if (animNow2 != 0x16) {
                            if (animNow2 == 0) {
                                goto block_72;
                            }
                        } else {
block_72:
                            ((UView *)(vars))->c[0x2E0] = 1;
                            ((UView *)(vars))->b[0x2E1] = 1U;
                            ((UView *)(vars))->c[0x71] = 0x13;
                            ((UView *)(vars))->c[0x72] = 0x13;
                            ((UView *)(vars))->c[0x2E2] = 0;
                            moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                            ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE58;
                            ((UView *)(moby))->b[0xBC] = 6U;
                            ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                            moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                            moby_set_state(moby, 0, 5);
                        }
                    }
                    break;
                case 6:                             /* switch 4 */
                    ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                    if ((distanceToHero <= D_L01_001AFE58) && (turnToHero < (D_L01_001AFEAC * 0.017453294f)) && (math_random_int_below(D_L01_001AFEC0 - 1) == 0) && (((UView *)(vars))->h[0x16E] == 0)) {
                        if ((D_L01_001AFE5C < distanceToHero) && (func_001163B0() & 1)) {
                            swamp_monster_start_attack_b(moby);
                        } else {
                            swamp_monster_start_claw_attack(moby);
                        }
                    }
                    break;
                }
                attackStageNow = ((UView *)(moby))->b[0xBC];
                if ((attackStageNow != 5) && (attackStageNow < 7U) && (D_L01_001AFE68 < distanceToHero)) {
                    moby_set_controller_speed_limits(moby, D_L01_001AFE9C * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFEA4 * 0.0000048481375f, D_L01_001AFEA8 * 0.00029088825f);
                    ((UView *)(moby))->b[0xBC] = 5U;
                    ((UView *)(vars))->c[0x2E0] = 0;
                    ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
                    ((UView *)(vars))->c[0x71] = 0xF;
                    ((UView *)(vars))->c[0x72] = 0xF;
                    ((UView *)(vars))->b[0x2E1] = 4U;
                    ((UView *)(vars))->c[0x2E2] = 0x16;
                }
                if (((UView *)(vars))->f[0x8] < (IntToFloat((s32) ((UView *)(vars))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(vars))->c[0x2E0] = 1;
                    ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE54;
                    ((UView *)(vars))->b[0x2E1] = 5U;
                    ((UView *)(vars))->c[0x2E2] = 0xE;
                    ((UView *)(vars))->c[0x71] = 0x13;
                    ((UView *)(vars))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE94 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(moby))->b[0xBC] = 7U;
                    moby_set_animation_and_speed(moby, 0x10, 0, 0xD);
                    moby_set_state(moby, 0, 5);
                }
                break;
            case 7:                                 /* switch 2 */
                if ((distanceToHero <= D_L01_001AFE54) && (turnToHero < (D_L01_001AFEB4 * 0.017453294f)) && (((UView *)(vars))->h[0x16F] == 0)) {
                    ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
                    ((UView *)(moby))->b[0xBC] = 9U;
                    ((UView *)(vars))->c[0x2E0] = 1;
                    ((UView *)(vars))->b[0x2E1] = 1U;
                    ((UView *)(vars))->c[0x2E2] = 0;
                    ((UView *)(vars))->c[0x71] = 0x13;
                    ((UView *)(vars))->c[0x72] = 0x13;
                    moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE98 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    swamp_monster_start_grab_attack(moby);
                }
                break;
            case 8:                                 /* switch 2 */
                ((UView *)(moby))->i[0x26] = 0;
                if (distanceToHero <= D_L01_001AFE5C) {
                    animNow3 = ((UView *)(moby))->b[0x42];
                    if (animNow3 != 0x16) {
                        if (animNow3 == 0) {
                            goto block_95;
                        }
                    } else {
block_95:
                        ((UView *)(vars))->c[0x2E0] = 1;
                        ((UView *)(vars))->b[0x2E1] = 1U;
                        ((UView *)(vars))->c[0x71] = 0x13;
                        ((UView *)(vars))->c[0x72] = 0x13;
                        ((UView *)(vars))->c[0x2E2] = 0;
                        moby_set_controller_speed_limits(moby, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                        ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
                        ((UView *)(moby))->b[0xBC] = 9U;
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        moby_set_animation_and_speed(moby, 0x16, 0, 0x14);
                        moby_set_state(moby, 0, 5);
                    }
                }
                break;
            case 9:                                 /* switch 2 */
                ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                if ((distanceToHero <= D_L01_001AFE5C) && (turnToHero < (D_L01_001AFEAC * 0.017453294f))) {
                    if ((math_random_int_below(D_L01_001AFEC0 - 1) == 0) && (((UView *)(vars))->h[0x16E] == 0)) {
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
                    if ((D_L01_001AFE5C < distanceToHero) && (distanceToHero <= D_L01_001AFE60) && (turnToHero < (D_L01_001AFEB0 * 0.017453294f))) {
                        if ((math_random_int_below(D_L01_001AFEC4 - 1) == 0) && (((UView *)(vars))->h[0x16D] == 0)) {
                            swamp_monster_start_attack_c(moby);
                        } else {
                            goto block_112;
                        }
                    } else {
block_112:
                        if (D_L01_001AFE68 < distanceToHero) {
                            ((UView *)(vars))->b[0x2E1] = 4U;
                            ((UView *)(vars))->c[0x2E2] = 0x16;
                            ((UView *)(vars))->c[0x2E0] = 0;
                            moby_set_controller_speed_limits(moby, D_L01_001AFE9C * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFEA4 * 0.0000048481375f, D_L01_001AFEA8 * 0.00029088825f);
                            ((UView *)(vars))->f[0xBB] = (f32) D_L01_001AFE5C;
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
        animFrame = moby_get_anim_value(moby);
        switch (((UView *)(moby))->b[0x20]) {                        /* switch 5; irregular */
        case 1:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if ((animFrame > 44.0f) && (animFrame < 68.0f)) {
                grabAnim = ((UView *)(moby))->b[0x42];
                jointBase = -1;
                if (grabAnim == 6) {
                    jointBase = 0;
                } else if (grabAnim == 7) {
                    jointBase = 4;
                }
                if (jointBase >= 0) {
                    moby_transform_joint_to_world(moby, jointBase, (scratch + 4));
                    for (jointStep = 1; jointStep < 3; jointStep++) {
                        part_init_effect_record((scratch + 8), (s32) moby, 1, (f32) ((UView *)(vars))->b[0x34]);
                        qcopy(scratch, scratch + 4);
                        moby_transform_joint_to_world(moby, jointBase + jointStep, scratch + 4);
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
            if (math_is_value_within_step((u8 *) moby, 16.0f) != 0) {
                moby_transform_joint_to_world(moby, 0xA, scratch);
                FastVecSub((scratch + 4), ((u8 *)((UView *)(vars))->p[0x48]) + 0x10, scratch);
                vec_scale_to_length((scratch + 4), (scratch + 4), D_L01_001AFEF4 * 0.016666668f);
                scratch[6] = weapon_compute_shot_launch_speed(scratch, ((u8 *)((UView *)(vars))->p[0x48]) + 0x10, NULL, D_L01_001AFEF4 * 0.016666668f, -(D_L01_001AFEF8 * 0.00027777778f));
                moby_spawn_thrown_object(scratch, (scratch + 4), moby, (f32) ((UView *)(vars))->b[0x34]);
            }
            break;
        case 3:                                     /* switch 5 */
            if ((animFrame > 34.0f) && (animFrame < 41.0f)) {
                hitFlags = (func_001163B0() & 1) | 8;
                coll_test_hit_at_bone(moby, 2.2f, (f32) ((UView *)(vars))->b[0x34], hitFlags, 1, 1.0f, 0, 1, 0);
            }
            break;
        case 4:                                     /* switch 5 */
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((HeroV *)g_hero_state)->x - ((UView *)(moby))->f[0x4], ((HeroV *)g_hero_state)->y - ((UView *)(moby))->f[0x5]));
            if (((UView *)(vars))->b[0x2F4] == 0) {
                if (animFrame > 12.0f) {
                    if (animFrame <= 17.0f) {
                        moby_transform_joint_to_world(moby, 0xC, scratch);
                        scratch[2] -= 2.4f;
                        if ((fast_vec_dist(scratch, &((HeroV *)g_hero_state)->x) < D_L01_001AFE6C) && (*(s32 *)(g_hero_state + 0x2294) != 0x6F)) {
                            ((UView *)(vars))->b[0x2F4] = 1U;
                        }
                    } else {
                        goto block_149;
                    }
                } else {
block_149:
                    if ((animFrame > 17.0f) && (animFrame < 19.0f)) {
                        ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                        hitFlags = (func_001163B0() & 1) | 0xC;
                        coll_test_hit_at_bone(moby, 2.0f, (f32) ((UView *)(vars))->b[0x35], hitFlags, 1, 1.0f, 0, 1, 0);
                    }
                }
            } else if (animFrame > 19.0f) {
                ((HeroV *)g_hero_state)->a22b5 = 1;
            }
            break;
        }
        if (((UView *)(vars))->b[0x2F4] != 0) {
            swamp_monster_hold_hero(moby);
            if (((UView *)(moby))->b[0x60] & 2) {
                if (((HeroV *)g_hero_state)->a24cc < 2) {
                    hero_record_play_counters();
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
        grabAnimFrame = moby_get_anim_value(moby);
        arenaRow = (u8 *)((((UView *)(vars))->i[0xB3] << 7) + (s32)D_L01_001B264C);
        angleToArena = mat_fast_helper_a(*(f32 *)(arenaRow + 0x30) - ((UView *)(moby))->f[0x4], *(f32 *)(arenaRow + 0x34) - ((UView *)(moby))->f[0x5]);
        anglePlus = FastAddRotations(angleToArena, 1.5707965f);
        angleMinus = fast_subtract_rotations(angleToArena, 1.5707965f);
        turnA = FastDiffRots(((UView *)(moby))->f[0x3E], anglePlus);
        moby_start_effect_from_entry(moby, turnA < FastDiffRots(((UView *)(moby))->f[0x3E], angleMinus) ? anglePlus : angleMinus);
        if (((UView *)(moby))->b[0x42] == 0xB) {
            handFar = 1;
            moby_transform_joint_to_world(moby, 0xE, scratch);
            handDistance = fast_vec_dist(scratch, &((Hero *)g_hero_state)->b[0x80]);
            if (!(handDistance > 13.0f)) {
                handFar = 0;
            }
            if (((UView *)(vars))->b[0x2F4] != 0) {
                if (grabAnimFrame > 33.0f) {
                    SetHeroMoveState(0x16, 1);
                    ((Hero *)g_hero_state)->i[0x2294 / 4] = 0x6F;
                    ((Hero *)g_hero_state)->i[0x24A0 / 4] = 0;
                    ((Hero *)g_hero_state)->i[0x229C / 4] = 9;
                    ((Hero *)g_hero_state)->c[0x22B5] = 0;
                    ((UView *)(vars))->b[0x2F4] = 0U;
                } else {
                    ((Hero *)g_hero_state)->c[0x22B5] = 1;
                    swamp_monster_hold_hero(moby);
                }
            }
            if ((((UView *)(vars))->b[0x2F4] == 0) && (handFar == 0)) {
                vec_scale_to_length((scratch + 4), moby + 0xC0, D_L01_001AFEEC);
                vec_scale_to_length((scratch + 8), (scratch + 4), D_L01_001AFEF0 * 0.016666668f);
                velocityLength = vec_length_xy((scratch + 8));
                scratch[10] = velocityLength * (math_square(1.0f - (handDistance * 0.006666667f)) * 0.7f);
                qcopy(&((Hero *)g_hero_state)->b[0xF0], scratch + 8);
                qcopy(&((Hero *)g_hero_state)->b[0x110], scratch + 8);
                FastVecAdd(&((Hero *)g_hero_state)->b[0x80], &((Hero *)g_hero_state)->b[0x80], (scratch + 8));
            }
            if (handFar != 0) {
                ((UView *)(moby))->i[0x27] = (s32) (((UView *)(moby))->i[0x27] & ~0x30);
                *(s32 *)(moby + 0x98) = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                if (D_0018C0B4 == 0x6F) {
                    SetHeroMoveState(0x16, 1);
                }
            }
            if (((UView *)(moby))->b[0x60] & 2) {
                ((UView *)(moby))->i[0x27] = (s32) (((UView *)(moby))->i[0x27] & ~0x30);
                ((UView *)(moby))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(moby))->p[0x9]) + 0x10);
                moby_set_animation_and_speed(moby, 0xC, 0, 0x14);
                moby_set_state(moby, 0, 5);
                if (D_0018C0B4 == 0x6F) {
                    SetHeroMoveState(0x16, 1);
                }
            }
        } else {
            if (((UView *)(moby))->b[0x95] == 4) {
                grabFlag = ((UView *)(vars))->b[0x2F4];
                if (grabFlag == 1) {
                    D_0018C0D5 = grabFlag;
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
        hitResult = moby_dispatch_action_by_kind(moby, vars + 0x60);
        if (hitResult & 1) {
            moby_set_state(moby, 0, 7);
        } else if (hitResult & 2) {
            moby_set_animation_and_speed(moby, (s32) ((UView *)(vars))->b[0x2E1], 0, 0xC);
            moby_set_state(moby, 0, 2);
        }
        break;
    case 7:                                         /* switch 1 */
        ((UView *)(moby))->i[0x12] = 0;
        ((UView *)(moby))->uh[0x1A] = (u16) (((UView *)(moby))->uh[0x1A] | 0x41);
        soundHandle = ((u8 *)((UView *)(vars))->p[0xB9]);
        if (soundHandle != NULL) {
            cam_end_override(soundHandle);
            ((u8 *)((UView *)(vars))->p[0xB9]) = NULL;
        }
        mobyPosition = moby + 0x10;
        newHeldMoby = SpawnGoldBolt(mobyPosition, 1, -1, -1);
        ((u8 *)((UView *)(vars))->p[0xC0]) = newHeldMoby;
        if (newHeldMoby != NULL) {
            SetHeroMoveState(0x6F, 1);
            throwVelocity = vars + 0x2A0;
            heldMobyPtr = ((u8 *)((UView *)(vars))->p[0xC0]);
            *(f32 *)(heldMobyPtr + 0x18) = (f32) (*(f32 *)(heldMobyPtr + 0x18) - 0.5f);
            FastVecSub(throwVelocity, mobyPosition, g_hero_position);
            ((UView *)(vars))->f[0xAA] = (f32) (((UView *)(vars))->f[0xAA] + 1.0f);
            FastVecScale(throwVelocity, throwVelocity, 0.85f);
            ((UView *)(vars))->f[0xAB] = 1.0f;
            moby_set_state(moby, 0, 8);
        }
        break;
    case 8:                                         /* switch 1 */
        heldLinkId = ((UView *)(vars))->i[0xBE];
        pullProgress = ((UView *)(vars))->f[0xAB] - 0.00625f;
        ((UView *)(vars))->f[0xAB] = pullProgress;
        if (heldLinkId != -1) {
            regionId = (*(s32 *)((u8 *)((*(u8 **)((u8 *)((heldLinkId << 8) + (s32)g_moby_l01_table) + 0x68))) + 0x28));
            regionTable = D_L01_001B264C_sda;
            if (regionId != -1) {
                rowOffset = regionId << 7;
                qcopy(g_hero_position, (u8 *)(rowOffset + (s32)regionTable) + 0x30);
                rowPointer = (u8 *)(rowOffset + (s32)regionTable);
                qcopy(g_hero_position + 0x10, (u8 *)rowPointer + 0x70);
            }
        }
        if ((u8) *(u8 *)(((u8 *)((UView *)(vars))->p[0xC0]) + 0x20) < 2U) {
            heldLinkId2 = ((UView *)(vars))->i[0xBE];
            if (heldLinkId2 != -1) {
                linkedMoby = (u8 *)((heldLinkId2 << 8) + (s32)D_L01_001B255C_sda);
                if (*(u8 *)(linkedMoby + 0xBC) != 0) {
                    *(u8 *)(linkedMoby + 0xBC) = 0U;
                    UpdateCameraPoseTrigger(g_moby_l01_table + (((UView *)(vars))->i[0xBE] << 8));
                }
            }
            throwVelocityPtr = vars + 0x2A0;
            heldPosition = ((u8 *)((UView *)(vars))->p[0xC0]) + 0x10;
            vec_scale_to_length(heldPosition, throwVelocityPtr, pullProgress * FastVecLength(throwVelocityPtr));

            *(f32 *)((((u8 *)((UView *)(vars))->p[0xC0])) + 0x18) = (f32) (*(f32 *)((((u8 *)((UView *)(vars))->p[0xC0])) + 0x18) + (math_fast_sin_or_cos_b(pullProgress * 3.1415927f) * 4.0f));
            effectPosition = ((u8 *)((UView *)(vars))->p[0xC0]) + 0x10;
            FastVecAdd(effectPosition, effectPosition, g_hero_position);
            heldVars = *(u8 **)(((u8 *)((UView *)(vars))->p[0xC0]) + 0x68);
            heldVelocity = heldVars + 0x10;
            FastVecSub(heldVelocity, moby + 0x10, g_hero_position);
            vec_scale_to_length(heldVelocity, heldVelocity, 2.5f);
            *(f32 *)(heldVars + 0x1C) = FastAddRotations(mat_fast_helper_a(*(f32 *)(heldVars + 0x10), *(f32 *)(heldVars + 0x14)), 3.1415927f);
            FastVecAdd(heldVelocity, heldVelocity, g_hero_position);
            func_002A0F48(((u8 *)((UView *)(vars))->p[0xC0]));
            ((UView *)(vars))->f[0xAB] = pullProgress;
        }
        heldMoby = ((u8 *)((UView *)(vars))->p[0xC0]);
        if ((heldMoby == NULL) || (*(s16 *)(heldMoby + 0xAA) != 0x1250 /* moby class 4688 */) || (heldState = *(u8 *)(heldMoby + 0x20), (heldState == 0xFE)) || (heldState == 0xFD)) {
            SetDeathBits(moby, 0, 3);

            if ((((UView *)(moby))->b[0xB0]) != 0xFF) {
                moby_mark_table_entry_flagged((u32) (((UView *)(moby))->b[0xB0]));
            }
            if (((UView *)(vars))->i[0xC1] != -1) {
                FadeToBlack(0x10);
                load_scene_chunk(0, 0);
                regionRow = D_L01_001B264C + (((UView *)(vars))->i[0xC1] << 7);
                hero_reset_position_and_direction(regionRow + 0x30, regionRow + 0x70, 0, 1);
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
            }
            linkedMobyId2 = ((UView *)(vars))->i[0xC2];
            if (linkedMobyId2 != -1) {
                (*(s8 *)((u8 *)((linkedMobyId2 << 8) + (s32)D_L01_001B255C_sda) + 0xBC)) = 1;
            }
            script_queue_keyed_request(((UView *)(vars))->i[0xC5], ((UView *)(vars))->i[0xC7]);
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
        waterHeight = level_get_water_height();
        if ((((UView *)(moby))->b[0x95] != 0) && (((HeroV *)g_hero_state)->z < (waterHeight - 1.8f)) && (((HeroV *)g_hero_state)->z < (((UView *)(moby))->f[0x6] - 1.0f)) && (vec_distance_xy(moby + 0x10, &((HeroV *)g_hero_state)->x) < 10.0f)) {
            hero_record_play_counters();
        }
        swamp_monster_update_timers(moby);
}
