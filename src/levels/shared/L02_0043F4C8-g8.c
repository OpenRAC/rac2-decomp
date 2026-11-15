/* Hovering object: idle, launch and impact states.
   The hit counter is one macro-addressed word ($gp only in delay slots), the two
   spin ranges are (low, high) small-data pairs whose high halves take the macro
   form, and the player record is read through a pointer local. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int D_L02_001AEC78 MACRO_ADDR;
/* Two (low, high) spin-rate ranges in small data. */
extern float ref_L02_0043F4C8_1[] __attribute__((sda));
extern float ref_L02_0043F4C8_2[] __attribute__((sda));
extern float ref_L02_0043F4C8_3 __attribute__((sda));
extern float ref_L02_0043F4C8_4 __attribute__((sda));
extern float ref_L02_0043F4C8_5 __attribute__((sda));
extern u8 D_00189E20[];
extern u8 D_L02_001A8F20[] MACRO_ADDR;
extern float func_002A7940(void);
extern float func_002A78D8(float,float);
extern int func_002A77E0(int);
extern void func_002A7470(void *,int,int,int);
extern void func_002A7750(void *,int,int);
extern float func_00283B98(float,float);
extern float func_00283198(float);
extern void func_002833F0(void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_L00_003206B8(void *,int);
extern u8 *func_002A9640(void *,u32,int);
extern int func_002A7820(int,int);
extern void func_00282F20(void *,void *,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00283698(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern float func_00282C68(float,float,float);
extern int func_002761F8(void *,void *,int,void *,int);
extern int func_002B3868(void *);
extern int func_002E5CF8(int,int,char *);
extern void func_L01_002E1680(void *,void *,int,int,int,float,float,float);
extern int func_00282978(short *);
extern void func_00282C88(void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_002B0A68(char *,int,float *,u8,float,float,float,float);
extern void func_L00_00326110(void *,int,float);
extern void func_0029F338(void *);
extern void func_L02_0043FA98(void *);

/* Advance the hovering object's idle, launch and impact states. */
void func_L02_0043F4C8(u8 *object)
{
    Vector delta;
    /* The tilt input dies after 833F0. The later inverse has four rows. */
    union {
        struct { Vector angles; Vector rotation[3]; } tilt;
        Vector inverse[4];
    } workspace;
    Vector destination;
    u8 *effect=*(u8 **)(object+0x68);
    u8 *hit;
    int mode;
    switch(object[0x20]) {
    case 0:
        if(*(int *)(effect+0x40)) gHoveringObjectCount=gHoveringObjectCount-1;
        qcopy(effect,object+0x10);
        *(float *)(effect+0x10)=RandomAngle();
        *(float *)(effect+0x14)=RandomAngle();
        *(float *)(effect+0x18)=RandomSignedFloatRange(ref_L02_0043F4C8_1[0],ref_L02_0043F4C8_1[1])*0.00029088825f;
        *(float *)(effect+0x1C)=RandomSignedFloatRange(ref_L02_0043F4C8_2[0],ref_L02_0043F4C8_2[1])*0.00029088825f;
        *(int *)(effect+0x40)=0;
        *(float *)(effect+0x4C)=0.104719773f;
        object[0x40]=RandomIntBelow((*(u8 **)(*(u8 **)(object+0x24)+0x48))[0x10]);
        *(short *)(effect+0x48)=180;
        mode=RandomIntBelow(2)+1;
        if(object[0x43]!=mode) StartAnimationBlended(object,mode,0,5);
        SetMobyState(object,1,-1);
        break;
    case 1: {
        if(object[0x31]) {
            u8 *position=object+0x10;
            *(float *)(effect+0x10)=FastAddRotations(*(float *)(effect+0x10),*(float *)(effect+0x18));
            *(float *)(effect+0x14)=FastAddRotations(*(float *)(effect+0x14),*(float *)(effect+0x1C));
            *(float *)(object+0xF0)=ref_L02_0043F4C8_3*FastSinOrCosB(*(float *)(effect+0x10));
            *(float *)(object+0xF4)=ref_L02_0043F4C8_4*FastSinOrCosB(*(float *)(effect+0x14));
            workspace.tilt.angles.q=0;
            workspace.tilt.angles.f[0]=*(float *)(effect+0x10);
            workspace.tilt.angles.f[2]=*(float *)(effect+0x14);
            delta.q=workspace.tilt.angles.q;
            euler_rotation_basis(workspace.tilt.rotation,&delta);
            FastVecScale(position,&workspace.tilt.rotation[1],ref_L02_0043F4C8_5);
            FastVecAdd(position,position,effect);
        }
        if(*(short *)(effect+0x3E)) {
            u8 *player=gHeroState; if(*(u8 **)(player+0x33C)==object && *(int *)(player+0x340)) *(short *)(effect+0x3E)=2;
            if(*(short *)(effect+0x3E)==2) {
                *(float *)(effect+8)-=0.06666667f;
                if(*(int *)(effect+0x50) && IsPointInsideRecordVolume(object+0x10,*(int *)(effect+0x50))) SetMobyState(object,3,-1);
            }
        }
        if(*(int *)(effect+0x40)) break;
        hit=FindOwnedEffectSlot(object,0x4210000,0);
        if(!hit) break;
        {
        gHoveringObjectCount--;
        *(short *)(effect+0x4A)=RandomIntRange(30,60);
        qcopy(effect+0x20,hit+0x10);
        vec_scale_to_length(effect+0x20,effect+0x20,0.25f);
        FastVecSub(&delta,hit,object+0x10);
        matrix_from_basis_rows(workspace.inverse,object+0xC0);
        transform_vector(&delta,&delta,workspace.inverse);
        *(float *)(effect+0x30)=-(FastFloatHelperE(delta.f[2],-1.0f,1.0f)*0.069813184f);
        *(float *)(effect+0x34)=FastFloatHelperE(delta.f[1],-1.0f,1.0f)*0.052359886f;
        FastVecScale(&destination,effect+0x20,(float)*(short *)(effect+0x4A));
        FastVecAdd(&destination,object+0x10,&destination);
        if(CollLine(object+0x10,&destination,2,0,0)) *(short *)(effect+0x3C)=1;
        if(*(short *)(effect+0x3C)) SetMobyState(object,3,-1);
        else SetMobyState(object,2,-1);
        }
        break;
    }
    case 2:
        if(SetFirstPendingFlag(object)) PlayMobySound(0,0,object);
        delta.q=0; workspace.tilt.angles.q=0;
        delta.f[2]=0.06666667f;
        workspace.tilt.angles.f[2]=-0.5f;
        FastVecAdd(&workspace.tilt.angles,&workspace.tilt.angles,object+0x10);
        if(!RandomIntBelow(2)) SpawnSparkBurst_L01(&workspace.tilt.angles,&delta,1,0x40F0F0F0,1,0.0066666673f,0.9f,1.04f);
        *(float *)(object+0xF4)=FastAddRotations(*(float *)(object+0xF4),*(float *)(effect+0x30));
        *(float *)(object+0xF8)=FastAddRotations(*(float *)(object+0xF8),*(float *)(effect+0x34));
        FastVecAdd(object+0x10,object+0x10,effect+0x20);
        if(FastDecTimer((short *)(effect+0x4A))) SetMobyState(object,3,-1);
        break;
    case 3:
        if(*(short *)(effect+0x3C)) ClearVector128(effect+0x20);
        SpawnExplosionEffects(object,D_L02_001A8F20,object+0x10,0.0f,0.0f,10,5,15,0.0f,0.0f,9.0f,*(float *)(object+0x2C)*10.0f,-1,0.0f,0,0,-1,0,0x810001);
        SpawnDebrisForMaskedParts((char *)object,0x3FFF,(float *)(effect+0x20),255,3.0f,6.0f,3.0f,6.0f);
        SpawnScaledBolts(object,3,0.0f);
        PlayMobySound(1,0,object);
        MarkMobySpawned(object);
        return;
    }
    if(object[0x20]) PickEvasiveAnimationState(object);
}
