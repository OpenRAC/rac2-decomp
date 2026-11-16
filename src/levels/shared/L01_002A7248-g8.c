#include "include_asm.h"
#include "names.h"

extern int g_hero_l01_control_mode;
extern char g_hud_overlay_timer __attribute__((sda));
extern int g_hud_overlay_result_code __attribute__((sda));
extern int math_fast_float_d(char *);
extern void level_clear_table_entry(int);

/* Counts down a timer while the level flag is clear, then returns a stored value. */
int level_tick_timer_get_value(void) {
    if (g_hero_l01_control_mode == 0) {
        if (math_fast_float_d(&g_hud_overlay_timer))
            level_clear_table_entry(0);
    }
    return g_hud_overlay_result_code;
}

extern int g_frame_counter_4;
extern int g_level_table_ptr;

/* Looks up a 16-bit value for an entry in a table, or gives -1 when the game is too early to have it. */
int level_get_table_entry_short(int index)
{
    int entryIndex = index;
    int table;

    if (g_frame_counter_4 < 5 || (table = g_level_table_ptr) == 0)
        return -1;
    return *(short *)(table + entryIndex * 0x28 + 0x24);
}

/* func_L01_002F1F70 is defined in L01_002A7248.c (this unit has no $gp access for it). */

typedef unsigned char u8;
typedef signed short s16;
typedef float f32;

extern u8 g_hero_l01_state_block[];

/* The same object as plain D_L01_001A8F40 above: that use stays absolute, this one is the
   $gp form the reach test reads. */
extern int D_L01_001A8F40_gp __asm__("D_L01_001A8F40") __attribute__((sda));

extern f32 func_002E3618(void *a0, void *a1);

/* Reach test against the level's live record: rejects the two "gone" states, an empty
   pair, a closed door, a nonzero key field, the third mode and the $gp flag, then asks
   the helper whether the doubled radius fits, and finally whether the stored count
   covers the caller's index. */
int hero_is_reachable_for_count(u8 *target, int minCount, f32 radius) {
    u8 *hero = g_hero_l01_state_block;
    int limit = minCount;
    f32 radiusCopy = radius;
    int heroState = *(int *)(hero + 0x2294);
    f32 distance;

    if (heroState == 0x1C)
        return 0;
    if (heroState == 0x31)
        return 0;
    if (*(int *)(hero + 0x24CC) == 0)
        return 0;
    if (*(int *)(hero + 0x340) == 0)
        return 0;
    if (*(s16 *)(hero + 0x34E) != 0)
        return 0;
    if (*(int *)(hero + 0x229C) == 3)
        return 0;
    if (D_L01_001A8F40_gp != 0)
        return 0;
    distance = func_002E3618(target + 0x10, hero + 0x80);
    if (radiusCopy + radiusCopy < distance)
        return 0;
    return g_frame_counter_4 >= limit;
}
