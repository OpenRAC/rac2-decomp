/* functional: high. Plain floats in place of VU0 code, in its order: VU0 vsqrt takes the absolute value (x*x + y*y is never negative, so sqrt of it as is); retail's two tests are on register bits: the 64-bit word holding lanes x (the length) and y (y*y) both zero, and the word of max - length as a signed integer positive. The stored quadword keeps v's z and w. */
extern float sqrtf(float);

/* Clamp the xy length of v to max: when |v.xy| is nonzero and not below max, out = v with xy scaled by max / |v.xy| and
   return 1; otherwise return 0 and leave out alone. */
int func_L00_002EE4D8(void *out, void *v, float max)
{
    float *p = v;
    float x = p[0], y = p[1];
    float x2 = x * x, y2 = y * y;
    float len, d, q;
    unsigned int zw[4];
    union {
        float f;
        int i;
    } a, b, c;

    zw[2] = ((unsigned int *)v)[2];
    zw[3] = ((unsigned int *)v)[3];
    x2 = x2 + y2;
    len = 0.0f + sqrtf(x2);
    d = max - len;
    a.f = len;
    c.f = y2;
    if (a.i == 0 && c.i == 0) {
        return 0;
    }
    b.f = d;
    if (b.i > 0) {
        return 0;
    }
    q = max / len;
    ((float *)out)[0] = x * q;
    ((float *)out)[1] = y * q;
    ((unsigned int *)out)[2] = zw[2];
    ((unsigned int *)out)[3] = zw[3];
    return 1;
}
