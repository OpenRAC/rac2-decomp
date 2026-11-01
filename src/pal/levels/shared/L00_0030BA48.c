#include "include_asm.h"

extern int D_001A8A5C __attribute__((sda));
extern int D_PAL_001B1D7C __attribute__((sda));

int func_PAL_L00_0030BA48(void) {
    return D_PAL_001B1D7C;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_0030BA80);
