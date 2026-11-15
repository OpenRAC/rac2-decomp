#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef float f32;

extern u8 *g_moby_l11_table __attribute__((sda));
extern u8 *g_group_id_lists[];
extern u8 g_hero_state[] __attribute__((nosda));

/* Walks the state's class list: the count and the sum of the records of the eight
   known classes go to the state's 0x140 and 0x144 words, the level's default to 0x148. */
/* Counts the arena fighters of the known kinds and adds up their health at the start of a wave. */
void arena_count_fighters(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 index = *(s32 *)(state + 0xC0);
    u16 *cursor;
    u8 *base;
    u8 *list;

    *(s32 *)(state + 0x140) = 0;
    *(f32 *)(state + 0x144) = 0.0f;
    if (index == 0xFF) {
        return;
    }
    list = g_group_id_lists[index];
    if (list == 0) {
        return;
    }
    cursor = (u16 *)list;
    base = g_moby_l11_table;
    do {
        u16 value = *cursor;
        u8 *record = base + ((value & 0x7FFF) << 8);

        if (record != 0 && record[0x20] != 0xFE && record[0x20] != 0xFD && record[0x20] != 1) {
            s16 id = *(s16 *)(record + 0xAA);

            if (id == 0xD98 /* Joba security robot */ || id == 0xDCF /* Joba smasher robot */ || id == 0xDF4 /* moby class 3572 */ || id == 0xDF7 /* moby class 3575 */ ||
                id == 0xDF9 /* Joba fighter */ || id == 0xD37 /* moby class 3383 */ || id == 0xD4A /* moby class 3402 */ || id == MOBY_CLASS_ARACHNOID) {
                *(s32 *)(state + 0x140) += 1;
                *(f32 *)(state + 0x144) += *(f32 *)(*(u32 *)(record + 0x68) + 0x20);
            }
        }
    } while (*(s16 *)cursor++ >= 0);
    list = g_hero_state;
    *(f32 *)(state + 0x148) = (f32)*(s32 *)(list + 0x24CC);
}

extern s32 arena_place_and_start_fighter(u8 *obj, u8 *record);
extern s32 arena_add_fighter_to_squad(u8 *obj, u8 *record);

/* Finds the class record the identifier names: the first live record of the state's
   class list whose identifier matches, and hands it to the class's handler. */
/* Wakes up the first sleeping fighter of the asked kind and sends it into the arena. */
s32 arena_activate_fighter_of_class(u8 *obj, s32 id, s32 flag) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 index = *(s32 *)(state + 0xC0);
    u16 *cursor;
    u8 *record;
    u8 *base;
    u8 *list;

    if (index == 0xFF) {
        return 0;
    }
    list = g_group_id_lists[index];
    if (list == 0) {
        return 0;
    }
    cursor = (u16 *)list;
    base = g_moby_l11_table;
    do {
        record = base + ((*cursor & 0x7FFF) << 8);

        if (record != 0 && record[0x20] != 0xFE && record[0x20] != 0xFD &&
            *(s16 *)(record + 0xAA) == id && record[0x20] == 1) {
            *(u32 *)(record + 0xB8) = (u32)obj;
            if (flag != 0) {
                return arena_place_and_start_fighter(obj, record);
            }
            return arena_add_fighter_to_squad(obj, record);
        }
    } while (*(s16 *)cursor++ >= 0);
    return 0;
}
