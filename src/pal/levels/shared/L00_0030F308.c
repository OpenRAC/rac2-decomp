#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void radial_menu_destroy(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_10_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        radial_menu_destroy(value + 0x3BB08);
}

extern int info_panel_update_pal(char *, int);

/* func_PAL_L00_0030F338, the PAL copy of func_L00_0030D4E8: the same C, where the object offset
 * 0x3B7C0 becomes 0x3BB08. */
int module_l00_call_handler_with_arg_10_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0) {
        return info_panel_update_pal((char *)value + 0x3BB08, argument);
    }
    return 0;
}

extern void menu_screen_draw_parts(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_11_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_screen_draw_parts(value + 0x3A0B0);
}

