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

/* Turns the stick input into smooth steering, pitch and banking values for the ridden vehicle,
   limited by its mode and by whether the boost button is held. */
/* Smooth the steering and orientation targets from the combined controls.
 * mode is 64-bit: its (zero_extend:DI (mem:QI)) differs from the (zero_extend:SI) of the first
 * test, so gcse keeps the second read of the field that retail has. */
void func_L08_003CD708(SteeringObject *vehicle,char *steer,float inputScale)
{
    u64 mode;

    float gain=D_L08_001B0028;
    float targetX,targetY,pitchBias=0.0f;
    float limit=D_L08_001B0038;
    float bankLimit,turnRate,turnStep;
    float magnitude;
    SteeringHero *hero;
    if (vehicle->mode==8) {
        limit=D_L08_001B0048;
        if (I(steer,0x50)==0) pitchBias=-2.0f;
    }
    targetX=(gPadState.x-gPadState.baseX+gPadState.z)*inputScale;
    targetY=(gPadState.y-gPadState.baseY+gPadState.baseZ+pitchBias)*inputScale;
    if (targetX>inputScale) targetX=inputScale;
    else if (targetX < -inputScale) targetX=-inputScale;
    if (targetY>inputScale) targetY=inputScale;
    else if (targetY < -inputScale) targetY=-inputScale;
    if (gPadState.flags&0x200) {
        targetX/=D_L08_001B0064;
        targetY/=D_L08_001B005C;
        targetX*=D_L08_001B006C;
        targetY*=D_L08_001B0068;
        gain=D_L08_001B002C;
        limit=D_L08_001B003C;
    }
    mode=vehicle->mode;
    if (mode==7 || mode<6) goto update_pitch;
    if (D_L08_001B001C) {
        if (mode!=8) {
            SpringFloatToGoal((float *)(steer+0x60),(float *)(steer+0x44),targetY,
                          D_L08_001B0030,D_L08_001B0034,limit);
            if (D_L08_001B0140)
                F(steer,0x14)=fast_subtract_rotations(F(steer,0x14),(F(steer,0x60)*0.0002908882452175021f)*D_L08_001B005C);
            bankLimit=D_L08_001B0004;
        } else {
            SpringFloatToGoal((float *)(steer+0x60),(float *)(steer+0x44),targetY,
                          D_L08_001B0040,D_L08_001B0044,limit);
            if (D_L08_001B0140)
                F(steer,0x14)=fast_subtract_rotations(F(steer,0x14),(F(steer,0x60)*0.0002908882452175021f)*D_L08_001B0060);
            bankLimit=D_L08_001B0008;
        }
        bankLimit*=0.01745329424738884f;
        if (F(steer,0x14)>bankLimit) F(steer,0x14)=bankLimit;
        else if (F(steer,0x14)<-bankLimit) F(steer,0x14)=-bankLimit;
    } else {
        hero=&gHeroState;
        magnitude=FloatAbs(hero->bank);
        if (magnitude<FloatAbs(F(steer,0x60)))
            ApproachValue((float *)(steer+0x60),-hero->bank,D_L08_001B0080);
        else F(steer,0x60)=-hero->bank;
        turnStep=(F(steer,0x60)*0.01745329424738884f)*D_L08_001B0074;
        if (FloatAbs(F(steer,0x60))>0.2f) {
            turnRate=fast_subtract_rotations(turnStep,F(steer,0x14));
            bankLimit=D_L08_001B0070*0.0002908882452175021f;
            if (turnRate>bankLimit) turnRate=bankLimit;
            else if (turnRate<-bankLimit) turnRate=-bankLimit;
            ApproachValue((float *)(steer+0x44),turnRate,
                         D_L08_001B0078*(gHeroState.tickScale*4.848137450608192e-06f));
            F(steer,0x14)=FastAddRotations(F(steer,0x14),F(steer,0x44));
        } else {
            ApproachWithVelocity((float *)(steer+0x14),0.0f,(float *)(steer+0x44),
                          0.010999999940395355f,0.3f,0.01454441249370575f,0);
        }
    }
update_pitch:
    SpringFloatToGoal((float *)(steer+0x5C),(float *)(steer+0x48),targetX,
                  D_L08_001B0020,D_L08_001B0024,gain);
    if (D_L08_001B0140)
        ApproachWithVelocity((float *)(steer+0x10),F(steer,0x5C)*D_L08_001B004C,
                      (float *)(steer+0x40),D_L08_001B0050,D_L08_001B0054,D_L08_001B0058,0);
    if (D_L08_001B0140)
        F(steer,0x18)=fast_subtract_rotations(F(steer,0x18),(F(steer,0x5C)*0.0002908882452175021f)*D_L08_001B0064);
}
