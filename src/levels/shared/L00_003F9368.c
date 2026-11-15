/* func_L00_003F9368: scale the object with its parent and emit its two trail effects. */
#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_QUAD_3F9368
#define RAC2_T_QUAD_3F9368
typedef int Quad_3f9368 __attribute__((mode(TI)));
typedef union { Quad_3f9368 q; float f[4]; } Vec_3f9368;
#endif

extern void moby_set_state(void *, int, int);
extern float FastAddRotations(float, float);

/* The bodies the retail calls reach, at 0x2D5940 and 0x33E220 in level 00. */
extern void FastVecScale(void *, void *, float);
extern void part_spawn_object_following_effect(void *, void *, int, int, int, float, float, int, int, int);

/* Grows the object with its parent and spawns two glowing trails each frame. */
void twin_trail_effect_update(char *self)
{
    Vec_3f9368 leftDir;
    Vec_3f9368 rightDir;
    char *parent;
    float scaleRatio;
    float trailFade;
    float trailLength;
    float angle;

    if (*(unsigned char *)(self + 0x20) == 0) {
        *(int *)(self + 0x78) = 0x150000FF;
        moby_set_state(self, 1, -1);
    }
    if (*(unsigned char *)(self + 0x20) != 1) {
        return;
    }
    parent = *(char **)(self + 0x24);
    scaleRatio = *(float *)(self + 0x2C) / *(float *)(parent + 0x24);
    trailLength = 243600.0f;
    trailFade = 0.1f;
    angle = FastAddRotations(*(float *)(self + 0xF4), 0.05235988646745682f);
    *(float *)(self + 0xF4) = angle;

    leftDir.q = 0;
    leftDir.f[1] = 0.5378739833831787f;
    leftDir.f[2] = -0.3785569965839386f;
    FastVecScale(&leftDir, &leftDir, scaleRatio);
    part_spawn_object_following_effect(&leftDir, self, 0x150000FF, -1, 1, trailLength, trailFade, 2, 1, -1);

    rightDir.q = 0;
    rightDir.f[1] = 0.5123069882392883f;
    rightDir.f[2] = 0.37711501121520996f;
    FastVecScale(&rightDir, &rightDir, scaleRatio);
    part_spawn_object_following_effect(&rightDir, self, 0x150000FF, -1, 1, trailLength, trailFade, 2, 1, -1);
}
