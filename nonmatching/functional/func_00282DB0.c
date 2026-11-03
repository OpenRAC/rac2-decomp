/* functional: high. Plain floats in place of VU0 code, in its order: the products, then (x + y) in ACC, then + z * 1. */

/* Dot product of the xyz of a and b. */
float func_00282DB0(void *a, void *b)
{
    float *p = a, *q = b;
    float x = p[0] * q[0], y = p[1] * q[1], z = p[2] * q[2];
    float s = x + y;

    return s + 1.0f * z;
}
