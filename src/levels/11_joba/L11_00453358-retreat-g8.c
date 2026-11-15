#include "common.h"

typedef int Quadword __attribute__((mode(TI)));

typedef union {
    Quadword q;
    float f[4];
} Probe;

typedef struct {
    char pad00[0x240];
    unsigned char *target;
} RetreatState;

typedef struct {
    char pad00[0x10];
    float position[4];
    char pad20[0x48];
    RetreatState *state;
} RetreatObject;

extern float D_L11_001B1DA0 SDATA(D_L11_001B1DA0);
extern float D_L11_001B1DA4 SDATA(D_L11_001B1DA4);
extern int D_L11_001B1DA8 SDATA(D_L11_001B1DA8);

extern void moby_set_state(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern int math_fast_helper_a(void *, float);
extern int math_random_int_below(int);

/* Chooses the next action from the distance to the target: action 4 without one, action 7
   when close or the way ahead is blocked, action 9 when far or the random roll fails. */
void fighter_choose_action(RetreatObject *object)
{
    RetreatState *state = object->state;
    unsigned char *target = state->target;
    float distance;
    Probe copy, probe;

    if (target == 0) {
        moby_set_state(object, 4, 2);
        return;
    }

    distance = vec_distance_xy(object->position, target + 0x10);
    if (distance < D_L11_001B1DA4) {
        moby_set_state(object, 7, 3);
    } else {
        probe.q = 0;
        probe.f[0] = object->position[0];
        probe.f[1] = object->position[1];
        probe.f[2] = object->position[2];
        probe.f[3] = 0.5f;
        copy.q = probe.q;
        if (math_fast_helper_a(&copy, 128.0f) <= 0) {
            moby_set_state(object, 7, 3);
        } else if (distance > D_L11_001B1DA0 || math_random_int_below(D_L11_001B1DA8) == 0) {
            moby_set_state(object, 9, 3);
        } else {
            moby_set_state(object, 7, 3);
        }
    }
}
