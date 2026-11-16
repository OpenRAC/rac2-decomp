#include "common.h"

extern int g_copy_source_index __attribute__((sda));
extern int g_copy_dest_index __attribute__((sda));
extern float g_museum_water_heights[];

/* Advance the interior of the 24-by-24 height field, then exchange its banks. */
void StepMuseumHeightField(void)
{
    int source = g_copy_source_index * 0x900;
    int destination = g_copy_dest_index * 0x900;
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
            float sum = *(float *)(previous+at+(char *)g_museum_water_heights)
                     +*(float *)(next+at+(char *)g_museum_water_heights)
                     +*(float *)(current+at-8+(char *)g_museum_water_heights)
                     +*(float *)(current+at+(char *)g_museum_water_heights)
                     +*(float *)(previous+at-4+(char *)g_museum_water_heights)
                     +*(float *)(previous+at+4+(char *)g_museum_water_heights)
                     +*(float *)(next+at-4+(char *)g_museum_water_heights)
                     +*(float *)(next+at+4+(char *)g_museum_water_heights);
            float *cell = (float *)(out+at+(char *)g_museum_water_heights);
            float value = sum * 0.25f - *cell;
            *cell = value - value * 0.0625f;
        }

        row = nextRow;
    } while (row < 23);
    {
        int old = g_copy_source_index;
        int other = g_copy_dest_index;
        g_copy_dest_index = old;
        g_copy_source_index = other;
    }
}
