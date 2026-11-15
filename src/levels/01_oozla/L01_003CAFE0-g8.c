#include "common.h"

extern u8 *D_L01_001B255C;

extern u32 D_L01_001FB020[];

extern u8 *func_00305EE8(int);
extern s32 func_355780(u32 a0, u32 a1, void *a2);
extern void func_00308938(void *);
extern void func_00314D00(void *);
extern float D_L01_001B0540 __attribute__((sda));

/* The spawned moby's vars (+0x68). Struct stores let the fixed scalar scale
   load be scheduled ahead of the model-pointer load, as in retail. */
typedef struct {
    u8 pad0[0x60];
    u8 pos[0x10];
    u8 *owner;
    int link;
    int timer;
    u16 index;
    s16 target;
} SpawnVars;

/* Creates a child moby at a position and ties it to its owner. */
u8 *func_L01_003D25B8(u8 *owner, void *pos, void *vel, int cls, int index)
{
    u8 *child = func_00305EE8(cls);
    if (child) {
        u8 *parent = *(u8 **)(owner + 0x68);
        SpawnVars *state = *(SpawnVars **)(child + 0x68);
        child[0x30] = 0xFF;
        *(s8 *)(child + 0x31) = 1;
        *(u16 *)(child + 0x32) = 0xFF;
        child[0x20] = 0;
        child[0xBC] = 0;
        state->owner = owner;
        state->index = index;
        *(float *)(child + 0x2C) = *(float *)(*(u8 **)(child + 0x24) + 0x24) * D_L01_001B0540;
        qcopy(child + 0x10, pos);
        qcopy(child + 0xF0, vel);
        qcopy(state->pos, pos);
        {
            int value;
            parent += index * 4;
            value = *(int *)(parent + 0x10);
            state->target = -1;
            state->link = value;
        }
        state->timer = 0;
        func_355780(2, 0, child);
        func_00308938(child);
        func_00314D00(child);
    }
    return child;
}

/* Walks the 0x7FFF-masked id list at table[index] and flags class 0xB2B entries. */
/* Flags every Mutant Muckdweller in a linked list so that it reacts. */
void func_L01_003D87B8(s32 index)
{
    u16 *idPtr;
    u32 slot;
    u8 *base;
    u8 *entry;

    if (index == -1)
        return;
    slot = D_L01_001FB020[index];
    if (slot == 0)
        return;
    idPtr = (u16 *)slot;
    base = gMobyTable_L01;
    do {
        entry = base + ((*idPtr & 0x7FFF) << 8);
        if (*(s8 *)(entry + 0x20) >= 0 && *(s16 *)(entry + 0xAA) == 0xB2B /* Mutant Muckdweller */)
            *(u16 *)(*(u8 **)(entry + 0x68) + 0x3DA) = 1;
    } while (*(s16 *)idPtr++ >= 0);
}

extern int D_001A79F0;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[];
/* Level save state: collected[] is indexed by a moby's save id (s16 at +0xB2). */
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState D_L01_0021D840;
extern LevelSaveState D_L01_0021E4B0;
typedef struct { u8 flags[256]; } MissionFlags;
extern MissionFlags D_L01_001B23A0 __attribute__((sda));

/* Records a moby (mission byte +0xB0, save id +0xB2) in the current and checkpoint
   collected[] tables; same shape as RAC1's helga_update tail. */
/* Records that a moby was collected, in the current and the checkpoint tables. */
void func_L01_003D8AD0(u8 *moby)
{
    u8 *counter;
    u8 group;

    if (moby[0xB0] != 0xFF && *(short *)(moby + 0xB2) >= 0 && !(moby[0xB1] & 0x80)) {
        if (*(u16 *)(moby + 0xB2) & 1) {
            counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (gCurrentMapIndex << 10));
            if (((*counter >> 4) & 7) != 7) *counter += 0x10;
        } else {
            counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (gCurrentMapIndex << 10));
            if ((*counter & 7) != 7) ++*counter;
        }
        D_L01_0021D840.collected[*(short *)(moby + 0xB2)] = moby[0xB0] + 2;
        if (moby[0xB0] == 0xFF) goto record;
        group = moby[0xB0];
        if (!(D_L01_001B23A0.flags[group] & 0x80) && (D_0019B2E8[group + (gCurrentMapIndex << 4)] & 0x80)) {
        record:
            D_L01_0021E4B0.collected[*(short *)(moby + 0xB2)] = moby[0xB0] + 2;
        }
    }
}

extern u8 D_00188660[], D_00189EA0[];
extern u8 D_L01_001AFE18[] MACRO_ADDR;
/* The tails read the level number $gp-relative, case 0 through D_001A79F0's absolute address. */
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern float D_L01_001B0794 __attribute__((sda));
extern float D_L01_001B0798 __attribute__((sda));
extern float D_L01_001B079C __attribute__((sda));
extern float D_L01_001B07A0 __attribute__((sda));
extern void func_0029F338(void *);
extern void func_002A7398(void *, int, int);
extern int func_002A8508(int, int);
extern void func_0029F390(void *);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002E5CF8(int, int, void *);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_L01_003BAFB0(void);
extern void *func_002C19D8(void *position, float size, void *owner, float spin, int color);
extern int func_002A9640(void *, int, int);
extern void func_L01_003D8C00(void *, int, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_L01_003D8830(void *);
extern int func_002E59B0(void *, int);
extern int func_002ACBC8(void *, int);

/* The moby's vars (+0x68). */
typedef struct {
    u8 pad[0x50];
    int mode;
    int parentIndex;
    int hitIndex;
    int childIndex;
    int persistent;
    int linkIndex;
    int linkCount;
    u8 unknown6c[4];
    int soundIndex;
} HandlerState;

/* Per-state update: state 0 initialises by mode, 1 runs the mode's behaviour, 2 finishes.
   A persistent moby (save id at +0xB2) counts itself in the level's 3-bit collection
   counters before it is deleted; any other one is recorded by func_L01_003D8AD0. */
/* Updates a moby that bursts open, with several modes. It makes sparkles, bursts into particles when it is hit and is removed after it is counted. */
void func_L01_003D8E80(u8 *moby)
{
    HandlerState *state = *(HandlerState **)(moby + 0x68);
    u8 *linkedMoby;
    u8 *entry;
    int flag, hit, i, color, persist_id;
    float size;
    float position[4] __attribute__((aligned(16)));

    switch (moby[0x20]) {
    case 0:
        if (state->persistent && moby[0xB0] != 255) {
            u16 id = *(u16 *)(moby + 0xB2);
            int bits;
            if (D_L01_0021E4B0.collected[(short)id] ||
                (bits = D_0019B4A8[((short)id >> 1) + (gCurrentMapIndex << 10)],
                 (id & 1) ? ((bits >> 4) & 7) : (bits & 7))) {
                if (state->childIndex != -1)
                    MarkMobySpawned(gMobyTable_L01 + (state->childIndex << 8));
                MarkMobySpawned(moby);
                return;
            }
        }
        moby[0x95] = 0;
        state->soundIndex = -1;
        switch (state->mode) {
        case 0:
            *(u16 *)(moby + 0x32) = 0x3FF;
            moby[0x30] = 255;
            if (state->parentIndex != -1) {
                u8 *parent = gMobyTable_L01 + (state->parentIndex << 8);
                if (parent) {
                    if (*(u8 **)(parent + 0x68) && *(int *)(*(u8 **)(parent + 0x68) + 0xC8))
                        StartAnimationImmediate(moby, 6, 0);
                    else
                        StartAnimationImmediate(moby, 9, 0);
                }
            }
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B0794;
            break;
        case 1:
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B0798;
            StartAnimationImmediate(moby, 2, 0);
            break;
        case 2:
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B079C;
            StartAnimationImmediate(moby, 4, 0);
            if (state->linkIndex != -1)
                state->linkCount = CountMobysInGroupNotInState(state->linkIndex, -1);
            break;
        case 3:
            *(int *)(moby + 0x98) = 0;
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B07A0;
            StartAnimationImmediate(moby, 10, 0);
            break;
        }
        if (state->parentIndex != -1) {
            linkedMoby = gMobyTable_L01 + (state->parentIndex << 8);
            if (linkedMoby) {
                moby[0x40] = linkedMoby[0x40];
                moby[0x41] = linkedMoby[0x41];
                *(float *)(moby + 0x44) = *(float *)(linkedMoby + 0x44);
                update_moby_animation_state(moby);
            }
        }
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        switch (state->mode) {
        case 1:
            if (state->soundIndex == -1 && !RandomIntBelow(79))
                state->soundIndex = PlayMobySound(0, 0, moby);
            if (moby[0x60] & 2) {
                if (!RandomIntBelow(3)) {
                    if (moby[0x43] != 2)
                        StartAnimationBlended(moby, 2, 0, RandomIntRange(8, 15));
                } else if (moby[0x43] != 1)
                    StartAnimationBlended(moby, 1, 0, RandomIntRange(8, 15));
                *(float *)(moby + 0x48) = RandomFloatRange(0.7f, 1.1f);
            }
            if (!RandomIntBelow(19)) {
                qcopy(position, moby + 0x10);
                position[2] = GetWaterHeight();
                size = RandomFloatRange(0.2f, 2.0f);
                color = ((RandomIntBelow(6) + 20) << 24) | 0x5060;
                SpawnDriftingParticle_002C19D8(position, size, D_L01_001AFE18, 10000.0f, color);
            }
            hit = 0;
            if (FindOwnedEffectSlot(moby, 0x10001, 0))
                hit = 1;
            if (IsPointInCuboid(gHeroPosition, state->hitIndex))
                hit = 1;
            if (hit) {
                state->soundIndex = PlayMobySound(0, 0, moby);
                SpawnWaterSplashEffect(moby, 3, 10, 1);
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 10);
                SetMobyState(moby, 2, -1);
            }
            break;
        case 2:
            switch (moby[0xBC]) {
            case 0:
                if (state->soundIndex == -1 && !RandomIntBelow(89))
                    state->soundIndex = PlayMobySound(0, 0, moby);
                {
                    int detected = FindOwnedEffectSlot(moby, 0x10001, 0);
                    flag = 0;
                    if (detected) {
                        flag = 1;
                        FlagMuckdwellersInGroup(state->linkIndex);
                    }
                }
                if (state->linkIndex != -1 && state->linkCount) {
                    if (CountMobysInGroupNotInState(state->linkIndex, -1) < state->linkCount)
                        flag = 1;
                }
                if (flag) {
                    state->soundIndex = PlayMobySound(0, 0, moby);
                    SpawnParticleBurst_L01(moby);
                    SpawnParticleBurst_L01(moby);
                    SpawnParticleBurst_L01(moby);
                    if (moby[0x43] != 11)
                        StartAnimationBlended(moby, 11, 0, 15);
                    moby[0xBC] = 1;
                }
                moby[0xA8] = 255;
                break;
            case 1:
                SpawnParticleBurst_L01(moby);
                if (moby[0x60] & 2) {
                    if (moby[0x43] != 3)
                        StartAnimationBlended(moby, 3, 0, 15);
                    SetMobyState(moby, 2, -1);
                }
                break;
            }
            break;
        case 3:
            *(int *)(moby + 0x98) = 0;
            if (state->parentIndex != -1) {
                linkedMoby = gMobyTable_L01 + (state->parentIndex << 8);
                if (!linkedMoby || linkedMoby[0x20] == 254 || linkedMoby[0x20] == 253) {
                    RecordMobyCollected(moby);
                } else {
                    qcopy(moby + 0x10, linkedMoby + 0x10);
                    qcopy(moby + 0xF0, linkedMoby + 0xF0);
                }
            }
            if (IsPointInCuboid(gHeroPosition, state->hitIndex)) {
                /* Retail shares state 2's counter and delete tails. */
                if (state->persistent) {
                    if (moby[0xB0] != 255) {
                        if ((persist_id = *(u16 *)(moby + 0xB2)) & 1)
                            goto persist_high;
                        else
                            goto persist_low;
                    }
                } else
                    goto delete_cleanup;
                goto delete_current;
            }
            /* Falls through to the sound trigger used by mode zero. */
        case 0:
            if (state->soundIndex == -1 && !RandomIntBelow(89))
                state->soundIndex = PlayMobySound(0, 0, moby);
            break;
        }
        break;
    case 2:
        if (state->mode == 2) {
            SpawnParticleBurst_L01(moby);
        } else if (state->mode == 1 && !RandomIntBelow(4)) {
            SpawnWaterSplashEffect(moby, 3, 10, 1);
            qcopy(position, moby + 0x10);
            position[2] = GetWaterHeight();
            size = RandomFloatRange(0.2f, 2.0f);
            color = ((RandomIntBelow(6) + 20) << 24) | 0x5060;
            SpawnDriftingParticle_002C19D8(position, size, D_L01_001AFE18, 10000.0f, color);
        }
        if (moby[0x60] & 2) {
            if (state->persistent) {
                if (moby[0xB0] != 255) {
                    if ((persist_id = *(u16 *)(moby + 0xB2)) & 1) {
                        u8 *counter;
                        u32 value;
persist_high:
                        counter = D_0019B4A8 + (((short)persist_id >> 1) + (D_001A79F0_gp << 10));
                        value = *counter;
                        if (((value >> 4) & 7) != 7)
                            *counter = value + 16;
                    } else {
                        u8 *counter;
                        u32 value;
persist_low:
                        counter = D_0019B4A8 + (((short)persist_id >> 1) + (D_001A79F0_gp << 10));
                        value = *counter;
                        if ((value & 7) != 7)
                            *counter = value + 1;
                    }
                }
            } else {
delete_cleanup:
                RecordMobyCollected(moby);
            }
delete_current:
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    /* Retail stores the index three times; the slot found by the scan is discarded. */
    if (!IsVoicePlayingForOwner(moby, state->soundIndex)) {
        state->soundIndex = -1;
        for (i = 0; i < 52; i++) {
            state->soundIndex = -1;
            entry = gSoundState + i * 0x70;
            if (*(u8 **)(entry + 0x88) == moby && entry[0x74]) {
                state->soundIndex = i;
                break;
            }
        }
        state->soundIndex = -1;
    }
    if (moby[0x95]) {
        if (state->persistent) {
            if (moby[0xB0] != 255) {
                if (*(u16 *)(moby + 0xB2) & 1) {
                    u8 *counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if (((value >> 4) & 7) != 7)
                        *counter = value + 16;
                } else {
                    u8 *counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if ((value & 7) != 7)
                        *counter = value + 1;
                }
            }
        } else {
            RecordMobyCollected(moby);
        }
        MarkMobySpawned(moby);
    }
}
