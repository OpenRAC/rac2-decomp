#include "common.h"

extern s32 func_002761F8(void *first, void *second, s32 mode, void *object, s32 flags);
extern float D_L08_001BFF68;

/* Checks for ground between two heights above a point and returns a fixed height value if it hits, otherwise 0. */
float func_L08_003D8290(void *position, float upperHeight, float lowerHeight)
{
    float lineEnds[2][4] __attribute__((aligned(16)));
    qcopy(lineEnds[0], position);
    lineEnds[0][2] = lowerHeight;
    qcopy(lineEnds[1], position);
    lineEnds[1][2] = upperHeight;
    if (CollLine(lineEnds[1], lineEnds[0], 2, 0, 0)) {
        return D_L08_001BFF68;
    }
    return 0.0f;
}
