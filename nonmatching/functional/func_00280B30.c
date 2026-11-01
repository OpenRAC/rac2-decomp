/* functional: medium. Plain floats in place of VU0 code; a zero-length segment gives the vector unit's largest float for the ratio, as retail's divide does. */

static float div_00280B30(float a, float b)
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

/* Closest point on the segment p1 -> p2 to the point p3 (xyz; w from p1) into dst. Returns the unclamped ratio along the segment. */
float func_00280B30(void *dst, void *p1, void *p2, void *p3)
{
    float *d = dst, *a = p1, *b = p2, *c = p3;
    float ex = b[0] - a[0], ey = b[1] - a[1], ez = b[2] - a[2];
    float fx = c[0] - a[0], fy = c[1] - a[1], fz = c[2] - a[2];
    float ee = ex * ex;
    float ef = ex * fx;
    float q, t;

    ee = ee + ey * ey;
    ee = ee + ez * ez;
    ef = ef + ey * fy;
    ef = ef + ez * fz;
    q = 0.0f + div_00280B30(ef, ee);
    t = q < 1.0f ? q : 1.0f;
    t = t > 0.0f ? t : 0.0f;
    d[0] = ex * t + a[0];
    d[1] = ey * t + a[1];
    d[2] = ez * t + a[2];
    d[3] = a[3];
    return q;
}
