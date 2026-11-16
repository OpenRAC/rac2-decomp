#include "include_asm.h"

#include "common.h"
typedef struct {
    s16 id;
    u8 pad02[0xE];
    u16 flags;
    s16 base;
    s16 names[8];
    s16 kind;
    s16 index;
} Entry_29DB28;
extern Entry_29DB28 *g_menu_active_entries[] __attribute__((sda));

/* List the live entries: their ids (or display names), a mask of the kind-2 ones and their values. */
int menu_list_active_entries_us2(int *ids, unsigned int *mask, int *values, int names)
{
    Entry_29DB28 *entry = g_menu_active_entries[0];
    int count = 0;
    int all = 1;
    *ids = 0;
    if (mask) *mask = 0;
    if (values) *values = -1;
    if (entry == 0) return 0;
    for (; entry->id != 0; entry++) {
        if (entry->kind != 2 && !(entry->flags & 2)) all = 0;
        if (entry->flags & 2) continue;
        if (entry->kind == 0) continue;
        if ((entry->flags & 1) && entry->kind == 2) continue;
        ids[count] = entry->id;
        if (names) ids[count] = entry->kind == 2 ? 0x31B9 : entry->names[entry->index];
        if (mask && entry->kind == 2) *mask |= 1 << count;
        if (values) {
            *values = entry->base + entry->index;
            values++;
        }
        count++;
    }
    if (mask && all) *mask |= 0x80000000;
    return count;
}

