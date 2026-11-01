#include "include_asm.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int func_US2_00340AA8(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030EF00(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_US2_00340AA8(value + 0x3A4C0, argument);
    return 0;
}

