/* func_00322CC0: boot + 6 levels (00, 02, 07, 11, 14, 26).
 * D_001A8BB0 is reached through the assembler's address macro (MACRO_ADDR): the entry read
 * at the join expands to lui/lw in flow, and reorg's copy of it in the state-2 branch's delay
 * slot is the $gp form.  func_0032C700 returns a pointer (void *).
 */
#include "common.h"

typedef int Quad00322CC0 __attribute__((mode(TI)));

extern int D_001A8BB0 MACRO_ADDR;
extern char D_00189EA0[];
extern char *D_0018C2BC;
extern u8 D_00188660[];
extern u32 D_001F1700[];
extern char D_001B0020[];

extern int func_003248A8(char *);
extern void func_0029F338(void *);
extern void func_002B5278(char *object, float factor);
extern int func_002B3890(char *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_00282948(void *);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_00282E80(void *, void *);
extern void *func_002A9640(void *, u32, s32);
extern int func_002B1C20(char *, char *);
extern int func_002E5CF8(int, int, char *);
extern void func_00325D30(char *, char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_002B0A68(char *, int, float *, float, float, float, float, unsigned char);
extern void func_002A6C58(char *, int, int);
extern void func_002A8C28(char *, char *, int, int, int, int, float, float, float);
extern void func_002AC728(char *, char *, float, float, int);
extern int func_002B5258(char *);
extern float func_002AA2E8(void *, float, float);
extern void func_002AE8C0(char *, char *, float, float);
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
extern int func_002B6120(char *, u32);
extern float func_00283C80(float, float);
extern int func_002B4FF0(char *, void *, float);
extern int func_002B50E0(char *, void *, float);
extern float func_0029F530(char *);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);
extern void func_0027CDC8(void (*)(char *), char *);
extern void func_00325A88(char *);
extern void func_00325B28(char *);
extern void func_00325158(char *);

/* Updates a robot enemy of moby class 2827: chooses what it does from its state, chases and attacks the player, and blows up when destroyed. */
void func_00322CC0(char *self)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);

    if (InitAndUpdateGroupEnemy(self) != 0) {
        MarkMobySpawned(self);
        return;
    }

    if (*(u8 *)(self + 0x20) != 0xC && *(u8 *)(self + 0x95) != 2)
        StepMovementAtOwnPositionWithFactor(self, *(float *)(self + 0xF8));

    if (gCurrentGameMode == 2) {
        *(u16 *)(self + 0x34) |= 0x41;
        *(u16 *)(self + 0x34) &= ~0x1000;
        *(int *)(self + 0x98) = 0;
        if (*(char **)(vars + 0x2A0) != 0 && *(char **)(vars + 0x2A4) != 0) {
            *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) |= 0x41;
            *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) &= ~0x1000;
            *(int *)(*(char **)(vars + 0x2A4) + 0x98) = 0;
            *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x41;
            *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) &= ~0x1000;
            *(int *)(*(char **)(vars + 0x2A0) + 0x98) = 0;
        }
        return;
    }

    *(u16 *)(self + 0x34) &= ~0x41;
    *(u16 *)(self + 0x34) |= 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    if (*(char **)(vars + 0x2A0) != 0 && *(char **)(vars + 0x2A4) != 0) {
        *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) &= ~0x41;
        *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) |= 0x1000;
        *(int *)(*(char **)(vars + 0x2A4) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A4) + 0x24) + 0x10);
        *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) &= ~0x41;
        *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x1000;
        *(int *)(*(char **)(vars + 0x2A0) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A0) + 0x24) + 0x10);
    }

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        if (SetSecondPendingFlag(self) != 0)
            SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && gCurrentGameMode != 2) {
            if (FastFloatHelperD(vars + 0x2D0) != 0) {
                SetMobyState(self, 0xB, 4);
                if (*(u8 *)(self + 0x42) == 0) {
                    if (*(u8 *)(self + 0x43) != 1)
                        StartAnimationBlended(self, 1, 0, 4);
                } else if (*(u8 *)(self + 0x43) != 5) {
                    int a = RandomIntBelow(2);
                    StartAnimationBlended(self, 5, a, RandomIntRange(10, 20));
                }
                if (*(int *)(vars + 0x288) != -1) {
                    SetMobyState(self, 0xA, 1);
                    if (*(u8 *)(self + 0x43) != 0x1A)
                        StartAnimationBlended(self, 0x1A, 0, 4);
                }
            }
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f) {
            SetMobyState(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    StartAnimationBlended(self, 1, 0, 4);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int a = RandomIntBelow(2);
                StartAnimationBlended(self, 5, a, RandomIntRange(10, 20));
            }
            *(int *)(vars + 0x294) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0) {
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
        *(int *)(self + 0x98) = 0;
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            if (FastFloatHelperD(vars + 0x2D0) != 0) {
                SetMobyState(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    StartAnimationBlended(self, 0x19, 0, 4);
                *(int *)(vars + 0x2E4) = 1;
            }
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            SetMobyState(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                StartAnimationBlended(self, 0x19, 0, 4);
            *(int *)(vars + 0x2E4) = 1;
        }
        hit = FindOwnedEffectSlot(*(char **)(vars + 0x2E0), 0x10000, 0);
        if (hit != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(hit + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2E0) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xF;
            if (*(int *)(vars + 0x2E4) == 0) {
                SetMobyState(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    StartAnimationBlended(self, 0x19, 0, 4);
                *(int *)(vars + 0x2E4) = 1;
            }
            if (*(float *)(vars + 0x20) <= 0.0f)
                SetMobyState(self, 0xF, 5);
        }
        qcopy(*(char **)(vars + 0x2E0) + 0x10, self + 0x10);
        break;
    }
    case 3:
        if (SetSecondPendingFlag(self) != 0)
            SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0
            && ((float *)gHeroPosition)[2] - *(float *)(self + 0x18) < 3.25f) {
            SetMobyState(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    StartAnimationBlended(self, 1, 0, 4);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int a = RandomIntBelow(2);
                StartAnimationBlended(self, 5, a, RandomIntRange(10, 20));
            }
        } else if (*(s16 *)(vars + 0x270) == 0) {
            SetMobyState(self, 2, 0);
            if (*(u8 *)(self + 0x43) != 4)
                StartAnimationBlended(self, 4, 0, 0xA);
        }
        break;
    case 4:
        if (SetSecondPendingFlag(self) != 0)
            SetControllerSpeedLimits(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if ((*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1)
            || *(float *)(vars + 0x238) - *(float *)(self + 0x18) >= 3.25f) {
            if (*(u8 *)(self + 0x20) != 5) if (*(u8 *)(self + 0x20) != 4) {
                SetMobyState(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7) {
                    int a = RandomIntBelow(2);
                    StartAnimationBlended(self, 7, a, RandomIntRange(10, 20));
                }
                *(s16 *)(vars + 0x270) = RandomIntRange(580, 600);
            }
        }
        break;
    case 5: {
        int flags = DispatchActionByKind(self, vars + 0x60);
        if ((flags & 1) || (*(float *)(vars + 0x20) <= 0.0f && *(int *)(vars + 0x2EC) == 0)) {
            char *child;
            PlayMobySound(0xD, 0, self);
            DestroyAttachedParts(self, vars + 0x2A0);
            child = *(char **)(vars + 0x2E0);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7 /* moby class 2743 */)
                MarkMobySpawned(child);
            *(Quad00322CC0 *)v = 0;
            v[2] = 0.75f;
            matrix_mul_vec3(v, v, self + 0xC0);
            FastVecAdd(v, v, self + 0x10);
            SpawnExplosion(v, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);




            vec_scale_to_length(w, vars + 0xE0, 0.050000004f);
            SpawnDebrisForMaskedParts(self, 0x3F8, w, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);

            SetDeathBits(self, 0, 3);
            MarkMobySpawned(self);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                SetMobyState(self, 0xC, 4);
                if (*(u8 *)(self + 0x43) != 0xB)
                    StartAnimationBlended(self, 0xB, 0, 0xA);
            } else {
                SetMobyState(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7)
                    StartAnimationBlended(self, 7, 0, 0xA);
                *(s16 *)(vars + 0x270) = RandomIntRange(580, 600);
            }
            if (*(int *)(vars + 0x294) != 1)
                *(int *)(vars + 0x294) = 1;
        }
        if (*(int *)(vars + 0x2EC) != 0)
            SweepCollisionFromObject(self, self + 0x10, 0x10000, 0, 1, 0, 0.9f, 0.1f, 1.0f);
        break;
    }
    case 6:
        DispatchActionByKind(self, vars + 0x60);
        if ((*(u8 *)(self + 0x60) & 2) || *(float *)(self + 0x18) < 100.0f) {
            DestroyAttachedParts(self, vars + 0x2A0);
            SpawnExplosionWithSparks(self, self + 0x10, 0.5f, 13.0f, -1);
            SetDeathBits(self, 0, 3);
            MarkMobySpawned(self);
            return;
        }
        v[0] = 0.0f;
        v[1] = -0.4f;
        v[2] = 0.0f;
        FastVecAdd(self + 0x10, self + 0x10, v);
        break;
    }

    switch (*(u8 *)(self + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2F0) != 0)
            StepMovementAtOwnPosition(self);
        break;
    case 2: {
        int anim;
        FastFloatHelperD(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 8 && anim != 2 && anim != 4 && anim != 8)
            StartAnimationBlended(self, 8, 0, 0xE);
        if (*(int *)(vars + 0x2D8) > 20)
            ApproachValue(vars + 0x214, 0.050000004f, 0.00083333335f);
        else
            ApproachValue(vars + 0x214, 0.0f, 0.00083333335f);
        anim = *(u8 *)(self + 0x43);
        if (anim == 8) {
            if (*(int *)(vars + 0x2D8) == 0) {
                StartAnimationBlended(self, 4, 0, 0xC);
                if (RandomIntBelow(3) == 1 && *(u8 *)(self + 0x43) != 2)
                    StartAnimationBlended(self, 2, 0, 0xC);
            }
            WanderAroundHomePoint(self, vars + 0x200, 0.35f, 0.25f);
        } else if (anim == 2 || anim == 4) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = RandomIntRange(120, 700);
                if (*(u8 *)(self + 0x43) != 8)
                    StartAnimationBlended(self, 8, 0, 0xC);
            }
        }
        break;
    }
    case 3:
        ScaleOwnerWordsByAngles(self, vars + 0x298, vars + 0x29C, 0.06981318f, 0.052359886f, 0.013089972f);
        break;
    case 5: {
        u8 *slot = gSoundState + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float y;
        if (*(char **)(slot + 0x88) != self || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = PlayMobySound(0xB, 4, self);
        *(int *)(vars + 0x2BC) += 1;
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
            if (*(u8 *)(self + 0x43) != 0xF)
                StartAnimationBlended(self, 0xF, 0, 3);
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
        *(int *)(vars + 0x2BC) += 1;
        TurnTowardPosition(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        SpringFloatToGoal(self + 0xF4, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        SpringFloatToGoal(self + 0xF0, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        height = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            StepValueTowardTarget(self + 0x18, vars + 0x280, height, 0.016666668f, 0.16333334f, 0.16666667f);
        } else {
            int index = *(int *)(vars + 0x2C0);
            char *child;
            if (index != -1) {
                u8 *slot = gSoundState + index * 0x70;
                if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                    StopSoundVoice(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            STUB_printf(D_001B0020, *(int *)(vars + 0x2BC));
            SetMobyState(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xF)
                StartAnimationBlended(self, 0xF, 0, 3);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            child = *(char **)(vars + 0x2E0);
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
            if (*(u8 *)(self + 0x43) != 0xE)
                StartAnimationBlended(self, 0xE, 0, 0xF);
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
            if (*(u8 *)(self + 0x43) != 0xF)
                StartAnimationBlended(self, 0xF, 0, 3);
        }
        break;
    }
    case 8:
        if (*(u8 *)(self + 0x60) & 2) {
            SetMobyState(self, 0xC, 4);
            if (*(u8 *)(self + 0x43) != 8)
                StartAnimationBlended(self, 8, 0, 0xF);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            *(float *)(self + 0x18) = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f);
        }
        break;
    case 9: {
        u8 anim;
        FastFloatHelperD(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 0xB && anim != 6 && anim != 7 && anim != 0xB)
            StartAnimationBlended(self, 0xB, 0, 0xE);
        if (*(int *)(vars + 0x2D8) > 20)
            ApproachValue(vars + 0x214, 0.10000001f, 0.0016666667f);
        else
            ApproachValue(vars + 0x214, 0.0f, 0.0016666667f);
        if (*(u8 *)(self + 0x43) == 0xB) {
            if (*(int *)(vars + 0x2D8) == 0) {
                StartAnimationBlended(self, 6, 0, 0xC);
                if (RandomIntBelow(3) == 1 && *(u8 *)(self + 0x43) != 7)
                    StartAnimationBlended(self, 7, 0, 0xC);
            }
            WanderAroundHomePoint(self, vars + 0x200, 0.35f, 0.25f);
        } else if (*(u8 *)(self + 0x43) == 6 || *(u8 *)(self + 0x43) == 7) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = RandomIntRange(120, 200);
                if (*(u8 *)(self + 0x43) != 0xB)
                    StartAnimationBlended(self, 0xB, 0, 0xC);
            }
        }
        break;
    }
    case 10:
        qcopy(v, vars + 0x300);
        v[2] -= 3.0f;
        FastVecSub(w, v, self + 0x10);
        *(float *)(self + 0xF8) = FastMatrixHelperA(w[0], w[1]);
        *(float *)(self + 0xF4) = FastMatrixHelperA(vec_length_xy(w), w[2]);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        SpringVectorToTarget(self + 0x10, v, vars + 0x280, 0.016666668f, 0.0f, 0.33333334f);
        if (fast_vec_dist(self + 0x10, v) < 0.4f) {
            if (*(u8 *)(self + 0x43) != 0xE)
                StartAnimationBlended(self, 0xE, 0, 0xA);
            SetMobyState(self, 7, -1);
        }
        break;
    case 11:
        StepMovementAtOwnPosition(self);
        if (*(u8 *)(self + 0x60) & 2) {
            SetControllerSpeedLimits(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            SetMobyState(self, 0xC, -1);
            if (*(u8 *)(self + 0x43) != 0xB)
                StartAnimationBlended(self, 0xB, 0, 0xF);
        }
        break;
    case 12:
        if (*(int *)(vars + 0x2F8) != -1) {
            if (FollowPathNodes(self, gPathTable_001F1700[*(int *)(vars + 0x2F8)]) != 0
                || vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f)
                *(int *)(vars + 0x2F8) = -1;
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
                   && FastDiffRots(*(float *)(self + 0xF8),
                                    FastMatrixHelperA(*(float *)(vars + 0x230) - *(float *)(self + 0x10),
                                                  *(float *)(vars + 0x234) - *(float *)(self + 0x14))) < 0.20943953f) {
            SetMobyState(self, 0xD, -1);
            if (*(u8 *)(self + 0x43) != 0x1B)
                StartAnimationBlended(self, 0x1B, 0, 6);
            if (RandomIntBelow(2) == 1) {
                if (*(u8 *)(self + 0x43) != 0x10)
                    StartAnimationBlended(self, 0x10, 0, 6);
            }
            *(int *)(vars + 0x2B0) = 0;
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            TurnTowardTargetAndStepMovement(self, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            StepMovementController(self, self + 0x10,
                          FastMatrixHelperA(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        }
        if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 5.0f && *(u8 *)(self + 0x42) == 8) {
            if (*(u8 *)(self + 0x43) != 0xB)
                StartAnimationBlended(self, 0xB, 0, 4);
            SetControllerSpeedLimits(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        }
        break;
    case 13: {
        float frame;
        if (*(u8 *)(self + 0x60) & 2) {
            *(float *)(vars + 0x2E8) = 8.0f;
            if (gActiveAttackerRobot == self) {
                SetMobyState(self, 0xE, -1);
                if (*(u8 *)(self + 0x43) != 0x11)
                    StartAnimationBlended(self, 0x11, 0, 7);
            } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                SetControllerSpeedLimits(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                SetMobyState(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    StartAnimationBlended(self, 0xB, 0, 0xA);
            } else {
                SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                SetMobyState(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    StartAnimationBlended(self, 8, 0, 0xA);
            }
        }
        StepMovementAtOwnPosition(self);
        frame = GetMobyAnimationValue(self);
        if (*(u8 *)(self + 0x42) == 0x1B || *(u8 *)(self + 0x42) == 0x10) {
            if (frame >= 19.0f && frame <= 25.0f) {
                TestHitAtBone(self, 0, 0.35f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                TestHitAtBone(self, 1, 0.15f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                TestHitAtBone(self, 2, 0.15f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                TestHitAtBone(self, 9, 0.35f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
            }
        }
        if ((*(u8 *)(self + 0x42) == 0x1B || *(u8 *)(self + 0x42) == 0x10) && frame >= 17.0f && frame <= 25.0f) {
            RegisterWorldDrawCallback(DrawObjectTrails, self);
            RecordPositionTrail(self);
            *(float *)(vars + 0x2E8) = 25.0f;
        }
        break;
    }
    case 14: {
        float frame;
        if (*(u8 *)(self + 0x60) & 2) {
            if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                SetControllerSpeedLimits(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                SetMobyState(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    StartAnimationBlended(self, 0xB, 0, 0xA);
            } else {
                SetControllerSpeedLimits(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                SetMobyState(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    StartAnimationBlended(self, 8, 0, 0xA);
            }
        }
        StepMovementAtOwnPosition(self);
        frame = GetMobyAnimationValue(self);
        if (*(u8 *)(self + 0x42) == 0x11 && (frame <= 5.0f || (frame >= 12.0f && frame <= 15.0f)))
            *(int *)(vars + 0x2C4) = 1;
        else
            *(int *)(vars + 0x2C4) = 0;
        break;
    }
    }
    UpdateTurnAndJoints(self);
}
