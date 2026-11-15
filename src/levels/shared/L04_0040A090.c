#include "common.h"

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);

/* Measures a path of 2D points: for each segment it stores the length, the direction and where the segment starts, and it gives the total length. */
void path_measure_segments(int n, int (*pts)[2], float (*dirs)[4], float *lens, float *starts, float *total)
{
    float delta[4] __attribute__((aligned(16)));
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    float segLength;
    int i;
    int next;

    *total = 0.0f;
    for (i = 0; i < n - 1; i = next) {
        next = i + 1;
        from[0] = pts[i][0];
        from[1] = pts[i][1];
        from[2] = 0.0f;
        to[0] = pts[next][0];
        to[1] = pts[next][1];
        to[2] = 0.0f;
        FastVecSub(delta, to, from);
        segLength = FastVecLength(delta);
        lens[i] = segLength;
        starts[i] = *total;
        *total = *total + segLength;
        FastVecScale(dirs[i], delta, 1.0f / segLength);
    }
}
