#include "include_asm.h"

extern int D_0018AA68;

/* Publishes the argument into the resident word, with 0xFFFFFFFF becoming 5. */
void func_PAL_L00_002D29D0(int value)
{
    if (value == -1)
        value = 4;
    D_0018AA68 = value;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002D29E8);
