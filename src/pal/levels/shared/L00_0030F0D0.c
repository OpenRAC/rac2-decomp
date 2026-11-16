#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void item_grid_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_5_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        item_grid_menu_draw(value + 0x39620);
}

extern void menu_screen_large_draw_parts(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_6_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_screen_large_draw_parts(value + 0x39BA0);
}

extern int UpdateItemGridMenu_pal(int, int);

/* Reads the object base from a shared global and, when it is non-zero, returns the handler's
 * result at a fixed byte offset in it; otherwise returns 0. */
int module_l00_call_handler_with_arg_6_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return UpdateItemGridMenu_pal(value + 0x39620, argument);
    return 0;
}

extern int mission_screen_place_parts_pal(int, int);

/* Reads the object base from a shared global and, when it is non-zero, returns the handler's
 * result at a fixed byte offset in it; otherwise returns 0. */
int module_l00_call_handler_with_arg_7_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return mission_screen_place_parts_pal(value + 0x3B4C8, argument);
    return 0;
}

extern void mission_screen_draw_parts(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_7_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        mission_screen_draw_parts(value + 0x3B4C8);
}

extern int list_screen_layout_pal(int, int);

/* Reads the object base from a shared global and, when it is non-zero, returns the handler's
 * result at a fixed byte offset in it; otherwise returns 0. */
int module_l00_call_handler_with_arg_8_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_screen_layout_pal(value + 0x3B030, argument);
    return 0;
}
