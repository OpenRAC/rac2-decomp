/* Initializes the movement state, full position and sixteen-byte zeroed vector. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B23E8 __attribute__((sda));

extern void moby_set_state(char *, int, int);

/* Starts the object moving along a path from a given start position. */
void moby_start_path_movement(char *moby, char *path, char *startPos)
{
    char *state = *(char **)(moby + 0x68);

    *(s32 *)(state + 0xA8) = (s32)(D_L20_001B23E8 * 60.0f);
    *(char **)(state + 0xA4) = path;
    *(s32 *)(state + 0xAC) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(s32 *)(moby + 0x98) = *(s32 *)(*(char **)(moby + 0x24) + 0x10);
    qcopy((moby + 0x10), startPos);
    *(f32 *)(moby + 0x18) = *(f32 *)(moby + 0x18) + 0.5f;
    qzero((state + 0x50));
    moby_set_state(moby, 2, -1);
}
