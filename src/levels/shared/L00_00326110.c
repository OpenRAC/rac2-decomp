#include "common.h"

extern u8 g_hero_position[];
extern u32 g_current_map_index MACRO_ADDR;
extern s32 g_bolt_amount_by_level[];
extern f32 fast_vec_dist(u8 *, u8 *);
extern void part_spawn_bolt_pickups(u8 *, s32, s32, s32, s32, s32, f32);

/* Spawns bolts from an object; the amount grows with the level, and the bolts are picked up automatically when the player is close. */
void part_spawn_scaled_bolts(u8 *object, s32 multiplier, f32 height) {
    s32 mode = 1;
    u32 level;
    s32 amount;

    if (fast_vec_dist(object + 0x10, g_hero_position) < 7.0f)
        mode = 3;
    level = g_current_map_index;
    if (level > 25)
        level = 25;
    amount = g_bolt_amount_by_level[level] * multiplier - 1;
    part_spawn_bolt_pickups(object, amount, amount, mode, -1, 0, height);
}
