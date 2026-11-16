#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef struct GornConfig { int words[10]; } GornConfig;
extern char g_mission_state[];
extern GornConfig g_reward_slot_table[];
extern int g_selected_mission_kind __attribute__((sda));
extern int g_mission_initialized __attribute__((sda));
extern void *g_gate_first __attribute__((sda));
extern void *g_gate_second __attribute__((sda));
extern int g_kind_choosing_flag __attribute__((sda));
extern int g_reward_active_flag __attribute__((sda));
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern int table_find_last_used_entry(int);
extern void hero_set_state_value_b(int);
extern void table_reset_working_values(void);
extern void level_clear_object_records(void);
extern void ship_save_transform_state(void);
extern void moby_mark_spawned(void *);

/* Resets the mission (the 004235A0 body without the carried-object test, with two more counters)'s shared counters and removes its two temporary objects. */
void mission_reset_counters_alt(void) {
    char *state;
    int i;
    entry_init_all_registered();
    hero_set_state_value_a(1);
    state = g_mission_state;
    g_selected_mission_kind = -2;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0xC) = 0;
    g_kind_choosing_flag = 1;
    *(int *)(state + 0x2C) = 1;
    *(int *)(state + 0x28) = 100;
    g_mission_initialized = 0;
    *(int *)(state + 0x14) = 0;
    i = table_find_last_used_entry(6);
    g_reward_active_flag = 0;
    *(float *)(state + 0x30) = 8.0f;
    g_reward_slot_table[i].words[5] = g_reward_slot_table[i].words[4];
    hero_set_state_value_b(0);
    table_reset_working_values();
    level_clear_object_records();
    ship_save_transform_state();
    if (g_gate_first) { moby_mark_spawned(g_gate_first); g_gate_first = 0; }
    if (g_gate_second) { moby_mark_spawned(g_gate_second); g_gate_second = 0; }
}
