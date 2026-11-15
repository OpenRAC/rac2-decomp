#include "names.h"
/* func_PAL_002BEB88, the PAL copy of func_002BDEB0: the same C, where wrap (*(float *)(q+12)-1.0f) (({e}) * 1.2f). */
#include "common.h"
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecAdd(void *,void *,void *);
extern void vec_transform_or_copy(void *,void *);
static __inline__ float ParticleLifetimeFraction(float remaining, float lifetime)
{
 return remaining / lifetime;
}

void func_PAL_002BEB88(char *p)
{
 char *q=p+32, *pos=p+16;
 float f,denom;
 int color, rgb, alpha;
 p[8]=(unsigned char)p[8]+(unsigned char)q[8];
 FastVecAdd(pos,pos,p+48);
 if (*(float *)(p+28)!=0.0f) {
  if (*(float *)(p+28)==2.0f) vec_transform_or_copy(pos,pos);
  *(float *)(p+28)=2.0f;
 }
 *(float *)(p+12) *= 1.0f+(((*(float *)(q+12)-1.0f)) * 1.2f);
 if (*(int *)(q+4)==0) {
  if (FastDecTimer(p+10)) {
   *(int *)(q+4)=1; *(short *)(p+10)=17;
   color=*(int *)q|0x7f000000;
  } else {
   alpha=FloatToInt((float)(8-*(short *)(p+10))*12.0f);
   rgb=*(int *)q;
   color=((alpha+32)<<24)|rgb;
  }
 } else if (*(int *)(q+4)==2) {
  if (FastDecTimer(p+10)) { part_kill(p); return; }
  else {
   denom=IntToFloat((unsigned char)q[11]);
   color=(FloatToInt((float)(unsigned char)q[10] * ParticleLifetimeFraction((float)*(short *)(p+10),denom))<<24)|(*(int *)q&0xffffff);
  }
 } else if (*(int *)(q+4)==3) {
  FastDecTimer(p+10);
  f=IntToFloat((unsigned char)q[11]-*(short *)(p+10))/ *(float *)(q+28);
  if (f>1.0f) f=1.0f;
  *(int *)(p+4)=(FloatToInt((float)(unsigned char)q[10]*f)<<24)|(*(int *)q&0xffffff);
  if ((unsigned char)q[11]-*(short *)(p+10)>=FloatToInt(*(float *)(q+28))) {
   alpha=FloatToInt(*(float *)(q+28));
   *(int *)(q+4)=2; q[11]=(unsigned char)q[11]-alpha;
  }
  return;
 } else {
  if (FastDecTimer(p+10)) { part_kill(p); return; }
  else color=(FloatToInt((float)*(short *)(p+10)*7.470588f)<<24)|*(int *)q;
 }
 *(int *)(p+4)=color;
}
