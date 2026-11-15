#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_3 __attribute__((sda));
extern int tab_menu_get_selected_value(int x);

/* When a global flag is set, derives a pointer from that global plus a fixed offset, runs it through one callee and stores the callee result into a field of the argument. */
int func_US2_L00_00349980(int *obj)
{
    if (D_L00_001A904C_3 != 0)
        obj[13] = tab_menu_get_selected_value(D_L00_001A904C_3 + 0x3C160);
    return 0;
}

