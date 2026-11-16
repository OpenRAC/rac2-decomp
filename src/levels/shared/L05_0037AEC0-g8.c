#include "include_asm.h"
#include "names.h"

/* Built with -G8: the spawn counter at 0x1AC4D8 and the object table base at 0x1B251C are
   reached through $gp in retail, so those two bodies live here. */

extern int g_level_object_count __attribute__((sda));

extern char *g_feltzin_target_mobys;

extern int g_level_object_list[];

extern int g_level_object_data[];

extern int g_level_object_extras[];

extern char *g_moby_l05_list_head __attribute__((nosda));

extern int g_feltzin_challenge_state[];

extern int g_spawn_list_table[];

extern char *moby_get_motion_data(char *object);

extern int level_get_saved_value(void);

extern void moby_reset_action_state(char *object);

extern void moby_init_spawned_sub_object(char *object, int flag);

extern void moby_mark_spawned(void *object);

extern /* Sets up one effect entry: calls the callbacks of matching registered objects, then spawns each object in its list. */
void entry_spawn_list_objects(int entry);

extern void effect_remove_family_mobys(void);

/* Runs the constructor over every registered entry, then clears the two shared counters. */
/* Sets up every registered effect entry, then resets the two shared counters. */
void entry_init_all_registered(void)
{
    int i;

    for (i = 0; i < g_level_object_count; i++)
        entry_spawn_list_objects(g_level_object_list[i]);
    g_feltzin_challenge_state[4] = 0;
    g_feltzin_challenge_state[3] = 0;
    effect_remove_family_mobys();
}

/* Runs the entry's list: every registered object with the same id gets its callback, then
   every object the list names is looked up and set. */
void entry_spawn_list_objects(int entry)
{
    unsigned char *obj = (unsigned char *)entry;
    int count;
    int i;
    unsigned short *p;
    int off;

    if (g_spawn_list_table[obj[0x21]] == 0)
        return;

    count = level_get_saved_value();
    for (i = 0; i < count; i++) {
        char *e = (char *)g_level_object_list[i];

        if (*(short *)(e + 0xAA) == *(short *)(obj + 0xAA)) {
            void (*fn)(char *) = (void (*)(char *))g_level_object_extras[i];

            if (fn != 0)
                fn(e);
        }
    }

    p = (unsigned short *)g_spawn_list_table[obj[0x21]];
    do {
        char *base;

        off = (p[0] & 0x7FFF) << 8;
        base = g_feltzin_target_mobys;
        if (moby_get_motion_data(base + off) != 0) {
            base = g_feltzin_target_mobys;
            moby_reset_action_state(base + off);
        }
    } while (*(short *)p++ >= 0);
}

/* Offers the entry to every registered object with the same id, then walks the entry's list
   and offers each object it names to the handler. */
/* Same as the entry setup above, but spawns the listed objects with a given flag. */
void entry_spawn_list_objects_with_flag(char *object, int handler)
{
    unsigned char *obj = (unsigned char *)object;
    int count;
    int i;
    unsigned short *p;
    int off;

    if (g_spawn_list_table[obj[0x21]] == 0)
        return;

    count = level_get_saved_value();
    for (i = 0; i < count; i++) {
        char *e = (char *)g_level_object_list[i];

        if (*(short *)(e + 0xAA) == *(short *)(obj + 0xAA)) {
            void (*fn)(char *) = (void (*)(char *))g_level_object_data[i];

            if (fn != 0)
                fn(e);
        }
    }

    p = (unsigned short *)g_spawn_list_table[obj[0x21]];
    do {
        char *base;

        off = (p[0] & 0x7FFF) << 8;
        base = g_feltzin_target_mobys;
        if (moby_get_motion_data(base + off) != 0) {
            base = g_feltzin_target_mobys;
            moby_init_spawned_sub_object(base + off, handler);
        }
    } while (*(short *)p++ >= 0);
}

/* Walks the live-object list and hands the objects of the listed ids to the shared handler. */
extern void effect_remove_family_mobys(void);

/* Finds the free entry of the level list that belongs to id and spawns it there. */
/* Finds the first listed object that is free and spawns it. */
char *SpawnFreeLevelObjectById(int id, int flag)
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
                    moby_init_spawned_sub_object(spawned, flag);
                    break;
                }
            } while (*entry++ >= 0);
            return spawned;
        }
    }
    return spawned;
}
