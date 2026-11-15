#include "common.h"
typedef int Quad9C58 __attribute__((mode(TI)));
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void func_002AFFD8(void *,void *,int);
extern void func_002FEE70(int,void *,int);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float),func_00282F20(void *,void *,float);
extern void func_00282D08(void *,void *,void *,float),func_00283028(void *,void *,void *);
extern float func_00282DF0(void *),func_00282DB0(void *,void *);
extern float func_00283CE0(int),func_00283B98(float,float),func_00283198(float),func_00282C48(float);
extern int func_00282978(void *),func_00282948(void *),func_002A77E0(int);
extern void func_L00_0031D670(void *,void *,void *,float);
extern char *func_002BDCE8(void *,float,float,float,int,void *,float,unsigned int,int);
extern int func_002761F8(void *,void *,int,void *,int),func_00277258(void *,int,int,float);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int),func_L00_00427078(void),func_002FEE50(int),func_0029F338(void *),func_00300190(void *,void *),func_002A9288(void *,float);
extern void func_L00_003A9798(void *,void *,void *,int);
extern void func_0032C700(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
typedef struct { char pad0[10]; union { short lifetime; unsigned char bytes[2]; } age; } Particle9C58;
typedef struct { char pad0[4]; int type; char pad8[2]; unsigned char alpha,life; } Payload9C58;
extern char D_L00_001A8F20[] MACRO_ADDR;
extern char D_L00_001BF220[] MACRO_ADDR;
typedef struct { char pad0[0x18]; char *hit; char pad1C[0x14]; float position[4],normal[4]; } Collision9C58;
extern Collision9C58 D_L00_001BF200;
extern char D_L00_001B9000[];
typedef struct {
 char pad0[0x1E0]; short control_state; char pad1E2[0x1230-0x1E2];
 int control_mask; char pad1234[0x1248-0x1234]; int state;
 char pad124C[0x2290-0x124C]; int collision_flags; int weapon;
} Hero9C58;
extern Hero9C58 D_00189E20;
typedef struct {
 char pad0[0x108]; float axis_x,axis_y; char pad110[0x1A0-0x110];
 int held,pressed;
} Pad9C58;
extern Pad9C58 D_00138180;
extern char D_00188660[];
extern int D_L00_001ADB2C __attribute__((sda));
/* Updates the Hoverbomb projectile: it flies, bounces off walls, can be steered with the pad, and explodes when released or out of bounds. */
void func_L00_003A9C58(char *moby)
{
 float old[4],direction[4],a[4],b[4],c[4];
 char *vars=*(char **)(moby+0x68),*sound;
 int i,n,prior;float scale,speed,t,bounce;
 ComputeViewDirection(moby+0x10,direction,1);
 H(vars,0x14)++;
 qcopy(old,moby+0x10);
 SteerEffectDirection(I(vars,0x48),vars,0);
 scale=0.45f;
 FastVecAdd(moby+0x10,moby+0x10,vars);
 FastDecTimer(vars+0x2C);
 if(H(vars,0x2C)) {
 short life=50;
 for(i=0;i<3;i++) {
   float third=0.3333f; float one=1.0f; int type=2;
   *(Quad9C58 *)b=*(Quad9C58 *)(moby+0x10);
   LerpVector4(a,old,b,IntToFloat(i)*third);
   n=RandomIntBelow(6);if(RandomIntBelow(2))n=-n;
   t=H(vars,0x2C)/IntToFloat(50)*70000.0f+10000.0f;
   { Particle9C58 *particle=(Particle9C58 *)SpawnSpinningSparkParticle(a,0.025f,one,one,n,D_L00_001A8F20,t,0x80808080,1);
   if(particle) {
     Payload9C58 *payload;
     particle->age.lifetime=life;
     payload=(Payload9C58 *)((char *)particle+32);
     payload->type=type;payload->alpha=127;
     { int l=particle->age.lifetime&0xFF; payload->life=l; }
   } }
 }
 }
 if(H(vars,0x14)<7) {scale=IntToFloat(H(vars,0x14))/IntToFloat(7);scale*=0.45f;
 qcopy(a,moby+0x10);
 FastVecScale(b,direction,F(vars,0x20));FastVecSub(c,moby+0x10,b);
 if(CollLine(a,c,18,moby,0))FastVecAdd(moby+0x10,D_L00_001BF220,b);
 }
 F(vars,0x24)=FastAddRotations(F(vars,0x24),0.025f);
 FastVecScale(a,direction,F(vars,0x28));FastVecSub(moby+0x10,moby+0x10,a);
 F(vars,0x28)=FastSinOrCosB(F(vars,0x24))*0.25f;
 FastVecScale(a,direction,F(vars,0x28));FastVecAdd(moby+0x10,moby+0x10,a);
 F(moby,0xF0)=FastAddRotations(F(moby,0xF0),F(vars,0x30));
 F(moby,0xF4)=FastAddRotations(F(moby,0xF4),F(vars,0x34));
 F(moby,0xF8)=FastAddRotations(F(moby,0xF8),F(vars,0x38));
 FastFloatHelperD(vars+0x44);
 if(TestPointAgainstCollision(moby+0x10,0,gHeroState.collision_flags,scale)) {
   qcopy(moby+0x10,gCollisionResult.position);
   speed=FastVecLength(vars);bounce=speed*0.25f;if(bounce<0.033333335f)bounce=0.033333335f;
   if(gCollisionResult.hit) {
     FastVecSub(a,moby+0x10,gCollisionResult.hit+0x10);
     t=FastVecDot(direction,a);FastVecScale(b,direction,t);
     FastVecAdd(c,gCollisionResult.hit+0x10,b);
     FastVecSub(a,moby+0x10,c);FastVectorNormalize(vars,vars,a);
   } else {
     FastVecScale(a,gCollisionResult.normal,0.0009765625f);vec_scale_to_length(a,a,1.0f);
     t=FastVecDot(a,direction);t=FloatAbs(t);if(t>=0.8f)bounce=speed;
     FastVectorNormalize(vars,vars,a);
   }
   if(!I(vars,0x44)) {PlayMobySound(2,0,moby);I(vars,0x44)=15;}
   vec_scale_to_length(vars,vars,bounce);
 }
 lerp_vector(vars,vars,vars+0x50,0.01f);
 sound=gSoundState+I(vars,0x40)*0x70;
 if(*(char **)(sound+0x88)!=moby || !B(sound,0x74)) I(vars,0x40)=PlayMobySound(0,4,moby);
 if(!((gPadState.pressed&gHeroState.control_mask) ||
       (!(gPadState.held&gHeroState.control_mask) && H(vars,0x2E)>20) ||
       ((gHeroState.state!=25 && gHeroState.state!=70) || B(moby,0x20)==1)))goto steer;
 if(H(vars,0x14)>=21) {
   B(moby,0x20)=1;prior=H(vars,0x16);
   if(FastDecTimer(vars+0x16)) {
     StopSoundVoice(I(vars,0x40));PlayMobySound(1,0,moby);
     if(!prior)SpawnExplosion(moby+0x10,1,40,20,30,40,50,1,1,1,0,D_L00_001ADB2C,1.5f,20.0f);
     else SpawnExplosion(moby+0x10,1,20,15,30,15,30,1,1,0,0,D_L00_001ADB2C,0.6f,20.0f);
     DamageNearbyOnProjectileHit(moby,vars,moby+0x10,1);goto destroy;
   }
 }
steer:
 if(gPadState.held&gHeroState.control_mask) {
   H(vars,0x2E)++;
   if(gHeroState.weapon!=49)gHeroState.control_state=2;
   FlagCameraEntryForHeroMode();
   if(gPadState.axis_x!=0 || gPadState.axis_y!=0) {
     float speed2=FastVecLength(vars);
     if(speed2!=0) {
       FastVecScale(a,D_L00_001B9000,-gPadState.axis_x*0.004166667f);FastVecAdd(vars,vars,a);
       FastVecScale(a,D_L00_001B9000+16,-gPadState.axis_y*0.00083333341f);FastVecAdd(vars,vars,a);
       vec_scale_to_length(vars,vars,speed2);
     }
   }
 }
 if(F(moby,0x10)<2 || F(moby,0x10)>1021 || F(moby,0x14)<2 || F(moby,0x14)>1021 || F(moby,0x18)<2 || F(moby,0x18)>1021) {
destroy:
   ClearEntryFlag(I(vars,0x48));MarkMobySpawned(moby);
 } else {TransformVectorOrCopy(moby+0x10,moby+0x10);QueueGroundShadow(moby,0.5f);}
}
