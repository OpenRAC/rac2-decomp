#include "include_asm.h"

#include "common.h"
extern char *g_group_l20_member_table;
extern char *g_linked_moby_table;
extern float g_hero_timer_trigger_a MACRO_ADDR;
extern void moby_set_scaled_speed_capped(char *);
extern u32 g_level_mode __attribute__((nosda));
extern float g_level_shared_float;
extern int g_current_map_index MACRO_ADDR;
extern u8 g_moby_group_flags[];
extern float g_hero_position[];
extern int g_boss_timer;
extern int g_hero_vehicle_mode;
extern int MemcardSave(int, int);
extern void script_queue_keyed_request(int, int);
extern void load_scene_chunk_pal(int, int);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_mark_table_entry_flagged(unsigned int);
extern void moby_set_flag_bit(unsigned char *, int);
extern void trooper_legs_destroy_group(s32);
extern void moby_set_state(u8 *, s32, s32);
extern s32 flag_set_first_pending(u8 *);
extern int math_fast_float_d(int *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void hero_load_state_by_game_mode(int);

/* The platform controller records switch edges and raises its linked platform. */
void UpdateLinkedPlatformController_pal(u8 *object) {
    s32 *state = *(s32 **)(object + 0x68);
    int frame_offset;

    if (g_level_mode < 2) g_level_shared_float = 85.0f;
    switch (object[0x20]) {
    case 0: {
        char *record;
        frame_offset = g_current_map_index * 16;
        state[8] = g_level_mode;
        state[5] = 0;
        state[4] = 0;
        state[0x23] = g_moby_group_flags[state[2] + frame_offset] >> 7;
        if ((g_moby_group_flags[state[1] + frame_offset] & 0x80) == 0) {
            state[0x1F] = 0;
            record = (char *)((state[0x1C] << 8) + (u32)g_group_l20_member_table);
            *(float *)(state + 0x1D) = *(float *)(record + 0x18);
            *(float *)(record + 0x18) += 20.0f;
        } else state[0x1F] = 1;
        moby_set_state(object, 1, -1);
        break;
    }
    case 1: {
        char *record;
        if (state[0x23] == 0 &&
            (g_moby_group_flags[state[2] + g_current_map_index * 16] & 0x80) != 0 &&
            IsPointInCuboid(g_hero_position, state[10]) != 0) {
            state[0x23] = 1;
            MemcardSave(0, -1);
        }
        if (g_level_mode == 2) {
            if (state[4] == 0) {
                if (IsPointInCuboid(g_hero_position, state[0x18])) {
                    state[4] = 1;
                    script_queue_keyed_request(state[0x20], -1);
                }
            }
        }
        if (IsPointInCuboid(g_hero_position, state[11]) != 0) {
            if (g_moby_group_flags[state[1] + g_current_map_index * 16] & 0x80) return;
            moby_mark_table_entry_flagged(state[1]);
            if (state[0x13] >= 0)
                moby_set_flag_bit((u8 *)g_group_l20_member_table + state[0x13] * 0x100, 1);
            trooper_legs_destroy_group(state[0x14]);
            trooper_legs_destroy_group(state[0x15]);
            state[8] = 2;
            state[15] = 3;
            moby_set_state(object, 5, -1);
        }
        if (g_moby_group_flags[state[1] + g_current_map_index * 16] & 0x80) return;
        if (*(u8 *)(g_group_l20_member_table + state[0x1B] * 0x100 + 0xBC) == 1) return;
        if (state[0x1F] != 0) return;
        record = g_group_l20_member_table + state[0x19] * 0x100;
        if (record != 0 && *(s16 *)(record + 0xAA) == 0xCBC &&
            *(u8 *)(record + 0x20) != 0xFE && *(u8 *)(record + 0x20) != 0xFD) return;
        record = g_group_l20_member_table + state[0x1A] * 0x100;
        if (record != 0 && *(s16 *)(record + 0xAA) == 0xCBC) {
            int status = *(u8 *)(record + 0x20);
            if (status != 0xFE && *(u8 *)(record + 0x20) != 0xFD) return;
        }
        moby_set_state(object, 7, -1);
        break;
    }
    case 2:
    case 3:
        if (flag_set_first_pending(object)) state[5] = 104;
        if (math_fast_float_d(state + 5)) goto movement_done;
        if (object[0x20] == 2) *(float *)(state + 3) = 1.0f - (float)state[5] * 0.008f;
        else *(float *)(state + 3) = (float)state[5] * 0.008f;
        goto movement_callback;
movement_done:
        moby_set_state(object, state[7], -1);
movement_callback:
        gfx_add_draw_callback_third((void (*)(void *))moby_set_scaled_speed_capped, object);
        break;
    case 4: {
        char *record;
        s32 *entry = (s32 *)((u32)state + (state[15] * 4));
        record = g_linked_moby_table + entry[9] * 0x80;
        load_scene_chunk_pal(state[8], state[0x21]);
        moby_mark_table_entry_flagged(state[0]);
        hero_reset_position_and_direction_pal(record + 0x30, record + 0x70, 0x6F, 1);
        hero_load_state_by_game_mode(0);
        state[7] = 1;
        g_hero_timer_trigger_a = 1.0f;
        *(float *)(state + 3) = 1.0f;
        gfx_add_draw_callback_third((void (*)(void *))moby_set_scaled_speed_capped, object);
        moby_set_state(object, 6, -1);
        break;
    }
    case 5:
        if (g_boss_timer == -2 && g_hero_vehicle_mode != 2) {
            *(float *)(state + 3) = 1.0f;
            gfx_add_draw_callback_third((void (*)(void *))moby_set_scaled_speed_capped, object);
            if (*(u8 *)(g_group_l20_member_table + state[0x13] * 0x100 + 0x20) > 0x80)
                moby_set_state(object, 4, -1);
        }
        state[6]++;
        break;
    case 6: {
        if (g_hero_vehicle_mode != 2) {
            g_hero_timer_trigger_a = 1.0f;
            *(float *)(state + 3) = 1.0f;
            gfx_add_draw_callback_third((void (*)(void *))moby_set_scaled_speed_capped, object);
        } else g_hero_timer_trigger_a = 0.0f;
        if (g_hero_vehicle_mode != 2) {
            char *mobys = g_group_l20_member_table;
            if (*(u8 *)(mobys + state[0x12] * 0x100 + 0x20) > 0x80) {
                *(u16 *)(mobys + state[0x17] * 0x100 + 0x34) &= 0xFFFD;
                *(u16 *)(mobys + state[0x16] * 0x100 + 0x34) &= 0xFFFD;
                *(u16 *)(mobys + state[0x17] * 0x100 + 0x34) &= 0xFFBE;
                *(u16 *)(mobys + state[0x17] * 0x100 + 0x34) |= 0x1000;
                {
                    char *first = (char *)((state[0x17] << 8) + (u32)mobys);
                    *(int *)(first + 0x98) = *(int *)(*(char **)(first + 0x24) + 0x10);
                }
                *(u16 *)(mobys + state[0x16] * 0x100 + 0x34) &= 0xFFBE;
                *(u16 *)(mobys + state[0x16] * 0x100 + 0x34) |= 0x1000;
                {
                    char *second = (char *)((state[0x16] << 8) + (u32)mobys);
                    *(int *)(second + 0x98) = *(int *)(*(char **)(second + 0x24) + 0x10);
                }
                g_hero_timer_trigger_a = 0.0f;
                moby_set_state(object, 3, -1);
            }
        }
        state[6]++;
        break;
    }
    case 7: {
        char *record;
        if (flag_set_first_pending(object)) {
            record = g_group_l20_member_table + state[0x1B] * 0x100;
            record[0xBC] = 1;
            {
                int duration = *(int *)(*(char **)(record + 0x68) + 0x2C);
                state[0x1F] = 1;
                state[6] = duration;
                state[0x1E] = duration;
            }
        }
        *(float *)(g_group_l20_member_table + state[0x1C] * 0x100 + 0x18) =
            *(float *)(state + 0x1D) + ((float)state[6] * 20.0f) / (float)state[0x1E];
        if (math_fast_float_d(state + 6)) moby_set_state(object, 1, -1);
        break;
    }
    }
}
