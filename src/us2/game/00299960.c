#include "include_asm.h"

extern int D_001A8A5C __attribute__((sda));

extern int D_US2_001B19BC __attribute__((sda));

int func_US2_00299960(void) {
    return D_US2_001B19BC;
}




int func_US2_00299968(void) {
    int value = D_US2_001B19BC;

    D_US2_001B19BC = 0;
    return value != 0;
}



INCLUDE_ASM("asm/us2/game", func_US2_00299980);
