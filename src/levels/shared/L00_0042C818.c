#include "include_asm.h"

extern int ref_L01_0042F820_00;

/* Returns a value stored by another level. */
int func_L00_0042C818(void)
{
    return ref_L01_0042F820_00;
}


/* Clears the pending pointer the level keeps at +0x1FC0. */
void func_L00_0042D9D0(void *a0) {
    int *p = *(int **)((char *)a0 + 0x1FC0);
    *p = 0;
}
