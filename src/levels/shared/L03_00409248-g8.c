/* The state timer is a 16-bit field incremented through a wider local; its old value decides
   case 4. The rest is the door pair: a child object at index s+8 and an optional push volume. */
#include "common.h"
extern u8 *D_L03_001B2A1C[] MACRO_ADDR;
extern u8 *D_L03_001B2A1C_gp SDATA(D_L03_001B2A1C);
typedef struct { u8 pad[0x2294]; int state; } PlayerState;
extern PlayerState D_00189E20;
extern u8 D_001395B8[];
extern int D_001A79F0[] MACRO_ADDR;
extern int D_00138324 __attribute__((nosda));
extern int D_L03_001A8F00[] MACRO_ADDR;
extern int D_0018C0B4 __attribute__((nosda));
extern u8 D_L03_001BFB80[];
typedef struct { u8 pad[0x158]; float yaw; u8 pad2[0x34]; u8 *camera; } CameraState;
extern CameraState D_L03_001B9840;
extern void func_002A7750(u8 *,int,int);
extern void func_L01_00371228(int,int);
extern int func_002ACBC8(u8 *,int);
extern void func_002B0C28(int,int,int);
extern int func_L03_0032AB20(int);
extern int func_00288AA0(u8 *,int);
extern void func_00288BE8(u8 *);
extern int func_002B3868(u8 *);
extern void func_00282F20(float *,u8 *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00283B98(float,float);
extern void func_L00_002D40A0(float *,int,float);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern float func_002AAA00(float *,float,float *,int,float,float,float);
extern float func_00283C80(float,float);
extern void func_L03_00409C38(u8 *,int);
extern int func_L00_002D40F0(void);
extern int func_L03_00409D28(u8 *);
extern void func_L00_002C8BA8(int);
extern int func_002B49E0(int,int,u8 *,int,int);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *);
extern void func_00282FB8(void *,void *,float);
void func_L03_00409248(u8 *e) {
 float v[4], angle, delta, interpolated[4];
 u8 *s=*(u8 **)(e+0x68), *other, *p, *cam;
 int n;
 switch(e[0x20]) {
 case 0:
  if (*(int *)s) {func_002A7750(e,3,-1);break;}
  func_002A7750(e,1,-1);
  {u8 *base=D_L03_001B2A1C[0]; u8 *child;
  *(int *)(e+0x98)=0; *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
  child=base+(*(int *)(s+8)<<8);
  *(int *)(child+0x98)=0; *(u16 *)(child+0x34)=(*(u16 *)(child+0x34)|0x41)&0xefff;}
  break;
 case 1:
  func_L01_00371228(D_001A79F0[0],1);
  if (D_00189E20.state!=0x31) {
   if(func_002ACBC8((u8 *)&D_00189E20+0x80,*(int *)(s+4))) {
    func_002B0C28(1,0x2799,1);
    if(func_L03_0032AB20(1) && (D_00138324&0x10)) func_002A7750(e,2,-1);
   }
   if(!D_001395B8[0x8c] && func_002ACBC8((u8 *)&D_00189E20+0x80,*(int *)(s+0xc))) {
    n=-1;
    switch(D_001A79F0[0]) {case 3:n=0x35;break;case 8:n=0x5c;break;case 13:n=0x79;break;}
    if(n!=-1 && func_00288AA0(D_L03_001BFB80,n)) {func_00288BE8(D_L03_001BFB80);D_001395B8[0x8c]=1;func_002A7750(e,4,-1);}
   }
  }
  *(int *)(e+0x98)=0; *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
  break;
 case 2:
  if(func_002B3868(e)) {
   func_00282F20(v,e+0xc0,3.0f);func_00282CC0(v,v,e+0x10);
   angle=func_00283B98(*(float *)(e+0xf8),3.1415927f);func_L00_002D40A0(v,0,angle);
  }
  cam=*(u8 **)(D_L03_001B9840.camera+0x70);p=cam+0x1c0;
  *(int *)(p+0x10)|=3;
  angle=func_00283248(*(float *)(cam+0x160),*(float *)(cam+0x164));
  interpolated[0]=func_00283BE0(*(float *)(e+0xf8),angle);
  func_002AAA00(interpolated,0.0f,(float *)(s+0x10),0,0.00096962746f,0.00096962746f,0.05817765f);
  *(float *)(p+0x1c)=1.0f;*(float *)(p+0x14)=-*(float *)(s+0x10);
  delta=func_00283C80(D_L03_001B9840.yaw,*(float *)(e+0xf8));
  other=D_L03_001B2A1C[0]+(*(int *)(s+8)<<8);
  if(delta>1.5707964f)func_L03_00409C38(other,0);
  if(func_L00_002D40F0()==2 && delta>3.135f && func_L03_00409D28(other)) {
   func_002A7750(e,1,-1);func_L00_002C8BA8(0);func_002B49E0(5,1,e,0,0);
  } else if((unsigned)(D_0018C0B4-0x62)>=3)func_002A7750(e,1,-1);
  break;
 case 4:
  {unsigned timer=*(u16 *)(e+0x96),old=timer++;
  *(u16 *)(e+0x96)=timer;
  if(old>20 && !D_L03_001A8F00[0]) {
   func_L03_00409C38(D_L03_001B2A1C[0]+(*(int *)(s+8)<<8),1);func_002B49E0(5,1,e,0,0);
  }}break;
 case 3:
  if(D_L03_001A8F00[0]==2){e[0x31]=0;*(u16 *)(e+0x34)|=1;}
  else {e[0x31]=1;*(u16 *)(e+0x34)&=0xfffe;}
  break;
 }
 n=*(int *)(s+0x14);
 if(n!=-1 && D_0018C0B4!=0x31) {
  other=D_L03_001B2A1C_gp+(n<<8)+0x10;
  func_00282CF0(v,other,e+0x10);
  if(func_00282DF0(v)<20.0f){if(v[0]!=0.0f)v[0]=20.0f/v[0];if(v[1]!=0.0f)v[1]=20.0f/v[1];v[2]=0.0f;func_00282FB8(v,v,1.0f/6.0f);func_00282CC0(other,other,v);}
 }
}
