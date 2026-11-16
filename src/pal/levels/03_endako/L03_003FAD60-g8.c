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

/* Eases the camera view angle toward the angle between the boss and the hero, then sets the
   camera override's tilt from it. */
void endako_boss_ease_view_angle_pal(u8 *entity) {
    u8 *state;
    u8 *obj;
    u8 *parts;
    f32 angle;
    f32 arg_a;
    f32 arg_b;
    f32 arg_c;
    f32 arg_d;
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

    arg_a = *(f32 *)(entity + 0x10) - g_hero_state.x;
    arg_b = *(f32 *)(entity + 0x14) - g_hero_state.y;
    parts = *(u8 **)(g_endako_boss_state_ptr + 0x70);
    first = mat_fast_helper_a(arg_a, arg_b);
    /* The base moves on between the two reads: combine cannot then fold the
     * second read's address, so retail's addiu and based load remain. */
    { f32 *rot = (f32 *)(parts + 0x160);
    arg_a = rot[0];
    parts += 0x1C0;
    arg_b = rot[1]; }
    angle = mat_fast_helper_a(arg_a, arg_b);

    arg_b = 3.14159274f;
    angle = FastAddRotations(angle, arg_b);
    angle = fast_subtract_rotations(first, angle);

    arg_b = 0.005026549f;
    arg_c = arg_b;
    arg_d = 0.25132746f;
    local = angle;
    arg_a = 0.0f;
    math_approach_target_with_direction_mode(&local, state + 0xCC, arg_a, arg_b, arg_c, arg_d, 0);

    *(f32 *)(parts + 0x1C) = 1.0f;
    *(f32 *)(parts + 0x14) = -*(f32 *)(state + 0xCC);
}
