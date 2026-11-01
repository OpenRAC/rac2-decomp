/* functional: high. Plain C in place of VU0 and MMI code; the float to integer conversion truncates and saturates as the vector unit does. */

static int ftoi_00283108(float f)
{
    if (f >= 2147483648.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)0x80000000;
    }
    return (int)f;
}

/* The four floats at v truncated to integers; their low bytes packed into one word, x lowest. */
int func_00283108(float *v)
{
    unsigned int r = 0;
    int i;

    for (i = 0; i < 4; i++) {
        r |= ((unsigned int)ftoi_00283108(v[i]) & 0xFF) << (i * 8);
    }
    return (int)r;
}
