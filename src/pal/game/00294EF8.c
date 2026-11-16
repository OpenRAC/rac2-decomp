#include "include_asm.h"
#include "names.h"

extern short F46b43b72_FUN_002B7CE0(int value);
extern void load_class_into_cache_slot(int a0, int a1);

void load_class_into_cache_slot_synced_pal(void *a0, void *a1)
{
    F46b43b72_FUN_002B7CE0(1);
    load_class_into_cache_slot(a0, a1);
    F46b43b72_FUN_002B7CE0(1);
}

