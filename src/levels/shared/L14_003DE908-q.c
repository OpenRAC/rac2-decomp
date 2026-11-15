#include "include_asm.h"
#include "common.h"

extern int func_L00_00324120(char *object);
extern int func_002761F8(void *a, void *b, int mode, void *self, int flag);
extern char D_00189EA0[];
extern int ref_L14_003DE908_00;

/* Tells whether the object is hit by the player or by the aim ray. */
int func_L14_003DE908(char *moby)
{
    char buf[0x20];

    if (IsCurrentSelectedId(moby) != 0)
        return 1;
    qcopy(buf, gHeroPosition);
    qcopy(buf + 0x10, gHeroPosition);
    *(float *)(buf + 0x18) = *(float *)(buf + 0x18) - 3.0f;
    if (CollLine(buf, buf + 0x10, 0x10, 0, 0) != 0 && ref_L14_003DE908_00 == (int)moby)
        return 1;
    return 0;
}
