#include "include_asm.h"
#include "names.h"

extern void F46b43b72_FUN_002B7CE0(int value);
extern void load_class_into_cache_slot(int a0, int a1);

void func_PAL_00294EF8(void *a0, void *a1)
{
    F46b43b72_FUN_002B7CE0(1);
    load_class_into_cache_slot(a0, a1);
    F46b43b72_FUN_002B7CE0(1);
}

