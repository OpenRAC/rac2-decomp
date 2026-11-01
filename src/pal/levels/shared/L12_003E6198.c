#include "include_asm.h"



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001A8FF0 __attribute__((sda));
extern u8 D_L12_001A63A8[];
extern u8 D_L12_001FEAC0[];
extern void func_L12_0031E1D0(s32, s32, s32);

void func_PAL_L12_003E6620(s32 a0) {
    s32 s0 = a0;
    s32 s1 = *(u32 *)(s0 + 0x68);
    s32 v = *(s32 *)(*(u32 *)(s1 + 0x294));

    if (v != -1) {
        s32 base = D_L12_001B2E9C;
        u8 *p = (u8 *)((u32)base + (v << 8));

        if (p != 0) {
            u8 t = *(u8 *)(p + 0x20);

            if (t != 0xFE) {
                if (t != 0xFD) {
                    if (v != ((s0 - base) >> 8))
                        return;
                }
            }
        }
    }
    func_L12_0031E1D0(s0, 0xF, 5);
    {
        s32 i = (s0 - D_L12_001B2E9C) >> 8;

        *(u16 *)(s1 + 0x29C) = 0xFA;
        *(s32 *)(*(u32 *)(s1 + 0x294)) = i;
    }
}

