/* functional: high. Plain floats in place of VU0 code: the three rows are read before any is written, and each element is 0 plus the source as VU0's vadd computes it. */

/* out = the transpose of in's upper 3x3, rows of four floats with w = 0. */
void func_002836E8(float *out, float *in)
{
    float r[12];
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            r[i * 4 + j] = 0.0f + in[j * 4 + i];
        }
        r[i * 4 + 3] = 0.0f;
    }
    for (i = 0; i < 12; i++) {
        out[i] = r[i];
    }
}
