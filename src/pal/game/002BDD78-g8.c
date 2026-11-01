#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A9568(int,int,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern float D_001B168C __attribute__((sda));
extern float func_00282E48(void *,void *);
extern char D_001B5340[];
extern char *func_002BCF18(void *,void *,int,int,float,int,int);
typedef struct { float v[4]; } GravityTable;
extern GravityTable D_001AA350;

void func_PAL_002BDD78(char *p)
{
 char *q=p+32,*pos;
 struct { Quad saved; GravityTable gravity; } local;
 float f,d,size;
 int color,alpha,other,kind;
 local.gravity=D_001AA350;
 if(*(short *)(q+26)==3 && D_001B168C>0.95f) func_00282978(p+10);
 if(func_00282978(p+10)) {func_002B9180(p);return;}
 pos=p+16;
 f=func_00283CE0(*(short *)(p+10));
 *(int *)(p+4)=func_002A9568(*(int *)(q+20),*(int *)(q+16),f/func_00283CE0(*(short *)(q+24)));
 alpha=*(int *)(p+4)>>24;
 d=func_00282E48(pos,D_001B5340);
 if(*(short *)(p+10)<5) alpha=alpha* *(short *)(p+10)/5;
 if(d<4.0f) {func_002B9180(p);return;}
 if(d<8.0f) alpha=func_00283CF0(func_00283CE0(alpha)*(d-4.0f)*0.25f);
 *(int *)(p+4)=(alpha<<24)|(*(int *)(p+4)&0xffffff);
 func_00282CC0(pos,pos,q);
 kind=*(short *)(q+26);
 *(float *)(q+8)-=local.gravity.v[kind];
 qcopy(&local.saved,pos);
 if(*(float *)(p+24)<*(float *)(q+12)) {
  if(kind==1) {
   f=func_002A7878(0.25f,1.0f);
   color=func_002A9568(0x7f000000,0x7f182030,f);
   f=func_002A7878(0.5f,1.0f);
   other=func_002A9568(0,0x5f5f5f,f);
   *(float *)(q+8)=0.0f;
   size=func_002A7878(200000.0f,300000.0f);
   func_002BCF18(pos,q,color,other,size,func_002A7820(75,125),3);
  }
  func_002B9180(p);
 } else p[8]=(unsigned char)p[8]+1;
}
