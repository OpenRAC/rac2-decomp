#include "common.h"

typedef struct Hero_4287E8 {
 char pad0[0x88]; float z;
 char pad8c[0xC]; float yaw;
 char pad9c[0xA38]; char *swing;
 char padad8[8]; float max_height;
 char padae4[0x17B0]; int state;
} Hero_4287E8;
extern Hero_4287E8 D_00189E20_6;
typedef struct CameraGlobals_4287E8 {char pad[0x190];char *follow;} CameraGlobals_4287E8;
extern CameraGlobals_4287E8 D_L00_001B8C80_1;
extern char D_00189EA0[];
/* Bank order as the callers set it up: the object pointer travels in a0 either way. */
extern float func_002703B0(float, float, char *, float, float, float);
extern void func_00282CC0_4(char *, char *, char *);
extern void func_002AA2E8(char *,float,float);
extern void func_00282CF0(char *,char *,char *);
extern void func_00282F20(char *,char *,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DB0(char *,char *);
extern float func_00282DF0(char *);
extern float func_00283248(float,float);
extern int func_00282978(char *);
extern int D_001A79F0 MACRO_ADDR;
extern short *D_L00_001FA920[];
extern char *D_L00_001B1E9C MACRO_ADDR;
/* Updates the swingshot camera each frame. It turns towards the nearest swingshot node the hero is facing, then places the camera behind the hero. */
void func_L00_004287E8(char *camera)
{
 char out[16] __attribute__((aligned(16)));
 char diff[16] __attribute__((aligned(16)));
 char unit[16] __attribute__((aligned(16)));
 float axis[4] __attribute__((aligned(16)));
 char *vars=*(char **)(camera+0x70),*cfg=vars+0xA0,*part=vars+0x40,*angle=vars+0xB8;
 char *swing,*bestNode,*node,*turn;
 float height,dist,aimDot,score,closest;
 short *list;
 if(D_00189E20_6.swing && D_00189E20_6.state==0x2B) {
  float aimDot=*(float *)(D_00189E20_6.swing+0x18)-D_00189E20_6.z;
  if(aimDot>D_00189E20_6.max_height) aimDot=D_00189E20_6.max_height;
  else if(aimDot<0.0f) aimDot=0.0f;
  aimDot/=D_00189E20_6.max_height;
  height=aimDot+3.65f; dist=aimDot+aimDot;
 } else {height=4.64f;dist=2.0f;}
 ApproachValue(*(char **)(D_L00_001B8C80_1.follow+0x70)+0xA0,height,0.13333334f);
 ApproachValue(*(char **)(D_L00_001B8C80_1.follow+0x70)+0xB0,dist,0.06666667f);
 ApproachValue(*(char **)(D_L00_001B8C80_1.follow+0x70)+0x8C,dist-0.5f,0.13333334f);
 if(D_00189E20_6.state==0x2B) {
  if((gCurrentMapIndex!=14 && gCurrentMapIndex!=7 && gCurrentMapIndex!=9) || (D_00189E20_6.swing && *(unsigned char *)(D_00189E20_6.swing+0x21)==255)) {
   *(float *)angle=StepSpringDamperStored(*(float *)angle,D_00189E20_6.yaw,angle+4,0.00125f,0.175f,0.0f);
  } else {
   turn=angle+4; bestNode=0; closest=1000.0f;
   swing=D_00189E20_6.swing;
   list=D_L00_001FA920[*(unsigned char *)(swing+0x21)];
   if(list) do {
    node=D_L00_001B1E9C+(*list&0x7FFF)*0x100;
    if(node!=swing && (*(short *)(node+0xAA)==0x323 /* Swingshot Node */ || *(short *)(node+0xAA)==0x2F6 /* Swingshot Node */)) {
     FastVecSub(diff,node+0x10,swing+0x10);
     vec_scale_to_length(unit,diff,1.0f);
     axis[0]=FastSinOrCosA(D_00189E20_6.yaw);
     axis[1]=FastSinOrCosB(D_00189E20_6.yaw);axis[2]=0.0f;
     aimDot=FastVecDot(unit,(char *)axis);
     if(aimDot>0.0f) {score=FastVecLength(diff)-aimDot*10.0f;if(score<closest){bestNode=node;closest=score;}}
    }
   } while(*list++>=0);
   if(bestNode) {
    FastVecSub(diff,bestNode+0x10,swing+0x10);
    *(float *)angle=StepSpringDamperStored(*(float *)angle,FastMatrixHelperA(*(float *)diff,*(float *)(diff+4)),turn,0.00125f,0.175f,0.0f);
   } else if(*(int *)(part+0x40)==1)
    *(float *)angle=StepSpringDamperStored(*(float *)angle,*(float *)(*(char **)(part+0x44)+0xF8),turn,0.00125f,0.175f,0.0f);
   else
    *(float *)angle=StepSpringDamperStored(*(float *)angle,D_00189E20_6.yaw,turn,0.00125f,0.175f,0.0f);
  }
 } else if(D_00189E20_6.state==0x24) {
  if(*(int *)(part+0x40)==1)
   *(float *)angle=StepSpringDamperStored(*(float *)angle,*(float *)(*(char **)(part+0x44)+0xF8),angle+4,0.00125f,0.175f,0.0f);
  else
   *(float *)angle=StepSpringDamperStored(*(float *)angle,D_00189E20_6.yaw,angle+4,0.00125f,0.175f,0.0f);
 }
 *(float *)(part+0x30)=FastSinOrCosA(*(float *)angle);
 *(float *)(part+0x34)=FastSinOrCosB(*(float *)angle);
 *(float *)(part+0x38)=0.0f;*(float *)(part+0x3C)=*(float *)(part+0x38);
 vec_scale_to_length(out,part+0x30,-*(float *)cfg);
 *(float *)(out+8)+=*(float *)(cfg+0x10);
 func_00282CC0_4(out,out,gHeroPosition);
 if(FastDecTimer(vars+0x1E)) {qcopy(camera+0x30,out);} else {qcopy(camera+0x30,out);}
}
