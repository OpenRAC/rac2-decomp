#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int D_L00_001A904C_2 __attribute__((sda));
extern void item_menu_draw(int);
extern int tab_menu_update_pal(int, int);
extern int item_menu_update_pal(int, int);

/* func_PAL_L00_0030F488, the PAL copy of func_L00_0030D638: the same C, where the field offset
 * becomes 0x3C210 and the callee is PAL's own. */
int module_l00_call_handler_with_arg_13_pal(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return tab_menu_update_pal(value + 0x3C210, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_14_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        item_menu_draw(value + 0x3C530);
}

/* func_PAL_L00_0030F4F8, the PAL copy of func_L00_0030D6A8: the same C, where the field offset
 * becomes 0x3C530 and the callee is PAL's own. */
int module_l00_call_handler_with_arg_14_pal(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return item_menu_update_pal(value + 0x3C530, argument);
    }
    return 0;
}
