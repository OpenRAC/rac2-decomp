#include "common.h"

extern s32 func_002761F8(void *first, void *second, s32 mode, void *object, s32 flags);
extern float D_L08_001BFF68;

float func_L08_003D8290(void *position, float first, float second)
{
    float endpoints[2][4] __attribute__((aligned(16)));
    qcopy(endpoints[0], position);
    endpoints[0][2] = second;
    qcopy(endpoints[1], position);
    endpoints[1][2] = first;
    if (CollLine(endpoints[1], endpoints[0], 2, 0, 0)) {
        return D_L08_001BFF68;
    }
    return 0.0f;
}
