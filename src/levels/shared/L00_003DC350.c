#include "include_asm.h"
#include "common.h"

extern int *D_L00_001B2B20[] MACRO_ADDR;
extern int *D_L00_001B2B24[] MACRO_ADDR;
extern int *D_L00_001B2B28[] MACRO_ADDR;

/* Clears three effect buffers back to zero. */
void func_L00_003DC350(void)
{
    int *p;
    int i;

    p = D_L00_001B2B20[0] + 60;
    for (i = 3; i >= 0; i--) { *p = 0; p -= 16; }

    p = D_L00_001B2B24[0] + 4799;
    for (i = 149; i >= 0; i--) { *p = 0; p -= 32; }

    p = D_L00_001B2B28[0];
    for (i = 9; i >= 0; i--) { p[1] = 0; p[0] = 0; p += 4; }
}
