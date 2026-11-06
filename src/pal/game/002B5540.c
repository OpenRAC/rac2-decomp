#include "include_asm.h"

/* func_PAL_002B5540, the PAL copy of func_002B49B0: the same C, where the value takes the 50 Hz scale. */

typedef int s32;

extern int D_001AA0F0 __attribute__((sda));

void func_PAL_002B5540(int value) {
    D_001AA0F0 = ((s32)(value) * 5 + 2) / 6;
}
