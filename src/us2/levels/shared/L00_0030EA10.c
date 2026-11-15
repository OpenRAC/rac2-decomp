#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int UpdateFourOptionMenuInput(int, int);

/* Reads a bound global word; when it is non-zero it calls the object's handler with that value
 * plus a fixed base offset as the first argument and the function's own argument as the second,
 * returning the handler's result, otherwise returns 0. */
int func_US2_L00_0030EA10(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return UpdateFourOptionMenuInput(value + 0x3D4B8, argument);
    return 0;
}

extern void four_option_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_US2_L00_0030EA50(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        four_option_menu_draw(value + 0x3D4B8);
}

extern int menu_handle_page_input_a(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030EA80(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_handle_page_input_a(value + 0x3D798, argument);
    return 0;
}

extern void two_toggle_a_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_US2_L00_0030EAC0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        two_toggle_a_draw(value + 0x3D798);
}

extern int menu_handle_page_input_b(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030EAF0(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_handle_page_input_b(value + 0x3DDE8, argument);
    return 0;
}

extern void single_toggle_a_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_US2_L00_0030EB30(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        single_toggle_a_draw(value + 0x3DDE8);
}

extern int screen_adjust_menu_update(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030EB60(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return screen_adjust_menu_update(value + 0x3E0C8, argument);
    return 0;
}

extern void onoff_menu_draw_with_help(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_US2_L00_0030EBA0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        onoff_menu_draw_with_help(value + 0x3E0C8);
}

extern int onoff_menu_update(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_US2_L00_0030EBD0(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return onoff_menu_update(value + 0x3E3A8, argument);
    return 0;
}

extern void onoff_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_US2_L00_0030EC10(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        onoff_menu_draw(value + 0x3E3A8);
}

