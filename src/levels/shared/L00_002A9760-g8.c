/* Steers the hero probe direction and samples vertical bounds with four rays. */
#include "common.h"
typedef struct {
    unsigned char pad0[0xC];
    float scale;
    float position[4];
    unsigned char pad20[0x14];
    unsigned short flags;
    unsigned char pad36[0x3A];
    float center, radius;
    unsigned char pad78[0x45];
    unsigned char opacity;
    unsigned char padbe[0x22];
    float up[4];
} HeroMoby;

typedef struct {
    unsigned char pad0[0x318];
    float f318;
    unsigned char pad31c[0x14];
    float f330;
    float f334;
    unsigned char pad338[0x16];
    short f34e;
    unsigned char pad350[0xB60];
    float feb0;
    unsigned char padeb4[0x13DC];
    HeroMoby *f2290;
    int f2294;
    unsigned char pad2298[0x4];
    int f229c;
    unsigned char pad22a0[0x14];
    unsigned char f22b4;
} HeroHeightProbeState;
extern HeroHeightProbeState D_00189E20_2;

extern int D_L00_001A8FF0 __attribute__((sda));
extern float D_L00_001A7F48[] SDATA(D_L00_001A7F48);
extern float D_L00_001A7F58[] SDATA(D_L00_001A7F58);
extern char D_L00_001BF220[];
typedef struct { char pad[0x28]; float height; } HitResult;
extern HitResult D_L00_001BF200;
extern char D_L00_001B1EE0[];
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern void func_002A04E8(void *, void *);
extern float func_00283248(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern float func_00282C50(float, float);
extern float func_L00_002EE050(float, float);
/* The bounds also have raw-word clear operations in the retail code. */
#define P D_00189E20_2.f2290
#define O(t, o) (*(t *)((char *)P + (o)))

void func_L00_002A9760(void)
{
    float a[4], b[4], c[4];
    float angle, cs, sn, height;
    int i, near;

    if (D_00189E20_2.f229c == 18 || D_00189E20_2.f229c == 21 ||
        D_00189E20_2.f2294 == 122 || D_00189E20_2.f229c == 22 ||
        D_00189E20_2.f229c == 31) {
        if (D_00189E20_2.f229c == 18)
            D_00189E20_2.feb0 = 1.56f;
        P->flags &= 0xfbff;
        return;
    }
    if (D_00189E20_2.f22b4 == 4)
        return;
    P->flags |= 0x400;
    if (D_L00_001A8FF0 || (O(float, 0xe8) < 0.99f && D_00189E20_2.f229c != 17)) {
        P->opacity = 255;
        FastVecScale(a, P, 0.0009765625f);
        FastVecScale(b, P->up, -16.0f);
        FastVecAdd(b, a, b);
        if (CollLine(a, b, 34, 0, 0)) {
            FastVecSub(c, D_L00_001BF220, P->position);
            O(float, 0x70) = FastVecDot(c, P->up);
            O(float, 0x74) = O(float, 0xc) * 0.000244140625f;
        } else {
            O(int, 0x70) = 0;
            O(int, 0x74) = 0;
        }
        D_00189E20_2.feb0 = 1.56f;
        return;
    }

    P->opacity = 1;
    {
        float delta, target = 0.97f;
        if (D_00189E20_2.f34e || D_00189E20_2.f229c == 4)
            target = 1.56f;
        delta = fast_subtract_rotations(target, D_00189E20_2.feb0);
        if (delta > 0.052f)
            delta = 0.052f;
        else if (delta < -0.052f)
            delta = -0.052f;
        D_00189E20_2.feb0 = FastAddRotations(D_00189E20_2.feb0, delta);
    }
    func_002A04E8(P, a);
    angle = func_00283248(a[0], a[1]);
    cs = func_00283180(angle);
    sn = func_00283198(angle);
    {
        float cosine = func_00283180(D_00189E20_2.feb0);
        a[0] = cs * cosine;
        a[1] = sn * cosine;
    }
    a[2] = -func_00283198(D_00189E20_2.feb0);
    qcopy(D_L00_001B1EE0, a);
    height = D_00189E20_2.f318;
    if (height < 1.0f) {
        if (D_00189E20_2.f330 >= 1.0f)
            height = D_00189E20_2.f330;
        else {
            if (D_00189E20_2.f334 > 1.0f)
                height = D_00189E20_2.f334;
            else {
                O(int, 0x70) = 0;
                O(int, 0x74) = 0;
                return;
            }
        }
    }
    near = 0;
    if (func_00282C48(D_00189E20_2.feb0 - 1.56f) < 0.1f)
        near = 1;
    if (!near) {
        float hi = height, lo = height;
        float *probeStart = b, *probeEnd = c;
        float *offset = D_L00_001A7F48, *turn = D_L00_001A7F58;

        for (i = 3; i >= 0; offset++, i--, turn++) {
            float scale, t, step, cosine, distance;
            scale = O(float, 0xc) * 0.0009765625f;
            FastVecScale(probeStart, P, 0.0009765625f);
            t = FastAddRotations(angle, *turn);
            cosine = func_00283180(t);
            step = scale * 0.35f;
            b[0] += cosine * step;
            b[1] += func_00283198(t) * step;
            b[2] += *offset * scale;
            distance = ((b[2] - height + 0.5f) * 2.0f) / -a[2];
            vec_scale_to_length(probeEnd, a, distance);
            FastVecAdd(probeEnd, probeStart, probeEnd);
            if (CollLine(probeStart, probeEnd, 34, 0, 0)) {
                lo = func_00282C50(lo, D_L00_001BF200.height);
                hi = func_L00_002EE050(hi, D_L00_001BF200.height);
            }
        }
        O(float, 0x70) = (lo + hi) * 0.5f - O(float, 0x18);
        O(float, 0x74) = (hi - lo) * 0.5f + 0.12f;
        {
            float radius = O(float, 0x74);
            if (radius > 1.0f) {
                O(float, 0x74) = 1.0f;
                O(float, 0x70) += (radius - 1.0f) * 0.5f;
            }
        }
    } else {
        O(float, 0x70) = height - O(float, 0x18);
        O(float, 0x74) = 0.18f;
    }
}
