#include "common.h"

extern u8 D_00188660[];
extern u8 *D_L01_001B255C MACRO_ADDR;
extern u8 *D_L01_001FE180[];
extern f32 D_L01_001B0540 __attribute__((sda));

extern s32 func_L01_00337888(u8 *object, u8 *entry, void *out, s32 current, s32 direction, f32 step);
extern s32 func_002E5CF8(s32 a0, s32 a1, void *a2);
extern void func_0029F338(void *a0);
extern void func_00282CF0(void *a0, void *a1, void *a2);
extern void func_002AD6F0(void *a0, void *a1, void *a2, void *a3);

void func_L01_003D26C0(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    u8 *os = *(u8 **)(*(u8 **)(state + 0x70) + 0x68);
    u8 *tbl;
    u8 *link;
    f32 tmp[4];

    *(f32 *)(self + 0x2C) = *(f32 *)(*(u8 **)(self + 0x24) + 0x24) * D_L01_001B0540;
    qcopy(state + 0x60, self + 0x10);
    tbl = D_L01_001FE180[*(s32 *)(state + 0x74)];
    *(s32 *)(state + 0x78) =
        func_L01_00337888(self, tbl, self + 0x10, *(s32 *)(state + 0x78), 1,
                          *(f32 *)(os + 0x20) * 0.016666668f);
    if (*(f32 *)(self + 0x18) < *(f32 *)(state + 0x68)) {
        if (!(*(u16 *)(state + 0x7C) & 0x80)) {
            func_002E5CF8(1, 0, self);
            *(u16 *)(state + 0x7C) = *(u16 *)(state + 0x7C) | 0x80;
        }
        D_L01_001B255C[(*(s32 *)(*(u8 **)(*(u8 **)(state + 0x70) + 0x68) + 0xC) << 8) + 0xBC] = 1;
    }
    link = D_00188660 + *(s16 *)(state + 0x7E) * 0x70;
    if (*(u8 **)(link + 0x88) != self || link[0x74] == 0)
        *(s16 *)(state + 0x7E) = func_002E5CF8(0, 4, self);
    if (*(s32 *)(state + 0x78) == *(s32 *)tbl - 1) {
        D_L01_001B255C[(*(s32 *)(*(u8 **)(*(u8 **)(state + 0x70) + 0x68) + 0xC) << 8) + 0xBC] = 0;
        func_0029F338(self);
    } else {
        func_00282CF0(tmp, self + 0x10, state + 0x60);
        func_002AD6F0(state + 0x20, tmp, self + 0xF0, self + 0xF0);
        qcopy(state + 0x60, self + 0x10);
    }
}
