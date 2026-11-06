/* func_PAL_L08_003D1540, the PAL copy of func_L08_003CD708: the same C, where the smoothing
 * rates are scaled by 1.44 and the limits by 1.2 for 50 Hz, and the angle constants change. */
#include "common.h"
typedef struct { unsigned char pad[0x108]; float x,y,z,baseX,baseY,baseZ; unsigned char gap[0x80]; int flags; } SteeringInputs;
extern SteeringInputs D_00138180;
typedef struct { unsigned char pad[0x1FB4]; float bank; unsigned char gap[0x24B8-0x1FB8]; float tickScale; } SteeringHero;
extern SteeringHero D_00189E20;
extern int D_L08_001B001C __attribute__((sda)),D_L08_001B0140 __attribute__((sda));
extern float D_L08_001B0004 __attribute__((sda));
extern float D_L08_001B0008 __attribute__((sda));
extern float D_L08_001B0020 __attribute__((sda));
extern float D_L08_001B0024 __attribute__((sda));
extern float D_L08_001B0028 __attribute__((sda));
extern float D_L08_001B002C __attribute__((sda));
extern float D_L08_001B0030 __attribute__((sda));
extern float D_L08_001B0034 __attribute__((sda));
extern float D_L08_001B0038 __attribute__((sda));
extern float D_L08_001B003C __attribute__((sda));
extern float D_L08_001B0040 __attribute__((sda));
extern float D_L08_001B0044 __attribute__((sda));
extern float D_L08_001B0048 __attribute__((sda));
extern float D_L08_001B004C __attribute__((sda));
extern float D_L08_001B0050 __attribute__((sda));
extern float D_L08_001B0054 __attribute__((sda));
extern float D_L08_001B0058 __attribute__((sda));
extern float D_L08_001B005C __attribute__((sda));
extern float D_L08_001B0060 __attribute__((sda));
extern float D_L08_001B0064 __attribute__((sda));
extern float D_L08_001B0068 __attribute__((sda));
extern float D_L08_001B006C __attribute__((sda));
extern float D_L08_001B0070 __attribute__((sda));
extern float D_L08_001B0074 __attribute__((sda));
extern float D_L08_001B0078 __attribute__((sda));
extern float D_L08_001B0080 __attribute__((sda));
extern float func_002AA3A8(float *,float *,float,float,float,float);
extern float func_002AA2E8(float *,float,float);
extern float func_002AA898(float *,float,float *,float,float,float,int);
extern float func_00283BE0(float,float),func_00283B98(float,float),func_00282C48(float);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))

typedef struct { unsigned char pad[0x20]; unsigned char mode; } SteeringObject;

/* Smooth the steering and orientation targets from the combined controls.
 * mode is 64-bit: its (zero_extend:DI (mem:QI)) differs from the (zero_extend:SI) of the first
 * test, so gcse keeps the second read of the field that retail has. */
void func_PAL_L08_003D1540(SteeringObject *object,char *state,float inputScale)
{
    u64 mode;

    float gain=D_L08_001B0028;
    float targetX,targetY,bias=0.0f;
    float limit=D_L08_001B0038;
    float bound,value,step;
    float magnitude;
    SteeringHero *hero;
    if (object->mode==8) {
        limit=D_L08_001B0048;
        if (I(state,0x50)==0) bias=-2.0f;
    }
    targetX=(D_00138180.x-D_00138180.baseX+D_00138180.z)*inputScale;
    targetY=(D_00138180.y-D_00138180.baseY+D_00138180.baseZ+bias)*inputScale;
    if (targetX>inputScale) targetX=inputScale;
    else if (targetX < -inputScale) targetX=-inputScale;
    if (targetY>inputScale) targetY=inputScale;
    else if (targetY < -inputScale) targetY=-inputScale;
    if (D_00138180.flags&0x200) {
        targetX/=D_L08_001B0064;
        targetY/=D_L08_001B005C;
        targetX*=D_L08_001B006C;
        targetY*=D_L08_001B0068;
        gain=D_L08_001B002C;
        limit=D_L08_001B003C;
    }
    mode=object->mode;
    if (mode==7 || mode<6) goto update_pitch;
    if (D_L08_001B001C) {
        if (mode!=8) {
            func_002AA3A8((float *)(state+0x60),(float *)(state+0x44),targetY,
                          D_L08_001B0030*1.44f,D_L08_001B0034*1.44f,limit*1.2f);
            if (D_L08_001B0140)
                F(state,0x14)=func_00283BE0(F(state,0x14),(F(state,0x60)*0.0003490659f)*D_L08_001B005C);
            bound=D_L08_001B0004;
        } else {
            func_002AA3A8((float *)(state+0x60),(float *)(state+0x44),targetY,
                          D_L08_001B0040*1.44f,D_L08_001B0044*1.44f,limit*1.2f);
            if (D_L08_001B0140)
                F(state,0x14)=func_00283BE0(F(state,0x14),(F(state,0x60)*0.0003490659f)*D_L08_001B0060);
            bound=D_L08_001B0008;
        }
        bound*=0.01745329424738884f;
        if (F(state,0x14)>bound) F(state,0x14)=bound;
        else if (F(state,0x14)<-bound) F(state,0x14)=-bound;
    } else {
        hero=&D_00189E20;
        magnitude=func_00282C48(hero->bank);
        if (magnitude<func_00282C48(F(state,0x60)))
            func_002AA2E8((float *)(state+0x60),-hero->bank,D_L08_001B0080*1.44f);
        else F(state,0x60)=-hero->bank;
        step=(F(state,0x60)*0.01745329424738884f)*D_L08_001B0074;
        if (func_00282C48(F(state,0x60))>0.2f) {
            value=func_00283BE0(step,F(state,0x14));
            bound=D_L08_001B0070*0.0003490659f;
            if (value>bound) value=bound;
            else if (value<-bound) value=-bound;
            func_002AA2E8((float *)(state+0x44),value,
                         D_L08_001B0078*(D_00189E20.tickScale*6.981318e-06f));
            F(state,0x14)=func_00283B98(F(state,0x14),F(state,0x44));
        } else {
            func_002AA898((float *)(state+0x14),0.0f,(float *)(state+0x44),
                          0.015840001f,0.43200004f,0.01745329424738884f,0);
        }
    }
update_pitch:
    func_002AA3A8((float *)(state+0x5C),(float *)(state+0x48),targetX,
                  D_L08_001B0020*1.44f,D_L08_001B0024*1.44f,gain*1.2f);
    if (D_L08_001B0140)
        func_002AA898((float *)(state+0x10),F(state,0x5C)*D_L08_001B004C,
                      (float *)(state+0x40),D_L08_001B0050*1.44f,D_L08_001B0054*1.44f,D_L08_001B0058*1.2f,0);
    if (D_L08_001B0140)
        F(state,0x18)=func_00283BE0(F(state,0x18),(F(state,0x5C)*0.0003490659f)*D_L08_001B0064);
}
