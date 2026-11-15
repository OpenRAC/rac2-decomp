/* func_00279B70: the per-level table is a two-dimensional array (0x400 bytes a level) and
 * the level index an sda word, read with the lw macro as retail does.
 * Takes a three-bit field out of the byte at the given index (the high nibble's low three
 * bits for an odd index, the low three bits for an even one), looks that field up in a
 * table, and scales the byte found there: times the scale, over 100. */
#include "common.h"

extern u8 D_0019B4A8[][0x400];
extern int D_001A79F0 __attribute__((sda));

/* Looks up a stat byte for a nibble and scales it by a percentage. */
int func_00279B70(u8 *table, int scale, int index)
{
    int packed = D_0019B4A8[gCurrentMapIndex][index >> 1];

    return (table[(index & 1) ? ((packed >> 4) & 7) : (packed & 7)] * scale) / 100;
}
