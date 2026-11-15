#include "common.h"

extern u8 *g_moby_l01_table;

extern u32 D_L01_001FB020[];

extern u8 *func_00305EE8(int);
extern s32 func_355780(u32 a0, u32 a1, void *a2);
extern void func_00308938(void *);
extern void func_00314D00(void *);
extern float D_L01_001B0540 __attribute__((sda));

/* The spawned moby's vars (+0x68). Struct stores let the fixed scalar scale
   load be scheduled ahead of the model-pointer load, as in retail. */
typedef struct {
    u8 pad0[0x60];
    u8 pos[0x10];
    u8 *owner;
    int link;
    int timer;
    u16 index;
    s16 target;
} SpawnVars;

/* Creates a child moby at a position and ties it to its owner. */
u8 *moby_l01_spawn_child(u8 *owner, void *pos, void *vel, int cls, int index)
{
    u8 *child = func_00305EE8(cls);
    if (child) {
        u8 *parent = *(u8 **)(owner + 0x68);
        SpawnVars *state = *(SpawnVars **)(child + 0x68);
        child[0x30] = 0xFF;
        *(s8 *)(child + 0x31) = 1;
        *(u16 *)(child + 0x32) = 0xFF;
        child[0x20] = 0;
        child[0xBC] = 0;
        state->owner = owner;
        state->index = index;
        *(float *)(child + 0x2C) = *(float *)(*(u8 **)(child + 0x24) + 0x24) * D_L01_001B0540;
        qcopy(child + 0x10, pos);
        qcopy(child + 0xF0, vel);
        qcopy(state->pos, pos);
        {
            int value;
            parent += index * 4;
            value = *(int *)(parent + 0x10);
            state->target = -1;
            state->link = value;
        }
        state->timer = 0;
        func_355780(2, 0, child);
        func_00308938(child);
        func_00314D00(child);
    }
    return child;
}

/* Walks the 0x7FFF-masked id list at table[index] and flags class 0xB2B entries. */
/* Flags every Mutant Muckdweller in a linked list so that it reacts. */
void muckdweller_flag_group(s32 index)
{
    u16 *id_ptr;
    u32 slot;
    u8 *base;
    u8 *entry;

    if (index == -1)
        return;
    slot = D_L01_001FB020[index];
    if (slot == 0)
        return;
    id_ptr = (u16 *)slot;
    base = g_moby_l01_table;
    do {
        entry = base + ((*id_ptr & 0x7FFF) << 8);
        if (*(s8 *)(entry + 0x20) >= 0 && *(s16 *)(entry + 0xAA) == MOBY_CLASS_MUTANT_MUCKDWELLER)
            *(u16 *)(*(u8 **)(entry + 0x68) + 0x3DA) = 1;
    } while (*(s16 *)id_ptr++ >= 0);
}

extern int g_current_map_index;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[];
/* Level save state: collected[] is indexed by a moby's save id (s16 at +0xB2). */
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState D_L01_0021D840;
extern LevelSaveState D_L01_0021E4B0;
typedef struct { u8 flags[256]; } MissionFlags;
extern MissionFlags D_L01_001B23A0 __attribute__((sda));

/* Records a moby (mission byte +0xB0, save id +0xB2) in the current and checkpoint
   collected[] tables; same shape as RAC1's helga_update tail. */
/* Records that a moby was collected, in the current and the checkpoint tables. */
void level_record_moby_collected(u8 *moby)
{
    u8 *counter;
    u8 group;

    if (moby[0xB0] != 0xFF && *(short *)(moby + 0xB2) >= 0 && !(moby[0xB1] & 0x80)) {
        if (*(u16 *)(moby + 0xB2) & 1) {
            counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (g_current_map_index << 10));
            if (((*counter >> 4) & 7) != 7) *counter += 0x10;
        } else {
            counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (g_current_map_index << 10));
            if ((*counter & 7) != 7) ++*counter;
        }
        D_L01_0021D840.collected[*(short *)(moby + 0xB2)] = moby[0xB0] + 2;
        if (moby[0xB0] == 0xFF) goto record;
        group = moby[0xB0];
        if (!(D_L01_001B23A0.flags[group] & 0x80) && (D_0019B2E8[group + (g_current_map_index << 4)] & 0x80)) {
        record:
            D_L01_0021E4B0.collected[*(short *)(moby + 0xB2)] = moby[0xB0] + 2;
        }
    }
}

extern u8 g_sound_state[], g_hero_position[];
extern u8 D_L01_001AFE18[] MACRO_ADDR;
/* The tails read the level number $gp-relative, case 0 through D_001A79F0's absolute address. */
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern float D_L01_001B0794 __attribute__((sda));
extern float D_L01_001B0798 __attribute__((sda));
extern float D_L01_001B079C __attribute__((sda));
extern float D_L01_001B07A0 __attribute__((sda));
extern void moby_mark_spawned(void *);
extern void anim_start_immediate(void *, int, int);
extern int moby_count_group_not_in_state(int, int);
extern void update_moby_animation_state(void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int PlayMobySound(int, int, void *);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float level_get_water_height(void);
extern void *part_spawn_drifting(void *position, float size, void *owner, float spin, int color);
extern int part_find_owned_effect_slot(void *, int, int);
extern void part_spawn_water_splash(void *, int, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void part_l01_spawn_burst(void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int IsPointInCuboid(void *, int);

/* The moby's vars (+0x68). */
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
/* Updates a moby that bursts open, with several modes. It makes sparkles, bursts into particles when it is hit and is removed after it is counted. */
void bursting_pod_update(u8 *moby)
{
    HandlerState *state = *(HandlerState **)(moby + 0x68);
    u8 *linked_moby;
    u8 *entry;
    int flag, hit, i, color, persist_id;
    float size;
    float position[4] __attribute__((aligned(16)));

    switch (moby[0x20]) {
    case 0:
        if (state->persistent && moby[0xB0] != 255) {
            u16 id = *(u16 *)(moby + 0xB2);
            int bits;
            if (D_L01_0021E4B0.collected[(short)id] ||
                (bits = D_0019B4A8[((short)id >> 1) + (g_current_map_index << 10)],
                 (id & 1) ? ((bits >> 4) & 7) : (bits & 7))) {
                if (state->childIndex != -1)
                    moby_mark_spawned(g_moby_l01_table + (state->childIndex << 8));
                moby_mark_spawned(moby);
                return;
            }
        }
        moby[0x95] = 0;
        state->soundIndex = -1;
        switch (state->mode) {
        case 0:
            *(u16 *)(moby + 0x32) = 0x3FF;
            moby[0x30] = 255;
            if (state->parentIndex != -1) {
                u8 *parent = g_moby_l01_table + (state->parentIndex << 8);
                if (parent) {
                    if (*(u8 **)(parent + 0x68) && *(int *)(*(u8 **)(parent + 0x68) + 0xC8))
                        anim_start_immediate(moby, 6, 0);
                    else
                        anim_start_immediate(moby, 9, 0);
                }
            }
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B0794;
            break;
        case 1:
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B0798;
            anim_start_immediate(moby, 2, 0);
            break;
        case 2:
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B079C;
            anim_start_immediate(moby, 4, 0);
            if (state->linkIndex != -1)
                state->linkCount = moby_count_group_not_in_state(state->linkIndex, -1);
            break;
        case 3:
            *(int *)(moby + 0x98) = 0;
            *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B07A0;
            anim_start_immediate(moby, 10, 0);
            break;
        }
        if (state->parentIndex != -1) {
            linked_moby = g_moby_l01_table + (state->parentIndex << 8);
            if (linked_moby) {
                moby[0x40] = linked_moby[0x40];
                moby[0x41] = linked_moby[0x41];
                *(float *)(moby + 0x44) = *(float *)(linked_moby + 0x44);
                update_moby_animation_state(moby);
            }
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        switch (state->mode) {
        case 1:
            if (state->soundIndex == -1 && !math_random_int_below(79))
                state->soundIndex = PlayMobySound(0, 0, moby);
            if (moby[0x60] & 2) {
                if (!math_random_int_below(3)) {
                    if (moby[0x43] != 2)
                        anim_start_blended(moby, 2, 0, math_random_int_range(8, 15));
                } else if (moby[0x43] != 1)
                    anim_start_blended(moby, 1, 0, math_random_int_range(8, 15));
                *(float *)(moby + 0x48) = math_random_float_range(0.7f, 1.1f);
            }
            if (!math_random_int_below(19)) {
                qcopy(position, moby + 0x10);
                position[2] = level_get_water_height();
                size = math_random_float_range(0.2f, 2.0f);
                color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
                part_spawn_drifting(position, size, D_L01_001AFE18, 10000.0f, color);
            }
            hit = 0;
            if (part_find_owned_effect_slot(moby, 0x10001, 0))
                hit = 1;
            if (IsPointInCuboid(g_hero_position, state->hitIndex))
                hit = 1;
            if (hit) {
                state->soundIndex = PlayMobySound(0, 0, moby);
                part_spawn_water_splash(moby, 3, 10, 1);
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 10);
                moby_set_state(moby, 2, -1);
            }
            break;
        case 2:
            switch (moby[0xBC]) {
            case 0:
                if (state->soundIndex == -1 && !math_random_int_below(89))
                    state->soundIndex = PlayMobySound(0, 0, moby);
                {
                    int detected = part_find_owned_effect_slot(moby, 0x10001, 0);
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
                    state->soundIndex = PlayMobySound(0, 0, moby);
                    part_l01_spawn_burst(moby);
                    part_l01_spawn_burst(moby);
                    part_l01_spawn_burst(moby);
                    if (moby[0x43] != 11)
                        anim_start_blended(moby, 11, 0, 15);
                    moby[0xBC] = 1;
                }
                moby[0xA8] = 255;
                break;
            case 1:
                part_l01_spawn_burst(moby);
                if (moby[0x60] & 2) {
                    if (moby[0x43] != 3)
                        anim_start_blended(moby, 3, 0, 15);
                    moby_set_state(moby, 2, -1);
                }
                break;
            }
            break;
        case 3:
            *(int *)(moby + 0x98) = 0;
            if (state->parentIndex != -1) {
                linked_moby = g_moby_l01_table + (state->parentIndex << 8);
                if (!linked_moby || linked_moby[0x20] == 254 || linked_moby[0x20] == 253) {
                    level_record_moby_collected(moby);
                } else {
                    qcopy(moby + 0x10, linked_moby + 0x10);
                    qcopy(moby + 0xF0, linked_moby + 0xF0);
                }
            }
            if (IsPointInCuboid(g_hero_position, state->hitIndex)) {
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
            if (state->soundIndex == -1 && !math_random_int_below(89))
                state->soundIndex = PlayMobySound(0, 0, moby);
            break;
        }
        break;
    case 2:
        if (state->mode == 2) {
            part_l01_spawn_burst(moby);
        } else if (state->mode == 1 && !math_random_int_below(4)) {
            part_spawn_water_splash(moby, 3, 10, 1);
            qcopy(position, moby + 0x10);
            position[2] = level_get_water_height();
            size = math_random_float_range(0.2f, 2.0f);
            color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
            part_spawn_drifting(position, size, D_L01_001AFE18, 10000.0f, color);
        }
        if (moby[0x60] & 2) {
            if (state->persistent) {
                if (moby[0xB0] != 255) {
                    if ((persist_id = *(u16 *)(moby + 0xB2)) & 1) {
                        u8 *counter;
                        u32 value;
persist_high:
                        counter = D_0019B4A8 + (((short)persist_id >> 1) + (D_001A79F0_gp << 10));
                        value = *counter;
                        if (((value >> 4) & 7) != 7)
                            *counter = value + 16;
                    } else {
                        u8 *counter;
                        u32 value;
persist_low:
                        counter = D_0019B4A8 + (((short)persist_id >> 1) + (D_001A79F0_gp << 10));
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
    if (!snd_is_voice_playing_for_owner(moby, state->soundIndex)) {
        state->soundIndex = -1;
        for (i = 0; i < 52; i++) {
            state->soundIndex = -1;
            entry = g_sound_state + i * 0x70;
            if (*(u8 **)(entry + 0x88) == moby && entry[0x74]) {
                state->soundIndex = i;
                break;
            }
        }
        state->soundIndex = -1;
    }
    if (moby[0x95]) {
        if (state->persistent) {
            if (moby[0xB0] != 255) {
                if (*(u16 *)(moby + 0xB2) & 1) {
                    u8 *counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (D_001A79F0_gp << 10));
                    u32 value = *counter;
                    if (((value >> 4) & 7) != 7)
                        *counter = value + 16;
                } else {
                    u8 *counter = D_0019B4A8 + ((*(short *)(moby + 0xB2) >> 1) + (D_001A79F0_gp << 10));
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
