#include "common.h"


#include "common.h"

/* Samples the cubic segment, adds jitter only to interior points, then
 * extrapolates its final point. The retail contract requires count >= 3,
 * count aligned 16-byte output vectors and four aligned control vectors. */
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } CurveVector;
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
/* The five-pointer/one-FP interpolation leaf differs between programs. */
extern void ref_L18_0043F130_00(void *, void *, void *, void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);

/* Same body as func_L11_00397C08, with this function's own callees. */
/* Builds a lightning-like curve of points along a smooth path, with small random wobble on the middle points. */
void func_L18_0043F130(CurveVector *points, int count, CurveVector *control, float noise) {
    CurveVector first, second, jitter;
    float inverse;
    int i;
    qcopy(&first, &control[2]);
    FastVecAdd(&first, &first, &control[0]);
    qcopy(&second, &control[3]);
    FastVecAdd(&second, &second, &control[1]);
    inverse = 1.0f / IntToFloat(count - 2);
    for (i = 0; i < count - 1; i++) {
        ref_L18_0043F130_00(&points[i], &control[0], &control[1], &first, &second, IntToFloat(i) * inverse);
        if (i > 0 && i < count - 2) {
            jitter.f[3] = 0.0f;
            jitter.f[0] = RandomFloatRange(-1.0f, 1.0f);
            jitter.f[1] = RandomFloatRange(-1.0f, 1.0f);
            jitter.f[2] = RandomFloatRange(-1.0f, 1.0f);
            vec_scale_to_length(&jitter, &jitter, noise);
            FastVecAdd(&points[i], &points[i], &jitter);
        }
    }
    FastVecSub(&jitter, &points[count - 2], &points[count - 3]);
    FastVecAdd(&points[count - 1], &points[count - 2], &jitter);
}
