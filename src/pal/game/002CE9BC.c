#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base[] __attribute__((sda));
extern void tab_menu_set_enabled_pal(void *, int);
extern void tab_menu_set_tables_pal(char *, char *, char *, char *);
extern void func_PAL_00343690(char *, int);
extern char g_extras_tab_table_a[];
extern char g_extras_tab_table_b[];
extern char g_extras_tab_table_c[];
extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));

int func_PAL_002CEA20(void)
{
    if (g_resident_data_base[0] != 0) {
        tab_menu_set_enabled_pal(g_resident_data_base[0] + 0x3C210, 1);
        tab_menu_set_tables_pal(g_resident_data_base[0] + 0x3C210, g_extras_tab_table_a, g_extras_tab_table_b, g_extras_tab_table_c);
        func_PAL_00343690(g_resident_data_base[0] + 0x3C210, 0);
    }
    return 0;
}

