#include "include_asm.h"
#include "names.h"
typedef struct { char pad[12]; int state; int pad10; int handle; char rest[200]; } RequestRow224;
extern unsigned char g_item_slot_to_record[];
extern RequestRow224 g_weapon_table[];
extern short g_sequence_active_flag;
extern int g_slot_index_first, g_slot_index_second, g_slot_index_third, g_slot_index_fourth;
extern int load_is_class_cached(int);
extern void LoadClassIntoFreeCacheSlot(int);
/* Finds the request slot for an index and records the index by the slot state. It starts the
   request if it is idle. Returns 1 if the slot was handled. */
int moby_handle_request_slot_state(int index)
{
    RequestRow224 *rows = g_weapon_table;
    unsigned char *key = g_item_slot_to_record + index;
    int result = 0;
    int state = rows[*key].state;
    if (state == 0) {
        if (!load_is_class_cached(rows[*key].handle) && g_sequence_active_flag) goto done;
        g_slot_index_first = index;
        if (!load_is_class_cached(rows[*key].handle)) LoadClassIntoFreeCacheSlot(rows[*key].handle);
        result = 1;
    } else if (state == 3) { g_slot_index_fourth = index; result = 1; }
    else if (state == 2) { g_slot_index_third = index; result = 1; }
    else if (state == 1) { g_slot_index_second = index; result = 1; }
done:
    return result;
}