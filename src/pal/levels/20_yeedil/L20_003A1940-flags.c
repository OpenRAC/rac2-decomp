#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

void func_PAL_L20_003A2180(char *arg0, char *arg1, int arg2) {
    char *dst = arg0 + 0x10;
    char *state;

    *(TI128 *)dst = *(TI128 *)arg1;
    state = *(char **)(arg0 + 0x68);
    *(int *)(state + 0xC) = arg2;
    *(int *)state = 4;
}
