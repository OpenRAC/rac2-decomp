#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
extern u8 *cam_alloc_override_slot_pal(s32 a0);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern f32 FastAddRotations(f32 a, f32 b);
extern f32 fast_subtract_rotations(f32 a, f32 b);
extern f32 math_approach_target_with_direction_mode(void *a0, void *a1, f32 a3, f32 a4, f32 a5, f32 a6, void *a2);
extern f32 g_endako_boss_view_angle_x __attribute__((sda));
extern f32 g_endako_boss_view_angle_y __attribute__((sda));
typedef struct { u8 pad[0x80]; f32 x, y; } Hero;
extern Hero g_hero_state;
extern u8 *g_endako_boss_state_ptr __attribute__((nosda));

void endako_boss_ease_view_angle_pal(u8 *entity) {
    u8 *state;
    u8 *obj;
    u8 *s0;
    f32 f0;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 f15;
    f32 first;
    f32 local;

    state = *(u8 **)(entity + 0x68);
    if (entity[0x95] < 2)
        return;
    if (*(u8 **)(state + 0x2C8) == 0)
        *(u8 **)(state + 0x2C8) = cam_alloc_override_slot_pal(5);
    obj = *(u8 **)(state + 0x2C8);
    { f32 x = g_endako_boss_view_angle_x; f32 y = g_endako_boss_view_angle_y;
    *(f32 *)obj = x;
    *(f32 *)(*(u8 **)(state + 0x2C8) + 4) = y; }

    f12 = *(f32 *)(entity + 0x10) - g_hero_state.x;
    f13 = *(f32 *)(entity + 0x14) - g_hero_state.y;
    s0 = *(u8 **)(g_endako_boss_state_ptr + 0x70);
    first = mat_fast_helper_a(f12, f13);
    /* The base moves on between the two reads: combine cannot then fold the
     * second read's address, so retail's addiu and based load remain. */
    { f32 *rot = (f32 *)(s0 + 0x160);
    f12 = rot[0];
    s0 += 0x1C0;
    f13 = rot[1]; }
    f0 = mat_fast_helper_a(f12, f13);

    f13 = 3.14159274f;
    f0 = FastAddRotations(f0, f13);
    f0 = fast_subtract_rotations(first, f0);

    f13 = 0.005026549f;
    f14 = f13;
    f15 = 0.25132746f;
    local = f0;
    f12 = 0.0f;
    math_approach_target_with_direction_mode(&local, state + 0xCC, f12, f13, f14, f15, 0);

    *(f32 *)(s0 + 0x1C) = 1.0f;
    *(f32 *)(s0 + 0x14) = -*(f32 *)(state + 0xCC);
}
