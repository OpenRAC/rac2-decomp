/* functional: medium. Written from the hand-written assembly, plain floats in place of VU0 code in its order. The three toSPR transfers (channel 9 at 0x1000D400) and the closing fromSPR transfer (channel 8 at 0x1000D000) are retail's register writes in retail's order; each toSPR wait polls the last doubleword of its destination, which retail clears first, as retail does. Retail then waits for the fromSPR transfer with bc0f (COP0's CPCOND0, after clearing channel 8's D_STAT bit), which reads no memory and has no C form; it is left out: the port (asm.dma_done) and fcheck finish a transfer at the CHCR store that starts it, so the wait never waits there. Retail's loads of the entry after the last (one past each list) only read and are left out. vrsqrt of 0 gives the VU's largest float. */

extern float sqrtf(float);

typedef union {
    float f;
    unsigned int u;
} FU_00314D40;

static unsigned int fbits_00314D40(float f)
{
    FU_00314D40 v;
    v.f = f;
    return v.u;
}

/* The four signed halfwords of the doubleword at p, as words. */
static void halves_00314D40(int *o, const unsigned char *p)
{
    int i;

    for (i = 0; i < 4; i++) {
        o[i] = *(const short *)(p + 2 * i);
    }
}

static void put4_00314D40(unsigned char *d, const float *v)
{
    float *o = (float *)d;
    float a = v[0], b = v[1], c = v[2], e = v[3];

    o[0] = a;
    o[1] = b;
    o[2] = c;
    o[3] = e;
}

/* VU0 vrsqrt with vf0.w: 1 / sqrt(|x|), the largest float for 0. */
static float rsqrt_00314D40(float x)
{
    if ((fbits_00314D40(x) & 0x7FFFFFFFu) == 0) {
        return 3.40282347e38f;
    }
    return 1.0f / sqrtf(x < 0.0f ? -x : x);
}

/* Blend the skeleton pose of an animated object into its bone records in the scratchpad and send them to
   obj+16 (48 bytes a bone: rotation, scale, translation and the record's own scratchpad address in word 11).
   obj: +2 bone count n, +12 bone index list, +16 destination, +20 model (+8 quadword count, +24 its 16-byte
   default translations), +32..+35 frame bytes, +36 blend weight t, +56 / +60 the two frames' packed
   channels (+6 quadword count, +10 scale count, +14 translation count, data at +16: n 8-byte rotations
   indexed by bone, then at qwc*8 the 8-byte scale and translation entries, bone byte at +6). With t != 0
   both frames are unpacked and blended by (1 - t, t); the rotations are normalised (with the shorter arc)
   unless both frame-byte pairs say the frames are adjacent. */
void func_L00_00314D40(void *obj)
{
    unsigned char *o = obj;
    unsigned char *S = (unsigned char *)0x70000000;
    volatile unsigned int *to = (volatile unsigned int *)0x1000D400;
    volatile unsigned int *from = (volatile unsigned int *)0x1000D000;
    unsigned char *model = *(unsigned char **)(o + 20);
    unsigned char *A = *(unsigned char **)(o + 56);
    unsigned char *B = *(unsigned char **)(o + 60);
    unsigned int n = *(unsigned short *)(o + 2);
    unsigned char *idx = *(unsigned char **)(o + 12);
    unsigned int mq = model[8];
    unsigned int tw = *(unsigned int *)(o + 36);
    unsigned char *map = S + 0x2800;
    float one[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
    int aq, ac1, ac2;
    unsigned int i;
    int k;

    to[32] = 0x2000;
    to[4] = *(unsigned int *)(model + 24);
    to[8] = mq;
    *(unsigned long *)(S + 0x1FF8 + mq * 16) = 0;
    to[0] = 0x100;
    A += 16;
    B += 16;

    for (k = 0; k < 128; k += 8) {
        *(unsigned long *)(map + k) = 0x7F7F7F7F7F7F7F7FUL;
    }
    i = 0;
    do {
        map[idx[i]] = (unsigned char)i;
        i++;
    } while (i != n);

    aq = *(short *)(A - 10);
    ac1 = *(short *)(A - 6);
    ac2 = *(short *)(A - 2);
    *(unsigned long *)(S + 0x2FF0 + aq * 16) = 0;
    *(unsigned long *)(S + 0x2FF8 + aq * 16) = 0;
    k = (int)n;
    i = 0;
    do {
        put4_00314D40(S + 128 * i, one);
        put4_00314D40(S + 128 * i + 16, one);
        put4_00314D40(S + 128 * i + 64, one);
        put4_00314D40(S + 128 * i + 80, one);
        i++;
        k -= 2;
    } while (k > 0);
    put4_00314D40(S + 0x1FC0, one);
    put4_00314D40(S + 0x1FD0, one);

    while (*(volatile unsigned long *)(S + 0x1FF8 + mq * 16) == 0) {
    }
    to[32] = 0x70003000;
    to[4] = (unsigned int)A;
    to[8] = aq;
    to[0] = 0x100;

    for (i = 0; i != n; i++) {
        unsigned char *rec = S + 64 * i;
        float v[4];
        for (k = 0; k < 4; k++) {
            v[k] = *(float *)(S + 0x2000 + idx[i] * 16 + 4 * k);
        }
        put4_00314D40(rec + 32, v);
        put4_00314D40(rec + 48, v);
        *(unsigned int *)(rec + 60) = 0;
    }
    *(unsigned long *)(S + 0x1FE0) = 0;
    *(unsigned long *)(S + 0x1FE8) = 0;
    *(unsigned long *)(S + 0x1FF0) = 0;
    *(unsigned long *)(S + 0x1FF8) = 0;

    if (tw != 0) {
        FU_00314D40 tv;
        float t, u;
        int bq = *(short *)(B - 10);
        int bc1 = *(short *)(B - 6);
        int bc2 = *(short *)(B - 2);
        unsigned int *ls = (unsigned int *)(S + 0x3C00);
        unsigned int *lt = (unsigned int *)(S + 0x3D00);
        unsigned char *e;
        unsigned char *r;
        unsigned int *p;
        int same;

        tv.u = tw;
        t = tv.f;
        *(unsigned long *)(S + 0x35F0 + bq * 16) = 0;
        *(unsigned long *)(S + 0x35F8 + bq * 16) = 0;
        u = 1.0f - t;
        while (*(volatile unsigned long *)(S + 0x2FF0 + aq * 16) == 0) {
        }
        to[4] = (unsigned int)B;
        to[32] = 0x70003600;
        to[8] = bq;
        to[0] = 0x100;

        /* Frame A: scales into +0 (listed in ls), translations into +32 (listed in lt). */
        e = S + 0x3000 + mq * 8;
        if (ac1 != 0) {
            do {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                r = S + map[e[6]] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)(int)((unsigned int)*(unsigned short *)(e + 2 * k) << 3) * (1.0f / 32768.0f);
                }
                v[3] = 0.0f;
                e += 8;
                *ls++ = (unsigned int)r;
                *(unsigned int *)(r + 28) = (unsigned int)(d >> 62) - 1;
                put4_00314D40(r, v);
                *(int *)(r + 12) = -4;
            } while (--ac1 > 0);
        }
        if (ac2 != 0) {
            do {
                int h[4];
                float v[4];
                unsigned int keep;
                halves_00314D40(h, e);
                r = S + map[e[6]] * 64;
                e += 8;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)h[k];
                }
                v[3] = 1.0f;
                *lt++ = (unsigned int)r;
                keep = *(unsigned int *)(r + 44);
                put4_00314D40(r + 32, v);
                *(unsigned int *)(r + 44) = keep;
                *(int *)(r + 60) = -4;
            } while (--ac2 > 0);
        }
        while (*(volatile unsigned long *)(S + 0x35F0 + bq * 16) == 0) {
        }

        /* Frame B: scales into +16, translations into +48; a bone frame A listed is not listed again. */
        e = S + 0x3600 + mq * 8;
        if (bc1 != 0) {
            do {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                int skip;
                r = S + map[e[6]] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)(int)((unsigned int)*(unsigned short *)(e + 2 * k) << 3) * (1.0f / 32768.0f);
                }
                v[3] = 0.0f;
                e += 8;
                *ls = (unsigned int)r;
                skip = *(int *)(r + 12);
                put4_00314D40(r + 16, v);
                *(unsigned int *)(r + 28) = (unsigned int)(d >> 62) - 1;
                ls = (unsigned int *)((unsigned char *)ls + 4 + skip);
            } while (--bc1 != 0);
        }
        if (bc2 != 0) {
            do {
                int h[4];
                float v[4];
                int skip;
                halves_00314D40(h, e);
                r = S + map[e[6]] * 64;
                e += 8;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)h[k];
                }
                v[3] = 1.0f;
                *lt = (unsigned int)r;
                skip = *(int *)(r + 60);
                put4_00314D40(r + 48, v);
                *(int *)(r + 60) = skip;
                lt = (unsigned int *)((unsigned char *)lt + 4 + skip);
            } while (--bc2 > 0);
        }

        /* Blend the listed scales (+0, +16 into +16) and translations (+32, +48 into +32); word 3 of the result is
           put back. */
        *ls = (unsigned int)(S + 0x1E00);
        for (p = (unsigned int *)(S + 0x3C00); p != ls; p++) {
            float *a = (float *)(unsigned char *)*p;
            unsigned int keep = ((unsigned int *)a)[7];
            for (k = 0; k < 3; k++) {
                a[4 + k] = a[k] * u + a[4 + k] * t;
            }
            ((unsigned int *)a)[7] = keep;
        }
        *lt = (unsigned int)(S + 0x1E00);
        for (p = (unsigned int *)(S + 0x3D00); p != lt; p++) {
            float *a = (float *)(unsigned char *)*p;
            unsigned int keep = ((unsigned int *)a)[11];
            for (k = 0; k < 3; k++) {
                a[8 + k] = a[8 + k] * u + a[12 + k] * t;
            }
            ((unsigned int *)a)[11] = keep;
        }

        /* Rotations: (1 - t) a + t b, normalised along the shorter arc unless the frames are adjacent. */
        same = (int)(o[34] - o[35]) | (int)(o[32] + 1 - o[33]);
        for (i = 0; i != n; i++) {
            unsigned int b = idx[i];
            int ha[4], hb[4];
            float qa[4], qb[4], q[4];
            unsigned char *rec = S + 64 * i;

            halves_00314D40(ha, S + 0x3000 + b * 8);
            halves_00314D40(hb, S + 0x3600 + b * 8);
            for (k = 0; k < 4; k++) {
                qa[k] = (float)ha[k] * (1.0f / 32768.0f);
                qb[k] = (float)hb[k] * (1.0f / 32768.0f);
            }
            if (same == 0) {
                for (k = 0; k < 4; k++) {
                    q[k] = qa[k] * u + qb[k] * t;
                }
                *(unsigned int *)(rec + 44) = (unsigned int)(S + b * 64);
            } else {
                float m[4], dot, len, s;
                for (k = 0; k < 4; k++) {
                    qa[k] = qa[k] * u;
                    qb[k] = qb[k] * t;
                }
                *(unsigned int *)(rec + 44) = (unsigned int)(S + b * 64);
                for (k = 0; k < 4; k++) {
                    q[k] = qa[k] + qb[k];
                    m[k] = qa[k] * qb[k];
                }
                dot = ((m[1] + m[0]) + 1.0f * m[2]) + 1.0f * m[3];
                len = ((q[0] * q[0] + q[1] * q[1]) + 1.0f * (q[2] * q[2])) + 1.0f * (q[3] * q[3]);
                if ((fbits_00314D40(dot) >> 31) != 0) {
                    for (k = 0; k < 4; k++) {
                        q[k] = qa[k] - qb[k];
                    }
                    len = ((q[0] * q[0] + q[1] * q[1]) + 1.0f * (q[2] * q[2])) + 1.0f * (q[3] * q[3]);
                }
                s = rsqrt_00314D40(len);
                for (k = 0; k < 4; k++) {
                    q[k] = q[k] * s;
                }
            }
            put4_00314D40(rec, q);
        }
    } else {
        unsigned char *e;

        while (*(volatile unsigned long *)(S + 0x2FF0 + aq * 16) == 0) {
        }
        e = S + 0x3000 + mq * 8;
        if (ac1 != 0) {
            do {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                unsigned char *r = S + map[e[6]] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)(int)((unsigned int)*(unsigned short *)(e + 2 * k) << 3) * (1.0f / 32768.0f);
                }
                v[3] = 0.0f;
                e += 8;
                put4_00314D40(r + 16, v);
                *(unsigned int *)(r + 28) = (unsigned int)(d >> 62) - 1;
            } while (--ac1 > 0);
        }
        if (ac2 != 0) {
            do {
                int h[4];
                float v[4];
                unsigned char *r;
                halves_00314D40(h, e);
                r = S + map[e[6]] * 64;
                e += 8;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)h[k];
                }
                v[3] = 1.0f;
                put4_00314D40(r + 32, v);
            } while (--ac2 > 0);
        }
        for (i = 0; i != n; i++) {
            unsigned int b = idx[i];
            int h[4];
            float q[4];
            unsigned char *rec = S + 64 * i;

            halves_00314D40(h, S + 0x3000 + b * 8);
            for (k = 0; k < 4; k++) {
                q[k] = (float)h[k] * (1.0f / 32768.0f);
            }
            *(unsigned int *)(rec + 44) = (unsigned int)(S + b * 64);
            put4_00314D40(rec, q);
        }
    }

    /* Pack the records to 48 bytes each and send them to obj+16. */
    i = 0;
    do {
        unsigned int w[12];
        for (k = 0; k < 12; k++) {
            w[k] = *(unsigned int *)(S + 64 * i + 4 * k);
        }
        for (k = 0; k < 12; k++) {
            *(unsigned int *)(S + 48 * i + 4 * k) = w[k];
        }
        i++;
    } while ((int)(n - i) > 0);
    from[32] = 0;
    from[8] = n * 3;
    from[4] = *(unsigned int *)(o + 16);
    *(volatile unsigned int *)0x1000E010 = 0x100;
    from[0] = 0x100;
}
