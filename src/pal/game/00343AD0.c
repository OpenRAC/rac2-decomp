#include "include_asm.h"
#include "names.h"

void option_list_draw_rows(int);
void option_list_draw_rows(int param_1);

void tab_menu_draw_list_pal(int param_1)
{
  option_list_draw_rows(param_1 + 0x238);
  return;
}


extern void func_00336320_6(char *);
extern void func_00336A78_7(char *);
extern void tab_menu_draw_part(char *);
extern void func_00341A68_1(char *);
extern void tab_menu_draw_icons(char *);

/* Reads a word at +544 of the object; returns when it is zero, otherwise calls a repeated callee four times with the object and the objects at +152, +76 and +228, then one callee each with +464, the object, the object and the object. */
void tab_menu_draw_pal(char *a0)
{
    if (*(int *)(a0 + 560) == 0)
        return;
    func_00336320_6(a0);
    func_00336320_6(a0 + 152);
    func_00336320_6(a0 + 76);
    func_00336320_6(a0 + 228);
    func_00336A78_7(a0 + 464);
    tab_menu_draw_part(a0);
    func_00341A68_1(a0);
    tab_menu_draw_icons(a0);
}

char *small_list_menu_construct_pal(char *p) {
    extern unsigned long long menu_pass_through_handle(void *);
    extern void *object_construct_derived_a(char *);
    menu_pass_through_handle(p + 0x10);
    object_construct_derived_a(p + 0xEC);
    object_construct_derived_a(p + 0x138);
    return p;
}

