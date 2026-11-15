#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern float square_root(float);
extern float FastVecLength(void *);
extern float math_fabs(float);
/* Chooses a point on the segment near the sphere, breaking ties by reference distance. */
float FindSegmentSpherePoint(float radius, float *out, float *reference, float *point, float *start, float *end)
{
    struct {
        float offset[4], segment[4], closest[4], first[4], second[4];
    } vectors;
    float along, distance, length, reach, firstT, secondT;
    float firstError, secondError, threshold;
    float *second;
    FastVecSub(vectors.offset, start, point);
    FastVecSub(vectors.segment, end, start);
    length = FastVecDot(vectors.segment, vectors.segment);
    along = -FastVecDot(vectors.offset, vectors.segment) / length;
    FastVecScale(vectors.closest, vectors.segment, along);
    FastVecAdd(vectors.closest, vectors.closest, start);
    distance = fast_vec_dist(vectors.closest, point);
    if (distance < radius) {
        reach = square_root(radius * radius - distance * distance);
        /* One statement keeps debug labels from adding padding before this division. */
        reach /= FastVecLength(vectors.segment);
        firstT = along - reach;
        if (firstT < 0.0f) firstT = 0.0f;
        else if (firstT > 1.0f) firstT = 1.0f;
        secondT = along + reach;
        if (secondT < 0.0f) secondT = 0.0f;
        else if (secondT > 1.0f) secondT = 1.0f;
        FastVecScale(vectors.first, vectors.segment, firstT);
        FastVecAdd(vectors.first, vectors.first, start);
        firstError = math_fabs(fast_vec_dist(vectors.first, point) - radius);
        threshold = radius * 0.01f;
        if (firstError < threshold) firstError = 0.0f;
        second = vectors.second;
        FastVecScale(second, vectors.segment, secondT);
        FastVecAdd(second, second, start);
        secondError = math_fabs(fast_vec_dist(second, point) - radius);
        if (secondError < threshold) secondError = 0.0f;
        if (firstError < secondError || (firstError == secondError && fast_vec_dist(vectors.first, reference) < fast_vec_dist(second, reference))) {
            qcopy(out, vectors.first);
            distance = firstError;
        } else {
            qcopy(out, second);
            distance = secondError;
        }
    } else {
        if (along < 0.0f) {
            qcopy(out, start);
            distance = math_fabs(fast_vec_dist(out, point) - radius);
        } else if (along > 1.0f) {
            qcopy(out, end);
            distance = math_fabs(fast_vec_dist(out, point) - radius);
        } else {
            qcopy(out, vectors.closest);
        }
        if (distance < radius * 0.01f) distance = 0.0f;
    }
    return distance;
}
