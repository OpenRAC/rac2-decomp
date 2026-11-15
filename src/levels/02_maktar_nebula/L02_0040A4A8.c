#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern void func_00335870(void);
extern void func_002A7750();
extern char D_L02_001BE200[];
extern void func_L02_003DAE60(void *, int);
extern void func_L02_003DB158(void *, int);
extern void func_L02_003DAF90(void *);
extern void func_L02_003DB030(void *);
extern void func_002AB8C0(void *, void *);
extern void func_002A0488(void *, void *, void *, void *);
extern void func_002B0990(void *, void *, int, int, float);
extern void func_002A8C28(void *, void *, int, float, float, float, int, int, int);
extern void func_L00_003D7250(void *, void *, float, int, int, int);
extern void func_002B60B0(u8 *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern float func_002A7878(float, float);
extern float func_00283248(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_31E6A0(void *, int, int);
extern char D_L02_00188660[];
extern void func_41F230(void *, int, int, int, int, int, int, int, int, int,
                        int, int, float, float);
extern void func_366BD8(int, int, void *, int);
extern void func_31EA58(void *, float, float);
extern void func_2F1F70(void *, void *, void *);
extern void func_32B068(void *, int, void *, int, float, float, float, float);
extern void func_31E3C0(void *, int, int, int);
extern void func_316220(void *);
extern void func_366830(int);
extern void func_3FC1B0(int, int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float,
                          int, int, int, int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A05A8(void *);
extern int func_002E59F8(int);
extern int func_L02_003FC1B0(void *, int);
extern int func_L02_003FC0D0(void *, int);
extern int func_002B3BA8(void *, u32, float, float, int, int);

typedef int TI128 __attribute__((mode(TI)));


extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern void *func_002A9640(void *, int, int);
extern int func_002B0ED8(void *, void *, int);
extern char D_L02_001BA500[];
extern void func_L02_0040B980(u8 *);
extern void func_002B60B0_1(void *, float, float, float, float);

/* Sets up the actor and refreshes its three effect tracks. In state 0 it points the sub-object's
   record at +0x100, draws two byte values and a turn rate (15 to 40 degrees, negated half of the
   time) for +0x2D8, may set bit 0x8000 of the halfword at +0x34, fills the sub-object's tuning
   floats and arms it (func_L02_0040B980). In every state it then, when the actor is shown (+0x31)
   and within 24.0 of D_L02_001BA500, starts func_002A93B0, rebuilds the tracks at +0x290, +0x2A0
   and +0x2B0 from the matrix func_0029FC20 returns, and, from state 3 on, clears the carried
   record's word at +0x2C filtering by class, tests func_002B0ED8 against 5 and refreshes the
   +0x2E0 handle. Retail passes the actor to func_002B60B0 (a0 is reloaded before the call), which
   the four-float declaration at the top of the file leaves out: the second name carries the
   five-argument prototype. */
/* Common per-frame work for the flamethrower robot: sets its starting values on the first frame, makes it glow when the player is close and checks what hit it. */
void func_L02_0040B0F8(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float matrix[16];
    float turnRate;
    u8 *glowPoint;
    u8 *hitRecord;
    u8 *hitOwner;
    short hitClass;

    if (moby[0x20] == 0) {
        *(u8 **)(vars + 0x18) = vars + 0x100;
        vars[0x48] = FloatToInt(15.0f);
        vars[0x4A] = FloatToInt(12.0f);
        turnRate = RandomFloatRange(15.0f, 40.0f) * 0.01745329424738884f;
        if (RandomIntBelow(2) != 0)
            turnRate = -turnRate;
        *(float *)(vars + 0x2D8) = turnRate;
        if (RandomIntBelow(2) == 1)
            *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x8000;
        vars[0x60] = 8;
        *(float *)(vars + 0x80) = 0.5f;
        *(float *)(vars + 0x84) = 0.5f;
        *(float *)(vars + 0x8C) = 0.4f;
        *(int *)(vars + 0x98) = 4;
        *(float *)(vars + 0x100) = 0.8f;
        *(float *)(vars + 0x104) = 0.5f;
        *(float *)(vars + 0x108) = 0.4f;
        *(float *)(vars + 0x10C) = 0.4f;
        *(float *)(vars + 0x110) = 1.5707965f;
        *(float *)(vars + 0x130) = 0.52359885f;
        *(float *)(vars + 0x12C) = 0.0055555557f;
        func_002B60B0_1(moby, 0.004444444552063942f, 0.13333334028720856f,
                        0.0011635529808700085f, 0.10471977293491364f);
        vars[0x28] = 3;
        KnockOutFlamethrowerRobot(moby);
    }
    if (moby[0x31] != 0) {
        if (fast_vec_dist(moby + 0x10, gCameraPosition_L02) < 24.0f) {
            UpdateMobyGroundCheck(moby);
            moby[0x6F] = 0x16;
        }
    }
    TransformMobyJointToWorld(moby, 1, vars + 0x290);
    glowPoint = vars + 0x2B0;
    TransformMobyJointToWorld(moby, 2, vars + 0x2A0);
    TransformMobyJointPoint(moby, 3, matrix);
    ClearVector128(glowPoint);
    *(float *)(vars + 0x2B0) = 0.25f;
    *(int *)(vars + 0x2B8) = 0;
    transform_vector(glowPoint, glowPoint, matrix);
    FastVecAdd(glowPoint, glowPoint, matrix + 12);
    if (moby[0x31] != 0 && moby[0x20] >= 3) {
        hitRecord = FindOwnedEffectSlot(moby, 0x10000, 1);
        if (hitRecord != 0) {
            hitOwner = *(u8 **)(hitRecord + 0x20);
            if (hitOwner != 0 && moby[0x31] == 0) {
                hitClass = *(short *)(hitOwner + 0xAA);
                if (hitClass == 0xA03 /* moby class 2563 */ || hitClass == 0xB89 /* moby class 2953 */)
                    *(int *)(hitRecord + 0x2C) = 0;
            }
        }
        if (ApplyDamageToObject(moby, vars + 0x50, 0) == 5) {
            *(int *)(vars + 0xE0) = 0;
            *(float *)(vars + 0xE4) = 0.8377582f;
        }
        if (moby[0x20] >= 2 && vars[0x2E] == 2)
            KnockOutFlamethrowerRobot(moby);
        *(s16 *)(vars + 0x2E0) = SelectAimTarget_002B3BA8(moby, *(u32 *)(vars + 0x2DC), 100.0f, 100.0f, 0, 0);
        *(int *)(vars + 0x2D4) = *(int *)(vars + 0x200);
    }
}

/* arms one actor: raises its counter, then two setup calls */
/* Counts up the robot's frame timer and updates its damage and hit effects. */
void func_L02_0040B420(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u16 *)(moby + 0x96) <= 0xFFFE)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
    SetValueAndStartSmoothChange(moby, vars + 0x210, 5, 1, 2.5f);
    SweepCollisionFromObject(moby, moby + 0x10, 0x4000000, 1.3f, 1.0f, 1.0f, 0, 1, 0);
}

/* starts the three effect tracks of the actor */
/* Draws the three glowing trails on the robot once it is awake. */
void func_L02_0040B4B0(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (moby[0x95] != 0) {
        DrawTwoLayerGlowSprite(moby, vars + 0x290, 0.125f, 0x36F6, 0x20000000, 0x20000000);
        DrawTwoLayerGlowSprite(moby, vars + 0x2A0, 0.15f, 0x1050B0, 0x30000000, 0x20000000);
        DrawTwoLayerGlowSprite(moby, vars + 0x2B0, 0.15f, 0x1050B0, 0x10000000, 0x30000000);
    }
}

/* brings the actor into its armed state */
/* Wakes the robot up: restores its health and puts it in its active state. */
void func_L02_0040B868(u8 *moby, int alertDelay) {
    u8 *vars = *(u8 **)(moby + 0x68);
    int one = 1;
    u32 flags;

    *(float *)(vars + 0x20) = (float)*(s16 *)(vars + 0x24);
    *(u16 *)(vars + 0x2E2) = one;
    SetControllerSpeedLimits(moby, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    SetMobyState(moby, 3, 1);
    if (*(u8 *)(moby + 0x43) != 2)
        StartAnimationBlended(moby, 2, 0, 0);
    *(u32 *)(moby + 0x98) = *(u32 *)(*(u32 *)(moby + 0x24) + 0x10);
    *(u8 *)(vars + 0x6A) = 0;
    *(u8 *)(vars + 0x2E) = one;
    *(u8 *)(moby + 0x31) = one;
    flags = *(u16 *)(moby + 0x34);
    *(u8 *)(moby + 0x7F) = 0;
    *(u16 *)(moby + 0x34) = (flags | 0x1000) & 0xFFB8;
    *(u16 *)(vars + 0x2E8) = alertDelay;
    *(u16 *)(vars + 0x88) = 0;
    if (*(s16 *)(vars + 0x50) != 0) {
        *(u16 *)(vars + 0x50) = 0;
        set_moby_color(moby, *(u8 *)(vars + 0x54), *(u8 *)(vars + 0x55), *(u8 *)(vars + 0x56));
        *(u16 *)(vars + 0x52) = one;
    }
}

/* arms the actor: its two effect tracks, then the shared state resets */
/* Knocks the robot out: plays the blast effect and sound, then puts it back in its idle state. */
void func_L02_0040B980(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float burstVelocity[3];

    *(u16 *)(vars + 0x2E2) = 0;
    *(u32 *)(vars + 0x2D4) = 0;
    if (moby[0x31]) {
        SpawnExplosion(moby + 0x10, 0, 5, 5, 0x19, 0x14, 0xA, 1, 0.5f, 0.0f,
                      1, 0, 0, 0);
        PlaySoundFromClassBank(0, 0, moby, 0xC3E);
        RandomDirectionVector(burstVelocity, 0.083333335816860199f, 0.11666667461395264f);
        FastVecAdd(burstVelocity, burstVelocity, vars + 0xD0);
        SpawnDebrisForMaskedParts(moby, 0xFF, burstVelocity, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    StartAnimationBlended(moby, 0, 0, 3);
    func_002A05A8(moby);
    SetMobyState(moby, 1, 0);
    *(u8 *)(moby + 0x31) = 0;
    *(u32 *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xEFFF) | 0x47;
}

/* sweeps the two effect tracks of the actor relative to a head position */
/* func_L02_0040BAB8 is defined in L02_0040BAB8.c. */

/* records the actor's two shot counters, then arms it */
/* Remembers what the robot was doing, then makes it turn around. */
void func_L02_0040BBA0(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    *(u16 *)(vars + 0x2E4) = *(u8 *)(moby + 0x20);
    *(u16 *)(vars + 0x2E6) = *(u8 *)(moby + 0x95);
    func_31E6A0(moby, 6, 3);
}

/* func_L02_0040BE08 is defined in L02_0040BE08-g8.c. */

/* func_L02_0040CAF0 is defined in L02_0040CAF0-g8.c. */

/* steps the actor's state machine, then raises its counter */
/* Updates the blade ball's hit reaction and counts up its frame timer. */
void func_L02_0040CEE8(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    UpdateColorFade(moby, vars + 0x50);
    if (*(s16 *)(vars + 0x50) == 0) {
        if (*(u32 *)(vars + 0x1AC) == 0) {
            set_moby_color(moby, *(u32 *)(vars + 0x1A0), *(u32 *)(vars + 0x1A4),
                          *(u32 *)(vars + 0x1A8));
            *(u32 *)(vars + 0x1AC) = 1;
        }
    } else {
        *(u32 *)(vars + 0x1AC) = 0;
    }
    if (*(u16 *)(moby + 0x96) <= 0xFFFE)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
}

/* Updates the actor's halfword at +0x1B8: below kind 4 it only clears it and the word at +0x184;
   while it is 1, or when the flag at +0x31 is set and func_L02_003FC0D0 agrees, it keeps it at 1
   and calls func_002B3BA8 on the slot at +0x1B0; otherwise it clears it and, for kinds 8 and 0xB,
   picks one of two states by the word at +0x180. */
/* Checks whether the blade ball may chase its target. If not, it goes back to patrolling. */
void func_L02_0040CF68(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (moby[0x20] < 4) {
        *(u16 *)(vars + 0x1B8) = 0;
        *(s32 *)(vars + 0x184) = 0;
    } else {
        if (*(s16 *)(vars + 0x1B8) == 1) {
            *(s16 *)(vars + 0x1B6) = SelectAimTarget_002B3BA8(moby, *(u32 *)(vars + 0x1B0), 100.0f, 100.0f, 0, 0);
            *(s32 *)(vars + 0x184) = *(s32 *)(vars + 0x160);
        } else {
            if (moby[0x31] != 0 && TakeEnemyQuota(*(void **)(moby + 0xB8), *(s16 *)(moby + 0xAA)) != 0) {
                *(u16 *)(vars + 0x1B8) = 1;
                *(s16 *)(vars + 0x1B6) = SelectAimTarget_002B3BA8(moby, *(u32 *)(vars + 0x1B0), 100.0f, 100.0f, 0, 0);
                *(s32 *)(vars + 0x184) = *(s32 *)(vars + 0x160);
            } else {
                *(u16 *)(vars + 0x1B8) = 0;
                if (moby[0x20] == 0xB || moby[0x20] == 8) {
                    if (*(s32 *)(vars + 0x180) != -1)
                        SetMobyState(moby, 7, 3);
                    else
                        SetMobyState(moby, 5, 2);
                }
            }
        }
    }
}

/* resets the actor's aim: three records and the two shared limits */
/* Wakes the blade ball up: restores its health and puts it in its active state. */
void func_L02_0040D080(u8 *moby, int alertDelay) {
    u8 *vars = *(u8 **)(moby + 0x68);

    *(u16 *)(vars + 0x1B8) = 0;
    *(float *)(vars + 0x20) = (float)*(s16 *)(vars + 0x24);
    SetMobyState(moby, 3, 1);
    if (*(u8 *)(moby + 0x43) != 0)
        StartAnimationBlended(moby, 0, 0, 10);
    *(u32 *)(moby + 0x98) = *(u32 *)(*(u32 *)(moby + 0x24) + 0x10);
    *(u8 *)(vars + 0x2E) = 1;
    *(u8 *)(moby + 0x7F) = 0;
    *(u8 *)(moby + 0x31) = 1;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x1000) & 0xFFB8;
    *(float *)(vars + 0x18C) = RandomFloatRange(0.0f, 90.0f) * 0.01745329424738884f;
    *(u16 *)(vars + 0x1BA) = alertDelay;
    *(u16 *)(vars + 0x3C) = 0;
    *(u32 *)(vars + 0x38) = 0;
    if (*(s16 *)(vars + 0x50) != 0) {
        *(u16 *)(vars + 0x50) = 0;
        set_moby_color(moby, *(u32 *)(vars + 0x1A0), *(u32 *)(vars + 0x1A4),
                      *(u32 *)(vars + 0x1A8));
        *(u16 *)(vars + 0x52) = 1;
    }
}

/* Lets go of the slot the actor holds (+0x19C) when that slot's record still names it and is live,
   ends the state at +0x1B8 when it is 1 (func_L02_003FC1B0), starts the effect pair when the actor
   is shown (+0x31), then clears the state and the shared fields as func_L02_0040B980 does. */
/* Blows up the blade ball: stops its sound, plays the blast effect and puts it back in its idle state. */
void func_L02_0040D180(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 slot = *(s32 *)(vars + 0x19C);

    if (slot != -1) {
        u8 *soundRecord = (u8 *)D_L02_00188660 + slot * 0x70;

        if (*(u8 **)(soundRecord + 0x88) == moby && soundRecord[0x74] != 0)
            StopSoundVoice(slot);
    }
    *(s32 *)(vars + 0x19C) = -1;
    if (*(s16 *)(vars + 0x1B8) == 1) {
        *(u16 *)(vars + 0x1B8) = 0;
        IncrementMaktarTypeCounter(*(void **)(moby + 0xB8), *(s16 *)(moby + 0xAA));
    }
    if (moby[0x31] != 0) {
        SpawnExplosion(moby + 0x10, 0, 0xA, 0x1E, 0, 0xA, 0x2D, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        PlaySoundFromClassBank(0, 0, moby, 0xC3E);
    }
    *(u16 *)(vars + 0x1B8) = 0;
    *(s32 *)(vars + 0x184) = 0;
    StartAnimationBlended(moby, 0, 0, 3);
    func_002A05A8(moby);
    SetMobyState(moby, 1, 0);
    moby[0x31] = 0;
    *(u32 *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xEFFF) | 0x47;
}

/* sda in this -G0 unit gives retail's bare-symbol load (`lui $r` / `lbu $r,%lo($r)`, one register);
   a plain declaration splits it into two registers. */
extern u8 D_001A7BCB __attribute__((sda));
extern u8 D_L02_001395B8[];
extern u8 D_L02_001C0700[];
extern char D_00189EA0[];
extern int func_002ACBC8(void *, int);
extern s32 func_00288AA0(u8 *, s32);
extern s32 func_00288BE8(u8 *);
extern int func_002F5D10(void);
extern void func_002AD7B8(int);
extern void func_002AF0A8(int);
extern void func_0029F338(u8 *);

/* Steps the actor by its kind byte (+0x20). Kind 0 hands it to func_0029F338 when it holds no
   record at +0x68 and calls func_002A7750 with 1 otherwise. Kind 1 waits for D_001A7BCB and the
   byte D_L02_001395B8[4] to be clear and func_002ACBC8 to accept the index at +0xC of the
   record, then queues the messages 0x2D, 3 and 0x2E on D_L02_001C0700, sets the byte and calls
   func_002A7750 with 2. Kind 2 runs func_002AD7B8 and func_002AF0A8 with 3 and calls
   func_002A7750 with 3, unless func_002F5D10 answers yes. */
/* Waits for the player to reach a certain point, then plays a short series of messages once. */
void func_L02_0040FB80(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        if (state == 0)
            MarkMobySpawned(moby);
        else
            SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (D_001A7BCB == 0 && D_L02_001395B8[4] == 0 &&
            IsPointInCuboid(gHeroPosition, *(s32 *)(state + 0xC)) != 0 &&
            PushRequestQueue(D_L02_001C0700, 0x2D) != 0) {
            PushRequestQueue(D_L02_001C0700, 3);
            PushRequestQueue(D_L02_001C0700, 0x2E);
            LaunchQueuedRequest(D_L02_001C0700);
            D_L02_001395B8[4] = 1;
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        if (IsEitherModeTwo() == 0) {
            MarkFlagAndAppendToList(3);
            PlayIndexedSound(3);
            SetMobyState(moby, 3, -1);
        }
        break;
    }
}

/* func_L02_00411750 is defined in L02_00411750-g8.c. */

/* func_L02_00411D18 is defined in L02_00411D18.c. */

extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern u16 D_0018CFDC;
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002AA2E8(float *, float, float);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283B98(float, float);
extern void *func_002A9640(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L02_00412808(u8 *);
extern void func_L02_004129D0(u8 *);

/* Steps the actor by its kind byte (+0x20). Kind 0 releases it (func_0029F338) when the table byte
   of its owner (D_0019B2E8, indexed by the byte at +0xB0 and D_001A79F0) has bit 7 set; otherwise
   it takes twice the size at +0x24 of its type record, sets or clears bit 15 of its flags at +0x34
   by func_002A77E0(2), starts state 1 and draws the block's two phases (+4 and +0x14) with
   func_002A7940. Kind 1 keeps its slot record (the index at +0x18 of the block) alive, eases the
   block's float at +0xC to 0 or 1 by whether func_00282E80 puts the actor farther than 64.0 from
   D_L02_001BA500, registers func_L02_004129D0 while it is nonzero, and when the entity found by
   func_002A9640 (a record whose halfword at +0xAA is 0x9C8) is within 5.0 starts state 2 and gives
   the slot up. Kind 2 only runs the common tail, which steps the two phases (func_00283B98), puts
   0.5 * sin(phase) + the base at +8 into the actor's float at +0x18 and runs the counter at +0x10
   down by 1/15, wrapping it into [-1, 1]. The first slot lookup is a separate block-local pointer
   from the one in the state-2 arm (retail keeps them in different registers). */
/* A floating object that bobs up and down and draws a wavy beam to another object. It stops when something of a certain kind touches it. */
void func_L02_004124A0(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *hitRecord;
    u8 *hitOwner;
    s32 slot;
    float value;

    switch (moby[0x20]) {
    case 0:
        if (D_0019B2E8[moby[0xB0] + gCurrentMapIndex * 16] & 0x80) {
            MarkMobySpawned(moby);
            return;
        }
        *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * 2.0f;
        if (RandomIntBelow(2))
            *(u16 *)(moby + 0x34) |= 0x8000;
        else
            *(u16 *)(moby + 0x34) &= 0x7FFF;
        SetMobyState(moby, 1, -1);
        *(float *)(vars + 8) = *(float *)(moby + 0x18);
        *(float *)(vars + 4) = RandomAngle();
        *(float *)(vars + 0x14) = RandomAngle();
        break;
    case 1:
        if (moby[0x31] != 0)
            ThrowFrontSparks(moby);
        {
            u8 *soundRecord = (u8 *)D_L02_00188660 + *(s32 *)(vars + 0x18) * 0x70;

            if (*(u8 **)(soundRecord + 0x88) != moby || soundRecord[0x74] == 0)
                *(s32 *)(vars + 0x18) = PlayMobySound(0, 4, moby);
        }
        value = vec_distance_xy(moby + 0x10, gCameraPosition_L02);
        if (value > 64.0f)
            ApproachValue((float *)(vars + 0xC), 0.0f, 0.016666668f);
        else
            ApproachValue((float *)(vars + 0xC), 1.0f, 0.016666668f);
        if (*(float *)(vars + 0xC) != 0.0f)
            AddDrawCallbackToList1((void *)DrawWavyBeamToTarget, moby);
        hitRecord = FindOwnedEffectSlot(moby, 0x10000, 0);
        if (hitRecord != 0) {
            hitOwner = *(u8 **)(hitRecord + 0x20);
            if (hitOwner != 0 && *(s16 *)(hitOwner + 0xAA) == 0x9C8 /* moby class 2504 */ &&
                fast_vec_dist(moby + 0x10, hitOwner + 0x10) < 5.0f) {
                D_0018CFDC = 0xFFFF;
                SetMobyState(moby, 2, -1);
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
                *(u32 *)(moby + 0x98) = 0;
                slot = *(s32 *)(vars + 0x18);
                if (slot != -1) {
                    u8 *heldRecord = (u8 *)D_L02_00188660 + slot * 0x70;

                    if (*(u8 **)(heldRecord + 0x88) == moby && heldRecord[0x74] != 0)
                        StopSoundVoice(slot);
                }
                *(s32 *)(vars + 0x18) = -1;
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        break;
    }
    *(float *)(vars + 4) = FastAddRotations(*(float *)(vars + 4), 0.05817765f);
    *(float *)(vars + 0x14) = FastAddRotations(*(float *)(vars + 0x14), -0.10471977f);
    *(float *)(moby + 0x18) = FastSinOrCosB(*(float *)(vars + 4)) * 0.5f + *(float *)(vars + 8);
    value = *(float *)(vars + 0x10) + -0.06666667f;
    *(float *)(vars + 0x10) = value;
    if (value > 1.0f)
        *(float *)(vars + 0x10) = value - 1.0f;
    else if (value < -1.0f)
        *(float *)(vars + 0x10) = value + 1.0f;
}

/* The effect's tuning, four resident tables copied onto the stack: the spread and fall speed of
   the sparks, the two sizes, the two colours and the two byte ranges of the kind. */
typedef struct { float f[4]; } SparkRange;
typedef struct { float f[2]; } SparkSizes;
typedef struct { int i[2]; } SparkColours;
typedef struct { u8 b[4]; } SparkKinds;
extern SparkRange D_L02_001B1C10;
extern SparkSizes D_L02_001B1C20;
extern SparkColours D_L02_001B1C28;
extern SparkKinds D_L02_001B1C30;
extern void func_00283098(void *, void *, void *);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void *func_002C3150(void *, void *, int, int, int, int, float);
extern void func_00282C88(void *);

/* Throws two sparks from a point 1.5 in front of the actor (carried by the matrix at +0xC0, then
   moved to the position at +0x10): the first with a velocity drawn between the first two range
   words per frame (no spread in this level's table), the second from a random point within 1.5
   of the first, falling at a speed drawn between the last two. */
/* Throws two small sparks from a point in front of the object. */
void func_L02_00412808(u8 *moby) {
    SparkRange range = D_L02_001B1C10;
    SparkSizes sizes = D_L02_001B1C20;
    SparkColours colours = D_L02_001B1C28;
    SparkKinds kinds = D_L02_001B1C30;
    float velocity[4];
    float front[4];
    float spot[4];

    *(TI128 *)front = 0;
    front[2] = 1.5f;
    matrix_mul_vec3(front, front, moby + 0xC0);
    FastVecAdd(front, front, moby + 0x10);
    RandomDirectionVector(velocity, range.f[0] * 0.016666668f, range.f[1] * 0.016666668f);
    SpawnHeroRelativeParticle(front, velocity, colours.i[0], (u8)RandomIntRange(kinds.b[0], kinds.b[1]),
                  (u8)RandomIntBelow(0xFF), 0, sizes.f[0]);
    ClearVector128(velocity);
    RandomDirectionVector(spot, 0.0f, 1.5f);
    FastVecAdd(spot, spot, front);
    velocity[2] = -(RandomFloatRange(range.f[2], range.f[3]) * 0.016666668f);
    SpawnHeroRelativeParticle(spot, velocity, colours.i[1], (u8)RandomIntRange(kinds.b[2], kinds.b[3]),
                  (u8)RandomIntBelow(0xFF), 0, sizes.f[1]);
}

/* func_L02_004129D0 is defined in L02_004129D0.c. */


/* func_L02_00413730 is defined in L02_00413730-g8.c. */

/* func_L02_004216F0 is matched in L02_004216F0-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -g). */

/* func_L02_00423520 is matched in L02_00423520-g8.c (built with -frac2-zero-ti-por). */

extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int D_L02_001B2050[2] __attribute__((sda));
extern int D_L02_001B2058[2] __attribute__((sda));

/* Throws twenty sparks from a point built from the actor's transform (+0x10) and its vectors at
   +0xC0 and +0xE0. Each one flies along a random mix of the vectors at +0xC0, +0xD0 and +0xE0 at
   a speed drawn between lo and hi, with a random size, two colours blended from the level's two
   colour pairs and a small downward pull. Retail negates its constant at run time (neg.s), so k
   stays a variable. */
/* Throws a burst of twenty sparks from behind the object, each with its own speed, size and colour. */
void func_L02_00423838(u8 *moby, float lo, float hi) {
    float offset[4];
    float origin[4];
    float upSpread[4];
    float sideSpread[4];
    float velocity[4];
    float pull[4];
    int i;
    float scale;
    int partA, partB, partC;
    int colorA, colorB;
    float k = 0.0013888889f;

    FastVecScale(offset, moby + 0xE0, 1.75f);
    FastVecAdd(origin, offset, moby + 0x10);
    FastVecScale(offset, moby + 0xC0, -0.5f);
    FastVecAdd(origin, offset, origin);
    i = 19;
    do {
        vec_scale_to_length(sideSpread, moby + 0xD0, RandomFloatRange(-1.0f, 1.0f));
        vec_scale_to_length(upSpread, moby + 0xE0, RandomFloatRange(-0.15f, 1.0f));
        FastVecAdd(velocity, moby + 0xC0, sideSpread);
        FastVecAdd(velocity, velocity, upSpread);
        vec_scale_to_length(velocity, velocity, RandomFloatRange(lo, hi));
        scale = RandomFloatRange(0.5f, 1.5f);
        partA = FloatToInt(scale * 10.0f);
        partB = FloatToInt(scale * 30.0f);
        partC = FloatToInt(scale * 7.0f);
        velocity[3] = RandomFloatRange(0.2f, 0.6f);
        ClearVector128(pull);
        pull[2] = -k * (float)(partA + partB + partC);
        FastVecAdd(pull, pull, velocity);
        pull[3] = 0.01f;
        colorA = FastTweenColor(D_L02_001B2050[0], D_L02_001B2050[1], RandomFloatRange(0.0f, 1.0f));
        colorB = FastTweenColor(D_L02_001B2058[0], D_L02_001B2058[1], RandomFloatRange(0.0f, 1.0f));
        SpawnTrailParticle_002BAA28(origin, velocity, pull, colorA, colorB, partA, partB, partC, 0x1003C);
    } while (--i >= 0);
}

struct Pair42E2F8 {
    float a;
    float b;
};

extern const struct Pair42E2F8 D_L02_001B23E0;
extern const struct Pair42E2F8 D_L02_001B23E8;
extern const TI128 D_L02_001B23F0[2];
extern s32 D_L02_001AEC78 __attribute__((sda));
extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, unsigned char, s32);
extern void *func_L00_0033E220(void *, void *, int, int, int, int, int, int, float, float);
extern void func_L00_00326110(void *, int, float);
extern void *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_L00_003263D0(void *,void *,int,int,void *,u32,void *,float,float,float,float);
extern void func_L02_0042E680(u8 *, float, float);

/* A small object that waits to be hit. When it is hit it bursts with a flash and sparks, and then goes away. */
void func_L02_0042E2F8(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    struct Pair42E2F8 sizesA = D_L02_001B23E0;
    struct Pair42E2F8 sizesB = D_L02_001B23E8;
    TI128 colors[2];
    float localOffset[4] __attribute__((aligned(16)));
    float flashPoint[4] __attribute__((aligned(16)));
    float flashStep[4] __attribute__((aligned(16)));

    colors[0] = D_L02_001B23F0[0];
    colors[1] = D_L02_001B23F0[1];
    switch (moby[0x20]) {
    case 0:
        *(TI128 *)localOffset = 0;
        localOffset[2] = 4.0f;
        SpawnObjectFollowingEffect(localOffset, moby, 0x28208080, -1, 0, -1, 0, 0x60, 409500.0f, 0.0f);
        SpawnObjectFollowingEffect(localOffset, moby, 0x20208080, -1, 1, -1, 0, 0x60, 367500.0f, 0.75f);
        if (*(s32 *)state != 0)
            gHoveringObjectCount = gHoveringObjectCount - 1;
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) != 0 && *(s32 *)state == 0) {
            gHoveringObjectCount = gHoveringObjectCount - 1;
            SetMobyState(moby, 2, -1);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        ExplodeObjectIntoPieces(moby, colors, &sizesB, &sizesA, 0xB, 0, 1, 5, 0xFFFF, 0xFF, 0);
        SpawnScaledBolts(moby, 1, 4.0f);
        *(TI128 *)localOffset = 0;
        localOffset[1] = -0.10000001f;
        localOffset[2] = 0.050000004f;
        matrix_mul_vec3(localOffset, localOffset, moby + 0xC0);
        CreateCameraMoby(moby, 1, *(s16 *)(moby + 0xAA), 1, moby + 0x10, moby + 0xF0, localOffset, 0xFF, 0.0f, 15.0f);
        *(TI128 *)flashPoint = 0;
        flashPoint[1] = 0.2f;
        flashPoint[2] = 4.3f;
        matrix_mul_vec3(flashPoint, flashPoint, moby + 0xC0);
        FastVecAdd(flashPoint, flashPoint, moby + 0x10);
        *(TI128 *)flashStep = 0;
        flashStep[1] = 0.050000004f;
        flashStep[2] = 0.025000002f;
        matrix_mul_vec3(flashStep, flashStep, moby + 0xC0);
        SpawnTintedEffects(moby,flashPoint,4,1,flashStep,0x50404040,0,0.25f,5.0f,0.5f,1.0f);
        ThrowSparkFan(moby, 0.016666668f, 0.23333335f);
        MarkMobySpawned(moby);
        break;
    }
}

/* func_L02_0042E680 is matched in L02_0042E680.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_0042E988 is defined in L02_0042E988-flags-g8.c. */


/* restarts the shared effect object the level keeps at 0x1BE200 */
/* Resets and re-arms the level's shared effect object so its effect starts again. */
void func_L02_00438B28(void) {
    char *p = D_L02_001BE200;

    DrawJointGlowFacingCamera(*(void **)(p + 0x198), 0);
    DrawJointGlowFacingCamera(*(void **)(p + 0x198), 1);
    DrawJointGlow(*(void **)(p + 0x198), 5);
    DrawJointGlow(*(void **)(p + 0x198), 6);
    DrawJointFourGlow(*(void **)(p + 0x198));
    DrawJointFourGlowFacingCamera(*(void **)(p + 0x198));
}

extern void func_L02_004388A0(u8 *);
extern void func_L02_003FFDB0(u8 *);
extern int D_L02_001A8F00 __attribute__((sda));
extern char *D_L02_001B359C __attribute__((sda));
extern char D_L02_004004D8[];
extern int D_L02_00258800[];
extern void func_00282F20(void *, void *, float);
extern void func_L00_002E6CF0(void *, void *);

typedef struct { u8 pad00[0x78]; int w78; u8 pad7C[0xB8 - 0x7C]; int wB8; } L02_Part;
typedef struct { u8 pad00[0x30]; int mode; u8 pad34[0x198 - 0x34]; L02_Part *part; int w19C; } L02_Level;
typedef struct { u8 pad00[4]; int ent; int armed; int ent2; } L02_CtlState;
typedef struct { u8 pad00[0x6C]; float f6C; } L02_EntVars;
typedef struct {
    u8 pad00[0x10];
    float pos[4];
    u8 pad20[0x34 - 0x20];
    u16 flags;
    u8 pad36[0x43 - 0x36];
    u8 b43;
    u8 pad44[0x48 - 0x44];
    int w48;
    u8 pad4C[0x68 - 0x4C];
    L02_EntVars *vars;
    u8 pad6C[0xD0 - 0x6C];
    float dir[4];
    u8 padE0[0x100 - 0xE0];
} L02_Ent;

/* Controller of the level's moving entity (state byte at +0x20; the words at +0x4 and +0xC of
   its state name two entities of the table D_L02_001B359C). State 0 shows it (byte +0x30 = 0xFF),
   clears the armed word at +0x8 and goes to state 1. State 1 follows D_L02_001A8F00: when it is 2
   the mode of the level block D_L02_001BE200 decides. Mode 0 hands func_L02_003FFDB0 and the
   handler at D_L02_004004D8 to the second entity and func_L02_004388A0 to itself, and once
   (func_002A7470 resets the entity's mode first) pushes the first entity by -2 along its +0xD0
   axis. Mode 1 hands the two handlers to the second entity. Mode 6 does that too, then sets that
   entity's float at +0x6C to 100.0 and its flag 2, writes the colour 0x40FF00EA to three words of
   D_L02_00258800 and to the part at +0x198 of the block, and hands func_L02_00438B28 to itself.
   With D_L02_001A8F00 not 2 it undoes the push (+2 along the axis) and clears the armed word. */
/* Controller that switches a moving object and a nearby effect on or off depending on the current stage of the level. */
void func_L02_00438B90(u8 *moby) {
    L02_CtlState *vars = *(L02_CtlState **)(moby + 0x68);
    L02_Level *level;
    L02_Ent *target;
    float push[4];
    int color;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        moby[0x20] = 1;
        vars->armed = 0;
        break;
    case 1:
        if (D_L02_001A8F00 != 2) {
            if (vars->armed != 0) {
                target = (L02_Ent *)(gMobyPool_L02 + (vars->ent << 8));
                vars->armed = 0;
                if (target->b43 != 0) {
                    StartAnimationBlended(target, 0, 0, 0);
                    target->w48 = 0;
                }
                vec_scale_to_length(push, target->dir, 2.0f);
                FastVecAdd(target->pos, target->pos, push);
            }
        } else {
            level = (L02_Level *)D_L02_001BE200;
            if (level->mode == 0) {
                AddDrawCallbackToList1(DrawRadialQuadEffect, gMobyPool_L02 + (vars->ent2 << 8));
                AddDrawCallbackToList1(D_L02_004004D8, gMobyPool_L02 + (vars->ent2 << 8));
                AddDrawCallbackToList1(DrawNearestPathRecordQuad, moby);
                if (vars->armed == 0) {
                    target = (L02_Ent *)(gMobyPool_L02 + (vars->ent << 8));
                    vars->armed = 1;
                    if (target->b43 != 1) {
                        StartAnimationBlended(target, 1, 7, 0);
                        target->w48 = 0;
                    }
                    vec_scale_to_length(push, target->dir, -2.0f);
                    FastVecAdd(target->pos, target->pos, push);
                }
            } else if (level->mode == 1) {
                AddDrawCallbackToList1(DrawRadialQuadEffect, gMobyPool_L02 + (vars->ent2 << 8));
                AddDrawCallbackToList1(D_L02_004004D8, gMobyPool_L02 + (vars->ent2 << 8));
            } else if (level->mode == 6) {
                color = 0x40FF00EA;
                AddDrawCallbackToList1(DrawRadialQuadEffect, gMobyPool_L02 + (vars->ent2 << 8));
                AddDrawCallbackToList1(D_L02_004004D8, gMobyPool_L02 + (vars->ent2 << 8));
                /* indexed, not `base + (n << 8)`: retail adds the shifted index first */
                ((L02_Ent *)gMobyPool_L02)[vars->ent2].vars->f6C = 100.0f;
                ((L02_Ent *)gMobyPool_L02)[vars->ent2].flags |= 2;
                D_L02_00258800[0x250 / 4] = color;
                D_L02_00258800[0x258 / 4] = color;
                D_L02_00258800[0x254 / 4] = color;
                level->part->wB8 = level->w19C;
                AddDrawCallbackToList1(ResetLevelEffectObject, moby);
                level->part->w78 = color;
            }
        }
        break;
    }
}

/* func_L02_00439CD8 is in L02_0040A4A8-f7-g8.c. */


typedef struct { u8 pad[0x464]; u8 spent[1]; } L02_CellFlags;
extern L02_CellFlags D_L02_0021F4F0;
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
/* sda in this -G0 unit keeps the address of the ring table one `la`, retail's adjacent `lui`/`addiu`
   in the last call's setup (a plain declaration splits it and the scheduler lifts the `lui`). */
extern char D_L02_001A8F20[] __attribute__((sda));
extern void *func_0029EFD0(int);
extern void func_002B37E8(void *, u8 *);
extern int func_002E5CF8(int, int, void *);

/* A breakable placed in the world, numbered by the halfword at +0xB2. Whether it was broken before
   is kept in D_0019B4A8 (one 1 KB table per planet, a 3-bit count in each nibble, the low bit of
   the number picking the nibble) and in a flag byte of its own. State 0 releases it when either
   says so, otherwise it goes to state 1. State 1 asks func_002A9640 what touches it: an actor of
   kind 0x9C8 breaks it (effect object 0xE43 started on it, the burst and the 0x3FFF ring, the
   count raised up to 7, the object released); with nothing there it only sets byte +0xA8 to 0xFF. */
/* A breakable object. A player attack destroys it, and the game remembers how many times it has been broken. */
void func_L02_00445200(u8 *moby) {
    u8 *hitRecord;
    u8 *hitOwner;
    void *breakEffect;
    int id;
    int id2;    /* state 1 reads the number again into a register of its own, as retail does */
    int count;

    switch (moby[0x20]) {
    case 0:
        id = *(u16 *)(moby + 0xB2);
        if (D_L02_0021F4F0.spent[(s16)id] == 0) {
            count = D_0019B4A8[((s16)id >> 1) + (gCurrentMapIndex << 10)];
            if (id & 1)
                count = (count >> 4) & 7;
            else
                count = count & 7;
            if (count == 0) {
                SetMobyState(moby, 1, -1);
                break;
            }
        }
        MarkMobySpawned(moby);
        break;
    case 1:
        hitRecord = FindOwnedEffectSlot(moby, 0x10000, 0);
        if (hitRecord != 0 && (hitOwner = *(u8 **)(hitRecord + 0x20)) != 0 && *(s16 *)(hitOwner + 0xAA) == 0x9C8 /* moby class 2504 */) {
            breakEffect = CreateMoby(0xE43 /* moby class 3651 */);
            if (breakEffect != 0)
                InitChildObjectFromParent(breakEffect, moby);
            SpawnDebrisForMaskedParts(moby, 0x3FFF, D_L02_001A8F20, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
            PlayMobySound(0, 0, moby);
            id2 = *(u16 *)(moby + 0xB2);
            if (id2 & 1) {
                if (((D_0019B4A8[((s16)id2 >> 1) + (gCurrentMapIndex << 10)] >> 4) & 7) != 7)
                    D_0019B4A8[((s16)id2 >> 1) + (gCurrentMapIndex << 10)] += 0x10;
            } else {
                if ((D_0019B4A8[((s16)id2 >> 1) + (gCurrentMapIndex << 10)] & 7) != 7)
                    D_0019B4A8[((s16)id2 >> 1) + (gCurrentMapIndex << 10)] += 1;
            }
            MarkMobySpawned(moby);
        } else {
            moby[0xA8] = 0xFF;
        }
        break;
    }
}

/* rac1-decomp src/core/00118A40.c: func_00119100 */
/* Takes an argument its callers pass (e.g. r1_func_00112468) and ignores
   it; an unused parameter costs no codegen. */
/* Always returns -1, whatever it is given. */
int func_L02_00456258(int unusedArg) {
    return -1;
}

extern void func_00335870(void);

/* Runs one engine routine (func_00335870) and does nothing else. */
void func_L02_00456AC0(void) {
    ResetObjectTypeAndFree();
}
