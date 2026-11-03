/* functional: high. Plain floats in place of VU0 code: each lane times scale, truncated toward zero (vftoi0) and clamped to [-32768, 32767] (pminw/pmaxw); the clamp is done before the conversion so the host never converts an out-of-range float, which gives the same results. Packed as retail's ppach: x in bits 0-15 up to w in bits 48-63. */

/* Pack v * scale as four signed 16-bit integers (x lowest) in a 64-bit word. */
unsigned long func_L00_002EE660(const void *v, float scale)
{
    const float *p = v;
    unsigned long r = 0;
    int i;

    for (i = 0; i < 4; i++) {
        float t = p[i] * scale;
        int n;

        if (t >= 32767.0f) {
            n = 32767;
        } else if (t <= -32768.0f) {
            n = -32768;
        } else {
            n = (int)t;
        }
        r |= (unsigned long)(n & 0xFFFF) << (16 * i);
    }
    return r;
}
