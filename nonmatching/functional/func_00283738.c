/* functional: high. Plain floats in place of VU0 code, accumulating in the assembly's order. */

/* dst = b times a for three rows of four floats: row i of dst = a0*b[i].x + a1*b[i].y + a2*b[i].z, on all four lanes. */
void func_00283738(void *dst, void *a, void *b)
{
    float *d = dst, *p = a, *q = b;
    float o[12];
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            float acc = p[j] * q[i * 4];
            acc = acc + p[4 + j] * q[i * 4 + 1];
            o[i * 4 + j] = acc + p[8 + j] * q[i * 4 + 2];
        }
    }
    for (i = 0; i < 12; i++) {
        d[i] = o[i];
    }
}
