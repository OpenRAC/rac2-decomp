#include "include_asm.h"
#include "common.h"

extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(void *, void *, int);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);

/* Picks the target point (the state's +0x80 point in mode 1, otherwise the 0x189EA0
   point) and reports the heading towards it and the two distances to it. */
void func_L11_003F2E38(u8 *object, float *target, float *distance, float *height, float *heading)
{
    u8 *state = *(u8 **)(object + 0x68);
    float offset[4] __attribute__((aligned(16)));
    void *from;

    if (*(int *)(state + 0x258) == 1)
        qcopy(target, state + 0x80);
    else
        qcopy(target, D_00189EA0);
    FastVecSub(offset, target, object + 0x10);
    *heading = func_002B04E0(object, offset, 0);
    *distance = fast_vec_dist(object + 0x10, target);
    *height = vec_distance_xy(object + 0x10, target);
}
