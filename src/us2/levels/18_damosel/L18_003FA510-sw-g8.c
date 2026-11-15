#include "include_asm.h"

#include "common.h"
extern u16 *D_L18_001FB320[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));
extern s32 D_L18_001B0454 __attribute__((sda));
extern s32 D_L18_001B04F0 __attribute__((sda));
extern u8 D_L18_001B0500[] SDATA(D_L18_001B0500);
extern u8 D_L18_001B0510[] SDATA(D_L18_001B0510);
extern s32 D_L18_001B2348[] __attribute__((sda));
extern s32 D_L18_001B2564[] __attribute__((sda));
extern s32 D_L18_001A8F00[] __attribute__((sda));
extern s32 D_L18_001A903C[] __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern u8 D_001395B8[];
extern u8 g_hero_position[];
extern u8 D_L18_001BF9C0[];
extern s32 D_0018C0B4[];
extern u8 D_001A7AFD[] __attribute__((sda));
extern u8 D_001A7A78[] __attribute__((sda));
extern int math_random_int_below(int);
extern void owner_set_word(void *, void *);
extern void protopet_reset_group_members(void *);
extern void state_set_flag_one(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern int IsPointInCuboid(void *, int);
extern int req_push_queue(void *, int);
extern void req_launch_queued(void *);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void snd_start_mode_sound(int);
extern void help_unlock_entry(int);
extern void moby_handle_request_slot_state(int);
extern void func_US2_002B1880(int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void MemcardSave(int, int);
extern int FastDecTimer(s16 *);
extern int SelectGroupMembersAndTarget(void *, int);
extern void protopet_wake_group_members(void *);
extern void script_queue_keyed_request(int, int);
extern void L18_DisableModeGroups(void *, int);
extern void moby_set_color_effect(void *, int);
extern void part_update_timed_sequence(void *);
extern void part_start_timed_sequence(void *);
extern void DrawSegmentedBeams(void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void protopet_clear_link_minus_one(void *);
extern void protopet_clear_link_zero(void *);
extern int flag_is_third_pending_set(void *);
extern void moby_mark_table_entry_flagged(int);
extern void func_US2_L18_002D0050(int);
extern void moby_set_flag_bit(void *, int);
extern int snd_play_from_global_bank(int, int, void *);
#define WORD(p, o) (*(s32 *)((p) + (o)))
#define HALF(p, o) (*(s16 *)((p) + (o)))
#define FLAGS(p) (*(u16 *)((p) + 0x34))
#define ENTITY(o) (D_L18_001B281C[0] + (WORD(state, (o)) << 8))
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

/* The group id and D_001A7A7B are read again where the logic needs them: GCSE
 * reduces the rereads to one load and a copy. D_L18_001B2568 and D_001A7A7B are
 * written as a base plus offset, which keeps those stores out of delay slots.
 */
void func_US2_L18_003FA510(u8 *object)
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
            for (entry = D_L18_001FB320[StreamGroup(state, i, 0)];
                 (StreamGroup(state, i, 0) & 255) != 255 &&
                 StreamGroup(state, i, 0) <= D_L18_001B2838[0] && entry &&
                 ((s16)entry[-1] >= 0 || entry == D_L18_001FB320[StreamGroup(state, i, 0)]);
                 entry++) {
                entity = g_moby_l18_table[0] + ((*entry & 0x7FFF) << 8);
                if (!entity) break;
                owner_set_word(entity, object);
            }
        }
        HALF(state, 0xA8) = 1;
        object[0x20] = 1;
        WORD(state, 0x88) = -1;
        HALF(state, 0xAA) = math_random_int_below(D_L18_001B0454);
        HALF(state, 0xAE) = -1;
        HALF(state, 0xAC) = 0;
        protopet_reset_group_members(object);
        if (WORD(state, 0xC4) != -1) {
            u8 *base = g_moby_l18_table[0];
            FLAGS(LOCAL_ENTITY(0xC4)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC4)) |= 1;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = 0;
        }
        if (WORD(state, 0xC8) != -1) {
            u8 *base = g_moby_l18_table[0];
            FLAGS(LOCAL_ENTITY(0xC8)) |= 2;
            FLAGS(LOCAL_ENTITY(0xC8)) |= 1;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = 0;
        }
        if (TRIGGER(0xB4) && !TRIGGER(0xB8)) {
            state_set_flag_one();
            hero_reset_position_and_direction(ENTITY(0xE4) + 0x10, ENTITY(0xE4) + 0xF0, 0, 1);
        }
        if (D_001395B8[0x9F]) {
            state_set_flag_one();
            hero_reset_position_and_direction(D_L18_001B0500, D_L18_001B0510, 0, 1);
            D_001395B8[0x9F] = 0;
            D_L18_001B04F0 = 1;
        }
        if (IsPointInCuboid(g_hero_position, WORD(state, 0x84)))
            WORD(state, 0x88) = 5;
    } else {
        if (D_L18_001B2348[0] < 10 && D_L18_001B04F0 == 1) {
            if (req_push_queue(D_L18_001BF9C0, 0x95)) {
                req_launch_queued(D_L18_001BF9C0);
                game_set_slowdown_factor();
                D_L18_001B04F0 = 2;
            }
        } else if (D_L18_001B04F0 == 2) {
            if (game_is_either_mode_two()) {
                D_L18_001B2564[1] = 1;
                if (D_L18_001A8F00[0] == 2) {
                    object[0x31] = 0;
                    FLAGS(object) |= 1;
                }
            } else {
                D_L18_001B2564[1] = 0;
                snd_start_mode_sound(0);
                D_L18_001B04F0 = 0;
                if (!D_001A7AFD[0] && D_001395B8[0xA1]) {
                    help_unlock_entry(5);
                    moby_handle_request_slot_state(5);
                    func_US2_002B1880(0x129F, -1);
                }
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                MemcardSave(0, -1);
            }
        }
        if (D_0018C0B4[0] != 0x6F) {
            for (i = 0; i < 4; i++) {
                if (!*StreamFlag(state, i)) {
                    if (IsPointInCuboid(g_hero_position, *StateSlot(state, i, 0x30)))
                        *StreamFlag(state, i) = 1;
                } else if (*StreamFlag(state, i) > 0) {
                    if (FastDecTimer((s16 *)(state + 0xAA)) &&
                        SelectGroupMembersAndTarget(object, i))
                        HALF(state, 0xAA) = math_random_int_below(D_L18_001B0454);
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
                    ((u32)i >= 8 || (((D_001395B8[0x94] >> i) ^ 1) & 1)) &&
                    IsPointInCuboid(g_hero_position, *StateSlot(state, i, 0x90))) {
                    *StateSlot(state, i, 0x90) = -1;
                    HALF(state, 0xAE) = i;
                    part_start_timed_sequence(object);
                    if ((u32)i < 8) D_001395B8[0x94] |= 1 << i;
                }
            }
        }
    }
    gfx_add_draw_callback_third(DrawSegmentedBeams, object);
    if (TRIGGER(0xBC) || (TRIGGER(0xB0) && !TRIGGER(0xB4))) {
        if (WORD(state, 0xC8) != -1 && WORD(state, 0xCC) != -1) {
            u8 *base = g_moby_l18_table[0];
            if ((FLAGS(LOCAL_ENTITY(0xC8)) & 1) && ((FLAGS(LOCAL_ENTITY(0xCC)) ^ 1) & 1)) {
                FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFD;
                FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFE;
                WORD(LOCAL_ENTITY(0xC8), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC8) + 0x24), 0x10);
                if (WORD(state, 0xCC) != -1) FLAGS(LOCAL_ENTITY(0xCC)) |= 2;
                {
                    u8 *nextBase = g_moby_l18_table[0];
                    FLAGS((u8 *)((WORD(state, 0xCC) << 8) + (s32)nextBase)) |= 1;
                    WORD((u8 *)((WORD(state, 0xCC) << 8) + (s32)nextBase), 0x98) = 0;
                }
            }
        }
    }
    if (TRIGGER(0xB4) && !TRIGGER(0xB8)) {
        u8 *base = g_moby_l18_table[0];
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
        func_US2_L18_002D0050(0);
        if (WORD(state, 0xC4) != -1) {
            u8 *base = g_moby_l18_table[0];
            FLAGS(LOCAL_ENTITY(0xC4)) &= 0xFFFD;
            FLAGS(LOCAL_ENTITY(0xC4)) &= 0xFFFE;
            WORD(LOCAL_ENTITY(0xC4), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC4) + 0x24), 0x10);
        }
        if (WORD(state, 0xC0) != -1) {
            if (WORD(state, 0xD0) != -1) moby_set_flag_bit(ENTITY(0xD0), 1);
            if (WORD(state, 0xD4) != -1) moby_set_flag_bit(ENTITY(0xD0), 1);
            ((u8 *)((WORD(state, 0xC0) << 8) + (s32)g_moby_l18_table[0]))[0xBC] = 1;
        }
    }
    if (object[0xBC] && TRIGGER(0xBC)) {
        object[0xBC] = 0;
        if (WORD(state, 0xC8) != -1) {
            u8 *base = g_moby_l18_table[0];
            FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFD;
            FLAGS(LOCAL_ENTITY(0xC8)) &= 0xFFFE;
            WORD(LOCAL_ENTITY(0xC8), 0x98) = WORD(*(u8 **)(LOCAL_ENTITY(0xC8) + 0x24), 0x10);
        }
        if (WORD(state, 0xC4) != -1) {
            u8 *base = g_moby_l18_table[0];
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
        if (!D_001A7A78[3]) {
            int ready;
            u16 *entry;
            u8 *entity;
            ready = 1;
            for (entry = D_L18_001FB320[WORD(state, 0xE0)];
            (WORD(state, 0xE0) & 255) != 255 && WORD(state, 0xE0) <= D_L18_001B2838[0] && entry &&
            ((entry && (s16)entry[-1] >= 0) || entry == D_L18_001FB320[WORD(state, 0xE0)]); entry++) {
                entity = g_moby_l18_table[0] + ((*entry & 0x7FFF) << 8);
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
                int allReady = 1;
                u16 *entry;
                u8 *entity;
                for (i = 0; i < 4 && allReady; i++) {
                    for (entry = D_L18_001FB320[StreamGroup(state, i, 0xF0)];
                    (StreamGroup(state, i, 0xF0) & 255) != 255 &&
                    StreamGroup(state, i, 0xF0) <= D_L18_001B2838[0] && entry &&
                    ((s16)entry[-1] >= 0 || entry == D_L18_001FB320[StreamGroup(state, i, 0xF0)]);
                    entry++) {
                        entity = g_moby_l18_table[0] + ((*entry & 0x7FFF) << 8);
                        if (!entity) break;
                        if (entity[0x20] != 0xFE) {
                            if (entity[0x20] != 0xFD) {
                                if ((FLAGS(entity) ^ 1) & 1) {
                                    allReady = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (allReady) {
                    if (!D_001A7A78[3]) {
                        D_001A7A78[3] = 1;
                        snd_play_from_global_bank(1, 0, 0);
                        func_US2_002B1880(0x1233, -1);
                        D_L18_001A903C[0] = 1;
                    }
                    moby_mark_table_entry_flagged(WORD(state, 0xE8));
                }
            }
        }
    }
}
