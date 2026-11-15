#include "common.h"

/* func_L14_003CB258: a three-state moby update (spawn and link a 0xF4D moby, wait for the
   animation, then swing through a bounded angle with restitution). Its tuning floats are
   read through $gp, and its switch table and float constants are this unit's .rodata. */
extern void func_002A7750(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern int func_002B3868(void *);
extern int func_002B38B8(void *);
extern void func_L00_003294F0(void *, int);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_L14_003CB608(void *);
extern void func_L14_003CB868(void *);
extern void func_L14_003CB4D8(void *);
extern int func_002E5CF8(int, int, void *);
extern char *D_0018A15C NOT_SDA;
extern unsigned short D_0018CDD8 NOT_SDA;
extern char D_L14_001A8F20[] __attribute__((sda));
extern float D_L14_001AFEF8 __attribute__((sda));
extern float D_L14_001AFEFC __attribute__((sda));
extern float D_L14_001AFF00 __attribute__((sda));
extern float D_L14_001AFF04 __attribute__((sda));
extern float D_L14_001AFF08 __attribute__((sda));
extern float D_L14_001AFF0C __attribute__((sda));
void func_L14_003CB258(char *self) {
 char *vars = *(char **)(self+0x68);
 char *child;
 float maxAngle,delta,velocity,angle,restitution;
 switch ((unsigned char)self[0x20]) {
 case 0:
  SetMobyState(self,1,-1);
  *(int *)(vars+0x5C) |= 1;
  qcopy(vars+0x70,self+0x10);
  *(float *)(vars+0x78) += D_L14_001AFF0C;
  child=CreateMoby(0xF4D /* moby class 3917 */);
  if(child) {
   unsigned short flags,link;
   InitChildObjectFromParent(child,self);
   flags=*(unsigned short *)(child+0x34);
   link=*(unsigned short *)(self+0x32);
   *(unsigned short *)(child+0x32)=link;
   *(unsigned short *)(child+0x34)=flags|2;
   *(int *)(child+0x9C)=0x80000001;
   child[0x30]=0;
   *(unsigned short *)(child+0x7C)=0x8001;
   *(int *)(self+0x9C)=6;
  }
  break;
 case 1:
  if(SetFirstPendingFlag(self))CombineTransformsAndStore(vars+0x20,D_L14_001A8F20,self+0xF0,self+0xF0);
  if(D_0018A15C==self)ClampGroupEntitiesToLiftBoxWide(self);
  if(IsThirdPendingFlagSet(self)) {
   SetMobyState(self,2,-1);
   SetObjectFlagBit(self,0);
   UpdateLaunchVolume(self);
  }
  break;
 case 2:
  if(SetFirstPendingFlag(self))*(float *)(vars+0x84)=D_L14_001AFEFC*0.0002908882452175021f;
  delta=D_L14_001AFEF8*4.848137450608192e-06f;
  velocity=*(float *)(vars+0x84)-delta;
  maxAngle=D_L14_001AFF04*0.01745329424738884f;
  angle=*(float *)(vars+0x80);
  angle+=velocity;
  *(float *)(vars+0x84)=velocity;
  *(float *)(vars+0x80)=angle;
  if(*(float *)(vars+0x80)>maxAngle) {
   restitution=D_L14_001AFF00;
   *(float *)(vars+0x80)=maxAngle;
   *(float *)(vars+0x84)*=restitution;
   PlayMobySound(0,0,self);
  } else if(*(float *)(vars+0x80)<0.0f) {
   restitution=D_L14_001AFF00;
   *(float *)(vars+0x80)=0.0f;
   *(float *)(vars+0x84)*=restitution;
   PlayMobySound(0,0,self);
   if(*(float *)(vars+0x84)<=D_L14_001AFF08*0.0002908882452175021f)SetMobyState(self,1,-1);
  }
  D_0018CDD8=-1;
  ApplySwingToObject(self);
  break;
 }
}
