#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_V4_002AE8C0
#define RAC2_T_V4_002AE8C0
typedef int V4_002AE8C0 __attribute__((mode(TI)));
#endif

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

/* The hero's world position is the 0x80 field of the resident block at D_00189E20;
   the address the retail body forms for it (0x189EA0) is this field's address. */
typedef struct {
    char reserved_000[0x80];
    float pos[4];
} GameState_189E20;

extern GameState_189E20 g_hero_state;

/* Runs the timer state, then integrates a copied position vector through two sine helpers
   and applies the result to the object's 0x24 field, either from the target position or from
   the hero position. The unit needs -frac2-qcopy -frac2-qcopy-barrier so the 16-byte copy
   reaches addiu/lq/sq, and -g for the two nops in front of the division. */
void moby_wander_around_home_point(char *objectPtr, char *statePtr, float speed, float slopeLimit)
{
    char *obj = objectPtr;
    char *st = statePtr;
    V4_002AE8C0 *pos;
    float nextPos[4];
    float distance;
    float limit;
    int moveResult;

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
    *(V4_002AE8C0 *)nextPos = *pos;
    nextPos[0] = nextPos[0] + math_fast_sin_or_cos_a(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    nextPos[1] = nextPos[1] + math_fast_sin_or_cos_b(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    moveResult = moby_move_over_ground(obj, (char *)pos, nextPos, 0, speed, *(float *)(st + 0x10), slopeLimit, 0.52359885f);
    *(float *)(obj + 0x18) = coll_probe_ground_height_below((char *)pos, 0, 0.5f);
    distance = vec_distance_xy((char *)pos, st);
    if (moveResult == 0 || *(float *)(st + 0x1C) < distance) {
        *(float *)(st + 0x24) = mat_fast_helper_a(*(float *)(st + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(st + 0x4) - *(float *)(obj + 0x14));
        *(short *)(st + 0x2A) = math_random_int_range(30, 90);
        *(short *)(st + 0x28) = 1;
    } else {
        float ratio;

        distance = vec_distance_xy((char *)pos, g_hero_state.pos);
        limit = *(float *)(st + 0x20);
        if (distance < limit) {
            ratio = distance / limit;
            *(float *)(st + 0x24) = math_move_angle_toward_target(*(float *)(st + 0x24),
                    mat_fast_helper_a(*(float *)(obj + 0x10) - g_hero_state.pos[0],
                                  *(float *)(obj + 0x14) - g_hero_state.pos[1]), ratio);
        }
    }
}
