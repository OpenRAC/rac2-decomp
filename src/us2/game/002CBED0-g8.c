#include "include_asm.h"
#include "names.h"
/* func_US2_002CBED0, the USA v2.00 copy of func_002CAF18: the same C, where the menu object moves
 * to +0x39160, its fields to +0x484 and +0x4AC, and the queries sit one or two accessors later. */
extern char *g_resident_data_base[] __attribute__((sda));
extern int g_pause_sprite_values[1] __attribute__((sda));
extern int g_pause_icons_seven[1] __attribute__((sda));
extern int g_pause_icons_five_a[1] __attribute__((sda));
extern int g_pause_icons_five_b[1] __attribute__((sda));
extern int g_pause_icons_three[1] __attribute__((sda));
extern int g_pause_icons_two[1] __attribute__((sda));
extern int g_pause_widget_icons_a[1] __attribute__((sda));
extern int g_pause_widget_icons_b[1] __attribute__((sda));
extern int g_pause_widget_icons_c[1] __attribute__((sda));
extern int g_pause_widget_icons_d[1] __attribute__((sda));
extern int g_pause_widget_data[];
extern unsigned char g_hero_state[];
extern int stub_empty_22(void), stub_empty_23(void), stub_empty_24(void), stub_empty_25(void), stub_empty_26(void), stub_empty_27(void), stub_empty_28(void), menu_always_return_true(void);
extern void func_US2_003492A8(char *, int), func_US2_003492B0(char *, int), menu_load_sprites_from_values(char *, int *), func_US2_00349368(char *, int, int), menu_page_set_labels_us2(char *, int, int *);
extern int menu_choice_list_update_widgets_us2(char *, int);
/* Sets up the choices shown in the menu list, depending on what the game is doing (USA v2.00). */
void ConfigureMenuChoiceList_us2(void)
{
    if (!g_resident_data_base[0]) return;
    if (stub_empty_26()) {
        func_US2_003492B0((g_resident_data_base[0] + 0x39160), 1);
        menu_page_set_labels_us2((g_resident_data_base[0] + 0x39160), 5, g_pause_icons_five_a);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *menu = (g_resident_data_base[0] + 0x39160);
        *(int **)(menu + 0x484) = g_pause_widget_icons_b;
        func_US2_003492A8(menu, 0);
        }
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 0, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 2, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 3, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 1, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 4, 1);
        { char *menu = (g_resident_data_base[0] + 0x39160); *(int *)(menu + 0x4AC) = 0; }
    } else if (stub_empty_23() && stub_empty_24()) {
        func_US2_003492B0((g_resident_data_base[0] + 0x39160), 1);
        menu_page_set_labels_us2((g_resident_data_base[0] + 0x39160), 5, g_pause_icons_five_b);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *menu = (g_resident_data_base[0] + 0x39160);
        *(int **)(menu + 0x484) = g_pause_widget_icons_c;
        func_US2_00349368(menu, 0, 1);
        }
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 1, stub_empty_22() ^ 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 2, stub_empty_22() ^ 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 3, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 4, stub_empty_22() ^ 1);
        func_US2_003492A8((g_resident_data_base[0] + 0x39160), 0);
        { char *menu = (g_resident_data_base[0] + 0x39160); *(int *)(menu + 0x4AC) = 0; }
    } else if (stub_empty_25()) {
        func_US2_003492B0((g_resident_data_base[0] + 0x39160), 1);
        menu_page_set_labels_us2((g_resident_data_base[0] + 0x39160), 3, g_pause_icons_three);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *menu = (g_resident_data_base[0] + 0x39160);
        *(int **)(menu + 0x484) = g_pause_widget_icons_d;
        func_US2_003492A8(menu, 0);
        }
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 0, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 1, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 2, 1);
        { char *menu = (g_resident_data_base[0] + 0x39160); *(int *)(menu + 0x4AC) = 0; }
    } else if (stub_empty_28() == 0x31 || stub_empty_27() || stub_empty_28() == 0x1C) {
        func_US2_003492B0((g_resident_data_base[0] + 0x39160), 1);
        menu_page_set_labels_us2((g_resident_data_base[0] + 0x39160), 2, g_pause_icons_two);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *menu = (g_resident_data_base[0] + 0x39160);
        *(int **)(menu + 0x484) = g_pause_widget_icons_a;
        func_US2_003492A8(menu, 0);
        }
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 0, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 1, 1);
        { char *menu = (g_resident_data_base[0] + 0x39160); *(int *)(menu + 0x4AC) = 0; }
    } else {
        func_US2_003492B0((g_resident_data_base[0] + 0x39160), 1);
        menu_page_set_labels_us2((g_resident_data_base[0] + 0x39160), 7, g_pause_icons_seven);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *menu = (g_resident_data_base[0] + 0x39160);
        *(int **)(menu + 0x484) = g_pause_widget_data;
        if (g_hero_state[0x22B4] == 1) {
            func_US2_00349368(menu, 0, 0);
            func_US2_00349368((g_resident_data_base[0] + 0x39160), 1, 0);
            func_US2_00349368((g_resident_data_base[0] + 0x39160), 2, 0);
        } else {
            func_US2_00349368(menu, 0, 1);
            func_US2_00349368((g_resident_data_base[0] + 0x39160), 1, 1);
            func_US2_00349368((g_resident_data_base[0] + 0x39160), 2, 1);
        }
        }
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 3, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 4, 1);
        func_US2_00349368((g_resident_data_base[0] + 0x39160), 5, 1);
        if (menu_always_return_true()) {
            func_US2_003492A8((g_resident_data_base[0] + 0x39160), 1);
            func_US2_00349368((g_resident_data_base[0] + 0x39160), 6, 1);
        } else {
            func_US2_003492A8((g_resident_data_base[0] + 0x39160), 0);
            func_US2_00349368((g_resident_data_base[0] + 0x39160), 6, 0);
        }
        if (g_hero_state[0x22B4] == 1) { char *menu = (g_resident_data_base[0] + 0x39160); *(int *)(menu + 0x4AC) = 3; }
        else { char *menu = (g_resident_data_base[0] + 0x39160); *(int *)(menu + 0x4AC) = 0; }
    }
    menu_choice_list_update_widgets_us2((g_resident_data_base[0] + 0x39160), 0);
}
