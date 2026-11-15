#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A9568(int,int,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern float func_00282DF0(void *);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern int D_001B1688 SDATA(D_001B1688);
extern void *func_002BCB00(void *,void *,int,int,float,int,int,int,int,int);
extern int D_001A8CA0;
extern void func_002AFFD8(void *,void *,int);
extern void func_00300190(void *,void *);
/* Updates a spark. It falls, fades, and sometimes throws off small sparks of its own. */
void func_002BCC58(char *particle) {
 char *motion=particle+32,*pos,*vel;
 float lifeRatio,speed,maxLife;
 float saved[4] __attribute__((aligned(16)));
 float accel[4] __attribute__((aligned(16)));
 float velocity[4] __attribute__((aligned(16)));
 float randomDir[4] __attribute__((aligned(16)));
 int childLife;
 if (FastDecTimer(particle+10)) { KillParticle(particle); return; }
  lifeRatio=IntToFloat(*(short *)(particle+10));
 maxLife=IntToFloat(*(short *)(motion+24));
 lifeRatio=lifeRatio* *(float *)(motion+28); lifeRatio=lifeRatio/maxLife;
 *(float *)(particle+12)=lifeRatio;
 *(int *)(particle+4)=ForwardTwoValuesAndAmount(*(int *)(motion+20),*(int *)(motion+16),IntToFloat(*(short *)(particle+10))/IntToFloat(*(short *)(motion+24)));
 FastVecAdd(particle+16,particle+16,motion);
 pos=particle+16;
 if (D_001A8CA0) {
  ComputeViewDirection(pos,accel,0);
  FastVecScale(accel,accel,*(float *)(motion+12));
  FastVecAdd(motion,motion,accel);
 } else *(float *)(motion+8)-=*(float *)(motion+12);
 qcopy(saved,pos);
 if (*(float *)(particle+28)!=0.0f) {
  if (*(float *)(particle+28)==2.0f) TransformVectorOrCopy(pos,pos);
  *(float *)(particle+28)=2.0f;
 }
 if (*(short *)(motion+26) && (gGameTime&1)) {
  *(Quad *)randomDir=0;
  randomDir[0]=RandomFloatRange(-1.0f,1.0f);
  randomDir[1]=RandomFloatRange(-1.0f,1.0f);
  randomDir[2]=RandomFloatRange(-1.0f,1.0f);
  *(Quad *)velocity=*(Quad *)randomDir;
  speed=FastVecLength(motion);
  vel=(char *)velocity;
  speed*=RandomFloatRange(0.15f,0.25f);
  vec_scale_to_length(vel,vel,speed);
  FastVecAdd(vel,vel,motion);
  FastVecScale(vel,vel,RandomFloatRange(0.75f,0.95f));
  childLife=RandomIntRange(15,30);
  SpawnSparkParticle_002BCB00(pos,vel,*(int *)(particle+4),*(int *)(motion+20),*(float *)(particle+12),childLife,0,(unsigned char)particle[2],(unsigned char)particle[3],FloatToInt(*(float *)(particle+28)));
 } else FastVecScale(motion,motion,0.96f);
}
