#include "common.h"

extern void func_002A7750(void *object, int state, int arg2);

/* Sets two flag bits on the object when it first appears, then moves it to state 1. */
void func_L22_003D0840(u8 *moby) {
    if (moby[0x20] == 0) {
        u16 newFlags = *(u16 *)(moby + 0x34) | 0x41;
        *(u16 *)(moby + 0x34) = newFlags;
        SetMobyState(moby, 1, -1);
    }
}
