#include "names.h"
/* func_PAL_L02_003FF718, the PAL copy of func_L02_003FB000: the same C, where the timer reload is
   scaled for 50 Hz and its source is read as a word. */
#include "common.h"

extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern int g_arena_tally_reload_time __attribute__((sda));
extern char g_hero_state[];

/* Accumulate the active group entries and reset their current report state. */
void arena_start_enemy_tally_pal(char *moby)
{
    char *state = *(char **)(moby + 0x68);
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
        if (type == 0x9CA || type == 0xB22 || type == MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER || type == MOBY_CLASS_PX6_BLADEBALL || type == MOBY_CLASS_CHAINBLADE || type == MOBY_CLASS_B2_BRAWLER_LEGS) {
            *(int *)(state + 0x60) += 1;
            *(float *)(state + 0x64) += *(float *)(*(char **)(record + 0x68) + 0x20);
        }
    } while (*cursor++ >= 0);
    hero = g_hero_state;
    *(float *)(state + 0x68) = (float)*(int *)(hero + 0x24CC);
    *(short *)(state + 0x11C) = 0;
    do {
        *(u16 *)(state + 0x11E) = ((int)g_arena_tally_reload_time * 5 + 2) / 6;
    } while (0);
}
