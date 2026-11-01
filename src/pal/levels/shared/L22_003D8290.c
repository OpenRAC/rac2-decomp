#include "include_asm.h"


typedef unsigned char u8;
extern u8 D_001A63A8_4[];
extern u8 D_00189E20[];
extern void func_L22_003D4320(u8 *a0, int a1, int a2);

void func_PAL_L22_003D8398(u8 *a0) {
    int v = *(int *)(a0 + 0x68);
    func_L22_003D4320(a0, v, v);
    *(u8 *)(a0 + 0x30) = 0xFF;
}

