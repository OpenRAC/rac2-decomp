#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern void *tab_menu_get_selected_value(void *);
extern char *g_resident_data_base[] __attribute__((sda));

/* Stores the selected tab menu value in the object's text pointer. */
int menu_assign_list_text_pointer_pal(char *object) {
    if (g_resident_data_base[0] != 0)
        *(void **)(object + 0x34) = tab_menu_get_selected_value(g_resident_data_base[0] + 0x3C210);
    return 0;
}

