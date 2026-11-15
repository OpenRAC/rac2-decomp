/* Emits randomized particles along the motion from the previous position. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
#define FIELD_F32(p,o) (*(float *)((char *)(p)+(o)))
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
/* The EE assigns integer and floating-point arguments to independent register banks. */
extern void FastVecScale(float,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern float math_random_signed_float_range(float,float);
extern float math_random_float_range(float,float);
extern int math_random_int_range(int,int);
extern int func_1163B0(void);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern char D_0018A0E0[];
typedef struct {char pad[0x5C]; unsigned char *data;} ParticleGlobals;
extern ParticleGlobals D_L00_001FE940;
extern char *part_spawn_burst(void *,void *,int,int,int,int,float,float,float,float,float);
void part_emit_shot_trail(char *moby,void *previous)
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
 type=FloatToInt(math_random_signed_float_range(1.0f,3.0f));
 FastVecScale(-(math_random_float_range(0.2f,1.0f)*(1.0f/60.0f)),velocity,D_0018A0E0);
 time=math_random_int_range(30,45);
 speed=math_random_float_range(200.0f,1000.0f);
 if(func_1163B0()&2) {flags=32;color=0x404040;speed+=speed;}
 else {flags=64;color=0x7F7F7F;}
 vel=velocity;
 particle=part_spawn_burst(point,vel,time,flags,color,type,21000.0f,speed,1.0f,0,0);
 FastVecAdd(point,point,step);
 if(particle) {particle[2]=D_L00_001FE940.data[0];particle[3]=flags==64?0x48:0x44;}
 n--;
 } while(n);
}
