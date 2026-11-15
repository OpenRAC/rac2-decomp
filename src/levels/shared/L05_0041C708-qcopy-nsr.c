#include "common.h"

extern char *func_0029EFD0(int kind);
extern void func_002A0F48(char *a0);

/* Arms the rung the factory returns: stamps the five flag bytes, binds the owner and the handle,
 * copies the owner's position and three matrix rows into the rung, folds the rate, then starts it. */
/* Creates a part object of the given class next to its owner. It copies the owner's position and turn, and the mirror flag marks the second, flipped copy. */
char *func_L05_0041C708(char *owner, char *mirror, int kind, f32 sizeScale)
{
    char *part = CreateMoby(kind);
    char *partVars;
    char *srcRow;
    char *dstRow;
    int i;

    if (part != 0) {
        partVars = *(char **)(part + 0x68);
        *(u8 *)(part + 0x30) = 0xFF;
        *(u16 *)(part + 0x32) = 0xFF;
        *(u8 *)(part + 0x31) = 1;
        *(u16 *)(part + 0x34) |= 0x100;
        *(u8 *)(part + 0x20) = 0;
        *(char **)partVars = owner;
        qcopy(part + 0x10, owner + 0x10);
        i = 0;
        srcRow = owner + 0xC0;
        dstRow = part + 0xC0;
        for (; i < 3; i++) {
            qcopy(dstRow, srcRow);
            srcRow += 16;
            dstRow += 16;
        }
        *(f32 *)(part + 0x2C) = *(f32 *)(*(char **)(part + 0x24) + 0x24) * sizeScale;
        *(char **)(partVars + 4) = mirror;
        func_002A0F48(part);
    }
    return part;
}
