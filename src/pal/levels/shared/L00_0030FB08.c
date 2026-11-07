#include "include_asm.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int func_PAL_00341C18(int, int);

/* func_PAL_L00_0030FB08, the PAL copy of func_L00_0030DCB8: the same C, where 0x3A388 becomes 0x3A570
   and the callee is PAL's own func_PAL_00341C18. */
int func_PAL_L00_0030FB08(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_00341C18(value + 0x3A570, argument);
    return 0;
}

void func_PAL_L00_0030FB48(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00340250(value + 0x3A570);
}

extern int D_L00_001A904C_7 __attribute__((sda));
extern int func_003387A0_1(int a, int b, int c);

/* Reads a bound global word; when it is zero it returns its first argument, otherwise it calls a helper with that value plus a fixed base offset and both of its arguments. */
int func_PAL_L00_0030FBC0(int a0, int a1)
{
    int v = D_L00_001A904C_7;

    if (v == 0) return a0;
    return func_003387A0_1(v + 0x36F28, a0, a1);
}

