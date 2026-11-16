#include "include_asm.h"
#include "names.h"

void option_list_draw_rows(int);
void option_list_draw_rows(int param_1);

/* Draws the list of the tab menu (PAL). */
void tab_menu_draw_list_pal(int self)
{
  option_list_draw_rows(self + 0x238);
  return;
}


extern void func_00336320_6(char *);
extern void func_00336A78_7(char *);
extern void tab_menu_draw_part(char *);
extern void func_00341A68_1(char *);
extern void tab_menu_draw_icons(char *);

/* Reads a word at +544 of the object; returns when it is zero, otherwise calls a repeated callee four times with the object and the objects at +152, +76 and +228, then one callee each with +464, the object, the object and the object. */
void tab_menu_draw_pal(char *self)
{
    if (*(int *)(self + 560) == 0)
        return;
    func_00336320_6(self);
    func_00336320_6(self + 152);
    func_00336320_6(self + 76);
    func_00336320_6(self + 228);
    func_00336A78_7(self + 464);
    tab_menu_draw_part(self);
    func_00341A68_1(self);
    tab_menu_draw_icons(self);
}

/* Constructs the widgets of the small list menu and returns the menu pointer (PAL). */
char *small_list_menu_construct_pal(char *self) {
    extern unsigned long long menu_pass_through_handle(void *);
    extern void *object_construct_derived_a(char *);
    menu_pass_through_handle(self + 0x10);
    object_construct_derived_a(self + 0xEC);
    object_construct_derived_a(self + 0x138);
    return self;
}

