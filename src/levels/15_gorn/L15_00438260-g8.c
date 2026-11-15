#include "common.h"
extern int D_L15_001B187C __attribute__((sda));
extern char *D_L15_001B261C __attribute__((sda));
extern void func_L15_00437B68(void *,int);
extern int func_00282948(void *);
extern float func_002A7878(float,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L15_004320B0(void *,void *);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_L15_00438B00(void *,int,int);
extern void func_002E5DA0(int,int,void *,int);
extern void func_L05_0037AC80(float);
/* Updates the backdrop and spawns sparks and bursts as the tracked object passes certain heights. */
void func_L15_00438260(char *self) {
 char *state=*(char **)(self+0x68);
 char *obj,*basis,*pos,*axis;
 float a[4],b[4],c[4];
 float distance;
 if(!D_L15_001B187C) return;
 DrawScrollingGridLayers(self,0);
 if(!FastFloatHelperD(state+0xC)) return;
 obj=D_L15_001B261C+(*(int *)state<<8);
 basis=obj+0xC0;
 qcopy(a,basis);
 axis=obj+0xE0;
 pos=obj+0x10;
 distance=800.0f;
 ApplyAxisRotationToQuaternion(a,a,axis,RandomFloatRange(-20.0f,20.0f)*0.01745329424738884f);
 vec_scale_to_length(a,a,distance);
 FastVecAdd(a,a,pos);
 a[2]=distance;
 qcopy(b,a);
 b[2]=400.0f;
 SpawnTimedEffectBetweenPoints(a,b);
 if(RandomIntBelow(2)) SpawnTimedEffectBetweenPoints(a,b);
 *(int *)(state+0xC)=FloatToInt(RandomFloatRange(90.0f,350.0f));
 if(*(float *)(obj+0x18)>=565.0f) {
  qcopy(a,pos); qcopy(b,a);
  a[2]=distance;
  b[2]=*(float *)(obj+0x18)-100.0f;
  SpawnTimedEffectBetweenPoints(a,b);
  qcopy(c,basis);
  vec_scale_to_length(c,c,10.0f);
  FastVecAdd(c,pos,c);
  c[2]-=1.25f;
  SpawnGornSparkBurst(c,40,0);
  PlaySoundFromClassBank(16,0,self,0xFBF);
  ApplyDamageToHero(40.0f);
 }
 if(*(float *)(obj+0x18)<=415.0f) {
  qcopy(c,basis);
  vec_scale_to_length(c,c,10.0f);
  FastVecAdd(c,pos,c);
  c[2]-=1.25f;
  SpawnGornSparkBurst(c,40,0);
  PlaySoundFromClassBank(16,0,self,0xFBF);
  ApplyDamageToHero(40.0f);
 }
}
