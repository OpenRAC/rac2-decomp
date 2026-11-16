#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int tab_menu_update(int a, int b);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_12_pal(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return tab_menu_update(value + 0x3C210, argument);
    }
    return 0;
}

