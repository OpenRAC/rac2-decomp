#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned int u32;

extern f32 g_water_texture_coords[];

/* divides FACTOR by the table's sixteenth entry and scales the whole table by it */
void water_normalize_table(f32 factor) {
    f32 scale = factor / g_water_texture_coords[0x10];
    u32 i;

    for (i = 0; i < 0x5C; i++)
        g_water_texture_coords[i] = g_water_texture_coords[i] * scale;
}
