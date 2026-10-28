/* func_L13_0041A398 - 440 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file L13_0041A398-g8.c, flags `-O2 -G8 -ffunction-sections
   -frac2-qcopy` (gp ints D_L13_001B1618/1630/1628/1634, gp = 0x1AEFF0;
   func_00283DB8 call constant is 52.0f). 444 B vs 440, ~34 diff lines,
   structure and callees all right.
   Left: retail `lq` of the pos precedes the lui/mtc1 of 52.0f; case 0 store
   order (retail swc1 0x624, sh 0xA, sh 8 in the b delay slot; permutations
   tried, best 34); case 3 end: retail jumps `b +5` over the reload of 0x12
   after `sh v0,0x10`; draft falls through. */

#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_L13_001B1618 __attribute__((sda));
extern s32 D_L13_001B1630 __attribute__((sda));
extern s32 D_L13_001B1628 __attribute__((sda));
extern s32 D_L13_001B1634 __attribute__((sda));
extern s32 func_00283DB8(void *a0, f32 f12);
extern s32 func_00282978(void *a0);
extern void func_L13_0041A550(u8 *a0);
extern void func_L13_0041AB30(u8 *a0);
extern void func_L00_002E6EF8(void *a0, u8 *a1);
extern u8 func_L13_0041AD00[];

typedef struct {
    f32 f[4];
} __attribute__((aligned(16))) L13_Quad;

void func_L13_0041A398(u8 *self)
{
    u8 *state;
    s32 one;
    L13_Quad v;

    state = *(u8 **)(self + 0x68);
    if (self[0x20] != 0) {
        *(TI128 *)&v = *(TI128 *)(self + 0x10);
        v.f[3] = *(f32 *)(state + 0x624);
        if (func_00283DB8(&v, 52.0f) < 0)
            return;
    }
    if (*(s32 *)(state + 0x628) == 0)
        return;
    one = 1;
    switch (self[0x20]) {
    case 0:
        func_L13_0041A550(self);
        *(u16 *)(state + 0x10) = *(u16 *)(state + 0xC);
        self[0x20] = 2;
        *(f32 *)(state + 0x624) = 2.5f;
        *(s16 *)(state + 0xA) = one;
        *(s16 *)(state + 8) = one;
        return;
    case 1:
        if (D_L13_001B1618 != 0 && *(s16 *)(state + 0x12) == 0) {
            D_L13_001B1618 = D_L13_001B1618 - 1;
            func_L13_0041A550(self);
        }
        break;
    case 2:
        if (func_00282978(state + 0x10) != 0) {
            self[0x20] = 3;
            *(u16 *)(state + 0x10) = *(u16 *)(state + 4);
            func_L13_0041A550(self);
        }
        break;
    case 3:
        if (func_00282978(state + 0x10) != 0) {
            if (*(s16 *)(state + 6) == 0)
                *(s16 *)(state + 0x10) = 5;
            else
                self[0x20] = 2;
        }
        break;
    }
    if (*(s16 *)(state + 0x12) == 0)
        func_L13_0041A550(self);
    if (*(s16 *)(state + 0x12) != 0) {
        if (D_L13_001B1630 == 0)
            func_L13_0041AB30(self);
        if (D_L13_001B1628 < *(s16 *)(state + 0x12) && D_L13_001B1634 == 0)
            func_L00_002E6EF8(func_L13_0041AD00, self);
    }
}
