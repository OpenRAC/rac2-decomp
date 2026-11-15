#include "include_asm.h"

extern int ref_L00_002F4398_00 __attribute__((sda));

/* Returns 1 when a flag word is set. */
int func_00288D30(void)
{
    return ref_L00_002F4398_00 != 0;
}
