#include "include_asm.h"
#include "names.h"

extern int g_level_object_count __attribute__((sda));
extern char *g_feltzin_target_mobys;
extern int g_level_object_list[];
extern int g_spawn_list_table[];
extern char *moby_get_motion_data(char *object);
extern void moby_init_spawned_sub_object_pal(char *object, int flag);

/* Finds the free entry of the level list that belongs to id and spawns it there. */
char *SpawnFreeLevelObjectById_pal(int id, int flag)
{
    int i;
    char *spawned = 0;

    for (i = 0; i < g_level_object_count; i++) {
        char *obj = (char *)g_level_object_list[i];
        if (*(short *)(obj + 0xAA) == id) {
            short *entry;
            int list = g_spawn_list_table[*(unsigned char *)(obj + 0x21)];
            if (list == 0)
                return 0;
            entry = (short *)list;
            do {
                unsigned int offset = (*entry & 0x7FFF) << 8;
                char *v = (char *)moby_get_motion_data(g_feltzin_target_mobys + offset);
                if (v != 0 && *(int *)(v + 0x110) == 0) {
                    spawned = g_feltzin_target_mobys + offset;
                    moby_init_spawned_sub_object_pal(spawned, flag);
                    break;
                }
            } while (*entry++ >= 0);
            return spawned;
        }
    }
    return spawned;
}
