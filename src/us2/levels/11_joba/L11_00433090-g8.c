/* func_US2_L11_00433090, the USA v2.00 copy of func_L11_00431860: the same C, where the
   counter increment is guarded by the release-only D_US2_001A9050 and type 0xed8 is also tested. */
#include "common.h"
extern int D_US2_001A9050;
extern int D_L11_001AED04;
extern int D_L11_001AED00;
extern char D_L11_001BA8C0[];
extern float func_002A89A8(void *, int, float);
extern int func_00283CF0(float);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern void func_L11_0042EF90(void *, int, int, int, int);
extern float func_002A7878(float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_00291450(int);
extern void func_002A7470(void *, int, int, int);
extern void func_L11_00431DB0(void *);
extern int func_002B3670(void *, void *, int, int, float, float, int);
#define I(o) (*(int *)(d+(o)))
#define F(o) (*(float *)(d+(o)))
#define B(o) (*(u8 *)(d+(o)))
void func_US2_L11_00433090(u8 *obj) {
 u8 *d=*(u8 **)(obj+0x68); int state; u8 *p;
 if (!obj[0x20]) {
  float height;
  if(!D_US2_001A9050) D_L11_001AED04++;
  height=func_002A89A8(obj+0x10,0,0.5f);
  *(void **)(d+0x18)=d+0x140;
  *(float *)(obj+0x18)=height;
  I(0x2a0)=0;
  B(0x48)=func_00283CF0(20.0f);
  B(0x4a)=func_00283CF0(12.8f);
  B(0x70)=26; B(0x71)=11; B(0x72)=11; B(0x76)=13;
  F(0x7c)=0.10000000894f; F(0x80)=0.0666666701f; F(0x84)=0.00416666688f;
  F(0x88)=0.00833333377f; F(0x8c)=0.00416666688f;
  I(0xa8)=3; F(0x90)=0.5f; F(0x94)=0.5f; F(0x9c)=0.4f;
  *(s8 *)(d+0xcc)=-1; *(s8 *)(d+0xcd)=-1; *(s8 *)(d+0xce)=-1; *(s8 *)(d+0xcf)=-1;
  *(s8 *)(d+0xd2)=-1; *(s8 *)(d+0xd3)=-1; B(0xd7)=1;
  F(0x140)=1; F(0x144)=0.25f; F(0x148)=0.6f; F(0x14c)=0.6f; F(0x150)=1.48353004f;
  F(0x170)=1.48353004f; F(0x16c)=0.00138888892f;
  func_002B60B0(obj,0.00222222228f,0.0666666701f,0.0011635529808700085f,0.10471977293491364f);
  qcopy(d+0x110,obj+0x10);
  F(0x120)=1.25f; F(0x12c)=F(0x290); F(0x130)=10;
  I(0x28c)=func_002A7820(120,700);
  B(0x28)=3; B(0x29)=1; F(0x2b4)=B(0x34); F(0x2b8)=B(0x36); F(0x30)=0.75f;
  func_002A7750(obj,1,0); func_L11_0042EF90(obj,4,1,0,0);
  *(float *)(obj+0x48)=func_002A7878(0.5f,1.25f);
  if (I(0x2bc)!=-1) func_002A7750(obj,2,-1);
 }
 if(obj[0x31] && func_00282E48(obj+0x10,D_L11_001BA8C0)<24.0f) {func_002A93B0(obj);obj[0x6f]=22;}
 if(obj[0x95]!=3) {
  float height=func_002A89A8(obj+0x10,0,0.5f);
  *(float *)(obj+0x18)-=1.146666765f;
  if(*(float *)(obj+0x18)<height) *(float *)(obj+0x18)=height;
 }
 state=func_002B0ED8(obj,d+0x60,0);
 if(state) {
  p=*(u8 **)(d+0x38);
  if(p) {int type=*(short *)(p+0xaa); if(type!=0xed8 && type!=0x47 && type!=0xdd9 && type!=0xd1b && type!=0xce7 && type!=0xd07 && type) D_L11_001AED00=0;}
  I(0x2a0)=0;
  if(I(0x2b0)>=0) {func_00291450(I(0x2b0));I(0x2b0)=-1;}
  if(state==5) {I(0xf0)=0;F(0xf4)=0.837758183f;}
  if(I(0x27c)) {
   switch(state) {
   case 1: break;
   case 2: case 3: func_002A7470(*(void **)(d+0x27c),8,0,3);break;
   case 4: case 5: func_002A7470(*(void **)(d+0x27c),9,0,3); *(int *)(*(u8 **)(*(u8 **)(d+0x27c)+0x68)+0x26c)=0;break;
   }
  }
  func_L11_00431DB0(obj);
  if(!obj[0x95]) {
   if(I(0x29c)!=-1) {func_002A7750(obj,12,1);func_L11_0042EF90(obj,4,3,0,12);}
   else {func_002A7750(obj,11,1);*(short *)(d+0x270)=func_002A7820(580,600);func_L11_0042EF90(obj,6,5,0,10);}
  }
 }
 *(short *)(d+0x274)=func_002B3670(obj,d+0x278,I(0x260),I(0x264),F(0x268),F(0x26c),0);
}
