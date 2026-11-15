#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);

/* Moves the actor's effect point to a spot around the target position at arg1: the heading from
   the target to the actor plus up to a quarter turn either way, at a distance of 8 plus or minus
   2; the point is copied from arg1 into the state (+0x4A0) and then offset in x and y. */
/* Picks a random spot near the target for the actor to walk to, about 8 units away. */
void func_L02_003F1A88(char *actor, char *targetPos) {
    char *state;
    float angle;
    float radius;

    angle = FastMatrixHelperA(*(float *)(actor + 0x10) - *(float *)targetPos,
                          *(float *)(actor + 0x14) - *(float *)(targetPos + 4));
    angle += RandomFloatRange(-0.78539824f, 0.78539824f);
    radius = RandomFloatRange(-2.0f, 2.0f) + 8.0f;
    state = *(char **)(actor + 0x68);
    qcopy(state + 0x4A0, targetPos);
    *(float *)(state + 0x4A0) += radius * FastSinOrCosA(angle);
    *(float *)(state + 0x4A4) += radius * FastSinOrCosB(angle);
}
