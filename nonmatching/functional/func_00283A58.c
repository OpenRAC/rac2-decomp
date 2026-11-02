/* functional: high. Plain floats in place of VU0 code, in the assembly's order of operations. */

/* Four rows of four floats at dst from the quaternion q (x y z w), the scale s (x y z) and the position t (x y z): the rotation matrix's rows scaled by s.x, s.y, s.z, then t with w = 1. */
void func_00283A58(void *q, void *s, void *t, void *dst)
{
    float *d = dst, *qq = q, *sc = s, *tt = t;
    float x = qq[0], y = qq[1], z = qq[2], w = qq[3];
    float x2 = x + x, y2 = y + y, z2 = z + z;
    float xw = x2 * w, yw = y2 * w, zw = z2 * w;
    float xx = x2 * x, yx = y2 * x, zx = z2 * x;
    float yy = y2 * y, zy = z2 * y;
    float zz = z2 * z;
    float sx = sc[0], sy = sc[1], sz = sc[2];
    float tx = tt[0], ty = tt[1], tz = tt[2];
    float r0[3], r1[3], r2[3];
    int i;

    r0[0] = (1.0f - yy) - zz;
    r0[1] = yx - zw;
    r0[2] = zx + yw;
    r1[0] = (0.0f + zw) + yx;
    r1[1] = (1.0f - xx) - zz;
    r1[2] = zy - xw;
    r2[0] = (0.0f - yw) + zx;
    r2[1] = (0.0f + xw) + zy;
    r2[2] = (1.0f - xx) - yy;
    for (i = 0; i < 3; i++) {
        d[i] = r0[i] * sx;
        d[4 + i] = r1[i] * sy;
        d[8 + i] = r2[i] * sz;
    }
    d[3] = 0.0f;
    d[7] = 0.0f;
    d[11] = 0.0f;
    d[12] = tx;
    d[13] = ty;
    d[14] = tz;
    d[15] = 1.0f;
}
