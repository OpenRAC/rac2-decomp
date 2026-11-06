#include "common.h"
#include "include_asm.h"

extern unsigned char D_PAL_001A7C3C MACRO_ADDR;

/* func_PAL_L02_00402928, PAL's own: is the language index (the byte D_PAL_001A7C3C) 2 or above? */
int func_PAL_L02_00402928(void) {
    return D_PAL_001A7C3C >= 2;
}
