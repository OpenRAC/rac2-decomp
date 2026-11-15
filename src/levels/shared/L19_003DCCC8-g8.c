#include "common.h"

extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 D_L19_001B09C4 __attribute__((sda));
extern s32 D_L19_001B0A60 __attribute__((sda));
extern u8 D_L19_001B0A70[] SDATA(D_L19_001B0A70);
extern u8 D_L19_001B0A80[] SDATA(D_L19_001B0A80);
extern s32 D_L19_001B2508[] __attribute__((sda));
extern s32 D_L19_001B2724[] __attribute__((sda));
extern s32 D_L19_001A8F00[] __attribute__((sda));
extern s32 D_L19_001A903C[] __attribute__((sda));
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern u8 D_001395B8[];
extern u8 D_00189EA0[];
extern u8 D_L19_001BFC40[];
extern s32 D_0018C0B4[];
extern u8 D_001A7AFD[] __attribute__((sda));
extern u8 D_001A7A78[] __attribute__((sda));

extern int func_002A77E0(int);
extern void func_L00_0043DA18(void *, void *);
extern void func_L18_003FA7C0(void *);
extern void func_L00_003672F8(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern int func_002ACBC8(void *, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void ref_L19_003DD9D8_01(int);
extern void func_00288308(int);
extern void func_002AD860(int);
extern void func_002B0A18(int, int);
extern void func_002DF3F8(void *, void *);
extern void func_0029B3E0(int, int);
extern int func_00282978(s16 *);
extern int func_L18_003FA920(void *, int);
extern void func_L18_003F9FB0(void *);
extern void func_L01_00323310(int, int);
extern void func_L18_003FA180(void *, int);
extern void func_L18_003F9DA0(void *, int);
extern void func_L18_003F9EF0(void *);
extern void func_L18_003F9E50(void *);
extern void func_L18_003FAE50(void *);
extern void ref_L19_003DD9D8_00(void *, void *);
extern void func_L18_003FE010(void *);
extern void func_L18_003FE020(void *);
extern int func_002B38B8(void *);
extern void func_002A0430(int);
extern void ref_L19_003DD9D8_02(int);
extern void func_L00_003294F0(void *, int);
extern int func_002E5E58(int, int, void *);

#define WORD(p, o) (*(s32 *)((p) + (o)))
#define HALF(p, o) (*(s16 *)((p) + (o)))
#define FLAGS(p) (*(u16 *)((p) + 0x34))
#define ENTITY(o) (D_L19_001B2A1C[0] + (WORD(state, (o)) << 8))
#define LOCAL_ENTITY(o) ((u8 *)((WORD(state, (o)) << 8) + (s32)base))
#define TRIGGER(o) (D_0019B2E8[WORD(state, (o)) + D_001A79F0[0] * 16] & 0x80)

static __inline__ s16 *StreamFlag(u8 *state, int i)
{
    int off = i << 1;
    s16 *flags = (s16 *)(state + 0xA0);
    return (s16 *)((u8 *)flags + off);
}

static __inline__ s32 *StateSlot(u8 *state, int i, int base)
{
    int off = i << 2;
    s32 *slots = (s32 *)(state + base);
    return (s32 *)((u8 *)slots + off);
}

static __inline__ int StreamGroup(u8 *state, int i, int base)
{
    int off = i << 2;
    int *ids = (int *)(state + base);
    return *(int *)((u8 *)ids + off);
}

/* The same instructions as func_L18_003F90A0. The group id and D_001A7A7B are read
 * again where the logic needs them: GCSE reduces the rereads to one load and a copy.
 * D_L19_001B2728 and D_001A7A7B are written as a base plus offset, which keeps those
 * stores out of delay slots.
 */
/* Runs the group encounter: starts the enemy waves when the hero reaches each trigger point, advances through the stages, and opens or closes the linked gates and doors. */
void func_L19_003DD9D8(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int mode;
    int i;

    if (!object[0x20]) {
        int i;
        u16 *entry;
        u8 *entity;
        HALF(object, 0x32) = 0;
        object[0x30] = 255;
        for (i = 0; i < 4; i++) {
            *StreamFlag(state, i) = 0;
            for (entry = D_L19_001FB5A0[StreamGroup(state, i, 0)];
                 (StreamGroup(state, i, 0) & 255) != 255 &&
                 StreamGroup(state, i, 0) <= D_L19_001B2A38[0] && entry &&
                 ((s16)entry[-1] >= 0 || entry == D_L19_001FB5A0[StreamGroup(state, i, 0)]);
                 entry++) {
                entity = gMobyArray_L19[0] + ((*entry & 0x7FFF) << 8);
                if (!entity) break;
                SetObjectWordB8(entity, object);
            }
        }
        HALF(state, 0xA8) = 1;
        object[0x20] = 1;
        WORD(state, 0x88) = -1;
        HALF(state, 0xAA) = RandomIntBelow(D_L19_001B09C4);
        HALF(state, 0xAE) = -1;
        HALF(state, 0xAC) = 0;
        ResetAllGroupMembers(object);
        if (WORD(state, 0xC4) != -1) {
            u8 *base = gMobyArray_L19[0];
            FLAGS(LOCAL_ENTITY(0xC4)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC4)) |= 1;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = 0;
        }
        if (WORD(state, 0xC8) != -1) {
            u8 *base = gMobyArray_L19[0];
            FLAGS(LOCAL_ENTITY(0xC8)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC8)) |= 1;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = 0;
        }
        if (TRIGGER(0xB4) && !TRIGGER(0xB8)) {
            SetFlagToOne();
            ResetHeroPositionAndDirection(ENTITY(0xE4) + 0x10, ENTITY(0xE4) + 0xF0, 0, 1);
        }
        if (D_001395B8[0x9F]) {
            SetFlagToOne();
            ResetHeroPositionAndDirection(D_L19_001B0A70, D_L19_001B0A80, 0, 1);
            D_001395B8[0x9F] = 0;
            D_L19_001B0A60 = 1;
        }
        if (IsPointInCuboid(gHeroPosition, WORD(state, 0x84)))
            WORD(state, 0x88) = 5;
    } else {
        if (gFrameCounter_L19[0] < 10 && D_L19_001B0A60 == 1) {
            if (PushRequestQueue(D_L19_001BFC40, 0x95)) {
                LaunchQueuedRequest(D_L19_001BFC40);
                SetSlowdownFactorAndLowFpsFade();
                D_L19_001B0A60 = 2;
            }
        } else if (D_L19_001B0A60 == 2) {
            if (IsEitherModeTwo()) {
                D_L19_001B2724[1] = 1;
                if (D_L19_001A8F00[0] == 2) {
                    object[0x31] = 0;
                    FLAGS(object) |= 1;
                }
            } else {
                D_L19_001B2724[1] = 0;
                ref_L19_003DD9D8_01(0);
                D_L19_001B0A60 = 0;
                if (!D_001A7AFD[0] && D_001395B8[0xA1]) {
                    UnlockHelpEntry(5);
                    HandleRequestSlotState(5);
                    SetEntryValueByIndex(0x129F, -1);
                }
                CaptureCheckpointState(gHeroPosition, gHeroPosition + 0x10);
                MemcardSave(0, -1);
            }
        }
        if (D_0018C0B4[0] != 0x6F) {
            for (i = 0; i < 4; i++) {
                if (!*StreamFlag(state, i)) {
                    if (IsPointInCuboid(gHeroPosition, *StateSlot(state, i, 0x30)))
                        *StreamFlag(state, i) = 1;
                } else if (*StreamFlag(state, i) > 0) {
                    if (FastDecTimer((s16 *)(state + 0xAA)) &&
                        SelectGroupMembersAndTarget(object, i))
                        HALF(state, 0xAA) = RandomIntBelow(D_L19_001B09C4);
                }
            }
        }
        if (IsPointInCuboid(gHeroPosition, *StateSlot(state, WORD(state, 0x88) + 1, 0x40))) {
            WORD(state, 0x88)++;
            if (WORD(state, 0x88) == 6) {
                WakeAllGroupMembers(object);
                QueueKeyedRequest(WORD(state, 0x104), -1);
            } else {
                if (!WORD(state, 0x88))
                    QueueKeyedRequest(WORD(state, 0x100), -1);
                L18_DisableModeGroups(object, WORD(state, 0x88));
            }
        }
        if (WORD(state, 0x88) == 5 && IsPointInCuboid(gHeroPosition, WORD(state, 0x44))) {
            WakeAllGroupMembers(object);
            WORD(state, 0x88) = 1;
            L18_DisableModeGroups(object, 1);
        }
        mode = 0;
        switch (WORD(state, 0x88)) {
        case 2:
            mode = 2;
            break;
        case 0: case 1: case 3: case 4:
            mode = 1;
            break;
        }
        SetObjectColorEffect(object, mode);
        if (HALF(state, 0xAC)) {
            UpdateTimedEffectSequence(object);
        } else {
            int i;
            for (i = 0; i < 4; i++) {
                if (*StateSlot(state, i, 0x90) != -1 &&
                    ((u32)i >= 8 || (((D_001395B8[0x94] >> i) ^ 1) & 1)) &&
                    IsPointInCuboid(gHeroPosition, *StateSlot(state, i, 0x90))) {
                    *StateSlot(state, i, 0x90) = -1;
                    HALF(state, 0xAE) = i;
                    StartTimedEffectSequence(object);
                    if ((u32)i < 8) D_001395B8[0x94] |= 1 << i;
                }
            }
        }
    }
    ref_L19_003DD9D8_00(DrawSegmentedBeams, object);
    if (TRIGGER(0xBC) || (TRIGGER(0xB0) && !TRIGGER(0xB4))) {
        if (WORD(state, 0xC8) != -1 && WORD(state, 0xCC) != -1) {
            u8 *base = gMobyArray_L19[0];
            if ((FLAGS(LOCAL_ENTITY(0xC8)) & 1) && ((FLAGS(LOCAL_ENTITY(0xCC)) ^ 1) & 1)) {
                FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFD;
                FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFE;
                WORD(LOCAL_ENTITY(0xC8), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC8) + 0x24), 0x10);
                if (WORD(state, 0xCC) != -1) FLAGS(LOCAL_ENTITY(0xCC)) |= 2;
                {
                    u8 *nextBase = gMobyArray_L19[0];
                    FLAGS((u8 *)((WORD(state, 0xCC) << 8) + (s32)nextBase)) |= 1;
                    WORD((u8 *)((WORD(state, 0xCC) << 8) + (s32)nextBase), 0x98) = 0;
                }
            }
        }
    }
    if (TRIGGER(0xB4) && !TRIGGER(0xB8)) {
        u8 *base = gMobyArray_L19[0];
        if (WORD(state, 0xC8) != -1) {
            FLAGS(LOCAL_ENTITY(0xC8)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC8)) |= 1;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = 0;
            ClearLinkToMinusOne(base + (WORD(state, 0xD8) << 8));
            ClearLinkToMinusOne(ENTITY(0xDC));
        }
    }
    if (!TRIGGER(0xB8) && IsThirdPendingFlagSet(object)) {
        object[0xBC] = 1;
        object[0xBE] &= 0xFB;
        MarkTableEntryFlagged(WORD(state, 0xB8));
        ref_L19_003DD9D8_02(0);
        if (WORD(state, 0xC4) != -1) {
            u8 *base = gMobyArray_L19[0];
            FLAGS(LOCAL_ENTITY(0xC4)) &= 0xFFFD;
            FLAGS(LOCAL_ENTITY(0xC4)) &= 0xFFFE;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC4) + 0x24), 0x10);
        }
        if (WORD(state, 0xC0) != -1) {
            if (WORD(state, 0xD0) != -1) SetObjectFlagBit(ENTITY(0xD0), 1);
            if (WORD(state, 0xD4) != -1) SetObjectFlagBit(ENTITY(0xD0), 1);
            ((u8 *)((WORD(state, 0xC0) << 8) + (s32)gMobyArray_L19[0]))[0xBC] = 1;
        }
    }
    if (object[0xBC] && TRIGGER(0xBC)) {
        object[0xBC] = 0;
        if (WORD(state, 0xC8) != -1) {
            u8 *base = gMobyArray_L19[0];
            FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFD;
            FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFE;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC8) + 0x24), 0x10);
        }
        if (WORD(state, 0xC4) != -1) {
            u8 *base = gMobyArray_L19[0];
            FLAGS(LOCAL_ENTITY(0xC4)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC4)) |= 1;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = 0;
        }
        if (WORD(state, 0xD0) != -1) SetObjectFlagBit(ENTITY(0xD0), 1);
        if (WORD(state, 0xD4) != -1) SetObjectFlagBit(ENTITY(0xD0), 1);
        ClearLinkToZero(ENTITY(0xD8));
        ClearLinkToZero(ENTITY(0xDC));
    }
    {
        if (!D_001A7A78[3]) {
            int ready;
            u16 *entry;
            u8 *entity;
            ready = 1;
            for (entry = D_L19_001FB5A0[WORD(state, 0xE0)];
            (WORD(state, 0xE0) & 255) != 255 && WORD(state, 0xE0) <= D_L19_001B2A38[0] && entry &&
            ((entry && (s16)entry[-1] >= 0) || entry == D_L19_001FB5A0[WORD(state, 0xE0)]); entry++) {
                entity = gMobyArray_L19[0] + ((*entry & 0x7FFF) << 8);
                if (!entity) break;
                if (entity[0x20] != 0xFE) {
                    if (entity[0x20] != 0xFD) {
                        if (!(FLAGS(entity) & 1)) continue;
                    }
                }
                ready = 0;
                break;
            }
            if (ready) {
                int allReady = 1;
                u16 *entry;
                u8 *entity;
                for (i = 0; i < 4 && allReady; i++) {
                    for (entry = D_L19_001FB5A0[StreamGroup(state, i, 0xF0)];
                    (StreamGroup(state, i, 0xF0) & 255) != 255 &&
                    StreamGroup(state, i, 0xF0) <= D_L19_001B2A38[0] && entry &&
                    ((s16)entry[-1] >= 0 || entry == D_L19_001FB5A0[StreamGroup(state, i, 0xF0)]);
                    entry++) {
                        entity = gMobyArray_L19[0] + ((*entry & 0x7FFF) << 8);
                        if (!entity) break;
                        if (entity[0x20] != 0xFE) {
                            if (entity[0x20] != 0xFD) {
                                if ((FLAGS(entity) ^ 1) & 1) {
                                    allReady = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (allReady) {
                    if (!D_001A7A78[3]) {
                        D_001A7A78[3] = 1;
                        PlaySoundFromGlobalBank(1, 0, 0);
                        SetEntryValueByIndex(0x1233, -1);
                        D_L19_001A903C[0] = 1;
                    }
                    MarkTableEntryFlagged(WORD(state, 0xE8));
                }
            }
        }
    }
}
