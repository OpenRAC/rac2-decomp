#include "include_asm.h"

#include "common.h"
extern void func_002ACB48(void *, float);
extern float func_00282E80(void *, void *);
extern void func_002A8F70(void *, int, int, void *, void *, float);
extern char *func_PAL_002C3798(void *, int, int, int, int, int, int, float, float);
extern unsigned char *D_001F2628;
extern char *D_001B1D90[] __attribute__((sda));
extern char D_00189EA0[];
typedef struct {
    char pad00[0x88];
    float height;
    char pad8C[0x2290 - 0x8C];
    void *owner;
} ParticleHero2C2C80;
extern int func_00283D38(int,int,float);
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_001163B0(void);
void func_002B9180(void *);
int func_00282978(short *);
extern float func_00283CE0(int v);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_001163B0(void);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283D38(int, int, float);
extern char D_00189EA0[];
extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int v);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* func_PAL_002C3798 uses the quadword-copy profile in 002C2A88-qcopy.c. */

void func_PAL_002C3990(char *p) {
 char *q=p+32; SplitVector v; int i; float f, a, speed;
 switch(*(unsigned char *)(q+20)) {
 case 0: {
  float duration=func_00283CE0(*(unsigned char *)(q+17));
  *(int *)(p+4)=func_00283D38(0xff4080ff,0,(duration-func_00283CE0(*(short *)(p+10)))/duration);
  if(func_00282978((short *)(p+10))) {
   if(*(unsigned char *)(q+16)==1)func_002B9180(p);
   else {*(unsigned char *)(q+20)=1;*(short *)(p+10)=*(unsigned char *)(q+18);}
  }
  break; }
 case 1:
  for(i=0;i<*(unsigned char *)(q+19);i++) {
   qcopy(&v,p+16);
   func_002ACB48(&v,0.05f);
   speed=1.0f;
   if(*(short *)(p+10)<8)speed=func_00283CE0(*(short *)(p+10))*0.125f;
   func_PAL_002C3798(&v,2,*(unsigned char *)(q+17),*(unsigned char *)(q+18),*(unsigned char *)(q+19),*(unsigned char *)(q+21),*(int *)(q+24),*(float *)(q+28),speed);
  }
  if(func_00282978((short *)(p+10)))func_002B9180(p);
  { char *pos=D_00189EA0; ParticleHero2C2C80 *hero;
  if(func_00282E80(p+16,pos)<0.3f) {
   hero=(ParticleHero2C2C80 *)(pos-128);
   if(hero->height<*(float *)(p+24)+1.2f) {
   func_00282CF0(&v,pos,p+16);
   func_00282F20(&v,&v,1.0f);v.f[2]=1.0f;
   func_002A8F70(hero->owner,*(int *)(q+24),1,p+16,&v,*(float *)(q+28));
  }}
  }
  break;
 case 2:
  func_00282CC0(p+16,p+16,q);
  a=func_00283CE0(*(unsigned char *)(q+21));
  f=(a-func_00283CE0(*(short *)(p+10)))/a;
  *(int *)(p+4)=func_00283D38((*(unsigned char *)(q+22)<<24)|0x4060,0x8fafff,f);
  if(f<0.6f)*(float *)(p+12)+=10836.001f;else *(float *)(p+12)-=2.016e+04f;
  p[2]=D_001F2628[func_001163B0()&7];
  if((((p-D_001B1D90[0])>>6)&1))p[8]++;else p[8]--;
  if(func_00282978((short *)(p+10)))func_002B9180(p);
  break;
 }
}
