#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed int s32;
extern s32 g_level_offer_entry_count __attribute__((sda));
extern u8 *g_level_entry_lists[] __attribute__((nosda));
extern void entry_spawn_list_objects_with_flag(void *, void *);

/* Offers every live entry to the handler that takes one pointer through the loop. */
void level_offer_entries_ptr_pal(u8 *a0) {
    s32 i;
    for (i = 0; i < g_level_offer_entry_count; i++) {
        entry_spawn_list_objects_with_flag(g_level_entry_lists[i], a0);
    }
}
