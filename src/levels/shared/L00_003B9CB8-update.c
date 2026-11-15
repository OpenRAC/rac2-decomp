#include "common.h"

typedef int TI128_L00_003BD7E0 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128_L00_003BD7E0 q[0x260]; } Hero_L00_003BD7E0;
extern u8 D_00189E20[];
extern char D_00189EA0[];
extern u8 D_00188660[];

extern char D_L00_001A8F20[16] MACRO_ADDR;
extern char *D_L00_001FDA80[];
extern char D_L00_001AFDC0[];
extern void func_0026FEB8(const char *, ...);
extern void func_L00_002E6EF8(void (*)(char *), char *);
extern int func_00282948(void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_0029F338(void *);
extern float func_0029F530(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002A7E08(void *, void *, void *, float, float, float);
extern float func_002A89A8(void *, int, float);
extern float func_002AA3A8(void *, float, void *, float, float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_002AC728(void *, void *, int, float, float);
extern int func_002ACBC8(void *, int);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_002AEB60(void *, float);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern int func_002B3890(void *);
extern int func_002B38B8(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern void *func_002C65A0(void *, void *, int, u32, int, int, int, int, float, float, float);
extern void func_002C9828(void *, int, void *, void *, int, float);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00319780(char *);
extern void func_00319FB8(char *);
extern void func_00319EC0(char *);
extern int func_0031A580(char *);
extern int func_0031A628(char *);
extern int func_0031A708(unsigned char *);
extern int func_0031A848(char *, float);
extern void func_0031AAB0(char *);
extern void *func_003280C8(char *, void *, void *, int, int, float);
extern float func_00282E80(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AEF28(float, float, char *, char *, float, char *);

/* A moby's per-frame update: pvars at moby+0x68, a switch on moby+0x95, a switch on the state at
   moby+0x20, then the sound-slot keep-alive on pvars+0x2C4. The template vector is MACRO_ADDR: retail
   schedules its address as one `la`, not a split %hi/%lo pair. func_00318340 is the boot twin. */
/* Per-frame update of the moby class 2484 enemy: it picks animations, turns toward the hero,
   walks, jumps and shoots depending on its state. */
void func_L00_003BD7E0(char *moby)
{
    f32 v0[4] __attribute__((aligned(16)));
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    char *tgt13, *tgt10, *tgt16;
    f32 *pos;
    s32 *path;
    int slotIndex;
    int m0, m2, flags, stateByte;
    float h13, h12, floor12, y12, diff12, h5, diff5, dist10, dot, dist11, dist16, sx, sy, sz;

    if (((Hero_L00_003BD7E0 *)gHeroState)->b[0x22B4] == 1)
        return;
    switch (*(u8 *)(moby + 0x95)) {
    case 0:
        if (*(s32 *)(vars + 0x2E0) != 0 && IsThirdPendingFlagSet(moby) == 0)
            break;
        if (SetSecondPendingFlag(moby) != 0)
            SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        m0 = *(s32 *)(vars + 0x34);
        if (m0 == 1 && *(s32 *)(vars + 0x2A4) != 0) {
            if (FastFloatHelperD(vars + 0x2D0) != 0) {
                SetMobyState(moby, 9, 3);
                if (*(u8 *)(moby + 0x43) != m0)
                    StartAnimationBlended(moby, 1, 0, 4);
            }
        } else if (*(s16 *)(vars + 0x286) != 0) {
            SetMobyState(moby, 8, 2);
            *(s16 *)(vars + 0x286) = 0;
            if (*(s16 *)(vars + 0x280) < 300)
                *(s16 *)(vars + 0x280) = RandomIntRange(0x1E0, 0x258);
        }
        break;
    case 2:
        if (SetSecondPendingFlag(moby) != 0) {
            SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            *(f32 *)(moby + 0x48) = 1.0f;
        }
        m2 = *(s32 *)(vars + 0x34);
        if (m2 == 1 && *(s32 *)(vars + 0x2A4) != 0) {
            SetMobyState(moby, 9, 3);
            if (*(u8 *)(moby + 0x43) != m2)
                StartAnimationBlended(moby, 1, 0, 4);
        } else if (*(s16 *)(vars + 0x280) == 0) {
            SetMobyState(moby, 2, 0);
            if (*(u8 *)(moby + 0x43) != 2)
                StartAnimationBlended(moby, 2, 0, 10);
        }
        break;
    case 1:
        if (SetSecondPendingFlag(moby) != 0)
            SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(vars + 0x34) == 1 && *(s32 *)(vars + 0x2A4) != 0) {
            if (FastFloatHelperD(vars + 0x2D0) == 0)
                break;
        } else {
            if (*(s16 *)(vars + 0x286) == 0 || *(s32 *)(vars + 0x2A4) == 0)
                break;
            *(s16 *)(vars + 0x286) = 0;
        }
        SetMobyState(moby, 0xD, 3);
        if (*(u8 *)(moby + 0x43) != 0x19)
            StartAnimationBlended(moby, 0x19, 0, 4);
        break;
    case 3:
        if (SetSecondPendingFlag(moby) != 0) {
            SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            *(f32 *)(moby + 0x48) = 1.0f;
        }
        if (*(s32 *)(vars + 0x34) != 1 && *(u8 *)(moby + 0x20) != 0xD && *(u8 *)(moby + 0x20) != 0xC && *(u8 *)(moby + 0x20) != 0xF) {
            SetMobyState(moby, 8, 2);
            if (*(u8 *)(moby + 0x43) != 6)
                StartAnimationBlended(moby, 6, 0, 10);
            *(s16 *)(vars + 0x280) = RandomIntRange(0x244, 0x258);
            if (*(s32 *)(vars + 0x28C) != 0) {
                SetMobyState(moby, 3, 1);
                if (*(u8 *)(moby + 0x43) != 0xB)
                    StartAnimationBlended(moby, 0xB, 0, 0x14);
            }
        }
        break;
    case 4:
        if (SetFirstPendingFlag(moby) != 0)
            *(s16 *)(vars + 0x46) = 0x3C;
        flags = DispatchActionByKind(moby, vars + 0x80);
        if ((flags & 1) || *(f32 *)(vars + 0x40) <= 0.0f) {
            SpawnExplosionWithSparks(moby, moby + 0x10, -1, 1.0f, 13.0f);
            SetDeathBits(moby, 0, 3);
            MarkMobySpawned(moby);
            return;
        }
        if (flags & 2) {
            if (*(s32 *)(vars + 0x34) == 1) {
                SetMobyState(moby, 7, 3);
                if (*(u8 *)(moby + 0x43) != 7)
                    StartAnimationBlended(moby, 7, 0, 6);
            } else {
                SetMobyState(moby, 8, 2);
                if (*(u8 *)(moby + 0x43) != 6)
                    StartAnimationBlended(moby, 6, 0, 10);
                *(s16 *)(vars + 0x280) = RandomIntRange(0x244, 0x258);
            }
            if (*(s32 *)(vars + 0x2A4) != 1)
                *(s32 *)(vars + 0x2A4) = 1;
        }
        break;
    }

    switch (*(u8 *)(moby + 0x20)) {
    case 2:
        break;
    case 7:
        if (IsTargetOutsideTurnLimit(moby, 10.0f) != 0) {
            TurnTowardTargetMoby(moby);
        } else {
            SetMobyState(moby, 0xA, -1);
            if (*(u8 *)(moby + 0x43) != 0x1E)
                StartAnimationBlended(moby, 0x1E, 0, 6);
        }
        break;
    case 3:
        ScaleOwnerWordsByAngles(0.06981318f, 0.052359886f, moby, vars + 0x2A8, 0.013089972f, vars + 0x2AC);
        break;
    case 13:
        tgt13 = *(char **)(vars + 0x30);
        *(s32 *)(vars + 0x2C0) += 1;
        if (tgt13 != 0) {
            TurnTowardPosition(moby, tgt13, vars + 0x29C, 0.001f, 0.01f, 0.1f);
            SpringFloatToGoal(moby + 0xF4, 0.0f, vars + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            SpringFloatToGoal(moby + 0xF0, 0.0f, vars + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            h13 = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
            if (*(f32 *)(moby + 0x18) - h13 > 0.05f) {
                *(f32 *)(moby + 0x18) -= h13 * 0.00025f;
            } else {
                SetMobyState(moby, 6, -1);
                if (*(u8 *)(moby + 0x43) != 0xE)
                    StartAnimationBlended(moby, 0xE, 0, 3);
            }
            if (*(u8 *)(moby + 0x60) & 2) {
                SetMobyState(moby, 0xC, -1);
                if (*(u8 *)(moby + 0x43) != 0x1A)
                    StartAnimationBlended(moby, 0x1A, 0, 0xF);
            }
        }
        break;
    case 12:
        *(s32 *)(vars + 0x2C0) += 1;
        TurnTowardTargetMoby(moby);
        h12 = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
        y12 = *(f32 *)(moby + 0x18);
        floor12 = *(f32 *)(vars + 0x2DC);
        diff12 = y12 - h12;
        h12 -= 3.0f;
        if (floor12 != -1.0f && y12 <= floor12) {
            if (IsMobyInGroup(moby) == 0) {
                SetMobyState(moby, 0x10, -1);
                if (*(u8 *)(moby + 0x43) != 0x1D)
                    StartAnimationBlended(moby, 0x1D, 0, 3);
            } else {
                *(s32 *)(vars + 0x354) = 0;
                ClaimGroupLeadToken(moby);
                SetMobyState(moby, 0xE, -1);
            }
        } else if (diff12 > 0.05f) {
            StepValueTowardTarget(moby + 0x18, vars + 0x290, h12, 0.016666668f, 0.16333334f, 0.16666667f);
        } else {
            STUB_printf(D_L00_001AFDC0, *(s32 *)(vars + 0x2C0));
            SetMobyState(moby, 6, -1);
            if (*(u8 *)(moby + 0x43) != 0xE)
                StartAnimationBlended(moby, 0xE, 0, 3);
        }
        break;
    case 14:
        if (SetFirstPendingFlag(moby) != 0) {
            *(TI128_L00_003BD7E0 *)(vars + 0x360) = *(TI128_L00_003BD7E0 *)(moby + 0x10);
            if (*(s32 *)(vars + 0x350) != 0)
                *(f32 *)(vars + 0x368) = *(f32 *)(vars + 0x2DC) + RandomFloatRange(4.0f, 7.0f);
            else
                *(f32 *)(vars + 0x368) = *(f32 *)(vars + 0x2DC) + RandomFloatRange(-3.0f, 3.0f);
        }
        if (fast_vec_dist(moby + 0x10, vars + 0x360) < 0.05f) {
            *(s32 *)(vars + 0x354) = 0;
            SetMobyState(moby, 0x10, -1);
        }
        *(s32 *)(vars + 0x2C0) += 1;
        TurnTowardTargetMoby(moby);
        StepValueTowardTarget(moby + 0x18, vars + 0x290, *(f32 *)(vars + 0x368), 0.004166667f, 0.004166667f, 0.16666667f);
        break;
    case 4:
        if (*(u8 *)(moby + 0x60) & 2) {
            SetMobyState(moby, 5, -1);
            if (*(u8 *)(moby + 0x43) != 0xD)
                StartAnimationBlended(moby, 0xD, 0, 0xF);
        }
        break;
    case 5:
        if (*(char **)(vars + 0x30) != 0) {
            SpringFloatToGoal(moby + 0xF4, 0.0f, vars + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            euler_rotation_basis(moby + 0xC0, moby + 0xF0);
            TurnTowardPosition(moby, *(char **)(vars + 0x30), vars + 0x29C, 0.001f, 0.01f, 0.1f);
            h5 = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
            diff5 = *(f32 *)(moby + 0x18) - h5;
            h5 -= 3.0f;
            if (diff5 > 0.05f) {
                StepValueTowardTarget(moby + 0x18, vars + 0x290, h5, 0.025000002f, 0.16333334f, 0.25f);
            } else {
                SetMobyState(moby, 6, -1);
                if (*(u8 *)(moby + 0x43) != 0xE)
                    StartAnimationBlended(moby, 0xE, 0, 3);
            }
        }
        break;
    case 6:
        if (*(u8 *)(moby + 0x60) & 2) {
            SetMobyState(moby, 0xA, 3);
            if (*(u8 *)(moby + 0x43) != 0x1E)
                StartAnimationBlended(moby, 0x1E, 0, 6);
            *(f32 *)(moby + 0x18) = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
        }
        break;
    case 9:
        if (*(u8 *)(moby + 0x60) & 2) {
            SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            SetMobyState(moby, 7, -1);
            if (*(u8 *)(moby + 0x43) != 7)
                StartAnimationBlended(moby, 7, 0, 6);
        }
        break;
    case 10:
        if (*(u8 *)(moby + 0x60) & 2) {
            if (IsTargetOutsideTurnLimit(moby, 10.0f) != 0) {
                SetMobyState(moby, 7, -1);
                if (*(u8 *)(moby + 0x43) != 7)
                    StartAnimationBlended(moby, 7, 0, 6);
            } else if (((Hero_L00_003BD7E0 *)gHeroState)->ptr[0x249C / 4] == (u8 *)moby || RandomIntBelow(6) == 1) {
                SetMobyState(moby, 0xB, -1);
                if (*(u8 *)(moby + 0x43) != 0x10)
                    StartAnimationBlended(moby, 0x10, 0, 7);
            }
        }
        dist10 = GetMobyAnimationValue(moby);
        if (IsValueWithinStepOfThreshold(moby, 17.0f) != 0) {
            TransformMobyJointToWorld(moby, 4, v0);
            tgt10 = *(char **)(vars + 0x30);
            if (tgt10 == (char *)((Hero_L00_003BD7E0 *)gHeroState)->ptr[0x2290 / 4]) {
                qcopy(v10, &((Hero_L00_003BD7E0 *)gHeroState)->q[0xD0 / 16]);
                pos = v10;
            } else {
                if (tgt10 == 0)
                    break;
                qcopy(v10, tgt10 + 0x10);
                pos = v10;
                v10[2] += *(f32 *)(tgt10 + 0xC) * 0.0009765625f;
            }
            if (IsTargetOutsideTurnLimit(moby, 10.0f) != 0) {
                FastVecSub(v40, pos, v0);
                qcopy(v20, D_L00_001A8F20);
                v20[0] = 1.0f;
                matrix_mul_vec3(v20, v20, moby + 0xC0);
                FastVecCross(v30, v20, v40);
                dot = FastVecDot(v20, v40);
                if (dot > 0.0f)
                    ApplyAxisRotationToQuaternion(v20, v20, v30, -0.17453294f);
                else
                    ApplyAxisRotationToQuaternion(v20, v20, v30, 0.17453294f);
            } else {
                FastVecSub(v20, pos, v0);
            }
            vec_scale_to_length(v20, v20, 0.33333334f);
            SpawnSpinningEffectMoby(moby, v20, v0, 0, 0, *(u8 *)(vars + 0x54));
        } else if (dist10 < 17.0f && *(u8 *)(moby + 0x43) == 0x1E) {
            TransformMobyJointToWorld(moby, 4, v0);
        }
        break;
    case 11:
        if (*(u8 *)(moby + 0x60) & 2) {
            if (vec_distance_xy(moby + 0x10, gHeroPosition) > 4.0f) {
                SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                SetMobyState(moby, 0xA, -1);
                if (*(u8 *)(moby + 0x43) != 0x1E)
                    StartAnimationBlended(moby, 0x1E, 0, 6);
            } else {
                SetControllerSpeedLimits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                SetMobyState(moby, 0xA, -1);
                if (*(u8 *)(moby + 0x43) != 0x1E)
                    StartAnimationBlended(moby, 0x1E, 0, 6);
            }
        }
        dist11 = GetMobyAnimationValue(moby);
        if (*(u8 *)(moby + 0x42) == 0x10 && (dist11 <= 5.0f || (dist11 >= 12.0f && dist11 <= 15.0f)))
            *(s32 *)(vars + 0x2C8) = 1;
        else
            *(s32 *)(vars + 0x2C8) = 0;
        break;
    case 15:
        if (SetFirstPendingFlag(moby) != 0) {
            *(f32 *)(vars + 0x374) = 0.0f;
            *(f32 *)(vars + 0x378) = 0.0f;
        }
        if (*(s32 *)(vars + 0x37C) == 0) {
            if (IsPointInCuboid(gHeroPosition, *(s32 *)(vars + 0x35C)) != 0)
                *(s32 *)(vars + 0x37C) = 1;
        } else {
            path = (s32 *)D_L00_001FDA80[*(s32 *)(vars + 0x370)];
            StepValueTowardTarget(vars + 0x374, vars + 0x378, (f32)(*path - 1), 0.013888889f, 0.0013888889f, 0.33333334f);
            SamplePathPosition(path, 0, moby + 0x10, moby + 0xF0, 0, *(f32 *)(vars + 0x374));
            euler_rotation_basis(moby + 0xC0, moby + 0xF0);
            if ((f32)(*path - 1) <= *(f32 *)(vars + 0x374))
                SetMobyState(moby, 0xA, 3);
        }
        break;
    case 16:
        if ((*(u8 *)(moby + 0x60) & 2) && IsMobyInGroup(moby) != 0) {
            *(s32 *)(vars + 0x354) += 1;
            if (*(s32 *)(vars + 0x350) != 0) {
                if (*(s32 *)(vars + 0x354) >= 3 && PassGroupLeadToken(moby) != 0) {
                    SetMobyState(moby, 0xE, -1);
                    if (*(u8 *)(moby + 0x43) != 0x1A)
                        StartAnimationBlended(moby, 0x1A, 0, 0xF);
                }
            } else {
                SetMobyState(moby, 0xE, -1);
                if (*(u8 *)(moby + 0x43) != 0x1A)
                    StartAnimationBlended(moby, 0x1A, 0, 0xF);
            }
        }
        dist16 = GetMobyAnimationValue(moby);
        if (IsValueWithinStepOfThreshold(moby, 16.0f) != 0) {
            TransformMobyJointToWorld(moby, 4, v0);
            tgt16 = *(char **)(vars + 0x30);
            if (tgt16 == (char *)((Hero_L00_003BD7E0 *)gHeroState)->ptr[0x2290 / 4]) {
                qcopy(v10, &((Hero_L00_003BD7E0 *)gHeroState)->q[0xD0 / 16]);
                pos = v10;
            } else {
                if (tgt16 == 0)
                    break;
                qcopy(v10, tgt16 + 0x10);
                pos = v10;
                v10[2] += *(f32 *)(tgt16 + 0xC) * 0.0009765625f;
            }
            FastVecSub(v20, pos, v0);
            vec_scale_to_length(v20, v20, 0.33333334f);
            PlayMobySound(0xB, 0, moby);
            SpawnSpinningEffectMoby(moby, v20, v0, 0, 0, *(u8 *)(vars + 0x54));
        } else if (dist16 < 17.0f && *(u8 *)(moby + 0x43) == 0x1E) {
            TransformMobyJointToWorld(moby, 4, v0);
            sx = RandomFloatRange(1.0f, 1.5f) * 210000.0f;
            sy = RandomFloatRange(0.2f, 0.4f) * 210000.0f;
            sz = RandomSignedFloatRange(0.0f, 0.1f);
            SpawnGravityFadeParticle(v0, D_L00_001A8F20, 4, 0x808080, 9, 0x4F, 0, 0, sx, sy, sz);
        }
        break;
    }

    stateByte = *(u8 *)(moby + 0x20);
    if (stateByte == 12 || stateByte == 13 || stateByte == 14 || stateByte == 16) {
        u8 *recA;
        recA = *(s32 *)(vars + 0x2C4) * 0x70 + gSoundState;
        if (*(char **)(recA + 0x88) != moby || recA[0x74] == 0)
            *(s32 *)(vars + 0x2C4) = PlayMobySound(10, 4, moby);
    } else {
        u8 *recB;
        slotIndex = *(s32 *)(vars + 0x2C4);
        if (slotIndex != -1) {
            recB = slotIndex * 0x70 + gSoundState;
            if (*(char **)(recB + 0x88) == moby && recB[0x74] != 0)
                StopSoundVoice(slotIndex);
        }
        *(s32 *)(vars + 0x2C4) = -1;
    }
    UpdateClass2484BodyAndGroup(moby);
    TickClass2484Timers(moby);
    AddDrawCallbackToList3(DrawClass2484Effects, moby);
}
