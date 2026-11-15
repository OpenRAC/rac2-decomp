/* func_L07_002E2090 (112 bytes): spawns a record through func_L04_0030C4C0 (here
   ref_L07_002E2090_00) with two zeroed vectors whose z is +-0.4 of the z distance
   between the two points, and returns what the spawner returns. */
#include "common.h"

extern void *ref_L07_002E2090_00(void *, void *, void *, void *, void *, void *, int, void *, unsigned int);

/* Spawns an effect between two points, pushing it forward and back along the depth axis by 40
   percent of the gap between them. */
void *func_L07_002E2090(void *owner, float *startPos, float *endPos, void *extra, int option, void *extraData, unsigned int extraFlags) {
    float startVelocity[4];
    float endVelocity[4];
    float depthSpeed;
    qzero_nc(startVelocity);
    qzero_nc(endVelocity);
    depthSpeed = (endPos[2] - startPos[2]) * 0.4f;
    startVelocity[2] = depthSpeed;
    endVelocity[2] = -depthSpeed;
    return ref_L07_002E2090_00(owner, startPos, startVelocity, endPos, endVelocity, extra, option, extraData, extraFlags);
}
