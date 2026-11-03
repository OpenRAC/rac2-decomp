/* functional: medium. Written from the hand-written VU0/MMI assembly (CollLine): plain floats in the VU's order (sums as (x + y) + 1*z, ACC chains left to right), the same reads, writes and calls in the same order. VU rounding is not reproduced; vdiv/vrsqrt by zero give +-FLT_MAX as the VU does; vsqrt is sqrtf of |x|. The MAC-flag tests (cfc2 $vi17) are the sign bits of min(a, b), of max(a, b) - 1024 and, for capsules, of (axis x dir)^2 - 1. The toSPR DMA of each level cell's chunk (0x1000D400 registers, double-buffered at scratchpad 0x70000000/0x70001000) is written as retail's register stores and its STR polls. func_00276158, the octree lookup retail calls with register arguments, is written out here (cell_002761F8); func_002A3110 is a real call. The w words of the result quads (D_001BAF80+0x20, +0x40..+0x70 and the ring record's first quad) are stale VU0 register contents in retail; here 0. Retail's caller-saved s registers kept in the upper halves (pcpyld/pcpyud) have no C spelling. With the stamp D_001BAF80+0x10 negative, or an end below 0, retail exits through its result code with the caller's $s5/$s6 (cleared only later), so a nonzero caller $s6 would write results and return 1; here 0, the intended exit. */
extern unsigned char D_001BAF80[];
extern unsigned char *D_001B1B5C;
extern unsigned char D_001D24E0[];
extern unsigned char D_001BF200[];
extern float sqrtf(float);
extern void func_002A3110(void *moby, int count, void *buf);

#define FMAX_002761F8 3.40282347e+38f

static int fbits_002761F8(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i;
}

static float bitsf_002761F8(unsigned int i)
{
    union {
        float f;
        unsigned int i;
    } u;
    u.i = i;
    return u.f;
}

static int neg_002761F8(float f)
{
    return fbits_002761F8(f) < 0;
}

static float vdiv_002761F8(float n, float d)
{
    float q;
    if (d == 0.0f) {
        return ((fbits_002761F8(n) ^ fbits_002761F8(d)) < 0) ? -FMAX_002761F8 : FMAX_002761F8;
    }
    q = n / d;
    if (q > FMAX_002761F8) {
        q = FMAX_002761F8;
    } else if (q < -FMAX_002761F8) {
        q = -FMAX_002761F8;
    }
    return q;
}

static int ftoi0_002761F8(float f)
{
    if (f >= 2147483647.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)(-2147483647 - 1);
    }
    return (int)f;
}

static float sum_002761F8(const float *a)
{
    return (a[0] + a[1]) + a[2];
}

static float dot_002761F8(const float *a, const float *b)
{
    float x = a[0] * b[0];
    float y = a[1] * b[1];
    float z = a[2] * b[2];
    return (x + y) + z;
}

/* r = a x b as vopmula ACC,a,b / vopmsub r,b,a compute it */
static void cross_002761F8(float *r, const float *a, const float *b)
{
    float t0 = a[1] * b[2];
    float t1 = a[2] * b[0];
    float t2 = a[0] * b[1];
    float x = t0 - b[1] * a[2];
    float y = t1 - b[2] * a[0];
    float z = t2 - b[0] * a[1];
    r[0] = x;
    r[1] = y;
    r[2] = z;
}

/* r = (m0*v.x + m1*v.y) + m2*v.z */
static void rot_002761F8(float *r, const float *m0, const float *m1, const float *m2, const float *v)
{
    float o[3];
    int i;
    for (i = 0; i < 3; i++) {
        float a = m0[i] * v[0];
        a = a + m1[i] * v[1];
        o[i] = a + m2[i] * v[2];
    }
    r[0] = o[0];
    r[1] = o[1];
    r[2] = o[2];
}

static float clamp01_002761F8(float t)
{
    t = 0.0f + t;
    if (!(t > 0.0f)) {
        t = 0.0f;
    }
    if (!(t < 1.0f)) {
        t = 1.0f;
    }
    return t;
}

static float sqrtabs_002761F8(float x)
{
    return sqrtf(x < 0.0f ? -x : x);
}

/* func_00276158: the level collision octree's word for cell (x, y, z), 0 when there is none. */
static unsigned int cell_002761F8(unsigned char *tree, int x, int y, int z)
{
    unsigned char *yl, *xl;
    int k, off;

    k = z - *(unsigned short *)(tree + 0);
    if (k < 0 || *(unsigned short *)(tree + 2) - k <= 0) {
        return 0;
    }
    off = *(unsigned short *)(tree + 4 + k * 2) << 2;
    if (off == 0) {
        return 0;
    }
    yl = tree + off;
    k = y - *(unsigned short *)(yl + 0);
    if (k < 0 || *(unsigned short *)(yl + 2) - k <= 0) {
        return 0;
    }
    off = *(int *)(yl + 4 + k * 4);
    if (off == 0) {
        return 0;
    }
    xl = tree + off;
    k = x - *(unsigned short *)(xl + 0);
    if (k < 0 || *(unsigned short *)(xl + 2) - k <= 0) {
        return 0;
    }
    return *(unsigned int *)(xl + 4 + k * 4);
}

static void dma_002761F8(unsigned int word, unsigned int sadr, unsigned char *tree)
{
    volatile unsigned int *d = (volatile unsigned int *)0x1000D400;
    d[8] = word & 0xFF;
    d[32] = sadr;
    d[4] = (unsigned int)(unsigned long)(tree + (word >> 8));
    d[0] = 0x100;
}

static void dmawait_002761F8(void)
{
    while (*(volatile unsigned int *)0x1000D400 & 0x100) {
    }
}

typedef struct {
    float A[3], B[3], D[3];
    float best;
    int flags;
    unsigned int s5;
    unsigned int s6;
    float v25[3], v26[3], v27[3], v28[3], v29[3];
} St_002761F8;

/* The triangle loop (retail 0x276728): triangles tp..tend over the vertices at scratchpad 0x70002000 (xyz relative
   to origin, outcode word in w); a1, b1 are the segment's ends relative to origin. */
static void tris_002761F8(St_002761F8 *st, unsigned int *tp, unsigned int *tend, const float *origin, const float *a1, const float *b1, unsigned int owner)
{
    int i;
    for (; tp != tend; tp++) {
        unsigned int tw = *tp;
        float *V0 = (float *)(unsigned long)(0x70002000 + (tw & 0xFF) * 16);
        float *V1 = (float *)(unsigned long)(0x70002000 + ((tw >> 8) & 0xFF) * 16);
        float *V2 = (float *)(unsigned long)(0x70002000 + ((tw >> 16) & 0xFF) * 16);
        unsigned int fl = tw >> 24;
        int flags = st->flags;
        float e1[3], e2[3], p4[3], p5[3], p10[3], N[3], t9[3], t7[3], t8[3], c7[3], c8[3], c9[3], e3[3];
        float dDN, d7, d8, Qv;

        if ((int)(((unsigned int *)V0)[3] & ((unsigned int *)V1)[3] & ((unsigned int *)V2)[3]) > 0) {
            continue;
        }
        if ((int)((flags & 0x80) & fl) > 0) {
            continue;
        }
        for (i = 0; i < 3; i++) {
            e1[i] = V1[i] - V0[i];
            e2[i] = V2[i] - V0[i];
            p4[i] = V0[i] - a1[i];
            p5[i] = V0[i] - b1[i];
        }
        cross_002761F8(N, e2, e1);
        if ((flags & 0x20) != 0 && ((((unsigned int)flags >> 8) ^ fl) & 0x1F) == 0) {
            continue;
        }
        for (i = 0; i < 3; i++) {
            t9[i] = st->D[i] * N[i];
            t7[i] = p4[i] * N[i];
            t8[i] = p5[i] * N[i];
            p10[i] = a1[i] - V0[i];
        }
        dDN = sum_002761F8(t9);
        d7 = sum_002761F8(t7);
        d8 = sum_002761F8(t8);
        Qv = vdiv_002761F8(d7, dDN);
        if ((flags & 0x10) == 0) {
            if (!neg_002761F8(d7)) {
                continue;
            }
            if (neg_002761F8(d8) || fbits_002761F8(d8) == 0) {
                continue;
            }
        }
        if (neg_002761F8(d7) == neg_002761F8(d8)) {
            continue;
        }
        {
            float p[3], w0[3], best_t;
            for (i = 0; i < 3; i++) {
                p[i] = p10[i] * 1.0f + st->D[i] * Qv;
                w0[i] = V0[i] + origin[i];
            }
            for (i = 0; i < 3; i++) {
                e3[i] = e2[i] - e1[i];
                p10[i] = p[i] - e1[i];
            }
            cross_002761F8(c7, p, e1);
            cross_002761F8(c8, e2, p);
            cross_002761F8(c9, p10, e3);
            for (i = 0; i < 3; i++) {
                c7[i] = c7[i] * N[i];
                c8[i] = c8[i] * N[i];
                c9[i] = c9[i] * N[i];
            }
            best_t = st->best - Qv;
            if (neg_002761F8(sum_002761F8(c7)) || neg_002761F8(sum_002761F8(c8)) || neg_002761F8(sum_002761F8(c9))) {
                continue;
            }
            if (neg_002761F8(best_t) || fbits_002761F8(best_t) == 0) {
                continue;
            }
            st->s6 = fl + 4096;
            st->s5 = owner;
            st->best = 0.0f + Qv;
            for (i = 0; i < 3; i++) {
                st->v25[i] = p[i] + w0[i];
                st->v26[i] = N[i] + 0.0f;
                st->v27[i] = 0.0f + w0[i];
                st->v28[i] = e1[i] + w0[i];
                st->v29[i] = e2[i] + w0[i];
            }
        }
    }
}

/* CollLine: the segment a..b (world units, inside the 1024 cube) against the level collision (unless flags & 1) and
   the mobys' collision. Level: the 4-unit cells the segment crosses, in order along it (a DDA, crossings listed at
   scratchpad 0x70003800 as {t, packed cell}), each cell's chunk DMA'd from the octree D_001BAF80+0 while the previous
   one is tested; stops past the first cell beyond the nearest hit. Mobys: the 16-unit cells of those cells, mobys
   whose bounding sphere the segment passes (all, or with flags & 9 only those flagged 0x4000 at +0x34), their
   triangles and primitives (spheres, capsules; unless flags & 2). Keeps the nearest hit t. No hit: 0. Otherwise 1
   and D_001BAF80: +0x18 the moby (0 for the level), +0x1C the material + 0x1000 or minus the primitive's address,
   +0x20 the hit point, +0x40 N (or the hit point minus the primitive centre), +0x50/+0x60/+0x70 the triangle (world
   units); with `rec` and a moby flagged 0x4000, a ring record at D_001BF200 as func_00277F48's (its +0x3C the
   primitive index, -1 for a triangle). */
int func_002761F8(void *a_, void *b_, int flags, void *skip, void *rec_)
{
    float *pa = (float *)a_;
    float *pb = (float *)b_;
    unsigned char *rec = (unsigned char *)rec_;
    unsigned char *D = D_001BAF80;
    St_002761F8 st;
    int stamp, stampw;
    unsigned char *tree;
    int ia[3], ib[3];
    unsigned int cell0;
    int i;

    stamp = *(int *)(D + 16);
    if (stamp < 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        st.A[i] = pa[i] * 1024.0f;
        st.B[i] = pb[i] * 1024.0f;
    }
    stamp = stamp + 1;
    *(int *)(D + 16) = stamp;
    stampw = (flags < 0) ? -1 : stamp; /* retail: s3 = (sign-extended flags) | stamp << 32, read back as s3 >> 32 */
    {
        float mn[3], mx[3];
        for (i = 0; i < 3; i++) {
            mn[i] = (pa[i] < pb[i]) ? pa[i] : pb[i];
            mx[i] = (pa[i] > pb[i]) ? pa[i] : pb[i];
        }
        if (neg_002761F8(mn[0]) || neg_002761F8(mn[1]) || neg_002761F8(mn[2])) {
            return 0;
        }
        tree = *(unsigned char **)(D + 0);
        if (!(neg_002761F8(mx[0] - 1024.0f) && neg_002761F8(mx[1] - 1024.0f) && neg_002761F8(mx[2] - 1024.0f))) {
            return 0;
        }
    }
    st.flags = flags;
    st.s5 = 0;
    st.s6 = 0;
    for (i = 0; i < 3; i++) {
        ia[i] = ftoi0_002761F8(st.A[i]);
        ib[i] = ftoi0_002761F8(st.B[i]);
        st.D[i] = st.B[i] - st.A[i];
    }
    {
        unsigned int c[3];
        for (i = 0; i < 3; i++) {
            c[i] = (unsigned int)ia[i] >> 12;
        }
        cell0 = (c[0] & 0xFF) | (c[1] & 0xFF) << 8 | (c[2] & 0xFF) << 16;
        *(unsigned int *)0x70003800 = 0;
        *(unsigned int *)0x70003804 = cell0;
        if ((flags & 1) == 0) {
            unsigned int w = cell_002761F8(tree, c[0] & 0xFFFF, c[1], c[2]);
            *(unsigned int *)0x70000000 = 0;
            *(unsigned int *)0x70000004 = 0;
            if (w != 0) {
                dma_002761F8(w, 0, tree);
            }
        }
    }

    {
        unsigned int c4[3], c5[3];
        unsigned int *ent = (unsigned int *)0x70003800;
        int same;

        for (i = 0; i < 3; i++) {
            c4[i] = (unsigned int)ia[i] >> 12;
            c5[i] = (unsigned int)ib[i] >> 12;
        }
        same = ((c4[0] - c5[0]) & 0xFFFF) == 0 && ((c4[1] - c5[1]) & 0xFFFF) == 0 && ((c4[2] - c5[2]) & 0xFFFF) == 0;
        if (same) {
            if (((ia[0] - ib[0]) | (ia[1] - ib[1])) == 0 && ((ia[1] - ib[1]) | (ia[2] - ib[2])) == 0) {
                dmawait_002761F8();
                return 0;
            }
        } else {
            /* the DDA: per axis the t (as float bits, clamped to [0, 1]) of each cell boundary crossed */
            int total = 0;
            int ax;
            unsigned int *arr[3];
            signed char step[3];
            unsigned int t1 = cell0;
            unsigned int *tx, *ty, *tz;
            int sx, sy, sz;

            for (ax = 0; ax < 3; ax++) {
                int at = (int)c4[ax], v0 = (int)c5[ax], st1;
                float Qv = vdiv_002761F8(1.0f, st.D[ax]);
                unsigned int *o = (unsigned int *)(unsigned long)(0x70003000 + ax * 512);

                arr[ax] = o;
                if (v0 - at >= 0) {
                    st1 = 1;
                } else {
                    at = at + 1;
                    v0 = v0 + 1;
                    st1 = -1;
                }
                while (at != v0) {
                    float t;
                    int tb;
                    at = at + st1;
                    t = (float)(int)(at << 12);
                    t = t - st.A[ax];
                    t = t * Qv;
                    tb = fbits_002761F8(t);
                    if (tb > 0x3F800000) {
                        tb = 0x3F800000;
                    }
                    if (tb < 0) {
                        tb = 0;
                    }
                    total++;
                    *o++ = tb;
                }
                *o = 0x50000000;
                step[ax] = st1;
                *(signed char *)(unsigned long)(0x70003FFC + ax) = st1;
            }
            sx = *(signed char *)0x70003FFC;
            sy = *(signed char *)0x70003FFD << 8;
            sz = *(signed char *)0x70003FFE << 16;
            tx = arr[0];
            ty = arr[1];
            tz = arr[2];
            while (total > 0) {
                int x = (int)*tx, y = (int)*ty, z = (int)*tz;
                ent += 2;
                total--;
                if (y - x < 0) {
                    if (z - y < 0) {
                        ent[0] = z;
                        t1 += sz;
                        ent[1] = t1;
                        tz++;
                    } else {
                        ent[0] = y;
                        t1 += sy;
                        ty++;
                        ent[1] = t1;
                    }
                } else if (z - x < 0) {
                    ent[0] = z;
                    t1 += sz;
                    ent[1] = t1;
                    tz++;
                } else {
                    ent[0] = x;
                    t1 += sx;
                    tx++;
                    ent[1] = t1;
                }
            }
            (void)step;
        }
        st.best = 0.0f + 1.0f;
        ent[2] = 0x3F800000;
        ent[3] = 0;
    }

    if ((flags & 1) == 0) {
        unsigned int *t9 = (unsigned int *)0x70003800;
        unsigned char *s7 = (unsigned char *)0x70001000;

        for (;;) {
            unsigned int t2 = t9[0];
            unsigned int t3, cell, next;
            float tt, tn;

            if (t2 == 0x3F800000) {
                break;
            }
            t3 = t9[2];
            cell = t9[1];
            if (st.s6 != 0 && !(fbits_002761F8(st.best) - (int)t2 > 0)) {
                dmawait_002761F8();
                break;
            }
            next = t9[3];
            s7 = (unsigned char *)((unsigned long)s7 ^ 0x1000);
            t9 += 2;
            dmawait_002761F8();
            if (t3 != 0x3F800000) {
                unsigned int w = cell_002761F8(tree, next & 0xFF, (next >> 8) & 0xFF, next >> 16);
                unsigned char *ob = (unsigned char *)((unsigned long)s7 ^ 0x1000);
                *(unsigned int *)ob = 0;
                *(unsigned int *)(ob + 4) = 0;
                if (w != 0) {
                    dma_002761F8(w, (unsigned int)(unsigned long)ob, tree);
                }
            }
            tt = bitsf_002761F8(t2);
            tn = bitsf_002761F8(t3);
            if (s7[2] == 0) {
                continue;
            }
            {
                float p10[3], p11[3], ctr[3], a1[3], b1[3];
                int i10[3], i11[3], cc[3];
                short l16[3], h16[3];
                int nv = s7[2];
                unsigned int *vw = (unsigned int *)(s7 + 4);
                float *out = (float *)0x70002000;
                unsigned int *tp, *tend, *t2p;
                int nq;

                for (i = 0; i < 3; i++) {
                    p10[i] = st.D[i] * tt + st.A[i] * 1.0f;
                    p11[i] = st.D[i] * tn + st.A[i] * 1.0f;
                }
                for (i = 0; i < 3; i++) {
                    i10[i] = ftoi0_002761F8(p10[i]);
                    i11[i] = ftoi0_002761F8(p11[i]);
                    cc[i] = (int)(((cell >> (i * 8)) & 0xFF) << 12) + 0x800;
                    ctr[i] = (float)cc[i];
                }
                for (i = 0; i < 3; i++) {
                    int u = i10[i] - cc[i], v = i11[i] - cc[i];
                    int mn = (u < v) ? u : v, mx = (u > v) ? u : v;
                    l16[i] = (short)(mn - 1);
                    h16[i] = (short)(mx + 1);
                    a1[i] = st.A[i] - ctr[i];
                    b1[i] = st.B[i] - ctr[i];
                }
                do {
                    int h;
                    for (h = 0; h < 2; h++) {
                        unsigned int w = vw[h];
                        short v[3];
                        unsigned int oc = 0;
                        v[0] = (short)((w & 0x3FF) << 6);
                        v[1] = (short)(((w >> 10) & 0x3FF) << 6);
                        v[2] = (short)((w >> 20) << 4);
                        for (i = 0; i < 3; i++) {
                            unsigned int b = 0;
                            if ((short)(v[i] - l16[i]) < 0) {
                                b |= 1;
                            }
                            if ((short)(h16[i] - v[i]) < 0) {
                                b |= 2;
                            }
                            oc |= b << (i * 8);
                        }
                        out[h * 4 + 0] = (float)v[0];
                        out[h * 4 + 1] = (float)v[1];
                        out[h * 4 + 2] = (float)v[2];
                        ((unsigned int *)out)[h * 4 + 3] = oc;
                    }
                    vw += 2;
                    out += 8;
                    nv -= 2;
                } while (nv > 0);

                tp = (unsigned int *)(s7 + 4 + s7[2] * 4);
                tend = tp + s7[0];
                t2p = tp;
                tris_002761F8(&st, tp, tend, ctr, a1, b1, (unsigned int)(unsigned long)tree);
                nq = s7[3];
                if (nq != 0) {
                    unsigned char *qa = (unsigned char *)t2p;
                    unsigned char *qb = (unsigned char *)tend;
                    int k;
                    for (k = 0; k < nq; k++) {
                        unsigned char a2 = qa[2];
                        unsigned char b0 = *qb++;
                        qa[1] = a2;
                        qa[2] = b0;
                        qa += 4;
                    }
                    tris_002761F8(&st, t2p, t2p + nq, ctr, a1, b1, (unsigned int)(unsigned long)tree);
                }
            }
        }
    }

    /* mobys (retail 0x276960) */
    {
        float dd2, dq[3], v21[3];
        unsigned int *src, *dst;
        unsigned int prev;
        unsigned int *t9;
        unsigned char *s0 = (unsigned char *)0x70000000;

        for (i = 0; i < 3; i++) {
            dq[i] = st.D[i] * st.D[i];
        }
        st.s5 = 0;
        {
            unsigned int h = *(unsigned short *)0x70003804;
            prev = (((h & 0xFF) >> 2) & 0xFFFF) | ((((h >> 8) & 0xFF) >> 2) << 16);
        }
        dd2 = sum_002761F8(dq);
        {
            float Qv = vdiv_002761F8(1.0f, dd2);
            *(unsigned int *)0x70003800 = prev;
            src = (unsigned int *)0x70003808;
            dst = (unsigned int *)0x70003804;
            for (;;) {
                unsigned int h = *(unsigned short *)(src + 1);
                unsigned int t = src[0];
                unsigned int c;
                if (t == 0x3F800000) {
                    break;
                }
                src += 2;
                c = (((h & 0xFF) >> 2) & 0xFFFF) | ((((h >> 8) & 0xFF) >> 2) << 16);
                if (prev == c) {
                    continue;
                }
                *dst++ = c;
                prev = c;
            }
            for (i = 0; i < 3; i++) {
                v21[i] = st.D[i] * Qv;
            }
            *dst = 0xFFFFFFFF;
        }

        for (t9 = (unsigned int *)0x70003800;; t9++) {
            unsigned int cw = *t9;
            unsigned char *c;
            unsigned short *e, *eend;

            if ((int)cw < 0) {
                break;
            }
            c = D_001D24E0 + (cw >> 8) + (cw & 0xFFFF) * 4;
            e = (unsigned short *)(D_001D24E0 + 0x4000 + *(unsigned short *)c * 32);
            eend = (unsigned short *)((unsigned char *)e + c[2] * 2);
            *t9 = (unsigned int)(unsigned long)eend;
            while (e != (unsigned short *)(unsigned long)*t9) {
                unsigned char *m = D_001B1B5C + (*e << 8);
                float *ms = (float *)m;
                unsigned char *col;
                float d2[3], r2, tp, pt[3], dd;
                float pos16[3], rows[3][3], sc;

                e++;
                if ((char *)m == (char *)skip) {
                    continue;
                }
                for (i = 0; i < 3; i++) {
                    d2[i] = ms[i] - st.A[i];
                }
                r2 = ms[3] * ms[3];
                col = *(unsigned char **)(m + 152);
                if ((((flags & 9) == 0) | (*(unsigned short *)(m + 52) & 0x4000)) == 0) {
                    continue;
                }
                for (i = 0; i < 3; i++) {
                    d2[i] = d2[i] * v21[i];
                }
                tp = sum_002761F8(d2);
                if (!(tp > 0.0f)) {
                    tp = 0.0f;
                }
                if (!(tp < st.best)) {
                    tp = st.best;
                }
                for (i = 0; i < 3; i++) {
                    pt[i] = (0.0f + st.A[i]) + st.D[i] * tp;
                    pt[i] = pt[i] - ms[i];
                    pt[i] = pt[i] * pt[i];
                }
                dd = ((pt[0] - r2) + pt[1]) + pt[2];
                if (col == 0) {
                    continue;
                }
                if (fbits_002761F8(dd) > 0) {
                    continue;
                }
                {
                    int old = *(int *)(m + 160);
                    int count, trib;

                    *(int *)(m + 160) = stampw;
                    if (old == stampw) {
                        continue;
                    }
                    count = *(unsigned short *)(col + (((flags & 4) == 0) ? 2 : 0));
                    trib = *(int *)(col + 12);
                    if (count != 0) {
                        int id;
                        unsigned int *t;
                        unsigned char *buf;
                        int k;

                        if (((flags & 2) == 0) == trib) {
                            continue;
                        }
                        id = *(int *)(m + 172);
                        t = *(unsigned int **)(D + 8);
                        buf = *(unsigned char **)(D + 4);
                        for (k = 0; k < 8; k++) {
                            if ((int)t[k * 2] == id) {
                                break;
                            }
                            buf += 2048;
                        }
                        s0 = buf;
                        if (k == 8) {
                            int slot = *(int *)(D + 12);
                            unsigned int *en;
                            unsigned char *nb;

                            *(int *)(D + 12) = (slot + 1) & 7;
                            en = *(unsigned int **)(D + 8) + slot * 2;
                            nb = *(unsigned char **)(D + 4) + slot * 2048;
                            en[0] = id;
                            en[1] = stampw;
                            func_002A3110(m, count, nb);
                            s0 = (unsigned char *)0x70000000;
                        }
                    }
                }

                for (i = 0; i < 3; i++) {
                    pos16[i] = ((float *)(m + 16))[i] * 1024.0f;
                    rows[0][i] = ((float *)(m + 192))[i];
                    rows[1][i] = ((float *)(m + 208))[i];
                    rows[2][i] = ((float *)(m + 224))[i];
                }
                sc = *(float *)(m + 44);

                if (*(int *)(col + 12) != 0 && *(int *)(m + 156) >= 0) {
                    float a1[3], b1[3], r3[3], r4[3], r5[3], lo[3], hi[3];
                    int vbytes = *(int *)(col + 12);
                    int voff = *(int *)(col + 4) + 16;
                    short *vp = (short *)(col + voff);
                    float *out = (float *)0x70002000;
                    unsigned int *tp2, *tend;

                    for (i = 0; i < 3; i++) {
                        a1[i] = st.A[i] - pos16[i];
                        b1[i] = st.B[i] - pos16[i];
                        r3[i] = rows[0][i] * sc;
                        r4[i] = rows[1][i] * sc;
                        r5[i] = rows[2][i] * sc;
                    }
                    for (i = 0; i < 3; i++) {
                        lo[i] = (a1[i] < b1[i]) ? a1[i] : b1[i];
                        hi[i] = (a1[i] > b1[i]) ? a1[i] : b1[i];
                    }
                    do {
                        int h;
                        for (h = 0; h < 2; h++) {
                            float v[3], w[3];
                            unsigned int oc = 0;
                            for (i = 0; i < 3; i++) {
                                v[i] = (float)vp[i];
                            }
                            rot_002761F8(w, r3, r4, r5, v);
                            for (i = 0; i < 3; i++) {
                                unsigned int b = 0;
                                if (neg_002761F8(w[i] - lo[i])) {
                                    b |= 1;
                                }
                                if (neg_002761F8(hi[i] - w[i])) {
                                    b |= 2;
                                }
                                oc |= b << (i * 8);
                            }
                            out[h * 4 + 0] = w[0];
                            out[h * 4 + 1] = w[1];
                            out[h * 4 + 2] = w[2];
                            ((unsigned int *)out)[h * 4 + 3] = oc;
                            vp += 4;
                        }
                        out += 8;
                        vbytes -= 16;
                    } while (vbytes > 0);

                    tp2 = (unsigned int *)(col + voff + *(int *)(col + 12));
                    tend = (unsigned int *)((unsigned char *)tp2 + *(int *)(col + 8));
                    tris_002761F8(&st, tp2, tend, pos16, a1, b1, (unsigned int)(unsigned long)m);
                }

                /* primitives (retail 0x276d10) */
                if ((flags & 2) == 0 && *(int *)(col + 4) != 0) {
                    unsigned char *pr = col + 16;
                    int want = ((flags & 4) == 0) + 1;
                    unsigned int mask = *(unsigned int *)(m + 156);
                    int last = 0;

                    while (last >= 0) {
                        int skipbit = mask & 1;
                        int type;
                        float c1[3], cw, base[3], axv[3], cr2, crad;
                        int capsule = 0;

                        mask >>= 1;
                        last = *(short *)(pr + 2);
                        type = *(signed char *)(pr + 0);
                        pr += 32;
                        if (skipbit > 0) {
                            continue;
                        }
                        if ((want & last) == 0) {
                            continue;
                        }
                        if (type == 1) {
                            float v[4];
                            for (i = 0; i < 4; i++) {
                                v[i] = ((float *)(pr - 16))[i] * sc;
                            }
                            rot_002761F8(c1, rows[0], rows[1], rows[2], v);
                            for (i = 0; i < 3; i++) {
                                c1[i] = c1[i] + pos16[i];
                            }
                            cw = v[3];
                        } else if (type == 2) {
                            float *vt = (float *)(s0 + *(int *)(pr - 28) * 16);
                            float v[4];
                            v[3] = ((float *)(pr - 32))[3];
                            for (i = 0; i < 3; i++) {
                                v[i] = vt[i] + ((float *)(pr - 16))[i];
                            }
                            for (i = 0; i < 4; i++) {
                                v[i] = v[i] * sc;
                            }
                            rot_002761F8(c1, rows[0], rows[1], rows[2], v);
                            for (i = 0; i < 3; i++) {
                                c1[i] = c1[i] + pos16[i];
                            }
                            cw = v[3];
                        } else if (type == 3) {
                            float v[4], len;
                            for (i = 0; i < 4; i++) {
                                v[i] = ((float *)(pr - 16))[i] * sc;
                            }
                            len = ((float *)(pr - 32))[1] * sc;
                            rot_002761F8(base, rows[0], rows[1], rows[2], v);
                            for (i = 0; i < 3; i++) {
                                base[i] = base[i] + pos16[i] * 1.0f;
                                axv[i] = rows[2][i] * len;
                            }
                            crad = 0.0f + v[3];
                            cr2 = crad * crad;
                            capsule = 1;
                        } else {
                            float *va = (float *)(s0 + *(short *)(pr - 28) * 16);
                            float *vb = (float *)(s0 + *(short *)(pr - 26) * 16);
                            float u[3], w[3], bw;
                            for (i = 0; i < 3; i++) {
                                u[i] = va[i] * sc;
                                w[i] = vb[i] * sc;
                            }
                            bw = ((float *)(pr - 32))[3] * sc;
                            rot_002761F8(base, rows[0], rows[1], rows[2], u);
                            crad = 0.0f + bw;
                            rot_002761F8(axv, rows[0], rows[1], rows[2], w);
                            cr2 = crad * crad;
                            for (i = 0; i < 3; i++) {
                                axv[i] = axv[i] - base[i];
                                base[i] = base[i] + pos16[i];
                            }
                            capsule = 1;
                        }
                        if (capsule) {
                            /* retail 0x276dd8: the point of the segment to test against the capsule axis */
                            float x3[3], x4[3], x9[3], x7[3], x8[3], P[3];
                            int par;

                            cross_002761F8(x3, axv, st.D);
                            cross_002761F8(x4, st.D, axv);
                            for (i = 0; i < 3; i++) {
                                x9[i] = x3[i] * x3[i];
                            }
                            cross_002761F8(x7, st.D, x3);
                            cross_002761F8(x8, axv, x4);
                            par = neg_002761F8(x9[0] - 1.0f) && neg_002761F8(x9[1] - 1.0f) && neg_002761F8(x9[2] - 1.0f);
                            for (i = 0; i < 3; i++) {
                                P[i] = st.A[i];
                            }
                            if (!par) {
                                float y5[3], y6[3], n9, s7v, s8v, q1, q2, s3p[3], s4p[3], a2, dd5[3], dl, qa, qd;
                                float ua[3], ud[3], cs, k, sq;

                                for (i = 0; i < 3; i++) {
                                    y5[i] = st.A[i] - base[i];
                                    y6[i] = base[i] - st.A[i];
                                }
                                n9 = sum_002761F8(x9);
                                for (i = 0; i < 3; i++) {
                                    x7[i] = x7[i] * y5[i];
                                    x8[i] = x8[i] * y6[i];
                                }
                                s7v = sum_002761F8(x7);
                                s8v = sum_002761F8(x8);
                                q1 = vdiv_002761F8(s7v, n9);
                                for (i = 0; i < 3; i++) {
                                    s3p[i] = (0.0f + base[i]) + axv[i] * q1;
                                }
                                q2 = vdiv_002761F8(s8v, n9);
                                for (i = 0; i < 3; i++) {
                                    s4p[i] = (0.0f + st.A[i]) + st.D[i] * q2;
                                }
                                a2 = dot_002761F8(axv, axv);
                                for (i = 0; i < 3; i++) {
                                    dd5[i] = s4p[i] - s3p[i];
                                    dd5[i] = dd5[i] * dd5[i];
                                }
                                {
                                    float dsum = dot_002761F8(st.D, st.D);
                                    dl = (((0.0f - cr2) + dd5[0]) + dd5[1]) + dd5[2];
                                    qa = vdiv_002761F8(1.0f, sqrtabs_002761F8(a2));
                                    if (!neg_002761F8(dl)) {
                                        continue;
                                    }
                                    dl = 0.0f - dl;
                                    for (i = 0; i < 3; i++) {
                                        ua[i] = axv[i] * qa;
                                    }
                                    qd = vdiv_002761F8(1.0f, sqrtabs_002761F8(dsum));
                                    for (i = 0; i < 3; i++) {
                                        ud[i] = st.D[i] * qd;
                                    }
                                }
                                cs = dot_002761F8(ua, ud);
                                cs = cs * cs;
                                cs = 1.0f - cs;
                                k = 0.0f + vdiv_002761F8(dl, cs);
                                if (!(k > 0.0f)) {
                                    k = 0.0f;
                                }
                                sq = sqrtabs_002761F8(k);
                                for (i = 0; i < 3; i++) {
                                    float b7 = ud[i] * sq;
                                    P[i] = s4p[i] - b7;
                                }
                                {
                                    float pd[3];
                                    for (i = 0; i < 3; i++) {
                                        pd[i] = P[i] - st.A[i];
                                    }
                                    if (neg_002761F8(dot_002761F8(pd, st.D))) {
                                        for (i = 0; i < 3; i++) {
                                            P[i] = st.A[i];
                                        }
                                    }
                                }
                            }
                            {
                                float pd[3], t;
                                for (i = 0; i < 3; i++) {
                                    pd[i] = P[i] - base[i];
                                }
                                t = clamp01_002761F8(vdiv_002761F8(dot_002761F8(pd, axv), dot_002761F8(axv, axv)));
                                for (i = 0; i < 3; i++) {
                                    c1[i] = base[i] + axv[i] * t;
                                }
                                cw = crad + 0.0f;
                            }
                        }
                        /* retail 0x276ff8: the segment against the sphere (c1, cw) */
                        {
                            float d3[3], aa, bb, cc2, rr2, t, p9[3], dd9, disc, sq, nb, a2x, hit[3], nrm[3];

                            for (i = 0; i < 3; i++) {
                                d3[i] = c1[i] - st.A[i];
                            }
                            aa = dot_002761F8(st.D, st.D);
                            bb = dot_002761F8(d3, st.D);
                            cc2 = dot_002761F8(d3, d3);
                            rr2 = cw * cw;
                            t = clamp01_002761F8(vdiv_002761F8(bb, aa));
                            for (i = 0; i < 3; i++) {
                                p9[i] = (0.0f + st.A[i]) + st.D[i] * t;
                                p9[i] = p9[i] - c1[i];
                                p9[i] = p9[i] * p9[i];
                            }
                            dd9 = ((p9[0] - rr2) + p9[1]) + p9[2];
                            if (fbits_002761F8(dd9) > 0) {
                                continue;
                            }
                            bb = bb + bb;
                            cc2 = cc2 - rr2;
                            disc = bb * bb;
                            disc = disc - (4.0f * aa) * cc2;
                            if (!(disc > 0.0f)) {
                                disc = 0.0f;
                            }
                            sq = sqrtabs_002761F8(disc);
                            nb = 0.0f - bb;
                            a2x = aa + aa;
                            nb = nb + sq;
                            t = 0.0f - vdiv_002761F8(nb, a2x);
                            if (!(t > 0.0f)) {
                                t = 0.0f;
                            }
                            if (!(t < 1.0f)) {
                                t = 1.0f;
                            }
                            for (i = 0; i < 3; i++) {
                                hit[i] = (0.0f + st.A[i]) + st.D[i] * t;
                                nrm[i] = hit[i] - c1[i];
                            }
                            {
                                float bt = st.best - t;
                                if (neg_002761F8(bt) || fbits_002761F8(bt) == 0) {
                                    continue;
                                }
                            }
                            st.s5 = (unsigned int)(unsigned long)m;
                            st.s6 = -(unsigned int)(unsigned long)(pr - 32);
                            st.best = 0.0f + t;
                            for (i = 0; i < 3; i++) {
                                st.v25[i] = 0.0f + hit[i];
                                st.v26[i] = 0.0f + nrm[i];
                            }
                        }
                    }
                }
            }
        }
    }

    /* retail 0x277118 */
    if (st.s6 == 0) {
        return 0;
    }
    {
        float k = bitsf_002761F8(0x3A800000);
        float *o;
        for (i = 0; i < 3; i++) {
            st.v25[i] = st.v25[i] * k;
            st.v27[i] = st.v27[i] * k;
            st.v28[i] = st.v28[i] * k;
            st.v29[i] = st.v29[i] * k;
        }
        o = (float *)(D + 32);
        o[0] = st.v25[0];
        o[1] = st.v25[1];
        o[2] = st.v25[2];
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 64);
        o[0] = st.v26[0];
        o[1] = st.v26[1];
        o[2] = st.v26[2];
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 80);
        o[0] = st.v27[0];
        o[1] = st.v27[1];
        o[2] = st.v27[2];
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 96);
        o[0] = st.v28[0];
        o[1] = st.v28[1];
        o[2] = st.v28[2];
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 112);
        o[0] = st.v29[0];
        o[1] = st.v29[1];
        o[2] = st.v29[2];
        ((unsigned int *)o)[3] = 0;
        *(unsigned int *)(D + 24) = st.s5;
        *(unsigned int *)(D + 28) = st.s6;
    }
    if (st.s5 == 0 || rec == 0) {
        return 1;
    }
    {
        unsigned char *m = (unsigned char *)(unsigned long)st.s5;
        int ring = *(int *)(D + 20);
        int slot = *(signed char *)(m + 168);
        unsigned int add = 0;
        unsigned char *v1;
        int idx;

        if ((*(unsigned short *)(m + 52) & 0x4000) == 0) {
            return 1;
        }
        if (slot >= 0) {
            unsigned char *o = D_001BF200 + slot * 64;
            if (*(unsigned int *)(o + 56) == st.s5) {
                if (*(int *)(o + 44) - *(int *)(rec + 28) >= 0) {
                    *(unsigned int *)(o + 36) = *(unsigned int *)(rec + 20) | *(unsigned int *)(o + 36);
                    return 1;
                }
                add = *(unsigned int *)(o + 36);
            }
        }
        *(int *)(D + 20) = (ring + 1) & 63;
        *(signed char *)(m + 168) = ring;
        v1 = D_001BF200 + ring * 64;
        {
            unsigned int w[10];
            unsigned int a3 = *(unsigned int *)(rec + 20);
            for (i = 0; i < 10; i++) {
                w[i] = ((unsigned int *)rec)[i];
            }
            ((float *)v1)[0] = st.v25[0];
            ((float *)v1)[1] = st.v25[1];
            ((float *)v1)[2] = st.v25[2];
            ((unsigned int *)v1)[3] = 0;
            for (i = 0; i < 10; i++) {
                ((unsigned int *)(v1 + 16))[i] = w[i];
            }
            *(unsigned int *)(v1 + 36) = a3 | add;
            *(unsigned int *)(v1 + 56) = st.s5;
        }
        idx = -32;
        if ((int)st.s6 < 0) {
            idx = (int)(-st.s6) - (int)(unsigned long)*(unsigned char **)(m + 152);
        }
        *(int *)(v1 + 60) = idx >> 5;
    }
    return 1;
}
