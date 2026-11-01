#include "include_asm.h"

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
extern void *func_PAL_002BD790(void *,void *,int,int,float,int,int,int,int,int);
extern int D_001A8CA0;
extern void func_002AFFD8(void *,void *,int);
extern void func_00300190(void *,void *);

void func_PAL_002BD8E8(char *p) {
 char *q=p+32,*pos,*vel;
 float f,speed,denom;
 float saved[4] __attribute__((aligned(16)));
 float accel[4] __attribute__((aligned(16)));
 float velocity[4] __attribute__((aligned(16)));
 float random[4] __attribute__((aligned(16)));
 int life;
 if (func_00282978(p+10)) { func_002B9180(p); return; }
  f=func_00283CE0(*(short *)(p+10));
 denom=func_00283CE0(*(short *)(q+24));
 f=f* *(float *)(q+28); f=f/denom;
 *(float *)(p+12)=f;
 *(int *)(p+4)=func_002A9568(*(int *)(q+20),*(int *)(q+16),func_00283CE0(*(short *)(p+10))/func_00283CE0(*(short *)(q+24)));
 func_00282CC0(p+16,p+16,q);
 pos=p+16;
 if (D_001A8CA0) {
  func_002AFFD8(pos,accel,0);
  func_00282D30(accel,accel,*(float *)(q+12));
  func_00282CC0(q,q,accel);
 } else *(float *)(q+8)-=*(float *)(q+12);
 qcopy(saved,pos);
 if (*(float *)(p+28)!=0.0f) {
  if (*(float *)(p+28)==2.0f) func_00300190(pos,pos);
  *(float *)(p+28)=2.0f;
 }
 if (*(short *)(q+26) && (D_001B1688&1)) {
  *(Quad *)random=0;
  random[0]=func_002A7878(-1.0f,1.0f);
  random[1]=func_002A7878(-1.0f,1.0f);
  random[2]=func_002A7878(-1.0f,1.0f);
  *(Quad *)velocity=*(Quad *)random;
  speed=func_00282DF0(q);
  vel=(char *)velocity;
  speed*=func_002A7878(0.15f,0.25f);
  func_00282F20(vel,vel,speed);
  func_00282CC0(vel,vel,q);
  func_00282D30(vel,vel,func_002A7878(0.75f,0.95f));
  life=((s32)(func_002A7820(15,30)) * 5 + 2) / 6;
  func_PAL_002BD790(pos,vel,*(int *)(p+4),*(int *)(q+20),*(float *)(p+12),life,0,(unsigned char)p[2],(unsigned char)p[3],func_00283CF0(*(float *)(p+28)));
 } else func_00282D30(q,q,0.96f);
}
