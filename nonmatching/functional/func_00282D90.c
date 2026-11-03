/* functional: high. Plain floats in place of VU0 code: Q = 1 / f (vdiv), then xyz * Q; the stored w is a's w word (retail stores the register loaded from a). The VU's divide by zero gives the largest finite float with the sign of f, and its products saturate there; both are written out so the host makes no infinity. */

static float clampf_00282D90(float v)
{
    if (v > 3.40282347e38f) {
        return 3.40282347e38f;
    }
    if (v < -3.40282347e38f) {
        return -3.40282347e38f;
    }
    return v;
}

/* dst.xyz = a.xyz / f (as a.xyz * (1 / f)), dst.w = a.w. */
void func_00282D90(void *dst, void *a, float f)
{
    float *p = a, *d = dst;
    union {
        float f;
        unsigned int u;
    } b;
    float q, x, y, z;
    unsigned int w = ((unsigned int *)a)[3];

    b.f = f;
    if ((b.u & 0x7FFFFFFFu) == 0) {
        q = (b.u >> 31) ? -3.40282347e38f : 3.40282347e38f;
    } else {
        q = 1.0f / f;
    }
    x = clampf_00282D90(p[0] * q);
    y = clampf_00282D90(p[1] * q);
    z = clampf_00282D90(p[2] * q);
    d[0] = x;
    d[1] = y;
    d[2] = z;
    ((unsigned int *)dst)[3] = w;
}
