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
extern void *part_spawn_spark(void *,void *,int,int,float,int,int,int,int,int);
extern int D_001A8CA0;
extern void cam_compute_view_direction(void *,void *,int);
extern void vec_transform_or_copy(void *,void *);
/* Updates a spark. It falls, fades, and sometimes throws off small sparks of its own. */
void part_update_spark(char *particle) {
 char *motion=particle+32,*pos,*vel;
 float lifeRatio,speed,maxLife;
 float saved[4] __attribute__((aligned(16)));
 float accel[4] __attribute__((aligned(16)));
 float velocity[4] __attribute__((aligned(16)));
 float randomDir[4] __attribute__((aligned(16)));
 int childLife;
 if (FastDecTimer(particle+10)) { part_kill(particle); return; }
  lifeRatio=IntToFloat(*(short *)(particle+10));
 maxLife=IntToFloat(*(short *)(motion+24));
 lifeRatio=lifeRatio* *(float *)(motion+28); lifeRatio=lifeRatio/maxLife;
 *(float *)(particle+12)=lifeRatio;
 *(int *)(particle+4)=moby_forward_two_values_and_amount(*(int *)(motion+20),*(int *)(motion+16),IntToFloat(*(short *)(particle+10))/IntToFloat(*(short *)(motion+24)));
 FastVecAdd(particle+16,particle+16,motion);
 pos=particle+16;
 if (D_001A8CA0) {
  cam_compute_view_direction(pos,accel,0);
  FastVecScale(accel,accel,*(float *)(motion+12));
  FastVecAdd(motion,motion,accel);
 } else *(float *)(motion+8)-=*(float *)(motion+12);
 qcopy(saved,pos);
 if (*(float *)(particle+28)!=0.0f) {
  if (*(float *)(particle+28)==2.0f) vec_transform_or_copy(pos,pos);
  *(float *)(particle+28)=2.0f;
 }
 if (*(short *)(motion+26) && (g_game_time&1)) {
  *(Quad *)randomDir=0;
  randomDir[0]=math_random_float_range(-1.0f,1.0f);
  randomDir[1]=math_random_float_range(-1.0f,1.0f);
  randomDir[2]=math_random_float_range(-1.0f,1.0f);
  *(Quad *)velocity=*(Quad *)randomDir;
  speed=FastVecLength(motion);
  vel=(char *)velocity;
  speed*=math_random_float_range(0.15f,0.25f);
  vec_scale_to_length(vel,vel,speed);
  FastVecAdd(vel,vel,motion);
  FastVecScale(vel,vel,math_random_float_range(0.75f,0.95f));
  childLife=math_random_int_range(15,30);
  part_spawn_spark(pos,vel,*(int *)(particle+4),*(int *)(motion+20),*(float *)(particle+12),childLife,0,(unsigned char)particle[2],(unsigned char)particle[3],FloatToInt(*(float *)(particle+28)));
 } else FastVecScale(motion,motion,0.96f);
}
