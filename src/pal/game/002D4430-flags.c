#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad00[6];
    short f06;
    char pad08[0x3A];
    short f42;
    char pad44[0x9C];
} ClassRecord;
extern char *g_resident_data_base __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern ClassRecord g_weapon_table[];
extern void tab_menu_set_enabled_pal(void *, int);
extern int item_menu_get_selected_id_pal(unsigned char *);
extern int func_PAL_00345620(char *);

/* Enables the preview tab menu and copies the selected weapon record fields into the preview object (PAL). */
int menu_preview_copy_class_fields_pal(char *object)
{
    char *target;
    int i;

    if (g_resident_data_base != 0) {
        tab_menu_set_enabled_pal(g_resident_data_base + 0x3C210, 1);
        i = item_menu_get_selected_id_pal((unsigned char *)g_resident_data_base + 0x3C530);
        {
            ClassRecord *r = &g_weapon_table[g_item_slot_to_record[i]];
            int v = r->f42;
            char *a = g_resident_data_base + 0x3C530;
            *(int *)(object + 0x34) = v;
            target = func_PAL_00345620(a);
        }
        i = item_menu_get_selected_id_pal((unsigned char *)g_resident_data_base + 0x3C530);
        *(int *)(target + 0x58) = g_weapon_table[g_item_slot_to_record[i]].f06;
    }
    return 0;
}
