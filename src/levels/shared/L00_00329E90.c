#include "common.h"

/* The two slots the level's resident records live in, and the counter that
   says which of them is the current one. */
typedef struct Slot_00329E90 {
    void (*callback)(struct Slot_00329E90 *);
    int id;
    char pad[0xA430 - 8];
} Slot_00329E90;

extern Slot_00329E90 g_level_slot_table[];
extern int g_double_buffer_index[] __attribute__((sda));

/* Finds or frees one of the two slots for this entity and returns its number; tells the caller if the slot was already its own. */
int AcquireEntitySlot(char *entity, void (*callback)(Slot_00329E90 *), int *out) {
    int tries, g, id, last;
    Slot_00329E90 *rec;

    for (tries = 0; tries < 2; tries++) {
        g = g_double_buffer_index[0];
        id = g_level_slot_table[g].id;
        if (id == -1 || id == *(short *)(entity + 0xAA)) {
            *out = id != -1;
            g_level_slot_table[g].id = *(short *)(entity + 0xAA);
            g_level_slot_table[g].callback = callback;
            g_double_buffer_index[0] = (g_double_buffer_index[0] + 1) % 2;
            return g;
        }
        g_double_buffer_index[0] = (g + 1) % 2;
    }
    rec = &g_level_slot_table[g_double_buffer_index[0]];
    if (rec->callback != 0)
        rec->callback(rec);
    last = g_double_buffer_index[0];
    *out = 0;
    g_level_slot_table[last].id = *(short *)(entity + 0xAA);
    g_level_slot_table[last].callback = callback;
    g_double_buffer_index[0] = (g_double_buffer_index[0] + 1) % 2;
    return last;
}
