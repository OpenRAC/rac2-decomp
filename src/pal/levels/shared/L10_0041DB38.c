#include "include_asm.h"


typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
extern s32 func_002ED688(u8 *);
extern void func_PAL_L05_0037D610(char *, int);
extern void func_PAL_002EF708(unsigned char *);

/* Restores the flying object's state and its linked motion record. */
void func_PAL_L10_0041DEA0(u8 *self) {
    char *state = *(char **)(self + 0x68);
    char *motion = (char *)func_002ED688(self);
    *(s32 *)(motion + 0x148) = 10;
    func_PAL_L05_0037D610((char *)self, 1);
    *(float *)(state + 0x180) = 10.0f;
    self[0x20] = 1;
    self[0x30] = 255;
    *(u16 *)(self + 0x32) = 511;
    *(u16 *)(self + 0x34) |= 0x100;
    *(float *)(self + 0x2C) = 0.07999999821186066f;
    *(s32 *)(state + 0x268) = 0;
    *(s32 *)(state + 0x26C) = -1;
    func_PAL_002EF708(self);
}

