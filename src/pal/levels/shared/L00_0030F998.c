#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int list_menu_update_pal(char *, int);

/* func_PAL_L00_0030F998, the PAL copy of func_L00_0030DB48: the same C, where the base offset
 * 0x3E1D8 becomes 0x3E810 and func_003424C0 becomes func_PAL_00344528. */
/* Passes the bound module (plus a PAL offset) and an argument to the list menu update; returns 0 when none is bound. */
int level_l00_call_module_handler_with_arg_5_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_menu_update_pal((char *)(value + 0x3E810), argument);
    return 0;
}

/* Draws the bound module's menu if it is active. */
void level_l00_call_module_handler_6_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_draw_if_active(value + 0x3E810);
}

