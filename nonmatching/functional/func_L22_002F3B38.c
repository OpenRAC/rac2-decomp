/* functional: high. Plain floats in place of VU0 code; the stored w is a's w word (retail stores the register loaded from a). */

/* out.xyz = a.xyz * b.xyz, out.w = a.w. */
void func_L22_002F3B38(void *out, void *a, void *b)
{
    float *p = a, *q = b, *d = out;
    unsigned int w = ((unsigned int *)a)[3];
    float r[3];
    int i;

    for (i = 0; i < 3; i++) {
        r[i] = p[i] * q[i];
    }
    d[0] = r[0];
    d[1] = r[1];
    d[2] = r[2];
    ((unsigned int *)out)[3] = w;
}
