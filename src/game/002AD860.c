#include "include_asm.h"
#include "names.h"
typedef struct { char pad[12]; int state; int pad10; int handle; char rest[200]; } RequestRow224;
extern unsigned char g_item_slot_to_record[];
extern RequestRow224 g_weapon_table[];
extern short D_001A63AC;
extern int D_0018C0E8, D_0018C0EC, D_0018C0F0, D_0018C0F4;
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
        if (!load_is_class_cached(rows[*key].handle) && D_001A63AC) goto done;
        D_0018C0E8 = index;
        if (!load_is_class_cached(rows[*key].handle)) LoadClassIntoFreeCacheSlot(rows[*key].handle);
        result = 1;
    } else if (state == 3) { D_0018C0F4 = index; result = 1; }
    else if (state == 2) { D_0018C0F0 = index; result = 1; }
    else if (state == 1) { D_0018C0EC = index; result = 1; }
done:
    return result;
}