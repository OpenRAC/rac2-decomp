/* functional: high. Plain floats in place of VU0 code, accumulating in the assembly's order. */

/* dst = vector at v (x y z w) times the 4x4 matrix at m (rows of four floats): row0*x + row1*y + row2*z + row3*w. */
void func_002830C0(void *dst, void *v, void *m)
{
    float *d = dst, *p = v, *r = m;
    float x = p[0], y = p[1], z = p[2], w = p[3];
    float o[4];
    int i;

    for (i = 0; i < 4; i++) {
        float acc = r[i] * x;
        acc = acc + r[4 + i] * y;
        acc = acc + r[8 + i] * z;
        o[i] = acc + r[12 + i] * w;
    }
    for (i = 0; i < 4; i++) {
        d[i] = o[i];
    }
}
