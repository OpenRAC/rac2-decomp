#include "common.h"

/* Samples the cubic segment, adds jitter only to interior points, then
 * extrapolates its final point. The retail contract requires count >= 3,
 * count aligned 16-byte output vectors and four aligned control vectors. */
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } CurveVector;
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
/* The five-pointer/one-FP interpolation leaf differs between programs. */
extern void ref_L11_00397C08_00(void *, void *, void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);

/* Builds a wobbly curve: fills in points along a smooth curve and nudges the middle ones at random. */
void curve_build_jittered_points(CurveVector *points, int count, CurveVector *control, float noise) {
    CurveVector first, second, jitter;
    float inverse;
    int i;
    qcopy(&first, &control[2]);
    FastVecAdd(&first, &first, &control[0]);
    qcopy(&second, &control[3]);
    FastVecAdd(&second, &second, &control[1]);
    inverse = 1.0f / IntToFloat(count - 2);
    for (i = 0; i < count - 1; i++) {
        ref_L11_00397C08_00(&points[i], &control[0], &control[1], &first, &second, IntToFloat(i) * inverse);
        if (i > 0 && i < count - 2) {
            jitter.f[3] = 0.0f;
            jitter.f[0] = math_random_float_range(-1.0f, 1.0f);
            jitter.f[1] = math_random_float_range(-1.0f, 1.0f);
            jitter.f[2] = math_random_float_range(-1.0f, 1.0f);
            vec_scale_to_length(&jitter, &jitter, noise);
            FastVecAdd(&points[i], &points[i], &jitter);
        }
    }
    FastVecSub(&jitter, &points[count - 2], &points[count - 3]);
    FastVecAdd(&points[count - 1], &points[count - 2], &jitter);
}
