/* functional: high. Plain C in place of lq/sq and the store of $vf0: the first three rows (three quadwords) are read before any is written, copied as words, and the fourth row is (0, 0, 0, 1). */
void func_00283658(void *dst, void *src)
{
    unsigned int *s = src, *d = dst;
    unsigned int r[12];
    int i;

    for (i = 0; i < 12; i++) {
        r[i] = s[i];
    }
    for (i = 0; i < 12; i++) {
        d[i] = r[i];
    }
    ((float *)dst)[12] = 0.0f;
    ((float *)dst)[13] = 0.0f;
    ((float *)dst)[14] = 0.0f;
    ((float *)dst)[15] = 1.0f;
}
