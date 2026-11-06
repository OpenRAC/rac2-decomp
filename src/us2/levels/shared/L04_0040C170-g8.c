#include "include_asm.h"

/* func_US2_L04_0040C170 and func_US2_L04_0040C190, the v2.00 copies of func_L04_0040AC80
   and func_L04_0040AC98: the same C with one more store, to 0x001A8EE4.  The $gp-relative
   store comes first in the source: cc1 moves it to the end of the run, into the delay
   slot, the only place it gets that form (see src/levels/shared/L04_00402D90-g8.c). */

extern unsigned int D_L04_001A8ED0;

extern unsigned int D_L04_001A8EE4;

extern unsigned int D_L04_001B0908 __attribute__((sda));

void func_US2_L04_0040C170(void)
{
    D_L04_001B0908 = 1;
    D_L04_001A8ED0 = 2;
    D_L04_001A8EE4 = 1;
}

extern unsigned int D_L04_001B0910 __attribute__((sda));

void func_US2_L04_0040C190(void)
{
    D_L04_001B0910 = 1;
    D_L04_001A8EE4 = 1;
}
