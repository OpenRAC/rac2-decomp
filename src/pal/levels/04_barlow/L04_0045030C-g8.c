#include "include_asm.h"

#include "common.h"
typedef int BarlowEffectQuad __attribute__((mode(TI)));
typedef union { BarlowEffectQuad q; float f[4]; } BarlowEffectVector;
extern void func_00282D30(void *, void *, float);
extern char *func_L00_0033E220(void *, void *, unsigned int, int, int, int, int, int, float, float);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, unsigned char, void *);
extern void func_PAL_L03_002EE460(void *, void *, void *, void *, void *, int, unsigned char);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_0029F338(void *);
extern float D_L04_001B1830[] SDATA(D_L04_001B1830);
extern float D_L04_001B1828[] SDATA(D_L04_001B1828);
extern float D_L04_001B1820[] SDATA(D_L04_001B1820);
extern int D_L04_001B1850 SDATA(D_L04_001B1850);

void func_PAL_L04_00451600(unsigned char *object)
{
    BarlowEffectVector velocity, lower, upper, min_offset, max_offset;
    char *state = *(char **)(object + 0x68);
    velocity.q = 0;
    velocity.f[0] = -21.5f;
    switch (object[0x20]) {
    case 0:
        func_00282D30(&velocity, &velocity, *(float *)(object + 0x2c));
        *(char **)(state + 4) = func_L00_0033E220(&velocity, object, 0x40208080, -1, 1, -1, 0, -1,
                                                *(float *)(object + 0x2c) * 5250000.0f, *(float *)(object + 0x2c) * 15.0f);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002A9640(object, 0x4010000, 0) && !*(int *)state) func_002A7750(object, 2, -1);
        object[0xa8] = 255;
        break;
    case 2:
        func_PAL_L00_0032C328(object, D_L04_001B1830, D_L04_001B1828, D_L04_001B1820, 65535, 0, D_L04_001B1850, 8, 65535, 255, 0);
        min_offset.q = 0;
        max_offset.q = 0;
        lower.q = 0;
        upper.q = 0;
        upper.f[0] = lower.f[0] = -15.0f;
        min_offset.f[0] = -10.0f;
        min_offset.f[2] = min_offset.f[1] = -4.0f;
        max_offset.f[0] = -3.0f;
        max_offset.f[1] = 5.0f;
        max_offset.f[2] = 4.0f;
        func_PAL_L03_002EE460(object, &lower, &upper, &min_offset, &max_offset, 45, 0);
        func_L00_00324F18(object, &velocity, -21.5f, 0.0f, 0.0f);
        func_PAL_L00_003FB330(object + 0x10, 0, 25, 20, 20, 20, 45, 1,
                     *(float *)(object + 0x2c) * 5.0f, 20.0f, 1, 1, 0, 0);
        func_0029F338(object);
        break;
    }
}

typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
extern u8 *D_L04_001B24DC __attribute__((sda));
extern float D_L04_001B1870 __attribute__((sda));
extern u8 D_L04_001B1880[8] __attribute__((sda));
extern u8 D_L04_001B9680[];
extern float func_002A89A8(void *, int, float);
extern int func_00283CF0(float);
extern void func_L04_0033CB88(void *);
extern int func_002A7820(int, int);
extern void func_002AB650(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern void func_L04_0044D7E0(void *);
extern void func_002B3BA8(void *, int, void *, int, float, float);
typedef struct {
    s32 i00;
    f32 f04;
    f32 f08;
    f32 f0C;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[8];
} D0C0Timer;
typedef struct {
    u8 pad000[0x28];
    u8 b28;
    u8 b29;
    u8 pad02A[6];
    f32 f30;
    u8 b34;
    u8 pad035[0x13];
    u8 b48;
    u8 pad049;
    u8 b4A;
    u8 pad04B[0x15];
    u8 ai[0x10];
    u8 b70;
    u8 b71;
    u8 b72;
    u8 pad073[3];
    u8 b76;
    u8 b77;
    u8 pad078[4];
    f32 f7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    f32 f90;
    f32 f94;
    u8 pad098[4];
    f32 f9C;
    u8 pad0A0[8];
    s32 iA8;
    u8 pad0AC[0x20];
    u8 bCC;
    u8 bCD;
    u8 bCE;
    u8 bCF;
    u8 pad0D0[2];
    u8 bD2;
    u8 bD3;
    u8 pad0D4[0x1C];
    s32 iF0;
    f32 fF4;
    u8 pad0F8[0x18];
    Quad v110;
    f32 f120;
    u8 pad124[0x1C];
    D0C0Timer t140;
    u8 pad170[0x90];
    u8 *p200;
    u8 pad204[0x1C];
    f32 f220;
    u8 pad224[0xC];
    f32 f230;
    u8 pad234[0xAC];
    union { Quad q; f32 f[4]; } v2E0;
    u8 pad2F0[4];
    f32 f2F4;
    u8 pad2F8[8];
    s16 h300;
    u8 pad302[0xA];
    f32 f30C;
    u8 pad310[8];
    s32 i318;
    s32 i31C;
    s32 i320;
    s32 i324;
    s32 i328;
    u8 pad32C[4];
    f32 f330;
} D0C0Vars;

/* Sets the state record up on the first update (ground height, spawn-point height,
   tuning block, timer, home position), then runs its distance, collision and
   func_PAL_002B1A50 checks on every update. */
void func_PAL_L04_00452A80(u8 *obj)
{
    D0C0Vars *p = *(D0C0Vars **)(obj + 0x68);
    u8 *hit;
    int result;

    obj[0x23] = 128;
    if (obj[0x20] == 0) {
        F(obj, 0x18) = func_002A89A8(obj + 0x10, 0, 0.5f);
        qzero_nc(obj + 0xF0);
        if (p->i328 != -1) {
            F(obj, 0x18) = F(D_L04_001B24DC + p->i328 * 256, 0x18) + 1.4f;
            H(obj, 0x34) |= 0x41;
            I(obj, 0x98) = 0;
        }
        p->i320 = 0;
        p->i324 = 0;
        p->b48 = func_00283CF0(15.0f);
        p->b4A = func_00283CF0(4.0f);
        p->b29 = 1;
        p->b70 = 6;
        p->iA8 = 3;
        p->b71 = 9;
        p->b72 = 9;
        p->b76 = 10;
        p->b77 = 11;
        p->f7C = 0.120000005f;
        p->f80 = 0.060000002f;
        p->f84 = 0.0044f;
        p->f88 = 0.0044f;
        p->f8C = 0.00080000004f;
        p->f90 = 0.35f;
        p->f94 = 0.35f;
        p->f9C = 0.4f;
        p->bCC = 6;
        p->bCD = 11;
        p->bCE = 6;
        p->bCF = 11;
        p->bD2 = 6;
        p->bD3 = 11;
        func_L04_0033CB88(&p->t140);
        p->t140.f0C = 2.5f;
        p->t140.f08 = 2.0f;
        p->t140.i00 = func_00283CF0(D_L04_001B1870 * 1024.0f);
        p->t140.f04 = D_L04_001B1870;
        p->t140.f24 = p->f30C * (0.020000001f);
        if (p->v2E0.f[3] != 12439.4f) {
            p->v2E0.q = *(Quad *)(obj + 0x10);
            p->v2E0.f[3] = 12439.4f;
        }
        qcopy(&p->v110, &p->v2E0);
        p->f120 = 0.5f;
        p->h300 = func_002A7820(100, 583);
        p->i31C = 0;
        func_002AB650(obj);
        p->f230 = F(obj, 0x2C);
        p->f220 = p->f30;
        p->b28 = 0;
        p->i318 = 0;
        p->p200 = D_L04_001B1880;
        p->f330 = (float)p->b34;
        func_002A7750(obj, 1, 0);
        if (obj[0x43])
            func_PAL_002A7E68(obj, 0, 0, 0);
    }
    if (obj[0x31] && func_00282E48(obj + 0x10, D_L04_001B9680) < 24.0f) {
        func_002A93B0(obj);
        obj[0x6F] = 22;
    }
    hit = (u8 *)func_002A9640(obj, 0x230000, 0);
    if (hit && hit[0x28] == 8) {
        obj[0x20] = 8;
        obj[0xBC] = 4;
    }
    result = func_PAL_002B1A50(obj, p->ai, 0);
    if (result) {
        if (result == 5) {
            p->iF0 = 0;
            p->fF4 = 1.0053098f;
        }
        func_L04_0044D7E0(obj);
    }
    func_002B3BA8(obj, -1, &p->v2E0, 0, p->f2F4, 10.0f);
}
