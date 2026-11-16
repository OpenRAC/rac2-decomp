#include "include_asm.h"

#include "common.h"
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

void part_spawn_small_burst_pal(char *a0, float f)
{
    float v[4];
    qcopy(v, a0 + 0x10);
    v[2] += f;
    SpawnExplosion_pal(v, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.5f, 20.0f, 1, 0, 0, 0);
}

