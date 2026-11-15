#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));

void func_US2_L00_0030EF40(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        radial_menu_draw(value + 0x3A4C0);
}

extern int D_L00_001A904C_7 __attribute__((sda));
extern int func_003387A0_1(int a, int b, int c);

/* Reads a bound global word; when it is zero it returns its first argument, otherwise it calls a helper with that value plus a fixed base offset and both of its arguments. */
int func_US2_L00_0030EFB8(int a0, int a1)
{
    int v = D_L00_001A904C_7;

    if (v == 0) return a0;
    return func_003387A0_1(v + 0x36F28, a0, a1);
}

