/* functional: high. Plain floats in place of VU0 code: the series of odd and even powers is summed left to right as retail does. */
extern float D_001AC3E0[8];
extern float D_001AC400[16];

/* Angle of the pair (a, b) from a polynomial in min/max of their magnitudes; 0 when both are 0. The quadrant offsets come from the sign bits of a, b and |a| - |b|. */
float func_00283248(float a, float b)
{
    union {
        float f;
        unsigned int i;
    } ua, ub, ud, ux;
    float fa, fb;
    float lo, hi, x, x2, x4, x8, p1, p2, p3, p4, p5, p6, p7, sum;
    unsigned int s1, sb, sa;
    float *tab;
    float t[8];
    int i;

    ua.f = a;
    ub.f = b;
    ux.i = ua.i & 0x7FFFFFFF;
    fa = ux.f;
    ux.i = ub.i & 0x7FFFFFFF;
    fb = ux.f;
    ud.f = fa - fb;
    if ((int)ud.i < 0) {
        lo = fa;
        hi = fb;
    } else {
        lo = fb;
        hi = fa;
    }
    if (hi <= 0.0f) {
        return 0.0f;
    }
    x = (lo - hi) / (lo + hi);
    s1 = ud.i >> 31;
    sb = ub.i >> 31;
    sa = ua.i >> 31;
    tab = D_001AC400 + 2 * s1 + 4 * sb + 8 * sa;

    x2 = x * x;
    x4 = x2 * x2;
    x8 = x4 * x4;
    p1 = x * x2;
    p2 = x * x4;
    p3 = p2 * x2;
    t[0] = x * D_001AC3E0[0];
    t[1] = p1 * D_001AC3E0[1];
    t[2] = p2 * D_001AC3E0[2];
    t[3] = p3 * D_001AC3E0[3];
    t[4] = (x * x8) * D_001AC3E0[4];
    t[5] = (p1 * x8) * D_001AC3E0[5];
    t[6] = (p2 * x8) * D_001AC3E0[6];
    t[7] = (p3 * x8) * D_001AC3E0[7];
    sum = t[0] + t[1];
    for (i = 2; i < 8; i++) {
        sum = sum + t[i];
    }
    ux.i = 0x3F490FDB;
    return (ux.f + sum) * tab[0] + tab[1];
}
