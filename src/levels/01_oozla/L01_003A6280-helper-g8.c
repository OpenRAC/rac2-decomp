#include "common.h"

extern void *func_0029EFD0(int);

extern void func_002A0F48(void *);

/* Spawns a helper object linked to a parent object and puts it at the given position. Returns the new object, or nothing if it could not be made. */
void *func_L01_003A6280(u8 *parent, void *position, u32 param, f32 sizeScale, f32 extraValue) {
    u8 *spawned = (u8 *)CreateMoby(0x660 /* moby class 1632 */);
    u8 *vars;

    if (spawned != 0) {
        spawned[0x30] = parent[0x30];
        vars = *(u8 **)(spawned + 0x68);
        *(u16 *)(spawned + 0x32) = *(u16 *)(parent + 0x32);
        spawned[0x31] = 1;
        spawned[0x20] = 0;
        *(u32 *)(vars + 0x50) = (u32)parent;
        *(f32 *)(spawned + 0x2C) = *(f32 *)(*(u32 *)(spawned + 0x24) + 0x24) * sizeScale;
        qcopy((spawned + 0x10), position);
        if (parent != 0) {
            *(u32 *)(vars + 0x54) = *(s16 *)(parent + 0xAA);
        }
        *(f32 *)(vars + 0x58) = extraValue;
        *(u32 *)(vars + 0x5C) = param;
        func_002A0F48(spawned);
    }
    return spawned;
}
