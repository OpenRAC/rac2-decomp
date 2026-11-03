/* functional: high. Plain floats in place of VU0 code, in its order. The sine and cosine are retail's register helper func_001291A0 (inlined here, as it has no C ABI): angle a folded to t = pi/2 - a (a >= 0) or pi/2 + a (a < 0), cos a = t + c.w t^3 + c.z t^5 + c.y t^7 + c.x t^9 from the D_00137EA0 coefficients, sin a = +-sqrt(|1 - cos^2|) (VU0 vsqrt takes the absolute value) with a's sign. The matrix product is row i of dst = r0*v.x + r1*v.y + r2*v.z + r3*v.w on all four lanes, each source row read before its dst row is written. */
extern float D_00137EA0[4];
extern float sqrtf(float);

/* r[0] = sin a, r[1] = cos a, as retail's func_001291A0 computes them. */
static void sincos_00129368(float a, float *r)
{
    float hp;
    float t, t2, s, x, y, z, w, q;
    int neg;
    union {
        unsigned int i;
        float f;
    } u;

    u.i = 0x3FC90FDB;
    hp = u.f;
    if (a < 0.0f) {
        t = hp + a;
        neg = 1;
    } else {
        t = hp - a;
        neg = 0;
    }
    s = 0.0f + t;
    t2 = t * t;
    x = D_00137EA0[0] * t;
    y = D_00137EA0[1] * t;
    z = D_00137EA0[2] * t;
    w = D_00137EA0[3] * t;
    x = x * t2;
    y = y * t2;
    z = z * t2;
    w = w * t2;
    x = x * t2;
    y = y * t2;
    z = z * t2;
    x = x * t2;
    y = y * t2;
    x = x * t2;
    s = s + w;
    s = s + z;
    s = s + y;
    s = s + x;
    q = 1.0f - s * s;
    if (q < 0.0f) {
        q = -q;
    }
    q = 0.0f + sqrtf(q);
    r[1] = 0.0f + s;
    r[0] = neg ? 0.0f - q : 0.0f + q;
}

/* Rotation about y (libvu0 sceVu0RotMatrixY): dst = src (4x4, rows) times (c, 0, -s, 0), (0, 1, 0, 0), (s, 0, c, 0), (0, 0, 0, 1). */
void func_00129368(void *dst, void *src, float angle)
{
    float *d = dst, *m = src;
    float sc[2];
    float s, c;
    int i, j;

    sincos_00129368(angle, sc);
    s = sc[0];
    c = sc[1];
    {
        float r0[4] = { 0.0f, 0.0f, 0.0f, 0.0f }, r1[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        float r2[4] = { 0.0f, 0.0f, 0.0f, 0.0f }, r3[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

        r1[1] = 0.0f + 1.0f;
        r3[3] = 0.0f + 1.0f;
        r0[2] = 0.0f - s;
        r0[0] = 0.0f + c;
        r2[0] = 0.0f + s;
        r2[2] = 0.0f + c;
        for (i = 0; i < 4; i++) {
            float v[4];
            float o[4];

            for (j = 0; j < 4; j++) {
                v[j] = m[i * 4 + j];
            }
            for (j = 0; j < 4; j++) {
                float acc = r0[j] * v[0];
                acc = acc + r1[j] * v[1];
                acc = acc + r2[j] * v[2];
                o[j] = acc + r3[j] * v[3];
            }
            for (j = 0; j < 4; j++) {
                d[i * 4 + j] = o[j];
            }
        }
    }
}
