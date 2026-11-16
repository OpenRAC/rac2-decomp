#include "include_asm.h"

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
void menu_update_unlock_entries_us2(void)
{
    int a = save_count_nonzero_flags() >= 15;
    int b = save_count_nonzero_flags() >= 30;
    int c = save_count_entries_above_threshold() >= 10;
    g_unlock_entry_slots[5].f2 = a ? 3 : 2;
    g_unlock_entry_slots[6].f2 = b ? 3 : 2;
    g_unlock_entry_slots[7].f2 = c ? 10 : 2;
    g_unlock_entry_slots[8].f2 = c ? 3 : 2;
    g_unlock_text_ids[0] = a ? 0x2CB5 : 0x2CBB;
    g_unlock_text_ids[1] = b ? 0x2CB6 : 0x2CBC;
    g_unlock_text_ids[2] = c ? 0x2CB9 : 0x2CBD;
    g_unlock_text_ids[3] = c ? 0x2CBA : 0x2CBD;
    if (g_menu_object_flag) g_unlock_entry_slots[8].f0 = 0;
}

