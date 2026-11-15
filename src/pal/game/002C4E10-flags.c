#include "include_asm.h"

#include "common.h"
extern char *part_spawn_owned_spark(int,void *,float,float,int,int,int,void *);
extern void euler_to_matrix(void *,void *);
extern void transform_vector(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void vec_clear_128(void *);
extern int moby_decrement_top_byte(void *, int);
void part_kill(void *);
int FastDecTimer(short *);
extern float IntToFloat(int v);
extern void FastVecAdd(char *, char *, char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern float IntToFloat(int v);
extern float math_fast_sin_or_cos_b(float);
extern int moby_decrement_top_byte(void *, int);

/* func_002C3F88 uses the quadword-copy profile in 002C3F88-qcopy.c. */

/* Updates an attached spark and emits children; mode 1 orbits its owner.
 * The interleaved prototype preserves each EE argument register bank. */
void func_PAL_002C4E10(char *p) {
 char *q=p+32; float v[4], w[4], rot[4], mat[16]; char *child;
 if(*(short *)(q+28)==0) {
  if(moby_decrement_top_byte(p+4,*(short *)(q+26))) {part_kill(p);return;}
  if(*(char **)(q+12)) {
   v[0]=*(float *)(p+32);v[1]=*(float *)(q+4);v[2]=*(float *)(q+8);
   FastVecScale(v,v,IntToFloat(*(short *)(q+24)));
   FastVecAdd(p+16,*(char **)(q+12)+16,(char *)v);
  }
  return;
 }
 if(FastDecTimer((short *)(p+10)) || (*(short *)(p+10)<8 && moby_decrement_top_byte(p+4,16))) {part_kill(p);return;}
 if(*(short *)(q+28)==1)part_spawn_owned_spark(0,p+16,0,0,8,0,*(signed char *)(p+7),0);
 else {
  v[0]=*(float *)(q);v[1]=*(float *)(q+4);v[2]=*(float *)(q+8);
  child=part_spawn_owned_spark(*(int *)(q+12),p+16,0,0,8,0,*(signed char *)(p+7),v);
  if(child) *(short *)(child+56)=*(short *)(q+24);
 }
 if(*(short *)(q+28)==1) {
  qcopy(p+16,*(char **)(q+12)+16);
  v[0]=math_fast_sin_or_cos_a(*(float *)(q+16))*2.25f;
  v[1]=math_fast_sin_or_cos_b(*(float *)(q+16))*2.25f;
  v[2]=v[0]; v[0]=0;
  w[0]=math_fast_sin_or_cos_a(*(float *)(q+20))*0.28f;
  w[1]=math_fast_sin_or_cos_b(*(float *)(q+20))*0.28f;
  w[2]=w[0]; w[0]=0;
  vec_clear_128(rot);rot[1]=*(float *)(q+16);
  euler_to_matrix(mat,rot);transform_vector(w,w,mat);
  FastVecAdd((char *)v,(char *)v,(char *)w);
  matrix_mul_vec3(v,v,*(char **)(q+12)+192);
  FastVecAdd(p+16,p+16,(char *)v);
  *(float *)(q+16)=FastAddRotations(*(float *)(q+16),0.019198624f);
  *(float *)(q+20)=FastAddRotations(*(float *)(q+20),0.08726648f);
 }
}
