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
extern void tab_menu_set_enabled_us2(void *, int);
extern int func_US2_00344480(unsigned char *);
extern int func_US2_003444C8(char *);

int menu_preview_copy_class_fields_us2(char *object)
{
    char *target;
    int i;

    if (g_resident_data_base != 0) {
        tab_menu_set_enabled_us2(g_resident_data_base + 0x3C160, 1);
        i = func_US2_00344480((unsigned char *)g_resident_data_base + 0x3C480);
        {
            ClassRecord *r = &g_weapon_table[g_item_slot_to_record[i]];
            int v = r->f42;
            char *a = g_resident_data_base + 0x3C480;
            *(int *)(object + 0x34) = v;
            target = func_US2_003444C8(a);
        }
        i = func_US2_00344480((unsigned char *)g_resident_data_base + 0x3C480);
        *(int *)(target + 0x58) = g_weapon_table[g_item_slot_to_record[i]].f06;
    }
    return 0;
}
