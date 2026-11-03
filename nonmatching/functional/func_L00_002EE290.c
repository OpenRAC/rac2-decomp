/* functional: high. Plain floats in place of VU0 code, in its order: (x*x + y*y) + 1*(z*z). */

/* Squared length of the xyz of v. */
float func_L00_002EE290(void *v)
{
    float *p = v;
    float x = p[0] * p[0], y = p[1] * p[1], z = p[2] * p[2];
    float acc = x + y;
    return acc + 1.0f * z;
}
