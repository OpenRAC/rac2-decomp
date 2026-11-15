#include "common.h"

typedef struct {
    char reserved00[0x1C];
    char *row;
} TableEntry;

extern void func_L00_002C42E0(int, int);
extern void func_L00_002D2E68(void);
extern int D_00221D94;
extern int D_001A79F0 MACRO_ADDR;
extern TableEntry *D_001B1EC4 MACRO_ADDR;
extern char D_00189E20[] MACRO_ADDR;
extern char D_0019B2E8[];

/* While the level is idle, checks the object's table bit before starting the encounter. */
/* Starts the ship fight the first time the player reaches it, unless it was already done. Returns 1 if it started. */
int func_L05_00445F90(char *object)
{
    char *row;
    char *base;

    row = D_001B1EC4[*(short *)(object + 0x84)].row;
    if (D_00221D94 != 0 ||
        (*(unsigned char *)(*(char **)(row + 0x5C) + (gCurrentMapIndex << 4) + (int)D_0019B2E8) & 0x80) != 0)
        return 0;
    SetHeroAction_L00(0x31, 1);
    base = gHeroState;
    *(int *)(*(char **)(base + 0x2290) + 0x98) = 0;
    SetHeroObjectsFlagBit();
    *(unsigned char *)(base + 0x22B5) = 1;
    return 1;
}
