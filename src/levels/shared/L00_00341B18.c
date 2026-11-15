#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void FastVecSub(void *, const void *, const void *);
extern void vec_fast_normalize_helper(void *, const void *, float);
extern float FastVecDot(const void *, const void *);
extern float vec_distance_xy(const void *, const void *);

/* Finds the closest point to a given point on a flat line segment, and returns how far away that point is. */
float math_closest_point_on_segment_2d(float *out, const float *point, const float *start, const float *end) {
    Vector delta;
    Vector normal;
    Vector base;
    float distance;
    float endpointDistance;
    int axis;
    const float *a, *b;
    float *projection;
    FastVecSub(&delta, start, end);
    normal.f[0] = -delta.f[1];
    normal.f[1] = delta.f[0];
    normal.f[2] = 0.0f;
    base.q = *(const Quadword *)start;
    base.f[2] = 0.0f;
    vec_fast_normalize_helper(&normal, &normal, 1.0f);
    distance = FastVecDot(&normal, &base);
    distance = normal.f[0] * point[0] + normal.f[1] * point[1] - distance;
    out[0] = point[0] - distance * normal.f[0];
    out[1] = point[1] - distance * normal.f[1];
    out[2] = 0.0f;
    axis = 0;
    b = end;
    projection = out;
    a = start;
    do {
        if (*a + 0.001f < *projection && *b + 0.001f < *projection)
            break;
        if (*projection < *a - 0.001f && *projection < *b - 0.001f)
            break;
        ++axis;
        ++b;
        ++projection;
        ++a;
    } while (axis < 2);
    if (axis < 2) {
        endpointDistance = vec_distance_xy(out, start);
        if (endpointDistance < vec_distance_xy(out, end)) {
            *(Quadword *)out = *(const Quadword *)start;
            out[2] = 0.0f;
        } else {
            *(Quadword *)out = *(const Quadword *)end;
            out[2] = 0.0f;
        }
    }
    return vec_distance_xy(point, out);
}
