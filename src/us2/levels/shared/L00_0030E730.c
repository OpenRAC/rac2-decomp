#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int info_panel_update(int, int);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_10_us2(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return info_panel_update(v + 0x3BA58, a0);
    }
    return 0;
}

