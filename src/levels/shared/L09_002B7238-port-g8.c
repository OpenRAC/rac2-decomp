#include "common.h"

/* Adapted from public OpenRAC/rac1-decomp hero_collision.c (GPL-3.0),
 * with the measured Going Commando fields and additional gravity probes. */
typedef int Q __attribute__((mode(TI)));
typedef union { float F; int I; } U32;
typedef union { short H; unsigned short U; } U16;
typedef union { float f[2]; int i[2]; } PAIR;
typedef union { float f[4]; int i[4]; } Vec4;
typedef struct {
    u8 pad0[136];
    float xF88;
    u8 pad8c[472];
    float xF234;
    u8 pad268[56];
    int xI270;
    int xI274;
    float xF278;
    u8 pad2ac[28];
    float xF298;
    u8 pad2cc[52];
    PAIR a2c0;
    PAIR a2c8;
    PAIR a2d0;
    U32 u2d8;
    float xF2dc;
    U32 u2e0;
    U32 u2e4;
    U32 u2e8;
    float xF2ec;
    float xF2f0;
    float xF2f4;
    int xI2f8;
    int xI2fc;
    int xI300;
    u8 pad344[6];
    short xH30a;
    U16 u30c;
    U16 u30e;
    u8 pad350[2240];
    int xIa80;
    u8 padc14[2172];
    short xH12e0;
    u8 pad1492[11];
    u8 xB12ed;
    u8 pad149e[1058];
    int field18c0;
    u8 pad18c4[2508];
    int xI2080;
    int xI2084;
    u8 pad2298[4];
    int xI208c;
    u8 pad22a0[35];
    u8 xB20b3;
} HeroGround;
extern HeroGround D_00189E20;
typedef struct { u8 pad[24]; int i18, i1C; Vec4 v20; u8 pad30[16]; float f40, f44; } Hit;
extern Hit D_L09_001BFE40;
extern char D_L09_001BFE60[];
extern int D_001A79F0;
extern int D_001A8FF0 MACRO_ADDR;
extern int D_001A8FF4;
extern int func_L00_002ADF80(void);
extern void func_00282C88(void *);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern int func_002761F8(void *, void *, int, int, int);
extern int func_L00_002E2048(void), func_00278E78(void);
extern float func_002A90F8(void *, void *);
extern int func_002ABB78(int);
extern u8 *func_002AB1F0(int);
extern u8 *func_002AD0B0(int);
extern float func_002B0360(void *);
extern void func_002AFF60(void *, void *, int);
extern void func_002AA2E8(float *, float, float);
extern float func_00282E48(void *, void *);
extern void func_001290E0(void *, void *);
extern float func_L00_002D3EA8(void *), func_00283248(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float), func_00282F20(void *, void *, float);
extern void func_L00_002B8E48(void *, void *);
/* The EE integer and FP argument banks retain their original order. */
extern void func_L00_002D3638(void *, float, float, float, int);
extern float func_00282C48(float);

void func_L09_002B7238(void) {
    Vec4 v0, v10, v20, v30, v40, v50, v60;
    s32 r;
    s32 i;
    f32 a;
    u8 *p;
    Vec4 *normal;
    HeroGround *hero;

    s32 k;
    f32 g;
    HeroGround *body;

    D_00189E20.xF278 = 1.0f;
    D_00189E20.u30e.U++;
    D_00189E20.u30c.U++;
    D_00189E20.xI270 = 0;
    D_00189E20.xI274 = 0;
    D_00189E20.u2e0.I = 0;
    D_00189E20.u2d8.I = 0;
    func_00282C88((u8 *)&D_00189E20 + 0x2D0);
    D_00189E20.xH30a = 0;
    D_00189E20.xF2dc = 32.0f;
    D_00189E20.xI2fc = 0;
    if (D_00189E20.xI2f8 != 0) {
        D_00189E20.xI2f8++;
    }
    k = 1;
    g = D_00189E20.xF234 * 2.2f;
    if (D_00189E20.xI208c == 2) {
        g = D_00189E20.xF234 * 2.9f;
    }
    if (func_L00_002ADF80()) g = 0.0f;
    func_L00_002B47A8(&v10, &v0, k, g, -48.0f);
    if (func_002761F8(&v10, &v0, 2, D_00189E20.xI2080, 0) == 0) {
        goto tail;
    }
    r = func_L00_002E2048();

    D_00189E20.xB12ed = r;
    if (D_L09_001BFE40.i18 != 0) D_00189E20.xB12ed = 0;
    if (D_001A79F0 == 7 && D_L09_001BFE40.i18 != 0) D_00189E20.xB12ed = 1;
    D_00189E20.xH12e0 = func_00278E78();
    if (D_00189E20.xH12e0 == 0) {
        D_00189E20.xF2f0 = func_002A90F8(D_L09_001BFE60, (u8 *)&D_00189E20 + 0x2B0);
        if (D_00189E20.xF88 < D_00189E20.xF2f0 && D_00189E20.xI2f8 <= 0) {
            D_00189E20.xI2f8 = 1;
        }
        if (func_002761F8(&v10, &v0, 0x24, D_00189E20.xI2080, 0) == 0) {
            goto tail;
        }
        r = func_L00_002E2048();
        D_00189E20.xB12ed = r;
    }
    if (D_00189E20.xH12e0 == 3) {
        D_00189E20.xF2f4 = D_L09_001BFE40.v20.f[2];
        v10.f[2] = D_L09_001BFE40.v20.f[2] - 0.01f;
        if (func_002761F8(&v10, &v0, 4, D_00189E20.xI2080, 0) == 0) {
            goto tail;
        }
    }
    if (D_00189E20.xH12e0 == 11) {
        D_00189E20.xF2f4 = D_L09_001BFE40.v20.f[2];
        goto tail;
    }
    if (D_00189E20.xH12e0 == 1 && (u32)(D_00189E20.xI2084 - 0x79) < 2) {
        goto tail;
    }
    if (D_L09_001BFE40.i18 != 0) {
        if (func_002ABB78(D_L09_001BFE40.i18)) {
            D_00189E20.xH30a = 1;
        }
        p = func_002AB1F0(D_L09_001BFE40.i18);
        if (p != 0 && (*(u16 *)(p + 0x1E) & 8)) {
            D_00189E20.xH30a = 1;
        }
        p = func_002AD0B0(D_L09_001BFE40.i18);
        if (p != 0 && (*(int *)(p + 0x3c) & 8)) D_00189E20.xH30a = 1;
    }
    if (D_L09_001BFE40.i1C > 0) {
        qcopy((u8 *)&D_00189E20 + 0x2D0, &D_L09_001BFE40.v20);
        D_00189E20.u2d8.F = D_L09_001BFE40.v20.f[2];
        if (D_001A8FF0) D_00189E20.u2d8.F = func_002B0360(&D_L09_001BFE40.v20);
        D_00189E20.xF2dc = func_00282E48((u8 *)&D_00189E20 + 0x80, ((u8 *)&D_00189E20 + 0x2D0));
        D_00189E20.xI2fc = D_L09_001BFE40.i18;
        func_001290E0((u8 *)&D_00189E20 + 0x2A0, (u8 *)&D_L09_001BFE40.f40);
        D_00189E20.u2e0.F = func_L00_002D3EA8((u8 *)&D_L09_001BFE40.f40);
        D_00189E20.xF2ec = func_00283248(D_L09_001BFE40.f40, D_L09_001BFE40.f44);
        func_00282CF0(&v20, ((u8 *)&D_00189E20 + 0x2D0), (u8 *)&D_00189E20 + 0x80);
        if (0.0f < func_00282DB0(&v20, (u8 *)&D_00189E20 + 0x2A0)) {
            D_00189E20.xF2dc = -D_00189E20.xF2dc;
        }
        if (D_00189E20.xF2dc < 0.02f) {
            D_00189E20.u30c.H = 0;
            if (D_00189E20.u2e0.F <= 0.87266469f || D_00189E20.xB20b3 != 0) {
                D_00189E20.u30e.H = 0;
                D_00189E20.xIa80 = D_L09_001BFE40.i18;
            }
        }
    }
tail:
    body = &D_00189E20;
    if (body->xF88 > body->xF2f0) body->xI2f8 = 0;
    if (body->u30e.H != 0) body->xI300 = 0;
    else {
        body->xI300++;
        qcopy((u8 *)body + 0x2E0, (u8 *)body + 0x2D0);
        if (body->xI2084 != 0x38) body->field18c0 = 0;
    }
    normal = (Vec4 *)((u8 *)&D_00189E20 + 0x2C0);
    func_00282C88(normal);
    hero = (HeroGround *)((u8 *)normal - 0x2C0);
    switch (hero->xB20b3) {
    case 0:
        hero->xF298 = -1.0f;
        break;
    case 1:
        if (D_001A8FF4) func_002AFF60((u8 *)normal - 0x240, normal, 0);
        else if (*(float *)((u8 *)hero + 0x2fc) != 0.0f) {
            func_002AA2E8((float *)((u8 *)normal + 0x3c), 0.0f, 1.0f);
            qcopy(normal, (u8 *)normal + 0x30);
        } else {
            qcopy(normal, (u8 *)normal - 0x20);
            func_00282D30(normal, normal, -1.0f);
        }
        break;
    case 2:
        a = -1.0f;
        if (*(float *)((u8 *)hero + 0xbc) > 0.0f) a = 1.0f;
        func_00282CF0(normal, (u8 *)normal - 0x210, (u8 *)normal - 0x240);
        func_00282F20(normal, normal, a);
        break;
    }
    D_00189E20.u2e4.I = 0;
    D_00189E20.u2e8.I = 0;
    D_00189E20.a2d0.i[0] = 0;
    D_00189E20.a2d0.i[1] = 0;
    D_00189E20.a2c8.i[0] = 0;
    D_00189E20.a2c8.i[1] = 0;
    D_00189E20.a2c0.i[0] = 0;
    D_00189E20.a2c0.i[1] = 0;
    if (!(D_00189E20.xF2dc < 0.25f)) {
        return;
    }
    if (!(D_00189E20.xI208c == 0 || D_00189E20.xI208c == 12 || D_00189E20.xI208c == 9 || D_00189E20.xI208c == 7 || (D_00189E20.xI208c == 4 && *(u8 *)((u8 *)&D_00189E20 + 0x49c)) || D_00189E20.xI208c == 1)) {
        return;
    }
    func_L00_002B8E48((u8 *)&D_00189E20 + 0x2A0, &v20);
    if (-0.785398244f < v20.f[1] && v20.f[1] < 0.785398244f) {
        D_00189E20.u2e4.F = v20.f[1];
    }
    if (-0.785398244f < v20.f[0] && v20.f[0] < 0.785398244f) {
        D_00189E20.u2e8.F = v20.f[0];
    }
    for (i = 0; i < 2; i++) {
        a = 1.57079649f;
        if (i == 1) {
            a = -a;
        }
        func_L00_002D3638(&v30, 0.2f, a, 0.45f, 1);
        func_L00_002D3638(&v40, 0.2f, a, -0.45f, 1);
        if (func_002761F8(&v30, &v40, 0x22, D_00189E20.xI2080, 0)) {
            if (D_001A8FF0) D_00189E20.a2c0.f[i] = func_002B0360(&D_L09_001BFE40.v20) - func_002B0360((u8 *)&D_00189E20 + 0x2d0);
            else D_00189E20.a2c0.f[i] = D_L09_001BFE40.v20.f[2] - D_00189E20.u2d8.F;
            if (0.4f < func_00282C48(D_00189E20.a2c0.f[i])) {
                D_00189E20.a2c0.f[i] = 0.0f;
            }
            func_001290E0(&v60, (u8 *)&D_L09_001BFE40.f40);
            func_L00_002B8E48(&v60, &v50);
            if (-0.785398244f < v50.f[1] && v50.f[1] < 0.785398244f) {
                D_00189E20.a2c8.f[i] = v50.f[1];
            }
            if (-0.785398244f < v50.f[0] && v50.f[0] < 0.785398244f) {
                D_00189E20.a2d0.f[i] = v50.f[0];
            }
        } else {
            D_00189E20.a2c0.i[i] = 0;
            D_00189E20.a2c8.f[i] = D_00189E20.u2e4.F;
            D_00189E20.a2d0.f[i] = D_00189E20.u2e8.F;
        }
    }
}
