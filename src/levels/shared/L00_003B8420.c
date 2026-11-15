#include "common.h"

extern char D_00189EA0[];

extern int func_002ACBC8(char *, int);

extern int func_002A8508(int, int);

extern void *func_L00_002D70A0(int);

extern void func_L00_002D7140(void *);

extern void func_L00_003B81D0(char *);

void func_L00_003B8420(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (IsPointInCuboid(D_00189EA0, *(int *)state) != 0 && *(int *)(state + 0x28) == 0 && func_002A8508(*(int *)(state + 0x40), -1) != 0) {
        *(int *)(state + 0x2C) = (int)func_L00_002D70A0(5);
        *(int *)(state + 0x28) = 1;
        func_L00_003B81D0(object);
    } else if (*(int *)(state + 0x28) != 0) {
        if (!IsPointInCuboid(D_00189EA0, *(int *)state) || !func_002A8508(*(int *)(state + 0x40), -1)) {
            func_L00_002D7140(*(void **)(state + 0x2C));
            *(int *)(state + 0x28) = 0;
        }
    }
}
