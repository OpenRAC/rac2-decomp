#include "include_asm.h"
#include "common.h"

extern s32 CollLine(void *first, void *second, s32 mode, void *object, s32 flags);
extern float D_L01_001BF928;

/* func_L08_00425328 with a cap on the lower end: a nonzero limit below the first height
   replaces it (-ffast-math for the min.s and max.s). */
float coll_get_ground_height_with_limit(void *position, float first, float second, float floor, float limit)
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
        return D_L01_001BF928 > floor ? D_L01_001BF928 : floor;
    }
    return floor;
}
