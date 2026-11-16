#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *a0, u8 a1, s32 a2);
extern int snd_play_from_global_bank(int a0, unsigned int a1, void *a2);
extern void value_set_entry_by_index_pal(int a0, int a1);
extern s32 g_arena_progress_level;
extern s32 g_enemy_spawn_enabled __attribute__((sda));
extern s32 g_active_rider_count __attribute__((sda));
extern s32 g_creature_burst_count __attribute__((sda));
extern s32 g_level_progress_flag;
extern u8 g_level_progress_flag_a NOT_SDA;
extern u8 g_level_progress_flag_b NOT_SDA;

/* Controller that watches the arena and the creature bursts. When the arena reaches level 6 with
   no riders left, and again after 12 bursts, it plays a sound and sets the level progress flag
   once each. */
void level_update_progress_flags_pal(u8 *object) {
    u8 *moby = object;
    int state = moby[0x20];
    int enabled;

    if (state != 1) {
        if (state < 2) {
            if (state == 0) {
                moby[0x30] = 0xFF;
                g_creature_burst_count = 0;
                moby_set_state(moby, 1, -1);
            }
        }
        return;
    }
    enabled = g_enemy_spawn_enabled;
    if (g_arena_progress_level >= 6 && g_active_rider_count == 0 &&
        enabled != 0 && g_level_progress_flag_a == 0) {
        g_level_progress_flag_a = 1;
        snd_play_from_global_bank(1, 0, 0);
        value_set_entry_by_index_pal(0x1233, -1);
        g_level_progress_flag = 1;
    }
    if (g_creature_burst_count < 12)
        return;
    if (g_level_progress_flag_b != 0)
        return;
    g_level_progress_flag_b = 1;
    snd_play_from_global_bank(1, 0, 0);
    value_set_entry_by_index_pal(0x1233, -1);
    g_level_progress_flag = 1;
}
