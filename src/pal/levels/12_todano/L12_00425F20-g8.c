#include "include_asm.h"

#include "common.h"
extern f32 D_L12_001B1F50[] SDATA(D_L12_001B1F50);
extern f32 D_L12_001B1F58[] SDATA(D_L12_001B1F58);
extern f32 D_L12_001B1F60[] SDATA(D_L12_001B1F60);
extern s32 D_L12_001B1FA0 __attribute__((sda));
extern f32 D_L12_001B1FB0 __attribute__((sda));
extern f32 D_L12_001B1FB4 __attribute__((nosda));
extern f32 D_L12_001B1FB8 __attribute__((nosda));
extern char D_L12_001B1F80[];
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern s32 func_002E5CF8(s32, s32, s32);
extern void func_0029F338(void *);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, unsigned char, int);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern s32 D_L12_001B29C8 __attribute__((sda));
extern u8 *D_L12_001B090C __attribute__((nosda));
extern u8 *D_L12_001B1360 __attribute__((nosda));
extern s32 D_L12_001B22D0 __attribute__((sda));
extern f32 D_L12_001B2280[] SDATA(D_L12_001B2280);
extern f32 D_L12_001B2288[] SDATA(D_L12_001B2288);
extern f32 D_L12_001B22B0[] SDATA(D_L12_001B22B0);
extern u8 *func_0029EFD0(int);

void func_PAL_L12_004264C8(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    f32 pos[4];

    switch (a0[0x20]) {
    case 0:
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) != 0 && *s == 0) {
            func_002A7750(a0, 2, -1);
            func_002E5CF8(0, 0, (s32)a0);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C328(a0, D_L12_001B1F60, D_L12_001B1F58, D_L12_001B1F50, 0xFFFF, 0,
                          D_L12_001B1FA0, 0, 1, 0xFF, 0);
        func_PAL_L00_0032C328(a0, D_L12_001B1F80, D_L12_001B1F58, D_L12_001B1F50, 0xFFFF, 0,
                          D_L12_001B1FA0, 1, 0x1FE, 0xFF, 0);
        func_L00_00324F18(a0, pos, D_L12_001B1FB0, D_L12_001B1FB4, D_L12_001B1FB8);
        func_PAL_L00_003FB330(pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(f32 *)(a0 + 0x2C) * 20.0f, 20.0f,
                      1, 0, 1, 0);
        func_0029F338(a0);
        break;
    }
}
