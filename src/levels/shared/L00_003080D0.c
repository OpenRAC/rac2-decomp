#include "names.h"
typedef struct Map80D0 {
    unsigned char pad00[0xc];
    unsigned char *bitmap;
    unsigned char pad10[0x18];
    int active;
    unsigned char pad2c[0xc];
    unsigned char *samples;
    unsigned char pad3c[0x174];
    unsigned char mask[32][4];
} Map80D0;
extern Map80D0 g_format_root;
extern int level_lookup_cache_entry(int);
extern int g_current_map_index __attribute__((sda));
extern int level_dispatch_event_once(void);
extern void map_convert_world_to_map_position(float, float, float *, float *, int);
/* Clears the unexplored-map bits around a world position wherever the map colour matches the colour at that spot. */
void coll_clear_map_bits_around_pos(float *position)
{
    float px, py;
    int x, y, maxY, maxX, minY, minX;
    int row, col;
    int colour;
    int regionRow, sampleRow;
    unsigned int sample;
    unsigned char *cell;
    int bit;
    if (g_format_root.active == 0)
        return;
    if (level_dispatch_event_once())
        return;
    map_convert_world_to_map_position(position[0], position[1], &px, &py, g_current_map_index);
    x = (int)(px * 512.0f) + 1;
    y = (int)(py * 512.0f) + 1;
    if (x < 0 || y < 0 || x >= 512 || y >= 512)
        return;
    minY = y - 16;
    minX = x - 16;
    maxY = y + 16;
    maxX = x + 16;
    if (minY < 0) minY = 0;
    if (maxY >= 512) maxY = 511;
    if (minX < 0) minX = 0;
    if (maxX >= 512) maxX = 511;
    regionRow = (y >> 5) * 16;
    level_lookup_cache_entry((x >> 5) + regionRow);
    sampleRow = y & 31;
    sampleRow *= 16;
    {
        unsigned char value;
        int index;
        sample = x & 31;
        index = (int)sample >> 1;
        value = *(g_format_root.samples + index + sampleRow);
        if (x & 1) value >>= 4;
        else value &= 15;
        colour = value;
    }
    for (row = minY; row < maxY; row++) {
        int dy;
        dy = row - y + 16;
        regionRow = (row >> 5) * 16;
        sampleRow = row & 31;
        sampleRow *= 16;
        for (col = minX; col < maxX; col++) {
            cell = g_format_root.bitmap + row * 64 + col / 8;
            if (*cell != 0) {
                bit = 1 << (col & 7);
                if (*cell & bit) {
                    int dx = col - x + 16;
                    if ((*(g_format_root.mask[0] + (dx / 8 + (dy << 2))) >> (dx % 8)) & 1)
                        continue;
                    level_lookup_cache_entry((col >> 5) + regionRow);
                    sample = (col & 31) / 2;
                    sample = *(g_format_root.samples + sample + sampleRow);
                    if (col & 1) sample >>= 4;
                    else sample &= 15;
                    if (colour == sample)
                        *cell &= ~bit;
                }
            }
        }
    }
}
