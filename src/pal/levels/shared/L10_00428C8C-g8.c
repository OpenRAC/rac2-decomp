#include "names.h"
/* func_PAL_L10_00428C8C, the PAL copy of func_L10_004235A0: the same C, where the callees func_L05_0037D6E8 and
   func_L05_00445A98 become func_PAL_L05_0037FEB0 and func_PAL_L05_0044BEB8, and the two closing tests that free
   D_L10_001B1400 and D_L10_001B1404 are gone. */
typedef struct GornConfig { int words[10]; } GornConfig;
extern char g_mission_state[];
extern GornConfig g_reward_slot_table[];
extern int g_mission_initialized __attribute__((sda));
extern char *g_hud_blink_moby __attribute__((sda));
extern int g_reward_active_flag __attribute__((sda));
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern int table_find_last_used_entry(int);
extern void hero_set_state_value_b(int);
extern int cam_is_mode_active(void);
extern void table_reset_working_values_pal(void);
extern void level_clear_object_records(void);
extern void ship_save_transform_state_pal(void);

/* Resets the mission's shared counters. */
void mission_reset_counters_pal(void) {
    char *state;
    int i;
    entry_init_all_registered();
    hero_set_state_value_a(1);
    state = g_mission_state;
    *(int *)(state + 0x28) = 100;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0xC) = 0;
    g_mission_initialized = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x2C) = 1;
    i = table_find_last_used_entry(6);
    g_reward_active_flag = 0;
    *(float *)(state + 0x30) = 8.0f;
    g_reward_slot_table[i].words[5] = g_reward_slot_table[i].words[4];
    hero_set_state_value_b(0);
    if (cam_is_mode_active()) {
        *(int *)(state + 0x2C) = 0;
        g_hud_blink_moby[0x20] = 1;
    }
    table_reset_working_values_pal();
    level_clear_object_records();
    ship_save_transform_state_pal();
}
