#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void math_l00_interpolate_cubic_curve(float *out, float *start, float *end, float *startTangent, float *endTangent, float amount)
{
    float tSquared, tCubed, cubicTerm, squareTerm, linearTerm;

    if (amount == 0.0f) {
        qcopy(out, start);
        return;
    }
    if (amount == 1.0f) {
        qcopy(out, end);
        return;
    }
    tSquared = amount * amount;
    tCubed = tSquared * amount;

    cubicTerm = (endTangent[0] - end[0]) - (startTangent[0] - start[0]);
    squareTerm = (startTangent[0] - start[0]) - cubicTerm;
    linearTerm = end[0] - startTangent[0];
    out[0] = cubicTerm * tCubed + squareTerm * tSquared + linearTerm * amount + start[0];

    cubicTerm = (endTangent[1] - end[1]) - (startTangent[1] - start[1]);
    squareTerm = (startTangent[1] - start[1]) - cubicTerm;
    linearTerm = end[1] - startTangent[1];
    out[1] = cubicTerm * tCubed + squareTerm * tSquared + linearTerm * amount + start[1];

    cubicTerm = (endTangent[2] - end[2]) - (startTangent[2] - start[2]);
    squareTerm = (startTangent[2] - start[2]) - cubicTerm;
    linearTerm = end[2] - startTangent[2];
    out[2] = cubicTerm * tCubed + squareTerm * tSquared + linearTerm * amount + start[2];
    out[3] = 0.0f;
}
