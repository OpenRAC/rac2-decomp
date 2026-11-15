#include "common.h"

extern void *func_0029EFD0(int);

extern void func_002A0F48(void *);

void *func_L01_003A6280(u8 *arg0, void *arg1, u32 arg2, f32 f12, f32 f13) {
    u8 *s0 = (u8 *)CreateMoby(0x660);
    u8 *a2;

    if (s0 != 0) {
        s0[0x30] = arg0[0x30];
        a2 = *(u8 **)(s0 + 0x68);
        *(u16 *)(s0 + 0x32) = *(u16 *)(arg0 + 0x32);
        s0[0x31] = 1;
        s0[0x20] = 0;
        *(u32 *)(a2 + 0x50) = (u32)arg0;
        *(f32 *)(s0 + 0x2C) = *(f32 *)(*(u32 *)(s0 + 0x24) + 0x24) * f12;
        qcopy((s0 + 0x10), arg1);
        if (arg0 != 0) {
            *(u32 *)(a2 + 0x54) = *(s16 *)(arg0 + 0xAA);
        }
        *(f32 *)(a2 + 0x58) = f13;
        *(u32 *)(a2 + 0x5C) = arg2;
        func_002A0F48(s0);
    }
    return s0;
}
