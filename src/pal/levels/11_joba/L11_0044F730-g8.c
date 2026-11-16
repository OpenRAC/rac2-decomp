#include "include_asm.h"

#include "common.h"
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern s32 FloatToInt(float);
extern float fast_vec_dist(char *, void *);
extern void moby_update_ground_check(char *);
extern float FastAddRotations(float, float);
extern void enemy_spawn_child_parts(char *, char *, s32, s32);
extern void enemy_attach_turn_child_parts_pal(char *, char *, s32, void *, float);
extern void group_sync_counter(char *, char *);
extern char *part_find_owned_effect_slot(char *, s32, s32);
extern s32 moby_apply_damage_to_object_pal(char *, char *, s32);
extern void matrix_from_basis_rows(char *, char *);
extern void cam_compute_view_direction(char *, char *, s32);
extern s32 arena_is_point_in_inner_zone(s32, char *);
extern void moby_set_state(char *, s32, s32);
extern char g_hero_l11_position[];
extern char g_identity_l11_matrix[] __attribute__((sda));
extern s32 g_enemy_ai_frozen;
extern void smasher_robot_deactivate_pal(char *);
extern void smasher_robot_update_pairing(char *);

/* Initializes the object and its child rig, then updates aim, damage and activation. */
void smasher_robot_update_aim_and_init_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit, *other;
    float speed, angle;
    if (*(u8 *)(object + 0x20) == 0) {
        *(char **)(state + 0x18) = state + 0x100;
        speed = math_random_float_range(15.0f, 40.0f) * 0.01745329424738884f;
        if (math_random_int_below(2)) speed = -speed;
        *(float *)(state + 0x494) = speed;
        if (math_random_int_below(2) == 1) *(u16 *)(object + 0x34) |= 0x8000;
        *(u8 *)(state + 0x48) = FloatToInt(15.0f);
        *(u8 *)(state + 0x4A) = FloatToInt(12.0f);
        *(float *)(state + 0x80) = 0.8f;
        *(float *)(state + 0x8C) = 0.4f;
        *(s8 *)(state + 0xBC) = -1;
        *(s8 *)(state + 0xBD) = -1;
        *(s8 *)(state + 0xBE) = -1;
        *(s8 *)(state + 0xBF) = -1;
        *(s8 *)(state + 0xC2) = -1;
        *(float *)(state + 0x108) = 0.4f;
        *(float *)(state + 0x4AC) = 8.0f;
        *(u8 *)(state + 0x60) = 10;
        *(int *)(state + 0x98) = 5;
        *(float *)(state + 0x84) = 0.8f;
        *(s8 *)(state + 0xC3) = -1;
        *(float *)(state + 0x100) = 0.6f;
        *(float *)(state + 0x104) = 0.2f;
        *(float *)(state + 0x10C) = 0.4f;
        *(float *)(state + 0x110) = 1.5707964897155762f;
        *(float *)(state + 0x130) = 0.523598849773407f;
        *(float *)(state + 0x12C) = 0.008f;
        *(u8 *)(state + 0x28) = 3;
        *(int *)(state + 0x49C) = 0;
        enemy_spawn_child_parts(object, state + 0x4A0, 0, 1);
        *(short *)(state + 0x4CA) = 0;
        smasher_robot_deactivate_pal(object);
    }
    if (*(short *)(state + 0x4D2) == 0 && *(u8 *)(object + 0x20) != 11 && !g_enemy_ai_frozen) {
        *(u16 *)(object + 0x34) |= 0x400;
        if (*(u8 *)(object + 0x31) && fast_vec_dist(object + 0x10, g_hero_l11_position) < 24.0f) {
            moby_update_ground_check(object);
            *(u8 *)(object + 0x6F) = 22;
        }
    } else *(u16 *)(object + 0x34) &= 0xFBFF;
    angle = FastAddRotations(*(float *)(state + 0x49C), *(float *)(state + 0x4AC) * 0.01745329424738884f);
    *(float *)(state + 0x49C) = angle;
    enemy_attach_turn_child_parts_pal(object, state + 0x4A0, 1, g_identity_l11_matrix, angle);
    group_sync_counter(object, state + 0x4BC);
    if (*(u8 *)(object + 0x20) >= 3) {
        hit = part_find_owned_effect_slot(object, 0x10000, 1);
        if (hit && (other = *(char **)(hit + 0x20)) && !*(u8 *)(object + 0x31)) {
            if (*(short *)(other + 0xAA) == 0xA03 || *(short *)(other + 0xAA) == 0xB89)
                *(int *)(hit + 0x2C) = 0;
        }
        if (moby_apply_damage_to_object_pal(object, state + 0x50, 0) == 5) {
            *(int *)(state + 0xE0) = 0;
            *(float *)(state + 0xE4) = 1.0053098f;
        }
        smasher_robot_update_pairing(object);
        if (*(short *)(state + 0x4D2)) {
            matrix_from_basis_rows(state + 0x230, object + 0xC0);
            cam_compute_view_direction(object + 0x10, state + 0x260, 0);
            if (!arena_is_point_in_inner_zone(*(int *)(object + 0xB8), object + 0x10)) {
                *(int *)(state + 0x20) = 0;
                moby_set_state(object, 11, 5);
            }
        }
    }
    if (*(u8 *)(object + 0x20) >= 2 && *(u8 *)(state + 0x2E) == 2)
        smasher_robot_deactivate_pal(object);
}
