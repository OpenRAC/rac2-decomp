#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { int count; int reserved[3]; Vector points[0]; } Path;
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);

/* rac1-decomp src/overlays/shared/moby_ground_collision.c: Spline_AdvanceByDistance.
 * Moves a distance along the path from segment *index at offset *offset, updates both and
 * writes the point reached to out; returns 1 when an end was passed. */
int Spline_AdvanceByDistance(const Path *path, Vector *out, int *index, float *offset, int wrap, float step) {
    Vector delta;
    int reached = 0;
    int direction = 1;
    int i;
    int j;

    if (step < 0.0f) {
        step = -step;
        direction = -1;
    }
    while (step != 0.0f && (*index != path->count - 1 || wrap)) {
        int crosses;

        i = *index;
        if (direction == 1) {
            crosses = path->points[i].f[3] < *offset + step;
        } else {
            crosses = *offset < step;
        }
        if (crosses) {
            i += direction;
            if (i >= path->count || i < 0) {
                i = (i + path->count) % path->count;
            }
            if (direction == 1) {
                step -= path->points[*index].f[3] - *offset;
                *offset = 0.0f;
                if (step < 0.0f) {
                    step = 0.0f;
                }
            } else {
                step -= *offset;
                *offset = path->points[i].f[3];
            }
            if ((direction == 1 && *index == path->count - 1) || (direction == -1 && *index == 0)) {
                reached = 1;
            }
            *index = i;
        } else {
            if (direction == 1) {
                *offset = *offset + step;
            } else {
                *offset = *offset - step;
            }
            step = 0.0f;
        }
    }
    i = *index;
    qcopy_nc(out, &path->points[i]);
    if (i == path->count - 1 && !wrap) {
        if (direction == -1) {
            *index = 0;
            qcopy_nc(out, &path->points[0]);
            *offset = 0.0f;
        }
        return 1;
    }
    j = i + 1;
    if (j >= path->count) {
        j %= path->count;
    }
    FastVecSub(&delta, &path->points[j], &path->points[i]);
    vec_scale_to_length(&delta, &delta, *offset);
    FastVecAdd(out, out, &delta);
    return reached;
}
