#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern int func_002B3868(void *);
extern int func_002B38B8(void *);
extern void func_L00_003294F0(void *, int);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_PAL_L14_003CF468(void *);
extern void func_PAL_L14_003CF6C8(void *);
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

void func_PAL_L14_003CF0B8(char *self) {
 char *s = *(char **)(self+0x68);
 char *e;
 float b,delta,velocity,position,restitution;
 switch ((unsigned char)self[0x20]) {
 case 0:
  func_002A7750(self,1,-1);
  *(int *)(s+0x5C) |= 1;
  qcopy(s+0x70,self+0x10);
  *(float *)(s+0x78) += D_L14_001AFF0C;
  e=func_0029EFD0(0xF4D);
  if(e) {
   unsigned short flags,link;
   func_002B37E8(e,self);
   flags=*(unsigned short *)(e+0x34);
   link=*(unsigned short *)(self+0x32);
   *(unsigned short *)(e+0x32)=link;
   *(unsigned short *)(e+0x34)=flags|2;
   *(int *)(e+0x9C)=0x80000001;
   e[0x30]=0;
   *(unsigned short *)(e+0x7C)=0x8001;
   *(int *)(self+0x9C)=6;
  }
  break;
 case 1:
  if(func_002B3868(self))func_002AD6F0(s+0x20,D_L14_001A8F20,self+0xF0,self+0xF0);
  if(D_0018A15C==self)func_PAL_L14_003CF468(self);
  if(func_002B38B8(self)) {
   func_002A7750(self,2,-1);
   func_L00_003294F0(self,0);
   func_PAL_L14_003CF6C8(self);
  }
  break;
 case 2:
  if(func_002B3868(self))*(float *)(s+0x84)=D_L14_001AFEFC*0.0003490659f;
  delta=D_L14_001AFEF8*6.981318e-06f;
  velocity=*(float *)(s+0x84)-delta;
  b=D_L14_001AFF04*0.01745329424738884f;
  position=*(float *)(s+0x80);
  position+=velocity;
  *(float *)(s+0x84)=velocity;
  *(float *)(s+0x80)=position;
  if(*(float *)(s+0x80)>b) {
   restitution=D_L14_001AFF00;
   *(float *)(s+0x80)=b;
   *(float *)(s+0x84)*=restitution;
   func_002E5CF8(0,0,self);
  } else if(*(float *)(s+0x80)<0.0f) {
   restitution=D_L14_001AFF00;
   *(float *)(s+0x80)=0.0f;
   *(float *)(s+0x84)*=restitution;
   func_002E5CF8(0,0,self);
   if(*(float *)(s+0x84)<=D_L14_001AFF08*0.0003490659f)func_002A7750(self,1,-1);
  }
  D_0018CDD8=-1;
  func_L14_003CB4D8(self);
  break;
 }
}
