#include "include_asm.h"

#include "common.h"
extern s32 FastDecTimer(s16 *timer);
extern s32 subtitle_request_voice_line_us2(s32 key, s32 selection);
extern s32 IsPointInCuboid(void *point, s32 index);
extern s32 snd_play_from_global_bank(s32 index, s32 value, void *object);
extern void value_set_entry_by_index_us2(s32 first, s32 second);
extern u16 g_two_step_trigger_flag;
extern u8 g_map_overlay_flag[] __attribute__((sda));
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern u8 g_hero_position[];
extern u8 g_hero_state[];
extern u32 g_two_step_trigger_step[] __attribute__((sda));
extern s32 func_001163B0(void);
extern s32 FloatToInt(float);
extern u8 *g_orbiting_effect_type_table;

/* Watches the hero in two steps, first for one action and then for another, and then triggers an event with a sound (USA v2.00 copy). */
void two_step_hero_trigger_update_us2(u8 *entity) {
    u8 *state;
    u32 substate;
    u8 mode;

    state = *(u8 **)(entity + 0x68);
    if (entity[0x20] == 0) {
        entity[0x30] = 0xFF;
        *(u16 *)(state + 0xE) = 0x28;
        *(u16 *)(state + 0xC) = 0;
        entity[0x20] = 1;
    }
    if (g_two_step_trigger_flag != 0)
        goto after;
    if (g_map_overlay_flag[0] != 0) {
        if (FastDecTimer((s16 *)(state + 0xE)) != 0)
            subtitle_request_voice_line_us2(0xA27, 0x7E);
    }
after:
    mode = entity[0x20];
    if (mode != 1)
        goto end;
    substate = *(u32 *)(state + 0x8);
    switch (substate) {
    case 0: {
        u8 *block = g_hero_position;
        if (IsPointInCuboid(block, *(u32 *)(state + 0)) != 0) {
            if (*(u32 *)(block + 0x221C) == 15)
                *(u32 *)(state + 8) = mode;
        }
        break;
    }
    case 1: {
        u8 *block = g_hero_state;
        if (*(u32 *)(block + 0x2294) == 0x3E) {
            *(u32 *)(state + 8) = 0;
        } else if (IsPointInCuboid(block + 0x80, *(u32 *)(state + 4)) != 0) {
            if (g_item_enabled_flags[7] == 0) {
                g_item_enabled_flags[7] = substate;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index_us2(0x1233, -1);
                g_two_step_trigger_step[0] = substate;
            }
        }
        break;
    }
    }
end:
    return;
}

