/* func_L04_0040A3B8 - 516 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file src/levels/shared/L04_0040A3B8-g8.c? (no gp use really;
   default flags probably fine; -g8 not needed), marker removal in
   L04_00402D90.c needed. 508 vs 516 bytes (2 places).
   Whole body matches in order; obj stays in a2 with the plain TImode copy
   `*(Quad*)(obj+0x10) = *(Quad*)D_00189EA0` (qcopy helper puts it in a0: do
   not use qcopy there).
   Remaining 8 bytes: retail does NOT reuse the s1=-1 register for
   `*(s32*)(st+0x314) = -1` in the `if (keep == 0)` block (it emits addiu
   v0,zero,-1 there); cse merges the literal in mine.
   Also retail schedules `sw zero,0x36C` after `sq zero,0(0x2F0)` pair
   differently, and loads D_001B24DC before `sw 0x3A8`. */

#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

extern void func_L04_0040E248(void *, void *);
extern void func_002A7398(void *, int, int);
extern void func_0029F338(void *);
extern u8 *D_L04_001B24DC;
extern u8 *D_L04_001B24E8;
extern u8 D_00189EA0[];

void func_L04_0040A3B8(u8 *obj, int keep) {
    u8 *st = *(u8 **)(obj + 0x68);
    u8 *target;
    u8 *cur;
    s32 none = -1;

    qzero(st + 0x2B0);
    *(f32 *)(st + 0x2B8) = 1.0f;
    qzero(st + 0x290);
    qzero(st + 0x2A0);
    qzero(st + 0x2C0);
    qzero(st + 0x6C0);
    *(Quad *)(obj + 0x10) = *(Quad *)D_00189EA0;
    *(s32 *)(st + 0x76C) = 0;
    *(s32 *)(st + 0x718) = 0;
    *(s16 *)(st + 0x274) = 0;
    st[0x349] = 0;
    *(s32 *)(st + 0x34C) = 0;
    *(s32 *)(st + 0x354) = 0;
    *(s32 *)(st + 0x358) = 0;
    *(s32 *)(st + 0x278) = 0;
    *(s32 *)(st + 0x27C) = 0;
    *(s32 *)(st + 0x300) = 0;
    *(s32 *)(st + 0x304) = 0;
    *(s32 *)(st + 0x308) = 0;
    *(s32 *)(st + 0x30C) = 0;
    *(s32 *)(st + 0x280) = 0;
    *(s32 *)(st + 0x288) = 0;
    *(s32 *)(st + 0x750) = 0;
    *(s32 *)(st + 0x738) = 0;
    *(s32 *)(st + 0x724) = 0;
    *(f32 *)(st + 0x28C) = 90.0f;
    func_L04_0040E248(obj, st);
    *(s32 *)(st + 0x3A8) = 10;
    target = D_L04_001B24DC + (*(s32 *)(st + 0x1DC) << 8);
    *(s32 *)(st + 0x328) = none;
    *(s32 *)(st + 0x330) = none;
    *(s32 *)(st + 0x334) = none;
    *(s32 *)(st + 0x3BC) = none;
    *(s32 *)(st + 0x714) = none;
    *(s32 *)(st + 0x324) = 0;
    *(s32 *)(st + 0x32C) = 0;
    *(s32 *)(st + 0x33C) = 0;
    *(s32 *)(st + 0x338) = 0;
    *(s32 *)(st + 0x38C) = 0;
    *(s32 *)(st + 0x390) = 0;
    *(s32 *)(st + 0x4C4) = 0;
    *(s32 *)(st + 0x3B0) = 0;
    *(s32 *)(st + 0x3AC) = 0;
    *(s32 *)(st + 0x3B4) = 0;
    *(s32 *)(st + 0x360) = 0;
    *(s32 *)(st + 0x364) = 0;
    *(s32 *)(st + 0x368) = 0;
    *(s32 *)(st + 0x4D8) = 0;
    *(s32 *)(st + 0x4DC) = 0;
    if (target != 0) {
        func_002A7398(target, 0, 0);
    }
    *(s16 *)(st + 0x34A) = none;
    qzero(st + 0x2F0);
    *(s32 *)(st + 0x36C) = 0;
    *(s32 *)(st + 0x64C) = 0;
    *(s32 *)(st + 0x70C) = 0;
    if (keep == 0) {
        *(s32 *)(st + 0x3A4) = 0;
        *(s32 *)(st + 0x314) = -1;
        *(s32 *)(st + 0x3B8) = 0;
        *(s32 *)(st + 0x310) = 0;
        *(s32 *)(st + 0x318) = 0;
    }
    for (cur = D_L04_001B24E8; cur != 0; cur = *(u8 **)(cur + 0x28)) {
        s32 kind = *(u16 *)(cur + 0xAA);

        if ((u16)(kind - 0xB3D) < 4 || (s16)kind == 0x27F || (s16)kind == 0x70 || (s16)kind == 0x7A) {
            func_0029F338(cur);
        }
    }
    *(s32 *)(st + 0x388) = 0;
}
