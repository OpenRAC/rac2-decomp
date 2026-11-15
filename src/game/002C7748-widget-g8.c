#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001AB7A8[1] __attribute__((sda));
extern int D_001AB7D0[1] __attribute__((sda));
extern int D_001AB7F0[1] __attribute__((sda));
extern int D_001AB808[1] __attribute__((sda));
extern int D_001AB820[1] __attribute__((sda));
extern int D_001AB830[1] __attribute__((sda));
extern int D_001AB838[1] __attribute__((sda));
extern int D_001AB850[1] __attribute__((sda));
extern int D_001AB890[1] __attribute__((sda));
extern int D_001AB8D0[1] __attribute__((sda));
extern int D_002614E8[];
extern unsigned char g_hero_state[];
extern int stub_empty_22(void), stub_empty_23(void), stub_empty_24(void), stub_empty_25(void), stub_empty_26(void), stub_empty_27(void), stub_empty_28(void), menu_always_return_true(void);
extern void menu_set_field_448(char *, int), menu_set_field_44c(char *, int), menu_load_sprites_from_values(char *, int *), menu_set_table_slot(char *, int, int), menu_set_icon_count_and_icons(char *, int, int *);
extern int UpdateMenuChoiceListWidgets(char *, int);
#define MENU (D_001A8CFC[0] + 0x39140)
/* Sets up the choices shown in the menu list, depending on what the game is doing. */
void ConfigureMenuChoiceList(void)
{
    if (!D_001A8CFC[0]) return;
    if (stub_empty_26()) {
        menu_set_field_44c(MENU, 1);
        menu_set_icon_count_and_icons(MENU, 5, D_001AB7F0);
        menu_load_sprites_from_values(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB850;
        menu_set_field_448(p, 0);
        }
        menu_set_table_slot(MENU, 0, 1);
        menu_set_table_slot(MENU, 2, 1);
        menu_set_table_slot(MENU, 3, 1);
        menu_set_table_slot(MENU, 1, 1);
        menu_set_table_slot(MENU, 4, 1);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else if (stub_empty_23() && stub_empty_24()) {
        menu_set_field_44c(MENU, 1);
        menu_set_icon_count_and_icons(MENU, 5, D_001AB808);
        menu_load_sprites_from_values(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB890;
        menu_set_table_slot(p, 0, 1);
        }
        menu_set_table_slot(MENU, 1, stub_empty_22() ^ 1);
        menu_set_table_slot(MENU, 2, stub_empty_22() ^ 1);
        menu_set_table_slot(MENU, 3, 1);
        menu_set_table_slot(MENU, 4, stub_empty_22() ^ 1);
        menu_set_field_448(MENU, 0);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else if (stub_empty_25()) {
        menu_set_field_44c(MENU, 1);
        menu_set_icon_count_and_icons(MENU, 3, D_001AB820);
        menu_load_sprites_from_values(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB8D0;
        menu_set_field_448(p, 0);
        }
        menu_set_table_slot(MENU, 0, 1);
        menu_set_table_slot(MENU, 1, 1);
        menu_set_table_slot(MENU, 2, 1);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else if (stub_empty_28() == 0x31 || stub_empty_27() || stub_empty_28() == 0x1C) {
        menu_set_field_44c(MENU, 1);
        menu_set_icon_count_and_icons(MENU, 2, D_001AB830);
        menu_load_sprites_from_values(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_001AB838;
        menu_set_field_448(p, 0);
        }
        menu_set_table_slot(MENU, 0, 1);
        menu_set_table_slot(MENU, 1, 1);
        { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    } else {
        menu_set_field_44c(MENU, 1);
        menu_set_icon_count_and_icons(MENU, 7, D_001AB7D0);
        menu_load_sprites_from_values(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x414) = D_002614E8;
        if (g_hero_state[0x22B4] == 1) {
            menu_set_table_slot(p, 0, 0);
            menu_set_table_slot(MENU, 1, 0);
            menu_set_table_slot(MENU, 2, 0);
        } else {
            menu_set_table_slot(p, 0, 1);
            menu_set_table_slot(MENU, 1, 1);
            menu_set_table_slot(MENU, 2, 1);
        }
        }
        menu_set_table_slot(MENU, 3, 1);
        menu_set_table_slot(MENU, 4, 1);
        menu_set_table_slot(MENU, 5, 1);
        if (menu_always_return_true()) {
            menu_set_field_448(MENU, 1);
            menu_set_table_slot(MENU, 6, 1);
        } else {
            menu_set_field_448(MENU, 0);
            menu_set_table_slot(MENU, 6, 0);
        }
        if (g_hero_state[0x22B4] == 1) { char *p = MENU; *(int *)(p + 0x43C) = 3; }
        else { char *p = MENU; *(int *)(p + 0x43C) = 0; }
    }
    UpdateMenuChoiceListWidgets(MENU, 0);
}
