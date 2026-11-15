/* func_L11_004580E8 (2,476 bytes, Joba level 11 only). Own unit:
 * -O2 -G8 -ffunction-sections -g -frac2-sched-call-addr-float -frac2-la-float-vars-last
 * (config/cflags.txt). Case 0 stores its floats in retail's order (0x4C gravity, then 0x20,
 * 0x28, 0x2C, 0x30, 0x50 limit, 0x54 0.1f). -frac2-sched-call-addr-float keeps a call's
 * address MEM from depending on pending FP stores (case 5's store order);
 * -frac2-la-float-vars-last allocates FP user variables after temporaries in local-alloc, so
 * 0.1 takes $f0 before gravity and limit (case 0), as retail (docs/build/compiler-notes.md).
 * Owner standard of 12 November 2026; forced on everywhere they change 136 and 436 functions.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int func_00283CF0(float);
extern float func_00283CE0(int),func_002A7878(float,float),func_00282E20(void *),func_00283B98(float,float),func_L02_002F21C0(void *,void *);
extern int func_002A77E0(int),func_002761F8(void *,void *,int,void *,int),func_00277258(void *,int,void *,float),func_002B3868(void *),func_00282948(void *),func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern void *func_002A9640(void *,unsigned int,int);
extern int func_002B4FF0(void *,void *,float);
extern float func_002AA548(void *,void *,float,float,float,float);
extern int func_00282978(void *);
extern void func_002A7750(void *,int,int),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float),func_00282D30(void *,void *,float),func_00283028(void *,void *,void *),func_L00_0031D670(void *,void *,void *,float),func_002E59F8(int),func_002A8BD0(void *,void *,int,float);
extern void func_L00_002E6EF8(void (*)(void *),void *);
extern int func_00277F48(float,void *,int,void *,void *);
typedef struct { int unused; int mode; short unused8; u8 alpha, duration; } ParticleAttributes;
typedef struct { char unused[10]; s16 lifetime; char unused12[20]; ParticleAttributes attributes; } Particle;
extern Particle *func_002BDCE8(void *,int,float,float,float,void *,unsigned,int,float);
extern char *func_L11_004417E8(void *);
extern char *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void func_002B60B0(void *,float,float,float,float);
extern void func_L11_00458C38(void *);
typedef struct { char pad0[0x18]; char *hit; int count; float point[4]; float pad30[4]; float normal[4]; } Collision;
extern Collision D_L11_001C0D00;
extern char D_00188660[];
/* Whether the moby hit belongs to the same class as this one's owner. */
static inline int func_IsOwnerClass(char *hit,char *vars) {
 int same=0;
 if(hit && *(char **)(vars+0x15C))same=*(s16 *)(hit+0xAA)==*(s16 *)(*(char **)(vars+0x15C)+0xAA);
 return same;
}
extern Quad D_L11_001A8F20;
extern float D_L11_001B1F80 SDATA(D_L11_001B1F80);
extern float D_L11_001B1F88 SDATA(D_L11_001B1F88);
extern float D_L11_001B1F8C SDATA(D_L11_001B1F8C);
extern float D_L11_001B1F94 SDATA(D_L11_001B1F94);
extern float D_L11_001B1F98 SDATA(D_L11_001B1F98);
extern float D_L11_001B1FA8 SDATA(D_L11_001B1FA8);
extern float D_L11_001B1FAC SDATA(D_L11_001B1FAC);
extern float D_L11_001B1F9C SDATA(D_L11_001B1F9C);
extern int D_L11_001B1F84 SDATA(D_L11_001B1F84);
extern int D_L11_001B1F90 SDATA(D_L11_001B1F90);
extern int D_L11_001B1FA4 SDATA(D_L11_001B1FA4);
typedef struct { float x,y,z; } FadeColor;
extern FadeColor D_L11_001B1FB0;
/* Per-frame update of a flying shot (moby class 3616): it bounces off walls, fades its colour, explodes with damage when done, and drops out if it falls below the floor. */
void func_L11_004580E8(char *moby) {
 char *vars=*(char **)(moby+0x68),*other,*entry;
 union { struct { float a[4],b[4],c[4]; } v; char damage[48]; } scratch;
 float f; int i,n; unsigned int r,g,blue;
 switch(*(u8 *)(moby+0x20)) {
 case 0: {
  *(u8 *)(vars+0x148)=FloatToInt(15);*(u8 *)(vars+0x14A)=FloatToInt(4);
  {float speed, max, damping, turn, gravity, limit;
  *(float *)(vars+0x160)=RandomFloatRange(-*(float *)(vars+0x160),*(float *)(vars+0x160))*0.017453294f;
  *(u8 *)(moby+0x30)=128;*(int *)(vars+0x24)=0;
  speed=0.3f;max=0.75f;damping=0.5f;turn=1.134464144706726f;gravity=0.0027777778450399637f;limit=0.523598849773407f;
  *(u8 *)(vars+0x128)=3;*(int *)(vars+0x130)=0;
  *(float *)(vars+0x4C)=gravity;
  *(float *)(vars+0x20)=speed;*(float *)(vars+0x28)=max;*(float *)(vars+0x2C)=damping;*(float *)(vars+0x30)=turn;*(float *)(vars+0x50)=limit;*(float *)(vars+0x54)=0.1f;
  *(int *)(vars+0x58)|=0x14;*(float *)(moby+0x2C)*=D_L11_001B1F88;*(int *)(vars+0x170)=-1;
  *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)&0xEFFF)|0x41;*(int *)(moby+0x98)=0;
  }
  SetMobyState(moby,1,-1);return;
 }
 case 2:case 3:
  FastVecAdd(scratch.v.a,moby+0x10,vars+0xC0);
  *(float *)(vars+0xC8)-=*(float *)(vars+0x4C);
  if(*(u8 *)(moby+0x20)==3 && *(float *)(vars+0xC8)<0) *(u8 *)(moby+0x20)=2;
  FastDecTimer(vars+0x16C);
  if(*(s16 *)(vars+0x16C)) {
   Quad *axis=&D_L11_001A8F20;
   for(i=0;i<3;i++) {
    *(Quad *)scratch.v.c=*(Quad *)(moby+0x10);LerpVector4(scratch.v.b,scratch.v.c,scratch.v.a,(float)i*0.3333f);
    n=RandomIntBelow(6);if(RandomIntBelow(2))n=-n;
    f=IntToFloat(D_L11_001B1F84);
    {
    int life=120,mode=2,alpha=127;
    float scale=45000;
    Particle *particle=SpawnSpinningSparkParticle(scratch.v.b,n,0.025f,1,1,axis,0x80808080,0,
      ({float lifetime=(float)*(s16 *)(vars+0x16C)/f;
        lifetime*scale+5000;}));
    if(particle) {ParticleAttributes *attributes;particle->lifetime=life;attributes=&particle->attributes;attributes->mode=mode;attributes->alpha=alpha;attributes->duration=(u8)particle->lifetime;}
    }
   }
  }
  if(CollLine(moby+0x10,scratch.v.a,0,moby,0) && !func_IsOwnerClass(D_L11_001C0D00.hit,vars)) qcopy(moby+0x10,D_L11_001C0D00.point);
  else qcopy(moby+0x10,scratch.v.a);
  if(!TestPointAgainstCollision(moby+0x10,0,moby,D_L11_001B1F80))break;
  if(*(u8 *)(moby+0x20)!=2) {Collision *col=&D_L11_001C0D00;if(!(*(float *)(moby+0x18)-col->point[2]<0))break;}
  {Collision *col=&D_L11_001C0D00;
  if(func_IsOwnerClass(col->hit,vars))break;}
  vec_scale_to_length(scratch.v.b,D_L11_001C0D00.normal,D_L11_001B1F80);
  FastVecAdd(moby+0x10,D_L11_001C0D00.point,scratch.v.b);
  FastVectorNormalize(vars+0xC0,vars+0xC0,D_L11_001C0D00.normal);
  PlayMobySound(1,0,moby);
  if(*(u8 *)(moby+0x20)==2) {float bounce;*(u8 *)(moby+0x20)=3;bounce=D_L11_001B1F8C;(*(u16 *)(vars+0x16E))++;FastVecScale(vars+0xC0,vars+0xC0,bounce);}
  if(*(s16 *)(vars+0x16E)>=D_L11_001B1F90) *(u8 *)(moby+0x20)=5;
  break;
 case 4: {
  float f;
  if(SetFirstPendingFlag(moby)){int duration=D_L11_001B1FA4;*(int *)(vars+0x150)=duration;*(float *)(vars+0x154)=1/IntToFloat(duration);}
  *(FadeColor *)scratch.v.a=D_L11_001B1FB0;
  f=(float)*(int *)(vars+0x150)**(float *)(vars+0x154);
  r=FloatToInt((scratch.v.a[0]-255)*f+255);g=FloatToInt(scratch.v.a[1]*f);blue=FloatToInt(scratch.v.a[2]*f);
  {unsigned int color=blue<<16;
  color|=0xFF000000;
  color|=g<<8;
  color|=r;
  *(unsigned int *)(moby+0x78)=color;}
  if(FastFloatHelperD(vars+0x150))SetMobyState(moby,6,-1);
  break;
 }
 case 5: {
  float f,t;
  if(SetFirstPendingFlag(moby)) {
   moby[0xBC]=0;f=RandomFloatRange(15,40)*0.017453294f;if(RandomIntBelow(2))f=-f;
   t=D_L11_001B1F98;
   *(float *)(vars+0x160)=f;SetControllerSpeedLimits(moby,(t+t)*0.00027777778450399637f,t*0.01666666753590107f,0.0011635529808700085f,0.10471977293491364f);
  } else if(!*(u8 *)(moby+0xBC)) {
   other=GetArenaCenterPoint(*(void **)(moby+0xB8));
   if(*(float *)(moby+0x18)<*(float *)(other+8)+D_L11_001B1F94) {
    float *height=(float *)(moby+0x18);
    other=GetArenaCenterPoint(*(void **)(moby+0xB8));
    StepValueTowardTarget(height,vars+0xC8,*(float *)(other+8)+D_L11_001B1F94,*(float *)(vars+0x40),*(float *)(vars+0x40),*(float *)(vars+0x48));
   }else moby[0xBC]=1;
  }else if(*(u8 *)(moby+0xBC)==1) {
   if(*(u8 *)(moby+0x31))TurnTowardTargetAndStepMovement(moby,*(char **)(vars+0x164)+16,*(float *)(vars+0x160));
   other=GetArenaCenterPoint(*(void **)(moby+0xB8));*(float *)(moby+0x18)=*(float *)(other+8)+D_L11_001B1F94;
   if(*(u8 *)(moby+0x31)) {f=DistanceSquaredXY(moby+0x10,*(char **)(vars+0x164)+16);if(f<D_L11_001B1F9C*D_L11_001B1F9C)SetMobyState(moby,4,-1);}
  }
  if(!IsVoicePlayingForOwner(moby,*(int *)(vars+0x170))) *(int *)(vars+0x170)=PlayMobySound(2,4,moby);
  break;
 }
 case 6:
  if(SetFirstPendingFlag(moby)) {
   SpawnExplosion(moby+16,1,10,10,2,20,60,1,D_L11_001B1FA8,0,1,1,0,0);
   PlayMobySound(0,0,moby);InitEffectRecord_002A8BD0(scratch.damage,moby,0x810001,*(float *)(vars+0x158));
   scratch.damage[24]=2;scratch.damage[25]=1;*(u16 *)(scratch.damage+26)=*(u16 *)(moby+0xAA);
   ProcessCollisionHit(D_L11_001B1FAC,moby+16,16,moby,scratch.damage);
   *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;SetMobyState(moby,1,-1);
  if(IsVoicePlayingForOwner(moby,*(int *)(vars+0x170))) {
   int sound=*(int *)(vars+0x170);if(sound!=-1){entry=gSoundState+sound*0x70;if(*(char **)(entry+0x88)==moby&&*(u8 *)(entry+0x74))StopSoundVoice(sound);}
   *(int *)(vars+0x170)=-1;
  }return;
  }
  break;
 default: case 1: break;
 }
 {
  float f;
  float min,max;
  f=vec_length_xy(vars+0xC0);min=0.0033333336468786f;max=0.10000000894069672f;
  if(f<min)f=min;if(f>max)f=max;
  f=f-min;
  *(float *)(moby+0xF4)=FastAddRotations(
    ({float fraction=f/0.09666667878627777f;
      (fraction*7+1)*0.017453294f;}),*(float *)(moby+0xF4));
 }
 if(*(u8 *)(moby+0x20)>=2)AddDrawCallbackToList3(SpawnJobaShotSmoke,moby);
 if(*(void **)(moby+0xB8)) {other=GetArenaCenterPoint(*(void **)(moby+0xB8));if(*(float *)(moby+0x18)<*(float *)(other+8)-1){*(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;SetMobyState(moby,1,-1);}}
 if(FindOwnedEffectSlot(moby,0x10000,0))SetMobyState(moby,6,-1);
 *(u8 *)(moby+0xA8)=255;if(*(u16 *)(moby+0x96)<0xFFFF)(*(u16 *)(moby+0x96))++;
}
