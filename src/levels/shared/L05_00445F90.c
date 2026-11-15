#include "common.h"

typedef struct {
    char reserved00[0x1C];
    char *row;
} TableEntry;

extern s32 hero_l00_set_action(int, int);
extern void hero_set_objects_flag_bit(void);
extern int D_00221D94;
extern int g_current_map_index MACRO_ADDR;
extern TableEntry *D_001B1EC4 MACRO_ADDR;
extern char g_hero_state[] MACRO_ADDR;
extern char D_0019B2E8[];

/* While the level is idle, checks the object's table bit before starting the encounter. */
/* Starts the ship fight the first time the player reaches it, unless it was already done. Returns 1 if it started. */
int ship_try_start_encounter(char *object)
{
    char *row;
    char *base;

    row = D_001B1EC4[*(short *)(object + 0x84)].row;
    if (D_00221D94 != 0 ||
        (*(unsigned char *)(*(char **)(row + 0x5C) + (g_current_map_index << 4) + (int)D_0019B2E8) & 0x80) != 0)
        return 0;
    hero_l00_set_action(0x31, 1);
    base = g_hero_state;
    *(int *)(*(char **)(base + 0x2290) + 0x98) = 0;
    hero_set_objects_flag_bit();
    *(unsigned char *)(base + 0x22B5) = 1;
    return 1;
}
