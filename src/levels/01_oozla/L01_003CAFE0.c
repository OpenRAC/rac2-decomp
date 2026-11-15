#include "include_asm.h"
#include "common.h"


/* Quadword copies and clears, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282948(void *a0);

extern void func_00282978(void *a0);

extern void func_0029F338(void *a0);

extern u32 D_L01_001BF918[];

extern u32 g_pHeroMoby[];

extern s32 func_3120A8(void *a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5,
                      u32 a6, f32 f12, f32 f13);

extern s32 func_355780(u32 a0, u32 a1, void *a2);

extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern u8 *D_L01_001B255C_sda[] __attribute__((sda));
extern u8 *D_L01_001FE180[];

extern u8 *D_L01_001B255C __attribute__((sda));

extern u32 D_L01_001FFE80[];

/* func_L01_003CEDA0: scalar `sda` declarations under -G0 give retail's absolute accesses and
   its $gp loads in delay slots. */
extern u8 D_001A7B1C __attribute__((sda));
extern u8 D_0018C958[];
extern u8 D_L01_001BF6C0[];
extern u8 *D_L01_001B264C __attribute__((sda));
extern int D_L01_001A8F40 __attribute__((sda));
extern int D_L01_001A900C __attribute__((sda));
extern float D_L01_001B1FA0 __attribute__((sda));
extern u32 D_001A7390 __attribute__((sda));
extern float func_00283B98(float, float);
extern int func_002ACBC8(void *, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern void func_L01_003CEB00(void *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_00288308(int);
extern void func_002AD860(int);
extern void func_002B0A18(int, int);
extern void func_0029B3E0(int, int);
extern void func_L00_00429020(int);
extern void func_00288E18(int, int);

/* func_L01_003CAFE0 is in L01_003CAFE0-ctx-g16.c. */


/* func_L01_003CB668 is in L01_003CB668-g16.c. */

/* func_L01_003CBCD8 is in L01_003CBCD8-qcopy.c. */

/* Frees the object at 0xD8 of the object at 0x68 and clears its 0xDC flag. */
/* Gives back the shared attack slot this monster was holding, if any. */
void func_L01_003CBFA8(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (moby[0x21] != 0xFF && *(u8 *)(vars + 0xDC) != 0)
        FastFloatHelperD(*(void **)(vars + 0xD8));
    *(u8 *)(vars + 0xDC) = 0;
}

/* func_L01_003CBFF0 is defined in a sibling -g8.c unit. */

/* Releases the sub-objects at 0xC0, 0xBC, 0xC4 and 0x26, first bumping the counter at 0x96. */
/* Cleans up the swamp monster arm timers when it is removed. */
void func_L01_003CC210(u8 *moby)
{
    u8 *mobyAlias = moby;
    u8 *vars = *(u8 **)(mobyAlias + 0x68);

    if (*(s32 *)(vars + 0x74) == 0)
        FastFloatHelperD(vars + 0xC0);
    if (*(u16 *)(mobyAlias + 0x96) < 0xFFFE)
        *(u16 *)(mobyAlias + 0x96) = *(u16 *)(mobyAlias + 0x96) + 1;
    FastFloatHelperD(vars + 0xBC);
    FastFloatHelperD(vars + 0xC4);
    FastDecTimer(vars + 0x26);
}

/* func_L01_003CC280 is defined in L01_003CC280-g8.c. */

/* Registers the object with the 0x04000009 descriptor and arms its 0x00 flag once. */
/* Tests a swing between two points against the hero and plays a hit sound the first time. */
void func_L01_003CC898(u8 *moby, u32 segmentStart, u32 segmentEnd, u8 width, u8 *soundPlayed)
{
    u8 *attacker = moby;
    u8 *soundFlag = soundPlayed;

    if (func_3120A8(attacker, segmentStart, segmentEnd, 0x04000009, 0, 1, 1, (f32)width, 1.0f) == 0)
        return;
    if (D_L01_001BF918[0] != g_pHeroMoby[0])
        return;
    if (*soundFlag == 0)
        return;
    func_355780(3, 0, attacker);
    *soundFlag = 1;
}


extern void func_L01_00323310(s32 a0, s32 a1);
extern void func_002A7470(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_L01_00337A60(void *a0, void *a1, void *a2, s32 a3);

/* While the owner's kind (+0x95) is 6, serves the two entities whose ids lie at +0xA0 and +0xA4. */
/* Shares health between this body and its two linked parts. When it runs out, both play their death moves. */
s32 func_L01_003CDB40(u8 *moby)
{
    u8 *vars;
    u8 *part;
    u8 *partVars;
    s32 *partIds;
    s32 i;
    u8 *pathTable;
    s32 sharedValue;

    vars = *(u8 **)(moby + 0x68);
    if (moby[0x95] == 6)
        return 0;
    partIds = (s32 *)(vars + 0xA0);
    for (i = 0; i < 2; i++) {
        if (partIds[i] == -1)
            continue;
        part = D_L01_001B255C_sda[0] + (partIds[i] << 8);
        partVars = *(u8 **)(part + 0x68);
        if (moby[0x95] == 4 && *(s32 *)(partVars + 0x74) == 1)
            QueueKeyedRequest(*(s32 *)(vars + 0xD0), *(s32 *)(vars + 0xD8));
        if (part[0x95] == 8)
            continue;
        sharedValue = *(s32 *)(partVars + 0xC0);
        if (sharedValue < *(s32 *)(vars + 0xBC))
            sharedValue = *(s32 *)(vars + 0xBC);
        *(s32 *)(vars + 0xBC) = sharedValue;
        *(s32 *)(partVars + 0xC0) = sharedValue;
        if (*(f32 *)(vars + 0x20) <= 0.0f) {
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 10);
            *(f32 *)(vars + 0x20) = 0.0f;
            *(f32 *)(partVars + 0x20) = 0.0f;
            if (part[0x43] != 4 && part[0x42] != 4)
                StartAnimationBlended(part, 4, 0, 10);
            part[0x95] = 8;
            SetMobyState(moby, 0, 6);
        }
        qcopy(vars + 0x80, partVars + 0x60);
        pathTable = D_L01_001FE180[*(s32 *)(vars + 0xA8)];
        ClosestPointOnPolygonEdge(vars + 0x70, partVars + 0x60, pathTable + 0x10, *(s32 *)pathTable);
    }
    return *(s32 *)(vars + 0xBC);
}

/* Sends the timer string and steps the 0x2E/0x28/0x2A state fields of the owner. */
extern s32 func_00283CF0(f32 a0);
extern void func_L01_003377C8(void *a0);
extern void func_002A7398(void *a0, s32 a1, s32 a2);

/* Seeds the state block (random timers, the saved position, its mode bytes), lets the table
   entry it names inherit the object's float at +0x18, then starts either the flagged (0xAC)
   or the plain animation. */
/* Sets up a body part when it appears, picks random timers and starts its first animation. */
void func_L01_003CDD00(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    *(u8 *)(vars + 0x48) = FloatToInt(30.0f);
    *(u8 *)(vars + 0x4A) = FloatToInt(24.0f);
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24);
    qcopy(vars + 0x60, moby + 0x10);
    *(u8 *)(vars + 0x28) = 3;
    *(u8 *)(vars + 0x2E) = 3;
    *(f32 *)(vars + 0x30) = 3.0f;
    *(u32 *)(vars + 0xB4) = 0;
    *(s32 *)(vars + 0xC0) = -1;
    *(u8 *)(vars + 0x2A) = 8;
    if (*(s32 *)(vars + 0xCC) != -1) {
        u8 *linkedPart = (u8 *)((*(s32 *)(vars + 0xCC) << 8) + (s32)D_L01_001B255C_sda[0]);

        if (*(u8 *)(linkedPart + 0x20) != 0xFE) {
            if (*(u8 *)(linkedPart + 0x20) != 0xFD)
                *(f32 *)(linkedPart + 0x18) = *(f32 *)(moby + 0x18);
        }
    }
    if (*(s32 *)(vars + 0xA8) != -1)
        ComputePathSegmentLengths_L01(D_L01_001FE180[*(s32 *)(vars + 0xA8)]);
    if (*(u32 *)(vars + 0xAC) != 0) {
        *(u16 *)(moby + 0x34) &= 0xEFFF;
        StartAnimationImmediate(moby, 0, 0);
        *(u32 *)(moby + 0x48) = 0;
        SetMobyState(moby, 0, 4);
        return;
    }
    *(u16 *)(moby + 0x34) |= 0x1000;
    StartAnimationImmediate(moby, 1, 0);
    SetMobyState(moby, 0, 1);
}

/* Releases the three sub-objects at 0xBC, 0xB4 and 0x26, first bumping the counter at 0x96. */
/* Cleans up the part timers when it is removed. */
void func_L01_003CDE58(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u16 *)(moby + 0x96) < 0xFFFE)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
    FastFloatHelperD(vars + 0xBC);
    FastFloatHelperD(vars + 0xB4);
    FastDecTimer(vars + 0x26);
}

/* The group count and the entity base, read as bare symbols (`sda` arrays of unknown size: the
   assembler makes the loads $gp ones in a branch delay slot); the base takes a second name
   because D_L01_001B255C is declared above with its pointer type. */
extern s32 D_L01_001B2578[] __attribute__((sda));
extern u16 *D_L01_001FB020[];
extern u8 D_00189EA0[];

extern void *func_002A9640(void *, s32, s32);
extern f32 func_002A96A0(void *, void *);
extern u8 *func_002AB1F0(u8 *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00283CE0(s32);
extern void func_L01_002F14E8(s32, s32, f32);

/* While the owner's kind (+0x95) is 5 or 6 and its timer (+0x20) is positive, finds the entity
   func_002A9640 names (only when the state's halfword at +0x26 is below 1) and its distance
   f20 from func_002A96A0; when that is positive, walks the id list of the owner's group and
   sets the effect record each entity hands out (func_002AB1F0: class-dependent 60 or 0 at +6,
   the distance taken off its float at +0), otherwise takes the distance off the timer. Then
   it runs the timer out (releasing the entity at +0xCC and switching to state 5), or, below it,
   enters state 4 for a distance of 1.0 or more and scales the vector at +0x90. At the end the
   shared update runs and the timer ratio is handed to func_L01_002F14E8. The function keeps
   the second `p != 0` guard of the walk; func_L01_003CDB40 returns a word, and the retail
   copy of the 0.2 limit holds one ulp more than 0.2f. */
/* Handles damage to a body part, then switches it to a hit or death animation and pushes it away. */
void func_L01_003CDEA8(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *attacker;
    u8 *hitSource;
    u8 *groupMember;
    u8 *hitRecord;
    u16 *memberList;
    f32 damage;
    f32 pushStrength;
    s32 hitDuration;
    u16 classId;

    if (moby[0x95] >= 5 && moby[0x95] <= 6 && 0.0f < *(f32 *)(state + 0x20)) {
        attacker = FindOwnedEffectSlot(moby, 0x10000, 0);
        hitSource = attacker;
        if (*(short *)(state + 0x26) >= 1)
            hitSource = 0;
        damage = UpdateAimTargetStrength(moby, hitSource);
        if (hitSource != 0 && 0.0f < damage) {
            if (moby[0x21] != 0xFF && *(s32 *)(state + 0xA0) != -1) {
                classId = *(u16 *)(*(u8 **)(hitSource + 0x20) + 0xAA);
                hitDuration = (classId == 0xCE4 /* moby class 3300 */ || classId == 0xCE5 /* moby class 3301 */) ? 60 : 0;
                for (memberList = D_L01_001FB020[moby[0x21]];
                     moby[0x21] != 0xFF && moby[0x21] <= D_L01_001B2578[0] && memberList != 0 &&
                     ((memberList != 0 && (short)memberList[-1] >= 0) || memberList == D_L01_001FB020[moby[0x21]]);
                     memberList++) {
                    groupMember = D_L01_001B255C_sda[0] + ((*memberList & 0x7FFF) << 8);
                    if (groupMember == 0)
                        break;
                    hitRecord = GetMobyPrivateValue0(groupMember);
                    if (hitRecord != 0) {
                        *(u16 *)(hitRecord + 6) = hitDuration;
                        *(f32 *)hitRecord = *(f32 *)hitRecord - damage;
                        hitRecord[0x17] = state[0x37];
                        *(s32 *)(hitRecord + 0x18) = *(s32 *)(state + 0x38);
                        *(u16 *)(hitRecord + 0x1C) = *(u16 *)(state + 0x3C);
                    }
                    groupMember[0xA8] = 0xFF;
                }
            } else {
                *(f32 *)(state + 0x20) = *(f32 *)(state + 0x20) - damage;
            }
        }
        moby[0xA8] = 0xFF;
        if (*(f32 *)(state + 0x20) < 0.0f) {
            if (*(s32 *)(state + 0xCC) != -1)
                MarkMobySpawned(D_L01_001B255C_sda[0] + (*(s32 *)(state + 0xCC) << 8));
            *(s32 *)(state + 0xCC) = -1;
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 10);
            *(f32 *)(state + 0x20) = 0.0f;
            SetMobyState(moby, 0, 6);
            *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) & 0xEFFF;
        } else {
            if (1.0f <= damage) {
                *(s32 *)(state + 0xBC) = 0xF0;
                if (moby[0x43] != 4)
                    StartAnimationBlended(moby, 4, 0, 3);
                *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) & 0xEFFF;
                SetMobyState(moby, 0, 6);
            }
            if (0.1f < damage) {
                FastVecSub(state + 0x90, moby + 0x10, gHeroPosition);
                pushStrength = (damage + damage + 3.0f) * 0.016666668f;
                if (0.20000002f < pushStrength)
                    pushStrength = 0.20000002f;
                vec_scale_to_length(state + 0x90, state + 0x90, pushStrength);
                *(s32 *)(state + 0x98) = 0;
            }
        }
    } else {
        moby[0xA8] = 0xFF;
    }
    SyncLinkedPartsHealth(moby);
    if (moby[0x95] >= 5 && moby[0x95] <= 6)
        StartHudOverlay(1, 0, *(f32 *)(state + 0x20) / IntToFloat(*(short *)(state + 0x24)));
}


/* func_L01_003CE868 is defined in L01_003CE868-g8.c. */

/* Three states on the byte at +0x20: 0 raises the moby by 0.75 and sets its scale to 1.5 times
   the class value (or frees it while D_001A7B1C is set); 1 turns it (+0xF8) and, once the point
   D_00189EA0 lies in the cuboid its vars name at +4, queues movie 0x26 (QueueMovie) and enters
   state 2; 2 bumps the counter at +0x96, waits for func_002F5D10, then runs the level calls for
   the entry its vars name at +8, flags the object named at +0xC once, steps the subtitle history
   timer of entry 16 (TryQueueSubtitleSelection 0x9B9 after 180 frames) and frees the moby.
   The timer's three loads keep their retail order only when the frame counter is read last. */
/* Cutscene trigger. When the hero walks into its zone it plays a movie, runs the level event and removes itself. */
void func_L01_003CEDA0(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68), *anchor;
    int screenMode;

    switch (moby[0x20]) {
    case 0:
        if (D_001A7B1C) {
            MarkMobySpawned(moby);
            break;
        }
        *(float *)(moby + 0x18) += 0.75f;
        *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * 1.5f;
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), 0.078539826f);
        if (IsPointInCuboid(gHeroPosition, *(int *)(vars + 4))) {
            vars = D_L01_001BF6C0;
            if (PushRequestQueue(vars, 0x26)) {
                LaunchQueuedRequest(vars);
                SetMobyState(moby, 2, -1);
            }
        }
        if (moby[0x31])
            SpawnSparklesAndGlowRings(moby);
        break;
    case 2:
        screenMode = D_L01_001A8F40;
        (*(u16 *)(moby + 0x96))++;
        if (screenMode == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (IsEitherModeTwo())
            break;
        anchor = D_L01_001B264C + (*(int *)(vars + 8) << 7);
        D_L01_001A900C = 0;
        D_L01_001B1FA0 = 0;
        ResetHeroPositionAndDirection(anchor + 0x30, anchor + 0x70, 0x6F, 1);
        UnlockHelpEntry(0x24);
        HandleRequestSlotState(0x24);
        SetEntryValueByIndex(0x1225, -1);
        MemcardSave(0, -1);
        if (*(int *)(vars + 12) != -1) {
            vars = *(u8 **)(gMobyTable_L01 + (*(int *)(vars + 12) << 8) + 0x68);
            if (!*(int *)(vars + 0x3C)) {
                LockCameraEntry(*(int *)(vars + 0x38));
                *(int *)(vars + 0x3C) = 1;
            }
            vars = gSubtitleHistory;
            if (!*(u16 *)(vars + 0xC0)) {
                u16 elapsed = *(u16 *)(vars + 0xC2);
                u32 start = *(u32 *)(vars + 0xC4);
                u32 now = D_001A7390;

                if (start + elapsed >= now - 2) {
                    *(u16 *)(vars + 0xC2) = ++elapsed;
                    if (elapsed >= 180) {
                        RequestSubtitleVoiceLine(0x9B9, 0x10);
                        *(u16 *)(vars + 0xC2) = 0;
                    }
                } else {
                    if (start < now)
                        *(u32 *)(vars + 0xC4) = now;
                    *(u16 *)(vars + 0xC2) = 0;
                }
            }
        }
        MarkMobySpawned(moby);
        break;
    }
}

/* func_L01_003D1A48 lives in L01_003D1A48-g8.c. */

/* func_L01_003D1F40 is defined in L01_003D1F40-g8.c. */

/* func_L01_003D25B8 is defined in a sibling -g8.c unit. */

/* func_L01_003D26C0 is in L01_003D26C0-g8.c. */

/* func_L01_003D2890 is in L01_003CAFE0-launch.c. */

/* func_L01_003D2E50 is in L01_003D2E50.c. */

/* func_L01_003D68C0 is defined in a sibling -g8.c unit. */

/* func_L01_003D8358 lives in L01_003D8358-g8.c. */

/* func_L01_003D8830 is in L01_003CAFE0-burst.c. */

/* func_L01_003D8AD0 is defined in a sibling -g8.c unit. */

/* func_L01_003D8C00 is defined in L01_003D8C00-qcopy-barrier.c. */

/* func_L01_003D8E80 is defined in L01_003CAFE0-g8.c. */


/* func_L01_003D98E0 is defined in L01_003D98E0-g8.c. */

/* func_L01_003DA300 is in L01_003DA300-g8.c. */

/* func_L01_003DA3F0 is defined in L01_003DA3F0-g8.c. */
