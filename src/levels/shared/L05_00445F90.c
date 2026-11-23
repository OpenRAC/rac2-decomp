#include "common.h"

typedef struct {
    char reserved00[0x1C];
    char *row;
} TableEntry;

extern s32 hero_l00_set_move_state(int, int);
extern void hero_set_objects_flag_bit(void);
extern int g_ship_encounter_flag;
extern int g_current_map_index MACRO_ADDR;
extern TableEntry *g_ship_encounter_table MACRO_ADDR;
extern char g_hero_state[] MACRO_ADDR;
extern char g_moby_group_flags[];

/* While the level is idle, checks the object's table bit before starting the encounter. */
/* Starts the ship fight the first time the player reaches it, unless it was already done. Returns 1 if it started. */
int ship_try_start_encounter(char *object)
{
    char *row;
    char *base;

    row = g_ship_encounter_table[*(short *)(object + 0x84)].row;
    if (g_ship_encounter_flag != 0 ||
        (*(unsigned char *)(*(char **)(row + 0x5C) + (g_current_map_index << 4) + (int)g_moby_group_flags) & 0x80) != 0)
        return 0;
    hero_l00_set_move_state(0x31, 1);
    base = g_hero_state;
    *(int *)(*(char **)(base + 0x2290) + 0x98) = 0;
    hero_set_objects_flag_bit();
    *(unsigned char *)(base + 0x22B5) = 1;
    return 1;
}
