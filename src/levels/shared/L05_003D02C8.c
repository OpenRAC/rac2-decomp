#include "include_asm.h"

extern int D_L05_001FB220[];
#include "common.h"
extern int D_L05_001B251C MACRO_ADDR;

/* Sets the active flag on every object listed in the object's link list. */
void func_L05_003D02C8(char *obj)
{
    int base = D_L05_001FB220[(unsigned char)obj[0x21]];
    unsigned short *p;

    if (base == 0)
        return;
    p = (unsigned short *)base;
    do {
        int tbl = D_L05_001B251C;

        *(char *)(tbl + ((int)*p & 0x7FFF) * 256 + 0x20) = 1;
    } while (*(short *)p++ >= 0);
}
