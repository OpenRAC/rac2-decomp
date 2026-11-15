#include "common.h"
typedef struct { float data[12]; } InitBlock;
extern u8 D_L09_001A8F20[] MACRO_ADDR;
extern void *D_L09_001FE6C0[];
extern u8 D_L09_001B10D0[] SDATA(D_L09_001B10D0);
extern float D_L09_001B0F08 __attribute__((sda));
extern float D_L09_001B0F0C __attribute__((sda)),D_L09_001B0F10 __attribute__((sda)),D_L09_001B0F1C __attribute__((sda)),D_L09_001B0F20 __attribute__((sda)),D_L09_001B0F24 __attribute__((sda)),D_L09_001B0F30 __attribute__((sda));
extern int func_00283CF0(float),func_001163B0(void),func_002A7820(int,int);
extern u8 *func_0029EFD0(int),*func_L02_0032B468(void *,int,void *,void *,int,int,void *,void *,void *,float);
extern void func_002B60B0(u8 *,float,float,float,float);
extern float func_L01_003377C8(void *);
extern int func_002B3380(void *,void *,void *),func_L09_003F7C50(void *,int,int);
extern void func_0029FCC0(void *,int,void *),func_0029FC20(void *,int,void *),func_00283678(void *,void *),func_002A0F48(void *),func_002AB028(void *),func_002A10E8(void *);
extern void func_00282CF0(void *,void *,void *),func_L09_003F73E8(void *),func_002A7750(void *,int,int),func_L09_003F7518(void *,int,int,int);
extern float func_002A89A8(void *,int,float);
/* Sets up a new trooper: fills in its tuning values, creates its torso and two arm parts, and picks its first animation. */
void func_L09_003F7CE0(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68), *torso,*torsoVars; float transform[16]; float pos[4]; int i,j; u8 *parameters; u8 stage; float acceleration; int animation=9; float slow=0.004166666883975267f;
    *(float *)(moby+0x2C)*=D_L09_001B0F08;
    vars[0x60]=14;
    *(int *)(vars+0x98)=animation;
    vars[0x61]=18;
    vars[0x62]=17;
    vars[0x66]=20;
    vars[0x67]=255;
    *(float *)(vars+0x6C)=0.36666667461395264f;
    *(float *)(vars+0x70)=0.11666667461395264f;
    *(float *)(vars+0x74)=slow;
    *(float *)(vars+0x78)=0.008333333767950535f;
    *(float *)(vars+0x7C)=slow;
    *(float *)(vars+0x8C)=0.4f;
    vars[0xBC]=5;
    vars[0xBD]=animation;
    stage=4;
    vars[0xBF]=7;
    vars[0xC2]=10;
    vars[0xC3]=17;
    *(float *)(vars+0x90)=*(float *)(vars+0x310);
    *(float *)(vars+0xF8)=0.45f;
    *(u8 **)(vars+0x2F8)=0;
    *(u8 **)(vars+0x2F0)=0;
    *(u8 **)(vars+0x2F4)=0;
    *(float *)(vars+0x80)=0.7f;
    *(float *)(vars+0x84)=0.7f;
    vars[0xBE]=stage;
    vars[0x28]=3;
    *(float *)(vars+0x30)=1.7f;
    vars[0x2F]=8;
    vars[0x2A]=2;
    vars[0x4D]=0;
    vars[0x2E]=1;
    vars[0x48]=FloatToInt(25.0f);vars[0x4A]=FloatToInt(16.0f);
    { float first,second,third,fourth;
    acceleration=D_L09_001B0F24*0.00027777778450399637f;
    vars[0x1E8]=12;vars[0x1E9]=11;
    first=D_L09_001B0F0C*0.00027777778450399637f;second=D_L09_001B0F10*0.01666666753590107f;third=D_L09_001B0F1C*0.000004848137454391923f;
    fourth=D_L09_001B0F20*0.0002908882452175021f;
    *(float *)(vars+0x100)=0.7f;*(float *)(vars+0x104)=0.5f;*(float *)(vars+0x108)=0.5f;*(float *)(vars+0x10C)=1.0f;
    *(float *)(vars+0x110)=0.7853982448577881f;*(float *)(vars+0x130)=0.349065899848938f;
    *(float *)(vars+0x12C)=acceleration;
    SetControllerSpeedLimits(moby,first,second,third,fourth); }
    *(int *)(vars+0x138)|=0x80;*(int *)(vars+0x1DC)=0;*(float *)(vars+0x1D4)=3.0f;
    *(u16 *)(vars+0x1E4)=0;*(u16 *)(vars+0x1E2)=0;*(int *)(vars+0x1D0)=0;
    if(*(int *)(vars+0x2BC)!=-1)ComputePathSegmentLengths_L01(D_L09_001FE6C0[*(int *)(vars+0x2BC)]);
    if(*(int *)(vars+0x2B4)!=-1)ComputePathSegmentLengths_L01(D_L09_001FE6C0[*(int *)(vars+0x2B4)]);
    if(*(int *)(vars+0x2B8)!=-1)ComputePathSegmentLengths_L01(D_L09_001FE6C0[*(int *)(vars+0x2B8)]);
    torso=CreateMoby(0xD0E /* Megacorp Trooper Torso */);
    if(torso) {
        *(u8 **)(vars+0x2F8)=torso;*(u16 *)(torso+0x32)=*(u16 *)(moby+0x32);torso[0x30]=moby[0x30];
        *(u64 *)(torso+0x38)=*(u64 *)(moby+0x38);*(int *)(torso+0x78)=*(int *)(moby+0x78);torso[0x31]=1;
        *(float *)(torso+0x2C)*=D_L09_001B0F08;
        TransformMobyJointToWorld(moby,0,torso+0x10);qcopy(torso+0xF0,moby+0xF0);
        torsoVars=*(u8 **)(torso+0x68);*(InitBlock *)(torsoVars+0x20)=*(InitBlock *)(vars+0x20);
        *(float *)(torsoVars+0x20)=*(float *)(vars+0x20);*(u16 *)(torsoVars+0x24)=*(u16 *)(vars+0x24);torsoVars[0x28]=vars[0x28];
        torsoVars[0x2F]=stage;*(float *)(torsoVars+0x30)=0.7f;torsoVars[0x2A]=2;torsoVars[0x4D]=1;torsoVars[0x4A]=3;torsoVars[0x2E]=1;*(u8 **)(torsoVars+0x70)=moby;
        TransformMobyJointPoint(moby,0,transform);copy_matrix3x4(torso+0xC0,transform);
        func_002A0F48(torso);NormalizeMatrixColumns(torso+0xC0);func_002A10E8(torso);
        for(i=0;i<2;i++) {
            u8 *child;
            TransformMobyJointToWorld(*(u8 **)(vars+0x2F8),i,pos);FastVecSub(pos,pos,*(u8 **)(vars+0x2F8)+0x10);
            child=SpawnFlyingFragment(*(u8 **)(vars+0x2F8),0xD66 /* moby class 3430 */,pos,D_L09_001A8F20,0,0,D_L09_001A8F20,D_L09_001A8F20,D_L09_001A8F20,0);
            if(child && *(s16 *)(child+0xAA)==0xD66 /* moby class 3430 */ && child[0x20]!=254 && child[0x20]!=253) {
                *(u16 *)(child+0x32)=*(u16 *)(moby+0x32);*(u8 **)(vars+0x2F0+i*4)=child;*(u16 *)(child+0x34)|=2;
            }
        }
        parameters=torsoVars+0x50;
        for(j=0;j<10;j++)parameters[j]=D_L09_001B10D0[j];
        switch(Rand()%3) {
        case 0:parameters[4]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[8]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 1:parameters[5]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[9]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 2:parameters[7]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        }
        SpawnDamageDebrisOnHealthLoss(*(u8 **)(vars+0x2F8),torsoVars+0x50,torsoVars+0x20);{ u8 *partner=*(u8 **)(vars+0x2F8);*(u16 *)(partner+0x7C)&=0xFCFF; }
    }
    if(vars[0x302]&1) {
        vars[0x302]=(vars[0x302]|1)&0xFD;
        if(vars[0x31F]) {
            u8 *partner; u8 **slots; int k;
            moby[0x31]=0;*(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|1)&0xEFFF;
            partner=*(u8 **)(vars+0x2F8);
            if(partner && *(s16 *)(partner+0xAA)==0xD0E /* Megacorp Trooper Torso */ && partner[0x20]!=254 && partner[0x20]!=253) {
                *(u16 *)(partner+0x34)|=1;(*(u8 **)(vars+0x2F8))[0x31]=0;*(int *)(*(u8 **)(vars+0x2F8)+0x98)=0;*(u16 *)(*(u8 **)(vars+0x2F8)+0x34)&=0xEFFF;
            }
            slots=(u8 **)(vars+0x2F0);
            for(k=0;k<2;k++) {
                u8 *child=slots[k];
                if(child && *(s16 *)(child+0xAA)==0xD66 /* moby class 3430 */ && child[0x20]!=254 && child[0x20]!=253) {
                    *(u16 *)(child+0x34)|=1;slots[k][0x31]=0;
                }
            }
            vars[0x31C]=0;vars[0x31D]=1;*(u16 *)(moby+0x34)|=2;
        }
    }
    if(*(float *)(vars+0x4BC)<10.0f)*(float *)(vars+0x4BC)=D_L09_001B0F30;
    SelectEnemyPath(moby,*(int *)(vars+0x2B4),-1);ReleaseSharedCounter(moby);**(int **)(vars+0x304)=0;
    if(*(int *)(vars+0x2B0)!=-1) {
        *(int *)(vars+0x2DC)=*(int *)(vars+0x2B0);*(int *)(vars+0x138)|=4;SetMobyState(moby,1,1);
        if(ProbeGroundHeightBelow(moby+0x10,0,0.5f)<*(float *)(moby+0x18)-*(float *)(vars+0x10C)-0.1f)
            SetEnemyAnimationState(moby,2,0,RandomIntRange(5,10));
        else
            SetEnemyAnimationState(moby,13,0,RandomIntRange(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    } else {
        int state;SetMobyState(moby,5,1);state=Rand()&1;
        SetEnemyAnimationState(moby,state,0,RandomIntRange(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    }
}
