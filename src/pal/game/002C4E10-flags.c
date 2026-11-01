#include "include_asm.h"

#include "common.h"
extern char *func_002C3F88(int,void *,float,float,int,int,int,void *);
extern void func_00283410(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282C88(void *);
extern int func_002A8860(void *, int);
void func_002B9180(void *);
int func_00282978(short *);
extern float func_00283CE0(int v);
extern void func_00282CC0(char *, char *, char *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282D30(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int v);
extern float func_00283198(float);
extern int func_002A8860(void *, int);

/* func_002C3F88 uses the quadword-copy profile in 002C3F88-qcopy.c. */

/* Updates an attached spark and emits children; mode 1 orbits its owner.
 * The interleaved prototype preserves each EE argument register bank. */
void func_PAL_002C4E10(char *p) {
 char *q=p+32; float v[4], w[4], rot[4], mat[16]; char *child;
 if(*(short *)(q+28)==0) {
  if(func_002A8860(p+4,*(short *)(q+26))) {func_002B9180(p);return;}
  if(*(char **)(q+12)) {
   v[0]=*(float *)(p+32);v[1]=*(float *)(q+4);v[2]=*(float *)(q+8);
   func_00282D30(v,v,func_00283CE0(*(short *)(q+24)));
   func_00282CC0(p+16,*(char **)(q+12)+16,(char *)v);
  }
  return;
 }
 if(func_00282978((short *)(p+10)) || (*(short *)(p+10)<8 && func_002A8860(p+4,16))) {func_002B9180(p);return;}
 if(*(short *)(q+28)==1)func_002C3F88(0,p+16,0,0,8,0,*(signed char *)(p+7),0);
 else {
  v[0]=*(float *)(q);v[1]=*(float *)(q+4);v[2]=*(float *)(q+8);
  child=func_002C3F88(*(int *)(q+12),p+16,0,0,8,0,*(signed char *)(p+7),v);
  if(child) *(short *)(child+56)=*(short *)(q+24);
 }
 if(*(short *)(q+28)==1) {
  qcopy(p+16,*(char **)(q+12)+16);
  v[0]=func_00283180(*(float *)(q+16))*2.25f;
  v[1]=func_00283198(*(float *)(q+16))*2.25f;
  v[2]=v[0]; v[0]=0;
  w[0]=func_00283180(*(float *)(q+20))*0.28f;
  w[1]=func_00283198(*(float *)(q+20))*0.28f;
  w[2]=w[0]; w[0]=0;
  func_00282C88(rot);rot[1]=*(float *)(q+16);
  func_00283410(mat,rot);func_002830C0(w,w,mat);
  func_00282CC0((char *)v,(char *)v,(char *)w);
  func_00283098(v,v,*(char **)(q+12)+192);
  func_00282CC0(p+16,p+16,(char *)v);
  *(float *)(q+16)=func_00283B98(*(float *)(q+16),0.019198624f);
  *(float *)(q+20)=func_00283B98(*(float *)(q+20),0.08726648f);
 }
}
