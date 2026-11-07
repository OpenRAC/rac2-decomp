#include "include_asm.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void func_0033A3E0(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F268(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033A3E0(value + 0x3B030);
}

extern void func_0033B910(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F298(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033B910(value + 0x3B7A8);
}

extern int func_PAL_0033D468(int, int);

/* func_PAL_L00_0030F2C8, the PAL copy of func_L00_0030D478: the same C, where the offset 0x3B490
 * becomes 0x3B7A8 and the callee func_0033B540 becomes func_PAL_0033D468. */
int func_PAL_L00_0030F2C8(int a0)
{
    int v = D_L00_001A904C_2;

    if (v != 0) {
        return func_PAL_0033D468(v + 0x3B7A8, a0);
    }
    return 0;
}
