#include "include_asm.h"
#include "names.h"
extern void gfx_draw_screen_element_stored(int *);
extern void list_menu_draw_cursor(int *);
extern void list_menu_draw_scroller(int);

void func_PAL_003447C0(int *p)
{
    if (p[92] != 0) {
        gfx_draw_screen_element_stored(p);
        gfx_draw_screen_element_stored(p + 19);
        list_menu_draw_cursor(p);
        list_menu_draw_scroller((int)p);
        menu_list_draw_rows(p);
    }
}
