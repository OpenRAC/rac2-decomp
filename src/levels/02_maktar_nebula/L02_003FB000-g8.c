#include "common.h"

extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern u16 g_arena_tally_reload_time __attribute__((sda));
extern char g_hero_state[];

/* Accumulate the active group entries and reset their current report state. */
/* Starts a fresh enemy tally for the arena: counts the enemies in the group and remembers their health total. */
void arena_start_enemy_tally(char *object)
{
    char *state = *(char **)(object + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 entry;
    short *cursor;
    char *table;
    char *record;
    char *hero;

    *(int *)(state + 0x60) = 0;
    *(float *)(state + 0x64) = 0;
    if (index == 0xFF)
        return;
    entry = g_entity_group_lists[index];
    if (entry == 0)
        return;
    cursor = (short *)entry;
    table = g_moby_l02_pool;
    do {
        short type;
        record = table + ((*(u16 *)cursor & 0x7FFF) << 8);
        if (record == 0)
            continue;
        if ((u8)record[0x20] == 0xFE)
            continue;
        if ((u8)record[0x20] == 0xFD)
            continue;
        if ((u8)record[0x20] == 1)
            continue;
        type = *(short *)(record + 0xAA);
        if (type == 0x9CA /* moby class 2506 */ || type == 0xB22 /* moby class 2850 */ || type == MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER || type == MOBY_CLASS_PX6_BLADEBALL || type == MOBY_CLASS_CHAINBLADE || type == MOBY_CLASS_B2_BRAWLER_LEGS) {
            *(int *)(state + 0x60) += 1;
            *(float *)(state + 0x64) += *(float *)(*(char **)(record + 0x68) + 0x20);
        }
    } while (*cursor++ >= 0);
    hero = g_hero_state;
    *(float *)(state + 0x68) = (float)*(int *)(hero + 0x24CC);
    *(short *)(state + 0x11C) = 0;
    do {
        *(u16 *)(state + 0x11E) = g_arena_tally_reload_time;
    } while (0);
}
