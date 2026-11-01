/* functional: high. Plain floats in place of VU0 code; the sign test reads the sign bit, so -0.0 counts as negative. */

static int negative_00283D80(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

/* 1 when the weighted sum (p - q) . w over xyz is not negative, else 0. */
int func_00283D80(void *p, void *q, void *w)
{
    float *a = p, *b = q, *c = w;
    float s = (a[0] - b[0]) * c[0];
    s = s + (a[1] - b[1]) * c[1];
    s = s + (a[2] - b[2]) * c[2];
    return negative_00283D80(s) ? 0 : 1;
}
