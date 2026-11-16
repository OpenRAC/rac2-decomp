#include "include_asm.h"
#include "names.h"

extern float g_menu_list_row_offset_x __attribute__((sda));

extern float g_menu_list_row_offset_y;

extern float g_menu_list_row_height __attribute__((sda));

extern void func_00335E38_5(void *, float, float, float, float);

extern void hud_set_widget_value_pair(void *, int, int);

extern void func_00336828_1(void *);

/* Draws the rows of a menu list one under the other, giving the fourth row a different label. */
void menu_list_draw_rows(int *menu)
{
    int row;

    for (row = 0; row < menu[95]; row++) {
        float *origin = (float *)menu[96];
        int labelId;

        func_00335E38_5(menu + 76, origin[0] + g_menu_list_row_offset_x,
                (origin[1] + g_menu_list_row_offset_y) + g_menu_list_row_height * (float)row, 0.0f, 0.0f);
        if (row == 3)
            labelId = 0xEA9E;
        else
            labelId = 0xEAA6;
        menu[93] = labelId;
        hud_set_widget_value_pair(menu + 76, labelId, ((int *)menu[94])[row]);
        func_00336828_1(menu + 76);
    }
}

extern void gfx_draw_screen_element_stored(int *);
extern void list_menu_draw_cursor(int *);
extern void list_menu_draw_scroller(int);

/* Draws the menu, but only when it is switched on. */
void menu_draw_if_active(int *menu)
{
    if (menu[92] != 0) {
        gfx_draw_screen_element_stored(menu);
        gfx_draw_screen_element_stored(menu + 19);
        list_menu_draw_cursor(menu);
        list_menu_draw_scroller((int)menu);
        menu_list_draw_rows(menu);
    }
}
