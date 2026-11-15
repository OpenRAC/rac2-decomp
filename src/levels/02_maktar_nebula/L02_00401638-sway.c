#include "common.h"
extern char D_00189EA0[];
extern void func_002A7750(char *,int,int);
extern float func_002AA2E8(float *,float,float);
extern int func_00282948(void *);
extern char *D_L02_001FF1C0[];
extern char D_L02_001A8F20[] MACRO_ADDR, D_L02_001BA500[];
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern float func_00283248(float,float), func_00283C80(float,float);
extern int func_002ACBC8(void *,int);
extern void *func_L02_003CD5B0(int);
extern void func_002AA548(float *,float *,float,float,float,float);
extern void func_002C9828(void *,int,void *,void *,int,float);
extern float func_002A89A8(void *,int,float);
extern int func_002E5CF8(int,int,void *);
extern void func_L02_003CD668(void *,void *);
extern int func_002A8508(int,int);
extern void func_0029F338(char *);
extern void func_L02_00401BF8(char *),func_L02_00401D38(char *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void *func_002A9640(void *,u32,s32);
extern float func_002A96A0(void *,void *);
extern void func_002B0A68(char *,int,void *,u8,float,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_0032DA58(void *,void *,void *,float);
/* Moves a swaying object along a preset path, drops a spawned item at the end, then lets the object fall apart and disappear. Update handler of moby class 2934. */
void func_L02_00401638(char *moby) {
    float oldPos[4] __attribute__((aligned(16))), scratch[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby+0x68), *path;
    float x,y,z,t;
    void *spawned;
    if ((unsigned)(*(u8 *)(moby+0x20)-2)<3) qcopy(&oldPos,moby+0x10);
    switch (*(u8 *)(moby+0x20)) {
    case 0: {
        float inv;
        if (!*(s16 *)(vars+0x24)) { *(s16 *)(vars+0x24)=40; *(float *)(vars+0x20)=40.0f; }
        SetMobyState(moby,1,-1);
        *(int *)(vars+0x16c)=-1;
        path=gRoutePolygons[*(int *)(vars+0x100)];
        *(char **)(vars+0x164)=path;
        inv=fast_vec_dist(path+0x10,path+0x20);
        inv=1.0f/inv;
        *(float *)(vars+0x15c)=inv*0.5f;
        *(float *)(vars+0x154)=inv*0.0013888889f;
        *(float *)(vars+0x158)=inv*0.0027777778f;
        *(float *)(vars+0x160)=inv;
        *(int *)(vars+0x150)=0;
        qcopy(vars+0x120,*(char **)(vars+0x164)+0x10);
        *(int *)(moby+0x98)=0;
        *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;
        break; }
    case 1:
        if (IsPointInCuboid(gHeroPosition,*(int *)(vars+0x104))) {
            if (!FindGroupEntityInState17(*(int *)(vars+0x110))) {MarkMobySpawned(moby);return;}
            StepValueTowardTarget((float *)(vars+0x14c),(float *)(vars+0x150),(float)**(int **)(vars+0x164)-1.0f,*(float *)(vars+0x15c),*(float *)(vars+0x158),*(float *)(vars+0x15c));
            *(int *)(vars+0x14c)=0; SetMobyState(moby,2,-1);
            *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)&0xffbe)|0x1000;
            *(int *)(moby+0x98)=*(int *)(*(char **)(moby+0x24)+0x10);
        }
        break;
    case 2:
        x=*(float *)(vars+0x150)*60.0f;
        x+=*(float *)(vars+0x14c);
        { float limit=(float)(**(int **)(vars+0x164)-2); if(limit<x)x=limit; }
        y=x+1.0f;
        {
            int highIndex=FloatToInt(y);
            int lowIndex=FloatToInt(x);
            char *path=*(char **)(vars+0x164);
            char *lowPoint=path+lowIndex*16;
            path+=highIndex*16;
            z=*(float *)(path+0x10)-*(float *)(lowPoint+0x10);
        }
        {
            int highIndex=FloatToInt(y);
            int lowIndex=FloatToInt(x);
            char *path=*(char **)(vars+0x164);
            char *lowPoint=path+lowIndex*16;
            path+=highIndex*16;
            t=*(float *)(path+0x14);
            t=FastMatrixHelperA(z,t-*(float *)(lowPoint+0x14));
        }
        t=1.0f-FastDiffRots(t,*(float *)(vars+0x138)); if(t<0.1f)t=0.1f;
        StepValueTowardTarget((float *)(vars+0x14c),(float *)(vars+0x150),(float)**(int **)(vars+0x164)-1.0f,*(float *)(vars+0x154),*(float *)(vars+0x158),t**(float *)(vars+0x15c));
        SamplePathPosition(*(void **)(vars+0x164),0,vars+0x120,vars+0x130,0,*(float *)(vars+0x14c));
        if(*(float *)(vars+0x14c)>=(float)**(int **)(vars+0x164)-1.0f)SetMobyState(moby,3,-1);
        break;
    case 3:
        if(*(int *)(vars+0x110)!=-1 && FastFloatHelperD(vars+0x168)) {
            spawned=FindGroupEntityInState17(*(int *)(vars+0x110));
            if(spawned){ qcopy(&scratch,moby+0x10); scratch[2]=ProbeGroundHeightBelow(&scratch,0,0.5f);PlayMobySound(0,0,moby);ResetPoseAndRegisterChild(spawned,&scratch);*(int *)(vars+0x168)=120; }
            else if(!CountMobysInGroupNotInState(*(int *)(vars+0x110),-1))SetMobyState(moby,4,-1);
        }
        break;
    case 4:
        ApproachValue((float *)(vars+0x11c),0.16666667f,0.0013888889f);
        *(float *)(vars+0x128)+=*(float *)(vars+0x11c);
        if(!*(u8 *)(moby+0x31)){MarkMobySpawned(moby);return;}
    }
    *(float *)(moby+0x2c)=*(float *)(*(char **)(moby+0x24)+0x24)*1.5f;
    if(*(u8 *)(moby+0x31)||*(u8 *)(moby+0x20)==2||*(u8 *)(moby+0x20)==4)ApplySwayWobble(moby);
    if(*(u8 *)(moby+0x31)) {
        if(*(u8 *)(moby+0x20)<2)return;
        if(*(u8 *)(moby+0x20)<5){FastVecSub(&scratch,moby+0x10,&oldPos);SpawnSparkBursts(moby,&scratch);}
    }
    if(*(u8 *)(moby+0x20)>=2){
        void *hitMoby=FindOwnedEffectSlot(moby,0x10000,0); x=UpdateAimTargetStrength(moby,hitMoby);
        ApproachValue((float *)(vars+0x20),0.0f,x); *(u8 *)(moby+0xa8)=255;
        if(*(float *)(vars+0x20)==0.0f){PlayMobySound(2,0,moby);SpawnDebrisForMaskedParts(moby,0x7f7,D_L02_001A8F20,255,5.0f,10.0f,5.0f,10.0f);FastVecSub(&scratch,gCameraPosition_L02,moby+0x10);vec_scale_to_length(&scratch,&scratch,1.0f);SpawnBlastEffectMoby(moby,moby+0x10,&scratch,0.0f);MarkMobySpawned(moby);}
    }
}


