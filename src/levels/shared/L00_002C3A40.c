#include "names.h"
extern int func_L00_002C3A78(void);

/* The offset that goes with the state func_L00_002C3A78 reports: none in state 2, 12 otherwise.
 * The zeroing block sits out of line, which -frac2-keep-block-order preserves; the delay-slot
 * pass then absorbs it into the branch-likely slot and the jump around it disappears. */
/* Gives the step size for the current input: 0 when the direction check says 2, otherwise 12. */
int func_L00_002C3A40(void)
{
    int result = 12;
    int direction = ClassifyHeroInputDirection();

    goto test;
zero:
    result = 0;
    goto done;
test:
    if (direction == 2)
        goto zero;
done:
    return result;
}
