#include "include_asm.h"
#include "names.h"



typedef unsigned char u8;
extern u8 g_save_baseline_count;
extern int F9a90bcc4_FUN_002A77E0(int count);
extern u8 g_smooth_value_flag __attribute__((sda));
extern u8 g_item_slot_to_record[];
extern u8 g_weapon_table[];
extern u8 g_item_enabled_flags[] __attribute__((sda));

/* func_002B1350 is defined in 002B00B0-reaction-g8.c. */

/* Picks one at random of the entries whose first byte matches, and returns its scaled values (PAL). */
int moby_pick_random_matching_pal(u8 *owner, int match_id, int *out_index,
                                       float *out0, float *out1, float *out2, float *out3,
                                       float *out4, float *out5, float *out6)
{
    int match_count;
    int count;
    int i;
    int pick;
    int remaining;
    u8 *record;

    match_count = 0;
    count = *(u8 *)(*(int *)(owner + 36) + 12);
    if (count != 0) {
        int *table_ptr = (int *)(*(int *)(owner + 36) + 72);
        u8 *slot_data;
        remaining = count;
        do {
            slot_data = *(u8 **)(*table_ptr + 20);
            if (slot_data != 0 && *slot_data == match_id)
                match_count++;
            table_ptr++;
            remaining--;
        } while (remaining != 0);
    }

    if (match_count != 0)
        goto second;

    return 0;

found:
    *out0 = *(float *)(record + 8) * 0.020000001f;
    *out1 = *(float *)(record + 12) * 0.020000001f;
    *out2 = *(float *)(record + 16) * 0.00040000002f;
    *out3 = *(float *)(record + 20) * 0.00040000002f;
    *out6 = *(float *)(record + 4) * 0.00040000002f;
    *out4 = *(float *)(record + 24);
    *out5 = *(float *)(record + 28);
    *out_index = i;
    return 1;

second:
    pick = F9a90bcc4_FUN_002A77E0(match_count);
    for (i = 0; i < *(u8 *)(*(int *)(owner + 36) + 12); i++) {
        char *table = (char *)(*(int *)(owner + 36) + 72);
        char *slot = *(char **)(table + i * 4);
        record = *(u8 **)(slot + 20);
        if (record == 0 || *record != match_id)
            continue;
        if (pick == 0)
            goto found;
        pick--;
    }
    return 0;
}


