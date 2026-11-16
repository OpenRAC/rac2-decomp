#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void menu_set_confirm_pending(void);
extern int g_menu_confirm_pending __attribute__((sda));

/* Sets a flag that tells the menu a confirmation is pending. */
void menu_set_confirm_pending(void) {
    g_menu_confirm_pending = 1;
}


/* Clears the confirmation-pending flag. */
void menu_clear_confirm_pending(void) {
    g_menu_confirm_pending = 0;
}

/* 0xE0-byte slots of the table at D_00239BA0; f4A and f4C link the slots. */
typedef struct {
    int f00;
    char pad04[0x46];
    short next;
    short prev;
    char pad4E[0x1E];
    int f6C;
    char pad70[0x1E];
    unsigned short f8E;
    char pad90[0x50];
} Slot287E98;
extern Slot287E98 g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
extern int g_help_entry_state[];
extern int g_item_ammo_counts[];

/* The second lookup re-reads D_00139568[index], which cc1 forwards from the stored value. With
   a cast on v instead, index and the link swap $a2/$a3 and the second mult moves ahead of the
   store. */
/* Moves an index to the next entry in its chain and raises its saved values to match that entry. */
void menu_advance_chain_entry(int index)
{
    Slot287E98 *s = &g_weapon_table[g_item_slot_to_record[index]];
    short v = s->next;
    if (v == 0) return;
    {
        int x = s->f6C;
        if (x >= 0) {
            x <<= 5;
            if (g_help_entry_state[index] < x) g_help_entry_state[index] = x;
        }
    }
    g_item_slot_to_record[index] = v;
    if (g_weapon_table[g_item_slot_to_record[index]].f00 != 0) g_item_ammo_counts[index] = g_weapon_table[g_item_slot_to_record[index]].f8E;
}

/* Counts how many entries follow the first entry of the chain that contains the given slot. */
int menu_count_chain_entries_after_head(int index)
{
    int count = 0;
    int i = index;
    while (g_weapon_table[i].prev != 0) i = g_weapon_table[i].prev;
    if (g_weapon_table[i].next != 0) {
        do {
            i = g_weapon_table[i].next;
            count++;
        } while (g_weapon_table[i].next != 0);
    }
    return count;
}

/* Moves a slot to the entry that is n steps along its chain, if the chain is long enough. Returns 1 on success. */
int menu_seek_chain_entry(int slot, int n)
{
    int result = 0;
    int i = slot;
    int k;
    if (menu_count_chain_entries_after_head(i) >= n) {
        while (g_weapon_table[i].prev != 0) i = g_weapon_table[i].prev;
        if (n > 0) {
            for (k = n; k != 0; k--) i = g_weapon_table[i].next;
        }
        g_item_slot_to_record[slot] = (unsigned char)i;
        result = 1;
    }
    return result;
}
