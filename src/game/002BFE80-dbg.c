#include "include_asm.h"
#include "names.h"

/* func_002BFE80 under its parent unit's profile (-g); its own file keeps its
   prototypes apart from 002BF6F0.c's per-caller spellings. */

typedef struct {
    int *owner;
    float angle;
    float minimum;
    int colour;
    float target[3];
    float rate;
} Orbit_002BFE80;

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern int moby_forward_two_values_and_amount(float, int, int);
extern char g_camera_eye_state[];

/* Moves an orbiting effect a quarter of the way toward D_001B5340 (capped when
   far), spins it, and fades it with the cosine of its angle; it dies with its
   owner, or once its timer runs out while the cosine is below its minimum. */
/* Updates a glowing effect that circles around a point and fades in and out.
   It disappears when its owner is gone. */
void part_update_orbiting_glow(char *effect)
{
    float d[4] __attribute__((aligned(16)));
    Orbit_002BFE80 *o;
    float c;
    float num;
    float den;
    float t;

    FastVecSub(d, g_camera_eye_state, effect + 0x30);
    o = (Orbit_002BFE80 *)(effect + 0x20);
    if (FastVecLength(d) > 1.0f)
        vec_scale_to_length(d, d, 0.25f);
    else
        FastVecScale(d, d, 0.25f);
    FastVecAdd(effect + 0x10, o->target, d);
    o->angle = FastAddRotations(o->angle, o->rate);
    c = math_fast_sin_or_cos_b(o->angle);
    if ((FastDecTimer(effect + 0xA) != 0 && (c < o->minimum || c < -0.9f)) || *o->owner == 0) {
        *o->owner = 0;
        part_kill(effect);
        return;
    }
    if (o->minimum < c) {
        num = c - o->minimum;
        den = 1.0f - o->minimum;
        t = num / den;
        *(int *)(effect + 4) = moby_forward_two_values_and_amount(t, 0, o->colour);
    }
    else
        *(int *)(effect + 4) = 0;
}
