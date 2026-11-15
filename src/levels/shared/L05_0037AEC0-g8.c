#include "include_asm.h"
#include "names.h"

/* Built with -G8: the spawn counter at 0x1AC4D8 and the object table base at 0x1B251C are
   reached through $gp in retail, so those two bodies live here. */

extern int D_L05_001AC4D8 __attribute__((sda));

extern char *D_L05_001B251C;

extern int D_L05_00225DD0[];

extern int D_L05_00225E50[];

extern int D_L05_00225F50[];

extern char *D_L05_001B2528 __attribute__((nosda));

extern int D_L05_00221D10[];

extern int D_L05_001FB220[];

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

    for (i = 0; i < D_L05_001AC4D8; i++)
        entry_spawn_list_objects(D_L05_00225DD0[i]);
    D_L05_00221D10[4] = 0;
    D_L05_00221D10[3] = 0;
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

    if (D_L05_001FB220[obj[0x21]] == 0)
        return;

    count = level_get_saved_value();
    for (i = 0; i < count; i++) {
        char *e = (char *)D_L05_00225DD0[i];

        if (*(short *)(e + 0xAA) == *(short *)(obj + 0xAA)) {
            void (*fn)(char *) = (void (*)(char *))D_L05_00225F50[i];

            if (fn != 0)
                fn(e);
        }
    }

    p = (unsigned short *)D_L05_001FB220[obj[0x21]];
    do {
        char *base;

        off = (p[0] & 0x7FFF) << 8;
        base = D_L05_001B251C;
        if (moby_get_motion_data(base + off) != 0) {
            base = D_L05_001B251C;
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

    if (D_L05_001FB220[obj[0x21]] == 0)
        return;

    count = level_get_saved_value();
    for (i = 0; i < count; i++) {
        char *e = (char *)D_L05_00225DD0[i];

        if (*(short *)(e + 0xAA) == *(short *)(obj + 0xAA)) {
            void (*fn)(char *) = (void (*)(char *))D_L05_00225E50[i];

            if (fn != 0)
                fn(e);
        }
    }

    p = (unsigned short *)D_L05_001FB220[obj[0x21]];
    do {
        char *base;

        off = (p[0] & 0x7FFF) << 8;
        base = D_L05_001B251C;
        if (moby_get_motion_data(base + off) != 0) {
            base = D_L05_001B251C;
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

    for (i = 0; i < D_L05_001AC4D8; i++) {
        char *obj = (char *)D_L05_00225DD0[i];
        if (*(short *)(obj + 0xAA) == id) {
            short *entry;
            int list = D_L05_001FB220[*(unsigned char *)(obj + 0x21)];
            if (list == 0)
                return 0;
            entry = (short *)list;
            do {
                unsigned int offset = (*entry & 0x7FFF) << 8;
                char *v = (char *)moby_get_motion_data(D_L05_001B251C + offset);
                if (v != 0 && *(int *)(v + 0x110) == 0) {
                    spawned = D_L05_001B251C + offset;
                    moby_init_spawned_sub_object(spawned, flag);
                    break;
                }
            } while (*entry++ >= 0);
            return spawned;
        }
    }
    return spawned;
}
