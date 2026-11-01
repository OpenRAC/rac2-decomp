#include "include_asm.h"



#include "common.h"
extern char D_L12_001FEAC0[];
extern f32 func_00283248(f32 a, f32 b);
extern int func_PAL_002B5C98(char *a, char *b, f32 c);

/* Aim pass over the slot the 0x110 record names: measure the two position differences,
   turn them into an angle, hand the slot to the shared pass, and step the 0x224 cursor
   when the pass reports one of the 0x8F bits. */
s32 func_PAL_L12_0041F710(char *a0)
{
    char *s1 = a0;
    char *s2 = *(char **)(s1 + 0x68);
    char *tbl = D_L12_001FEAC0;
    s32 s0 = *(s32 *)(tbl + *(s32 *)(s2 + 0x110) * 4);
    s32 off = *(s32 *)(s2 + 0x224) << 4;
    char *src = (char *)off;
    char *p;
    int copy[4] __attribute__((aligned(16)));
    f32 dx;
    f32 dy;
    f32 r;
    s32 n;

    src += s0;
    src += 0x10;
    qcopy_nc(copy, src);
    p = (char *)s0 + off;
    dx = *(f32 *)(p + 0x10) - *(f32 *)(s1 + 0x10);
    dy = *(f32 *)(p + 0x14) - *(f32 *)(s1 + 0x14);
    r = func_00283248(dx, dy);
    if ((func_PAL_002B5C98(s1, (char *)s0 + ((*(s32 *)(s2 + 0x224) << 4) + 0x10), r) & 0x8F) != 0) {
        n = *(s32 *)(s2 + 0x224);
        if (n == *(s32 *)(s2 + 0x220))
            return 1;
        *(s32 *)(s2 + 0x224) = n + 1;
    }
    return 0;
}

