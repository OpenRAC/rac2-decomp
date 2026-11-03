/* functional: medium. Gate: SAME on 12 calls (level00 8, level03 4), all with flags 0x300/0x301, so the obj+80 and obj+84 list blocks (retail 0x2A2E88-0x2A2FEC, 0x2A3000-0x2A3104) and the negative-dot branches of the normalised blend never ran; they were read against the assembly instruction by instruction. Written from the hand-written assembly, plain floats in place of VU0 code in its order. The toSPR transfers (channel 9 at 0x1000D400) and the closing fromSPR transfer (channel 8 at 0x1000D000) are retail's register writes in retail's order; each toSPR wait polls the last doubleword of its destination (cleared first) or channel 9's CHCR busy bit, as retail does. Retail then waits for the fromSPR transfer with sync and bc0f (COP0's CPCOND0), which reads no memory and has no C form; it is left out: the port (asm.dma_done) and fcheck finish a transfer at the CHCR store that starts it. Retail's unrolled loops fill records past the bone count (to a multiple of 2 or 4) and so does the C; its loads of one entry past each list only read and are left out. Where retail loads the next record before storing the current one (the two blend lists and the obj+80 list) the C does the same, so a bone listed twice behaves as retail. vrsqrt of 0 gives the VU's largest float; VU ftoi saturates, as here; the VU multiply by 1 that makes the +48 copy of the default translations flushes a denormal to a signed 0, written out. */

extern float sqrtf(float);
extern char D_001C5540[];

typedef union {
    float f;
    unsigned int u;
} FU_002A2450;

static unsigned int fbits_002A2450(float f)
{
    FU_002A2450 v;
    v.f = f;
    return v.u;
}

static float fword_002A2450(unsigned int u)
{
    FU_002A2450 v;
    v.u = u;
    return v.f;
}

static void get4_002A2450(float *v, const unsigned char *s)
{
    const float *i = (const float *)s;

    v[0] = i[0];
    v[1] = i[1];
    v[2] = i[2];
    v[3] = i[3];
}

static void put4_002A2450(unsigned char *d, const float *v)
{
    float *o = (float *)d;
    float a = v[0], b = v[1], c = v[2], e = v[3];

    o[0] = a;
    o[1] = b;
    o[2] = c;
    o[3] = e;
}

/* The four signed halfwords at p, as floats over 32768 (VU itof15). */
static void rot_002A2450(float *q, const unsigned char *p)
{
    int k;

    for (k = 0; k < 4; k++) {
        q[k] = (float)*(const short *)(p + 2 * k) * (1.0f / 32768.0f);
    }
}

/* A packed scale channel: three unsigned halfwords times 8, over 32768; w = 0. */
static void scale_002A2450(float *v, const unsigned char *e)
{
    int k;

    for (k = 0; k < 3; k++) {
        v[k] = (float)(int)((unsigned int)*(const unsigned short *)(e + 2 * k) << 3) * (1.0f / 32768.0f);
    }
    v[3] = 0.0f;
}

/* A packed translation channel: three signed halfwords; w = 1. */
static void trans_002A2450(float *v, const unsigned char *e)
{
    int k;

    for (k = 0; k < 3; k++) {
        v[k] = (float)*(const short *)(e + 2 * k);
    }
    v[3] = 1.0f;
}

/* VU0 vrsqrt with vf0.w: 1 / sqrt(|x|), the largest float for 0. */
static float rsqrt_002A2450(float x)
{
    if ((fbits_002A2450(x) & 0x7FFFFFFFu) == 0) {
        return 3.40282347e38f;
    }
    return 1.0f / sqrtf(x < 0.0f ? -x : x);
}

/* (1 - t) a + t b over four components, normalised along the shorter arc (VU0 order: products, sum, dot). */
static void slerpn_002A2450(float *q, const float *a, const float *b, float u, float t)
{
    float qa[4], qb[4], m[4], dot, len, s;
    int k;

    for (k = 0; k < 4; k++) {
        qa[k] = a[k] * u;
        qb[k] = b[k] * t;
    }
    for (k = 0; k < 4; k++) {
        q[k] = qa[k] + qb[k];
        m[k] = qa[k] * qb[k];
    }
    dot = ((m[1] + m[0]) + 1.0f * m[2]) + 1.0f * m[3];
    len = ((q[0] * q[0] + q[1] * q[1]) + 1.0f * (q[2] * q[2])) + 1.0f * (q[3] * q[3]);
    if ((fbits_002A2450(dot) >> 31) != 0) {
        for (k = 0; k < 4; k++) {
            q[k] = qa[k] - qb[k];
        }
        len = ((q[0] * q[0] + q[1] * q[1]) + 1.0f * (q[2] * q[2])) + 1.0f * (q[3] * q[3]);
    }
    s = rsqrt_002A2450(len);
    for (k = 0; k < 4; k++) {
        q[k] = q[k] * s;
    }
}

/* VU ftoi: truncate toward zero, saturating to the int range. */
static int ftoi_002A2450(float x)
{
    if (x >= 2147483648.0f) {
        return 0x7FFFFFFF;
    }
    if (x <= -2147483648.0f) {
        return (int)0x80000000;
    }
    return (int)x;
}

/* Take a pose snapshot of an animated object into blend slot (flags & 0xFF): unpack its current frame (obj+88)
   and, when the blend weight obj+68 is not 0, the next frame (obj+92) into 64-byte bone records in the
   scratchpad (+0 rotation, +16 scale with a flag word at +28, +32 translation), blending scales and translations
   by (1 - t, t) and rotations the same way, normalised along the shorter arc unless the frame bytes obj+64..67
   say the frames are adjacent. Unless flag 0x200, blend in the poses listed from obj+80 (each: +2 count, +8
   weight, +16 packed pose, +28 next); unless flag 0x100, compose the parent links listed from obj+84 (each: +3
   blend flag, +4 record, +8 next, +12 weight, +16 rotation, +32 scale, +48 translation). Then pack the pose
   (n rotations as 4 x s16, scales differing from 1 and translations differing from the model's defaults
   obj+36 -> +24 as 8-byte entries tagged with the bone) behind a 16-byte header and send it to
   D_001C5540 + slot * 2048. */
void func_002A2450(void *obj, int flags)
{
    unsigned char *o = obj;
    unsigned char *S = (unsigned char *)0x70000000;
    volatile unsigned int *to = (volatile unsigned int *)0x1000D400;
    volatile unsigned int *from = (volatile unsigned int *)0x1000D000;
    unsigned char *model = *(unsigned char **)(o + 36);
    unsigned char *A = *(unsigned char **)(o + 88);
    unsigned char *B = *(unsigned char **)(o + 92);
    unsigned int defs = *(unsigned int *)(model + 24);
    unsigned int n = model[8];
    unsigned int tw;
    unsigned int l80, l84;
    float one[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
    int aq, ac1, ac2;
    unsigned int i;
    int k;

    to[32] = 0x2000;
    to[4] = defs;
    to[8] = n;
    *(unsigned long *)(S + 0x1FF8 + n * 16) = 0;
    to[0] = 0x100;
    A += 16;
    B += 16;
    aq = *(short *)(A - 10);
    ac1 = *(short *)(A - 6);
    ac2 = *(short *)(A - 2);
    tw = *(unsigned int *)(o + 68);
    *(unsigned long *)(S + 0x2FF0 + aq * 16) = 0;
    *(unsigned long *)(S + 0x2FF8 + aq * 16) = 0;

    for (i = 0; i < ((n + 1) & ~1u); i++) {
        put4_002A2450(S + 64 * i, one);
        put4_002A2450(S + 64 * i + 16, one);
    }

    while (*(volatile unsigned long *)(S + 0x1FF8 + n * 16) == 0) {
    }
    to[32] = 0x70003000;
    to[4] = (unsigned int)A;
    to[8] = aq;
    to[0] = 0x100;

    /* Default translations: +32 as sent, +48 times 1 (the VU flushes a denormal to a signed 0) with w = 0. */
    for (i = 0; i < ((n + 3) & ~3u); i++) {
        float v[4];
        unsigned int w[4];
        get4_002A2450(v, S + 0x2000 + 16 * i);
        put4_002A2450(S + 64 * i + 32, v);
        for (k = 0; k < 3; k++) {
            w[k] = fbits_002A2450(v[k]);
            if ((w[k] & 0x7F800000u) == 0) {
                w[k] &= 0x80000000u;
            }
        }
        w[3] = 0;
        for (k = 0; k < 4; k++) {
            *(unsigned int *)(S + 64 * i + 48 + 4 * k) = w[k];
        }
    }

    if (tw != 0) {
        float t = fword_002A2450(tw);
        float u;
        int same;
        int bq, bc1, bc2;
        unsigned int *ls = (unsigned int *)(S + 0x3C00);
        unsigned int *lt = (unsigned int *)(S + 0x3D00);
        unsigned int *p;
        unsigned char *e;
        unsigned char *r;

        same = (int)(o[66] - o[67]) | (int)(o[64] + 1 - o[65]);
        bq = *(short *)(B - 10);
        bc1 = *(short *)(B - 6);
        bc2 = *(short *)(B - 2);
        *(unsigned long *)(S + 0x35F0 + bq * 16) = 0;
        *(unsigned long *)(S + 0x35F8 + bq * 16) = 0;
        u = 1.0f - t;
        while (*(volatile unsigned long *)(S + 0x2FF0 + aq * 16) == 0) {
        }
        to[4] = (unsigned int)B;
        to[32] = 0x70003600;
        to[8] = bq;
        to[0] = 0x100;

        /* Frame A: scales into +0 (listed in ls, +12 = -4), translations into +32 (listed in lt, +60 = -4). */
        e = S + 0x3000 + n * 8;
        if (ac1 != 0) {
            do {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                r = S + e[6] * 64;
                scale_002A2450(v, e);
                e += 8;
                *ls++ = (unsigned int)r;
                *(unsigned int *)(r + 28) = (unsigned int)(d >> 62) - 1;
                put4_002A2450(r, v);
                *(int *)(r + 12) = -4;
            } while (--ac1 > 0);
        }
        if (ac2 != 0) {
            do {
                float v[4];
                unsigned int keep;
                r = S + e[6] * 64;
                trans_002A2450(v, e);
                e += 8;
                *lt++ = (unsigned int)r;
                keep = *(unsigned int *)(r + 44);
                put4_002A2450(r + 32, v);
                *(unsigned int *)(r + 44) = keep;
                *(int *)(r + 60) = -4;
            } while (--ac2 > 0);
        }
        while (*(volatile unsigned long *)(S + 0x35F0 + bq * 16) == 0) {
        }

        /* Frame B: scales into +16, translations into +48; a bone frame A listed is not listed again. */
        e = S + 0x3600 + n * 8;
        if (bc1 != 0) {
            do {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                int skip;
                r = S + e[6] * 64;
                scale_002A2450(v, e);
                e += 8;
                *ls = (unsigned int)r;
                skip = *(int *)(r + 12);
                put4_002A2450(r + 16, v);
                *(unsigned int *)(r + 28) = (unsigned int)(d >> 62) - 1;
                ls = (unsigned int *)((unsigned char *)ls + 4 + skip);
            } while (--bc1 != 0);
        }
        if (bc2 != 0) {
            do {
                float v[4];
                int skip;
                r = S + e[6] * 64;
                trans_002A2450(v, e);
                e += 8;
                *lt = (unsigned int)r;
                skip = *(int *)(r + 60);
                put4_002A2450(r + 48, v);
                lt = (unsigned int *)((unsigned char *)lt + 4 + skip);
            } while (--bc2 > 0);
        }

        /* Blend the listed scales (+0, +16 into +16) and translations (+32, +48 into +32); the result's word 3
           is put back. Each next record is loaded before the current one is stored. */
        *ls = (unsigned int)(S + 0x1E00);
        p = (unsigned int *)(S + 0x3C00);
        if (p != ls) {
            float a[4], b[4];
            unsigned char *cur = (unsigned char *)*p;
            get4_002A2450(a, cur);
            get4_002A2450(b, cur + 16);
            do {
                float c[4];
                unsigned int keep = *(unsigned int *)(cur + 28);
                unsigned char *nx = (unsigned char *)p[1];
                for (k = 0; k < 3; k++) {
                    c[k] = a[k] * u + b[k] * t;
                }
                c[3] = 0.0f;
                p++;
                get4_002A2450(a, nx);
                get4_002A2450(b, nx + 16);
                put4_002A2450(cur + 16, c);
                *(unsigned int *)(cur + 28) = keep;
                cur = nx;
            } while (p != ls);
        }
        *lt = (unsigned int)(S + 0x1E00);
        p = (unsigned int *)(S + 0x3D00);
        if (p != lt) {
            float a[4], b[4];
            unsigned char *cur = (unsigned char *)*p;
            get4_002A2450(a, cur + 32);
            get4_002A2450(b, cur + 48);
            do {
                float c[4];
                unsigned int keep = *(unsigned int *)(cur + 44);
                unsigned char *nx = (unsigned char *)p[1];
                for (k = 0; k < 3; k++) {
                    c[k] = a[k] * u + b[k] * t;
                }
                c[3] = 0.0f;
                p++;
                get4_002A2450(a, nx + 32);
                get4_002A2450(b, nx + 48);
                put4_002A2450(cur + 32, c);
                *(unsigned int *)(cur + 44) = keep;
                cur = nx;
            } while (p != lt);
        }

        /* Rotations: (1 - t) a + t b, normalised along the shorter arc unless the frames are adjacent. */
        for (i = 0; i < ((n + 1) & ~1u); i++) {
            float qa[4], qb[4], q[4];

            rot_002A2450(qa, S + 0x3000 + i * 8);
            rot_002A2450(qb, S + 0x3600 + i * 8);
            if (same == 0) {
                for (k = 0; k < 4; k++) {
                    q[k] = qa[k] * u + qb[k] * t;
                }
            } else {
                slerpn_002A2450(q, qa, qb, u, t);
            }
            put4_002A2450(S + 64 * i, q);
        }
    } else {
        unsigned char *e;

        while (*(volatile unsigned long *)(S + 0x2FF0 + aq * 16) == 0) {
        }
        e = S + 0x3000 + n * 8;
        if (ac1 != 0) {
            do {
                unsigned long d = *(unsigned long *)e;
                float v[4];
                unsigned char *r = S + e[6] * 64;
                scale_002A2450(v, e);
                e += 8;
                put4_002A2450(r + 16, v);
                *(unsigned int *)(r + 28) = (unsigned int)(d >> 62) - 1;
            } while (--ac1 > 0);
        }
        if (ac2 != 0) {
            do {
                float v[4];
                unsigned int keep;
                unsigned char *r = S + e[6] * 64;
                trans_002A2450(v, e);
                e += 8;
                keep = *(unsigned int *)(r + 44);
                put4_002A2450(r + 32, v);
                *(unsigned int *)(r + 44) = keep;
            } while (--ac2 > 0);
        }
        for (i = 0; i < ((n + 3) & ~3u); i++) {
            float q[4];
            rot_002A2450(q, S + 0x3000 + i * 8);
            put4_002A2450(S + 64 * i, q);
        }
    }

    l80 = *(unsigned int *)(o + 80);
    l84 = *(unsigned int *)(o + 84);
    if (l80 != 0 || l84 != 0) {
        /* Blend other objects' packed poses into the matching records (each 48-byte record's word 11 names
           the record it goes to). */
        if ((flags & 0x200) == 0) {
            unsigned char *ent = (unsigned char *)l80;
            while (ent != 0) {
                unsigned int cnt = *(unsigned short *)(ent + 2) * 3;
                unsigned char *in = S + 0x2800;
                unsigned char *end;
                unsigned char *cur;
                float t, u;
                float ra[4], rb[4], rc[4];

                to[32] = 0x2800;
                to[4] = *(unsigned int *)(ent + 16);
                to[8] = cnt;
                to[0] = 0x100;
                end = S + 0x2800 + cnt * 16;
                t = *(float *)(ent + 8);
                ent = *(unsigned char **)(ent + 28);
                *(unsigned int *)(end + 44) = (unsigned int)(S + 0x1E00);
                u = 1.0f - t;
                while ((to[0] & 0x100) != 0) {
                }
                cur = *(unsigned char **)(in + 44);
                get4_002A2450(ra, cur);
                get4_002A2450(rb, cur + 16);
                get4_002A2450(rc, cur + 32);
                do {
                    float xa[4], xb[4], xc[4], q[4];
                    unsigned int w28 = *(unsigned int *)(in + 28);
                    unsigned char *nx = *(unsigned char **)(in + 92);

                    get4_002A2450(xa, in);
                    get4_002A2450(xb, in + 16);
                    get4_002A2450(xc, in + 32);
                    slerpn_002A2450(q, ra, xa, u, t);
                    for (k = 0; k < 3; k++) {
                        rb[k] = rb[k] * u + xb[k] * t;
                        rc[k] = rc[k] * u + xc[k] * t;
                    }
                    put4_002A2450(cur + 16, rb);
                    put4_002A2450(cur + 32, rc);
                    get4_002A2450(ra, nx);
                    get4_002A2450(rb, nx + 16);
                    get4_002A2450(rc, nx + 32);
                    if (*(unsigned int *)(cur + 28) == 0) {
                        *(unsigned int *)(cur + 28) = w28;
                    }
                    in += 48;
                    put4_002A2450(cur, q);
                    cur = nx;
                } while (in != end);
            }
        }

        /* Compose the listed links: rotation product and scale product, translation sum, or a normalised
           blend by the link's weight. */
        if ((flags & 0x100) == 0) {
            unsigned char *ent = (unsigned char *)l84;
            while (ent != 0) {
                unsigned char *r = *(unsigned char **)(ent + 4);
                unsigned char *nxe;
                float a[4], b[4], sa[4], sb[4], ta[4], tb[4];

                get4_002A2450(a, r);
                get4_002A2450(sa, r + 16);
                get4_002A2450(ta, r + 32);
                get4_002A2450(b, ent + 16);
                get4_002A2450(sb, ent + 32);
                get4_002A2450(tb, ent + 48);
                nxe = *(unsigned char **)(ent + 8);
                if (ent[3] == 0) {
                    float m[4], aw[3], bw[3], c[3], d, qw;
                    qw = b[3] * a[3];
                    for (k = 0; k < 3; k++) {
                        m[k] = b[k] * a[k];
                        aw[k] = b[k] * a[3];
                        bw[k] = a[k] * b[3];
                    }
                    c[0] = a[1] * b[2] - b[1] * a[2];
                    c[1] = a[2] * b[0] - b[2] * a[0];
                    c[2] = a[0] * b[1] - b[0] * a[1];
                    d = (m[0] + m[1]) + 1.0f * m[2];
                    for (k = 0; k < 3; k++) {
                        a[k] = (aw[k] + bw[k]) + c[k];
                    }
                    a[3] = qw - d;
                    for (k = 0; k < 3; k++) {
                        sa[k] = sa[k] * sb[k];
                        ta[k] = ta[k] + tb[k];
                    }
                } else {
                    float t = *(float *)(ent + 12);
                    float u = 1.0f - t;
                    float q[4];
                    slerpn_002A2450(q, a, b, u, t);
                    for (k = 0; k < 3; k++) {
                        sa[k] = sa[k] * u + sb[k] * t;
                        ta[k] = ta[k] * u + tb[k] * t;
                    }
                    for (k = 0; k < 4; k++) {
                        a[k] = q[k];
                    }
                }
                ent = nxe;
                put4_002A2450(r, a);
                put4_002A2450(r + 16, sa);
                put4_002A2450(r + 32, ta);
            }
        }
    }

    /* Pack: n rotations (4 x s16) at +16; scales that are not 1 (3 x u16 by 4096, bone, flag byte) and
       translations that differ from the model's defaults (3 x s16, bone) gathered at 0x2800 and 0x2C00. */
    {
        unsigned char *ps = S + 0x2800;
        unsigned char *pt = S + 0x2C00;
        unsigned char *out = S + 16;
        unsigned int nb, sb, tb, qw;

        for (i = 0; i != n; i++) {
            const float *rec = (const float *)(S + 64 * i);
            const float *def = (const float *)(S + 0x2000 + 16 * i);
            unsigned short hr[4], hs[3], ht[3], hd[3];

            for (k = 0; k < 4; k++) {
                int v = ftoi_002A2450(rec[k] * 32768.0f);
                if (v < -32768) {
                    v = -32768;
                }
                if (v > 32767) {
                    v = 32767;
                }
                hr[k] = (unsigned short)v;
            }
            for (k = 0; k < 3; k++) {
                unsigned int v = (unsigned int)ftoi_002A2450(rec[4 + k] * 32768.0f) >> 3;
                if (v > 0xFFFF) {
                    v = 0xFFFF;
                }
                hs[k] = (unsigned short)v;
                ht[k] = (unsigned short)ftoi_002A2450(rec[8 + k]);
                hd[k] = (unsigned short)ftoi_002A2450(def[k]);
            }
            for (k = 0; k < 4; k++) {
                *(unsigned short *)(out + 2 * k) = hr[k];
            }
            out += 8;
            if (hs[0] != 0x1000 || hs[1] != 0x1000 || hs[2] != 0x1000) {
                unsigned int fl = *(const unsigned int *)(rec + 7);
                for (k = 0; k < 3; k++) {
                    *(unsigned short *)(ps + 2 * k) = hs[k];
                }
                ps[6] = (unsigned char)i;
                ps[7] = (unsigned char)((fl & 0x80) ^ 0x80);
                ps += 8;
            }
            if (ht[0] != hd[0] || ht[1] != hd[1] || ht[2] != hd[2]) {
                for (k = 0; k < 3; k++) {
                    *(unsigned short *)(pt + 2 * k) = ht[k];
                }
                *(unsigned short *)(pt + 6) = (unsigned short)i;
                pt += 8;
            }
        }

        sb = (unsigned int)(ps - (S + 0x2800));
        tb = (unsigned int)(pt - (S + 0x2C00));
        nb = n * 8;
        qw = (nb + sb + tb + 8) >> 4;
        *(unsigned short *)(S + 8) = (unsigned short)nb;
        *(unsigned short *)(S + 12) = (unsigned short)(nb + sb);
        *(unsigned long *)S = 0;
        *(unsigned short *)(S + 6) = (unsigned short)qw;
        *(unsigned short *)(S + 10) = (unsigned short)(sb >> 3);
        *(unsigned short *)(S + 14) = (unsigned short)(tb >> 3);
        for (k = 0; k < (int)sb; k += 8) {
            *(unsigned long *)out = *(unsigned long *)(S + 0x2800 + k);
            out += 8;
        }
        for (k = 0; k < (int)tb; k += 8) {
            *(unsigned long *)out = *(unsigned long *)(S + 0x2C00 + k);
            out += 8;
        }
        *(unsigned long *)out = 1;

        from[32] = 0;
        from[8] = qw + 1;
        from[4] = (unsigned int)(D_001C5540 + (flags & 0xFF) * 2048);
        *(volatile unsigned int *)0x1000E010 = 0x100;
        from[0] = 0x100;
    }
}
