#include "names.h"
/* func_PAL_L10_00428D58, the PAL relative of func_L10_004235A0: the same reset with
   the two counters of func_L10_00423698, and without removing the temporary objects. */
typedef struct GornConfig { int words[10]; } GornConfig;
extern char D_L10_00221CD0[];
extern GornConfig D_L10_002A3C70[];
extern int D_L10_001B13A0 __attribute__((sda));
extern int g_mission_initialized __attribute__((sda));
extern char *D_L10_001B13F0 __attribute__((sda));
extern int D_L10_001B1438 __attribute__((sda));
extern int D_L10_001B1440 __attribute__((sda));
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern int table_find_last_used_entry(int);
extern void hero_set_state_value_b(int);
extern int cam_is_mode_active(void);
extern void func_PAL_L05_0037FEB0(void);
extern void level_clear_object_records(void);
extern void func_PAL_L05_0044BEB8(void);

void func_PAL_L10_00428D58(void) {
    char *state;
    int i;
    entry_init_all_registered();
    hero_set_state_value_a(1);
    state = D_L10_00221CD0;
    D_L10_001B13A0 = -2;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0x28) = 100;
    *(int *)(state + 0xC) = 0;
    D_L10_001B1438 = 1;
    g_mission_initialized = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x2C) = 1;
    i = table_find_last_used_entry(6);
    D_L10_001B1440 = 0;
    *(float *)(state + 0x30) = 8.0f;
    D_L10_002A3C70[i].words[5] = D_L10_002A3C70[i].words[4];
    hero_set_state_value_b(0);
    if (cam_is_mode_active()) {
        *(int *)(state + 0x2C) = 0;
        D_L10_001B13F0[0x20] = 1;
    }
    func_PAL_L05_0037FEB0();
    level_clear_object_records();
    func_PAL_L05_0044BEB8();
}
