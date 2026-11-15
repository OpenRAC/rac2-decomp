#include "include_asm.h"
#include "common.h"

extern s32 func_002761F8(void *first, void *second, s32 mode, void *object, s32 flags);
extern float D_L08_001BFF68;

/* func_L01_003BD560 with a zero floor meaning the probe's own height. */
float func_L08_00422850(void *position, float first, float second, float floor, float limit)
{
    float endpoints[2][4] __attribute__((aligned(16)));
    qcopy(endpoints[0], position);
    endpoints[0][2] = second;
    qcopy(endpoints[1], position);
    if (limit != 0.0f)
        endpoints[1][2] = first < limit ? first : limit;
    else
        endpoints[1][2] = first;
    if (CollLine(endpoints[1], endpoints[0], 2, 0, 0)) {
        return D_L08_001BFF68 > floor ? D_L08_001BFF68 : floor;
    }
    if (floor != 0.0f)
        return floor;
    return ((float *)position)[2];
}
