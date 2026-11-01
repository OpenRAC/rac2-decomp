/* functional: high. Plain floats in place of VU0 code; the division and the float to integer conversion saturate as the vector unit does. */

static float div_00283D00(float a, float b)
{
    union {
        float f;
        unsigned int i;
    } ua, ub, r;
    ua.f = a;
    ub.f = b;
    if ((ub.i & 0x7FFFFFFF) == 0) {
        r.i = ((ua.i ^ ub.i) & 0x80000000) | 0x7F7FFFFF;
        return r.f;
    }
    return a / b;
}

/* Floating-point remainder of value by divisor, with the sign of value: (q - trunc(q)) * divisor for q = value / divisor. */
float func_00283D00(float value, float divisor)
{
    float q = 0.0f + div_00283D00(value, divisor);
    float t;

    if (q >= 2147483648.0f) {
        t = 2147483648.0f;
    } else if (q <= -2147483648.0f) {
        t = -2147483648.0f;
    } else {
        t = (float)(int)q;
    }
    return (q - t) * divisor;
}
