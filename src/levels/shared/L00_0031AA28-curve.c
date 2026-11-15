#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void math_l00_interpolate_cubic_vector(float *out, float *p1, float *p2, float *p0, float *p3, float ratio)
{
    float t_squared, t_cubed, cubic_coef, quad_coef, linear_coef;

    if (ratio == 0.0f) {
        qcopy(out, p1);
        return;
    }
    if (ratio == 1.0f) {
        qcopy(out, p2);
        return;
    }
    t_squared = ratio * ratio;
    t_cubed = t_squared * ratio;

    cubic_coef = (p3[0] - p2[0]) - (p0[0] - p1[0]);
    quad_coef = (p0[0] - p1[0]) - cubic_coef;
    linear_coef = p2[0] - p0[0];
    out[0] = cubic_coef * t_cubed + quad_coef * t_squared + linear_coef * ratio + p1[0];

    cubic_coef = (p3[1] - p2[1]) - (p0[1] - p1[1]);
    quad_coef = (p0[1] - p1[1]) - cubic_coef;
    linear_coef = p2[1] - p0[1];
    out[1] = cubic_coef * t_cubed + quad_coef * t_squared + linear_coef * ratio + p1[1];

    cubic_coef = (p3[2] - p2[2]) - (p0[2] - p1[2]);
    quad_coef = (p0[2] - p1[2]) - cubic_coef;
    linear_coef = p2[2] - p0[2];
    out[2] = cubic_coef * t_cubed + quad_coef * t_squared + linear_coef * ratio + p1[2];
    out[3] = 0.0f;
}
