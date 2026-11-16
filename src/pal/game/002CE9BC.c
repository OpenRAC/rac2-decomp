#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base[] __attribute__((sda));
extern void tab_menu_set_enabled_pal(void *, int);
extern void tab_menu_set_tables_pal(char *, char *, char *, char *);
extern void tab_menu_switch_tab_pal(char *, int);
extern char g_extras_tab_table_a[];
extern char g_extras_tab_table_b[];
extern char g_extras_tab_table_c[];
extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));

/* Builds the three-entry Extras menu list and selects its first entry (PAL). */
int menu_build_extras_list_pal(void)
{
    if (g_resident_data_base[0] != 0) {
        tab_menu_set_enabled_pal(g_resident_data_base[0] + 0x3C210, 1);
        tab_menu_set_tables_pal(g_resident_data_base[0] + 0x3C210, g_extras_tab_table_a, g_extras_tab_table_b, g_extras_tab_table_c);
        tab_menu_switch_tab_pal(g_resident_data_base[0] + 0x3C210, 0);
    }
    return 0;
}

