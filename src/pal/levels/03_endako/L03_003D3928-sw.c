#include "include_asm.h"

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
void func_PAL_L03_003D3928(char *obj)
{
    TriggerState *state  =  *(TriggerState **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0: {
        u16 id = *(u16 *)(obj + 0xb2);
        int bits;
        if (D_L03_0021EA30.entries[(s16)id] != 0) goto enabled;
        bits = D_0019B4A8[((s16)id>>1)+(D_001A79F0[0]<<10)];
        if ((id&1) ? ((bits>>4)&7) : (bits&7)) {
        enabled:
            func_L02_0031F858(state->first, 1);
            func_L02_0031F858(state->second, 1);
            func_002A7750(obj, 5, -1);
        } else func_002A7750(obj, 1, -1);
        break;
    }
    case 1: {
        int yes = 0;
        if (state->source != -1 && func_L03_003CF7B8(D_L03_001B2A1C[0]+state->source*256)) yes = 1;
        else if (state->handle != -1 && func_002ACBC8(D_00189EA0, state->handle)) yes = 1;
        else if (state->active != -1) yes = func_002A8508(state->active, -1) == 0;
        if (yes) func_002A7750(obj, 2, -1);
        break;
    }
    case 2:
        if (*(u16 *)(obj + 0x96) >= 26) {
            func_002A7750(obj, 3, -1);
            if (state->phase == 0) func_L02_0031F858(state->first, 1);
            else func_L02_0031F858(state->second, 1);
        }
        break;
    case 3: {
        int *p, *q; int i;
        if (*(u16 *)(obj + 0x96) >= 26) {
            if (state->phase) {
                int invalid = -1;
                q = state->actions; p = state->handles;
                i = 3;
                do {
                    if (*p != invalid) func_L02_0031F858(*q, 1);
                    q++;
                    i--;
                    p++;
                } while (i >= 0);
                D_L03_0021DDC0.entries[*(short *)(obj + 0xb2)] = *(u8 *)(obj + 0xb0) + 2;
                { u32 idx = *(u8 *)(obj + 0xb0);
                if (idx == 255 || (!(D_L03_001B2860[(u8)idx]&0x80) && (D_0019B2E8[(u8)idx+(D_001A79F0[0]<<4)]&0x80)))
                    D_L03_0021EA30.entries[*(short *)(obj + 0xb2)] = idx + 2; }
                func_002A7750(obj, 5, -1);
            } else {
                int *handles = state->handles;
                int j;
                for (j = 3;j >= 0;j--, handles++) if (*handles != -1) func_L02_0031F858(*handles, 1);
                func_002A7750(obj, 4, -1);
            }
        }
        break;
    }
    case 4: {
        int yes = 1, i; int invalid = -1; int *p = state->handles;
        for (i = 3;i >= 0;i--, p++) if (*p != invalid && func_002A8508(*p, -1)) yes = 0;
        if (yes) { state->phase++; func_002A7750(obj, 2, -1); }
        break;
    }
    }
    (*(u16 *)(obj + 0x96))++;
}
