#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
/* Works out a smooth in-between point on a curve from a start point to an end point, given how far along it is. */
void math_l00_interpolate_cubic_vector_2(float *out, float *start_point, float *end_point, float *before, float *after, float amount)
{
    float t2, t3, cubic_term, square_term, linear_term;

    if (amount == 0.0f) {
        qcopy(out, start_point);
        return;
    }
    if (amount == 1.0f) {
        qcopy(out, end_point);
        return;
    }
    t2 = amount * amount;
    t3 = t2 * amount;

    cubic_term = (after[0] - end_point[0]) - (before[0] - start_point[0]);
    square_term = (before[0] - start_point[0]) - cubic_term;
    linear_term = end_point[0] - before[0];
    out[0] = cubic_term * t3 + square_term * t2 + linear_term * amount + start_point[0];

    cubic_term = (after[1] - end_point[1]) - (before[1] - start_point[1]);
    square_term = (before[1] - start_point[1]) - cubic_term;
    linear_term = end_point[1] - before[1];
    out[1] = cubic_term * t3 + square_term * t2 + linear_term * amount + start_point[1];

    cubic_term = (after[2] - end_point[2]) - (before[2] - start_point[2]);
    square_term = (before[2] - start_point[2]) - cubic_term;
    linear_term = end_point[2] - before[2];
    out[2] = cubic_term * t3 + square_term * t2 + linear_term * amount + start_point[2];
    out[3] = 0.0f;
}
