#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void list_menu_set_enabled(char *, int);
extern void list_menu_set_record_table(char *, char *);
extern char g_list_menu_record_table_second[];

int menu_page_text_init_second_us2(void)
{
    if (g_resident_data_base[0] != 0) {
        list_menu_set_enabled(g_resident_data_base[0] + 0x3E760, 1);
        list_menu_set_record_table(g_resident_data_base[0] + 0x3E760, g_list_menu_record_table_second);
    }
    return 0;
}

