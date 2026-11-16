#include "include_asm.h"


#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern int ref_L13_0040A480_00(void *);
extern char g_hero_position[];

/* func_L13_0040A3B0 is matched in L13_0040A3B0.c (built with -frac2-zero-ti-barrier). */


void moby_turn_toward_hero_pal(char *a0)
{
    char tmp[16];
    FastVecSub(tmp, g_hero_position, a0 + 0x10);
    creature_turn_toward_target(a0, (void *)ref_L13_0040A480_00(a0), tmp, 0);
}

