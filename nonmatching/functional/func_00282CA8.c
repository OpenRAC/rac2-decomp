/* functional: high. Plain floats in place of VU0 vadd.xyzw: both vectors read before the four lanes are written. */
void func_00282CA8(void *dst, void *a, void *b)
{
    float *p = a, *q = b, *d = dst;
    float r[4];
    int i;

    for (i = 0; i < 4; i++) {
        r[i] = p[i] + q[i];
    }
    for (i = 0; i < 4; i++) {
        d[i] = r[i];
    }
}
