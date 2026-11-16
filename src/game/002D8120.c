#include "common.h"

typedef struct {
    short id;
    short active;
    char pad[8];
} Func002D8120Slot;

extern int g_recent_text_count MACRO_ADDR;
extern unsigned char g_recent_text_entries[];
extern short g_text_pair_table[][2];
extern Func002D8120Slot g_menu_slot_list[];

/* Fills the slot list from a saved order and ends the list with an id of 0. */
int menu_slot_list_fill_from_saved_order(void)
{
    int i;

    for (i = 0; i < g_recent_text_count; i++) {
        g_menu_slot_list[i].active = 1;
        g_menu_slot_list[i].id = *g_text_pair_table[g_recent_text_entries[g_recent_text_count - 1 - i]];
    }
    g_menu_slot_list[g_recent_text_count].id = 0;
    return 0;
}
