#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00283248(float, float);

extern float func_002A7878(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

/* Places the output point at a given distance from a source point, with a small random change in direction, distance and height. */
void func_L02_003D5E40(float *out, TI128 *src, float dist, float ang_jit, float dist_jit, float z_jit) {
    TI128 vec = *src;
    TI128 *p = &vec;
    float *v = (float *)&vec;
    float ang;

    ang = FastMatrixHelperA(out[0] - v[0], out[1] - v[1]);
    ang_jit *= 0.017453294f;
    ang += RandomFloatRange(-ang_jit, ang_jit);
    dist += RandomFloatRange(-dist_jit, dist_jit);
    qcopy(out, p);
    out[0] += dist * FastSinOrCosA(ang);
    out[1] += dist * FastSinOrCosB(ang);
    out[2] = v[2] + RandomFloatRange(-z_jit, z_jit);
}
