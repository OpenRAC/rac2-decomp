#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vector;
typedef struct {
    u8 pad[0x6C];
    s16 f6C;
    u8 pad6E[4];
    s16 f72;
} GameStatus;
typedef struct {
    u8 pad[0x140];
    float pos[4];
    u8 pad150[0x16C - 0x150];
    int f16C;
    u8 pad170[0x180 - 0x170];
    float f180;
    int f184;
    int f188;
} CameraObject;
typedef struct {
    u8 pad00[0x90];
    int f90;
    u8 pad94[0xD0 - 0x94];
    int fD0;
    u8 padD4[0x100 - 0xD4];
    void *f100;
    u8 pad104[0x110 - 0x104];
    float f110;
    float f114;
    float f118;
    float f11C;
    u8 pad120[0x1AC - 0x120];
    int f1AC;
    u8 pad1B0[0x16B0 - 0x1B0];
    float f16B0;
    float f16B4;
    float f16B8;
    int f16BC;
    u8 pad16C0[8];
    float f16C8;
    int f16CC;
} ShipState;
typedef struct {
    u8 pad00[0x10];
    float pos[4];
    u8 state;
    u8 pad21[15];
    u8 f30;
    u8 f31;
    u16 f32;
    u16 flags;
    u8 pad36[0x68 - 0x36];
    ShipState *vars;
    u8 pad6C[0xAA - 0x6C];
    s16 classId;
    u8 padAC[4];
    u8 fB0;
    u8 padB1[0xC0 - 0xB1];
    float mtx[12];
    float rot[4];
} ShipObject;
extern void func_L07_0040F8F8(void *);
extern void func_L07_0040FC50(void *);
extern void func_PAL_L07_004138B8(void *);
extern void func_PAL_L07_00415638(void *, int);
extern void func_PAL_L07_00413B40(void *);
extern void func_PAL_L07_00414BC0(void *);
extern void func_PAL_L07_00414008(void *);
extern void func_PAL_L07_00415868(void *);
extern void func_L07_004106B8(void *);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern int func_002B3868(void *);
extern float func_002AAA00(void *, void *, float, float, float, float, int);
extern void func_L02_002DCEA0(int, float);
extern void func_PAL_L00_00305110(int, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_002B6D28(void);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002AA140(float, float, float);
extern void func_00283098(void *, void *, void *);
extern float func_00282C48(float);
extern void func_002833F0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_002AA2E8(void *, float, float);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_00283B98(float, float);
extern void func_002AD6F0(void *, void *, void *, void *);
extern int D_L07_001B1740 __attribute__((sda));
extern int D_L07_001C9780 NOT_SDA;
extern int D_L07_001B19F8;
extern u8 D_0018C0E2 NOT_SDA;
extern u8 D_001A7BD0;
extern int D_001A79F0;
extern u8 D_0019B2E8[][16];
extern void *D_0018A15C[3] NOT_SDA;
extern float D_L07_001B1D20;
extern GameStatus D_001A63A8;
extern int D_L07_001B9330 NOT_SDA;
extern CameraObject D_L07_001B90C0;
extern float D_L07_001B9200[4];
extern float D_L07_001B1744 __attribute__((sda));
extern float D_L07_001B1748 __attribute__((sda));
extern float D_L07_001B174C __attribute__((sda));
extern float D_L07_001B1750 __attribute__((sda));
extern float D_L07_001B1758 __attribute__((sda));
extern float D_L07_001B175C __attribute__((sda));
extern float D_L07_001B1760[2] __attribute__((sda));
extern struct {
    s16 f0;
    s16 f2;
    int f4;
} D_L07_001B2024;

void func_PAL_L07_004130D0(ShipObject *o)
{
    Vector p, r, v, w, x, y;
    ShipState *s = o->vars;
    float t, z, k, m;
    int i;

    if (!s)
        return;

    switch (o->state) {
    case 0:
        o->flags |= 1;
        o->f31 = 0;
        func_L07_0040F8F8(o);
        s->f1AC = -1;
        if (s->f90 == -1) {
            if (o->classId == 0x11D9)
                func_002A7750(o, 3, -1);
            else
                func_002A7750(o, 4, -1);
        } else {
            o->f30 = 255;
            func_L07_0040FC50(o);
            func_PAL_L07_004138B8(o);
            func_002A7750(o, 2, -1);
        }
        break;
    case 2:
        if (D_L07_001B1740) {
            D_L07_001B1740 = 0;
            func_PAL_L07_00415638(s->f100, s->fD0);
        }
        if (D_L07_001C9780) {
            func_002A7750(o, 1, -1);
            s->f16CC = func_002E5CF8(2, 4, o);
            s->f16C8 = 6.0f;
        }
        break;
    case 1:
        D_0018C0E2 = 1;
        D_L07_001B19F8 = 1;
        func_PAL_L07_00413B40(o);
        func_PAL_L07_00414BC0(o);
        break;
    case 3:
        if (func_002B3868(o))
            func_002E5CF8(1, 0, o);
        func_PAL_L07_00414008(o);
        if (D_001A7BD0 || (D_0019B2E8[D_001A79F0][o->fB0] & 0x80)) {
            func_PAL_L07_00414008(o);
            o->flags |= 2;
            break;
        }
        if (D_0018A15C[0] == o) {
            if (s->f110 >= 0.5f)
                func_002E5CF8(1, 0, o);
            func_002AAA00(&s->f110, &s->f118, -1.0f, 0.0025132746f,
                          0.0025132746f, 0.12566373f, 0);
            if (s->f110 <= -1.0f) {
                func_L02_002DCEA0(1, 8.0f);
                if (D_L07_001B1D20 >= 1.0f) {
                    p.q = 0;
                    r.q = 0;
                    p.f[0] = 191.5800018310547f;
                    p.f[1] = 501.15f;
                    p.f[2] = 457.69000244140625f;
                    r.f[2] = 3.1415927f;
                    func_PAL_L00_00305110(1, 0);
                    func_PAL_L00_002B9CD8(&p, &r, 0, 1);
                }
            }
        } else {
            func_002AAA00(&s->f110, &s->f118, 0.5f, 0.0025132746f,
                          0.0025132746f, 0.12566373f, 0);
        }
        break;
    case 5:
        if (s->f16B8 >= 1.0f && D_L07_001B1D20 >= 1.0f) {
            if (D_001A63A8.f72 != 3 || D_001A63A8.f6C >= 6000)
                break;
            D_L07_001B9330 = 0;
            func_002B6D28();
        }
        p.q = *(TI128 *)o->pos;
        r.q = *(TI128 *)o->rot;
        if (s->f16B8 > 0.0f) {
            func_002AA548(o->pos, &s->f11C, 400.0f, 0.0f, D_L07_001B1748 * 0.00040000002f,
                          D_L07_001B1744 * 0.020000001f);
            s->f16B8 = (o->pos[0] - 400.0f) * 0.014285714f;
            o->rot[2] = func_002AA140(D_L07_001B1750, 0.0f, s->f16B8);
            o->rot[0] = func_002AA140(0.7853975296020508f, 0.0f, s->f16B8);
            o->pos[2] = 213.0f - s->f16B8 * 3.0f;
        } else if ((m = D_L07_001B1D20) == 0.0f) {
            func_00283098(&v, D_L07_001B1760, o->mtx);
            s->f16B4 += o->rot[0] * 0.00010471977f + 0.00010471977f;
            o->rot[0] += s->f16B4;
            if (o->rot[0] > 1.5707964f) {
                o->rot[0] = 1.5707964f;
                t = func_00282C48(s->f16B4);
                if (t < 0.0006981318f)
                    func_L02_002DCEA0(1, 12.0f);
                else
                    s->f16B4 *= -0.333f;
                if (!s->f16BC) {
                    D_L07_001B90C0.f16C = 0;
                    D_L07_001B90C0.f188 = 75;
                    D_L07_001B90C0.f180 = 0.02f;
                    s->f16BC = 1;
                }
            }
            func_002833F0(o->mtx, o->rot);
            func_00283098(&w, D_L07_001B1760, o->mtx);
            func_00282CF0(&v, &w, &v);
            func_00282CF0(o->pos, o->pos, &v);
        } else if (m >= 1.0f) {
            func_PAL_L07_00415868(o);
            break;
        }

        D_L07_001B2024.f4 = 1;
        func_002AA2E8(&s->f16B0, 1.0f, D_L07_001B174C * 0.00040000002f);
        k = s->f11C + s->f16B0;
        if (k > 0.0f)
            k = 0.0f;
        v.q = *(TI128 *)D_L07_001B9200;
        v.f[0] += k;
        v.f[2] += D_L07_001B175C * 0.020000001f;
        func_00335370(&v);

        qzero_nc(&w);
        x.q = *(TI128 *)o->pos;
        x.f[2] += 6.0f;
        w.f[2] = func_00283248(o->pos[0] - D_L07_001B90C0.pos[0], o->pos[1] - D_L07_001B90C0.pos[1]);
        w.f[1] = func_00283248(func_00282E80(&x, D_L07_001B90C0.pos), D_L07_001B90C0.pos[2] - x.f[2]);
        w.f[0] = D_L07_001B1758 * 0.017453294f;
        func_003353C8(&w);

        func_L07_004106B8(o);

        z = s->f16B8 * 0.052359886f + 0.010471977f;
        for (i = 0; i < 8; i++)
            *(float *)((u8 *)s + 0x15B4 + i * 0x20) = func_00283B98(*(float *)((u8 *)s + 0x15B4 + i * 0x20), z);

        func_00282CF0(&y, o->pos, &p);
        func_002AD6F0((u8 *)s + 0x20, &y, &r, o->rot);
        break;
    }
}
