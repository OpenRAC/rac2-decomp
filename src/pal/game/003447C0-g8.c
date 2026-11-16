#include "include_asm.h"
#include "names.h"
extern void gfx_draw_screen_element_stored(int *);
extern void list_menu_draw_cursor(int *);
extern void list_menu_draw_scroller(int);

/* Draws the list menu's elements, cursor, scroller and rows when it is active. */
void menu_draw_if_active_pal(int *menu)
{
    if (menu[92] != 0) {
        gfx_draw_screen_element_stored(menu);
        gfx_draw_screen_element_stored(menu + 19);
        list_menu_draw_cursor(menu);
        list_menu_draw_scroller((int)menu);
        menu_list_draw_rows(menu);
    }
}
