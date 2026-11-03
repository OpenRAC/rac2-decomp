/* functional: high. Plain floats in place of VU0 code, in its order: the differences, their squares, (x + y) in ACC, then + z * 1. */

/* Squared distance between the xyz of a and b. */
float func_00282EB0(void *a, void *b)
{
    float *p = a, *q = b;
    float x = p[0] - q[0], y = p[1] - q[1], z = p[2] - q[2];
    float s;

    x = x * x;
    y = y * y;
    z = z * z;
    s = x + y;
    return s + 1.0f * z;
}
