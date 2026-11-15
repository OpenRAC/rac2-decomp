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
extern Hit D_L00_001BF200;
extern char D_L00_001BF220[];
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

/* Finds the ground under the hero, and records its slope, height and what it is made of. It also checks the ground at the sides. */
void func_L00_002B4900(void) {
    Vec4 rayEnd, rayStart, scratchVec, sideStart, sideEnd, sideSlope, sideNormal;
    s32 surfaceType;
    s32 i;
    f32 angle;
    u8 *data;
    Vec4 *normal;
    HeroGround *hero;

    s32 probeMode;
    f32 probeDepth;

    gHeroState.xF278 = 1.0f;
    gHeroState.u30e.U++;
    gHeroState.u30c.U++;
    gHeroState.xI270 = 0;
    gHeroState.xI274 = 0;
    gHeroState.u2e0.I = 0;
    gHeroState.u2d8.I = 0;
    ClearVector128((u8 *)&gHeroState + 0x2D0);
    gHeroState.xH30a = 0;
    gHeroState.xF2dc = 32.0f;
    gHeroState.xI2fc = 0;
    if (gHeroState.xI2f8 != 0) {
        gHeroState.xI2f8++;
    }
    probeMode = 1;
    probeDepth = gHeroState.xF234 * 2.2f;
    if (gHeroState.xI208c == 2) {
        probeDepth = gHeroState.xF234 * 2.9f;
    }
    if (IsHeroInSpecialKindOrMode()) probeDepth = 0.0f;
    BuildOffsetVectorPair(&rayStart, &rayEnd, probeMode, probeDepth, -48.0f);
    if (CollLine(&rayStart, &rayEnd, 2, gHeroState.xI2080, 0) == 0) {
        goto tail;
    }
    surfaceType = func_L00_002E2048();

    gHeroState.xB12ed = surfaceType;
    if (gCollisionResult.i18 != 0) gHeroState.xB12ed = 0;
    if (gCurrentMapIndex == 7 && gCollisionResult.i18 != 0) gHeroState.xB12ed = 1;
    gHeroState.xH12e0 = GetCollHitMaterial();
    if (gHeroState.xH12e0 == 0) {
        gHeroState.xF2f0 = GetGroundHeightAtPosition(D_L00_001BF220, (u8 *)&gHeroState + 0x2B0);
        if (gHeroState.xF88 < gHeroState.xF2f0 && gHeroState.xI2f8 <= 0) {
            gHeroState.xI2f8 = 1;
        }
        if (CollLine(&rayStart, &rayEnd, 0x24, gHeroState.xI2080, 0) == 0) {
            goto tail;
        }
        surfaceType = func_L00_002E2048();
        gHeroState.xB12ed = surfaceType;
    }
    if (gHeroState.xH12e0 == 0xD) {
        gHeroState.xF2f0 = gCollisionResult.v20.f[2];
        rayStart.f[2] = gCollisionResult.v20.f[2] - 0.01f;
        if (CollLine(&rayStart, &rayEnd, 4, gHeroState.xI2080, 0) == 0) {
            goto tail;
        }
    }
    if (gHeroState.xH12e0 == 3) {
        gHeroState.xF2f4 = gCollisionResult.v20.f[2];
        rayStart.f[2] = gCollisionResult.v20.f[2] - 0.01f;
        if (CollLine(&rayStart, &rayEnd, 4, gHeroState.xI2080, 0) == 0) {
            goto tail;
        }
    }
    if (gHeroState.xH12e0 == 0xB) {
        gHeroState.xF2f4 = gCollisionResult.v20.f[2];
        goto tail;
    }
    if (gHeroState.xH12e0 == 1 && (u32)(gHeroState.xI2084 - 0x79) < 2) {
        goto tail;
    }
    if (gCollisionResult.i18 != 0) {
        if (IsMobyInSpecialClassRange(gCollisionResult.i18)) {
            gHeroState.xH30a = 1;
        }
        data = GetMobyPrivateValue0(gCollisionResult.i18);
        if (data != 0 && (*(u16 *)(data + 0x1E) & 8)) {
            gHeroState.xH30a = 1;
        }
        data = GetMobyPrivateValue2(gCollisionResult.i18);
        if (data != 0 && (*(int *)(data + 0x3c) & 8)) gHeroState.xH30a = 1;
    }
    if (gCollisionResult.i1C > 0) {
        qcopy((u8 *)&gHeroState + 0x2D0, &gCollisionResult.v20);
        gHeroState.u2d8.F = gCollisionResult.v20.f[2];
        if (D_001A8FF0) gHeroState.u2d8.F = GetDistanceFromGravityCenter(&gCollisionResult.v20);
        gHeroState.xF2dc = fast_vec_dist((u8 *)&gHeroState + 0x80, ((u8 *)&gHeroState + 0x2D0));
        gHeroState.xI2fc = gCollisionResult.i18;
        func_001290E0((u8 *)&gHeroState + 0x2A0, (u8 *)&gCollisionResult.f40);
        gHeroState.u2e0.F = GetViewSpaceAngle((u8 *)&gCollisionResult.f40);
        gHeroState.xF2ec = FastMatrixHelperA(gCollisionResult.f40, gCollisionResult.f44);
        FastVecSub(&scratchVec, ((u8 *)&gHeroState + 0x2D0), (u8 *)&gHeroState + 0x80);
        if (0.0f < FastVecDot(&scratchVec, (u8 *)&gHeroState + 0x2A0)) {
            gHeroState.xF2dc = -gHeroState.xF2dc;
        }
        if (gHeroState.xF2dc < 0.02f) {
            gHeroState.u30c.H = 0;
            if (gHeroState.u2e0.F <= 0.87266469f || gHeroState.xB20b3 != 0) {
                gHeroState.u30e.H = 0;
                gHeroState.xIa80 = gCollisionResult.i18;
            }
        }
    }
tail:
    if (gHeroState.xF88 > gHeroState.xF2f0) gHeroState.xI2f8 = 0;
    if (gHeroState.u30e.H != 0) gHeroState.xI300 = 0;
    else {
        gHeroState.xI300++;
        *(Q *)((u8 *)&gHeroState + 0x2E0) = *(Q *)((u8 *)&gHeroState + 0x2D0);
        if (gHeroState.xI2084 != 0x38) gHeroState.field18c0 = 0;
    }
    normal = (Vec4 *)((u8 *)&gHeroState + 0x2C0);
    ClearVector128(normal);
    hero = (HeroGround *)((u8 *)normal - 0x2C0);
    switch (hero->xB20b3) {
    case 0:
        hero->xF298 = -1.0f;
        break;
    case 1:
        if (D_001A8FF4) ComputeFlatDirectionFromPoint((u8 *)normal - 0x240, normal, 0);
        else if (*(float *)((u8 *)hero + 0x2fc) != 0.0f) {
            ApproachValue((float *)((u8 *)normal + 0x3c), 0.0f, 1.0f);
            qcopy(normal, (u8 *)normal + 0x30);
        } else {
            qcopy(normal, (u8 *)normal - 0x20);
            FastVecScale(normal, normal, -1.0f);
        }
        break;
    case 2:
        angle = -1.0f;
        if (*(float *)((u8 *)hero + 0xbc) > 0.0f) angle = 1.0f;
        FastVecSub(normal, (u8 *)normal - 0x210, (u8 *)normal - 0x240);
        vec_scale_to_length(normal, normal, angle);
        break;
    }
    gHeroState.u2e4.I = 0;
    gHeroState.u2e8.I = 0;
    gHeroState.a2d0.i[0] = 0;
    gHeroState.a2d0.i[1] = 0;
    gHeroState.a2c8.i[0] = 0;
    gHeroState.a2c8.i[1] = 0;
    gHeroState.a2c0.i[0] = 0;
    gHeroState.a2c0.i[1] = 0;
    if (!(gHeroState.xF2dc < 0.25f)) {
        return;
    }
    if (!(gHeroState.xI208c == 0 || gHeroState.xI208c == 12 || gHeroState.xI208c == 9 || gHeroState.xI208c == 7 || (gHeroState.xI208c == 4 && *(u8 *)((u8 *)&gHeroState + 0x49c)) || gHeroState.xI208c == 1)) {
        return;
    }
    ComputeAnglesToHeroLocalDirection((u8 *)&gHeroState + 0x2A0, &scratchVec);
    if (-0.785398244f < scratchVec.f[1] && scratchVec.f[1] < 0.785398244f) {
        gHeroState.u2e4.F = scratchVec.f[1];
    }
    if (-0.785398244f < scratchVec.f[0] && scratchVec.f[0] < 0.785398244f) {
        gHeroState.u2e8.F = scratchVec.f[0];
    }
    for (i = 0; i < 2; i++) {
        angle = 1.57079649f;
        if (i == 1) {
            angle = -angle;
        }
        BuildHeroRelativeOffset(&sideStart, 0.2f, angle, 0.45f, 1);
        BuildHeroRelativeOffset(&sideEnd, 0.2f, angle, -0.45f, 1);
        if (CollLine(&sideStart, &sideEnd, 0x22, gHeroState.xI2080, 0)) {
            if (D_001A8FF0) gHeroState.a2c0.f[i] = GetDistanceFromGravityCenter(&gCollisionResult.v20) - GetDistanceFromGravityCenter((u8 *)&gHeroState + 0x2d0);
            else gHeroState.a2c0.f[i] = gCollisionResult.v20.f[2] - gHeroState.u2d8.F;
            if (0.4f < FloatAbs(gHeroState.a2c0.f[i])) {
                gHeroState.a2c0.f[i] = 0.0f;
            }
            func_001290E0(&sideNormal, (u8 *)&gCollisionResult.f40);
            ComputeAnglesToHeroLocalDirection(&sideNormal, &sideSlope);
            if (-0.785398244f < sideSlope.f[1] && sideSlope.f[1] < 0.785398244f) {
                gHeroState.a2c8.f[i] = sideSlope.f[1];
            }
            if (-0.785398244f < sideSlope.f[0] && sideSlope.f[0] < 0.785398244f) {
                gHeroState.a2d0.f[i] = sideSlope.f[0];
            }
        } else {
            gHeroState.a2c0.i[i] = 0;
            gHeroState.a2c8.f[i] = gHeroState.u2e4.F;
            gHeroState.a2d0.f[i] = gHeroState.u2e8.F;
        }
    }
}
