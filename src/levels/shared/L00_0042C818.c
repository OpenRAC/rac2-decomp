#include "include_asm.h"
#include "names.h"

extern int ref_L01_0042F820_00;

/* Returns a value stored by another level. */
int level_get_pending_value(void)
{
    return ref_L01_0042F820_00;
}


/* Clears the pending pointer the level keeps at +0x1FC0. */
void level_clear_pending_pointer(void *a0) {
    int *p = *(int **)((char *)a0 + 0x1FC0);
    *p = 0;
}
