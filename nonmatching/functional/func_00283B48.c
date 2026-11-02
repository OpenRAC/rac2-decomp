/* functional: high. Plain floats in place of VU0 code. */

/* Blend of two matrices of three rows of four floats: dst = a*(1-t) + b*t, on all four lanes. */
void func_00283B48(void *dst, void *a, void *b, float t)
{
    float *d = dst, *p = a, *q = b;
    float inv = 1.0f - t;
    float o[12];
    int i;

    for (i = 0; i < 12; i++) {
        o[i] = p[i] * inv + q[i] * t;
    }
    for (i = 0; i < 12; i++) {
        d[i] = o[i];
    }
}
