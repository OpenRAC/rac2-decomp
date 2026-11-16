#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void item_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_14_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        item_menu_draw(value + 0x3C480);
}

extern int D_L00_001A904C_1 __attribute__((sda));
extern int item_menu_update(int, int);

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_14_us2(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return item_menu_update(v + 0x3C480, a0);
    }
    return 0;
}

