#include "common.h"

extern void moby_set_state(void *object, int state, int arg2);

/* Sets two flag bits on the object when it first appears, then moves it to state 1. */
void moby_init_flags_advance_state(u8 *moby) {
    if (moby[0x20] == 0) {
        u16 newFlags = *(u16 *)(moby + 0x34) | 0x41;
        *(u16 *)(moby + 0x34) = newFlags;
        moby_set_state(moby, 1, -1);
    }
}
