#include "include_asm.h"






typedef unsigned char u8;
extern void func_L00_002A61C8(int arg0, int arg1, int arg2, int arg3);
extern int func_L00_002B3998_1(float value);
typedef struct {
    u8 pad000[0x1b8];
    int f1B8;
    u8 pad1bc[0x222 - 0x1bc];
    short s222;
    u8 pad224[0xc2c - 0x224];
    int fC2C;
    u8 padc30[0x149d - 0xc30];
    u8 b149D;
    u8 pad149e[0x2290 - 0x149e];
    u8 *p2290;
    int f2294;
    u8 pad2298[0x22b8 - 0x2298];
    u8 b22B8;
    u8 pad22b9[0x22bb - 0x22b9];
    u8 b22BB;
    u8 pad22bc[0x22bf - 0x22bc];
    u8 b22BF;
    u8 pad22c0[0x24ec - 0x22c0];
    short s24EC;
} ResidentState_Fd160fb9c;
extern ResidentState_Fd160fb9c D_00189E20_16;
extern u8 D_00189E20_1[];

/* Reads a resident mode word and the kind byte of a pointer field, then for kind 3, 4 or 20 tests two float thresholds through a predicate and triggers a four-argument action with selector zero or one. */
void func_PAL_L00_002A62B0(void)
{
    int selector;

    if (D_00189E20_16.f2294 == 2) {
        if (D_00189E20_16.f1B8 < 12)
            return;
    }

    selector = D_00189E20_16.b149D;

    if (D_00189E20_16.f2294 == 2) {
        if (D_00189E20_16.f1B8 == 18)
            func_L00_002A61C8(selector, 0, 1, 30);
    }

    switch (D_00189E20_16.p2290[67]) {
    case 3:
        if (D_00189E20_16.fC2C != 0)
            return;
        if (func_L00_002B3998_1(49.5f) != 0)
            func_L00_002A61C8(selector, 0, 1, 30);
        if (func_L00_002B3998_1(17.0f) != 0)
            func_L00_002A61C8(selector, 1, 1, 30);
        return;
    case 4:
        if (D_00189E20_16.fC2C != 0)
            return;
        if (func_L00_002B3998_1(12.5f) != 0)
            func_L00_002A61C8(selector, 0, 1, 30);
        if (func_L00_002B3998_1(1.0f) != 0)
            func_L00_002A61C8(selector, 1, 1, 30);
        return;
    case 20:
        if (D_00189E20_16.fC2C != 0)
            return;
        if (func_L00_002B3998_1(8.0f) != 0)
            func_L00_002A61C8(selector, 0, 1, 30);
        if (func_L00_002B3998_1(21.0f) != 0)
            func_L00_002A61C8(selector, 1, 1, 30);
        return;
    }
}

