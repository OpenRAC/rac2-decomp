#include "include_asm.h"



INCLUDE_ASM("asm/pal/levels", func_PAL_L10_003AF110);



typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
extern u32 *func_0037BA88(u8 *arg0);
extern s32 func_003351C0(s32 mode);
extern s32 func_003737B8(s32 a, s32 b, u8 *c, s32 d);
extern void func_0037CCB0(u8 *arg0, s32 a1);
extern f32 func_00335320(void);
extern u8 *func_0037B670(u8 *arg0);
extern s32 func_003062A0(u8 *a0);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_00335200(s32 a0, s32 a1);
extern f32 func_00309138(f32 f12);
extern f32 func_00309120(f32 f12);
extern s32 func_L05_0037B538(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_002E5DA0(s32 index, s32 value, u8 *object, s32 kind);
extern s32 func_0037D6E0(u8 *a0);
extern u8 *D_L10_0020B1E0[];
extern u8 *D_001B251C;
extern u8 D_L10_00265BA0[];
extern u8 D_L10_00188660[];
extern u8 D_L10_00221CD0[];
extern u8 D_00188660[];
extern s32 D_001B0F44 __attribute__((sda));
extern s32 D_001B0F48 __attribute__((sda));

void func_PAL_L10_003FA370(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    u8 *s2 = (u8 *)func_0037BA88(arg0);

    *(s32 *)(s2 + 0x148) = 2;
    func_0037CCB0(arg0, 1);
    *(f32 *)(s1 + 0x180) = 2.0f;
    arg0[0x20] = 1;
    arg0[0x30] = 0xFF;
    *(u16 *)(arg0 + 0x32) = 0x1FF;
    *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) | 0x100;
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(*(u8 **)(arg0 + 0x24) + 0x24) * 4.1f;
    *(s32 *)(s2 + 0x14C) = 0;
    *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) & 0xEFFF;
}

