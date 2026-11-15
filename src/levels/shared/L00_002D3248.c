#include "names.h"
/* The resident block the level state lives in. */
extern char D_00189E20[];

/* Writes the level state's clock pair and its packed byte pair: the two floats at
 * +0x1430 and +0x1434, the short argument at +0x1438, the byte at +0x143C, and the
 * third and fourth byte arguments spliced into the halfword at +0x143E as
 * (old & ~arg3) | arg2. */
void func_L00_002D3248(short count, unsigned char byteValue, unsigned char setBits, unsigned char clearBits,
                       float clockA, float clockB)
{
    char *base = gHeroState;
    unsigned short old = *(unsigned short *)(base + 0x143E);

    *(float *)(base + 0x1434) = clockB;
    *(int *)(base + 0x1438) = count;
    *(short *)(base + 0x143C) = byteValue;
    *(short *)(base + 0x143E) = (short)((old & ~clearBits) | setBits);
    *(float *)(base + 0x1430) = clockA;
}
