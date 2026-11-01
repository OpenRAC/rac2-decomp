#include "include_asm.h"

#include "common.h"
extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 D_L07_001B0F84 __attribute__((sda));
extern u8 *D_L07_001B22DC __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 D_L07_001B10B8 __attribute__((sda));
extern f32 D_L07_001B10BC __attribute__((sda));
extern u32 D_L07_001B10C0 __attribute__((sda));
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern f32 D_L07_001B0E98 __attribute__((sda));
extern f32 D_L07_001B0E9C __attribute__((sda));
extern f32 D_L07_001B0EA0 __attribute__((sda));
extern f32 func_002AA2E8(f32 *value, f32 target, f32 step);
extern void func_002A7750(u8 *a, u8 b, s32 c);
extern f32 func_00283B98(f32 a, f32 b);
extern s32 func_L01_003120A8(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern f32 D_L07_001B173C;
extern u8 D_L07_001B1730 __attribute__((sda));
extern u16 **D_L07_001A9014;
extern u8 *D_L07_001B2954;
extern u8 *D_L07_001B295C;
extern s32 D_L07_001B1E90;
extern u8 *func_L00_002D70A0(s32);
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 D_L07_001B17D4 __attribute__((sda));
extern f32 D_L07_001B17D8 __attribute__((sda));
extern u8 *D_L07_001B9250 __attribute__((nosda));
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern u8 D_L07_001B31A9;
extern u8 D_00189E20[];
extern u32 D_L07_001B1E08 MACRO_ADDR;
extern f32 func_00282E48(u8 *a, u8 *b);
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern char D_00189EA0[];
extern char D_L07_001B9200[];
extern u8 *D_L07_001C36C0[];
extern int func_00277F48(void *, float, int, char *, void *);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002A8C28(char *, char *, int, float, float, float, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_0032F3B8(char *, char *, char *, float);
extern void func_PAL_L07_003FB4A0(u8 *a);
extern void func_PAL_L07_003FB570(u8 *self, float *target);
extern void func_PAL_L07_003FB6B0(u8 *a0);

void func_PAL_L07_003FB110(u8 *a0)
{
    u8 *state;
    u8 *p;
    char *pos;
    char *tune;
    f32 dir[4];
    s32 n, k;

    state = *(u8 **)(a0 + 0x68);
    if (a0[0x20] != 1)
        func_PAL_L07_003FB4A0(a0);
    switch (a0[0x20]) {
    case 2:
        *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24) * D_L07_001B0FD0;
        func_PAL_L07_003FB570(a0, (float *)D_00189EA0);
        func_PAL_L07_003FB6B0(a0);
        n = func_00277F48(a0 + 0x10, 0.333f, 0, (char *)a0, 0);
        if (n > 0) {
            p = (u8 *)D_L07_001C36C0;
            for (k = n; k != 0; k--, p += 4) {
                u8 *other = *(u8 **)p;
                if (other == a0)
                    continue;
                if (other != *(u8 **)(a0 + 0xB8))
                    func_002A7750(a0, 3, -1);
            }
        }
        break;
    case 3:
        func_002E5DA0(6, 0, (char *)a0, 0xE5F);
        pos = (char *)a0 + 0x10;
        func_002A8C28((char *)a0, pos, 0x10000, 6.0f, 5.0f, 1.0f, 0, 1, 0);
        func_002A8C28((char *)a0, pos, 1, 4.0f, (f32)state[0x34], 1.0f, 0, 1, 0);
        func_00282CF0(dir, D_L07_001B9200, pos);
        func_00282F20(dir, dir, 1.0f);
        func_PAL_0032F3B8((char *)a0, pos, (char *)dir, 0.0f);
        tune = D_L07_001B9200 - 0x140;
        *(f32 *)(tune + 0x180) = 0.1f;
        *(s32 *)(tune + 0x188) = 0x4B;
        *(f32 *)(tune + 0x160) = 0.2f;
        *(s32 *)(tune + 0x168) = 0x32;
        *(s32 *)(tune + 0x16C) = 0;
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(a0, 1, -1);
        break;
    }
}
