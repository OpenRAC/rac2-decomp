#include "include_asm.h"
#include "common.h"

extern s32 CollLine(void *first, void *second, s32 mode, void *object, s32 flags);
extern float g_ground_height_result;

/* func_L08_003D8290 with a floor (-ffast-math for the max.s): the clear result is the floor, a hit is raised to it. */
float coll_find_ground_height_floor(void *position, float first, float second, float floor)
{
    float endpoints[2][4] __attribute__((aligned(16)));
    qcopy(endpoints[0], position);
    endpoints[0][2] = second;
    qcopy(endpoints[1], position);
    endpoints[1][2] = first;
    if (CollLine(endpoints[1], endpoints[0], 2, 0, 0)) {
        return g_ground_height_result > floor ? g_ground_height_result : floor;
    }
    return floor;
}
