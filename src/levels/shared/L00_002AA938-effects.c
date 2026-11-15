#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char D_00189E20[];
extern float func_002A7878(float, float);
extern void func_0029FCC0(char *, int, char *);
extern void func_00282D30(void *, void *, float);
extern void func_L00_00335558(Vector *, void *, float);
extern unsigned char *func_002BF728(Vector *, Vector *, float, float);

/* Joint branches and velocity copy follow RAC1 emit_hero_randomized_motion_effects
 * in overlays/shared/hero_idle_and_animation.c (OpenRAC/rac1-decomp, GPL-3.0). */
/* Emit particles either around the player or alternately from selected joints. */
void func_L00_002AA938(int count, int sourceMode, int sparks) {
    Vector position;
    Vector velocity;
    unsigned char *player;
    Vector *inheritedVelocity;
    int index;
    float size;
    for (index = 0; index < count; ++index) {
        player = D_00189E20;
        inheritedVelocity = (Vector *)(player + 0x110);
        if (sourceMode == 0) {
            position.f[0] = *(float *)(player + 0x80) + func_002A7878(-0.1f, 0.1f);
            position.f[1] = *(float *)(player + 0x84) + func_002A7878(-0.1f, 0.1f);
            position.f[2] = *(float *)(player + 0x88) + func_002A7878(-0.5f, 0.1f);
        } else if (sourceMode == 1) {
            if (!(index & 1))
                func_0029FCC0(*(char **)(player + 0x2290), 0, (char *)&position);
            else
                func_0029FCC0(*(char **)(player + 0x2290), 14, (char *)&position);
        } else if (sourceMode == 2) {
            if (!(index & 1))
                func_0029FCC0(*(char **)(player + 0x2290), 23, (char *)&position);
            else
                func_0029FCC0(*(char **)(player + 0x2290), 22, (char *)&position);
        }
        qcopy(&velocity, inheritedVelocity);
        if (*(int *)(player + 0x2294) == 0x33) FastVecScale(&velocity, &velocity, 1.15f);
        else FastVecScale(&velocity, &velocity, 0.7f);
        velocity.f[0] += func_002A7878(-0.0066666672937572f, 0.0066666672937572f);
        velocity.f[1] += func_002A7878(-0.0066666672937572f, 0.0066666672937572f);
        velocity.f[2] += func_002A7878(-0.01666666753590107f, 0.0f);
        if (sparks) {
            unsigned char *matrix = *(unsigned char **)(player + 0x2290) + 0xC0;
            size = func_002A7878(0.7f, 1.1f);
            func_L00_00335558(&position, matrix, *(float *)(player + 0x170) * size);
        } else {
            size = func_002A7878(4200.0f, 7350.0f);
            func_002BF728(&position, &velocity, size, -1.0f);
        }
    }
}
