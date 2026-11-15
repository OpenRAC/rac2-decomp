#include "common.h"
extern void func_L07_003E56B8(void *);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_L07_003E5910(void *,void *,float,float);
extern float func_002A78D8(float,float);
extern void func_002A8C28(void *,void *,float,float,float,int,int,int,int);
extern float func_00282DF0(void *);
extern void func_002AC9F8(void *,float);
extern void func_L07_003E5FA8(void *);
extern void func_002AA548(void *,float,void *,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_L07_003E5A70(void *);
extern float D_L07_001B0A88 __attribute__((sda));
extern float D_L07_001B0A8C __attribute__((sda));
extern float D_L07_001B0A90 __attribute__((sda));
extern float D_L07_001B0A94 __attribute__((sda));
extern float D_L07_001B0A98[] __attribute__((sda));
struct PlayerState1310 { char pad[0x229C]; int state; char pad2[0x1FC]; void *target; };
extern struct PlayerState1310 D_00189E20;
/* Advance the entity state machine, movement and recovery scaling. */
/* Per-frame update for moby class 3357: runs its behaviour states and eases the object toward
   its goals. */
void func_L07_003E5198(unsigned char *moby)
{
    float goalPos[4] __attribute__((aligned(16)));
    float lengths[2];
    char *vars=*(char **)(moby+0x68);
    int i;
    UpdateGroupEntityBase(moby);
    switch(moby[0x95]) {
    case 0:
        if (*(int *)(vars+0x114)==1) SetMobyState(moby,5,2);
        break;
    case 2:
        if (*(int *)(vars+0x114)!=1) SetMobyState(moby,1,0);
        break;
    }
    switch(moby[0x20]) {
    case 1:
        if (SetFirstPendingFlag(moby) && moby[0x43]) StartAnimationBlended(moby,0,0,20);
        if (*(char **)(vars+0x260)) {
            matrix_mul_vec3(goalPos,vars+0x220,*(char **)(vars+0x260)+0xC0);
            FastVecAdd(goalPos,goalPos,*(char **)(vars+0x260)+0x10);
        } else qcopy(goalPos,vars+0x220);
        MoveEntityToTrackedHeight(moby,goalPos,0,1);
        break;
    case 3:
        if(SetFirstPendingFlag(moby)) *(float *)(vars+0x250)=RandomSignedFloatRange(D_L07_001B0A98[0],D_L07_001B0A98[1])*0.01745329424738884f;
        if(MoveEntityToTrackedHeight(moby,vars+0x100,*(float *)(vars+0x250),1)<2) SetMobyState(moby,4,-1);
        break;
    case 4:
        if(SetFirstPendingFlag(moby) && moby[0x43]!=2) StartAnimationBlended(moby,2,0,5);
        MoveEntityToTrackedHeight(moby,vars+0x100,*(float *)(vars+0x250),1);
        if(moby[0x60]&2) SetMobyState(moby,5,-1);
        break;
    case 5:
        if(SetFirstPendingFlag(moby) && moby[0x43]!=3) StartAnimationBlended(moby,3,0,2);
        MoveEntityToTrackedHeight(moby,vars+0x100,*(float *)(vars+0x250),1);
        if(*(unsigned short *)(moby+0x96)>10)
            SweepCollisionFromObject(moby,moby+0x10,D_L07_001B0A94,(float)*(unsigned char *)(vars+0x34),1,0x4000001,0,1,0);
        if(*(unsigned short *)(moby+0x96)>30 &&
            (gHeroState.state==7 || gHeroState.state==20) &&
            gHeroState.target==moby) SetMobyState(moby,6,-1);
        break;
    case 6:
        if(SetFirstPendingFlag(moby) && moby[0x43]!=4) StartAnimationBlended(moby,4,0,1);
        if(moby[0x60]&2) SetMobyState(moby,5,-1);
        break;
    case 9: {
        float tolerance=0.08333333582f;
        FastVecSub(goalPos,vars+0x230,moby+0x10);
        if(FastVecLength(goalPos)>tolerance) ClampVectorLength(goalPos,tolerance);
        else SetMobyState(moby,10,-1);
        FastVecAdd(moby+0x10,moby+0x10,goalPos);
        SpawnEntityParticlePair(moby);
        break;
    }
    case 10:
        if(SetFirstPendingFlag(moby)) *(int *)(moby+0x98)=*(int *)(*(char **)(moby+0x24)+0x10);
        lengths[1]=FastVecLength(moby+0xC0);
        lengths[0]=FastVecLength(moby+0xE0);
        {
            float a=D_L07_001B0A88*0.0002777777845f;
            float b=D_L07_001B0A8C*0.01666666754f;
            StepValueTowardTarget(&lengths[0],1,vars+0x254,a,a,b);
            if(lengths[0]>D_L07_001B0A90) StepValueTowardTarget(&lengths[1],1,vars+0x258,a,a,b);
        }
        for(i=0;i<2;i++) vec_scale_to_length(moby+0xC0+i*16,moby+0xC0+i*16,lengths[1]);
        vec_scale_to_length(moby+0xE0,moby+0xE0,lengths[0]);
        if(lengths[1]>=1) {
            for(i=0;i<3;i++) vec_scale_to_length(moby+0xC0+i*16,moby+0xC0+i*16,1);
            SetMobyState(moby,3,2);
        }
        SpawnEntityParticlePair(moby);
        break;
    }
    TickEntityTimers(moby);
}
