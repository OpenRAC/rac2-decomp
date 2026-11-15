#include "common.h"

/* func_L17_003E7068 has a unit of its own for two flags (config/cflags.txt):
 * -frac2-gcse-unsplit-edges lets PRE put the &v30 copy before the state switch's
 * bounds check, as GCC 2.95 does, instead of in a split-off default block; and
 * -fmove-all-movables hoists the case 8 loop's D_L17_001C0020 address in loop.c's
 * first pass, ahead of st + 0x710, which decides the loop's s1/s5 allocation.
 * The pool reads use Moby member access (index scaled first), the address-of
 * uses plain pointer sums (base first), as retail's operand order shows. */
typedef union { u8 b[0x2000]; s8 c[0x2000]; s16 h[0x1000]; u16 uh[0x1000]; s32 i[0x800]; u32 u[0x800]; f32 f[0x800]; void *p[0x800]; } UView;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { u8 pad0[0xAA]; s16 oclass; u8 padAC[0xF8 - 0xAC]; float rotz; u8 padFC[0x100 - 0xFC]; } Moby;
typedef struct { float sn, cs, one, big; void *obj; int flags; u8 z, o; u16 id; float val; int k; } Hit;
extern void func_0026FEB8(const char *, ...);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00282948(void *);
extern int func_00282978(short *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern void func_0029F338(void *);
extern float func_0029F530(u8 *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(u8 *, int, int);
extern int func_002A77E0(int);
extern float func_002A89A8(void *, int, float);
extern int func_002A8D70(float, float, float, void *, int, int, int, int, int);
extern void func_002AA800(void *, int, float, float);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(u8 *);
extern int func_002B3890(u8 *);
extern int func_002B50E0(void *, void *, float);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_L01_00321178(void *, void *);
extern void func_L01_003E9CF8(u8 *, int, void *);
extern void func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, float, float);
extern void func_L02_0032EF10(void *, void *, void *, int, float);
extern void func_L17_0032C070(void *, void *, void *, int, float, float);
extern void func_L17_003C5AF8(u8 *);
extern int func_L17_003C5B68(u8 *);
extern void func_L17_003C7250(u8 *, u8 *);
extern int func_L17_003E6DE8(u8 *);
extern void func_L17_003E6F20(u8 *);
extern int func_L17_003E6F58(u8 *);
extern int func_L17_003E7010(u8 *);
extern void func_L17_003E8A58(void);
extern u8 D_00189E20[];
extern u8 *D_L17_001B2C1C[] __attribute__((sda));
extern int D_L17_001B3940[] __attribute__((sda));
extern u8 *D_L17_001FB720[];
extern u8 *D_L17_001FE880[];
extern Vec D_L17_001B9BC0;
extern Vec D_L17_001C0020;
extern char D_L17_001B0ED0[], D_L17_001B0EE8[], D_L17_001B0F10[], D_L17_001B0F20[];
extern float D_L17_001B0E3C __attribute__((sda));
extern float D_L17_001B0E58 __attribute__((sda));
extern int D_L17_001B0E68 __attribute__((sda));
extern int D_L17_001B0E6C __attribute__((sda));
extern float D_L17_001B0E70 __attribute__((sda));
extern float D_L17_001B0E74 __attribute__((sda));
extern float D_L17_001B0E7C __attribute__((sda));
extern float D_L17_001B0E80 __attribute__((sda));
extern float D_L17_001B0E88 __attribute__((sda));
extern int D_L17_001B0E8C __attribute__((sda));
extern float D_L17_001B0E90 __attribute__((sda));
extern int D_L17_001B0E94 __attribute__((sda));
extern int D_L17_001B0E9C __attribute__((sda));
extern float D_L17_001B0EA4 __attribute__((sda));
extern int D_L17_001B0EA8 __attribute__((sda));
extern float D_L17_001B0EAC __attribute__((sda));
extern float D_L17_001B0EB0 __attribute__((sda));
extern float D_L17_001B0EB4 __attribute__((sda));
extern float D_L17_001B0EB8 __attribute__((sda));
extern int D_L17_001B0EC0 __attribute__((sda));
extern int D_L17_001B0EC4 __attribute__((sda));
extern float D_L17_001B0EC8 __attribute__((sda));

/* Updates the two-headed Smolgian snapper (moby class 3019): it sets itself up, walks along
   its path, chases the player, bites when close, and is removed if it falls out of the
   level. */
void func_L17_003E7068(u8 *self) {
    Hit hitInfo;
    u8 *vars = ((u8 *)((UView *)(self))->p[0x1A]);
    float dist, ang, animProgress, animSpeed, attackProgress, chaseScale, biteProgress, turnAngle, height, idleProgress;
    Vec targetPoint, probePoint, probeEnd;
    float pathCost;
    int attachedIndex, damageType, hitFlags, pointIndex;
    int leaderIndex, attachedIndex2;
    u8 *leader;
    int attempts, moveFlags, nearGround, moveFlags13;
    float fallbackDistance;
    Moby *mobyPool;

    InitSnapperStateAndCheckHits();
    dist = vec_distance_xy(self + 0x10, vars + 0x240);
    ang = FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]);
    attachedIndex = *(int *)(vars + 0x6B8);
    if (attachedIndex != -1) {
        if (((Moby *)gMobyPool_L17[0])[attachedIndex].oclass != 0x929 /* moby class 2345 */) {
            STUB_printf(D_L17_001B0ED0);
        } else {
            SetPlatformPathIndex((u8 *)&((Moby *)gMobyPool_L17[0])[attachedIndex], self);
        }
    }
    switch (self[0x95]) {
    case 5:
        TransformPointAndRotationByParent(self, gMobyPool_L17[0] + (*(int *)(vars + 0x6B8) << 8), self + 0x10, self + 0xF0, self + 0x10, self + 0xF0);
        leaderIndex = *(int *)(vars + 0x6DC);
        if (leaderIndex == -1 || (leader = gMobyPool_L17[0] + (leaderIndex << 8)) == self || leader == 0 || leader[0x20] == 0xFE || leader[0x20] == 0xFD) {
            attachedIndex2 = *(int *)(vars + 0x6B8);
            if (attachedIndex2 != -1) {
                if (*(s16 *)(vars + 0x69E) == 1 && CanRidePlatformStart(gMobyPool_L17[0] + (attachedIndex2 << 8))) {
                    StartRidePlatform(gMobyPool_L17[0] + (*(int *)(vars + 0x6B8) << 8));
                    if (((Moby *)gMobyPool_L17[0])[*(int *)(vars + 0x6B8)].oclass == 0x929 /* moby class 2345 */) {
                        if (self[0x20] != 6) SetMobyState(self, 6, -1);
                        mobyPool = (Moby *)gMobyPool_L17[0];
                        ((UView *)(self))->uh[0x1A] = ((UView *)(self))->uh[0x1A] & 0xFFBE;
                        ((UView *)(self))->i[0x26] = *(int *)(((u8 *)((UView *)(self))->p[0x9]) + 0x10);
                        ((UView *)(self))->f[0x3E] = mobyPool[*(int *)(vars + 0x6B8)].rotz;
                    } else if (self[0x20] != 6) {
                        SetMobyState(self, 6, -1);
                    }
                }
                break;
            }
            goto case0;
        }
        break;
    case 0:
    case0:
        if (*(s16 *)(vars + 0x69E) == 1) {
            if (*(int *)(vars + 0x730) == 0 || D_L17_001FB720[self[0x21]] == 0 || ClaimNearestObjectSlot(self) != 0) {
                SetMobyState(self, 0xF, 2);
            } else {
                SetMobyState(self, 7, 6);
                if (self[0x43] != 1) StartAnimationBlended(self, 1, 0, D_L17_001B0E9C);
            }
            SetControllerSpeedLimits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            *(s16 *)(vars + 0x69C) = 0xC8;
            *(int *)(vars + 0x148) = *(int *)(vars + 0x148) | 0x10;
        }
        break;
    case 2:
        if (*(s16 *)(vars + 0x69E) == 1) *(s16 *)(vars + 0x69C) = 0xC8;
        if (FastDecTimer((short *)(vars + 0x69C)) != 0) {
            SetMobyState(self, 5, 4);
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 3) StartAnimationBlended(self, 3, 0, 0x14);
            *(s16 *)(vars + 0x69C) = 0xDC;
        }
        break;
    case 4:
        if (*(s16 *)(vars + 0x69E) == 1) goto alert;
        goto b62;
    case 6:
        if (ClaimNearestObjectSlot(self) != 0) {
            if ((self[0x42] != 1 && self[0x43] != 1) || (self[0x60] & 2)) {
alert:
                SetMobyState(self, 0xB, 2);
                SetControllerSpeedLimits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
                *(s16 *)(vars + 0x69C) = 0xC8;
                *(int *)(vars + 0x148) = *(int *)(vars + 0x148) | 0x10;
            }
        } else {
            animProgress = GetMobyAnimationValue(self);
            if (*(s16 *)(vars + 0x69E) == 1) *(s16 *)(vars + 0x69C) = 0xC8;
            if ((self[0x60] & 2) && self[0x42] == 3 && self[0x43] != 0xE) StartAnimationBlended(self, 0xE, 0, D_L17_001B0E9C);
            if (animProgress >= 20.0f && self[0x42] == 0xE && self[0x43] != 3) StartAnimationBlended(self, 3, 0, D_L17_001B0E9C);
            if (self[0x60] & 2) {
                if (self[0x42] == 1) {
                    if (self[0x43] != 0xE) StartAnimationBlended(self, 0xE, 0, D_L17_001B0E9C);
                    goto b60;
                }
            } else {
b60:
                if (self[0x42] == 1) {
                    StepAngleTowardTarget(self + 0xF8, 0, FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), 0.10471977f);
                }
            }
b62:
            if (FastDecTimer((short *)(vars + 0x69C)) != 0) {
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 2) StartAnimationBlended(self, 2, 0, 0x14);
                SetMobyState(self, 3, 0);
            }
        }
        break;
    case 3:
        if (SetSecondPendingFlag(self) != 0) {
            animSpeed = ((UView *)(self))->f[0x12];
            if (animSpeed <= 0.0f || animSpeed > 1.0f) ((UView *)(self))->f[0x12] = 1.0f;
            SetControllerSpeedLimits(self, (float)(D_L17_001B0E68 * 8) * 0.00027777778f, D_L17_001B0E70 * 0.13333334f, 0.10471977f, 0.10471977f);
        }
        if (((UView *)(self))->f[0x6] < D_L17_001B0E3C) goto b262;
        if (*(float *)(vars + 0xE8) > 0.016666668f) {
            *(float *)(vars + 0xE8) = 0.016666668f;
            STUB_printf(D_L17_001B0F10);
        }
        hitFlags = DispatchActionByKind(self, vars + 0x60);
        if (hitFlags & 1) {
            QueueMobyForGlowEffect(self, 0, 0);
            SetDeathBits(self, 0, 3);
        }
        attackProgress = GetMobyAnimationValue(self);
        if (attackProgress >= 13.0f && attackProgress <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, vars + 0x240) < D_L17_001B0E58) {
            if (self[0x42] == 4) {
                if (IsTargetReachable(self) != 0) {
                    hitInfo.obj = self;
                    hitInfo.flags = 0x10001;
                    hitInfo.val = *(float *)(vars + 0x700);
                    hitInfo.sn = FastSinOrCosA(FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
                    hitInfo.cs = FastSinOrCosB(FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
                    hitInfo.one = 1.0f;
                    hitInfo.big = 5627.925f;
                    hitInfo.o = hitInfo.k = 1;
                    hitInfo.z = 0;
                    hitInfo.id = ((UView *)(self))->uh[0x55];
                    damageType = self[0x42] == 4 ? D_L17_001B0EC4 : D_L17_001B0EC0;
                    TestHitAtBone(D_L17_001B0EC8, *(float *)(vars + 0x700), 1.0f, self, damageType, 0x10001, 0, 1, 0);
                }
            }
        }
        if ((self[0x42] == 4 || self[0x43] == 4) && !(attackProgress > 13.0f)) {
            TurnMobyTowardTarget(self, vars + 0x240);
        }
        if ((hitFlags & 2) && D_L17_001B0EB0 <= attackProgress) SetMobyState(self, 0xD, 2);
        if (self[0x42] == 0xD && D_L17_001B0EB4 <= attackProgress) {
            if (self[0x43] != 4) StartAnimationBlended(self, 4, 0, 8);
            *(s16 *)(gHeroState + 0x1DC) = 0;
        }
        break;
    }
    switch (self[0x20]) {
    case 3:
        if (SetFirstPendingFlag(self) != 0) {
            if (RandomIntBelow(2) == 0) {
                if (self[0x43] != 2) StartAnimationBlended(self, 2, 0, D_L17_001B0E9C);
            } else if (self[0x43] != 0xE) {
                StartAnimationBlended(self, 0xE, 0, D_L17_001B0E9C);
            }
        }
        idleProgress = GetMobyAnimationValue(self);
        if ((self[0x42] == 2 && (self[0x60] & 2)) || (self[0x42] == 0xE && idleProgress >= 20.0f)) {
            if (RandomIntBelow(2) == 0) {
                if (self[0x43] != 2) StartAnimationBlended(self, 2, 0, D_L17_001B0E9C);
            } else if (self[0x43] != 0xE) {
                StartAnimationBlended(self, 0xE, 0, D_L17_001B0E9C);
            }
        }
        break;
    case 8:
        if (SetFirstPendingFlag(self) != 0) {
            attempts = 0;
            do {
                pointIndex = PickRandomPathPointAway(self);
                qcopy(&targetPoint, self + 0x10);
                qcopy(&probePoint, &((Vec *)gPathTable_L17[*(int *)(vars + 0x684)])[pointIndex + 1]);
                targetPoint.f[2] = targetPoint.f[2] + 1.0f;
                probePoint.f[2] = targetPoint.f[2];
                if (CollLine(&targetPoint, &probePoint, 0, self, 0) != 0) {
                    if (!(vec_distance_xy(self + 0x10, &D_L17_001C0020) < 2.0f)) {
                        qcopy(vars + 0x710, &D_L17_001C0020);
                        break;
                    }
                } else {
                    qcopy(vars + 0x710, &probePoint);
                    break;
                }
                attempts++;
            } while (attempts < 5);
            if (attempts != 5) {
                if (self[0x43] != 0xC) StartAnimationBlended(self, 0xC, 0, D_L17_001B0E9C);
            } else {
                SetMobyState(self, 3, -1);
                break;
            }
        }
        moveFlags = TurnMobyTowardTarget(self, vars + 0x710);
        StepAngleTowardTarget(self + 0xF8, 0, FastMatrixHelperA(*(float *)(vars + 0x710) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x714) - ((UView *)(self))->f[0x5]), 0.043633237f);
        if (!(moveFlags & 0x80) && *(int *)(vars + 0x190) < 0xB && !(moveFlags & 0x10F)) {
        } else {
            SetMobyState(self, 3, -1);
        }
        break;
    case 6:
        if (SetFirstPendingFlag(self) != 0) {
            if (((Moby *)gMobyPool_L17[0])[*(int *)(vars + 0x6B8)].oclass != 0x929 /* moby class 2345 */) {
                if (self[0x43] != 1) StartAnimationBlended(self, 1, 0, D_L17_001B0E9C);
                SetControllerSpeedLimits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            } else {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) StartAnimationBlended(self, 0xA, 0, D_L17_001B0E9C);
                SetControllerSpeedLimits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            }
            ((UView *)(self))->f[0x6] = ProbeGroundHeightBelow(self + 0x10, 0, 3.0f);
            qcopy(vars + 0x6C0, self + 0x10);
        }
        if (self[0x60] & 2) {
            if (self[0x42] == 1) {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) StartAnimationBlended(self, 0xA, 0, 0x14);
                TurnMobyTowardTarget(self, self + 0x10);
                goto s6_157;
            }
            goto s6_159;
        }
s6_157:
        if (self[0x42] == 1) {
            ((UView *)(self))->f[0x6] = ProbeGroundHeightBelow(self + 0x10, 0, 3.0f);
            break;
        }
s6_159:
        if (self[0x42] == 0xA) {
            (&targetPoint)->f[0] = FastSinOrCosA(((UView *)(self))->f[0x3E]) * 3.0f;
            (&targetPoint)->f[1] = FastSinOrCosB(((UView *)(self))->f[0x3E]) * 3.0f;
            (&targetPoint)->f[2] = 0.0f;
            FastVecAdd(&probePoint, self + 0x10, (&targetPoint));
            ((UView *)(self))->f[0x6] = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f);
            TurnMobyTowardTarget(self, &probePoint);
            if (!(vec_distance_xy(self + 0x10, vars + 0x6C0) > 4.9f)) {
            } else if (*(int *)(vars + 0x730) == 0 || D_L17_001FB720[self[0x21]] == 0 || (((UView *)(self))->f[0x12] = 1.0f, ClaimNearestObjectSlot(self) != 0)) {
                SetMobyState(self, 0xB, 2);
            } else {
                SetMobyState(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) StartAnimationBlended(self, 3, 0, 0x14);
            }
        }
        break;
    case 11:
        if (SetFirstPendingFlag(self) != 0) {
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) StartAnimationBlended(self, 0xA, 0, D_L17_001B0E9C);
            chaseScale = D_L17_001B0EB8;
            ((UView *)(self))->f[0x12] = -chaseScale;
            SetControllerSpeedLimits(self, (float)D_L17_001B0E68 * 0.00027777778f, chaseScale * D_L17_001B0E70 * 0.016666668f, 0.05817765f, 0.05817765f);
        }
        if (self[0x42] == 0xA) {
            if (dist < D_L17_001B0E7C) {
                qcopy((&targetPoint), &D_L17_001B9BC0);
                if (vec_distance_xy((&targetPoint), self + 0x10) < D_L17_001B0EA4) {
                    if (*(int *)(vars + 0x738) < D_L17_001B0EA8) {
                        (&targetPoint)->f[2] = *(float *)(vars + 0x248);
                        FastVecSub((&targetPoint), vars + 0x240, (&targetPoint));
                        vec_scale_to_length((&targetPoint), (&targetPoint), 2.0f * D_L17_001B0EA4);
                        FastVecAdd((&targetPoint), &D_L17_001B9BC0, (&targetPoint));
                        probePoint.q = *(Quad *)(self + 0x10);
                        ClampMoveToPathArea(&probePoint, (&targetPoint), (&targetPoint), *(int *)(vars + 0x684), 3.0f);
                        fallbackDistance = vec_distance_xy(self + 0x10, (&targetPoint));
                        if (D_L17_001B0EA4 + 0.3f < fallbackDistance) {
                            TurnMobyTowardTarget(self, (&targetPoint));
                            *(int *)(vars + 0x738) = *(int *)(vars + 0x738) + 1;
                            break;
                        }
                    } else {
                        goto s11_184;
                    }
                }
                if (*(int *)(vars + 0x738) >= D_L17_001B0EA8) {
s11_184:
                    STUB_printf(D_L17_001B0F20);
                }
                *(int *)(vars + 0x738) = 0;
                SetMobyState(self, 0xC, -1);
                ((UView *)(self))->f[0x12] = 1.0f;
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != RandomIntBelow(2) + 4) StartAnimationBlended(self, RandomIntBelow(2) + 4, 2, 0x14);
            } else {
                ComputeRegionRouteHeading(self + 0x10, vars + 0x240, &pathCost, vars + 0x280, *(int *)(vars + 0x750), vars + 0x758, vars + 0x754, 0.0f, 0.5f);
                StepMovementController(self, vars + 0x240, pathCost);
                StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
                if (*(int *)(vars + 0x190) >= 0x3D) {
                    *(int *)(vars + 0x704) = D_L17_001B0E8C;
                    SetMobyState(self, 4, -1);
                    ((UView *)(self))->f[0x12] = 1.0f;
                    if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                    if (self[0x43] != 2) StartAnimationBlended(self, 2, 0, 0x14);
                }
            }
        }
        break;
    case 15:
        if (SetFirstPendingFlag(self) != 0 && self[0x43] != 1) StartAnimationBlended(self, 1, 0, 0x14);
        StepAngleTowardTarget(self + 0xF8, 0, FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), 0.10471977f);
        if (self[0x60] & 2) SetMobyState(self, 0xB, -1);
        break;
    case 12:
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
        biteProgress = GetMobyAnimationValue(self);
        if (biteProgress >= 13.0f && biteProgress <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, vars + 0x240) < D_L17_001B0E58
            && IsTargetReachable(self) != 0) {
            hitInfo.obj = self;
            hitInfo.flags = 0x10001;
            hitInfo.val = *(float *)(vars + 0x700);
            hitInfo.sn = FastSinOrCosA(FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
            hitInfo.cs = FastSinOrCosB(FastMatrixHelperA(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
            hitInfo.one = 1.0f;
            hitInfo.big = 5627.925f;
            hitInfo.o = hitInfo.k = 1;
            hitInfo.z = 0;
            hitInfo.id = ((UView *)(self))->uh[0x55];
            damageType = self[0x42] == 4 ? D_L17_001B0EC4 : D_L17_001B0EC0;
            TestHitAtBone(D_L17_001B0EC8, *(float *)(vars + 0x700), 1.0f, self, damageType, 0x10001, 0, 1, 0);
        }
        if ((u32)(self[0x42] - 4) < 2U && D_L17_001B0EAC <= biteProgress) SetMobyState(self, 0xD, -1);
        break;
    case 4:
        if (FastFloatHelperD(vars + 0x704) != 0) {
            SetMobyState(self, 0xC, -1);
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != RandomIntBelow(2) + 4) StartAnimationBlended(self, RandomIntBelow(2) + 4, 0, 0x14);
        }
        break;
    case 13:
        if (SetFirstPendingFlag(self) != 0) {
            turnAngle = FastAddRotations(((UView *)(self))->f[0x3E], 3.141593f);
            (&targetPoint)->f[0] = FastSinOrCosA(turnAngle) * D_L17_001B0E88;
            (&targetPoint)->f[1] = FastSinOrCosB(turnAngle) * D_L17_001B0E88;
            (&targetPoint)->f[2] = 0.0f;
            FastVecAdd((&targetPoint), (&targetPoint), self + 0x10);
            probePoint.q = *(Quad *)(self + 0x10);
            ClampMoveToPathArea(&probePoint, (&targetPoint), (&targetPoint), *(int *)(vars + 0x684), 3.0f);
            if (fast_vec_dist(self + 0x10, (&targetPoint)) < D_L17_001B0E88 * 0.5f) {
                FindClearSidePoint(self + 0x10, vars + 0x240, (&targetPoint), *(int *)(vars + 0x684), D_L17_001B0E90, 1.0f);
            }
            qcopy(&probePoint, self + 0x10);
            probePoint.f[2] += 0.5f;
            qcopy(&probeEnd, (&targetPoint));
            probeEnd.f[2] += 0.5f;
            if (CollLine(&probePoint, &probeEnd, 2, 0, 0) != 0) qcopy((&targetPoint), &D_L17_001C0020);
            qcopy(vars + 0x710, (&targetPoint));
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) StartAnimationBlended(self, 0xA, 0, D_L17_001B0E9C);
            SetControllerSpeedLimits(self, (float)D_L17_001B0E6C * 0.00027777778f, D_L17_001B0E74 * 0.016666668f, 0.10471977f, 0.10471977f);
            *(int *)(vars + 0x708) = D_L17_001B0E94;
            ReleaseObjectSlot(self);
            ((UView *)(self))->f[0x12] = D_L17_001B0EB8;
        }
        nearGround = 0;
        moveFlags13 = TurnMobyTowardTarget(self, vars + 0x710);
        TransformMobyJointToWorld(self, 3, (&targetPoint));
        if (ProbeGroundHeightBelow((&targetPoint), 0, 0.5f) < 10.0f) nearGround = 1;
        if (!(moveFlags13 & 0x80) && *(int *)(vars + 0x190) < 0xA && !(moveFlags13 & 0xF) && nearGround != 1) {
        } else {
            ((UView *)(self))->f[0x12] = 1.0f;
            if (dist < D_L17_001B0E7C + D_L17_001B0E80) {
                SetMobyState(self, 0xC, -1);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != RandomIntBelow(2) + 4) StartAnimationBlended(self, RandomIntBelow(2) + 4, 0, 0x14);
            } else {
                SetMobyState(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) StartAnimationBlended(self, 3, 0, 0x14);
            }
        }
        if (FastFloatHelperD(vars + 0x708) != 0 && dist < D_L17_001B0E7C) {
            SetMobyState(self, 0xC, -1);
            ((UView *)(self))->f[0x12] = 1.0f;
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != RandomIntBelow(2) + 4) StartAnimationBlended(self, RandomIntBelow(2) + 4, 0, 0x14);
        }
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
        break;
    case 9:
        if (SetFirstPendingFlag(self) != 0 && self[0x43] != 7) StartAnimationBlended(self, 7, 0, 0x14);
        qcopy((&targetPoint), self + 0x10);
        height = ((UView *)(self))->f[0x6] - 0.050000004f;
        (&targetPoint)->f[2] = 70.0f;
        ((UView *)(self))->f[0x6] = height;
        if (height < 70.0f) {
b262:
            SetDeathBits(self, 0, 3);
            MarkMobySpawned(self);
            return;
        }
        break;
    }
    TransformMobyJointToWorld(self, D_L17_001B3940[0], (&targetPoint));
    if (ProbeGroundHeightBelow((&targetPoint), 0, 1.0f) < 20.0f && self[0x95] != 3 && self[0x20] != 9) {
        if (self[0x20] == 0xD || self[0x20] == 0xB) SetMobyState(self, 9, 7);
    }
}
