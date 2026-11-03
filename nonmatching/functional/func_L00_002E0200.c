/* functional: medium. Written from the hand-written VU0/MMI assembly (CollCylinder, the vertical-cylinder sibling of CollSphere func_00277258): plain floats in the VU's order (sums as (x + y) + 1*z, ACC chains left to right), the same reads, writes and calls in the same order. VU rounding is not reproduced; vdiv/vrsqrt by zero give +-FLT_MAX as the VU does; vsqrt is sqrtf of |x|. The MAC-flag tests (cfc2 $vi17) are the sign bits of pos - r and of pos + r (+h in z) - 1024. The toSPR DMA of each level cell's chunk (0x1000D400 registers, double-buffered at scratchpad 0x70000000/0x70001000) is written as retail's register stores and its STR polls. func_00276158 (its level copy), the octree lookup retail calls with register arguments, is written out here (cell_002E0200); func_002A3110 (its level copy) is a real call. The w words of the result quads (D_L00_001BF200+0x20..+0x70) are stale VU0 register contents in retail; here 0, except +0x3C (the pushed point's w, retail's vf2.w: whatever full quad was last loaded into vf2), which is left as it was (on 2 of 8 captured calls retail rewrote the value already there, 0x7F07; 0 differed). The word +4 of a new moby collision-cache entry gets whatever $a3 held (a leftover of earlier tests), reproduced as retail computes it, except right after a func_002A3110 call with no triangle pass in between, where retail's $a3 is that function's leftover and here the previous value. The moby's top test (vf5 after prot3w, as a 64-bit word) also sees a stale y lane when the top is exactly +0; here +0 counts as above. With the stamp D_L00_001BF200+0x10 negative retail exits through its result code with the caller's $s6 (cleared only later), so a nonzero caller $s6 would write results and return 1; here 0, the intended exit. Retail's caller-saved s registers kept in the upper halves (pcpyld/pcpyud) have no C spelling. */
extern unsigned char D_L00_001BF200[];
extern unsigned char *D_L00_001B1E9C;
extern unsigned char D_L00_001DE860[];
extern float sqrtf(float);
extern void func_002A3110(void *moby, int count, void *buf);

#define FMAX_002E0200 3.40282347e+38f

static int fbits_002E0200(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i;
}

static float bitsf_002E0200(unsigned int i)
{
    union {
        float f;
        unsigned int i;
    } u;
    u.i = i;
    return u.f;
}

static int neg_002E0200(float f)
{
    return fbits_002E0200(f) < 0;
}

static float vdiv_002E0200(float n, float d)
{
    float q;
    if (d == 0.0f) {
        return ((fbits_002E0200(n) ^ fbits_002E0200(d)) < 0) ? -FMAX_002E0200 : FMAX_002E0200;
    }
    q = n / d;
    if (q > FMAX_002E0200) {
        q = FMAX_002E0200;
    } else if (q < -FMAX_002E0200) {
        q = -FMAX_002E0200;
    }
    return q;
}

static int ftoi0_002E0200(float f)
{
    if (f >= 2147483647.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)(-2147483647 - 1);
    }
    return (int)f;
}

static float min_002E0200(float a, float b)
{
    return (a < b) ? a : b;
}

static float max_002E0200(float a, float b)
{
    return (a > b) ? a : b;
}

static float dot_002E0200(const float *a, const float *b)
{
    float x = a[0] * b[0];
    float y = a[1] * b[1];
    float z = a[2] * b[2];
    return (x + y) + z;
}

/* r = a x b as vopmula ACC,a,b / vopmsub r,b,a compute it */
static void cross_002E0200(float *r, const float *a, const float *b)
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

/* c * N, then the y lane's sum (y + x) + 1*z. */
static float side_002E0200(float *c, const float *N)
{
    int i;
    for (i = 0; i < 3; i++) {
        c[i] = c[i] * N[i];
    }
    return (c[1] + c[0]) + c[2];
}

static void xform_002E0200(float *r, const float *m0, const float *m1, const float *m2, const float *v, const float *t)
{
    float o[3];
    int i;
    for (i = 0; i < 3; i++) {
        float a = m0[i] * v[0];
        a = a + m1[i] * v[1];
        a = a + m2[i] * v[2];
        o[i] = a + t[i] * 1.0f;
    }
    r[0] = o[0];
    r[1] = o[1];
    r[2] = o[2];
}

/* 0 + p.e / e.e, clamped to [0, 1] (vmax with 0, vmini with 1). */
static float seg_t_002E0200(const float *p, const float *e)
{
    float t = 0.0f + vdiv_002E0200(dot_002E0200(p, e), dot_002E0200(e, e));
    t = max_002E0200(t, 0.0f);
    t = min_002E0200(t, 1.0f);
    return t;
}

/* func_00276158: the level collision octree's word for cell (x, y, z), 0 when there is none. */
static unsigned int cell_002E0200(unsigned char *tree, int x, int y, int z)
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

static void dma_002E0200(unsigned int word, unsigned int sadr, unsigned char *tree)
{
    volatile unsigned int *d = (volatile unsigned int *)0x1000D400;
    d[8] = word & 0xFF;
    d[32] = sadr;
    d[4] = (unsigned int)(unsigned long)(tree + (word >> 8));
    d[0] = 0x100;
}

typedef struct {
    float q[3];
    float R;
    float H;
    float best;
    int flags;
    unsigned int a3r;
    unsigned int s5;
    unsigned int s6;
    float v25[3], v26[3], v27[3], v28[3], v29[3];
} St_002E0200;

/* The triangle loop (retail 0x2E0608): triangles tp..tend over the vertices at scratchpad 0x70002000 (xyz relative
   to origin, outcode word in w); v22 is the cylinder's base centre relative to origin, its top is H above; owner
   goes to s5 on a hit. */
static void tris_002E0200(St_002E0200 *st, unsigned int *tp, unsigned int *tend, const float *origin, const float *v22, unsigned int owner)
{
    int i;
    for (; tp != tend; tp++) {
        unsigned int tw = *tp;
        float *V0 = (float *)(unsigned long)(0x70002000 + (tw & 0xFF) * 16);
        float *V1 = (float *)(unsigned long)(0x70002000 + ((tw >> 8) & 0xFF) * 16);
        float *V2 = (float *)(unsigned long)(0x70002000 + ((tw >> 16) & 0xFF) * 16);
        unsigned int fl = tw >> 24;
        float e1[3], e2[3], p4[3], p5[3], N[3], m[3];
        float c7[3], c8[3], c9[3], v13[3], v8[3], v4[3], A[3], B[3];
        float dB, dT, Qv, d2, v11z, v12z, v13z, v14z;
        int flags = st->flags;
        int edge;

        st->a3r = ((unsigned int *)V1)[3];
        if ((int)(((unsigned int *)V0)[3] & ((unsigned int *)V1)[3] & ((unsigned int *)V2)[3]) > 0) {
            continue;
        }
        if ((int)((flags & 0x80) & fl) > 0) {
            continue;
        }
        for (i = 0; i < 3; i++) {
            e1[i] = V1[i] - V0[i];
            e2[i] = V2[i] - V0[i];
            p5[i] = v22[i] - V0[i];
            p4[i] = v22[i] - V0[i];
        }
        st->a3r = (((unsigned int)flags >> 8) ^ fl) & 0x1F;
        cross_002E0200(N, e2, e1);
        if ((flags & 0x20) != 0 && st->a3r == 0) {
            continue;
        }
        p5[2] = p5[2] + st->H;
        dB = dot_002E0200(p4, N);
        dT = dot_002E0200(p5, N);
        v11z = p4[2] - e1[2];
        v12z = p4[2] - e2[2];
        if ((flags & 0x10) == 0) {
            st->a3r = (unsigned int)fbits_002E0200(dT);
            if ((fbits_002E0200(dB) & fbits_002E0200(dT)) < 0) {
                continue;
            }
        }
        v13z = p5[2] - e1[2];
        v14z = p5[2] - e2[2];

        if ((fbits_002E0200(N[2]) & 0x7FFFFFFF) - 0x3F800000 < 0) {
            /* a near-vertical plane (|N.z| < 1): the axis point nearest V0's height */
            v13[2] = 0.0f - p4[2];
            goto clamp2;
        } else {
            Qv = vdiv_002E0200(dB, st->H * N[2]);
            if ((fbits_002E0200(p4[2]) | fbits_002E0200(v11z) | fbits_002E0200(v12z)) >= 0) {
                /* the base is above the triangle: project the base */
                Qv = vdiv_002E0200(dB, dot_002E0200(N, N));
                for (i = 0; i < 3; i++) {
                    v13[i] = p4[i];
                    v8[i] = N[i] * Qv;
                }
                goto proj;
            }
            if ((fbits_002E0200(p5[2]) & fbits_002E0200(v13z) & fbits_002E0200(v14z)) < 0) {
                /* the top is below the triangle: project the top */
                Qv = vdiv_002E0200(dT, dot_002E0200(N, N));
                for (i = 0; i < 3; i++) {
                    v13[i] = p5[i];
                    v8[i] = N[i] * Qv;
                }
                goto proj;
            }
            {
                /* the axis crosses the triangle's height: where it meets the plane, or the nearest edge point */
                float v5[3], v9[3], v10[3], s7, s8, s9, t;
                float v7z = st->H * Qv;
                v5[0] = p4[0];
                v5[1] = p4[1];
                v5[2] = p4[2] - v7z;
                for (i = 0; i < 3; i++) {
                    v9[i] = e2[i] - e1[i];
                    v10[i] = v5[i] - e1[i];
                }
                cross_002E0200(c7, v5, e1);
                cross_002E0200(c8, e2, v5);
                cross_002E0200(c9, v10, v9);
                s7 = side_002E0200(c7, N);
                s8 = side_002E0200(c8, N);
                s9 = side_002E0200(c9, N);
                if (!neg_002E0200(s7) && !neg_002E0200(s8) && !neg_002E0200(s9)) {
                    v13[2] = v5[2] - p4[2];
                    goto clamp2;
                }
                if (neg_002E0200(s7)) {
                    A[0] = A[1] = A[2] = 0.0f;
                    for (i = 0; i < 3; i++) {
                        B[i] = e1[i] + 0.0f;
                    }
                } else if (neg_002E0200(s8)) {
                    for (i = 0; i < 3; i++) {
                        A[i] = e2[i] + 0.0f;
                    }
                    B[0] = B[1] = B[2] = 0.0f;
                } else {
                    for (i = 0; i < 3; i++) {
                        A[i] = e1[i] + 0.0f;
                        B[i] = e2[i] + 0.0f;
                    }
                }
                for (i = 0; i < 3; i++) {
                    v9[i] = v5[i] - A[i];
                    B[i] = B[i] - A[i];
                }
                t = seg_t_002E0200(v9, B);
                v13[2] = ((0.0f + A[2]) + B[2] * t) - p4[2];
            }
        }
    clamp2:
        /* the axis point: the base raised by clamp(z - base.z, 0, H) */
        v13[2] = min_002E0200(v13[2], st->H);
        v13[2] = max_002E0200(v13[2], 0.0f);
        v13[2] = v13[2] + p4[2];
        v13[0] = p4[0];
        v13[1] = p4[1];
        Qv = vdiv_002E0200(dot_002E0200(v13, N), dot_002E0200(N, N));
        for (i = 0; i < 3; i++) {
            v8[i] = N[i] * Qv;
        }
    proj:
        for (i = 0; i < 3; i++) {
            m[i] = v8[i] * v8[i];
            v4[i] = v13[i] - v8[i];
        }
        d2 = (m[0] + m[1]) + m[2];
        {
            float v10[3], v11[3], s7, s8, s9;
            cross_002E0200(c7, v4, e1);
            for (i = 0; i < 3; i++) {
                v10[i] = e2[i] - e1[i];
                v11[i] = v4[i] - e1[i];
            }
            cross_002E0200(c8, e2, v4);
            cross_002E0200(c9, v11, v10);
            st->a3r = 0;
            if (neg_002E0200(st->best - d2)) {
                continue;
            }
            for (i = 0; i < 3; i++) {
                c7[i] = c7[i] * N[i];
            }
            st->a3r = (unsigned int)fbits_002E0200(c7[0]);
            s7 = (c7[1] + c7[0]) + c7[2];
            s8 = side_002E0200(c8, N);
            s9 = side_002E0200(c9, N);
            edge = 1;
            if (neg_002E0200(s7)) {
                A[0] = A[1] = A[2] = 0.0f;
                for (i = 0; i < 3; i++) {
                    B[i] = e1[i] + 0.0f;
                }
            } else if (neg_002E0200(s8)) {
                for (i = 0; i < 3; i++) {
                    A[i] = e2[i] + 0.0f;
                }
                B[0] = B[1] = B[2] = 0.0f;
            } else if (!neg_002E0200(s9)) {
                edge = 0;
            } else {
                for (i = 0; i < 3; i++) {
                    A[i] = e1[i] + 0.0f;
                    B[i] = e2[i] + 0.0f;
                }
            }
            if (edge) {
                float v9[3], t, dv[3];
                for (i = 0; i < 3; i++) {
                    v9[i] = v4[i] - A[i];
                    B[i] = B[i] - A[i];
                }
                t = seg_t_002E0200(v9, B);
                for (i = 0; i < 3; i++) {
                    v4[i] = (0.0f + A[i]) + B[i] * t;
                }
                for (i = 0; i < 3; i++) {
                    dv[i] = v4[i] - v13[i];
                    dv[i] = dv[i] * dv[i];
                }
                d2 = (dv[0] + dv[1]) + dv[2];
                if (neg_002E0200(st->best - d2)) {
                    continue;
                }
            }
        }
        /* hit (retail 0x2E09E0) */
        {
            float w0[3];
            st->s5 = owner;
            for (i = 0; i < 3; i++) {
                w0[i] = V0[i] + origin[i];
            }
            st->s6 = fl + 4096;
            st->best = d2 * bitsf_002E0200(0x3F7FDF3B);
            for (i = 0; i < 3; i++) {
                st->v26[i] = N[i] + 0.0f;
                st->v25[i] = v4[i] + w0[i];
                st->v27[i] = 0.0f + w0[i];
                st->v28[i] = e1[i] + w0[i];
                st->v29[i] = e2[i] + w0[i];
            }
        }
    }
}

/* CollCylinder: the upright cylinder (base centre pos xyz, radius r, height h) against the level collision (unless
   flags & 1) and the mobys' collision. Level: the octree D_L00_001BF200+0 is looked up for every 4-unit cell whose
   box is within r of the base; each found cell's chunk is DMA'd to the scratchpad, its packed vertices (10/10/12 bits
   around the cell centre) unpacked with box outcodes at 0x70002000, its triangles and quads (as second triangles)
   tested. Mobys (moby grid D_L00_001DE860, table D_L00_001B1E9C): those whose sphere reaches the cylinder, their
   triangles, then their primitives (unless flags & 2). Keeps the closest hit (squared distance from the axis, shrunk
   by 0.9995 for triangles). No hit: returns 0. Otherwise returns 1 and writes D_L00_001BF200: +0x18 the moby (the
   octree for the level), +0x1C the triangle's material + 0x1000 or minus the primitive's address, +0x20 the closest
   point, +0x30 that point pushed out to the radius from the axis, +0x40 N (or the primitive push), +0x50/+0x60/+0x70
   the triangle (world units). flags: 1 no level, 2 no primitives, 4 the other primitive class and count, 0x10 two-
   sided, 0x20 only material (flags >> 8) & 0x1F, 0x80 skip triangles flagged 0x80. */
int func_L00_002E0200(float r, void *pos_, int flags, void *skip, float h)
{
    float *pos = (float *)pos_;
    unsigned char *D = D_L00_001BF200;
    St_002E0200 st;
    float lo[3], hi[3];
    int stamp;
    unsigned char *tree;
    int i;

    st.flags = flags;
    stamp = *(int *)(D + 16);
    for (i = 0; i < 3; i++) {
        lo[i] = pos[i] - r;
        hi[i] = pos[i] + r;
    }
    hi[2] = hi[2] + h;
    for (i = 0; i < 3; i++) {
        st.q[i] = pos[i] * 1024.0f;
    }
    st.R = r * 1024.0f;
    st.H = h * 1024.0f;
    if (stamp < 0) {
        return 0;
    }
    st.s5 = 0;
    st.s6 = 0;
    st.a3r = 0;
    stamp = stamp + 1;
    *(int *)(D + 16) = stamp;
    if (neg_002E0200(lo[0]) || neg_002E0200(lo[1]) || neg_002E0200(lo[2])) {
        return 0;
    }
    tree = *(unsigned char **)(D + 0);
    if (fbits_002E0200(r) <= 0) {
        return 0;
    }
    if (!(neg_002E0200(hi[0] - 1024.0f) && neg_002E0200(hi[1] - 1024.0f) && neg_002E0200(hi[2] - 1024.0f))) {
        return 0;
    }
    if (fbits_002E0200(h) <= 0) {
        return 0;
    }
    {
        int ilo[3], ihi[3];
        float mR2;

        for (i = 0; i < 3; i++) {
            ilo[i] = ftoi0_002E0200(lo[i]);
            ihi[i] = ftoi0_002E0200(hi[i]);
        }
        st.best = st.R * st.R;
        for (i = 0; i < 3; i++) {
            lo[i] = lo[i] * 1024.0f;
            hi[i] = hi[i] * 1024.0f;
        }
        mR2 = 0.0f - st.best;
        st.best = st.best * bitsf_002E0200(0x3F7FDF3B);

        if ((flags & 1) == 0) {
            unsigned int x, y, z;
            unsigned int x0 = (unsigned int)ilo[0] >> 2, y0 = (unsigned int)ilo[1] >> 2, z0 = (unsigned int)ilo[2] >> 2;
            unsigned int x1 = (unsigned int)ihi[0] >> 2, y1 = (unsigned int)ihi[1] >> 2, z1 = (unsigned int)ihi[2] >> 2;
            float org[3];
            float *rec = (float *)0x70003800;
            int started = 0;
            unsigned char *s7;
            unsigned int *cl;

            *(unsigned int *)0x70000000 = 0;
            *(unsigned int *)0x70000004 = 0;
            org[0] = (float)(int)(x0 << 12);
            org[1] = (float)(int)(y0 << 12);
            org[2] = (float)(int)(z0 << 12);
            for (z = z0;; z++) {
                float oy = (float)(int)(y0 << 12);
                org[1] = oy;
                for (y = y0;; y++) {
                    org[0] = (float)(int)(x0 << 12);
                    for (x = x0;; x++) {
                        float c[3], d;
                        for (i = 0; i < 3; i++) {
                            float m = org[i] + 4096.0f;
                            float v = max_002E0200(org[i], st.q[i]);
                            v = min_002E0200(v, m);
                            c[i] = v - st.q[i];
                            c[i] = c[i] * c[i];
                        }
                        d = ((mR2 + c[0]) + c[1]) + c[2];
                        if (neg_002E0200(d)) {
                            unsigned int w;
                            rec[0] = org[0] + 2048.0f;
                            rec[1] = org[1] + 2048.0f;
                            rec[2] = org[2] + 2048.0f;
                            ((unsigned int *)rec)[3] = 0;
                            w = cell_002E0200(tree, x, y, z);
                            ((unsigned int *)rec)[3] = w;
                            if (w != 0) {
                                rec += 4;
                                if (!started) {
                                    started = 1;
                                    dma_002E0200(w, 0, tree);
                                }
                            }
                        }
                        org[0] = org[0] + 4096.0f;
                        if (x == x1) {
                            break;
                        }
                    }
                    org[1] = org[1] + 4096.0f;
                    if (y == y1) {
                        break;
                    }
                }
                org[2] = org[2] + 4096.0f;
                if (z == z1) {
                    break;
                }
            }
            ((unsigned int *)rec)[3] = 0;

            s7 = (unsigned char *)0x70001000;
            for (cl = (unsigned int *)0x70003800; cl[3] != 0; cl += 4) {
                unsigned int next = cl[7];
                float v23[3], v22[3], l1[3], h1[3];
                int nv;

                v23[0] = ((float *)cl)[0];
                v23[1] = ((float *)cl)[1];
                v23[2] = ((float *)cl)[2];
                s7 = (unsigned char *)((unsigned long)s7 ^ 0x1000);
                while (*(volatile unsigned int *)0x1000D400 & 0x100) {
                }
                if (next != 0) {
                    unsigned char *ob = (unsigned char *)((unsigned long)s7 ^ 0x1000);
                    *(unsigned int *)ob = 0;
                    *(unsigned int *)(ob + 4) = 0;
                    dma_002E0200(next, (unsigned int)(unsigned long)ob, tree);
                }
                nv = s7[2];
                for (i = 0; i < 3; i++) {
                    l1[i] = lo[i] - v23[i];
                    h1[i] = hi[i] - v23[i];
                    v22[i] = st.q[i] - v23[i];
                }
                if (nv == 0) {
                    continue;
                }
                {
                    short l16[3], h16[3];
                    unsigned int *vw = (unsigned int *)(s7 + 4);
                    float *out = (float *)0x70002000;
                    unsigned int *tp, *tend, *t2;
                    int nq;

                    for (i = 0; i < 3; i++) {
                        l16[i] = (short)ftoi0_002E0200(l1[i]);
                        h16[i] = (short)ftoi0_002E0200(h1[i]);
                    }
                    do {
                        int hh;
                        for (hh = 0; hh < 2; hh++) {
                            unsigned int w = vw[hh];
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
                            out[hh * 4 + 0] = (float)v[0];
                            out[hh * 4 + 1] = (float)v[1];
                            out[hh * 4 + 2] = (float)v[2];
                            ((unsigned int *)out)[hh * 4 + 3] = oc;
                        }
                        vw += 2;
                        out += 8;
                        nv -= 2;
                    } while (nv > 0);

                    tp = (unsigned int *)(s7 + 4 + s7[2] * 4);
                    tend = tp + s7[0];
                    t2 = tp;
                    tris_002E0200(&st, tp, tend, v23, v22, (unsigned int)(unsigned long)tree);
                    nq = s7[3];
                    if (nq != 0) {
                        unsigned char *a = (unsigned char *)t2;
                        unsigned char *b = (unsigned char *)tend;
                        int k;
                        for (k = 0; k < nq; k++) {
                            unsigned char a2 = a[2];
                            unsigned char b0 = *b++;
                            a[1] = a2;
                            a[2] = b0;
                            a += 4;
                        }
                        tris_002E0200(&st, t2, t2 + nq, v23, v22, (unsigned int)(unsigned long)tree);
                    }
                }
            }
        }

        /* mobys (retail 0x2E0A60) */
        st.s5 = 0;
        {
            unsigned int x, y;
            unsigned int x0 = (unsigned int)ftoi0_002E0200(lo[0]) >> 14;
            unsigned int y0 = (unsigned int)ftoi0_002E0200(lo[1]) >> 14;
            unsigned int x1 = (unsigned int)ftoi0_002E0200(hi[0]) >> 14;
            unsigned int y1 = (unsigned int)ftoi0_002E0200(hi[1]) >> 14;
            unsigned int *L = (unsigned int *)0x70003800;
            unsigned char *s0 = (unsigned char *)0x70000000;

            st.a3r = (unsigned int)(unsigned long)D_L00_001DE860;
            for (y = y0;; y++) {
                for (x = x0;; x++) {
                    unsigned char *c = D_L00_001DE860 + x * 4 + y * 256;
                    unsigned char *s = D_L00_001DE860 + 0x4000 + *(unsigned short *)c * 32;
                    L[0] = (unsigned int)(unsigned long)s;
                    L[1] = (unsigned int)(unsigned long)(s + c[2] * 2);
                    L += 2;
                    if (x == x1) {
                        break;
                    }
                }
                if (y == y1) {
                    break;
                }
            }
            L[0] = 0;
            L[1] = 0;

            for (L = (unsigned int *)0x70003800; L[0] != 0; L += 2) {
                unsigned short *e = (unsigned short *)(unsigned long)L[0];
                while (e != (unsigned short *)(unsigned long)L[1]) {
                    unsigned char *m = D_L00_001B1E9C + (*e << 8);
                    unsigned char *col;
                    float *ms = (float *)m;
                    float dx, dy, T, T2, dd, zlo, zhi;
                    float pos15[3], rows[3][3], sc;

                    e++;
                    if ((void *)m == skip) {
                        continue;
                    }
                    T = st.R + ms[3];
                    dx = ms[0] - st.q[0];
                    dy = ms[1] - st.q[1];
                    col = *(unsigned char **)(m + 152);
                    zlo = ms[2] - T;
                    zhi = ms[2] + T;
                    T2 = T * T;
                    dx = dx * dx;
                    dy = dy * dy;
                    zlo = zlo - st.q[2];
                    zhi = zhi - st.q[2];
                    dd = (dx - T2) + dy;
                    zlo = zlo - st.H;
                    if (*(int *)(m + 160) == stamp) {
                        continue;
                    }
                    if (col == 0) {
                        continue;
                    }
                    if (fbits_002E0200(dd) > 0) {
                        continue;
                    }
                    if (fbits_002E0200(zhi) < 0) {
                        continue;
                    }
                    if (fbits_002E0200(zlo) >= 0) {
                        continue;
                    }
                    {
                        int count = *(unsigned short *)(col + (((flags & 4) == 0) ? 2 : 0));
                        int trib = *(int *)(col + 12);

                        *(int *)(m + 160) = stamp;
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
                                unsigned int *ent;
                                unsigned char *nb;

                                *(int *)(D + 12) = (slot + 1) & 7;
                                ent = *(unsigned int **)(D + 8) + slot * 2;
                                nb = *(unsigned char **)(D + 4) + slot * 2048;
                                ent[0] = id;
                                ent[1] = st.a3r;
                                func_002A3110(m, count, nb);
                                s0 = (unsigned char *)0x70000000;
                            }
                        }
                    }

                    for (i = 0; i < 3; i++) {
                        pos15[i] = ((float *)(m + 16))[i] * 1024.0f;
                    }
                    for (i = 0; i < 3; i++) {
                        rows[0][i] = ((float *)(m + 192))[i];
                        rows[1][i] = ((float *)(m + 208))[i];
                        rows[2][i] = ((float *)(m + 224))[i];
                    }
                    sc = *(float *)(m + 44);

                    if (*(int *)(col + 12) != 0 && *(int *)(m + 156) >= 0) {
                        float r3[3], r4[3], r5[3], v22[3], v11[3], v12[3];
                        int vbytes = *(int *)(col + 12);
                        int voff = *(int *)(col + 4) + 16;
                        short *vp = (short *)(col + voff);
                        float *out = (float *)0x70002000;
                        unsigned int *tp, *tend;

                        for (i = 0; i < 3; i++) {
                            r3[i] = rows[0][i] * sc;
                            r4[i] = rows[1][i] * sc;
                            r5[i] = rows[2][i] * sc;
                        }
                        for (i = 0; i < 3; i++) {
                            v22[i] = st.q[i] - pos15[i];
                        }
                        for (i = 0; i < 3; i++) {
                            v12[i] = v22[i] + st.R;
                            v11[i] = v22[i] - st.R;
                        }
                        v12[2] = v12[2] + st.H;
                        do {
                            int hh;
                            for (hh = 0; hh < 2; hh++) {
                                float v[3], w[3];
                                unsigned int oc = 0;
                                for (i = 0; i < 3; i++) {
                                    v[i] = (float)vp[i];
                                }
                                for (i = 0; i < 3; i++) {
                                    float a = r3[i] * v[0];
                                    a = a + r4[i] * v[1];
                                    w[i] = a + r5[i] * v[2];
                                }
                                for (i = 0; i < 3; i++) {
                                    unsigned int b = 0;
                                    if (neg_002E0200(w[i] - v11[i])) {
                                        b |= 1;
                                    }
                                    if (neg_002E0200(v12[i] - w[i])) {
                                        b |= 2;
                                    }
                                    oc |= b << (i * 8);
                                }
                                if (hh == 0) {
                                    st.a3r = neg_002E0200(v12[0] - w[0]) ? 2 : 0;
                                }
                                out[hh * 4 + 0] = w[0];
                                out[hh * 4 + 1] = w[1];
                                out[hh * 4 + 2] = w[2];
                                ((unsigned int *)out)[hh * 4 + 3] = oc;
                                vp += 4;
                            }
                            out += 8;
                            vbytes -= 16;
                        } while (vbytes > 0);

                        tp = (unsigned int *)(col + voff + *(int *)(col + 12));
                        tend = (unsigned int *)((unsigned char *)tp + *(int *)(col + 8));
                        tris_002E0200(&st, tp, tend, pos15, v22, (unsigned int)(unsigned long)m);
                    }

                    /* primitives (retail 0x2E0DE0) */
                    if ((flags & 2) == 0 && *(int *)(col + 4) != 0) {
                        unsigned char *pr = col + 16;
                        int want = ((flags & 4) == 0) + 1;
                        unsigned int mask = *(unsigned int *)(m + 156);
                        int last = 0;

                        while (last >= 0) {
                            int skipbit = mask & 1;
                            int type;
                            float c[3], cw, T3, dv[3], d2, ax[3], az;

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
                                xform_002E0200(c, rows[0], rows[1], rows[2], v, pos15);
                                cw = v[3];
                            } else if (type == 2) {
                                float *vt = (float *)(s0 + *(int *)(pr - 28) * 16);
                                float v[4];
                                for (i = 0; i < 3; i++) {
                                    v[i] = vt[i] + ((float *)(pr - 16))[i];
                                }
                                v[3] = ((float *)(pr - 32))[3];
                                for (i = 0; i < 4; i++) {
                                    v[i] = v[i] * sc;
                                }
                                xform_002E0200(c, rows[0], rows[1], rows[2], v, pos15);
                                cw = v[3];
                            } else {
                                float a[3], b[3], p4[3], sxy, bxy, Qv;
                                if (type == 3) {
                                    float v[4], len;
                                    for (i = 0; i < 4; i++) {
                                        v[i] = ((float *)(pr - 16))[i] * sc;
                                    }
                                    len = ((float *)(pr - 32))[1] * sc;
                                    xform_002E0200(a, rows[0], rows[1], rows[2], v, pos15);
                                    for (i = 0; i < 3; i++) {
                                        b[i] = rows[2][i] * len;
                                    }
                                    cw = v[3];
                                } else {
                                    float *va = (float *)(s0 + *(short *)(pr - 28) * 16);
                                    float *vb = (float *)(s0 + *(short *)(pr - 26) * 16);
                                    float u[3], w[3];
                                    for (i = 0; i < 3; i++) {
                                        u[i] = va[i] * sc;
                                        w[i] = vb[i] * sc;
                                    }
                                    cw = ((float *)(pr - 32))[3] * sc;
                                    xform_002E0200(a, rows[0], rows[1], rows[2], u, pos15);
                                    xform_002E0200(b, rows[0], rows[1], rows[2], w, pos15);
                                    for (i = 0; i < 3; i++) {
                                        b[i] = b[i] - a[i];
                                    }
                                }
                                for (i = 0; i < 3; i++) {
                                    p4[i] = st.q[i] - a[i];
                                }
                                /* the segment's point nearest the axis in xy; a near-vertical segment gives its
                                   point at the base's height */
                                sxy = p4[0] * b[0];
                                bxy = b[0] * b[0];
                                sxy = sxy + p4[1] * b[1];
                                bxy = bxy + b[1] * b[1];
                                Qv = vdiv_002E0200(sxy, bxy);
                                bxy = (bxy < 0.0f) ? -bxy : bxy;
                                st.a3r = 0;
                                if (!neg_002E0200(1.0f - bxy)) {
                                    float bz = b[2] + a[2];
                                    c[0] = a[0];
                                    c[1] = a[1];
                                    c[2] = max_002E0200(a[2], st.q[2]);
                                    c[2] = min_002E0200(bz, c[2]);
                                } else {
                                    float t = 0.0f + Qv;
                                    t = max_002E0200(t, 0.0f);
                                    t = min_002E0200(t, 1.0f);
                                    for (i = 0; i < 3; i++) {
                                        c[i] = (0.0f + a[i]) + b[i] * t;
                                    }
                                }
                            }
                            /* the axis point nearest c */
                            az = c[2] - st.q[2];
                            T3 = st.R + cw;
                            az = min_002E0200(az, st.H);
                            az = max_002E0200(az, 0.0f);
                            ax[0] = st.q[0];
                            ax[1] = st.q[1];
                            ax[2] = st.q[2] + az;
                            for (i = 0; i < 3; i++) {
                                dv[i] = c[i] - ax[i];
                            }
                            T3 = T3 * T3;
                            for (i = 0; i < 3; i++) {
                                dv[i] = dv[i] * dv[i];
                            }
                            d2 = (dv[0] + dv[1]) + dv[2];
                            if (neg_002E0200(T3 - d2)) {
                                continue;
                            }
                            {
                                float dist, inv, k, s5v[3];
                                dist = 0.0f + sqrtf(d2 < 0.0f ? -d2 : d2);
                                inv = vdiv_002E0200(1.0f, dist);
                                dist = dist * 1.0f;
                                k = min_002E0200(dist, cw);
                                inv = 0.0f + inv;
                                for (i = 0; i < 3; i++) {
                                    s5v[i] = ax[i] - c[i];
                                    s5v[i] = s5v[i] * inv;
                                    s5v[i] = s5v[i] * k;
                                    c[i] = c[i] + s5v[i];
                                }
                                for (i = 0; i < 3; i++) {
                                    dv[i] = c[i] - ax[i];
                                    dv[i] = dv[i] * dv[i];
                                }
                                d2 = (dv[0] + dv[1]) + dv[2];
                                if (neg_002E0200(st.best - d2)) {
                                    continue;
                                }
                                st.s5 = (unsigned int)(unsigned long)m;
                                st.s6 = -(unsigned int)(unsigned long)(pr - 32);
                                st.best = d2 * 1.0f;
                                for (i = 0; i < 3; i++) {
                                    st.v25[i] = 0.0f + c[i];
                                    st.v26[i] = 0.0f + s5v[i];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /* retail 0x2E1040 */
    if (st.s6 == 0) {
        return 0;
    }
    {
        float Qv = vdiv_002E0200(st.R, sqrtf(st.best < 0.0f ? -st.best : st.best));
        float k = bitsf_002E0200(0x3A800000);
        float v1[3], v2[3];
        float *o;

        for (i = 0; i < 3; i++) {
            v2[i] = st.q[i] - st.v25[i];
            v1[i] = st.v25[i] - st.q[i];
        }
        for (i = 0; i < 3; i++) {
            st.v25[i] = st.v25[i] * k;
            st.v27[i] = st.v27[i] * k;
            st.v28[i] = st.v28[i] * k;
            st.v29[i] = st.v29[i] * k;
        }
        o = (float *)(D + 32);
        for (i = 0; i < 3; i++) {
            o[i] = st.v25[i];
        }
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 64);
        for (i = 0; i < 3; i++) {
            o[i] = st.v26[i];
        }
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 80);
        for (i = 0; i < 3; i++) {
            o[i] = st.v27[i];
        }
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 96);
        for (i = 0; i < 3; i++) {
            o[i] = st.v28[i];
        }
        ((unsigned int *)o)[3] = 0;
        o = (float *)(D + 112);
        for (i = 0; i < 3; i++) {
            o[i] = st.v29[i];
        }
        ((unsigned int *)o)[3] = 0;
        *(unsigned int *)(D + 24) = st.s5;
        *(unsigned int *)(D + 28) = st.s6;
        v1[2] = min_002E0200(v1[2], st.H);
        v1[2] = max_002E0200(v1[2], 0.0f);
        v2[2] = v2[2] + v1[2];
        for (i = 0; i < 3; i++) {
            v2[i] = v2[i] * Qv;
        }
        v2[2] = v2[2] - v1[2];
        for (i = 0; i < 3; i++) {
            v2[i] = v2[i] * k;
            v2[i] = v2[i] + st.v25[i];
        }
        o = (float *)(D + 48);
        for (i = 0; i < 3; i++) {
            o[i] = v2[i];
        }
    }
    return 1;
}
