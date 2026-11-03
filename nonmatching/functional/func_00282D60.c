/* functional: high. Plain floats in place of VU0 vmulx.xyzw: all four lanes of a scaled by s. */
void func_00282D60(void *dst, void *a, float s)
{
    float *p = a, *d = dst;
    float r[4];
    int i;

    for (i = 0; i < 4; i++) {
        r[i] = p[i] * s;
    }
    for (i = 0; i < 4; i++) {
        d[i] = r[i];
    }
}
