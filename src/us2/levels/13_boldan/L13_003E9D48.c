#include "include_asm.h"

#include "common.h"
extern u8 g_hero_state[];
extern u8 g_hero_position[];
extern u8 g_progress_statistics[];
extern u8 g_game_flag_table[];
extern u32 g_frame_counter[] __attribute__((sda));
extern u8 g_item_enabled_flags[] __attribute__((sda));
extern s32 g_scene_trigger_flag[] __attribute__((sda));
extern s32 g_hint_index;
extern s32 IsPointInCuboid(void *a0, s32 a1);
extern int snd_play_from_global_bank(s32 a0, s32 a1, s32 a2);
extern void value_set_entry_by_index_us2(s32 a0, s32 a1);
extern int subtitle_request_voice_line_us2(s32 a0, s32 a1);

/* Watches the player entering two trigger boxes and, on the second, unlocks a story event with a sound. Also plays a one-time hint when the player enters the main box. (USA v2.00) */
void trigger_hint_update_us2(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    s16 phase;
    u8 *hero;
    u8 *timers;
    u8 *counters;

    if (self[0x20] == 0) {
        self[0x30] = 0xFF;
        *(s16 *)(state + 0xC) = 0;
        self[0x20] = 1;
    }
    if (self[0x20] != 1)
        return;
    phase = *(s16 *)(state + 0xE);
    switch (phase) {
    case 0:
        if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 4)) != 0 && *(s32 *)(g_hero_position + 0x221C) == 0xF)
            *(s16 *)(state + 0xE) = 1;
        break;
    case 1:
        hero = g_hero_state;
        if (*(s32 *)(hero + 0x2294) == 0x3E) {
            *(s16 *)(state + 0xE) = 0;
        } else if (IsPointInCuboid(hero + 0x80, *(s32 *)(state + 8)) != 0 && g_item_enabled_flags[4] == 0) {
            g_item_enabled_flags[4] = 1;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index_us2(0x1233, -1);
            g_scene_trigger_flag[0] = 1;
        }
        break;
    }
    if (IsPointInCuboid(g_hero_position, *(s32 *)state) == 0)
        return;
    timers = g_progress_statistics;
    if (*(u16 *)(timers + 0x1BC) != 0 && !(g_frame_counter[0] - *(u32 *)(timers + 0x1C0) > 0x69780))
        return;
    counters = g_game_flag_table;
    if (counters[0x7E] < 2 && *(s16 *)(state + 0xC) == 0) {
        if (g_hint_index >= 0)
            subtitle_request_voice_line_us2(0x9E3, 0x3A);
        counters[0x7E] = counters[0x7E] + 1;
        *(s16 *)(state + 0xC) = 1;
    }
}

