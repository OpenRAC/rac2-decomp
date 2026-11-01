#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
extern void func_002A7750(char *, int, int);
extern void func_PAL_L20_003A1538(char *);
extern void func_PAL_L20_003A16B8(char *);
extern s32 func_002B3868(char *);
extern void func_PAL_002A7E68(char *, s32, s32, s32);
extern void func_0029FCC0(char *, s32, char *);
extern void func_0029FC20(char *, s32, char *);
extern void func_00282F20(char *, char *, float);
extern void func_PAL_L09_003B20E8(char *, char *, char *, s32, s32, float, float, float, float);
extern void func_00282CF0(char *, void *, char *);
extern void func_PAL_0032F3B8(char *, char *, char *, float);
extern void func_PAL_002A7650(char *, s32, s32);
extern void func_0029F338(char *);
extern int D_L20_001A8F00;
extern int D_L20_001BDCF0 __attribute__((nosda));
extern int D_L20_001B2AC8;
extern void *D_L20_001B9FC0[];
extern float D_L20_001AED04 __attribute__((sda));
extern float D_L20_001AED08 __attribute__((sda));
extern u8 D_0019B2E8[] __attribute__((nosda));
extern u8 D_L20_001B2DE0[] __attribute__((nosda));
extern s32 D_001A79F0 __attribute__((sda));

void func_PAL_L20_003A12B0(char *arg0)
{
    char bufA[0x10];
    char bufB[0x40];
    char bufC[0x10];
    char *state;

    state = *(char **)(arg0 + 0x68);
    func_PAL_L20_003A1538(arg0);
    if (D_L20_001A8F00 == 2 && D_L20_001BDCF0 >= 5) {
        func_0029F338(arg0);
        return;
    }
    switch (*(u8 *)(arg0 + 0x20)) {
    case 2:
        if (func_002B3868(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 0)
            func_PAL_002A7E68(arg0, 0, 0, 0x8);
        if (*(u8 *)(arg0 + 0x31) != 0 && *(u16 *)(arg0 + 0x96) >= 0x97)
            func_002A7750(arg0, 3, -1);
        break;
    case 3:
        if (func_002B3868(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 1)
            func_PAL_002A7E68(arg0, 1, 0, 0xC);
        if ((D_L20_001B2AC8 & 0xF) == (((int)arg0 >> 8) & 0xF)) {
            func_0029FCC0(arg0, 2, bufA);
            func_0029FC20(arg0, 2, bufB);
            func_00282F20(bufC, bufB, D_L20_001AED04 * 0.020000001f);
            func_PAL_L09_003B20E8(bufA, arg0, bufC, 1, 1, (float)*(u8 *)(state + 0x34),
                              D_L20_001AED08, 1.0f, 1.0f);
        }
        if (*(u8 *)(arg0 + 0x31) == 0 || *(u16 *)(arg0 + 0x96) >= 0x97)
            func_002A7750(arg0, 2, -1);
        break;
    case 4:
        if (func_002B3868(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 2)
            func_PAL_002A7E68(arg0, 2, 0, 0x8);
        if (*(u8 *)(arg0 + 0x60) & 0x2)
            func_002A7750(arg0, 2, -1);
        break;
    case 5:
        func_00282CF0(bufA, D_L20_001B9FC0, arg0 + 0x10);
        func_00282F20(bufA, bufA, 1.0f);
        func_PAL_0032F3B8(arg0, arg0 + 0x10, bufA, 0.0f);
        func_PAL_002A7650(arg0, 0, 3);
        func_0029F338(arg0);
        return;
    default:
        break;
    case 1:
        return;
    }
    func_PAL_L20_003A16B8(arg0);
}
