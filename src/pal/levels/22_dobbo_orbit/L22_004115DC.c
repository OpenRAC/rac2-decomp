#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L22_004115DC);

INCLUDE_ASM("asm/pal/levels", func_PAL_L22_004123B0);

#include "common.h"
extern s32 func_002A77E0(s32 a0);
extern s32 func_002E5DA0(s32 a0, s32 a1, char *a2, s32 a3);
extern s32 func_002E5CF8(s32 a0, s32 a1, char *a2);
extern int func_002A77E0(int);
extern u8 *D_0018C0B0;
extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));
extern s32 D_L22_0018B6A8 __attribute__((sda));
extern s32 func_00282948(s32);
extern void func_00282978();
extern void func_00283898(s32, s32, f32);
extern f32 func_00283BE0(f32, f32);
extern void func_0029F978(s32, s32, s32);
extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern u8 *D_0018C0B0;

/* func_L22_0040C888 is in L22_0040C888-g8.c. */

/* func_L22_0040D638 lives in L22_00358778-state-g8.c. */

void func_PAL_L22_00412818(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(u32 *)(s1 + 0x68);

    func_00282948(s0 + 0x258);
    func_00282978(s0 + 0x25C);
    if (*(u16 *)(s1 + 0x96) <= 0xFFFE)
        *(u16 *)(s1 + 0x96) = *(u16 *)(s1 + 0x96) + 1;
    if (*(u8 *)(s0 + 0x211) == 0)
        func_0029F978(s1, 7, s0 + 0x210);
    func_00283898(s0 + 0x220, 2, *(f32 *)(s0 + 0x26C));
    *(f32 *)(s0 + 0x26C) = func_00283BE0(*(f32 *)(s0 + 0x26C), 0.49916422f);
}


extern void func_00282F20(void *, void *, float);
extern s32 func_2F36F0(s32);
extern f32 func_2F4AD0(f32, f32);
extern void func_00282F20(void *, void *, float);
extern void func_0029FCC0(void *, s32, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282F20(void *, void *, f32);

void func_PAL_L22_004128B8(u8 *a0, f32 *a1, f32 f12) {
    f32 vec1[4] __attribute__((aligned(16)));
    f32 vec2[4] __attribute__((aligned(16)));
    f32 scale = f12;

    if (D_L22_001AF314[0] != 0 && *(f32 *)(*(u8 **)(D_L22_001AF314[0] + 0x68) + 0x20) <= 0.0f) {
        return;
    }
    func_0029FCC0(a0, 2, vec1);
    if (scale == 0.0f) {
        scale = D_L22_001B2A98;
    }
    func_00282CF0(vec2, a1, vec1);
    func_00282F20(vec2, vec2, 0.8000001f);
    func_PAL_L22_00412B98(vec1, vec2, &scale);
    func_0029FCC0(a0, 3, vec1);
    func_00282CF0(vec2, a1, vec1);
    func_00282F20(vec2, vec2, 0.8000001f);
    func_PAL_L22_00412B98(vec1, vec2, &scale);
}


extern void func_L22_003300E8();
extern void func_00282CC0(void *, void *, void *);
extern void func_L02_00332630(s32, s32);
extern void func_L22_003A2988(void *, f32);

void func_PAL_L22_004129D8(s32 a0, s32 a1, s32 a2, f32 f12) {
    u8 buf[0x10];
    u8 buf2[0x10];
    f32 v = f12;

    func_00282CF0(buf, (void *)a1, (void *)(a0 + 0x10));
    v = v * 0.020000001f;
    func_00282F20(buf, buf, v);
    if (a2 != 0) {
        func_00282CC0(buf2, (void *)(a0 + 0x10), buf);
        func_L22_003A2988(buf2, 7.2f);
        func_00282CF0(buf, buf2, (void *)(a0 + 0x10));
        func_00282F20(buf, buf, v);
    }
    func_L02_00332630(a0, a1);
    func_L22_003300E8(a0, buf);
}

