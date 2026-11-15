#include "common.h"
extern int D_L00_001AA374 __attribute__((sda));
extern int D_L00_001B19C8;
extern int D_L00_001B208C;
/* Retail updates this counter through GP, but reads/resets its absolute view. */
extern int ref_L00_0032A258_00 __attribute__((sda));
extern void func_L00_00326110(void *,int,float);
extern void func_0029F648(void *,int *,int *);
extern void func_002E5CF8(int,int,void *);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern void func_00283098(void *,void *,void *);
extern void *func_00273730(void *,int,int,int,void *,void *,void *,int,float,float);
extern void func_0026FEB8(void *);
extern char D_L00_001AA380[];
/* Breaks an object into flying pieces, one for each part, with random speed, size and lifetime. */
void func_L00_0032A258(unsigned char *object,float *range,float *scale,float *lifetime,int kinds,int sound,int skip,int flags,int mask,unsigned char alpha,void *callback)
{
    float velocity[4], life, size;
    int first,count,i;
    unsigned char *particle;
    if(D_L00_001AA374 != gFrameCounter_L00) {
        D_L00_001AA374=gFrameCounter_L00;
        D_L00_001B208C=0;
    }
    ref_L00_0032A258_00=D_L00_001B208C+1;
    if(!object) return;
    *(short *)(object+0x7c)=0;
    *(int *)(object+0x98)=0;
    if((flags ^ 1)&1) SpawnScaledBolts(object,1,0.0f);
    if(flags&16) SpawnScaledBolts(object,9,0.0f);
    else if(flags&32) SpawnScaledBolts(object,2,0.0f);
    GetMobyAnimationEntryCount(object,&first,&count);
    if(sound!=-1) PlayMobySound(sound,0,object);
    for(i=0;i<count;++i) {
        if(skip==i || (((mask>>i)^1)&1)) continue;
        life=RandomFloatRange(lifetime[0],lifetime[1]);
        size=RandomFloatRange(scale[0],scale[1]);
        if(flags&2) velocity[0]=RandomSignedFloatRange(range[0],range[4])*0.0166666675f;
        else velocity[0]=RandomFloatRange(range[0],range[4])*0.0166666675f;
        if(flags&4) velocity[1]=RandomSignedFloatRange(range[1],range[5])*0.0166666675f;
        else velocity[1]=RandomFloatRange(range[1],range[5])*0.0166666675f;
        velocity[2]=RandomFloatRange(range[2],range[6])*0.0166666675f;
        if(!(flags&8)) matrix_mul_vec3(velocity,velocity,object+0xc0);
        if((kinds>>i)&1)
            particle=CreateCameraMoby(object,2,*(short *)(object+0xaa),i,object+0x10,object+0xf0,velocity,alpha,size,life);
        else particle=CreateCameraMoby(object,1,*(short *)(object+0xaa),i,object+0x10,object+0xf0,velocity,alpha,size,life);
        if(particle) { if(callback) *(void **)(particle+0x64)=callback; }
        else STUB_printf(D_L00_001AA380);
    }
}
