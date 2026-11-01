#include "include_asm.h"

#include "common.h"
extern char D_00189EA0[];
extern int func_002ACBC8(char *, int);
extern int func_002A8508(int, int);
extern void *func_PAL_L00_002D7850(int);
extern void func_L00_002D7140(void *);
extern void func_L00_003B81D0(char *);

void func_PAL_L00_003BBFC8(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (func_002ACBC8(D_00189EA0, *(int *)state) != 0 && *(int *)(state + 0x28) == 0 && func_002A8508(*(int *)(state + 0x40), -1) != 0) {
        *(int *)(state + 0x2C) = (int)func_PAL_L00_002D7850(5);
        *(int *)(state + 0x28) = 1;
        func_L00_003B81D0(object);
    } else if (*(int *)(state + 0x28) != 0) {
        if (!func_002ACBC8(D_00189EA0, *(int *)state) || !func_002A8508(*(int *)(state + 0x40), -1)) {
            func_L00_002D7140(*(void **)(state + 0x2C));
            *(int *)(state + 0x28) = 0;
        }
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003BC098);
