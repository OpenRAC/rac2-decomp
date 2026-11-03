/* functional: high. Plain floats in place of VU0 code, in its order (row i of dst = a0*b_i.x + a1*b_i.y + a2*b_i.z on all four lanes); a and b are read whole first, then dst's three w words, then the rows are stored and the w words put back, as retail. */

/* 3x3 rotation product: dst rows 0-2 = b's rows times a's rows; dst's w words (+12, +28, +44) are kept. */
void func_L02_002F2B88(void *dst, void *a, void *b)
{
    float *m = a, *n = b, *d = dst;
    float am[12], bm[12], r[12];
    unsigned int w0, w1, w2;
    int i, j;

    for (i = 0; i < 12; i++) {
        am[i] = m[i];
    }
    for (i = 0; i < 12; i++) {
        bm[i] = n[i];
    }
    w0 = ((unsigned int *)dst)[3];
    w1 = ((unsigned int *)dst)[7];
    w2 = ((unsigned int *)dst)[11];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            float acc = am[j] * bm[i * 4];
            acc = acc + am[4 + j] * bm[i * 4 + 1];
            r[i * 4 + j] = acc + am[8 + j] * bm[i * 4 + 2];
        }
    }
    for (i = 0; i < 12; i++) {
        d[i] = r[i];
    }
    ((unsigned int *)dst)[3] = w0;
    ((unsigned int *)dst)[7] = w1;
    ((unsigned int *)dst)[11] = w2;
}
