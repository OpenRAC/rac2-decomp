#include "include_asm.h"
#include "names.h"
/* func_PAL_002CBD80, the PAL copy of func_002CAF18: the same C, where the menu object moves
 * to +0x39160, its fields to +0x484 and +0x4AC, and each query is the next accessor along. */
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
extern void menu_set_field_448_pal(char *, int), menu_set_field_44c_pal(char *, int), menu_load_sprites_from_values(char *, int *), menu_set_table_slot_pal(char *, int, int), menu_set_icon_count_and_icons_pal(char *, int, int *);
extern int UpdateMenuChoiceListWidgets_pal(char *, int);
void ConfigureMenuChoiceList_pal(void)
{
    if (!g_resident_data_base[0]) return;
    if (stub_empty_26()) {
        menu_set_field_44c_pal((g_resident_data_base[0] + 0x39160), 1);
        menu_set_icon_count_and_icons_pal((g_resident_data_base[0] + 0x39160), 5, g_pause_icons_five_a);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *p = (g_resident_data_base[0] + 0x39160);
        *(int **)(p + 0x484) = g_pause_widget_icons_b;
        menu_set_field_448_pal(p, 0);
        }
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 0, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 2, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 3, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 1, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 4, 1);
        { char *p = (g_resident_data_base[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else if (stub_empty_23() && stub_empty_24()) {
        menu_set_field_44c_pal((g_resident_data_base[0] + 0x39160), 1);
        menu_set_icon_count_and_icons_pal((g_resident_data_base[0] + 0x39160), 5, g_pause_icons_five_b);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *p = (g_resident_data_base[0] + 0x39160);
        *(int **)(p + 0x484) = g_pause_widget_icons_c;
        menu_set_table_slot_pal(p, 0, 1);
        }
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 1, stub_empty_22() ^ 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 2, stub_empty_22() ^ 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 3, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 4, stub_empty_22() ^ 1);
        menu_set_field_448_pal((g_resident_data_base[0] + 0x39160), 0);
        { char *p = (g_resident_data_base[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else if (stub_empty_25()) {
        menu_set_field_44c_pal((g_resident_data_base[0] + 0x39160), 1);
        menu_set_icon_count_and_icons_pal((g_resident_data_base[0] + 0x39160), 3, g_pause_icons_three);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *p = (g_resident_data_base[0] + 0x39160);
        *(int **)(p + 0x484) = g_pause_widget_icons_d;
        menu_set_field_448_pal(p, 0);
        }
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 0, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 1, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 2, 1);
        { char *p = (g_resident_data_base[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else if (stub_empty_28() == 0x31 || stub_empty_27() || stub_empty_28() == 0x1C) {
        menu_set_field_44c_pal((g_resident_data_base[0] + 0x39160), 1);
        menu_set_icon_count_and_icons_pal((g_resident_data_base[0] + 0x39160), 2, g_pause_icons_two);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *p = (g_resident_data_base[0] + 0x39160);
        *(int **)(p + 0x484) = g_pause_widget_icons_a;
        menu_set_field_448_pal(p, 0);
        }
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 0, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 1, 1);
        { char *p = (g_resident_data_base[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else {
        menu_set_field_44c_pal((g_resident_data_base[0] + 0x39160), 1);
        menu_set_icon_count_and_icons_pal((g_resident_data_base[0] + 0x39160), 7, g_pause_icons_seven);
        menu_load_sprites_from_values((g_resident_data_base[0] + 0x39160), g_pause_sprite_values);
        { char *p = (g_resident_data_base[0] + 0x39160);
        *(int **)(p + 0x484) = g_pause_widget_data;
        if (g_hero_state[0x22B4] == 1) {
            menu_set_table_slot_pal(p, 0, 0);
            menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 1, 0);
            menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 2, 0);
        } else {
            menu_set_table_slot_pal(p, 0, 1);
            menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 1, 1);
            menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 2, 1);
        }
        }
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 3, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 4, 1);
        menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 5, 1);
        if (menu_always_return_true()) {
            menu_set_field_448_pal((g_resident_data_base[0] + 0x39160), 1);
            menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 6, 1);
        } else {
            menu_set_field_448_pal((g_resident_data_base[0] + 0x39160), 0);
            menu_set_table_slot_pal((g_resident_data_base[0] + 0x39160), 6, 0);
        }
        if (g_hero_state[0x22B4] == 1) { char *p = (g_resident_data_base[0] + 0x39160); *(int *)(p + 0x4ac) = 3; }
        else { char *p = (g_resident_data_base[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    }
    UpdateMenuChoiceListWidgets_pal((g_resident_data_base[0] + 0x39160), 0);
}
