#include "include_asm.h"

#include "common.h"
extern s32 math_random_int_below(s32 arg0);
extern s32 arena_get_fighter_count(s32 arg0);
extern s32 g_joba_max_fighter_count __attribute__((sda));
extern s32 g_joba_attack_random_range __attribute__((sda));
extern f32 g_l11_unused_float;
extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);
extern f32 moby_update_aim_target_strength(u8 *arg0, u8 *arg1);
extern s32 part_spawn_damage_debris(u8 *arg0, u8 *arg1, u8 *arg2);
extern s32 weapon_select_aim_target(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);
extern f32 g_joba_damage_threshold __attribute__((sda));
extern s32 g_enemy_damage_accum[];
extern void matrix_mul_vec3(void *out, void *in, void *matrix);
extern void FastVecAdd(void *out, void *in, void *matrix);
extern f32 mat_fast_helper_a(f32 a0, f32 a1);
extern void euler_rotation_basis(void *a0, void *a1);
extern s32 FloatToInt(f32 a0);
extern void enemy_init_state_pal(u8 *a0, s32 a1, s32 a2);
extern void security_robot_init_pal(u8 *a0, s32 a1, s32 a2);
extern void smasher_robot_init_pal(u8 *a0, s32 a1, s32 a2);
extern void flamethrower_robot_init_pal(u8 *a0, s32 a1, s32 a2);
extern void drone_init_state_pal(u8 *a0, s32 a1, s32 a2);
extern void path_mover_reset_pal(u8 *a0, s32 a1);
extern u32 g_joba_child_offset_step __attribute__((sda));
extern u8 g_hero_state[];

/* Places the measured point on the state's three vertices, then walks them: each one gets
   its angle to the shared origin and the class call its identifier names. */
void joba_place_child_mobys_pal(u8 *moby) {
    u8 *parent = moby;
    u8 *vars = *(u8 **)(parent + 0x68);
    u8 *child;
    u8 *hero;
    f32 spawn_point[4];
    s32 delay;
    s32 i;

    spawn_point[0] = 0.0f;
    spawn_point[1] = -9.0f;
    spawn_point[2] = -3.0f;
    spawn_point[3] = 0.0f;
    matrix_mul_vec3(spawn_point, spawn_point, parent + 0xC0);
    FastVecAdd(spawn_point, spawn_point, parent + 0x10);

    if (*(u8 **)(vars + 0x10) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x10) = spawn_point[0] - 2.0f;
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x14) = spawn_point[1];
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x18) = spawn_point[2];
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x1C) = spawn_point[3];
    }
    if (*(u8 **)(vars + 0x14) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x10) = spawn_point[0];
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x14) = spawn_point[1] + 1.0f;
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x18) = spawn_point[2];
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x1C) = spawn_point[3];
    }
    if (*(u8 **)(vars + 0x18) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x10) = spawn_point[0];
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x14) = spawn_point[1] - 1.0f;
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x18) = spawn_point[2];
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x1C) = spawn_point[3];
    }

    hero = g_hero_state;
    child = *(u8 **)(vars + 0x10);
    delay = 0;
    for (i = 0; i < 3; i++) {
        if (i == 1) {
            child = *(u8 **)(vars + 0x14);
        }
        if (i == 2) {
            child = *(u8 **)(vars + 0x18);
        }
        if (child == 0) {
            continue;
        }
        *(s32 *)(child + 0xF0) = 0;
        *(f32 *)(child + 0xF4) = 0.0f;
        *(f32 *)(child + 0xF8) = mat_fast_helper_a(*(f32 *)(hero + 0x80) - *(f32 *)(child + 0x10),
                                          *(f32 *)(hero + 0x84) - *(f32 *)(child + 0x14));
        *(s32 *)(child + 0xFC) = 0;
        euler_rotation_basis(child + 0xC0, child + 0xF0);
        switch (*(s16 *)(child + 0xAA)) {
        case 0xD98:
            security_robot_init_pal(child, delay, 0);
            break;
        case 0xDCF:
            smasher_robot_init_pal(child, delay, 0);
            break;
        case 0xDF4:
            flamethrower_robot_init_pal(child, delay, 0);
            break;
        case 0xDF7:
            *(f32 *)(child + 0x18) += 0.5f;
            drone_init_state_pal(child, FloatToInt((f32)delay * 0.16666667f), 0);
            break;
        case 0xDF9:
            path_mover_reset_pal(child, delay);
            break;
        case 0xD37:
            enemy_init_state_pal(child, delay, 0);
            break;
        }
        delay += ((s32)(g_joba_child_offset_step) * 5 + 2) / 6;
    }

    *(u8 **)(vars + 0x10) = 0;
    *(u8 **)(vars + 0x14) = 0;
    *(u8 **)(vars + 0x18) = 0;
}
