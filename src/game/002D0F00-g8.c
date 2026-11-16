#include "include_asm.h"
#include "names.h"

/* func_002D0F00: a -G8 unit, so a word load of a global gives the base and the value one
 * register as retail does. The loop pointers are set up in the order whose schedule puts
 * the constant 1 before the destination, as retail has it. The clear address is an
 * integer sum so its operands come out in retail's order. */

extern char *g_resident_data_base;

extern int g_menu_unlock_flags[];

extern short g_movie_availability_table[];

extern unsigned int g_request_flag_table[];

extern unsigned char g_extras_unlocked_flag;

/* Marks each movie in the list as available if the player has seen it, or all of them when everything is unlocked. */
int movie_list_update_availability(void)
{
    unsigned int *seen_mask;
    unsigned char all_unlocked;
    char *entry_table;
    char *table_end;
    int clear_base;
    char *id_ptr;
    char *enabled_ptr;
    int clear_offset;
    int one;

    if (g_resident_data_base == 0)
        goto done;
    g_menu_unlock_flags[0] = 1;
    entry_table = (char *)g_movie_availability_table;
    seen_mask = g_request_flag_table;
    all_unlocked = g_extras_unlocked_flag;
    clear_base = (int)entry_table + 2;
    one = 1;
    enabled_ptr = entry_table + 8;
    id_ptr = entry_table + 6;
    table_end = entry_table + 0xC6;
    clear_offset = 6;
    do {
        int entry_id;
        if (all_unlocked != 0) {
            *(short *)enabled_ptr = one;
        } else {
            entry_id = *(short *)id_ptr;
            if (seen_mask[(unsigned int)entry_id >> 2] & (one << (entry_id & 31)))
                *(short *)enabled_ptr = one;
            else
                *(short *)(clear_offset + clear_base) = 0;
        }
        id_ptr += 6;
        enabled_ptr += 6;
        clear_offset += 6;
    } while ((int)id_ptr < (int)table_end);
done:
    return 0;
}
