#include "include_asm.h"

#include "common.h"
extern int D_L15_001B187C __attribute__((sda));
extern char *D_L15_001B261C __attribute__((sda));
extern void func_L15_00437B68(void *,int);
extern int func_00282948(void *);
extern float func_002A7878(float,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_PAL_L15_00437CD0(void *,void *);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_PAL_L15_0043E840(void *,int,int);
extern void func_002E5DA0(int,int,void *,int);
extern void func_PAL_L05_0037D3D0(float);

void func_PAL_L15_0043DF7C(char *self) {
 char *state=*(char **)(self+0x68);
 char *obj,*basis,*pos,*axis;
 float a[4],b[4],c[4];
 float distance;
 if(!D_L15_001B187C) return;
 func_L15_00437B68(self,0);
 if(!func_00282948(state+0xC)) return;
 obj=D_L15_001B261C+(*(int *)state<<8);
 basis=obj+0xC0;
 qcopy(a,basis);
 axis=obj+0xE0;
 pos=obj+0x10;
 distance=800.0f;
 func_002ACEC0(a,a,axis,func_002A7878(-20.0f,20.0f)*0.01745329424738884f);
 func_00282F20(a,a,distance);
 func_00282CC0(a,a,pos);
 a[2]=distance;
 qcopy(b,a);
 b[2]=400.0f;
 func_PAL_L15_00437CD0(a,b);
 if(func_002A77E0(2)) func_PAL_L15_00437CD0(a,b);
 *(int *)(state+0xC)=((s32)(func_00283CF0(func_002A7878(90.0f,350.0f))) * 5 + 2) / 6;
 if(*(float *)(obj+0x18)>=565.0f) {
  qcopy(a,pos); qcopy(b,a);
  a[2]=distance;
  b[2]=*(float *)(obj+0x18)-100.0f;
  func_PAL_L15_00437CD0(a,b);
  qcopy(c,basis);
  func_00282F20(c,c,10.0f);
  func_00282CC0(c,pos,c);
  c[2]-=1.25f;
  func_PAL_L15_0043E840(c,40,0);
  func_002E5DA0(16,0,self,0xFBF);
  func_PAL_L05_0037D3D0(40.0f);
 }
 if(*(float *)(obj+0x18)<=415.0f) {
  qcopy(c,basis);
  func_00282F20(c,c,10.0f);
  func_00282CC0(c,pos,c);
  c[2]-=1.25f;
  func_PAL_L15_0043E840(c,40,0);
  func_002E5DA0(16,0,self,0xFBF);
  func_PAL_L05_0037D3D0(40.0f);
 }
}
