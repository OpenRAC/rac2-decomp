/* functional: medium. Plain floats in place of VU0 macro code, in the assembly's order of operations; the cross products follow the VU opmula/opmsub pattern (a x b = a.y*b.z - b.y*a.z, ...); the w lanes of the hit record are left as they were (retail stores stale vector register lanes there); the fourth argument is unused by retail too; the VU divide by zero gives the largest finite float, written out here. */
#include "common.h"

#define TRIANGLES ((float *)0x001C0200)     /* 64 bytes each: v0, v1, v2, normal (4 floats each) */
#define HIT ((float *)0x001BAF80)           /* the hit record */

static int neg_00278CE0(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

static int pos_00278CE0(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i > 0;
}

static float div_00278CE0(float n, float d)
{
    union {
        float f;
        int i;
    } un, ud, r;

    if (d == 0.0f) {
        un.f = n;
        ud.f = d;
        r.i = ((un.i ^ ud.i) < 0) ? (int)0xFF7FFFFF : 0x7F7FFFFF;
        return r.f;
    }
    return n / d;
}

/* a x b the way the VU forms it: ACC = (a.y*b.z, a.z*b.x, a.x*b.y), minus (b.y*a.z, b.z*a.x, b.x*a.y). */
static void cross_00278CE0(float *out, float *a, float *b)
{
    float x = a[1] * b[2];
    float y = a[2] * b[0];
    float z = a[0] * b[1];

    out[0] = x - b[1] * a[2];
    out[1] = y - b[2] * a[0];
    out[2] = z - b[0] * a[1];
}

/* TestLineVsGatheredTris: tests the segment from a (4 floats) to b against the first `count`
   triangles gathered at 0x1C0200 (vertices v0, v1, v2 and the normal, 64 bytes each). A triangle
   counts when the segment starts on the back of its plane (dot(v0-a, n) < 0) and ends on the
   front (dot(v0-b, n) > 0), the crossing point is inside its edges (all three cross-product
   dots have a clear sign bit) and it is nearer than the best so far (the fraction starts at 1.0).
   The nearest one is written to the hit record at 0x1BAF80: the hit point at +32, the normal at
   +64, v0, v1 and v2 at +80, +96 and +112, 0 at +24 and the triangle's address at +28. Returns 1
   if there was one, else 0. */
int func_00278CE0(float *a, float *b, int count, int unused)
{
    float dir[3], best = 1.0f;
    float *tri = TRIANGLES, *end = TRIANGLES + count * 16, *found = 0;
    float hitp[3], hitn[3], hv0[3], hv1[3], hv2[3];
    int i;

    for (i = 0; i < 3; i++) {
        dir[i] = b[i] - a[i];
    }
    while (tri != end) {
        float *v0 = tri, *n = tri + 12;
        float e1[3], e2[3], da[3], db[3], pa[3], pb[3], pn[3], H[3], d10[3], d9[3], c7[3], c8[3], c9[3];
        float dot0, dot1, dd, t, s7, s8, s9, left;

        for (i = 0; i < 3; i++) {
            e1[i] = tri[4 + i] - v0[i];
            e2[i] = tri[8 + i] - v0[i];
            da[i] = v0[i] - a[i];
            db[i] = v0[i] - b[i];
        }
        for (i = 0; i < 3; i++) {
            pn[i] = dir[i] * n[i];
            pa[i] = da[i] * n[i];
            pb[i] = db[i] * n[i];
        }
        {
            float acc;

            acc = pn[0] + pn[1];
            dd = acc + pn[2];
            acc = pa[0] + pa[1];
            dot0 = acc + pa[2];
            acc = pb[0] + pb[1];
            dot1 = acc + pb[2];
        }
        tri += 16;
        t = div_00278CE0(dot0, dd);
        if (!neg_00278CE0(dot0)) {
            continue;
        }
        if (!pos_00278CE0(dot1)) {
            continue;
        }
        for (i = 0; i < 3; i++) {
            H[i] = (a[i] - v0[i]) + dir[i] * t;
        }
        for (i = 0; i < 3; i++) {
            d9[i] = e2[i] - e1[i];
            d10[i] = H[i] - e1[i];
        }
        cross_00278CE0(c7, H, e1);
        cross_00278CE0(c8, e2, H);
        cross_00278CE0(c9, d10, d9);
        for (i = 0; i < 3; i++) {
            c7[i] = c7[i] * n[i];
            c8[i] = c8[i] * n[i];
            c9[i] = c9[i] * n[i];
        }
        left = best - t;
        {
            float acc;

            acc = c7[0] + c7[1];
            s7 = acc + c7[2];
            acc = c8[0] + c8[1];
            s8 = acc + c8[2];
            acc = c9[0] + c9[1];
            s9 = acc + c9[2];
        }
        if (neg_00278CE0(s7) || neg_00278CE0(s8) || neg_00278CE0(s9)) {
            continue;
        }
        if (!pos_00278CE0(left)) {
            continue;
        }
        best = 0.0f + t;
        for (i = 0; i < 3; i++) {
            hitp[i] = H[i] + v0[i];
            hitn[i] = n[i] + 0.0f;
            hv0[i] = 0.0f + v0[i];
            hv1[i] = e1[i] + v0[i];
            hv2[i] = e2[i] + v0[i];
        }
        found = v0;
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        HIT[8 + i] = hitp[i];
        HIT[16 + i] = hitn[i];
        HIT[20 + i] = hv0[i];
        HIT[24 + i] = hv1[i];
        HIT[28 + i] = hv2[i];
    }
    *(int *)(HIT + 6) = 0;
    *(float **)(HIT + 7) = found;
    return 1;
}
