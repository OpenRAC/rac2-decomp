#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
extern int module_l00_call_handler_with_arg_15(int a);

int pad_run_input_update_return_zero_pal(void)
{
    module_l00_call_handler_with_arg_15(g_menu_input_flags);
    return 0;
}

