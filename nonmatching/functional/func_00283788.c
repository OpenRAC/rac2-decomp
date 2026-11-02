/* functional: high. Plain floats in place of VU0 code, accumulating in its order. As retail does, a is read whole first, then each row of b is read and the matching row of dst written before the next row of b is read. */

/* dst = a times b, 4x4: row i of dst = a0*b[i].x + a1*b[i].y + a2*b[i].z + a3*b[i].w, on all four lanes. */
void func_00283788(void *dst, void *a, void *b)
{
    float *d = dst, *q = b;
    float m[16];
    int i, j;

    for (i = 0; i < 16; i++) {
        m[i] = ((float *)a)[i];
    }
    for (i = 0; i < 4; i++) {
        float v[4];
        float r[4];

        for (j = 0; j < 4; j++) {
            v[j] = q[i * 4 + j];
        }
        for (j = 0; j < 4; j++) {
            float acc = m[j] * v[0];
            acc = acc + m[4 + j] * v[1];
            acc = acc + m[8 + j] * v[2];
            r[j] = acc + m[12 + j] * v[3];
        }
        for (j = 0; j < 4; j++) {
            d[i * 4 + j] = r[j];
        }
    }
}
