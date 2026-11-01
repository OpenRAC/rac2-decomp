#include "include_asm.h"

extern void F70997ba9_FUN_002FC560(int a, int b);
extern void F70997ba9_FUN_0027C540(int a);
extern void *F70997ba9_FUN_00288FB8(int id);
extern int F70997ba9_FUN_0027F198(void *p, int i);
extern void F70997ba9_FUN_0027F120(void);
extern void F70997ba9_FUN_0027F5B8(int a, int b, long c, void *d, int e);
extern void F70997ba9_FUN_0027F110(void);
extern void F70997ba9_FUN_0027C660(void);

int func_PAL_002DA4B8(int *arg0)
{
    int min;
    int v;
    int slot;
    int count;
    int off;

    F70997ba9_FUN_002FC560(66, 68);
    F70997ba9_FUN_002FC560(71, 11);
    F70997ba9_FUN_0027C540(0);
    min = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(2926), -1);
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(2938), -1);
    if (v >= min)
        min = v;
    if (*(int *)0x1A7A78 != 0) {
        v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(2927), -1);
        if (v >= min)
            min = v;
    }
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(2939), -1);
    if (v >= min)
        min = v;
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(2940), -1);
    if (v >= min)
        min = v;
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(2912), -1);
    if (v >= min)
        min = v;
    slot = (arg0[8] - min) >> 1;
    if (slot <= 1)
        slot = 2;
    count = arg0[9] / (*(int *)0x1A7A78 != 0 ? 7 : 6);
    F70997ba9_FUN_0027F120();
    off = count - 6;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(2926), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(2938), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(2939), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(2940), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(2912), -1);
    F70997ba9_FUN_0027F110();
    F70997ba9_FUN_0027C660();
    return 2;
}


