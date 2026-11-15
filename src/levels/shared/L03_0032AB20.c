#include "common.h"

extern unsigned char D_L03_00189E20[];
extern int D_L03_001A8FB4 MACRO_ADDR;

/* Returns 1 when the level mode matches the given one and the hero is in a state that allows it, otherwise 0. */
int func_L03_0032AB20(int mode)
{
    unsigned char *hero;

    if (D_L03_001A8FB4 != mode)
        return 0;
    hero = D_L03_00189E20;
    if (*(unsigned char *)(hero + 0x123A) != 0)
        return 0;
    if (*(int *)(hero + 0x24CC) == 0 || *(int *)(hero + 0x229C) == 0x14)
        return 0;
    return 1;
}
