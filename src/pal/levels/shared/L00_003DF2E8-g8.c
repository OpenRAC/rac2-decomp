#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[112]; float scale; char tail[108]; } TableEntry;
typedef struct {
    char state[24];
    char *object;
    unsigned int detail;
    Vec position;
    Vec unk30;
    Vec normal;
} CollisionResult;
typedef struct {
    Vec pos;
    char pad10[8];
    unsigned char kind;
    unsigned char flag;
    unsigned short type;
    char pad1c[4];
    int count;
    char pad24[12];
} HitInfo;
extern unsigned char D_00139585 __attribute__((nosda));
extern char D_L00_00262570[];
extern CollisionResult D_L00_001BF200;
extern struct { Vec position; Vec unk; Vec normal; } D_L00_001BF220;
extern Vec D_L00_001BF240;
extern char *D_0018C0B0 __attribute__((nosda));
extern float D_L00_001B03E4 __attribute__((sda));
extern float D_L00_001A8F20;
extern void func_00300190(void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_002FEE50(int);
extern void func_002FE880(void *a, void *b, float c);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern float func_00283198(float);
extern float func_00283180(float);
extern int func_002A7820(int, int);
extern void func_00282D30(void *, void *, float);
extern int func_001163B0(void);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_002BEF58(void *, void *, int, float);
extern int func_00282948(void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(char *, void *);
extern void func_PAL_0032F0B8(void *, int, int);
extern void func_PAL_L00_003E05B0(char *, int, void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_002A7940(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern unsigned char *func_PAL_L00_00343208(void *, void *, void *, float, int, int);
extern void func_L00_003DCAC8(char *, int, float, int, int, int, char *, float);
extern int func_002A77E0(int);
extern u8 *func_PAL_002BE9A8(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern int func_00283CF0(float);
extern void func_L00_003DC2D0(char *);
extern int func_002B4038(int, int);
extern void ref_L00_003DB118_00(void *, void *);
extern void func_L00_003DC640();
extern void func_0029F338(void *);

void func_PAL_L00_003DF2E8(char *self)
{
    Vec ray;
    Vec scale3;
    Vec push;
    char *timer;
    char *pv;
    int i;
    u8 *p;

    pv = *(char **)(self + 0x68);
    if (*(unsigned char *)(self + 0x20) != 0) {
        char *trail = pv + 0x10;
        func_00300190(self + 0x10, self + 0x10);
        for (i = 3; i >= 0; i--) {
            func_00300190(trail, trail);
            trail += 0x10;
        }
    }
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        for (i = 0; i < 4; i++) {
            qcopy(pv + 0x10 + i * 0x10, self + 0x10);
        }
        *(unsigned char *)(self + 0x20) = 1;
    case 1:
        {
        float a30[4] __attribute__((aligned(16)));
        float a40[4] __attribute__((aligned(16)));
        HitInfo hit;
        float spark[4] __attribute__((aligned(16)));
        ray.q = *(Quad *)(self + 0x10);
        timer = pv + 0x60;
        func_002FEE70(*(int *)(pv + 0x78), pv, 0);
        func_00282CC0(self + 0x10, self + 0x10, pv);
        func_002FE880(self + 0x10, pv, D_L00_001B03E4 * 0.00040000002f);
        for (i = 3; i > 0; i--) {
            func_00282D08(pv + 0x10 + i * 0x10, pv + 0x10 + i * 0x10, pv + i * 0x10, 0.2f);
        }
        *(Quad *)(pv + 0x10) = *(Quad *)(self + 0x10);
        *(float *)(pv + 0x64) = func_00283B98(*(float *)(pv + 0x64), *(float *)(pv + 0x68));
        func_00282C88(&scale3);
        scale3.f[1] = *(float *)(pv + 0x64) * 0.5f;
        scale3.f[0] = *(float *)(pv + 0x64) * 0.25f;
        scale3.f[2] = *(float *)(pv + 0x64) * 0.375f;
        func_002833F0(self + 0xC0, &scale3);
        *(float *)(self + 0xC0) = *(float *)(self + 0xC0) * 0.4f * (func_00283198(*(float *)(pv + 0x64)) + 2.0f);
        *(float *)(self + 0xD4) = *(float *)(self + 0xD4) * 0.5f * (func_00283180(*(float *)(pv + 0x64)) + 2.0f);
        *(float *)(self + 0xE8) = *(float *)(self + 0xE8) * 0.75f * (func_00283198(*(float *)(pv + 0x64)) + 2.0f);
        {
            int c = func_002A7820(0x7F, 0xFF);
            *(int *)(self + 0x78) = ((c << 16) + (c << 8) + c) | 0x7F000000;
        }
        func_00282D30(&push, pv, -0.125f);
        if (func_001163B0() % 10 == 0) {
            func_00282C88(a40);
            a30[0] = *(float *)(self + 0x10) + func_002A7878(-0.15f, 0.15f);
            a30[1] = *(float *)(self + 0x14) + func_002A7878(-0.15f, 0.15f);
            a30[2] = *(float *)(self + 0x18) + func_002A7878(-0.15f, 0.15f);
            a40[0] = func_002A7878(-0.025f, 0.025f);
            a40[1] = func_002A7878(-0.025f, 0.025f);
            a40[2] = func_002A7878(0.0f, 0.025f);
            func_00282F20(a40, a40, 0.05f);
            func_PAL_002BEF58(a30, a40, 0, -1.0f);
        }
        if (func_00282948(timer) != 0) goto kill;
        {
        int collision;
        if (func_002761F8(&ray, self + 0x10, 0, self, 0) != 0)
            collision = 1;
        else
            collision = func_00277258(self + 0x10, 0, self, 0.05f) != 0;
        if (collision) {
            CollisionResult *col = &D_L00_001BF200;
            char *obj = col->object;
            if (obj != 0) {
                char *hero;
                if ((*(long long *)(obj + 0x30) & ((long long)0xA000 << 31)) && obj != (hero = D_0018C0B0)
                    && *(short *)(obj + 0xAA) != 0x5C9) {
                    func_00282CF0(a30, obj + 0x10, hero + 0x10);
                    func_00282F20(a30, a30, 1.0f);
                    func_00282F20(&hit, &hit, 0.14000002f);
                    func_002A8C00(&hit, self, 0x910000, a30, ((TableEntry *)D_L00_00262570)[D_00139585].scale);
                    {
                    Quad hitPosition = *(Quad *)a30;
                    hit.kind = 5;
                    hit.pos.q = hitPosition;
                    hit.pos.f[3] = 5627.925f;
                    hit.count = 1;
                    hit.flag = 1;
                    hit.type = *(unsigned short *)(col->object + 0xAA);
                    func_002A8E20(col->object, &hit);
                    }
                    func_PAL_0032F0B8(col->object, 0x3F, *(int *)(self + 0xB8));
                    *(Quad *)a40 = *(Quad *)(col->object + 0x10);
                    a40[2] = a40[2] + 5.0f;
                    *(Quad *)a30 = *(Quad *)a40;
                    a30[2] = a30[2] - 10.0f;
                    *(Quad *)(self + 0x10) = col->position.q;
                    *(unsigned char *)(self + 0x20) = 2;
                    *(unsigned short *)(self + 0x34) |= 0x41;
                    *(Quad *)(pv + 0x50) = col->normal.q;
                    *(int *)(pv + 0x7C) = 1;
                    for (i = 0; i < 3; i++) {
                        func_00282F20(spark, &D_L00_001BF240, func_002A7878(0.20000002f, 0.40000004f));
                        spark[0] += func_002A7878(-0.15f, 0.15f);
                        spark[1] += func_002A7878(-0.15f, 0.15f);
                        spark[2] += func_002A7878(-0.15f, 0.15f);
                        func_00282F20(spark, spark, func_002A7878(0.040000003f, 0.120000005f));
                        func_PAL_002BEF58(self + 0x10, spark, 0, -1.0f);
                    }
                } else {
                    *(Quad *)(self + 0x10) = D_L00_001BF220.position.q;
                    *(unsigned char *)(self + 0x20) = 2;
                    *(unsigned short *)(self + 0x34) |= 0x41;
                    *(Quad *)(pv + 0x50) = D_L00_001BF220.normal.q;
                    for (i = 0; i < 6; i++) {
                        func_00282F20(a30, &D_L00_001BF240, func_002A7878(0.20000002f, 0.40000004f));
                        a30[0] += func_002A7878(-0.15f, 0.15f);
                        a30[1] += func_002A7878(-0.15f, 0.15f);
                        a30[2] += func_002A7878(-0.15f, 0.15f);
                        func_00282F20(a30, a30, func_002A7878(0.040000003f, 0.120000005f));
                        func_PAL_002BEF58(self + 0x10, a30, 0, -1.0f);
                    }
                }
            } else {
                *(Quad *)(self + 0x10) = col->position.q;
                *(unsigned char *)(self + 0x20) = 2;
                *(unsigned short *)(self + 0x34) |= 0x41;
                *(Quad *)(pv + 0x50) = col->normal.q;
                for (i = 0; i < 6; i++) {
                    func_00282F20(a30, &D_L00_001BF240, func_002A7878(0.20000002f, 0.40000004f));
                    a30[0] += func_002A7878(-0.15f, 0.15f);
                    a30[1] += func_002A7878(-0.15f, 0.15f);
                    a30[2] += func_002A7878(-0.15f, 0.15f);
                    func_00282F20(a30, a30, func_002A7878(0.040000003f, 0.120000005f));
                    func_PAL_002BEF58(self + 0x10, a30, 0, -1.0f);
                }
            }
            *(int *)(pv + 0x60) = 12;
            func_PAL_L00_003E05B0(self, 12, self + 0x10, &D_L00_001BF240, 0.10000001f);
        }
        }
        }
        break;
    case 2:
        {
            int pick[2];
            float a40[4] __attribute__((aligned(16)));
            HitInfo hit;
            pick[0] = 0x44;
            pick[1] = 0x48;
            func_00282F20(a40, pv, 2.0f);
            func_00282CC0(a40, a40, self + 0x10);
            func_00282DD8(&hit, self + 0x10, a40);
            func_00282F20(&hit, &hit, 1.0f);
            func_002ACEC0(&hit, &hit, pv, func_002A7940());
            func_PAL_L00_00343208(self + 0x10, pv, &hit, func_002A7878(0.010000001f, 0.060000002f), pick[func_001163B0() % 2], func_002A7820(0x19, 0x2A));
            func_L00_003DCAC8(self + 0x10, 0x103080, func_002A7878(0.75f, 1.2f), func_002A7820(0x3F, 0x5F), 0xB, 2, pv, func_002A7940());
            func_L00_003DCAC8(self + 0x10, 0x103080, func_002A7878(0.75f, 1.2f) * 0.75f, func_002A7820(0x4F, 0x6F), 0xB, 2, pv, func_002A7940());
            func_L00_003DCAC8(self + 0x10, 0x103080, func_002A7878(0.75f, 1.2f) * 0.5f, func_002A7820(0x5F, 0x7F), 0xB, 2, pv, func_002A7940());
            if (func_00282948(pv + 0x60) != 0) goto kill;
            if (*(int *)(pv + 0x7C) == 0) {
                for (i = 3; i > 0; i--) {
                    func_00282D08(pv + 0x10 + i * 0x10, pv + 0x10 + i * 0x10, pv + i * 0x10, 0.2f);
                }
            } else {
                for (i = 3; i > 0; i--) {
                    func_00282D08(pv + 0x10 + i * 0x10, pv + 0x10 + i * 0x10, pv + i * 0x10, 0.5f);
                }
            }
            *(Quad *)(pv + 0x10) = *(Quad *)(self + 0x10);
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) + 0.0005f;
        }
        break;
    }
    if (*(unsigned char *)(self + 0x20) == 1) {
        for (i = 0; i < 4; i++) {
            int n = func_002A77E0(5);
            p = func_PAL_002BE9A8(self + 0x10, 0.2f, 1.0f, 0.9f, func_002A77E0(2) ? -n : n, &D_L00_001A8F20, 210000.0f, 0x7F204080, 1);
            if (p) {
                u8 *t = p + 0x20;
                *(unsigned short *)(p + 0xA) = 4;
                p[9] = func_00283CF0(4.0f) + 0x40;
                *(int *)(t + 4) = 2;
                t[0xA] = 0x30;
                t[0xB] = p[0xA];
            }
        }
        for (i = 0; i < 3; i++) {
            int n = func_002A77E0(3);
            p = func_PAL_002BE9A8(self + 0x10, 0.05f, 1.0f, 0.9f, func_002A77E0(2) ? -n : n, &D_L00_001A8F20, 157500.0f, 0x7F4080FF, 1);
            if (p) {
                u8 *t = p + 0x20;
                *(unsigned short *)(p + 0xA) = 2;
                p[9] = func_00283CF0(4.0f) + 0x40;
                *(int *)(t + 4) = 2;
                t[0xA] = 0x40;
                t[0xB] = p[0xA];
            }
        }
        for (i = 0; i < 2; i++) {
            int n = func_002A77E0(3);
            p = func_PAL_002BE9A8(self + 0x10, 0.05f, 1.0f, 0.9f, func_002A77E0(2) ? -n : n, &D_L00_001A8F20, 105000.0f, 0x7FFFFFFF, 1);
            if (p) {
                u8 *t = p + 0x20;
                *(unsigned short *)(p + 0xA) = 2;
                p[9] = func_00283CF0(4.0f) + 0x40;
                *(int *)(t + 4) = 2;
                t[0xA] = 0x60;
                t[0xB] = p[0xA];
            }
        }
    }
    func_L00_003DC2D0(self);
    if (func_002B4038(*(int *)(pv + 0x74), *(int *)(pv + 0x70)) == 0) {
kill:
        func_002FEE50(*(int *)(pv + 0x78));
        func_0029F338(self);
    } else {
        ref_L00_003DB118_00(func_L00_003DC640, self);
    }
}
