#include "names.h"
/* func_0028AB20: counts the 8-byte records of the table at 0x1B188C up to the one whose
 * first halfword is the given value or the 0xFFFF end; the end record is counted too
 * (retail increments in the delay slot of the end test). The table pointer is an sda
 * word, read with the lw macro, and both early exits share the one return. */
typedef unsigned short u16;

extern u16 *g_hud_element_table __attribute__((sda));

/* Finds the position of the entry with this id in the 8-byte entry table and returns it. */
int hud_find_entry_index(int value)
{
    u16 *table = g_hud_element_table;
    int count = 0;

    if (table[0] != 0xFFFF && table[0] != value) {
        u16 *p = table;

        do {
            p += 4;
            count++;
        } while (p[0] != 0xFFFF && p[0] != value);
    }
    return count;
}
