#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));

/* Calls the menu handler of the level module with the given argument. */
void module_l00_call_handler_with_arg_4_pal(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        menu_set_flag_restart_fades(value + 0x37ED0, argument);
}

