#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern void *tab_menu_get_selected_value(void *);

int menu_item_set_preview_us2(char *object) {
    if (g_resident_data_base[0] != 0)
        *(void **)(object + 0x34) = tab_menu_get_selected_value(g_resident_data_base[0] + 0x3C160);
    return 0;
}

