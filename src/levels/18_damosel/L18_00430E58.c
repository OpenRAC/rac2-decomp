/* func_L18_00430E58: own unit for -frac2-keep-block-order (the class-switch default stays last)
 * and -frac2-hazard-labels (case 9 branches to the hazard nop of a shared c.lt.s).
 * D_L18_001B290C is a MACRO_ADDR scalar (tied lui/lw); arms that end in a call repeat the
 * following store so the tails cross-jump as in retail. */
#include "common.h"

extern u8 *D_L18_001B290C MACRO_ADDR;

extern int func_00282948(void *);
extern int func_00282978(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0029F338(void *);
extern float func_0029F530(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_002A8D70(void *, float, float, int, int, float, int, int, int);
extern float func_002AA2E8(void *, float, float);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_L02_003329C8(void *, void *, float, float);
extern int func_L07_00323038(void *, float, float, float);
extern void func_L18_00432548(void *, void *, int);
extern int func_L18_00432598(void *, void *);
extern float func_L18_004325D8(void *, void *);
extern float func_L18_00432630(void *, void *);
extern int func_L18_00432698(void *, void *);
extern int func_L18_004326E8(void *);
extern int func_L18_00432718(void *, void *);
extern int func_L18_004327B0(void *);
extern void func_L18_00432910(void *);
extern void func_L18_00432960(void *);
extern void func_L18_004329B0(void *);
extern void func_L18_00432E78(void *, int, int, int);
extern void func_L18_004331D0(void *);
extern void func_L18_00433430(void *);
extern void func_L18_00433450(void *);

/* Runs the Extermibot's main behaviour: it idles, picks a target, walks toward it, attacks and finally blows up. Each state starts an animation and moves on when the animation ends. */
void func_L18_00430E58(u8 *self)
{
    float vec[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(self + 0x68);

    switch (self[0x20]) {
    case 0:
    case 1:
        break;
    case 2:
        if (SetFirstPendingFlag(self) != 0)
            SetAnimOnMobyAndParts(self, 1, 0, 0xA);
        break;
    case 3:
        if (SetFirstPendingFlag(self) != 0) {
            self[0xBC] = 0;
            *(s16 *)(vars + 0x80C) = RandomIntBelow(30);
        } else {
            if (self[0xBC] == 0 && *(u16 *)(self + 0x96) > *(s16 *)(vars + 0x80C)) {
                *(int *)(vars + 0x188) = 0;
                SetAnimOnMobyAndParts(self, 2, 0, 3);
                self[0xBC] = 1;
                vec_scale_to_length(vec, self + 0xC0, 2.0f);
                FastVecAdd(vec, vec, self + 0x10);
                vec[2] -= 6.0f;
                AimMoveRecordAtTarget(self, vec, 0.033333335f, 0.0055555557f);
            }
            if (self[0xBC] == 1) {
                ApproachValue(self + 0xF0, 0.0f, 0.052359886f);
                ApproachValue(self + 0xF4, 0.0f, 0.052359886f);
                *(int *)(vars + 0x138) |= 2;
                if (*(u8 **)(vars + 0x7EC) != 0)
                    *(int *)(*(u8 **)(vars + 0x7EC) + 0x98) = 0;
                if (AdjustJumpSpeedToTarget(self, 11.0f, 18.0f, 27.0f) != 0) {
                    SetFastMotionLimits(self);
                    SetAnimOnMobyAndParts(self, 9, 0, 0xA);
                    *(float *)(vars + 0x134) = 0.2f;
                    if (*(int *)(vars + 0x7D0) != -1) {
                        self[0xBC] = 2;
                        qcopy(vars + 0x750, (u8 *)((*(int *)(vars + 0x7D0) << 7) + (s32)gWaypointTable) + 0x30);
                    } else {
                        SetMobyState(self, 4, 1);
                    }
                }
                *(int *)(vars + 0x138) &= ~2;
                if (*(u8 **)(vars + 0x7EC) != 0)
                    *(int *)(*(u8 **)(vars + 0x7EC) + 0x98) = *(int *)(*(u8 **)(*(u8 **)(vars + 0x7EC) + 0x24) + 0x10);
            } else if (self[0xBC] == 2) {
                if (vec_distance_xy(self + 0x10, gWaypointTable + (*(int *)(vars + 0x7D0) << 7) + 0x30) < 0.5f)
                    SetMobyState(self, 4, 1);
            }
        }
        break;
    case 4:
        if (SetFirstPendingFlag(self) != 0) {
            SetAnimOnMobyAndParts(self, RandomIntBelow(2) + 3, 0, 0xA);
            if (self[0x94] != 4)
                *(int *)(vars + 0x7AC) = RandomIntRange(0, 30);
        } else if (self[0x60] & 2) {
            SetMobyState(self, 4, -1);
        } else if (*(s16 *)(vars + 0x7FA) == 0 && *(int *)(vars + 0x79C) == 1 && FastFloatHelperD(vars + 0x7AC) != 0) {
            SetMobyState(self, 6, -1);
            SetMobyState(self, 5, -1);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(self) != 0)
            SetAnimOnMobyAndParts(self, 5, 0, 0xA);
        else if (self[0x60] & 2)
            SetMobyState(self, self[0x94], -1);
        break;
    case 6:
        if (SetFirstPendingFlag(self) != 0) {
            SetAnimOnMobyAndParts(self, RandomIntBelow(2) + 6, 0, 0xA);
            *(int *)(vars + 0x7A8) = RandomIntRange(480, 600);
        } else if (*(int *)(vars + 0x79C) == 1) {
            if (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))
                SetMobyState(self, 8, -1);
            else if (FindNearestProtopetInGroup(self) != 0)
                SetMobyState(self, 7, 1);
        } else if (*(int *)(vars + 0x7A8) <= 0) {
            SetMobyState(self, 4, -1);
        }
        FastFloatHelperD(vars + 0x7A8);
        break;
    case 9: {
        float frame;
        if (SetFirstPendingFlag(self) != 0) {
            *(float *)(vars + 0x134) = 2.0f;
            switch (self[0x42]) {
            case 8:
                SetSlowMotionLimits(self);
                self[0xBC] = 1;
                break;
            case 9:
                SetFastMotionLimits(self);
                self[0xBC] = 2;
                break;
            default:
                SetSlowMotionLimits(self);
                self[0xBC] = 1;
                SetAnimOnMobyAndParts(self, 8, 0, 0xA);
                break;
            }
        }
        if (*(u8 **)(vars + 0x7BC) != 0) {
            u8 *target = *(u8 **)(vars + 0x7BC);
            if (target[0x20] != 0xFE && (*(u8 **)(vars + 0x7BC))[0x20] != 0xFD && ((*(u16 *)(target + 0x34) ^ 1) & 1))
                qcopy(vars + 0x750, target + 0x10);
            else
                SetMobyState(self, self[0x94], -1);
        } else {
            qcopy(vars + 0x750, vars + 0x1F0);
        }
        SetAimTowardPoint(self, vars + 0x750, 0);
        frame = GetMobyAnimationValue(self);
        if (self[0xBC] == 2) {
            if (GetPositionLengthOffset(self, vars + 0x750) < 4.0f && (self[0x60] & 2)) {
                SetSlowMotionLimits(self);
                self[0xBC] = 1;
                SetAnimOnMobyAndParts(self, 8, 0, 0xA);
            }
        } else if (self[0xBC] == 1) {
            if (GetPositionLengthOffset(self, vars + 0x750) > 7.0f && frame > 4.0f && frame < 9.0f) {
                SetFastMotionLimits(self);
                self[0xBC] = 2;
                SetAnimOnMobyAndParts(self, 9, 6, 0xA);
            }
            if (((frame > 4.0f && frame < 9.0f) || (frame > 21.0f && frame < 26.0f))
                && GetPositionLengthOffset(self, vars + 0x750) < 0.0f && GetTurnAngleToPoint(self, vars + 0x750) < 0.0f
                && IsPathToPointClear(self, vars + 0x750) != 0) {
                SetAnimOnMobyAndParts(self, RandomIntBelow(2) + 6, 0, 0xA);
                SetMobyState(self, self[0x94], -1);
            }
        } else {
            if ((self[0x60] & 2) && *(u16 *)(self + 0x96) >= 0x79) {
                SetSlowMotionLimits(self);
                self[0xBC] = 1;
                SetAnimOnMobyAndParts(self, 8, 0, 0xA);
            }
            if (GetPositionLengthOffset(self, vars + 0x750) < 0.0f && GetTurnAngleToPoint(self, vars + 0x750) < 0.0f
                && IsPathToPointClear(self, vars + 0x750) != 0) {
                SetAnimOnMobyAndParts(self, RandomIntBelow(2) + 6, 0, 0xA);
                SetMobyState(self, self[0x94], -1);
            }
        }
        if ((self[0xBC] == 1 || self[0xBC] == 2)
            && (*(int *)(vars + 0x180) >= 2 || (*(int *)(vars + 0x194) & 0xF))) {
            self[0xBC] = 0;
            SetAnimOnMobyAndParts(self, RandomIntBelow(2) + 6, 0, 0xA);
            *(u16 *)(self + 0x96) = 0;
        }
        if (self[0x94] == 7 && *(int *)(vars + 0x79C) == 1
            && (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))) {
            *(u8 **)(vars + 0x7BC) = 0;
            SetMobyState(self, 8, -1);
        }
        break;
    }
    case 7:
        if (SetFirstPendingFlag(self) != 0 && FindNearestProtopetInGroup(self) == 0) {
            SetMobyState(self, 6, -1);
        } else if (GetPositionLengthOffset(self, *(u8 **)(vars + 0x7B8) + 0x10) >= 0.0f
                   || GetTurnAngleToPoint(self, *(u8 **)(vars + 0x7B8) + 0x10) >= 0.0f
                   || IsPathToPointClear(self, *(u8 **)(vars + 0x7B8) + 0x10) == 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            SetMobyState(self, 9, -1);
        } else if (*(int *)(vars + 0x79C) == 1
                   && (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))) {
            *(u8 **)(vars + 0x7BC) = 0;
            SetMobyState(self, 6, -1);
        } else if (IsPositionVectorShort(self, *(u8 **)(vars + 0x7B8) + 0x10) != 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            SetMobyState(self, 0xB, -1);
        } else if (IsCooldownFinished(self) != 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            SetMobyState(self, 0xA, -1);
        }
        break;
    case 8: {
        u8 *homePoint;
        if (SetFirstPendingFlag(self) != 0)
            SetAnimOnMobyAndParts(self, RandomIntBelow(2) + 6, 0, 0xA);
        if (*(int *)(vars + 0x79C) != 1) {
            SetMobyState(self, 6, -1);
            break;
        }
        homePoint = vars + 0x1F0;
        if (IsPositionVectorShort(self, homePoint) != 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            SetMobyState(self, 0xB, -1);
        } else if (GetPositionLengthOffset(self, homePoint) >= 0.0f || GetTurnAngleToPoint(self, homePoint) >= 0.0f
                   || IsPathToPointClear(self, homePoint) == 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            SetMobyState(self, 9, -1);
        } else if (IsCooldownFinished(self) != 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            SetMobyState(self, 0xA, -1);
        }
        break;
    }
    case 10:
        if (SetFirstPendingFlag(self) != 0) {
            SetAnimOnMobyAndParts(self, 0xA, 0, 0xA);
            self[0xBC] = 0;
            *(float *)(self + 0x48) = 2.0f;
            if (*(s16 *)(vars + 0x7FC) != 0)
                *(s16 *)(vars + 0x806) = 0;
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            qcopy(vec, *(u8 **)(vars + 0x7BC) + 0x10);
        else
            qcopy(vec, vars + 0x1F0);
        SetAimTowardPoint(self, vec, 0);
        if (self[0xBC] == 0) {
            if (IsPositionVectorShort(self, vec) != 0) {
                u8 savedAnim = self[0x94];
                SetMobyState(self, 0xB, -1);
                self[0x94] = savedAnim;
                break;
            }
            if (self[0x60] & 2) {
                if (IsFacingPoint(self, vec) != 0) {
                    self[0xBC] = 2;
                    if (*(s16 *)(vars + 0x7FC) != 0) {
                        SetAnimOnMobyAndParts(self, 0xC, 0, 0xA);
                        *(float *)(self + 0x48) = 1.0f;
                    } else {
                        SetAnimOnMobyAndParts(self, 0xD, 0, 0xA);
                        *(float *)(self + 0x48) = 1.0f;
                    }
                } else {
                    self[0xBC] = 1;
                    SetAnimOnMobyAndParts(self, 0xB, 0, 0xA);
                    *(float *)(self + 0x48) = 1.0f;
                }
            }
        }
        if (self[0xBC] == 1) {
            if (IsPositionVectorShort(self, vec) != 0) {
                u8 savedAnim = self[0x94];
                SetMobyState(self, 0xB, -1);
                self[0x94] = savedAnim;
                break;
            }
            if (IsFacingPoint(self, vec) != 0) {
                self[0xBC] = 2;
                if (*(s16 *)(vars + 0x7FC) != 0)
                    SetAnimOnMobyAndParts(self, 0xC, 0, 0xA);
                else
                    SetAnimOnMobyAndParts(self, 0xD, 0, 0xA);
                *(float *)(self + 0x48) = 1.0f;
            }
        } else if (self[0xBC] == 2) {
            float frame = GetMobyAnimationValue(self);
            if (*(s16 *)(vars + 0x7FC) != 0) {
                if (frame < 2.0f && *(s16 *)(vars + 0x806) == 0) {
                    qcopy(vars + 0x760, vec);
                    FireShotAtTarget(self);
                    *(s16 *)(vars + 0x806) = 1;
                }
            } else if (frame < 5.0f && *(s16 *)(vars + 0x806) == 0) {
                StartAttackTimer(self);
            }
            if (self[0x60] & 2) {
                if (*(u8 **)(vars + 0x7BC) == 0) {
                    if (IsPositionVectorShort(self, vec) != 0) {
                        u8 savedAnim = self[0x94];
                        SetMobyState(self, 0xB, -1);
                        self[0x94] = savedAnim;
                        break;
                    }
                    if (IsCooldownFinished(self) != 0 && GetPositionLengthOffset(self, vec) < 0.0f
                        && IsFacingPoint(self, vec) != 0) {
                        self[0xBC] = 2;
                        if (*(s16 *)(vars + 0x7FC) != 0) {
                            SetAnimOnMobyAndParts(self, 0xC, 0, 0xA);
                            *(float *)(self + 0x48) = 1.0f;
                        } else {
                            SetAnimOnMobyAndParts(self, 0xD, 0, 0xA);
                            *(float *)(self + 0x48) = 1.0f;
                        }
                    }
                }
                self[0xBC] = 3;
                SetAnimOnMobyAndParts(self, 0xE, 0, 0xA);
                *(float *)(self + 0x48) = 1.0f;
            }
        } else if (self[0xBC] == 3) {
            if (self[0x60] & 2) {
                SetAnimOnMobyAndParts(self, 8, 0, 0xA);
                SetMobyState(self, self[0x94], -1);
                *(float *)(self + 0x48) = 1.0f;
            }
        }
        break;
    case 11: {
        float frame;
        if (SetFirstPendingFlag(self) != 0) {
            SetAnimOnMobyAndParts(self, 0xF, 0, 0xA);
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            SetAimTowardPoint(self, *(u8 **)(vars + 0x7BC) + 0x10, 1);
        else
            SetAimTowardPoint(self, vars + 0x1F0, 1);
        frame = GetMobyAnimationValue(self);
        if (frame > 11.0f && frame < 17.0f)
            TestHitAtBone(self, 0.8f, (float)vars[0x36], 2, 0x10001, 4.0f, 0, 1, 0);
        if (self[0x60] & 2)
            SetMobyState(self, self[0x94], -1);
        break;
    }
    case 12: {
        float frame;
        if (SetFirstPendingFlag(self) != 0) {
            SetAnimOnMobyAndParts(self, 0xF, 2, 0xA);
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            SetAimTowardPoint(self, *(u8 **)(vars + 0x7BC) + 0x10, 1);
        else
            SetAimTowardPoint(self, vars + 0x1F0, 1);
        frame = GetMobyAnimationValue(self);
        if (frame > 11.0f && frame < 17.0f)
            TestHitAtBone(self, 0.8f, (float)vars[0x36], 2, 0x10001, 4.0f, 0, 1, 0);
        if (self[0x60] & 2)
            SetMobyState(self, self[0x94], -1);
        break;
    }
    case 13: {
        int flags;
        float frame;
        if (SetFirstPendingFlag(self) != 0) {
            ClearAttackCounters(self);
            *(s16 *)(vars + 0x804) = 0;
            *(s16 *)(vars + 0x80E) = 1;
        }
        flags = DispatchActionByKind(self, vars + 0x50);
        frame = GetMobyAnimationValue(self);
        if (*(u16 *)(self + 0x96) >= 0xB5 || (flags & 1)) {
            SetDeathBits(self, 0, 3);
            DestroyPieceAndParts(self);
        } else if ((self[0x42] == 0x10 && frame > 27.0f) || (self[0x42] == 0x11 && frame > 47.0f) || (flags & 2)) {
            if (*(u8 **)(vars + 0x7C0) != 0) {
                if (IsPositionVectorShort(self, vars + 0x1F0) != 0) {
                    *(float *)(self + 0x48) = 0.0f;
                    *(u8 **)(vars + 0x7BC) = 0;
                    SetMobyState(self, 8, 1);
                    SetMobyState(self, 0xB, -1);
                } else {
                    SetAnimOnMobyAndParts(self, RandomIntBelow(2) + 6, 0, 0xA);
                    SetMobyState(self, 8, 1);
                }
                break;
            }
            SetMobyState(self, 0xE, 1);
        }
        if (*(s16 *)(vars + 0x80E) != 0 && *(u8 **)(vars + 0x38) != 0
            && *(s16 *)(*(u8 **)(vars + 0x38) + 0xAA) == 0x47 /* moby class 71 */ && *(u8 **)(vars + 0x7C0) != 0
            && self[0x42] == 0x10 && frame > 13.0f) {
            *(float *)(self + 0x48) = 0.0f;
            *(u8 **)(vars + 0x7BC) = 0;
            SetMobyState(self, 8, 1);
            SetMobyState(self, 0xC, -1);
        }
        break;
    }
    case 14:
        if (SetFirstPendingFlag(self) != 0) {
            if (*(s16 *)(vars + 0x80A) == 0)
                *(s16 *)(vars + 0x80A) = 600;
            if (*(u8 **)(vars + 0x7C0) != 0) {
                TransformMobyJointToWorld(self, 0, vec);
                SpawnExplosion(vec, 1, 10, 30, 0, 10, 45, 1, 0.5f, 20.0f, 0, 0, 0, 0);
                MarkMobySpawned(*(u8 **)(vars + 0x7C0));
                *(u8 **)(vars + 0x7C0) = 0;
            }
            if (*(u8 **)(vars + 0x7C4) != 0) {
                MarkMobySpawned(*(u8 **)(vars + 0x7C4));
                *(u8 **)(vars + 0x7C4) = 0;
            }
            if (*(u8 **)(vars + 0x7C8) != 0) {
                MarkMobySpawned(*(u8 **)(vars + 0x7C8));
                *(u8 **)(vars + 0x7C8) = 0;
            }
            if (self[0x43] != 8)
                StartAnimationBlended(self, 8, 0, 0xA);
        } else {
            qcopy(vars + 0x750, vars + 0x1F0);
            if (IsPositionVectorShort(self, vars + 0x1F0) != 0) {
                SetMobyState(self, 0xB, -1);
            } else if (FastDecTimer(vars + 0x80A) != 0) {
                SetDeathBits(self, 0, 3);
                DestroyPieceAndParts(self);
            }
        }
        break;
    }
}
