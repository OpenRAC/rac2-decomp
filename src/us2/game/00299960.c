#include "include_asm.h"

extern int D_001A8A5C __attribute__((sda));

extern int D_US2_001B19BC __attribute__((sda));

int func_US2_00299960(void) {
    return D_US2_001B19BC;
}




INCLUDE_ASM("asm/us2/game", func_US2_00299968);

INCLUDE_ASM("asm/us2/game", func_US2_00299980);

INCLUDE_ASM("asm/us2/game", func_US2_00299998);
