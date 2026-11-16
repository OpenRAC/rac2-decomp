#include "common.h"
typedef struct {
    short f0;
    short f2;
    char pad4[8];
} Slot;
extern Slot g_unlock_entry_slots[];
extern int g_unlock_text_ids[4] MACRO_ADDR;
extern int g_menu_object_flag MACRO_ADDR;
extern int save_count_nonzero_flags(void);
extern int save_count_entries_above_threshold(void);

/* Unlock levels for the counts the player has collected. */
void menu_update_unlock_entries(void)
{
    int reached_first = save_count_nonzero_flags() >= 15;
    int reached_second = save_count_nonzero_flags() >= 30;
    int reached_third = save_count_entries_above_threshold() >= 10;
    g_unlock_entry_slots[5].f2 = reached_first ? 3 : 2;
    g_unlock_entry_slots[6].f2 = reached_second ? 3 : 2;
    g_unlock_entry_slots[7].f2 = reached_third ? 10 : 2;
    g_unlock_entry_slots[8].f2 = reached_third ? 3 : 2;
    g_unlock_text_ids[0] = reached_first ? 0x2E1F : 0x2E25;
    g_unlock_text_ids[1] = reached_second ? 0x2E20 : 0x2E26;
    g_unlock_text_ids[2] = reached_third ? 0x2E23 : 0x2E27;
    g_unlock_text_ids[3] = reached_third ? 0x2E24 : 0x2E27;
    if (g_menu_object_flag) g_unlock_entry_slots[8].f0 = 0;
}
