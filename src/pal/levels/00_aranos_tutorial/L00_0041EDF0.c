#include "include_asm.h"

#include "common.h"

void func_PAL_L00_0041EDF0(char *p)
{
    if (*(unsigned char *)(p + 0x20) == 0) {
        *(unsigned short *)(p + 0x34) |= 0x800;
        *(unsigned char *)(p + 0x20) = 1;
    }
}

