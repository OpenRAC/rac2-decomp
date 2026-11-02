/* functional: medium. Written from the hand-written VU0/MMI assembly: plain floats in the VU's order (sums as (x + y) + 1*z, ACC chains left to right), the same reads, writes and calls in the same order. VU rounding is not reproduced; vdiv by zero gives +-FLT_MAX as the VU does; vsqrt is sqrtf of |x|. The two MAC-flag tests (cfc2 $vi17) are the sign bits of (p - r) and (p + r - 1024). Retail's caller-saved s registers kept in the upper halves (pcpyld/pcpyud) have no C spelling. The word +4 of a new collision-cache entry gets whatever $a3 held (a leftover of the previous moby's tests); it is reproduced as retail computes it (`a3r`), except right after a func_002A3110 call with no triangle pass in between, where retail's $a3 is that function's leftover and here the previous value. */
extern unsigned char D_001BAF80[];
extern unsigned char *D_001B1B5C;
extern unsigned char D_001D24E0[];
extern unsigned int D_001BF000[];
extern unsigned char D_001BF200[];
extern float sqrtf(float);
extern void func_002A3110(void *moby, int count, void *buf);

#define FMAX_277F48 3.40282347e+38f

static int fbits_277F48(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i;
}

static int neg_277F48(float f)
{
    return fbits_277F48(f) < 0;
}

static float vdiv_277F48(float n, float d)
{
    float q;
    if (d == 0.0f) {
        return ((fbits_277F48(n) ^ fbits_277F48(d)) < 0) ? -FMAX_277F48 : FMAX_277F48;
    }
    q = n / d;
    if (q > FMAX_277F48) {
        q = FMAX_277F48;
    } else if (q < -FMAX_277F48) {
        q = -FMAX_277F48;
    }
    return q;
}

static int ftoi0_277F48(float f)
{
    if (f >= 2147483647.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)(-2147483647 - 1);
    }
    return (int)f;
}

/* (a.x*b.x + a.y*b.y) + 1*(a.z*b.z), as vmul then vadday/vmaddz */
static float dot_277F48(const float *a, const float *b)
{
    float x = a[0] * b[0];
    float y = a[1] * b[1];
    float z = a[2] * b[2];
    return (x + y) + z;
}

/* r = a x b as vopmula ACC,a,b / vopmsub r,b,a compute it */
static void cross_277F48(float *r, const float *a, const float *b)
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

/* r = ((m0*v.x + m1*v.y) + m2*v.z) + t*k, the moby transform */
static void xform_277F48(float *r, const float *m0, const float *m1, const float *m2, const float *v, const float *t, float k)
{
    float o[3];
    int i;
    for (i = 0; i < 3; i++) {
        float a = m0[i] * v[0];
        a = a + m1[i] * v[1];
        a = a + m2[i] * v[2];
        o[i] = a + t[i] * k;
    }
    r[0] = o[0];
    r[1] = o[1];
    r[2] = o[2];
}

/* t = clamp(dot(p, e) / dot(e, e), 0, 1) */
static float seg_t_277F48(const float *p, const float *e)
{
    float t = 0.0f + vdiv_277F48(dot_277F48(p, e), dot_277F48(e, e));
    if (!(t > 0.0f)) {
        t = 0.0f;
    }
    if (!(t < 1.0f)) {
        t = 1.0f;
    }
    return t;
}

/* Collects the mobys whose collision touches the sphere (pos xyz, radius r): the cells of the 64x64 grid
   D_001D24E0 under the sphere's box, each moby once (stamp at +0xA0 against D_001BAF80+0x10), not `skip`, with a
   collision (+0x98) and a bounding sphere (+0x00, w radius) that overlaps; then its triangles (vertices transformed
   into scratchpad 0x70002000, outcodes against the box, material filters from `flags`) and its primitives
   (spheres, capsules, joint-relative spheres from the vertex cache D_001BAF80+4/+8, func_002A3110 filling a new
   one). Hits are listed at D_001BF000 (0-terminated); D_001BAF80+0x18 gets the first, +0x1C 63, +0x20 (0,0,0,1).
   With `rec`, each hit moby flagged 0x4000 at +0x34 gets a 64-byte record in the ring D_001BF200 (slot at
   +0xA8, ring index D_001BAF80+0x14), or has rec's +0x14 word ORed into its live one. Returns the hit count. */
int func_00277F48(void *pos_, int flags, char *skip, void *rec_, float r)
{
    float *pos = (float *)pos_;
    unsigned char *rec = (unsigned char *)rec_;
    unsigned char *D = D_001BAF80;
    unsigned int *hits = D_001BF000;
    unsigned int *hp;
    float q[3], lo[3], hi[3];
    float R, R2;
    int stamp;
    unsigned int x, y, x0, y0, x1, y1;
    unsigned int *L;
    unsigned char *s0 = (unsigned char *)0x70000000;
    unsigned int a3r = (unsigned int)(unsigned long)D_001D24E0;
    int i;

    for (i = 0; i < 3; i++) {
        lo[i] = pos[i] - r;
        hi[i] = pos[i] + r;
        q[i] = pos[i] * 1024.0f;
    }
    R = r * 1024.0f;
    stamp = *(int *)(D + 16);
    if (stamp < 0) {
        return 0;
    }
    stamp = stamp + 1;
    *(int *)(D + 16) = stamp;
    if (neg_277F48(lo[0]) || neg_277F48(lo[1]) || neg_277F48(lo[2])) {
        return 0;
    }
    if (fbits_277F48(r) <= 0) {
        return 0;
    }
    if (!(neg_277F48(hi[0] - 1024.0f) && neg_277F48(hi[1] - 1024.0f) && neg_277F48(hi[2] - 1024.0f))) {
        return 0;
    }
    R2 = R * R;

    x0 = (unsigned int)ftoi0_277F48(lo[0]) >> 4;
    y0 = (unsigned int)ftoi0_277F48(lo[1]) >> 4;
    x1 = (unsigned int)ftoi0_277F48(hi[0]) >> 4;
    y1 = (unsigned int)ftoi0_277F48(hi[1]) >> 4;
    L = (unsigned int *)0x70003800;
    for (y = y0;; y++) {
        for (x = x0;; x++) {
            unsigned char *c = D_001D24E0 + x * 4 + y * 256;
            unsigned char *s = D_001D24E0 + 0x4000 + *(unsigned short *)c * 32;
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

    hp = hits;
    for (L = (unsigned int *)0x70003800;; L += 2) {
        unsigned short *e = (unsigned short *)(unsigned long)L[0];
        if (e == 0) {
            break;
        }
        while (e != (unsigned short *)(unsigned long)L[1]) {
            unsigned char *m = D_001B1B5C + (*e << 8);
            unsigned char *col;
            float *ms = (float *)m;
            float d[3], tq, dd;
            float pos15[3], rows[3][3], sc;
            int hit = 0;

            e++;
            if ((char *)m == skip) {
                continue;
            }
            col = *(unsigned char **)(m + 152);
            tq = R + ms[3];
            for (i = 0; i < 3; i++) {
                d[i] = ms[i] - q[i];
            }
            tq = tq * tq;
            for (i = 0; i < 3; i++) {
                d[i] = d[i] * d[i];
            }
            dd = ((d[0] - tq) + d[1]) + d[2];
            if (*(int *)(m + 160) == stamp) {
                continue;
            }
            if (col == 0) {
                continue;
            }
            if (fbits_277F48(dd) > 0) {
                continue;
            }
            {
                int count = *(unsigned short *)(col + (((flags & 4) == 0) ? 2 : 0));
                int id = *(int *)(m + 172);

                *(int *)(m + 160) = stamp;
                if (count != 0) {
                    unsigned int *t = *(unsigned int **)(D + 8);
                    unsigned char *buf = *(unsigned char **)(D + 4);
                    int k;

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
                        ent[1] = a3r;
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

            /* triangles */
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
                    v22[i] = q[i] - pos15[i];
                }
                for (i = 0; i < 3; i++) {
                    v11[i] = v22[i] - R;
                    v12[i] = v22[i] + R;
                }
                do {
                    int h;
                    for (h = 0; h < 2; h++) {
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
                            if (neg_277F48(w[i] - v11[i])) {
                                b |= 1;
                            }
                            if (neg_277F48(v12[i] - w[i])) {
                                b |= 2;
                            }
                            if (h == 0 && i == 0) {
                                a3r = neg_277F48(v12[0] - w[0]) ? 2 : 0;
                            }
                            oc |= b << (i * 8);
                        }
                        out[h * 4 + 0] = w[0];
                        out[h * 4 + 1] = w[1];
                        out[h * 4 + 2] = w[2];
                        out[h * 4 + 3] = (float)0;
                        ((unsigned int *)out)[h * 4 + 3] = oc;
                        vp += 4;
                    }
                    out += 8;
                    vbytes -= 16;
                } while (vbytes > 0);

                tp = (unsigned int *)(col + voff + *(int *)(col + 12));
                tend = (unsigned int *)((unsigned char *)tp + *(int *)(col + 8));
                for (; tp != tend; tp++) {
                    unsigned int tw = *tp;
                    float *V0 = (float *)(unsigned long)(0x70002000 + (tw & 0xFF) * 16);
                    float *V1 = (float *)(unsigned long)(0x70002000 + ((tw >> 8) & 0xFF) * 16);
                    float *V2 = (float *)(unsigned long)(0x70002000 + ((tw >> 16) & 0xFF) * 16);
                    unsigned int fl = tw >> 24;
                    float e1[3], e2[3], p[3], N[3], c7[3], c8[3], c9[3], e3[3], p1[3];
                    float dn, nn, Qv, dist2;
                    float A[3], B[3];

                    a3r = ((unsigned int *)V1)[3]; /* retail 0x278358: lw a3,12(v0), left in $a3 by a rejected triangle */
                    if ((int)(((unsigned int *)V0)[3] & ((unsigned int *)V1)[3] & ((unsigned int *)V2)[3]) > 0) {
                        continue;
                    }
                    if ((int)((flags & 0x80) & fl) > 0) {
                        continue;
                    }
                    for (i = 0; i < 3; i++) {
                        e1[i] = V1[i] - V0[i];
                        e2[i] = V2[i] - V0[i];
                        p[i] = v22[i] - V0[i];
                    }
                    a3r = (((unsigned int)flags >> 8) ^ fl) & 0x1F;
                    cross_277F48(N, e2, e1);
                    if (((flags & 0x20) == 0) == 0 && a3r == 0) {
                        continue;
                    }
                    dn = dot_277F48(p, N);
                    nn = dot_277F48(N, N);
                    Qv = vdiv_277F48(dn, nn);
                    a3r = 0;
                    if ((flags & 0x10) == 0 && neg_277F48(dn)) {
                        continue;
                    }
                    for (i = 0; i < 3; i++) {
                        float nq = N[i] * Qv;
                        p[i] = p[i] + (0.0f - N[i]) * Qv;
                        c7[i] = nq * nq;
                    }
                    for (i = 0; i < 3; i++) {
                        e3[i] = e2[i] - e1[i];
                        p1[i] = p[i] - e1[i];
                    }
                    dist2 = (c7[0] + c7[1]) + c7[2];
                    cross_277F48(c7, p, e1);
                    cross_277F48(c8, e2, p);
                    cross_277F48(c9, p1, e3);
                    if (neg_277F48(R2 - dist2)) {
                        continue;
                    }
                    for (i = 0; i < 3; i++) {
                        c7[i] = c7[i] * N[i];
                        c8[i] = c8[i] * N[i];
                        c9[i] = c9[i] * N[i];
                    }
                    a3r = (unsigned int)fbits_277F48(c7[0]);
                    c7[1] = (c7[1] + c7[0]) + c7[2];
                    c8[1] = (c8[1] + c8[0]) + c8[2];
                    c9[1] = (c9[1] + c9[0]) + c9[2];
                    if (neg_277F48(c7[1])) {
                        A[0] = A[1] = A[2] = 0.0f;
                        B[0] = e1[0];
                        B[1] = e1[1];
                        B[2] = e1[2];
                    } else if (neg_277F48(c8[1])) {
                        A[0] = e2[0];
                        A[1] = e2[1];
                        A[2] = e2[2];
                        B[0] = B[1] = B[2] = 0.0f;
                    } else if (!neg_277F48(c9[1])) {
                        hit = 1;
                        break;
                    } else {
                        A[0] = e1[0];
                        A[1] = e1[1];
                        A[2] = e1[2];
                        B[0] = e2[0];
                        B[1] = e2[1];
                        B[2] = e2[2];
                    }
                    {
                        float pa[3], ba[3], t, cl[3], dv[3];
                        for (i = 0; i < 3; i++) {
                            A[i] = A[i] + 0.0f;
                            B[i] = B[i] + 0.0f;
                            pa[i] = p[i] - A[i];
                            ba[i] = B[i] - A[i];
                        }
                        t = seg_t_277F48(pa, ba);
                        for (i = 0; i < 3; i++) {
                            cl[i] = (0.0f + A[i]) + ba[i] * t;
                        }
                        for (i = 0; i < 3; i++) {
                            dv[i] = v22[i] - V0[i];
                            dv[i] = cl[i] - dv[i];
                            dv[i] = dv[i] * dv[i];
                        }
                        if (neg_277F48(R2 - ((dv[0] + dv[1]) + dv[2]))) {
                            continue;
                        }
                        hit = 1;
                        break;
                    }
                }
                if (hit) {
                    *hp++ = (unsigned int)(unsigned long)m;
                    continue;
                }
            }

            /* primitives */
            if (*(int *)(col + 4) != 0) {
                unsigned char *pr = col + 16;
                int want = ((flags & 4) == 0) + 1;
                unsigned int mask = *(unsigned int *)(m + 156);
                int last = 0;

                while (last >= 0) {
                    int skipbit = mask & 1;
                    int type;
                    float c[4], cw, tq3, dv[3], d2;

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
                        xform_277F48(c, rows[0], rows[1], rows[2], v, pos15, 1.0f);
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
                        xform_277F48(c, rows[0], rows[1], rows[2], v, pos15, 1.0f);
                        cw = v[3];
                    } else {
                        float a[3], b[3], p4[3], t;
                        if (type == 3) {
                            float v[4], len;
                            for (i = 0; i < 4; i++) {
                                v[i] = ((float *)(pr - 16))[i] * sc;
                            }
                            len = ((float *)(pr - 32))[1] * sc;
                            xform_277F48(a, rows[0], rows[1], rows[2], v, pos15, 1.0f);
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
                            xform_277F48(a, rows[0], rows[1], rows[2], u, pos15, 1.0f);
                            xform_277F48(b, rows[0], rows[1], rows[2], w, pos15, 1.0f);
                            for (i = 0; i < 3; i++) {
                                b[i] = b[i] - a[i];
                            }
                        }
                        for (i = 0; i < 3; i++) {
                            p4[i] = q[i] - a[i];
                        }
                        t = seg_t_277F48(p4, b);
                        for (i = 0; i < 3; i++) {
                            c[i] = a[i] + b[i] * t;
                        }
                    }
                    /* sphere (c, cw) against the query sphere */
                    tq3 = R + cw;
                    for (i = 0; i < 3; i++) {
                        dv[i] = c[i] - q[i];
                    }
                    tq3 = tq3 * tq3;
                    for (i = 0; i < 3; i++) {
                        dv[i] = dv[i] * dv[i];
                    }
                    d2 = (dv[0] + dv[1]) + dv[2];
                    if (neg_277F48(tq3 - d2)) {
                        continue;
                    }
                    {
                        float dist, inv, k;
                        dist = 0.0f + sqrtf(d2 < 0.0f ? -d2 : d2);
                        inv = 0.0f + vdiv_277F48(1.0f, dist);
                        dist = dist * 1.0f;
                        k = (dist < cw) ? dist : cw;
                        for (i = 0; i < 3; i++) {
                            float s5 = q[i] - c[i];
                            s5 = s5 * inv;
                            s5 = s5 * k;
                            c[i] = c[i] + s5;
                        }
                        for (i = 0; i < 3; i++) {
                            dv[i] = c[i] - q[i];
                            dv[i] = dv[i] * dv[i];
                        }
                        if (neg_277F48(R2 - ((dv[0] + dv[1]) + dv[2]))) {
                            continue;
                        }
                    }
                    hit = 1;
                    break;
                }
                if (hit) {
                    *hp++ = (unsigned int)(unsigned long)m;
                }
            }
        }
    }

    *hp = 0;
    *(unsigned int *)(D + 32) = 0;
    *(unsigned int *)(D + 36) = 0;
    *(unsigned int *)(D + 40) = 0;
    *(float *)(D + 44) = 1.0f;
    *(int *)(D + 28) = 63;
    *(unsigned int *)(D + 24) = hits[0];
    if (rec != 0 && hp != hits) {
        int ring = *(int *)(D + 20);
        unsigned int w0[8], w2[2];
        unsigned int *hq;

        for (i = 0; i < 8; i++) {
            w0[i] = ((unsigned int *)rec)[i];
        }
        w2[0] = ((unsigned int *)rec)[8];
        w2[1] = ((unsigned int *)rec)[9];
        for (hq = hits; hq != hp; hq++) {
            unsigned char *m = (unsigned char *)(unsigned long)*hq;
            int slot = *(signed char *)(m + 168);
            unsigned int add = 0;
            unsigned char *a0;

            if ((*(unsigned short *)(m + 52) & 0x4000) == 0) {
                continue;
            }
            a0 = D_001BF200 + ring * 64;
            if (slot >= 0) {
                unsigned char *o = D_001BF200 + slot * 64;
                if (*(unsigned char **)(o + 56) == m) {
                    if (*(int *)(o + 44) - *(int *)(rec + 28) >= 0) {
                        *(unsigned int *)(o + 36) = *(unsigned int *)(o + 36) | *(unsigned int *)(rec + 20);
                        continue;
                    }
                    add = *(unsigned int *)(o + 36);
                }
            }
            ((unsigned int *)a0)[0] = 0;
            ((unsigned int *)a0)[1] = 0;
            ((unsigned int *)a0)[2] = 0;
            ((float *)a0)[3] = 1.0f;
            *(unsigned int *)(a0 + 60) = 0;
            for (i = 0; i < 8; i++) {
                ((unsigned int *)(a0 + 16))[i] = w0[i];
            }
            ((unsigned int *)(a0 + 48))[0] = w2[0];
            ((unsigned int *)(a0 + 48))[1] = w2[1];
            *(unsigned int *)(a0 + 36) = *(unsigned int *)(rec + 20) | add;
            *(unsigned char **)(a0 + 56) = m;
            *(signed char *)(m + 168) = ring;
            ring = (ring + 1) & 63;
        }
        *(int *)(D + 20) = ring;
    }
    return hp - hits;
}
