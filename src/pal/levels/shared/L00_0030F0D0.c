#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void item_grid_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F0D0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        item_grid_menu_draw(value + 0x39620);
}

extern void menu_screen_large_draw_parts(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F100(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_screen_large_draw_parts(value + 0x39BA0);
}

extern int func_PAL_00348DF8(int, int);

/* Reads the object base from a shared global and, when it is non-zero, returns the handler's
 * result at a fixed byte offset in it; otherwise returns 0. */
int func_PAL_L00_0030F130(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_00348DF8(value + 0x39620, argument);
    return 0;
}

extern int func_PAL_0033B218(int, int);

/* Reads the object base from a shared global and, when it is non-zero, returns the handler's
 * result at a fixed byte offset in it; otherwise returns 0. */
int func_PAL_L00_0030F1B8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0033B218(value + 0x3B4C8, argument);
    return 0;
}

extern void mission_screen_draw_parts(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F1F8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        mission_screen_draw_parts(value + 0x3B4C8);
}

extern int func_PAL_0033BE50(int, int);

/* Reads the object base from a shared global and, when it is non-zero, returns the handler's
 * result at a fixed byte offset in it; otherwise returns 0. */
int func_PAL_L00_0030F228(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0033BE50(value + 0x3B030, argument);
    return 0;
}
