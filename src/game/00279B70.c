/* func_00279B70: the per-level table is a two-dimensional array (0x400 bytes a level) and
 * the level index an sda word, read with the lw macro as retail does.
 * Takes a three-bit field out of the byte at the given index (the high nibble's low three
 * bits for an odd index, the low three bits for an even one), looks that field up in a
 * table, and scales the byte found there: times the scale, over 100. */
#include "common.h"

extern u8 D_0019B4A8[][0x400];
extern int D_001A79F0 __attribute__((sda));

/* Returns a percentage of a1 taken from a small table indexed by the current mode and a2. */
int func_00279B70(u8 *a0, int a1, int a2)
{
    int c = D_0019B4A8[D_001A79F0][a2 >> 1];

    return (a0[(a2 & 1) ? ((c >> 4) & 7) : (c & 7)] * a1) / 100;
}
