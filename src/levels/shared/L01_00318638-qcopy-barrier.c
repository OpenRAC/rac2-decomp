#include "include_asm.h"
#include "names.h"


typedef int V4_002AE8C0 __attribute__((mode(TI)));
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float);
extern int moby_l01_turn_toward_target(char *, float *);
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

/* Hand-adapted from func_002AE8C0. */
/* Moves a wandering enemy: picks a new heading when its timer runs out, turns away from walls and edges, and turns away from the hero when close. */
void enemy_update_wander_heading(char *obj, char *wander, char *context)
{
    char *selfPos;
    float probePoint[4];
    float amount;

    int blocked;

    if (*(short *)(wander + 0x28) == 0) {
        *(float *)(wander + 0x24) = *(float *)(wander + 0x24) + math_random_signed_float_range(0.78539824f, 2.6179941f);
        *(short *)(wander + 0x2A) = math_random_int_range(*(short *)(wander + 0x2C), *(short *)(wander + 0x2E));
        *(short *)(wander + 0x28) = 1;
    } else {
        StepAngleTowardTarget((float *)(obj + 0xF8), 0, *(float *)(wander + 0x24), *(float *)(wander + 0x18));
        if (FastDecTimer(wander + 0x2A) != 0)
            *(short *)(wander + 0x28) = 0;
    }
    selfPos = obj + 0x10;
    *(V4_002AE8C0 *)probePoint = *(V4_002AE8C0 *)selfPos;
    amount = *(float *)(context + 0x28);
    *(float *)(context + 0x28) = *(float *)(wander + 0x14);
    probePoint[0] = probePoint[0] + math_fast_sin_or_cos_a(*(float *)(obj + 0xF8)) * 2.0f;
    probePoint[1] = probePoint[1] + math_fast_sin_or_cos_b(*(float *)(obj + 0xF8)) * 2.0f;
    *(float *)(context + 0x28) = amount;
    blocked = moby_l01_turn_toward_target(obj, probePoint);
    *(float *)(obj + 0x18) = coll_probe_ground_height_below(selfPos, 0, 0.5f);
    amount = vec_distance_xy(selfPos, wander);
    if (blocked != 0 || *(float *)(wander + 0x1C) < amount) {
        *(float *)(wander + 0x24) = mat_fast_helper_a(*(float *)(wander + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(wander + 0x4) - *(float *)(obj + 0x14));
        *(short *)(wander + 0x2A) = math_random_int_range(30, 90);
        *(short *)(wander + 0x28) = 1;
    } else {
        float limit;

        amount = vec_distance_xy(selfPos, g_hero_state.pos);
        limit = *(float *)(wander + 0x20);
        if (amount < limit) {
            amount = amount / limit;
            *(float *)(wander + 0x24) = math_move_angle_toward_target(*(float *)(wander + 0x24),
                    mat_fast_helper_a(*(float *)(obj + 0x10) - g_hero_state.pos[0],
                                  *(float *)(obj + 0x14) - g_hero_state.pos[1]), amount);
        }
    }
}
