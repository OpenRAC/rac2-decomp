#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_1 __attribute__((sda));
extern int simple_page_update_pal(int, int);

/* func_PAL_L00_0030F568, the PAL copy of func_L00_0030D718: the same C with its own offset and
 * handler. */
int module_l00_call_handler_with_arg_15_pal(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return simple_page_update_pal(value + 0x3C898, argument);
    }
    return 0;
}

extern int D_L00_001A904C_2 __attribute__((sda));
extern void two_toggle_b_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_16_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        two_toggle_b_draw(value + 0x3D288);
}

extern int menu_handle_page_input_c_pal(int, int);

/* func_PAL_L00_0030F5D8, the PAL copy of func_L00_0030D788: the same C with its own offset and
 * handler. */
int module_l00_call_handler_with_arg_16_pal(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return menu_handle_page_input_c_pal(value + 0x3D288, argument);
    }
    return 0;
}

extern int four_option_menu_update_pal(int, int);

/* func_PAL_L00_0030F618, the PAL copy of func_L00_0030D7C8: the same C with its own offset and
 * handler. */
int module_l00_call_handler_with_arg_17_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return four_option_menu_update_pal(value + 0x3D568, argument);
    return 0;
}

extern void four_option_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_17_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        four_option_menu_draw(value + 0x3D568);
}

extern int menu_handle_page_input_a_pal(int, int);

/* func_PAL_L00_0030F688, the PAL copy of func_L00_0030D838: the same C with its own offset and
 * handler. */
int module_l00_call_handler_with_arg_18_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_handle_page_input_a_pal(value + 0x3D848, argument);
    return 0;
}

extern void two_toggle_a_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_18_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        two_toggle_a_draw(value + 0x3D848);
}

extern int single_toggle_a_update_pal(int, int);

/* func_PAL_L00_0030F6F8, the PAL copy of func_L00_0030D8A8: the same C with its own offset and
 * handler. */
int module_l00_call_handler_with_arg_19_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return single_toggle_a_update_pal(value + 0x3DE98, argument);
    return 0;
}

extern void single_toggle_a_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_19_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        single_toggle_a_draw(value + 0x3DE98);
}

extern int screen_adjust_menu_update_pal(int, int);

/* func_PAL_L00_0030F768, the PAL copy of func_L00_0030D918: the same C with its own offset and
 * handler. */
int module_l00_call_handler_with_arg_20_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return screen_adjust_menu_update_pal(value + 0x3E178, argument);
    return 0;
}

extern void onoff_menu_draw_with_help(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void level_l00_call_module_handler_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        onoff_menu_draw_with_help(value + 0x3E178);
}

extern int onoff_menu_update_pal(int, int);

/* func_PAL_L00_0030F7D8, the PAL copy of func_L00_0030D988: the same C with its own offset and
 * handler. */
int level_l00_call_module_handler_with_arg_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return onoff_menu_update_pal(value + 0x3E458, argument);
    return 0;
}

extern void onoff_menu_draw(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void level_l00_call_module_handler_2_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        onoff_menu_draw(value + 0x3E458);
}

extern int list_page_update_pal(int, int);

/* func_PAL_L00_0030F848, the PAL copy of func_L00_0030D9F8: the same C with its own offset and
 * handler. */
int level_l00_call_module_handler_with_arg_2_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_page_update_pal(value + 0x3F4A0, argument);
    return 0;
}

void level_l00_call_module_handler_3_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_page_draw(value + 0x3F4A0);
}

extern int audio_menu_update_pal(int, int);

/* func_PAL_L00_0030F8B8, the PAL copy of func_L00_0030DA68: the same C with its own offset and
 * handler. */
int level_l00_call_module_handler_with_arg_3_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return audio_menu_update_pal(value + 0x3DB28, argument);
    return 0;
}

void level_l00_call_module_handler_4_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        audio_menu_draw(value + 0x3DB28);
}

extern int menu_update_two_part_flags_a_pal(int, int);

/* func_PAL_L00_0030F928, the PAL copy of func_L00_0030DAD8: the same C with its own offset and
 * handler. */
int level_l00_call_module_handler_with_arg_4_pal(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_update_two_part_flags_a_pal(value + 0x3EC00, argument);
    return 0;
}

void level_l00_call_module_handler_5_pal(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        single_toggle_c_draw(value + 0x3EC00);
}

