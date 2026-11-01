#include "include_asm.h"


#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern int ref_L13_0040A480_00(void *);
extern char D_00189EA0[];

/* func_L13_0040A3B0 is matched in L13_0040A3B0.c (built with -frac2-zero-ti-barrier). */


void func_PAL_L13_0040EDF0(char *a0)
{
    char tmp[16];
    func_00282CF0(tmp, D_00189EA0, a0 + 0x10);
    func_L13_0040A3B0(a0, (void *)ref_L13_0040A480_00(a0), tmp, 0);
}

