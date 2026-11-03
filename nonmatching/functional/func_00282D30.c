/* functional: high. Plain floats in place of VU0 vmulx.xyz; the stored w is a's w word (retail stores the register loaded from a). */

/* dst.xyz = a.xyz * s, dst.w = a.w. */
void func_00282D30(void *dst, void *a, float s)
{
    float *p = a, *d = dst;
    float x = p[0] * s, y = p[1] * s, z = p[2] * s;
    unsigned int w = ((unsigned int *)a)[3];

    d[0] = x;
    d[1] = y;
    d[2] = z;
    ((unsigned int *)dst)[3] = w;
}
