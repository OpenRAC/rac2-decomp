#include "include_asm.h"

extern void func_002AEF28(void *a0, void *a1, void *a2, float f12, float f13, float f14);
extern char D_00189E20_2[];

/* func_L00_002A70F8 is defined in L00_002A70F8-glow.c. */

/* func_L00_002A74A8 is defined in L00_002A74A8-tint.c. */


/* runs a three-float setup over two resident blocks when the mode is 124, then publishes a
   height once two resident flags are clear */
void func_PAL_L00_002A75A0(void)
{
    char *base = D_00189E20_2;

    if (*(int *)(base + 0x2294) == 124)
        func_002AEF28(*(void **)(base + 0x2290), base + 0x7B0, base + 0x7B4,
                      0.174532949924469f, 0.031415932f, 0.04188791f);
    if (*(short *)(base + 0x6BC) == 0)
        return;
    if (*(int *)(base + 0x660) != 0)
        return;
    *(float *)(*(char **)(base + 0x2290) + 0xF4) = *(float *)(base + 0x6B0);
}
