/*
 * func_PAL_L00_00410630, the PAL copy of func_L00_0040BA30: the same C, where the effect timer and the
 * particle lifetimes take the 50 Hz scale, the literal 30 becomes 25, and the second burst loop keeps its
 * counter and random value in locals of its own.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; float f[0x980]; char *ptr[0x980]; TI128 q[0x260]; } Hero;
extern Hero D_00189E20;
typedef union { unsigned char b[0x400]; short h[0x200]; int i[0x100]; float f[0x100]; char *p[0x100]; TI128 q[0x40]; } Blk;
extern Blk D_0018BE30;
extern Blk D_00139568;
typedef struct {
    unsigned char pad0[4];
    unsigned char b4;
    unsigned char pad5[0x6B];
    float f70;
    unsigned char pad74[0x6C];
} ClassEntry;
extern ClassEntry D_L00_00262570[];
extern Blk D_L00_001BF200;
extern Blk D_L00_001FE940;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FE9F4[];
extern float D_L00_001B1008 __attribute__((sda));
extern float D_L00_001B1000 __attribute__((sda));
extern int D_L00_001B0FE4 __attribute__((sda));
extern int D_L00_001B0FEC __attribute__((sda));
extern int D_L00_001B0FF0 __attribute__((sda));
extern int D_L00_001B0FE8 __attribute__((sda));
extern int D_L00_001B0FF4 __attribute__((sda));
extern int D_L00_001B19C8 __attribute__((sda));

extern void func_002AFFD8(void *, void *, int);
extern void func_0029FCC0(int, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002AB1F0(void *);
extern int func_00282948(void *);
extern void func_00291450(int);
extern void func_0029F338(void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002761F8(void *, void *, int, int, void *);
extern void func_PAL_L00_00411978(void *, int, int);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_PAL_L00_0040FF58(void *);
extern void ref_L00_0040BA30_00(void (*)(void *), void *);
extern void func_PAL_L00_004114B0(void *);

typedef struct {
    float v[4];
    char *owner;
    int flags;
    signed char b18;
    signed char b19;
    unsigned short h1A;
    float f1C;
    int f20;
} Hit;

typedef struct BeamVars {
    char pad00[0xC];
    struct BeamMoby *target;
    int timer;
    int pad14;
    int effect;
    int enabled;
    char pad20[0x10];
    float end[4];
    float aim[4];
    float dir[4];
    float left[4];
    float right[4];
} BeamVars;

typedef struct BeamMoby {
    char pad00[0x10];
    float pos[4];
    unsigned char state;
    char pad21[0x13];
    unsigned short flags;
    char pad36[0x32];
    BeamVars *vars;
    char pad6c[0x3E];
    unsigned short oClass;
} BeamMoby;

void func_PAL_L00_00410630(BeamMoby *self)
{
    float old0[4];
    float mtx[4];
    float old20[4];
    float dir[4];
    float v40[4];
    float v50[4];
    Hit hit;
    BeamVars *vars = self->vars;
    float ang;
    float r;
    int i;
    int m;
    BeamMoby *t;
    float s1, s2, s3, s4, s5, s6, s7, s8, s9;
    int n;
    int heroNode;
    ClassEntry *tbl;

    qcopy(old0, self->pos);
    func_002AFFD8(self->pos, mtx, 1);
    heroNode = D_00189E20.i[0x1314 / 4];
    func_0029FCC0(heroNode, 6, vars->left);
    func_0029FCC0(heroNode, 7, vars->right);
    qcopy(old20, self->pos);
    func_00282CF0(dir, vars->end, &D_00189E20.b[0x2010]);
    func_00282F20(dir, dir, 1.0f);
    ang = func_00283248(*(float *)(D_00189E20.ptr[0x18D0 / 4] + 0x10) - D_00189E20.f[0x80 / 4],
                        *(float *)(D_00189E20.ptr[0x18D0 / 4] + 0x14) - D_00189E20.f[0x84 / 4]);
    if (ang < 1.5707964897155762f)
        r = func_002A7878(0.0f, -0.7853982448577881f);
    else
        r = func_002A7878(0.0f, 0.7853982448577881f);
    qcopy(vars->aim, &D_0018BE30);
    vars->aim[2] -= D_L00_001B1008;
    func_00282CF0(vars->aim, vars->aim, &D_0018BE30);
    func_002ACEC0(vars->aim, vars->aim, dir, r);
    func_00282CC0(vars->aim, &D_0018BE30, vars->aim);
    t = vars->target;
    if (t != 0) {
        if (t->state == 0xFE) {
            vars->target = 0;
        } else if (t->state == 0xFD) {
            vars->target = 0;
        } else {
            func_00282CF0(v40, t->pos, self->pos);
            if (func_00282DF0(v40) != 0.0f) {
                char *target = func_002AB1F0(vars->target);
                if (target != 0) {
                    func_00282D30(v50, mtx, *(float *)(target + 0x10));
                    func_00282CC0(v40, v40, v50);
                    func_00282DF0(v40);
                }
            } else {
                vars->target = 0;
            }
        }
    }
    ang = func_00283C80(func_00283248(*(float *)(D_00189E20.ptr[0x18D0 / 4] + 0x10) - D_00189E20.f[0x80 / 4],
                                      *(float *)(D_00189E20.ptr[0x18D0 / 4] + 0x14) - D_00189E20.f[0x84 / 4]),
                        D_00189E20.f[0x98 / 4]);
    switch (self->state) {
    case 0:
        /* Each arm repeats its whole setup; the compiler cross-jumps the shared tails away. */
        tbl = D_L00_00262570;
        if (tbl[D_00139568.b[9]].b4 != 0) {
            hit.flags = 0x110000;
            hit.owner = (char *)self;
            hit.f20 = 1;
            hit.f1C = tbl[D_00139568.b[0x49]].f70;
            qcopy(hit.v, vars->dir);
            func_00282F20(&hit, &hit, 0.2f);
            hit.b18 = 1;
            hit.b19 = 1;
            hit.v[3] = 5627.9248046875f;
            hit.h1A = self->oClass;
        } else {
            hit.flags = 0x10000;
            hit.owner = (char *)self;
            hit.f20 = 1;
            hit.f1C = tbl[D_00139568.b[9]].f70;
            qcopy(hit.v, vars->dir);
            func_00282F20(&hit, &hit, 0.2f);
            hit.b18 = 1;
            hit.b19 = 1;
            hit.v[3] = 5627.9248046875f;
            hit.h1A = self->oClass;
        }
        if (D_L00_001B1000 * 0.01745329424738884f < ang) {
            if (vars->enabled == 0)
                { func_0029F338(self); return; }
            if (func_002761F8(&D_0018BE30, vars->end, 0, D_0018BE30.i[0x280 / 4], &hit) == 0)
                { func_0029F338(self); return; }
            if (D_L00_001BF200.i[0x1C / 4] > 0)
                { func_0029F338(self); return; }
            if (D_L00_001BF200.p[0x18 / 4] == 0)
                func_PAL_L00_00411978(&D_L00_001BF200.b[0x20], 0xF, 1);
            else if (*(int *)(D_L00_001BF200.p[0x18 / 4] + 0x98) != 0)
                func_PAL_L00_00411978(&D_L00_001BF200.b[0x20], 0xA, 1);
            func_002E5DA0(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = ((s32)(D_L00_001B0FE4) * 5 + 2) / 6;
        } else {
            if (func_002761F8(&D_0018BE30, vars->end, 0, D_0018BE30.i[0x280 / 4], &hit) == 0)
                { func_0029F338(self); return; }
            if (D_L00_001BF200.i[0x1C / 4] > 0)
                { func_0029F338(self); return; }
            if (D_L00_001BF200.p[0x18 / 4] == 0)
                func_PAL_L00_00411978(&D_L00_001BF200.b[0x20], 0xF, 0);
            else if (*(int *)(D_L00_001BF200.p[0x18 / 4] + 0x98) != 0)
                func_PAL_L00_00411978(&D_L00_001BF200.b[0x20], 0xA, 0);
            func_002E5DA0(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = ((s32)(D_L00_001B0FE4) * 5 + 2) / 6;
        }
        func_00282CF0(v40, vars->end, &D_0018BE30);
        func_00282F20(v40, v40, func_00282DF0(v40) * 0.5f);
        func_00282CC0(v40, &D_0018BE30, v40);
        if (D_L00_001B1000 * 0.01745329424738884f < ang) {
            if (vars->enabled == 0)
                goto bounds;
            vars->effect = func_L00_002FCF18(v40, 10.0f, 0.0f, 1.0f, 0.1f, 0.1f);
        } else {
            vars->effect = func_L00_002FCF18(v40, 10.0f, 0.0f, 0.1f, 1.0f, 0.1f);
        }
        break;
    case 1:
        if (func_00282948(&vars->timer) != 0) {
            vars->target = 0;
            if (vars->effect != -1)
                func_00291450(vars->effect);
            func_0029F338(self);
            return;
        }
        if (D_L00_001B1000 * 0.01745329424738884f < ang) {
            if (vars->enabled != 0) {
                for (i = 0; i < 10; i++) {
                    char *p;
                    s1 = func_002A7878(0.0f, 1.0f);
                    func_00282CF0(v40, vars->end, vars->left);
                    func_00282F20(v40, v40, s1 * func_00282DF0(v40));
                    func_00282CC0(v40, vars->left, v40);
                    s2 = func_002A7878(0.0f, 1.0f);
                    func_00282CF0(v50, vars->end, vars->right);
                    func_00282F20(v50, v50, s2 * func_00282DF0(v50));
                    func_00282CC0(v50, vars->right, v50);
                    n = func_002A77E0(0xFF);
                    s3 = func_002A7878(0.35f, 0.5f);
                    p = func_002C65A0(v40, D_L00_001A8F20, ((s32)(D_L00_001B0FEC) * 5 + 2) / 6, D_L00_001B0FF0, n, 0x30, 0,
                                      s3 * 210000.0f, s3 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (D_L00_001FE940.p[0x184 / 4])[7];
                    p = func_002C65A0(v50, D_L00_001A8F20, ((s32)(D_L00_001B0FEC) * 5 + 2) / 6, D_L00_001B0FF0, n, 0x30, 0,
                                      s3 * 210000.0f, s3 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (D_L00_001FE940.p[0x184 / 4])[7];
                }
                {
                    int j;
                    int n2;

                for (j = 0; j < 20; j++) {
                    char *p;
                    s4 = func_002A7878(0.0f, 1.0f);
                    func_00282CF0(v40, vars->end, vars->left);
                    func_00282F20(v40, v40, s4 * func_00282DF0(v40));
                    func_00282CC0(v40, vars->left, v40);
                    s5 = func_002A7878(0.0f, 1.0f);
                    func_00282CF0(v50, vars->end, vars->right);
                    func_00282F20(v50, v50, s5 * func_00282DF0(v50));
                    func_00282CC0(v50, vars->right, v50);
                    n2 = func_002A77E0(0xFF);
                    s6 = func_002A7878(0.2f, 0.35f);
                    v40[0] += func_002A78D8(0.0f, 0.02f);
                    v40[1] += func_002A78D8(0.0f, 0.02f);
                    v40[2] += func_002A78D8(0.0f, 0.02f);
                    p = func_002C65A0(v40, D_L00_001A8F20, ((s32)(D_L00_001B0FE8) * 5 + 2) / 6, D_L00_001B0FF4, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                    s6 *= 0.5f;
                    p = func_002C65A0(v40, D_L00_001A8F20, ((s32)(D_L00_001B0FE8) * 5 + 2) / 6, 0x808080, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                    v50[0] += func_002A78D8(0.0f, 0.02f);
                    v50[1] += func_002A78D8(0.0f, 0.02f);
                    v50[2] += func_002A78D8(0.0f, 0.02f);
                    p = func_002C65A0(v50, D_L00_001A8F20, ((s32)(D_L00_001B0FE8) * 5 + 2) / 6, D_L00_001B0FF4, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                    s6 *= 0.5f;
                    p = func_002C65A0(v50, D_L00_001A8F20, ((s32)(D_L00_001B0FE8) * 5 + 2) / 6, 0x808080, n2, 0x30, 0,
                                      s6 * 210000.0f, s6 * 42000.0f, 0.0f, 0);
                    if (p != 0)
                        p[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                }
                }
                if (vars->target != 0 && D_L00_001B19C8 % 5 == 0) {
                    char *p;
                    s7 = func_002A7878(0.0f, 1.0f);
                    func_00282CF0(v40, vars->end, vars->left);
                    func_00282F20(v40, v40, s7 * func_00282DF0(v40));
                    func_00282CC0(v40, vars->left, v40);
                    s8 = func_002A7878(0.0f, 1.0f);
                    func_00282CF0(v50, vars->end, vars->right);
                    func_00282F20(v50, v50, s8 * func_00282DF0(v50));
                    func_00282CC0(v50, vars->right, v50);
                    p = func_002C65A0(v40, D_L00_001A8F20, 0x19, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (p != 0)
                        p[2] = *D_L00_001FE9F4[0];
                    p = func_002C65A0(v50, D_L00_001A8F20, 0x19, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (p != 0)
                        p[2] = *D_L00_001FE9F4[0];
                }
            }
        } else {
            for (m = 0; m < 10; m++) {
                char *p;
                s9 = func_002A7878(0.25f, 0.4f) * 210000.0f;
                p = func_002C65A0(&D_00189E20.b[0x2010], D_L00_001A8F20, 2, 0x108010, 2, 0x7F, 0x10,
                                  s9, s9, 0.0f, 0);
                if (p != 0)
                    p[2] = *D_L00_001FE940.p[0x64 / 4];
                p = func_002C65A0(&D_00189E20.b[0x2010], D_L00_001A8F20, 2, 0x208020, -1, 0x7F, 0x10,
                                  s9, s9, 0.0f, 0);
                if (p != 0)
                    p[2] = *D_L00_001FE940.p[0x64 / 4];
            }
        }
        func_PAL_L00_0040FF58(self);
        ref_L00_0040BA30_00(func_PAL_L00_004114B0, self);
        break;
    }
bounds:
    if (self->pos[0] < 2.0f || self->pos[0] > 1021.0f ||
        self->pos[1] < 2.0f || self->pos[1] > 1021.0f ||
        self->pos[2] < 2.0f || self->pos[2] > 1021.0f)
        func_0029F338(self);
}
