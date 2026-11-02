/* functional: high. Plain floats in place of VU0 code. */

/* Transposes the 3x3 part of the matrix at src (rows of four floats) into dst; the w of every row is 0 and the fourth row is 0 0 0 1. */
void func_00283698(void *dst, void *src)
{
    float *d = dst, *s = src;
    float a[3][3];
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            a[i][j] = s[i * 4 + j];
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            d[i * 4 + j] = a[j][i];
        }
        d[i * 4 + 3] = 0.0f;
    }
    d[12] = 0.0f;
    d[13] = 0.0f;
    d[14] = 0.0f;
    d[15] = 1.0f;
}
