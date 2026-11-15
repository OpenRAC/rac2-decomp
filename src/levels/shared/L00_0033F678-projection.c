#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern float func_00282C48(float);
extern float func_L00_00341B18(float *, const float *, const float *, const float *);
extern float func_00282E80(const void *, const void *);
extern float func_00282E48(const void *, const void *);
extern void func_L00_0031D670(void *, const void *, const void *, float);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern float func_00282DB0(const void *, const void *);
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern float func_L00_00341A88(void *, void *, float);

/* Return the distance to the segment and write the nearest projected point. */
float func_L00_00341D08(Vector *out, const Vector *point, const Vector *start, const Vector *end, float height) {
    Vector direction, base, normal, pointCopy, outCopy;
    float distance, endpointDistance, negativeDot, baseDot, denominator;
    int axis;
    const float *a, *b;
    float *projection;
    if (0.0f < height && func_00282C48(point->f[2] - start->f[2]) < height &&
        func_00282C48(point->f[2] - end->f[2]) < height) {
        distance = func_L00_00341B18(out->f, point->f, start->f, end->f);
        height = vec_distance_xy(start, out);
        height /= vec_distance_xy(start, end);
        direction.q = start->q;
        base.q = end->q;
        LerpVector4(out, &direction, &base, height);
        return distance;
    }
    FastVecSub(&direction, end, start);
    base.q = start->q;
    vec_scale_to_length(&direction, &direction, 1.0f);
    qcopy(&normal, &direction);
    negativeDot = -FastVecDot(point, &direction);
    baseDot = FastVecDot(&base, &normal);
    denominator = FastVecDot(&direction, &normal);
    {
        float numerator = -(negativeDot + baseDot);
        float scale = numerator / denominator;
        FastVecScale(out, &direction, scale);
    }
    FastVecAdd(out, out, &base);
    axis = 0;
    b = end->f;
    a = start->f;
    projection = out->f;
    do {
        float value = *projection;
        if (*a < value && *b < value) break;
        if (value < *a && value < *b) break;
        ++axis;
        ++b;
        ++a;
        ++projection;
    } while (axis < 3);
    if (axis < 3) {
        endpointDistance = fast_vec_dist(out, start);
        if (endpointDistance < fast_vec_dist(out, end)) qcopy(out, start);
        else qcopy(out, end);
    }
    pointCopy.q = point->q;
    outCopy.q = out->q;
    return func_L00_00341A88(&pointCopy, &outCopy, 0.0f);
}
