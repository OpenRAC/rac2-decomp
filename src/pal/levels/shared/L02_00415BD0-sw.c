#include "include_asm.h"

typedef unsigned char u8;
extern void func_002B0C28(int, int, int);

void func_PAL_L02_00416108(u8 *a0) {
    int v = *(int *)(*(void **)(a0 + 0x68) + 0x10);
    int msg;

    switch (v) {
    case 1:
        msg = 0x130B;
        break;
    case 3:
        msg = 0x133B;
        break;
    case 4:
        msg = 0x1348;
        break;
    case 5:
        msg = 0x133D;
        break;
    case 6:
        msg = 0x1344;
        break;
    case 7:
        msg = 0x1345;
        break;
    case 8:
        msg = 0x1346;
        break;
    case 9:
        msg = 0x1347;
        break;
    case 0:
    case 2:
    default:
        msg = 0x12E5;
        break;
    }
    func_002B0C28(0xB, msg, 1);
}
