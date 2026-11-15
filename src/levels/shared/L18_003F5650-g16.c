/*
 * func_L18_003F5650 (levels 18, 19, 20), built on its own at -G16. Cases 12 and 13 share
 * the function-scope `grp`, as retail does: one pseudo, so both loops keep it in $a1.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char D_00189E20[];
extern char D_00189EA0[];
extern u8 *D_0018C2BC[];
extern s32 D_0018C0B4[];
extern s32 D_001A7A00[] __attribute__((section(".sdata")));
extern u8 *D_L18_001BFC18[];
extern u8 *D_L18_001C3C80[];
extern u32 D_L18_001B2348[] __attribute__((section(".sdata")));
/* The 16-byte offset vector (0, 0, 0.5, 0); its size keeps it $gp-relative at -G16. */
extern float D_L18_001B0420[4] __attribute__((sda));
extern u16 *D_L18_001FB320[];
extern s32 D_L18_001B2838[] __attribute__((section(".sdata")));
extern u8 *D_L18_001B281C[] __attribute__((section(".sdata")));
extern s32 *D_L18_001FE480[];

extern int func_00277258(void *, int, void *, float);
extern int func_00277F48(void *, int, void *, int, float);
extern float func_0029F530(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern void func_002A05A8(void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern u8 *func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern void func_002ACB48(void *, float);
extern int func_002ACBC8(void *, int);
extern void func_002B1350(void *, void *, void *, int);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_L09_0033E690(void *, int, float);
extern int func_L14_00423CD0(void *, void *, int, s16 *, int, float);
extern void func_L18_0032B768(void *, int, int);
extern void func_L18_003F72D8(void *, void *);
extern int func_L18_003F7320(void *);
extern int func_L18_003F7358(void *, void *);
extern int func_L18_003F73B8(void *, void *);
extern int func_L18_003F7470(void *);
extern void func_L18_003F74B8(void *, int);
extern u8 *func_L18_003F75E8(void *, s32 *);
extern void func_L18_003F76F0(void *, void *, void *);
extern int func_L18_003F8E80(void *);

/* Runs the Protopet state machine: idling, wandering, chasing, attacking, shooting and dying. */
void func_L18_003F5650(u8 *moby)
{
    float point[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    s32 spawnLimit;
    u8 *vars;
    s32 groupId;

    vars = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 3:
        if (SetFirstPendingFlag(moby) != 0) {
            *(s16 *)(vars + 0x2A6) = 0;
            StartAnimationBlended(moby, 9, 0, 3);
            func_002A05A8(moby);
            moby[0x31] = 1;
            *(float *)(moby + 0x2C) = 0.001f;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            *(s16 *)(vars + 0x294) = 0;
            *(s16 *)(vars + 0x29E) = RandomIntRange(0xB4, 0xB4);
            *(s16 *)(vars + 0x2A4) = RandomIntRange(2, 4);
        } else {
            if (*(s16 *)(vars + 0x2A6) == 0 && *(u16 *)(moby + 0x96) >= 0x1F) {
                *(s16 *)(vars + 0x2A6) = 1;
            }
            if (*(float *)(moby + 0x2C) < *(float *)(vars + 0x268)) {
                *(float *)(moby + 0x2C) += *(float *)(vars + 0x268) * 0.1f;
            }
            if (IsActionFinished(moby) != 0) {
                *(float *)(moby + 0x2C) = *(float *)(vars + 0x268);
                SetMobyState(moby, 6, 2);
                SetMobyState(moby, 7, -1);
            }
        }
        *(TI128 *)offset = 0;
        offset[2] = *(float *)(vars + 0x104) + *(float *)(vars + 0x100);
        *(TI128 *)vec = *(TI128 *)offset;
        FastVecAdd(point, moby + 0x10, vec);
        SweepCollisionFromObject(moby, point, 0x4000000, 0, 1, 0, *(float *)(vars + 0x100) + 0.2f, 10.0f, 1.0f);
        break;
    case 2:
        if (SetFirstPendingFlag(moby) != 0) {
            *(float *)(vars + 0x100) = 0.34f;
            *(float *)(vars + 0x108) = 0.1f;
            *(float *)(vars + 0x104) = 0.0f;
            if (moby[0x43] != 9) {
                StartAnimationBlended(moby, 9, 0, 0);
            }
            moby[0x31] = 0;
            moby[0xBC] = 0;
            *(u16 *)(moby + 0x34) |= 1;
            break;
        }
        if (moby[0xBC] == 0) {
            if (IsPointInCuboid(gHeroPosition, *(s32 *)(vars + 0x270)) != 0) {
                *(u16 *)(moby + 0x96) = 0;
                moby[0xBC] = 1;
            }
            break;
        }
        if (moby[0xBC] != 1) {
            break;
        }
        *(TI128 *)offset = 0;
        offset[2] = *(float *)(vars + 0x104) + *(float *)(vars + 0x100);
        *(TI128 *)vec = *(TI128 *)offset;
        FastVecAdd(point, moby + 0x10, vec);
        SweepCollisionFromObject(moby, point, 0x4000000, 0, 1, 0, *(float *)(vars + 0x100) + *(float *)(vars + 0x100), 10.0f,
                      1.0f);
        if (*(u16 *)(moby + 0x96) >= 0xB) {
            vec_scale_to_length(offset, moby + 0xC0, 0.06666667f);
            offset[2] = 0.033333335f;
            LaunchProtopetShot(moby, moby + 0x10, offset);
        }
        break;
    case 7:
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x43] != 0) {
                StartAnimationBlended(moby, 0, 0, 0xA);
            }
        } else if (moby[0x60] & 2) {
            SetMobyState(moby, moby[0x94], -1);
        }
        break;
    case 16: {
        float heroDistance;
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x43] != 2) {
                StartAnimationBlended(moby, 2, 0, 0xA);
            }
            vec_scale_to_length(vars + 0x1A0, moby + 0xC0, -0.06666667f);
            break;
        }
        heroDistance = GetMobyAnimationValue(moby);
        if (*(float *)(moby + 0x48) == 1.0f && 23.0f < heroDistance) {
            *(float *)(moby + 0x48) = -0.65f;
            vec_scale_to_length(vars + 0x1A0, moby + 0xC0, 0.13333334f);
            *(float *)(vars + 0x1A8) += 0.1388889f;
        } else if (*(float *)(moby + 0x48) == -0.65f && heroDistance < 3.0f) {
            *(float *)(moby + 0x48) = 1.0f;
            SetMobyState(moby, moby[0x94], -1);
        }
        break;
    }
    case 6:
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x43] != RandomIntBelow(2) + 1) {
                StartAnimationBlended(moby, RandomIntBelow(2) + 1, 0, RandomIntRange(9, 0xF));
            }
            *(s32 *)(vars + 0x250) = RandomIntRange(0x1E0, 0x258);
        } else if (*(s32 *)(vars + 0x258) != 0) {
            SetMobyState(moby, 0xB, -1);
        } else if (*(s32 *)(vars + 0x278) != -1) {
            SetMobyState(moby, 0xD, -1);
        } else if (*(s32 *)(vars + 0x248) == 1 && D_0018C0B4[0] != 0x6F) {
            SetMobyState(moby, 0xC, -1);
        }
        if (moby[0x60] & 2) {
            if (RandomIntBelow(0x31) == 0) {
                if (moby[0x43] != 0xA) {
                    StartAnimationBlended(moby, 0xA, 0, RandomIntRange(9, 0xF));
                }
                *(float *)(moby + 0x48) = RandomFloatRange(0.85f, 1.15f);
            } else {
                if (moby[0x43] != RandomIntBelow(2) + 1) {
                    StartAnimationBlended(moby, RandomIntBelow(2) + 1, 0, RandomIntRange(9, 0xF));
                }
                *(float *)(moby + 0x48) = RandomFloatRange(0.85f, 1.15f);
            }
        }
        break;
    case 8:
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x43] != 0xA) {
                StartAnimationBlended(moby, 0xA, 0, 0xA);
            }
        } else if (moby[0x60] & 2) {
            SetMobyState(moby, moby[0x94], -1);
        }
        break;
    case 9:
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x43] != 6) {
                StartAnimationBlended(moby, 6, 0, 0xA);
            }
            moby[0xBC] = 0;
            *(s16 *)(vars + 0x298) = 0;
            break;
        }
        if (moby[0xBC] == 0 && (moby[0x60] & 2)) {
            if (moby[0x43] != 7) {
                StartAnimationBlended(moby, 7, 0, 0xA);
            }
            moby[0xBC] = 1;
        } else if (moby[0xBC] == 1) {
            spawnLimit = 0x32;
            if (*(u16 *)(moby + 0x96) >= 0x15) {
                u8 *spawn;
                *(u16 *)(moby + 0x96) = 0;
                spawn = CountGroupProtopets(*(u8 **)(vars + 0x25C), &spawnLimit);
                if (spawn != 0) {
                    float wobble;
                    FastVecAdd(point, moby + 0x10, D_L18_001B0420);
                    ClearVector128(vec);
                    vec[2] = 0.13333334f;
                    wobble = RandomFloatRange(2.0f, 3.0f) * 0.016666668f;
                    vec[0] = vec[0] + (RandomIntBelow(2) != 0 ? wobble : -wobble);
                    wobble = RandomFloatRange(2.0f, 3.0f) * 0.016666668f;
                    vec[1] = vec[1] + (RandomIntBelow(2) != 0 ? wobble : -wobble);
                    LaunchProtopetShot(spawn, point, vec);
                    *(s32 *)(spawn + 0xB8) = *(s32 *)(moby + 0xB8);
                    (*(s16 *)(vars + 0x298))++;
                }
            }
            if (*(s16 *)(vars + 0x298) >= 3 || spawnLimit == 0) {
                if (moby[0x43] != 8) {
                    StartAnimationBlended(moby, 8, 0, 0xA);
                }
                moby[0xBC] = 2;
            }
        } else if (moby[0xBC] == 2) {
            if (moby[0x60] & 2) {
                SetMobyState(moby, moby[0x94], -1);
            }
        }
        break;
    case 10: {
        float heroDistance;
        s32 count;
        s32 i;
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x43] != 5) {
                StartAnimationBlended(moby, 5, 0, 0xA);
            }
            break;
        }
        heroDistance = GetMobyAnimationValue(moby);
        if (moby[0x42] == 5 && heroDistance < 10.0f) {
            SetControllerSpeedLimits(moby, 0.083333336f, 0.33333334f, 0.1939255f, 2.9088826f);
            if (moby[0x94] == 0xB && *(u8 **)(vars + 0x258) != 0) {
                StartTurnTowardTarget(moby, *(u8 **)(vars + 0x258) + 0x10);
            } else {
                StartTurnTowardTarget(moby, vars + 0x1F0);
            }
        }
        if (moby[0x42] == 5 && 10.0f < heroDistance && heroDistance < 17.0f) {
            TransformMobyJointToWorld(moby, 0, point);
            count = ProcessCollisionHit(point, 0, moby, 0, 0.2f);
            if (count != 0) {
                for (i = 0; i < count; i++) {
                    u8 *other = gNearbyHitTargets[i];
                    char *hero = gHeroState;
                    if (other == *(u8 **)(hero + 0x2290)) {
                        qcopy(vec, hero + 0x80);
                    } else {
                        qcopy(vec, other + 0x10);
                        if (*(s16 *)(other + 0xAA) == 0xB69 /* Protopet */) {
                            continue;
                        }
                    }
                    FastVecSub(offset, other + 0x10, moby + 0x10);
                    offset[2] = 0.0f;
                    vec_scale_to_length(offset, offset, 2.0f);
                    offset[3] = 5627.925f;
                    QueueImpactEffect(other, moby, 0x10001, other + 0x10, offset, vars[0x34]);
                }
            }
        }
        if (moby[0x60] & 2) {
            SetControllerSpeedLimits(moby, 0.0044444446f, 0.13333334f, 0.003490659f, 0.20943955f);
            if (gActiveAttackerRobot[0] == moby) {
                u8 next = moby[0x94];
                SetMobyState(moby, 8, -1);
                moby[0x94] = next;
            } else {
                SetMobyState(moby, moby[0x94], -1);
            }
        }
        break;
    }
    case 11: {
        u8 *other;
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x43] != 4) {
                StartAnimationBlended(moby, 4, 0, 0xA);
            }
            *(float *)(vars + 0x24C) = 0.017453294f;
            break;
        }
        qcopy_nc(vars + 0x230, *(u8 **)(vars + 0x258) + 0x10);
        if (IsInStateSix(*(u8 **)(vars + 0x258)) != 0 && IsTargetCloseAndInFront(moby, *(u8 **)(vars + 0x258) + 0x10) != 0) {
            SetMobyState(moby, 0xA, -1);
            break;
        }
        if (IsNearPickupReady(moby, *(u8 **)(vars + 0x258)) != 0) {
            SetMobyState(moby, 8, -1);
            break;
        }
        other = *(u8 **)(vars + 0x258);
        if (other == 0 || other[0x20] == 0xFE || other[0x20] == 0xFD || (*(u16 *)(other + 0x34) & 1)) {
            *(u8 **)(vars + 0x258) = 0;
            SetMobyState(moby, 0xC, -1);
            SetMobyState(moby, 8, -1);
        }
        break;
    }
    case 12: {
        u8 phase;
        if (SetFirstPendingFlag(moby) != 0) {
            float turnDegrees;
            if (moby[0x43] != 4) {
                StartAnimationBlended(moby, 4, 0, 0xA);
            }
            turnDegrees = RandomFloatRange(15.0f, 30.0f);
            *(float *)(vars + 0x24C) = turnDegrees * (RandomIntBelow(2) != 0 ? -0.017453294f : 0.017453294f);
            moby[0xBC] = 0;
        }
        phase = moby[0xBC];
        if (phase == 0) {
            qcopy(vars + 0x230, vars + 0x1F0);
            groupId = *(s32 *)(vars + 0x27C);
            if (groupId != -1 && (D_L18_001B2348[0] & 7) == (((s32)moby >> 8) & 7)) {
                u16 *groupEntry;
                float best = 1000.0f;
                s32 lost = 1;
                for (groupEntry = D_L18_001FB320[groupId];
                     (u8)groupId != 0xFF && groupId <= D_L18_001B2838[0] && groupEntry != 0
                     && ((groupEntry != 0 && (s16)groupEntry[-1] >= 0) || groupEntry == D_L18_001FB320[groupId]);
                     groupId = *(s32 *)(vars + 0x27C), groupEntry++) {
                    u8 *other = gMobyTable_L18[0] + ((*groupEntry & 0x7FFF) << 8);
                    if (other == 0) {
                        break;
                    }
                    if (other[0x20] != 0xFE) {
                        if (other[0x20] != 0xFD) {
                            float candidateDistance;
                            lost = 0;
                            candidateDistance = vec_distance_xy(moby + 0x10, other + 0x10);
                            if (candidateDistance < best) {
                                best = candidateDistance;
                            }
                        }
                    }
                }
                if (lost) {
                    *(s32 *)(vars + 0x278) = -1;
                    *(s32 *)(vars + 0x27C) = -1;
                }
            }
            if (IsTargetCloseAndInFront(moby, vars + 0x1F0) != 0) {
                *(u16 *)(moby + 0x96) = 0;
                moby[0xBC] = 1;
                if (moby[0x43] != RandomIntBelow(2) + 1) {
                    StartAnimationBlended(moby, RandomIntBelow(2) + 1, 0, 0xA);
                }
            }
        } else if (phase == 1) {
            if (IsTargetCloseAndInFront(moby, vars + 0x1F0) != 0 && *(s32 *)(vars + 0x180) < 2) {
                SetMobyState(moby, 0xA, -1);
            } else if (*(u16 *)(moby + 0x96) >= 0x3D) {
                SetMobyState(moby, 0xC, -1);
            }
        }
        if (FindProtopetForGroup(moby) != 0) {
            SetMobyState(moby, 9, 2);
        }
        if (*(s32 *)(vars + 0x248) != 1) {
            SetMobyState(moby, 6, -1);
        }
        break;
    }
    case 13: {
        u16 *groupEntry;
        s32 lost;
        if (SetFirstPendingFlag(moby) != 0) {
            float turnDegrees;
            if (moby[0x43] != 4) {
                StartAnimationBlended(moby, 4, 0, 0xA);
            }
            *(s16 *)(vars + 0x29A) = MeasureMobyAgainstPathEntry(moby + 0x10, *(s32 *)(vars + 0x278), 0.0f);
            turnDegrees = RandomFloatRange(15.0f, 30.0f);
            *(float *)(vars + 0x24C) = turnDegrees * (RandomIntBelow(2) != 0 ? -0.017453294f : 0.017453294f);
            SetControllerSpeedLimits(moby, 0.0016666667f, 0.050000004f, 0.003490659f, 0.10471977f);
            break;
        }
        AdvanceAlongPath_L14(moby, vars + 0x230, *(s32 *)(vars + 0x278), (s16 *)(vars + 0x29A), 0, 3.0f);
        groupId = *(s32 *)(vars + 0x27C);
        if (groupId == -1) {
            break;
        }
        if ((D_L18_001B2348[0] & 0x3F) != (((s32)moby >> 8) & 0x3F)) {
            break;
        }
        lost = 1;
        for (groupEntry = D_L18_001FB320[groupId];
             (*(s32 *)(vars + 0x27C) & 0xFF) != 0xFF && *(s32 *)(vars + 0x27C) <= D_L18_001B2838[0] && groupEntry != 0
             && ((groupEntry != 0 && (s16)groupEntry[-1] >= 0) || groupEntry == D_L18_001FB320[*(s32 *)(vars + 0x27C)]);
             groupEntry++) {
            u8 *other = gMobyTable_L18[0] + ((*groupEntry & 0x7FFF) << 8);
            if (other == 0) {
                break;
            }
            if (other[0x20] != 0xFE) {
                if (other[0x20] != 0xFD) {
                    lost = 0;
                    break;
                }
            }
        }
        if (lost) {
            *(s32 *)(vars + 0x278) = -1;
            *(s32 *)(vars + 0x27C) = -1;
            SetMobyState(moby, 0xC, -1);
        }
        break;
    }
    case 14:
        if (SetFirstPendingFlag(moby) != 0) {
            s32 next;
            s32 *path;
            *(float *)(vars + 0xAC) = 1.0f;
            *(float *)(vars + 0xA8) = 1.0f;
            *(float *)(vars + 0x134) = 0.001f;
            *(s16 *)(vars + 0x29A) = MeasureMobyAgainstPathEntry(moby + 0x10, *(s32 *)(vars + 0x26C), 0.0f);
            if (*(s16 *)(vars + 0x29C) != 0) {
                if (*(s16 *)(vars + 0x29A) == 0) {
                    next = *D_L18_001FE480[*(s32 *)(vars + 0x26C)] - 1;
                } else {
                    next = *(s16 *)(vars + 0x29A) - 1;
                }
            } else {
                next = (*(s16 *)(vars + 0x29A) == *D_L18_001FE480[*(s32 *)(vars + 0x26C)] - 1) ? 0
                                                                                           : *(s16 *)(vars + 0x29A) + 1;
            }
            path = D_L18_001FE480[*(s32 *)(vars + 0x26C)];
            FastVecSub(point, path + (next * 4 + 4), path + (*(s16 *)(vars + 0x29A) * 4 + 4));
            FastVecSub(vec, D_L18_001FE480[*(s32 *)(vars + 0x26C)] + (*(s16 *)(vars + 0x29A) * 4 + 4), moby + 0x10);
            if (FastVecDot(vec, point) < 0.0f) {
                *(s16 *)(vars + 0x29A) = next;
            }
            *(s32 *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
            if (moby[0x43] != RandomIntBelow(2) + 1) {
                StartAnimationBlended(moby, RandomIntBelow(2) + 1, RandomIntBelow(0xA), 0xA);
            }
            moby[0xBC] = 0;
            break;
        }
        if (moby[0xBC] == 0) {
            if (*(s32 *)(vars + 0x270) != -1 && IsPointInCuboid(gHeroPosition, *(s32 *)(vars + 0x270)) != 0) {
                moby[0xBC] = 1;
                *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
                SetTableEntryByte(moby, 0, 2);
            }
        } else {
            float targetDistance;
            u8 *pos;
            if (AdvanceAlongPath_L14(moby, vars + 0x230, *(s32 *)(vars + 0x26C), (s16 *)(vars + 0x29A),
                                  *(s16 *)(vars + 0x29C), 0.2f) == 0) {
                SetMobyState(moby, 0xF, -1);
            }
            pos = moby + 0x10;
            targetDistance = fast_vec_dist(pos, gHeroPosition);
            if (targetDistance < 8.0f) {
                if (moby[0x43] != 1) {
                    StartAnimationBlended(moby, 1, 0, 0xA);
                }
                if (targetDistance < 2.0f) {
                    u8 *hit;
                    float reach;
                    qcopy(point, pos);
                    point[2] = point[2] + (*(float *)(vars + 0x104) + *(float *)(vars + 0x100));
                    reach = *(float *)(vars + 0x100) + 0.2f;
                    SweepCollisionFromObject(moby, point, 1, 0, 1, 0, reach, IntToFloat(D_001A7A00[0]) * 0.25f, 1.0f);
                    if (TestPointAgainstCollision(point, 1, moby, *(float *)(vars + 0x100) + 0.2f) != 0) {
                        hit = D_L18_001BFC18[0];
                        if (hit != 0 && *(s16 *)(hit + 0xAA) != 0xB69 /* Protopet */) {
                            *(s32 *)(vars + 0x20) = 0;
                            vec_scale_to_length(vec, moby + 0xC0, -1.0f);
                            AddRandomOffsetToVector(vec, 0.3f);
                            ApplyObjectReaction(moby, vars + 0x50, vec, 2);
                            SetMobyState(moby, 0x11, 3);
                        }
                    }
                }
            }
        }
        break;
    case 15:
        if (SetFirstPendingFlag(moby) != 0) {
            AddRandomOffsetToVector(vars + 0x1A0, 0.050000004f);
            *(float *)(vars + 0x1A8) = 0.083333336f;
            if (moby[0x43] != 0xD) {
                StartAnimationBlended(moby, 0xD, 0, 0xA);
            }
        } else if (*(u16 *)(moby + 0x96) >= 0x12D) {
            SetDeathBits(moby, 0, 1);
            EndCurrentAction(moby, 0);
        }
        break;
    case 17: {
        s32 flags;
        float heroDistance;
        if (SetFirstPendingFlag(moby) != 0) {
            if (moby[0x42] == 0xC || moby[0x43] == 0xC) {
                *(u16 *)(moby + 0x34) &= 0xEFFF;
            }
            if (moby[0x94] == 0xE) {
                FastVecScale(vars + 0xD0, vars + 0xD0, 3.0f);
            }
        }
        flags = DispatchActionByKind(moby, vars + 0x50);
        if (moby[0x94] == 0xE || moby[0x94] == 0xF) {
            heroDistance = GetMobyAnimationValue(moby);
            if (moby[0x42] == 0xB && 16.0f < heroDistance) {
                SetMobyState(moby, 0xF, -1);
            }
        }
        heroDistance = GetMobyAnimationValue(moby);
        if ((flags & 1) || (moby[0x42] == 0xC && 15.0f < heroDistance && RandomIntBelow(0xF) == 0)) {
            SetDeathBits(moby, 0, 1);
            EndCurrentAction(moby, 0);
            break;
        }
        if (flags & 2) {
            u8 mode;
            *(u8 **)(vars + 0x258) = 0;
            mode = moby[0x95];
            SetMobyState(moby, 0xC, 2);
            if (mode == 1) {
                SetMobyState(moby, 7, -1);
            }
        }
        break;
    }
    case 18:
        if (SetFirstPendingFlag(moby) != 0) {
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            if (moby[0x95] == 2) {
                if (moby[0x43] != 3) {
                    StartAnimationBlended(moby, 3, 0, 0xA);
                }
            }
            *(float *)(moby + 0x48) = 1.0f;
        }
        if ((moby[0x60] & 2) || *(u16 *)(moby + 0x96) >= 0x3D) {
            *(s32 *)(vars + 0x20) = 0;
            SetDeathBits(moby, 0, 1);
            EndCurrentAction(moby, 0);
        }
        break;
    case 0:
    default:
        break;
    }
}
