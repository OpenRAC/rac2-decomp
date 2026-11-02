/* functional: medium. Plain C in place of VU0 and MMI code. The colour packing keeps the halfword products of retail's pmulth; no caller was found, so the argument types are a guess from the assembly. */

static int ftoi_0029D258(float f)
{
    if (f >= 2147483648.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)0x80000000;
    }
    return (int)f;
}

/* One byte of the packed colour: the halfword product, saturated to 15 bits and shifted down 7. */
static unsigned int shade_0029D258(unsigned int a, unsigned int b)
{
    unsigned int p = a * b;

    if (p > 32767) {
        p = 32767;
    }
    return (p >> 7) & 0xFF;
}

/* Colour word: each byte is the product of the same bytes of colour and factor. */
static unsigned int colour_0029D258(unsigned int c, unsigned int f)
{
    return shade_0029D258(c & 0xFF, f & 0xFF)
         | (shade_0029D258((c >> 8) & 0xFF, (f >> 8) & 0xFF) << 8)
         | (shade_0029D258((c >> 16) & 0xFF, (f >> 16) & 0xFF) << 16)
         | (shade_0029D258(c >> 24, f >> 24) << 24);
}

/* Transforms `count` vertices of 16 bytes at src (four 16-bit values x y z and a matrix index, two 16-bit texture coordinates, a colour word) into 32-byte records from the scratchpad (0x70000000): colour, 1.0, u/4096, v/4096, and the 16-bit screen x and y of the point moved by the 64-byte matrix the index picks at 0x70002000 and then by the matrix at `matrix`. At least one vertex is done. */
void func_0029D258(void *src, void *matrix, int count, int factor)
{
    short *s = src;
    float *g = matrix;
    unsigned char *out = (unsigned char *)0x70000000;

    do {
        float *m = (float *)(0x70002000 + s[3] * 64);
        float x = (float)s[0], y = (float)s[1], z = (float)s[2];
        float t[3], r[2];
        int i;

        for (i = 0; i < 3; i++) {
            float acc = m[i] * x;
            acc = acc + m[4 + i] * y;
            acc = acc + m[8 + i] * z;
            t[i] = acc + m[12 + i] * 1.0f;
        }
        for (i = 0; i < 2; i++) {
            float acc = g[i] * t[0];
            acc = acc + g[4 + i] * t[1];
            acc = acc + g[8 + i] * t[2];
            r[i] = acc + g[12 + i] * 1.0f;
        }
        *(unsigned int *)(out + 0) = colour_0029D258(*(unsigned int *)((char *)s + 12), (unsigned int)factor);
        *(unsigned int *)(out + 4) = 0x3F800000;
        *(float *)(out + 8) = (float)s[4] * (1.0f / 4096.0f);
        *(float *)(out + 12) = (float)s[5] * (1.0f / 4096.0f);
        *(unsigned int *)(out + 16) = ((unsigned int)ftoi_0029D258(r[0]) & 0xFFFF) | ((unsigned int)ftoi_0029D258(r[1]) << 16);
        *(unsigned int *)(out + 20) = 0;
        out += 32;
        s += 8;
        count--;
    } while (count > 0);
}
