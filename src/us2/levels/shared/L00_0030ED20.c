#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int menu_update_two_part_flags_a(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030ED20(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_update_two_part_flags_a(value + 0x3EB50, argument);
    return 0;
}

void func_US2_L00_0030ED60(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        single_toggle_c_draw(value + 0x3EB50);
}

extern int list_menu_update(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030ED90(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_menu_update(value + 0x3E760, argument);
    return 0;
}

void func_US2_L00_0030EDD0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_draw_if_active(value + 0x3E760);
}

extern int list_menu_set_selection(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030EE00(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_menu_set_selection(value + 0x3E9C8, argument);
    return 0;
}

