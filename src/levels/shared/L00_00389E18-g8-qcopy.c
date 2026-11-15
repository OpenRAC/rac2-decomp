#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

extern float ref_L00_00389E18_00 __attribute__((sda));
extern void func_00282CC0(void *a, void *b, void *c);
extern void func_002FE880(void *a, void *b, float c);
extern int func_002761F8(void *a, void *b, int c, void *d, int e);

/* The level's copy of func_00304AD0: same body, the $gp word is the level's. */
/* Moves the projectile forward and checks if it hit something; if so it switches to its hit state. */
void func_L00_00389E18(void *moby)
{
    void *owner = moby;
    void *target = (char *)owner + 0x10;
    void *source = *(void **)((char *)owner + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)target;
    FastVecAdd(target, target, source);
    AddObjectDirectionScaled(target, source, ref_L00_00389E18_00 * 2.7777778e-05f);
    if (CollLine(&local, target, 0x10, owner, 0) != 0)
        *(unsigned char *)((char *)owner + 0x20) = 8;
}
