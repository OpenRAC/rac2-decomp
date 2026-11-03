/* functional: high. Gate: on all 12 captured calls (level00 8, level03 4) every memory word, register and the result equal retail's but for the 8 scratchpad words 0x70003700-0x7000371F: retail's first act is to save its hand-written callers' t8/t9 (128-bit; 0x70000000 and 0x10010000 in the captures) there and reload them at the end. C cannot see those registers and the port's callers (CollLine/CollSphere func_00277F48/func_00277258/func_002761F8, func_002DFD88, a matched caller in src/game/002A99A0.c) are C that keep nothing in them, and no code reads those words otherwise, so the save is left out (BACKFILL.md: noted, not counted as same). Written from the hand-written VU0/MMI assembly: plain floats in the VU's order (ACC chains left to right, 4-lane sums as ((x + y) + z) + w), the same reads, writes and calls in the same order. VU rounding is not reproduced; vrsqrt of 0 gives FLT_MAX as the VU does. The toSPR DMAs (0x1000D400 registers) are written as retail's register stores, and their completion is polled as retail does: the last doubleword of each block (zeroed first) until non-zero, the attachment block by the channel's STR bit. Where retail stores a VU register whose w lane it did not set and then restores the word, only the final value is written. buf is used as an address only when its low 32 bits are > 0 (two callers declare it int and pass 0 or -1). */
extern float sqrtf(float);
#define SPR_002A3110 0x70000000u

static float bitsf_002A3110(unsigned int i)
{
    union {
        float f;
        unsigned int i;
    } u;
    u.i = i;
    return u.f;
}

static int neg_002A3110(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

static float rsqrt_002A3110(float x)
{

    float s = sqrtf(x < 0.0f ? -x : x);
    if (s == 0.0f) {
        return 3.40282347e+38f;
    }
    return 1.0f / s;
}

static unsigned char *sp_002A3110(unsigned int off)
{
    return (unsigned char *)(unsigned long)(SPR_002A3110 + off);
}

static void wait_002A3110(unsigned int off)
{
    volatile unsigned int *p = (volatile unsigned int *)(unsigned long)(SPR_002A3110 + off);
    while ((p[0] | p[1]) == 0) {
    }
}

/* q[4] = itof15 of the four signed halfwords at h */
static void quat_002A3110(float *q, const short *h)
{
    int i;
    for (i = 0; i < 4; i++) {
        q[i] = (float)h[i] * (1.0f / 32768.0f);
    }
}

/* Normalised blend: a*w + b*x, b's sign flipped when the weighted dot product is negative; into r[4]. */
static void nlerp_002A3110(float *r, const float *a, const float *b, float w, float x)
{
    float p[4], s[4], d[4], sq[4], dt, l, k;
    int i;
    for (i = 0; i < 4; i++) {
        p[i] = a[i] * w;
        s[i] = b[i] * x;
    }
    for (i = 0; i < 4; i++) {
        d[i] = p[i] + s[i];
        sq[i] = p[i] * s[i];
    }
    dt = ((sq[1] + sq[0]) + sq[2]) + sq[3];
    for (i = 0; i < 4; i++) {
        sq[i] = d[i] * d[i];
    }
    l = ((sq[0] + sq[1]) + sq[2]) + sq[3];
    if (neg_002A3110(dt)) {
        for (i = 0; i < 4; i++) {
            d[i] = p[i] - s[i];
        }
        for (i = 0; i < 4; i++) {
            sq[i] = d[i] * d[i];
        }
        l = ((sq[0] + sq[1]) + sq[2]) + sq[3];
    }
    k = rsqrt_002A3110(l);
    for (i = 0; i < 4; i++) {
        r[i] = d[i] * k;
    }
}

/* Moby animation: the pose of `count` joints of moby m into scratchpad 0x70000000 (64 bytes a joint). The class's
   joint table (m+0x24 -> +0x18, a quad per joint: bind translation, w the parent joint's address) and the frame
   (m+0x58; with a blend weight at m+0x44, a second frame at m+0x5C, normalised blend when m+0x40..0x43 differ) are
   DMA'd in; their rotations (s16 quaternions), scales and translations (8-byte entries: three s16, joint byte, flags)
   go into the joint slots; then the attachment lists at m+0x50 (blend) and m+0x54 (multiply or blend) are applied;
   then each joint's matrix times its parent's. Finally each joint's position (matrix row 3) is packed at
   0x70000000 + 16*j and, when buf > 0, also copied to buf. */
void func_002A3110(void *moby, int count, void *buf)
{
    unsigned char *m = (unsigned char *)moby;
    volatile unsigned int *dma = (volatile unsigned int *)0x1000D400;
    unsigned char *cls = *(unsigned char **)(m + 36);
    unsigned char *fa = *(unsigned char **)(m + 88);
    unsigned char *fb = *(unsigned char **)(m + 92);
    unsigned int blendw = *(unsigned int *)(m + 68);
    int nA0, nA1, nA2;
    unsigned int off;
    int i, j;

    *(unsigned int *)sp_002A3110(0x3720) = (unsigned int)(unsigned long)buf;

    /* the joint table, to 0x70003000 */
    dma[32] = 0x3000;
    dma[4] = *(unsigned int *)(cls + 24);
    dma[8] = count;
    *(unsigned int *)sp_002A3110(0x2FF8 + count * 16) = 0;
    *(unsigned int *)sp_002A3110(0x2FFC + count * 16) = 0;
    dma[0] = 0x100;

    nA0 = *(short *)(fa + 6);
    nA1 = *(short *)(fa + 10);
    nA2 = *(short *)(fa + 14);
    off = cls[8] << 3;
    for (i = 0; i < 4; i++) {
        *(unsigned int *)sp_002A3110(0x1FF0 + nA0 * 16 + i * 4) = 0;
    }
    *(unsigned int *)sp_002A3110(0x3728) = off;
    j = count;
    i = 0;
    do {
        int k;
        for (k = 0; k < 2; k++) {
            float *s = (float *)sp_002A3110((i + k) * 64);
            s[0] = 1.0f;
            s[1] = 1.0f;
            s[2] = 1.0f;
            s[3] = 0.0f;
            s[4] = 1.0f;
            s[5] = 1.0f;
            s[6] = 1.0f;
            s[7] = 0.0f;
        }
        i += 2;
        j -= 2;
    } while (j > 0);
    wait_002A3110(0x2FF8 + count * 16);

    /* frame A, to 0x70002000 */
    dma[32] = 0x70002000;
    dma[4] = (unsigned int)(unsigned long)(fa + 16);
    dma[8] = nA0;
    dma[0] = 0x100;

    j = count;
    i = 0;
    do {
        int k;
        for (k = 0; k < 4; k++) {
            float *src = (float *)sp_002A3110(0x3000 + (i + k) * 16);
            float *s = (float *)sp_002A3110((i + k) * 64);
            float v[4];
            v[0] = src[0];
            v[1] = src[1];
            v[2] = src[2];
            v[3] = src[3];
            s[8] = v[0];
            s[9] = v[1];
            s[10] = v[2];
            s[11] = v[3];
            s[12] = v[0] * 1.0f;
            s[13] = v[1] * 1.0f;
            s[14] = v[2] * 1.0f;
            ((unsigned int *)s)[15] = 0;
        }
        i += 4;
        j -= 4;
    } while (j > 0);

    if (blendw != 0) {
        float wx = bitsf_002A3110(blendw);
        float ww = 1.0f - wx;
        int nB0 = *(short *)(fb + 6), nB1 = *(short *)(fb + 10), nB2 = *(short *)(fb + 14);
        unsigned int *ls = (unsigned int *)sp_002A3110(0x2C00);
        unsigned int *lt = (unsigned int *)sp_002A3110(0x2D00);
        unsigned char *e;
        int n;

        *(unsigned int *)sp_002A3110(0x3724) = (unsigned int)((m[66] - m[67]) | (m[64] + 1 - m[65]));
        for (i = 0; i < 4; i++) {
            *(unsigned int *)sp_002A3110(0x25F0 + nB0 * 16 + i * 4) = 0;
        }
        wait_002A3110(0x1FF0 + nA0 * 16);

        /* frame B, to 0x70002600 */
        dma[4] = (unsigned int)(unsigned long)(fb + 16);
        dma[32] = 0x70002600;
        dma[8] = nB0;
        dma[0] = 0x100;

        /* A's scales (flagged entries) into +0, listed at 0x70002C00 */
        e = sp_002A3110(0x2000 + off);
        for (n = nA1; n > 0;) {
            unsigned int jt = e[6];
            unsigned int fl = e[7] >> 6;
            float *s;
            if ((int)(count - jt) <= 0) {
                break;
            }
            s = (float *)sp_002A3110(jt * 64);
            n--;
            if (fl != 0) {
                *ls++ = (unsigned int)(unsigned long)s;
                s[0] = (float)(int)*(unsigned short *)(e + 0) * 8.0f * (1.0f / 32768.0f);
                s[1] = (float)(int)*(unsigned short *)(e + 2) * 8.0f * (1.0f / 32768.0f);
                s[2] = (float)(int)*(unsigned short *)(e + 4) * 8.0f * (1.0f / 32768.0f);
                ((int *)s)[3] = -4;
            }
            e += 8;
        }
        /* A's translations into +32 (w kept), listed at 0x70002D00 */
        e = sp_002A3110(0x2000 + off + nA1 * 8);
        for (n = nA2; n != 0;) {
            unsigned int jt = e[6];
            float *s;
            unsigned int keep;
            if ((int)(count - jt) <= 0) {
                break;
            }
            s = (float *)sp_002A3110(jt * 64);
            *lt++ = (unsigned int)(unsigned long)s;
            keep = ((unsigned int *)s)[11];
            s[8] = (float)*(short *)(e + 0);
            s[9] = (float)*(short *)(e + 2);
            s[10] = (float)*(short *)(e + 4);
            ((unsigned int *)s)[11] = keep;
            ((int *)s)[15] = -4;
            e += 8;
            n--;
            if (n <= 0) {
                break;
            }
        }
        wait_002A3110(0x25F0 + nB0 * 16);
        off = *(unsigned int *)sp_002A3110(0x3728);
        /* B's scales into +16, added to the list unless A listed the joint (its +12 is -4) */
        e = sp_002A3110(0x2600 + off);
        for (n = nB1; n > 0;) {
            unsigned int jt = e[6];
            unsigned int fl = e[7] >> 6;
            float *s;
            int adv;
            if ((int)(count - jt) <= 0) {
                break;
            }
            s = (float *)sp_002A3110(jt * 64);
            *ls = (unsigned int)(unsigned long)s;
            adv = ((int *)s)[3];
            n--;
            if (fl != 0) {
                s[4] = (float)(int)*(unsigned short *)(e + 0) * 8.0f * (1.0f / 32768.0f);
                s[5] = (float)(int)*(unsigned short *)(e + 2) * 8.0f * (1.0f / 32768.0f);
                s[6] = (float)(int)*(unsigned short *)(e + 4) * 8.0f * (1.0f / 32768.0f);
                ((unsigned int *)s)[7] = 0;
                ls = (unsigned int *)((unsigned char *)ls + 4 + adv);
                if (n == 0) {
                    e += 8;
                    break;
                }
            }
            e += 8;
        }
        /* B's translations into +48, likewise */
        e = sp_002A3110(0x2600 + off + nB1 * 8);
        for (n = nB2; n > 0;) {
            unsigned int jt = e[6];
            float *s;
            int adv;
            if ((int)(count - jt) <= 0) {
                break;
            }
            s = (float *)sp_002A3110(jt * 64);
            *lt = (unsigned int)(unsigned long)s;
            adv = ((int *)s)[15];
            s[12] = (float)*(short *)(e + 0);
            s[13] = (float)*(short *)(e + 2);
            s[14] = (float)*(short *)(e + 4);
            s[15] = 1.0f;
            n--;
            lt = (unsigned int *)((unsigned char *)lt + 4 + adv);
            e += 8;
        }
        /* blend the listed scales (+0, +16 -> +16) and translations (+32, +48 -> +32), w words kept */
        {
            unsigned int *p;
            *ls = 0x70001E00;
            for (p = (unsigned int *)sp_002A3110(0x2C00); p != ls; p++) {
                float *s = (float *)(unsigned long)*p;
                float r[3];
                for (i = 0; i < 3; i++) {
                    r[i] = s[i] * ww + s[4 + i] * wx;
                }
                s[4] = r[0];
                s[5] = r[1];
                s[6] = r[2];
            }
            *lt = 0x70001E00;
            for (p = (unsigned int *)sp_002A3110(0x2D00); p != lt; p++) {
                float *s = (float *)(unsigned long)*p;
                float r[3];
                for (i = 0; i < 3; i++) {
                    r[i] = s[8 + i] * ww + s[12 + i] * wx;
                }
                s[8] = r[0];
                s[9] = r[1];
                s[10] = r[2];
            }
        }
        /* rotations: A*(1-w) + B*w, normalised (the shorter way) when the frames differ */
        {
            int nl = *(int *)sp_002A3110(0x3724) != 0;
            short *qa = (short *)sp_002A3110(0x2000);
            short *qb = (short *)sp_002A3110(0x2600);
            j = count;
            i = 0;
            do {
                int k;
                for (k = 0; k < 2; k++) {
                    float a[4], b[4], r[4];
                    float *s = (float *)sp_002A3110((i + k) * 64);
                    int c;
                    quat_002A3110(a, qa + k * 4);
                    quat_002A3110(b, qb + k * 4);
                    if (nl) {
                        nlerp_002A3110(r, a, b, ww, wx);
                    } else {
                        for (c = 0; c < 4; c++) {
                            r[c] = a[c] * ww + b[c] * wx;
                        }
                    }
                    for (c = 0; c < 4; c++) {
                        s[c] = r[c];
                    }
                }
                qa += 8;
                qb += 8;
                i += 2;
                j -= 2;
            } while (j > 0);
        }
    } else {
        unsigned char *e;
        int n;

        wait_002A3110(0x1FF0 + nA0 * 16);
        off = *(unsigned int *)sp_002A3110(0x3728);
        e = sp_002A3110(0x2000 + off);
        for (n = nA1; n > 0;) {
            unsigned int jt = e[6];
            unsigned int fl = e[7] >> 6;
            float *s;
            if ((int)(count - jt) <= 0) {
                break;
            }
            s = (float *)sp_002A3110(jt * 64);
            n--;
            e += 8;
            if (fl != 0) {
                s[4] = (float)(int)*(unsigned short *)(e - 8) * 8.0f * (1.0f / 32768.0f);
                s[5] = (float)(int)*(unsigned short *)(e - 6) * 8.0f * (1.0f / 32768.0f);
                s[6] = (float)(int)*(unsigned short *)(e - 4) * 8.0f * (1.0f / 32768.0f);
                ((unsigned int *)s)[7] = 0;
                if (n <= 0) {
                    break;
                }
            }
        }
        e = sp_002A3110(0x2000 + off + nA1 * 8);
        for (n = nA2; n != 0;) {
            unsigned int jt = e[6];
            float *s;
            unsigned int keep;
            if ((int)(count - jt) <= 0) {
                break;
            }
            s = (float *)sp_002A3110(jt * 64);
            keep = ((unsigned int *)s)[11];
            s[8] = (float)*(short *)(e + 0);
            s[9] = (float)*(short *)(e + 2);
            s[10] = (float)*(short *)(e + 4);
            ((unsigned int *)s)[11] = keep;
            e += 8;
            n--;
            if (n <= 0) {
                break;
            }
        }
        {
            short *qa = (short *)sp_002A3110(0x2000);
            j = count;
            i = 0;
            do {
                int k, c;
                for (k = 0; k < 4; k++) {
                    float a[4];
                    float *s = (float *)sp_002A3110((i + k) * 64);
                    quat_002A3110(a, qa + k * 4);
                    for (c = 0; c < 4; c++) {
                        s[c] = a[c];
                    }
                }
                qa += 16;
                i += 4;
                j -= 4;
            } while (j > 0);
        }
    }

    /* attachments (retail 0x2A3B10 and 0x2A3C88) */
    {
        unsigned int l0 = *(unsigned int *)(m + 80);
        unsigned int l1 = *(unsigned int *)(m + 84);

        if (l0 != 0 || l1 != 0) {
            unsigned char *at = (unsigned char *)(unsigned long)l0;
            unsigned char *end = sp_002A3110(count * 64);

            while (at != 0) {
                int nrec = *(unsigned short *)(at + 2) * 3;
                float wx = *(float *)(at + 8);
                float ww;
                unsigned char *r = sp_002A3110(0x2000);
                unsigned char *rend;

                dma[32] = 8192;
                dma[4] = *(unsigned int *)(at + 16);
                dma[8] = nrec;
                dma[0] = 256;
                rend = sp_002A3110(0x2000 + nrec * 16);
                at = *(unsigned char **)(at + 28);
                *(unsigned int *)(rend + 44) = 0x70001E00;
                ww = 1.0f - wx;
                while (dma[0] & 0x100) {
                }
                for (;;) {
                    float *jt = (float *)(unsigned long)*(unsigned int *)(r + 44);
                    float *rq = (float *)r;
                    float q[4], sc[3], tr[3];
                    unsigned int rw;
                    if ((int)((unsigned int)(unsigned long)end - (unsigned int)(unsigned long)jt) <= 0) {
                        break;
                    }
                    nlerp_002A3110(q, jt, rq, ww, wx);
                    for (i = 0; i < 3; i++) {
                        sc[i] = jt[4 + i] * ww + rq[4 + i] * wx;
                        tr[i] = jt[8 + i] * ww + rq[8 + i] * wx;
                    }
                    rw = *(unsigned int *)(r + 28);
                    jt[4] = sc[0];
                    jt[5] = sc[1];
                    jt[6] = sc[2];
                    jt[8] = tr[0];
                    jt[9] = tr[1];
                    jt[10] = tr[2];
                    if (((unsigned int *)jt)[7] == 0) {
                        ((unsigned int *)jt)[7] = rw;
                    }
                    jt[0] = q[0];
                    jt[1] = q[1];
                    jt[2] = q[2];
                    jt[3] = q[3];
                    r += 48;
                    if (r == rend) {
                        break;
                    }
                }
            }

            at = (unsigned char *)(unsigned long)l1;
            while (at != 0) {
                unsigned char *rc = at;
                float *jt = (float *)(unsigned long)*(unsigned int *)(rc + 4);
                int mode = rc[3];
                float *rq = (float *)(rc + 16);
                float q[4], sc[3], tr[3];

                at = *(unsigned char **)(rc + 8);
                if ((int)((unsigned int)(unsigned long)end - (unsigned int)(unsigned long)jt) <= 0) {
                    continue;
                }
                if (mode == 0) {
                    /* the record's rotation times the joint's; scales multiplied, translations added */
                    float c[3], d3[3], a14[3], a15[3], ww4, dsum;
                    ww4 = rq[3] * jt[3];
                    for (i = 0; i < 3; i++) {
                        d3[i] = rq[i] * jt[i];
                        a14[i] = rq[i] * jt[3];
                        a15[i] = jt[i] * rq[3];
                    }
                    {
                        float t0 = jt[1] * rq[2];
                        float t1 = jt[2] * rq[0];
                        float t2 = jt[0] * rq[1];
                        c[0] = t0 - rq[1] * jt[2];
                        c[1] = t1 - rq[2] * jt[0];
                        c[2] = t2 - rq[0] * jt[1];
                    }
                    dsum = (d3[0] + d3[1]) + d3[2];
                    for (i = 0; i < 3; i++) {
                        q[i] = a14[i] + a15[i];
                        q[i] = q[i] + c[i];
                    }
                    q[3] = ww4 - dsum;
                    for (i = 0; i < 3; i++) {
                        sc[i] = jt[4 + i] * rq[4 + i];
                        tr[i] = jt[8 + i] + rq[8 + i];
                    }
                } else {
                    /* blend toward the record by its weight (+0xC) */
                    float wx = *(float *)(rc + 12);
                    float ww = 1.0f - wx;
                    nlerp_002A3110(q, jt, rq, ww, wx);
                    for (i = 0; i < 3; i++) {
                        sc[i] = jt[4 + i] * ww + rq[4 + i] * wx;
                        tr[i] = jt[8 + i] * ww + rq[8 + i] * wx;
                    }
                }
                jt[0] = q[0];
                jt[1] = q[1];
                jt[2] = q[2];
                jt[3] = q[3];
                jt[4] = sc[0];
                jt[5] = sc[1];
                jt[6] = sc[2];
                jt[8] = tr[0];
                jt[9] = tr[1];
                jt[10] = tr[2];
            }
        }
    }

    /* the hierarchy (retail 0x2A37E0): world = parent * (rotation * scale, translation) */
    {
        float P[16];
        unsigned char *s = sp_002A3110(0);
        unsigned char *end = sp_002A3110(count * 64);

        *(unsigned int *)(end + 44) = SPR_002A3110;
        for (i = 0; i < 16; i++) {
            P[i] = (i % 5 == 0) ? 1.0f : 0.0f;
        }
        do {
            float *q = (float *)s;
            float *sc = (float *)(s + 16);
            float *tr = (float *)(s + 32);
            float q2[4], a12[3], a13[3], a14y, a14z, a15z;
            float r0[4], r1[4], r2[4], r3[4], o[16];
            unsigned int par;
            int c;

            for (c = 0; c < 4; c++) {
                q2[c] = q[c] + q[c];
            }
            for (c = 0; c < 3; c++) {
                a12[c] = q2[c] * q[3];
                a13[c] = q2[c] * q[0];
            }
            a14y = q2[1] * q[1];
            a14z = q2[2] * q[1];
            a15z = q2[2] * q[2];
            r0[0] = 1.0f; r0[1] = 0.0f; r0[2] = 0.0f; r0[3] = 0.0f;
            r1[0] = 0.0f; r1[1] = 1.0f; r1[2] = 0.0f; r1[3] = 0.0f;
            r2[0] = 0.0f; r2[1] = 0.0f; r2[2] = 1.0f; r2[3] = 0.0f;
            r3[0] = 0.0f; r3[1] = 0.0f; r3[2] = 0.0f; r3[3] = 1.0f;
            r1[0] = 0.0f + a12[2];
            r2[0] = 0.0f - a12[1];
            r2[1] = 0.0f + a12[0];
            r0[0] = r0[0] - a14y;
            r1[1] = r1[1] - a13[0];
            r2[2] = r2[2] - a13[0];
            r0[1] = a13[1] - a12[2];
            r0[2] = a13[2] + a12[1];
            r1[2] = a14z - a12[0];
            r1[0] = r1[0] + a13[1];
            r2[0] = r2[0] + a13[2];
            r2[1] = r2[1] + a14z;
            r0[0] = r0[0] - a15z;
            r1[1] = r1[1] - a15z;
            r2[2] = r2[2] - a14y;
            for (c = 0; c < 3; c++) {
                r0[c] = r0[c] * sc[0];
                r1[c] = r1[c] * sc[1];
                r2[c] = r2[c] * sc[2];
                r3[c] = r3[c] + tr[c];
            }
            par = *(unsigned int *)(s + 64 + 44);
            for (c = 0; c < 4; c++) {
                float a;
                a = P[c] * r0[0];
                a = a + P[4 + c] * r0[1];
                o[c] = a + P[8 + c] * r0[2];
                a = P[c] * r1[0];
                a = a + P[4 + c] * r1[1];
                o[4 + c] = a + P[8 + c] * r1[2];
                a = P[c] * r2[0];
                a = a + P[4 + c] * r2[1];
                o[8 + c] = a + P[8 + c] * r2[2];
                a = P[c] * r3[0];
                a = a + P[4 + c] * r3[1];
                a = a + P[8 + c] * r3[2];
                o[12 + c] = a + P[12 + c] * 1.0f;
            }
            for (c = 0; c < 16; c++) {
                ((float *)s)[c] = o[c];
            }
            if (par == 0) {
                for (c = 0; c < 16; c++) {
                    P[c] = (c % 5 == 0) ? 1.0f : 0.0f;
                }
            } else {
                float *pp = (float *)(unsigned long)par;
                for (c = 0; c < 16; c++) {
                    P[c] = pp[c];
                }
            }
            s += 64;
        } while (s != end);
    }

    /* positions packed at 0x70000000 + 16*j, and copied to buf */
    {
        int b = (int)(unsigned long)buf;
        float *dst = (float *)sp_002A3110(0);
        float *src = (float *)sp_002A3110(0);
        float *out = (float *)(unsigned long)(unsigned int)b;

        if (b >= 0) {
            j = count;
            do {
                float v1[4], v2[4];
                int c;
                for (c = 0; c < 4; c++) {
                    v1[c] = src[12 + c];
                    v2[c] = src[28 + c];
                }
                src += 32;
                for (c = 0; c < 4; c++) {
                    dst[c] = v1[c];
                }
                for (c = 0; c < 4; c++) {
                    dst[4 + c] = v2[c];
                }
                dst += 8;
                j -= 2;
                if (b > 0) {
                    for (c = 0; c < 4; c++) {
                        out[c] = v1[c];
                    }
                    if (j < 0) {
                        break;
                    }
                    for (c = 0; c < 4; c++) {
                        out[4 + c] = v2[c];
                    }
                    out += 8;
                }
            } while (j > 0);
        }
    }
}
