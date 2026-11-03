/* functional: high. Plain floats in place of VU0 code: all sixteen floats scaled, the source read whole before the stores. */

/* dst = src (4x4) * scale. */
void func_L03_002EFB60(void *dst, void *src, float scale)
{
    float *s = src, *d = dst;
    float r[16];
    int i;

    for (i = 0; i < 16; i++) {
        r[i] = s[i];
    }
    for (i = 0; i < 16; i++) {
        r[i] = r[i] * scale;
    }
    for (i = 0; i < 16; i++) {
        d[i] = r[i];
    }
}
