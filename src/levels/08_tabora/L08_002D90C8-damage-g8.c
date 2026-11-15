#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
extern char D_L08_001B9B00[], D_0019B4A8[];
extern char D_L08_001A8F20[] __attribute__((sda));
/* GCC 2.9 uses a zero-length tail for the variable-sized flag table. */
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021EAF0;
extern int D_001A79F0;
extern int D_L08_001A8F00 __attribute__((sda));
extern float D_L08_001B02F0 __attribute__((sda)), D_L08_001B02F4 __attribute__((sda)), D_L08_001B02F8 __attribute__((sda));
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *), func_0029F338(void *);
extern int func_002ACD38(void *),func_002F5D10(void);
extern float func_002A89A8(void *,int,float),func_002A7878(float,float),func_002A7940(void),func_00283CE0(int);
extern int func_00283CF0(float),func_002A7820(int,int);
extern void func_002A7750(void *,int,int),func_L08_003CC4B8(void *);
extern void *func_002A9640(void *,int,int);
extern float func_002A96A0(void *,void *);
extern void func_002AB800(void *,void *),func_002AB8C0(void *,void *),func_0029FCC0(void *,int,void *),func_002A7398(void *,int,int);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_L03_003268C0(void *,int,int,int,int,int,int,void *);
extern int func_002E5CF8(int,int,void *);
extern void *func_0029EFD0(int);
extern void func_002A0F48(void *),func_002AB650(void *),func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *),func_L08_0040F9D0(void *,void *,void *,float,float);
/* Applies damage, updates hit effects, and spawns debris when health reaches zero. */
void func_L08_003D2F50(char *o) {
    char *p=F(o,char *,0x68), *hit, *spawn, *health, *effect;
    float impact, z, angle, speed, t;
    int n, bits, sound;
    float at[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    if(F(o,u8,0x31) && fast_vec_dist(o+0x10,D_L08_001B9B00)<48.0f) {
        UpdateMobyGroundCheck(o); F(o,u8,0x6F)=45;
    }
    if(F(o,u8,0xB0)!=255) {
        unsigned short index=F(o,u16,0xB2);
        if(D_L08_0021EAF0.flags[(short)index]) {MarkMobySpawned(o);return;}
        bits=F(D_0019B4A8,u8,((short)index>>1)+(gCurrentMapIndex<<10));
        if((index&1) ? ((bits>>4)&7) : (bits&7)) {MarkMobySpawned(o);return;}
    }
    if(!IsObjectInSelectedZone(o+0x10)) return;
    if(D_L08_001A8F00==2) {F(o,u8,0x31)=0;F(o,u16,0x34)|=1;}
    else {F(o,u8,0x31)=1;F(o,u16,0x34)&=0xFFFE;}
    if(IsEitherModeTwo())return;
    if(!F(o,u8,0x20)) {
        z=ProbeGroundHeightBelow(o+0x10,0,0.5f);
        z-=RandomFloatRange(0.2f,0.7f);
        F(o,float,0x18)=z;
        SetMobyState(o,1,-1);
    }
    if(!p)return;
    if(F(o,u8,0x31))DrawGlowingSparkRings(o);
    health=p+0x20;effect=p+0x50;
    hit=FindOwnedEffectSlot(o,0x230000,0);
    impact=UpdateAimTargetStrength(o,hit);
    if(impact>0) {
        F(health,float,0)-=impact;
        F(effect,u8,7)=255;F(effect,u8,8)=255;F(effect,u8,9)=255;
        StartColorFade(o,effect);
        TransformMobyJointToWorld(o,0,at);
        StartAnimationImmediate(o,3,FloatToInt(IntToFloat(F(p,s16,0x24))-F(health,float,0))<16 ? FloatToInt(IntToFloat(F(p,s16,0x24))-F(health,float,0)) : 15);
        F(o,int,0x48)=0;
        z=F(o,float,0x48);
        SpawnExplosionEffects(o,D_L08_001A8F20,at,z,z,4,2,5,2,1,9,1,-1,z,0,0,-1,0,0x810001);
        SpawnEffectBurstFromObject(o,-1,0,0x96D,1,3,0,D_L08_001A8F20);
        sound=RandomIntRange(0,2);
        if(F(health,float,0)>z)PlayMobySound(sound,0,o);
    }
    F(o,u8,0xA8)=255;
    UpdateColorFade(o,effect);
    if(F(health,float,0)<=0) {
        qzero(at);at[2]=0.16666667f;
        if(hit)qcopy(target,hit);
        else {qcopy(target,o+0x10);target[2]+=2;}
        spawn=CreateMoby(0x8C4 /* moby class 2244 */);
        if(spawn) {
            F(spawn,u8,0x23)=80;F(spawn,u16,0x34)|=0x800;
            F(spawn,float,0x2C)=F(F(spawn,char *,0x24),float,0x24)*0.65f;
            F(spawn,u8,0x30)=255;F(spawn,u16,0x32)=255;
            F(spawn,u8,0x31)=1;F(spawn,u8,0x20)=0;
            F(spawn,u8,0xBC)=0;
            qcopy(spawn+0x10,o+0x10);
            func_002A0F48(spawn);CopyHeroField38ToMoby(spawn);
            F(F(spawn,char *,0x68),char *,4)=o;
            SpawnExplosionEffects(o,at,target,0,0,20,6,32,6,4,3,2,-1,20,1,3,-1,0,0x810001);
            SpawnEffectBurstFromObject(o,0x96D,3,0,0,0,0,D_L08_001A8F20);
            PlayMobySound(3,0,o);
            angle=RandomAngle();
            n=0;
            do {
                speed=D_L08_001B02F0*0.016666668f;
                t=RandomFloatRange(D_L08_001B02F4,D_L08_001B02F8);
                --n;
                BuildSphericalOffset(velocity,speed,angle,t*0.017453294f);
                angle+=2.0943954f;
                FastVecAdd(position,target,velocity);
                t=RandomFloatRange(1,10);
                z=RandomFloatRange(8,12);
                SpawnSpinningObject(o,position,velocity,t,z);
            }while(n>=0);
            MarkMobySpawned(o);
        }
    }
}
