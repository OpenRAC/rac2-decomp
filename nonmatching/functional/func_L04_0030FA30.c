/* functional: high. Plain floats in place of VU0 code: both 4x4 inputs read whole before the stores. */

/* dst = a + b, 4x4, all lanes. */
void func_L04_0030FA30(void *dst, void *a, void *b)
{
    float *p = a, *q = b, *d = dst;
    float r[16], s[16];
    int i;

    for (i = 0; i < 16; i++) {
        r[i] = p[i];
    }
    for (i = 0; i < 16; i++) {
        s[i] = q[i];
    }
    for (i = 0; i < 16; i++) {
        r[i] = r[i] + s[i];
    }
    for (i = 0; i < 16; i++) {
        d[i] = r[i];
    }
}
