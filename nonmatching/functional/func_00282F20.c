/* functional: high. Plain floats in place of VU0 code; the division by a zero length is skipped as retail does, and the unit vector keeps the source's w. */
extern float sqrtf(float);

static int zero_bits_00282F20(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i == 0;
}

/* Scale the xyz of the vector at src to length `length` into dst; a zero-length source gives zeros. The w of src is copied. */
void func_00282F20(void *dst, void *src, float length)
{
    float *d = dst, *s = src;
    float x = s[0], y = s[1], z = s[2], w = s[3];
    float len2 = x * x;
    len2 = len2 + y * y;
    len2 = len2 + z * z;
    if (zero_bits_00282F20(len2)) {
        d[0] = 0.0f;
        d[1] = 0.0f;
        d[2] = 0.0f;
    } else {
        float q = length / sqrtf(len2);
        d[0] = x * q;
        d[1] = y * q;
        d[2] = z * q;
    }
    d[3] = w;
}
