#include "include_asm.h"
#include "common.h"

extern char g_hero_position[];
extern void FastVecSub(void *, void *, void *);
extern float vec_get_heading_angle(void *, void *, int);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);

/* Picks the target point (the state's +0x80 point in mode 1, otherwise the 0x189EA0
   point) and reports the heading towards it and the two distances to it. */
void aim_get_target_heading_distances(u8 *object, float *target, float *distance, float *height, float *heading)
{
    u8 *state = *(u8 **)(object + 0x68);
    float offset[4] __attribute__((aligned(16)));
    void *from;

    if (*(int *)(state + 0x258) == 1)
        qcopy(target, state + 0x80);
    else
        qcopy(target, g_hero_position);
    FastVecSub(offset, target, object + 0x10);
    *heading = vec_get_heading_angle(object, offset, 0);
    *distance = fast_vec_dist(object + 0x10, target);
    *height = vec_distance_xy(object + 0x10, target);
}
