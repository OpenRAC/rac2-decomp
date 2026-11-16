#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int D_L00_001A904C_2 __attribute__((sda));
extern int grid_menu_update_pal(int, int);
extern void tab_menu_draw(int);

/* func_PAL_L00_0030F3A8, the PAL copy of func_L00_0030D558: the same C, where the offset becomes 0x3A0B0 and the handler func_PAL_00346528. */
int func_PAL_L00_0030F3A8(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return grid_menu_update_pal(v + 0x3A0B0, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_12_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        tab_menu_draw(value + 0x3C210);
}

