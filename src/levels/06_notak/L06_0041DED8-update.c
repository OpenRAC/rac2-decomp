#include "common.h"

extern int func_002E5CF8(int, int, char *);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern int func_00283CF0(float);
extern float func_00283248(float, float);
extern float func_002A7940(void);
extern void func_L06_0041EF08(char *);
extern void func_L06_0041FAF8(char *);
extern int func_002A7820(int, int);
extern int func_002B1C20(char *, char *);
extern void func_002A6C58(char *, int, int);
extern void func_L06_004294A0(char *, int, int);
extern float func_00283C80(float, float);
extern int *D_L06_001FE500[];

extern int func_00282978(char *);
extern void func_L06_00458138(char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern int func_L06_0041FC58(char *, char *);
extern int func_L06_0041F2A0(char *, char *, float, float, float, float);
extern float func_0029F530(char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A89A8(char *, int, float);
extern int func_00277258(char *, int, char *, float);
extern char *D_L06_001BFC98;
extern float func_00282E80(char *, char *);
extern float func_002A78D8(float, float);
extern int func_002AEB60(char *, float);
extern void func_0029FCC0(char *, int, void *);
extern void *D_L06_001B3760[6];
extern void func_L06_0041F818(float *, int);
extern void func_L06_00458E10(char *, float *, float *, int, float);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00282E48(void *, void *);
extern void func_002A8C28(char *, void *, int, int, int, int, float, float, float);
extern void func_L06_0041F558(char *);

/* Updates the actor's alert mode, movement and attack animation states. */
void func_L06_0041DED8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int *pathData;
    int hitFlags;
    float pos[4], target[4], direction[4];
    float frame, savedW, groundHeight;
    int i;

    InitActorAndCheckHits(moby);
    pathData = gPathList[*(int *)(vars + 0x23C)];
    switch (*(unsigned char *)(moby + 0x95)) {
    case 0:
        if (*(int *)(vars + 0x228) == 1) {
            if (*(int *)(vars + 0x5C8)) {
                *(int *)(vars + 0x5C8) = 0;
                PlayMobySound(11, 0, moby);
            }
            ChooseActorIdleAnimation(moby);
            if (*(int *)(vars + 0x5C0)) {
                *(int *)(vars + 0x238) = *(int *)(vars + 0x234);
                *(int *)(vars + 0x220) = *(int *)(vars + 0x224);
            }
        } else if (*(int *)(vars + 0x258)) {
            ChooseActorIdleAnimation(moby);
        }
        break;
    case 1:
        if (*(int *)(vars + 0x228) == 1 || *(int *)(vars + 0x22C) == 1)
            ChooseActorIdleAnimation(moby);
        else if (*(short *)(vars + 0x24A) == 0)
            moby[0x95] = 0;
        *(int *)(vars + 0x258) = 0;
        break;
    case 2:
        if (*(int *)(vars + 0x228) != 1 && *(int *)(vars + 0x22C) != 1 && (moby[0x60] & 2)) {
            if (*(int *)(vars + 0x23C) != -1)
                *(int *)(vars + 0x478) = pathData[0] - 1;
            *(float *)(vars + 0x494) = 2.0f;
            SetMobyState(moby, 14, 4);
            *(short *)(vars + 0x24A) = RandomIntRange(580, 600);
        }
        break;
    case 3:
        hitFlags = DispatchActionByKind(moby, vars + 0x60);
        if (hitFlags & 1) {
            SetDeathBits(moby, 0, 3);
            func_L06_004294A0(moby, 0, 0);
            return;
        }
        if (hitFlags & 2) {
            if (*(int *)(vars + 0x228) == 1 || *(int *)(vars + 0x22C) == 1) {
                if (FastDiffRots(*(float *)(moby + 0xF8),
                        FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                    *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                    SetMobyState(moby, 11, 2);
                    if (*(unsigned char *)(moby + 0x43) != 9)
                        StartAnimationBlended(moby, 9, 0, 2);
                    vars[0x48] = FloatToInt(20.0f);
                    vars[0x4A] = FloatToInt(8.0f);
                } else {
                    SetMobyState(moby, 9, 2);
                    if (*(unsigned char *)(moby + 0x43) != 18)
                        StartAnimationBlended(moby, 18, 0, 10);
                    vars[0x48] = FloatToInt(20.0f);
                    vars[0x4A] = FloatToInt(24.0f);
                }
            } else {
                *(short *)(vars + 0x24A) = RandomIntRange(580, 600);
                SetMobyState(moby, 5, 1);
                if (*(unsigned char *)(moby + 0x43) != 18)
                    StartAnimationBlended(moby, 18, 0, 20);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(24.0f);
            }
        }
        break;
    case 4:
        if (*(float *)(vars + 0x494) <= 0.0f) {
            *(float *)(vars + 0x5A4) = RandomAngle();
            qcopy(vars + 0x5B0, vars + 0x460);
            *(short *)(vars + 0x24C) = 270;
            SetMobyState(moby, 4, -1);
            if (*(unsigned char *)(moby + 0x43) != 6)
                StartAnimationBlended(moby, 6, 0, 10);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
            SetMobyState(moby, 5, 1);
        }
        break;
    }
    switch (*(unsigned char *)(moby + 0x20)) {
    case 1:
        if (FastDecTimer(vars + 0x24C) && *(short *)(vars + 0x492) == 0) {
            if (*(unsigned char *)(moby + 0x43) != 2)
                StartAnimationBlended(moby, 2, 0, 20);
            *(short *)(vars + 0x24C) = RandomIntRange(900, 1200);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        } else if ((moby[0x60] & 2) && *(short *)(vars + 0x492) == 0) {
            if (*(unsigned char *)(moby + 0x43) != 1)
                StartAnimationBlended(moby, 1, 0, 5);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(8.0f);
        }
        break;
    case 2:
    case 3:
        break;
    case 5:
        if (moby[0x60] & 2) {
            *(float *)(vars + 0x5A4) = RandomAngle();
            FindActorPathAreaPoint(moby, vars);
            *(short *)(vars + 0x24C) = 270;
            SetMobyState(moby, 4, -1);
            if (*(unsigned char *)(moby + 0x43) != 6)
                StartAnimationBlended(moby, 6, 0, 10);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 4:
        if (SteerActorTowardGoal(moby, vars + 0x5B0, *(float *)(vars + 0x5A4), 4.0f,
                              0.25f, *(float *)(vars + 0x47C)) ||
            FastDecTimer(vars + 0x24C)) {
            SetMobyState(moby, 5, -1);
            if (*(unsigned char *)(moby + 0x43) != 7)
                StartAnimationBlended(moby, 7, 0, 10);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(8.0f);
        }
        break;
    case 7:
        if (moby[0x60] & 2) {
            moby[0x20] = 9;
            if (*(unsigned char *)(moby + 0x43) != 18)
                StartAnimationBlended(moby, 18, 0, 20);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
            *(int *)(vars + 0x5A0) = 0;
        } else if (*(int *)(vars + 0x5C4)) {
            frame = GetMobyAnimationValue(moby);
            if ((unsigned char)moby[0x42] == (unsigned char)moby[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                savedW = *(float *)(moby + 0x1C);
                pos[0] = FastSinOrCosA(*(float *)(moby + 0xF8)) * 0.16f;
                pos[1] = FastSinOrCosB(*(float *)(moby + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                FastVecAdd(moby + 0x10, (char *)pos, moby + 0x10);
                groundHeight = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
                *(float *)(moby + 0x18) -= 0.1666666716337204f;
                if (*(float *)(moby + 0x18) < groundHeight)
                    *(float *)(moby + 0x18) = groundHeight;
                *(float *)(moby + 0x1C) = savedW;
            }
            qcopy(pos, moby + 0x10);
            pos[2] += 0.6f;
            target[0] = FastSinOrCosA(*(float *)(moby + 0xF8));
            target[1] = FastSinOrCosB(*(float *)(moby + 0xF8));
            target[2] = 0.0f;
            FastVecAdd((char *)pos, (char *)target, (char *)pos);
        } else {
            frame = GetMobyAnimationValue(moby);
            if ((unsigned char)moby[0x42] == (unsigned char)moby[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                savedW = *(float *)(moby + 0x1C);
                pos[0] = FastSinOrCosA(*(float *)(moby + 0xF8)) * 0.16f;
                pos[1] = FastSinOrCosB(*(float *)(moby + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                FastVecAdd(moby + 0x10, (char *)pos, moby + 0x10);
                *(float *)(moby + 0x1C) = savedW;
            }
            qcopy(pos, moby + 0x10);
            pos[2] += 0.6f;
            target[0] = FastSinOrCosA(*(float *)(moby + 0xF8));
            target[1] = FastSinOrCosB(*(float *)(moby + 0xF8));
            target[2] = 0.0f;
            FastVecAdd((char *)pos, (char *)target, (char *)pos);
            if (TestPointAgainstCollision((char *)pos, 0, moby, 0.5f)) {
                char *hitMoby = D_L06_001BFC98;
                if (hitMoby && *(short *)(hitMoby + 0xAA) == 0xFDC /* moby class 4060 */)
                    EmitSparkBurstAndRemove(hitMoby);
            }
        }
        break;
    case 6:
        if (moby[0x60] & 2) {
            SetMobyState(moby, 9, 2);
            if (*(unsigned char *)(moby + 0x43) != 18)
                StartAnimationBlended(moby, 18, 0, 20);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 8:
        if (*(int *)(vars + 0x23C) != -1) {
            char *waypoint = (char *)(pathData + 4) + *(int *)(vars + 0x478) * 16;
            SteerActorTowardGoal(moby, waypoint,
                FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                            *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
                8.0f, 0.25f, 0.0f);
            if (vec_distance_xy(moby + 0x10, (char *)(pathData + 4) + *(int *)(vars + 0x478) * 16) < 1.5f)
                ++*(int *)(vars + 0x478);
            {
                int count = pathData[0];
                if (*(int *)(vars + 0x478) >= count) {
                    *(int *)(vars + 0x5A0) = 0;
                    *(int *)(vars + 0x478) = count - 1;
                    if (FastDiffRots(*(float *)(moby + 0xF8),
                        FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                    *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                        qcopy(vars + 0x460, moby + 0x10);
                        SetMobyState(moby, 10, -1);
                        if (*(unsigned char *)(moby + 0x43) != 21)
                            StartAnimationBlended(moby, 21, 0, 16);
                        vars[0x48] = FloatToInt(20.0f);
                        vars[0x4A] = FloatToInt(8.0f);
                    }
                }
            }
        } else {
            SetMobyState(moby, 9, -1);
        }
        break;
    case 9:
        if (*(unsigned short *)(moby + 0x96) < 2)
            *(float *)(vars + 0x47C) = RandomSignedFloatRange(10.0f, 25.0f) * 0.01745329424738884f;
        if (SteerActorTowardGoal(moby, vars + 0x200,
            FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                        *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
            8.0f, 16.0f, *(float *)(vars + 0x47C))) {
            if (FastDiffRots(*(float *)(moby + 0xF8),
                FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                            *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                SetMobyState(moby, 10, -1);
                if (*(unsigned char *)(moby + 0x43) != 21)
                    StartAnimationBlended(moby, 21, 0, 16);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(8.0f);
            }
        }
        break;
    case 10:
        SteerActorTowardGoal(moby, moby + 0x10,
            FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                        *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
            6.0f, 6.0f, 0.0f);
        if (moby[0x60] & 2) {
            if (vec_distance_xy(moby + 0x10, vars + 0x200) < 3.0f) {
                SetMobyState(moby, 12, -1);
                if (*(unsigned char *)(moby + 0x43) != 13)
                    StartAnimationBlended(moby, 13, 10, 20);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(24.0f);
            } else {
                SetMobyState(moby, 11, -1);
                if (*(unsigned char *)(moby + 0x43) != 9)
                    StartAnimationBlended(moby, 9, 0, 2);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(8.0f);
            }
        }
        break;
    case 11:
        if (moby[0x60] & 2) {
            SetMobyState(moby, 13, -1);
            if (*(unsigned char *)(moby + 0x43) != 10)
                StartAnimationBlended(moby, 10, 0, RandomIntRange(10, 30));
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(8.0f);
        } else if (IsValueWithinStepOfThreshold(moby, 2.0f)) {
            TransformMobyJointToWorld(moby, 0, pos);
            qcopy(target, vars + 0x200);
            FastVecSub((char *)direction, (char *)target, (char *)pos);
            vec_scale_to_length((char *)direction, (char *)direction, 0.1666666716337204f);
            *(int *)(vars + 0x498) = -1;
            for (i = 0; i < 6; i++) {
                if (!D_L06_001B3760[i]) {
                    *(int *)(vars + 0x498) = i;
                    break;
                }
            }
            if (*(int *)(vars + 0x498) != -1) {
                SpawnParticleBurst_L06(pos, 10);
                SpawnChildMobyInSlot(moby, direction, pos, *(int *)(vars + 0x498),
                                  (float)*(unsigned char *)(vars + 0x35));
                *(int *)(vars + 0x498) = -1;
            }
            vars[0xD7] = 0;
        }
        break;
    case 12:
        frame = GetMobyAnimationValue(moby);
        if ((unsigned char)moby[0x42] == (unsigned char)moby[0x43] && frame >= 17.0f && frame <= 25.0f) {
            vars[0xD7] = 0;
            TransformMobyJointToWorld(moby, 0, pos);
            qcopy(target, moby + 0x10);
            target[2] += 2.0f;
            lerp_vector(direction, pos, target, 0.5f);
            direction[3] = fast_vec_dist(direction, target) * 0.75f;
            SweepCollisionFromObject(moby, direction, 1, 0, 1, 0, direction[3], *(float *)(vars + 0x5AC), 1.0f);
        } else if (moby[0x60] & 2) {
            SetMobyState(moby, 13, -1);
            if (*(unsigned char *)(moby + 0x43) != 11)
                StartAnimationBlended(moby, 11, 0, RandomIntRange(10, 30));
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 13:
        if (moby[0x60] & 2) {
            if ((unsigned char)moby[0x95] == 4) {
                *(float *)(vars + 0x494) -= 1.0f;
                SetMobyState(moby, 14, -1);
            } else {
                SetMobyState(moby, 9, -1);
                if (*(unsigned char *)(moby + 0x43) != 18)
                    StartAnimationBlended(moby, 18, 0, 10);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(24.0f);
            }
            if (vec_distance_xy(moby + 0x10, vars + 0x200) < 16.0f) {
                if (FastDiffRots(*(float *)(moby + 0xF8),
                    FastMatrixHelperA(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                    SetMobyState(moby, 10, -1);
                    if (*(unsigned char *)(moby + 0x43) != 21)
                        StartAnimationBlended(moby, 21, 0, 16);
                    vars[0x48] = FloatToInt(20.0f);
                    vars[0x4A] = FloatToInt(8.0f);
                }
            }
        }
        break;
    case 14:
        SetMobyState(moby, 10, -1);
        if (*(unsigned char *)(moby + 0x43) != 21)
            StartAnimationBlended(moby, 21, 0, 16);
        vars[0x48] = FloatToInt(20.0f);
        vars[0x4A] = FloatToInt(8.0f);
        break;
    }
    AimActorBodyAtTarget(moby);
}
