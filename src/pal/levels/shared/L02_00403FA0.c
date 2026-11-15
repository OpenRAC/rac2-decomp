#include "include_asm.h"

#include "common.h"
extern int PadPressedWithin(int, int, int);
extern void moby_set_state(void *, int, int);

/* Allocates sixteen of sixty with no owner; on success attaches A0 as kind two. */
void func_PAL_L02_00403FA0(void *a0) {
    if (PadPressedWithin(16, 50, 0))
        moby_set_state(a0, 2, -1);
}

