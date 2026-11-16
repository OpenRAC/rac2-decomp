#include "include_asm.h"

#include "common.h"
extern int math_random_int_below(int);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int armed_enemy_has_partner_in_group(char *);
extern u8 *g_moby_l02_pool[] __attribute__((sda));
extern int math_random_int_below(int);
extern float vec_distance_xy(char *, char *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int math_random_int_below(int);

/* Picks the idle variant the actor should play, from its distance and heading. */
int armed_enemy_try_close_attack_pal(char *object) {
    char *state = *(char **)(object + 0x68);
    float dist;
    float ang;

    if (armed_enemy_has_partner_in_group(object) != 0)
        return 0;
    dist = 100.0f;
    ang = 1.0f;
    if (*(char **)(state + 0x2E0) != 0) {
        dist = vec_distance_xy(object + 0x10, *(char **)(state + 0x2E0) + 0x10);
        ang = mat_fast_helper_a(*(float *)(*(char **)(state + 0x2E0) + 0x10) - *(float *)(object + 0x10),
                            *(float *)(*(char **)(state + 0x2E0) + 0x14) - *(float *)(object + 0x14));
    }
    if (dist < 4.0f) {
        if (FastDiffRots(ang, *(float *)(object + 0xF8)) < 0.26179942f) {
            if (math_random_int_below(5) == 0) {
                moby_set_state(object, 0xC, 5);
                if (*(u8 *)(object + 0x43) != 7)
                    func_PAL_002A7E68(object, 7, 0, 0x8);
            } else if (*(int *)(state + 0x2E4) != 0) {
                moby_set_state(object, 0x12, 6);
                if (*(u8 *)(object + 0x43) != 0xD)
                    func_PAL_002A7E68(object, 0xD, 8, 0xC);
            } else {
                moby_set_state(object, 0xF, 6);
                if (*(u8 *)(object + 0x43) != 0xA)
                    func_PAL_002A7E68(object, 0xA, 8, 0xC);
            }
            return 1;
        }
    }
    return 0;
}

