/* Lightning-arc effect update: 12 segments of 20 points and three travelling sparks.
 * Twin of func_L00_00406150 (same instructions, its own data).
 * Spill slots follow gcse's expression-table order, which depends on the insn count
 * at gcse; the locals' initialisers are part of that. The spawn copies use qcopy_nc:
 * the call that follows reads the copied vector itself. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char b0, b1, b2, b3;
} Particle;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; Vec normal; char rest[0x30]; } Collision;
typedef struct { unsigned char pad[0x2290]; char *object; } PlayerView;
typedef struct { int c[5]; } Colors;

extern Colors D_L00_001B0048 NOT_SDA;

extern PlayerView D_00189E20;
extern char D_0018A0E0[];
extern Collision D_L00_001BF200;
extern float D_L00_001A8F20;
extern unsigned char *D_L00_001FEAC4[];
extern signed char D_L00_001B003F;

extern float D_L00_001AFFA4 __attribute__((sda));
extern float D_L00_001AFFCC __attribute__((sda));
extern float D_L00_001AFFD4 __attribute__((sda));
extern float D_L00_001AFFD8 __attribute__((sda));
extern float D_L00_001AFFE0 __attribute__((sda));
extern float D_L00_001AFFE4 __attribute__((sda));
extern float D_L00_001AFFE8 __attribute__((sda));
extern float D_L00_001B0008 __attribute__((sda));
extern float D_L00_001B000C __attribute__((sda));
extern float D_L00_001B0010 __attribute__((sda));
extern float D_L00_001B0018 __attribute__((sda));
extern float D_L00_001B001C __attribute__((sda));
extern int D_L00_001AFFD0 __attribute__((sda));
extern int D_L00_001B0020 __attribute__((sda));
extern int D_L00_001B0028 __attribute__((sda));
extern int D_L00_001B002C __attribute__((sda));
extern float D_L00_001B0024 __attribute__((sda));
extern float D_L00_001B0034 __attribute__((sda));
extern float D_L00_001B0038 __attribute__((sda));
extern float D_L00_001B0044 __attribute__((sda));

extern float D_L00_001B2A10;
extern float D_L00_001B2A14;
extern Vec D_L00_001B2A20[3];
extern Vec D_L00_001B2A50[3];
extern int D_L00_001B2A80[3];
extern float D_L00_001B2A90[3];
extern float D_L00_001B2AA0[3];
extern float D_L00_001B2AB0[3];
extern int D_L00_001B2AC0[3];
extern int D_L00_001B2ACC;

extern Vec D_L00_002403C0[];
extern Vec D_L00_00240480[];
extern Vec D_L00_00240540[];
extern Vec D_L00_00240600[][20];

extern void func_L00_003C6A88(char *);
extern void func_L00_003C79F8();
extern void ref_L00_003C6B98_00(void *, void *);
extern Particle *func_002C2210(void *, int, float, float, int, int, int, void *, float, int);
extern Particle *func_L00_0033C638(float, float, void *, int, int, int, int, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern float func_00282DF0(void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern float func_002ABB18(float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern void func_002830C0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_00282948(void *);
extern void func_00300190(void *, void *);
extern void func_002AF000(void *, float, float, float);
extern char *func_002AB1F0(char *);
extern float func_002A7878(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern int func_002761F8(void *, void *, int, void *, void *);

void func_L00_003C6B98(char *arg)
{
    float v0[4], v10[4], v20[4], v30[4], v40[4];
    char *disabled[128];
    float v250[4], v260[4];
    char *obj;
    char *def = 0;
    float dist, t = 0.0f, w, r, ang, f, len = 0.0f, scale;
    int n, tries, j = 0, k = 0, kk = 0, q = 0, sign = 0, seg = 0;
    Particle *p = 0;

    v20[3] = 1.0f;
    obj = *(char **)(arg + 0x68);
    *(int *)v20 = 0;
    ResetBeamChainAndPulseState(arg);
    D_L00_001B2A14 = func_002ABB18(D_L00_001B2A14 + D_L00_001AFFD4);
    vec_scale_to_length(v0, arg + 0xD0, -D_L00_001B2A10);
    if (*(char **)(obj + 0x10) != 0 && (def = func_002AB1F0(*(char **)(obj + 0x10))) != 0) {
        FastVecScale(v40, *(char **)(obj + 0x10) + 0xE0, *(float *)(def + 0x10));
        FastVecAdd(v30, *(char **)(obj + 0x10) + 0x10, v40);
    } else {
        float x = *(float *)(obj + 0x48), y = *(float *)(obj + 0x4C);
        func_002AF000(v30, D_L00_001AFFA4, x, y);
        FastVecAdd(v30, v30, obj);
    }
    n = 0;
    dist = D_L00_001AFFA4;
    tries = 0;
    if (*(char **)(obj + 0x10) == 0) {
        qcopy(v40, obj);
        while (CollLine(v40, v30, 0x14, D_00189E20.object, 0)) {
            Collision *col;
            char *hit;
            if (++tries >= 7) break;
            col = &D_L00_001BF200;
            if (D_L00_001BF200.hit != 0 && (*(short *)(D_L00_001BF200.hit + 0xAA) == 0xE7D || *(short *)(D_L00_001BF200.hit + 0xAA) == 0xEB0)) {
                disabled[n++] = D_L00_001BF200.hit;
                *(int *)(D_L00_001BF200.hit + 0x98) = 0;
                if (n < 128) {
                    qcopy(v40, &D_L00_001BF200.point);
                    continue;
                }
            }
            {
                float v270[4];
                FastVecSub(v250, obj, &D_L00_001BF200.point);
                f = FastVecDot(D_00189E20.object + 0xE0, v250);
                FastVecScale(v260, D_00189E20.object + 0xE0, f);
                FastVecSub(v270, v250, v260);
                dist = FastVecLength(v270);
            }
            break;
        }
        for (q = 0; q < n; q++) {
            *(int *)(disabled[q] + 0x98) = *(int *)(*(char **)(disabled[q] + 0x24) + 0x10);
        }
    } else {
        FastVecSub(v40, obj, *(char **)(obj + 0x10) + 0x10);
        f = FastVecDot(D_00189E20.object + 0xE0, v40);
        FastVecScale(v250, D_00189E20.object + 0xE0, f);
        FastVecSub(v260, v40, v250);
        dist = FastVecLength(v260);
    }
    D_L00_001B2A10 = dist * D_L00_001AFFCC;
    qcopy(&D_L00_002403C0[0], obj);
    qcopy(&D_L00_00240480[0], obj);
    qcopy(&D_L00_00240540[0], obj);
    {
    int i;
    for (i = 1; i < 12; i++) {
        func_00300190(&D_L00_002403C0[i], &D_L00_002403C0[i]);
        FastVecSub(v10, &D_L00_002403C0[i], &D_L00_002403C0[i - 1]);
        t = IntToFloat(i) * D_L00_001AFFCC;
        w = t * -0.49999997f + 0.9f;
        if (D_L00_001AFFD0 < i && *(char **)(obj + 0x10) != 0) {
            FastVecSub(v40, *(char **)(obj + 0x10) + 0x10, &D_L00_002403C0[i]);
            vec_scale_to_length(v40, v40, D_L00_001B2A10);
            lerp_vector(v0, v0, v40, 0.2f);
        }
        lerp_vector(v40, v10, v0, w);
        len = FastVecLength(v40);
        if (len == 0.0f) {
            qcopy(&D_L00_002403C0[i], &D_L00_002403C0[i - 1]);
        } else {
            FastVecScale(v40, v40, D_L00_001B2A10 / len);
            FastVecAdd(&D_L00_002403C0[i], &D_L00_002403C0[i - 1], v40);
        }
        FastVecSub(v250, &D_L00_002403C0[i], &D_L00_002403C0[i - 1]);
        FastVecCross(v260, v250, D_0018A0E0);
        vec_scale_to_length(v260, v260, D_L00_001AFFE4 + (D_L00_001AFFE8 - D_L00_001AFFE4) * t);
        {
        float v270[4];
        float m[4][4];
        for (j = 0; j < 20; j++) {
            func_002ACEC0(v270, v260, v250, (float)j * D_L00_001AFFE0);
            FastVecAdd(&D_L00_00240600[i][j], v270, &D_L00_002403C0[i]);
        }
        qcopy(m[3], &D_L00_002403C0[i]);
        vec_scale_to_length(m[0], v250, 1.0f);
        vec_scale_to_length(m[1], v260, 1.0f);
        FastVecCross(m[2], m[1], m[0]);
        r = D_L00_001B0008 + (D_L00_001B000C - D_L00_001B0008) * t;
        ang = func_002ABB18(D_L00_001B2A14 + D_L00_001AFFD8 * IntToFloat(i));
        v20[1] = r * func_00283198(ang);
        v20[2] = r * func_00283180(ang);
        transform_vector(&D_L00_00240480[i], v20, m);
        v20[2] = -v20[2];
        transform_vector(&D_L00_00240540[i], v20, m);
        }
    }
    }
    ref_L00_003C6B98_00(DrawBeamRingAndRailEffects, arg);
    scale = func_002A7878(0.1f, 1.7f);
    sign = func_002A77E0(2);
    if (sign == 0) sign = sign - 1;
    if (func_002A77E0(2) == 0) {
        qcopy_nc(v40, &D_L00_00240480[11]);
        p = func_002C2210(v40, 0x1E, scale * 0.1f, scale, 0x7F10107F, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        p = func_002C2210(v40, 0x1E, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
    }
    if (func_002A77E0(2) == 0) {
        qcopy_nc(v40, &D_L00_00240540[11]);
        p = func_002C2210(v40, 0x1E, scale * 0.1f, scale, 0x7F104FFF, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        p = func_002C2210(v40, 0x1E, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
    }
    FastVecSub(v250, &D_L00_002403C0[1], &D_L00_002403C0[0]);
    vec_scale_to_length(v250, v250, D_L00_001B0010);
    if (func_002A77E0(2) == 0) {
        vec_scale_to_length(v260, arg + 0xD0, D_L00_001B001C);
        FastVecAdd(v40, &D_L00_002403C0[0], v260);
        {
            Colors colors = D_L00_001B0048;
            float up[4], side[4];
            int color, count;
            float a, b;
        color = colors.c[func_002A77E0(5)];
        a = func_002A78D8(0.0f, D_L00_001B0018);
        b = func_002A78D8(0.0f, D_L00_001B0018);
        func_002ACEC0(up, v250, D_0018A0E0, b);
        FastVecCross(side, v250, D_0018A0E0);
        func_002ACEC0(up, up, side, a);
        count = FloatToInt(dist * 1.2f / D_L00_001B0010);
        if (*(char **)(obj + 0x10) != 0) count *= 3;
        p = func_L00_0033C638(scale * 0.1f, scale, v40, count, color, 0, sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = D_L00_001FEAC4[0][6];
        p = func_L00_0033C638(scale * 0.07f, scale * 0.7f, v40, count, 0x7F7F7F7F, 1, -sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = D_L00_001FEAC4[0][6];
        }
    }
    if (func_00282948(&D_L00_001B2ACC)) {
        D_L00_001B2ACC = D_L00_001B0020;
        for (k = 0; k < 3; k++) {
            if (D_L00_001B2AC0[k] == 0) {
                D_L00_001B2AC0[k] = 1;
                D_L00_001B2A80[k] = D_L00_001B0028;
                D_L00_001B2AA0[k] = 0;
                D_L00_001B2AB0[k] = D_L00_001B0038;
                D_L00_001B2A90[k] = IntToFloat(D_L00_001B003F);
                qcopy(&D_L00_001B2A20[k], obj);
                FastVecSub(v260, &D_L00_002403C0[1], &D_L00_002403C0[0]);
                vec_scale_to_length(&D_L00_001B2A50[k], v260, 1.0f);
                break;
            }
        }
    }
    {
    for (kk = 0; kk < 3; kk++) {
        if (D_L00_001B2AC0[kk] != 0) {
            if (func_00282948(&D_L00_001B2A80[kk]) != 0) {
                D_L00_001B2AC0[kk] = 0;
            } else {
                float step, u, rem, inv;
                float v270[4];
                if (D_L00_001B2A80[kk] < D_L00_001B002C) D_L00_001B2A90[kk] -= D_L00_001B0044;
                step = D_L00_001B0024 * 0.016666668f;
                D_L00_001B2AA0[kk] += step;
                u = D_L00_001B2AA0[kk] / D_L00_001AFFA4;
                if (u > 1.0f) u = 1.0f;
                D_L00_001B2AB0[kk] = D_L00_001B0038 + (D_L00_001B0034 - D_L00_001B0038) * u;
                if (D_L00_001B2AA0[kk] >= D_L00_001AFFA4) {
                    FastVecScale(v260, &D_L00_001B2A50[kk], step);
                    FastVecAdd(&D_L00_001B2A20[kk], &D_L00_001B2A20[kk], v260);
                } else {
                    seg = FloatToInt(D_L00_001B2AA0[kk] / D_L00_001B2A10);
                    rem = D_L00_001B2AA0[kk] - IntToFloat(seg) * D_L00_001B2A10;
                    qcopy(&D_L00_001B2A20[kk], &D_L00_002403C0[seg]);
                    if (seg == 11) FastVecSub(v260, &D_L00_002403C0[seg], &D_L00_002403C0[seg + -1]);
                    else FastVecSub(v260, &D_L00_002403C0[seg + 1], &D_L00_002403C0[seg]);
                    inv = FastVecLength(v260);
                    if (inv != 0.0f) {
                        inv = 1.0f / inv;
                        FastVecScale(v270, v260, rem * inv);
                        FastVecAdd(&D_L00_001B2A20[kk], &D_L00_001B2A20[kk], v270);
                        vec_scale_to_length(v270, v260, inv);
                        lerp_vector(&D_L00_001B2A50[kk], &D_L00_001B2A50[kk], v270, 0.1f);
                        vec_scale_to_length(&D_L00_001B2A50[kk], &D_L00_001B2A50[kk], 1.0f);
                    }
                }
            }
        }
    }
    }
}
