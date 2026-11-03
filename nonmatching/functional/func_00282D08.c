/* functional: high. Plain floats in place of VU0 code, in its order: (to - from) * t, then from plus that; the stored w is from's w word (retail stores the register loaded from from). */

/* out.xyz = from + (to - from) * t, out.w = from.w. */
void func_00282D08(void *out, void *from, void *to, float t)
{
    float *p = from, *q = to, *d = out;
    float r[3];
    unsigned int w = ((unsigned int *)from)[3];
    int i;

    for (i = 0; i < 3; i++) {
        float s = q[i] - p[i];
        s = s * t;
        r[i] = p[i] + s;
    }
    d[0] = r[0];
    d[1] = r[1];
    d[2] = r[2];
    ((unsigned int *)out)[3] = w;
}
