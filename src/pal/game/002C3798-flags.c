#include "include_asm.h"

#include "common.h"
extern void vec_add_random_offset(void *, float);
extern float vec_distance_xy(void *, void *);
extern void part_queue_impact_effect(void *, int, int, void *, void *, float);
extern char *func_PAL_002C3798(void *, int, int, int, int, int, int, float, float);
extern unsigned char *g_part_tex_burst_ember_table;
extern char *g_particle_pool_base[] __attribute__((sda));
extern char g_hero_position[];
typedef struct {
    char pad00[0x88];
    float height;
    char pad8C[0x2290 - 0x8C];
    void *owner;
} ParticleHero2C2C80;
extern int FastTweenColor(int,int,float);
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int func_001163B0(void);
void part_kill(void *);
int FastDecTimer(short *);
extern float IntToFloat(int v);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int func_001163B0(void);
extern void FastVecAdd(char *, char *, char *);
extern int FastTweenColor(int, int, float);
extern char g_hero_position[];
extern void FastVecAdd(char *, char *, char *);
extern float IntToFloat(int v);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* func_PAL_002C3798 uses the quadword-copy profile in 002C2A88-qcopy.c. */

void func_PAL_002C3990(char *p) {
 char *q=p+32; SplitVector v; int i; float f, a, speed;
 switch(*(unsigned char *)(q+20)) {
 case 0: {
  float duration=IntToFloat(*(unsigned char *)(q+17));
  *(int *)(p+4)=FastTweenColor(0xff4080ff,0,(duration-IntToFloat(*(short *)(p+10)))/duration);
  if(FastDecTimer((short *)(p+10))) {
   if(*(unsigned char *)(q+16)==1)part_kill(p);
   else {*(unsigned char *)(q+20)=1;*(short *)(p+10)=*(unsigned char *)(q+18);}
  }
  break; }
 case 1:
  for(i=0;i<*(unsigned char *)(q+19);i++) {
   qcopy(&v,p+16);
   vec_add_random_offset(&v,0.05f);
   speed=1.0f;
   if(*(short *)(p+10)<8)speed=IntToFloat(*(short *)(p+10))*0.125f;
   func_PAL_002C3798(&v,2,*(unsigned char *)(q+17),*(unsigned char *)(q+18),*(unsigned char *)(q+19),*(unsigned char *)(q+21),*(int *)(q+24),*(float *)(q+28),speed);
  }
  if(FastDecTimer((short *)(p+10)))part_kill(p);
  { char *pos=g_hero_position; ParticleHero2C2C80 *hero;
  if(vec_distance_xy(p+16,pos)<0.3f) {
   hero=(ParticleHero2C2C80 *)(pos-128);
   if(hero->height<*(float *)(p+24)+1.2f) {
   FastVecSub(&v,pos,p+16);
   vec_scale_to_length(&v,&v,1.0f);v.f[2]=1.0f;
   part_queue_impact_effect(hero->owner,*(int *)(q+24),1,p+16,&v,*(float *)(q+28));
  }}
  }
  break;
 case 2:
  FastVecAdd(p+16,p+16,q);
  a=IntToFloat(*(unsigned char *)(q+21));
  f=(a-IntToFloat(*(short *)(p+10)))/a;
  *(int *)(p+4)=FastTweenColor((*(unsigned char *)(q+22)<<24)|0x4060,0x8fafff,f);
  if(f<0.6f)*(float *)(p+12)+=10836.001f;else *(float *)(p+12)-=2.016e+04f;
  p[2]=g_part_tex_burst_ember_table[func_001163B0()&7];
  if((((p-g_particle_pool_base[0])>>6)&1))p[8]++;else p[8]--;
  if(FastDecTimer((short *)(p+10)))part_kill(p);
  break;
 }
}
