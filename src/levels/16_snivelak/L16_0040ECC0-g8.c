/* Snivelak boss update, alone in its unit for -g (statement-boundary nops) and its -G8 $gp reads.
 * The switch needs `case 1: break;` (retail's table starts at 1). func_002AAA00 returns the new
 * heading in $f0: as a call_value, each turn call's f0 set ends the earlier f0 reads, which is
 * what orders retail's a0 move before mov.s $f12 at the turn calls in cases 4 and 13. One local
 * per heading, slot and sound handle; D_0013963B is D_001395B8[0x83]; plain externs for the
 * level scalars the assembler reaches through $gp only in delay slots.
 */
#include "common.h"



typedef int BossQuadword __attribute__((mode(TI)));

/* Measured partial view of the boss's private record, through offset 0x36f. */
typedef struct {
    u8 reserved00[0x20];
    float health;
    short maximumHealth;
    u8 reserved26[15];
    u8 power;
    u8 reserved36[0x142];
    int entryArea;
    u8 reserved17c[0x18];
    int exitArea;
    u8 reserved198[0x24];
    int introStarted;
    u8 reserved1c0[0x30];
    u8 *body;
    u8 reserved1f4[12];
    float destination[4];
    float lastPlayer[4];
    u8 reserved220[0x14];
    float turnVelocity;
    u8 *arms[2];
    int activeArm;
    int fired;
    int reserved248;
    u8 *target;
    float aimTime;
    float aimBlend;
    int reserved258;
    int aimTimeout;
    int reserved260;
    float floorHeight;
    float verticalSpeed;
    int bodyMode;
    int resumeState;
    int resumeArgument;
    u8 reserved278[0xa8];
    u8 taunted;
    u8 reserved321[0x2f];
    int suppressSpeech;
    int reserved354[2];
    int fireTimer;
    u8 *projectile;
    short leftUsed;
    short rightUsed;
    int attackSound;
    int bodySound;
} SnivelakBossState;

/* The same work area holds a bone matrix or two temporary vectors in disjoint states. */
typedef union {
    float bone[16];
    struct { float position[4], offset[4]; } vectors;
} BossWork;

typedef struct {
    u8 prefix[0x30];
    int field30, field34, field38, field3c, field40, field44;
} BarlowUtilityQueueView;

typedef int HeroTI __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; HeroTI q[0x260]; } Hero;
extern char g_hero_state[];
/* These resident scalars/pointer are outside the GP-relative range. */
extern u8 D_001395B8[];
extern u8 g_sound_state[];
extern BarlowUtilityQueueView D_L16_001BFD00;
extern int D_L16_001A8F00;
extern u8 *D_L16_001B16C0 __attribute__((sda));
extern float D_L16_001B16E4 __attribute__((sda));
extern float D_L16_001B16E8 __attribute__((sda));
extern float D_L16_001B16EC __attribute__((sda));
extern float D_L16_001B16F0 __attribute__((sda));
extern float D_L16_001B16F4 __attribute__((sda));
extern float D_L16_001B16F8 __attribute__((sda));
extern unsigned int D_L16_001B2648;
extern float D_L16_001B2564;
extern float D_L16_001B9B00[4];

/* Current C interfaces and retail-observed register banks for assembly callees. */
extern void UpdateSnivelakBossDamage(u8 *);
extern int IsPointInCuboid(void *, int);
extern int req_push_queue(u8 *, int);
extern int req_launch_queued(BarlowUtilityQueueView *);
extern void game_set_stored_value_pair(int, int);
extern int game_is_either_mode_two(void);
extern void snivelak_finish_boss_intro_state(u8 *);
extern void snivelak_clean_up_boss_and_free(u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern int flag_set_first_pending(u8 *);
extern void anim_play_on_self_or_child(u8 *, int, int, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float vec_distance_squared_xy(void *, void *);
extern void snd_play_unplayed_voice_line(u8 *, int, int);
extern void snivelak_find_closest_path_point(u8 *, void *);
extern void snivelak_move_along_path(u8 *, float);
extern float vec_distance_xy(void *, void *);
extern float moby_get_anim_value(char *);
extern float math_fabs(float);
extern int PlayMobySound(int, int, char *);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void snd_stop_voice(int);
extern void RequestVoiceLine(u8 *, int);
extern void snivelak_fire_body_shots(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_approach_target_with_direction_mode(float *, float, float, float, float, float *, int);
extern int math_fast_float_d(int *);
extern void snivelak_drop_falling_shot(u8 *);
extern int snd_start_in_slot(int, int, int);
extern void snivelak_fire_arm_shot(u8 *);
extern void path_pick_new_slot(u8 *, float, float);
extern void snivelak_switch_fly_hover_state(u8 *);
extern void anim_start_blended(u8 *, int, int, int);
extern float ApproachValue(float *, float, float);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void snivelak_draw_laser_beam(void *);
extern int coll_sweep_from_object(u8 *, void *, int, int, int, int, float, float, float);
extern u8 *snivelak_spawn_rock_projectile(u8 *, int);
extern void snivelak_fire_lobbed_shot(u8 *);
extern void moby_transform_joint_point(char *, int, char *);
extern int coll_is_behind_surface(u8 *);
extern void snivelak_attach_child_to_parent_pose(u8 *, u8 *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float weapon_compute_shot_launch_speed(void *, void *, float *, float, float);
extern void snivelak_launch_projectile(u8 *, void *, float);
extern float math_random_signed_float_range(float, float), math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_blast_effect_moby(u8 *, void *, void *, float);
extern void transition_arm_shared(int, float, float);
extern void SetMobyAndGroupsEnabled(u8 *, int);
extern void snivelak_part_update(u8 *);
extern void snivelak_copy_bones_to_children(u8 *);

/* Advances the boss's arena, animation, aiming and projectile phases. */
/* This is the per-frame update of the Snivelak boss (moby class 3961). */
void snivelak_update(u8 *moby)
{
    u8 *slot1, *slot2, *slot3, *slot4, *slot5, *slot6;
    SnivelakBossState *state = *(SnivelakBossState **)(moby + 0x68);
    BossWork work;
    float velocity[4] __attribute__((aligned(16)));
    float angle, distance, frame, frame2, gravity;
    u8 *flags;
    float *heading0, *heading1, *heading2, *heading3, *heading6, *heading7, *heading8;
    int next, sound1, sound2, sound3, sound4;
    UpdateSnivelakBossDamage(moby);
    if (!moby || moby[0x20] == 254 || moby[0x20] == 253) return;

    switch (moby[0x95]) {
    case 0:
        if (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x20], state->entryArea) ||
            (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x20], state->exitArea) && D_001395B8[0x83] == 1)) {
            flags = D_001395B8;
            if (!flags[0x83]) {
                if (req_push_queue((u8 *)&D_L16_001BFD00, 132)) {
                    req_launch_queued(&D_L16_001BFD00);
                    game_set_stored_value_pair((int)snivelak_finish_boss_intro_state, (int)moby);
                    flags[0x83] = 1;
                    state->introStarted = 1;
                }
            } else if (!game_is_either_mode_two()) {
                snivelak_finish_boss_intro_state(moby);
            }
        } else if ((*(unsigned short *)(moby + 0x34) & 1) && ((Hero *)g_hero_state)->f[0x20] >= 610.0f) {
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xffbe) | 0x1000;
            *(int *)(moby + 0x98) = *(int *)(*(u8 **)(moby + 0x24) + 0x10);
            if (state->body) {
                *(unsigned short *)(state->body + 0x34) &= 0xffbe;
                *(unsigned short *)(state->body + 0x34) |= 0x1000;
                *(int *)(state->body + 0x98) = *(int *)(*(u8 **)(state->body + 0x24) + 0x10);
            }
            if (state->arms[0]) {
                *(unsigned short *)(state->arms[0] + 0x34) &= 0xffbe;
                *(unsigned short *)(state->arms[0] + 0x34) |= 0x1000;
                *(int *)(state->arms[0] + 0x98) = *(int *)(*(u8 **)(state->arms[0] + 0x24) + 0x10);
            }
            if (state->arms[1]) {
                *(unsigned short *)(state->arms[1] + 0x34) &= 0xffbe;
                *(unsigned short *)(state->arms[1] + 0x34) |= 0x1000;
                *(int *)(state->arms[1] + 0x98) = *(int *)(*(u8 **)(state->arms[1] + 0x24) + 0x10);
            }
        }
        break;
    case 1:
        if (D_L16_001B16C0) {
            state->target = D_L16_001B16C0;
            moby_set_state(moby, 7, 2);
        }
        break;
    case 2:
        if (!D_L16_001B16C0) moby_set_state(moby, 2, 1);
        break;
    }
    if (D_L16_001A8F00 == 2) return;

    switch (moby[0x20]) {
    case 1:
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 10, 15, 3.0f);
            if (!math_random_int_below(1)) {
                if (vec_distance_squared_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x20]) > 1600.0f)
                    snd_play_unplayed_voice_line(moby, 3, 6);
                else snd_play_unplayed_voice_line(moby, 7, 11);
            }
        }
        snivelak_find_closest_path_point(moby, &((Hero *)g_hero_state)->f[0x20]);
        snivelak_move_along_path(moby, D_L16_001B16E4 * 0.016666668f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 32.0f) {
            frame = moby_get_anim_value((char *)moby);
            if (math_fabs(frame - 5.0f) < 1.0f || math_fabs(frame - 21.0f) < 1.0f) {
                PlayMobySound(8, 0, (char *)moby);
                moby_set_state(moby, 3, -1);
            }
        }
        snivelak_switch_fly_hover_state(moby);
        break;
    case 16:
        if (flag_set_first_pending(moby)) state->verticalSpeed = 0.0f;
        state->verticalSpeed -= 0.008333334f;
        *(float *)(moby + 0x18) += state->verticalSpeed;
        if (*(float *)(moby + 0x18) <= state->floorHeight) {
            *(float *)(moby + 0x18) = state->floorHeight;
            PlayMobySound(9, 0, (char *)moby);
            moby_set_state(moby, state->resumeState, state->resumeArgument);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            PlayMobySound(9, 0, (char *)moby);
            anim_play_on_self_or_child(moby, 3, 15, 6.0f);
            if (!math_random_int_below(1)) snd_play_unplayed_voice_line(moby, 12, 15);
        }
        if (!state->taunted && !state->suppressSpeech && !math_random_int_below(2) &&
            ((Hero *)g_hero_state)->i[0x8A5] == 22 && ((Hero *)g_hero_state)->i[0x6E] == 1 && ((u8 *)((Hero *)g_hero_state)->ptr[0x927]) &&
            *(short *)(((u8 *)((Hero *)g_hero_state)->ptr[0x927]) + 0xaa) == 0xea7) {
            state->taunted = 1;
            RequestVoiceLine(moby, 16);
        }
        if ((D_L16_001B2648 & 15) == (((int)moby >> 8) & 15)) snivelak_fire_body_shots(moby);
        snivelak_find_closest_path_point(moby, &((Hero *)g_hero_state)->f[0x20]);
        if (((Hero *)g_hero_state)->i[0x8A5] == 129) moby_set_state(moby, 6, -1);
        else if (vec_distance_xy(moby + 0x10, state->destination) > 48.0f) moby_set_state(moby, 2, -1);
        else if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x20]) < 12.0f &&
                 math_fabs(((Hero *)g_hero_state)->f[0x22] - state->floorHeight) < 10.0f) moby_set_state(moby, 5, -1);
        else {
            angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
            if (FastDiffRots(*(float *)(moby + 0xf8), angle) > 0.26179942f) moby_set_state(moby, 4, -1);
            else if (*(unsigned short *)(moby + 0x96) > 900) {
                moby_set_state(moby, 11, -1);
                state->target = 0;
                qcopy(state->lastPlayer, &((Hero *)g_hero_state)->f[0x34]);
            }
        }
        snivelak_switch_fly_hover_state(moby);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
            if (fast_subtract_rotations(*(float *)(moby + 0xf8), angle) > 0.0f)
                anim_play_on_self_or_child(moby, 10, 30, 1.0f);
            else
                anim_play_on_self_or_child(moby, 10, 30, 10.0f);
        }
        heading0 = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(heading0, angle, 0.00174532947f, 0.00174532947f, 0.104719773f, &state->turnVelocity, 0);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xf8), angle) < 0.087266475f && moby[0x42] == moby[0x43]) moby_set_state(moby, 3, -1);
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            state->verticalSpeed = 0.0f;
            state->bodyMode = 1;
            state->fireTimer = 30;
            anim_play_on_self_or_child(moby, 0, 30, state->verticalSpeed);
        }
        heading1 = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(heading1, angle, 0.000872664736f, 0.000872664736f, 0.104719773f, &state->turnVelocity, 0);
        if (math_fast_float_d(&state->fireTimer)) {
            snivelak_drop_falling_shot(moby);
            snd_start_in_slot(17, 0, (int)moby);
            state->fireTimer = math_random_int_range(45, 75);
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x20]) > 16.0f || math_fabs(((Hero *)g_hero_state)->f[0x22] - state->floorHeight) > 10.0f) moby_set_state(moby, 2, -1);
        break;
    case 6:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 16, 30, 0.0f);
            *(float *)(moby + 0x48) = 0.666f;
        }
        if (state->body[0x60] & 2) moby_set_state(moby, 2, -1);
        break;
    case 8:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, state->activeArm + 11, 20, 0.0f);
            if (!state->suppressSpeech) snd_play_unplayed_voice_line(moby, 17, 23);
            state->fired = 0;
            *(float *)(moby + 0x48) = 1.0f;
        }
        heading2 = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(heading2, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (!state->fired && state->body[0x42] == state->body[0x43] && moby_get_anim_value((char *)state->body) >= 13.0f) {
            if (state->body[0x42] == 11) PlayMobySound(7, 0, (char *)moby);
            snivelak_fire_arm_shot(moby);
            state->fired = 1;
        } else if (moby_get_anim_value((char *)state->body) > 20.0f) {
            anim_play_on_self_or_child(moby, state->activeArm + 11, 20, 0.0f);
            state->fired = 0;
        }
        if (*(unsigned short *)(moby + 0x96) > 300) moby_set_state(moby, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 10, 30, 6.0f);
            path_pick_new_slot(moby, D_L16_001B16EC, D_L16_001B16F0);
        }
        snivelak_move_along_path(moby, D_L16_001B16E8 * 0.016666668f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 1.0f) moby_set_state(moby, 8, -1);
        snivelak_switch_fly_hover_state(moby);
        break;
    case 9:
        if (flag_set_first_pending(moby)) anim_play_on_self_or_child(moby, 16, 30, 6.0f);
        heading3 = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(heading3, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (state->body[0x60] & 2) {
            if ((float)state->maximumHealth * 0.55f <= state->health) moby_set_state(moby, 10, -1);
            else if (math_random_int_below(2) || !state->leftUsed || !state->rightUsed) moby_set_state(moby, 13, -1);
            else moby_set_state(moby, 10, -1);
        }
        break;
    case 10:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 10, 30, 6.0f);
            snivelak_find_closest_path_point(moby, state->target + 0x10);
        }
        snivelak_move_along_path(moby, D_L16_001B16E8 * 0.016666668f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 1.0f) {
            if (math_fabs(*(float *)(state->target + 0x18) - 120.0f) < 1.0f) moby_set_state(moby, 12, -1);
            else moby_set_state(moby, 11, -1);
        }
        break;
    case 11:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != 22) anim_start_blended(moby, 22, 0, 20);
            anim_start_blended(state->body, 3, 0, 30);
            state->aimTimeout = 120;
            state->aimTime = D_L16_001B16F4;
            state->aimBlend = 0.0f;
            state->verticalSpeed = 0.0f;
        }
        if (state->target) {
            angle = mat_fast_helper_a(*(float *)(state->target + 0x10) - *(float *)(moby + 0x10), *(float *)(state->target + 0x14) - *(float *)(moby + 0x14));
        } else {
            angle = mat_fast_helper_a(state->lastPlayer[0] - *(float *)(moby + 0x10), state->lastPlayer[1] - *(float *)(moby + 0x14));
        }
        math_approach_target_with_direction_mode((float *)(moby + 0xf8), angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (FastDiffRots(angle, *(float *)(moby + 0xf8)) < 0.087266475f) {
            ApproachValue(&state->aimTime, 0.0f, D_L16_001B16F8 * 0.016666668f);
            ApproachValue(&state->aimBlend, 1.0f, 0.06666667f);
            slot1 = g_sound_state + state->attackSound * 112;
            if (*(u8 **)(slot1 + 0x88) != state->body || !slot1[0x74])
                state->attackSound = PlayMobySound(2, 4, (char *)state->body);
            gfx_add_draw_callback_first(snivelak_draw_laser_beam, moby);
        }
        if ((state->target && (*(unsigned short *)(state->target + 0x34) & 1) && math_fast_float_d(&state->aimTimeout)) || (!state->target && state->aimTime <= 0.0f)) {
            moby_set_state(moby, 3, 1);
            sound1 = state->attackSound;
            if (sound1 != -1) {
                slot2 = g_sound_state + sound1 * 112;
                if (*(u8 **)(slot2 + 0x88) == state->body && slot2[0x74]) snd_stop_voice(sound1);
            }
            state->attackSound = -1;
        }
        break;
    case 12:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 1, 30, 0.0f);
            *(float *)(moby + 0x48) = 0.5f;
        }
        angle = mat_fast_helper_a(*(float *)(state->target + 0x10) - *(float *)(moby + 0x10), *(float *)(state->target + 0x14) - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode((float *)(moby + 0xf8), angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        frame2 = moby_get_anim_value((char *)moby);
        if (frame2 > 30.0f) ApproachValue((float *)(moby + 0x48), 1.0f, 0.13333334f);
        if (frame2 > 40.0f && frame2 < 42.0f) coll_sweep_from_object(moby, state->target + 0x10, 0x10001, 0, 1, 0, 4.0f, (float)state->power, 1.0f);
        if (moby[0x60] & 2) moby_set_state(moby, 2, 1);
        else if (((Hero *)g_hero_state)->i[0x8A5] == 22 && ((Hero *)g_hero_state)->i[0x6E] == 1 && ((u8 *)((Hero *)g_hero_state)->ptr[0x927]) == moby) snd_play_unplayed_voice_line(moby, 24, 27);
        break;
    case 13:
        if (flag_set_first_pending(moby)) {
            state->verticalSpeed = 0.0f;
            state->bodyMode = 1;
            anim_play_on_self_or_child(moby, 0, 30, state->verticalSpeed);
            if (state->leftUsed == state->rightUsed) {
                state->projectile = !math_random_int_below(2) ? 0 : snivelak_spawn_rock_projectile(moby, 1);
            } else if (!state->leftUsed) state->projectile = snivelak_spawn_rock_projectile(moby, 1);
            else state->projectile = 0;
        }
        heading6 = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(heading6, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (*(float *)(moby + 0x18) > state->floorHeight + 20.0f) {
            if (state->projectile) { moby_set_state(moby, 14, -1);
            state->leftUsed = 1; }
            else { moby_set_state(moby, 15, -1);
            state->rightUsed = 1; }
        }
        break;
    case 15:
        if (flag_set_first_pending(moby)) anim_play_on_self_or_child(moby, 14, 30, 0.0f);
        heading7 = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(heading7, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (state->body[0x42] == state->body[0x43] && (D_L16_001B2648 & 15) == (((int)moby >> 8) & 15)) snivelak_fire_lobbed_shot(moby);
        if (*(unsigned short *)(moby + 0x96) > 180) moby_set_state(moby, 2, 1);
        break;
    case 14:
        if (flag_set_first_pending(moby)) anim_play_on_self_or_child(moby, 6, 30, 0.0f);
        moby_transform_joint_point((char *)state->body, 3, (char *)work.bone);
        switch (state->body[0x43]) {
        case 6:
            if (coll_is_behind_surface(state->projectile)) {
                snivelak_attach_child_to_parent_pose(state->projectile, (u8 *)work.bone);
                anim_play_on_self_or_child(moby, 7, 5, 0.0f);
            }
            break;
        case 7:
            snivelak_attach_child_to_parent_pose(state->projectile, (u8 *)work.bone);
            if (state->body[0x60] & 2) anim_play_on_self_or_child(moby, 9, 5, 0.0f);
            break;
        case 9:
            if (state->projectile) {
                snivelak_attach_child_to_parent_pose(state->projectile, (u8 *)work.bone);
                if (state->body[0x42] == 9 && moby_get_anim_value((char *)state->body) > 16.0f) {
                    gravity = 0.0013888889f;
                    distance = vec_distance_xy(state->projectile + 0x10, state->target + 0x10) * 0.008333334f;
                    FastVecSub(velocity, state->target + 0x10, state->projectile + 0x10);
                    velocity[2] = 0.0f;
                    vec_scale_to_length(velocity, velocity, distance);
                    velocity[2] = weapon_compute_shot_launch_speed(state->projectile + 0x10, state->target + 0x10, 0, distance, -gravity);
                    snivelak_launch_projectile(state->projectile, velocity, gravity);
                    state->projectile = 0;
                }
            }
            if (state->body[0x60] & 2) moby_set_state(moby, 2, 1);
            break;
        }
        break;
    case 17:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 16, 30, 0.0f);
            *(float *)(moby + 0x48) = 0.5f;
            state->bodyMode = 1;
            if (state->verticalSpeed < 0.0f) state->verticalSpeed = 0.0f;
            sound2 = state->attackSound;
            if (sound2 != -1) {
                slot3 = g_sound_state + sound2 * 112;
                if (*(u8 **)(slot3 + 0x88) == state->body && slot3[0x74]) snd_stop_voice(sound2);
            }
            state->attackSound = -1;
            sound3 = state->bodySound;
            if (sound3 != -1) {
                slot4 = g_sound_state + sound3 * 112;
                if (*(u8 **)(slot4 + 0x88) == moby && slot4[0x74]) snd_stop_voice(sound3);
            }
            state->bodySound = -1;
        }
        heading8 = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(heading8, angle, 0.00174532947f, 0.00174532947f, 0.104719773f, &state->turnVelocity, 0);
        if ((D_L16_001B2648 & 15) == (((int)moby >> 8) & 15)) {
            *(BossQuadword *)work.vectors.offset = 0;
            work.vectors.offset[0] = math_random_signed_float_range(0.0f, 6.0f);
            work.vectors.offset[1] = math_random_signed_float_range(0.0f, 6.0f);
            work.vectors.offset[2] = math_random_float_range(5.0f, 20.0f);
            {
                BossQuadword q = *(BossQuadword *)work.vectors.offset;
                *(BossQuadword *)work.vectors.position = q;
            }
            FastVecAdd(work.vectors.position, work.vectors.position, moby + 0x10);
            FastVecSub(work.vectors.offset, D_L16_001B9B00, work.vectors.position);
            vec_scale_to_length(work.vectors.offset, work.vectors.offset, 1.0f);
            part_spawn_blast_effect_moby(moby, work.vectors.position, work.vectors.offset, 0.0f);
            snd_play_from_class_bank(6, 0, (char *)moby, 0xf78);
        }
        if (state->body[0x42] == state->body[0x43] && state->body[0x41] > 29) transition_arm_shared(5, 5.0f, 15.0f);
        if (D_L16_001B2564 >= 1.0f) {
            moby_set_state(moby, 18, -1);
            moby[0x31] = 0;
            *(unsigned short *)(moby + 0x34) |= 1;
            state->bodyMode = 0;
        }
        break;
    case 18:
        *(float *)(moby + 0x48) = 0.1f;
        *(float *)(state->body + 0x48) = 0.1f;
        state->bodyMode = 0;
        state->verticalSpeed -= 0.0055555557f;
        *(float *)(moby + 0x18) += state->verticalSpeed;
        if (*(unsigned short *)(moby + 0x96) > 90 && D_001395B8[0x83] != 2 && req_push_queue((u8 *)&D_L16_001BFD00, 133)) {
            moby_set_state(moby, 19, -1);
            req_push_queue((u8 *)&D_L16_001BFD00, 17);
            req_push_queue((u8 *)&D_L16_001BFD00, 134);
            req_launch_queued(&D_L16_001BFD00);
            game_set_stored_value_pair((int)snivelak_clean_up_boss_and_free, (int)moby);
        }
        break;
    case 19:
        if (flag_set_first_pending(moby)) {
            *(int *)(moby + 0x98) = 0;
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xefff;
            *(unsigned short *)(state->body + 0x34) |= 0x41;
            *(unsigned short *)(state->body + 0x34) &= 0xefff;
            *(int *)(state->body + 0x98) = 0;
            *(unsigned short *)(state->arms[0] + 0x34) |= 0x41;
            *(unsigned short *)(state->arms[0] + 0x34) &= 0xefff;
            *(int *)(state->arms[0] + 0x98) = 0;
            *(unsigned short *)(state->arms[1] + 0x34) |= 0x41;
            *(unsigned short *)(state->arms[1] + 0x34) &= 0xefff;
            *(int *)(state->arms[1] + 0x98) = 0;
        }
        if (D_L16_001A8F00 == 2) SetMobyAndGroupsEnabled(moby, 0);
        break;
    }
    snivelak_part_update(moby);
    snivelak_copy_bones_to_children(moby);
    if (state->bodyMode) {
        slot5 = g_sound_state + state->bodySound * 112;
        if (*(u8 **)(slot5 + 0x88) != moby || !slot5[0x74])
            state->bodySound = PlayMobySound(10, 4, (char *)moby);
    } else {
        sound4 = state->bodySound;
        if (sound4 != -1) {
            slot6 = g_sound_state + sound4 * 112;
            if (*(u8 **)(slot6 + 0x88) == moby && slot6[0x74])
                snd_stop_voice(sound4);
        }
        state->bodySound = -1;
    }
}
