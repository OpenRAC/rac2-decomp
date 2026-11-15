#include "common.h"

extern int g_mission_initialized __attribute__((sda));
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
extern void hrugis_finish_mission_reward(void *, int);

/* Mission controller for the third challenge: sets up on the first frame, then ends the round
   once every class 3982 target is gone. */
void mission_third_update(void *object)
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
            if (*(short *)(entries[i] + 0xAA) == 0xF8E /* moby class 3982 */)
                entry_spawn_list_objects_with_flag(entries[i], 1);
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(0x32, (void *)0xC);
    }
    if (!list_count_ready_objects(level_find_object_by_class_id(0xF8E /* moby class 3982 */)))
        hrugis_finish_mission_reward(object, 2);
}
