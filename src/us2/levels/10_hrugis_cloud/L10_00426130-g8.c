#include "names.h"
/* func_US2_L10_00426130, the v2.00 copy of func_L10_00424448: the same C, plus destroying the two
 * path markers func_US2_L10_00426260 may have left behind. Its own unit for -G8. */
#include "common.h"

extern int g_mission_initialized __attribute__((sda));
typedef struct { char pad[0x34]; unsigned short flags; } GateObject;
extern GateObject *D_L10_001B1400 __attribute__((sda)), *D_L10_001B1404 __attribute__((sda));
extern void moby_mark_spawned(void *);
extern int D_L10_00221CFC __attribute__((section(".data")));
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern unsigned char **level_get_object_list(void);
extern int level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(void *, int);
extern void cloud_destroy_leftover_objects(void);
extern void cloud_spawn_objects(int, void *);
extern void *level_find_object_by_class_id(int);
extern int list_count_ready_objects(void *);
extern void func_US2_L10_00425A78(void *, int);

void func_US2_L10_00426130(void *object)
{
    unsigned char **entries;
    int i, count;

    if (!g_mission_initialized) {
        D_L10_00221CFC = 0;
        g_mission_initialized = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        entries = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (*(short *)(entries[i] + 0xAA) == 0xF8E)
                entry_spawn_list_objects_with_flag(entries[i], 1);
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(0x32, (void *)0xC);
        if (D_L10_001B1400 && D_L10_001B1400->flags) {
            moby_mark_spawned(D_L10_001B1400);
            D_L10_001B1400 = 0;
        }
        if (D_L10_001B1404 && D_L10_001B1404->flags) {
            moby_mark_spawned(D_L10_001B1404);
            D_L10_001B1404 = 0;
        }
    }
    if (!list_count_ready_objects(level_find_object_by_class_id(0xF8E)))
        func_US2_L10_00425A78(object, 2);
}
