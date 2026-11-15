#include "include_asm.h"
#include "common.h"

extern int CollLine(void *a, void *b, int mode, void *self, int flag);
typedef struct { int pad[6]; int f18; int f1C; } L04Flags;
extern L04Flags ref_L04_0033C420_00;

/* Checks for ground just below a point, and returns 0 if the ground is not allowed. */
int coll_check_ground_below_point(void *probePos, void *selfMoby, int rejectFlagged, float upOffset, float downOffset)
{
    float top[4];
    float bottom[4];
    int hit;

    qcopy(top, probePos);
    top[2] += upOffset;
    qcopy(bottom, probePos);
    bottom[2] -= downOffset;
    if (bottom[2] < 0.0f)
        bottom[2] = 0.0f;
    hit = CollLine(top, bottom, 0x22, selfMoby, 0);
    if (ref_L04_0033C420_00.f1C <= -1)
        hit = 0;
    if (rejectFlagged != 0 && ref_L04_0033C420_00.f18 != 0)
        hit = 0;
    return hit;
}
