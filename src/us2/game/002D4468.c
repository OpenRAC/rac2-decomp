#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern void item_menu_set_title_mode(char *, int);
extern void item_menu_fill_list(char *, char *);
extern void item_menu_clear_selection_state(char *);
extern void item_menu_set_extra_value(char *, char *);
extern char g_menu_item_table_first[];
extern char g_preview_extra_value_first[];
extern char *g_resident_data_base[] __attribute__((sda));

/* Sets up the first model preview object of the menu with its model data. (USA v2.00) */
int menu_preview_object_init_first_us2(void)
{
    if (g_resident_data_base[0] != 0) {
        item_menu_set_title_mode(g_resident_data_base[0] + 0x3C480, 0);
        item_menu_fill_list(g_resident_data_base[0] + 0x3C480, g_menu_item_table_first);
        item_menu_clear_selection_state(g_resident_data_base[0] + 0x3C480);
        item_menu_set_extra_value(g_resident_data_base[0] + 0x3C480, g_preview_extra_value_first);
    }
    return 0;
}

extern char g_menu_item_table_second[];
extern char g_preview_extra_value_second[];

/* Sets up the second model preview object of the menu with its model data. (USA v2.00) */
int menu_preview_object_init_second_us2(void)
{
    if (g_resident_data_base[0] != 0) {
        item_menu_set_title_mode(g_resident_data_base[0] + 0x3C480, 1);
        item_menu_fill_list(g_resident_data_base[0] + 0x3C480, g_menu_item_table_second);
        item_menu_clear_selection_state(g_resident_data_base[0] + 0x3C480);
        item_menu_set_extra_value(g_resident_data_base[0] + 0x3C480, g_preview_extra_value_second);
    }
    return 0;
}

