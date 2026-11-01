#include "include_asm.h"

extern void ref_L22_003A4FF8_00(void);

int func_PAL_L22_003A8388(void) {
    ref_L22_003A4FF8_00();
    return 1;
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L22_003A83A8);

