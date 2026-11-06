/*
 * func_PAL_L13_0041F0C0, the PAL copy of func_L13_0041A398: the same C, with the
 * 50 Hz scale on the two timers stored at state + 0x10, and 4 where v1.01 has 5.
 */
#include "common.h"

extern s32 D_L13_001B1618 __attribute__((sda));
extern s32 D_L13_001B1630 __attribute__((sda));
extern s32 D_L13_001B1628 __attribute__((sda));
extern s32 D_L13_001B1634 __attribute__((sda));
extern s32 func_00283DB8(void *a0, f32 f12);
extern s32 func_00282978(void *a0);
extern void func_PAL_L13_0041F2B8(u8 *a0);
extern void func_L13_0041AB30(u8 *a0);
extern void func_L00_002E6EF8(void *a0, u8 *a1);
extern u8 func_L13_0041AD00[];

typedef struct {
    f32 f[4];
} __attribute__((aligned(16))) L13_Quad;

void func_PAL_L13_0041F0C0(u8 *self)
{
    u8 *state;
    s32 one;
    L13_Quad v;

    state = *(u8 **)(self + 0x68);
    if (self[0x20] != 0) {
        qcopy(&v, self + 0x10);
        v.f[3] = *(f32 *)(state + 0x624);
        if (func_00283DB8(&v, 52.0f) < 0)
            return;
    }
    if (*(s32 *)(state + 0x628) == 0)
        return;
    one = 1;
    switch (self[0x20]) {
    case 0:
        func_PAL_L13_0041F2B8(self);
        *(u16 *)(state + 0x10) = (*(s32 *)(state + 0xC) * 5 + 2) / 6;
        self[0x20] = 2;
        *(f32 *)(state + 0x624) = 2.5f;
        *(s16 *)(state + 8) = one;
        *(s16 *)(state + 0xA) = one;
        break;
    case 1:
        if (D_L13_001B1618 != 0 && *(s16 *)(state + 0x12) == 0) {
            D_L13_001B1618 = D_L13_001B1618 - 1;
            func_PAL_L13_0041F2B8(self);
        }
        break;
    case 2:
        if (func_00282978(state + 0x10) != 0) {
            self[0x20] = 3;
            *(u16 *)(state + 0x10) = ((int)(*(s16 *)(state + 4)) * 5 + 2) / 6;
            func_PAL_L13_0041F2B8(self);
        }
        break;
    case 3:
        if (func_00282978(state + 0x10) != 0) {
            if (*(s16 *)(state + 6) != 0)
                self[0x20] = 2;
            *(s16 *)(state + 0x10) = 4;
        } else if (*(s16 *)(state + 0x12) == 0) {
            func_PAL_L13_0041F2B8(self);
        }
        break;
    }
    if (*(s16 *)(state + 0x12) != 0) {
        if (D_L13_001B1630 == 0)
            func_L13_0041AB30(self);
        if (D_L13_001B1628 < *(s16 *)(state + 0x12) && D_L13_001B1634 == 0)
            func_L00_002E6EF8(func_L13_0041AD00, self);
    }
}
