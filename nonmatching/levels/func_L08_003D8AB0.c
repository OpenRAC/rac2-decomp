/* func_L08_003D8AB0 - 504 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file L08_003D8AB0-qcopy.c, flags `-O2 -G0 -ffunction-sections
   -frac2-qcopy` (the TI copy `*(TI128 *)dst = *(TI128 *)(state+0x3E0)` gets
   its address reg $s2 from the transformer).
   12 real diff lines (rest is reloc names). Left: (1) block E (random angles,
   ends in func_00282CC0(dst,dst,ent+0x10)) must use $s2 for a0/a1 (retail
   `daddu a0,s2`), draft uses $s1 (cse merges the copy);
   (2) beq v1,-1 delay slot holds `addiu v1,s0,0x3E0` in retail (nop in
   draft), (3) lw 0x404 sits before the mul.s/sw zero in retail. */

#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001FE7BC;
extern u8 D_00189EA0[];
extern s32 func_001163B0(void);
extern s32 func_L01_003165E8(void *a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern void func_L01_00337A60(void *a0, void *a1, void *a2, s32 a3);
extern f32 func_002A7878(f32 a0, f32 a1);
extern f32 func_00283180(f32 a0);
extern f32 func_00283198(f32 a0);
extern void func_00282CC0(void *a0, void *a1, void *a2);

void func_L08_003D8AB0(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *pos;
    u8 *dst;

    if (*(s32 *)(state + 0x428) == -1) {
        u8 *tbl = D_L08_001FE7BC;

        func_L01_00337A60(state + 0x3F0, state + 0x3F0, tbl + 0x10, *(s32 *)tbl);
        return;
    }
    pos = state + 0x3F0;
    dst = pos;
    if (func_L01_003165E8(pos, *(s32 *)(state + 0x428), -1, -1, -1) != 0)
        return;
    if ((func_001163B0() & 1) || *(s32 *)(state + 0x254) == 2 || *(s32 *)(state + 0x44C) != 0) {
        if (*(s32 *)(state + 0x404) != -1 && (func_001163B0() & 1)) {
            *(TI128 *)dst = *(TI128 *)(state + 0x3E0);
            return;
        }
        *(f32 *)(state + 0x3F0) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
        *(f32 *)(state + 0x3F4) = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
        *(s32 *)(state + 0x3F8) = 0;
        func_00282CC0(dst, dst, (u8 *)D_L08_001B29DC + (*(s32 *)(state + 0x404) << 8) + 0x10);
    } else {
        *(f32 *)(state + 0x3F0) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
        *(f32 *)(state + 0x3F4) = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
        *(s32 *)(state + 0x3F8) = 0;
        func_00282CC0(pos, pos, D_00189EA0);
    }
}
