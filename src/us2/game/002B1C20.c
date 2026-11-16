#include "include_asm.h"
#include "names.h"

extern unsigned char g_level_progress_flags[28][4];

extern int save_count_entries_above_threshold_us2(int index);

extern int g_level_value_table[21];

/* Sums the counts of every entry but 26, and clamps the total to 0..40. */
int save_count_filled_slots_us2(void)
{
    int count = 0;
    int i;

    for (i = 0; i < 28; i++) {
        if (i != 26) {
            count += save_count_entries_above_threshold_us2(i);
        }
    }
    if (count < 0) {
        count = 0;
    }
    if (count > 40) {
        count = 40;
    }
    return count;
}

/* Counts the non-zero bytes of a 4-byte table entry, entry 2 also counting entry 26, and clamps
   the count to 0..40. */
int save_count_entries_above_threshold_us2(int index)
{
    int count = 0;
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        if (g_level_progress_flags[index][i] != 0) {
            count++;
        }
    }
    if (index == 2) {
        for (j = 0; j < 4; j++) {
            if (g_level_progress_flags[26][j] != 0) {
                count++;
            }
        }
    }
    if (count < 0) {
        count = 0;
    }
    if (count > 40) {
        count = 40;
    }
    return count;
}

/* Entry of a 21-entry table, 0 past its end. */
int level_get_table_value_us2(unsigned int index)
{
    if (index < 21) {
        return g_level_value_table[index];
    }
    return 0;
}
