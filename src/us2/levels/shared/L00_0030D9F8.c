#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));

void module_l00_call_handler_with_arg_4_us2(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        menu_set_flag_restart_fades(value + 0x37ED0, argument);
}

