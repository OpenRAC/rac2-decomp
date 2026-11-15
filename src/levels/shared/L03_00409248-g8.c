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
/* Runs the Slim Cognito button that opens a door: it watches the player, plays the camera when pressed, and opens the linked door. */
void func_L03_00409248(u8 *moby) {
 float vec[4], angle, delta, interpolated[4];
 u8 *vars=*(u8 **)(moby+0x68), *other, *cameraBlock, *cameraRecord;
 int linkIndex;
 switch(moby[0x20]) {
 case 0:
  if (*(int *)vars) {SetMobyState(moby,3,-1);break;}
  SetMobyState(moby,1,-1);
  {u8 *base=D_L03_001B2A1C[0]; u8 *child;
  *(int *)(moby+0x98)=0; *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;
  child=base+(*(int *)(vars+8)<<8);
  *(int *)(child+0x98)=0; *(u16 *)(child+0x34)=(*(u16 *)(child+0x34)|0x41)&0xefff;}
  break;
 case 1:
  SetBitInFlagTable(gCurrentMapIndex[0],1);
  if (gHeroState.state!=0x31) {
   if(IsPointInCuboid((u8 *)&gHeroState+0x80,*(int *)(vars+4))) {
    TryClaimNotice(1,0x2799,1);
    if(IsHeroAllowedForMode(1) && (D_00138324&0x10)) SetMobyState(moby,2,-1);
   }
   if(!D_001395B8[0x8c] && IsPointInCuboid((u8 *)&gHeroState+0x80,*(int *)(vars+0xc))) {
    linkIndex=-1;
    switch(gCurrentMapIndex[0]) {case 3:linkIndex=0x35;break;case 8:linkIndex=0x5c;break;case 13:linkIndex=0x79;break;}
    if(linkIndex!=-1 && PushRequestQueue(D_L03_001BFB80,linkIndex)) {LaunchQueuedRequest(D_L03_001BFB80);D_001395B8[0x8c]=1;SetMobyState(moby,4,-1);}
   }
  }
  *(int *)(moby+0x98)=0; *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;
  break;
 case 2:
  if(SetFirstPendingFlag(moby)) {
   vec_scale_to_length(vec,moby+0xc0,3.0f);FastVecAdd(vec,vec,moby+0x10);
   angle=FastAddRotations(*(float *)(moby+0xf8),3.1415927f);StartHeroTargetState(vec,0,angle);
  }
  cameraRecord=*(u8 **)(D_L03_001B9840.camera+0x70);cameraBlock=cameraRecord+0x1c0;
  *(int *)(cameraBlock+0x10)|=3;
  angle=FastMatrixHelperA(*(float *)(cameraRecord+0x160),*(float *)(cameraRecord+0x164));
  interpolated[0]=fast_subtract_rotations(*(float *)(moby+0xf8),angle);
  ApproachTargetWithDirectionMode(interpolated,0.0f,(float *)(vars+0x10),0,0.00096962746f,0.00096962746f,0.05817765f);
  *(float *)(cameraBlock+0x1c)=1.0f;*(float *)(cameraBlock+0x14)=-*(float *)(vars+0x10);
  delta=FastDiffRots(D_L03_001B9840.yaw,*(float *)(moby+0xf8));
  other=D_L03_001B2A1C[0]+(*(int *)(vars+8)<<8);
  if(delta>1.5707964f)StartMobyDrop(other,0);
  if(GetHeroTargetStateKind()==2 && delta>3.135f && IsMobyAtStoredHeight(other)) {
   SetMobyState(moby,1,-1);StartHeroLoaderState(0);BeginSlotRequest(5,1,moby,0,0);
  } else if((unsigned)(D_0018C0B4-0x62)>=3)SetMobyState(moby,1,-1);
  break;
 case 4:
  {unsigned timer=*(u16 *)(moby+0x96),old=timer++;
  *(u16 *)(moby+0x96)=timer;
  if(old>20 && !D_L03_001A8F00[0]) {
   StartMobyDrop(D_L03_001B2A1C[0]+(*(int *)(vars+8)<<8),1);BeginSlotRequest(5,1,moby,0,0);
  }}break;
 case 3:
  if(D_L03_001A8F00[0]==2){moby[0x31]=0;*(u16 *)(moby+0x34)|=1;}
  else {moby[0x31]=1;*(u16 *)(moby+0x34)&=0xfffe;}
  break;
 }
 linkIndex=*(int *)(vars+0x14);
 if(linkIndex!=-1 && D_0018C0B4!=0x31) {
  other=D_L03_001B2A1C_gp+(linkIndex<<8)+0x10;
  FastVecSub(vec,other,moby+0x10);
  if(FastVecLength(vec)<20.0f){if(vec[0]!=0.0f)vec[0]=20.0f/vec[0];if(vec[1]!=0.0f)vec[1]=20.0f/vec[1];vec[2]=0.0f;FastVectorDivideHelper(vec,vec,1.0f/6.0f);FastVecAdd(other,other,vec);}
 }
}
