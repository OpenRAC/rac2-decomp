#include "include_asm.h"

#include "common.h"
extern void math_update_wrapped_angle_offset(u8 *, u8 *, u8 *, float, float, float);
extern void moby_mark_spawned(void *);
extern void gfx_draw_sparkle_trail_to_hero(void *);
extern float vec_distance_xy(void *, void *);
extern void value_set_entry_by_index_us2(int, int);
extern void help_unlock_entry(int);
extern void moby_set_flag_bit(void *, int);
extern int moby_handle_request_slot_state(int);
extern float g_collectible_angle_offset __attribute__((sda));
extern float g_collectible_spin_speed __attribute__((sda));
extern float g_collectible_tilt_x __attribute__((sda));
extern float g_collectible_tilt_y __attribute__((sda));
extern float g_todano_spin_degrees __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_collectible_angle_state_a[] MACRO_ADDR;
extern u8 g_collectible_angle_state_b[] MACRO_ADDR;
extern u8 g_moby_nibble_table[];
extern u8 g_hero_position[];
extern u8 *g_moby_list_start MACRO_ADDR;
typedef struct {
    u8 pad[0x464];
    u8 flags[0];
} TodanoObjectFlags;
extern TodanoObjectFlags g_object_flags;
#define OBJECT_COUNTERS(o) \
    ((u8 *)D_0019B4A8)[((s16)*(u16 *)((o) + 0xB2) >> 1) + (D_001A79F0 << 10)]
#define INCREMENT_OBJECT_COUNTER(o) { \
    if (*(u16 *)((o) + 0xB2) & 1) { \
        if (((OBJECT_COUNTERS(o) >> 4) & 7) != 7) OBJECT_COUNTERS(o) += 16; \
    } else { \
        if ((OBJECT_COUNTERS(o) & 7) != 7) OBJECT_COUNTERS(o)++; \
    } \
}
typedef struct {
    u8 pad[0xF0];
    f32 rx, ry, rz;
} TodanoRotation;

/* Sets the object's rotation and bob from the level's tuning floats. An object whose packed
   counter is already set is removed; otherwise, once within 1.5 units of the target position,
   it plays its sound, bumps the counter and is removed. */
void collectible_update_todano_us2(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 index;
    s32 bits;
    TodanoObjectFlags *record;

    if (object[0x20]) return;
    ((TodanoRotation *)object)->rx = g_collectible_tilt_x * 0.0174532942f;
    ((TodanoRotation *)object)->ry = g_collectible_tilt_y * 0.0174532942f;
    ((TodanoRotation *)object)->rz = g_todano_spin_degrees * 0.0174532942f;
    math_update_wrapped_angle_offset(object, g_collectible_angle_state_a, g_collectible_angle_state_b, g_collectible_angle_offset, g_collectible_spin_speed * 0.00029088825f, 0.0f);
    index = *(u16 *)(object + 0xB2);
    record = &g_object_flags;
    if (record->flags[(s16)index]) goto kill;
    bits = (u8)g_moby_nibble_table[((s16)index >> 1) + (g_current_map_index << 10)];
    if (index & 1) {
        if ((bits >> 4) & 7) goto kill;
    } else if (bits & 7) {
        goto kill;
    }
    goto update;

kill:
    moby_mark_spawned(object);
    return;

update:
    gfx_draw_sparkle_trail_to_hero(object);
    if (vec_distance_xy(object + 0x10, g_hero_position) < 1.5f) {
        value_set_entry_by_index_us2(0x1246, 0x1F4);
        help_unlock_entry(0x10);
        moby_set_flag_bit(g_moby_list_start + (*(s32 *)state << 8), 1);
        moby_handle_request_slot_state(0x10);
        INCREMENT_OBJECT_COUNTER(object);
        moby_mark_spawned(object);
    }
}
