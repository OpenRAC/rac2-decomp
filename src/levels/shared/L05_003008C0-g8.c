#include "include_asm.h"
#include "names.h"

extern int g_level_l05_saved_value;
extern void func_0029BCC8(void);

/* Returns the saved value and then calls a shared helper. */
int level_get_saved_value_and_release(void) {
    int value = g_level_l05_saved_value;
    func_0029BCC8();
    return value;
}

extern int g_level_step_table[1] __attribute__((sda));

/* Replaces the shared step with its table entry, leaving a negative step alone. */
int level_lookup_step_table(void)
{
    int step = level_get_saved_value_and_release();

    if (step >= 0)
        step = g_level_step_table[step];
    return step;
}

extern int g_level_counter;

/* Stores the given value plus one in a shared counter. */
void level_set_counter_plus_one(int value) {
    g_level_counter = value + 1;
}

extern int g_level_object_count __attribute__((sda));
extern int g_level_object_list[];
extern int g_level_object_data[];
extern int g_level_object_callbacks[];
extern int g_level_object_extras[];

/* Adds an object and its callback to the end of the live object list. */
void level_append_object(int object, int data, int callback, int extra) {
    int count = g_level_object_count;
    g_level_object_list[count] = object;
    g_level_object_data[count] = data;
    g_level_object_callbacks[count] = callback;
    g_level_object_extras[count] = extra;
    g_level_object_count = count + 1;
}

/* Walk the live object list and return the first one whose id matches. */
/* Standalone declarations recovered from src/levels/shared/L05_003008C0-g8.c. */
extern int g_level_object_count __attribute__((sda));

extern int g_level_object_list[];

/* Returns the first live object with the given class id, or 0. */
void *level_find_object_by_class_id(int classId) {
    int i;

    for (i = 0; i < g_level_object_count; i++) {
        char *item = (char *)g_level_object_list[i];

        if (*(short *)(item + 0xAA) == classId)
            return (int)item;
    }
    return 0;
}
