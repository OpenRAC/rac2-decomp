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

u8 *func_L01_003D25B8(u8 *owner, void *pos, void *vel, int cls, int index)
{
    u8 *p = func_00305EE8(cls);
    if (p) {
        u8 *parent = *(u8 **)(owner + 0x68);
        SpawnVars *state = *(SpawnVars **)(p + 0x68);
        p[0x30] = 0xFF;
        *(s8 *)(p + 0x31) = 1;
        *(u16 *)(p + 0x32) = 0xFF;
        p[0x20] = 0;
        p[0xBC] = 0;
        state->owner = owner;
        state->index = index;
        *(float *)(p + 0x2C) = *(float *)(*(u8 **)(p + 0x24) + 0x24) * D_L01_001B0540;
        qcopy(p + 0x10, pos);
        qcopy(p + 0xF0, vel);
        qcopy(state->pos, pos);
        {
            int value;
            parent += index * 4;
            value = *(int *)(parent + 0x10);
            state->target = -1;
            state->link = value;
        }
        state->timer = 0;
        func_355780(2, 0, p);
        func_00308938(p);
        func_00314D00(p);
    }
    return p;
}

/* Walks the 0x7FFF-masked id list at table[index] and flags class 0xB2B entries. */
void func_L01_003D87B8(s32 index)
{
    u16 *p;
    u32 slot;
    u8 *base;
    u8 *e;

    if (index == -1)
        return;
    slot = D_L01_001FB020[index];
    if (slot == 0)
        return;
    p = (u16 *)slot;
    base = D_L01_001B255C;
    do {
        e = base + ((*p & 0x7FFF) << 8);
        if (*(s8 *)(e + 0x20) >= 0 && *(s16 *)(e + 0xAA) == 0xB2B)
            *(u16 *)(*(u8 **)(e + 0x68) + 0x3DA) = 1;
    } while (*(s16 *)p++ >= 0);
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
void func_L01_003D8AD0(u8 *p)
{
    u8 *b;
    u8 group;

    if (p[0xB0] != 0xFF && *(short *)(p + 0xB2) >= 0 && !(p[0xB1] & 0x80)) {
        if (*(u16 *)(p + 0xB2) & 1) {
            b = D_0019B4A8 + ((*(short *)(p + 0xB2) >> 1) + (D_001A79F0 << 10));
            if (((*b >> 4) & 7) != 7) *b += 0x10;
        } else {
            b = D_0019B4A8 + ((*(short *)(p + 0xB2) >> 1) + (D_001A79F0 << 10));
            if ((*b & 7) != 7) ++*b;
        }
        D_L01_0021D840.collected[*(short *)(p + 0xB2)] = p[0xB0] + 2;
        if (p[0xB0] == 0xFF) goto record;
        group = p[0xB0];
        if (!(D_L01_001B23A0.flags[group] & 0x80) && (D_0019B2E8[group + (D_001A79F0 << 4)] & 0x80)) {
        record:
            D_L01_0021E4B0.collected[*(short *)(p + 0xB2)] = p[0xB0] + 2;
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
void func_L01_003D8E80(u8 *a0)
{
    HandlerState *state = *(HandlerState **)(a0 + 0x68);
    u8 *p;
    u8 *entry;
    int flag, hit, i, color, persist_id;
    float f;
    float v[4] __attribute__((aligned(16)));

    switch (a0[0x20]) {
    case 0:
        if (state->persistent && a0[0xB0] != 255) {
            u16 id = *(u16 *)(a0 + 0xB2);
            int bits;
            if (D_L01_0021E4B0.collected[(short)id] ||
                (bits = D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)],
                 (id & 1) ? ((bits >> 4) & 7) : (bits & 7))) {
                if (state->childIndex != -1)
                    func_0029F338(D_L01_001B255C + (state->childIndex << 8));
                func_0029F338(a0);
                return;
            }
        }
        a0[0x95] = 0;
        state->soundIndex = -1;
        switch (state->mode) {
        case 0:
            *(u16 *)(a0 + 0x32) = 0x3FF;
            a0[0x30] = 255;
            if (state->parentIndex != -1) {
                u8 *parent = D_L01_001B255C + (state->parentIndex << 8);
                if (parent) {
                    if (*(u8 **)(parent + 0x68) && *(int *)(*(u8 **)(parent + 0x68) + 0xC8))
                        func_002A7398(a0, 6, 0);
                    else
                        func_002A7398(a0, 9, 0);
                }
            }
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * D_L01_001B0794;
            break;
        case 1:
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * D_L01_001B0798;
            func_002A7398(a0, 2, 0);
            break;
        case 2:
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * D_L01_001B079C;
            func_002A7398(a0, 4, 0);
            if (state->linkIndex != -1)
                state->linkCount = func_002A8508(state->linkIndex, -1);
            break;
        case 3:
            *(int *)(a0 + 0x98) = 0;
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * D_L01_001B07A0;
            func_002A7398(a0, 10, 0);
            break;
        }
        if (state->parentIndex != -1) {
            p = D_L01_001B255C + (state->parentIndex << 8);
            if (p) {
                a0[0x40] = p[0x40];
                a0[0x41] = p[0x41];
                *(float *)(a0 + 0x44) = *(float *)(p + 0x44);
                update_moby_animation_state(a0);
            }
        }
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        switch (state->mode) {
        case 1:
            if (state->soundIndex == -1 && !func_002A77E0(79))
                state->soundIndex = PlayMobySound(0, 0, a0);
            if (a0[0x60] & 2) {
                if (!func_002A77E0(3)) {
                    if (a0[0x43] != 2)
                        func_002A7470(a0, 2, 0, func_002A7820(8, 15));
                } else if (a0[0x43] != 1)
                    func_002A7470(a0, 1, 0, func_002A7820(8, 15));
                *(float *)(a0 + 0x48) = func_002A7878(0.7f, 1.1f);
            }
            if (!func_002A77E0(19)) {
                qcopy(v, a0 + 0x10);
                v[2] = func_L01_003BAFB0();
                f = func_002A7878(0.2f, 2.0f);
                color = ((func_002A77E0(6) + 20) << 24) | 0x5060;
                func_002C19D8(v, f, D_L01_001AFE18, 10000.0f, color);
            }
            hit = 0;
            if (func_002A9640(a0, 0x10001, 0))
                hit = 1;
            if (IsPointInCuboid(D_00189EA0, state->hitIndex))
                hit = 1;
            if (hit) {
                state->soundIndex = PlayMobySound(0, 0, a0);
                func_L01_003D8C00(a0, 3, 10, 1);
                if (a0[0x43] != 3)
                    func_002A7470(a0, 3, 0, 10);
                func_002A7750(a0, 2, -1);
            }
            break;
        case 2:
            switch (a0[0xBC]) {
            case 0:
                if (state->soundIndex == -1 && !func_002A77E0(89))
                    state->soundIndex = PlayMobySound(0, 0, a0);
                {
                    int detected = func_002A9640(a0, 0x10001, 0);
                    flag = 0;
                    if (detected) {
                        flag = 1;
                        func_L01_003D87B8(state->linkIndex);
                    }
                }
                if (state->linkIndex != -1 && state->linkCount) {
                    if (func_002A8508(state->linkIndex, -1) < state->linkCount)
                        flag = 1;
                }
                if (flag) {
                    state->soundIndex = PlayMobySound(0, 0, a0);
                    func_L01_003D8830(a0);
                    func_L01_003D8830(a0);
                    func_L01_003D8830(a0);
                    if (a0[0x43] != 11)
                        func_002A7470(a0, 11, 0, 15);
                    a0[0xBC] = 1;
                }
                a0[0xA8] = 255;
                break;
            case 1:
                func_L01_003D8830(a0);
                if (a0[0x60] & 2) {
                    if (a0[0x43] != 3)
                        func_002A7470(a0, 3, 0, 15);
                    func_002A7750(a0, 2, -1);
                }
                break;
            }
            break;
        case 3:
            *(int *)(a0 + 0x98) = 0;
            if (state->parentIndex != -1) {
                p = D_L01_001B255C + (state->parentIndex << 8);
                if (!p || p[0x20] == 254 || p[0x20] == 253) {
                    func_L01_003D8AD0(a0);
                } else {
                    qcopy(a0 + 0x10, p + 0x10);
                    qcopy(a0 + 0xF0, p + 0xF0);
                }
            }
            if (IsPointInCuboid(D_00189EA0, state->hitIndex)) {
                /* Retail shares state 2's counter and delete tails. */
                if (state->persistent) {
                    if (a0[0xB0] != 255) {
                        if ((persist_id = *(u16 *)(a0 + 0xB2)) & 1)
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
            if (state->soundIndex == -1 && !func_002A77E0(89))
                state->soundIndex = PlayMobySound(0, 0, a0);
            break;
        }
        break;
    case 2:
        if (state->mode == 2) {
            func_L01_003D8830(a0);
        } else if (state->mode == 1 && !func_002A77E0(4)) {
            func_L01_003D8C00(a0, 3, 10, 1);
            qcopy(v, a0 + 0x10);
            v[2] = func_L01_003BAFB0();
            f = func_002A7878(0.2f, 2.0f);
            color = ((func_002A77E0(6) + 20) << 24) | 0x5060;
            func_002C19D8(v, f, D_L01_001AFE18, 10000.0f, color);
        }
        if (a0[0x60] & 2) {
            if (state->persistent) {
                if (a0[0xB0] != 255) {
                    if ((persist_id = *(u16 *)(a0 + 0xB2)) & 1) {
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
                func_L01_003D8AD0(a0);
            }
delete_current:
            func_0029F338(a0);
            return;
        }
        break;
    }
    /* Retail stores the index three times; the slot found by the scan is discarded. */
    if (!func_002E59B0(a0, state->soundIndex)) {
        state->soundIndex = -1;
        for (i = 0; i < 52; i++) {
            state->soundIndex = -1;
            entry = D_00188660 + i * 0x70;
            if (*(u8 **)(entry + 0x88) == a0 && entry[0x74]) {
                state->soundIndex = i;
                break;
            }
        }
        state->soundIndex = -1;
    }
    if (a0[0x95]) {
        if (state->persistent) {
            if (a0[0xB0] != 255) {
                if (*(u16 *)(a0 + 0xB2) & 1) {
                    u8 *counter = D_0019B4A8 + ((*(short *)(a0 + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if (((value >> 4) & 7) != 7)
                        *counter = value + 16;
                } else {
                    u8 *counter = D_0019B4A8 + ((*(short *)(a0 + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if ((value & 7) != 7)
                        *counter = value + 1;
                }
            }
        } else {
            func_L01_003D8AD0(a0);
        }
        func_0029F338(a0);
    }
}
