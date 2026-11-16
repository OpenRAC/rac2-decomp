#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

/* Places the electric orb at a position and sets its mode. */
void electric_orb_set_position_mode_pal(char *orb, char *position, int mode) {
    char *dst = orb + 0x10;
    char *state;

    *(TI128 *)dst = *(TI128 *)position;
    state = *(char **)(orb + 0x68);
    *(int *)(state + 0xC) = mode;
    *(int *)state = 4;
}
