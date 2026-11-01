#include "include_asm.h"

#include "common.h"
extern int func_L00_0032EF10(int, int, int);
extern void func_002A7750(void *, int, int);

/* Allocates sixteen of sixty with no owner; on success attaches A0 as kind two. */
void func_PAL_L02_00403FA0(void *a0) {
    if (func_L00_0032EF10(16, 50, 0))
        func_002A7750(a0, 2, -1);
}

