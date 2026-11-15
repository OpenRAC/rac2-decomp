/* func_L00_003D54B0 (levels 00 and 07; 4,424 bytes): family F28, the same body as func_00320550 (boot),
 * written from func_00322CC0 (src/game/00322CC0.c).
 * D_L00_001A8F00 (the mode word) is reached through the address macro (MACRO_ADDR): lui/lw in flow,
 * $gp in delay slots.  The func_00322690 table is an sda incomplete array.
 * func_0032C700 returns a pointer: a value-returning call sets $v0, which gives sched2
 * retail's `li.s $f12; li $v0,1; li.s $f13` before it.
 */
#include "common.h"

typedef int Quad003D54B0 __attribute__((mode(TI)));

extern int D_L00_001A8F00 MACRO_ADDR;
extern u8 D_00188660[];
extern char D_L00_001A8F20[] __attribute__((sda));
extern char D_L00_001B0318[];

extern int func_003216E8(char *);
extern void func_0029F338(void *);
extern int func_002B3890(char *);
extern void func_002B60B0(void *, float, float, float, float);
extern float func_00282C48(float);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_002A7820(int, int);
extern float func_00282E80(void *, void *);
extern void *func_002A9640(void *, u32, s32);
extern int func_002B1C20(char *, char *);
extern int func_002E5CF8(int, int, char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_00322A30(void *);
extern void func_002A6C58(char *, int, int);
extern int func_002B5258(char *);
extern void func_002AEF28(char *, char *, char *, float, float, float);
extern float func_002A7E08(char *, char *, char *, float, float, float);
extern float func_002AA3A8(void *, float, void *, float, float, float);
extern float func_002A89A8(void *, int, float);
extern void func_002E59F8(s32);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_0026FEB8(const char *, ...);
extern void func_002833F0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E20(void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00282E48(void *, void *);
extern float func_00283C80(float, float);
extern int func_002B4FF0(char *, void *, float);
extern int func_002B50E0(char *, void *, float);
extern void func_00322690(float, char *, void *, int);
extern void func_0027CFD0(void (*)(char *), char *);
extern void func_003225C0(char *);
extern void func_00321E80(char *);
extern void func_00321FE0(char *);

/* Per-frame update of a flying enemy. It idles, hovers and chases the player, takes hits, and crashes and explodes when its health runs out. */
void func_L00_003D54B0(char *self)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);

    if (InitAndUpdateRobotEnemyHealth(self) != 0) {
        MarkMobySpawned(self);
        return;
    }

    if (D_L00_001A8F00 == 2) {
        *(u16 *)(self + 0x34) |= 0x41;
        *(u16 *)(self + 0x34) &= ~0x1000;
        *(int *)(self + 0x98) = 0;
        return;
    }

    *(u16 *)(self + 0x34) &= ~0x41;
    *(u16 *)(self + 0x34) |= 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        if (SetSecondPendingFlag(self) != 0)
            SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0
            && FloatAbs(*(float *)(self + 0x18) - *(float *)(vars + 0x238)) < 2.0f && D_L00_001A8F00 != 2) {
            SetMobyState(self, 0xB, 4);
            if (*(u8 *)(self + 0x43) != 1)
                StartAnimationBlended(self, 1, 0, 4);
            if (*(int *)(vars + 0x288) != -1) {
                SetMobyState(self, 0xA, 1);
                if (*(u8 *)(self + 0x43) != 0x1A)
                    StartAnimationBlended(self, 0x1A, 0, 4);
            }
        } else if (*(s16 *)(vars + 0x276) != 0) {
            SetMobyState(self, 9, 3);
            *(s16 *)(vars + 0x276) = 0;
            if (*(s16 *)(vars + 0x270) < 300)
                *(s16 *)(vars + 0x270) = RandomIntRange(480, 600);
        }
        break;
    case 2: {
        char *hit;
        if (SetSecondPendingFlag(self) != 0)
            SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            SetMobyState(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                StartAnimationBlended(self, 0x19, 0, 4);
            *(int *)(vars + 0x2B0) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            SetMobyState(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                StartAnimationBlended(self, 0x19, 0, 4);
            *(int *)(vars + 0x2B0) = 1;
        }
        hit = FindOwnedEffectSlot(*(char **)(vars + 0x2AC), 0x10000, 0);
        if (hit != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(hit + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2AC) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xF;
            if (*(int *)(vars + 0x2B0) == 0) {
                SetMobyState(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    StartAnimationBlended(self, 0x19, 0, 4);
                *(int *)(vars + 0x2B0) = 1;
            }
            if (*(float *)(vars + 0x20) <= 0.0f)
                SetMobyState(self, 0xF, 5);
        }
        qcopy(*(char **)(vars + 0x2AC) + 0x10, self + 0x10);
        break;
    }
    case 3:
        if (SetSecondPendingFlag(self) != 0)
            SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0) {
            SetMobyState(self, 0xB, 4);
            if (*(u8 *)(self + 0x43) != 1)
                StartAnimationBlended(self, 1, 0, 4);
        } else if (*(s16 *)(vars + 0x270) == 0) {
            SetMobyState(self, 2, 0);
            if (*(u8 *)(self + 0x43) != 3)
                StartAnimationBlended(self, 3, 0, 0xA);
        }
        break;
    case 4:
        if (SetSecondPendingFlag(self) != 0)
            SetControllerSpeedLimits(self, 0.0044444446f, 0.13333334f, 0.001163553f, 0.10471977f);
        if (*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1) {
            if (*(u8 *)(self + 0x20) != 5) if (*(u8 *)(self + 0x20) != 4) {
                SetMobyState(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 6)
                    StartAnimationBlended(self, 6, 0, 0xA);
                *(s16 *)(vars + 0x270) = RandomIntRange(580, 600);
            }
        }
        break;
    case 5: {
        int flags = DispatchActionByKind(self, vars + 0x60);
        int index = *(int *)(vars + 0x2C0);
        if (index != -1) {
            u8 *slot = gSoundState + index * 0x70;
            if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                StopSoundVoice(index);
        }
        *(int *)(vars + 0x2C0) = -1;
        if ((flags & 1) || *(float *)(vars + 0x20) <= 0.0f) {
            char *child;
            PlayMobySound(0xC, 0, self);
            child = *(char **)(vars + 0x2AC);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7 /* moby class 2743 */)
                MarkMobySpawned(child);
            *(Quad003D54B0 *)v = 0;
            v[2] = 0.75f;
            *(u16 *)(self + 0x34) |= 0x41;
            *(u16 *)(self + 0x34) &= ~0x1000;
            *(int *)(self + 0x98) = 0;
            matrix_mul_vec3(v, v, self + 0xC0);
            FastVecAdd(v, v, self + 0x10);
            SpawnExplosion(v, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);
            SpawnRobotDeathDebris(self);
            SetDeathBits(self, 0, 3);
            MarkMobySpawned(self);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                SetMobyState(self, 0xC, 4);
                if (*(u8 *)(self + 0x43) != 0x1C)
                    StartAnimationBlended(self, 0x1C, 0, 0xA);
            } else {
                SetMobyState(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 6)
                    StartAnimationBlended(self, 6, 0, 0xA);
                *(s16 *)(vars + 0x270) = RandomIntRange(580, 600);
            }
        }
        break;
    }
    }

    switch (*(u8 *)(self + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2BC) == 0)
            StepMovementAtOwnPosition(self);
        break;
    case 3:
        ScaleOwnerWordsByAngles(self, vars + 0x2A4, vars + 0x2A8, 0.06981318f, 0.052359886f, 0.013089972f);
        break;
    case 5: {
        u8 *slot = gSoundState + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float y;
        *(int *)(vars + 0x2A0) += 1;
        if (*(char **)(slot + 0x88) != self || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = PlayMobySound(0xD, 4, self);
        TurnTowardPosition(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        SpringFloatToGoal(self + 0xF4, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        SpringFloatToGoal(self + 0xF0, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        height = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f);
        y = *(float *)(self + 0x18);
        if (y - height > 0.05f) {
            *(float *)(self + 0x18) = y - height * 0.00025f;
        } else {
            int index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *other = gSoundState + index * 0x70;
                if (*(char **)(other + 0x88) == self && other[0x74] != 0)
                    StopSoundVoice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            SetMobyState(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                StartAnimationBlended(self, 0xE, 0, 3);
        }
        if (*(u8 *)(self + 0x60) & 2) {
            SetMobyState(self, 4, -1);
            if (*(u8 *)(self + 0x43) != 0x1A)
                StartAnimationBlended(self, 0x1A, 0, 0xF);
        }
        break;
    }
    case 4: {
        float height;
        float above;
        *(int *)(vars + 0x2A0) += 1;
        TurnTowardPosition(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        SpringFloatToGoal(self + 0xF4, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        SpringFloatToGoal(self + 0xF0, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        height = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            StepValueTowardTarget(self + 0x18, vars + 0x280, height, 0.016666668f, 0.16333334f, 0.16666667f);
        } else {
            int index;
            char *child;
            STUB_printf(D_L00_001B0318, *(int *)(vars + 0x2A0));
            index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *slot = gSoundState + index * 0x70;
                if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                    StopSoundVoice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            SetMobyState(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                StartAnimationBlended(self, 0xE, 0, 3);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            child = *(char **)(vars + 0x2AC);
            if (*(s16 *)(child + 0xAA) == 0xAB7 /* moby class 2743 */)
                MarkMobySpawned(child);
            *(float *)(vars + 0x30) = 0.5f;
            *(u16 *)(self + 0x34) |= 0x1000;
        }
        break;
    }
    case 6:
        if (*(u8 *)(self + 0x60) & 2) {
            SetMobyState(self, 7, -1);
            if (*(u8 *)(self + 0x43) != 0xD)
                StartAnimationBlended(self, 0xD, 0, 0xF);
        }
        break;
    case 7: {
        float height;
        float above;
        SpringFloatToGoal(self + 0xF4, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        TurnTowardPosition(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        height = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            StepValueTowardTarget(self + 0x18, vars + 0x280, height, 0.025000002f, 0.16333334f, 0.25f);
        } else {
            SetMobyState(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                StartAnimationBlended(self, 0xE, 0, 3);
        }
        break;
    }
    case 8:
        if (*(u8 *)(self + 0x60) & 2) {
            SetMobyState(self, 0xC, 4);
            if (*(u8 *)(self + 0x43) != 0x1C)
                StartAnimationBlended(self, 0x1C, 0, 0xF);
            *(float *)(self + 0x18) = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f);
        }
        break;
    case 10:
        qcopy(v, vars + 0x380);
        v[2] -= 3.0f;
        FastVecSub(w, v, self + 0x10);
        *(float *)(self + 0xF8) = FastMatrixHelperA(w[0], w[1]);
        *(float *)(self + 0xF4) = FastMatrixHelperA(vec_length_xy(w), w[2]);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        SpringVectorToTarget(self + 0x10, v, vars + 0x280, 0.016666668f, 0.0f, 0.33333334f);
        if (fast_vec_dist(self + 0x10, v) < 0.4f) {
            if (*(u8 *)(self + 0x43) != 0xD)
                StartAnimationBlended(self, 0xD, 0, 0xA);
            SetMobyState(self, 7, -1);
        }
        break;
    case 11:
        StepMovementAtOwnPosition(self);
        if (*(u8 *)(self + 0x60) & 2) {
            SetControllerSpeedLimits(self, 0.0011111111f, 0.033333335f, 0.001163553f, 0.10471977f);
            SetMobyState(self, 0xC, -1);
            if (*(u8 *)(self + 0x43) != 0x1C)
                StartAnimationBlended(self, 0x1C, 0, 0xF);
        }
        break;
    case 12:
        SetControllerSpeedLimits(self, 0.0011111111f, 0.033333335f, 0.001163553f, 0.10471977f);
        if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
            && FastDiffRots(*(float *)(self + 0xF8),
                             FastMatrixHelperA(*(float *)(vars + 0x230) - *(float *)(self + 0x10),
                                           *(float *)(vars + 0x234) - *(float *)(self + 0x14))) < 0.38397247f) {
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            TurnTowardTargetAndStepMovement(self, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            StepMovementController(self, self + 0x10,
                          FastMatrixHelperA(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        }
        if (*(u8 *)(self + 0x42) == 0x1C)
            SpawnJointHitEffects(*(float *)(vars + 0x298), self, D_L00_001A8F20, 4);
        break;
    case 13: {
        char *target;
        if (*(u8 *)(self + 0x42) == 0xF)
            RegisterOverlayDrawCallback(DrawRobotJointFlash, self);
        target = *(char **)(vars + 0x240);
        StepMovementController(self, self + 0x10,
                      FastMatrixHelperA(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                    *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        break;
    }
    case 14:
        if (*(u8 *)(self + 0x60) & 2) {
            if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                SetControllerSpeedLimits(self, 0.0044444446f, 0.13333334f, 0.001163553f, 0.10471977f);
                SetMobyState(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0x1C)
                    StartAnimationBlended(self, 0x1C, 0, 0xA);
            } else {
                SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                SetMobyState(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 7)
                    StartAnimationBlended(self, 7, 0, 0xA);
            }
        }
        break;
    }
    UpdateEnemyTimersAndLimbs(self);
    RegisterOverlayDrawCallback(DrawObjectGlowEffects, self);
}
