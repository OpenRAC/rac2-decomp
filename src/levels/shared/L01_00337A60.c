#include "common.h"

extern s32 coll_find_outside_edge_index(void *, void *, s32);
extern void math_closest_point_on_segment(void *, char *, char *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);

/* Copy the edge nearest the point p from a closed polygon of n points, or p itself when inside. */
s32 math_closest_point_on_polygon_edge(void *out, void *p, char *pts, s32 n)
{
    f32 closest_point[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 best = 0.0f;
    f32 len;
    s32 i, next_index;

    if (coll_find_outside_edge_index(p, pts, n) == 0) {
        qcopy(out, p);
        return 0;
    }
    for (i = 0; i < n; i++) {
        next_index = i + 1;
        math_closest_point_on_segment(closest_point, pts + i * 16, pts + (next_index % n) * 16, p);
        FastVecSub(delta, p, closest_point);
        len = FastVecLength(delta);
        if (i == 0 || len < best) {
            best = len;
            qcopy(out, closest_point);
        }
    }
    return 1;
}
