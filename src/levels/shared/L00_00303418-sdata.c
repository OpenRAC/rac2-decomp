#include "common.h"

extern unsigned char *g_tie_table __attribute__((sda));
extern unsigned char *g_tie_table_end __attribute__((sda));
extern unsigned char *g_shrub_table __attribute__((sda));
extern unsigned char *g_shrub_table_end __attribute__((sda));
extern unsigned char *g_moby_array_base __attribute__((sda));
extern unsigned char *g_moby_array_end_sentinel __attribute__((sda));
extern int level_find_first_accepted_entry(void *);

/* Shows or hides each object in three lists depending on whether it matches the selected item. */
void level_update_object_visibility(int selected)
{
    unsigned char *entry;
    for (entry = g_tie_table; entry != g_tie_table_end; entry += 0x20) {
        if (level_find_first_accepted_entry(entry) != selected)
            entry[0x1E] |= 4;
        else
            entry[0x1E] &= 0xFB;
    }
    for (entry = g_shrub_table; entry != g_shrub_table_end; entry += 0x20) {
        if (level_find_first_accepted_entry(entry) != selected)
            entry[0x16] |= 1;
        else
            entry[0x16] &= 0xFE;
    }
    for (entry = g_moby_array_base; entry != g_moby_array_end_sentinel; entry += 0x100) {
        if (*(s16 *)(entry + 0xAA) != 0) {
            if (level_find_first_accepted_entry(entry + 0x10) != selected)
                *(u16 *)(entry + 0x34) |= 0x80;
            else
                *(u16 *)(entry + 0x34) &= 0xFF7F;
        }
    }
}
