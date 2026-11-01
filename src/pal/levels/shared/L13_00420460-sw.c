#include "include_asm.h"

typedef unsigned char u8;
extern void func_002B0C28(int, int, int);

/* The func_L02_004114A0 message pick for the five level-13 states. Each case calls on
   its own: with one shared body the five labels would collapse into three ranges and
   the switch would become a compare tree. */
void func_PAL_L13_00420888(u8 *a0) {
    int v = *(int *)(*(void **)(a0 + 0x68) + 0x10);

    switch (v) {
    case 0:
        func_002B0C28(0xB, 0x1BC6, 1);
        break;
    case 1:
        func_002B0C28(0xB, 0x130B, 1);
        break;
    case 2:
        func_002B0C28(0xB, 0x12E5, 1);
        break;
    case 3:
        func_002B0C28(0xB, 0x12E5, 1);
        break;
    case 4:
        func_002B0C28(0xB, 0x12E5, 1);
        break;
    default:
        func_002B0C28(0xB, 0x12E5, 1);
        break;
    }
}
