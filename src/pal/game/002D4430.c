#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern void item_menu_set_title_mode(char *, int);
extern void item_menu_fill_list(char *, char *);
extern void item_menu_clear_selection_state(char *);
extern void item_menu_set_extra_value(char *, char *);
extern char D_00259F58[];
extern char D_0025D0E0[];
extern char *D_001A8CFC[] __attribute__((sda));

int func_PAL_002D4430(void)
{
    if (D_001A8CFC[0] != 0) {
        item_menu_set_title_mode(D_001A8CFC[0] + 0x3C530, 0);
        item_menu_fill_list(D_001A8CFC[0] + 0x3C530, D_00259F58);
        item_menu_clear_selection_state(D_001A8CFC[0] + 0x3C530);
        item_menu_set_extra_value(D_001A8CFC[0] + 0x3C530, D_0025D0E0);
    }
    return 0;
}

extern char D_00259CE0[];
extern char D_0025D288[];

int func_PAL_002D44B0(void)
{
    if (D_001A8CFC[0] != 0) {
        item_menu_set_title_mode(D_001A8CFC[0] + 0x3C530, 1);
        item_menu_fill_list(D_001A8CFC[0] + 0x3C530, D_00259CE0);
        item_menu_clear_selection_state(D_001A8CFC[0] + 0x3C530);
        item_menu_set_extra_value(D_001A8CFC[0] + 0x3C530, D_0025D288);
    }
    return 0;
}

