#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void math_l00_interpolate_cubic_curve(float *out, float *start, float *end, float *start_tangent, float *end_tangent, float amount)
{
    float t_squared, t_cubed, cubic_term, square_term, linear_term;

    if (amount == 0.0f) {
        qcopy(out, start);
        return;
    }
    if (amount == 1.0f) {
        qcopy(out, end);
        return;
    }
    t_squared = amount * amount;
    t_cubed = t_squared * amount;

    cubic_term = (end_tangent[0] - end[0]) - (start_tangent[0] - start[0]);
    square_term = (start_tangent[0] - start[0]) - cubic_term;
    linear_term = end[0] - start_tangent[0];
    out[0] = cubic_term * t_cubed + square_term * t_squared + linear_term * amount + start[0];

    cubic_term = (end_tangent[1] - end[1]) - (start_tangent[1] - start[1]);
    square_term = (start_tangent[1] - start[1]) - cubic_term;
    linear_term = end[1] - start_tangent[1];
    out[1] = cubic_term * t_cubed + square_term * t_squared + linear_term * amount + start[1];

    cubic_term = (end_tangent[2] - end[2]) - (start_tangent[2] - start[2]);
    square_term = (start_tangent[2] - start[2]) - cubic_term;
    linear_term = end[2] - start_tangent[2];
    out[2] = cubic_term * t_cubed + square_term * t_squared + linear_term * amount + start[2];
    out[3] = 0.0f;
}
