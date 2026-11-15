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
extern char D_00189E20[];
/* These resident scalars/pointer are outside the GP-relative range. */
extern u8 D_001395B8[];
extern u8 D_00188660[];
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
extern void func_L16_00410618(u8 *);
extern int func_002ACBC8(void *, int);
extern int func_00288AA0(u8 *, int);
extern int func_00288BE8(BarlowUtilityQueueView *);
extern void func_002F5CB8(int, int);
extern int func_002F5D10(void);
extern void func_L16_00412D48(u8 *);
extern void func_L16_00412E70(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern int func_002B3868(u8 *);
extern void func_L16_004116C8(u8 *, int, int, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_L02_002F21C0(void *, void *);
extern void func_L16_00412C58(u8 *, int, int);
extern void func_L16_00410CC0(u8 *, void *);
extern void func_L16_004110D0(u8 *, float);
extern float func_00282E80(void *, void *);
extern float func_0029F530(char *);
extern float func_00282C48(float);
extern int func_002E5CF8(int, int, char *);
extern int func_002E5DA0(int, int, char *, int);
extern void func_002E59F8(int);
extern void func_L16_00412BA8(u8 *, int);
extern void func_L16_00411B40(u8 *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern float func_002AAA00(float *, float, float, float, float, float *, int);
extern int func_00282948(int *);
extern void func_L16_00411ED0(u8 *);
extern int func_L00_0035F5A0(int, int, int);
extern void func_L16_00411900(u8 *);
extern void func_L16_00410E40(u8 *, float, float);
extern void func_L16_00410B88(u8 *);
extern void func_002A7470(u8 *, int, int, int);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L16_00412560(void *);
extern int func_002A8C28(u8 *, void *, int, int, int, int, float, float, float);
extern u8 *func_L16_004130B0(u8 *, int);
extern void func_L16_00411D00(u8 *);
extern void func_0029FC20(char *, int, char *);
extern int func_L16_00413638(u8 *);
extern void func_L16_00413690(u8 *, u8 *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_L00_0031CDD0(void *, void *, float *, float, float);
extern void func_L16_00413700(u8 *, void *, float);
extern float func_002A78D8(float, float), func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_0032DA58(u8 *, void *, void *, float);
extern void func_L16_002D2D10(int, float, float);
extern void func_L16_00411F80(u8 *, int);
extern void func_L16_00411480(u8 *);
extern void func_L16_00411600(u8 *);

/* Advances the boss's arena, animation, aiming and projectile phases. */
/* This is the per-frame update of the Snivelak boss (moby class 3961). */
void func_L16_0040ECC0(u8 *moby)
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
        if (IsPointInCuboid(&((Hero *)gHeroState)->f[0x20], state->entryArea) ||
            (IsPointInCuboid(&((Hero *)gHeroState)->f[0x20], state->exitArea) && D_001395B8[0x83] == 1)) {
            flags = D_001395B8;
            if (!flags[0x83]) {
                if (PushRequestQueue((u8 *)&D_L16_001BFD00, 132)) {
                    LaunchQueuedRequest(&D_L16_001BFD00);
                    SetStoredValuePair((int)FinishBossIntroState, (int)moby);
                    flags[0x83] = 1;
                    state->introStarted = 1;
                }
            } else if (!IsEitherModeTwo()) {
                FinishBossIntroState(moby);
            }
        } else if ((*(unsigned short *)(moby + 0x34) & 1) && ((Hero *)gHeroState)->f[0x20] >= 610.0f) {
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
            SetMobyState(moby, 7, 2);
        }
        break;
    case 2:
        if (!D_L16_001B16C0) SetMobyState(moby, 2, 1);
        break;
    }
    if (D_L16_001A8F00 == 2) return;

    switch (moby[0x20]) {
    case 1:
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) {
            PlayAnimationOnSelfOrChild(moby, 10, 15, 3.0f);
            if (!RandomIntBelow(1)) {
                if (DistanceSquaredXY(moby + 0x10, &((Hero *)gHeroState)->f[0x20]) > 1600.0f)
                    PlayUnplayedVoiceLine(moby, 3, 6);
                else PlayUnplayedVoiceLine(moby, 7, 11);
            }
        }
        FindClosestPathSegmentPoint(moby, &((Hero *)gHeroState)->f[0x20]);
        MoveBossAlongPath(moby, D_L16_001B16E4 * 0.016666668f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 32.0f) {
            frame = GetMobyAnimationValue((char *)moby);
            if (FloatAbs(frame - 5.0f) < 1.0f || FloatAbs(frame - 21.0f) < 1.0f) {
                PlayMobySound(8, 0, (char *)moby);
                SetMobyState(moby, 3, -1);
            }
        }
        SwitchBossFlyHoverState(moby);
        break;
    case 16:
        if (SetFirstPendingFlag(moby)) state->verticalSpeed = 0.0f;
        state->verticalSpeed -= 0.008333334f;
        *(float *)(moby + 0x18) += state->verticalSpeed;
        if (*(float *)(moby + 0x18) <= state->floorHeight) {
            *(float *)(moby + 0x18) = state->floorHeight;
            PlayMobySound(9, 0, (char *)moby);
            SetMobyState(moby, state->resumeState, state->resumeArgument);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(moby)) {
            PlayMobySound(9, 0, (char *)moby);
            PlayAnimationOnSelfOrChild(moby, 3, 15, 6.0f);
            if (!RandomIntBelow(1)) PlayUnplayedVoiceLine(moby, 12, 15);
        }
        if (!state->taunted && !state->suppressSpeech && !RandomIntBelow(2) &&
            ((Hero *)gHeroState)->i[0x8A5] == 22 && ((Hero *)gHeroState)->i[0x6E] == 1 && ((u8 *)((Hero *)gHeroState)->ptr[0x927]) &&
            *(short *)(((u8 *)((Hero *)gHeroState)->ptr[0x927]) + 0xaa) == 0xea7) {
            state->taunted = 1;
            RequestVoiceLine(moby, 16);
        }
        if ((D_L16_001B2648 & 15) == (((int)moby >> 8) & 15)) FireBossBodyShots(moby);
        FindClosestPathSegmentPoint(moby, &((Hero *)gHeroState)->f[0x20]);
        if (((Hero *)gHeroState)->i[0x8A5] == 129) SetMobyState(moby, 6, -1);
        else if (vec_distance_xy(moby + 0x10, state->destination) > 48.0f) SetMobyState(moby, 2, -1);
        else if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x20]) < 12.0f &&
                 FloatAbs(((Hero *)gHeroState)->f[0x22] - state->floorHeight) < 10.0f) SetMobyState(moby, 5, -1);
        else {
            angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
            if (FastDiffRots(*(float *)(moby + 0xf8), angle) > 0.26179942f) SetMobyState(moby, 4, -1);
            else if (*(unsigned short *)(moby + 0x96) > 900) {
                SetMobyState(moby, 11, -1);
                state->target = 0;
                qcopy(state->lastPlayer, &((Hero *)gHeroState)->f[0x34]);
            }
        }
        SwitchBossFlyHoverState(moby);
        break;
    case 4:
        if (SetFirstPendingFlag(moby)) {
            angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
            if (fast_subtract_rotations(*(float *)(moby + 0xf8), angle) > 0.0f)
                PlayAnimationOnSelfOrChild(moby, 10, 30, 1.0f);
            else
                PlayAnimationOnSelfOrChild(moby, 10, 30, 10.0f);
        }
        heading0 = (float *)(moby + 0xf8);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode(heading0, angle, 0.00174532947f, 0.00174532947f, 0.104719773f, &state->turnVelocity, 0);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xf8), angle) < 0.087266475f && moby[0x42] == moby[0x43]) SetMobyState(moby, 3, -1);
        break;
    case 5:
        if (SetFirstPendingFlag(moby)) {
            state->verticalSpeed = 0.0f;
            state->bodyMode = 1;
            state->fireTimer = 30;
            PlayAnimationOnSelfOrChild(moby, 0, 30, state->verticalSpeed);
        }
        heading1 = (float *)(moby + 0xf8);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode(heading1, angle, 0.000872664736f, 0.000872664736f, 0.104719773f, &state->turnVelocity, 0);
        if (FastFloatHelperD(&state->fireTimer)) {
            DropBossFallingShot(moby);
            StartEffectInSlot(17, 0, (int)moby);
            state->fireTimer = RandomIntRange(45, 75);
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x20]) > 16.0f || FloatAbs(((Hero *)gHeroState)->f[0x22] - state->floorHeight) > 10.0f) SetMobyState(moby, 2, -1);
        break;
    case 6:
        if (SetFirstPendingFlag(moby)) {
            PlayAnimationOnSelfOrChild(moby, 16, 30, 0.0f);
            *(float *)(moby + 0x48) = 0.666f;
        }
        if (state->body[0x60] & 2) SetMobyState(moby, 2, -1);
        break;
    case 8:
        if (SetFirstPendingFlag(moby)) {
            PlayAnimationOnSelfOrChild(moby, state->activeArm + 11, 20, 0.0f);
            if (!state->suppressSpeech) PlayUnplayedVoiceLine(moby, 17, 23);
            state->fired = 0;
            *(float *)(moby + 0x48) = 1.0f;
        }
        heading2 = (float *)(moby + 0xf8);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode(heading2, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (!state->fired && state->body[0x42] == state->body[0x43] && GetMobyAnimationValue((char *)state->body) >= 13.0f) {
            if (state->body[0x42] == 11) PlayMobySound(7, 0, (char *)moby);
            FireBossArmShot(moby);
            state->fired = 1;
        } else if (GetMobyAnimationValue((char *)state->body) > 20.0f) {
            PlayAnimationOnSelfOrChild(moby, state->activeArm + 11, 20, 0.0f);
            state->fired = 0;
        }
        if (*(unsigned short *)(moby + 0x96) > 300) SetMobyState(moby, 7, -1);
        break;
    case 7:
        if (SetFirstPendingFlag(moby)) {
            PlayAnimationOnSelfOrChild(moby, 10, 30, 6.0f);
            PickNewPathSlot(moby, D_L16_001B16EC, D_L16_001B16F0);
        }
        MoveBossAlongPath(moby, D_L16_001B16E8 * 0.016666668f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 1.0f) SetMobyState(moby, 8, -1);
        SwitchBossFlyHoverState(moby);
        break;
    case 9:
        if (SetFirstPendingFlag(moby)) PlayAnimationOnSelfOrChild(moby, 16, 30, 6.0f);
        heading3 = (float *)(moby + 0xf8);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode(heading3, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (state->body[0x60] & 2) {
            if ((float)state->maximumHealth * 0.55f <= state->health) SetMobyState(moby, 10, -1);
            else if (RandomIntBelow(2) || !state->leftUsed || !state->rightUsed) SetMobyState(moby, 13, -1);
            else SetMobyState(moby, 10, -1);
        }
        break;
    case 10:
        if (SetFirstPendingFlag(moby)) {
            PlayAnimationOnSelfOrChild(moby, 10, 30, 6.0f);
            FindClosestPathSegmentPoint(moby, state->target + 0x10);
        }
        MoveBossAlongPath(moby, D_L16_001B16E8 * 0.016666668f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 1.0f) {
            if (FloatAbs(*(float *)(state->target + 0x18) - 120.0f) < 1.0f) SetMobyState(moby, 12, -1);
            else SetMobyState(moby, 11, -1);
        }
        break;
    case 11:
        if (SetFirstPendingFlag(moby)) {
            if (moby[0x43] != 22) StartAnimationBlended(moby, 22, 0, 20);
            StartAnimationBlended(state->body, 3, 0, 30);
            state->aimTimeout = 120;
            state->aimTime = D_L16_001B16F4;
            state->aimBlend = 0.0f;
            state->verticalSpeed = 0.0f;
        }
        if (state->target) {
            angle = FastMatrixHelperA(*(float *)(state->target + 0x10) - *(float *)(moby + 0x10), *(float *)(state->target + 0x14) - *(float *)(moby + 0x14));
        } else {
            angle = FastMatrixHelperA(state->lastPlayer[0] - *(float *)(moby + 0x10), state->lastPlayer[1] - *(float *)(moby + 0x14));
        }
        ApproachTargetWithDirectionMode((float *)(moby + 0xf8), angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (FastDiffRots(angle, *(float *)(moby + 0xf8)) < 0.087266475f) {
            ApproachValue(&state->aimTime, 0.0f, D_L16_001B16F8 * 0.016666668f);
            ApproachValue(&state->aimBlend, 1.0f, 0.06666667f);
            slot1 = gSoundState + state->attackSound * 112;
            if (*(u8 **)(slot1 + 0x88) != state->body || !slot1[0x74])
                state->attackSound = PlayMobySound(2, 4, (char *)state->body);
            AddDrawCallbackToList1(DrawBossLaserBeam, moby);
        }
        if ((state->target && (*(unsigned short *)(state->target + 0x34) & 1) && FastFloatHelperD(&state->aimTimeout)) || (!state->target && state->aimTime <= 0.0f)) {
            SetMobyState(moby, 3, 1);
            sound1 = state->attackSound;
            if (sound1 != -1) {
                slot2 = gSoundState + sound1 * 112;
                if (*(u8 **)(slot2 + 0x88) == state->body && slot2[0x74]) StopSoundVoice(sound1);
            }
            state->attackSound = -1;
        }
        break;
    case 12:
        if (SetFirstPendingFlag(moby)) {
            PlayAnimationOnSelfOrChild(moby, 1, 30, 0.0f);
            *(float *)(moby + 0x48) = 0.5f;
        }
        angle = FastMatrixHelperA(*(float *)(state->target + 0x10) - *(float *)(moby + 0x10), *(float *)(state->target + 0x14) - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode((float *)(moby + 0xf8), angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        frame2 = GetMobyAnimationValue((char *)moby);
        if (frame2 > 30.0f) ApproachValue((float *)(moby + 0x48), 1.0f, 0.13333334f);
        if (frame2 > 40.0f && frame2 < 42.0f) SweepCollisionFromObject(moby, state->target + 0x10, 0x10001, 0, 1, 0, 4.0f, (float)state->power, 1.0f);
        if (moby[0x60] & 2) SetMobyState(moby, 2, 1);
        else if (((Hero *)gHeroState)->i[0x8A5] == 22 && ((Hero *)gHeroState)->i[0x6E] == 1 && ((u8 *)((Hero *)gHeroState)->ptr[0x927]) == moby) PlayUnplayedVoiceLine(moby, 24, 27);
        break;
    case 13:
        if (SetFirstPendingFlag(moby)) {
            state->verticalSpeed = 0.0f;
            state->bodyMode = 1;
            PlayAnimationOnSelfOrChild(moby, 0, 30, state->verticalSpeed);
            if (state->leftUsed == state->rightUsed) {
                state->projectile = !RandomIntBelow(2) ? 0 : SpawnBossRockProjectile(moby, 1);
            } else if (!state->leftUsed) state->projectile = SpawnBossRockProjectile(moby, 1);
            else state->projectile = 0;
        }
        heading6 = (float *)(moby + 0xf8);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode(heading6, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (*(float *)(moby + 0x18) > state->floorHeight + 20.0f) {
            if (state->projectile) { SetMobyState(moby, 14, -1);
            state->leftUsed = 1; }
            else { SetMobyState(moby, 15, -1);
            state->rightUsed = 1; }
        }
        break;
    case 15:
        if (SetFirstPendingFlag(moby)) PlayAnimationOnSelfOrChild(moby, 14, 30, 0.0f);
        heading7 = (float *)(moby + 0xf8);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode(heading7, angle, 0.00349065894f, 0.00349065894f, 0.209439546f, &state->turnVelocity, 0);
        if (state->body[0x42] == state->body[0x43] && (D_L16_001B2648 & 15) == (((int)moby >> 8) & 15)) FireBossLobbedShot(moby);
        if (*(unsigned short *)(moby + 0x96) > 180) SetMobyState(moby, 2, 1);
        break;
    case 14:
        if (SetFirstPendingFlag(moby)) PlayAnimationOnSelfOrChild(moby, 6, 30, 0.0f);
        TransformMobyJointPoint((char *)state->body, 3, (char *)work.bone);
        switch (state->body[0x43]) {
        case 6:
            if (IsBehindSurface(state->projectile)) {
                AttachChildToParentPose(state->projectile, (u8 *)work.bone);
                PlayAnimationOnSelfOrChild(moby, 7, 5, 0.0f);
            }
            break;
        case 7:
            AttachChildToParentPose(state->projectile, (u8 *)work.bone);
            if (state->body[0x60] & 2) PlayAnimationOnSelfOrChild(moby, 9, 5, 0.0f);
            break;
        case 9:
            if (state->projectile) {
                AttachChildToParentPose(state->projectile, (u8 *)work.bone);
                if (state->body[0x42] == 9 && GetMobyAnimationValue((char *)state->body) > 16.0f) {
                    gravity = 0.0013888889f;
                    distance = vec_distance_xy(state->projectile + 0x10, state->target + 0x10) * 0.008333334f;
                    FastVecSub(velocity, state->target + 0x10, state->projectile + 0x10);
                    velocity[2] = 0.0f;
                    vec_scale_to_length(velocity, velocity, distance);
                    velocity[2] = ComputeShotLaunchSpeed(state->projectile + 0x10, state->target + 0x10, 0, distance, -gravity);
                    LaunchBossProjectile(state->projectile, velocity, gravity);
                    state->projectile = 0;
                }
            }
            if (state->body[0x60] & 2) SetMobyState(moby, 2, 1);
            break;
        }
        break;
    case 17:
        if (SetFirstPendingFlag(moby)) {
            PlayAnimationOnSelfOrChild(moby, 16, 30, 0.0f);
            *(float *)(moby + 0x48) = 0.5f;
            state->bodyMode = 1;
            if (state->verticalSpeed < 0.0f) state->verticalSpeed = 0.0f;
            sound2 = state->attackSound;
            if (sound2 != -1) {
                slot3 = gSoundState + sound2 * 112;
                if (*(u8 **)(slot3 + 0x88) == state->body && slot3[0x74]) StopSoundVoice(sound2);
            }
            state->attackSound = -1;
            sound3 = state->bodySound;
            if (sound3 != -1) {
                slot4 = gSoundState + sound3 * 112;
                if (*(u8 **)(slot4 + 0x88) == moby && slot4[0x74]) StopSoundVoice(sound3);
            }
            state->bodySound = -1;
        }
        heading8 = (float *)(moby + 0xf8);
        angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)gHeroState)->f[0x21] - *(float *)(moby + 0x14));
        ApproachTargetWithDirectionMode(heading8, angle, 0.00174532947f, 0.00174532947f, 0.104719773f, &state->turnVelocity, 0);
        if ((D_L16_001B2648 & 15) == (((int)moby >> 8) & 15)) {
            *(BossQuadword *)work.vectors.offset = 0;
            work.vectors.offset[0] = RandomSignedFloatRange(0.0f, 6.0f);
            work.vectors.offset[1] = RandomSignedFloatRange(0.0f, 6.0f);
            work.vectors.offset[2] = RandomFloatRange(5.0f, 20.0f);
            {
                BossQuadword q = *(BossQuadword *)work.vectors.offset;
                *(BossQuadword *)work.vectors.position = q;
            }
            FastVecAdd(work.vectors.position, work.vectors.position, moby + 0x10);
            FastVecSub(work.vectors.offset, D_L16_001B9B00, work.vectors.position);
            vec_scale_to_length(work.vectors.offset, work.vectors.offset, 1.0f);
            SpawnBlastEffectMoby(moby, work.vectors.position, work.vectors.offset, 0.0f);
            PlaySoundFromClassBank(6, 0, (char *)moby, 0xf78);
        }
        if (state->body[0x42] == state->body[0x43] && state->body[0x41] > 29) ArmSharedTransition(5, 5.0f, 15.0f);
        if (D_L16_001B2564 >= 1.0f) {
            SetMobyState(moby, 18, -1);
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
        if (*(unsigned short *)(moby + 0x96) > 90 && D_001395B8[0x83] != 2 && PushRequestQueue((u8 *)&D_L16_001BFD00, 133)) {
            SetMobyState(moby, 19, -1);
            PushRequestQueue((u8 *)&D_L16_001BFD00, 17);
            PushRequestQueue((u8 *)&D_L16_001BFD00, 134);
            LaunchQueuedRequest(&D_L16_001BFD00);
            SetStoredValuePair((int)CleanUpBossAndFree, (int)moby);
        }
        break;
    case 19:
        if (SetFirstPendingFlag(moby)) {
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
    UpdateBossPartMoby_L16(moby);
    CopyBossBonesToChildren(moby);
    if (state->bodyMode) {
        slot5 = gSoundState + state->bodySound * 112;
        if (*(u8 **)(slot5 + 0x88) != moby || !slot5[0x74])
            state->bodySound = PlayMobySound(10, 4, (char *)moby);
    } else {
        sound4 = state->bodySound;
        if (sound4 != -1) {
            slot6 = gSoundState + sound4 * 112;
            if (*(u8 **)(slot6 + 0x88) == moby && slot6[0x74])
                StopSoundVoice(sound4);
        }
        state->bodySound = -1;
    }
}
