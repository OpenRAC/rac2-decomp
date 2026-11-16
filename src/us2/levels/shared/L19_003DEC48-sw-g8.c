#include "include_asm.h"

#include "common.h"
extern u16 *g_group_ptr_table[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern s32 g_max_l19_group_index[] __attribute__((sda));
extern s32 g_random_range_limit __attribute__((sda));
extern s32 g_warp_sequence_state __attribute__((sda));
extern u8 g_hero_l19_reset_position[] SDATA(D_L19_001B0A70);
extern u8 g_hero_l19_reset_direction[] SDATA(D_L19_001B0A80);
extern s32 g_frame_l19_counter[] __attribute__((sda));
extern s32 g_glow_state_flags[] __attribute__((sda));
extern s32 g_hero_l19_mode[] __attribute__((sda));
extern s32 g_warp_triggered_flags[] __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 g_moby_group_flags[];
extern u8 g_game_flag_table[];
extern u8 g_hero_position[];
extern u8 g_request_l19_queue[];
extern s32 g_game_mode[];
extern u8 g_map_overlay_flag[] __attribute__((sda));
extern u8 g_trigger_event_flags[] __attribute__((sda));
extern int math_random_int_below(int);
extern void owner_set_word(void *, void *);
extern void protopet_reset_group_members(void *);
extern void state_set_flag_one(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern int IsPointInCuboid(void *, int);
extern int req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void ref_L19_003DD9D8_01(int);
extern void help_unlock_entry(int);
extern int moby_handle_request_slot_state(int);
extern void value_set_entry_by_index_us2(int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern int MemcardSave(int, int);
extern int FastDecTimer(s16 *);
extern int SelectGroupMembersAndTarget(void *, int);
extern void protopet_wake_group_members(void *);
extern void script_queue_keyed_request(int, int);
extern void L18_DisableModeGroups(void *, int);
extern void moby_set_color_effect(void *, int);
extern void part_update_timed_sequence(void *);
extern void part_start_timed_sequence(void *);
extern void DrawSegmentedBeams(void *);
extern void ref_L19_003DD9D8_00(void *, void *);
extern void protopet_clear_link_minus_one(void *);
extern void protopet_clear_link_zero(void *);
extern int flag_is_third_pending_set(void *);
extern void moby_mark_table_entry_flagged(int);
extern void ref_L19_003DD9D8_02(int);
extern void moby_set_flag_bit(void *, int);
extern int snd_play_from_global_bank(int, int, void *);
#define WORD(p, o) (*(s32 *)((p) + (o)))
#define HALF(p, o) (*(s16 *)((p) + (o)))
#define FLAGS(p) (*(u16 *)((p) + 0x34))
#define ENTITY(o) (D_L19_001B2A1C[0] + (WORD(state, (o)) << 8))
#define LOCAL_ENTITY(o) ((u8 *)((WORD(state, (o)) << 8) + (s32)base))
#define TRIGGER(o) (D_0019B2E8[WORD(state, (o)) + D_001A79F0[0] * 16] & 0x80)
static __inline__ s16 *StreamFlag(u8 *state, int i)
{
    int off = i << 1;
    s16 *flags = (s16 *)(state + 0xA0);
    return (s16 *)((u8 *)flags + off);
}
static __inline__ s32 *StateSlot(u8 *state, int i, int base)
{
    int off = i << 2;
    s32 *slots = (s32 *)(state + base);
    return (s32 *)((u8 *)slots + off);
}
static __inline__ int StreamGroup(u8 *state, int i, int base)
{
    int off = i << 2;
    int *ids = (int *)(state + base);
    return *(int *)((u8 *)ids + off);
}

/* The same instructions as func_L18_003F90A0. The group id and D_001A7A7B are read
 * again where the logic needs them: GCSE reduces the rereads to one load and a copy.
 * D_L19_001B2728 and D_001A7A7B are written as a base plus offset, which keeps those
 * stores out of delay slots.
 */
void group_trigger_controller_update_us2(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int mode;
    int i;

    if (!object[0x20]) {
        int i;
        u16 *entry;
        u8 *entity;
        HALF(object, 0x32) = 0;
        object[0x30] = 255;
        for (i = 0; i < 4; i++) {
            *StreamFlag(state, i) = 0;
            for (entry = g_group_ptr_table[StreamGroup(state, i, 0)];
                 (StreamGroup(state, i, 0) & 255) != 255 &&
                 StreamGroup(state, i, 0) <= g_max_l19_group_index[0] && entry &&
                 ((s16)entry[-1] >= 0 || entry == g_group_ptr_table[StreamGroup(state, i, 0)]);
                 entry++) {
                entity = g_moby_l19_array[0] + ((*entry & 0x7FFF) << 8);
                if (!entity) break;
                owner_set_word(entity, object);
            }
        }
        HALF(state, 0xA8) = 1;
        object[0x20] = 1;
        WORD(state, 0x88) = -1;
        HALF(state, 0xAA) = math_random_int_below(g_random_range_limit);
        HALF(state, 0xAE) = -1;
        HALF(state, 0xAC) = 0;
        protopet_reset_group_members(object);
        if (WORD(state, 0xC4) != -1) {
            u8 *base = g_moby_l19_array[0];
            FLAGS(LOCAL_ENTITY(0xC4)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC4)) |= 1;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = 0;
        }
        if (WORD(state, 0xC8) != -1) {
            u8 *base = g_moby_l19_array[0];
            FLAGS(LOCAL_ENTITY(0xC8)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC8)) |= 1;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = 0;
        }
        if (TRIGGER(0xB4) && !TRIGGER(0xB8)) {
            state_set_flag_one();
            hero_reset_position_and_direction(ENTITY(0xE4) + 0x10, ENTITY(0xE4) + 0xF0, 0, 1);
        }
        if (g_game_flag_table[0x9F]) {
            state_set_flag_one();
            hero_reset_position_and_direction(g_hero_l19_reset_position, g_hero_l19_reset_direction, 0, 1);
            g_game_flag_table[0x9F] = 0;
            g_warp_sequence_state = 1;
        }
        if (IsPointInCuboid(g_hero_position, WORD(state, 0x84)))
            WORD(state, 0x88) = 5;
    } else {
        if (g_frame_l19_counter[0] < 10 && g_warp_sequence_state == 1) {
            if (req_push_queue(g_request_l19_queue, 0x95)) {
                req_launch_queued(g_request_l19_queue);
                game_set_slowdown_factor();
                g_warp_sequence_state = 2;
            }
        } else if (g_warp_sequence_state == 2) {
            if (game_is_either_mode_two()) {
                g_glow_state_flags[1] = 1;
                if (g_hero_l19_mode[0] == 2) {
                    object[0x31] = 0;
                    FLAGS(object) |= 1;
                }
            } else {
                g_glow_state_flags[1] = 0;
                ref_L19_003DD9D8_01(0);
                g_warp_sequence_state = 0;
                if (!g_map_overlay_flag[0] && g_game_flag_table[0xA1]) {
                    help_unlock_entry(5);
                    moby_handle_request_slot_state(5);
                    value_set_entry_by_index_us2(0x129F, -1);
                }
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                MemcardSave(0, -1);
            }
        }
        if (g_game_mode[0] != 0x6F) {
            for (i = 0; i < 4; i++) {
                if (!*StreamFlag(state, i)) {
                    if (IsPointInCuboid(g_hero_position, *StateSlot(state, i, 0x30)))
                        *StreamFlag(state, i) = 1;
                } else if (*StreamFlag(state, i) > 0) {
                    if (FastDecTimer((s16 *)(state + 0xAA)) &&
                        SelectGroupMembersAndTarget(object, i))
                        HALF(state, 0xAA) = math_random_int_below(g_random_range_limit);
                }
            }
        }
        if (IsPointInCuboid(g_hero_position, *StateSlot(state, WORD(state, 0x88) + 1, 0x40))) {
            WORD(state, 0x88)++;
            if (WORD(state, 0x88) == 6) {
                protopet_wake_group_members(object);
                script_queue_keyed_request(WORD(state, 0x104), -1);
            } else {
                if (!WORD(state, 0x88))
                    script_queue_keyed_request(WORD(state, 0x100), -1);
                L18_DisableModeGroups(object, WORD(state, 0x88));
            }
        }
        if (WORD(state, 0x88) == 5 && IsPointInCuboid(g_hero_position, WORD(state, 0x44))) {
            protopet_wake_group_members(object);
            WORD(state, 0x88) = 1;
            L18_DisableModeGroups(object, 1);
        }
        mode = 0;
        switch (WORD(state, 0x88)) {
        case 2:
            mode = 2;
            break;
        case 0: case 1: case 3: case 4:
            mode = 1;
            break;
        }
        moby_set_color_effect(object, mode);
        if (HALF(state, 0xAC)) {
            part_update_timed_sequence(object);
        } else {
            int i;
            for (i = 0; i < 4; i++) {
                if (*StateSlot(state, i, 0x90) != -1 &&
                    ((u32)i >= 8 || (((g_game_flag_table[0x94] >> i) ^ 1) & 1)) &&
                    IsPointInCuboid(g_hero_position, *StateSlot(state, i, 0x90))) {
                    *StateSlot(state, i, 0x90) = -1;
                    HALF(state, 0xAE) = i;
                    part_start_timed_sequence(object);
                    if ((u32)i < 8) g_game_flag_table[0x94] |= 1 << i;
                }
            }
        }
    }
    ref_L19_003DD9D8_00(DrawSegmentedBeams, object);
    if (TRIGGER(0xBC) || (TRIGGER(0xB0) && !TRIGGER(0xB4))) {
        if (WORD(state, 0xC8) != -1 && WORD(state, 0xCC) != -1) {
            u8 *base = g_moby_l19_array[0];
            if ((FLAGS(LOCAL_ENTITY(0xC8)) & 1) && ((FLAGS(LOCAL_ENTITY(0xCC)) ^ 1) & 1)) {
                FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFD;
                FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFE;
                WORD(LOCAL_ENTITY(0xC8), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC8) + 0x24), 0x10);
                if (WORD(state, 0xCC) != -1) FLAGS(LOCAL_ENTITY(0xCC)) |= 2;
                {
                    u8 *next_base = g_moby_l19_array[0];
                    FLAGS((u8 *)((WORD(state, 0xCC) << 8) + (s32)next_base)) |= 1;
                    WORD((u8 *)((WORD(state, 0xCC) << 8) + (s32)next_base), 0x98) = 0;
                }
            }
        }
    }
    if (TRIGGER(0xB4) && !TRIGGER(0xB8)) {
        u8 *base = g_moby_l19_array[0];
        if (WORD(state, 0xC8) != -1) {
            FLAGS(LOCAL_ENTITY(0xC8)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC8)) |= 1;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = 0;
            protopet_clear_link_minus_one(base + (WORD(state, 0xD8) << 8));
            protopet_clear_link_minus_one(ENTITY(0xDC));
        }
    }
    if (!TRIGGER(0xB8) && flag_is_third_pending_set(object)) {
        object[0xBC] = 1;
        object[0xBE] &= 0xFB;
        moby_mark_table_entry_flagged(WORD(state, 0xB8));
        ref_L19_003DD9D8_02(0);
        if (WORD(state, 0xC4) != -1) {
            u8 *base = g_moby_l19_array[0];
            FLAGS(LOCAL_ENTITY(0xC4)) &= 0xFFFD;
            FLAGS(LOCAL_ENTITY(0xC4)) &= 0xFFFE;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC4) + 0x24), 0x10);
        }
        if (WORD(state, 0xC0) != -1) {
            if (WORD(state, 0xD0) != -1) moby_set_flag_bit(ENTITY(0xD0), 1);
            if (WORD(state, 0xD4) != -1) moby_set_flag_bit(ENTITY(0xD0), 1);
            ((u8 *)((WORD(state, 0xC0) << 8) + (s32)g_moby_l19_array[0]))[0xBC] = 1;
        }
    }
    if (object[0xBC] && TRIGGER(0xBC)) {
        object[0xBC] = 0;
        if (WORD(state, 0xC8) != -1) {
            u8 *base = g_moby_l19_array[0];
            FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFD;
            FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFE;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC8) + 0x24), 0x10);
        }
        if (WORD(state, 0xC4) != -1) {
            u8 *base = g_moby_l19_array[0];
            FLAGS(LOCAL_ENTITY(0xC4)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC4)) |= 1;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = 0;
        }
        if (WORD(state, 0xD0) != -1) moby_set_flag_bit(ENTITY(0xD0), 1);
        if (WORD(state, 0xD4) != -1) moby_set_flag_bit(ENTITY(0xD0), 1);
        protopet_clear_link_zero(ENTITY(0xD8));
        protopet_clear_link_zero(ENTITY(0xDC));
    }
    {
        if (!g_trigger_event_flags[3]) {
            int ready;
            u16 *entry;
            u8 *entity;
            ready = 1;
            for (entry = g_group_ptr_table[WORD(state, 0xE0)];
            (WORD(state, 0xE0) & 255) != 255 && WORD(state, 0xE0) <= g_max_l19_group_index[0] && entry &&
            ((entry && (s16)entry[-1] >= 0) || entry == g_group_ptr_table[WORD(state, 0xE0)]); entry++) {
                entity = g_moby_l19_array[0] + ((*entry & 0x7FFF) << 8);
                if (!entity) break;
                if (entity[0x20] != 0xFE) {
                    if (entity[0x20] != 0xFD) {
                        if (!(FLAGS(entity) & 1)) continue;
                    }
                }
                ready = 0;
                break;
            }
            if (ready) {
                int all_ready = 1;
                u16 *entry;
                u8 *entity;
                for (i = 0; i < 4 && all_ready; i++) {
                    for (entry = g_group_ptr_table[StreamGroup(state, i, 0xF0)];
                    (StreamGroup(state, i, 0xF0) & 255) != 255 &&
                    StreamGroup(state, i, 0xF0) <= g_max_l19_group_index[0] && entry &&
                    ((s16)entry[-1] >= 0 || entry == g_group_ptr_table[StreamGroup(state, i, 0xF0)]);
                    entry++) {
                        entity = g_moby_l19_array[0] + ((*entry & 0x7FFF) << 8);
                        if (!entity) break;
                        if (entity[0x20] != 0xFE) {
                            if (entity[0x20] != 0xFD) {
                                if ((FLAGS(entity) ^ 1) & 1) {
                                    all_ready = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (all_ready) {
                    if (!g_trigger_event_flags[3]) {
                        g_trigger_event_flags[3] = 1;
                        snd_play_from_global_bank(1, 0, 0);
                        value_set_entry_by_index_us2(0x1233, -1);
                        g_warp_triggered_flags[0] = 1;
                    }
                    moby_mark_table_entry_flagged(WORD(state, 0xE8));
                }
            }
        }
    }
}
