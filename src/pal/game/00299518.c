#include "include_asm.h"

extern int D_001A8A5C __attribute__((sda));
extern int D_PAL_001B1A3C __attribute__((sda));

int func_PAL_00299518(void) {
    return D_PAL_001B1A3C;
}


int func_PAL_00299520(void) {
    int value = D_PAL_001B1A3C;
    D_PAL_001B1A3C = 0;
    return value != 0;
}


INCLUDE_ASM("asm/pal/game", func_PAL_00299538);
