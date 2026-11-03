/* functional: high. Plain floats in place of VU0 code, accumulating in its order; the last term is $vf0 (0, 0, 0, 1) times v.w, so w gains v.w and x, y, z gain 0 * v.w. Every input is read before dst is written. */

/* dst = m * v: dst[j] = m[0][j]*v.x + m[1][j]*v.y + m[2][j]*v.z (+ v.w on w), m three rows of four floats. */
void func_00283098(void *dst, void *v, void *m)
{
    float *p = v, *q = m, *d = dst;
    float r[4];
    int j;

    for (j = 0; j < 4; j++) {
        float acc = q[j] * p[0];
        acc = acc + q[4 + j] * p[1];
        acc = acc + q[8 + j] * p[2];
        r[j] = acc + (j == 3 ? 1.0f : 0.0f) * p[3];
    }
    for (j = 0; j < 4; j++) {
        d[j] = r[j];
    }
}
