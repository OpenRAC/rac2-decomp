#include "include_asm.h"


#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern int ref_L13_0040A480_00(void *);
extern char g_hero_position[];

/* func_L13_0040A3B0 is matched in L13_0040A3B0.c (built with -frac2-zero-ti-barrier). */


/* Turns a moby toward the hero (PAL). */
void moby_turn_toward_hero_pal(char *moby)
{
    char to_hero[16];
    FastVecSub(to_hero, g_hero_position, moby + 0x10);
    creature_turn_toward_target(moby, (void *)ref_L13_0040A480_00(moby), to_hero, 0);
}

