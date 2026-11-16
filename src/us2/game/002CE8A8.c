#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void tab_menu_set_enabled(void *, int);
extern char *g_resident_data_base[] __attribute__((sda));
extern void *tab_menu_get_selected_value(void *);
extern char *g_resident_data_base[] __attribute__((sda));

int menu_init_list_object_us2(void *object) { char *root=g_resident_data_base[0]; if (root != 0) { tab_menu_set_enabled(root+0x3C160,1); *(void **)((char *)object+0x34)=tab_menu_get_selected_value(g_resident_data_base[0]+0x3C160); } return 0; }

extern void tab_menu_set_enabled_us2(void *, int);
extern void tab_menu_set_tables_us2(char *, char *, char *, char *);
extern void tab_menu_switch_tab_us2(char *, int);
extern char g_extras_tab_table_a[];
extern char g_extras_tab_table_b[];
extern char g_extras_tab_table_c[];

int func_US2_002CEA38(void)
{
    if (g_resident_data_base[0] != 0) {
        tab_menu_set_enabled_us2(g_resident_data_base[0] + 0x3C160, 1);
        tab_menu_set_tables_us2(g_resident_data_base[0] + 0x3C160, g_extras_tab_table_a, g_extras_tab_table_b, g_extras_tab_table_c);
        tab_menu_switch_tab_us2(g_resident_data_base[0] + 0x3C160, 0);
    }
    return 0;
}

