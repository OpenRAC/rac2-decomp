#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int);

/* Spawns an object of type 0x12F2 and fills its position and its sub-record vector. */
/* Creates a Yeedil shot at a position with a direction and a size, owned by another object. */
char *func_L20_0039C540(char *owner, char *position, char *direction, float radius) {
    char *vars;
    char *moby = CreateMoby(0x12F2 /* moby class 4850 */);

    if (moby != 0) {
        *(int *)(moby + 0xB8) = (int)owner;
        *(TI128 *)(moby + 0x10) = *(TI128 *)position;
        vars = *(char **)(moby + 0x68);
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(TI128 *)(vars + 0x10) = *(TI128 *)direction;
        *(float *)(vars + 0x2C) = radius;
        *(int *)(vars + 0x20) = 0x12C;
    }
    return moby;
}
