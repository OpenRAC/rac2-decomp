#include "include_asm.h"

#include "common.h"

/* Clear both entry tables and reset the record state. */
void func_PAL_L00_00418190(char *object)
{
    char *state = *(char **)(object + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        *(int *)(*(char **)(state + 0) + i * 16 + 0) = 0;
        *(int *)(*(char **)(state + 0) + i * 16 + 4) = 0;
        *(int *)(*(char **)(state + 0) + i * 16 + 8) = 0;
        *(float *)(*(char **)(state + 0) + i * 16 + 12) = 1.0f;
    }

    for (i = 0; i < 20; i++) {
        *(int *)(*(char **)(state + 4) + i * 16 + 0) = 0;
        *(int *)(*(char **)(state + 4) + i * 16 + 4) = 0;
        *(int *)(*(char **)(state + 4) + i * 16 + 8) = 0;
        *(float *)(*(char **)(state + 4) + i * 16 + 12) = 1.0f;
    }

    *(int *)(state + 0xC) = 0;
    *(short *)(state + 0x1C) = 5;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x8) = 0;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00418250);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00418768);
