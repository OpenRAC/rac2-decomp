#include "common.h"

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void func_L11_00472090(float *out, float *b, float *c, float *a, float *d, float t)
{
    float t2, t3, p, q, r;

    if (t == 0.0f) {
        qcopy(out, b);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, c);
        return;
    }
    t2 = t * t;
    t3 = t2 * t;

    p = (d[0] - c[0]) - (a[0] - b[0]);
    q = (a[0] - b[0]) - p;
    r = c[0] - a[0];
    out[0] = p * t3 + q * t2 + r * t + b[0];

    p = (d[1] - c[1]) - (a[1] - b[1]);
    q = (a[1] - b[1]) - p;
    r = c[1] - a[1];
    out[1] = p * t3 + q * t2 + r * t + b[1];

    p = (d[2] - c[2]) - (a[2] - b[2]);
    q = (a[2] - b[2]) - p;
    r = c[2] - a[2];
    out[2] = p * t3 + q * t2 + r * t + b[2];
    out[3] = 0.0f;
}
