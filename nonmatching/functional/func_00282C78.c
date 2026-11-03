/* functional: high. Plain floats in place of VU0 vabs.xyzw: all four lanes read, then all four written. */
void func_00282C78(float *dst, float *src)
{
    float r[4];
    int i;

    for (i = 0; i < 4; i++) {
        r[i] = src[i] < 0.0f ? -src[i] : src[i];
    }
    for (i = 0; i < 4; i++) {
        dst[i] = r[i];
    }
}
