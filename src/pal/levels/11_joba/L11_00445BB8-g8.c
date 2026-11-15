#include "include_asm.h"
#include "names.h"
typedef int s32;
typedef unsigned char u8;
typedef short s16;
typedef float f32;
extern s32 D_L11_001B1530 __attribute__((sda));
extern s32 D_L11_001B1540 __attribute__((sda));
extern s32 D_L11_001B1550 __attribute__((sda));
extern s32 D_L11_001B1560 __attribute__((sda));
extern u8 D_L11_001BA8C0[];
extern u8 *g_moby_l11_table[3] __attribute__((sda));
extern u8 *g_group_id_lists[];
extern s32 D_L11_001B35B8 __attribute__((sda));
extern u8 *D_L11_001B359C_abs[3] __attribute__((sda));
extern s32 arena_is_entity_far_in_direction(u8 *);
extern s32 moby_has_free_child_slot_state2(u8 *);
extern f32 D_L11_001B15AC __attribute__((sda));
extern f32 D_L11_001B15B0 __attribute__((sda));
extern f32 D_L11_001B15B4 __attribute__((sda));
extern f32 D_L11_001B15B8 __attribute__((sda));
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_random_float_range(float, float);
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern void euler_rotation_basis(u8 *, u8 *);
extern u8 *arena_get_center_point(u8 *);
extern void enemy_init_state(char *, int, int);
extern void security_robot_init(char *, int, int);
extern void smasher_robot_init(char *, int, int);
extern void flamethrower_robot_init(char *, int, int);
extern void drone_init_state(char *, int, int);
extern s32 D_L11_001B35B8_1[] __attribute__((sda));
extern f32 D_L11_001B1614 __attribute__((sda));
extern f32 D_L11_001B1618 __attribute__((sda));
extern s32 moby_is_state_six(u8 *);
extern s32 moby_is_state_one_cleared_vars(u8 *);
extern s32 math_random_int_below(s32);

/* Turns the script's angle around the actor, hands the result to the level's helpers
   and counts the class the script's identifier names. */
s32 func_PAL_L11_004461C8(u8 *object, u8 *arg) {
    u8 *state = *(u8 **)(object + 0x68);
    f32 step = D_L11_001B15B4;
    f32 v;

    v = FastAddRotations(*(f32 *)(state + 0x19C), step);
    *(f32 *)(state + 0x19C) = v;
    v = math_fast_sin_or_cos_a(v);
    *(f32 *)(arg + 0x10) = D_L11_001B15B8 * v;
    v = math_fast_sin_or_cos_b(*(f32 *)(state + 0x19C));
    *(f32 *)(arg + 0x14) = D_L11_001B15B8 * v;
    FastVecAdd(arg + 0x10, arg + 0x10, arena_get_center_point(object));
    *(f32 *)(arg + 0x18) = math_random_float_range(D_L11_001B15AC, D_L11_001B15B0);
    *(f32 *)(arg + 0xF4) = -1.570796489715576171875f;
    *(s32 *)(arg + 0xF0) = 0;
    *(f32 *)(arg + 0xF8) = *(f32 *)(state + 0x19C);
    euler_rotation_basis(arg + 0xC0, arg + 0xF0);
    switch (*(s16 *)(arg + 0xAA)) {
    case 0xD98:
        security_robot_init(arg, 0, 1);
        *(s32 *)(state + 0x100) += 1;
        break;
    case 0xDCF:
        smasher_robot_init(arg, 0, 1);
        *(s32 *)(state + 0x104) += 1;
        break;
    case 0xDF4:
        flamethrower_robot_init(arg, 0, 1);
        *(s32 *)(state + 0x108) += 1;
        break;
    case 0xDF7:
        drone_init_state(arg, 0, 1);
        *(s32 *)(state + 0x10C) += 1;
        break;
    case 0xD37:
        enemy_init_state(arg, 0, 1);
        *(s32 *)(state + 0x114) += 1;
        break;
    }
    return 1;
}
