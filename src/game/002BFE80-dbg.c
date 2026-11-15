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

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern int func_002A9568(float, int, int);
extern char D_001B5340[];

/* Moves an orbiting effect a quarter of the way toward D_001B5340 (capped when
   far), spins it, and fades it with the cosine of its angle; it dies with its
   owner, or once its timer runs out while the cosine is below its minimum. */
/* Updates a glowing effect that circles around a point and fades in and out.
   It disappears when its owner is gone. */
void func_002BFE80(char *effect)
{
    float d[4] __attribute__((aligned(16)));
    Orbit_002BFE80 *o;
    float c;
    float num;
    float den;
    float t;

    FastVecSub(d, gCameraState_001B5340, effect + 0x30);
    o = (Orbit_002BFE80 *)(effect + 0x20);
    if (FastVecLength(d) > 1.0f)
        vec_scale_to_length(d, d, 0.25f);
    else
        FastVecScale(d, d, 0.25f);
    FastVecAdd(effect + 0x10, o->target, d);
    o->angle = FastAddRotations(o->angle, o->rate);
    c = FastSinOrCosB(o->angle);
    if ((FastDecTimer(effect + 0xA) != 0 && (c < o->minimum || c < -0.9f)) || *o->owner == 0) {
        *o->owner = 0;
        KillParticle(effect);
        return;
    }
    if (o->minimum < c) {
        num = c - o->minimum;
        den = 1.0f - o->minimum;
        t = num / den;
        *(int *)(effect + 4) = ForwardTwoValuesAndAmount(t, 0, o->colour);
    }
    else
        *(int *)(effect + 4) = 0;
}
