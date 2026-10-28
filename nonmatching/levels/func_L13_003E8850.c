/* func_L13_003E8850 - 440 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file L13_003E8850.c, flags `-O2 -G0 -ffunction-sections` (all data is
   boot data D_00189E20/EA0, 18C750, 13F5B8, 1A7390/7A64/903C as incomplete
   sda arrays for the tied abs form). 432 vs 440 B; structure decoded
   completely (state machine on state.h[0xE]: 0 / 1 / other, then the common
   func_002ACBC8(D_00189EA0, state.w[0]) block).
   Left: retail dispatch is `beqz h -> case0; beq h,1 -> case1; else common`
   with likely branches (bnel + delay lw a1,8(s2)); draft inverts (bnez
   first). Retail reaches hero fields as D_00189EA0+0x221C in case 0 and
   D_00189E20+0x2294 via a separately built base (addiu v0,v0,-0x61E0) in case
   1; s3 holds hi(0x190000) for the common call. */

#include "include_asm.h"
#include "common.h"

extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern u8 D_0018C750[];
extern u8 D_0013F5B8[];
extern u32 D_001A7390[] __attribute__((sda));
extern u8 D_001A7A64[] __attribute__((sda));
extern s32 D_001A903C[] __attribute__((sda));
extern s32 D_0018CC18;
extern s32 func_002ACBC8(void *a0, s32 a1);
extern void func_002E5E58(s32 a0, s32 a1, s32 a2);
extern void func_002B0A18(s32 a0, s32 a1);
extern void func_00288E18(s32 a0, s32 a1);

void func_L13_003E8850(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    s16 h;

    if (self[0x20] == 0) {
        self[0x30] = 0xFF;
        *(s16 *)(state + 0xC) = 0;
        self[0x20] = 1;
    }
    if (self[0x20] != 1)
        return;
    h = *(s16 *)(state + 0xE);
    switch (h) {
    case 0:
        if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 4)) != 0 && *(s32 *)(D_00189EA0 + 0x221C) == 0xF)
            *(s16 *)(state + 0xE) = 1;
        break;
    case 1:
        if (*(s32 *)(D_00189E20 + 0x2294) == 0x3E) {
            *(s16 *)(state + 0xE) = 0;
        } else if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 8)) != 0 && D_001A7A64[0] == 0) {
            func_002E5E58(1, 0, 0);
            D_001A7A64[0] = 1;
            func_002B0A18(0x1233, -1);
            D_001A903C[0] = 1;
        }
        break;
    }
    if (func_002ACBC8(D_00189EA0, *(s32 *)state) == 0)
        return;
    if (*(u16 *)(D_0018C750 + 0x1BC) != 0 && !(D_001A7390[0] - *(u32 *)(D_0018C750 + 0x1C0) > 0x69780))
        return;
    if (D_0013F5B8[0x7E] < 2 && *(s16 *)(state + 0xC) == 0) {
        if (D_0018CC18 >= 0)
            func_00288E18(0x9E3, 0x3A);
        D_0013F5B8[0x7E] = D_0013F5B8[0x7E] + 1;
        *(s16 *)(state + 0xC) = 1;
    }
}
