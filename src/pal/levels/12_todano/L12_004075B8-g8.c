#include "include_asm.h"

#include "common.h"
extern void math_update_wrapped_angle_offset(u8 *, u8 *, u8 *, float, float, float);
extern void moby_mark_spawned(void *);
extern void func_PAL_L12_004075B8(void *);
extern float vec_distance_xy(void *, void *);
extern void func_PAL_002B1588(int, int);
extern void help_unlock_entry(int);
extern void moby_set_flag_bit(void *, int);
extern void moby_handle_request_slot_state(int);
extern float D_L12_001B12B0 __attribute__((sda));
extern float D_L12_001B12B4 __attribute__((sda));
extern float D_L12_001B12B8 __attribute__((sda));
extern float D_L12_001B12BC __attribute__((sda));
extern float D_L12_001B12C0 __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 D_L12_001B3C1C[] MACRO_ADDR;
extern u8 D_L12_001B3C20[] MACRO_ADDR;
extern u8 D_0019B4A8[];
extern u8 g_hero_position[];
extern u8 *D_L12_001B2E9C MACRO_ADDR;
typedef struct {
    u8 pad[0x464];
    u8 flags[0];
} TodanoObjectFlags;
extern TodanoObjectFlags D_L12_0021EDF0;
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
void func_PAL_L12_00407880(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 index;
    s32 bits;
    TodanoObjectFlags *record;

    if (object[0x20]) return;
    ((TodanoRotation *)object)->rx = D_L12_001B12B8 * 0.0174532942f;
    ((TodanoRotation *)object)->ry = D_L12_001B12BC * 0.0174532942f;
    ((TodanoRotation *)object)->rz = D_L12_001B12C0 * 0.0174532942f;
    math_update_wrapped_angle_offset(object, D_L12_001B3C1C, D_L12_001B3C20, D_L12_001B12B0, D_L12_001B12B4 * 0.0003490659f, 0.0f);
    index = *(u16 *)(object + 0xB2);
    record = &D_L12_0021EDF0;
    if (record->flags[(s16)index]) goto kill;
    bits = (u8)D_0019B4A8[((s16)index >> 1) + (g_current_map_index << 10)];
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
    func_PAL_L12_004075B8(object);
    if (vec_distance_xy(object + 0x10, g_hero_position) < 1.5f) {
        func_PAL_002B1588(0x1246, 0x1A1);
        help_unlock_entry(0x10);
        moby_set_flag_bit(D_L12_001B2E9C + (*(s32 *)state << 8), 1);
        moby_handle_request_slot_state(0x10);
        INCREMENT_OBJECT_COUNTER(object);
        moby_mark_spawned(object);
    }
}
