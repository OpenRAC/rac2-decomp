#include "include_asm.h"

#include "common.h"
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* Spawns a small burst effect just above the object (PAL). */
void part_spawn_small_burst_pal(char *moby, float height_offset)
{
    float v[4];
    qcopy(v, moby + 0x10);
    v[2] += height_offset;
    SpawnExplosion_pal(v, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.5f, 20.0f, 1, 0, 0, 0);
}

