#include "include_asm.h"

#include "common.h"
extern void func_PAL_L01_002BEC60(unsigned long, unsigned long);
extern float D_L01_00189F90;

void func_PAL_L01_002C9B28(void) {
    if (D_L01_00189F90 < 0.054000005f)
        func_PAL_L01_002BEC60(0, 1);
    else
        func_PAL_L01_002BEC60(3, 1);
}

