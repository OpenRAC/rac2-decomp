#include "include_asm.h"


typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));
extern s32 D_L22_0018B6A8 __attribute__((sda));
extern s32 func_2F36F0(s32);
extern void func_L22_003E87B8(s32, s32, s32);

void func_PAL_L22_003ECA58(s32 a0) {
    s32 x = *(u32 *)(a0 + 0x68);

    func_L22_003E87B8(a0, x, x);
    *(u8 *)(a0 + 0x30) = 0xFF;
}

