#include "common.h"

/* Samples the cubic segment, adds jitter only to interior points, then
 * extrapolates its final point. The retail contract requires count >= 3,
 * count aligned 16-byte output vectors and four aligned control vectors. */
typedef int Vec128_00414660 __attribute__((mode(TI)));
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
/* The five-pointer/one-FP interpolation leaf differs between programs. */
extern void ref_L11_003F4198_00(void *, void *, void *, void *, void *, float);

/* Builds a wobbly curve: fills in points along a smooth curve and nudges the middle ones at random. */
void curve_build_jittered_points_alt(float (*points)[4], int count, float (*control)[4], float displacement)
{
    float before[4] __attribute__((aligned(16)));
    float after[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float step;
    int i;
    qcopy(before, control[2]);
    FastVecAdd(before, before, control[0]);
    qcopy(after, control[3]);
    FastVecAdd(after, after, control[1]);
    step = 1.0f / IntToFloat(count - 2);
    for (i = 0; i < count - 1; i++) {
        ref_L11_003F4198_00(points[i], control[0], control[1], before, after, IntToFloat(i) * step);
        if (i > 0 && i < count - 2) {
            offset[3] = 0.0f;
            offset[0] = math_random_float_range(-1.0f, 1.0f);
            offset[1] = math_random_float_range(-1.0f, 1.0f);
            offset[2] = math_random_float_range(-1.0f, 1.0f);
            vec_scale_to_length(offset, offset, displacement);
            FastVecAdd(points[i], points[i], offset);
        }
    }
    FastVecSub(offset, points[count - 2], points[count - 3]);
    FastVecAdd(points[count - 1], points[count - 2], offset);
}
