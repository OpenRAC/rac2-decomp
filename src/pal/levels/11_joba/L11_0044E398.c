#include "include_asm.h"

#include "common.h"
extern void func_32C9E0();
extern void func_32C700();
extern s32 func_441868(s32 a0, s32 a1);
extern s32 func_33C800(char *a0, s32 a1, s32 a2, s32 a3, float f12, float f13);

/* Starts the idle animation: one pose while the robot holds an item, another without. */
void security_robot_play_idle_pal(char *object)
{
    if (*(s32 *)(*(char **)(object + 0x68) + 0x354) != 0) {
        func_32C9E0(object, 4, 2);
        if (*(u8 *)(object + 0x43) != 0)
            func_32C700(object, 0, 0, 0x8);
    } else {
        func_32C9E0(object, 5, 2);
        if (*(u8 *)(object + 0x43) != 1)
            func_32C700(object, 1, 0, 0x8);
    }
}

typedef int Rac2TI128 __attribute__((mode(TI)));
extern int joba_group_has_three_live_objects(char *object);
extern void FastVecSub(void *, void *, void *);
extern float vec_get_heading_angle(char *object, float *src, char *third);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_vec_dist(void *, void *);
extern int math_random_int_below(int);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended_pal(char *, int, int, int);
extern char g_hero_position[];

/* Picks the attack variant the actor plays against its target: the aim vector comes from the
   state's target record, or the shared default, and a close and well aimed target starts one
   of three attacks. */
int security_robot_try_start_attack_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    float v[4];
    float tmp[4];
    float ang;
    char *p;

    if (joba_group_has_three_live_objects(object) != 0)
        return 0;
    p = *(char **)(state + 0x350);
    if (p != 0)
        *(Rac2TI128 *)v = *(Rac2TI128 *)(p + 0x10);
    else
        *(Rac2TI128 *)v = *(Rac2TI128 *)g_hero_position;
    if (*(short *)(state + 0x36E) != 0) {
        FastVecSub(tmp, v, object + 0x10);
        ang = vec_get_heading_angle(object, tmp, state + 0x2F0);
    } else {
        ang = FastDiffRots(mat_fast_helper_a(v[0] - *(float *)(object + 0x10), v[1] - *(float *)(object + 0x14)),
                            *(float *)(object + 0xF8));
    }
    if (fast_vec_dist(object + 0x10, v) < 4.0f) {
        if (ang < 0.26179942f) {
            if (math_random_int_below(4) == 0) {
                moby_set_state(object, 0xC, 5);
                if (*(unsigned char *)(object + 0x43) != 7)
                    anim_start_blended_pal(object, 7, 0, 0x8);
            } else if (*(int *)(state + 0x354) != 0) {
                moby_set_state(object, 0xE, 6);
                if (*(unsigned char *)(object + 0x43) != 9)
                    anim_start_blended_pal(object, 9, 8, 0xC);
            } else {
                moby_set_state(object, 0xD, 6);
                if (*(unsigned char *)(object + 0x43) != 8)
                    anim_start_blended_pal(object, 8, 8, 0xC);
            }
            return 1;
        }
    }
    return 0;
}

