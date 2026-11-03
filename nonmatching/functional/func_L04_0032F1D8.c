/* functional: high. Same reads and writes in the same order; retail's 32-byte lq/lq/sq/sq copies and its three-way quadword copies are written as words, each group read before it is written as retail does. Retail's `qmtc2 zero,$vf0` writes the constant VU0 register and does nothing. */

static void copyq_0032F1D8(unsigned int *d, const unsigned int *s, int words)
{
    unsigned int t[8];
    int i;

    for (i = 0; i < words; i++) {
        t[i] = s[i];
    }
    for (i = 0; i < words; i++) {
        d[i] = t[i];
    }
}

/* Unpack a packed 1432-byte block at src into the 16-row (96-byte rows from dst+0x70) layout at dst: sixteen 64-byte
   blocks to dst+0x70+96i, three 64-byte runs (src+0x400/+0x480/+0x500 to dst+0x10/+0x670/+0x6D0), three words per row
   (src+0x440/+0x4C0/+0x540 to dst+0x6C/+0xB0/+0xB4 + 96i) and six single words from src+0x580. */
void func_L04_0032F1D8(void *dst, void *src)
{
    unsigned char *d = dst, *s = src;
    unsigned char *sp = s;
    int i, j;

    for (i = 0; i < 16; i++) {
        unsigned char *dp = d + 112 + 96 * i;
        for (j = 0; j < 2; j++) {
            copyq_0032F1D8((unsigned int *)dp, (unsigned int *)sp, 8);
            sp += 32;
            dp += 32;
        }
    }
    for (i = 0; i < 4; i++) {
        unsigned int a[4], b[4], c[4];
        int k;

        for (k = 0; k < 4; k++) {
            a[k] = ((unsigned int *)(s + 1024 + 16 * i))[k];
        }
        for (k = 0; k < 4; k++) {
            b[k] = ((unsigned int *)(s + 1152 + 16 * i))[k];
        }
        for (k = 0; k < 4; k++) {
            c[k] = ((unsigned int *)(s + 1280 + 16 * i))[k];
        }
        copyq_0032F1D8((unsigned int *)(d + 16 + 16 * i), a, 4);
        copyq_0032F1D8((unsigned int *)(d + 1648 + 16 * i), b, 4);
        copyq_0032F1D8((unsigned int *)(d + 1744 + 16 * i), c, 4);
    }
    for (i = 0; i < 16; i++) {
        unsigned int a = *(unsigned int *)(s + 1088 + 4 * i);
        unsigned int b = *(unsigned int *)(s + 1216 + 4 * i);
        unsigned int c = *(unsigned int *)(s + 1344 + 4 * i);
        *(unsigned int *)(d + 108 + 96 * i) = a;
        *(unsigned int *)(d + 176 + 96 * i) = b;
        *(unsigned int *)(d + 180 + 96 * i) = c;
    }
    {
        unsigned int a, b;

        a = *(unsigned int *)(s + 1408);
        b = *(unsigned int *)(s + 1412);
        *(unsigned int *)(d + 12) = a;
        *(unsigned int *)(d + 80) = b;
        a = *(unsigned int *)(s + 1416);
        b = *(unsigned int *)(s + 1420);
        *(unsigned int *)(d + 1644) = a;
        *(unsigned int *)(d + 1712) = b;
        a = *(unsigned int *)(s + 1424);
        b = *(unsigned int *)(s + 1428);
        *(unsigned int *)(d + 1716) = a;
        *(unsigned int *)(d + 1808) = b;
    }
}
