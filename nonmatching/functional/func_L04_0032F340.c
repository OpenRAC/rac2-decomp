/* functional: high. Plain floats in place of VU0 code, in its order: ACC = a*(1-t), then + b*t, on all four lanes; each matrix's a and b read whole before its rows are stored. */

/* Blend 23 4x4 matrices: dst[k] = a[k]*(1-t) + b[k]*t. */
void func_L04_0032F340(void *dst, void *a, void *b, float t)
{
    float *d = dst, *p = a, *q = b;
    float u = 1.0f - t;
    int k, i;

    for (k = 0; k < 23; k++) {
        float r[16], s[16];

        for (i = 0; i < 16; i++) {
            r[i] = p[i];
        }
        for (i = 0; i < 16; i++) {
            s[i] = q[i];
        }
        for (i = 0; i < 16; i++) {
            float acc = r[i] * u;
            r[i] = acc + s[i] * t;
        }
        for (i = 0; i < 16; i++) {
            d[i] = r[i];
        }
        d += 16;
        p += 16;
        q += 16;
    }
}
