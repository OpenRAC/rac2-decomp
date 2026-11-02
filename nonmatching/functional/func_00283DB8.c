/* functional: medium. Plain floats in place of VU0 code, in its order; the sign tests read the VU results' sign bits, here the IEEE sign bits. VU rounding is not reproduced, so a value within rounding of zero could take the other branch. Retail also leaves vf3.y (f*s - (Z - a)) for func_00283EB0, which carries its own copy of this test. */
extern float D_001B92C0[];

static int fneg_00283DB8(float v)
{
    union {
        float f;
        unsigned int u;
    } t;

    t.f = v;
    return (int)(t.u >> 31);
}

/* Sphere p (xyz centre, w radius) against the view volume in the table D_001B92C0 (rows 0-2 a 3x3 transform,
   row 3 the eye and in w the scale s, rows 4-7 the frustum slopes and limits): -1 outside, 0 crossing, 1 inside;
   f is the far distance. */
int func_00283DB8(void *v, float f)
{
    const float *T = D_001B92C0;
    float *p = v;
    float s = T[15];
    float ps[4];
    float u[3];
    float X, Y, Z, a, AX, AY;
    float v1x, v1y, v3x, v3y;
    float g_x, g_y;
    float v5x, v5y, v9x, v9y, v6x, v6y;
    float v7x, v7y, v8x, v8y, v4x, v4y;
    float v7ox, v7oy;
    float fy;
    int k;

    for (k = 0; k < 4; k++) {
        ps[k] = p[k] * s;
    }
    a = ps[3];
    for (k = 0; k < 3; k++) {
        u[k] = ps[k] - T[12 + k];
    }
    v3x = 0.0f + a;
    v3y = 0.0f - a;

    /* vf2.xyz = M * u, M = rows T0, T1, T2 (0x00, 0x10, 0x20) taken as columns. */
    X = (T[0] * u[0] + T[4] * u[1]) + T[8] * u[2];
    Y = (T[1] * u[0] + T[5] * u[1]) + T[9] * u[2];
    Z = (T[2] * u[0] + T[6] * u[1]) + T[10] * u[2];

    fy = f * s;
    g_x = T[24] * a;
    g_y = T[25] * a;
    v1x = v3x + Z;
    v1y = v3y + Z;
    v5x = T[16] * Z;
    v5y = T[17] * Z;
    AX = X < 0.0f ? -X : X;
    AY = Y < 0.0f ? -Y : Y;
    v7ox = g_x * T[26];
    v7oy = g_y * T[26];
    v3x = 0.0f - v1x;
    v3y = fy - v1y;
    v9x = v5x * T[20];
    v9y = v5y * T[21];
    v6x = AX - g_x;
    v6y = AY - g_y;
    v8x = AX + v7ox;
    v8y = AY + v7oy;
    v4x = v1x - T[28];
    v4y = v1y - T[29];
    v7x = v5x - v6x;
    v7y = v5y - v6y;
    v8x = v9x - v8x;
    v8y = v9y - v8y;

    if (fneg_00283DB8(v3y) || !fneg_00283DB8(v3x)) {
        return -1;
    }
    if (fneg_00283DB8(v7y) || fneg_00283DB8(v7x)) {
        return -1;
    }
    if (fneg_00283DB8(v8y) || fneg_00283DB8(v4y)) {
        return 0;
    }
    if (fneg_00283DB8(v8x) || !fneg_00283DB8(v4x)) {
        return 0;
    }
    return 1;
}
