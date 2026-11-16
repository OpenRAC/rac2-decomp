#include "include_asm.h"

#include "common.h"
extern float g_path_movement_seconds __attribute__((sda));
extern void moby_set_state(char *, int, int);

/* Starts the object moving along a path from a given start position (PAL: 50 Hz frame count). */
void moby_start_path_movement_pal(char *moby, char *path, char *start_pos)
{
    char *state = *(char **)(moby + 0x68);

    *(s32 *)(state + 0xA8) = (s32)(g_path_movement_seconds * 5e+01f);
    *(char **)(state + 0xA4) = path;
    *(s32 *)(state + 0xAC) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(s32 *)(moby + 0x98) = *(s32 *)(*(char **)(moby + 0x24) + 0x10);
    qcopy((moby + 0x10), start_pos);
    *(f32 *)(moby + 0x18) = *(f32 *)(moby + 0x18) + 0.5f;
    qzero((state + 0x50));
    moby_set_state(moby, 2, -1);
}
