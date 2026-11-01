#include "include_asm.h"

extern int func_L00_002C3A78(void);

/* The offset that goes with the state func_L00_002C3A78 reports: none in state 2, 12 otherwise.
 * The zeroing block sits out of line, which -frac2-keep-block-order preserves; the delay-slot
 * pass then absorbs it into the branch-likely slot and the jump around it disappears. */
int func_PAL_L00_002C3BE0(void)
{
    int r = 10;
    int x = func_L00_002C3A78();

    goto test;
zero:
    r = 0;
    goto done;
test:
    if (x == 2)
        goto zero;
done:
    return r;
}
