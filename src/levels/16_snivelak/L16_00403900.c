#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_L16_00410CC0(u8 *, u8 *);

extern void func_2E74B8(void *, void *, void *);

extern float func_2E7590(void *, void *);

extern s32 func_313EA0(s32);

extern void func_30AD48(void *, s32, void *);

extern float func_313F38(float, float);

extern void func_41F1F0(void *, void *, void *, s32, float, float);

extern void func_00282DD8(void *, void *, void *);

extern void func_002ACE78(void *, void *, float);

extern void func_002A7750(void *, s32, s32);

extern void func_0029FCC0(void *, s32, void *);

extern void func_0029FC20(void *, s32, void *);

extern void func_002A0F48(void *);

extern void func_00283678(void *, void *);

extern void func_002A7470(void *, s32, s32, s32);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282E48(void *, void *);

extern float func_00282E80(void *, void *);

extern int func_L07_00321D68(void *, void *);

extern void func_L02_00327350(s32, s32);

extern void func_L01_00323310(s32, s32);
extern u8 *D_L16_001B2C0C[] __attribute__((sda));
extern u8 D_0013963B;

extern void func_L00_003294F0(void *, s32);

extern void func_002DF3F8(void *, void *);

extern void func_0029F338(void *);

extern void func_0029B3E0(s32, s32);

extern void func_L16_00412C58(u8 *, s32, s32);
extern void func_L16_00412BA8(u8 *, s32);

extern void func_L16_004117A8(u8 *);

extern void func_L16_00411F80(u8 *, s32);

extern void func_L16_0041ECF8(void *, float);

extern void func_002AD7B8(s32);

extern s32 func_00282948(void *);

extern void func_L16_004050D8(u8 *);

extern void func_0029F978(u8 *, s32, void *);

extern void func_00283898(void *, s32, float);

extern float func_00283BE0(float, float);

extern void func_002A8C00(void *, u8 *, s32, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern float func_00282C48(float);

extern void func_002A8E20(s32, void *);

/* func_L16_00403900 is in L16_00403900-update-g8.c. */

/* func_L16_00404A60 is in the sibling file L16_00403900-g8.c: its body
   reaches the level's small-data floats through $gp. */

extern u8 *D_L16_001FE7C0[];

/* Steers the object toward the next point of its path (the state's table and cursor at
   0x294/0x2A4); advances the cursor once within half a unit, and returns 1 when the path is done. */
/* Steers the object towards the next point of its path and returns 1 when the path is finished. */
s32 func_L16_00404E40(u8 *moby)
{
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = D_L16_001FE7C0[*(s32 *)(state + 0x294)];

    if (*(s32 *)(state + 0x2A4) >= *(s32 *)path)
        return 1;
    qcopy(point, path + 16 + *(s32 *)(state + 0x2A4) * 16);
    FastVecSub(step, point, moby + 0x10);
    vec_scale_to_length(step, step, 0.20000002f);
    SetControlMotionAndStep(moby, step);
    if (*(s32 *)(state + 0x2AC) != 0) {
        if (fast_vec_dist(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    } else {
        if (vec_distance_xy(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    }
    return 0;
}

/* func_L16_00404F50 is defined in L16_00404F50.c. */

/* func_L16_004050D8 is defined in L16_004050D8-helpers.c. */

/* func_L16_00405488 is in L16_00405488-g8.c. */


/* func_L16_0040C840 is in L16_0040C840-g8.c. */

extern void func_002B60B0(void *, float, float, float, float);
extern s32 func_00283CF0(float);
extern s32 D_L16_001B2648 MACRO_ADDR;
extern float func_00283198(float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_L16_00412F48(u8 *);
extern void func_002A93B0(void *);
extern s32 func_002B0ED8(void *, void *, s32);
extern void func_L16_0040D188(u8 *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern float D_L16_001B9B00[];

/* Object update: on the first frame (+0x20 still zero) sets the state's defaults and
   rates; then, with +0x31 set and the object within 32 units of D_L16_001B9B00, runs
   func_002A93B0 and sets +0x6F to 30; marks the group when func_002B0ED8 reports, and
   runs func_002B3BA8 on the state's two slots, keeping the object's +0x18 across them. */
/* Updates a small enemy part each frame: sets it up on the first frame and wakes the group when hurt. */
void func_L16_0040CD88(u8 *moby)
{
    u8 *state;

    state = *(u8 **)(moby + 0x68);
    if (moby[0x20] == 0) {
        *(s32 *)(state + 0x54) = 0;
        *(s32 *)(state + 0x7C) = 0;
        state[0x150] = 5;
        *(s32 *)(state + 0x188) = 3;
        *(float *)(state + 0x17C) = 0.15f;
        *(float *)(state + 0x50) = 1.868f;
        *(float *)(state + 0x170) = 0.5f;
        *(float *)(state + 0x174) = 0.5f;
        *(float *)(state + 0x58) = 0.5f;
        *(float *)(state + 0x5C) = 0.5f;
        *(float *)(state + 0x60) = 3.141593f;
        *(float *)(state + 0x80) = 0.52359885f;
        SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.00043633237f, 0.034906592f);
        *(s32 *)(state + 0x88) |= 2;
        if (*(s16 *)(state + 0x24) == 0) {
            *(s16 *)(state + 0x24) = 1;
            *(float *)(state + 0x20) = 1.0f;
        }
        SetMobyState(moby, 1, 0);
        if (moby[0x43])
            StartAnimationBlended(moby, 0, 0, 0);
        state[0x48] = FloatToInt(18.0f);
        state[0x4A] = FloatToInt(16.0f);
        *(float *)(state + 0x358) = *(float *)(moby + 0x18);
    }
    if (moby[0x31] && fast_vec_dist(moby + 0x10, D_L16_001B9B00) < 32.0f) {
        UpdateMobyGroundCheck(moby);
        moby[0x6F] = 30;
    }
    if (ApplyDamageToObject(moby, state + 0x140, 0))
        WakeGroupMembers(moby);
    *(s32 *)(state + 0x240) = SelectAimTarget_002B3BA8(moby, *(s32 *)(state + 0x230), *(float *)(state + 0x234), 0.0f, 0, 0);
    *(s32 *)(state + 0x354) = SelectAimTarget_002B3BA8(moby, *(s32 *)(state + 0x350), 0.0f, 0.0f, 0, 0);
    *(float *)(moby + 0x18) = *(float *)(state + 0x358);
}

/* func_L16_0040CF98 is defined in L16_00403900-g8.c. */

extern u16 *D_L16_001FB660[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern s32 D_L16_001B2B38[] __attribute__((sda));

/* Sets a flag word in the state record (+0x68) of every entity of the object's group, stopping
   at the first id with no entity: +0x244 for class 0xF35, +0x24C for class 0xEA3. */
/* Tells the other objects in the same group that one of them has been woken. */
void func_L16_0040D188(u8 *moby)
{
    u16 *groupIds;
    u8 *other;

    if (moby[0x21] == 0xFF)
        return;
    groupIds = D_L16_001FB660[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L16_001B2B38[0] && groupIds != 0 &&
           ((groupIds != 0 && (s16)groupIds[-1] >= 0) || groupIds == D_L16_001FB660[moby[0x21]])) {
        other = D_L16_001B2B1C[0] + ((*groupIds & 0x7FFF) << 8);
        if (other == 0)
            break;
        if (*(s16 *)(other + 0xAA) == 0xF35)
            *(s32 *)(*(u8 **)(other + 0x68) + 0x244) = 1;
        else if (*(s16 *)(other + 0xAA) == 0xEA3)
            *(s32 *)(*(u8 **)(other + 0x68) + 0x24C) = 1;
        groupIds++;
    }
}


/* func_L16_0040D4E8 is compiled from L16_0040D4E8-g16.c. */



/* func_L16_00410618 is in L16_00410618-g8.c. */

/* func_L16_00410B88 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

/* Copies the measured 32-bit field pair of the handle reached at 0x68 onto the second
   pair after the helper has prepared the object's second half. */
/* Copies the position pair of the object once its second half is ready. */
void func_L16_00410C80(u8 *moby)
{
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    FindClosestPathSegmentPoint(moby, moby + 0x10);
    *(s32 *)(vars + 0x220) = *(s32 *)(vars + 0x1F4);
    *(s32 *)(vars + 0x224) = *(s32 *)(vars + 0x1F8);
}

/* func_L16_00410CC0 is defined in L16_00410CC0.c. */

extern s32 func_L16_00417788(void *);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_002A77E0(s32);

/* Picks the row of the level's table that is closest to the handle, then, from a random
   start, the first other usable row, and copies it into the state's slot at 0x200. */
/* Picks a new place on the path near the object, different from the closest one, and moves its marker there. */
void func_L16_00410E40(u8 *moby)
{
    u8 **base;
    u8 *state;
    u8 *table;
    u8 *slot;
    s32 target;
    u8 *p;
    s32 i;
    s32 best;
    s32 found;
    s32 start;
    s32 rem;
    s32 result;
    f32 bestf;
    f32 f;

    base = D_L16_001FE7C0;
    i = 0;
    best = -1;
    state = *(u8 **)(moby + 0x68);
    bestf = 1024.0f;
    table = base[*(s32 *)(state + 0x170)];
    target = GetTurretModelIndex(*(void **)(state + 0x24C));
    p = table + 0x10;
    do {
        f = vec_distance_xy(moby + 0x10, p);
        if (f < bestf) {
            bestf = f;
            best = i;
        }
        i++;
        p += 0x10;
    } while (i < 8);
    found = -1;
    start = RandomIntBelow(8);
    i = 0;
    while (i < 8) {
        /* Never read: the invariant also computed after the loop is what makes gcse insert
           it on the loop's entry path, which keeps loop.c off this loop (phony). */
        slot = state + 0x200;
        rem = (i + start) % 8;
        result = IsPointInCuboid(table + (rem * 16 + 0x10), target);
        if (result == 0) {
            i++;
            continue;
        }
        if (rem != best) {
            found = rem;
            break;
        }
        i++;
    }
    qcopy(state + 0x200, table + (found * 16 + 0x10));
    FindClosestPathSegmentPoint(moby, state + 0x200);
}

/* func_L16_00410FA8 is in L16_00410CC0.c. */

/* func_L16_004110D0 is compiled from L16_004110D0-g8.c. */

/* Moves the object up and down along a sine wave around its target height. */
void func_L16_00411368(u8 *moby)
{
    u8 *moby2;
    u8 *vars;
    float wave;
    float period = 120.0f;

    moby2 = moby;
    vars = *(u8 **)(moby + 0x68);
    wave = 10.0f;
    if (moby2[0x20] == 0xD || moby2[0x20] == 0xF || moby2[0x20] == 0xE || moby2[0x20] == 0x11)
        wave = 25.0f;
    wave = wave + FastSinOrCosB((float)(D_L16_001B2648 % FloatToInt(120.0f)) / period * 6.2831855f - 3.1415927f);
    StepValueTowardTarget(moby2 + 0x18, vars + 0x268, *(float *)(vars + 0x264) + wave,
                  0.0083333338f, 0.0027777778f, 0.16666667f);
    EmitFireBurstFromAttachPoints(moby2);
}

/* func_L16_00411480 is defined in L16_00403900-g8.c. */

/* func_L16_00411600 is in L16_00411600-qcopy.c. */

/* Routes one transition request to the handle itself or to its first child, depending on
   the state word and on which of the two animation slots is current. */
/* Plays an animation on the object, or on its child when the object is in the other mode. */
void func_L16_004116C8(u8 *moby, s32 animation, s32 duration, float frame)
{
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (*(s32 *)(vars + 0x26C) == 0) {
        if (*(u8 *)(moby + 0x43) != animation)
            StartAnimationBlended(moby, animation, (s32)frame, duration);
    } else {
        if (*(u8 *)(moby + 0x43) != 0x16)
            StartAnimationBlended(moby, 0x16, (s32)frame, duration);
        if (animation == 0xA)
            animation = 0x16;
    }
    if (animation < 0x11)
        StartAnimationBlended(*(u8 **)(vars + 0x1F0), animation, (s32)frame, duration);
    else
        StartAnimationBlended(*(u8 **)(vars + 0x1F0), 0, (s32)frame, duration);
}

/* func_L16_004117A8 is defined in L16_004117A8.c. */

/* func_L16_00411900 is defined in L16_00411900-g8.c. */

/* func_L16_00411B40 is defined in L16_00411B40-g16.c. */

/* func_L16_00411D00 is defined in L16_00411D00-g8.c. */

/* func_L16_00411F80 is defined in L16_00411F80.c. */

/* func_L16_00412560 is defined in L16_00412560-g32.c. */

/* func_L16_00412AF0 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

/* The voice-load state the level shares with the engine (see L03VoiceState in L03_003F09C0.c). */
typedef struct {
    u8 pad[0x24];
    s32 key;
    s32 selection;
    u8 pad2[0x3C];
    s32 active;
} L16VoiceState;

extern L16VoiceState D_001A63A8;
extern int D_L16_001B1888[];
extern void func_002A6170(void *);

/* Asks the engine to load voice line idx, from the first table below 20 and the second from 20 up,
   unless a load is active or pending or that line is already the current one. The arms are written
   out: cross-jump merges their stores after allocation, which leaves them before the shared tail. */
/* Asks to play voice line number idx unless one is already playing or loading. */
void func_L16_00412BA8(u8 *moby, s32 idx)
{
    L16VoiceState *voice = &gMusicState;
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (voice->active == 0) {
        if (voice->key == -1 && idx != *(s32 *)(vars + 0x354)) {
            if (idx < 20) {
                s32 lineKey = *(s32 *)(vars + (idx << 2) + 0x280);
                voice->selection = 0;
                voice->key = (lineKey & 0x3FFF) + 0x7D0;
            } else {
                s32 lineKey = *(s32 *)(vars + ((idx - 20) << 2) + 0x2D0);
                voice->selection = 0;
                voice->key = (lineKey & 0x3FFF) + 0x7D0;
            }
            func_002A6170(D_L16_001B1888);
            *(u8 *)(vars + idx + 0x310) = 1;
            *(s32 *)(vars + 0x350) = 0x384;
            *(s32 *)(vars + 0x354) = idx;
        }
    }
}

/* Walks a rotating candidate index over the measured byte table until a free slot
   is found, arms it, and clears the whole window when none is. */
/* Picks a voice line in a range that was not played yet, and resets the range when all were played. */
void func_L16_00412C58(u8 *moby, s32 start, s32 end)
{
    u8 *vars;
    s32 span;
    s32 i;
    s32 pick;

    vars = *(u8 **)(moby + 0x68);
    if (end < start)
        return;
    span = end - start + 1;
    pick = func_313EA0(span);
    for (i = 0; i < span; i++) {
        u8 *played = vars + 0x310;

        if (played[start + pick] == 0) {
            RequestVoiceLine(moby, start + pick);
            return;
        }
        pick = (pick + 1) % span;
    }
    for (i = 0; i < span; i++)
        vars[0x310 + start + i] = 0;
    RequestVoiceLine(moby, start + pick);
}

/* Finishes the pending entry (its two saved vectors are copied back), then resets the
   level's handles. */
/* Finishes the cutscene state of the boss, restores positions and goes to state 2. */
void func_L16_00412D48(u8 *moby)
{
    u8 *vars;
    s32 slot;
    u8 *table;

    vars = *(u8 **)(moby + 0x68);
    if (*(s32 *)(vars + 0x1BC) != 0) {
        s32 h = *(s32 *)(vars + 0x1B0);
        s32 m = *(s32 *)(vars + 0x1B4);

        *(s32 *)(vars + 0x1BC) = 0;
        StartRecordEffectByIndex(h, m);
        slot = *(s32 *)(vars + 0x1B8) << 7;
        table = D_L16_001B2C0C[0];
        qcopy(moby + 0x10, table + 0x30 + slot);
        qcopy(moby + 0xF0, table + 0x70 + slot);
        QueueKeyedRequest(*(s32 *)(vars + 0x1A4), -1);
    } else {
        QueueKeyedRequest(*(s32 *)(vars + 0x1A4), *(s32 *)(vars + 0x1AC));
    }
    D_0013963B = 1;
    CleanUpArenaMobys(moby);
    SetMobyAndGroupsEnabled(moby, 1);
    SetObjectFlagBit(D_L16_001B2B1C[0] + (*(s32 *)(vars + 0x190) << 8), 1);
    CaptureCheckpointState(D_L16_001B2C0C[0] + (*(s32 *)(vars + 0x198) << 7) + 0x30,
                  D_L16_001B2C0C[0] + (*(s32 *)(vars + 0x198) << 7) + 0x70);
    PlayUnplayedVoiceLine(moby, 0, 2);
    MemcardSave(0, -1);
    SetMobyState(moby, 2, 1);
}

/* Level teardown: releases the handles the level state holds. */
extern char D_00189EA0[];

/* Cleans up the boss and its parts when the fight ends, then frees the object. */
void func_L16_00412E70(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    D_0013963B = 2;
    SpinGroupEntities(D_L16_001B2B1C[0] + (*(s32 *)(vars + 0x190) << 8), 0.0f);
    StartRecordEffectByIndex(*(s32 *)(vars + 0x188), *(s32 *)(vars + 0x18C));
    CaptureCheckpointState(gHeroPosition, gHeroPosition + 0x10);
    MarkFlagAndAppendToList(0x11);
    if (*(s32 *)(vars + 0x1F0) != 0)
        MarkMobySpawned((void *)*(s32 *)(vars + 0x1F0));
    if (*(s32 *)(vars + 0x238) != 0)
        MarkMobySpawned((void *)*(s32 *)(vars + 0x238));
    if (*(s32 *)(vars + 0x23C) != 0)
        MarkMobySpawned((void *)*(s32 *)(vars + 0x23C));
    QueueKeyedRequest(*(s32 *)(vars + 0x1A0), -1);
    MemcardSave(0, -1);
    MarkMobySpawned(moby);
}


/* func_L16_00412F48 is in L16_00412F48-g8.c. */

/* func_L16_004130B0 is in L16_004130B0-qcopy.c. */

extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern s32 func_002A9640(void *, s32, s32);
extern s32 func_00277258(void *, s32, void *, float);
extern void func_0032DA58(void *, void *, void *, float);
extern void func_002A8C28(void *, void *, s32, s32, s32, s32, float, float, float);
extern void func_002AB6D8(void *, void *);
extern void func_002A7A00(void *, float, float);
extern float func_002A7878(float, float);
extern void func_00273730(void *, s32, s32, s32, void *, void *, void *, s32, float, float);

/* State 0: moves by the state's velocity and frees itself when the state's timer (+0x30)
   runs out, unless +0x31 is set. State 2: moves, lowers the velocity's third component by
   +0x34, turns its basis by the state's rotation and ages; on a collision record, or past
   90 frames when func_00277258 reports, it runs its impact effects toward D_L16_001B9B00,
   spawns six particles and frees itself. */
/* Moves a flying debris piece and makes it explode with particles when it hits something. */
void func_L16_004133B0(u8 *moby)
{
    float spin[12];
    float toward[4];
    float velocity[4];
    u8 *state;
    u8 *basis;
    u8 *angles;
    s32 hit;
    u32 old;
    u32 age;
    s32 i;
    s32 kind;
    float speed;
    float life;

    state = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        if (FastFloatHelperD(state + 0x30) && !moby[0x31])
            MarkMobySpawned(moby);
        break;
    case 2:
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        basis = moby + 0xC0;
        *(float *)(state + 8) -= *(float *)(state + 0x34);
        quaternion_to_rotation_basis(state + 0x20, spin);
        multiply_matrix3x3(basis, spin, basis);
        hit = 0;
        if (FindOwnedEffectSlot(moby, 0x10000, 0))
            hit = 1;
        age = *(u16 *)(moby + 0x96);
        old = age++;
        *(u16 *)(moby + 0x96) = age;
        if (old > 90 && TestPointAgainstCollision(moby + 0x10, 0, moby, 1.0f))
            hit = 1;
        if (hit) {
            FastVecSub(toward, D_L16_001B9B00, moby + 0x10);
            angles = moby + 0xF0;
            vec_scale_to_length(toward, toward, 1.0f);
            SpawnBlastEffectMoby(moby, moby + 0x10, toward, 0.0f);
            SweepCollisionFromObject(moby, moby + 0x10, 0x10001, 0, 1, 0, 4.0f, 20.0f, 2.0f);
            GetEulerAnglesFromMatrix(basis, angles);
            for (i = 0; i < 6; i++) {
                RandomDirectionVector(velocity, 0.0f, 0.33333334f);
                FastVecAdd(velocity, velocity, state);
                kind = *(s16 *)(moby + 0xAA);
                speed = RandomFloatRange(180.0f, 720.0f);
                life = RandomFloatRange(5.0f, 15.0f);
                CreateCameraMoby(moby, 2, kind, i, moby + 0x10, moby + 0xF0, velocity, 255, speed, life);
            }
            MarkMobySpawned(moby);
        }
        break;
    }
}

/* Prepares a 16-byte record from the handle and reports one when the queried value
   does not exceed zero. */
/* Returns 1 when the object is behind the surface in front of it. */
s32 func_L16_00413638(u8 *moby)
{
    s32 buf[4];
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    func_2E74B8(buf, vars + 0x10, moby + 0x10);
    if (func_2E7590(vars, buf) <= 0.0f)
        return 1;
    return 0;
}

/* func_L16_00413700 is in L16_00413700-qcopy.c. */

/* func_L16_00413D10 is in L16_00413D10-g8.c. */
