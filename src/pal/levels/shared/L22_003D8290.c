#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern u8 D_001A63A8_4[];
extern u8 g_hero_state[];
extern void moby_explode(u8 *a0, int a1, int a2);

void func_PAL_L22_003D8398(u8 *a0) {
    int v = *(int *)(a0 + 0x68);
    moby_explode(a0, v, v);
    *(u8 *)(a0 + 0x30) = 0xFF;
}

