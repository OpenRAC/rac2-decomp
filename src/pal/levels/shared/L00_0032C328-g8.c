#include "include_asm.h"

#include "common.h"
extern int D_L00_001AA374 __attribute__((sda));
extern int D_L00_001B19C8;
extern int D_L00_001B208C;
extern int ref_L00_0032A258_00 __attribute__((sda));
extern void func_PAL_L00_003281C0(void *,int,float);
extern void func_0029F648(void *,int *,int *);
extern void func_002E5CF8(int,int,void *);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern void func_00283098(void *,void *,void *);
extern void *func_PAL_002735D0(void *,int,int,int,void *,void *,void *,int,float,float);
extern void func_0026FEB8(void *);
extern char D_L00_001AA380[];

void func_PAL_L00_0032C328(unsigned char *object,float *range,float *scale,float *lifetime,int kinds,int sound,int skip,int flags,int mask,unsigned char alpha,void *callback)
{
    float velocity[4], life, size;
    int first,count,i;
    unsigned char *particle;
    if(D_L00_001AA374 != D_L00_001B19C8) {
        D_L00_001AA374=D_L00_001B19C8;
        D_L00_001B208C=0;
    }
    ref_L00_0032A258_00=D_L00_001B208C+1;
    if(!object) return;
    *(short *)(object+0x7c)=0;
    *(int *)(object+0x98)=0;
    if((flags ^ 1)&1) func_PAL_L00_003281C0(object,1,0.0f);
    if(flags&16) func_PAL_L00_003281C0(object,9,0.0f);
    else if(flags&32) func_PAL_L00_003281C0(object,2,0.0f);
    func_0029F648(object,&first,&count);
    if(sound!=-1) func_002E5CF8(sound,0,object);
    for(i=0;i<count;++i) {
        if(skip==i || (((mask>>i)^1)&1)) continue;
        life=func_002A7878(lifetime[0],lifetime[1]);
        size=func_002A7878(scale[0],scale[1]);
        if(flags&2) velocity[0]=func_002A78D8(range[0],range[4])*0.020000001f;
        else velocity[0]=func_002A7878(range[0],range[4])*0.020000001f;
        if(flags&4) velocity[1]=func_002A78D8(range[1],range[5])*0.020000001f;
        else velocity[1]=func_002A7878(range[1],range[5])*0.020000001f;
        velocity[2]=func_002A7878(range[2],range[6])*0.020000001f;
        if(!(flags&8)) func_00283098(velocity,velocity,object+0xc0);
        if((kinds>>i)&1)
            particle=func_PAL_002735D0(object,2,*(short *)(object+0xaa),i,object+0x10,object+0xf0,velocity,alpha,size,life);
        else particle=func_PAL_002735D0(object,1,*(short *)(object+0xaa),i,object+0x10,object+0xf0,velocity,alpha,size,life);
        if(particle) { if(callback) *(void **)(particle+0x64)=callback; }
        else func_0026FEB8(D_L00_001AA380);
    }
}
