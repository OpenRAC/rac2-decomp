#include "include_asm.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;
extern f32 func_002A7878(f32 a, f32 b);
extern void func_L04_0039FA08(u8 *base, s32 count);
extern void func_L04_0039FEA8(f32 factor);
extern void func_L04_003A1868(u8 *a0, u32 a1, u32 a2);
extern void func_L04_003A19E8(u8 *a0, u32 a1, u32 a2);
extern void func_L04_003A1240(u8 *a0, u32 a1);
extern void func_L04_003A1A48(u8 *dst, u16 *src, s32 count);
extern void func_L04_003A15C0(u32 a0, u32 a1, u32 a2, u32 a3, s32 t0);
extern void func_L04_003A1578(u32 a0, u32 a1, u32 a2);
extern void func_L04_003A02A0(u32 a0, u32 a1, f32 f12, f32 f13, f32 f14,
                              f32 f15);

void func_PAL_L04_003A47C0(u8 *p) {
    u8 *s1 = *(u8 **)(*(u32 *)(p + 0x28) + 0x68);
    f32 x;
    f32 y;
    s32 i;
    s32 j;

    *(u8 *)(*(u32 *)(p + 0x28) + 0xBC) = 0;
    *(u16 *)(*(u32 *)(p + 0x28) + 0x34) |= 1;
    *(u16 *)(*(u32 *)(*(u32 *)(p + 0x28) + 0x24) + 0x46) = 0x12;
    *(u8 *)(s1 + 0x15) = 0x19;
    *(f32 *)(s1 + 0x8) = *(f32 *)(s1 + 0x8) * 0.017453294f;
    *(f32 *)(s1 + 0xC) = *(f32 *)(s1 + 0xC) * 0.0003490659f;
    func_L04_003A15C0(*(u32 *)(p + 0x28), *(u32 *)(p + 0x20),
                      *(u32 *)(p + 0x24), *(u32 *)(p + 0x1C),
                      *(s32 *)(p + 0x18));
    func_L04_003A1578(*(u32 *)(p + 0x28), *(u32 *)(p + 0x1C),
                      *(s32 *)(p + 0x18));
    if (*(s32 *)(s1 + 0x10) == 0) {
        *(u8 *)(*(u32 *)(p + 0x28) + 0x30) = 0xFF;
        func_L04_0039FA08(*(u8 **)(p + 0x8), *(s32 *)(p + 0x0));
        func_L04_0039FEA8(1.0f);
        func_L04_003A1868(*(u8 **)(p + 0x8), *(u32 *)(p + 0xC),
                          *(u32 *)(p + 0x0));
        func_L04_003A19E8(*(u8 **)(p + 0x8), *(u32 *)(p + 0xC),
                          *(u32 *)(p + 0x0));
        func_L04_003A1240(*(u8 **)(p + 0x8), *(u32 *)(p + 0x0));
        func_L04_003A1A48(*(u8 **)(p + 0x8), *(u16 **)(p + 0x10),
                          *(s32 *)(p + 0x0));
        if (*(u8 *)(s1 + 0x14) == 0) {
            for (i = 0; i < *(s32 *)(p + 0x0); i++) {
                for (j = 0; j < 2; j++) {
                    x = *(f32 *)(i * 0x1190 + *(s32 *)(p + 0x8)) +
                        func_002A7878(-6.0f, 6.0f);
                    y = *(f32 *)(i * 0x1190 + *(s32 *)(p + 0x8) + 0x4) +
                        func_002A7878(-6.0f, 6.0f);
                    func_L04_003A02A0(*(u32 *)(p + 0x8), *(u32 *)(p + 0x0),
                                      x, y, 2.0f, 0.2f);
                }
            }
        }
    }
    *(u16 *)(*(u32 *)(p + 0x28) + 0x32) = 0;
    *(u8 *)(*(u32 *)(p + 0x28) + 0x20) = 1;
}


