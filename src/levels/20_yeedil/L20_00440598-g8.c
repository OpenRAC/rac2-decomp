#include "common.h"
extern int func_00282948(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E80(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern f32 func_00283C80(f32, f32);
extern void func_00285788(int, int);
extern void func_00285828(int, int, int, int);
extern s32 func_00288AA0(u8 *, s32);
extern s32 func_00288BE8(u8 *);
extern int func_00288FB8(int);
extern void func_0029F338(void *);
extern float func_0029F530(char *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(char *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_002A89A8(void *, int, float);
extern int func_002A8C28(void *, void *, s32, s32, s32, s32, f32, f32, f32);
extern float func_002AA2E8(float *, float, float);
extern void func_002AA800(float *, int, f32, f32);
extern void func_002ACB48(float *, float);
extern int func_002ACBC8(void *, int);
extern s32 func_002AEB60(u8 *, f32);
extern int func_002B3868(u8 *);
extern int func_002B49E0(int, int, int, int, int);
extern void func_002BDBC0(char *, char *, int, int, int, float);
extern void func_002DF3F8(void *, void *);
extern void func_002E59F8(s32);
extern int func_002E5CF8(int, int, char *);
extern void func_L00_002B30E8(void);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_002F3478(void);
extern int func_L01_00322288(void *, float);
extern void func_L20_0036E720(void);
extern void func_L20_0039DE88(char *arg0);
extern void func_L20_0039F210(char *arg0, char *arg1, int arg2);
extern void func_L20_00442140(char *arg0);
extern void func_L20_004424A0(char *actor);
extern void func_L20_00442740(char *arg0, float f);
extern void func_L20_004427C8(char *arg0, char *arg1, float f);
extern void func_L20_00442C10(char *arg0);
extern void func_L20_00442F30(char *arg0);
extern int func_L20_00443508(char *arg0, char *arg1);
extern char * func_L20_00443790(char *arg0, int arg1, char *arg2);
extern void func_L20_00443B60(char *, char *, char *, float *);
extern void func_L20_00444088(char *arg0);
extern void func_L20_00444AA8(char *arg0, float *arg1);
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; } Hero;
extern u8 D_00189E20[];

extern void func_L20_00441CB8(char *);
extern int func_L20_004421A8(char *);
extern int func_L20_00442550(char *);
extern void func_L20_00442F80(char *);
extern void func_L20_00442CD8(char *);
extern void func_L20_004435A0(char *);
extern void func_L20_00443A10(char *, char *);
extern u8 *func_L20_00443CF0(char *);
extern char *func_L20_00443D58(char *);
extern char *func_L20_00443DF0(char *);
extern int func_L20_00444018(char *);
extern void func_L20_004441D8(char *);
extern int func_L20_00440398(int);
extern char *func_L20_0039EEC8(char *, char *);
extern char *func_L20_0043F318(char *, char *, int, float, int, int);
extern void func_L20_00440570(void);
extern s32 D_L20_001A8F00[] __attribute__((sda));
/* The same word, read through $gp in some places and absolutely in others. */
extern s32 D_L20_001A8F00_gp SDATA(D_L20_001A8F00);
extern s32 D_L20_001A8F08 __attribute__((sda));
extern f32 D_L20_001B2030 __attribute__((sda));
extern f32 D_L20_001B2038 __attribute__((sda));
extern f32 D_L20_001B2040[] SDATA(D_L20_001B2040);
extern f32 D_L20_001B2054 __attribute__((sda));
extern f32 D_L20_001B2060[] SDATA(D_L20_001B2060);
extern s32 D_L20_001B2070 __attribute__((sda));
extern s32 D_L20_001B2074 __attribute__((sda));
extern f32 D_L20_001B209C __attribute__((sda));
extern f32 D_L20_001B20A0 __attribute__((sda));
extern f32 D_L20_001B20B0[] SDATA(D_L20_001B20B0);
extern s32 D_L20_001B20C4 __attribute__((sda));
extern s32 D_L20_001B20C8 __attribute__((sda));
extern f32 D_L20_001B2100[] SDATA(D_L20_001B2100);
extern u8 D_00188660[];
extern s32 D_L20_001B29C0[] MACRO_ADDR;
extern s32 D_L20_001B29E0[] MACRO_ADDR;
extern s32 D_L20_001B2AC8[] __attribute__((sda));
extern s32 D_L20_001B2AD4[] MACRO_ADDR;
extern f32 D_L20_001B2BE8[] MACRO_ADDR;
extern char * D_L20_001B2FA8[] __attribute__((sda));
extern char * D_L20_001B308C[] __attribute__((sda));
typedef union { u8 b[0x200]; s32 i[0x80]; f32 f[0x80]; } Blk200;
extern u8 D_L20_001B9E80[];
extern s16 D_L20_001C0184[];
extern u8 D_L20_001C01C0[];
extern s32 D_L20_001CA540[];
extern s32 D_L20_0021FC18[];
extern s8 D_L20_001A8F20[] __attribute__((sda));
/* Lane 3 of the D_L20_001B2100 vector, read absolutely. */
extern f32 D_L20_001B210C[] MACRO_ADDR;
extern char * D_0018C0B0[];
extern s32 D_0018C0B4[];
#define AT(T, p, o) (*(T *)((char *)(p) + (o)))

/* Runs the main Yeedil enemy each frame (moby class 4576). It walks, throws things and shoots at the hero, calls in helpers, and plays the scripted end of the fight. */
void func_L20_00440598(char *self) {
    float vecs[16] __attribute__((aligned(16)));
    char *st;
    int levelMode = D_L20_001CA540[0];
    int soundIndex, animDone, gameMode, animDoneB, soundIndexEnd;
    int modeNow;
    char *heroMoby, *target, *heroPos, *sideOffset, *heroPosNear, *iter, *sideOffsetCopy, *soundSlot, *soundSlotCheck, *soundSlotEnd;

    if (levelMode == 2) {
        st = AT(char *, self, 0x68);
        InitBossAndHandleDamage(self);
        if (AT(u8, self, 0x95) == 6) {
            if (AT(u8, self, 0x20) == 0x18 || AT(u8, self, 0x20) == 0x19) {
                if (IsPointInCuboid(gHeroState + 0x80, AT(s32, st, 0x230)) != 0) {
                    qcopy(vecs, D_L20_001B2100);
                    qzero_nc(&vecs[4]);
                    vecs[6] = D_L20_001B210C[0];
                    CaptureCheckpointState(vecs, &vecs[4]);
                    D_L20_001B20A0 = D_L20_001B20A0 + 1.0f;
                    SetMobyState(self, 1, 0);
                    modeNow = D_L20_001A8F00[0];
                } else {
                    modeNow = D_L20_001A8F00_gp;
                }
                /* ctr is 2 here; retail compares against its saved copy. */
                if (modeNow == levelMode) {
                    AT(s32, self, 0x98) = 0;
                    AT(u16, self, 0x34) = (AT(u16, self, 0x34) | 0x41) & 0xEFFF;
                } else {
                    AT(u16, self, 0x34) = (AT(u16, self, 0x34) & 0xFFBE) | 0x1000;
                    AT(s32, self, 0x98) = AT(s32, AT(char *, self, 0x24), 0x10);
                }
            }
            if (D_L20_001CA540[0] == 2) {
                D_L20_001B2BE8[0] = AT(f32, self, 0x18) - 2.0f;
            }
        }
        switch (AT(u8, self, 0x20)) {
        case 1:
            if (SetFirstPendingFlag(self) != 0 && AT(u8, self, 0x43) != 0x13) {
                StartAnimationBlended(self, 0x13, 0, 0x14);
            }
            heroMoby = gHeroMoby_0018C0B0[0];
            StartMobyEffectFromEntry(self, FastMatrixHelperA(AT(f32, heroMoby, 0x10) - AT(f32, self, 0x10), AT(f32, heroMoby, 0x14) - AT(f32, self, 0x14)));
            if (AT(u8, self, 0x60) & 2) {
                ChooseNextEnemyState(self);
            }
            break;
        case 2:
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 6) {
                    StartAnimationBlended(self, 6, 0, 0x14);
                }
                SetMobyMotionLimits(self);
                AT(s32, self, 0x9C) = 1;
            }
            soundSlot = (char *)gSoundState + AT(s32, st, 0x1854) * 0x70;
            if (AT(s32, soundSlot, 0x88) != (s32)self || AT(u8, soundSlot, 0x74) == 0) {
                AT(s32, st, 0x1854) = PlayMobySound(1, 4, self);
            }
            if (AT(char *, st, 0x1850) != 0) {
                matrix_mul_vec3(vecs, D_L20_001B20B0, self + 0xC0);
                FastVecAdd(vecs, vecs, self + 0x10);
                SetElectricOrbPositionAndMode(AT(char *, st, 0x1850), (char *)vecs, 1);
            }
            if (UpdateBossGrabMove(self) != 0) {
                SetMobyState(self, 3, -1);
                soundIndex = AT(s32, st, 0x1854);
                if (soundIndex != -1 && (soundSlotCheck = (char *)gSoundState + soundIndex * 0x70, AT(s32, soundSlotCheck, 0x88) == (s32)self)) {
                    if (AT(u8, soundSlotCheck, 0x74) != 0) {
                        StopSoundVoice(soundIndex);
                    }
                }
                AT(s32, st, 0x1854) = -1;
            }
            break;
        case 3:
            if (SetFirstPendingFlag(self) != 0) {
                StartBossJump(self);
                if (AT(u8, self, 0x43) != 6) {
                    StartAnimationBlended(self, 6, 0, 0x14);
                }
                AT(s32, self, 0x9C) = 1;
                if (AT(char *, st, 0x1850) == 0) {
                    if (AT(s32, st, 0x17F8) != 0) {
                        AT(char *, st, 0x1850) = SpawnElectricOrb(self, self + 0x10);
                    }
                }
            }
            if (AT(char *, st, 0x1850) != 0) {
                matrix_mul_vec3(vecs, D_L20_001B20B0, self + 0xC0);
                FastVecAdd(vecs, vecs, self + 0x10);
                SetElectricOrbPositionAndMode(AT(char *, st, 0x1850), (char *)vecs, 0);
            }
            StepAngleTowardTarget((float *)(st + 0x1804), 0, 0.0f, 0.10471977f);
            if (UpdateBouncingMoby(self) != 0) {
                if (D_0018C0B4[0] != 0x8C && (FastFloatHelperD(st + 0x17F8) == 1 || D_L20_001B20C8 != 0)) {
                    if (AT(s32, st, 0x1810) > 0) {
                        AT(s32, st, 0x1810) = -1;
                        SpawnMinionAtArenaPoint(self);
                    }
                    ChooseNextEnemyState(self);
                    AT(s32, self, 0x9C) = 2;
                } else {
                    SetMobyState(self, 2, 1);
                }
            }
            break;
        case 4:
            if (SetFirstPendingFlag(self) != 0) {
                SetMobyMotionLimitsWithRange(self, D_L20_001B2038);
                if (AT(u8, self, 0x43) != 2) {
                    StartAnimationBlended(self, 2, 0, 0x14);
                }
            }
            { char *p = AT(char *, st, 0x17FC);
            UpdateMobyChaseTarget(self, p + 0x10, FastMatrixHelperA(AT(f32, p, 0x10) - AT(f32, self, 0x10), AT(f32, p, 0x14) - AT(f32, self, 0x14))); }
            if (IsValidEnemyTarget(self, AT(char *, st, 0x17FC)) == 0) {
                SetMobyState(self, 1, -1);
            } else {
                if (AT(f32, st, 0x11C) <= D_L20_001B2038 || AT(u16, self, 0x96) >= 0x12DU) {
                    SetMobyState(self, 5, -1);
                }
            }
            break;
        case 5:
            if (SetFirstPendingFlag(self) != 0 && AT(u8, self, 0x43) != 0xB) {
                StartAnimationBlended(self, 0xB, 0, 0xF);
            }
            if (GetMobyAnimationValue(self) < 31.0f) {
                { char *p = AT(char *, st, 0x17FC);
                StartMobyEffectFromEntry(self, FastMatrixHelperA(AT(f32, p, 0x10) - AT(f32, self, 0x10), AT(f32, p, 0x14) - AT(f32, self, 0x14))); }
                if (IsValidEnemyTarget(self, AT(char *, st, 0x17FC)) == 0) {
                    SetMobyState(self, 1, -1);
                }
            } else if (IsValueWithinStepOfThreshold((u8 *)self, 32.0f) != 0) {
                target = AT(char *, st, 0x17FC);
                FastVecScale(vecs, D_L20_001B2040, D_L20_001B2030);
                matrix_mul_vec3(vecs, vecs, self + 0xC0);
                FastVecAdd(vecs, vecs, self + 0x10);
                AT(char *, st, 0x17FC) = SpawnLobbedObject(target, AT(s16, target, 0xAA), (char *)vecs);
                AT(s32, st, 0x183C) = AT(s16, target, 0xAA);
                RunMobyTypeUpdate(target);
                AT(f32, self, 0x48) = D_L20_001B2054;
            } else if (IsValueWithinStepOfThreshold((u8 *)self, 50.0f) != 0) {
                AT(f32, self, 0x48) = 1.0f;
            }
            if (GetMobyAnimationValue(self) >= 60.0f) {
                ChooseNextBossAttack(self);
                SetMobyState(self, 6, 3);
            }
            break;
        case 6:
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 2) {
                    StartAnimationBlended(self, 2, 0, 0x14);
                }
                SetMobyMotionLimitsWithRange(self, AT(f32, st, 0x1838) * 0.5f);
            }
            heroPos = (char *)(&((Hero *)gHeroState)->b[0x80]);
            UpdateMobyChaseTarget(self, heroPos, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) < AT(f32, st, 0x1838) && FastDiffRots(AT(f32, self, 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                SetMobyState(self, AT(s32, st, 0x1834), -1);
            }
            break;
        case 7: {
            int n;
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    StartAnimationBlended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x180C) = 0;
            }
            StartMobyEffectFromEntry(self, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14)));
            AT(s32, st, 0x1808) = D_L20_001B2AC8[0];
            matrix_mul_vec3(vecs, D_L20_001B2060, self + 0xC0);
            FastVecAdd(vecs, vecs, self + 0x10);
            for (n = 1; n >= 0; n -= 1) {
                qcopy(&vecs[4], vecs);
                AddRandomOffsetToVector(&vecs[4], 1.5f);
                vecs[2] -= 0.5f;
                SpawnGrowingPuffParticle((char *)&vecs[4], D_L20_001A8F20, 0x60309030, 0x107090, 0x2D, RandomFloatRange(2.0f, 3.0f) * 210000.0f);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && FastFloatHelperD(st + 0x180C) != 0) {
                AT(s32, st, 0x180C) = D_L20_001B2070;
                ComputeShotLaunch(self, (char *)&vecs[4], (char *)&vecs[8], &vecs[12]);
                vecs[6] += 1.5f;
                SpawnEnemyProjectile(self, (char *)&vecs[4], 0x78, (f32)AT(u8, st, 0x35), RandomIntBelow(2), (int)(st + 0x1808));
            }
            if (D_L20_001B2074 < (s32)AT(u16, self, 0x96)) {
                SetMobyState(self, 1, -1);
            }
            break;
        }
        case 11:
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    StartAnimationBlended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = RandomIntRange(0xA, 0xF);
            }
            ComputeAimTurnAngle(self, (float *)(&((Hero *)gHeroState)->b[0x80]));
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (AT(u16, self, 0x96) % 60U) == 0x1E) {
                LaunchDamagingShot(self);
                FastFloatHelperD(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                SetMobyState(self, 1, -1);
            }
            break;
        case 10:
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    StartAnimationBlended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = RandomIntRange(0x1E, 0x32);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 7) == (((s32)self >> 8) & 7)) {
                FireProjectileAlongAim(self);
                FastFloatHelperD(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                SetMobyState(self, 1, -1);
            }
            break;
        case 8:
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    StartAnimationBlended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = RandomIntRange(0xA, 0x14);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 0x1F) == (((s32)self >> 8) & 0x1F)) {
                FireLobbedProjectile(self);
                FastFloatHelperD(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                SetMobyState(self, 1, -1);
            }
            break;
        case 9:
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    StartAnimationBlended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = RandomIntRange(4, 5);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 0x1F) == (((s32)self >> 8) & 0x1F)) {
                if (LaunchGroupShot(self) != 0) {
                    FastFloatHelperD(st + 0x1840);
                } else {
                    AT(s32, st, 0x1840) = 0;
                }
            }
            if (AT(s32, st, 0x1840) == 0) {
                SetMobyState(self, 1, -1);
            }
            break;
        case 12:
            if (SetFirstPendingFlag(self) != 0 && AT(u8, self, 0x43) != 0x11) {
                StartAnimationBlended(self, 0x11, 0, 0x14);
            }
            if ((D_L20_001B2AC8[0] & 7) == (((s32)self >> 8) & 7)) {
                if (D_L20_001B20C4 != 0) {
                    SetMobyState(self, 0xD, -1);
                } else if (ActivateGroupMemberAlongAim(self) == 0 || CountActiveGroupMembers(AT(s32, st, 0x21C)) >= 0x15) {
                    SetMobyState(self, 0xD, -1);
                }
            }
            break;
        case 13:
            animDone = SetFirstPendingFlag(self);
            sideOffset = st + 0x17D0;
            if (animDone != 0) {
                if (AT(u8, self, 0x43) != 2) {
                    StartAnimationBlended(self, 2, 0, 0x14);
                }
                ComputeSideStepTarget(self, sideOffset);
                SetMobyMotionLimitsWithRange(self, 1.0f);
            }
            UpdateMobyChaseTarget(self, sideOffset, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) < 1.0f && FastDiffRots(AT(f32, self, 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                SetMobyState(self, 0xE, -1);
            } else if (CountActiveGroupMembers(AT(s32, st, 0x21C)) < 3) {
                SetMobyState(self, 1, -1);
            }
            break;
        case 14:
            if (SetFirstPendingFlag(self) != 0 && AT(u8, self, 0x43) != 1) {
                StartAnimationBlended(self, 1, 0, 0x14);
            }
            ComputeAimTurnAngle(self, (float *)(&((Hero *)gHeroState)->b[0x80]));
            if (vec_distance_xy(self + 0x10, gHeroState + 0x80) < D_L20_001B209C) {
                SetMobyState(self, 0xD, -1);
            }
            if (CountActiveGroupMembers(AT(s32, st, 0x21C)) < 3) {
                SetMobyState(self, 1, -1);
            }
            break;
        case 15:
            if (SetFirstPendingFlag(self) != 0 && AT(u8, self, 0x43) != 0x15) {
                StartAnimationBlended(self, 0x15, 0, 0xA);
            }
            { float t = ProbeGroundHeightBelow(self + 0x10, 0, 0.5f); ApproachValue((f32 *)(self + 0x18), t, 0.16666667f); }
            if (AT(u8, self, 0x60) & 2) {
                if (AT(u8, self, 0xBC) != 0) {
                    SetMobyState(self, 1, 0);
                } else {
                    SetMobyState(self, 0x10, -1);
                }
                AT(u8, self, 0xBC) = 0;
            }
            break;
        case 16: {
            f32 dist;
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 7) {
                    StartAnimationBlended(self, 7, 0, 0x14);
                }
                SetMobyMotionLimitsWithRange(self, 1.0f);
                AT(s32, st, 0x1830) = 0;
            }
            if (AT(u8, self, 0x60) & 2) {
                switch (AT(u8, self, 0x42)) {
                case 7:
                    if (AT(u8, self, 0x43) != 8) {
                        StartAnimationBlended(self, 8, 0, 1);
                    }
                    break;
                case 8:
                    if (AT(u8, self, 0x43) != 9) {
                        StartAnimationBlended(self, 9, 0, 1);
                    }
                    break;
                case 9:
                    AT(s32, st, 0x1830) = AT(s32, st, 0x1830) + 1;
                    break;
                }
            }
            if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x8C) {
                ((Hero *)gHeroState)->h[0x1E0 / 2] = 0xF;
            }
            dist = GetMobyAnimationValue(self);
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43)) {
                if ((AT(u8, self, 0x42) == 8 && dist < 9.0f) || (AT(u8, self, 0x42) == 9 && dist > 12.0f && dist < 30.0f)) {
                    heroPosNear = (char *)(&((Hero *)gHeroState)->b[0x80]);
                    UpdateMobyChaseTarget(self, heroPosNear, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14)));
                    if (AT(u8, self, 0x42) == AT(u8, self, 0x43)) {
                        if ((AT(u8, self, 0x42) == 8 && dist < 9.0f && dist > 7.0f) || (AT(u8, self, 0x43) == 9 && dist > 25.0f && dist < 30.0f)) {
                            qcopy(vecs, self + 0x10);
                            vecs[2] += 1.0f;
                            SweepCollisionFromObject(self, vecs, 0x10008, 0, 1, 0, 5.5f, (f32)AT(u8, st, 0x34), 2.0f);
                        }
                    }
                }
            }
            if (AT(u8, self, 0x42) == 8 && IsValueWithinStepOfThreshold((u8 *)self, 6.0f) != 0) {
                ((Blk200 *)D_L20_001B9E80)->i[0x16C / 4] = 0;
                ((Blk200 *)D_L20_001B9E80)->i[0x188 / 4] = 0x2D;
                ((Blk200 *)D_L20_001B9E80)->f[0x180 / 4] = 0.05f;
            }
            if (AT(u8, self, 0x42) == 9 && IsValueWithinStepOfThreshold((u8 *)self, 30.0f) != 0) {
                if (AT(s32, st, 0x1830) >= 2 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x8C) {
                    ExplodeBossOnDeath(self);
                    SetMobyState(self, 3, -1);
                }
                ((Blk200 *)D_L20_001B9E80)->f[0x180 / 4] = (f32)(AT(s32, st, 0x1830) + 1) * 0.05f;
                ((Blk200 *)D_L20_001B9E80)->i[0x16C / 4] = 0;
                ((Blk200 *)D_L20_001B9E80)->i[0x188 / 4] = 0x2D;
            }
            break;
        }
        case 17:
            if (SetFirstPendingFlag(self) != 0) {
                if (AT(u8, self, 0x43) != 0x15) {
                    StartAnimationBlended(self, 0x15, 0, 0xA);
                }
                iter = D_L20_001B2FA8[0];
                gameMode = D_L20_001A8F00_gp;
                if (iter != 0) {
                    /* Retail keeps these four in saved registers; with literals cc1 folds the two state
                       tests into one range check. */
                    int class_removed = 0xCBC /* Megacorp Hover Tank */, state_dead = 0xFE, state_dying = 0xFD;
                    int class_reset = 0xD0F /* Megacorp Trooper Legs */;
                    int id;
                    do {
                        id = AT(s16, iter, 0xAA);
                        if (id == class_removed && iter != 0) {
                            u8 k = AT(u8, iter, 0x20);
                            if (k != state_dead && k != state_dying) {
                                MarkMobySpawned(iter);
                            }
                            id = AT(s16, iter, 0xAA);
                        }
                        if (id == class_reset && iter != 0) {
                            u8 k = AT(u8, iter, 0x20);
                            if (k != state_dead && k != state_dying && AT(u8, iter, 0x21) == AT(s32, st, 0x21C)) {
                                SetDeathBits(iter, 0, 3);
                                DestroyTrooperParts(iter);
                            }
                        }
                        iter = AT(char *, iter, 0x28);
                    } while (iter != 0);
                    gameMode = D_L20_001A8F00[0];
                }
            } else {
                gameMode = D_L20_001A8F00[0];
            }
            if (gameMode == 2) {
                AT(s32, self, 0x98) = 0;
                AT(u16, self, 0x34) = (AT(u16, self, 0x34) | 0x41) & 0xEFFF;
            }
            if (AT(u8, self, 0x60) & 2) {
                AT(s32, self, 0x48) = 0;
            }
            break;
        case 18:
            if (SetFirstPendingFlag(self) != 0) {
                D_L20_001B29C0[0] = 0;
                BeginSlotRequest(9, 1, 0, 0, 0);
            }
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0 && PushRequestQueue(D_L20_001C01C0, 0x1E) != 0) {
                LaunchQueuedRequest(D_L20_001C01C0);
                SetMobyState(self, 0x13, -1);
            }
            break;
        case 19:
            if (D_L20_001A8F00[0] == 0) {
                if (D_L20_001A8F08 <= 0) {
                    D_L20_001B2AD4[0] = 1;
                    BeginSlotRequest(9, 1, 0, 0, 0);
                    SetMobyState(self, 0x14, -1);
                }
                if (D_L20_001A8F00[0] == 0) {
                    AddDrawCallbackToList3(StartScreenEffect, self);
                }
            }
            break;
        case 20:
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0 && PushRequestQueue(D_L20_001C01C0, 0x1F) != 0) {
                LaunchQueuedRequest(D_L20_001C01C0);
                SetMobyState(self, 0x15, -1);
            }
            break;
        case 21:
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0) {
                int a, b;
                SetMobyState(self, 0x16, -1);
                a = GetLocalizedString(0x325E);
                b = GetLocalizedString(0x3210);
                StoreFourSettings(a, b, GetLocalizedString(0xA1F), 1);
                SetMenuSizeLimits(0x40, 0x20);
                BeginSlotRequest(4, 1, 9, 0, 0);
            }
            break;
        case 22:
            D_L20_001B29E0[0] = 0;
            if (D_L20_001C0184[0] == 1) {
                StartYeedilScene();
                SetMobyState(self, 0x17, -1);
            } else {
                char *t;
                ClearFirstLevelTableEntry();
                t = D_L20_001B308C[0] + (AT(s32, st, 0x248) << 7);
                CaptureCheckpointState(t + 0x30, t + 0x70);
                D_L20_0021FC18[0] = 0;
                RecordHeroPlayCounters();
            }
            break;
        case 24:
            animDoneB = SetFirstPendingFlag(self);
            sideOffsetCopy = st + 0x17D0;
            if (animDoneB != 0) {
                f32 mag = RandomFloatRange(5.0f, 15.0f);
                f32 ang = RandomAngle();
                char *target;
                f32 y;
                AT(f32, st, 0x17D0) = FastSinOrCosA(ang) * mag;
                y = FastSinOrCosB(ang) * mag;
                target = D_L20_001B308C[0] + (AT(s32, st, 0x230) << 7);
                AT(s32, st, 0x17D8) = 0;
                AT(f32, st, 0x17D4) = y;
                FastVecAdd(sideOffsetCopy, sideOffsetCopy, target + 0x30);
                if (AT(u8, self, 0x43) != 2) {
                    StartAnimationBlended(self, 2, 0, 0x14);
                }
                SetMobyMotionLimitsWithRange(self, 1.5f);
            }
            UpdateMobyChaseTarget(self, sideOffsetCopy, FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) <= 1.5f && FastDiffRots(AT(f32, self, 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)gHeroState)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                SetMobyState(self, 0x19, -1);
            }
            break;
        case 25: {
            int anim;
            if (SetFirstPendingFlag(self) != 0) {
                anim = (RandomIntBelow(3) != 0) ? 0x13 : 0x14;
                if (AT(u8, self, 0x43) != anim) {
                    StartAnimationBlended(self, anim, 0, 0x14);
                }
            }
            if (AT(u8, self, 0x60) & 2) {
                SetMobyState(self, 0x18, -1);
            }
            break;
        }
        }
        RunBossFrameUpkeep(self);
        if (AT(u8, self, 0x20) != 2) {
            soundIndexEnd = AT(s32, st, 0x1854);
            if (soundIndexEnd != -1) {
                soundSlotEnd = (char *)gSoundState + soundIndexEnd * 0x70;
                if (AT(s32, soundSlotEnd, 0x88) == (s32)self && AT(u8, soundSlotEnd, 0x74) != 0) {
                    StopSoundVoice(soundIndexEnd);
                }
            }
            AT(s32, st, 0x1854) = -1;
        }
    }
}
