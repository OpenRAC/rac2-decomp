#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int moby_forward_two_values_and_amount(int,int,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern float FastVecLength(void *);
extern float math_random_float_range(float,float);
extern int math_random_int_range(int,int);
extern int g_game_time SDATA(D_001B1688);
extern void *func_PAL_002BD790(void *,void *,int,int,float,int,int,int,int,int);
extern int g_ground_check_inhibit;
extern void cam_compute_view_direction(void *,void *,int);
extern void vec_transform_or_copy(void *,void *);

void func_PAL_002BD8E8(char *p) {
 char *q=p+32,*pos,*vel;
 float f,speed,denom;
 float saved[4] __attribute__((aligned(16)));
 float accel[4] __attribute__((aligned(16)));
 float velocity[4] __attribute__((aligned(16)));
 float random[4] __attribute__((aligned(16)));
 int life;
 if (FastDecTimer(p+10)) { part_kill(p); return; }
  f=IntToFloat(*(short *)(p+10));
 denom=IntToFloat(*(short *)(q+24));
 f=f* *(float *)(q+28); f=f/denom;
 *(float *)(p+12)=f;
 *(int *)(p+4)=moby_forward_two_values_and_amount(*(int *)(q+20),*(int *)(q+16),IntToFloat(*(short *)(p+10))/IntToFloat(*(short *)(q+24)));
 FastVecAdd(p+16,p+16,q);
 pos=p+16;
 if (g_ground_check_inhibit) {
  cam_compute_view_direction(pos,accel,0);
  FastVecScale(accel,accel,*(float *)(q+12));
  FastVecAdd(q,q,accel);
 } else *(float *)(q+8)-=*(float *)(q+12);
 qcopy(saved,pos);
 if (*(float *)(p+28)!=0.0f) {
  if (*(float *)(p+28)==2.0f) vec_transform_or_copy(pos,pos);
  *(float *)(p+28)=2.0f;
 }
 if (*(short *)(q+26) && (g_game_time&1)) {
  *(Quad *)random=0;
  random[0]=math_random_float_range(-1.0f,1.0f);
  random[1]=math_random_float_range(-1.0f,1.0f);
  random[2]=math_random_float_range(-1.0f,1.0f);
  *(Quad *)velocity=*(Quad *)random;
  speed=FastVecLength(q);
  vel=(char *)velocity;
  speed*=math_random_float_range(0.15f,0.25f);
  vec_scale_to_length(vel,vel,speed);
  FastVecAdd(vel,vel,q);
  FastVecScale(vel,vel,math_random_float_range(0.75f,0.95f));
  life=((s32)(math_random_int_range(15,30)) * 5 + 2) / 6;
  func_PAL_002BD790(pos,vel,*(int *)(p+4),*(int *)(q+20),*(float *)(p+12),life,0,(unsigned char)p[2],(unsigned char)p[3],FloatToInt(*(float *)(p+28)));
 } else FastVecScale(q,q,0.96f);
}
