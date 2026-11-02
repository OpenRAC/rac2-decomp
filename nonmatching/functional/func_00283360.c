/* functional: high. Plain floats in place of VU0 code built from $vf0 (0, 0, 0, 1). */

/* Writes the 3x4 identity rows (1,0,0,0), (0,1,0,0), (0,0,1,0). */
void func_00283360(float *m)
{
    int i;

    for (i = 0; i < 12; i++) {
        m[i] = 0.0f;
    }
    m[0] = 1.0f;
    m[5] = 1.0f;
    m[10] = 1.0f;
}
