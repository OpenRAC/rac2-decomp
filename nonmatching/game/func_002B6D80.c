#include "include_asm.h"

typedef unsigned char u8;
typedef int s32;

extern u8 D_001A63A8[];
extern u8 D_0014B540[];
extern void func_002B7EA8(s32, long);
extern void func_00133340(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, long long);

typedef struct {
    u8 before44[0x44];
    s32 busy;
    short first;
    short third;
    short second;
    short state;
    u8 before54[4];
    short reset;
    u8 before58[2];
    s32 count;
    s32 rate;
} RequestState_002B6D80;

typedef struct {
    s32 entry;
    s32 next;
} RequestEntry_002B6D80;

void func_002B6D80(s32 a0, s32 a1, s32 a2)
{
    RequestState_002B6D80 *state = (RequestState_002B6D80 *)D_001A63A8;
    u8 *base = D_0014B540;
    RequestEntry_002B6D80 *table = (RequestEntry_002B6D80 *)(base + 0x5300);
    s32 handle;
    s32 offset;

    if (state->busy != 0)
        return;
    handle = table[a0].entry;
    if (handle == 0)
        return;
    offset = *(s32 *)(base + 0x52FC);
    state->count = 10;
    state->rate = 48000;
    state->busy = -1;
    state->state = 1;
    state->second = a1;
    state->first = a0;
    state->third = a2;
    state->reset = 0;
    func_00133340(handle + offset, table[a0 + 1].entry + offset, 0, 0, (short)a2, 0, 1, 0, 0, 1,
                  (s32)(long)func_002B7EA8, (long long)&state->busy);
}
