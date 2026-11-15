/* -G16 -Wa,-G16 lets the two 9-byte state-transition tables (nw + old * 3) take retail's $gp form.
 * Both func_0029F338(self); return; tails are written out: jump2 cross-jumps them after sched2, and
 * until then the second a0 set in case 14's block gives a0 = self its extra dependent. */
#include "common.h"
#define NULL ((void *)0)
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; Quad q[0x260]; } Hero;
typedef struct { Vector pos, v30, v40, v50; void *obj; int kind; } Hit;
extern char D_00189E20[];
extern char D_00189EA0[];
extern u8 *D_0018C0B0 __attribute__((nosda));
extern s16 D_0018A16C __attribute__((nosda));
extern int D_L06_001B2348[] __attribute__((sda));
extern int D_L06_001B2FB8[] __attribute__((sda));
extern u8 D_L06_001BFCA0[];
extern char D_L06_001B1A68[], D_L06_001B1AA0[];
extern u8 *D_L06_001B281C __attribute__((sda));
extern int D_L06_001B2FB0 __attribute__((sda));
extern u8 D_L06_001B1970[9] __attribute__((sda));
extern u8 D_L06_001B1980[9] __attribute__((sda));
extern void func_0026FEB8(const char *, ...);
extern int func_00277258(void *, int, void *, float);
extern int func_00278E78(void);
extern int func_00282948(void *);
extern float func_00282C48(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern int func_00283CF0(float);
extern void func_0029F338(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7470(void *, int, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_002A7CA0(void *, float, void *, float, float, float);
extern int func_002A7EA0(void *, void *, void *, float, float, float, float, int);
extern int func_002A8AF0(void *, void *, int);
extern float func_002A90F8(void *, void *);
extern void func_002AB8C0(void *, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002C19D8(void *, void *, int, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_L00_002C42E0(int, int);
extern void func_L00_00410D18(void *, void *, void *);
extern float func_L01_00310BC0(void *, float, float, float, float, float);
extern int func_L04_0033CB08(void *, void *, int, int, float, float);
extern int func_001163B0(void);
extern int func_L06_0035EA68(void *, void *);
extern void func_L06_00361728(void *, void *, float);
extern void func_L06_003660F0(void *, int, void *, float);
extern int func_L06_00459BA8(void *, void *);
extern void func_L06_00459C38(void *, void *);
extern int func_L06_00459D08(void *, void *);
extern void func_L06_00459EC0(void *, void *);
extern void func_L06_0045A0D0(void *, void *, float, float, float);
extern int func_L06_0045A1B0(void *, void *, float, float, float, float, float, float, float);
extern void func_L06_0045A2D8(void *, void *, int, int, float, float, float, float, float, int, int, int, void *);
extern int func_L06_0045A490(void *, void *, float);
extern int func_L06_0045A500(void *, int, int);

#define B(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define UH(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(int *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))

/* Updates a Notak walking creature: it wanders, chases the player when it spots them, grabs and carries them, and removes itself if it leaves the map. */
void func_L06_0045A5B0(u8 *self) {
    Hit hit;
    Vector vecHead, vecDelta, vecTmp1, vecTmp2, vecPrevPos, vecTarget;
    u8 *vars;
    u8 *pathData;
    float *unusedPtr;
    u8 *selfPosA, *selfPosB, *selfPosC, *velA, *velB, *velC, *velD, *velE;
    int rayHit, timerExpired, closeEnough, tableIdx;
    u8 nextAnim, nextState;
    u8 oldMode;
    int curIndex;
    int newMode;
    float floatA, floatB, floatC;

    if (self != NULL && (vars = *(u8 **)(self + 0x68)) != NULL) {
        UpdateAttachedEffectScale(self, 0, vars + 0x140, 2.20000005f);
        if (B(self, 0x20) == 0) {
            if (ResolveSpawnRecordLinks(self, vars) != 0) {
                STUB_printf(D_L06_001B1A68, H(self, 0xB2));
                MarkMobySpawned(self);
                return;
            }
            goto check;
        }
        FindNearestTargetForMoby(self, &hit, 30.0f);
        EmptyMobyUpdate(self, vars, vars + 0x20);
        UpdateColorFade(self, vars + 0x50);
        timerExpired = FastFloatHelperD(vars + 0x124) != 0;
        if (W(vars, 0x100) != 0 && B(self, 0x20) >= 7) {
            pathData = *(u8 **)(vars + 0x138);
            rayHit = point_in_path_xy(&hit, pathData + 0x10, *(int *)pathData) != 0;
        } else {
            pathData = *(u8 **)(vars + 0x138);
            rayHit = point_in_path_xy(gHeroPosition, pathData + 0x10, *(int *)pathData) != 0;
            if (vec_distance_xy(self + 0x10, gHeroPosition) < 30.0f) {
                hit.obj = *(void **)(gHeroPosition + 0x2210);
                qcopy(&hit.pos, gHeroPosition);
                qcopy(&hit.v30, gHeroPosition + 0x10);
                qcopy(&hit.v40, gHeroPosition + 0x50);
                qcopy(&hit.v50, gHeroPosition + 0x60);
                hit.kind = 0;
            } else {
                hit.obj = NULL;
                qzero(&hit.pos);
                qzero(&hit.v30);
                qzero(&hit.v50);
                qzero(&hit.v40);
                hit.kind = 2;
            }
        }
        if (W(vars, 0x100) != 0) {
            pathData = *(u8 **)(vars + 0x118);
            point_in_path_xy(self + 0x10, pathData + 0x10, *(int *)pathData);
        }
        oldMode = B(self, 0xBC);
        nextState = 0xFF;
        newMode = ClassifyHeadroomSize(self, vars);
        nextAnim = 0xFF;
        B(self, 0xBC) = newMode;
        if (oldMode != (u8)newMode) {
            tableIdx = (u8)newMode + oldMode * 3;
            nextState = D_L06_001B1970[tableIdx];
            nextAnim = D_L06_001B1980[tableIdx];
        }
        TransformMobyJointToWorld(self, 0, vecHead.f);
        if (TestPointAgainstCollision(vecHead.f, 1, self, 0.800000012f) != 0 && GetCollHitMaterial() == 0) {
            floatA = **(float **)(vars + 0x11C);
            floatA -= F(vars, 0x120);
            floatA *= 0.5f;
            if (floatA < FloatAbs(F(self, 0x18) - vecHead.f[2])) {
                floatA = (**(float **)(vars + 0x11C) - F(vars, 0x120)) * 0.5f;
            } else {
                floatA = FloatAbs(F(self, 0x18) - vecHead.f[2]);
            }
            if (F(vars, 0xC8) < 0.0f) {
                floatA = -floatA;
            }
            if (B(self, 0x20) == 0xE || B(self, 0x20) == 0xC) {
                floatA *= 2.0f;
            }
            selfPosA = self + 0x10;
            if (vec_distance_xy(selfPosA, D_L06_001BFCA0) > 0.5f) {
                floatB = vec_distance_xy(selfPosA, D_L06_001BFCA0) * 2.0f;
            } else {
                floatB = 1.0f;
            }
            if (D_L06_001B2348[0] % 45 == H(self, 0xB2) && RandomIntBelow(2) == 0) {
                RippleDisturb(D_L06_001B2FB0, D_L06_001B2FB8[0], 1, F(self, 0x10), F(self, 0x14), floatB, floatA);
            }
            if (D_L06_001B2348[0] % ((Rand() & 7) + 0x14) == 0) {
                floatC = RandomFloatRange(1.5f, 2.4000001f);
                vecHead.f[0] += RandomFloatRange(-0.150000006f, 0.150000006f);
                vecHead.f[1] += RandomFloatRange(-0.150000006f, 0.150000006f);
                vecHead.f[2] = GetGroundHeightAtPosition(D_L06_001BFCA0, NULL);
                SpawnDriftingParticle_002C19D8(vecHead.f, NULL, -1, floatC, 5250.0f);
            }
        }
        if (F(vars, 0x13C) >= 1.0f) {
            *(Quad *)gHeroPosition = *(Quad *)(self + 0x10);
        }
        curIndex = W(vars, 0x108);
        if (curIndex != -1 && B(*(u8 **)(D_L06_001B281C + (curIndex << 8) + 0x68), 0x14) != 0) {
            if (B(self, 0x43) != 0xD) {
                StartAnimationBlended(self, 0xD, 0, 0xA);
            }
            B(self, 0x20) = 0x14;
        }
        switch (B(self, 0x20)) {
        case 0:
            STUB_printf(D_L06_001B1AA0);
            break;
        case 20:
            curIndex = W(vars, 0x108);
            if (curIndex != -1 && B(*(u8 **)(D_L06_001B281C + (curIndex << 8) + 0x68), 0x14) == 0) {
                B(self, 0x20) = 0x15;
            }
            break;
        case 21:
            if (UH(self, 0x96) >= 0x168) {
                if (B(self, 0x43) != 0) {
                    StartAnimationBlended(self, 0, 0, 0xA);
                }
                UH(self, 0x96) = 0;
                B(self, 0x20) = 1;
            } else {
                ApplyFallAndMove(self, vars, 0.00416666688f, 0.013888889f, 0.13333334f);
                UH(self, 0x96) = UH(self, 0x96) + 1;
            }
            break;
        case 1:
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 0) {
                StartAnimationBlended(self, 0, 0, 0xA);
            }
            if (rayHit != 0 && hit.obj != NULL && hit.obj == gHeroMoby_0018C0B0 && IsGroupMemberInStateRange(self, 4, 6) == 0) {
                if (B(self, 0x43) != 1) {
                    StartAnimationBlended(self, 1, 0, 0xA);
                }
                B(self, 0x20) = 4;
            }
            if (hit.obj != NULL && hit.obj == gHeroMoby_0018C0B0 && ProbeHitsTarget(self, hit.obj, 1.5f) != 0) {
                if (B(self, 0x43) != 2) {
                    StartAnimationBlended(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                B(self, 0x20) = 5;
            } else if (timerExpired != 0) {
                if (B(self, 0x43) != 1) {
                    StartAnimationBlended(self, 1, 0, 0xA);
                }
                W(vars, 0x124) = Rand() % 200 + 0x12C;
                F(vars, 0x12C) = RandomAngle();
                B(self, 0x20) = 2;
            }
            FastVecScale(vars + 0xC0, vars + 0xC0, 0.949999988f);
            ApplyFallAndMove(self, vars, 0.00416666688f, 0.013888889f, 0.13333334f);
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 2:
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 1) {
                StartAnimationBlended(self, 1, 0, 0xA);
            }
            if (rayHit != 0 && hit.obj != NULL && hit.obj == gHeroMoby_0018C0B0) {
                if (IsGroupMemberInStateRange(self, 4, 6) == 0) {
                    if (B(self, 0x43) != 1) {
                        StartAnimationBlended(self, 1, 0, 0xA);
                    }
                    B(self, 0x20) = 4;
                }
            } else {
                MobySpringTurn(self, F(vars, 0x12C), vars + 0x110, 0.000484813732f, 0.00126051577f, 0.029088825f);
                F(self, 0xF4) = TurnAngleTowardTarget(vars + 0x114, F(self, 0xF4), 0.0f, 0.000484813732f, 0.00126051577f, 0.029088825f);
                if (timerExpired != 0 && IsPointInCuboid(self + 0x10, W(vars, 0x104)) != 0) {
                    if (B(self, 0x43) != 0) {
                        StartAnimationBlended(self, 0, 0, 0xA);
                    }
                    W(vars, 0x124) = Rand() % 120 + 0x3C;
                    B(self, 0x20) = 1;
                }
            }
            ChooseFreeHeading(self, vars);
            if (AdjustSpeedTowardFacing(self, vars, F(vars, 0x12C), 0.209439531f, 0.00166666671f, 0.52359885f, 0.00111111114f, 0.116666675f, 0.0500000045f) != 0 && timerExpired != 0) {
                if (B(self, 0x43) != 0) {
                    StartAnimationBlended(self, 0, 0, 0xA);
                }
                W(vars, 0x124) = Rand() % 120 + 0x3C;
                B(self, 0x20) = 1;
            }
            if (hit.obj != NULL && hit.obj == gHeroMoby_0018C0B0 && ProbeHitsTarget(self, hit.obj, 1.5f) != 0) {
                if (B(self, 0x43) != 2) {
                    StartAnimationBlended(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                B(self, 0x20) = 5;
            }
            ApplyFallAndMove(self, vars, 0.00416666688f, 0.013888889f, 0.13333334f);
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 4:
            selfPosB = self + 0x10;
            closeEnough = 1;
            floatC = FastMatrixHelperA(hit.pos.f[0] - F(self, 0x10), hit.pos.f[1] - F(self, 0x14));
            MobySpringTurn(self, floatC, vars + 0x110, 0.00349065894f, 0.0f, 0.209439546f);
            { float t = -FastMatrixHelperA(vec_distance_xy(selfPosB, &hit), hit.pos.f[2] - F(self, 0x18));
            F(self, 0xF4) = TurnAngleTowardTarget(vars + 0x114, F(self, 0xF4), t, 0.00349065894f, 0.0f, 0.209439546f); }
            if (vec_distance_xy(selfPosB, gHeroPosition) < 3.0f) {
            } else {
                closeEnough = 0;
            }
            if (closeEnough != 0) {
                FastVecScale(vars + 0xC0, vars + 0xC0, 0.899999976f);
            }
            if (AdjustSpeedTowardFacing(self, vars, floatC, 0.209439531f, 0.00555555569f, 0.52359885f, 0.000833333354f, 0.333333343f, 0.0833333358f) != 0 && closeEnough != 0 && (u32)(W(gHeroPosition, 0x221C) - 0x11) < 2) {
                if (B(self, 0x43) != 2) {
                    StartAnimationBlended(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                W(self, 0x98) = 0;
                B(self, 0x20) = 5;
                F(vars, 0x13C) = 0.0f;
                qcopy(vars + 0xF0, selfPosB);
            }
            F(vars, 0x128) = hit.pos.f[2] - 0.25f;
            ApplyFallAndMove(self, vars, 0.010555556f, 0.0f, 0.633333385f);
            if (rayHit == 0 || D_0018A16C == 0) {
                if (B(self, 0x43) != 1) {
                    StartAnimationBlended(self, 1, 0, 0xA);
                }
                B(self, 0x20) = 2;
            }
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 5:
            selfPosC = self + 0x10;
            TransformMobyJointToWorld(self, 0, vecHead.f);
            FastVecSub(&vecDelta, vecHead.f, selfPosC);
            floatB = FastMatrixHelperA(hit.pos.f[0] - vecHead.f[0], hit.pos.f[1] - vecHead.f[1]);
            MobySpringTurn(self, floatB, vars + 0x110, 0.00349065894f, 0.0f, 0.209439546f);
            F(self, 0xF4) = F(self, 0xF4) * 0.699999988f;
            F(vars, 0x13C) = F(vars, 0x13C) + 0.0280000009f;
            qcopy(&vecPrevPos, selfPosC);
            FastVecSub(&vecTmp1, &hit, &vecDelta);
            FastVecSub(&vecTmp2, &vecTmp1, vars + 0xF0);
            FastVecScale(&vecTmp2, &vecTmp2, F(vars, 0x13C) < 1.0f ? F(vars, 0x13C) : 1.0f);
            FastVecAdd(&vecTarget, &vecTmp2, vars + 0xF0);
            MoveOverGround(self, selfPosC, &vecTarget, 0.75f, 0.75f, 40.0f, 6.28318596f, 3);
            FastVecSub(vars + 0xC0, selfPosC, &vecPrevPos);
            if (F(vars, 0x13C) >= 1.0f) {
                ((Hero *)gHeroState)->i[0x24CC / 4] = 0;
                SetHeroAction_L00(0x39, 1);
                W(((Hero *)gHeroState)->ptr[0x2290 / 4], 0x9C) = -1;
                ((Hero *)gHeroState)->b[0x22B5] = 1;
                B(self, 0x20) = 6;
            } else {
                F(vars, 0x12C) = floatB;
            }
            break;
        case 6:
            ChooseFreeHeading(self, vars);
            AdjustSpeedTowardFacing(self, vars, F(vars, 0x12C), 0.209439531f, 0.00166666671f, 0.52359885f, 0.00111111114f, 0.116666675f, 0.0500000045f);
            ApplyFallAndMove(self, vars, 0.00333333341f, 0.013888889f, 0.116666675f);
            MobySpringTurn(self, F(vars, 0x12C), vars + 0x110, 0.000436332368f, 0.000872664736f, 0.0523598865f);
            F(self, 0xF4) = TurnAngleTowardTarget(vars + 0x114, F(self, 0xF4), 0.0f, 0.000436332368f, 0.000872664736f, 0.0523598865f);
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 1) {
                StartAnimationBlended(self, 1, 0, 0xA);
            }
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 7:
            if (rayHit != 0) {
                if (B(self, 0x43) != 4) {
                    StartAnimationBlended(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 9;
            } else if (timerExpired != 0) {
                if (B(self, 0x43) != 4) {
                    StartAnimationBlended(self, 4, 0, 0xA);
                }
                W(vars, 0x124) = Rand() % 200 + 0x12C;
                F(vars, 0x12C) = RandomAngle();
                B(self, 0x20) = 8;
            }
            velA = vars + 0xC0;
            FastVecScale(velA, velA, 0.949999988f);
            F(vars, 0xC8) = F(vars, 0xC8) - 0.163333341f;
            if (BlendWithScaledCount(self, velA, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(velA, velA, 0.5f);
            }
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 8:
            if (rayHit != 0) {
                if (B(self, 0x43) != 4) {
                    StartAnimationBlended(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 9;
            } else {
                MobySpringTurn(self, F(vars, 0x12C), vars + 0x110, 0.000218166184f, 0.000436332368f, 0.0130899716f);
                F(self, 0xF4) = TurnAngleTowardTarget(vars + 0x114, F(self, 0xF4), 0.0f, 0.000218166184f, 0.000436332368f, 0.0130899716f);
                if (timerExpired != 0 && IsPointInCuboid(self + 0x10, W(vars, 0x104)) != 0) {
                    if (B(self, 0x43) != 3) {
                        StartAnimationBlended(self, 3, 0, 0xA);
                    }
                    W(vars, 0x124) = Rand() % 120 + 0x3C;
                    B(self, 0x20) = 7;
                }
            }
            ChooseFreeHeading(self, vars);
            if (AdjustSpeedTowardFacing(self, vars, F(vars, 0x12C), 0.3490659f, 0.000833333354f, 1.0471977f, 0.00249999994f, 0.0166666675f, 0.0166666675f) != 0 && timerExpired != 0) {
                if (B(self, 0x43) != 3) {
                    StartAnimationBlended(self, 3, 0, 0xA);
                }
                W(vars, 0x124) = Rand() % 120 + 0x3C;
                B(self, 0x20) = 7;
            }
            velB = vars + 0xC0;
            F(vars, 0xC8) = F(vars, 0xC8) - 0.163333341f;
            if (BlendWithScaledCount(self, velB, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(velB, velB, 0.5f);
            }
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 9:
        case 10:
            floatA = FastMatrixHelperA(hit.pos.f[0] - F(self, 0x10), hit.pos.f[1] - F(self, 0x14));
            MobySpringTurn(self, floatA, vars + 0x110, 0.000218166184f, 0.000436332368f, 0.0130899716f);
            if (AdjustSpeedTowardFacing(self, vars, floatA, 0.52359885f, 0.00111111114f, 1.57079649f, 0.00249999994f, 0.0250000022f, 0.0166666675f) != 0 && vec_distance_xy(self + 0x10, &hit) < 1.89999998f && B(self, 0x20) != 0xA) {
                if (B(self, 0x43) != 5) {
                    StartAnimationBlended(self, 5, 0, 2);
                }
                B(self, 0x20) = 0xA;
            }
            velC = vars + 0xC0;
            F(vars, 0xC8) = F(vars, 0xC8) - 0.163333341f;
            if (BlendWithScaledCount(self, velC, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(velC, velC, 0.5f);
            }
            B(vars, 0x48) = FloatToInt(8.0f);
            B(vars, 0x4A) = FloatToInt(9.60000038f);
            if (rayHit == 0) {
                if (B(self, 0x43) != 4) {
                    StartAnimationBlended(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 8;
            }
            TryPickupTransition(self, vars, 0xA, 5, 17.0f, 20.0f, 1.0f, 1.0f, 1.0f, 4, 4, 0xB, hit.obj);
            if (B(self, 0x60) & 2) {
                if (B(self, 0x43) != 4) {
                    StartAnimationBlended(self, 4, 0, 0xA);
                }
                W(vars, 0x124) = Rand() % 200 + 0x12C;
                B(self, 0x20) = 8;
            }
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 11:
            if (B(self, 0x60) & 2) {
                B(self, 0x20) = 7;
            }
            break;
        case 12:
            if (mine_fall(self, vars + 0x60) & 1) {
                StartAnimationForSizeClass(self, vars);
            }
            break;
        case 13:
            if (B(self, 0x60) & 2) {
                StartAnimationForSizeClass(self, vars);
            }
            break;
        case 14:
            if (mine_fall(self, vars + 0x60) & (B(self, 0x60) & 2)) {
                SpawnExplosionEffects(self, vars + 0xC0, NULL, 0.0f, 0.0f, 3, 3, 5, 2.0f, 1.0f, 4.0f, 1.0f, -1, 7.0f, 0, 1, -1, 0, 0x810001);
                MarkMobySpawned(self);
                return;
            }
            break;
        case 16:
            velD = vars + 0xC0;
            FastVecScale(velD, velD, 0.949999988f);
            F(vars, 0xC8) = F(vars, 0xC8) - 0.163333341f;
            BlendWithScaledCount(self, velD, 0x400, 0x10, 1.0f, 0.0f);
            if (B(self, 0x60) & 2) {
                StartAnimationForSizeClass(self, vars);
            }
            break;
        case 15:
            velE = vars + 0xC0;
            FastVecScale(velE, velE, 0.949999988f);
            F(vars, 0xC8) = F(vars, 0xC8) - 0.163333341f;
            BlendWithScaledCount(self, velE, 0x400, 0x10, 1.0f, 0.0f);
            if (nextState != 0xFF) {
                if (B(self, 0x43) != nextAnim) {
                    StartAnimationBlended(self, nextAnim, 0, 6);
                }
                B(self, 0x20) = nextState;
            }
            break;
        case 17:
            FastVecScale(vars + 0xC0, vars + 0xC0, 0.949999988f);
            if (B(self, 0x60) & 2) {
                StartAnimationForSizeClass(self, vars);
            }
            break;
        }
    check:
        if (F(self, 0x10) < 2.0f || F(self, 0x10) > 1021.0f || F(self, 0x14) < 2.0f || F(self, 0x14) > 1021.0f || F(self, 0x18) < 2.0f || F(self, 0x18) > 1021.0f) {
            MarkMobySpawned(self);
        }
    }
}
