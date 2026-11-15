#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float mat_fast_helper_a(float, float);

extern float math_random_float_range(float, float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

/* Places the output point at a given distance from a source point, with a small random change in direction, distance and height. */
void PlacePointWithPolarJitter(float *out, TI128 *src, float dist, float ang_jit, float dist_jit, float z_jit) {
    TI128 vec = *src;
    TI128 *p = &vec;
    float *v = (float *)&vec;
    float ang;

    ang = mat_fast_helper_a(out[0] - v[0], out[1] - v[1]);
    ang_jit *= 0.017453294f;
    ang += math_random_float_range(-ang_jit, ang_jit);
    dist += math_random_float_range(-dist_jit, dist_jit);
    qcopy(out, p);
    out[0] += dist * math_fast_sin_or_cos_a(ang);
    out[1] += dist * math_fast_sin_or_cos_b(ang);
    out[2] = v[2] + math_random_float_range(-z_jit, z_jit);
}
