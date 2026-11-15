#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void vec_l00_interpolate_cubic(float *out, float *from, float *to, float *before, float *after, float t)
{
    float t_squared, t_cubed, cubic_term, square_term, linear_term;

    if (t == 0.0f) {
        qcopy(out, from);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, to);
        return;
    }
    t_squared = t * t;
    t_cubed = t_squared * t;

    cubic_term = (after[0] - to[0]) - (before[0] - from[0]);
    square_term = (before[0] - from[0]) - cubic_term;
    linear_term = to[0] - before[0];
    out[0] = cubic_term * t_cubed + square_term * t_squared + linear_term * t + from[0];

    cubic_term = (after[1] - to[1]) - (before[1] - from[1]);
    square_term = (before[1] - from[1]) - cubic_term;
    linear_term = to[1] - before[1];
    out[1] = cubic_term * t_cubed + square_term * t_squared + linear_term * t + from[1];

    cubic_term = (after[2] - to[2]) - (before[2] - from[2]);
    square_term = (before[2] - from[2]) - cubic_term;
    linear_term = to[2] - before[2];
    out[2] = cubic_term * t_cubed + square_term * t_squared + linear_term * t + from[2];
    out[3] = 0.0f;
}
