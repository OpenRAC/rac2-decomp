/* functional: high. Plain floats in place of VU0 code, in its order: dx*dx + dy*dy. */

/* Squared distance in xy between a and b. */
float func_L02_002F21C0(void *a, void *b)
{
    float *p = a, *q = b;
    float dx = p[0] - q[0], dy = p[1] - q[1];

    dx = dx * dx;
    dy = dy * dy;
    return dx + dy;
}
