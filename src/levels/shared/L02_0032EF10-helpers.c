#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } MoveVector;
extern int SegmentCrossPolyline(int, void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int path_push_point_away(int, void *, void *, float);

/* Moves a point toward a target along a path, stopping just short of any wall in the way. The result is kept inside the path's allowed area and keeps the target height. */
void path_clamp_move_to_area(MoveVector *start, MoveVector *target, MoveVector *output, int path, float radius) {
    MoveVector source, intersection, destination;
    MoveVector *hit = &intersection;
    source.q = start->q;
    if (SegmentCrossPolyline(path, &source, target, hit)) {
        FastVecSub(hit, hit, &source);
        FastVecScale(hit, hit, 0.9900000095367432f);
        FastVecAdd(&destination, &intersection, &source);
    } else {
        qcopy(&destination, target);
    }
    if (!path_push_point_away(path, &destination, output, radius))
        qcopy(output, &destination);
    output->f[2] = target->f[2];
}
