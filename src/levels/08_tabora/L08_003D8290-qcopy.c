#include "common.h"

extern s32 CollLine(void *first, void *second, s32 mode, void *object, s32 flags);
extern float D_L08_001BFF68;

/* Checks for ground between two heights above a point and returns a fixed height value if it hits, otherwise 0. */
float coll_find_ground_height_between(void *position, float upper_height, float lower_height)
{
    float line_ends[2][4] __attribute__((aligned(16)));
    qcopy(line_ends[0], position);
    line_ends[0][2] = lower_height;
    qcopy(line_ends[1], position);
    line_ends[1][2] = upper_height;
    if (CollLine(line_ends[1], line_ends[0], 2, 0, 0)) {
        return D_L08_001BFF68;
    }
    return 0.0f;
}
