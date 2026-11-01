#include "include_asm.h"

#include "common.h"
extern int ref_L00_003DD2B8_00(void *);
extern int ref_L00_003DD2B8_01(float);
extern void ref_L00_003DD2B8_02(void *, void *, void *);
extern void ref_L00_003DD2B8_03(void *, void *, void *);
extern void ref_L00_003DD2B8_04(void *, float, float, void *, int);
extern void ref_L00_003DD2B8_05(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern char ref_L00_003DD2B8_06[] __attribute__((sda));
extern void ref_L00_003DD2B8_07(void *);
extern void ref_L00_003DD2B8_08(void *, void *);
extern void ref_L00_003DD2B8_09(void *, void *, void *);
extern void ref_L00_003DD2B8_10(void *, void *, void *);
extern int ref_L00_003DD2B8_11(void *, float, int, void *);
extern void ref_L00_003DD2B8_12(void *, void *, float);
extern char ref_L00_003DD2B8_13[];
extern float ref_L00_003DD2B8_14(void *);
extern float ref_L00_003DD2B8_15(void *, void *);
extern void ref_L00_003DD2B8_16(void *, void *, void *);
extern void ref_L00_003DD2B8_17(void *, void *, void *);
extern void ref_L00_003DD2B8_18(void *, void *, float);
extern void ref_L00_003DD2B8_19(void *, void *);
extern void ref_L00_003DD2B8_20(void *, void *);
typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char phase;
    char pad21[2];
    unsigned char fade;
    char pad24[0x10];
    unsigned short flags;
    char pad36[0x32];
    struct BounceState *state;
    char pad6C[0x54];
    float orientation[4];
} BounceObject;
typedef struct BounceState {
    float velocity[4];
    float spin[4];
    float pivot[3];
    float radius;
    int timer;
    int flags;
    float gravity;
} BounceState;

/* Per-frame update of a bouncing object: runs its timed phases, then moves and bounces it. */
void func_PAL_L09_00409700(BounceObject *object)
{
    float point[4];
    float rotation[12];
    float after[4], delta[4], probe[4];
    float matrix[16], normalStep[4], axis[4];
    BounceState *state = object->state;
    float radius, length, projection;
    switch (object->phase) {
    case 0:
        ref_L00_003DD2B8_07(object);
        return;
    case 1:
        if (ref_L00_003DD2B8_00(&state->timer)) {
            object->phase = 3;
            state->timer = ref_L00_003DD2B8_01(8.666667f);
            object->flags |= 0x2000;
            return;
        }
        break;
    case 2:
        ref_L00_003DD2B8_02(point, state->pivot, object->orientation);
        ref_L00_003DD2B8_03(point, point, object->position);
        if (state->flags & 2) {
            ref_L00_003DD2B8_04(object, 0.3f, 10.0f, point, -1);
        } else {
            ref_L00_003DD2B8_05(object, ref_L00_003DD2B8_06, point, 0.0f, 0.0f,
                5, 3, 5, 1.0f, 0.5f, 9.0f, 0.3330000042915344f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        }
        ref_L00_003DD2B8_07(object);
        return;
    case 3:
        if (ref_L00_003DD2B8_00(&state->timer)) {
            ref_L00_003DD2B8_07(object);
            return;
        }
        object->fade = ref_L00_003DD2B8_01((float)state->timer * 14.76923f);
        break;
    }
    ref_L00_003DD2B8_08(rotation, state->spin);
    ref_L00_003DD2B8_02(point, state->pivot, object->orientation);
    ref_L00_003DD2B8_09(object->orientation, rotation, object->orientation);
    ref_L00_003DD2B8_02(after, state->pivot, object->orientation);
    ref_L00_003DD2B8_10(delta, after, point);
    ref_L00_003DD2B8_10(object->position, object->position, delta);
    ref_L00_003DD2B8_03(object->position, object->position, state->velocity);
    radius = state->radius;
    state->velocity[2] -= state->gravity;
    ref_L00_003DD2B8_02(probe, state->pivot, object->orientation);
    ref_L00_003DD2B8_03(probe, probe, object->position);
    if (ref_L00_003DD2B8_11(probe, radius, 0, object)) {
        ref_L00_003DD2B8_12(ref_L00_003DD2B8_13, ref_L00_003DD2B8_13, 1.0f);
        length = ref_L00_003DD2B8_14(state->velocity);
        projection = ref_L00_003DD2B8_15(state->velocity, ref_L00_003DD2B8_13);
        if (projection < 0.0f) {
            ref_L00_003DD2B8_16(state->velocity, state->velocity, ref_L00_003DD2B8_13);
            ref_L00_003DD2B8_12(normalStep, ref_L00_003DD2B8_13, projection * 0.5f);
            ref_L00_003DD2B8_03(state->velocity, state->velocity, normalStep);
            ref_L00_003DD2B8_12(state->velocity, state->velocity, length);
            ref_L00_003DD2B8_17(axis, ref_L00_003DD2B8_13, state->velocity);
            ref_L00_003DD2B8_12(axis, axis, 1.0f);
            ref_L00_003DD2B8_18(axis, axis, ref_L00_003DD2B8_14(state->spin));
            ref_L00_003DD2B8_19(axis, matrix);
            ref_L00_003DD2B8_20(matrix, state->spin);
        }
    }
}

