#include "common.h"
typedef struct PathWaypoint { u8 transform[0x30]; f32 position[4]; u8 tail[0x40]; } PathWaypoint;
typedef struct PathTarget { u8 prefix[0x10]; f32 position[4]; u8 mid[0x14]; u16 flags; u8 tail[0xCA]; } PathTarget;
typedef struct WaypointPath { s32 points[10]; } WaypointPath;
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
extern void func_L12_003E04B8(void *);
extern void func_L12_003E07B0(void *);
extern s32 func_002B1C20(void *,void *);
extern void func_00288E18(s32,s32);
extern void func_002A7750(void *,s32,s32);
extern void func_002A7470(void *,s32,s32,s32);
extern void func_002AC728(void *,void *,s32,f32,f32);
extern void func_002A6C58(void *,s32,s32);
extern void func_00282CF0(void *,void *,void *);
extern f32 func_00282DF0(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_0032E998(void *,void *,void *,void *,s32,f32,f32,void *,void *);
extern s32 func_L12_003E1B28(s32,void *);
extern s32 func_00282948(void *);
extern f32 func_00283B98(f32,f32);
extern f32 func_002A78D8(f32,f32);
extern s32 func_L02_00331440(void *,void *,s32,f32,f32,f32);
extern s32 func_002A7820(s32,s32);
extern s32 func_002ACBC8(void *,s32);
extern int func_002E5E58(int,int,void *);
extern void func_002B0A18(s32,s32);
extern void func_L12_00419D68(void *,void *,void *);
extern f32 func_002A7878(f32,f32);
extern s32 func_002A77E0(s32);
extern f32 func_002A7940(void);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_00283248(f32,f32);
extern f32 func_00282E20(void *);
extern void func_002B5278(void *,f32);
extern void func_00282F20(void *,void *,f32);
extern s32 D_L12_001B09F0 __attribute__((sda));
extern s32 D_L12_001B09F4 __attribute__((sda));
extern PathWaypoint *D_L12_001B2F8C MACRO_ADDR;
extern s32 D_L12_001B2E9C MACRO_ADDR;
/* Per-entry flag table; other code indexes it too. An element access keeps the
 * store two words long, so it stays out of the call's delay slot, as in retail. */
extern u8 D_001A7A60[] MACRO_ADDR;
extern s32 D_L12_001A903C;
#define ANIM(o,n,t) { if ((o)[0x43]!=(n)) func_002A7470(o,n,0,t); }
#define REST(o) { I(o,0x98)=0; U(o,0x34)=(U(o,0x34)|0x41)&0xEFFF; }
/* Space Tourist (moby class 3000) update. Waypoint-following state machine for a level 12 object: walks a path of 0x80-byte
 * waypoints, looks at targets, and counts hits in D_L12_001B09F0 (50/100/150/200). */
void func_L12_003DF9A0(u8 *creature) {
    u8 *vars=*(u8 **)(creature+0x68);
    f32 step[4] __attribute__((aligned(16)));
    f32 angle,angle2,speed,yaw,pitch;
    PathTarget *target;
    s32 hit;
    UpdateTodanoCreatureMoby(creature);
    if (creature[0x95]==1) goto states;
    if (creature[0x95]==3) {
        hit=DispatchActionByKind(creature,vars+0x60);
        if (hit&1) {
            D_L12_001B09F0++;
            if (D_L12_001B09F0==50) RequestSubtitleVoiceLine(0xA2D,0x84);
            else if (D_L12_001B09F0==100) RequestSubtitleVoiceLine(0xA2E,0x85);
            else if (D_L12_001B09F0==150) RequestSubtitleVoiceLine(0xA2F,0x86);
            else if (D_L12_001B09F0==200) RequestSubtitleVoiceLine(0xA30,0x87);
            SetMobyState(creature,1,0);
            ANIM(creature,4,20);
            D_L12_001B09F4++;
            SpawnExplosionWithSparks(creature,creature+0x10,-1,1.0f,0.0f);
            SetDeathBits(creature,0,3);
            H(vars,0x98)=0;
            F(vars,0x20)=H(vars,0x24);
            REST(creature);
        } else if (hit&2) SetMobyState(creature,4,1);
    }
states:
    switch(creature[0x20]) {
    case 2:
        D_L12_001B09F4=0;
        I(vars,0x7B8)=0;
        FastVecSub(step,vars+0x740,creature+0x10);
        speed=0.10000000894069672f;
        if (FastVecLength(step)>speed) { vec_scale_to_length(step,step,speed); goto add; }
        SetMobyState(creature,3,-1);
        ANIM(creature,4,20);
        goto add;
    case 3: {
        WaypointPath *path=(WaypointPath *)(vars+0x518);
        matrix_mul_vec3(step,vars+0x770,&D_L12_001B2F8C[path->points[I(vars,0x794)]]);
        FastVecAdd(step,step,D_L12_001B2F8C[path->points[I(vars,0x794)]].position);
        ComputeRegionRouteHeading(creature+0x10,step,&angle,vars+0x110,I(vars,0x790),0.0f,F(vars,0x7A4),vars+0x79C,vars+0x7A0);
        if (I(vars,0x540) && I(vars,0x540)==I(vars,0x794)-1) {
            speed=0.05000000447034836f;
            if (!I(vars,0x7B8)) {
                I(vars,0x7B8)=AlertSquirrelContainingObject(I(vars,0x544),creature);
                if (I(vars,0x7B8)) { SetMobyState(creature,7,2); ANIM(creature,5,10); }
            }
        } else speed=F(vars,0x7AC);
        if (!FastFloatHelperD(vars+0x7B0)) angle=FastAddRotations(angle,F(vars,0x7B4));
        if (!I(vars,0x7B0) && I(vars,0x5D0)>60) {
            I(vars,0x7B0)=60;
            F(vars,0x7B4)=RandomSignedFloatRange(90.0f,135.0f)*0.01745329424738884f;
        }
        if (MoveToTargetWithTempLimits(creature,step,1,angle,speed,-1.0f)&0x80) {
            SetMobyState(creature,4,-1);
            ANIM(creature,1,20);
            if (I(vars,0x540) && I(vars,0x540)==I(vars,0x794)) I(vars,0x7A8)=RandomIntRange(80,180);
            else I(vars,0x7A8)=RandomIntRange(10,160);
        }
        if (F(creature,0x18)<50.0f) SetMobyState(creature,1,0);
        if (I(vars,0x5D0)>200) {
            SetMobyState(creature,1,0);
            ANIM(creature,4,20);
            SpawnExplosionWithSparks(creature,creature+0x10,-1,1.0f,0.0f);
            SetDeathBits(creature,0,3);
            F(vars,0x20)=H(vars,0x24);
            REST(creature);
        } else if (F(vars,0x7A4)>=0.5f && F(vars,0x61C)<4.0f) F(vars,0x7A4)=0.4f;
        if (I(vars,0x794)!=I(vars,0x798) && I(vars,0x7A8)>20) I(vars,0x7A8)=20;
        break;
    }
    case 5:
        ComputeRegionRouteHeading(creature+0x10,vars+0x740,&angle2,vars+0x110,I(vars,0x790),0.0f,F(vars,0x7A4),vars+0x79C,vars+0x7A0);
        if (!FastFloatHelperD(vars+0x7B0)) angle2=FastAddRotations(angle2,F(vars,0x7B4));
        MoveToTargetWithTempLimits(creature,vars+0x740,1,angle2,F(vars,0x7AC),-1.0f);
        if (F(creature,0x18)<50.0f) SetMobyState(creature,1,0);
        if (!I(vars,0x7B0) && I(vars,0x5D0)>60) {
            I(vars,0x7B0)=60;
            F(vars,0x7B4)=RandomSignedFloatRange(90.0f,135.0f)*0.01745329424738884f;
        }
        if (IsPointInCuboid(creature+0x10,I(vars,0x54C))) { SetMobyState(creature,6,-1); ANIM(creature,3,20); }
        break;
    case 4: {
        if (I(vars,0x794)!=I(vars,0x798) && FastFloatHelperD(vars+0x7A8)) {
            if (I(vars,0x798)>=6) {
                if (!D_L12_001B09F4 && !D_001A7A60[10]) {
                    D_001A7A60[10]=1;
                    PlaySoundFromGlobalBank(1,0,0);
                    SetEntryValueByIndex(0x1233,-1);
                    D_L12_001A903C=1;
                }
                ComputeGateSightPoints((PathTarget *)(D_L12_001B2E9C+(I(vars,0x514)<<8)),vars+0x740,vars+0x750);
                SetMobyState(creature,5,-1);
                ANIM(creature,4,20);
            } else {
                I(vars,0x794)=I(vars,0x798);
                SetMobyState(creature,3,-1);
                ANIM(creature,4,20);
                F(vars,0x7A4)=RandomFloatRange(0.5f,0.7f);
            }
            break;
        }
        if (U(creature,0x96)<2 || FastFloatHelperD(vars+0x7BC)) {
            if ((u32)(I(vars,0x794)-1)<4 && (U(creature,0x96)<2 || RandomIntBelow(2))) {
                qcopy(vars+0x780,D_L12_001B2F8C[I(vars+((u32)(I(vars,0x794)-1)<<2),0x530)].position);
            } else {
                target=(PathTarget *)((I(vars,0x548)<<8)+D_L12_001B2E9C);
                if ((target->flags^1)&1) { qcopy(vars+0x780,target->position); F(vars,0x788)+=0.5f; }
                else {
                    f32 randomYaw=RandomAngle();
                    F(vars,0x780)=FastSinOrCosA(randomYaw);
                    F(vars,0x784)=FastSinOrCosB(randomYaw);
                    I(vars,0x788)=0;
                    F(vars,0x788)+=RandomFloatRange(F(vars,0x788),0.5f);
                    FastVecAdd(vars+0x780,vars+0x780,creature+0x10);
                }
            }
            I(vars,0x7BC)=RandomIntRange(60,120);
        }
        FastVecSub(step,vars+0x780,creature+0x10);
        yaw=FastMatrixHelperA(step[0],step[1]);
        pitch=-FastMatrixHelperA(vec_length_xy(step),step[2]);
        StepMovementAtOwnPositionWithFactor(creature,yaw);
        F(vars,0x6A4)=F(vars,0x724)=pitch*0.5f;
        break;
    }
    case 8:
        if (U(creature,0x96)>=5) {
            REST(creature);
            SpawnExplosionWithSparks(creature,creature+0x10,-1,1.0f,0.0f);
            SetMobyState(creature,1,0);
        }
    case 6:
        FastVecSub(step,vars+0x750,creature+0x10);
        speed=0.10000000894069672f;
        if (FastVecLength(step)>speed) {
            vec_scale_to_length(step,step,speed);
        } else {
            SetMobyState(creature,1,0);
            ANIM(creature,4,20);
            U(creature,0x7C)=1<<RandomIntBelow(6);
            REST(creature);
        }
add:
        FastVecAdd(creature+0x10,creature+0x10,step);
        break;
    case 7:
        if (creature[0x60]&2) { SetMobyState(creature,3,1); ANIM(creature,7,10); }
        break;
    case 1:
        REST(creature);
        break;
    }
    AdvanceJointPairAndCounter(creature);
}
