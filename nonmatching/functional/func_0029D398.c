/* functional: medium. Plain C in place of VU0 and MMI code. The colour packing keeps the halfword products of retail's pmulth; no caller was found, so the argument types are a guess from the assembly. */

static int ftoi_0029D398(float f)
{
    if (f >= 2147483648.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)0x80000000;
    }
    return (int)f;
}

static unsigned int shade_0029D398(unsigned int a, unsigned int b)
{
    unsigned int p = a * b;

    if (p > 32767) {
        p = 32767;
    }
    return (p >> 7) & 0xFF;
}

/* Colour word, built once: each byte is the product of the same bytes of the two arguments, saturated to 15 bits and shifted down 7. */
static unsigned int colour_0029D398(unsigned int c, unsigned int f)
{
    return shade_0029D398(c & 0xFF, f & 0xFF)
         | (shade_0029D398((c >> 8) & 0xFF, (f >> 8) & 0xFF) << 8)
         | (shade_0029D398((c >> 16) & 0xFF, (f >> 16) & 0xFF) << 16)
         | (shade_0029D398(c >> 24, f >> 24) << 24);
}

/* Transforms `count` packed vertices (one word each at src: a signed 4-bit matrix index in bits 28-31, a signed 16-bit value in bits 12-27 and a signed 14-bit value times 4 from bits 0-13) into 32-byte records at the scratchpad (0x70000000): the shared colour word, 1.0, zeros, and the 16-bit screen x and y. The point is (bits 0-13 value, 0 or -1 by its sign, bits 12-27 value) moved by the 64-byte matrix at 0x70002000 + index * 64 and then by the matrix at `matrix`. At least one vertex is done. */
void func_0029D398(void *src, void *matrix, int count, int colour, int factor)
{
    int *s = src;
    float *g = matrix;
    unsigned int shade = colour_0029D398((unsigned int)colour, (unsigned int)factor);
    unsigned char *out = (unsigned char *)0x70000000;

    do {
        int w = *s++;
        float *m = (float *)(0x70002000 + (w >> 28) * 64);
        int lo = (int)((unsigned int)w << 18) >> 16;
        int mid = (int)((unsigned int)w << 4) >> 16;
        float x = (float)lo, y = (float)(lo < 0 ? -1 : 0), z = (float)mid;
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
        *(unsigned int *)(out + 0) = shade;
        *(unsigned int *)(out + 4) = 0x3F800000;
        *(unsigned int *)(out + 8) = 0;
        *(unsigned int *)(out + 12) = 0;
        *(unsigned int *)(out + 16) = ((unsigned int)ftoi_0029D398(r[0]) & 0xFFFF) | ((unsigned int)ftoi_0029D398(r[1]) << 16);
        *(unsigned int *)(out + 20) = 0;
        out += 32;
        count--;
    } while (count > 0);
}
