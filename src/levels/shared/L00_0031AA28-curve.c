#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void func_L00_0031AA28(float *out, float *p1, float *p2, float *p0, float *p3, float ratio)
{
    float tSquared, tCubed, cubicCoef, quadCoef, linearCoef;

    if (ratio == 0.0f) {
        qcopy(out, p1);
        return;
    }
    if (ratio == 1.0f) {
        qcopy(out, p2);
        return;
    }
    tSquared = ratio * ratio;
    tCubed = tSquared * ratio;

    cubicCoef = (p3[0] - p2[0]) - (p0[0] - p1[0]);
    quadCoef = (p0[0] - p1[0]) - cubicCoef;
    linearCoef = p2[0] - p0[0];
    out[0] = cubicCoef * tCubed + quadCoef * tSquared + linearCoef * ratio + p1[0];

    cubicCoef = (p3[1] - p2[1]) - (p0[1] - p1[1]);
    quadCoef = (p0[1] - p1[1]) - cubicCoef;
    linearCoef = p2[1] - p0[1];
    out[1] = cubicCoef * tCubed + quadCoef * tSquared + linearCoef * ratio + p1[1];

    cubicCoef = (p3[2] - p2[2]) - (p0[2] - p1[2]);
    quadCoef = (p0[2] - p1[2]) - cubicCoef;
    linearCoef = p2[2] - p0[2];
    out[2] = cubicCoef * tCubed + quadCoef * tSquared + linearCoef * ratio + p1[2];
    out[3] = 0.0f;
}
