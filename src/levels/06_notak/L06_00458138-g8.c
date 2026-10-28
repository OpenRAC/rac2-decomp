#include "common.h"

extern float D_L06_001B234C __attribute__((sda));

extern float D_001B2350 __attribute__((sda));

extern int func_0035CBA0(char *, int, int);

extern void func_L06_0045BE30(char *, int, float, float, float, float);

extern int func_003A0948(int, int, char *);

extern void func_00350388(char *);

extern u8 *D_L06_001B281C MACRO_ADDR;
extern u8 *D_L06_001B290C MACRO_ADDR;
extern char D_L06_001B1990[];
extern char D_L06_001B19C8[];
extern char D_L06_001B1A00[];
extern char D_L06_001B1A30[];
extern u8 *D_L06_001FE500[];

extern void func_0026FEB8(char *, ...);
extern int func_001163B0(void);
extern void func_L06_00459B18(char *a0);
extern int func_L06_00459BA8(char *a0, char *a1);
extern void func_L06_00459C38(unsigned char *a0, u8 *a1);

/* Resolves the table entries a spawn record names; returns 1 after reporting a missing one. */
int func_L06_00459D08(u8 *a0, u8 *a1)
{
    s32 i1, i2, i3, i4;
    u8 *e1, *e2;

    i1 = *(s32 *)(a1 + 0x100);
    if (i1 == -1) {
        func_0026FEB8(D_L06_001B1990, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    e1 = D_L06_001FE500[i1];
    *(u8 **)(a1 + 0x118) = e1;
    func_L06_00459B18((char *)e1);
    i2 = *(s32 *)(a1 + 0x134);
    if (i2 == -1) {
        func_0026FEB8(D_L06_001B19C8, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    e2 = D_L06_001FE500[i2];
    *(u8 **)(a1 + 0x138) = e2;
    func_L06_00459B18((char *)e2);
    i3 = *(s32 *)(a1 + 0x108);
    if (i3 == -1) {
        func_0026FEB8(D_L06_001B1A00, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    *(u8 **)(a1 + 0x11C) = D_L06_001B281C + (i3 << 8) + 0x18;
    a0[0xBC] = func_L06_00459BA8((char *)a0, (char *)a1);
    i4 = *(s32 *)(a1 + 0x104);
    if (i4 == -1) {
        func_0026FEB8(D_L06_001B1A30, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    qcopy(a1 + 0xE0, D_L06_001B290C + 0x30 + (i4 << 7));
    qcopy(a1 + 0xD0, a0 + 0x10);
    func_L06_00459C38(a0, a1);
    *(s32 *)(a1 + 0x124) = func_001163B0() % 120;
    if (func_001163B0() & 1)
        *(f32 *)(a1 + 0x130) = 0.3490659f;
    else
        *(f32 *)(a1 + 0x130) = -0.3490659f;
    *(s32 *)(a1 + 0x13C) = 0;
    a1[0x29] = 1;
    return 0;
}
