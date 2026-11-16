#include "names.h"
/* func_PAL_L26_003E0168, the PAL copy of func_L26_003DBE18: the same C, where the two tuning
   words are read as ints and scaled to 50 Hz before they go to the halfwords at 0x1E2 and 0x1E4. */
#include "common.h"

extern float g_flying_creature_turn_degrees __attribute__((sda));
extern int g_flying_creature_value_a __attribute__((sda));
extern int g_flying_creature_value_b;
extern float g_hero_l26_origin[4];
extern float gravity_get_center_distance(char *);
extern int math_random_int_below(int);
extern void enemy_spawn_child_parts(char *, char **, int, int);
extern void moby_set_state(unsigned char *, unsigned char, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void moby_l26_set_group_alert_flag(void *);
extern int weapon_select_aim_target(void *, int, void *, int, float, float);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(char *, char *, int);
extern void group_destroy_attached_parts(char *, char *);

int flying_creature_update_state_pal(unsigned char *object) {
    char *private = *(char **)(object + 0x68);
    float height;
    float turn;
    if (object[0x20] == 0) {
        *(int *)(private + 0x98) = 3;
        *(float *)(private + 0x80) = 1.0f;
        private[0x60] = 7;
        *(float *)(private + 0x84) = 0.8f;
        *(float *)(private + 0x8C) = 0.15f;
        height = gravity_get_center_distance((char *)object + 0x10) - 1.5f;
        turn = g_flying_creature_turn_degrees;
        *(float *)(private + 0x100) = 1.0f;
        turn *= 0.017453294f;
        *(float *)(private + 0x90) = height;
        *(float *)(private + 0x104) = 0.5f;
        {
            int flip = math_random_int_below(2);
            float angle = turn;
            if (flip) angle = -angle;
            *(float *)(private + 0x1DC) = angle;
        }
        *(unsigned short *)(private + 0x1E2) = ((s32)(g_flying_creature_value_a) * 5 + 2) / 6;
        *(unsigned short *)(private + 0x1E4) = ((s32)(g_flying_creature_value_b) * 5 + 2) / 6;
        private[0x2E] = 1;
        *(unsigned short *)(object + 0x34) |= 0x100;
        if (*(float *)(private + 0x20) == 0.0f) {
            *(short *)(private + 0x24) = 3;
            *(float *)(private + 0x20) = 3.0f;
        }
        enemy_spawn_child_parts((char *)object, (char **)(private + 0x270), 0, 2);
        moby_set_state(object, 1, 0);
        if (object[0x43]) anim_start_blended_pal(object, 0, 0, 0);
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, g_hero_l26_origin) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 0x16;
    }
    if (moby_apply_damage_to_object(object, private + 0x50, 0)) moby_l26_set_group_alert_flag(object);
    *(short *)(private + 0x224) = weapon_select_aim_target(object, *(int *)(private + 0x210), 0, 0, 16.0f, 0.0f);
    matrix_from_basis_rows(private + 0x230, object + 0xC0);
    cam_compute_view_direction((char *)object + 0x10, private + 0x260, 0);
    if ((unsigned char)private[0x2E] == 2) {
        group_destroy_attached_parts((char *)object, private + 0x270);
        return 1;
    }
    return 0;
}
