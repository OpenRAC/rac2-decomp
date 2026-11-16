#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void sub_object_get_value_second(int);

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void module_l00_l00_call_handler_2_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        sub_object_get_value_second(value + 0x36F28);
}

extern void hud_item_bolt_draw(int);

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void module_l00_call_handler_3_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        hud_item_bolt_draw(value + 0x36F28);
}

extern void list_menu_draw_centered_rows_pal(int);

/* func_PAL_L00_0030F060, the PAL copy of func_L00_0030D210: the same C, where the offset becomes 0x39160 and the handler func_PAL_0034B088. */
void module_l00_call_handler_4_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_menu_draw_centered_rows_pal(value + 0x39160);
}

extern int UpdateMenuChoiceListWidgets_pal(int, int);

/* func_PAL_L00_0030F090, the PAL copy of func_L00_0030D240: the same C, where the offset becomes 0x39160 and the handler func_PAL_0034ABB0. */
int module_l00_call_handler_with_arg_5_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return UpdateMenuChoiceListWidgets_pal(value + 0x39160, argument);
    return 0;
}
