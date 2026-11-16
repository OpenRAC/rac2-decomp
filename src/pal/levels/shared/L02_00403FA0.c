#include "include_asm.h"

#include "common.h"
extern int PadPressedWithin(int, int, int);
extern void moby_set_state(void *, int, int);

/* Allocates sixteen of sixty with no owner; on success attaches A0 as kind two. */
/* Moves the object to state 2 when the pad is pressed (PAL: 50 frame window). */
void moby_try_alloc_enter_state2_pal(void *moby) {
    if (PadPressedWithin(16, 50, 0))
        moby_set_state(moby, 2, -1);
}

