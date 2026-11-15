#include "common.h"

/* func_L04_003E2438: the level's state-machine update (switch on 0x95), twin of func_L11_0042F018.
   Its own -G8 unit with -frac2-hazard-labels (retail keeps the branch label on the mtc1 hazard
   nop before the 9.0f compare). What it took:
   - the hero block through the Hero union view; switch bodies in retail address order;
     addressed block locals scoped so their stack slots are reused as retail does;
   - func_002C2210 declared with its float parameters interleaved
     (pos, size, f, f, color, mode, flag, vector, f, counter) and func_00277F48 as
     (pos, f, flag, obj, req): EABI passes floats in their own registers, so only the
     parameter order of the argument moves changes, and retail's order of those moves
     follows this prototype;
   - arg0 + 0x10 written out at each use in the 0x60 & 2 / 0x2AC|0x27C block instead of a
     local, so gcse gives the expression one reaching register with several sets; with a
     single set sched1's birthing-insn priority boost puts the reaching copy before the
     argument move and local-alloc ties the value to $a0 (retail: $v0, copied to $a0 and $s0). */

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

extern char D_00189E20[];
extern s32 D_L04_001C9C00[];
extern s32 D_L04_001A8F00;
extern s32 *D_L04_001FE340[];
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern char D_L04_001A8F20[] __attribute__((sda));
extern u8 D_L04_001C7800[];
extern TI128 D_L04_001BFAE0;

extern s32 func_L04_003E4C00(u8 *);
extern void func_L04_003E51F0(u8 *);
extern void func_L04_003E5318(u8 *);
extern void func_L04_003E5B10(u8 *, void *);
extern void func_L04_003E2338(u8 *);
extern s32 func_002B3890(u8 *);
extern void func_002B60B0(u8 *, f32, f32, f32, f32);
extern void func_002A7750(u8 *, s32, s32);
extern void func_002A7470(u8 *a0, u32 a1, u32 a2, u32 a3);
extern s32 func_002A7820(s32, s32);
extern s32 func_002A77E0(s32);
extern s32 func_002A8AF0(void *, void *, s32);
extern s32 func_002B1C20(u8 *, void *);
extern void func_002A6C58(u8 *, s32, s32);
extern void func_L01_003E9CF8(u8 *, s32, void *);
extern void func_0029F338(void *);
extern f32 func_002A7878(f32, f32);
extern s32 func_00282948(void *);
extern s32 func_00282978(void *);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_002AE8C0(u8 *, void *, f32, f32);
extern s32 func_002B6120(u8 *, void *);
extern s32 func_002B6228(u8 *, void *, s32, s32);
extern f32 func_002A7E08(u8 *, void *, void *, f32, f32, f32);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern s32 func_L01_00321178(u8 *, void *);
extern void func_0029FCC0(u32 a0, s32 a1, f32 *a2);
extern f32 func_00283180(f32 a0);
extern f32 func_00283198(f32 a0);
extern void func_00282D30(void *, void *, f32);
extern void func_002A8C00(void *, void *, s32, f32, void *);
extern void func_002A8C28(void *, void *, s32, f32, f32, f32, s32, s32, s32);
extern s32 func_00277F48(void *, f32, s32, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern s32 func_L02_00331440(u8 *, void *, f32, s32, f32, f32);
extern f32 func_0029F530(u8 *);
extern void func_002C2210(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern s32 func_002A8D70(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern s32 func_002AEB60(u8 *, f32);
extern void func_L00_003294F0(u8 *, s32);
extern s32 func_L00_002FCF18(void *, f32, f32, f32, f32, f32);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_002B38B8(u8 *);
extern void func_L04_003E5830(void *, s32);
extern void func_L00_002E6EF8(void *, void *);
extern void func_00291450(s32);
extern s32 func_002B50E0(u8 *, void *, f32);
extern void func_L04_003E22B0(u8 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/* Updates the main creature on this level. It picks its next action (idle, walk, chase, attack) based on the player and plays the matching animations and sounds. */
void func_L04_003E2438(u8 *moby) {
    u8 *vars;

    vars = *(u8 **)(moby + 0x68);
    if (D_L04_001C9C00[0] == 1) {
        if (D_L04_001A8F00 == 2) {
            *(s32 *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        } else {
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
        }
    }
    if (UpdateBarlowEnemyCore(moby) != 0) {
        MarkMobySpawned(moby);
        return;
    }

    switch (moby[0x95]) {
    case 0: {
        s32 homeSlot;

        homeSlot = *(s32 *)(vars + 0x2F0);
        if (homeSlot != -1)
            break;
        if (SetSecondPendingFlag(moby) != 0) {
            SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            if (*(f32 *)(vars + 0x2C0) < 0.2f)
                SetObjectAndLinkedStates(moby, 4, 3, 0, 0xC);
            if (*(s32 *)(vars + 0x2CC) != homeSlot && *(s32 *)(vars + 0x2C4) == homeSlot) {
                SetObjectAndLinkedStates(moby, 5, 4, 0, 0xC);
                SetMobyState(moby, 2, -1);
            }
        }
        if (*(s32 *)(vars + 0x258) == 1 && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x6F) {
            if (*(s32 *)(vars + 0x2C4) != -1) {
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
                SetControllerSpeedLimits(moby, 0.016666668f, 0.5f, 0.001163553f, 0.10471977f);
                *(f32 *)(vars + 0x164) = 0.0055555557f;
                SetMobyState(moby, 0xD, 2);
            } else if (*(u8 **)(vars + 0x2AC) != 0) {
                SetMobyState(moby, 0xA, 2);
            } else {
                SetObjectAndLinkedStates(moby, 0, 2, 0, 0xA);
                SetMobyState(moby, 0xA, 2);
            }
        } else if (*(s16 *)(vars + 0x2A6) != 0) {
            SetMobyState(moby, 8, 1);
            *(s16 *)(vars + 0x2A6) = 0;
            if (*(s16 *)(vars + 0x2A0) < 0x12C)
                *(s16 *)(vars + 0x2A0) = RandomIntRange(0x1E0, 0x258);
            if (*(s32 *)(vars + 0x2CC) != -1) {
                SetMobyState(moby, 8, 1);
                SetObjectAndLinkedStates(moby, 4, 3, 0, 0xC);
            }
        } else if (*(s32 *)(vars + 0x2DC) != -1 &&
                   point_in_path_xy(vars + 0x230, (u8 *)gRoutePathTable[*(s32 *)(vars + 0x2DC)] + 0x10,
                                 *gRoutePathTable[*(s32 *)(vars + 0x2DC)]) != 0) {
            SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
            SetControllerSpeedLimits(moby, 0.016666668f, 0.5f, 0.001163553f, 0.10471977f);
            *(f32 *)(vars + 0x164) = 0.0055555557f;
            SetMobyState(moby, 0xD, 2);
        }
        break;
    }
    case 1:
        if (SetSecondPendingFlag(moby) != 0)
            SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(vars + 0x258) == 1 || *(s32 *)(vars + 0x25C) == 1) {
            if (*(u8 **)(vars + 0x2AC) != 0) {
                SetMobyState(moby, 0xA, 2);
            } else {
                SetObjectAndLinkedStates(moby, 0, 2, 0, 0xA);
                SetMobyState(moby, 0xA, 2);
            }
        } else if (*(s16 *)(vars + 0x2A0) == 0 && *(s32 *)(vars + 0x30C) == 0) {
            SetMobyState(moby, 1, 0);
            SetObjectAndLinkedStates(moby, 5, 4, 0, 0xC);
        }
        break;
    case 2:
        if (SetSecondPendingFlag(moby) != 0)
            SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if ((*(s32 *)(vars + 0x2DC) == -1 ||
             point_in_path_xy(vars + 0x230, (u8 *)gRoutePathTable[*(s32 *)(vars + 0x2DC)] + 0x10,
                           *gRoutePathTable[*(s32 *)(vars + 0x2DC)]) == 0) &&
            *(s32 *)(vars + 0x258) != 1 && *(s32 *)(vars + 0x25C) != 1) {
            if (moby[0x20] == 0xD || moby[0x20] == 0x10 || moby[0x20] == 0xC) {
            } else if (moby[0x20] == 0xF) {
                SetObjectAndLinkedStates(moby, 8, 0, 1, 3);
                SetMobyState(moby, 0x10, -1);
            } else if (*(s32 *)(vars + 0x2CC) != -1 && *(s32 *)(vars + 0x2C4) == -1) {
                SetObjectAndLinkedStates(moby, 5, 4, 0, 0xC);
                SetMobyState(moby, 2, 1);
            } else {
                *(s32 *)(vars + 0x2D0) = 0;
                SetObjectAndLinkedStates(moby, 3, 1, 0, 0xC);
                SetMobyState(moby, 8, 1);
                if (*(s32 *)(vars + 0x2D4) != -1) {
                    qcopy(vars + 0x110, D_L04_001B25CC[0] + (*(s32 *)(vars + 0x2D4) << 7) + 0x30);
                    if (*(f32 *)(vars + 0x12C) == 0.0f)
                        *(f32 *)(vars + 0x12C) = 4.0f;
                }
                *(s16 *)(vars + 0x2A0) = RandomIntRange(0x4B0, 0x514);
            }
        }
        break;
    case 3: {
        s32 moveFlags;
        s32 homeSlot;

        moveFlags = DispatchActionByKind(moby, vars + 0x60);
        if (moveFlags & 1) {
            SetDeathBits(moby, 0, 3);
            QueueMobyForGlowEffect(moby, 0, 0);
            return;
        }
        if (moveFlags & 2) {
            homeSlot = *(s32 *)(vars + 0x2F0);
            if (homeSlot != -1) {
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
                SetMobyState(moby, 7, 0);
                *(s8 *)(vars + 0x307) = 0x78;
            } else if (*(s32 *)(vars + 0x258) == 1 || *(s32 *)(vars + 0x25C) == 1) {
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
                SetMobyState(moby, 0xB, 2);
            } else {
                SetMobyState(moby, 8, 1);
                SetObjectAndLinkedStates(moby, 1, 1, 0, 0xA);
                *(s16 *)(vars + 0x2A0) = RandomIntRange(0x244, 0x258);
                if (*(s32 *)(vars + 0x2CC) != -1) {
                    SetMobyState(moby, 8, 1);
                    SetObjectAndLinkedStates(moby, 4, 3, 0, 0xC);
                }
            }
        }
        break;
    }
    }

    switch (moby[0x20]) {
    case 1:
        if (*(f32 *)(vars + 0x2C0) > 0.2f) {
            FastFloatHelperD(vars + 0x2BC);
            if (*(s32 *)(vars + 0x2BC) >= 0x15)
                *(f32 *)(vars + 0x124) = 0.06666667f;
            else
                ApproachValue((f32 *)(vars + 0x124), 0.0f, 0.0011111111f);
            if (moby[0x43] == 5) {
                if (*(s32 *)(vars + 0x2BC) == 0) {
                    SetObjectAndLinkedStates(moby, 1, 1, 0, 0xC);
                    if (RandomIntBelow(2) == 1)
                        SetObjectAndLinkedStates(moby, 0, 0, 0, 0xC);
                }
                WanderAroundHomePoint(moby, vars + 0x110, 0.35f, 0.25f);
            } else if (moby[0x43] < 2 && (moby[0x60] & 2)) {
                *(s32 *)(vars + 0x2BC) = RandomIntRange(0x78, 0x2BC);
                SetObjectAndLinkedStates(moby, 5, 4, 0, 0xC);
            }
        } else if (*(u8 **)(vars + 0x2AC) != 0 && (*(u8 **)(vars + 0x2AC))[0x43] != 3) {
            SetObjectAndLinkedStates(moby, 4, 3, 0, 0xC);
        }
        break;
    case 2:
        if (FollowPathNodes(moby, gRoutePathTable[*(s32 *)(vars + 0x2CC)]) != 0) {
            SetMobyState(moby, 4, -1);
            SetObjectAndLinkedStates(moby, 4, 3, 0, 0xA);
            SetPathFollowerNodes(moby, gRoutePathTable[*(s32 *)(vars + 0x2CC)], 0, 1);
            *(s32 *)(vars + 0x308) = 1;
        }
        break;
    case 3:
        if (FollowPathNodes(moby, gRoutePathTable[*(s32 *)(vars + 0x2CC)]) != 0) {
            SetMobyState(moby, 4, -1);
            SetObjectAndLinkedStates(moby, 4, 3, 0, 0xA);
            SetPathFollowerNodes(moby, gRoutePathTable[*(s32 *)(vars + 0x2CC)], 1, 0);
            *(s32 *)(vars + 0x308) = 0;
        }
        break;
    case 4:
        if (moby[0x60] & 2) {
            SetObjectAndLinkedStates(moby, 0xF, 0x17, 0, 7);
            SetMobyState(moby, 0x15, -1);
        }
        break;
    case 5:
        if (FastDecTimer(vars + 0x300) != 0) {
            SetObjectAndLinkedStates(moby, 5, 4, 0, 0xA);
            SelectRandomOtherLiveSlot(moby);
            SetMobyState(moby, 6, 0);
        }
        break;
    case 6: {
        {
        f32 homePoint[4] __attribute__((aligned(16)));

        *(TI128 *)homePoint = *(TI128 *)(vars + 0x280);
        SetControllerSpeedLimits(moby, 0.00044444445f, 0.02666667f, 0.001163553f, 0.10471977f);
        TurnMobyTowardTarget(moby, homePoint);
        if (vec_distance_xy(moby + 0x10, homePoint) < 1.0f) {
            SetObjectAndLinkedStates(moby, 1, 1, 0, 0xA);
            *(s16 *)(vars + 0x300) = RandomIntRange(0x4B0, 0xBB8);
            SetMobyState(moby, 5, -1);
        }
        }
        break;
    }
    case 7: {
        {
        f32 homePoint[4] __attribute__((aligned(16)));
        f32 m;

        *(TI128 *)homePoint = *(TI128 *)(vars + 0x280);
        SetControllerSpeedLimits(moby, 0.0006666667f, 0.040000003f, 0.001163553f, 0.10471977f);
        MoveAlongAnimToTargetWithSparks(moby, homePoint);
        m = *(f32 *)(vars + 0x16C) * 30.0f;
        if (m < *(f32 *)(vars + 0x1E8))
            *(f32 *)(vars + 0x1E8) = m;
        if (vec_distance_xy(moby + 0x10, homePoint) < 1.0f || *(s32 *)(vars + 0x1C0) >= 0x3D) {
            SetObjectAndLinkedStates(moby, 1, 1, 0, 0xA);
            *(s16 *)(vars + 0x300) = RandomIntRange(0x4B0, 0xBB8);
            SetMobyState(moby, 5, -1);
        }
        }
        break;
    }
    case 8:
        FastFloatHelperD(vars + 0x2BC);
        if (*(s32 *)(vars + 0x2BC) >= 0x15)
            ApproachValue((f32 *)(vars + 0x124), 0.06666667f, 0.0019444445f);
        else
            ApproachValue((f32 *)(vars + 0x124), 0.0f, 0.0019444445f);
        if (moby[0x43] == 6) {
            if (*(s32 *)(vars + 0x2BC) == 0) {
                SetObjectAndLinkedStates(moby, 3, 2, 0, 0xC);
                if (RandomIntBelow(2) == 1)
                    SetObjectAndLinkedStates(moby, 4, 3, 0, 0xC);
            }
            WanderAroundHomePoint(moby, vars + 0x110, 0.35f, 0.25f);
        } else if ((u8)(moby[0x43] - 3) < 2 && (moby[0x60] & 2)) {
            *(s32 *)(vars + 0x2BC) = RandomIntRange(0x78, 0x2BC);
            SetObjectAndLinkedStates(moby, 6, 5, 0, 0xC);
        }
        break;
    case 9:
        if (moby[0x60] & 2) {
            SetObjectAndLinkedStates(moby, 5, 4, 0, 0xC);
            SetMobyState(moby, 2, -1);
        }
        break;
    case 10:
        TurnTowardPosition(moby, *(void **)(vars + 0x240), vars + 0x2B4, 0.001f, 0.01f, 0.1f);
        if (*(u8 **)(vars + 0x2AC) != 0) {
            SetMobyState(moby, 0x14, -1);
            SetObjectAndLinkedStates(moby, 0x10, 4, 0, 0xA);
        } else if (*(s32 *)(vars + 0x2D8) != 0) {
            SetMobyState(moby, 0xF, -1);
            SetObjectAndLinkedStates(moby, 7, 5, 0, 0xA);
        } else {
            SetMobyState(moby, 0xB, -1);
            SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
        }
        break;
    case 11:
        MoveAlongAnimToTargetWithSparks(moby, vars + 0x230);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (*(u8 **)(vars + 0x2AC) != 0) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 20.0f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.17453295f) {
                SetObjectAndLinkedStates(moby, 9, 6, 0, 0xA);
                SetMobyState(moby, 0xE, -1);
            }
        } else {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 2.7f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.3490659f) {
                SetObjectAndLinkedStates(moby, 0xC, 0, 0, 5);
                SetMobyState(moby, 0x11, -1);
            }
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) > 2.7f && (moby[0x42] == 5 || moby[0x42] == 0x10)) {
                SetObjectAndLinkedStates(moby, 6, 5, 0, 4);
                SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            }
        }
        break;
    case 15: {
        *(f32 *)(vars + 0x164) = 0.0069444445f;
        SetControllerSpeedLimits(moby, 0.006666667f, 0.20000002f, 0.001163553f, 0.10471977f);
        TurnMobyTowardTarget(moby, vars + 0x230);
        TurnTowardPosition(moby, *(void **)(vars + 0x240), vars + 0x2B4, 0.001f, 0.01f, 0.1f);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 3.5f) {
            SetObjectAndLinkedStates(moby, 8, 0, 1, 3);
            *(f32 *)(moby + 0x48) = 1.0f;
            SetMobyState(moby, 0x10, -1);
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));
        f32 z;

        TransformMobyJointToWorld((u32)moby, 1, pos);
        dir[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8));
        dir[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8));
        dir[2] = 0.0f;
        z = dir[2];
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        FastVecScale(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        make_hit_descriptor(req, moby, 1, *(f32 *)(vars + 0x2E8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
        req[0x18] = 0;
        ProcessCollisionHit(pos, 1.1f, 0, moby, req);
        SweepCollisionFromObject(moby, pos, 0x10000, 1.1f, *(f32 *)(vars + 0x2E8) * 4.0f, z, 0, 1, 0);
        }
        break;
    }
    case 16: {
        u8 *p;

        p = moby + 0x10;
        {
        f32 off[4] __attribute__((aligned(16)));
        SetControllerSpeedLimits(moby, 0.004166667f, 0.033333335f, 0.001163553f, 0.10471977f);
        off[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 4.0f;
        off[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 4.0f;
        off[2] = 0.0f;
        FastVecAdd(off, p, off);
        TurnMobyTowardTarget(moby, vars + 0x230);
        *(s32 *)(vars + 0x2B0) = *(s32 *)(vars + 0x2B0) + 1;
        if (moby[0x60] & 2) {
            SetObjectAndLinkedStates(moby, 2, 2, 0, 0xA);
            SetMobyState(moby, 0xC, -1);
            if (vec_distance_xy(p, &((Hero *)gHeroState)->f[0x80 / 4]) < 3.0f) {
                SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                if (moby[0x43] != 0x11)
                    StartAnimationBlended(moby, 0x11, 0, 0xA);
                SetMobyState(moby, 0x17, -1);
            }
        }
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));

        TransformMobyJointToWorld((u32)moby, 1, pos);
        dir[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8));
        dir[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8));
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        FastVecScale(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        make_hit_descriptor(req, moby, 0x04000001, *(f32 *)(vars + 0x2E8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
        req[0x18] = 0;
        ProcessCollisionHit(pos, 1.3f, 0, moby, req);
        }
        break;
    }
    case 23: {
        SetControllerSpeedLimits(moby, 0.0011111111f, 0.033333335f, 0.001163553f, 0.10471977f);
        {
        f32 homePoint[4] __attribute__((aligned(16)));

        vec_scale_to_length(homePoint, moby + 0xC0, -5.5f);
        FastVecAdd(homePoint, homePoint, moby + 0x10);
        MoveToTargetWithTempLimits(moby, homePoint, FastMatrixHelperA(homePoint[0] - *(f32 *)(moby + 0x10), homePoint[1] - *(f32 *)(moby + 0x14)), 0x10, -1.0f, -1.0f);
        }
        if (*(u16 *)(moby + 0x96) >= 0x79) {
            *(f32 *)(vars + 0x164) = 0.00083333335f;
            if (*(u8 **)(vars + 0x2AC) != 0) {
                SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                SetObjectAndLinkedStates(moby, 9, 6, 0, 0xA);
                SetMobyState(moby, 0xE, -1);
            } else {
                SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
                SetMobyState(moby, 0xB, -1);
            }
        }
        break;
    }
    case 12:
        if (moby[0x60] & 2) {
            *(f32 *)(vars + 0x164) = 0.00083333335f;
            if (*(u8 **)(vars + 0x2AC) != 0) {
                SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                SetObjectAndLinkedStates(moby, 9, 6, 0, 0xA);
                SetMobyState(moby, 0xE, -1);
            } else {
                SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
                SetMobyState(moby, 0xB, -1);
            }
        }
        break;
    case 13:
        SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if (FollowPathNodes(moby, gRoutePathTable[*(s32 *)(vars + 0x2C4)]) != 0) {
            SetMobyState(moby, 0x14, -1);
            SetObjectAndLinkedStates(moby, 0x10, 4, 0, 0xA);
            SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            *(s32 *)(vars + 0x2C4) = -1;
            *(f32 *)(vars + 0x164) = 0.00083333335f;
            *(s32 *)(vars + 0x2DC) = -1;
        }
        break;
    case 14: {
        f32 v0[4] __attribute__((aligned(16)));
        f32 v10[4] __attribute__((aligned(16)));
        f32 f, g;
        s32 n;

        if (*(u8 **)(vars + 0x2AC) != 0 && moby[0x42] == 9) {
            TransformMobyJointToWorld(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
            v10[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
            v10[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
            v10[2] = 0.0f;
            FastVecAdd(v0, v0, v10);
            v0[2] -= 0.05f;
            g = GetMobyAnimationValue(moby);
            f = RandomFloatRange(0.2f, 0.9f) * 0.2f * g;
            n = RandomIntBelow(2);
            if (n == 0)
                n = n - 1;
            SpawnGroundEffectParticle(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L04_001A8F20, 0.0f, 0);
            SpawnGroundEffectParticle(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
            *(f32 *)(vars + 0x2B8) = g;
        }
        if (*(u16 *)(moby + 0x96) >= 0x2E) {
            SetObjectAndLinkedStates(moby, 0xA, 7, 0, 0xA);
            SetMobyState(moby, 0x12, -1);
        }
        break;
    }
    case 17: {
        f32 f;

        f = GetMobyAnimationValue(moby);
        if (moby[0x42] == 0xC && f >= 10.0f && f <= 15.0f)
            TestHitAtBone(moby, 1.0f, *(f32 *)(vars + 0x2E4), 1, 0x04000001, 1.0f, 0, 1, 0);
        if (moby[0x60] & 2) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 2.7f &&
                FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.3490659f) {
                SetObjectAndLinkedStates(moby, 0xC, 0, 0, 0xA);
                SetMobyState(moby, 0x11, -1);
            } else {
                SetMobyState(moby, 0xB, -1);
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
                SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            }
        }
        break;
    }
    case 18: {
        f32 t;
        f32 hp;

        if (moby[0x60] & 2) {
            if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) < 25.0f && *(u8 **)(vars + 0x2AC) != 0 &&
                *(s32 *)(vars + 0x2D0) < 3) {
                if (FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                     *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) > 0.087266475f) {
                    SetMobyState(moby, 0x14, -1);
                    SetObjectAndLinkedStates(moby, 0x10, 4, 0, 0xA);
                } else {
                    SetObjectAndLinkedStates(moby, 9, 6, 0, 0xA);
                    SetMobyState(moby, 0xE, -1);
                }
            } else if (vec_distance_xy(moby + 0x10, *(u8 **)(vars + 0x240) + 0x10) > 10.0f && *(u8 **)(vars + 0x2AC) != 0 &&
                       *(s32 *)(vars + 0x2D0) >= 3) {
                SetObjectAndLinkedStates(moby, 3, 2, 0, 0xA);
                SetMobyState(moby, 0x13, -1);
                *(s32 *)(vars + 0x2D0) = 0;
            } else {
                SetMobyState(moby, 0x14, -1);
                SetObjectAndLinkedStates(moby, 0x10, 4, 0, 0xA);
            }
            if (*(u8 **)(vars + 0x2AC) != 0) {
                *(s32 *)(vars + 0x2D0) = *(s32 *)(vars + 0x2D0) + 1;
            } else {
                SetMobyState(moby, 0xB, -1);
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
                break;
            }
        } else if (IsValueWithinStepOfThreshold(moby, 3.0f) != 0 && *(u8 **)(vars + 0x2AC) != 0) {
            f32 v0[4] __attribute__((aligned(16)));
            f32 v10[4] __attribute__((aligned(16)));

            if (FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                                 *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) < 0.78539824f) {
                s32 k;
                u8 *l;

                TransformMobyJointToWorld(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(vars + 0x260) = *(TI128 *)v0;
                FastVecSub(vars + 0x280, vars + 0x230, v0);
                *(f32 *)(vars + 0x2C8) = 0.0f;
                SetObjectFlagBit(moby, 0);
                k = AllocateEffectSlot_L00_2(moby + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(vars + 0x2E0) = k;
                if (k >= 0) {
                    l = D_L04_001C7800 + (k << 5);
                    qcopy(l + 0x10, vars + 0x260);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            } else {
                s32 k;
                u8 *l;

                TransformMobyJointToWorld(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(vars + 0x260) = *(TI128 *)v0;
                v10[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 25.0f;
                v10[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 25.0f;
                v10[2] = 0.0f;
                FastVecAdd(v10, v10, moby + 0x10);
                FastVecSub(vars + 0x280, v10, v0);
                *(f32 *)(vars + 0x2C8) = 0.0f;
                SetObjectFlagBit(moby, 0);
                k = AllocateEffectSlot_L00_2(moby + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(vars + 0x2E0) = k;
                if (k >= 0) {
                    l = D_L04_001C7800 + (k << 5);
                    qcopy(l + 0x10, vars + 0x260);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            }
        }
        t = GetMobyAnimationValue(moby);
        if (t < 3.0f || moby[0x42] != 0xA) {
            if (*(u8 **)(vars + 0x2AC) != 0) {
                f32 v0[4] __attribute__((aligned(16)));
                f32 v10[4] __attribute__((aligned(16)));
                f32 f;
                s32 n;

                TransformMobyJointToWorld(*(u32 *)(*(u8 **)(*(u8 **)(vars + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                FastVecAdd(v0, v0, v10);
                v0[2] -= 0.05f;
                f = RandomFloatRange(0.2f, 0.9f) * 0.2f * *(f32 *)(vars + 0x2B8);
                n = RandomIntBelow(2);
                if (n == 0)
                    n = n - 1;
                SpawnGroundEffectParticle(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L04_001A8F20, 0.0f, 0);
                SpawnGroundEffectParticle(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
                *(f32 *)(vars + 0x2B8) = *(f32 *)(vars + 0x2B8) + 1.0f;
            }
        }
        hp = (f32)vars[0x35];
        if (t >= 3.0f) {
            if (t < 9.0f) {
                if (moby[0x42] == 0xA) {
            u8 req[0x30] __attribute__((aligned(16)));
            f32 v30[4] __attribute__((aligned(16)));
                                    u8 *l;
            f32 f, f3, f04, f4;
            s32 n;

            *(f32 *)(vars + 0x2C8) = *(f32 *)(vars + 0x2C8) + 1.0f;
            vec_scale_to_length(vars + 0x270, vars + 0x280, *(f32 *)(vars + 0x2C8));
            make_hit_descriptor(req, moby, 0x04000001, hp, vars + 0x270);
            *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
            FastVecAdd(vars + 0x270, vars + 0x260, vars + 0x270);
            if (CollLine(vars + 0x260, vars + 0x270, 0, moby, req) != 0) {
                *(TI128 *)(vars + 0x270) = D_L04_001BFAE0;
                if (IsThirdPendingFlagSet(moby) == 0) {
                    SpawnPairedSparkParticles_L04(&D_L04_001BFAE0, 0x1E);
                    SetObjectFlagBit(moby, 1);
                }
            }
            f = RandomFloatRange(1.0f, 6.0f);
            n = RandomIntRange(0x19, 0x23);
            if (n == 0)
                n = n - 1;
            qcopy(v30, vars + 0x270);
            v30[2] -= 0.1f;
            f3 = f * 0.3f;
            SpawnGroundEffectParticle(v30, 0x19, f3, f, 0xFF000080, 0, n, D_L04_001A8F20, 0.0f, 0);
            n = -n;
            f04 = f * 0.04f;
            f4 = f * 0.4f;
            SpawnGroundEffectParticle(v30, 5, f04, f4, 0x7F6F6FFF, 1, n, D_L04_001A8F20, 0.0f, 0);
            SpawnGroundEffectParticle(v30, 0x14, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L04_001A8F20, 0.0f, 0);
            SpawnGroundEffectParticle(vars + 0x260, 0xA, f3, f, 0x80CA00CB, 0, n, D_L04_001A8F20, 0.0f, 0);
            SpawnGroundEffectParticle(vars + 0x260, 0xA, f04, f4, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
            AddDrawCallbackToList3(DrawLinkedObjectBeam, moby);
            if (*(s32 *)(vars + 0x2E0) >= 0) {
                l = D_L04_001C7800 + (*(s32 *)(vars + 0x2E0) << 5);
                qcopy(l + 0x10, vars + 0x270);
                *(f32 *)(l + 0x1C) = 5.0f;
                *(f32 *)(l + 0) = 1.0f;
                *(f32 *)(l + 4) = 0.0f;
                *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                *(f32 *)(l + 8) = 0.0f;
                *(f32 *)(l + 0xC) = 0.0f;
            }
                }
            }
        }
        if (t >= 9.0f && t < 15.0f && moby[0x42] == 0xA) {
                        
            if (vec_distance_xy(vars + 0x260, vars + 0x270) > 0.5f) {
                u8 req[0x30] __attribute__((aligned(16)));
                f32 v30[4] __attribute__((aligned(16)));
                f32 v40[4] __attribute__((aligned(16)));
                u8 *l;
                f32 f, f4;
                s32 n;

                *(f32 *)(vars + 0x2C8) = *(f32 *)(vars + 0x2C8) + 1.0f;
                vec_scale_to_length(vars + 0x270, vars + 0x280, *(f32 *)(vars + 0x2C8));
                make_hit_descriptor(req, moby, 0x04000001, hp, vars + 0x270);
                *(u16 *)(req + 0x1A) = *(u16 *)(moby + 0xAA);
                FastVecAdd(vars + 0x270, vars + 0x260, vars + 0x270);
                if (CollLine(vars + 0x260, vars + 0x270, 0, moby, req) != 0) {
                    *(TI128 *)(vars + 0x270) = D_L04_001BFAE0;
                    if (IsThirdPendingFlagSet(moby) == 0) {
                        SpawnPairedSparkParticles_L04(&D_L04_001BFAE0, 0x1E);
                        SetObjectFlagBit(moby, 1);
                    }
                }
                vec_scale_to_length(v30, vars + 0x280, 1.6666667f);
                FastVecAdd(vars + 0x260, vars + 0x260, v30);
                f = RandomFloatRange(1.0f, 6.0f);
                n = RandomIntRange(0x19, 0x23);
                if (n == 0)
                    n = n - 1;
                qcopy(v40, vars + 0x270);
                v40[2] -= 0.1f;
                SpawnGroundEffectParticle(v40, 0x19, f * 0.3f, f, 0xFF000080, 0, n, D_L04_001A8F20, 0.0f, 0);
                n = -n;
                f4 = f * 0.4f;
                SpawnGroundEffectParticle(v40, 5, f * 0.04f, f4, 0x7F6F6FFF, 1, n, D_L04_001A8F20, 0.0f, 0);
                SpawnGroundEffectParticle(v40, 0x14, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L04_001A8F20, 0.0f, 0);
                AddDrawCallbackToList3(DrawLinkedObjectBeam, moby);
                if (*(s32 *)(vars + 0x2E0) >= 0) {
                    l = D_L04_001C7800 + (*(s32 *)(vars + 0x2E0) << 5);
                    qcopy(l + 0x10, vars + 0x270);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            } else if (*(s32 *)(vars + 0x2E0) >= 0) {
                FreePointLight(*(s32 *)(vars + 0x2E0));
                *(s32 *)(vars + 0x2E0) = -1;
            }
        } else if (t > 15.0f && moby[0x42] == 0xA) {
            if (*(s32 *)(vars + 0x2E0) >= 0) {
                FreePointLight(*(s32 *)(vars + 0x2E0));
                *(s32 *)(vars + 0x2E0) = -1;
            }
        }
        break;
    }
    case 19: {
        u8 *p = moby + 0x10;

        if (moby[0x60] & 2) {
            if (vec_distance_xy(p, *(u8 **)(vars + 0x240) + 0x10) < 25.0f && *(u8 **)(vars + 0x2AC) != 0) {
                SetMobyState(moby, 0x14, -1);
                SetObjectAndLinkedStates(moby, 5, 4, 0, 0xA);
            } else {
                SetMobyState(moby, 0xB, -1);
                SetObjectAndLinkedStates(moby, 6, 5, 0, 0xA);
            }
        } else if (vec_distance_xy(p, *(u8 **)(vars + 0x240) + 0x10) < 6.0f) {
            SetObjectAndLinkedStates(moby, 9, 6, 0, 0xA);
            SetMobyState(moby, 0xE, -1);
        }
        break;
    }
    case 20:
        if (FastDiffRots(*(f32 *)(moby + 0xF8), FastMatrixHelperA(*(f32 *)(vars + 0x230) - *(f32 *)(moby + 0x10),
                                                             *(f32 *)(vars + 0x234) - *(f32 *)(moby + 0x14))) <= 0.087266475f) {
            SetObjectAndLinkedStates(moby, 9, 6, 0, 0xA);
            SetMobyState(moby, 0xE, -1);
        } else {
            StepMovementController(moby, moby + 0x10, FastMatrixHelperA(*(f32 *)(*(u8 **)(vars + 0x240) + 0x10) - *(f32 *)(moby + 0x10),
                                                           *(f32 *)(*(u8 **)(vars + 0x240) + 0x14) - *(f32 *)(moby + 0x14)));
        }
        break;
    case 21:
        if (moby[0x60] & 2) {
            if (*(s32 *)(vars + 0x308) == 0) {
                SetObjectAndLinkedStates(moby, 5, 4, 0, 0);
                SetMobyState(moby, 2, -1);
            } else {
                SetObjectAndLinkedStates(moby, 5, 4, 0, 0);
                SetMobyState(moby, 3, -1);
            }
        } else if (moby[0x43] == 0xF) {
            SetControllerSpeedLimits(moby, 0.13333334f, 0.06666667f, 0.009696275f, 0.6981318f);
            FollowPathNodes(moby, gRoutePathTable[*(s32 *)(vars + 0x2CC)]);
        }
        break;
    }
    UpdateObjectAgeTimer(moby);
    if (*(f32 *)(moby + 0x18) < 40.0f) {
        SetDeathBits(moby, 0, 3);
        MarkMobySpawned(moby);
    }
}
