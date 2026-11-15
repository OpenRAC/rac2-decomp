#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int tab_menu_update(int a, int b);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_PAL_L00_0030F418(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return tab_menu_update(v + 0x3C210, a0);
    }
    return 0;
}

