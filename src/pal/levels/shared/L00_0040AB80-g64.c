/* func_PAL_L00_0040AB80, the PAL copy of func_L00_00406150: the same C, where the spark timers get
 * the 50 Hz scale, the spawn step and its reach are scaled by 1.2f, the spawn lifetime drops from 30
 * to 25 and the per-frame 1/60 becomes 1/50. Twin of func_PAL_L00_003CA9E0. Spill slots follow gcse's
 * expression-table order, which depends on the insn count at gcse and on i's pseudo number: the
 * locals' initialisers and the function-scope declarations of color, count, a and b are part of
 * that. The spawn copies use qcopy_nc: the call that follows reads the copied vector itself. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char b0, b1, b2, b3;
} Particle;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; Vec normal; char rest[0x30]; } Collision;
typedef struct { unsigned char pad[0x2290]; char *object; } PlayerView;
typedef struct { int c[5]; } Colors;

extern Colors D_L00_001B0EC8 NOT_SDA;

extern PlayerView D_00189E20;
extern char D_0018A0E0[];
extern Collision D_L00_001BF200;
extern float D_L00_001A8F20;
extern unsigned char *D_L00_001FEAC4[];
extern signed char D_L00_001B0EBF;

extern float D_L00_001B0E38 __attribute__((sda));
extern float D_L00_001B0E4C __attribute__((sda));
extern float D_L00_001B0E54 __attribute__((sda));
extern float D_L00_001B0E58 __attribute__((sda));
extern float D_L00_001B0E60 __attribute__((sda));
extern float D_L00_001B0E64 __attribute__((sda));
extern float D_L00_001B0E68 __attribute__((sda));
extern float D_L00_001B0E88 __attribute__((sda));
extern float D_L00_001B0E8C __attribute__((sda));
extern float D_L00_001B0E90 __attribute__((sda));
extern float D_L00_001B0E98 __attribute__((sda));
extern float D_L00_001B0E9C __attribute__((sda));
extern int D_L00_001B0E50 __attribute__((sda));
extern int D_L00_001B0EA0 __attribute__((sda));
extern int D_L00_001B0EA8 __attribute__((sda));
extern int D_L00_001B0EAC __attribute__((sda));
extern float D_L00_001B0EA4 __attribute__((sda));
extern float D_L00_001B0EB4 __attribute__((sda));
extern float D_L00_001B0EB8 __attribute__((sda));
extern float D_L00_001B0EC4 __attribute__((sda));

extern float D_L00_001B2C80;
extern float D_L00_001B2C84;
extern Vec D_L00_001B2C90[3];
extern Vec D_L00_001B2CC0[3];
extern int D_L00_001B2CF0[3];
extern float D_L00_001B2D00[3];
extern float D_L00_001B2D10[3];
extern float D_L00_001B2D20[3];
extern int D_L00_001B2D30[3];
extern int D_L00_001B2D3C;

extern Vec D_L00_00254A60[];
extern Vec D_L00_00254B20[];
extern Vec D_L00_00254BE0[];
extern Vec D_L00_00254CA0[][20];

extern void func_L00_00406040(char *);
extern void func_PAL_L00_0040BA28();
extern void ref_L00_00406150_00(void *, void *);
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

void func_PAL_L00_0040AB80(char *arg)
{
    float v0[4], v10[4], v20[4], v30[4], v40[4];
    char *disabled[128];
    float v250[4], v260[4];
    char *obj;
    char *def = 0;
    float dist, t = 0.0f, w, r, ang, f, len = 0.0f, scale;
    int n, tries, j = 0, k = 0, kk = 0, q = 0, sign = 0, seg = 0;
    Particle *p = 0;
    int color, count;
    float a, b;

    v20[3] = 1.0f;
    obj = *(char **)(arg + 0x68);
    *(int *)v20 = 0;
    func_L00_00406040(arg);
    D_L00_001B2C84 = func_002ABB18(D_L00_001B2C84 + D_L00_001B0E54);
    func_00282D30(v0, arg + 0xD0, -D_L00_001B2C80);
    if (*(char **)(obj + 0x10) != 0 && (def = func_002AB1F0(*(char **)(obj + 0x10))) != 0) {
        func_00282D30(v40, *(char **)(obj + 0x10) + 0xE0, *(float *)(def + 0x10));
        func_00282CC0(v30, *(char **)(obj + 0x10) + 0x10, v40);
    } else {
        float x = *(float *)(obj + 0x48), y = *(float *)(obj + 0x4C);
        func_002AF000(v30, D_L00_001B0E38, x, y);
        func_00282CC0(v30, v30, obj);
    }
    n = 0;
    dist = D_L00_001B0E38;
    tries = 0;
    if (*(char **)(obj + 0x10) == 0) {
        qcopy(v40, obj);
        while (func_002761F8(v40, v30, 0x14, D_00189E20.object, 0)) {
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
                func_00282CF0(v250, obj, &D_L00_001BF200.point);
                f = func_00282DB0(D_00189E20.object + 0xE0, v250);
                func_00282D30(v260, D_00189E20.object + 0xE0, f);
                func_00282CF0(v270, v250, v260);
                dist = func_00282DF0(v270);
            }
            break;
        }
        for (q = 0; q < n; q++) {
            *(int *)(disabled[q] + 0x98) = *(int *)(*(char **)(disabled[q] + 0x24) + 0x10);
        }
    } else {
        func_00282CF0(v40, obj, *(char **)(obj + 0x10) + 0x10);
        f = func_00282DB0(D_00189E20.object + 0xE0, v40);
        func_00282D30(v250, D_00189E20.object + 0xE0, f);
        func_00282CF0(v260, v40, v250);
        dist = func_00282DF0(v260);
    }
    D_L00_001B2C80 = dist * D_L00_001B0E4C;
    qcopy(&D_L00_00254A60[0], obj);
    qcopy(&D_L00_00254B20[0], obj);
    qcopy(&D_L00_00254BE0[0], obj);
    {
    int i;
    for (i = 1; i < 12; i++) {
        func_00300190(&D_L00_00254A60[i], &D_L00_00254A60[i]);
        func_00282CF0(v10, &D_L00_00254A60[i], &D_L00_00254A60[i - 1]);
        t = func_00283CE0(i) * D_L00_001B0E4C;
        w = t * -0.49999997f + 0.9f;
        if (D_L00_001B0E50 < i && *(char **)(obj + 0x10) != 0) {
            func_00282CF0(v40, *(char **)(obj + 0x10) + 0x10, &D_L00_00254A60[i]);
            func_00282F20(v40, v40, D_L00_001B2C80);
            func_00282D08(v0, v0, v40, 0.2f);
        }
        func_00282D08(v40, v10, v0, w);
        len = func_00282DF0(v40);
        if (len == 0.0f) {
            qcopy(&D_L00_00254A60[i], &D_L00_00254A60[i - 1]);
        } else {
            func_00282D30(v40, v40, D_L00_001B2C80 / len);
            func_00282CC0(&D_L00_00254A60[i], &D_L00_00254A60[i - 1], v40);
        }
        func_00282CF0(v250, &D_L00_00254A60[i], &D_L00_00254A60[i - 1]);
        func_00282DD8(v260, v250, D_0018A0E0);
        func_00282F20(v260, v260, D_L00_001B0E64 + (D_L00_001B0E68 - D_L00_001B0E64) * t);
        {
        float v270[4];
        float m[4][4];
        for (j = 0; j < 20; j++) {
            func_002ACEC0(v270, v260, v250, (float)j * D_L00_001B0E60);
            func_00282CC0(&D_L00_00254CA0[i][j], v270, &D_L00_00254A60[i]);
        }
        qcopy(m[3], &D_L00_00254A60[i]);
        func_00282F20(m[0], v250, 1.0f);
        func_00282F20(m[1], v260, 1.0f);
        func_00282DD8(m[2], m[1], m[0]);
        r = D_L00_001B0E88 + (D_L00_001B0E8C - D_L00_001B0E88) * t;
        ang = func_002ABB18(D_L00_001B2C84 + D_L00_001B0E58 * func_00283CE0(i));
        v20[1] = r * func_00283198(ang);
        v20[2] = r * func_00283180(ang);
        func_002830C0(&D_L00_00254B20[i], v20, m);
        v20[2] = -v20[2];
        func_002830C0(&D_L00_00254BE0[i], v20, m);
        }
    }
    }
    ref_L00_00406150_00(func_PAL_L00_0040BA28, arg);
    scale = func_002A7878(0.1f, 1.7f);
    sign = func_002A77E0(2);
    if (sign == 0) sign = sign - 1;
    if (func_002A77E0(2) == 0) {
        qcopy_nc(v40, &D_L00_00254B20[11]);
        p = func_002C2210(v40, 0x19, scale * 0.1f, scale, 0x7F103FFF, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        p = func_002C2210(v40, 0x19, scale * 0.07f, scale * 0.7f, 0x80808080, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
    }
    if (func_002A77E0(2) == 0) {
        qcopy_nc(v40, &D_L00_00254BE0[11]);
        p = func_002C2210(v40, 0x19, scale * 0.1f, scale, 0x80FF4F10, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        p = func_002C2210(v40, 0x19, scale * 0.07f, scale * 0.7f, 0x80808080, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
    }
    func_00282CF0(v250, &D_L00_00254A60[1], &D_L00_00254A60[0]);
    func_00282F20(v250, v250, D_L00_001B0E90 * 1.2f);
    if (func_002A77E0(2) == 0) {
        func_00282F20(v260, arg + 0xD0, D_L00_001B0E9C);
        func_00282CC0(v40, &D_L00_00254A60[0], v260);
        {
            Colors colors = D_L00_001B0EC8;
            float up[4], side[4];
        color = colors.c[func_002A77E0(5)];
        a = func_002A78D8(0.0f, D_L00_001B0E98);
        b = func_002A78D8(0.0f, D_L00_001B0E98);
        func_002ACEC0(up, v250, D_0018A0E0, b);
        func_00282DD8(side, v250, D_0018A0E0);
        func_002ACEC0(up, up, side, a);
        count = func_00283CF0(dist * 1.2f / (D_L00_001B0E90 * 1.2f));
        if (*(char **)(obj + 0x10) != 0) count *= 3;
        p = func_L00_0033C638(scale * 0.1f, scale, v40, count, color, 0, sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = D_L00_001FEAC4[0][6];
        p = func_L00_0033C638(scale * 0.07f, scale * 0.7f, v40, count, 0x7F7F7F7F, 1, -sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = D_L00_001FEAC4[0][6];
        }
    }
    if (func_00282948(&D_L00_001B2D3C)) {
        D_L00_001B2D3C = ((s32)(D_L00_001B0EA0) * 5 + 2) / 6;
        for (k = 0; k < 3; k++) {
            if (D_L00_001B2D30[k] == 0) {
                D_L00_001B2D30[k] = 1;
                D_L00_001B2CF0[k] = ((s32)(D_L00_001B0EA8) * 5 + 2) / 6;
                D_L00_001B2D10[k] = 0;
                D_L00_001B2D20[k] = D_L00_001B0EB8;
                D_L00_001B2D00[k] = func_00283CE0(D_L00_001B0EBF);
                qcopy(&D_L00_001B2C90[k], obj);
                func_00282CF0(v260, &D_L00_00254A60[1], &D_L00_00254A60[0]);
                func_00282F20(&D_L00_001B2CC0[k], v260, 1.0f);
                break;
            }
        }
    }
    {
    for (kk = 0; kk < 3; kk++) {
        if (D_L00_001B2D30[kk] != 0) {
            if (func_00282948(&D_L00_001B2CF0[kk]) != 0) {
                D_L00_001B2D30[kk] = 0;
            } else {
                float step, u, rem, inv;
                float v270[4];
                if (D_L00_001B2CF0[kk] < D_L00_001B0EAC) D_L00_001B2D00[kk] -= D_L00_001B0EC4;
                step = D_L00_001B0EA4 * 0.020000001f;
                D_L00_001B2D10[kk] += step;
                u = D_L00_001B2D10[kk] / D_L00_001B0E38;
                if (u > 1.0f) u = 1.0f;
                D_L00_001B2D20[kk] = D_L00_001B0EB8 + (D_L00_001B0EB4 - D_L00_001B0EB8) * u;
                if (D_L00_001B2D10[kk] >= D_L00_001B0E38) {
                    func_00282D30(v260, &D_L00_001B2CC0[kk], step);
                    func_00282CC0(&D_L00_001B2C90[kk], &D_L00_001B2C90[kk], v260);
                } else {
                    seg = func_00283CF0(D_L00_001B2D10[kk] / D_L00_001B2C80);
                    rem = D_L00_001B2D10[kk] - func_00283CE0(seg) * D_L00_001B2C80;
                    qcopy(&D_L00_001B2C90[kk], &D_L00_00254A60[seg]);
                    if (seg == 11) func_00282CF0(v260, &D_L00_00254A60[seg], &D_L00_00254A60[seg + -1]);
                    else func_00282CF0(v260, &D_L00_00254A60[seg + 1], &D_L00_00254A60[seg]);
                    inv = func_00282DF0(v260);
                    if (inv != 0.0f) {
                        inv = 1.0f / inv;
                        func_00282D30(v270, v260, rem * inv);
                        func_00282CC0(&D_L00_001B2C90[kk], &D_L00_001B2C90[kk], v270);
                        func_00282F20(v270, v260, inv);
                        func_00282D08(&D_L00_001B2CC0[kk], &D_L00_001B2CC0[kk], v270, 0.1f);
                        func_00282F20(&D_L00_001B2CC0[kk], &D_L00_001B2CC0[kk], 1.0f);
                    }
                }
            }
        }
    }
    }
}
