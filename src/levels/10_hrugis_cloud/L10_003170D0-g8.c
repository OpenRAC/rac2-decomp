#include "include_asm.h"
#include "common.h"

extern s32 g_boss_flag_a __attribute__((sda));
extern s32 g_boss_flag_b __attribute__((sda));

/* Returns the first boss flag and clears it, so each event is seen only once. */
s32 hrugis_take_boss_flag_a(void) {
    s32 value = g_boss_flag_a;
    g_boss_flag_a = 0;
    return value;
}

/* Returns the second boss flag and clears it, so each event is seen only once. */
s32 hrugis_take_boss_flag_b(void) {
    s32 value = g_boss_flag_b;
    g_boss_flag_b = 0;
    return value;
}

extern s32 g_boss_flag_a __attribute__((sda));
extern s32 g_boss_flag_b __attribute__((sda));
extern u8 g_group_state_buffer[];
extern u8 *g_group_moby_id_lists[];
extern u8 *g_moby_pool_base;

/* Clears the arena's 128 records of 0x60 bytes and then walks the entry's two-byte
   id list, flagging every live object of one class. */
void hrugis_init_group_states(u8 *group) {
    s32 *clear_ptr;
    s32 i;
    u8 *id_list;
    u16 *id_ptr;
    u8 *moby;

    g_boss_flag_a = 0;
    clear_ptr = (s32 *)g_group_state_buffer;
    g_boss_flag_b = 0;
    clear_ptr = (s32 *)((u8 *)clear_ptr + 0x2FE0);
    for (i = 0x7F; i >= 0; i--) {
        *clear_ptr = 0;
        clear_ptr -= 0x18;
    }
    id_list = g_group_moby_id_lists[group[0x21]];
    if (id_list == 0)
        return;
    id_ptr = (u16 *)id_list;
    do {
        moby = g_moby_pool_base + ((*id_ptr & 0x7FFF) << 8);
        moby[0x20] = 1;
        if ((s16)*id_ptr < 0)
            break;
        id_ptr++;
    } while (1);
}

extern void func_0032BD98(s32 a0, u8 *a1);
extern void func_0032AF78(s32 a0);

/* Releases both timed effects the entry's live objects still hold: the id list walks the
   same arena records as func_L10_00417440, one record per id, and tears down the two
   effect slots at +0x2C4 and +0x2C0 of each record. */
void hrugis_release_group_effects(u8 *group) {
    u16 *id_ptr;
    u8 *moby;
    u8 *vars;
    u8 *id_list;
    u32 child_vars;

    id_list = g_group_moby_id_lists[group[0x21]];
    if (id_list == 0)
        return;
    id_ptr = (u16 *)id_list;
    do {
        moby = g_moby_pool_base + ((*id_ptr & 0x7FFF) << 8);
        vars = *(u8 **)(moby + 0x68);
        if (*(u8 **)(vars + 0x2C4) != 0) {
            func_0032BD98((s32)*(u8 **)(vars + 0x2C4), vars + 0x370);
            func_0032BD98((s32)*(u8 **)(vars + 0x2C4), vars + 0x3B0);
            child_vars = *(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2C4) + 0x68) + 0x18);
            if (child_vars != 0)
                func_0032AF78(child_vars);
            func_0032AF78((s32)*(u8 **)(vars + 0x2C4));
            *(u32 *)(vars + 0x2C4) = 0;
        }
        if (*(u8 **)(vars + 0x2C0) != 0) {
            func_0032BD98((s32)*(u8 **)(vars + 0x2C0), vars + 0x2F0);
            func_0032BD98((s32)*(u8 **)(vars + 0x2C0), vars + 0x330);
            child_vars = *(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2C0) + 0x68) + 0x18);
            if (child_vars != 0)
                func_0032AF78(child_vars);
            func_0032AF78((s32)*(u8 **)(vars + 0x2C0));
            *(u32 *)(vars + 0x2C0) = 0;
        }
    } while ((s16)*id_ptr++ >= 0);
}

/* The mission state (D_L10_00221CD0), as far as func_L10_00423500 resets it. */
typedef struct {
    u8 pad00[0x10];
    s32 f10;                    /* 0x10 */
    s32 rounds;                 /* 0x14 */
    u8 pad18[0x28 - 0x18];
    s32 f28;                    /* 0x28 */
    s32 waiting;                /* 0x2C */
    f32 f30;                    /* 0x30 */
} MissionState;

/* A 40-byte reward slot of D_L10_002A3C70: available while value has not reached limit. */
typedef struct {
    u8 pad[16];
    s32 limit;                  /* 0x10 */
    s32 value;                  /* 0x14 */
    u8 tail[16];
} RewardSlot;

extern s32 g_selected_mission_kind __attribute__((sda));  /* the selected kind, -2 for none */
extern s32 g_mission_initialized __attribute__((sda));
extern s32 g_kind_choosing_flag __attribute__((sda));  /* set while a kind is being chosen */
extern MissionState g_mission_state;
extern RewardSlot g_reward_slot_table[];

extern s32 table_find_last_used_entry(s32 kind);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_b(s32 value);
extern void table_reset_working_values(void);
extern void level_clear_object_records(void);

/* Resets the mission state and refills the reward slot of kind 6. */
void hrugis_reset_mission_state(void *object) {
    s32 slot;

    g_selected_mission_kind = -2;
    g_kind_choosing_flag = 1;
    g_mission_state.waiting = 1;
    g_mission_state.f28 = 100;
    g_mission_initialized = 0;
    g_mission_state.rounds = 0;
    slot = table_find_last_used_entry(6);
    g_reward_slot_table[slot].value = g_reward_slot_table[slot].limit;
    entry_init_all_registered();
    g_mission_state.f30 = 8.0f;
    g_mission_state.f10 = 0;
    hero_set_state_value_b(0);
    table_reset_working_values();
    level_clear_object_records();
}
