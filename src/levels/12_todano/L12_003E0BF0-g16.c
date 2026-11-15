#include "common.h"
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_0019B2E8[];
extern float D_L12_001B0A20 __attribute__((sda));
extern float D_L12_001B0A24 __attribute__((sda));
extern float D_L12_001B0A30[4] __attribute__((sda));
typedef struct TodanoPlayerView { u8 pad[0x80]; float position[4]; } TodanoPlayerView;
extern TodanoPlayerView D_00189E20;
extern u8 *D_0018C0B0 NOT_SDA;
extern void func_L12_003E1638(u8 *);
extern void func_L12_003E19F0(u8 *);
extern int func_002B3890(u8 *);
extern void func_002A7750(u8 *,int,int);
extern void func_002A7470(u8 *,int,int,int);
extern void func_002B60B0(u8 *,float,float,float,float);
extern int func_002A7820(int,int);
extern int func_002B1C20(u8 *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002A8F70(u8 *,u8 *,int,void *,void *,float);
extern void func_002A6C58(u8 *,int,int);
extern void func_L01_003E9CF8(u8 *,int,int);
extern void func_0029F338(u8 *);
extern float func_002A7940(void);
extern float func_002A7878(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern int func_L01_00321178(u8 *,void *);
extern int func_002A77E0(int);
extern float func_00283248(float,float);
extern void func_002B50E0(u8 *,void *,float);
extern void func_L12_003E1AA8(u8 *);
extern void func_002AA800(void *,int,float,float);
extern float func_0029F530(u8 *);
extern void func_002A8D70(u8 *,int,int,int,int,int,float,float,float);
extern void func_002B5258(u8 *);
extern void func_00283098(void *,void *,void *);
extern void func_L12_003E0A38(void *,void *,void *,int);
/* Updates a Mutant Test-Squirrel. It idles and wanders, walks to an object, picks it up and
   throws it. */
void func_L12_003E0BF0(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    float temp[4] __attribute__((aligned(16)));
    float angle, speed;
    UpdateGuardCreatureMoby(moby);
    switch(moby[0x95]) {
    case 5: {

        if(SetSecondPendingFlag(moby)) {
            *(u16 *)(moby+0x34)|=1;
            *(int *)(moby+0x98)=0;
            moby[0x31]=0;

        }
        if(D_0019B2E8[moby[0xB0]+(gCurrentMapIndex<<4)]&0x80) {
            if(*(int *)(vars+0x13C)==-1) {
                SetMobyState(moby,1,0);
                if(moby[0x43]) StartAnimationBlended(moby,0,0,0);
            } else {
                SetMobyState(moby,9,4);
                if(moby[0x43]!=14) StartAnimationBlended(moby,14,0,0);
                *(float *)(moby+0x18)+=4.0f;
                *(int *)(moby+0x98)=0;
                *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;
            }
            *(int *)(moby+0x98)=*(int *)(*(u8 **)(moby+0x24)+0x10);
            moby[0x31]=1;
            *(u16 *)(moby+0x34)&=0xFFFE;
        }
        break; }
    case 0:
        if(SetSecondPendingFlag(moby)) SetControllerSpeedLimits(moby,0.001111111138f,D_L12_001B0A20*0.0166666675359f,0.0008726647356525064f,0.104719772935f);
        if(*(short *)(vars+0x364)==1) {
            SetMobyState(moby,5,2);
            if(moby[0x43]!=2) StartAnimationBlended(moby,2,0,10);
        } else if(*(short *)(vars+0x366)) {
            SetMobyState(moby,3,1);
            if(moby[0x43]!=3) StartAnimationBlended(moby,3,0,20);
            *(short *)(vars+0x366)=0;
            if(*(short *)(vars+0x360)<300) *(short *)(vars+0x360)=RandomIntRange(480,600);
        }
        break;
    case 1:
        if(SetSecondPendingFlag(moby)) SetControllerSpeedLimits(moby,0.003333333414f,D_L12_001B0A24*0.0166666675359f,0.0017453294713050127f,0.20943954587f);
        if(*(short *)(vars+0x364)==1) {
            SetMobyState(moby,6,2);
            if(moby[0x43]!=7) StartAnimationBlended(moby,7,0,10);
        } else if(!*(short *)(vars+0x360)) {
            SetMobyState(moby,1,0);
            if(moby[0x43]) StartAnimationBlended(moby,0,0,20);
        }
        break;
    case 2:
        if(SetSecondPendingFlag(moby)) SetControllerSpeedLimits(moby,0.003333333414f,D_L12_001B0A24*0.0166666675359f,0.0017453294713050127f,0.20943954587f);
        if(*(short *)(vars+0x364)!=1) {
            SetMobyState(moby,3,1);
            if(moby[0x43]!=3) StartAnimationBlended(moby,3,0,20);
            *(short *)(vars+0x360)=RandomIntRange(580,600);
        }
        break;
    case 3: {
        int hit; u8 *target;
        hit=DispatchActionByKind(moby,vars+0x60);
        target=*(u8 **)(vars+0x38);
        if(target && *(short *)(target+0xAA)==0xFAB /* moby class 4011 */) {
            FastVecSub(temp,moby+0x10,target+0x10);
            vec_scale_to_length(temp,temp,1.0f);
            QueueImpactEffect(moby,gHeroMoby_0018C0B0,0x10000,*(u8 **)(vars+0x38)+0x10,temp,50.0f);
        }
        if(hit&1) {
            SetDeathBits(moby,0,3);
            qcopy(temp,moby+0x10);
            temp[2]+=0.25f;
            QueueMobyForGlowEffect(moby,0,0);
            MarkMobySpawned(moby);
            return;
        }
        if(hit&2) {
            if(*(short *)(vars+0x364)==1) {
                SetMobyState(moby,6,2);
                if(moby[0x43]!=7) StartAnimationBlended(moby,7,0,20);
            } else {
                SetMobyState(moby,3,1);
                if(moby[0x43]!=3) StartAnimationBlended(moby,3,0,20);
                *(short *)(vars+0x360)=RandomIntRange(580,600);
            }
        }
        break; }
    case 4:
        if(SetSecondPendingFlag(moby)) SetControllerSpeedLimits(moby,0.004444444552f,D_L12_001B0A24*0.0166666675359f,0.0034906589426100254f,0.20943954587f);
        break;
    }
    switch(moby[0x20]) {
    case 1:
        if(!*(short *)(vars+0x362)) {
            SetMobyState(moby,2,-1);
            angle=RandomAngle();
            speed=RandomFloatRange(3.0f,5.0f);
            *(float *)(vars+0x350)=FastSinOrCosA(angle)*speed;
            *(float *)(vars+0x354)=FastSinOrCosB(angle)*speed;
            *(int *)(vars+0x358)=0;
            FastVecAdd(vars+0x350,vars+0x350,vars+0x340);
            if(moby[0x43]!=15) StartAnimationBlended(moby,15,0,10);
        }
        StepMovementAtOwnPosition(moby);
        break;
    case 2: {
        int hit;
        hit=TurnMobyTowardTarget(moby,vars+0x350);
        if((*(u16 *)(moby+0x96)>=31 && (hit&0x80)) || *(u16 *)(moby+0x96)>=601) {
            SetMobyState(moby,1,-1);
            *(short *)(vars+0x362)=RandomIntRange(300,500);
            if(moby[0x43]!=RandomIntBelow(2)) StartAnimationBlended(moby,RandomIntBelow(2),0,20);
        }
        break; }
    case 3: StepMovementAtOwnPosition(moby); break;
    case 5: {
        u8 *position=moby+0x10;
        u8 *target=*(u8 **)(vars+0x368);
        int animFlags;
        angle=FastMatrixHelperA(gHeroState.position[0]-*(float *)(target+0x10),gHeroState.position[1]-*(float *)(target+0x14));
        StepMovementController(moby,position,angle);
        animFlags=moby[0x60];
        animFlags&=2;
        if(animFlags) {
            SetMobyState(moby,6,-1);
            if(moby[0x43]!=7) StartAnimationBlended(moby,7,0,20);
        } else {
            animFlags=*(u16 *)(moby+0x96);
            if(animFlags==20) AlertSquirrelsInGroup(moby);
        }
        break; }
    case 6:
        if(TurnMobyTowardTarget(moby,*(u8 **)(vars+0x368)+0x10)&0x80) {
            SetMobyState(moby,7,-1);
            if(moby[0x43]!=8) StartAnimationBlended(moby,8,0,20);
        }
        break;
    case 7:
        if(moby[0x60]&2) {
            SetMobyState(moby,6,-1);
            if(moby[0x43]!=7) StartAnimationBlended(moby,7,0,10);
        } else {
            float animTime;
            u8 *yawField=moby+0xF8;
            u8 *target=*(u8 **)(vars+0x368);
            angle=FastMatrixHelperA(*(float *)(target+0x10)-*(float *)(moby+0x10),*(float *)(target+0x14)-*(float *)(moby+0x14));
            StepAngleTowardTarget(yawField,0,angle,0.058177649974823f);
            animTime=GetMobyAnimationValue(moby);
            if(12.0f<=animTime && animTime<=14.0f) TestHitAtBone(moby,2,1,0,1,0,0.25f,vars[0x34],1.0f);
            StepMovementAtOwnPosition(moby);
        }
        break;
    case 10: {
        u8 *position=moby+0x10;
        u8 *target=*(u8 **)(vars+0x374);
        angle=FastMatrixHelperA(*(float *)(target+0x10)-*(float *)(moby+0x10),*(float *)(target+0x14)-*(float *)(moby+0x14));
        StepMovementController(moby,position,angle);
        if(moby[0x43]==5 && *(float *)(moby+0x18)<*(float *)(vars+0x348)+*(float *)(vars+0x1F8)*10.0f) StartAnimationBlended(moby,6,0,10);
        if(moby[0x43]==6 && (moby[0x60]&2)) {
            SetMobyState(moby,11,-1);
            if(moby[0x43]!=7) StartAnimationBlended(moby,7,0,20);
        }
        break; }
    case 11:
        TurnMobyTowardTarget(moby,*(u8 **)(vars+0x374)+0x10);
        if(*(float *)(vars+0x21C)<2.0f) {
            SetMobyState(moby,12,-1);
            if(moby[0x43]!=8) StartAnimationBlended(moby,8,0,20);
        }
        break;
    case 12: {
        float animTime;
        if(*(u8 **)(vars+0x374)) {
            TurnMobyTowardTarget(moby,*(u8 **)(vars+0x374)+0x10);
            animTime=GetMobyAnimationValue(moby);
            if(11.0f<=animTime) {
                int release=1;
                matrix_mul_vec3(temp,D_L12_001B0A30,moby+0xC0);
                FastVecAdd(temp,temp,moby+0x10);
                if(!(14.0f<=animTime)) release=0;
                StartSubObjectMove(*(u8 **)(vars+0x374),temp,moby+0xF0,release);
                if(release) *(int *)(vars+0x374)=0;
            }
        }
        if(moby[0x60]&2) {
            SetMobyState(moby,13,-1);
            if(moby[0x43]!=9) StartAnimationBlended(moby,9,0,10);
        }
        break; }
    case 13:
        if(moby[0x60]&2) {
            SetMobyState(moby,1,0);
            if(moby[0x43]) StartAnimationBlended(moby,0,0,10);
        }
        break;
    }
    ResetJointSlotsAndAdvanceCounter(moby);
}
