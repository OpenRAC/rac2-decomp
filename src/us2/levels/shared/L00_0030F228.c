#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));

/* Calls the menu draw handler (with prompts) in the loaded module, if a module is loaded. */
void level_l00_call_module_handler_10_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_draw_with_prompts(value + 0x3CEA0);
}

extern int popup_update_position(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_11_us2(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return popup_update_position(value + 0x3CEA0, argument);
    return 0;
}

