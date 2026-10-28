/* func_00342978 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/game/00342978-g8.c: 576/584 bytes.
 * US: 0/28 local places; PAL: 0/28 local places; US2: 0/28 local places.
 * No strict linked build was run because no local placement matched.
 * Scroll, state and loop-bound GPR allocation and loop fill differ. Guarded bound captures and separate value lifetimes did not close it. Reopen with allocator evidence.
 */

#include "common.h"

extern int func_002E5E58(int, unsigned int, void *);
extern int D_001AE1CC __attribute__((sda));

int func_00342978(void *owner, int flags)
{
    char *p = owner;
    int index;
    int scroll;
    int state;
    int limit;
    int final_state;
    *(int *)(p + 0x94) += 1;
    switch (*(int *)(p + 0x18)) {
    case 0:
        if ((flags & 0x1000) && *(int *)(p + 0x14) > 0) {
            func_002E5E58(3, 0, 0);
            *(int *)(p + 0x1C) = 1;
            *(int *)(p + 0x18) = 1;
            break;
        }
        if ((flags & 0x4000) && *(int *)(p + 0x14) < *(int *)(p + 0x10) - 1) {
            func_002E5E58(3, 0, 0);
            *(int *)(p + 0x18) = 1;
            *(int *)(p + 0x1C) = 0;
        }
        break;
    case 1:
        *(int *)(p + 0x18) = 2;
        *(int *)(p + 0x90) = 0;
    case 2:
        scroll = *(int *)(p + 0x90);
        if (*(int *)(p + 0x1C) == 0) scroll -= 4;
        else scroll += 4;
        *(int *)(p + 0x90) = scroll;
        if ((float)scroll >= *(float *)(p + 0xC) || (float)scroll <= -*(float *)(p + 0xC)) {
            if (*(int *)(p + 0x1C) == 0) index = ++*(int *)(p + 0x14);
            else index = --*(int *)(p + 0x14);
            *(int *)(p + 0x14) = index;
            if (index < 0) *(int *)(p + 0x14) = 0;
            if (*(int *)(p + 0x14) > *(int *)(p + 0x10) - 1)
                *(int *)(p + 0x14) = *(int *)(p + 0x10) - 1;
            state = flags ? *(int *)(p + 0x18) : 0;
            *(int *)(p + 0x18) = state;
            final_state = 0;
            if (*(int *)(p + 0x14) != 0)
                final_state = *(int *)(p + 0x14) == *(int *)(p + 0x10) - 1 ? 0 : state;
            *(int *)(p + 0x18) = final_state;
            *(int *)(p + 0x90) = 0;
        }
        break;
    }
    *(int *)(p + 0x20) = 0;
    index = *(int *)(p + 0x14);
    if (index > 0) {
        limit = -D_001AE1CC;
        if (limit < 0) {
            do {
                index--;
                *(int *)(p + 0x20) -= 1;
            } while (index > 0 && *(int *)(p + 0x20) > limit);
        }
    }
    *(int *)(p + 0x24) = 0;
    index = *(int *)(p + 0x14);
    state = *(int *)(p + 0x10) - 1;
    if (index < state) {
        limit = D_001AE1CC;
        if (limit > 0) {
            do {
                index++;
                *(int *)(p + 0x24) += 1;
            } while (index < state && *(int *)(p + 0x24) < limit);
        }
    }
    return 0;
}