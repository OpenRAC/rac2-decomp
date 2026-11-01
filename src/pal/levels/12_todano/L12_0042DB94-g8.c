#include "include_asm.h"

#include "common.h"
extern f32 D_L12_001B1F50[] SDATA(D_L12_001B1F50);
extern f32 D_L12_001B1F58[] SDATA(D_L12_001B1F58);
extern f32 D_L12_001B1F60[] SDATA(D_L12_001B1F60);
extern s32 D_L12_001B1FA0 __attribute__((sda));
extern f32 D_L12_001B1FB0 __attribute__((sda));
extern f32 D_L12_001B1FB4 __attribute__((nosda));
extern f32 D_L12_001B1FB8 __attribute__((nosda));
extern void func_002A7750(void *, int, int);
extern s32 func_002E5CF8(s32, s32, s32);
extern void func_0029F338(void *);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, unsigned char, int);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern s32 D_L12_001B29C8 __attribute__((sda));
extern u8 *D_L12_001B090C __attribute__((nosda));
extern u8 *D_L12_001B1360 __attribute__((nosda));
extern s32 D_L12_001B22D0 __attribute__((sda));
extern f32 D_L12_001B2280[] SDATA(D_L12_001B2280);
extern f32 D_L12_001B2288[] SDATA(D_L12_001B2288);
extern f32 D_L12_001B22B0[] SDATA(D_L12_001B22B0);
extern int func_002A7820(int, int);
extern int func_PAL_00273A10(unsigned char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E5DA0(int, int, void *, int);
extern u8 *func_0029EFD0(int);
extern void func_00282AB0(void *, void *, int);

void func_PAL_L12_0042EE58(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    s32 life;
    u8 *obj;
    u16 flags;
    f32 v[4];

    int state = a0[0x20];

    switch (state) {
    case 0:
        *(s16 *)((u8 *)s + 0x34) = ((s32)(func_002A7820(20, 50)) * 5 + 2) / 6;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        life = *(s16 *)((u8 *)s + 0x34);
        if (life < 0 || func_PAL_00273A10(a0)) {
            func_00283098(v, (u8 *)s + 0x20, a0 + 0xC0);
            obj = 0;
            func_00282CC0(v, a0 + 0x10, v);
            func_PAL_L00_003FB330(v, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, state, state, 0, 0);
            func_002E5DA0(2, 0, a0, 0x12B1);
            flags = *(u16 *)(a0 + 0x7C);
            if (flags & 1)
                obj = func_0029EFD0(0x12E0);
            else if (flags & 2)
                obj = func_0029EFD0(0x12E1);
            else if (flags & 4)
                obj = func_0029EFD0(0x12E2);
            if (obj != 0) {
                qcopy(obj + 0x10, v);
                *(f32 *)(obj + 0x2C) = *(f32 *)(*(u8 **)(obj + 0x24) + 0x24) *
                                       (*(f32 *)(a0 + 0x2C) / *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24));
                func_00282AB0(obj + 0xC0, a0 + 0xC0, 0x18);
                func_PAL_L00_0032C328(obj, D_L12_001B22B0, D_L12_001B2288, D_L12_001B2280, 0xFF, -1,
                                  D_L12_001B22D0, 0xF, 0xFF, 0xFF, 0);
                func_0029F338(obj);
            }
            func_0029F338(a0);
        } else {
            *(s16 *)((u8 *)s + 0x34) = life - 1;
        }
        break;
    }
}
