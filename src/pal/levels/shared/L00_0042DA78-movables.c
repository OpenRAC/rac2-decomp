#include "include_asm.h"

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
extern float func_002703B0(float, float, char *, float, float, float);
extern void func_00282CC0(char *, char *, char *);
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

void func_PAL_L00_0042DCD8(char *a)
{
 char out[16] __attribute__((aligned(16)));
 char diff[16] __attribute__((aligned(16)));
 char unit[16] __attribute__((aligned(16)));
 float axis[4] __attribute__((aligned(16)));
 char *s=*(char **)(a+0x70),*cfg=s+0xA0,*part=s+0x40,*angle=s+0xB8;
 char *p,*best,*obj,*turn;
 float height,dist,v,score,closest;
 short *list;
 if(D_00189E20_6.swing && D_00189E20_6.state==0x2B) {
  float v=*(float *)(D_00189E20_6.swing+0x18)-D_00189E20_6.z;
  if(v>D_00189E20_6.max_height) v=D_00189E20_6.max_height;
  else if(v<0.0f) v=0.0f;
  v/=D_00189E20_6.max_height;
  height=v+3.65f; dist=v+v;
 } else {height=4.64f;dist=2.0f;}
 func_002AA2E8(*(char **)(D_L00_001B8C80_1.follow+0x70)+0xA0,height,0.16000001f);
 func_002AA2E8(*(char **)(D_L00_001B8C80_1.follow+0x70)+0xB0,dist,0.080000006f);
 func_002AA2E8(*(char **)(D_L00_001B8C80_1.follow+0x70)+0x8C,dist-0.5f,0.16000001f);
 if(D_00189E20_6.state==0x2B) {
  if((D_001A79F0!=14 && D_001A79F0!=7 && D_001A79F0!=9) || (D_00189E20_6.swing && *(unsigned char *)(D_00189E20_6.swing+0x21)==255)) {
   *(float *)angle=func_002703B0(*(float *)angle,D_00189E20_6.yaw,angle+4,0.00125f,0.175f,0.0f);
  } else {
   turn=angle+4; best=0; closest=1000.0f;
   p=D_00189E20_6.swing;
   list=D_L00_001FA920[*(unsigned char *)(p+0x21)];
   if(list) do {
    obj=D_L00_001B1E9C+(*list&0x7FFF)*0x100;
    if(obj!=p && (*(short *)(obj+0xAA)==0x323 || *(short *)(obj+0xAA)==0x2F6)) {
     func_00282CF0(diff,obj+0x10,p+0x10);
     func_00282F20(unit,diff,1.0f);
     axis[0]=func_00283180(D_00189E20_6.yaw);
     axis[1]=func_00283198(D_00189E20_6.yaw);axis[2]=0.0f;
     v=func_00282DB0(unit,(char *)axis);
     if(v>0.0f) {score=func_00282DF0(diff)-v*10.0f;if(score<closest){best=obj;closest=score;}}
    }
   } while(*list++>=0);
   if(best) {
    func_00282CF0(diff,best+0x10,p+0x10);
    *(float *)angle=func_002703B0(*(float *)angle,func_00283248(*(float *)diff,*(float *)(diff+4)),turn,0.00125f,0.175f,0.0f);
   } else if(*(int *)(part+0x40)==1)
    *(float *)angle=func_002703B0(*(float *)angle,*(float *)(*(char **)(part+0x44)+0xF8),turn,0.00125f,0.175f,0.0f);
   else
    *(float *)angle=func_002703B0(*(float *)angle,D_00189E20_6.yaw,turn,0.00125f,0.175f,0.0f);
  }
 } else if(D_00189E20_6.state==0x24) {
  if(*(int *)(part+0x40)==1)
   *(float *)angle=func_002703B0(*(float *)angle,*(float *)(*(char **)(part+0x44)+0xF8),angle+4,0.00125f,0.175f,0.0f);
  else
   *(float *)angle=func_002703B0(*(float *)angle,D_00189E20_6.yaw,angle+4,0.00125f,0.175f,0.0f);
 }
 *(float *)(part+0x30)=func_00283180(*(float *)angle);
 *(float *)(part+0x34)=func_00283198(*(float *)angle);
 *(float *)(part+0x38)=0.0f;*(float *)(part+0x3C)=*(float *)(part+0x38);
 func_00282F20(out,part+0x30,-*(float *)cfg);
 *(float *)(out+8)+=*(float *)(cfg+0x10);
 func_00282CC0(out,out,D_00189EA0);
 if(func_00282978(s+0x1E)) {qcopy(a+0x30,out);} else {qcopy(a+0x30,out);}
}
