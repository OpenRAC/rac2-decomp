#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef struct GornConfig { int words[10]; } GornConfig;
extern char D_L10_00221CD0[];
extern GornConfig D_L10_002A3C70[];
extern int D_L10_001B13A0 __attribute__((sda));
extern int g_mission_initialized __attribute__((sda));
extern void *D_L10_001B1400 __attribute__((sda));
extern void *D_L10_001B1404 __attribute__((sda));
extern int D_L10_001B1438 __attribute__((sda));
extern int D_L10_001B1440 __attribute__((sda));
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
    state = D_L10_00221CD0;
    D_L10_001B13A0 = -2;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0xC) = 0;
    D_L10_001B1438 = 1;
    *(int *)(state + 0x2C) = 1;
    *(int *)(state + 0x28) = 100;
    g_mission_initialized = 0;
    *(int *)(state + 0x14) = 0;
    i = table_find_last_used_entry(6);
    D_L10_001B1440 = 0;
    *(float *)(state + 0x30) = 8.0f;
    D_L10_002A3C70[i].words[5] = D_L10_002A3C70[i].words[4];
    hero_set_state_value_b(0);
    table_reset_working_values();
    level_clear_object_records();
    ship_save_transform_state();
    if (D_L10_001B1400) { moby_mark_spawned(D_L10_001B1400); D_L10_001B1400 = 0; }
    if (D_L10_001B1404) { moby_mark_spawned(D_L10_001B1404); D_L10_001B1404 = 0; }
}
