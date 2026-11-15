#include "common.h"
extern int D_001A8FF4;
extern char D_00189EA0[];
extern char *D_0018C2BC __attribute__((section(".data")));
typedef int TIAfc8 __attribute__((mode(TI)));
extern void func_L11_0044BD68(char *);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern int func_002A77E0(int);
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(char *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_002B3890(char *);
extern int func_002B3868(char *);
extern void func_002B60B0(char *, float, float, float, float);
extern char *func_L11_004417E8(int);
extern int func_L11_00441808(int, void *);
extern void func_L11_0044C688(char *, void *);
extern void func_L11_0044C818(char *);
extern void func_L01_00321178(char *, void *);
extern void func_L02_00333438(char *, void *);
extern int func_002B5278(char *, float);
extern int func_002B50E0(char *, void *, float);
extern int func_L11_0044C850(char *);
extern int func_002B4FF0(char *, void *, float);
extern void func_L02_00333480(char *, void *, void *);
extern float func_0029F530(char *);
extern int func_002A8D70(char *, int, float, float, int, float, int, int, int);
extern void func_L00_002E6CF0(void (*)(char *), char *);
extern void func_L11_0044C220(char *);
extern void func_L11_0044C180(char *);
extern void func_L11_00340500(char *, void *);
extern int func_002B1C20(char *, void *);
extern void func_L02_003FC248(char *, int, int);
extern void func_L11_0044C4F0(char *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern void func_L07_00321D68(char *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A3F10(char *, int, void *, void *);
extern void func_002B4090(char *, void *, float, float, float);
extern void func_002833F0(void *, void *);
extern void func_L11_0044C0F0(char *);

/* Per-frame update of the Joba smasher robot (moby class 3535): it patrols, chases the hero, smashes with its arms and flies off when destroyed. */
void func_L11_0044AFC8(char *object)
{
    float target[4], direction[4], matrix[16];
    int collision_flags;
    char *state = *(char **)(object + 0x68);
    char *position, *waypoint;
    float angle, difference, distance, frame, scale;
    int result, i;
    float *rotation;
    if (*(u8 *)(object + 0x20) == 1) return;
    if (*(short *)(state + 0x4D2) && !D_001A8FF4 &&
        *(u8 *)(object + 0x20) != 11 && *(u8 *)(object + 0x20) != 10) return;
    UpdateSmasherRobotAimAndInit(object);
    if (*(u8 *)(object + 0x20) == 1) return;
    if (*(short *)(state + 0x4D2) && !D_001A8FF4) return;
    if (*(short *)(state + 0x4CA) == 0) {
        *(int *)(state + 0x490) = 0;
        if (*(u8 *)(object + 0x95) == 4) {
            SetMobyState(object, 4, 2);
            if (RandomIntBelow(2)) {
                if (*(u8 *)(object + 0x43) != 2) StartAnimationBlended(object, 2, 0, 10);
            } else if (*(u8 *)(object + 0x43) != 3) StartAnimationBlended(object, 3, 0, 10);
        }
    }
    if (*(char **)(state + 0x490)) *(TIAfc8 *)target = *(TIAfc8 *)(*(char **)(state + 0x490) + 0x10);
    else *(TIAfc8 *)target = *(TIAfc8 *)gHeroPosition;
    if (*(short *)(state + 0x4D2)) {
        FastVecSub(direction, target, object + 0x10);
        position = object + 0x10;
        difference = GetHeadingAngleOfVector(object, direction, state + 0x230);
        angle = 0.0f;
    } else {
        position = object + 0x10;
        angle = FastMatrixHelperA(target[0] - *(float *)(object + 0x10), target[1] - *(float *)(object + 0x14));
        difference = FastDiffRots(angle, *(float *)(object + 0xF8));
    }
    distance = fast_vec_dist(position, target);
    if (*(u8 *)(object + 0x95) == 2) {
        if (SetSecondPendingFlag(object)) {
            if (*(u8 *)(object + 0x43) != 10) StartAnimationBlended(object, 10, 0, 10);
            *(u8 *)(object + 0xBC) = 0;
            SetControllerSpeedLimits(object, 0.002222222276031971f, 0.06666667014360428f, 0.0011635529808700085f, 0.10471977293491364f);
            PickSmasherRobotWanderPoint(object, GetArenaCenterPoint(*(int *)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (*(u8 *)(object + 0xBC) == 1 && *(u16 *)(object + 0x96) > 300) {
            switch (RandomIntBelow(5)) {
            case 0: if (*(u8 *)(object + 0x43) != 2) StartAnimationBlended(object,2,0,10); break;
            case 1: if (*(u8 *)(object + 0x43) != 3) StartAnimationBlended(object,3,0,10); break;
            case 2: if (*(u8 *)(object + 0x43) != 4) StartAnimationBlended(object,4,0,10); break;
            case 3: if (*(u8 *)(object + 0x43) != 6) StartAnimationBlended(object,6,0,10); break;
            case 4: if (*(u8 *)(object + 0x43) != 7) StartAnimationBlended(object,7,0,10); break;
            }
            *(u16 *)(object + 0x96) = RandomIntBelow(100);
        }
        if (*(short *)(state + 0x4CA)) {
            SetMobyState(object,5,4);
            if (RandomIntBelow(2)) {
                if (*(u8 *)(object + 0x43) != 1) StartAnimationBlended(object,1,0,10);
            } else if (*(u8 *)(object + 0x43) != 5) StartAnimationBlended(object,5,0,10);
        }
        if (difference > 2.792527198791504f) StartSmasherRobotTurnAround(object);
        waypoint = state + 0x470;
        if (*(u8 *)(object + 0xBC) == 0 && vec_distance_xy(position, waypoint) < 0.5f) *(u8 *)(object + 0xBC) = 1;
        else if (*(short *)(state + 0x4D2)) AimAtTargetOffset(object,waypoint);
        else TurnMobyTowardTarget(object,waypoint);
    }
    switch (*(u8 *)(object + 0x20)) {
    case 3:
        if (SetFirstPendingFlag(object)) {
            *(u8 *)(object + 0xBC) = 0;
            if (*(u8 *)(object + 0x43) != 2) StartAnimationBlended(object,2,0,0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (*(u8 *)(object + 0xBC) == 0 && *(short *)(state + 0x4D0) < *(u16 *)(object + 0x96)) {
            if (*(u8 *)(object + 0x43) != 10) StartAnimationBlended(object,10,0,10);
            *(u8 *)(object + 0xBC) = 1;
        } else if (*(u8 *)(object + 0xBC) == 1) {
            if (IsPointInArenaPolygon(*(int *)(object+0xB8),position)) SetMobyState(object,4,2);
            TurnMobyTowardTarget(object,GetArenaCenterPoint(*(int *)(object+0xB8)));
        }
        break;
    case 5:
        if (*(u8 *)(object + 0x60) & 2) SetMobyState(object,7,-1);
        break;
    case 6:
        if (SetFirstPendingFlag(object)) {
            if (*(u8 *)(object + 0x43) != 9) StartAnimationBlended(object,9,0,10);
            SetControllerSpeedLimits(object,0.004444444552063942f,0.13333334028720856f,0.006981317885220051f,0.8377581834793091f);
        }
        StepMovementAtOwnPositionWithFactor(object,angle);
        if (*(u8 *)(object+0x60)&2) SetMobyState(object,*(short *)(state+0x4CC),*(short *)(state+0x4CE));
        break;
    case 7:
        if (SetFirstPendingFlag(object)) {
            if (*(u8 *)(object+0x43)!=10) StartAnimationBlended(object,10,0,15);
        }
        if (*(u8 *)(object+0x42)==8 && distance>15.0f) {
            if (*(u8 *)(object+0x43)!=10) StartAnimationBlended(object,10,0,4);
            SetControllerSpeedLimits(object,0.004444444552063942f,0.13333334028720856f,0.0011635529808700085f,0.10471977293491364f);
        } else if (*(u8 *)(object+0x42)==10 && distance<7.0f) {
            if (*(u8 *)(object+0x43)!=8) StartAnimationBlended(object,8,0,4);
            SetControllerSpeedLimits(object,0.004444444552063942f,0.03333333507180214f,0.0011635529808700085f,0.10471977293491364f);
        }
        if (distance<2.8f && difference<0.3839724659919739f) {
            SetMobyState(object,8,-1);
            if (*(u8 *)(object+0x43)!=11) StartAnimationBlended(object,11,4,3);
            *(int *)(state+0x4B0)=0;
        } else if (distance>2.8f) {
            if (*(short *)(state+0x4D2)) AimAtTargetOffset(object,target);
            else if (!AimAtGroupEntityInConeB(object)) TurnTowardTargetAndStepMovement(object,target,*(float *)(state+0x494));
        } else {
            if (*(short *)(state+0x4D2)) {
                FastVecSub(direction,target,position);
                UpdateObjectController(object,position,direction);
            } else StepMovementController(object,position,angle);
        }
        if (difference>2.792527198791504f) StartSmasherRobotTurnAround(object);
        break;
    case 8:
        if (*(u8 *)(object+0x60)&2) {
            *(float *)(state+0x4AC)=8.0f;
            if (gActiveAttackerRobot==object) {
                SetMobyState(object,9,-1);
                if (*(u8 *)(object+0x43)!=12) StartAnimationBlended(object,12,0,7);
            } else SetMobyState(object,7,-1);
        }
        frame=GetMobyAnimationValue(object);
        if (*(u8 *)(object+0x42)==11) {
            if (19.0f<=frame && frame<=25.0f) {
                TestHitAtBone(object,0,0.35f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
                TestHitAtBone(object,1,0.15f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
                TestHitAtBone(object,2,0.15f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
            }
        }
        if (*(u8 *)(object+0x42)==11 && 17.0f<=frame && frame<=25.0f) {
            AddDrawCallbackToList1(SubmitSceneEffectParams,object);
            AdvanceSmasherArmHistory(object);
            *(float *)(state+0x4AC)=25.0f;
        }
        if (*(short *)(state+0x4D2)) CheckMoveToPoint(object,target);
        else StepMovementController(object,position,angle);
        break;
    case 9:
        if (*(u8 *)(object+0x60)&2) SetMobyState(object,7,-1);
        break;
    case 10:
        result=DispatchActionByKind(object,state+0x50);
        if (*(u8 *)(object+0x42)==15) {
            if (!RandomIntBelow(30) || (result&1)) {
                if (GetMobyAnimationValue(object)<15.0f && *(short *)(state+0x4D2) && !RandomIntBelow(2)) SetMobyState(object,11,-1);
                else {SetMobyAnimTypeThree(object,0,-1); DeactivateSmasherRobot(object);}
            }
        } else if (result&2) SetMobyState(object,7,4);
        break;
    case 11:
        if (SetFirstPendingFlag(object)) {
            FastVecSub(state+0x1A0,GetArenaCenterPoint(*(int *)(object+0xB8)),position);
            *(int *)(state+0x1A8)=0;
            scale=RandomFloatRange(3.0f,5.0f);
            vec_scale_to_length(state+0x1A0,state+0x1A0,scale*0.01666666753590107f);
            if (*(u8 *)(object+0x43)!=17) StartAnimationBlended(object,17,0,30);
            *(short *)(state+0x4D2)=0;
            rotation = (float *)(state + 0x480);
            for (i = 0; i < 3; i++) {
                rotation[i] = RandomFloatRange(240.0f,720.0f)*0.0002908882452175021f;
                qcopy((char *)matrix + i * 16, object + 0xC0 + i * 16);
            }
            GetEulerAnglesFromMatrix(matrix,object+0xF0);
            *(u16 *)(object+0x34)&=0xEFFF;
        }
        *(float *)(state+0x1A8)-=*(float *)(state+0x12C);
        SetControlMotionAndStep(object,state+0x1A0);
        FastVecScale(state+0x480,state+0x480,0.98f);
        scale=*(float *)(object+0x2C)*0.0009765625f;
        collision_flags=6;
        get_moby_joint_matrices(object,1,&collision_flags,matrix);
        FastVecScale(direction,matrix+12,scale);
        RotateObjectAboutPoint(object,direction,*(float *)(state+0x480),*(float *)(state+0x484),*(float *)(state+0x488));
        euler_rotation_basis(object+0xC0,object+0xF0);
        if (*(float *)(object+0x18)<*(float *)(GetArenaCenterPoint(*(int *)(object+0xB8))+8)+5.0f ||
            !RandomIntBelow(450) || *(u16 *)(object+0x96)>300) {
            SetMobyAnimTypeThree(object,0,-1); DeactivateSmasherRobot(object);
        }
        break;
    }
    FinishSmasherRobotFrame(object);
}
