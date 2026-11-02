/* functional: high. Plain floats in place of VU0 code. */

/* Writes the 4x4 identity matrix (rows of four floats) at m. */
void func_00283388(void *m)
{
    float *d = m;
    int i;

    for (i = 0; i < 16; i++) {
        d[i] = 0.0f;
    }
    d[0] = 1.0f;
    d[5] = 1.0f;
    d[10] = 1.0f;
    d[15] = 1.0f;
}
