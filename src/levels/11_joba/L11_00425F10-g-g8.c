#include "common.h"

/* func_L11_00425F10: the level's two-switch AI update (state 0x95, then animation state 0x20).
   Built -G8 -g in its own unit: D_L11_001B0FEC/0FF8/0FFC are $gp-relative in ordinary flow,
   while the incomplete sda arrays below keep retail's lui form outside delay slots (and the
   $gp store of D_L11_001AED04 inside one). -g supplies the pre-div.s nop pair.
   The moby table base is read-only here; its const qualifier lets sched1 order the
   0x548 load before the 0x290 store as retail does. */

typedef int TI128 __attribute__((mode(TI)));
/* The hero block at D_00189E20; 0x80 is the position read as D_00189EA0 elsewhere. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

extern char D_00189E20[];
extern u8 *const D_L11_001B359C[] __attribute__((sda));
extern u8 *D_L11_001B368C[] __attribute__((sda));
extern void *D_L11_001FC420[];
extern s32 *D_L11_001FF580[];
extern s32 D_L11_001CAE40[];
extern s32 D_L11_001AED04[] __attribute__((sda));
extern s32 D_L11_001B35B8 __attribute__((sda));
extern s32 D_L11_001B0FEC __attribute__((sda));
extern s32 D_L11_001B0FF8 __attribute__((sda));
extern f32 D_L11_001B0FFC __attribute__((sda));
extern char D_L11_001A8F20[] __attribute__((sda));

extern void func_002A7470(u8 *a0, u32 a1, u32 a2, u32 a3);
extern void func_0029FCC0(u32 a0, s32 a1, f32 *a2);
extern f32 func_00283180(f32 a0);
extern f32 func_00283198(f32 a0);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_L11_004295A0(u8 *);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern s32 func_002B38B8(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002A7820(s32, s32);
extern f32 func_0029F530(u8 *);
extern f32 func_002A89A8(void *, s32, f32);
extern s32 func_002A77E0(s32);
extern void func_002B60B0(u8 *, f32, f32, f32, f32);
extern s32 func_002A8508(s32, s32);
extern u8 *func_L04_0033D4B0(u8 *);
extern s32 func_002B50E0(u8 *, void *, f32);
extern s32 func_002B6120(u8 *, void *);
extern s32 func_002B6228(u8 *, void *, s32, s32);
extern s32 func_L01_00321178(u8 *, void *);
extern s32 func_002B4FF0(u8 *, void *, f32);
extern f32 func_002AA458(void *, void *, void *, f32, f32, f32);
extern void func_002833F0(void *, void *);
extern f32 func_002AA3A8(void *, void *, f32, f32, f32, f32);
extern f32 func_00282C48(f32);
extern s32 func_002AEB60(u8 *, f32);
extern void func_L11_004349F8(u8 *, f32 *, f32 *, f32);
extern f32 func_002A7878(f32, f32);
extern void func_002C2210(void *, u32, u32, u32, s32, void *, f32, f32, f32, s32);
extern f32 func_002A7E08(u8 *, void *, void *, f32, f32, f32);
extern void func_L00_003294F0(u8 *, s32);
extern void func_002A8C28(void *, void *, s32, f32, f32, f32, s32, s32, s32);
extern s32 func_002B3890(u8 *);
extern void func_0029F338(void *);
extern s32 func_002B1C20(u8 *, void *);
extern void func_002A6C58(u8 *, s32, s32);
extern void func_L01_003E9CF8(u8 *, s32, void *);
extern void func_002AF1D0(u8 *, void *, s32, s32);
extern void func_002AC728(u8 *, void *, f32, f32, s32);
extern s32 func_L11_00425EC0(u8 *);
extern u8 *func_0029EFD0(s32);
extern void func_002A0F48(void *);
extern void func_00283898(void *, s32, f32);
extern void func_L11_0042A420(u8 *arg0);
extern int func_L11_0042A158(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00283C80(f32, f32);
extern void func_00282F20(void *, void *, f32);
extern int func_002A7EA0(void *, void *, void *, f32, f32, f32, f32, int);

/* Updates one of the Joba tribe fighters (a sibling of the Tribesman). It picks animations from its mode, chases and faces the hero, throws spark shots, rides or follows a linked partner, and removes itself when it is done. */
void func_L11_00425F10(u8 *moby) {
    f32 workVec[4] __attribute__((aligned(16)));
    f32 offsetVec[4] __attribute__((aligned(16)));
    f32 startVec[4] __attribute__((aligned(16)));
    f32 endVec[4] __attribute__((aligned(16)));
    u8 *vars;
    f32 startZ;
    f32 maxTurn;
    f32 turnAngle;
    s32 spareInt1;
    s32 bumpCount;
    f32 bestDistance;
    s32 nodeIdx;
    s32 nearestNode;
    f32 nodeDistance;
    s32 spareInt2;
    s32 spareInt3;
    f32 spareFloat1;
    s32 hitFlags;
    u8 *mount;
    u8 *saddle;
    u8 *hurtEffect;
    u8 *rider;
    u8 *riderVars;
    f32 tiltAngle;
    f32 spareFloat2;
    f32 groundDistance;
    f32 groundDistance2;
    s32 partnerKind;
    s32 roll;
    u8 *partner;
    u8 partnerFrame;
    s32 *pathA;
    f32 distToStartA;
    s32 *pathB;
    f32 distToStartB;
    f32 spareFloat3;
    u8 groupId;
    u16 *groupCursor;
    u8 *mobyTable;
    u8 *groupMember;
    u8 *memberVars;
    f32 memberDistance;
    u8 *linked;
    u8 *linkedVars;
    u8 *linkedMoby;
    f32 spareFloat4;
    u8 *linkedMoby2;
    s32 *patrolPoint;
    s32 *patrolPoint2;
    u8 *linkedMoby3;
    f32 spareFloat5;
    f32 spareFloat6;
    s32 chance;
    f32 spareFloat7;
    f32 sparkSize;
    f32 animFrame;
    s32 sparkSign;
    f32 spareFloat8;
    f32 sparkSize2, animFrame2;
    f32 animFrame3;
    s32 sparkSign2;

    if (D_L11_001CAE40[0] != 0)
        return;
    if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x6F && moby[0x95] != 4)
        return;
    startZ = *(f32 *)(moby + 0x18);
    vars = *(u8 **)(moby + 0x68);
    if (UpdateJobianLieutenantMoby(moby) != 0) {
        MarkMobySpawned(moby);
        return;
    }
    switch (moby[0x95]) {
    case 9:
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 6.0f) {
            maxTurn = 1.5707965f;
            turnAngle = fast_subtract_rotations(FastMatrixHelperA(*(f32 *)(((Hero *)gHeroState)->ptr[0x2290 / 4] + 0x10) - *(f32 *)(moby + 0x10),
                                            *(f32 *)(((Hero *)gHeroState)->ptr[0x2290 / 4] + 0x14) - *(f32 *)(moby + 0x14)),
                              *(f32 *)(moby + 0xF8));
            if (IsThirdPendingFlagSet(moby) != 0)
                turnAngle = -turnAngle;
            if (turnAngle > maxTurn)
                turnAngle = maxTurn;
            else if (turnAngle < -maxTurn)
                turnAngle = -maxTurn;
            *(f32 *)(vars + 0x308) = turnAngle;
        }
        if (((Hero *)gHeroState)->i[0x1248 / 4] != 0x41)
            moby[0x95] = 0;
        break;
    case 0:
        if (SetSecondPendingFlag(moby) != 0)
            SetControllerSpeedLimits(moby, 0.0015277779f, 0.045833334f, 0.001163553f, 0.10471977f);
        if (*(s16 *)(vars + 0x264) == 2) {
            if (*(s32 *)(vars + 0x284) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x1A, 2);
            }
            if (*(s32 *)(vars + 0x548) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x19, 2);
            } else if (*(s32 *)(vars + 0x294) == 1) {
                if (moby[0x43] != 0xA)
                    StartAnimationBlended(moby, 0xA, RandomIntBelow(4), RandomIntRange(7, 0x14));
                SetMobyState(moby, 0x13, 2);
            } else {
                if (*(s32 *)(vars + 0x570) != 0) {
                    if (moby[0x43] != 2)
                        StartAnimationBlended(moby, 2, 0, 0xA);
                    SetMobyState(moby, 0x13, 3);
                } else {
                    *(s32 *)(vars + 0x290) = 1;
                    if (moby[0x43] != 2)
                        StartAnimationBlended(moby, 2, 0, 0x28);
                    SetMobyState(moby, 0x13, 3);
                }
            }
        } else if (*(s16 *)(vars + 0x266) != 0) {
            if (*(s32 *)(vars + 0x558) != -1) {
                bumpCount = *(s32 *)(vars + 0x560);
                if (bumpCount == 1) {
                    if (moby[0x43] != 9)
                        StartAnimationBlended(moby, 9, 0, RandomIntRange(5, 0xF));
                    SetMobyState(moby, 6, -1);
                } else if (bumpCount >= 2) {
                    if (moby[0x43] != 3)
                        StartAnimationBlended(moby, 3, 0, RandomIntRange(5, 0xF));
                    SetMobyState(moby, 7, -1);
                    SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
                }
            }
            if (*(s32 *)(vars + 0x548) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x19, 2);
            }
            if ((u16)(*(s16 *)(vars + 0x264) - 1) < 2) {
                if (*(s32 *)(vars + 0x294) == 1) {
                    if (moby[0x43] != 0xA)
                        StartAnimationBlended(moby, 0xA, 0, RandomIntRange(0xA, 0x14));
                    SetMobyState(moby, 0x13, 2);
                } else if (*(s32 *)(vars + 0x570) != 0) {
                    if (moby[0x43] != 2)
                        StartAnimationBlended(moby, 2, 0, 0x28);
                    SetMobyState(moby, 0x13, 3);
                } else {
                    *(s32 *)(vars + 0x290) = 1;
                    if (moby[0x43] != 2)
                        StartAnimationBlended(moby, 2, 0, 0xA);
                    SetMobyState(moby, 0x13, 3);
                }
            }
            *(s16 *)(vars + 0x266) = 0;
        }
        break;
    case 1:
        if (SetSecondPendingFlag(moby) != 0) {
            SetControllerSpeedLimits(moby, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
            *(f32 *)(vars + 0x12C) = 6.0f;
        }
        if ((u16)(*(s16 *)(vars + 0x264) - 1) < 2) {
            if (*(s32 *)(vars + 0x284) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                bestDistance = 100.0f;
                SetMobyState(moby, 0x1A, 2);
                nodeIdx = 0;
                nearestNode = 0;
                for (; nodeIdx < *D_L11_001FF580[*(s32 *)(vars + 0x284)]; ) {
                    nodeDistance = vec_distance_xy(moby + 0x10, (u8 *)D_L11_001FF580[*(s32 *)(vars + 0x284)] + 0x10 + nodeIdx * 0x10);
                    if (nodeDistance < bestDistance) {
                        bestDistance = nodeDistance;
                        nearestNode = nodeIdx;
                    }
                    nodeIdx++;
                }
                SetPathFollowerNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x284)], -1, nearestNode);
            }
            if (*(s32 *)(vars + 0x548) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x19, 2);
            } else if (*(s32 *)(vars + 0x294) == 1) {
                if (moby[0x43] != 0xA)
                    StartAnimationBlended(moby, 0xA, RandomIntBelow(4), RandomIntRange(7, 0x14));
                SetMobyState(moby, 0x13, 2);
            } else {
                *(s32 *)(vars + 0x290) = 1;
                if (moby[0x43] != 2)
                    StartAnimationBlended(moby, 2, 0, 0x28);
                SetMobyState(moby, 0x13, 3);
            }
        }
        break;
    case 2:
        if (SetSecondPendingFlag(moby) != 0)
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.003781547f, 0.29670602f);
        if ((u16)(*(s16 *)(vars + 0x264) - 1) >= 2 && moby[0x20] != 0x19 && RandomIntBelow(4) == 1) {
            *(f32 *)(moby + 0x48) = 1.0f;
            if (moby[0x43] != 2)
                StartAnimationBlended(moby, 2, 0, 0xA);
            SetMobyState(moby, 0xE, 1);
            *(s32 *)(vars + 0x560) = 0;
            *(s16 *)(vars + 0x260) = RandomIntRange(0x244, 0x258);
        }
        if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x31 && *(s32 *)(vars + 0x558) != -1) {
            if (moby[0x43] != 3)
                StartAnimationBlended(moby, 3, 0, RandomIntRange(5, 0xF));
            SetMobyState(moby, 7, 8);
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
        }
        break;
    case 8:
        if (((Hero *)gHeroState)->i[0x2294 / 4] != 0x31) {
            if (*(s32 *)(vars + 0x548) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x19, 2);
            } else {
                if (moby[0x43] != 0xA)
                    StartAnimationBlended(moby, 0xA, 0, 0xA);
                SetMobyState(moby, 0x13, 2);
            }
        }
        break;
    case 4:
        if (*(f32 *)(vars + 0x20) > 0.0f)
            StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        hitFlags = DispatchActionByKind(moby, vars + 0x60);
        if (hitFlags & 1) {
            MarkMobySpawned(*(u8 **)(vars + 0x278));
            D_L11_001AED04[0] = D_L11_001AED04[0] - 1;
            SetDeathBits(moby, 0, 3);
            QueueMobyForGlowEffect(moby, 0, 0);
            return;
        }
        if (hitFlags & 2) {
            *(s16 *)(vars + 0x26) = 0;
            if ((u16)(*(s16 *)(vars + 0x264) - 1) < 2) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x17, 2);
                if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 6.5f &&
                    FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                     ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.6108653f) {
                    if (moby[0x43] != 5)
                        StartAnimationBlended(moby, 5, 1, 4);
                    SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
                    SetMobyState(moby, 0x1D, 2);
                }
            } else if (*(s32 *)(vars + 0x558) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, RandomIntRange(5, 0xF));
                SetMobyState(moby, 7, 0);
                SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
            } else {
                if (moby[0x43] != 0)
                    StartAnimationBlended(moby, 0, 0, 0xA);
                SetMobyState(moby, 0xE, 1);
                *(s16 *)(vars + 0x260) = RandomIntRange(0x244, 0x258);
            }
        }
        break;
    case 3:
        if (SetSecondPendingFlag(moby) != 0)
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(vars + 0x294) == 1) {
            if (moby[0x43] != 3)
                StartAnimationBlended(moby, 3, 0, 0xA);
            SetMobyState(moby, 0x17, 2);
            if (*(s32 *)(vars + 0x284) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x1A, 2);
            }
        }
        if ((u16)(*(s16 *)(vars + 0x264) - 1) >= 2) {
            if (moby[0x43] != 0xB)
                StartAnimationBlended(moby, 0xB, 0, 0x1E);
            SetMobyState(moby, 0xE, 1);
            *(s16 *)(vars + 0x260) = RandomIntRange(0x244, 0x258);
            *(s32 *)(vars + 0x560) = 0;
        }
        break;
    case 5:
        if (*(u8 **)(vars + 0x278) != 0)
            CopyJointTransformToObject(moby, *(u8 **)(vars + 0x278), 1, 0);
        mount = *(u8 **)(vars + 0x274);
        qcopy(moby + 0x10, mount + 0x10);
        qcopy(moby + 0xF0, mount + 0xF0);
        saddle = *(u8 **)(vars + 0x280);
        qcopy(saddle + 0x10, moby + 0x10);
        qcopy(saddle + 0xF0, moby + 0xF0);
        qcopy(saddle + 0x10, moby + 0x10);
        *(f32 *)(saddle + 0x18) = *(f32 *)(saddle + 0x18) + 0.65f;
        if (*(s32 *)(vars + 0x26C) == 0) {
            SpawnExplosionWithSparks(moby, *(u8 **)(vars + 0x278) + 0x10, 0.5f, 3.0f, -1);
            MarkMobySpawned(*(u8 **)(vars + 0x278));
            MarkMobySpawned(*(u8 **)(vars + 0x280));
            *(s32 *)(*(u8 **)(*(u8 **)(vars + 0x274) + 0x68) + 0x27C) = 0;
            SetMobyState(moby, 2, 6);
        } else if (TickTribesmanLinkedClock(moby) != 0) {
            SpawnExplosionWithSparks(moby, *(u8 **)(vars + 0x278) + 0x10, 0.5f, 3.0f, -1);
            MarkMobySpawned(*(u8 **)(vars + 0x278));
            MarkMobySpawned(*(u8 **)(vars + 0x280));
            *(s32 *)(*(u8 **)(*(u8 **)(vars + 0x274) + 0x68) + 0x27C) = 0;
            if (moby[0x43] != 0)
                StartAnimationBlended(moby, 0, 0, 0);
            SetMobyState(moby, 3, 6);
        }
        break;
    case 6:
        if (SetSecondPendingFlag(moby) != 0) {
            hurtEffect = CreateMoby(0x9AC /* moby class 2476 */);
            *(u8 **)(vars + 0x29C) = hurtEffect;
            if (hurtEffect != 0) {
                hurtEffect[0x30] = moby[0x30];
                *(u16 *)(*(u8 **)(vars + 0x29C) + 0x32) = *(u16 *)(moby + 0x32);
                (*(u8 **)(vars + 0x29C))[0x31] = 1;
                *(s64 *)(*(u8 **)(vars + 0x29C) + 0x38) = *(s64 *)(moby + 0x38);
                func_002A0F48(*(u8 **)(vars + 0x29C));
                *(s32 *)(*(u8 **)(vars + 0x29C) + 0x98) = 0;
                CopyJointTransformToObject(moby, *(u8 **)(vars + 0x29C), 3, 0);
                *(s32 *)(vars + 0x290) = 1;
                *(f32 *)(moby + 0xF0) = 0.0f;
                *(f32 *)(moby + 0xF4) = 0.0f;
                euler_rotation_basis(moby + 0xC0, moby + 0xF0);
            } else {
                MarkMobySpawned(moby);
                return;
            }
        }
        break;
    case 7:
        *(s32 *)(vars + 0x290) = 0;
        rider = gMobyTable_L11[0] + (*(s32 *)(vars + 0x548) << 8);
        riderVars = *(u8 **)(rider + 0x68);
        if (moby[0x20] != 0x22) {
            StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
            tiltAngle = FastMatrixHelperA(vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0xD0 / 4]),
                                 ((Hero *)gHeroState)->f[0xD8 / 4] - *(f32 *)(moby + 0x18));
            build_axis_rotation_quaternion(riderVars + 0x10, 1, -tiltAngle);
        }
        *(f32 *)(moby + 0x10) = *(f32 *)(rider + 0x10);
        *(f32 *)(moby + 0x14) = *(f32 *)(rider + 0x14);
        *(f32 *)(moby + 0x18) = *(f32 *)(rider + 0x18) + 1.5f;
        euler_rotation_basis(rider + 0xC0, moby + 0xF0);
        if ((u16)(*(s16 *)(vars + 0x264) - 1) >= 2 && moby[0x20] != 0x20) {
            if (moby[0x43] != 0)
                StartAnimationBlended(moby, 0, 0, 0xA);
            StartAnimationBlended(rider, 0, 0, 0xA);
            SetMobyState(moby, 0x22, -1);
        }
        if (moby[0x20] == 0x22 && *(s16 *)(vars + 0x264) == 2) {
            if (moby[0x43] != 0)
                StartAnimationBlended(moby, 0, 0, 0xA);
            SetMobyState(moby, 0x21, -1);
            StartAnimationBlended(rider, 1, 0, 0xA);
        }
        break;
    }

    switch (moby[0x20]) {
    case 1:
        break;
    case 2:
        if (moby[0x60] & 2) {
            *(u16 *)(moby + 0x34) |= 0x5000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            SetMobyState(moby, 0xE, 1);
            if (*(s16 *)(vars + 0x260) < 0x12C)
                *(s16 *)(vars + 0x260) = RandomIntRange(0x1E0, 0x258);
            if (moby[0x43] != 1)
                StartAnimationBlended(moby, 1, 0, 0xA);
        }
        groundDistance = GetMobyAnimationValue(moby);
        if (groundDistance >= 10.0f)
            *(f32 *)(moby + 0x18) = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
        if (groundDistance >= 1.5f && groundDistance <= 17.0f) {
            workVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            workVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            workVec[2] = 0.0f;
            FastVecAdd(moby + 0x10, moby + 0x10, workVec);
            offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            offsetVec[2] = 0.0f;
            FastVecAdd(moby + 0x10, moby + 0x10, offsetVec);
        }
        break;
    case 3:
        if (moby[0x60] & 2) {
            *(u16 *)(moby + 0x34) |= 0x5000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            SetMobyState(moby, 0xE, 1);
            if (*(s16 *)(vars + 0x260) < 0x12C)
                *(s16 *)(vars + 0x260) = RandomIntRange(0x1E0, 0x258);
            if (moby[0x43] != 1)
                StartAnimationBlended(moby, 1, 0, 0xA);
        }
        groundDistance2 = GetMobyAnimationValue(moby);
        if (groundDistance2 >= 10.0f)
            *(f32 *)(moby + 0x18) = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
        if (groundDistance2 >= 1.5f && groundDistance2 <= 17.0f) {
            workVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            workVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8) + 3.141593f) * 0.15f;
            workVec[2] = 0.0f;
            offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8) + 1.5707965f) * 0.05f;
            offsetVec[2] = 0.0f;
            qcopy(startVec, moby + 0x10);
            FastVecAdd(startVec, moby + 0x10, offsetVec);
            FastVecAdd(startVec, moby + 0x10, workVec);
            MoveOverGround(moby, moby + 0x10, startVec, 0.5f, 0.55f, 0.5f, 0.523598849773407f, 0);
        }
        break;
    case 5:
        if (*(u8 **)(vars + 0x55C) != 0) {
            partnerKind = *(s32 *)(vars + 0x540);
            if (partnerKind == 1 && moby[0x42] == 0xD) {
                roll = RandomIntBelow(0xC8);
                if (roll == partnerKind) {
                    if (moby[0x43] != 0xC)
                        StartAnimationBlended(moby, 0xC, 0, 0x1E);
                    if (RandomIntBelow(3) == roll && moby[0x43] != 0xB)
                        StartAnimationBlended(moby, 0xB, 0, 0x1E);
                }
            }
            if ((u8)(moby[0x42] - 0xB) < 2 && (moby[0x60] & 2)) {
                if (moby[0x43] != 0xE)
                    StartAnimationBlended(moby, 0xE, 0, 0x1E);
                partner = *(u8 **)(vars + 0x55C);
                if (*(s16 *)(partner + 0xAA) == 0xCF6 /* moby class 3318 */) {
                    *(s32 *)(*(u8 **)(partner + 0x68) + 0x540) = 1;
                    *(s32 *)(vars + 0x540) = 2;
                }
            }
            if (moby[0x42] == 0xE && (moby[0x60] & 2)) {
                if (moby[0x43] != 0xF)
                    StartAnimationBlended(moby, 0xF, 0, 0x1E);
                if (*(s32 *)(vars + 0x540) == 1 && moby[0x43] != 0xD)
                    StartAnimationBlended(moby, 0xD, 0, 0x1E);
            }
            if (*(s32 *)(vars + 0x540) == 1 && moby[0x42] == 0xF && moby[0x43] != 0xE)
                StartAnimationBlended(moby, 0xE, 0, 0x14);
            if (*(s32 *)(vars + 0x540) == 3) {
                partnerFrame = (*(u8 **)(vars + 0x55C))[0x42];
                if (partnerFrame == 0xE && moby[0x43] != partnerFrame)
                    StartAnimationBlended(moby, 0xE, 0, 0x23);
            }
        }
        break;
    case 6:
        *(s32 *)(vars + 0x290) = 1;
        if (moby[0x60] & 2) {
            SetMobyState(moby, 7, -1);
            if (moby[0x43] != 4)
                StartAnimationBlended(moby, 4, 0, 0x1E);
            *(s32 *)(vars + 0x290) = 0;
        }
        break;
    case 7:
        if (FollowPathNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x558)]) != 0) {
            SetMobyState(moby, 8, -1);
            if (moby[0x43] != 9)
                StartAnimationBlended(moby, 9, 0, 0x14);
        }
        break;
    case 8:
        if (moby[0x60] & 2) {
            SetControllerSpeedLimits(moby, 0.0015277779f, 0.045833334f, 0.001163553f, 0.10471977f);
            if (CountMobysInGroupNotInState(moby[0x21], -1) >= 2) {
                *(u8 **)(vars + 0x55C) = FindLinkedObject(moby);
                SetMobyState(moby, 0xA, -1);
                if (moby[0x43] != 0xD)
                    StartAnimationBlended(moby, 0xD, 0, 0x1E);
                *(s32 *)(vars + 0x540) = 1;
                if ((*(u8 **)(vars + 0x55C))[0x42] == 0xD) {
                    if (moby[0x43] != 0xF)
                        StartAnimationBlended(moby, 0xF, 0, 0x1E);
                    *(s32 *)(vars + 0x540) = 2;
                }
            }
        }
        break;
    case 10:
        StepMovementController(moby, moby + 0x10, FastMatrixHelperA(*(f32 *)(*(u8 **)(vars + 0x55C) + 0x10) - *(f32 *)(moby + 0x10),
                                                       *(f32 *)(*(u8 **)(vars + 0x55C) + 0x14) - *(f32 *)(moby + 0x14)));
        if (FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(*(f32 *)(*(u8 **)(vars + 0x55C) + 0x10) - *(f32 *)(moby + 0x10),
                                                              *(f32 *)(*(u8 **)(vars + 0x55C) + 0x14) - *(f32 *)(moby + 0x14))) < 0.087266475f)
            SetMobyState(moby, 5, -1);
        break;
    case 11:
        SetControllerSpeedLimits(moby, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
        if (FollowPathNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x54C)]) != 0) {
            SetMobyState(moby, 0xC, -1);
            if (moby[0x43] != 1)
                StartAnimationBlended(moby, 1, 0, 0x14);
        }
        break;
    case 12:
        if (moby[0x60] & 2) {
            pathA = D_L11_001FF580[*(s32 *)(vars + 0x54C)];
            distToStartA = vec_distance_xy(moby + 0x10, pathA + 4);
            if (vec_distance_xy(moby + 0x10, (u8 *)pathA + *pathA * 0x10) < distToStartA)
                SetPathFollowerNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x54C)], 0, *pathA - 1);
            else
                SetPathFollowerNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x54C)], *pathA - 1, 0);
            SetMobyState(moby, 0xB, -1);
            if (moby[0x43] != 4)
                StartAnimationBlended(moby, 4, 0, 0x14);
        }
        break;
    case 14:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 4)
                StartAnimationBlended(moby, 4, 0, 0x14);
            SetMobyState(moby, 0xF, -1);
            if (*(s32 *)(vars + 0x56C) != -1)
                SetMobyState(moby, 0x11, -1);
        }
        break;
    case 15:
        TurnMobyTowardTarget(moby, vars + 0x110);
        if (vec_distance_xy(moby + 0x10, vars + 0x110) < 2.0f) {
            SetMobyState(moby, 0x10, -1);
            if (moby[0x43] != 9)
                StartAnimationBlended(moby, 9, 0, 0x14);
        }
        break;
    case 17:
        SetControllerSpeedLimits(moby, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
        if (FollowPathNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x56C)]) != 0) {
            SetMobyState(moby, 0x12, -1);
            if (moby[0x43] != 9)
                StartAnimationBlended(moby, 9, 0, 0x14);
        }
        break;
    case 18:
        if (moby[0x60] & 2) {
            pathB = D_L11_001FF580[*(s32 *)(vars + 0x56C)];
            distToStartB = vec_distance_xy(moby + 0x10, pathB + 4);
            if (vec_distance_xy(moby + 0x10, (u8 *)pathB + *pathB * 0x10) < distToStartB)
                SetPathFollowerNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x56C)], 0, *pathB - 1);
            else
                SetPathFollowerNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x56C)], *pathB - 1, 0);
            SetMobyState(moby, 0x11, -1);
            if (moby[0x43] != 4)
                StartAnimationBlended(moby, 4, 0, 0x14);
        }
        break;
    case 23:
        if (*(s32 *)(vars + 0x57C) != -1) {
            SetMobyState(moby, 0x18, -1);
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f &&
                   FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                    ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.3490659f) {
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 6);
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            SetMobyState(moby, 0x1C, 2);
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
            StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        } else if (*(s32 *)(vars + 0x528) != 0) {
            if (WalkTowardTargetPoint(moby, &((Hero *)gHeroState)->f[0x80 / 4], *(f32 *)(moby + 0xF8), 7.0f, 0.25f, *(f32 *)(vars + 0x298)) != 0) {
                groupId = moby[0x21];
                if (D_L11_001B35B8 >= groupId && CountMobysInGroupNotInState(groupId, -1) >= 2) {
                    mobyTable = gMobyTable_L11[0];
                    groupCursor = gGroupIdLists[moby[0x21]];
                    do {
                        groupMember = mobyTable + ((*groupCursor & 0x7FFF) << 8);
                        memberVars = *(u8 **)(groupMember + 0x68);
                        if (*(s32 *)(memberVars + 0x294) == 0) {
                            memberDistance = vec_distance_xy(groupMember + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]);
                            if (memberDistance < vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) && *(f32 *)(memberVars + 0x20) > 0.0f) {
                                *(s32 *)(memberVars + 0x294) = 1;
                                *(s32 *)(vars + 0x294) = 0;
                                if (moby[0x43] != 2)
                                    StartAnimationBlended(moby, 2, 0, 0xA);
                                SetMobyState(moby, 0x13, 3);
                            }
                            break;
                        }
                    } while (*(s16 *)groupCursor++ >= 0);
                }
            }
        } else {
            TurnTowardTargetAndStepMovement(moby, &((Hero *)gHeroState)->f[0x80 / 4], *(f32 *)(vars + 0x298));
        }
        break;
    case 24:
        *(s32 *)(vars + 0x290) = 0;
        SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0033936962f, 0.27925274f);
        *(TI128 *)workVec = *(TI128 *)&D_L11_001B368C[0][(*(s32 *)(vars + 0x57C) << 7) + 0x30];
        TurnMobyTowardTarget(moby, workVec);
        if (vec_distance_xy(moby + 0x10, workVec) < 1.5f) {
            if (moby[0x43] != 0x12)
                StartAnimationBlended(moby, 0x12, 0, 0x10);
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            SetMobyState(moby, 0x1B, 2);
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 6);
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            SetMobyState(moby, 0x1D, 2);
        }
        break;
    case 25:
        linked = gMobyTable_L11[0] + (*(s32 *)(vars + 0x548) << 8);
        linkedVars = *(u8 **)(linked + 0x68);
        if (linked[0x20] != 5) {
            SpringVectorToTarget(linked + 0xF0, moby + 0xF0, vars + 0x550, 0.001163553f, 0.0023271059f, 0.10471977f);
            euler_rotation_basis(linked + 0xC0, linked + 0xF0);
            *(f32 *)(linked + 0x18) = *(f32 *)(linked + 0x18) + ((*(f32 *)(linkedVars + 0x5C) - 1.2f) - *(f32 *)(linked + 0x18)) * 0.11f;
        }
        TurnMobyTowardTarget(moby, linked + 0x10);
        if (vec_distance_xy(moby + 0x10, linked + 0x10) < 1.5f && linked[0x20] != 5) {
            linked[0x20] = 6;
            *(f32 *)(moby + 0x10) = *(f32 *)(linked + 0x10);
            *(f32 *)(moby + 0x14) = *(f32 *)(linked + 0x14);
            *(f32 *)(moby + 0x18) = *(f32 *)(linked + 0x18) + 1.5f;
            *(f32 *)(vars + 0x554) = *(f32 *)(linked + 0x18) + 0.75f;
            if (moby[0x43] != 0)
                StartAnimationBlended(moby, 0, 0, 0x19);
            SetMobyState(moby, 0x20, 7);
            moby[0xBC] = 1;
        }
        break;
    case 32:
        linkedMoby = gMobyTable_L11[0] + (*(s32 *)(vars + 0x548) << 8);
        SpringFloatToGoal(linkedMoby + 0x18, vars + 0x550, *(f32 *)(vars + 0x554), 0.00027777778f, 0.0016666667f, 0.033333335f);
        *(f32 *)(moby + 0x18) = *(f32 *)(linkedMoby + 0x18) + 1.5f;
        if (FloatAbs(*(f32 *)(linkedMoby + 0x18) - *(f32 *)(vars + 0x554)) < 0.1f) {
            if (moby[0x43] != 0)
                StartAnimationBlended(moby, 0, 0, 5);
            SetMobyState(moby, 0x21, -1);
            if (linkedMoby[0x43] != 1)
                StartAnimationBlended(linkedMoby, 1, 0, 5);
        }
        if (FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                              ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.26179942f &&
            linkedMoby[0x43] != 1) {
            StartAnimationBlended(linkedMoby, 1, 0, 5);
            if (moby[0x43] != 0)
                StartAnimationBlended(moby, 0, 0, 5);
        } else if (linkedMoby[0x42] == 1) {
            if (IsValueWithinStepOfThreshold(linkedMoby, 6.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby, 12.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby, 0.0f) != 0) {
                TransformMobyJointToWorld((u32)linkedMoby, 1, workVec);
                FastVecSub(offsetVec, &((Hero *)gHeroState)->f[0xD0 / 4], workVec);
                vec_scale_to_length(offsetVec, offsetVec, 0.5f);
                SpawnStateVectorMoby(linkedMoby, offsetVec, workVec, 1.0f);
            } else if (IsValueWithinStepOfThreshold(linkedMoby, 3.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby, 9.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby, 15.0f) != 0) {
                TransformMobyJointToWorld((u32)linkedMoby, 0, workVec);
                FastVecSub(offsetVec, &((Hero *)gHeroState)->f[0xD0 / 4], workVec);
                vec_scale_to_length(offsetVec, offsetVec, 0.5f);
                SpawnStateVectorMoby(linkedMoby, offsetVec, workVec, 1.0f);
            }
        }
        break;
    case 33:
        linkedMoby2 = gMobyTable_L11[0] + (*(s32 *)(vars + 0x548) << 8);
        if (IsValueWithinStepOfThreshold(linkedMoby2, 6.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby2, 12.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby2, 0.0f) != 0) {
            TransformMobyJointToWorld((u32)linkedMoby2, 1, workVec);
            FastVecSub(offsetVec, &((Hero *)gHeroState)->f[0xD0 / 4], workVec);
            vec_scale_to_length(offsetVec, offsetVec, 0.5f);
            SpawnStateVectorMoby(linkedMoby2, offsetVec, workVec, 1.0f);
        } else if (IsValueWithinStepOfThreshold(linkedMoby2, 3.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby2, 9.0f) != 0 || IsValueWithinStepOfThreshold(linkedMoby2, 15.0f) != 0) {
            TransformMobyJointToWorld((u32)linkedMoby2, 0, workVec);
            FastVecSub(offsetVec, &((Hero *)gHeroState)->f[0xD0 / 4], workVec);
            vec_scale_to_length(offsetVec, offsetVec, 0.5f);
            SpawnStateVectorMoby(linkedMoby2, offsetVec, workVec, 1.0f);
        }
        break;
    case 34:
        if (*(s32 *)(vars + 0x564) != -1) {
            patrolPoint = (s32 *)((u8 *)D_L11_001FF580[*(s32 *)(vars + 0x564)] + *(s32 *)(vars + 0x568) * 0x10);
            linkedMoby3 = gMobyTable_L11[0] + (*(s32 *)(vars + 0x548) << 8);
            StepMovementController(moby, moby + 0x10, FastMatrixHelperA(*(f32 *)((u8 *)patrolPoint + 0x10) - *(f32 *)(moby + 0x10),
                                                           *(f32 *)((u8 *)patrolPoint + 0x14) - *(f32 *)(moby + 0x14)));
            *(f32 *)(moby + 0x10) = *(f32 *)(linkedMoby3 + 0x10);
            *(f32 *)(moby + 0x14) = *(f32 *)(linkedMoby3 + 0x14);
            *(f32 *)(moby + 0x18) = *(f32 *)(linkedMoby3 + 0x18) + 1.5f;
            euler_rotation_basis(linkedMoby3 + 0xC0, moby + 0xF0);
            patrolPoint2 = (s32 *)((u8 *)D_L11_001FF580[*(s32 *)(vars + 0x564)] + *(s32 *)(vars + 0x568) * 0x10);
            if (FastMatrixHelperA(*(f32 *)((u8 *)patrolPoint2 + 0x10) - *(f32 *)(moby + 0x10),
                              *(f32 *)((u8 *)patrolPoint2 + 0x14) - *(f32 *)(moby + 0x14)) <= 0.6108653f) {
                if (++*(s32 *)(vars + 0x568) >= 2)
                    *(s32 *)(vars + 0x568) = 0;
            }
        }
        break;
    case 19:
        *(s32 *)(vars + 0x290) = 0;
        StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        if (*(s32 *)(vars + 0x294) == 0) {
            *(s32 *)(vars + 0x290) = 1;
            if (moby[0x43] != 0x11)
                StartAnimationBlended(moby, 0x11, 0, 0xA);
            SetMobyState(moby, 0x14, -1);
        } else {
            if (moby[0x43] != 3)
                StartAnimationBlended(moby, 3, 0, 0xA);
            SetMobyState(moby, 0x17, 2);
            if (*(s32 *)(vars + 0x284) != -1) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x1A, 2);
            }
        }
        break;
    case 20:
        TurnTowardPosition(moby, ((Hero *)gHeroState)->ptr[0x2290 / 4], vars + 0x27C, 0.001f, 0.01f, 0.1f);
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 0xA);
            SetMobyState(moby, 0x1C, -1);
        }
        chance = RandomIntBelow(3);
        if (chance == 1 && (moby[0x60] & 2)) {
            if (moby[0x43] != 0xA)
                StartAnimationBlended(moby, 0xA, 0, 0xA);
            if (RandomIntBelow(3) == chance && moby[0x43] != 9)
                StartAnimationBlended(moby, 9, 0, 0xA);
            SetMobyState(moby, 0x13, 3);
        }
        break;
    case 21:
        if (*(s32 *)(vars + 0x528) != 0) {
            if (WalkTowardTargetPoint(moby, &((Hero *)gHeroState)->f[0x80 / 4], *(f32 *)(moby + 0xF8), 7.0f, 0.25f, *(f32 *)(vars + 0x298)) != 0) {
                if (moby[0x43] != 0x11)
                    StartAnimationBlended(moby, 0x11, 0, 0xA);
                SetMobyState(moby, 0x14, -1);
            }
        } else {
            TurnTowardTargetAndStepMovement(moby, &((Hero *)gHeroState)->f[0x80 / 4], *(f32 *)(vars + 0x298));
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 8.0f) {
            if (moby[0x43] != 0x11)
                StartAnimationBlended(moby, 0x11, 0, 0xA);
            SetMobyState(moby, 0x14, -1);
        }
        break;
    case 22:
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f &&
            FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                             ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.3490659f) {
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 6);
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            SetMobyState(moby, 0x1C, 2);
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
            StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                           ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        } else if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) > 6.0f) {
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            if (moby[0x43] != 3)
                StartAnimationBlended(moby, 3, 0, 0xA);
            SetMobyState(moby, 0x17, -1);
        } else {
            SetControllerSpeedLimits(moby, 0.00055555557f, 0.016666668f, 0.001163553f, 0.10471977f);
            TurnTowardTargetAndStepMovement(moby, &((Hero *)gHeroState)->f[0x80 / 4], *(f32 *)(vars + 0x298));
        }
        break;
    case 26:
        *(f32 *)(vars + 0x174) = 1.5f;
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 2);
            SetMobyState(moby, 0x1C, -1);
            *(s32 *)(vars + 0x284) = -1;
            *(f32 *)(vars + 0x164) = 0.00083333335f;
        } else {
            *(f32 *)(vars + 0x164) = 0.004166667f;
            if (FollowPathNodes(moby, D_L11_001FF580[*(s32 *)(vars + 0x284)]) != 0) {
                if (*(s32 *)(vars + 0x294) == 1) {
                    if (moby[0x43] != 3)
                        StartAnimationBlended(moby, 3, 0, 0xA);
                    SetMobyState(moby, 0x17, 2);
                } else {
                    *(s32 *)(vars + 0x290) = 1;
                    if (RandomIntBelow(3) == 1) {
                        if (moby[0x43] != 2)
                            StartAnimationBlended(moby, 2, 0, 0xA);
                        SetMobyState(moby, 0x13, 3);
                    } else {
                        if (moby[0x43] != 3)
                            StartAnimationBlended(moby, 3, 0, 0xA);
                        SetMobyState(moby, 0x15, 3);
                    }
                }
                *(s32 *)(vars + 0x284) = -1;
            }
        }
        break;
    case 27:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x13)
                StartAnimationBlended(moby, 0x13, 0, 6);
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            SetMobyState(moby, 0x1C, 2);
        }
        StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        if (moby[0x42] == 0x12) {
            animFrame = GetMobyAnimationValue(moby);
            TransformMobyJointToWorld(*(u32 *)(vars + 0x278), 0, workVec);
            offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
            offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
            offsetVec[2] = 0.0f;
            FastVecAdd(workVec, workVec, offsetVec);
            workVec[2] = workVec[2] - 0.05f;
            sparkSize = RandomFloatRange(0.2f, 0.9f) * (animFrame / D_L11_001B0FFC);
            sparkSign = RandomIntBelow(2);
            if (sparkSign == 0) sparkSign = sparkSign - 1;
            SpawnGroundEffectParticle(workVec, 2, D_L11_001B0FEC, 0, sparkSign, D_L11_001A8F20, sparkSize * 0.3f, sparkSize, 0.0f, 0);
            SpawnGroundEffectParticle(workVec, 2, D_L11_001B0FF8, 1, -sparkSign, D_L11_001A8F20, sparkSize * 0.04f, sparkSize * 0.4f, 0.0f, 0);
            *(f32 *)(vars + 0x574) = *(f32 *)(vars + 0x574) + 1.0f;
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
            if (moby[0x43] != 5)
                StartAnimationBlended(moby, 5, 0, 6);
            SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            SetMobyState(moby, 0x1D, 2);
        }
        break;
    case 28:
        StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        *(s32 *)(vars + 0x290) = 0;
        if (IsValueWithinStepOfThreshold(moby, 1.0f) != 0 || IsValueWithinStepOfThreshold(moby, 7.0f) != 0 || IsValueWithinStepOfThreshold(moby, 14.0f) != 0) {
            if (FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                  ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.78539824f) {
                TransformMobyJointToWorld(*(u32 *)(vars + 0x278), 0, workVec);
                offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[2] = 0.0f;
                FastVecAdd(workVec, workVec, offsetVec);
                workVec[2] = workVec[2] - 0.05f;
                *(TI128 *)(vars + 0x580) = *(TI128 *)workVec;
                FastVecSub(vars + 0x5A0, &((Hero *)gHeroState)->f[0xD0 / 4], workVec);
                *(s32 *)(vars + 0x578) = 0;
                SetObjectFlagBit(moby, 0);
                *(TI128 *)startVec = *(TI128 *)(vars + 0x580);
                *(TI128 *)endVec = *(TI128 *)(vars + 0x5A0);
                SpawnStateVectorMoby(moby, startVec, endVec, *(f32 *)(vars + 0x28C));
                FastVecSub(startVec, &((Hero *)gHeroState)->f[0xD0 / 4], workVec);
                vec_scale_to_length(startVec, startVec, 0.8333334f);
            } else {
                TransformMobyJointToWorld(*(u32 *)(vars + 0x278), 0, workVec);
                offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[2] = 0.0f;
                FastVecAdd(workVec, workVec, offsetVec);
                workVec[2] = workVec[2] - 0.05f;
                *(TI128 *)(vars + 0x580) = *(TI128 *)workVec;
                offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 25.0f;
                offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 25.0f;
                offsetVec[2] = 0.0f;
                FastVecAdd(offsetVec, offsetVec, moby + 0x10);
                FastVecSub(vars + 0x5A0, offsetVec, workVec);
                *(s32 *)(vars + 0x578) = 0;
                SetObjectFlagBit(moby, 0);
                *(TI128 *)startVec = *(TI128 *)(vars + 0x580);
                *(TI128 *)endVec = *(TI128 *)(vars + 0x5A0);
                SpawnStateVectorMoby(moby, startVec, endVec, *(f32 *)(vars + 0x28C));
            }
        }
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x14)
                StartAnimationBlended(moby, 0x14, 0, 0x14);
            if (*(s32 *)(vars + 0x5B4) != 0 && moby[0x43] != 0xA)
                StartAnimationBlended(moby, 0xA, 0, 0x14);
            SetMobyState(moby, 0x1E, -1);
            if (moby[0x95] != 2) {
                SetMobyState(moby, 0x14, -1);
                if (moby[0x43] != 0x11)
                    StartAnimationBlended(moby, 0x11, 0, 0xA);
            }
            *(f32 *)(vars + 0x574) = 0.0f;
        }
        break;
    case 29:
        StepMovementController(moby, moby + 0x10, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                       ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14)));
        *(s32 *)(vars + 0x290) = 0;
        if (moby[0x42] == 5 && GetMobyAnimationValue(moby) < 11.0f) {
            animFrame3 = GetMobyAnimationValue(moby);
            TransformMobyJointToWorld(*(u32 *)(vars + 0x278), 0, workVec);
            offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
            offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
            offsetVec[2] = 0.0f;
            FastVecAdd(workVec, workVec, offsetVec);
            workVec[2] = workVec[2] - 0.05f;
            sparkSize2 = RandomFloatRange(0.2f, 0.9f) * (animFrame3 / D_L11_001B0FFC);
            sparkSign2 = RandomIntBelow(2);
            if (sparkSign2 == 0) sparkSign2 = sparkSign2 - 1;
            SpawnGroundEffectParticle(workVec, 2, D_L11_001B0FEC, 0, sparkSign2, D_L11_001A8F20, sparkSize2 * 0.3f, sparkSize2, 0.0f, 0);
            SpawnGroundEffectParticle(workVec, 2, D_L11_001B0FF8, 1, -sparkSign2, D_L11_001A8F20, sparkSize2 * 0.04f, sparkSize2 * 0.4f, 0.0f, 0);
            *(f32 *)(vars + 0x574) = *(f32 *)(vars + 0x574) + 1.0f;
        }
        if (IsValueWithinStepOfThreshold(moby, 11.0f) != 0) {
            if (FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - *(f32 *)(moby + 0x10),
                                                                  ((Hero *)gHeroState)->f[0x84 / 4] - *(f32 *)(moby + 0x14))) < 0.78539824f) {
                TransformMobyJointToWorld(*(u32 *)(vars + 0x278), 0, workVec);
                offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[2] = 0.0f;
                FastVecAdd(workVec, workVec, offsetVec);
                workVec[2] = workVec[2] - 0.05f;
                *(TI128 *)(vars + 0x580) = *(TI128 *)workVec;
                FastVecSub(vars + 0x5A0, &((Hero *)gHeroState)->f[0xD0 / 4], workVec);
                *(s32 *)(vars + 0x578) = 0;
                SetObjectFlagBit(moby, 0);
                *(TI128 *)startVec = *(TI128 *)(vars + 0x580);
                *(TI128 *)endVec = *(TI128 *)(vars + 0x5A0);
                SpawnStateVectorMoby(moby, startVec, endVec, *(f32 *)(vars + 0x28C));
            } else {
                TransformMobyJointToWorld(*(u32 *)(vars + 0x278), 0, workVec);
                offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
                offsetVec[2] = 0.0f;
                FastVecAdd(workVec, workVec, offsetVec);
                workVec[2] = workVec[2] - 0.05f;
                *(TI128 *)(vars + 0x580) = *(TI128 *)workVec;
                offsetVec[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 25.0f;
                offsetVec[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 25.0f;
                offsetVec[2] = 0.0f;
                FastVecAdd(offsetVec, offsetVec, moby + 0x10);
                FastVecSub(vars + 0x5A0, offsetVec, workVec);
                *(s32 *)(vars + 0x578) = 0;
                SetObjectFlagBit(moby, 0);
                *(TI128 *)startVec = *(TI128 *)(vars + 0x580);
                *(TI128 *)endVec = *(TI128 *)(vars + 0x5A0);
                SpawnStateVectorMoby(moby, startVec, endVec, *(f32 *)(vars + 0x28C));
            }
        }
        animFrame2 = GetMobyAnimationValue(moby);
        if (moby[0x42] == 5 && animFrame2 >= 10.0f && animFrame2 <= 15.0f) {
            TransformMobyJointToWorld(*(u32 *)(vars + 0x278), 0, workVec);
            SweepCollisionFromObject(moby, workVec, 1, 0.4f, *(f32 *)(vars + 0x28C), 1.0f, 0, 1, 0);
        }
        if (moby[0x60] & 2) {
            if (moby[0x43] != 0x11)
                StartAnimationBlended(moby, 0x11, 0, 0x14);
            RandomIntBelow(3);
            SetMobyState(moby, 0x1E, -1);
            if (moby[0x95] != 2) {
                SetMobyState(moby, 0x14, -1);
                if (moby[0x43] != 0x11)
                    StartAnimationBlended(moby, 0x11, 0, 0xA);
            }
            *(f32 *)(vars + 0x574) = 0.0f;
        }
        break;
    case 30:
        if (moby[0x60] & 2) {
            *(s32 *)(vars + 0x5B0) = 0;
            if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x17, -1);
            } else {
                if (moby[0x43] != 3)
                    StartAnimationBlended(moby, 3, 0, 0xA);
                SetMobyState(moby, 0x17, -1);
            }
            *(TI128 *)workVec = *(TI128 *)&D_L11_001B368C[0][(*(s32 *)(vars + 0x57C) << 7) + 0x30];
            TurnMobyTowardTarget(moby, workVec);
            if (vec_distance_xy(moby + 0x10, workVec) < 1.5f) {
                if (*(s32 *)(vars + 0x5B4) != 0) {
                    if (moby[0x43] != 0x12)
                        StartAnimationBlended(moby, 0x12, 0, 0x14);
                } else if (moby[0x43] != 0x12) {
                    StartAnimationBlended(moby, 0x12, 0, 6);
                }
                SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
                SetMobyState(moby, 0x1B, 2);
            }
            if (vec_distance_xy(moby + 0x10, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.5f) {
                if (moby[0x43] != 5)
                    StartAnimationBlended(moby, 5, 0, 6);
                SetControllerSpeedLimits(moby, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
                SetMobyState(moby, 0x1D, 2);
            }
        }
        break;
    }
    PrepareObjectTwoStageAnimation(moby);
    if (FloatAbs(*(f32 *)(moby + 0x18) - startZ) < 0.005f)
        *(f32 *)(moby + 0x18) = startZ;
}
