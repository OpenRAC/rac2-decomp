#include "include_asm.h"

#include "common.h"
extern u8 *g_moby_l01_table;
extern u32 g_group_list_table[];
extern u8 *func_00305EE8(int);
extern int g_current_map_index;
extern u8 g_moby_nibble_table[];
extern u8 g_moby_group_flags[];
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState g_level_l01_save_state;
extern LevelSaveState g_level_save_state_backup;
extern u8 g_sound_state[], g_hero_position[];
extern u8 g_water_l01_height[] MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern float g_pod_scale_factor_a __attribute__((sda));
extern float g_pod_scale_factor_b __attribute__((sda));
extern float g_pod_scale_factor_c __attribute__((sda));
extern float g_pod_scale_factor_d __attribute__((sda));
extern void moby_mark_spawned(void *);
extern void anim_start_immediate(void *, int, int);
extern int moby_count_group_not_in_state(int, int);
extern void update_moby_animation_state(void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int PlayMobySound(int, int, void *);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float level_get_water_height_pal(void);
extern void *part_spawn_drifting(void *position, float size, void *owner, float spin, int color);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void part_spawn_water_splash_pal(void *, int, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void part_l01_spawn_burst_pal(void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int IsPointInCuboid(void *, int);
typedef struct {
    u8 pad[0x50];
    int mode;
    int parent_index;
    int hit_index;
    int child_index;
    int persistent;
    int link_index;
    int link_count;
    u8 unknown_6c[4];
    int sound_index;
} HandlerState;

/* Per-state update: state 0 initialises by mode, 1 runs the mode's behaviour, 2 finishes.
   A persistent moby (save id at +0xB2) counts itself in the level's 3-bit collection
   counters before it is deleted; any other one is recorded by func_L01_003D8AD0. */
void bursting_pod_update_pal(u8 *moby)
{
    HandlerState *state = *(HandlerState **)(moby + 0x68);
    u8 *parent;
    u8 *entry;
    int flag, hit, i, color, persist_id;
    float size;
    float pos[4] __attribute__((aligned(16)));

    switch (moby[0x20]) {
    case 0:
        if (state->persistent && moby[0xB0] != 255) {
            u16 id = *(u16 *)(moby + 0xB2);
            int bits;
            if (g_level_save_state_backup.collected[(short)id] ||
                (bits = g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)],
                 (id & 1) ? ((bits >> 4) & 7) : (bits & 7))) {
                if (state->child_index != -1)
                    moby_mark_spawned(g_moby_l01_table + (state->child_index << 8));
                moby_mark_spawned(moby);
                return;
            }
        }
        moby[0x95] = 0;
        state->sound_index = -1;
        switch (state->mode) {
        case 0:
            *(u16 *)(moby + 0x32) = 0x3FF;
            moby[0x30] = 255;
            if (state->parent_index != -1) {
                u8 *parent = g_moby_l01_table + (state->parent_index << 8);
                if (parent) {
                    if (*(u8 **)(parent + 0x68) && *(int *)(*(u8 **)(parent + 0x68) + 0xC8))
                        anim_start_immediate(moby, 6, 0);
                    else
                        anim_start_immediate(moby, 9, 0);
                }
            }
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * g_pod_scale_factor_a;
            break;
        case 1:
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * g_pod_scale_factor_b;
            anim_start_immediate(moby, 2, 0);
            break;
        case 2:
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * g_pod_scale_factor_c;
            anim_start_immediate(moby, 4, 0);
            if (state->link_index != -1)
                state->link_count = moby_count_group_not_in_state(state->link_index, -1);
            break;
        case 3:
            *(int *)(moby + 0x98) = 0;
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * g_pod_scale_factor_d;
            anim_start_immediate(moby, 10, 0);
            break;
        }
        if (state->parent_index != -1) {
            parent = g_moby_l01_table + (state->parent_index << 8);
            if (parent) {
                moby[0x40] = parent[0x40];
                moby[0x41] = parent[0x41];
                *(float *)(moby + 0x44) = *(float *)(parent + 0x44);
                update_moby_animation_state(moby);
            }
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        switch (state->mode) {
        case 1:
            if (state->sound_index == -1 && !math_random_int_below(79))
                state->sound_index = PlayMobySound(0, 0, moby);
            if (moby[0x60] & 2) {
                if (!math_random_int_below(3)) {
                    if (moby[0x43] != 2)
                        anim_start_blended_pal(moby, 2, 0, math_random_int_range(8, 15));
                } else if (moby[0x43] != 1)
                    anim_start_blended_pal(moby, 1, 0, math_random_int_range(8, 15));
                *(float *)(moby + 0x48) = math_random_float_range(0.7f, 1.1f);
            }
            if (!math_random_int_below(19)) {
                qcopy(pos, moby + 0x10);
                pos[2] = level_get_water_height_pal();
                size = math_random_float_range(0.2f, 2.0f);
                color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
                part_spawn_drifting(pos, size, g_water_l01_height, 1.2e+04f, color);
            }
            hit = 0;
            if (part_find_owned_effect_slot(moby, 0x10001, 0))
                hit = 1;
            if (IsPointInCuboid(g_hero_position, state->hit_index))
                hit = 1;
            if (hit) {
                state->sound_index = PlayMobySound(0, 0, moby);
                part_spawn_water_splash_pal(moby, 3, 10, 1);
                if (moby[0x43] != 3)
                    anim_start_blended_pal(moby, 3, 0, 10);
                moby_set_state(moby, 2, -1);
            }
            break;
        case 2:
            switch (moby[0xBC]) {
            case 0:
                if (state->sound_index == -1 && !math_random_int_below(89))
                    state->sound_index = PlayMobySound(0, 0, moby);
                {
                    int detected = part_find_owned_effect_slot(moby, 0x10001, 0);
                    flag = 0;
                    if (detected) {
                        flag = 1;
                        muckdweller_flag_group(state->link_index);
                    }
                }
                if (state->link_index != -1 && state->link_count) {
                    if (moby_count_group_not_in_state(state->link_index, -1) < state->link_count)
                        flag = 1;
                }
                if (flag) {
                    state->sound_index = PlayMobySound(0, 0, moby);
                    part_l01_spawn_burst_pal(moby);
                    part_l01_spawn_burst_pal(moby);
                    part_l01_spawn_burst_pal(moby);
                    if (moby[0x43] != 11)
                        anim_start_blended_pal(moby, 11, 0, 15);
                    moby[0xBC] = 1;
                }
                moby[0xA8] = 255;
                break;
            case 1:
                part_l01_spawn_burst_pal(moby);
                if (moby[0x60] & 2) {
                    if (moby[0x43] != 3)
                        anim_start_blended_pal(moby, 3, 0, 15);
                    moby_set_state(moby, 2, -1);
                }
                break;
            }
            break;
        case 3:
            *(int *)(moby + 0x98) = 0;
            if (state->parent_index != -1) {
                parent = g_moby_l01_table + (state->parent_index << 8);
                if (!parent || parent[0x20] == 254 || parent[0x20] == 253) {
                    level_record_moby_collected(moby);
                } else {
                    qcopy(moby + 0x10, parent + 0x10);
                    qcopy(moby + 0xF0, parent + 0xF0);
                }
            }
            if (IsPointInCuboid(g_hero_position, state->hit_index)) {
                /* Retail shares state 2's counter and delete tails. */
                if (state->persistent) {
                    if (moby[0xB0] != 255) {
                        if ((persist_id = *(u16 *)(moby + 0xB2)) & 1)
                            goto persist_high;
                        else
                            goto persist_low;
                    }
                } else
                    goto delete_cleanup;
                goto delete_current;
            }
            /* Falls through to the sound trigger used by mode zero. */
        case 0:
            if (state->sound_index == -1 && !math_random_int_below(89))
                state->sound_index = PlayMobySound(0, 0, moby);
            break;
        }
        break;
    case 2:
        if (state->mode == 2) {
            part_l01_spawn_burst_pal(moby);
        } else if (state->mode == 1 && !math_random_int_below(4)) {
            part_spawn_water_splash_pal(moby, 3, 10, 1);
            qcopy(pos, moby + 0x10);
            pos[2] = level_get_water_height_pal();
            size = math_random_float_range(0.2f, 2.0f);
            color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
            part_spawn_drifting(pos, size, g_water_l01_height, 1.2e+04f, color);
        }
        if (moby[0x60] & 2) {
            if (state->persistent) {
                if (moby[0xB0] != 255) {
                    if ((persist_id = *(u16 *)(moby + 0xB2)) & 1) {
                        u8 *counter;
                        u32 value;
persist_high:
                        counter = g_moby_nibble_table + (((short)persist_id >> 1) + (D_001A79F0_gp << 10));
                        value = *counter;
                        if (((value >> 4) & 7) != 7)
                            *counter = value + 16;
                    } else {
                        u8 *counter;
                        u32 value;
persist_low:
                        counter = g_moby_nibble_table + (((short)persist_id >> 1) + (D_001A79F0_gp << 10));
                        value = *counter;
                        if ((value & 7) != 7)
                            *counter = value + 1;
                    }
                }
            } else {
delete_cleanup:
                level_record_moby_collected(moby);
            }
delete_current:
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    /* Retail stores the index three times; the slot found by the scan is discarded. */
    if (!snd_is_voice_playing_for_owner(moby, state->sound_index)) {
        state->sound_index = -1;
        for (i = 0; i < 52; i++) {
            state->sound_index = -1;
            entry = g_sound_state + i * 0x70;
            if (*(u8 **)(entry + 0x88) == moby && entry[0x74]) {
                state->sound_index = i;
                break;
            }
        }
        state->sound_index = -1;
    }
    if (moby[0x95]) {
        if (state->persistent) {
            if (moby[0xB0] != 255) {
                if (*(u16 *)(moby + 0xB2) & 1) {
                    u8 *counter = g_moby_nibble_table + ((*(short *)(moby + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if (((value >> 4) & 7) != 7)
                        *counter = value + 16;
                } else {
                    u8 *counter = g_moby_nibble_table + ((*(short *)(moby + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if ((value & 7) != 7)
                        *counter = value + 1;
                }
            }
        } else {
            level_record_moby_collected(moby);
        }
        moby_mark_spawned(moby);
    }
}
