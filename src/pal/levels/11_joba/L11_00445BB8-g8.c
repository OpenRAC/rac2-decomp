#include "include_asm.h"
#include "names.h"
typedef int s32;
typedef unsigned char u8;
typedef short s16;
typedef float f32;
extern s32 g_arena_intro_script_handle_a __attribute__((sda));
extern s32 g_arena_intro_script_handle_b __attribute__((sda));
extern s32 g_arena_intro_script_handle_c __attribute__((sda));
extern s32 g_arena_intro_script_handle_d __attribute__((sda));
extern u8 g_hero_l11_position[];
extern u8 *g_moby_l11_table[3] __attribute__((sda));
extern u8 *g_group_id_lists[];
extern s32 g_tribe_group_limit __attribute__((sda));
extern u8 *D_L11_001B359C_abs[3] __attribute__((sda));
extern s32 arena_is_entity_far_in_direction(u8 *);
extern s32 moby_has_free_child_slot_state2(u8 *);
extern f32 g_arena_fighter_param_min __attribute__((sda));
extern f32 g_arena_fighter_param_max __attribute__((sda));
extern f32 g_arena_fighter_turn_step __attribute__((sda));
extern f32 g_arena_fighter_velocity_scale __attribute__((sda));
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
extern f32 g_arena_spawn_time_scale __attribute__((sda));
extern f32 g_arena_spawn_angle_scale __attribute__((sda));
extern s32 moby_is_state_six(u8 *);
extern s32 moby_is_state_one_cleared_vars(u8 *);
extern s32 math_random_int_below(s32);

/* Turns the script's angle around the actor, hands the result to the level's helpers
   and counts the class the script's identifier names. */
s32 arena_place_and_start_fighter_pal(u8 *object, u8 *fighter) {
    u8 *state = *(u8 **)(object + 0x68);
    f32 step = g_arena_fighter_turn_step;
    f32 value;

    value = FastAddRotations(*(f32 *)(state + 0x19C), step);
    *(f32 *)(state + 0x19C) = value;
    value = math_fast_sin_or_cos_a(value);
    *(f32 *)(fighter + 0x10) = g_arena_fighter_velocity_scale * value;
    value = math_fast_sin_or_cos_b(*(f32 *)(state + 0x19C));
    *(f32 *)(fighter + 0x14) = g_arena_fighter_velocity_scale * value;
    FastVecAdd(fighter + 0x10, fighter + 0x10, arena_get_center_point(object));
    *(f32 *)(fighter + 0x18) = math_random_float_range(g_arena_fighter_param_min, g_arena_fighter_param_max);
    *(f32 *)(fighter + 0xF4) = -1.570796489715576171875f;
    *(s32 *)(fighter + 0xF0) = 0;
    *(f32 *)(fighter + 0xF8) = *(f32 *)(state + 0x19C);
    euler_rotation_basis(fighter + 0xC0, fighter + 0xF0);
    switch (*(s16 *)(fighter + 0xAA)) {
    case 0xD98:
        security_robot_init(fighter, 0, 1);
        *(s32 *)(state + 0x100) += 1;
        break;
    case 0xDCF:
        smasher_robot_init(fighter, 0, 1);
        *(s32 *)(state + 0x104) += 1;
        break;
    case 0xDF4:
        flamethrower_robot_init(fighter, 0, 1);
        *(s32 *)(state + 0x108) += 1;
        break;
    case 0xDF7:
        drone_init_state(fighter, 0, 1);
        *(s32 *)(state + 0x10C) += 1;
        break;
    case 0xD37:
        enemy_init_state(fighter, 0, 1);
        *(s32 *)(state + 0x114) += 1;
        break;
    }
    return 1;
}
