#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int func_US2_00340AA8(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_8_us2(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_US2_00340AA8(value + 0x3A4C0, argument);
    return 0;
}

