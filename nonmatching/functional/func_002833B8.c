/* functional: high. Plain floats in place of VU0 code. */

/* Writes a scale matrix (rows of four floats) at m: s on the first three diagonal places, 1 on the last. */
void func_002833B8(void *m, float s)
{
    float *d = m;
    int i;

    for (i = 0; i < 16; i++) {
        d[i] = 0.0f;
    }
    d[0] = s;
    d[5] = s;
    d[10] = s;
    d[15] = 1.0f;
}
