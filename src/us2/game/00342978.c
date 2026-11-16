#include "include_asm.h"
#include "names.h"

void option_list_draw_rows(int);
void option_list_draw_rows(int menu);

/* Draws the rows of the tab menu's list. */
void tab_menu_draw_list_us2(int menu)
{
  option_list_draw_rows(menu + 0x238);
  return;
}


extern void func_00336320_6(char *);
extern void func_00336A78_7(char *);
extern void tab_menu_draw_part(char *);
extern void func_00341A68_1(char *);
extern void tab_menu_draw_icons(char *);

/* Reads a word at +544 of the object; returns when it is zero, otherwise calls a repeated callee four times with the object and the objects at +152, +76 and +228, then one callee each with +464, the object, the object and the object. */
void tab_menu_draw_us2(char *menu)
{
    if (*(int *)(menu + 560) == 0)
        return;
    func_00336320_6(menu);
    func_00336320_6(menu + 152);
    func_00336320_6(menu + 76);
    func_00336320_6(menu + 228);
    func_00336A78_7(menu + 464);
    tab_menu_draw_part(menu);
    func_00341A68_1(menu);
    tab_menu_draw_icons(menu);
}

/* Constructs the sub-objects of a small list menu and returns it. */
char *small_list_menu_construct_us2(char *menu) {
    extern unsigned long long menu_pass_through_handle(void *);
    extern void *object_construct_derived_a(char *);
    menu_pass_through_handle(menu + 0x10);
    object_construct_derived_a(menu + 0xEC);
    object_construct_derived_a(menu + 0x138);
    return menu;
}

