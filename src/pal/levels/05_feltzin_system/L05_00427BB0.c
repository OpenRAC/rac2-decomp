#include "include_asm.h"


typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
extern s32 func_003062A0(u8 *a0);
extern s32 func_0030CBA8(s32 a0);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern s32 func_00379860(u8 *a0);
extern s32 func_0037B3A0(u8 *a0);
extern s32 func_00332AF8(s32 a0, s32 a1);
extern u32 *func_00379CA0(u8 *a0);
extern void func_0037AEC0(u8 *a0, s32 a1);
extern void func_00379C68(u8 *a0, s32 a1);
extern u8 *func_0037B440(s32 a0);
extern void func_L05_004224C8(u8 *a0);
extern s32 D_001B1364 __attribute__((sda));
extern s32 D_001B13E4 __attribute__((sda));
extern u8 D_L05_00221D10[];
extern u8 D_L05_001B3550[];
extern s32 D_L05_001B2048;
extern u8 *D_001B2614;
extern u8 D_L05_001B1354[];
extern u8 D_L05_001B1358[];
extern u8 D_L05_001B135C[];
extern u8 D_L05_001495B8[];
extern u8 *D_L05_0020B220[];
extern u8 *D_001B251C;
extern s32 D_001B1350 __attribute__((sda));

void func_PAL_L05_00427CF8(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);

    *(u16 *)(arg0 + 0x34) |= 0x100;
    arg0[0x20] = 1;
    *(s32 *)((u8 *)func_00379CA0(arg0) + 0x148) = 0xA;
    func_0037AEC0(arg0, 1);
    *(s32 *)(s1 + 0x26C) = 0;
    *(s32 *)(s1 + 0x268) = 0;
    *(f32 *)(s1 + 0x230) = 10.0f;
    func_00379C68(arg0, 0xFFFF);
}

