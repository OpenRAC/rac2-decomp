#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void list_screen_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_8_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_screen_draw(value + 0x3B030);
}

extern void map_screen_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_9_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        map_screen_draw(value + 0x3B7A8);
}

extern int map_screen_update_layout_pal(int, int);

/* func_PAL_L00_0030F2C8, the PAL copy of func_L00_0030D478: the same C, where the offset 0x3B490
 * becomes 0x3B7A8 and the callee func_0033B540 becomes func_PAL_0033D468. */
int module_l00_call_handler_with_arg_9_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0) {
        return map_screen_update_layout_pal(value + 0x3B7A8, argument);
    }
    return 0;
}
