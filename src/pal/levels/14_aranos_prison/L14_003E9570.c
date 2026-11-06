#include "include_asm.h"
#include "common.h"

extern void func_321F58();

static inline s16 RingEntry(s16 *ring, int i)
{
    return ring[i];
}

static inline int RingPending(s16 *ring, s16 index)
{
    s16 timer = RingEntry(ring, 10);
    s16 entry = RingEntry(ring, index);
    int limit = ((s32)entry * 5 + 2) / 6;
    return timer < limit;
}

/* func_PAL_L14_003E9570, the PAL copy of func_L14_003E50B8: the same walk over the ring, where each
 * entry takes the 50 Hz scale. The scale makes the loop test too long for jump1 to copy in front of
 * the loop (more than 30 insns), so loop.c hoists first and the test is copied afterwards. */
void func_PAL_L14_003E9570(char *object)
{
    s16 *ring = *(s16 **)(object + 0x68);
    s16 index = ring[11];
    while (RingPending(ring, index)) {
        ring[11] = (index + 1) % 8;
        index = ring[11];
    }
    if (((u16)ring[11] & 1) == 0) {
        if (*(u8 *)(object + 0x20) != 1)
            func_321F58(object, 1, -1);
    } else {
        if (*(u8 *)(object + 0x20) != 2)
            func_321F58(object, 2, -1);
    }
}
