#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void tab_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F458(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        tab_menu_draw(value + 0x3C210);
}

