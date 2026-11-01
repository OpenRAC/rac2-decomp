#include "common.h"

typedef struct { float f[4]; } __attribute__((aligned(16))) V;
typedef struct { float a, va, b, vb, ang, z, vz; } S_9f38;
typedef struct { u8 p0[0x15C]; float f15C; u8 p1[0x348-0x160]; short s348; u8 p2[0x2290-0x34A]; u8 *p2290; u8 p3[0x22A0-0x2294]; int i22A0; u8 p4[0x22B5-0x22A4]; u8 b22B5; } HeroInput;
typedef struct { u8 p0[0x100]; float f100,f104,f108,f10C; u8 p1[0x1A0-0x110]; int i1A0; } Controller;
extern HeroInput D_00189E20;
extern Controller D_00138180;
typedef struct { u8 pad[0x290]; short phase; } CamGlobal;
extern CamGlobal D_L00_001B8C80_1;
extern char *D_L00_001B1844;
extern int D_001A7BA0[] __attribute__((sda));
extern int D_001A8FF0 __attribute__((sda));
extern float D_L00_001B15C8 __attribute__((sda));
extern float D_L00_001B15CC __attribute__((sda));
extern float D_L00_001B15D0 __attribute__((sda));
extern float D_L00_001B15D4 __attribute__((sda));
extern float D_L00_001B15D8 __attribute__((sda));
void func_L00_00426480(void *);
void func_00282F20(void *,void *,float);
void func_00282DD8(void *,void *,void *);
void func_00282CC0(void *,void *,void *);
float func_00283CE0(int);
float func_00282C48(float);
float func_002702C8(float,float,float,float,float,float *);
void func_002ACEC0(void *,void *,void *,float);
float func_00283B98(float,float);
float func_00283BE0(float,float);
int func_00277258(void *,int,void *,float);

/* Adapted from RAC1 update_hero_aligned_camera_from_input, camera_modes_and_scripts.c. */
void func_L00_004266E8(u8 *o) {
    V up;
    V side;
    V d;
    S_9f38 *st;
    float t, r, k;
    char *params = *(char **)(D_L00_001B1844 + *(short *)(o + 0x84) * 0x20 + 0x1C);
    st = *(S_9f38 **)(o + 0x70);
    func_L00_00426480(o);
    func_00282F20(&up, D_00189E20.p2290 + 0xE0, 1.0f);
    if (D_L00_001B8C80_1.phase == 0 && D_00189E20.b22B5 == 0) D_00189E20.b22B5 = 1;
    t = -D_00138180.f108;
    if (t == 0.0f) t = -D_00138180.f100;
    if (t == 0.0f) t = func_00283CE0((D_00138180.i1A0 >> 15) & 1);
    if (t == 0.0f) t = -func_00283CE0((D_00138180.i1A0 >> 13) & 1);
    if (*(short *)(params + 0x26)) t = 0.0f;
    r = func_00282C48(st->a);
    k = D_L00_001B15C8 + (D_L00_001B15CC - D_L00_001B15C8) * r;
    st->a = r = func_002702C8(st->a, t, D_L00_001B15D0, D_L00_001B15D4, D_L00_001B15D8, &st->va);
    if (r != 0.0f) func_002ACEC0(o, o, &up, k * r);
    if (D_00189E20.f15C != 0.0f && D_00189E20.s348 == 0 && D_001A8FF0 == 0)
        func_002ACEC0(o, o, &up, D_00189E20.f15C);
    t = -D_00138180.f10C;
    if (t == 0.0f) t = -D_00138180.f104;
    if (t == 0.0f) t = func_00283CE0((D_00138180.i1A0 >> 12) & 1);
    if (t == 0.0f) t = -func_00283CE0((D_00138180.i1A0 >> 14) & 1);
    if (D_L00_001B8C80_1.phase != 0 && D_00189E20.i22A0 == 2) t = 0.0f;
    if (*(short *)(params + 0x26)) t = 0.0f;
    if (D_001A7BA0[1] == 0) t = -t;
    r = func_00282C48(st->b);
    k = D_L00_001B15C8 + (D_L00_001B15CC - D_L00_001B15C8) * r;
    st->b = func_002702C8(st->b, t, D_L00_001B15D0, D_L00_001B15D4, D_L00_001B15D8, &st->vb);
    if (st->b != 0.0f) {
        float a, n, z;
        func_00282DD8(&side, o, &up);
        a = k * st->b;
        n = func_00282C48(func_00283B98(st->ang, a));
        if (1.1170108318328857f < n && func_00282C48(st->ang) < n)
            a += -a * (func_00283BE0(n, 1.1170108318328857f) * 2.86478853225708f);
        if (n >= 1.1152654886245728f && st->ang > 0.0f)
            st->z = func_002702C8(st->z, 0.5f, 0.005f, 0.2f, 0.0f, &st->vz);
        else
            st->z = func_002702C8(st->z, 0.0f, 0.005f, 0.2f, 0.0f, &st->vz);
        z = 0.0f;
        d.f[0] = *(float *)(o + 0);
        d.f[1] = *(float *)(o + 4);
        d.f[3] = z;
        d.f[2] = z;
        func_00282F20(&d, &d, st->z);
        func_00282CC0(o + 0x30, o + 0x30, &d);
        if (func_00277258(o + 0x30, 0x12, D_00189E20.p2290, 0.3f))
            st->z = func_002702C8(st->z, z, 0.005f, 0.2f, z, &st->vz);
        n = func_00283B98(st->ang, a);
        if (func_00282C48(n) > 1.4660767316818237f)
            { float m = 1.4660767316818237f; if (!(z < n)) m = -1.4660767316818237f; a = func_00283BE0(m, st->ang); }
        func_002ACEC0(o, o, &side, a);
        st->ang = func_00283B98(st->ang, a);
    }
    func_00282F20(o, o, 1.0f);
    func_00282DD8(o + 0x10, o, &up);
    func_00282F20(o + 0x10, o + 0x10, 1.0f);
    func_00282DD8(o + 0x20, o + 0x10, o);
    *(short *)(params + 0x26) = 0;
}
