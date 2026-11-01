#include "include_asm.h"

#include "common.h"
extern int func_00283CF0(f32);
extern s32 func_L17_00340DD0(f32, s32, s32, s32);
extern f32 D_L17_001B04B8 __attribute__((sda));
extern void func_002A7750(void *, s32, s32);
extern s32 func_002A9640(void *, s32, s32);
extern s32 D_L17_001B1E00 __attribute__((sda));
extern s32 D_L17_001B1DE0 __attribute__((sda));
extern s32 D_L17_001B1DD8 __attribute__((sda));
extern s32 D_L17_001B1DD0 __attribute__((sda));
extern char *D_L17_001B2C1C __attribute__((sda));
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
typedef struct {
    s32 i00;
    f32 f04;
    f32 f08;
    f32 f0C;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[8];
} L17Timer;
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
    u8 pad072[4];
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
    L17Timer t140;
    u8 pad170[0x30];
    u8 *target;
    u8 pad1A4[0x16C];
    u8 *p310;
    u8 pad314[0x1C];
    f32 f330;
    u8 pad334[0xC];
    f32 f340;
    u8 pad344[0x8C];
    union { Quad q; f32 f[4]; } v3D0;
    u8 pad3E0[0x20];
    s16 h400;
    u8 pad402[2];
    s16 h404;
    u8 pad406[2];
    u8 *p408;
    f32 f40C;
    u8 pad410[8];
    s32 i418;
    s32 i41C;
    s32 i420;
    s32 i424;
    s32 i428;
    u8 pad42C[4];
    f32 f430;
    u8 pad434[0x1C];
    s32 i450;
} L17Vars;
extern float D_L17_001B0CA8 __attribute__((sda));
extern u8 D_L17_001B0CB8[4] __attribute__((sda));
extern u8 D_L17_001B9BC0[];
extern char D_L17_001B0CC8[];
extern u8 *D_0018C0B0 NOT_SDA;
extern float func_002A89A8(void *, int, float);
extern void func_L04_0033CB88(void *);
extern int func_002A7820(int, int);
extern void func_002AB650(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern void func_L17_003E4860(void *);
extern int func_002B3BA8(void *, int, int, int, float, float);
extern void func_0026FEB8(void *, ...);
extern s32 D_001A79F0 MACRO_ADDR;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[];
extern u8 *D_L17_001FE880[];
extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern f32 func_002A7940(void);
extern s32 func_002B3868(void *);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_002E5CF8(s32, s32, void *);

/* Sets the state record up on the first update (the tuning block in field order), then
   handles damage and keeps a target, falling back to D_0018C0B0 when the record has none. */
void func_PAL_L17_003E89B0(u8 *obj)
{
    L17Vars *p = *(L17Vars **)(obj + 0x68);
    u8 *hit;
    u8 *target;
    int result;

    obj[0x23] = 128;
    if (obj[0x20] == 0) {
        float ground = func_002A89A8(obj + 0x10, 0, 0.5f);
        float radius = F(*(u8 **)(obj + 0x24), 0x24);

        F(obj, 0x18) = ground;
        F(obj, 0x2C) = radius;
        qzero_nc(obj + 0xF0);
        if (p->i428 != -1) {
            F(obj, 0x18) = F((u8 *)D_L17_001B2C1C + p->i428 * 256, 0x18) + 1.4f;
            H(obj, 0x34) |= 0x41;
            I(obj, 0x98) = 0;
        }
        p->i420 = 0;
        p->i424 = 0;
        p->b48 = func_00283CF0(15.0f);
        p->b4A = func_00283CF0(4.0f);
        p->b29 = 1;
        p->b70 = 7;
        p->iA8 = 3;
        p->b71 = 9;
        p->b76 = 12;
        p->b77 = 15;
        p->f7C = 0.50000006f;
        p->f80 = 0.060000002f;
        p->f84 = 0.0044f;
        p->f88 = 0.008f;
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
        p->t140.i00 = func_00283CF0(D_L17_001B0CA8 * 1024.0f);
        p->t140.f04 = D_L17_001B0CA8;
        p->t140.f24 = p->f40C * (0.020000001f);
        if (p->v3D0.f[3] != 12439.4f) {
            p->v3D0.q = *(Quad *)(obj + 0x10);
            p->v3D0.f[3] = 12439.4f;
        }
        qcopy_nc(&p->v110, &p->v3D0);
        p->f120 = 0.5f;
        p->h400 = func_002A7820(100, 583);
        p->i41C = 0;
        func_002AB650(obj);
        p->f340 = F(obj, 0x2C);
        p->f330 = p->f30;
        p->b28 = 0;
        p->i418 = 0;
        p->p310 = D_L17_001B0CB8;
        p->f430 = (float)p->b34;
        func_002A7750(obj, 1, 0);
        if (obj[0x43])
            func_PAL_002A7E68(obj, 0, 0, 0);
        p->i450 = p->i428;
    }
    if (obj[0x31] && func_00282E48(obj + 0x10, D_L17_001B9BC0) < 24.0f) {
        func_002A93B0(obj);
        obj[0x6F] = 22;
    }
    hit = (u8 *)func_002A9640(obj, 0x230000, 0);
    if (hit && hit[0x28] == 8) {
        obj[0x20] = 9;
        obj[0xBC] = 4;
    }
    result = func_PAL_002B1A50(obj, p->ai, 0);
    if (result) {
        if (result == 5) {
            p->iF0 = 0;
            p->fF4 = 1.0053098f;
        }
        func_L17_003E4860(obj);
    }
    p->h404 = func_002B3BA8(obj, -1, 0, 0, 15.0f, 3.0f);
    target = p->target;
    if (!target) {
        func_0026FEB8(D_L17_001B0CC8);
        target = D_0018C0B0;
    }
    p->p408 = target;
}
