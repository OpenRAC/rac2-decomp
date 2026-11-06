#include "include_asm.h"

/* func_US2_L05_00421A98, the v2.00 copy of func_L05_0041FE98: the same C, where the store of 1 to
   +0x2C comes after the store of 0 to +0x14, and a test of func_442860 before the two cached
   records are freed clears +0x2C and sets the byte at +0x20 of D_L05_001B13B0. */

extern int D_L05_00221D10[];

extern unsigned char D_L05_001B2000;

extern unsigned char D_L05_001B2001;

extern unsigned char D_L05_001B2002;

extern float D_L05_001B2004;

extern float D_L05_001B2008;

extern float D_L05_001B200C;

extern float D_L05_001B2010;

extern int D_L05_001B2014;

extern unsigned char D_L05_001B3558;

extern unsigned char D_L05_001B3559;

extern unsigned char D_L05_001B355A;

extern float D_L05_001B355C;

extern float D_L05_001B3560;

extern float D_L05_001B3564;

extern float D_L05_001B3568;

extern int D_L05_001B356C;

extern int D_L05_001B1360 __attribute__((sda));

extern int D_L05_001B1364 __attribute__((sda));

extern int D_L05_001B13E8 __attribute__((sda));

extern int D_L05_001B13B0 __attribute__((sda));

extern int D_L05_001B13B4 __attribute__((sda));

extern int D_L05_001B13B8 __attribute__((sda));

extern int D_L05_001B13F0 __attribute__((sda));

extern void func_379F28(int a0);

extern void func_37D6E8(void);

extern void func_379F68(void);

extern void func_37B210(void);

extern void func_379F18(int a0);

extern int func_442860(void);

extern void func_445A98(void);

extern void func_328870(int a0);

typedef struct { int words[10]; } SpawnEntry;
extern SpawnEntry D_L05_002A1800[];
extern int func_37AAC8(int a0);

void func_US2_L05_00421A98(void)
{
    char *p;
    int i;

    func_37B210();
    func_379F18(1);
    p = (char *)D_L05_00221D10;
    D_L05_001B1360 = -2;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
    D_L05_001B13E8 = 1;
    *(int *)(p + 0x28) = 100;
    D_L05_001B1364 = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x2C) = 1;
    i = func_37AAC8(6);
    D_L05_001B13F0 = 0;
    D_L05_002A1800[i].words[5] = D_L05_002A1800[i].words[4];
    func_37D6E8();
    func_379F68();
    func_445A98();
    *(float *)(p + 0x30) = 8.0f;
    func_379F28(0);
    if (func_442860() != 0) {
        *(int *)(p + 0x2C) = 0;
        *(unsigned char *)(D_L05_001B13B0 + 0x20) = 1;
    }
    if (D_L05_001B13B4 != 0) {
        func_328870(D_L05_001B13B4);
        D_L05_001B13B4 = 0;
    }
    if (D_L05_001B13B8 != 0) {
        func_328870(D_L05_001B13B8);
        D_L05_001B13B8 = 0;
    }
    D_L05_001B2000 = D_L05_001B3558;
    D_L05_001B2001 = D_L05_001B3559;
    D_L05_001B2002 = D_L05_001B355A;
    D_L05_001B2008 = D_L05_001B3560;
    D_L05_001B2010 = D_L05_001B3568;
    D_L05_001B2004 = D_L05_001B355C;
    D_L05_001B200C = D_L05_001B3564;
    D_L05_001B2014 = D_L05_001B356C;
}
