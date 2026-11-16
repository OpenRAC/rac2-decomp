#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

/* One 0xA430-byte slot of the level table: a key at +4, then two payloads. */
typedef struct {
    int unk0;
    int key;
    u8 head[0x18];
    u8 body[0xA430 - 0x20];
} Slot;

extern Slot g_level_slot_table[];

/* Returns the main data of a slot if the slot belongs to this key, otherwise nothing. */
u8 *level_get_slot_body(int key, int index)
{
    if (g_level_slot_table[index].key != key)
        return 0;
    return g_level_slot_table[index].body;
}

/* Returns the header data of a slot if the slot belongs to this key, otherwise nothing. */
u8 *level_get_slot_header(int key, int index)
{
    if (g_level_slot_table[index].key != key)
        return 0;
    return g_level_slot_table[index].head;
}
