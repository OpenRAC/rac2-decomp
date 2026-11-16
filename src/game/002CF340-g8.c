#include "include_asm.h"
#include "names.h"

/* 0xE0-byte class records indexed through D_00139568. */
typedef struct {
    int active;
    char pad04[0x94];
    int requirement[3];
    char pad_a4[0x3C];
} ClassRecord;

typedef struct {
    int text_id;
    int unk04;
    void *data;
    int unk0C;
    int unk10;
} MenuEntry;

typedef struct {
    char header[0x40];
    MenuEntry entries[3];
} Menu;

extern char *g_resident_data_base;
extern int g_extras_unlock_flag_a __attribute__((sda));
extern int g_extras_unlock_flag_b __attribute__((sda));
extern int g_special_items_unlock_flag __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_extras_unlocked_flag;
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_movie_seen_flags[] __attribute__((sda));
extern unsigned char g_weapon_table[];
extern Menu g_extras_tab_table_c;
extern char g_extras_tab_table_a[], g_extras_tab_table_b[];
extern char g_extras_unlock_entry_a[], g_extras_unlock_entry_b[], g_extras_unlock_entry_c[];
extern void tab_menu_set_tables(char *, char *, char *, char *);
extern void tab_menu_switch_tab(char *, int);

/* Works out which Extras sections are unlocked from game progress and fills in the three-entry Extras menu. */
int menu_update_extras_unlocks(void)
{
    int i, j;

    if (g_resident_data_base) {
        g_extras_unlock_flag_a = 1;
        g_extras_unlock_flag_b = 1;
        g_special_items_unlock_flag = 1;
        for (i = 0; i < 56; i++) {
            if (((ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table))->active && i != 9 && i != 10) {
                if (!g_item_owned_flags[i]) {
                    g_extras_unlock_flag_a = 0;
                    g_extras_unlock_flag_b = 0;
                    g_special_items_unlock_flag = 0;
                } else {
                    for (j = 0; j < 3; j++) {
                        int value;
                        ClassRecord *record;
                        switch (j) {
                        case 0:
                            record = (ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table);
                            value = record->requirement[0];
                            break;
                        case 1:
                            record = (ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table);
                            value = record->requirement[1];
                            break;
                        case 2:
                            record = (ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table);
                            value = record->requirement[2];
                            break;
                        default:
                            value = 0;
                            break;
                        }
                        if (value && !((unsigned long)g_movie_seen_flags[i] & ((1U << (j * 2)) & 255UL))) {
                            g_extras_unlock_flag_b = 0;
                            g_special_items_unlock_flag = 0;
                        }
                    }
                }
            }
        }
        if (!g_extras_unlocked_flag) {
            Menu *menu = &g_extras_tab_table_c;
            menu->entries[0].text_id = 0x2DC0;
            menu->entries[0].data = 0;
            menu->entries[1].text_id = 0x2DC0;
            menu->entries[1].data = 0;
            menu->entries[2].text_id = 0x2DC0;
            menu->entries[2].data = 0;
        } else {
            Menu *menu = &g_extras_tab_table_c;
            menu->entries[0].text_id = 0x3202;
            menu->entries[0].data = g_extras_unlock_entry_a;
            menu->entries[1].text_id = 0x320C;
            menu->entries[1].data = g_extras_unlock_entry_b;
            menu->entries[2].text_id = 0x323F;
            menu->entries[2].data = g_extras_unlock_entry_c;
        }
        tab_menu_set_tables(g_resident_data_base + 0x3BE08, g_extras_tab_table_a, g_extras_tab_table_b, (char *)&g_extras_tab_table_c);
        tab_menu_switch_tab(g_resident_data_base + 0x3BE08, 2);
    }
    return 0;
}
