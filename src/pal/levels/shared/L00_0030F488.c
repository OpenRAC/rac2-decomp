#include "include_asm.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int D_L00_001A904C_2 __attribute__((sda));
extern void func_003438E8(int);
extern int func_PAL_00343928(int, int);
extern int func_PAL_003457F0(int, int);

/* func_PAL_L00_0030F488, the PAL copy of func_L00_0030D638: the same C, where the field offset
 * becomes 0x3C210 and the callee is PAL's own. */
int func_PAL_L00_0030F488(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_PAL_00343928(v + 0x3C210, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F4C8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_003438E8(value + 0x3C530);
}

/* func_PAL_L00_0030F4F8, the PAL copy of func_L00_0030D6A8: the same C, where the field offset
 * becomes 0x3C530 and the callee is PAL's own. */
int func_PAL_L00_0030F4F8(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_PAL_003457F0(v + 0x3C530, a0);
    }
    return 0;
}
