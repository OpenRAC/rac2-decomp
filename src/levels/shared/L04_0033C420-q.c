#include "include_asm.h"
#include "common.h"

extern int CollLine(void *a, void *b, int mode, void *self, int flag);
typedef struct { int pad[6]; int f18; int f1C; } L04Flags;
extern L04Flags ref_L04_0033C420_00;

/* Checks for ground just below a point, and returns 0 if the ground is not allowed. */
int coll_check_ground_below_point(void *probe_pos, void *self_moby, int reject_flagged, float up_offset, float down_offset)
{
    float top[4];
    float bottom[4];
    int hit;

    qcopy(top, probe_pos);
    top[2] += up_offset;
    qcopy(bottom, probe_pos);
    bottom[2] -= down_offset;
    if (bottom[2] < 0.0f)
        bottom[2] = 0.0f;
    hit = CollLine(top, bottom, 0x22, self_moby, 0);
    if (ref_L04_0033C420_00.f1C <= -1)
        hit = 0;
    if (reject_flagged != 0 && ref_L04_0033C420_00.f18 != 0)
        hit = 0;
    return hit;
}
