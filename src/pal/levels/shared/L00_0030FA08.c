#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int list_menu_set_selection_pal(int, int);

/* Sets the list menu selection of the bound module (PAL offsets); returns 0 when none is bound. */
int level_l00_call_module_handler_with_arg_6_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_menu_set_selection_pal(value + 0x3EA78, argument);
    return 0;
}
