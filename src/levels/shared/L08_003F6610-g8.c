#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 D_00189EA0[];
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
#define E_I(p,o) (*(int *)((u8 *)(p)+(o)))
#define E_F(p,o) (*(float *)((u8 *)(p)+(o)))
extern void func_L08_003F6348(void *,void *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern int D_L08_001B2508;
extern u8 D_L08_001B9B00[];
extern u8 *D_L08_001FE7C0[];
extern u8 *D_L08_001B2ACC __attribute__((sda));
extern float D_L08_001B0B5C __attribute__((sda));
extern u8 D_L08_001AC5E0[] MACRO_ADDR;
extern void func_0029F338(void *);
extern int func_002A8600(void **,int,int,int);
extern int func_00282978(void *);
extern int func_002A77E0(int);
extern void func_L04_003429F8(void *,void *,void *,int,void *,int,float);
extern int func_L08_003F6568(void *,void *);
extern void func_002A7470(void *,int,int,int);
extern float func_0029F530(void *);
extern float func_00282DF0(void *);
extern void func_00282FB8(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern int func_002A7820(int,int);
extern void func_L02_0031E9E8(void *,float);
extern float func_002A7878(float,float);
extern float func_002A89A8(void *,int,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_002ACB48(void *,float);
extern float func_L00_0031CDD0(void *,void *,int,float,float);
extern u8 *func_L08_003F6018(void *,void *,void *);
extern int func_L06_0035EA68(void *,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
typedef struct { u8 pad[0x120]; float speed; int path,object; u16 delay, timer; u8 limit,count,nearest,pad2; int children[2]; int pad3; int targets[4]; } FVars;
/* Updates a Spawner (moby class 3098): it fires off child objects (each aimed at a target or
   random spot) while it has some left, and removes itself when destroyed. */
void func_L08_003F6610(u8 *moby)
{
    void *foundChild;
    struct { TI128 target, direction, velocity, step; } frame;
    u8 *vars=*(u8 **)(moby+0x68);
    int index;

    void *pathArg,*targetPos;
    int pathFlag,targetId;
    UpdateDestructibleObject(moby,vars);
    if(moby[0x31] && fast_vec_dist(moby+0x10,D_L08_001B9B00)<24.0f) {
        UpdateMobyGroundCheck(moby);moby[0x6f]=0x16;
    }
    switch(moby[0x20]) {
    case 0:
        if(D_L08_001B2508) {
            int i;
            foundChild=0;
            for(i=0;i<2;i++) {
                while(!GetFirstMobyInGroup(&foundChild,((FVars *)vars)->children[i],0,0)) MarkMobySpawned(foundChild);
            }
            moby[0x20]=1;
        }
        vars[0x29]=1;
        break;
    case 1:
        if(!FastDecTimer(vars+0x12e)) break;
        if(!RandomIntBelow(7)) {
            pathArg=0;pathFlag=0;targetPos=0;targetId=0;
            if(E_I(vars,0x124)!=-1) {pathArg=vars+0x124;pathFlag=1;}
            if(E_I(vars,0x128)!=-1) {u8 *target=D_L08_001FE7C0[E_I(vars,0x128)];targetId=E_I(target,0);targetPos=target+0x10;}
            FindHeroOrMobyTarget(moby,vars+0xc0,pathArg,pathFlag,targetPos,targetId,E_F(vars,0x120));
        } else {
            u8 *target=*(u8 **)(vars+0x100);
            if(target && target[0x20]!=0xfe && target[0x20]!=0xfd) qcopy(vars+0xc0,target+0x10);
            else {E_I(vars,0x100)=0;E_I(vars,0x104)=2;}
        }
        if(E_I(vars,0x104)==2) break;
        index=CountListEntries(moby,vars);
        if(vars[0x130]>vars[0x131] && index!=-1) {
            moby[0x20]=2;
            if(moby[0x43]!=1) StartAnimationBlended(moby,1,0,10);
        }
        break;
    case 2: {
        u8 *chosenTarget;
        float speed;
        if(moby[0x60]&2) {
            moby[0x20]=1;
            if(moby[0x43]) StartAnimationBlended(moby,0,0,10);
            break;
        }
        if(GetMobyAnimationValue(moby)!=12.0f) break;
        chosenTarget=0;
        if(vars[0x132]) {
            int i;
            float best, distance;
            best=100000.0f;
            for(i=0;i<4;i++) {
                if(((FVars *)vars)->targets[i]!=-1) {
                    u8 *target=D_L08_001B2ACC+((FVars *)vars)->targets[i]*128;
                    distance=fast_vec_dist(gHeroPosition,target+0x30);
                    if(distance<best) {chosenTarget=target;best=distance;}
                }
            }
            if(!chosenTarget) {
                FastVecSub(&frame.target,vars+0xc0,(moby+0x10));
                FastVecScale(&frame.target,&frame.target,0.5f);
                if(E_F(vars,0x120)>3.0f) FastVectorDivideHelper(&frame.target,&frame.target,3.0f);
                if(FastVecLength(&frame.target)<3.0f) vec_scale_to_length(&frame.target,&frame.target,3.0f);
                FastVecAdd(&frame.target,&frame.target,(moby+0x10));
            } else qcopy(&frame.target,chosenTarget+0x30);
        } else {
            int startSlot=RandomIntRange(0,3);
            int i;
            for(i=0;i<4;i++) {
                int slot=(i+startSlot)%4;
                if(((FVars *)vars)->targets[slot]!=-1) {
                    chosenTarget=D_L08_001B2ACC+((FVars *)vars)->targets[slot]*128;
                    break;
                }
            }
            if(!chosenTarget) {
                float radius=E_F(vars,0x120);if(radius<3.0f) radius=3.0f;
                RandomPlanarOffset(&frame.target,radius);
                FastVecAdd(&frame.target,&frame.target,(moby+0x10));
            } else qcopy(&frame.target,chosenTarget+0x30);
        }
        if(chosenTarget) {
            FastVecScale(&frame.direction,chosenTarget,RandomFloatRange(-1.0f,1.0f));
            FastVecAdd(&frame.target,&frame.target,&frame.direction);
            FastVecScale(&frame.direction,chosenTarget+0x10,RandomFloatRange(-1.0f,1.0f));
            FastVecAdd(&frame.target,&frame.target,&frame.direction);
        }
        {float height=ProbeGroundHeightBelow(&frame.target,0,0.5f);
        if(height!=0.0f) E_F(&frame.target,8)=height;}
        FastVecSub(&frame.direction,&frame.target,(moby+0x10));
        speed=FastVecLength(&frame.direction)/D_L08_001B0B5C<0.08000000566f ? FastVecLength(&frame.direction)/D_L08_001B0B5C : 0.08000000566f;
        vec_scale_to_length(&frame.direction,&frame.direction,speed);
        TransformMobyJointToWorld(moby,0,&frame.velocity);
        vec_scale_to_length(&frame.step,&frame.direction,0.05f);
        AddRandomOffsetToVector(&frame.step,0.025f);
        FastVecAdd(&frame.velocity,&frame.velocity,&frame.step);
        E_F(&frame.direction,8)=ComputeShotLaunchSpeed(&frame.velocity,&frame.target,0,speed,-0.002722222358f);
        AllocateOwnedPoolObject(moby,&frame.velocity,&frame.direction);
        ((FVars *)vars)->timer=((FVars *)vars)->delay;
        ((FVars *)vars)->count++;
        break;
    }
    case 3:
        mine_fall(moby,vars+0x60);
        if(moby[0x60]&2) {
            moby[0x20]=1;
            if(moby[0x43]) StartAnimationBlended(moby,0,0,20);
        }
        break;
    case 4:
        if(mine_fall(moby,vars+0x60)&0x40) {
            vec_scale_to_length(&frame.target,D_L08_001AC5E0,0.1666666716f);
            SpawnExplosionEffects(moby,&frame.target,0,0.0f,0.0f,30,8,20,8.0f,4.0f,18.0f,1.0f,1,15.0f,1,1,-1,0,0x810001);
            MarkMobySpawned(moby);
        }
        break;
    }
}
