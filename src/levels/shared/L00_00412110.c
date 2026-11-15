#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
/* Works out a smooth in-between point on a curve from a start point to an end point, given how far along it is. */
void func_L00_00412110(float *out, float *startPoint, float *endPoint, float *before, float *after, float amount)
{
    float t2, t3, cubicTerm, squareTerm, linearTerm;

    if (amount == 0.0f) {
        qcopy(out, startPoint);
        return;
    }
    if (amount == 1.0f) {
        qcopy(out, endPoint);
        return;
    }
    t2 = amount * amount;
    t3 = t2 * amount;

    cubicTerm = (after[0] - endPoint[0]) - (before[0] - startPoint[0]);
    squareTerm = (before[0] - startPoint[0]) - cubicTerm;
    linearTerm = endPoint[0] - before[0];
    out[0] = cubicTerm * t3 + squareTerm * t2 + linearTerm * amount + startPoint[0];

    cubicTerm = (after[1] - endPoint[1]) - (before[1] - startPoint[1]);
    squareTerm = (before[1] - startPoint[1]) - cubicTerm;
    linearTerm = endPoint[1] - before[1];
    out[1] = cubicTerm * t3 + squareTerm * t2 + linearTerm * amount + startPoint[1];

    cubicTerm = (after[2] - endPoint[2]) - (before[2] - startPoint[2]);
    squareTerm = (before[2] - startPoint[2]) - cubicTerm;
    linearTerm = endPoint[2] - before[2];
    out[2] = cubicTerm * t3 + squareTerm * t2 + linearTerm * amount + startPoint[2];
    out[3] = 0.0f;
}
