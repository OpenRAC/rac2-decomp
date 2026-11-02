/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* sol-high tier, USA v1.01, current game compiler, -O2 -G8.
 * Best: 1484/1484 bytes, 0/4 places; first mismatch +0x1B0.
 * Complete declarations below; use a dedicated -g8.c unit.
 * An incomplete sda timer table fixes its tied address construction and s6/s7
 * allocation. Indexing the global directly at the timer call also fixes addu
 * operand order. The remaining differences start at the outer-loop preheader:
 * the 10.0f bound is hoisted out of the outer loop, shifting vector-load setup;
 * the later position-pointer/countdown setup is also ordered differently.
 * Whole-file -mno-split-addresses, -fno-rerun-loop-opt and ordinary TI copies
 * with -frac2-qcopy/-frac2-qcopy-barrier were worse. An explicit bound local did
 * not keep the constant in the outer body. An explicit later position pointer
 * fixes its setup but substantially worsens the timer/prologue allocation.
 * Union vectors and float arrays tie; void-pointer views retain the best bytes.
 * 1 November 2026: indexed k loops fix the later pointer/countdown setup; only the
 * 10.0f hoist remains (13 rows). Retail keeps 10.0f in the outer body although it
 * is single-set, so something blocks the movable in the outer pass (maybe_never).
 * 1 November 2026, later: a do/while has one use of 10.0f (life 1), so it stays in
 * the inner loop (10 rows: retail has it in the outer body). With `for` the top test
 * gives a second use, the inner pass hoists it, and the outer pass hoists it again
 * because life is 84. Retail needs the first without the second. A second-pass inner
 * hoist needs at most 61 real insns (threshold) against 68 here.
 */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; float f[4]; } BurstVector;
extern void func_3D33E8(char *);
extern float func_3067D8(void *,void *);
extern void func_3719A8(int,int,void *,int);
extern int func_3062A0(void *);
extern void func_3068F8(void *,void *,float),func_306630(void *,void *,void *);
extern float func_332B50(float,float),func_332C18(void);
extern int func_332AF8(int,int),func_332AB8(int);
extern char *func_347040(void *,int,float,void *,int,int,float,float,float);
extern char *func_346748(void *,void *);
extern void func_33B330(void *,float,float,float);
extern int func_336380(int,int);
extern char *func_345D48(void *,void *,int,int,int,int,int,int,int,float);
extern void func_2FF698(void *,void *),func_L05_003D2618(void);
extern int D_L05_001B3000[] __attribute__((sda));
extern char D_L05_001B96C0[],D_L05_001B98F0[],D_L05_0024D020[];
extern float D_L05_001AFC94 __attribute__((sda));
void func_L05_003D2048(char *obj)
{
 BurstVector v,small,offset,pos,velocity;
 char *s=*(char **)(obj+0x68);
 int *timers=D_L05_001B3000;
 int color1,color2,duration;
 float scale,a,b;
 if (*(unsigned char *)(obj+0x20)==0) {
  func_3D33E8(obj);*(unsigned char *)(obj+0x20)=1;
  timers[*(int *)s]=5;
  if(func_3067D8(obj+0x10,D_L05_001B96C0)>200.0f) *(float *)(s+4)=4;
  else if(func_3067D8(obj+0x10,D_L05_001B96C0)>100.0f) *(float *)(s+4)=2;
  else if(func_3067D8(obj+0x10,D_L05_001B96C0)>25.0f) *(float *)(s+4)=1;
  else if(func_3067D8(obj+0x10,D_L05_001B96C0)>0.0f) *(float *)(s+4)=0.5f;
  func_3719A8(10,0,obj,0xFBF);
 }
 if(!func_3062A0(&D_L05_001B3000[*(int *)s]) && !*(int *)(s+8)) {
  int i;
  void *smallp=&small,*posp=&pos;
  for(i=0;i<4;i++) {
   int j;
   char *effect,*record;
   scale=D_L05_001AFC94*8.0f;
   qcopy(&v,D_L05_0024D020+*(int *)s*64+i*16);
   v.f[0]+=0.1f;
   func_3068F8(smallp,D_L05_001B98F0,0.20000002f);
   func_3068F8(&offset,D_L05_001B98F0,0.5f);
   func_306630(&v,&v,&offset);
   scale*=3.0f;
   j=0;
   do {
    pos.f[0]=v.f[0];pos.f[1]=v.f[1];pos.f[2]=v.f[2];
    velocity.f[0]=(func_332B50(0,0.1f)+ -0.05f)**(float *)(s+4);
    velocity.f[1]=(func_332B50(0,0.1f)+ -0.05f)**(float *)(s+4);
    velocity.f[2]=(func_332B50(0,0.1f)+ -0.05f)**(float *)(s+4);
    duration=func_332AF8(-3,3);
    effect=func_347040(posp,duration,0,&velocity,0x7F204080,0,1,1.02f,scale*210000.0f);
    if(effect) {
     record=effect+0x20;
     *(unsigned short *)(effect+0xA)=100;
     *(unsigned char *)(effect+8)=func_332AB8(255);
     *(unsigned char *)(effect+3)=0x48;
     *(int *)(record+4)=2;*(unsigned char *)(record+0xA)=127;
     *(unsigned char *)(record+0xB)=*(unsigned char *)(effect+0xA);
    }
    j++;
   } while((float)j<10.0f);
  }
  if(!*(int *)(s+8)) {
   int k;
   for(k=0;k<10;k++) {
    char *effect,*record;
    v.f[0]=func_332B50(-0.3f,0.3f)**(float *)(s+4);
    v.f[1]=func_332B50(-0.3f,0.3f)**(float *)(s+4);
    v.f[2]=func_332B50(-0.3f,0.3f)**(float *)(s+4);v.f[3]=0;
    effect=func_346748(obj+0x10,&v);
    if(effect) {
     record=effect+0x30;
     func_3068F8(&v,&v,1.0f);func_306630(effect+0x10,obj+0x10,&v);
     qcopy(effect+0x20,obj+0x10);
     *(float *)(record+0xC)=1;*(float *)(effect+0x1C)=0.05f;*(float *)(effect+0x2C)=0.25f;
    }
   }
   for(k=0;k<10;k++) {
    char *effect;
    a=func_332C18();b=func_332C18();
    func_33B330(&v,func_332B50(7,10.5f)*(*(float *)(s+4)*0.016666668f),b,a);
    v.f[2]+=0.050000004f;
    color1=func_336380(0x4F007FFF,0);color2=func_336380(0x1F00007F,0);
    duration=func_332AF8(60,120);
    effect=func_345D48(obj+0x10,&v,color1,color2,duration,1,-1,-1,0,40000.0f);
    if(effect) *(int *)(effect+0x2C)=0;
   }
  }
 }
 func_2FF698(func_L05_003D2618,obj);
}
