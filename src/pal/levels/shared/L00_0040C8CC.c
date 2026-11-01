#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_0040D328);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_0040D990);

#include "common.h"
extern void func_002E6EF8(void (*f)(char *), char *arg);

/* shared native body of family af5b3bc3a678ed5c */
void func_PAL_L00_0040DF78(char *object)
{
    char *o = object;
    int *q = *(int **)(o + 104);

    if (*(unsigned char *)(o + 32))
        return;

    q[2] = 53;
    q[4] = 42;
    q[0] = 0;
    q[3] = -1;
    q[5] = 0;
    *(unsigned char *)(o + 32) = 1;
    q[6] = -1;

    *(float *)(o + 44) = *(float *)(*(int *)(o + 36) + 36) * 0.8f;
}

