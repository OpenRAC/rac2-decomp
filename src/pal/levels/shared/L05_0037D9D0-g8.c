#include "include_asm.h"
#include "names.h"
extern char *g_feltzin_target_mobys;
extern int g_level_object_list[];
extern int g_level_object_data[];
extern int g_spawn_list_table[];
extern char *moby_get_motion_data(char *object);
extern int level_get_saved_value(void);
extern void moby_init_spawned_sub_object(char *object, int flag);

/* Offers the entry to every registered object with the same id, then walks the entry's list
   and offers each object it names to the handler. */
void entry_spawn_list_objects_with_flag_pal(char *object, int handler)
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
