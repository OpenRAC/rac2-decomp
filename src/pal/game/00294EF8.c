#include "include_asm.h"
#include "names.h"

extern short F46b43b72_FUN_002B7CE0(int value);
extern void load_class_into_cache_slot(int a0, int a1);

/* Loads a class into a cache slot, waiting for pending disc reads before and after. */
void load_class_into_cache_slot_synced_pal(void *id, void *slot_index)
{
    F46b43b72_FUN_002B7CE0(1);
    load_class_into_cache_slot(id, slot_index);
    F46b43b72_FUN_002B7CE0(1);
}

