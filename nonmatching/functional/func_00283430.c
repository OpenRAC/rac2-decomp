/* functional: high. Plain floats in place of VU0 and FPU code, in retail's order: sine and cosine by retail's odd polynomial (accumulated as x, then x^3, x^5, x^7, x^9 terms), the z, y, x rotations applied in that order, each skipped when its angle word is 0, and each 3x3 product accumulated as row*v.x + row*v.y + row*v.z over all four lanes as VU0 does. */

static float bits_00283430(unsigned int u)
{
    union {
        unsigned int i;
        float f;
    } c;
    c.i = u;
    return c.f;
}

/* Retail's sine: folds x into [-pi/2, pi/2] (x >= pi/2 -> pi - x; x < -pi/2 -> -pi - x), then an odd polynomial. */
static float sin_00283430(float x)
{
    float hp = bits_00283430(0x3FC90FDB);
    float pi = bits_00283430(0x40490FDB);
    float x2, x3, x5, x7, x9, acc;
    int lt_hp = x < hp;
    int lt_nhp = x < -hp;

    if (!lt_hp) {
        x = pi - x;
    }
    if (lt_nhp) {
        x = -pi - x;
    }
    x2 = x * x;
    x3 = x * x2;
    x5 = x3 * x2;
    x7 = x5 * x2;
    x9 = x7 * x2;
    acc = x + 0.0f;
    acc = acc + x3 * bits_00283430(0xBE2AAAA4);
    acc = acc + x5 * bits_00283430(0x3C08873E);
    acc = acc + x7 * bits_00283430(0xB94FB21F);
    return acc + x9 * bits_00283430(0x362E9C14);
}

/* m[i] = a*v.x + b*v.y + c*v.z on all four lanes, for rows 0..2 of m. */
static void rotate_00283430(float *m, const float *a, const float *b, const float *c)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        float v[4];
        for (j = 0; j < 4; j++) {
            v[j] = m[i * 4 + j];
        }
        for (j = 0; j < 4; j++) {
            float acc = a[j] * v[0];
            acc = acc + b[j] * v[1];
            m[i * 4 + j] = acc + c[j] * v[2];
        }
    }
}

/* Build the rotation matrix (4x4, rows of 16 bytes) for the angles x, y, z at angles: identity, then z, then y, then x. */
void func_00283430(void *m, void *angles)
{
    float r[16];
    float *d = m;
    unsigned int *aw = angles;
    float hp = bits_00283430(0x3FC90FDB);
    int i;

    for (i = 0; i < 16; i++) {
        r[i] = 0.0f;
    }
    r[0] = 1.0f;
    r[5] = 1.0f;
    r[10] = 1.0f;
    r[15] = 1.0f;

    if (aw[2] != 0) {
        float a = bits_00283430(aw[2]);
        float s = sin_00283430(a);
        float c = sin_00283430(a + hp);
        r[0] = 0.0f + c;
        r[1] = 0.0f + s;
        r[5] = 0.0f + c;
        r[4] = 0.0f - s;
    }
    if (aw[1] != 0) {
        float a = bits_00283430(aw[1]);
        float s = sin_00283430(a);
        float c = sin_00283430(a + hp);
        float p[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        float q[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        float t[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        p[0] = 0.0f + c;
        p[2] = 0.0f - s;
        q[1] = 0.0f + 1.0f;
        t[2] = 0.0f + c;
        t[0] = 0.0f + s;
        rotate_00283430(r, p, q, t);
    }
    if (aw[0] != 0) {
        float a = bits_00283430(aw[0]);
        float s = sin_00283430(a);
        float c = sin_00283430(a + hp);
        float p[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        float q[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        float t[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        p[0] = 0.0f + 1.0f;
        q[1] = 0.0f + c;
        q[2] = 0.0f + s;
        t[2] = 0.0f + c;
        t[1] = 0.0f - s;
        rotate_00283430(r, p, q, t);
    }
    for (i = 0; i < 16; i++) {
        d[i] = r[i];
    }
}
