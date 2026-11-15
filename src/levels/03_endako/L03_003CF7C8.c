#include "common.h"

extern char *D_L03_001B2A1C[] __attribute__((sda));
typedef struct {
    u8 header[0x464];
    u8 entries[0];
} TriggerTable;
extern TriggerTable D_L03_0021EA30, D_L03_0021DDC0;
extern u8 D_L03_001B2860[] __attribute__((sda));
extern u8 D_0019B4A8[], D_0019B2E8[];
extern int D_001A79F0[] __attribute__((sda));
extern char D_00189EA0[];
extern int func_L03_003CF7B8(void *);
extern int func_002ACBC8(void *, int);
extern void func_L02_0031F858(int, int);
extern int func_002A8508(int, int);
extern void func_002A7750(void *, int, int);
typedef struct {
    int source, handle, active, first, second;
    int handles[4];
    int actions[4];
    int pad[3];
    int phase;
} TriggerState;

/* Runs the two trigger phases and records completion in the level tables. */
/* Per-frame update of moby class 2482. */
void func_L03_003CF7C8(char *obj)
{
    TriggerState *state  =  *(TriggerState **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0: {
        u16 id = *(u16 *)(obj + 0xb2);
        int bits;
        if (D_L03_0021EA30.entries[(s16)id] != 0) goto enabled;
        bits = D_0019B4A8[((s16)id>>1)+(gCurrentMapIndex[0]<<10)];
        if ((id&1) ? ((bits>>4)&7) : (bits&7)) {
        enabled:
            SetGroupObjectsEnabled(state->first, 1);
            SetGroupObjectsEnabled(state->second, 1);
            SetMobyState(obj, 5, -1);
        } else SetMobyState(obj, 1, -1);
        break;
    }
    case 1: {
        int triggered = 0;
        if (state->source != -1 && IsInStateTwoToFour(D_L03_001B2A1C[0]+state->source*256)) triggered = 1;
        else if (state->handle != -1 && IsPointInCuboid(gHeroPosition, state->handle)) triggered = 1;
        else if (state->active != -1) triggered = CountMobysInGroupNotInState(state->active, -1) == 0;
        if (triggered) SetMobyState(obj, 2, -1);
        break;
    }
    case 2:
        if (*(u16 *)(obj + 0x96) >= 31) {
            SetMobyState(obj, 3, -1);
            if (state->phase == 0) SetGroupObjectsEnabled(state->first, 1);
            else SetGroupObjectsEnabled(state->second, 1);
        }
        break;
    case 3: {
        int *handlePtr, *actionPtr; int i;
        if (*(u16 *)(obj + 0x96) >= 31) {
            if (state->phase) {
                int invalid = -1;
                actionPtr = state->actions; handlePtr = state->handles;
                i = 3;
                do {
                    if (*handlePtr != invalid) SetGroupObjectsEnabled(*actionPtr, 1);
                    actionPtr++;
                    i--;
                    handlePtr++;
                } while (i >= 0);
                D_L03_0021DDC0.entries[*(short *)(obj + 0xb2)] = *(u8 *)(obj + 0xb0) + 2;
                { u32 idx = *(u8 *)(obj + 0xb0);
                if (idx == 255 || (!(D_L03_001B2860[(u8)idx]&0x80) && (D_0019B2E8[(u8)idx+(gCurrentMapIndex[0]<<4)]&0x80)))
                    D_L03_0021EA30.entries[*(short *)(obj + 0xb2)] = idx + 2; }
                SetMobyState(obj, 5, -1);
            } else {
                int *handles = state->handles;
                int j;
                for (j = 3;j >= 0;j--, handles++) if (*handles != -1) SetGroupObjectsEnabled(*handles, 1);
                SetMobyState(obj, 4, -1);
            }
        }
        break;
    }
    case 4: {
        int triggered = 1, i; int invalid = -1; int *handlePtr = state->handles;
        for (i = 3;i >= 0;i--, handlePtr++) if (*handlePtr != invalid && CountMobysInGroupNotInState(*handlePtr, -1)) triggered = 0;
        if (triggered) { state->phase++; SetMobyState(obj, 2, -1); }
        break;
    }
    }
    (*(u16 *)(obj + 0x96))++;
}
