#include "common.h"

typedef struct {
    u32 value;
    u8 pad[0x14];
    u32 id;
} Entry_0028BCE8;

typedef struct {
    u8 pad[0x3C];
    u16 value;
    u8 pad3E[0xA2];
} Rec_0028BCE8;

extern u32 g_radial_slot_count;
extern u32 g_radial_menu_pages;
extern u32 g_radial_pages_data __attribute__((sda));
extern u32 g_radial_menu_page_index __attribute__((sda));
extern u32 g_weapon_menu_slots[] MACRO_ADDR;
extern u8 g_item_slot_to_record[];
extern Rec_0028BCE8 g_weapon_table[];
extern Entry_0028BCE8 g_weapon_menu_slots_2[];

/* Sets up the eight weapon menu slots from the current weapon list. */
void weapon_menu_init_slots(void)
{
    int i;
    u32 weapon_id;
    Rec_0028BCE8 *rec;

    g_radial_slot_count = 8;
    g_radial_menu_pages = (u32)&g_radial_pages_data;
    g_radial_menu_page_index = 0;
    for (i = 0; i < 8; i++) {
        weapon_id = g_weapon_menu_slots[i];
        rec = &g_weapon_table[g_item_slot_to_record[weapon_id]];
        g_weapon_menu_slots_2[i].id = weapon_id;
        g_weapon_menu_slots_2[i].value = rec->value;
    }
}
