#include "common.h"
extern int g_frame_l00_counter;
extern unsigned char g_screen_mode_flag NOT_SDA;
extern u32 g_hero_mode NOT_SDA;
extern int g_game_mode NOT_SDA;
extern int g_current_map_index;
extern unsigned char g_moby_group_flags[], g_moby_nibble_table[];
typedef struct { char pad[0x464]; u8 disabled[1]; } TriggerTable;
extern TriggerTable g_level_work_area, g_controller_level_state;
extern float g_hero_position[4];
extern char *g_last_checkpoint_actor __attribute__((sda));
extern void cam_reset_entry(int arg0);
extern int math_fast_float_d(int *), IsPointInCuboid(void *, int);
extern void moby_mark_table_entry_flagged(unsigned int);
extern float coll_probe_ground_height_below(void *, int, float), math_fabs(float);
extern void level_capture_checkpoint_state(void *, void *), value_set_entry_by_index(int, int);
/* Applies a regional activation trigger and records its checkpoint flags. */
void checkpoint_trigger_update_us2(char *trigger) {
    int *state = *(int **)(trigger + 0x68);
    unsigned long long flags;
    unsigned short id;
    unsigned char *packed;
    int bits;
    int active;
    float point[4];
    if (*(u8 *)(trigger + 0x30) < 0x20) *(u8 *)(trigger + 0x30) = 0x20;
    if (g_frame_l00_counter == 0 && state[5] != -1) cam_reset_entry(state[5]);
    {
        int current_flags = state[2];
        int disabled = current_flags & 8;
        flags = current_flags;
        if (disabled) return;
    }
    if (*(u8 *)(trigger + 0xBC) == 0) {
        *(u8 *)(trigger + 0xBC) = 1;
        state[7] = 0;
        state[8] = 0;
        return;
    }
    if (state[6] != -1 && !(g_moby_group_flags[state[6] + g_current_map_index * 16] & 0x80)) return;
    if ((flags & 2) && g_screen_mode_flag != 1) return;
    if ((flags & 4) && g_screen_mode_flag != 3 && g_screen_mode_flag != 0) return;
    if ((flags & 16) && g_hero_mode > 1 && g_hero_mode != 9) return;
    if ((flags & 32) && g_game_mode == 49) return;
    if (state[3] == 2 && math_fast_float_d(state + 8)) state[3] = 0;
    active = IsPointInCuboid(g_hero_position, state[0]);
    if (active) goto activate;
    {
        unsigned short trigger_id = *(u16 *)(trigger + 0xB2);
        if (g_controller_level_state.disabled[(short)trigger_id]) goto activate;
        bits = g_moby_nibble_table[((short)trigger_id >> 1) + g_current_map_index * 0x400];
        if (trigger_id & 1) {
            if ((bits >> 4) & 7) goto activate;
            goto inactive;
        }
        if (!(bits & 7)) goto inactive;
    }
activate:
    {
        if (state[3] && (state[4] == 0 || state[8] != 0)) goto finish;
        state[3] = 1;
        moby_mark_table_entry_flagged(*(u8 *)(trigger + 0xB0));
        qcopy(point, (trigger + 0x10));
        point[2] = coll_probe_ground_height_below(point, 0, 0.5f);
        if (math_fabs(*(float *)(trigger + 0x18) - point[2]) > 2.0f) point[2] = *(float *)(trigger + 0x18);
        level_capture_checkpoint_state(point, trigger + 0xF0);
        g_level_work_area.disabled[*(short *)(trigger + 0xB2)] = 0;
        g_controller_level_state.disabled[*(short *)(trigger + 0xB2)] = 0;
        id = *(u16 *)(trigger + 0xB2);
        {
            int index = (short)id >> 1;
            index += g_current_map_index * 0x400;
            packed = g_moby_nibble_table + index;
        }
        bits = *packed;
        {
            int value = bits & 0xF8;
            if (id & 1) value = bits & 0x8F;
            *packed = value;
        }
        if (state[9] && g_last_checkpoint_actor != trigger) {
            value_set_entry_by_index(0x2DCC, 90);
            g_last_checkpoint_actor = trigger;
        }
        state[8] = 900;
        goto finish;
    }
inactive:
    if (state[3]) state[3] = 2;
finish:
    if (*(u8 *)(trigger + 0x20) == 0 && (g_moby_group_flags[*(u8 *)(trigger + 0xB0) + g_current_map_index * 16] & 0x80)) *(u8 *)(trigger + 0x20) = 1;
}
