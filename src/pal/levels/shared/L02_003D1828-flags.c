#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int D_L02_001A8FF0 __attribute__((sda));
extern char g_camera_l02_position[];
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern int g_current_map_index[] __attribute__((sda));
extern char *D_L02_001B3200 __attribute__((sda));
extern char D_L02_001B3210[] __attribute__((sda));
extern float coll_get_ground_distance_below(void *, void *, void *);
extern void moby_update_ground_check(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern void chickenbot_alert_group(void *);
extern int weapon_select_aim_target(void *, int, float, float, int, int);
extern void cam_compute_view_direction(void *, void *, int);

void func_PAL_L02_003D24B8(char *obj) {
    char *d = *(char **)(obj + 0x68);
    char *entry;
    int hit;
    if (*(unsigned char *)(obj + 0x20) == 0) {
        if (g_current_map_index[0] == 26) {
            if (D_L02_001A8FF0 == 0) return;
            coll_get_ground_distance_below(obj + 0x10, obj, obj + 0x10);
            *(short *)(d + 0x338) = 1;
            *(int *)(obj + 0x9c) = 3;
            *(unsigned short *)(obj + 0x34) |= 0x100;
            *(float *)(d + 0x90) = fast_vec_dist(obj + 0x10, D_L02_001B3210) - 1.5f;
        } else {
            *(int *)(obj + 0x9c) = 12;
            *(float *)(d + 0x90) = *(float *)(obj + 0x18) - 1.0f;
        }
        if (*(int *)(d + 0x210) == -1) {
            moby_mark_spawned(obj);
            return;
        }
        entry = D_L02_001B3200 + *(int *)(d + 0x210) * 0x30;
        if (*(short *)(entry + 0x30)) {
            *(int *)(d + 0x13c) = *(int *)(d + 0x218) = **(int **)(entry + 0x3c);
        } else *(int *)(d + 0x218) = -1;
        *(float *)(d + 0x324) = func_002A7878_range(1.0f, 1.332999945f);
        *(float *)(obj + 0x2c) = *(float *)(*(char **)(obj + 0x24) + 0x24) * *(float *)(d + 0x324);
        *(char *)(d + 0x48) = FloatToInt(15.0f);
        *(char *)(d + 0x4a) = FloatToInt(6.4f);
        *(int *)(d + 0x98) = 3;
        *(float *)(d + 0x80) = 0.2f;
        *(float *)(d + 0x84) = 0.2f;
        *(float *)(d + 0x8c) = 0.4f;
        *(float *)(d + 0x108) = 0.4f;
        *(float *)(d + 0x134) = 0.05f;
        *(char *)(d + 0x60) = 11;
        *(char *)(d + 0x28) = 3;
        *(float *)(d + 0x30) = 0.3330000043f;
        *(float *)(d + 0x104) = *(float *)(d + 0x324) * 0.2f;
        *(float *)(d + 0x100) = *(float *)(d + 0x324) * 0.3f;
        *(float *)(d + 0x10c) = 0.4f;
        *(float *)(d + 0x110) = 1.57079649f;
        *(float *)(d + 0x130) = 0.52359885f;
        *(int *)(d + 0x138) |= 0x280;
        *(float *)(d + 0x1dc) = math_random_signed_float_range(18.0f, 22.0f) * 0.01745329425f;
        *(short *)(d + 0x1e2) = 100;
        *(short *)(d + 0x1e4) = 150;
        *(char *)(d + 0x1e8) = 7;
        *(char *)(d + 0x1e9) = 6;
        *(float *)(d + 0x1d4) = 3.0f;
        *(float *)(d + 0x1d0) = 0.080000006f;
        *(float *)(d + 0x328) = math_random_angle();
        if (*(int *)(d + 0x214)) {
            *(int *)(obj + 0x98) = 0;
            *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xefff;
            moby_set_state(obj, 13, 4);
            if (*(unsigned char *)(obj + 0x43) != 10) func_PAL_002A7E68(obj, 10, 0, 0);
        } else {
            moby_set_state(obj, 1, 0);
            if (*(unsigned char *)(obj + 0x43)) func_PAL_002A7E68(obj, 0, 0, 0);
        }
        qcopy(d + 0x2e0, obj + 0x10);
    }
    if (*(unsigned char *)(obj + 0x31) && fast_vec_dist(obj + 0x10, g_camera_l02_position) < 24.0f) {
        moby_update_ground_check(obj);
        *(char *)(obj + 0x6f) = 22;
    }
    hit = func_PAL_002B1A50(obj, d + 0x50, 0);
    if (hit) {
        chickenbot_alert_group(obj);
        if (hit >= 4) moby_set_state(obj, 12, -1);
    }
    if ((unsigned int)(*(unsigned char *)(obj + 0x95) - 3) >= 2)
        *(short *)(d + 0x314) = weapon_select_aim_target(obj, *(int *)(d + 0x210), 16.0f, 0.0f, 0, 0);
    if (*(short *)(d + 0x338)) cam_compute_view_direction(obj + 0x10, d + 0x300, 0);
}

extern int FastDecTimer(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void func_PAL_002B14F8(void *, void *, int, float, int);

/* Clears the two angle words at +0x310 and +0x312 and counts up the +0x96 word, then runs the
   two placement helpers on the sub-object at +0x260. */
void func_PAL_L02_003D28F0(char *a0) {
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
    func_PAL_002B14F8(a0, q, 0, 1.79999995231628417968750f, 1);
}
