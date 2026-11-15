#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

/* Places the electric orb at a position and sets its mode. */
void func_L20_0039F210(char *moby, char *position, int mode) {
    char *dst = moby + 0x10;
    char *state;

    *(TI128 *)dst = *(TI128 *)position;
    state = *(char **)(moby + 0x68);
    *(int *)(state + 0xC) = mode;
    *(int *)state = 5;
}
