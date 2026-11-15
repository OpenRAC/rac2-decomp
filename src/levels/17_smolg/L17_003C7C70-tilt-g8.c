#include "common.h"

/* func_L17_003C7C70 has a unit of its own: it needs -G8 for its $gp tuning values and -g,
   which gives the nop pairs retail has before each division, and its jump table is this
   unit's only .rodata. */

/* The tuning value the first rate divides by is read-only here: as const its load carries no
   anti-dependences on the flag stores, so sched1 issues it after the 360.0f numerator, which
   lengthens that constant's life and leaves $f20 to the scale constant, as in retail. */
extern const float D_L17_001B03B4 __attribute__((sda));
extern float D_L17_001B03B8 __attribute__((sda));
extern float D_L17_001B03BC __attribute__((sda));
extern float D_L17_001B03C0 __attribute__((sda));
extern float D_L17_001B03C4 __attribute__((sda));
extern float D_L17_001B03C8 __attribute__((sda));
extern float D_L17_001B03CC __attribute__((sda));
extern float D_L17_001B03D0 __attribute__((sda));
extern float D_L17_001B03D4 __attribute__((sda));
extern float D_L17_001B03D8 __attribute__((sda));
extern void func_002AEE70(void *,void *,void *,float,float,float),func_002AEF28(void *,void *,void *,float,float,float);
extern int func_L00_00324120(void *),func_002B3868(void *),func_00282948(void *),func_00283CF0(float);
extern void func_002A7750(void *,int,int),func_002E5CF8(int,int,void *);
extern float func_00283CE0(int),func_002ABB18(float),func_00283198(float),func_00283180(float),func_00283B98(float,float),func_00283C28(float);
extern void func_00282CF0(void *,void *,void *),func_002AD6F0(void *,void *,void *,void *);
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } UpdateVector;
typedef struct {
    u8 pad00[0x3e];
    u16 flags3e;
    u8 pad40[0x4c];
    int flags8c;
    UpdateVector origin;
    float a0, a4, a8, ac;
    int b0, b4, b8;
} UpdateState;
typedef struct {
    u8 pad00[0x10];
    UpdateVector position;
    u8 mode;
    u8 pad21[0x13];
    u16 flags34;
    u8 pad36[0x32];
    UpdateState *state;
    u8 pad6c[0x84];
    UpdateVector rotation;
} UpdateObject;
/* Moves a tilting platform: it waits for a trigger, wobbles, tips over along an arc, then
   swings back up to where it started (moby class 2359). */
void func_L17_003C7C70(UpdateObject *moby)
{
    float oldpos[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    UpdateState *vars;
    float first_rate;
    float rate_scale = 0.000290888245f;
    first_rate=360.0f/D_L17_001B03B4;
    *(Quad *)oldpos=moby->position.q;
    *(Quad *)oldrot=moby->rotation.q;
    vars=moby->state;
    vars->flags8c|=1;
    vars->flags3e|=8;
    moby->flags34|=0x20;
    UpdateWrappedAngleOffset(moby,&vars->a0,&vars->a4,D_L17_001B03B8,first_rate*rate_scale,-1.0f);
    ScaleOwnerWordsByAngles(moby,&vars->a8,&vars->ac,D_L17_001B03BC,(360.0f/D_L17_001B03C0)*rate_scale,(360.0f/D_L17_001B03C4)*rate_scale);
    switch(moby->mode) {
    case 0:
        vars->origin.q=*(Quad *)oldpos;
        moby->mode=1;
        break;
    case 1:
        if(IsCurrentSelectedId(moby)) {
            SetMobyState(moby,2,-1);
            vars->b0=FloatToInt(D_L17_001B03C8*60.0f);
        }
        break;
    case 2: {
        float progress;
        if(SetFirstPendingFlag(moby))PlayMobySound(0,0,moby);
        if(vars->b0==60)PlayMobySound(0,0,moby);
        if(FastFloatHelperD(&vars->b0)) {
            vars->b4=FloatToInt(D_L17_001B03CC*60.0f);
            moby->mode=3;
        } else {
            rot[0]=FastSinOrCosB(WrapAngleToPi(IntToFloat(vars->b0)*0.75f))*0.017453294f;
            rot[1]=FastSinOrCosA(WrapAngleToPi(IntToFloat(vars->b0)*0.89f))*0.017453294f;
            if((float)vars->b4>D_L17_001B03C8*60.0f-30.0f) {
                progress=IntToFloat(vars->b0)/(D_L17_001B03C8*60.0f-30.0f);
                moby->rotation.f[0]=moby->rotation.f[0]*progress+rot[0]*(1.0f-progress);
                moby->rotation.f[1]=moby->rotation.f[1]*progress+rot[1]*(1.0f-progress);
            } else {
                moby->rotation.f[1]=rot[1];
                moby->rotation.f[0]=rot[0];
            }
        }
        break;
    }
    case 3: {
        float progress,f,b,ax,ay;
        progress=IntToFloat(vars->b4)/(D_L17_001B03CC*60.0f);
        f=(1.0f-progress)*D_L17_001B03D4;
        moby->rotation.f[1]=0;
        moby->rotation.f[0]=(1.0f-progress)*1.57079649f;
        ax=FastSinOrCosA(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=FastSinOrCosB(moby->rotation.f[0]);
        ax*=f*b;
        moby->position.f[0]=ax;
        ay=FastSinOrCosB(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=FastSinOrCosB(moby->rotation.f[0]);
        ay*=f*b;
        moby->position.f[1]=ay;
        moby->position.f[2]=0;
        moby->position.f[0]+=vars->origin.f[0];
        ay+=vars->origin.f[1];
        moby->position.f[1]=ay;
        f*=FastSinOrCosA(moby->rotation.f[0]);
        moby->position.f[2]=vars->origin.f[2]-f;
        moby->position.f[2]-=FastSinOrCosA(progress*1.57079649f)*D_L17_001B03D8;
        vars->flags8c&=~1;
        vars->flags3e&=~8;
        moby->flags34&=~0x20;
        if(FastFloatHelperD(&vars->b4)) {
            moby->mode=4;
            vars->b8=FloatToInt(D_L17_001B03D0*60.0f);
        }
        break;
    }
    case 4: {
        float progress,f,b,c,ax,ay;
        progress=IntToFloat(vars->b8)/(D_L17_001B03D0*60.0f);
        *(Quad *)rot=moby->rotation.q;
        c=1.0f-progress;
        f=(1.0f-c)*D_L17_001B03D4;
        moby->rotation.f[0]=FastFloatHelperG((rot[0]*c+c*4.71238947f)+1.57079649f);
        moby->rotation.f[1]=rot[1]*c;
        ax=FastSinOrCosA(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=FastSinOrCosB(moby->rotation.f[0]);
        ax*=f*b;
        moby->position.f[0]=ax;
        ay=FastSinOrCosB(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=FastSinOrCosB(moby->rotation.f[0]);
        ay*=f*b;
        moby->position.f[1]=ay;
        moby->position.f[2]=0;
        moby->position.f[0]+=vars->origin.f[0];
        ay+=vars->origin.f[1];
        moby->position.f[1]=ay;
        f*=FastSinOrCosA(moby->rotation.f[0]);
        moby->position.f[2]=vars->origin.f[2]-f;
        moby->position.f[2]-=FastSinOrCosA(c*1.57079649f)*D_L17_001B03D8;
        vars->flags8c&=~1;
        vars->flags3e&=~8;
        moby->flags34&=~0x20;
        if(FastFloatHelperD(&vars->b8)) {
            moby->mode=1;
            {
                Quad home = vars->origin.q;
                moby->rotation.q=*(Quad *)rot;
                moby->position.q=home;
            }
        }
        break;
    }
    }
    if(moby->mode<3) {
        FastVecSub(pos,&moby->position,oldpos);
        CombineTransformsAndStore((u8 *)vars+0x50,pos,oldrot,&moby->rotation);
    }
}
