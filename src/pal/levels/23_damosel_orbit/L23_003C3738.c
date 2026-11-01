#include "include_asm.h"


extern void func_323FF0(char *, int, int, int);

void func_PAL_L23_003C3868(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5) {
    char *state = *(char **)(arg0 + 0x68);

    if (arg4 & 1)
        func_323FF0(arg0, arg1, 0, 3);
    if (arg4 & 2)
        func_323FF0(*(char **)(state + 0x2A0), arg1, 0, 3);
}

