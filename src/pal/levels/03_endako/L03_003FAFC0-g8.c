#include "include_asm.h"

#include "common.h"
extern s32 g_frame_l03_counter;
extern u8 *g_moby_record_base;
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_item_slot_to_record[];
extern s32 g_item_ammo_counts[];
extern struct { u8 pad[0xE0]; } g_item_l03_record_table[];
extern s16 *g_wake_object_lists[];
extern u8 g_hero_position[];
extern s32 moby_is_state_six(u8 *obj);
extern void nanotech_crate_init(u8 *obj);
extern f32 fast_vec_dist(u8 *a, u8 *b);
extern int moby_fuse_linked_objects(u8 *obj, u8 *pos, u8 *vel, s32 a3, s32 t0);

/* Every 64th tick: when one of the 56 tracked entries is below a tenth of its limit, wakes the
   objects listed for the state that are in range. */
void endako_wake_objects_low_counters_pal(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    s32 low = 0;
    u8 *obj;
    u8 *pos;
    s16 *list;
    s32 i;

    if ((g_frame_l03_counter & 0x3F) == 0) {
        for (i = 0; i < 0x38; i++) {
            if (g_item_owned_flags[i] != 0) {
                u8 *record = (u8 *)&g_item_l03_record_table[g_item_slot_to_record[i]];
                s16 limit = *(s16 *)(record + 0x40);
                if (limit != 0 && (f32)g_item_ammo_counts[i] < (f32)limit * 0.1f) {
                    low = 1;
                }
            }
        }
    }
    if (low != 0) {
        list = g_wake_object_lists[*(s32 *)(state + 0xAC)];
        if (list != 0) {
            do {
                obj = g_moby_record_base + (((u16)*list & 0x7FFF) << 8);
                if (moby_is_state_six(obj) != 0 && *(s32 *)(*(u8 **)(obj + 0x68) + 0x100) >= 0x33) {
                    pos = obj + 0x10;
                    if (fast_vec_dist(g_hero_position, pos) > 3.0f) {
                        nanotech_crate_init(obj);
                        moby_fuse_linked_objects(obj, pos, obj + 0xF0, 0, 0);
                    }
                }
            } while (*list++ >= 0);
        }
    }
}
