#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void func_L00_003A2018(float *out, float *from, float *to, float *before, float *after, float t)
{
    float tSquared, tCubed, cubicTerm, squareTerm, linearTerm;

    if (t == 0.0f) {
        qcopy(out, from);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, to);
        return;
    }
    tSquared = t * t;
    tCubed = tSquared * t;

    cubicTerm = (after[0] - to[0]) - (before[0] - from[0]);
    squareTerm = (before[0] - from[0]) - cubicTerm;
    linearTerm = to[0] - before[0];
    out[0] = cubicTerm * tCubed + squareTerm * tSquared + linearTerm * t + from[0];

    cubicTerm = (after[1] - to[1]) - (before[1] - from[1]);
    squareTerm = (before[1] - from[1]) - cubicTerm;
    linearTerm = to[1] - before[1];
    out[1] = cubicTerm * tCubed + squareTerm * tSquared + linearTerm * t + from[1];

    cubicTerm = (after[2] - to[2]) - (before[2] - from[2]);
    squareTerm = (before[2] - from[2]) - cubicTerm;
    linearTerm = to[2] - before[2];
    out[2] = cubicTerm * tCubed + squareTerm * tSquared + linearTerm * t + from[2];
    out[3] = 0.0f;
}
