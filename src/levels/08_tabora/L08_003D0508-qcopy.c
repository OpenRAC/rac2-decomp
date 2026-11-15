#include "common.h"

extern void FastVecSub(void *out, void *first, void *second);
extern void mat_combine_and_store(void *out, void *position, void *rotation, void *direction);

/* Keeps a trail effect attached to the object by feeding it how far the object moved since last frame. */
void trail_follow_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float movement[4] __attribute__((aligned(16)));
    if (moby[0x20] == 0) {
        qcopy(vars + 0x90, moby + 0x10);
        *(s32 *)(vars + 0x8C) |= 1;
        *(u16 *)(vars + 0x3E) = 15;
        *(u8 **)(vars + 8) = vars + 0x50;
        *(u8 **)vars = vars + 0x20;
        moby[0x20] = 1;
        *(u16 *)(moby + 0x34) |= 0x20;
    }
    FastVecSub(movement, moby + 0x10, vars + 0x90);
    mat_combine_and_store(vars + 0x50, movement, moby + 0xF0, moby + 0xF0);
    qcopy(vars + 0x90, moby + 0x10);
}
