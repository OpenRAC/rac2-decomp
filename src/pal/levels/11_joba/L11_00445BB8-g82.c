#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
extern u8 *g_moby_l11_table __attribute__((sda));
extern u8 *g_group_id_lists[];
extern u8 g_hero_state[] __attribute__((nosda));
extern s32 arena_place_and_start_fighter_pal(u8 *obj, u8 *record);
extern s32 arena_add_fighter_to_squad(u8 *obj, u8 *record);

/* Finds the class record the identifier names: the first live record of the state's
   class list whose identifier matches, and hands it to the class's handler. */
s32 arena_activate_fighter_of_class_pal(u8 *obj, s32 id, s32 flag) {
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
                return arena_place_and_start_fighter_pal(obj, record);
            }
            return arena_add_fighter_to_squad(obj, record);
        }
    } while (*(s16 *)cursor++ >= 0);
    return 0;
}
