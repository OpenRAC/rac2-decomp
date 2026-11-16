#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));

int module_l00_call_handler_with_arg_7_us2(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return mission_screen_place_parts(value + 0x3B418, argument);
    return 0;
}

