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
extern float func_PAL_L01_003BEB40(void);
extern void *part_spawn_drifting(void *position, float size, void *owner, float spin, int color);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void func_PAL_L01_003DD0E8(void *, int, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_L01_003DCCC8(void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int IsPointInCuboid(void *, int);
typedef struct {
    u8 pad[0x50];
    int mode;
    int parentIndex;
    int hitIndex;
    int childIndex;
    int persistent;
    int linkIndex;
    int linkCount;
    u8 unknown6c[4];
    int soundIndex;
} HandlerState;

/* Per-state update: state 0 initialises by mode, 1 runs the mode's behaviour, 2 finishes.
   A persistent moby (save id at +0xB2) counts itself in the level's 3-bit collection
   counters before it is deleted; any other one is recorded by func_L01_003D8AD0. */
void func_PAL_L01_003DD368(u8 *a0)
{
    HandlerState *state = *(HandlerState **)(a0 + 0x68);
    u8 *p;
    u8 *entry;
    int flag, hit, i, color, persist_id;
    float f;
    float v[4] __attribute__((aligned(16)));

    switch (a0[0x20]) {
    case 0:
        if (state->persistent && a0[0xB0] != 255) {
            u16 id = *(u16 *)(a0 + 0xB2);
            int bits;
            if (g_level_save_state_backup.collected[(short)id] ||
                (bits = g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)],
                 (id & 1) ? ((bits >> 4) & 7) : (bits & 7))) {
                if (state->childIndex != -1)
                    moby_mark_spawned(g_moby_l01_table + (state->childIndex << 8));
                moby_mark_spawned(a0);
                return;
            }
        }
        a0[0x95] = 0;
        state->soundIndex = -1;
        switch (state->mode) {
        case 0:
            *(u16 *)(a0 + 0x32) = 0x3FF;
            a0[0x30] = 255;
            if (state->parentIndex != -1) {
                u8 *parent = g_moby_l01_table + (state->parentIndex << 8);
                if (parent) {
                    if (*(u8 **)(parent + 0x68) && *(int *)(*(u8 **)(parent + 0x68) + 0xC8))
                        anim_start_immediate(a0, 6, 0);
                    else
                        anim_start_immediate(a0, 9, 0);
                }
            }
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * g_pod_scale_factor_a;
            break;
        case 1:
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * g_pod_scale_factor_b;
            anim_start_immediate(a0, 2, 0);
            break;
        case 2:
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * g_pod_scale_factor_c;
            anim_start_immediate(a0, 4, 0);
            if (state->linkIndex != -1)
                state->linkCount = moby_count_group_not_in_state(state->linkIndex, -1);
            break;
        case 3:
            *(int *)(a0 + 0x98) = 0;
            *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * g_pod_scale_factor_d;
            anim_start_immediate(a0, 10, 0);
            break;
        }
        if (state->parentIndex != -1) {
            p = g_moby_l01_table + (state->parentIndex << 8);
            if (p) {
                a0[0x40] = p[0x40];
                a0[0x41] = p[0x41];
                *(float *)(a0 + 0x44) = *(float *)(p + 0x44);
                update_moby_animation_state(a0);
            }
        }
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        switch (state->mode) {
        case 1:
            if (state->soundIndex == -1 && !math_random_int_below(79))
                state->soundIndex = PlayMobySound(0, 0, a0);
            if (a0[0x60] & 2) {
                if (!math_random_int_below(3)) {
                    if (a0[0x43] != 2)
                        func_PAL_002A7E68(a0, 2, 0, math_random_int_range(8, 15));
                } else if (a0[0x43] != 1)
                    func_PAL_002A7E68(a0, 1, 0, math_random_int_range(8, 15));
                *(float *)(a0 + 0x48) = math_random_float_range(0.7f, 1.1f);
            }
            if (!math_random_int_below(19)) {
                qcopy(v, a0 + 0x10);
                v[2] = func_PAL_L01_003BEB40();
                f = math_random_float_range(0.2f, 2.0f);
                color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
                part_spawn_drifting(v, f, g_water_l01_height, 1.2e+04f, color);
            }
            hit = 0;
            if (part_find_owned_effect_slot(a0, 0x10001, 0))
                hit = 1;
            if (IsPointInCuboid(g_hero_position, state->hitIndex))
                hit = 1;
            if (hit) {
                state->soundIndex = PlayMobySound(0, 0, a0);
                func_PAL_L01_003DD0E8(a0, 3, 10, 1);
                if (a0[0x43] != 3)
                    func_PAL_002A7E68(a0, 3, 0, 10);
                moby_set_state(a0, 2, -1);
            }
            break;
        case 2:
            switch (a0[0xBC]) {
            case 0:
                if (state->soundIndex == -1 && !math_random_int_below(89))
                    state->soundIndex = PlayMobySound(0, 0, a0);
                {
                    int detected = part_find_owned_effect_slot(a0, 0x10001, 0);
                    flag = 0;
                    if (detected) {
                        flag = 1;
                        muckdweller_flag_group(state->linkIndex);
                    }
                }
                if (state->linkIndex != -1 && state->linkCount) {
                    if (moby_count_group_not_in_state(state->linkIndex, -1) < state->linkCount)
                        flag = 1;
                }
                if (flag) {
                    state->soundIndex = PlayMobySound(0, 0, a0);
                    func_PAL_L01_003DCCC8(a0);
                    func_PAL_L01_003DCCC8(a0);
                    func_PAL_L01_003DCCC8(a0);
                    if (a0[0x43] != 11)
                        func_PAL_002A7E68(a0, 11, 0, 15);
                    a0[0xBC] = 1;
                }
                a0[0xA8] = 255;
                break;
            case 1:
                func_PAL_L01_003DCCC8(a0);
                if (a0[0x60] & 2) {
                    if (a0[0x43] != 3)
                        func_PAL_002A7E68(a0, 3, 0, 15);
                    moby_set_state(a0, 2, -1);
                }
                break;
            }
            break;
        case 3:
            *(int *)(a0 + 0x98) = 0;
            if (state->parentIndex != -1) {
                p = g_moby_l01_table + (state->parentIndex << 8);
                if (!p || p[0x20] == 254 || p[0x20] == 253) {
                    level_record_moby_collected(a0);
                } else {
                    qcopy(a0 + 0x10, p + 0x10);
                    qcopy(a0 + 0xF0, p + 0xF0);
                }
            }
            if (IsPointInCuboid(g_hero_position, state->hitIndex)) {
                /* Retail shares state 2's counter and delete tails. */
                if (state->persistent) {
                    if (a0[0xB0] != 255) {
                        if ((persist_id = *(u16 *)(a0 + 0xB2)) & 1)
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
            if (state->soundIndex == -1 && !math_random_int_below(89))
                state->soundIndex = PlayMobySound(0, 0, a0);
            break;
        }
        break;
    case 2:
        if (state->mode == 2) {
            func_PAL_L01_003DCCC8(a0);
        } else if (state->mode == 1 && !math_random_int_below(4)) {
            func_PAL_L01_003DD0E8(a0, 3, 10, 1);
            qcopy(v, a0 + 0x10);
            v[2] = func_PAL_L01_003BEB40();
            f = math_random_float_range(0.2f, 2.0f);
            color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
            part_spawn_drifting(v, f, g_water_l01_height, 1.2e+04f, color);
        }
        if (a0[0x60] & 2) {
            if (state->persistent) {
                if (a0[0xB0] != 255) {
                    if ((persist_id = *(u16 *)(a0 + 0xB2)) & 1) {
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
                level_record_moby_collected(a0);
            }
delete_current:
            moby_mark_spawned(a0);
            return;
        }
        break;
    }
    /* Retail stores the index three times; the slot found by the scan is discarded. */
    if (!snd_is_voice_playing_for_owner(a0, state->soundIndex)) {
        state->soundIndex = -1;
        for (i = 0; i < 52; i++) {
            state->soundIndex = -1;
            entry = g_sound_state + i * 0x70;
            if (*(u8 **)(entry + 0x88) == a0 && entry[0x74]) {
                state->soundIndex = i;
                break;
            }
        }
        state->soundIndex = -1;
    }
    if (a0[0x95]) {
        if (state->persistent) {
            if (a0[0xB0] != 255) {
                if (*(u16 *)(a0 + 0xB2) & 1) {
                    u8 *counter = g_moby_nibble_table + ((*(short *)(a0 + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if (((value >> 4) & 7) != 7)
                        *counter = value + 16;
                } else {
                    u8 *counter = g_moby_nibble_table + ((*(short *)(a0 + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if ((value & 7) != 7)
                        *counter = value + 1;
                }
            }
        } else {
            level_record_moby_collected(a0);
        }
        moby_mark_spawned(a0);
    }
}
