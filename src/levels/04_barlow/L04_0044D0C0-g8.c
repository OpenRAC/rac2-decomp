/* func_L04_0044D0C0: a -G8 unit (D_L04_001B24DC, D_L04_001B1870 and D_L04_001B1880 are
 * read through $gp). The same set-up as func_L17_003E41A8 in
 * L17_003C7C70-g8.c, whose field-order tuning block it follows. */
#include "common.h"

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
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void *func_002A9640(void *, int, int);
extern int func_002B0ED8(void *, void *, int);
extern void func_L04_0044D7E0(void *);
extern void func_002B3BA8(void *, int, void *, int, float, float);

/* The 0x30-byte record func_L04_0033CB88 fills with its defaults. */
typedef struct {
    s32 i00;
    f32 f04;
    f32 f08;
    f32 f0C;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[8];
} D0C0Timer;

/* The object's state record, as far as func_L04_0044D0C0 uses it. */
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
   func_002B0ED8 checks on every update. */
void func_L04_0044D0C0(u8 *obj)
{
    D0C0Vars *vars = *(D0C0Vars **)(obj + 0x68);
    u8 *hit;
    int result;

    obj[0x23] = 128;
    if (obj[0x20] == 0) {
        F(obj, 0x18) = ProbeGroundHeightBelow(obj + 0x10, 0, 0.5f);
        qzero_nc(obj + 0xF0);
        if (vars->i328 != -1) {
            F(obj, 0x18) = F(gMobyPool_L04 + vars->i328 * 256, 0x18) + 1.4f;
            H(obj, 0x34) |= 0x41;
            I(obj, 0x98) = 0;
        }
        vars->i320 = 0;
        vars->i324 = 0;
        vars->b48 = FloatToInt(15.0f);
        vars->b4A = FloatToInt(4.0f);
        vars->b29 = 1;
        vars->b70 = 6;
        vars->iA8 = 3;
        vars->b71 = 9;
        vars->b72 = 9;
        vars->b76 = 10;
        vars->b77 = 11;
        vars->f7C = 0.10000001f;
        vars->f80 = 0.050000004f;
        vars->f84 = 0.0030555557f;
        vars->f88 = 0.0030555557f;
        vars->f8C = 0.00055555557f;
        vars->f90 = 0.35f;
        vars->f94 = 0.35f;
        vars->f9C = 0.4f;
        vars->bCC = 6;
        vars->bCD = 11;
        vars->bCE = 6;
        vars->bCF = 11;
        vars->bD2 = 6;
        vars->bD3 = 11;
        MoveCtl_Init(&vars->t140);
        vars->t140.f0C = 2.5f;
        vars->t140.f08 = 2.0f;
        vars->t140.i00 = FloatToInt(D_L04_001B1870 * 1024.0f);
        vars->t140.f04 = D_L04_001B1870;
        vars->t140.f24 = vars->f30C * (1.0f / 60.0f);
        if (vars->v2E0.f[3] != 12439.4f) {
            vars->v2E0.q = *(Quad *)(obj + 0x10);
            vars->v2E0.f[3] = 12439.4f;
        }
        qcopy(&vars->v110, &vars->v2E0);
        vars->f120 = 0.5f;
        vars->h300 = RandomIntRange(120, 700);
        vars->i31C = 0;
        CopyHeroField38ToMoby(obj);
        vars->f230 = F(obj, 0x2C);
        vars->f220 = vars->f30;
        vars->b28 = 0;
        vars->i318 = 0;
        vars->p200 = D_L04_001B1880;
        vars->f330 = (float)vars->b34;
        SetMobyState(obj, 1, 0);
        if (obj[0x43])
            StartAnimationBlended(obj, 0, 0, 0);
    }
    if (obj[0x31] && fast_vec_dist(obj + 0x10, D_L04_001B9680) < 24.0f) {
        UpdateMobyGroundCheck(obj);
        obj[0x6F] = 22;
    }
    hit = (u8 *)FindOwnedEffectSlot(obj, 0x230000, 0);
    if (hit && hit[0x28] == 8) {
        obj[0x20] = 8;
        obj[0xBC] = 4;
    }
    result = ApplyDamageToObject(obj, vars->ai, 0);
    if (result) {
        if (result == 5) {
            vars->iF0 = 0;
            vars->fF4 = 0.8377582f;
        }
        FlagHoundsInGroup(obj);
    }
    SelectAimTarget_002B3BA8(obj, -1, &vars->v2E0, 0, vars->f2F4, 10.0f);
}
