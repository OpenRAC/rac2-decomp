#include "include_asm.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int func_PAL_00344528(char *, int);

/* func_PAL_L00_0030F998, the PAL copy of func_L00_0030DB48: the same C, where the base offset
 * 0x3E1D8 becomes 0x3E810 and func_003424C0 becomes func_PAL_00344528. */
int func_PAL_L00_0030F998(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_00344528((char *)(value + 0x3E810), argument);
    return 0;
}

void func_PAL_L00_0030F9D8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00342758(value + 0x3E810);
}

