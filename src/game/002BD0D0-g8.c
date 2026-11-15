#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A9568(int,int,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern float D_001B168C __attribute__((sda));
extern float func_00282E48(void *,void *);
extern char D_001B5340[];
extern char *func_002BCF18(void *,void *,int,int,float,int,int);
typedef struct { float v[4]; } GravityTable;
extern GravityTable D_001AA350;
/* Updates a falling drop. It falls, fades near the end and near the camera, and splashes into a small drop when it lands. */
void func_002BD0D0(char *particle)
{
 char *motion=particle+32,*pos;
 struct { Quad saved; GravityTable gravity; } local;
 float lifeRatio,cameraDistance,size;
 int color,alpha,endColor,dropType;
 local.gravity=D_001AA350;
 if(*(short *)(motion+26)==3 && D_001B168C>0.95f) FastDecTimer(particle+10);
 if(FastDecTimer(particle+10)) {KillParticle(particle);return;}
 pos=particle+16;
 lifeRatio=IntToFloat(*(short *)(particle+10));
 *(int *)(particle+4)=ForwardTwoValuesAndAmount(*(int *)(motion+20),*(int *)(motion+16),lifeRatio/IntToFloat(*(short *)(motion+24)));
 alpha=*(int *)(particle+4)>>24;
 cameraDistance=fast_vec_dist(pos,gCameraState_001B5340);
 if(*(short *)(particle+10)<6) alpha=alpha* *(short *)(particle+10)/6;
 if(cameraDistance<4.0f) {KillParticle(particle);return;}
 if(cameraDistance<8.0f) alpha=FloatToInt(IntToFloat(alpha)*(cameraDistance-4.0f)*0.25f);
 *(int *)(particle+4)=(alpha<<24)|(*(int *)(particle+4)&0xffffff);
 FastVecAdd(pos,pos,motion);
 dropType=*(short *)(motion+26);
 *(float *)(motion+8)-=local.gravity.v[dropType];
 qcopy(&local.saved,pos);
 if(*(float *)(particle+24)<*(float *)(motion+12)) {
  if(dropType==1) {
   lifeRatio=RandomFloatRange(0.25f,1.0f);
   color=ForwardTwoValuesAndAmount(0x7f000000,0x7f182030,lifeRatio);
   lifeRatio=RandomFloatRange(0.5f,1.0f);
   endColor=ForwardTwoValuesAndAmount(0,0x5f5f5f,lifeRatio);
   *(float *)(motion+8)=0.0f;
   size=RandomFloatRange(200000.0f,300000.0f);
   SpawnFallingDropParticle(pos,motion,color,endColor,size,RandomIntRange(90,150),3);
  }
  KillParticle(particle);
 } else particle[8]=(unsigned char)particle[8]+1;
}
