/* Emits randomized particles along the motion from the previous position. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
#define FIELD_F32(p,o) (*(float *)((char *)(p)+(o)))
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
/* The EE assigns integer and floating-point arguments to independent register banks. */
extern void func_00282D30(float,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A78D8(float,float);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern int func_1163B0(void);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern char D_0018A0E0[];
typedef struct {char pad[0x5C]; unsigned char *data;} ParticleGlobals;
extern ParticleGlobals D_L00_001FE940;
extern char *func_002C16C0(void *,void *,int,int,int,int,float,float,float,float,float);
void func_L00_003ACA60(char *moby,void *previous)
{
 float initial[4],velocity[4],position[4],step[4];
 float scale, speed, ratio;
 float *start=initial;
 float *point;
 float *vel;
 int n,type,time,flags,color;
 char *particle;
 *(Quadword *)start=*(Quadword *)previous;
 scale=FIELD_F32(*(char **)(moby+0x68),0x18);
 n=FloatToInt(scale*10.0f);
 point=position;
 qcopy(point,start);
 FastVecSub(step,moby+0x10,initial);
 ratio=IntToFloat(n);
 ratio=scale/ratio;
 vec_scale_to_length(step,step,ratio);
 if(n>0) do {
 type=FloatToInt(RandomSignedFloatRange(1.0f,3.0f));
 FastVecScale(-(RandomFloatRange(0.2f,1.0f)*(1.0f/60.0f)),velocity,D_0018A0E0);
 time=RandomIntRange(30,45);
 speed=RandomFloatRange(200.0f,1000.0f);
 if(func_1163B0()&2) {flags=32;color=0x404040;speed+=speed;}
 else {flags=64;color=0x7F7F7F;}
 vel=velocity;
 particle=SpawnBurstParticle_002C16C0(point,vel,time,flags,color,type,21000.0f,speed,1.0f,0,0);
 FastVecAdd(point,point,step);
 if(particle) {particle[2]=D_L00_001FE940.data[0];particle[3]=flags==64?0x48:0x44;}
 n--;
 } while(n);
}
