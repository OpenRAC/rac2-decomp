/* functional: high. Plain floats and shifts in place of VU0 and MMI code; the bytes are scaled by 16, truncated, rounded by 2 and shifted down as 16-bit lanes the way retail packs them. */

static int ftoi_00280A70(float f)
{
    if (f >= 2147483648.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)0x80000000;
    }
    return (int)f;
}

/* Blend of two records at a and b by weight t into dst: floats 0-5 (a row of four, then two) are a*(1-t) + b*t; the four colour bytes at +24 are blended the same way and written back as bytes. The word after them (+28) is copied from a. */
void func_00280A70(void *dst, void *a, void *b, float t)
{
    float *d = dst, *p = a, *q = b;
    unsigned char *ca = (unsigned char *)a + 24, *cb = (unsigned char *)b + 24;
    float inv = 1.0f - t;
    float o[6], c[4];
    unsigned int packed = 0;
    float tail = p[7];
    int i;

    for (i = 0; i < 4; i++) {
        c[i] = (float)ca[i] * inv + (float)cb[i] * t;
    }
    for (i = 0; i < 6; i++) {
        o[i] = p[i] * inv + q[i] * t;
    }
    for (i = 0; i < 4; i++) {
        unsigned int h = (unsigned int)ftoi_00280A70(c[i] * 16.0f) & 0xFFFF;
        h = ((h + 2) & 0xFFFF) >> 4;
        packed |= (h & 0xFF) << (i * 8);
    }
    for (i = 0; i < 6; i++) {
        d[i] = o[i];
    }
    ((unsigned int *)dst)[6] = packed;
    d[7] = tail;
}
