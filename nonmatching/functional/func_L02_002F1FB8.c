/* functional: high. Plain floats in place of VU0 code: all four lanes subtracted, both inputs read before the store. */

/* out = a - b on all four lanes. */
void func_L02_002F1FB8(void *out, void *a, void *b)
{
    float *p = a, *q = b, *d = out;
    float r[4];
    int i;

    for (i = 0; i < 4; i++) {
        r[i] = p[i] - q[i];
    }
    for (i = 0; i < 4; i++) {
        d[i] = r[i];
    }
}
