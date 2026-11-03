/* functional: medium. Written from the hand-written assembly, plain floats in place of VU0 code in its order (ACC chains left to right, 4-lane sums as ((x + y) + z) + w). The toSPR transfers (channel 9 at 0x1000D400) are retail's register writes in retail's order; the default-translation and frame transfers are waited for by polling the last doubleword of the destination, which retail clears first, and each layer transfer by the channel's STR bit, as retail does. The +48 copy of a default translation is retail's vmulw by 1.0, which flushes a denormal to a signed zero as the VU does. Retail's loads past the end of each list (the next entry, the next layer target) only read and are left out where they change nothing; where a load feeds the next iteration (the layer blend reloads its target before the rotation store) the order is kept. vrsqrt of 0 gives the VU's largest float. Retail keeps its return address in the upper half of $ra (pcpyld/pcpyud), which has no C spelling. */

extern float sqrtf(float);

typedef union {
    float f;
    unsigned int u;
} FU_00316F60;

static unsigned int fbits_00316F60(float f)
{
    FU_00316F60 v;
    v.f = f;
    return v.u;
}

static float fval_00316F60(unsigned int u)
{
    FU_00316F60 v;
    v.u = u;
    return v.f;
}

/* The four signed halfwords at p, as words. */
static void halves_00316F60(int *o, const unsigned char *p)
{
    int i;

    for (i = 0; i < 4; i++) {
        o[i] = *(const short *)(p + 2 * i);
    }
}

static void get4_00316F60(float *v, const unsigned char *s)
{
    const float *p = (const float *)s;
    float a = p[0], b = p[1], c = p[2], e = p[3];

    v[0] = a;
    v[1] = b;
    v[2] = c;
    v[3] = e;
}

static void put4_00316F60(unsigned char *d, const float *v)
{
    float *o = (float *)d;
    float a = v[0], b = v[1], c = v[2], e = v[3];

    o[0] = a;
    o[1] = b;
    o[2] = c;
    o[3] = e;
}

/* VU0 vrsqrt with vf0.w: 1 / sqrt(|x|), the largest float for 0. */
static float rsqrt_00316F60(float x)
{
    if ((fbits_00316F60(x) & 0x7FFFFFFFu) == 0) {
        return 3.40282347e38f;
    }
    return 1.0f / sqrtf(x < 0.0f ? -x : x);
}

/* x * 1.0 on the VU: a denormal becomes a zero of its sign. */
static float mul1_00316F60(float x)
{
    unsigned int b = fbits_00316F60(x);

    if ((b & 0x7F800000u) == 0) {
        return fval_00316F60(b & 0x80000000u);
    }
    return x;
}

/* ((m.y + m.x) + z) + w, the dot product's lane order. */
static float dot4_00316F60(const float *m)
{
    return ((m[1] + m[0]) + 1.0f * m[2]) + 1.0f * m[3];
}

/* ((x*x + y*y) + z*z) + w*w. */
static float len4_00316F60(const float *q)
{
    float s0 = q[0] * q[0], s1 = q[1] * q[1], s2 = q[2] * q[2], s3 = q[3] * q[3];

    return ((s0 + s1) + 1.0f * s2) + 1.0f * s3;
}

/* (a * u) + (b * t), normalised along the shorter arc: the sign of the lane products' sum picks a + b or a - b. */
static void nblend_00316F60(float *q, const float *a, const float *b)
{
    float m[4], dot, len, s;
    int k;

    for (k = 0; k < 4; k++) {
        q[k] = a[k] + b[k];
        m[k] = a[k] * b[k];
    }
    dot = dot4_00316F60(m);
    len = len4_00316F60(q);
    if ((fbits_00316F60(dot) >> 31) != 0) {
        for (k = 0; k < 4; k++) {
            q[k] = a[k] - b[k];
        }
        len = len4_00316F60(q);
    }
    s = rsqrt_00316F60(len);
    for (k = 0; k < 4; k++) {
        q[k] = q[k] * s;
    }
}

/* Build the skeleton pose of an animated object as 64-byte bone records in the scratchpad (rotation +0, scale +16,
   translation +32). obj: +36 model (+8 bone count n, +24 its 16-byte default translations), +64..+67 frame bytes,
   +68 blend weight t, +80 list of blended poses (+2 bone count, +8 weight, +16 48-byte records whose word 11 is the
   target record, +28 next), +84 list of bone adjustments (+3 mode, +4 target record, +8 next, +12 weight, +16
   rotation, +32 scale, +48 translation), +88 / +92 the two frames' packed channels (+6 quadword count, +10 scale
   count, +14 translation count, data at +16: n 8-byte rotations, then at n*8 the 8-byte scale and translation
   entries, bone byte at +6, a scale entry with its top two bits clear is skipped). With t != 0 both frames are
   unpacked and blended by (1 - t, t); the rotations are normalised (with the shorter arc) unless both frame-byte
   pairs say the frames are adjacent. Then each pose of +80 is blended in by its weight, and each adjustment of +84
   either composed (mode 0: quaternion product, scale product, translation sum) or blended by its weight. */
void func_L00_00316F60(void *obj)
{
    unsigned char *o = obj;
    unsigned char *S = (unsigned char *)0x70000000;
    volatile unsigned int *to = (volatile unsigned int *)0x1000D400;
    unsigned char *model = *(unsigned char **)(o + 36);
    unsigned char *A = *(unsigned char **)(o + 88);
    unsigned char *B = *(unsigned char **)(o + 92);
    unsigned int mq = model[8];
    unsigned int tw = *(unsigned int *)(o + 68);
    float one[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
    unsigned char *L;
    unsigned char *M;
    int aq, ac1, ac2;
    int k, c;
    unsigned int i;

    to[32] = 0x2000;
    to[4] = *(unsigned int *)(model + 24);
    to[8] = mq;
    *(unsigned long *)(S + 0x1FF8 + mq * 16) = 0;
    to[0] = 0x100;
    A += 16;
    B += 16;

    aq = *(short *)(A - 10);
    ac1 = *(short *)(A - 6);
    ac2 = *(short *)(A - 2);
    *(unsigned long *)(S + 0x2FF0 + aq * 16) = 0;
    *(unsigned long *)(S + 0x2FF8 + aq * 16) = 0;
    c = (int)mq;
    i = 0;
    do {
        put4_00316F60(S + 128 * i, one);
        put4_00316F60(S + 128 * i + 16, one);
        put4_00316F60(S + 128 * i + 64, one);
        put4_00316F60(S + 128 * i + 80, one);
        i++;
        c -= 2;
    } while (c > 0);

    while (*(volatile unsigned long *)(S + 0x1FF8 + mq * 16) == 0) {
    }
    to[32] = 0x70003000;
    to[4] = (unsigned int)A;
    to[8] = aq;
    to[0] = 0x100;

    /* Default translations into +32 (whole quad) and +48 (w 0), four bones a pass. */
    c = (int)mq;
    i = 0;
    do {
        int j;
        for (j = 0; j < 4; j++) {
            float v[4];
            unsigned char *rec = S + 256 * i + 64 * j;
            get4_00316F60(v, S + 0x2000 + 64 * i + 16 * j);
            put4_00316F60(rec + 32, v);
            for (k = 0; k < 3; k++) {
                v[k] = mul1_00316F60(v[k]);
            }
            v[3] = 0.0f;
            put4_00316F60(rec + 48, v);
        }
        i++;
        c -= 4;
    } while (c > 0);

    if (tw != 0) {
        float t, u;
        int same = (int)(o[66] - o[67]) | (int)(o[64] + 1 - o[65]);
        int bq = *(short *)(B - 10);
        int bc1 = *(short *)(B - 6);
        int bc2 = *(short *)(B - 2);
        unsigned int *ls = (unsigned int *)(S + 0x3C00);
        unsigned int *lt = (unsigned int *)(S + 0x3D00);
        unsigned int *p;
        unsigned char *e;
        unsigned char *r;

        t = fval_00316F60(tw);
        *(unsigned long *)(S + 0x35F0 + bq * 16) = 0;
        *(unsigned long *)(S + 0x35F8 + bq * 16) = 0;
        u = 1.0f - t;
        while (*(volatile unsigned long *)(S + 0x2FF0 + aq * 16) == 0) {
        }
        to[4] = (unsigned int)B;
        to[32] = 0x70003600;
        to[8] = bq;
        to[0] = 0x100;

        /* Frame A: scales into +0 (listed in ls, word 3 set to -4), translations into +32 (listed in lt, word 15
           set to -4). */
        e = S + 0x3000 + mq * 8;
        if (ac1 != 0) {
            while (ac1 > 0) {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                r = S + e[6] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)(int)((unsigned int)*(unsigned short *)(e + 2 * k) << 3) * (1.0f / 32768.0f);
                }
                v[3] = 0.0f;
                e += 8;
                ac1--;
                if ((d >> 62) == 0) {
                    continue;
                }
                *ls++ = (unsigned int)r;
                put4_00316F60(r, v);
                *(int *)(r + 12) = -4;
            }
        }
        if (ac2 != 0) {
            do {
                int h[4];
                float v[4];
                unsigned int keep;
                halves_00316F60(h, e);
                r = S + e[6] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)h[k];
                }
                v[3] = 1.0f;
                e += 8;
                *lt++ = (unsigned int)r;
                keep = *(unsigned int *)(r + 44);
                put4_00316F60(r + 32, v);
                *(unsigned int *)(r + 44) = keep;
                *(int *)(r + 60) = -4;
            } while (--ac2 > 0);
        }
        while (*(volatile unsigned long *)(S + 0x35F0 + bq * 16) == 0) {
        }

        /* Frame B: scales into +16, translations into +48; a bone frame A listed is not listed again. */
        e = S + 0x3600 + mq * 8;
        if (bc1 != 0) {
            while (bc1 > 0) {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                int skip;
                r = S + e[6] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)(int)((unsigned int)*(unsigned short *)(e + 2 * k) << 3) * (1.0f / 32768.0f);
                }
                v[3] = 0.0f;
                e += 8;
                *ls = (unsigned int)r;
                skip = *(int *)(r + 12);
                bc1--;
                if ((d >> 62) == 0) {
                    continue;
                }
                put4_00316F60(r + 16, v);
                ls = (unsigned int *)((unsigned char *)ls + 4 + skip);
                if (bc1 == 0) {
                    break;
                }
            }
        }
        if (bc2 != 0) {
            do {
                int h[4];
                float v[4];
                int skip;
                halves_00316F60(h, e);
                r = S + e[6] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)h[k];
                }
                v[3] = 1.0f;
                e += 8;
                *lt = (unsigned int)r;
                skip = *(int *)(r + 60);
                put4_00316F60(r + 48, v);
                lt = (unsigned int *)((unsigned char *)lt + 4 + skip);
            } while (--bc2 > 0);
        }

        /* Blend the listed scales (+0, +16 into +16) and translations (+32, +48 into +32); word 3 of the result is
           put back. */
        *ls = (unsigned int)(S + 0x2000);
        for (p = (unsigned int *)(S + 0x3C00); p != ls; p++) {
            float *a = (float *)(unsigned char *)*p;
            unsigned int keep = ((unsigned int *)a)[7];
            for (k = 0; k < 3; k++) {
                a[4 + k] = a[k] * u + a[4 + k] * t;
            }
            ((unsigned int *)a)[7] = keep;
        }
        *lt = (unsigned int)(S + 0x2000);
        for (p = (unsigned int *)(S + 0x3D00); p != lt; p++) {
            float *a = (float *)(unsigned char *)*p;
            unsigned int keep = ((unsigned int *)a)[11];
            for (k = 0; k < 3; k++) {
                a[8 + k] = a[8 + k] * u + a[12 + k] * t;
            }
            ((unsigned int *)a)[11] = keep;
        }

        /* Rotations, two bones a pass: (1 - t) a + t b, normalised along the shorter arc unless the frames are
           adjacent. */
        c = (int)mq;
        i = 0;
        do {
            int j;
            float q[2][4];
            for (j = 0; j < 2; j++) {
                int ha[4], hb[4];
                float qa[4], qb[4];
                halves_00316F60(ha, S + 0x3000 + 16 * i + 8 * j);
                halves_00316F60(hb, S + 0x3600 + 16 * i + 8 * j);
                for (k = 0; k < 4; k++) {
                    qa[k] = (float)ha[k] * (1.0f / 32768.0f);
                    qb[k] = (float)hb[k] * (1.0f / 32768.0f);
                }
                if (same == 0) {
                    for (k = 0; k < 4; k++) {
                        q[j][k] = qa[k] * u + qb[k] * t;
                    }
                } else {
                    for (k = 0; k < 4; k++) {
                        qa[k] = qa[k] * u;
                        qb[k] = qb[k] * t;
                    }
                    nblend_00316F60(q[j], qa, qb);
                }
            }
            put4_00316F60(S + 128 * i, q[0]);
            put4_00316F60(S + 128 * i + 64, q[1]);
            i++;
            c -= 2;
        } while (c > 0);
    } else {
        unsigned char *e;

        while (*(volatile unsigned long *)(S + 0x2FF0 + aq * 16) == 0) {
        }
        e = S + 0x3000 + mq * 8;
        if (ac1 != 0) {
            while (ac1 > 0) {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                unsigned char *r = S + e[6] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)(int)((unsigned int)*(unsigned short *)(e + 2 * k) << 3) * (1.0f / 32768.0f);
                }
                v[3] = 0.0f;
                e += 8;
                ac1--;
                if ((d >> 62) == 0) {
                    continue;
                }
                put4_00316F60(r + 16, v);
            }
        }
        if (ac2 != 0) {
            do {
                int h[4];
                float v[4];
                unsigned int keep;
                unsigned char *r;
                halves_00316F60(h, e);
                r = S + e[6] * 64;
                for (k = 0; k < 3; k++) {
                    v[k] = (float)h[k];
                }
                v[3] = 1.0f;
                e += 8;
                keep = *(unsigned int *)(r + 44);
                put4_00316F60(r + 32, v);
                *(unsigned int *)(r + 44) = keep;
            } while (--ac2 > 0);
        }
        /* Rotations, four bones a pass. */
        c = (int)mq;
        i = 0;
        do {
            int j;
            for (j = 0; j < 4; j++) {
                int h[4];
                float q[4];
                halves_00316F60(h, S + 0x3000 + 32 * i + 8 * j);
                for (k = 0; k < 4; k++) {
                    q[k] = (float)h[k] * (1.0f / 32768.0f);
                }
                put4_00316F60(S + 256 * i + 64 * j, q);
            }
            i++;
            c -= 4;
        } while (c > 0);
    }

    /* Blended poses: each record's rotation, scale and translation blended into its target by (1 - w, w); a
       target's scale word 3, when 0, takes the pose's. */
    L = *(unsigned char **)(o + 80);
    M = *(unsigned char **)(o + 84);
    while (L != 0) {
        unsigned int h = *(unsigned short *)(L + 2);
        unsigned char *src = S + 0x2000;
        unsigned char *end;
        unsigned char *tg;
        float w, wu;
        float a6[4], a7[4], a8[4], a9[4], a10[4], a11[4];

        to[32] = 0x2000;
        to[4] = *(unsigned int *)(L + 16);
        to[8] = h * 3;
        to[0] = 0x100;
        end = S + 0x2000 + h * 48;
        w = *(float *)(L + 8);
        L = *(unsigned char **)(L + 28);
        *(unsigned int *)(end + 44) = (unsigned int)(S + 0x2000);
        wu = 1.0f - w;
        while (to[0] & 0x100) {
        }
        tg = (unsigned char *)*(unsigned int *)(src + 44);
        get4_00316F60(a9, src);
        get4_00316F60(a10, src + 16);
        get4_00316F60(a11, src + 32);
        get4_00316F60(a6, tg);
        get4_00316F60(a7, tg + 16);
        get4_00316F60(a8, tg + 32);
        do {
            float q[4];
            unsigned int keep;
            unsigned char *nx;
            for (k = 0; k < 4; k++) {
                a6[k] = a6[k] * wu;
                a9[k] = a9[k] * w;
            }
            for (k = 0; k < 3; k++) {
                a7[k] = a7[k] * wu;
                a10[k] = a10[k] * w;
                a8[k] = a8[k] * wu;
                a11[k] = a11[k] * w;
            }
            nblend_00316F60(q, a6, a9);
            for (k = 0; k < 3; k++) {
                a7[k] = a7[k] + a10[k];
                a8[k] = a8[k] + a11[k];
            }
            keep = *(unsigned int *)(src + 28);
            nx = (unsigned char *)*(unsigned int *)(src + 92);
            get4_00316F60(a9, src + 48);
            get4_00316F60(a10, src + 64);
            get4_00316F60(a11, src + 80);
            put4_00316F60(tg + 16, a7);
            put4_00316F60(tg + 32, a8);
            get4_00316F60(a6, nx);
            get4_00316F60(a7, nx + 16);
            get4_00316F60(a8, nx + 32);
            if (*(unsigned int *)(tg + 28) == 0) {
                *(unsigned int *)(tg + 28) = keep;
            }
            src += 48;
            put4_00316F60(tg, q);
            tg = nx;
        } while (src != end);
    }

    /* Bone adjustments. */
    while (M != 0) {
        unsigned char *tg = (unsigned char *)*(unsigned int *)(M + 4);
        unsigned int mode = M[3];
        float a6[4], a7[4], a8[4], a9[4], a10[4], a11[4];

        get4_00316F60(a6, tg);
        get4_00316F60(a8, tg + 16);
        get4_00316F60(a10, tg + 32);
        get4_00316F60(a7, M + 16);
        get4_00316F60(a9, M + 32);
        get4_00316F60(a11, M + 48);
        if (mode == 0) {
            /* a6 * a7 as quaternions: (b.xyz a.w + a.xyz b.w + a x b, a.w b.w - a.b). */
            float ww = a7[3] * a6[3];
            float m0 = a7[0] * a6[0], m1 = a7[1] * a6[1], m2 = a7[2] * a6[2];
            float d, x[3], y[3], z[3];
            for (k = 0; k < 3; k++) {
                x[k] = a7[k] * a6[3];
                y[k] = a6[k] * a7[3];
            }
            z[0] = a6[1] * a7[2] - a7[1] * a6[2];
            z[1] = a6[2] * a7[0] - a7[2] * a6[0];
            z[2] = a6[0] * a7[1] - a7[0] * a6[1];
            d = (m0 + m1) + 1.0f * m2;
            for (k = 0; k < 3; k++) {
                a6[k] = (x[k] + y[k]) + z[k];
            }
            a6[3] = ww - d;
            for (k = 0; k < 3; k++) {
                a8[k] = a8[k] * a9[k];
                a10[k] = a10[k] + a11[k];
            }
        } else {
            float w = *(float *)(M + 12);
            float wu = 1.0f - w;
            float q[4];
            for (k = 0; k < 4; k++) {
                a6[k] = a6[k] * wu;
                a7[k] = a7[k] * w;
            }
            for (k = 0; k < 3; k++) {
                a8[k] = a8[k] * wu;
                a9[k] = a9[k] * w;
                a10[k] = a10[k] * wu;
                a11[k] = a11[k] * w;
            }
            nblend_00316F60(q, a6, a7);
            for (k = 0; k < 3; k++) {
                a8[k] = a8[k] + a9[k];
                a10[k] = a10[k] + a11[k];
            }
            for (k = 0; k < 4; k++) {
                a6[k] = q[k];
            }
        }
        M = *(unsigned char **)(M + 8);
        put4_00316F60(tg, a6);
        put4_00316F60(tg + 16, a8);
        put4_00316F60(tg + 32, a10);
    }
}
