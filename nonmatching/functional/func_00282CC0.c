/* functional: high. Plain floats in place of VU0 vadd.xyz; the stored w is a's w word, copied as a word (retail stores the whole register loaded from a). */

/* dst.xyz = a.xyz + b.xyz, dst.w = a.w. */
void func_00282CC0(void *dst, void *a, void *b)
{
    float *p = a, *q = b, *d = dst;
    float x = p[0] + q[0], y = p[1] + q[1], z = p[2] + q[2];
    unsigned int w = ((unsigned int *)a)[3];

    d[0] = x;
    d[1] = y;
    d[2] = z;
    ((unsigned int *)dst)[3] = w;
}
