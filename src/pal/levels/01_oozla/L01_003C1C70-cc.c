/* func_PAL_L01_003C1C70, the PAL copy of func_L01_003BE058: the same C, where lit 0.0008726647356525064f becomes 0.0012566373f; lit 0.0008726647356525064f becomes 0.0012566373f. */
#include "common.h"

#define I32(p,o) (*(int *)((p)+(o)))
#define F32(p,o) (*(float *)((p)+(o)))
extern float func_00283248(float,float),func_00282E20(void *),func_00282E80(void *,void *);
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *);
struct family_27f9_object;
extern float func_002A7CA0(struct family_27f9_object *,float,float *,float,float,float);
extern float func_00283180(float),func_00283198(float);
extern float func_L01_003BD560(void *,float,float,float,float);
extern float D_00189EA0[];
/* Scalar view of D_00189EA0[2] (its z): retail addresses it on its own. */
extern float D_00189EA8;
extern void func_002AF000(float *,float,float,float);
extern int func_002A8240(void *,void *,int,float,float,float);
extern float func_L01_00310BC0(float *,float,float,float,float,float);
extern int func_L01_003165E8(void *,int,int,int,int);
static __inline__ float ScaleAcceleration(float acceleration, float distance)
{
    return acceleration * distance;
}

int func_PAL_L01_003C1C70(u8 *object,float turn,float turn2,float rate,float acceleration,float brake,float maxspeed,float altitude,float deadzone)
{
    u8 *state=*(u8 **)(object+0x68);
    float direction[4] __attribute__((aligned(16)));
    float proposed[4] __attribute__((aligned(16)));
    float angle, distance, step, cap, limit, pitch, height;
    int flags=0;
    angle=func_00283248(F32(state,0x1e0)-F32(object,0x10),F32(state,0x1e4)-F32(object,0x14));
    func_00282CF0(direction,state+0x1e0,object+0x10);
    distance=func_00282E20(direction)-deadzone;
    if(distance<0.0f) distance=0.0f;
    cap=ScaleAcceleration(acceleration,0.00040000002f);
    step=ScaleAcceleration(acceleration,distance*0.00040000002f);
    if(cap<step) step=cap;
    F32(state,0x240)+=step;
    if(distance<F32(state,0x240)*10.0f)
        F32(state,0x240)-=brake*F32(state,0x240);
    if(distance<deadzone) flags=8;
    limit=maxspeed*F32(state,0x28c)*0.020000001f;
    if(limit<F32(state,0x240)) F32(state,0x240)=limit;
    else if(F32(state,0x240)<-limit) F32(state,0x240)=-limit;
    func_002A7CA0((struct family_27f9_object *)object,angle,(float *)(state+0x244),
        turn*6.981318e-06f,turn2*6.981318e-06f,rate*0.0003490659f);
    proposed[0]=func_00283180(angle)*F32(state,0x240)*10.0f;
    proposed[1]=func_00283198(angle)*F32(state,0x240)*10.0f;
    proposed[2]=0.0f;
    func_00282CC0(proposed,proposed,object+0x10);
    height=F32(state,0x27c);
    if(object[0x20]==8) height = height > D_00189EA8 ? height : D_00189EA8;
    proposed[2]=func_L01_003BD560(proposed,F32(state,0x1d8)+2.0f,F32(state,0x1d8)-3.0f,height,F32(state,0x288));
    if(func_00282E80(object+0x10,D_00189EA0)<5.0f && D_00189EA0[2]<proposed[2]) proposed[2]=D_00189EA0[2];
    proposed[2]+=altitude;
    pitch=func_00283248(func_00282E80(object+0x10,proposed),proposed[2]-F32(object,0x18));
    func_002AF000((float *)(state+0x1f0),F32(state,0x240),F32(object,0xf8),pitch);
    if(object[0x20]!=8) F32(state,0x1f8)*=0.4f;
    else if((unsigned int)(object[0x95]-1)<2) {
        I32(state,0x1f0)=0;
        I32(state,0x1f4)=0;
    }
    flags|=func_002A8240(object,state+0x1f0,0,0.0f,0.3f,0.0f);
    F32(object,0xf4)=func_L01_00310BC0((float *)(state+0x248),F32(object,0xf4),-pitch,
        0.0025132746f,0.0012566373f,0.0012566373f);
    if(I32(state,0x238)>0 && func_L01_003165E8((char *)(object+0x10),I32(state,0x210),I32(state,0x218),I32(state,0x21c),-1)==0) flags|=7;
    if(flags&7) func_002A7CA0((struct family_27f9_object *)object,angle,(float *)(state+0x244),
        turn*2.0943955e-05f,turn2*6.981318e-06f,rate*0.0010471977f);
    return flags;
}
