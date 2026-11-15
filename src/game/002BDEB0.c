#include "common.h"
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00300190(void *,void *);
static __inline__ float ParticleLifetimeFraction(float remaining, float lifetime)
{
 return remaining / lifetime;
}

/* Moves a puff particle and changes its see-through amount in steps: fade in, hold, then fade out. It disappears once it has faded out. */
void func_002BDEB0(char *particle)
{
 char *state=particle+32, *pos=particle+16;
 float fraction,denom;
 int color, rgb, alpha;
 particle[8]=(unsigned char)particle[8]+(unsigned char)state[8];
 FastVecAdd(pos,pos,particle+48);
 if (*(float *)(particle+28)!=0.0f) {
  if (*(float *)(particle+28)==2.0f) TransformVectorOrCopy(pos,pos);
  *(float *)(particle+28)=2.0f;
 }
 *(float *)(particle+12) *= 1.0f+(*(float *)(state+12)-1.0f);
 if (*(int *)(state+4)==0) {
  if (FastDecTimer(particle+10)) {
   *(int *)(state+4)=1; *(short *)(particle+10)=20;
   color=*(int *)state|0x7f000000;
  } else {
   alpha=FloatToInt((float)(10-*(short *)(particle+10))*9.6f);
   rgb=*(int *)state;
   color=((alpha+32)<<24)|rgb;
  }
 } else if (*(int *)(state+4)==2) {
  if (FastDecTimer(particle+10)) { KillParticle(particle); return; }
  else {
   denom=IntToFloat((unsigned char)state[11]);
   color=(FloatToInt((float)(unsigned char)state[10] * ParticleLifetimeFraction((float)*(short *)(particle+10),denom))<<24)|(*(int *)state&0xffffff);
  }
 } else if (*(int *)(state+4)==3) {
  FastDecTimer(particle+10);
  fraction=IntToFloat((unsigned char)state[11]-*(short *)(particle+10))/ *(float *)(state+28);
  if (fraction>1.0f) fraction=1.0f;
  *(int *)(particle+4)=(FloatToInt((float)(unsigned char)state[10]*fraction)<<24)|(*(int *)state&0xffffff);
  if ((unsigned char)state[11]-*(short *)(particle+10)>=FloatToInt(*(float *)(state+28))) {
   alpha=FloatToInt(*(float *)(state+28));
   *(int *)(state+4)=2; state[11]=(unsigned char)state[11]-alpha;
  }
  return;
 } else {
  if (FastDecTimer(particle+10)) { KillParticle(particle); return; }
  else color=(FloatToInt((float)*(short *)(particle+10)*6.35f)<<24)|*(int *)state;
 }
 *(int *)(particle+4)=color;
}
