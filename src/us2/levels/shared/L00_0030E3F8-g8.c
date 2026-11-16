#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base;
extern int menu_choice_list_update_widgets_us2(void *, int);

/* Calls the resident-data sub-object routine at +0x39160 with a value, or returns 0 when no resident data is loaded. */
int resident_sub_39160_query_us2(int value) {
    if (g_resident_data_base != 0)
        return menu_choice_list_update_widgets_us2(g_resident_data_base + 0x39160, value);
    return 0;
}

extern int UpdateItemGridMenu_us2(void *, int);

/* Calls the resident-data sub-object routine at +0x39620 with a value, or returns 0 when no resident data is loaded. */
int resident_sub_39620_query_us2(int value) {
    if (g_resident_data_base != 0)
        return UpdateItemGridMenu_us2(g_resident_data_base + 0x39620, value);
    return 0;
}
