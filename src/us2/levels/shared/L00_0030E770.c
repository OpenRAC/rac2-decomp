#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void menu_screen_draw_parts(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_11_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_screen_draw_parts(value + 0x3A000);
}

extern int D_L00_001A904C_1 __attribute__((sda));
extern int grid_menu_update(int, int);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_11_us2(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return grid_menu_update(v + 0x3A000, a0);
    }
    return 0;
}

