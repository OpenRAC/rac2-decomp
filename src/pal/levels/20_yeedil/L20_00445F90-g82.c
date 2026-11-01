#include "include_asm.h"

#include "common.h"
extern float func_L20_00444B48(int,int,float,float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_002A89A8(char *,int,float);
extern void func_L20_00442E68(char *);
extern void func_L20_00444138(char *,int);
extern void func_002A7750(char *,int,int);
extern void func_PAL_002A7E68(char *,int,int,int);
extern char *func_002A9640(char *,int,int);
extern float func_PAL_002AA108(char *,char *);
extern void func_002AA2E8(char *,float,float);
extern int func_00288AA0(char *,int);
extern void func_00288BE8(char *);
extern void func_PAL_002A7650(char *,int,int);
extern void func_002F5CB8(void (*)(int),char *);
extern void func_L20_00444C68(int);
extern void func_L20_0039E890(int,float);
extern void func_002B3BA8(char *,int,float,float,int,int);
extern void func_002833F0(char *,char *);
extern const float D_L20_001B2030 __attribute__((sda));
extern const float D_L20_001B2034 __attribute__((sda));
extern char D_L20_001C01C0[];

void func_PAL_L20_004476F0(char *obj) {
 char *st=*(char **)(obj+0x68), *p;
 float f, h;
 if (*(u8 *)(obj+0x20)==0) {
  *(int *)(st+0x1854)=-1;
  *(short *)(obj+0x32)=255; *(u8 *)(obj+0x30)=255;
  { float scale=func_L20_00444B48(5,20,1.0f,0.5f);
  *(float *)(st+0x20)=*(float *)(st+0x20)*scale;
  *(short *)(st+0x24)=func_00283CF0((float)*(short *)(st+0x24)*scale); }
  *(float *)(st+0x54)=0.5f; *(float *)(st+0x50)=4.0f;
  *(float *)(st+0xE0)=func_002A89A8(obj+0x10,0,0.5f);
  *(float *)(st+0x58)=2.0f; *(float *)(st+0x5C)=2.0f;
  *(float *)(st+0x60)=3.1415927f; *(int *)(st+0x184C)=15;
  f=func_00283CE0(*(short *)(st+0x24));
  *(float *)(st+0x1828)=(2.0f-(float)*(int *)(st+0x182C))*(f*0.33333f);
  func_L20_00442E68(obj); func_L20_00444138(obj,0);
  *(float *)(obj+0x18)+=5.0f;
  *(float *)(obj+0x18)=func_002A89A8(obj+0x10,0,0.5f);
  *(u16 *)(obj+0x34)|=0x400; *(int *)(obj+0x9C)=2;
  func_002A7750(obj,24,6);
  if (*(u8 *)(obj+0x43)!=1) func_PAL_002A7E68(obj,1,0,0);
  *(u8 *)(st+0x48)=func_00283CF0(15.0f);
  *(u8 *)(st+0x4A)=func_00283CF0(12.8f);
  *(u16 *)(obj+0x34)|=0x1000;
  qcopy(st+0x17E0,obj+0x10);
 }
 if (*(u8 *)(obj+0x95)==6) return;
 *(float *)(obj+0x2C)=*(float *)(*(char **)(obj+0x24)+0x24)*D_L20_001B2030;
 *(float *)(st+0x30)=D_L20_001B2034;
 p=func_002A9640(obj,0x10000,0);
 if(p && (p=*(char **)(p+0x20))) {
  switch (*(short *)(p+0xAA)) { case 0x5DE: case 0x3A6: case 0xD0F: *(u8 *)(obj+0xA8)=255; }
 }
 h=func_PAL_002AA108(obj,func_002A9640(obj,0x10000,0));
 func_002AA2E8(st+0x20,0.0f,h); *(u8 *)(obj+0xA8)=255;
 f=*(float *)(st+0x20);
 if(f<=0.0f || *(u8 *)(st+0x2E)==2) {
  *(float *)(st+0x20)=0.0f;
  if(!func_00288AA0(D_L20_001C01C0,0xA1)) goto done;
  if(*(u8 *)(st+0x2E)!=2) func_PAL_002A7650(obj,0,3);
  func_00288AA0(D_L20_001C01C0,0xA0); func_00288BE8(D_L20_001C01C0);
  func_002A7750(obj,17,6); func_002F5CB8(func_L20_00444C68,obj);
 } else if(f<=*(float *)(st+0x1828)) {
  func_002A7750(obj,15,5); ++*(int *)(st+0x182C);
  f=func_00283CE0(*(short *)(st+0x24));
  *(float *)(st+0x1804)=0.0f; *(float *)(st+0x1800)=0.0f;
  *(float *)(st+0x1828)=(2.0f-(float)*(int *)(st+0x182C))*(f*0.33333f);
  if(*(int *)(st+0x182C)==2) func_L20_0039E890(*(int *)(st+0x244),-1.0f);
 } else if(h!=0.0f && (p=*(char **)(st+0x38)) && *(short *)(p+0xAA)==0x12D3) {
  func_002A7750(obj,15,5); *(float *)(st+0x1804)=0.0f; *(float *)(st+0x1800)=0.0f; *(u8 *)(obj+0xBC)=1;
 }
done:
 *(u8 *)(st+0x2E)=1;
 func_002B3BA8(obj,*(int *)(st+0x220),64.0f,0.0f,0,0);
 qcopy(obj+0x10,st+0x17E0);
 if(*(float *)(obj+0xF0)!=0.0f || *(float *)(obj+0xF4)!=0.0f) {
  *(float *)(obj+0xF4)=0.0f; *(float *)(obj+0xF0)=0.0f; func_002833F0(obj+0xC0,obj+0xF0);
 }
}
