#include "common.h"

extern void TriggerSubtitleInCuboid(s32, s32, s32, s32, s32);
extern s32 IsPointInCuboid(void *, s32);
extern s32 math_fast_float_d(void *);
extern s32 subtitle_request_voice_line(s32, s32);
extern u16 g_level_id_word NOT_SDA;
extern u16 g_level_flag_word NOT_SDA;
extern u16 g_arena_flag_word NOT_SDA;
extern s32 g_arena_progress_level __attribute__((sda));
extern u8 g_hero_position[];
/* g_inventoryOwned: 0x38 item ownership flags (public USA v2 symbol map). */
extern u8 g_inventory_have_flags[0x38] __attribute__((sda));
extern s32 g_arena_l11_active_flag[] __attribute__((sda));

/* Queues Joba subtitles when inventory and cuboid gates permit, with retry timers. */
void UpdateJobaSubtitleTriggers(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);

    if (*(u8 *)(object + 0x20) == 0) {
        *(u8 *)(object + 0x20) = 1;
        *(u8 *)(object + 0x30) = 0xFF;
        *(s32 *)(state + 0x8) = 0x1A4;
        *(s32 *)(state + 0x10) = 0x12C;
    }
    if (*(u8 *)(object + 0x20) != 1) {
        return;
    }
    if (g_inventory_have_flags[0]) {
        TriggerSubtitleInCuboid(0x9FF, 0x56, 3, *(s32 *)(state + 0x4), -1);
    }
    if (g_arena_l11_active_flag[0] != 0 && g_arena_progress_level >= 3) {
        g_level_id_word = 0xFFFF;
    }
    if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 0x0)) != 0) {
        if (math_fast_float_d(state + 0x8) != 0) {
            if (g_level_flag_word == 0) {
                subtitle_request_voice_line(0xA00, 0x57);
                *(s32 *)(state + 0x8) = 0x1A4;
            }
        }
    }
    if (g_inventory_have_flags[0x2E]) {
        TriggerSubtitleInCuboid(0xA03, 0x5A, 0, *(s32 *)(state + 0xC), -1);
    }
    if (g_inventory_have_flags[0xB]) {
        if (g_arena_flag_word == 0) {
            if (math_fast_float_d(state + 0x10) != 0) {
                subtitle_request_voice_line(0xA3D, 0x94);
            }
        }
    }
}
