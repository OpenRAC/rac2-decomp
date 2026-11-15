#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

/* Moves the actor's effect point to a spot around the target position at arg1: the heading from
   the target to the actor plus up to a quarter turn either way, at a distance of 8 plus or minus
   2; the point is copied from arg1 into the state (+0x4A0) and then offset in x and y. */
/* Picks a random spot near the target for the actor to walk to, about 8 units away. */
void actor_pick_approach_point(char *actor, char *target_pos) {
    char *state;
    float angle;
    float radius;

    angle = mat_fast_helper_a(*(float *)(actor + 0x10) - *(float *)target_pos,
                          *(float *)(actor + 0x14) - *(float *)(target_pos + 4));
    angle += math_random_float_range(-0.78539824f, 0.78539824f);
    radius = math_random_float_range(-2.0f, 2.0f) + 8.0f;
    state = *(char **)(actor + 0x68);
    qcopy(state + 0x4A0, target_pos);
    *(float *)(state + 0x4A0) += radius * math_fast_sin_or_cos_a(angle);
    *(float *)(state + 0x4A4) += radius * math_fast_sin_or_cos_b(angle);
}
