#include "include_asm.h"
#include "names.h"

typedef int V4_002AE8C0 __attribute__((mode(TI)));
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float);
extern int moby_move_over_ground(char *, char *, float *, int, float, float, float, float);
extern float coll_probe_ground_height_below(char *, int, float);
extern float math_move_angle_toward_target(float, float, float);
extern void StepAngleTowardTarget(float *, int, float, float);
extern int FastDecTimer(char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(char *, char *);
typedef struct {
    char reserved_000[0x80];
    float pos[4];
} GameState_189E20;
extern GameState_189E20 g_hero_state;

/* Runs the timer state, then integrates a copied position vector through two sine helpers
   and applies the result to the object's 0x24 field, either from the target position or from
   the hero position. The unit needs -frac2-qcopy -frac2-qcopy-barrier so the 16-byte copy
   reaches addiu/lq/sq, and -g for the two nops in front of the division. */
void moby_wander_around_home_point_pal(char *moby, char *home, float speed, float max_step)
{
    char *obj = moby;
    char *st = home;
    V4_002AE8C0 *pos;
    float v[4];
    float f;
    float limit;
    int r;

    if (*(short *)(st + 0x28) == 0) {
        *(float *)(st + 0x24) = *(float *)(st + 0x24) + math_random_signed_float_range(0.78539824f, 2.6179941f);
        *(short *)(st + 0x2A) = math_random_int_range(*(short *)(st + 0x2C), *(short *)(st + 0x2E));
        *(short *)(st + 0x28) = 1;
    } else {
        StepAngleTowardTarget((float *)(obj + 0xF8), 0, *(float *)(st + 0x24), *(float *)(st + 0x18));
        if (FastDecTimer(st + 0x2A) != 0)
            *(short *)(st + 0x28) = 0;
    }
    pos = (V4_002AE8C0 *)(obj + 0x10);
    *(V4_002AE8C0 *)v = *pos;
    v[0] = v[0] + math_fast_sin_or_cos_a(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    v[1] = v[1] + math_fast_sin_or_cos_b(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    r = moby_move_over_ground(obj, (char *)pos, v, 0, speed, *(float *)(st + 0x10), max_step, 0.52359885f);
    *(float *)(obj + 0x18) = coll_probe_ground_height_below((char *)pos, 0, 0.5f);
    f = vec_distance_xy((char *)pos, st);
    if (r == 0 || *(float *)(st + 0x1C) < f) {
        *(float *)(st + 0x24) = mat_fast_helper_a(*(float *)(st + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(st + 0x4) - *(float *)(obj + 0x14));
        *(short *)(st + 0x2A) = math_random_int_range(25, 75);
        *(short *)(st + 0x28) = 1;
    } else {
        float t;

        f = vec_distance_xy((char *)pos, g_hero_state.pos);
        limit = *(float *)(st + 0x20);
        if (f < limit) {
            t = f / limit;
            *(float *)(st + 0x24) = math_move_angle_toward_target(*(float *)(st + 0x24),
                    mat_fast_helper_a(*(float *)(obj + 0x10) - g_hero_state.pos[0],
                                  *(float *)(obj + 0x14) - g_hero_state.pos[1]), t);
        }
    }
}
