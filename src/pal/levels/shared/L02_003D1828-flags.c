#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern int g_tether_lock_active __attribute__((sda));
extern char g_camera_l02_position[];
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern int g_current_map_index[] __attribute__((sda));
extern char *g_enemy_init_table __attribute__((sda));
extern char g_arena_anchor_pos[] __attribute__((sda));
extern float coll_get_ground_distance_below(void *, void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern void chickenbot_alert_group(void *);
extern int weapon_select_aim_target(void *, int, float, float, int, int);
extern void cam_compute_view_direction(void *, void *, int);

/* Sets up an enemy when it first appears, with its speed, size and turn limits. Then it checks
   hits and plays its starting animation. */
void enemy_init_pal(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    char *entry;
    int hit;
    if (*(unsigned char *)(obj + 0x20) == 0) {
        if (g_current_map_index[0] == 26) {
            if (g_tether_lock_active == 0) return;
            coll_get_ground_distance_below(obj + 0x10, obj, obj + 0x10);
            *(short *)(vars + 0x338) = 1;
            *(int *)(obj + 0x9c) = 3;
            *(unsigned short *)(obj + 0x34) |= 0x100;
            *(float *)(vars + 0x90) = fast_vec_dist(obj + 0x10, g_arena_anchor_pos) - 1.5f;
        } else {
            *(int *)(obj + 0x9c) = 12;
            *(float *)(vars + 0x90) = *(float *)(obj + 0x18) - 1.0f;
        }
        if (*(int *)(vars + 0x210) == -1) {
            moby_mark_spawned(obj);
            return;
        }
        entry = g_enemy_init_table + *(int *)(vars + 0x210) * 0x30;
        if (*(short *)(entry + 0x30)) {
            *(int *)(vars + 0x13c) = *(int *)(vars + 0x218) = **(int **)(entry + 0x3c);
        } else *(int *)(vars + 0x218) = -1;
        *(float *)(vars + 0x324) = func_002A7878_range(1.0f, 1.332999945f);
        *(float *)(obj + 0x2c) = *(float *)(*(char **)(obj + 0x24) + 0x24) * *(float *)(vars + 0x324);
        *(char *)(vars + 0x48) = FloatToInt(15.0f);
        *(char *)(vars + 0x4a) = FloatToInt(6.4f);
        *(int *)(vars + 0x98) = 3;
        *(float *)(vars + 0x80) = 0.2f;
        *(float *)(vars + 0x84) = 0.2f;
        *(float *)(vars + 0x8c) = 0.4f;
        *(float *)(vars + 0x108) = 0.4f;
        *(float *)(vars + 0x134) = 0.05f;
        *(char *)(vars + 0x60) = 11;
        *(char *)(vars + 0x28) = 3;
        *(float *)(vars + 0x30) = 0.3330000043f;
        *(float *)(vars + 0x104) = *(float *)(vars + 0x324) * 0.2f;
        *(float *)(vars + 0x100) = *(float *)(vars + 0x324) * 0.3f;
        *(float *)(vars + 0x10c) = 0.4f;
        *(float *)(vars + 0x110) = 1.57079649f;
        *(float *)(vars + 0x130) = 0.52359885f;
        *(int *)(vars + 0x138) |= 0x280;
        *(float *)(vars + 0x1dc) = math_random_signed_float_range(18.0f, 22.0f) * 0.01745329425f;
        *(short *)(vars + 0x1e2) = 100;
        *(short *)(vars + 0x1e4) = 150;
        *(char *)(vars + 0x1e8) = 7;
        *(char *)(vars + 0x1e9) = 6;
        *(float *)(vars + 0x1d4) = 3.0f;
        *(float *)(vars + 0x1d0) = 0.080000006f;
        *(float *)(vars + 0x328) = math_random_angle();
        if (*(int *)(vars + 0x214)) {
            *(int *)(obj + 0x98) = 0;
            *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xefff;
            moby_set_state(obj, 13, 4);
            if (*(unsigned char *)(obj + 0x43) != 10) anim_start_blended_pal(obj, 10, 0, 0);
        } else {
            moby_set_state(obj, 1, 0);
            if (*(unsigned char *)(obj + 0x43)) anim_start_blended_pal(obj, 0, 0, 0);
        }
        qcopy(vars + 0x2e0, obj + 0x10);
    }
    if (*(unsigned char *)(obj + 0x31) && fast_vec_dist(obj + 0x10, g_camera_l02_position) < 24.0f) {
        moby_update_ground_check(obj);
        *(char *)(obj + 0x6f) = 22;
    }
    hit = moby_apply_damage_to_object_pal(obj, vars + 0x50, 0);
    if (hit) {
        chickenbot_alert_group(obj);
        if (hit >= 4) moby_set_state(obj, 12, -1);
    }
    if ((unsigned int)(*(unsigned char *)(obj + 0x95) - 3) >= 2)
        *(short *)(vars + 0x314) = weapon_select_aim_target(obj, *(int *)(vars + 0x210), 16.0f, 0.0f, 0, 0);
    if (*(short *)(vars + 0x338)) cam_compute_view_direction(obj + 0x10, vars + 0x300, 0);
}

extern int FastDecTimer(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void value_set_and_smooth_pal(void *, void *, int, float, int);

/* Clears the two angle words at +0x310 and +0x312 and counts up the +0x96 word, then runs the
   two placement helpers on the sub-object at +0x260. */
void moby_reset_turn_place_pal(char *a0) {
    char *p = *(char **)(a0 + 0x68);
    char *q;
    unsigned short n;

    FastDecTimer(p + 0x310);
    FastDecTimer(p + 0x312);
    n = *(unsigned short *)(a0 + 0x96);
    if (n <= 0xFFFE)
        *(unsigned short *)(a0 + 0x96) = n + 1;
    q = p + 0x260;
    moby_update_eased_node(a0, q, 0, 0.0432f, 0.43200004f);
    value_set_and_smooth_pal(a0, q, 0, 1.79999995231628417968750f, 1);
}
