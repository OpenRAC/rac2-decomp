#include "common.h"

extern int D_001AEBB8 __attribute__((sda));
extern int D_001AEBBC __attribute__((sda));
extern float D_L30_00233A60[];

/* Advance the interior of the 24-by-24 height field, then exchange its banks. */
void func_L30_00382FB8(void)
{
    int source = D_001AEBB8 * 0x900;
    int destination = D_001AEBBC * 0x900;
    int sourceCenter = source + 4;
    int row, column;

    row = 1;
    do {
        int rowOffset = row * 0x60;
        int nextRow = row + 1;
        int current = rowOffset;
        int previous = (row - 1) * 0x60 + source;
        int next = nextRow * 0x60 + source;
        int out = rowOffset + destination;

        current += sourceCenter;
        for (column = 1; column < 23; column++) {
            int at = column * 4;
            float sum = *(float *)(previous+at+(char *)gMuseumWaterHeights)
                     +*(float *)(next+at+(char *)gMuseumWaterHeights)
                     +*(float *)(current+at-8+(char *)gMuseumWaterHeights)
                     +*(float *)(current+at+(char *)gMuseumWaterHeights)
                     +*(float *)(previous+at-4+(char *)gMuseumWaterHeights)
                     +*(float *)(previous+at+4+(char *)gMuseumWaterHeights)
                     +*(float *)(next+at-4+(char *)gMuseumWaterHeights)
                     +*(float *)(next+at+4+(char *)gMuseumWaterHeights);
            float *cell = (float *)(out+at+(char *)gMuseumWaterHeights);
            float value = sum * 0.25f - *cell;
            *cell = value - value * 0.0625f;
        }

        row = nextRow;
    } while (row < 23);
    {
        int old = D_001AEBB8;
        int other = D_001AEBBC;
        D_001AEBBC = old;
        D_001AEBB8 = other;
    }
}
