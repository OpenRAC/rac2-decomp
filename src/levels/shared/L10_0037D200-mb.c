#include "include_asm.h"
#include "common.h"

typedef struct { char pad[0x34]; unsigned short flags; char pad2[0x68 - 0x36]; float **health; char pad3[0x100 - 0x6C]; } Moby;
extern unsigned short *g_group_moby_id_lists[];
extern Moby *g_moby_base_table MACRO_ADDR;

/* Counts how many mobys in the same group are still alive. */
int group_count_alive(u8 *self) {
    unsigned short *list = g_group_moby_id_lists[self[0x21]];
    unsigned short *entry;
    Moby *object;
    float *health;
    int count = 0;
    if (!list) return 0;
    entry = list;
    do {
        object = (Moby *)((*entry & 0x7FFF) * 0x100 + (int)g_moby_base_table);
        if (object->flags & 0x20) {
            health = *object->health;
            if (health && *health > 0.0f) count++;
        }
    } while (*(short *)(entry++) >= 0);
    return count;
}
