#include "common.h"
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern float D_L12_001B09F8 __attribute__((sda));
extern int D_L12_001B09F4 __attribute__((sda));
extern u8 *D_L12_001B2F8C[] __attribute__((sda));
extern u8 D_L12_001B9E00[];
extern void func_002B60B0(void *, float, float, float, float);
extern void func_00282CF0(void *, void *, void *), func_00283098(void *, void *, void *);
extern int func_L02_0032E508(void *, int, void *, int);
extern void func_002A7470(void *, int, int, int), func_002A93B0(void *);
extern float func_00282E48(void *, void *);
extern void func_002B0ED8(void *, void *, int), func_L00_002E6EF8(void (*)(u8 *), void *);
extern void func_L12_003E0B68(u8 *);

typedef struct TodanoInitState {
    u8 pad0[0x28];
    u8 f28;
    u8 pad29[0x47];
    u8 f70;
    u8 f71;
    u8 f72;
    u8 pad73[0x3];
    u8 f76;
    u8 f77;
    u8 pad78[0x4];
    float f7C;
    float f80;
    float f84;
    float f88;
    float f8C;
    float f90;
    float f94;
    u8 pad98[0x4];
    float f9C;
    u8 padA0[0x8];
    int fA8;
    u8 padAC[0x20];
    u8 fCC;
    u8 fCD;
    u8 fCE;
    u8 fCF;
    u8 padD0[0x2];
    u8 fD2;
    u8 fD3;
    u8 padD4[0x43C];
    int f510;
    u8 pad514[0x4];
    int f518;
    u8 pad51C[0x34];
    float f550;
    float f554;
    float f558;
    float f55C;
    float f560;
    u8 pad564[0x18];
    float f57C;
    float f580;
    float f584;
    int f588;
    int f58C;
    u8 pad590[8];
    u8 *f598, *f59C;
    u8 pad5A0[0x1F0];
    int f790;
} TodanoInitState;

typedef struct TodanoInitObject {
    u8 pad0[0x20];
    u8 f20;
    u8 pad21[0xF];
    u8 f30;
    u8 f31;
 u16 f32;
 u16 f34;
    u8 pad36[0xD];
    u8 f43;
    u8 pad44[0x24];
    TodanoInitState *f68;
    u8 pad6C[0x3];
    u8 f6F;
    u8 pad70[0xC];
 u16 f7C;
    u8 pad7E[0x1A];
    int f98;
} TodanoInitObject;

/* Sets up a Todano creature on its first frame (health, speeds, animation) and then handles
   its hits and its death each frame. */
void func_L12_003E04B8(TodanoInitObject *moby) {
    TodanoInitState *vars = moby->f68;
    if (!moby->f20) {
        int kind;
        moby->f7C = 1 << RandomIntBelow(6);
        kind = 3;
        vars->fCC = kind;
        vars->fCE = kind;
        vars->fA8 = kind;
        vars->f70 = 9;
        vars->f71 = 8;
        vars->f72 = 8;
        vars->f76 = 9;
        vars->f77 = 10;
        vars->f7C = 0.100000009f;
        vars->f80 = 0.0666666701f;
        vars->f84 = 0.00416666688f;
        vars->f88 = 0.00833333377f;
        vars->f8C = 0.00416666688f;
        vars->f90 = 0.5f;
        vars->f94 = 0.5f;
        vars->f9C = 0.4f;
        vars->fCD = 6;
        vars->fCF = 6;
        vars->fD2 = 13;
        vars->fD3 = 26;
        vars->f28 = kind;
        moby->f30 = 200;
        moby->f32 = 200;
        vars->f584 = 0.25f;
        vars->f554 = D_L12_001B09F8;
        vars->f550 = 0.3f;
        vars->f558 = 1;
        vars->f55C = 1;
        vars->f580 = 0.261799425f;
        vars->f57C = 0.00555555569f;
        vars->f58C = -1;
        vars->f560 = 3.14159012f;
        vars->f588 |= 1;
        SetControllerSpeedLimits(moby, 0.00333333341f, 0.100000009f, 0.00349065894f, 0.209439546f);
        qcopy((u8 *)vars + 0x760, (u8 *)moby + 0x10);
        FastVecSub((u8 *)vars + 0x770, (u8 *)moby + 0x10, D_L12_001B2F8C[0] + (vars->f518 << 7) + 0x30);
        matrix_mul_vec3((u8 *)vars + 0x770, (u8 *)vars + 0x770, D_L12_001B2F8C[0] + (vars->f518 << 7) + 0x40);
        vars->f598 = (u8 *)vars + 0x6C0;
        vars->f59C = (u8 *)vars + 0x640;
        vars->f790 = BuildRouteNodes(moby, vars->f510, (u8 *)vars + 0x110, 32);
        moby->f98 = 0;
        moby->f34 = (moby->f34 | 0x41) & 0xEFFF;
        SetMobyState(moby, 1, 0);
        if (moby->f43)StartAnimationBlended(moby, 0, 0, 0);
        D_L12_001B09F4 = 0;
    }
    if (moby->f31 && fast_vec_dist((u8 *)moby + 0x10, D_L12_001B9E00) < 24) {
        UpdateMobyGroundCheck(moby);
        moby->f6F = 22;
    }
    ApplyDamageToObject(moby, (u8 *)vars + 0x60, 0);
    if (moby->f20 != 8 && moby->f20 != 1)AddDrawCallbackToList3(AddTwoGlowSprites, moby);
}
