#include "common.h"

extern unsigned char g_hero_l03_state_block[];
extern int g_hero_allowed_mode MACRO_ADDR;

/* Returns 1 when the level mode matches the given one and the hero is in a state that allows it, otherwise 0. */
int hero_is_allowed_for_mode(int mode)
{
    unsigned char *hero;

    if (g_hero_allowed_mode != mode)
        return 0;
    hero = g_hero_l03_state_block;
    if (*(unsigned char *)(hero + 0x123A) != 0)
        return 0;
    if (*(int *)(hero + 0x24CC) == 0 || *(int *)(hero + 0x229C) == 0x14)
        return 0;
    return 1;
}
