#include "include_asm.h"
#include "common.h"
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* Spawns a small burst effect just above the object. */
void func_L09_003F7370(char *moby, float heightOffset)
{
    float position[4];
    qcopy(position, moby + 0x10);
    position[2] += heightOffset;
    SpawnExplosion(position, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.5f, 20.0f, 1, 0, 0, 0);
}
