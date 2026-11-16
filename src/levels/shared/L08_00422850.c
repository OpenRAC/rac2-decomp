#include "include_asm.h"
#include "common.h"

extern s32 CollLine(void *first, void *second, s32 mode, void *object, s32 flags);
extern float g_ground_height_result;

/* func_L01_003BD560 with a zero floor meaning the probe's own height. */
/* Looks for solid ground below a point and returns its height, or the floor value if nothing is hit. */
float coll_find_ground_height(void *position, float first, float second, float floor, float limit)
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
        return g_ground_height_result > floor ? g_ground_height_result : floor;
    }
    if (floor != 0.0f)
        return floor;
    return ((float *)position)[2];
}
